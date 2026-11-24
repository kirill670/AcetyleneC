#include "ac.h"
#include <stdarg.h>

int ac_verbose = 0;

void *ac_alloc(size_t n)
{
    void *p = malloc(n ? n : 1);
    if (!p)
        ac_die("out of memory allocating %u bytes", (unsigned)n);
    return p;
}

void *ac_calloc(size_t n, size_t sz)
{
    void *p = calloc(n ? n : 1, sz ? sz : 1);
    if (!p)
        ac_die("out of memory allocating %u x %u bytes", (unsigned)n, (unsigned)sz);
    return p;
}

void *ac_realloc(void *p, size_t n)
{
    void *q = realloc(p, n ? n : 1);
    if (!q)
        ac_die("out of memory reallocating %u bytes", (unsigned)n);
    return q;
}

char *ac_strdup(const char *s)
{
    size_t n = strlen(s) + 1;
    char *p = ac_alloc(n);
    memcpy(p, s, n);
    return p;
}

void buf_init(Buf *b)
{
    b->data = NULL;
    b->len = 0;
    b->cap = 0;
}

void buf_free(Buf *b)
{
    free(b->data);
    b->data = NULL;
    b->len = b->cap = 0;
}

void buf_reserve(Buf *b, size_t extra)
{
    size_t need = b->len + extra;
    size_t cap;
    if (need <= b->cap)
        return;
    cap = b->cap ? b->cap : 256;
    while (cap < need)
        cap += cap / 2 + 64;
    b->data = ac_realloc(b->data, cap);
    b->cap = cap;
}

void buf_put(Buf *b, const void *p, size_t n)
{
    if (!n)
        return;
    buf_reserve(b, n);
    memcpy(b->data + b->len, p, n);
    b->len += n;
}

void buf_u8(Buf *b, u8 v)
{
    buf_reserve(b, 1);
    b->data[b->len++] = v;
}

void buf_u16(Buf *b, u16 v)
{
    buf_reserve(b, 2);
    wr16(b->data + b->len, v);
    b->len += 2;
}

void buf_u32(Buf *b, u32 v)
{
    buf_reserve(b, 4);
    wr32(b->data + b->len, v);
    b->len += 4;
}

void buf_zeros(Buf *b, size_t n)
{
    if (!n)
        return;
    buf_reserve(b, n);
    memset(b->data + b->len, 0, n);
    b->len += n;
}

size_t buf_align(Buf *b, size_t a)
{
    size_t pad;
    if (a < 2)
        return b->len;
    pad = (a - (b->len % a)) % a;
    buf_zeros(b, pad);
    return b->len;
}

int ac_read_file(const char *path, Buf *out)
{
    FILE *f = fopen(path, "rb");
    long n;
    buf_init(out);
    if (!f)
        return -1;
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return -1;
    }
    n = ftell(f);
    if (n < 0) {
        fclose(f);
        return -1;
    }
    rewind(f);
    buf_reserve(out, (size_t)n);
    if (n && fread(out->data, 1, (size_t)n, f) != (size_t)n) {
        fclose(f);
        buf_free(out);
        return -1;
    }
    out->len = (size_t)n;
    fclose(f);
    return 0;
}

int ac_write_file(const char *path, const void *data, size_t len)
{
    FILE *f = fopen(path, "wb");
    if (!f)
        return -1;
    if (len && fwrite(data, 1, len, f) != len) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

void ac_die(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fputs("acetylene: error: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
    exit(1);
}

void ac_warn(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fputs("acetylene: warning: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
}

void ac_info(const char *fmt, ...)
{
    va_list ap;
    if (!ac_verbose)
        return;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
}

const char *ac_basename(const char *p)
{
    const char *s = p, *b = p;
    for (; *s; s++)
        if (*s == '/' || *s == '\\')
            b = s + 1;
    return b;
}

const char *ac_ext(const char *p)
{
    const char *s = p, *d = NULL;
    for (; *s; s++)
        if (*s == '.')
            d = s;
    return d ? d : "";
}

int ac_has_ext(const char *p, const char *e)
{
    size_t n = strlen(p), m = strlen(e);
    if (m > n)
        return 0;
    return strcmp(p + n - m, e) == 0;
}

void sv_init(StrVec *v)
{
    v->items = NULL;
    v->count = 0;
    v->cap = 0;
}

void sv_push(StrVec *v, const char *s)
{
    if (v->count == v->cap) {
        v->cap = v->cap ? v->cap * 2 : 8;
        v->items = ac_realloc(v->items, sizeof(char *) * (size_t)v->cap);
    }
    v->items[v->count++] = ac_strdup(s);
}

void sv_free(StrVec *v)
{
    int i;
    for (i = 0; i < v->count; i++)
        free(v->items[i]);
    free(v->items);
    sv_init(v);
}
