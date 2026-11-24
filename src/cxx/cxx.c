#include "../common/ac.h"

typedef struct {
    char name[96];
    char fields[64][96];
    int nfields;
    char methods[64][96];
    char mrets[64][64];
    int nmethods;
} Cls;

typedef struct {
    Cls *classes;
    int nclasses;
    Buf out;
    Buf meta;
    Buf decls;
    const char *file;
    int errors;
} Cx;

static int is_type_word(const char *s);

static const char NL_STR[2] = {10, 0};

static void put_line(Buf *b, const char *s)
{
    size_t n = strlen(s);
    buf_put(b, s, n);
    buf_u8(b, 0x0a);
}

static Cls *find_cls(Cx *c, const char *name)
{
    int i;
    for (i = 0; i < c->nclasses; i++)
        if (strcmp(c->classes[i].name, name) == 0)
            return &c->classes[i];
    return NULL;
}

static int is_id_start(int ch) { return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'; }
static int is_id_char(int ch) { return is_id_start(ch) || (ch >= '0' && ch <= '9'); }

static void warn_once(Cx *c, const char *fmt, const char *arg)
{
    fprintf(stderr, "acetylene-cxx: ");
    fprintf(stderr, fmt, arg);
    fprintf(stderr, " (%s)\n", c->file);
    c->errors++;
}

static int is_field(Cls *cls, const char *name)
{
    int i;
    for (i = 0; i < cls->nfields; i++)
        if (strcmp(cls->fields[i], name) == 0)
            return 1;
    return 0;
}

static int is_method(Cls *cls, const char *name)
{
    int i;
    for (i = 0; i < cls->nmethods; i++)
        if (strcmp(cls->methods[i], name) == 0)
            return 1;
    return 0;
}

static void mangle(char *out, size_t cap, const char *cls, const char *method, int is_ctor, int is_dtor)
{
    if (is_ctor)
        snprintf(out, cap, "_ZN%u%sC1Ev", (unsigned)strlen(cls), cls);
    else if (is_dtor)
        snprintf(out, cap, "_ZN%u%sD1Ev", (unsigned)strlen(cls), cls);
    else
        snprintf(out, cap, "_ZN%u%s%u%sEv", (unsigned)strlen(cls), cls, (unsigned)strlen(method), method);
}

static const char *trim(const char *s)
{
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
        s++;
    return s;
}

static void rtrim(char *s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\r' || s[n - 1] == '\n'))
        s[--n] = 0;
}

typedef struct {
    char **lines;
    int count;
} Lines;

static Lines split_lines(Buf *b)
{
    Lines l;
    char *p = (char *)b->data;
    char *end = (char *)b->data + b->len;
    int cap = 128;
    l.lines = ac_calloc((size_t)cap, sizeof(char *));
    l.count = 0;
    while (p < end) {
        char *nl = memchr(p, '\n', (size_t)(end - p));
        size_t len = nl ? (size_t)(nl - p) : (size_t)(end - p);
        char *line = ac_calloc(len + 1, 1);
        memcpy(line, p, len);
        if (l.count == cap) {
            cap *= 2;
            l.lines = ac_realloc(l.lines, sizeof(char *) * (size_t)cap);
        }
        l.lines[l.count++] = line;
        if (!nl)
            break;
        p = nl + 1;
    }
    return l;
}

static void strip_comments(Buf *b)
{
    size_t i = 0, j = 0;
    while (i < b->len) {
        if (b->data[i] == '/' && i + 1 < b->len && b->data[i + 1] == '/') {
            while (i < b->len && b->data[i] != '\n')
                i++;
            continue;
        }
        if (b->data[i] == '/' && i + 1 < b->len && b->data[i + 1] == '*') {
            i += 2;
            while (i + 1 < b->len && !(b->data[i] == '*' && b->data[i + 1] == '/'))
                i++;
            i += 2;
            continue;
        }
        b->data[j++] = b->data[i++];
    }
    b->len = j;
}

static void rewrite_body(Cx *c, Cls *cls, const char *body, size_t len, Buf *out)
{
    size_t i = 0;
    (void)c;
    while (i < len) {
        if (is_id_start((unsigned char)body[i])) {
            char id[96];
            size_t n = 0;
            while (i < len && is_id_char((unsigned char)body[i]) && n < 95)
                id[n++] = body[i++];
            id[n] = 0;
            if (is_field(cls, id)) {
                buf_put(out, "self->", 6);
                buf_put(out, id, strlen(id));
                continue;
            }
            if (is_method(cls, id)) {
                char mg[256];
                size_t q;
                mangle(mg, sizeof(mg), cls->name, id, 0, 0);
                buf_put(out, mg, strlen(mg));
                buf_put(out, "(self", 5);
                q = i;
                while (q < len && (body[q] == ' ' || body[q] == '\t'))
                    q++;
                if (q < len && body[q] == '(') {
                    int depth = 0;
                    q++;
                    while (q < len) {
                        if (body[q] == '(')
                            depth++;
                        if (body[q] == ')') {
                            if (depth == 0)
                                break;
                            depth--;
                        }
                        q++;
                    }
                    {
                        char args[512];
                        size_t alen = 0;
                        size_t k;
                        for (k = i + 1; k < q && alen < 500; k++) {
                            char ch = body[k];
                            if (ch == '(' || ch == ')' || ch == ' ' || ch == '\t')
                                continue;
                            args[alen++] = ch;
                        }
                        args[alen] = 0;
                        if (alen)
                            buf_put(out, ", ", 2);
                        {
                            Buf sub;
                            buf_init(&sub);
                            rewrite_body(c, cls, args, alen, &sub);
                            buf_put(out, sub.data, sub.len);
                            buf_free(&sub);
                        }
                    }
                    i = q + 1;
                }
                buf_put(out, ")", 1);
                continue;
            }
            buf_put(out, id, strlen(id));
            continue;
        }
        buf_u8(out, (u8)body[i++]);
    }
}

static int parse_class_lines(Cx *c, Lines *ls, int start, const char *cls_name, const char *base_ignored)
{
    Cls cls;
    int i = start;
    int depth = 1;
    memset(&cls, 0, sizeof(cls));
    snprintf(cls.name, sizeof(cls.name), "%s", cls_name);
    (void)base_ignored;
    while (i < ls->count) {
        char line[512];
        char *s;
        snprintf(line, sizeof(line), "%s", ls->lines[i]);
        rtrim(line);
        s = (char *)trim(line);
        i++;
        if (!*s)
            continue;
        if (s[0] == '}') {
            depth--;
            if (depth == 0)
                break;
            continue;
        }
        if (strncmp(s, "public", 6) == 0 || strncmp(s, "private", 7) == 0 || strncmp(s, "protected", 9) == 0) {
            continue;
        }
        if (strncmp(s, "virtual", 7) == 0) {
            warn_once(c, "unsupported: %s", "virtual methods");
            continue;
        }
        if (strncmp(s, "static ", 7) == 0)
            s = (char *)trim(s + 7);
        if (strncmp(s, "const ", 6) == 0)
            s = (char *)trim(s + 6);
        if (strncmp(s, "inline ", 7) == 0)
            s = (char *)trim(s + 7);
        if (!*s)
            continue;
        {
            char *paren = strchr(s, '(');
            if (paren) {
                char name[96];
                int n = 0;
                char *q = paren;
                while (q > s && (q[-1] == ' ' || q[-1] == '\t'))
                    q--;
                {
                    char *e = q;
                    while (e > s && is_id_char((unsigned char)e[-1]))
                        e--;
                    while (*e && is_id_char((unsigned char)*e) && n < 95)
                        name[n++] = *e++;
                }
                name[n] = 0;
                if (name[0]) {
                    char rt[64];
                    char head[256];
                    size_t hl = (size_t)((q < s + 0) ? 0 : 0);
                    (void)hl;
                    memset(head, 0, sizeof(head));
                    {
                        const char *p0 = s;
                        const char *p1 = q;
                        while (p1 > p0 && (p1[-1] == 32 || p1[-1] == 9))
                            p1--;
                        while (p1 > p0 && is_id_char((unsigned char)p1[-1]))
                            p1--;
                        {
                            size_t len = (size_t)(p1 - p0);
                            if (len > 200)
                                len = 200;
                            memcpy(head, p0, len);
                        }
                    }
                    rt[0] = 0;
                    {
                        char *tok = strtok(head, " ");
                        while (tok) {
                            if (is_type_word(tok) && strcmp(tok, "const") != 0 &&
                                strcmp(tok, "static") != 0 && strcmp(tok, "inline") != 0) {
                                snprintf(rt, sizeof(rt), "%s", tok);
                                break;
                            }
                            tok = strtok(NULL, " ");
                        }
                    }
                    if (strcmp(name, cls.name) == 0 || name[0] == '~') {
                        if (cls.nmethods < 64) {
                            snprintf(cls.methods[cls.nmethods], 96, "%s", cls.name);
                            cls.mrets[cls.nmethods][0] = 0;
                            cls.nmethods++;
                        }
                    } else if (cls.nmethods < 64) {
                        snprintf(cls.methods[cls.nmethods], 96, "%s", name);
                        snprintf(cls.mrets[cls.nmethods], 64, "%s", rt);
                        cls.nmethods++;
                    }
                }
                {
                    int d = 0;
                    char *p = paren;
                    while (*p) {
                        if (*p == '{')
                            d++;
                        if (*p == '}') {
                            d--;
                            if (d < 0) {
                                depth--;
                                break;
                            }
                        }
                        p++;
                    }
                }
                continue;
            }
            {
                char *semi = strchr(s, ';');
                if (semi) {
                    char name[96];
                    int n = 0;
                    char *e = semi;
                    while (e > s && (e[-1] == ' ' || e[-1] == '\t'))
                        e--;
                    while (e > s && is_id_char((unsigned char)e[-1]))
                        e--;
                    while (*e && *e != ';' && *e != '[' && *e != ' ' && n < 95)
                        name[n++] = *e++;
                    name[n] = 0;
                    if (name[0] && cls.nfields < 64)
                        snprintf(cls.fields[cls.nfields++], 96, "%s", name);
                }
            }
        }
    }
    c->classes[c->nclasses++] = cls;
    buf_put(&c->decls, "typedef struct ", 15);
    buf_put(&c->decls, cls.name, strlen(cls.name));
    buf_put(&c->decls, " {\n", 3);
    {
        int k;
        for (k = 0; k < cls.nfields; k++) {
            buf_put(&c->decls, "    TInt ", 9);
            buf_put(&c->decls, cls.fields[k], strlen(cls.fields[k]));
            buf_put(&c->decls, ";\n", 2);
        }
    }
    buf_put(&c->decls, "} ", 2);
    buf_put(&c->decls, cls.name, strlen(cls.name));
    buf_put(&c->decls, ";\n\n", 3);
    return i;
}

static int is_type_word(const char *s)
{
    static const char *t[] = {"void", "TInt", "TUint", "TBool", "TInt64", "char", "int", "short", "long",
                              "unsigned", "float", "double", "const", 0};
    int i;
    for (i = 0; t[i]; i++)
        if (strcmp(s, t[i]) == 0)
            return 1;
    return 0;
}

static void translate_methods(Cx *c, Buf *src)
{
    const char *s = (const char *)src->data;
    const char *end = s + src->len;
    const char *p = s;
    while ((p = strstr(p, "::")) != NULL) {
        const char *stmt = p;
        char cls_name[96];
        char meth[96];
        char ret[64];
        const char *q;
        Cls *cls;
        int n;
        while (stmt > s && stmt[-1] != ';' && stmt[-1] != '}' && stmt[-1] != '{')
            stmt--;
        q = p;
        n = 0;
        while (q > stmt && (q[-1] == 32 || q[-1] == 9 || q[-1] == 10))
            q--;
        while (q > stmt && is_id_char((unsigned char)q[-1]))
            q--;
        {
            const char *r = q;
            while (r < p && is_id_char((unsigned char)*r) && n < 95)
                cls_name[n++] = *r++;
        }
        cls_name[n] = 0;
        ret[0] = 0;
        {
            char head[256];
            size_t hl = (size_t)(q - stmt);
            char *tok;
            if (hl > 200)
                hl = 200;
            memcpy(head, stmt, hl);
            head[hl] = 0;
            tok = strtok(head, " ");
            while (tok) {
                if (is_type_word(tok) && strcmp(tok, "const") != 0) {
                    snprintf(ret, sizeof(ret), "%s", tok);
                    break;
                }
                tok = strtok(NULL, " ");
            }
        }
        {
            const char *r = p + 2;
            n = 0;
            while (*r == 32 || *r == 9 || *r == 10)
                r++;
            if (*r == '~') {
                warn_once(c, "unsupported: %s", "destructors");
                p = r + 1;
                continue;
            }
            while (is_id_char((unsigned char)*r) && n < 95)
                meth[n++] = *r++;
            meth[n] = 0;
            if (!meth[0] || !cls_name[0]) {
                p += 2;
                continue;
            }
            cls = find_cls(c, cls_name);
            if (!cls) {
                p += 2;
                continue;
            }
            {
                const char *paren = strchr(r, '(');
                const char *body;
                if (!paren) {
                    p += 2;
                    continue;
                }
                body = strchr(paren, '{');
                if (!body) {
                    p += 2;
                    continue;
                }
                {
                    const char *close = paren;
                    int pd = 0;
                    while (close < body) {
                        if (*close == 40)
                            pd++;
                        if (*close == 41) {
                            pd--;
                            if (pd == 0)
                                break;
                        }
                        close++;
                    }
                    char params[256];
                    size_t plen;
                    const char *be = body + 1;
                    int d = 1;
                    while (be < end && d > 0) {
                        if (*be == '{')
                            d++;
                        if (*be == '}')
                            d--;
                        if (d == 0)
                            break;
                        be++;
                    }
                    if (!close || close > body) {
                        p += 2;
                        continue;
                    }
                    plen = (size_t)(close - paren - 1);
                    if (plen > 200)
                        plen = 200;
                    memcpy(params, paren + 1, plen);
                    params[plen] = 0;
                    if (strstr(params, "&")) {
                        warn_once(c, "unsupported: %s", "references");
                        p = be;
                        continue;
                    }
                    {
                        Buf bodyb;
                        char hdr[512];
                        char mg[256];
                        int is_ctor = strcmp(meth, cls->name) == 0;
                        {
                            int mi;
                            for (mi = 0; mi < cls->nmethods; mi++) {
                                if (strcmp(cls->methods[mi], meth) == 0 && cls->mrets[mi][0]) {
                                    snprintf(ret, sizeof(ret), "%s", cls->mrets[mi]);
                                    break;
                                }
                            }
                        }
                        char selfp[96];
                        char trimmed[256];
                        snprintf(selfp, sizeof(selfp), "struct %s *self", cls->name);
                        snprintf(trimmed, sizeof(trimmed), "%s", params);
                        rtrim(trimmed);
                        buf_init(&bodyb);
                        rewrite_body(c, cls, body + 1, (size_t)(be - body - 1), &bodyb);
                        mangle(mg, sizeof(mg), cls->name, meth, is_ctor, 0);
                        {
                            char *t = (char *)trim(trimmed);
                            if (!*t || strcmp(t, "void") == 0)
                                snprintf(hdr, sizeof(hdr), "%s%s %s(%s)%s{%s", NL_STR,
                                         is_ctor ? "void" : (ret[0] ? ret : "TInt"), mg, selfp, NL_STR, NL_STR);
                            else
                                snprintf(hdr, sizeof(hdr), "%s%s %s(%s, %s)%s{%s", NL_STR,
                                         is_ctor ? "void" : (ret[0] ? ret : "TInt"), mg, selfp, t, NL_STR, NL_STR);
                        }
                        buf_put(&c->out, hdr, strlen(hdr));
                        buf_put(&c->out, bodyb.data, bodyb.len);
                        buf_put(&c->out, NL_STR, 1);
                        buf_put(&c->out, "}", 1);
                        buf_put(&c->out, NL_STR, 1);
                        buf_free(&bodyb);
                        printf("method %s::%s -> %s\n", cls->name, meth, mg);
                    }
                    p = be + 1;
                }
            }
        }
    }
}

static Cls *class_of_method(Cx *c, const char *meth)
{
    int i;
    for (i = 0; i < c->nclasses; i++) {
        if (is_method(&c->classes[i], meth))
            return &c->classes[i];
    }
    return NULL;
}

static void rewrite_free_calls(Cx *c, const char *body, size_t len, Buf *out)
{
    size_t i = 0;
    while (i < len) {
        if (is_id_start((unsigned char)body[i])) {
            char a[96];
            size_t n = 0;
            size_t start = i;
            while (i < len && is_id_char((unsigned char)body[i]) && n < 95)
                a[n++] = body[i++];
            a[n] = 0;
            if (i < len && body[i] == '.' && i + 1 < len && is_id_start((unsigned char)body[i + 1])) {
                char m[96];
                size_t mn = 0;
                size_t j = i + 1;
                Cls *k;
                while (j < len && is_id_char((unsigned char)body[j]) && mn < 95)
                    m[mn++] = body[j++];
                m[mn] = 0;
                k = class_of_method(c, m);
                if (k) {
                    size_t q = j;
                    while (q < len && (body[q] == ' ' || body[q] == 9))
                        q++;
                    if (q < len && body[q] == '(') {
                        char mg[256];
                        size_t depth = 0;
                        size_t astart = q + 1;
                        size_t aend;
                        mangle(mg, sizeof(mg), k->name, m, strcmp(m, k->name) == 0, 0);
                        q++;
                        while (q < len) {
                            if (body[q] == '(')
                                depth++;
                            if (body[q] == ')') {
                                if (depth == 0)
                                    break;
                                depth--;
                            }
                            q++;
                        }
                        aend = q;
                        buf_put(out, mg, strlen(mg));
                        buf_put(out, "(&", 2);
                        buf_put(out, a, strlen(a));
                        if (aend > astart) {
                            buf_put(out, ", ", 2);
                            buf_put(out, body + astart, aend - astart);
                        }
                        buf_put(out, ")", 1);
                        i = q + 1;
                        continue;
                    }
                }
            } else if (n == 1 && i < len && body[i] == '.' && i + 1 < len && body[i + 1] == '~') {
                buf_put(out, a, n);
                continue;
            } else if (i + 1 < len && body[i] == '-' && body[i + 1] == '>') {
                size_t j = i + 2;
                char m[96];
                size_t mn = 0;
                Cls *k;
                while (j < len && is_id_char((unsigned char)body[j]) && mn < 95)
                    m[mn++] = body[j++];
                m[mn] = 0;
                k = class_of_method(c, m);
                if (k && j < len && body[j] == '(') {
                    char mg[256];
                    size_t q = j;
                    size_t depth = 0;
                    size_t astart;
                    size_t aend;
                    mangle(mg, sizeof(mg), k->name, m, 0, 0);
                    q++;
                    astart = q;
                    while (q < len) {
                        if (body[q] == '(')
                            depth++;
                        if (body[q] == ')') {
                            if (depth == 0)
                                break;
                            depth--;
                        }
                        q++;
                    }
                    aend = q;
                    buf_put(out, mg, strlen(mg));
                    buf_put(out, "(", 1);
                    buf_put(out, a, strlen(a));
                    if (aend > astart) {
                        buf_put(out, ", ", 2);
                        buf_put(out, body + astart, aend - astart);
                    }
                    buf_put(out, ")", 1);
                    i = q + 1;
                    continue;
                }
            }
            buf_put(out, a, n);
            (void)start;
            continue;
        }
        buf_u8(out, (u8)body[i++]);
    }
}

static void translate_plain(Cx *c, Lines *ls)
{
    int i;
    int in_class = -1;
    int in_method = 0;
    int depth = 0;
    for (i = 0; i < ls->count; i++) {
        char line[1024];
        char *s;
        snprintf(line, sizeof(line), "%s", ls->lines[i]);
        rtrim(line);
        s = (char *)trim(line);
        if (in_class >= 0)
            continue;
        if (in_method) {
            int k;
            for (k = 0; s[k]; k++) {
                if (s[k] == '{')
                    depth++;
                if (s[k] == '}') {
                    depth--;
                    if (depth <= 0) {
                        in_method = 0;
                        break;
                    }
                }
            }
            continue;
        }
        if (strstr(s, "::") && strchr(s, '(')) {
            in_method = 1;
            depth = 0;
            {
                int k;
                for (k = 0; s[k]; k++) {
                    if (s[k] == '{')
                        depth++;
                    if (s[k] == '}') {
                        depth--;
                        if (depth <= 0) {
                            in_method = 0;
                            break;
                        }
                    }
                }
            }
            continue;
        }
        if (strncmp(s, "class ", 6) == 0 || strncmp(s, "struct ", 7) == 0) {
            const char *rest = s + (s[0] == 'c' ? 6 : 7);
            char name[96];
            int n = 0;
            rest = trim(rest);
            while (is_id_char((unsigned char)*rest) && n < 95)
                name[n++] = *rest++;
            name[n] = 0;
            if (name[0] && !find_cls(c, name)) {
                int k = i + 1;
                in_class = 1;
                if (strchr(s, '{'))
                    i = parse_class_lines(c, ls, i + 1, name, NULL) - 1;
                else {
                    while (k < ls->count && !strchr(ls->lines[k], '{'))
                        k++;
                    i = parse_class_lines(c, ls, k + 1, name, NULL) - 1;
                }
                in_class = -1;
                printf("class %s: %d fields, %d methods\n", name,
                       c->classes[c->nclasses - 1].nfields, c->classes[c->nclasses - 1].nmethods);
                continue;
            }
        }
        {
            char clsname[96];
            int n = 0;
            const char *r = s;
            while (is_id_char((unsigned char)*r) && n < 95)
                clsname[n++] = *r++;
            clsname[n] = 0;
            if (n > 0 && find_cls(c, clsname)) {
                const char *v = r;
                char var[96];
                int vn = 0;
                while (*v == 32 || *v == 9)
                    v++;
                while (is_id_char((unsigned char)*v) && vn < 95)
                    var[vn++] = *v++;
                var[vn] = 0;
                while (*v == 32 || *v == 9)
                    v++;
                if (vn > 0 && *v == ';') {
                    char mg[256];
                    mangle(mg, sizeof(mg), clsname, clsname, 1, 0);
                    buf_put(&c->meta, "struct ", 7);
                    buf_put(&c->meta, clsname, strlen(clsname));
                    buf_put(&c->meta, " ", 1);
                    buf_put(&c->meta, var, strlen(var));
                    buf_put(&c->meta, "; ", 2);
                    buf_put(&c->meta, mg, strlen(mg));
                    buf_put(&c->meta, "(&", 2);
                    buf_put(&c->meta, var, strlen(var));
                    buf_put(&c->meta, ");", 2);
                    buf_u8(&c->meta, 10);
                    continue;
                }
            }
        }
        if (!*s)
            continue;
        rewrite_free_calls(c, s, strlen(s), &c->meta);
        buf_u8(&c->meta, 10);
    }
}

int main(int argc, char **argv)
{
    const char *in = NULL, *out_path = NULL;
    Buf src;
    Cx c;
    Lines ls;
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            out_path = argv[++i];
        else if (argv[i][0] != '-')
            in = argv[i];
    }
    if (!in || !out_path) {
        fprintf(stderr, "usage: acetylene-cxx input.cpp -o output.c\n"
                        "supports: classes, fields, methods, constructors, this-member access\n"
                        "rejects:  inheritance, virtual, destructors, references, templates\n");
        return 1;
    }
    if (ac_read_file(in, &src) != 0) {
        fprintf(stderr, "acetylene-cxx: cannot read %s\n", in);
        return 1;
    }
    strip_comments(&src);
    memset(&c, 0, sizeof(c));
    c.file = in;
    c.classes = ac_calloc(64, sizeof(Cls));
    buf_init(&c.out);
    buf_init(&c.meta);
    buf_init(&c.decls);
    put_line(&c.decls, "#include <acetylene/e32c.h>");
    put_line(&c.decls, "#include <stdio.h>");
    put_line(&c.decls, "#include <stdlib.h>");
    put_line(&c.decls, "#include <string.h>");
    put_line(&c.decls, "");
    ls = split_lines(&src);
    translate_plain(&c, &ls);
    translate_methods(&c, &src);
    {
        Buf final;
        buf_init(&final);
        put_line(&final, "/* generated by acetylene-cxx */");
        buf_put(&final, c.decls.data, c.decls.len);
        buf_put(&final, c.out.data, c.out.len);
        buf_put(&final, c.meta.data, c.meta.len);
        ac_write_file(out_path, final.data, final.len);
        buf_free(&final);
    }
    printf("acetylene-cxx: %s -> %s, classes: %d, errors: %d\n", in, out_path, c.nclasses, c.errors);
    for (i = 0; i < ls.count; i++)
        free(ls.lines[i]);
    free(ls.lines);
    buf_free(&src);
    buf_free(&c.out);
    buf_free(&c.meta);
    buf_free(&c.decls);
    free(c.classes);
    return c.errors ? 2 : 0;
}
