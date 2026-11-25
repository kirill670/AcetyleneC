#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t s32;

#define OUT_NONE -1
#define OUT_TEXT 0
#define OUT_DATA 1
#define OUT_BSS 2

#define IMAGE_BASE 0x400000u

#define COFF_MACHINE_ARM 0x0a00
#define COFF_ARM32 0x2
#define COFF_ARM26 0x3

#define ELF_REL_PC24 1
#define ELF_REL_ABS32 2
#define ELF_REL_V4BX 40

#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHF_ALLOC 2
#define SHF_EXECINSTR 4

static void die(const char *fmt, ...)
{
    va_list ap;
    fprintf(stderr, "acetylene-pe: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(1);
}

static u16 rd16(const u8 *p) { return (u16)(p[0] | (p[1] << 8)); }
static u32 rd32(const u8 *p)
{
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}
static void wr32(u8 *p, u32 v)
{
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16);
    p[3] = (u8)(v >> 24);
}

static void *xcalloc(size_t n, size_t sz)
{
    void *p = calloc(n ? n : 1, sz);
    if (!p)
        die("out of memory");
    return p;
}

static void *xrealloc(void *p, size_t n)
{
    void *q = realloc(p, n ? n : 1);
    if (!q)
        die("out of memory");
    return q;
}

static char *xstrdup(const char *s)
{
    size_t n = strlen(s) + 1;
    char *p = xcalloc(n, 1);
    memcpy(p, s, n);
    return p;
}

static u8 *read_file(const char *path, size_t *len)
{
    FILE *f = fopen(path, "rb");
    long n;
    u8 *d;
    if (!f)
        die("cannot open %s", path);
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n <= 0)
        die("%s is empty", path);
    d = xcalloc((size_t)n, 1);
    if (fread(d, 1, (size_t)n, f) != (size_t)n)
        die("cannot read %s", path);
    fclose(f);
    *len = (size_t)n;
    return d;
}

typedef struct {
    char name[32];
    u8 *data;
    u32 size;
    u8 *rel;
    u32 nrel;
    int out;
    u32 out_off;
    int obj;
    int index;
} Sec;

typedef struct {
    char name[256];
    int sec;
    u32 value;
    int is_global;
    u32 addr;
    int is_sec_sym;
} Sym;

typedef struct {
    int sec;
    u32 off;
    int sym;
    int type;
    int is_coff;
} Rel;

typedef struct {
    char name[200];
    u8 *data;
    size_t len;
    Sec *secs;
    int nsec;
    Sym *syms;
    int nsym;
    Rel *rels;
    int nrel;
    int import_stub;
    int section_of_iat;
    char dll[128];
    int ordinal;
    int iat_slot;
} Obj;

typedef struct {
    char *path;
    u8 *data;
    size_t len;
    char dll[128];
    char **members;
    u32 *member_off;
    u32 *member_len;
    int nmembers;
} Lib;

typedef struct {
    char name[256];
    int obj;
    int sym;
    u32 addr;
    int defined;
    int iat_slot;
} GSym;

static Obj **objs;
static int nobjs;
static Lib **libs;
static int nlibs;
static GSym *gsyms;
static int ngsyms;

static u32 text_size, data_size, bss_size;
static u32 iat_count;

typedef struct {
    char dll[128];
    int *ordinals;
    int count;
} ImportGroup;

static ImportGroup *groups;
static int ngroups;
static int g_verbose;

static int gsym_find(const char *name)
{
    int i;
    for (i = 0; i < ngsyms; i++)
        if (strcmp(gsyms[i].name, name) == 0)
            return i;
    return -1;
}

static int gsym_add(const char *name)
{
    int i = gsym_find(name);
    if (i >= 0)
        return i;
    gsyms = xrealloc(gsyms, sizeof(GSym) * (size_t)(ngsyms + 1));
    memset(&gsyms[ngsyms], 0, sizeof(GSym));
    snprintf(gsyms[ngsyms].name, sizeof(gsyms[ngsyms].name), "%s", name);
    gsyms[ngsyms].obj = -1;
    gsyms[ngsyms].sym = -1;
    gsyms[ngsyms].iat_slot = -1;
    ngsyms++;
    return ngsyms - 1;
}

static int is_idata(const char *name)
{
    return strncmp(name, ".idata$", 7) == 0;
}

static int classify_coff(const char *name, u32 chars)
{
    if (is_idata(name) || strncmp(name, ".drectve", 8) == 0 || strncmp(name, ".debug", 6) == 0)
        return OUT_NONE;
    if (strcmp(name, ".text") == 0 || (chars & 0x20))
        return OUT_TEXT;
    if (strcmp(name, ".bss") == 0 || (chars & 0x80))
        return OUT_BSS;
    return OUT_DATA;
}

static int classify_elf(const char *name, u32 flags, u32 type)
{
    if (strncmp(name, ".text", 5) == 0)
        return OUT_TEXT;
    if (type == SHT_NOBITS)
        return flags & SHF_ALLOC ? OUT_BSS : OUT_NONE;
    if (type != SHT_PROGBITS || !(flags & SHF_ALLOC))
        return OUT_NONE;
    if (flags & SHF_EXECINSTR)
        return OUT_TEXT;
    return OUT_DATA;
}

static int add_obj(Obj *o)
{
    objs = xrealloc(objs, sizeof(Obj *) * (size_t)(nobjs + 1));
    objs[nobjs] = o;
    return nobjs++;
}

static void obj_register(Obj *o)
{
    int i, idx = add_obj(o);
    for (i = 0; i < o->nsym; i++) {
        Sym *s = &o->syms[i];
        int gi;
        if (!s->is_global || !s->name[0])
            continue;
        if (s->sec < 0) {
            gsym_add(s->name);
            continue;
        }
        gi = gsym_add(s->name);
        if (!gsyms[gi].defined) {
            gsyms[gi].defined = 1;
            gsyms[gi].obj = idx;
            gsyms[gi].sym = i;
        }
    }
}

static void parse_elf(Obj *o, const char *path)
{
    u32 shoff, shnum, shstr, symdata = 0, strtab = 0;
    int symsec = -1;
    u32 i;

    o->data = read_file(path, &o->len);
    snprintf(o->name, sizeof(o->name), "%s", path);
    if (memcmp(o->data, "\177ELF", 4) != 0)
        die("%s is not an ELF object", path);
    if (o->data[4] != 1 || o->data[5] != 1)
        die("%s must be 32-bit little-endian ELF", path);
    shoff = rd32(o->data + 32);
    shnum = rd16(o->data + 48);
    shstr = rd16(o->data + 50);
    o->nsec = (int)shnum;
    o->secs = xcalloc(shnum, sizeof(Sec));
    for (i = 0; i < shnum; i++) {
        const u8 *s = o->data + shoff + i * 40;
        const char *names = (const char *)(o->data + rd32(o->data + shoff + shstr * 40 + 16));
        u32 type = rd32(s + 4);
        u32 flags = rd32(s + 8);
        Sec *sec = &o->secs[i];
        snprintf(sec->name, sizeof(sec->name), "%s", names + rd32(s));
        sec->size = rd32(s + 20);
        sec->data = (type == SHT_PROGBITS && (flags & SHF_ALLOC)) ? o->data + rd32(s + 16) : NULL;
        sec->out = classify_elf(sec->name, flags, type);
        if (type == SHT_SYMTAB) {
            symsec = (int)i;
            symdata = rd32(s + 16);
            strtab = rd32(o->data + shoff + rd32(s + 24) * 40 + 16);
            o->nsym = (int)(sec->size / 16);
        }
    }
    if (symsec < 0)
        die("%s has no symbol table", path);
    o->syms = xcalloc((size_t)o->nsym, sizeof(Sym));
    for (i = 0; i < (u32)o->nsym; i++) {
        const u8 *s = o->data + symdata + i * 16;
        const char *nm = (const char *)(o->data + strtab + rd32(s));
        snprintf(o->syms[i].name, sizeof(o->syms[i].name), "%s", nm);
        o->syms[i].value = rd32(s + 4);
        o->syms[i].sec = rd16(s + 14);
        o->syms[i].is_global = (s[12] != 0);
        if (o->syms[i].sec == 0)
            o->syms[i].sec = -1;
    }
    for (i = 0; i < shnum; i++) {
        const u8 *s = o->data + shoff + i * 40;
        u32 count;
        u32 k;
        int target;
        u32 off;
        if (rd32(s + 4) != SHT_REL || !rd32(s + 20))
            continue;
        target = (int)rd32(s + 28);
        off = rd32(s + 16);
        count = rd32(s + 20) / 8;
        for (k = 0; k < count; k++) {
            const u8 *r = o->data + off + k * 8;
            o->rels = xrealloc(o->rels, sizeof(Rel) * (size_t)(o->nrel + 1));
            o->rels[o->nrel].sec = target;
            o->rels[o->nrel].off = rd32(r);
            o->rels[o->nrel].sym = (int)(rd32(r + 4) >> 8);
            o->rels[o->nrel].type = (int)(rd32(r + 4) & 0xff);
            o->rels[o->nrel].is_coff = 0;
            o->nrel++;
        }
    }
}

static void parse_coff(Obj *o, const char *label, u8 *data, size_t len)
{
    u32 symptr, nsym, i;
    int k;

    o->data = data;
    o->len = len;
    snprintf(o->name, sizeof(o->name), "%s", label);
    if (len < 20 || rd16(data) != COFF_MACHINE_ARM)
        die("%s is not an ARM COFF object", label);
    o->nsec = (int)rd16(data + 2);
    symptr = rd32(data + 8);
    nsym = rd32(data + 12);
    o->secs = xcalloc((size_t)(o->nsec ? o->nsec : 1), sizeof(Sec));
    for (i = 0; i < (u32)o->nsec; i++) {
        const u8 *s = data + 20 + i * 40;
        u32 rawsz = rd32(s + 16);
        u32 rawptr = rd32(s + 20);
        u32 chars = rd32(s + 36);
        Sec *sec = &o->secs[i];
        snprintf(sec->name, sizeof(sec->name), "%s", (const char *)s);
        sec->size = rawsz;
        sec->data = rawsz ? data + rawptr : NULL;
        sec->out = classify_coff(sec->name, chars);
        sec->rel = rd16(s + 32) ? data + rd32(s + 24) : NULL;
        sec->nrel = rd16(s + 32);
        if (strcmp(sec->name, ".idata$5") == 0)
            o->section_of_iat = 1;
        for (k = 0; k < (int)sec->nrel; k++) {
            const u8 *r = sec->rel + (size_t)k * 14;
            o->rels = xrealloc(o->rels, sizeof(Rel) * (size_t)(o->nrel + 1));
            o->rels[o->nrel].sec = (int)i;
            o->rels[o->nrel].off = rd32(r);
            o->rels[o->nrel].sym = (int)rd32(r + 4);
            o->rels[o->nrel].type = (int)rd16(r + 8);
            o->rels[o->nrel].is_coff = 1;
            o->nrel++;
        }
    }
    o->syms = xcalloc(nsym ? nsym : 1, sizeof(Sym));
    o->nsym = (int)nsym;
    {
        u8 *is_aux = xcalloc(nsym ? nsym : 1, 1);
        u32 a;
        for (a = 0; a < nsym; ) {
            u32 naux = data[symptr + a * 18 + 17];
            u32 k;
            for (k = 1; k <= naux && a + k < nsym; k++)
                is_aux[a + k] = 1;
            a += 1 + naux;
        }
        for (i = 0; i < nsym; i++) {
        const u8 *s = data + symptr + i * 18;
        Sym *sy = &o->syms[i];
        if (is_aux[i]) {
            sy->sec = -1;
            continue;
        }
        if (rd32(s) == 0) {
            u32 off = rd32(s + 4);
            snprintf(sy->name, sizeof(sy->name), "%s", (const char *)(data + symptr + nsym * 18 + off));
        } else {
            u32 namelen = 8;
            while (namelen > 0 && s[namelen - 1] == 0)
                namelen--;
            memcpy(sy->name, s, namelen);
            sy->name[namelen] = 0;
        }
        sy->value = rd32(s + 8);
        sy->sec = (int)(int16_t)rd16(s + 12);
        sy->is_global = (s[16] == 2);
        if (sy->sec > 0)
            sy->sec--;
        else
            sy->sec = -1;
        if (sy->is_global && sy->sec >= 0 && strcmp(o->secs[sy->sec].name, ".text") == 0)
            o->import_stub = o->section_of_iat;
        }
        free(is_aux);
    }
}

static int obj_find_sec(Obj *o, const char *name)
{
    int i;
    for (i = 0; i < o->nsec; i++)
        if (strcmp(o->secs[i].name, name) == 0)
            return i;
    return -1;
}

static int member_defines(Lib *l, int mi, const char *name)
{
    Obj o;
    int k, found = 0;
    memset(&o, 0, sizeof(o));
    parse_coff(&o, l->members[mi], l->data + l->member_off[mi], l->member_len[mi]);
    for (k = 0; k < o.nsym; k++)
        if (o.syms[k].is_global && o.syms[k].sec >= 0 && strcmp(o.syms[k].name, name) == 0) {
            found = 1;
            break;
        }
    free(o.secs);
    free(o.syms);
    free(o.rels);
    return found;
}

static void load_lib(const char *path)
{
    Lib *l = xcalloc(1, sizeof(Lib));
    size_t off = 8;
    u8 *longnames = NULL;
    size_t longlen = 0;

    l->path = xstrdup(path);
    l->data = read_file(path, &l->len);
    if (memcmp(l->data, "!<arch>\n", 8) != 0)
        die("%s is not an archive", path);
    while (off + 60 <= l->len) {
        const u8 *hdr = l->data + off;
        char name[32];
        u32 size;
        char *p;
        memcpy(name, hdr, 16);
        name[16] = 0;
        p = name + strlen(name);
        while (p > name && p[-1] == ' ')
            *--p = 0;
        if (strcmp(name, "/") != 0 && strcmp(name, "//") != 0)
            if (p > name && p[-1] == '/')
                *--p = 0;
        size = (u32)strtoul((const char *)hdr + 48, NULL, 10);
        if (strcmp(name, "//") == 0) {
            longnames = l->data + off + 60;
            longlen = size;
        } else if (name[0] == '/' && name[1] >= '0' && name[1] <= '9') {
            u32 no = (u32)strtoul(name + 1, NULL, 10);
            if (longnames && no < longlen) {
                size_t e = no;
                char *nm;
                while (e < longlen && longnames[e] != '\n')
                    e++;
                nm = xcalloc(e - no + 1, 1);
                memcpy(nm, longnames + no, e - no);
                l->members = xrealloc(l->members, sizeof(char *) * (size_t)(l->nmembers + 1));
                l->member_off = xrealloc(l->member_off, sizeof(u32) * (size_t)(l->nmembers + 1));
                l->member_len = xrealloc(l->member_len, sizeof(u32) * (size_t)(l->nmembers + 1));
                l->members[l->nmembers] = nm;
                l->member_off[l->nmembers] = (u32)(off + 60);
                l->member_len[l->nmembers] = size;
                l->nmembers++;
            }
        } else if (name[0] && strcmp(name, "/") != 0 && strcmp(name, "/SYM64/") != 0) {
            l->members = xrealloc(l->members, sizeof(char *) * (size_t)(l->nmembers + 1));
            l->member_off = xrealloc(l->member_off, sizeof(u32) * (size_t)(l->nmembers + 1));
            l->member_len = xrealloc(l->member_len, sizeof(u32) * (size_t)(l->nmembers + 1));
            l->members[l->nmembers] = xstrdup(name);
            l->member_off[l->nmembers] = (u32)(off + 60);
            l->member_len[l->nmembers] = size;
            l->nmembers++;
        }
        off += 60 + size + (size & 1);
    }
    {
        int i;
        for (i = 0; i < l->nmembers; i++) {
            Obj o;
            int s7;
            memset(&o, 0, sizeof(o));
            parse_coff(&o, l->members[i], l->data + l->member_off[i], l->member_len[i]);
            s7 = obj_find_sec(&o, ".idata$7");
            if (s7 >= 0 && o.secs[s7].size >= 8 && o.secs[s7].size < sizeof(l->dll)) {
                u32 n = o.secs[s7].size;
                char *src = (char *)o.secs[s7].data;
                u32 k = 0;
                while (k < n && src[k] && src[k] >= 32 && src[k] < 127) {
                    l->dll[k] = src[k];
                    k++;
                }
                l->dll[k] = 0;
                if (strchr(l->dll, '.') && strchr(l->dll, '['))
                    break;
                l->dll[0] = 0;
            }
            free(o.secs);
            free(o.syms);
            free(o.rels);
        }
    }
    libs = xrealloc(libs, sizeof(Lib *) * (size_t)(nlibs + 1));
    libs[nlibs++] = l;
}

static Obj *pull_member(Lib *l, int mi)
{
    Obj *o = xcalloc(1, sizeof(Obj));
    const char *nm = l->members[mi];
    const char *base = nm;
    const char *bs = strrchr(nm, '\\');
    const char *fs = strrchr(nm, '/');
    char label[400];
    if (bs && bs + 1 > base)
        base = bs + 1;
    if (fs && fs + 1 > base)
        base = fs + 1;
    snprintf(label, sizeof(label), "%s:%.120s", l->path, base);
    parse_coff(o, label, l->data + l->member_off[mi], l->member_len[mi]);
    if (o->import_stub) {
        int s5 = obj_find_sec(o, ".idata$5");
        int s4 = obj_find_sec(o, ".idata$4");
        u32 v = 0;
        snprintf(o->dll, sizeof(o->dll), "%s", l->dll);
        if (s5 >= 0 && o->secs[s5].data)
            v = rd32(o->secs[s5].data);
        if (!v && s4 >= 0 && o->secs[s4].data)
            v = rd32(o->secs[s4].data);
        o->ordinal = (int)(v & 0x7fffffffu);
    }
    return o;
}

static void collect_undefined(char ***names, int *count)
{
    int i, k;
    for (i = 0; i < nobjs; i++) {
        Obj *o = objs[i];
        for (k = 0; k < o->nsym; k++) {
            Sym *s = &o->syms[k];
            int gi;
            if (!s->is_global || s->sec >= 0 || !s->name[0])
                continue;
            gi = gsym_find(s->name);
            if (gi >= 0 && gsyms[gi].defined)
                continue;
            {
                int j, seen = 0;
                for (j = 0; j < *count; j++)
                    if (strcmp((*names)[j], s->name) == 0) {
                        seen = 1;
                        break;
                    }
                if (!seen) {
                    *names = xrealloc(*names, sizeof(char *) * (size_t)(*count + 1));
                    (*names)[*count] = s->name;
                    (*count)++;
                }
            }
        }
    }
}

static int pull_symbol(const char *name)
{
    int li, mi;
    for (li = 0; li < nlibs; li++)
        for (mi = 0; mi < libs[li]->nmembers; mi++)
            if (member_defines(libs[li], mi, name)) {
                Obj *o = pull_member(libs[li], mi);
                obj_register(o);
                return 1;
            }
    return 0;
}

static void link_objects(void)
{
    int pass;
    for (pass = 0; pass < 128; pass++) {
        char **names = NULL;
        int count = 0;
        int i, j, pulled = 0;
        collect_undefined(&names, &count);
        for (i = 0; i < count; i++) {
            int gi = gsym_find(names[i]);
            if (gi >= 0 && gsyms[gi].defined)
                continue;
            for (j = 0; j < nlibs && !pulled; j++) {
                int mi;
                for (mi = 0; mi < libs[j]->nmembers; mi++) {
                    if (member_defines(libs[j], mi, names[i])) {
                        Obj *o = pull_member(libs[j], mi);
                        obj_register(o);
                        pulled = 1;
                        break;
                    }
                }
            }
        }
        free(names);
        if (!pulled)
            break;
    }
}

static u32 align4(u32 v) { return (v + 3u) & ~3u; }

static void layout(void)
{
    int i, k;
    text_size = 0;
    data_size = 0;
    bss_size = 0;
    iat_count = 0;
    for (i = 0; i < nobjs; i++) {
        Obj *o = objs[i];
        for (k = 0; k < o->nsec; k++) {
            Sec *s = &o->secs[k];
            if (s->out == OUT_TEXT) {
                text_size = align4(text_size);
                s->out_off = text_size;
                text_size += s->size;
                s->obj = i;
                s->index = k;
            }
        }
        if (o->import_stub)
            o->iat_slot = (int)iat_count++;
    }
    for (i = 0; i < nobjs; i++) {
        Obj *o = objs[i];
        for (k = 0; k < o->nsec; k++) {
            Sec *s = &o->secs[k];
            if (s->out == OUT_DATA) {
                data_size = align4(data_size);
                s->out_off = data_size;
                data_size += s->size;
                s->obj = i;
                s->index = k;
            }
        }
    }
    for (i = 0; i < nobjs; i++) {
        Obj *o = objs[i];
        for (k = 0; k < o->nsec; k++) {
            Sec *s = &o->secs[k];
            if (s->out == OUT_BSS) {
                bss_size = align4(bss_size);
                s->out_off = bss_size;
                bss_size += s->size;
                s->obj = i;
                s->index = k;
            }
        }
    }
    text_size = align4(text_size);
    if (g_verbose) {
        int oi, si;
        for (oi = 0; oi < nobjs; oi++) {
            Obj *vo = objs[oi];
            for (si = 0; si < vo->nsec; si++) {
                Sec *vs = &vo->secs[si];
                if (vs->out != OUT_NONE)
                    fprintf(stderr, "  %-10s %-6s size=%-6u off=%#x  %s\n", vs->name, vs->out == OUT_TEXT ? "text" : vs->out == OUT_DATA ? "data" : "bss",
                            vs->size, vs->out_off, vo->name);
            }
        }
    }
}

static u32 iat_addr(int slot)
{
    return IMAGE_BASE + text_size + (u32)slot * 4u;
}

static s32 read_imm24(const u8 *p)
{
    u32 w = rd32(p);
    s32 v = (s32)(w << 8) >> 8;
    return (s32)((u32)v << 2);
}

static void write_imm24(u8 *p, s32 v)
{
    u32 w = rd32(p);
    wr32(p, (w & 0xff000000u) | (((u32)v >> 2) & 0x00ffffffu));
}

static u8 *out_text_buf;
static u8 *out_data_buf;

static void apply_relocs(void)
{
    int i, k;
    for (i = 0; i < nobjs; i++) {
        Obj *o = objs[i];
        for (k = 0; k < o->nrel; k++) {
            Rel *r = &o->rels[k];
            Sec *sec;
            Sym *ts;
            u32 target = 0;
            u8 *field;
            if (r->sec < 0 || r->sec >= o->nsec)
                continue;
            sec = &o->secs[r->sec];
            if (sec->out != OUT_TEXT && sec->out != OUT_DATA)
                continue;
            if (r->sym < 0 || r->sym >= o->nsym)
                die("%s: relocation with a bad symbol %d (nsym %d, sec %s)", o->name, r->sym, o->nsym, sec->name);
            ts = &o->syms[r->sym];
            field = (sec->out == OUT_TEXT ? out_text_buf + sec->out_off : out_data_buf + sec->out_off) + r->off;

            if (ts->sec < 0) {
                int gi = gsym_find(ts->name);
                if (gi < 0 || !gsyms[gi].defined)
                    die("%s: undefined symbol %s", o->name, ts->name);
                target = gsyms[gi].addr;
            } else if (ts->sec < o->nsec) {
                Sec *tsec = &o->secs[ts->sec];
                if (strcmp(tsec->name, ".idata$5") == 0) {
                    target = iat_addr(o->iat_slot);
                } else if (tsec->out == OUT_TEXT) {
                    target = IMAGE_BASE + tsec->out_off + ts->value;
                } else if (tsec->out == OUT_DATA) {
                    target = IMAGE_BASE + text_size + iat_count * 4 + 4 + tsec->out_off + ts->value;
                } else if (tsec->out == OUT_BSS) {
                    target = IMAGE_BASE + text_size + iat_count * 4 + 4 + data_size + tsec->out_off + ts->value;
                } else {
                    die("%s: relocation against %s which is not emitted", o->name, tsec->name);
                }
            }

            {
                int kind;
                if (r->is_coff) {
                    if (r->type == COFF_ARM32)
                        kind = 0;
                    else if (r->type == COFF_ARM26)
                        kind = 1;
                    else
                        die("%s: unsupported COFF relocation %d in %s", o->name, r->type, sec->name);
                } else {
                    if (r->type == ELF_REL_ABS32)
                        kind = 0;
                    else if (r->type == ELF_REL_PC24)
                        kind = 1;
                    else if (r->type == ELF_REL_V4BX)
                        kind = 2;
                    else
                        die("%s: unsupported ELF relocation %d in %s", o->name, r->type, sec->name);
                }
                if (kind == 0) {
                    wr32(field, rd32(field) + target);
                } else if (kind == 1) {
                    u32 p = (sec->out == OUT_TEXT ? IMAGE_BASE + sec->out_off : IMAGE_BASE + text_size + iat_count * 4 + 4 + sec->out_off) + r->off;
                    s32 a = read_imm24(field);
                    write_imm24(field, a + (s32)target - (s32)p);
                }
            }
        }
    }
}

static u32 uid_check(u32 u1, u32 u2, u32 u3)
{
    static const u32 a[3][8] = {
        {0x000045a0u, 0x00008b40u, 0x000006a1u, 0x00000d42u, 0x00001a84u, 0x00003508u, 0x00006a10u, 0x0000d420u},
        {0x000076b4u, 0x0000ed68u, 0x0000caf1u, 0x000085c3u, 0x00001ba7u, 0x0000374eu, 0x00006e9cu, 0x0000dd38u},
        {0x00003331u, 0x00006662u, 0x0000ccc4u, 0x000089a9u, 0x00000373u, 0x000006e6u, 0x00000dccu, 0x00001b98u}
    };
    static const u32 b[3][8] = {
        {0x0000aa51u, 0x00004483u, 0x00008906u, 0x0000022du, 0x0000045au, 0x000008b4u, 0x00001168u, 0x000022d0u},
        {0x00003730u, 0x00006e60u, 0x0000dcc0u, 0x0000a9a1u, 0x00004363u, 0x000086c6u, 0x00001dadu, 0x00003b5au},
        {0x00001021u, 0x00002042u, 0x00004084u, 0x00008108u, 0x00001231u, 0x00002462u, 0x000048c4u, 0x00009188u}
    };
    u32 u[3];
    u32 lo = 0, hi = 0;
    int s, k;
    u[0] = u1;
    u[1] = u2;
    u[2] = u3;
    for (s = 0; s < 3; s++) {
        for (k = 0; k < 8; k++) {
            if ((u[s] >> k) & 1u)
                lo ^= a[s][k];
            if ((u[s] >> (k + 8)) & 1u)
                hi ^= a[s][k];
            if ((u[s] >> (k + 16)) & 1u)
                lo ^= b[s][k];
            if ((u[s] >> (k + 24)) & 1u)
                hi ^= b[s][k];
        }
    }
    return (hi << 16) | lo;
}

static u32 text_checksum(const u8 *p, u32 n)
{
    u32 sum = 0;
    u32 i;
    for (i = 0; i + 4 <= n; i += 4)
        sum += rd32(p + i);
    return sum;
}

static void write_image(const char *path, const char *entry, u32 u1, u32 u2, u32 u3,
                        u32 heapmin, u32 heapmax, u32 stack, u32 priority)
{
    u8 *image;
    u32 iat_bytes = iat_count ? (iat_count + 1) * 4 : 0;
    u32 code_size = text_size + iat_bytes;
    int has_data;
    u32 data_base;
    u32 entry_off;
    u32 import_off, import_size;
    u32 i, k;
    u32 pos;
    int gi;

    gi = gsym_find(entry);
    if (gi < 0 || !gsyms[gi].defined)
        die("entry symbol %s not found", entry);
    entry_off = gsyms[gi].addr - IMAGE_BASE;
    if (entry_off >= text_size)
        die("entry symbol %s is not in the code section", entry);

    import_size = 4;
    {
        int d;
        for (i = 0; i < iat_count; i++) {
            char dll[128];
            Obj *o = NULL;
            int j;
            for (j = 0; j < nobjs; j++)
                if (objs[j]->import_stub && objs[j]->iat_slot == (int)i) {
                    o = objs[j];
                    break;
                }
            if (!o)
                continue;
            snprintf(dll, sizeof(dll), "%s", o->dll);
            for (d = 0; d < ngroups; d++)
                if (strcmp(groups[d].dll, dll) == 0)
                    break;
            if (d == ngroups) {
                groups = xrealloc(groups, sizeof(ImportGroup) * (size_t)(ngroups + 1));
                memset(&groups[ngroups], 0, sizeof(ImportGroup));
                snprintf(groups[ngroups].dll, sizeof(groups[ngroups].dll), "%s", dll);
                ngroups++;
            }
        }
        for (d = 0; d < ngroups; d++) {
            for (i = 0; i < iat_count; i++) {
                int j;
                for (j = 0; j < nobjs; j++)
                    if (objs[j]->import_stub && objs[j]->iat_slot == (int)i &&
                        strcmp(objs[j]->dll, groups[d].dll) == 0) {
                        groups[d].ordinals = xrealloc(groups[d].ordinals,
                                                     sizeof(int) * (size_t)(groups[d].count + 1));
                        groups[d].ordinals[groups[d].count++] = objs[j]->ordinal;
                    }
            }
            import_size += 8 + (u32)groups[d].count * 4 + (u32)strlen(groups[d].dll) + 1;
        }
    }
    has_data = (data_size != 0 || bss_size != 0);
    data_base = has_data ? IMAGE_BASE + code_size : 0;
    if (iat_count == 0)
        import_size = 0;
    import_size = align4(import_size);
    import_off = 0x7c + code_size + data_size;

    image = xcalloc((size_t)import_off + import_size, 1);
    memcpy(image + 0x7c, out_text_buf, text_size);
    for (i = 0; i < iat_count; i++) {
        int j;
        for (j = 0; j < nobjs; j++)
            if (objs[j]->import_stub && objs[j]->iat_slot == (int)i) {
                wr32(image + 0x7c + text_size + i * 4, (u32)objs[j]->ordinal);
                break;
            }
    }
    wr32(image + 0x7c + text_size + iat_count * 4, 0);
    if (data_size)
        memcpy(image + 0x7c + code_size, out_data_buf, data_size);

    pos = import_off;
    wr32(image + pos, import_size - 4);
    pos += 4;
    {
        u32 name_base = 4 + (u32)ngroups * 8 + (u32)iat_count * 4;
        u32 name_cur = name_base;
        int d;
        for (d = 0; d < ngroups; d++) {
            wr32(image + pos, name_cur);
            wr32(image + pos + 4, (u32)groups[d].count);
            pos += 8;
            for (i = 0; i < (u32)groups[d].count; i++) {
                wr32(image + pos, (u32)groups[d].ordinals[i]);
                pos += 4;
            }
            name_cur += (u32)strlen(groups[d].dll) + 1;
        }
        name_cur = name_base;
        for (d = 0; d < ngroups; d++) {
            size_t n = strlen(groups[d].dll) + 1;
            memcpy(image + import_off + name_cur, groups[d].dll, n);
            name_cur += (u32)n;
        }
        wr32(image + 0x6c, iat_count ? import_off : 0);
    }

    wr32(image + 0x00, u1);
    wr32(image + 0x04, u2);
    wr32(image + 0x08, u3);
    wr32(image + 0x0c, uid_check(u1, u2, u3));
    wr32(image + 0x10, 0x434f5045u);
    wr32(image + 0x14, 0x00002000u);
    wr32(image + 0x18, text_checksum(image + 0x7c, code_size));
    wr32(image + 0x1c, 0);
    wr32(image + 0x20, 0x00c00001u);
    wr32(image + 0x24, 0x5f315e00u);
    wr32(image + 0x28, 0x00e33ec1u);
    wr32(image + 0x2c, 0x01000000u);
    wr32(image + 0x30, code_size);
    wr32(image + 0x34, data_size);
    wr32(image + 0x38, heapmin);
    wr32(image + 0x3c, heapmax);
    wr32(image + 0x40, stack);
    wr32(image + 0x44, bss_size);
    wr32(image + 0x48, entry_off);
    wr32(image + 0x4c, IMAGE_BASE);
    wr32(image + 0x50, data_base);
    wr32(image + 0x54, (u32)ngroups);
    wr32(image + 0x58, 0);
    wr32(image + 0x5c, 0);
    wr32(image + 0x60, text_size);
    wr32(image + 0x64, 0x7c);
    wr32(image + 0x68, data_size ? 0x7c + code_size : 0);
    wr32(image + 0x70, 0);
    wr32(image + 0x74, 0);
    wr32(image + 0x78, priority);

    {
        FILE *f = fopen(path, "wb");
        if (!f)
            die("cannot create %s", path);
        if (fwrite(image, 1, (size_t)import_off + import_size, f) != (size_t)import_off + import_size)
            die("write failed");
        fclose(f);
    }
    printf("image: %s (%u bytes)\n", path, import_off + import_size);
    printf("  code %u, data %u, bss %u, imports %u from %d dll(s), entry +%#x\n",
           code_size, data_size, bss_size, iat_count, ngroups, entry_off);
    (void)k;
}

static u32 addr_of(Sec *sec, u32 value)
{
    u32 data_base = IMAGE_BASE + text_size + (iat_count + 1) * 4;
    if (strcmp(sec->name, ".idata$5") == 0)
        return 0;
    if (sec->out == OUT_TEXT)
        return IMAGE_BASE + sec->out_off + value;
    if (sec->out == OUT_DATA)
        return data_base + sec->out_off + value;
    if (sec->out == OUT_BSS)
        return data_base + data_size + sec->out_off + value;
    return 0;
}

static void define_linker_symbols(void)
{
    static const char *names[] = {
        "__CTOR_LIST__", "__CTOR_END__", "__DTOR_LIST__", "__DTOR_END__",
        "__EH_FRAME_BEGIN__", "__EH_FRAME_END__"
    };
    u32 end = IMAGE_BASE + text_size + (iat_count + 1) * 4 + data_size;
    size_t i;
    for (i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
        int gi = gsym_find(names[i]);
        if (gi >= 0 && !gsyms[gi].defined) {
            gsyms[gi].defined = 1;
            gsyms[gi].addr = end;
        }
    }
}

static void compute_addresses(void)
{
    int i;
    for (i = 0; i < ngsyms; i++) {
        Obj *o;
        Sym *s;
        if (!gsyms[i].defined || gsyms[i].obj < 0)
            continue;
        o = objs[gsyms[i].obj];
        s = &o->syms[gsyms[i].sym];
        if (s->sec < 0 || s->sec >= o->nsec)
            continue;
        {
            Sec *sec = &o->secs[s->sec];
            if (strcmp(sec->name, ".idata$5") == 0)
                gsyms[i].addr = iat_addr(o->iat_slot);
            else
                gsyms[i].addr = addr_of(sec, s->value);
        }
    }
}

static void copy_sections(void)
{
    int i, k;
    out_text_buf = xcalloc((size_t)(text_size ? text_size : 1), 1);
    out_data_buf = xcalloc((size_t)(data_size ? data_size : 1), 1);
    for (i = 0; i < nobjs; i++) {
        Obj *o = objs[i];
        for (k = 0; k < o->nsec; k++) {
            Sec *s = &o->secs[k];
            if (!s->data || !s->size)
                continue;
            if (s->out == OUT_TEXT && text_size)
                memcpy(out_text_buf + s->out_off, s->data, s->size);
            else if (s->out == OUT_DATA && data_size)
                memcpy(out_data_buf + s->out_off, s->data, s->size);
        }
    }
}

static char *lib_path_for(const char *name, char **dirs, int ndirs)
{
    char *p = xcalloc(600, 1);
    int i;
    if (strchr(name, '/') || strchr(name, (char)92)) {
        snprintf(p, 600, "%s", name);
        {
            FILE *f = fopen(p, "rb");
            if (f) {
                fclose(f);
                return p;
            }
        }
    }
    for (i = 0; i < ndirs; i++) {
        snprintf(p, 600, "%s/%s.lib", dirs[i], name);
        {
            FILE *f = fopen(p, "rb");
            if (f) {
                fclose(f);
                return p;
            }
        }
        snprintf(p, 600, "%s/lib%s.lib", dirs[i], name);
        {
            FILE *f = fopen(p, "rb");
            if (f) {
                fclose(f);
                return p;
            }
        }
    }
    die("cannot find library %s (use -L)", name);
    return NULL;
}

int main(int argc, char **argv)
{
    const char *outpath = NULL;
    const char *entry = "_E32Startup";
    u32 u1 = 0x100039CEu, u2 = 0xE0000001u, u3 = 0;
    u32 heapmin = 0x1000, heapmax = 0x100000;
    u32 stack = 0x2000, priority = 0x15e;
    char **inputs = xcalloc((size_t)argc, sizeof(char *));
    char **libnames = xcalloc((size_t)argc, sizeof(char *));
    char **libdirs = xcalloc((size_t)argc, sizeof(char *));
    int ninputs = 0, nlibnames = 0, nlibdirs = 0;
    int i;

    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        if (strcmp(a, "-o") == 0 && i + 1 < argc)
            outpath = argv[++i];
        else if (strcmp(a, "-entry") == 0 && i + 1 < argc)
            entry = argv[++i];
        else if (strcmp(a, "-uid1") == 0 && i + 1 < argc)
            u1 = (u32)strtoul(argv[++i], NULL, 0);
        else if (strcmp(a, "-uid2") == 0 && i + 1 < argc)
            u2 = (u32)strtoul(argv[++i], NULL, 0);
        else if (strcmp(a, "-uid3") == 0 && i + 1 < argc)
            u3 = (u32)strtoul(argv[++i], NULL, 0);
        else if (strcmp(a, "-heap") == 0 && i + 2 < argc) {
            heapmin = (u32)strtoul(argv[++i], NULL, 0);
            heapmax = (u32)strtoul(argv[++i], NULL, 0);
        } else if (strcmp(a, "-stack") == 0 && i + 1 < argc)
            stack = (u32)strtoul(argv[++i], NULL, 0);
        else if (strcmp(a, "-priority") == 0 && i + 1 < argc)
            priority = (u32)strtoul(argv[++i], NULL, 0);
        else if (strcmp(a, "-v") == 0)
            g_verbose = 1;
        else if (strcmp(a, "-L") == 0 && i + 1 < argc)
            libdirs[nlibdirs++] = argv[++i];
        else if (strncmp(a, "-l", 2) == 0 && a[2])
            libnames[nlibnames++] = (char *)a + 2;
        else if (a[0] == '-')
            die("unknown option %s", a);
        else if (strstr(a, ".lib") || strstr(a, ".a"))
            libnames[nlibnames++] = (char *)a;
        else
            inputs[ninputs++] = (char *)a;
    }
    if (!outpath)
        die("usage: acetylene-pe -o out.app [options] objects... -L dir -lname");
    if (!ninputs)
        die("no input objects");

    for (i = 0; i < ninputs; i++) {
        Obj *o = xcalloc(1, sizeof(Obj));
        parse_elf(o, inputs[i]);
        obj_register(o);
    }
    for (i = 0; i < nlibnames; i++) {
        char *p = strstr(libnames[i], ".lib") || strstr(libnames[i], ".a")
                      ? xstrdup(libnames[i])
                      : lib_path_for(libnames[i], libdirs, nlibdirs);
        load_lib(p);
    }

    if (!pull_symbol(entry))
        die("entry symbol %s is not defined by any input or library", entry);
    link_objects();
    layout();
    define_linker_symbols();
    compute_addresses();

    {
        int gi = gsym_find(entry);
        if (gi < 0 || !gsyms[gi].defined)
            die("entry symbol %s not found", entry);
    }

    copy_sections();
    apply_relocs();
    write_image(outpath, entry, u1, u2, u3, heapmin, heapmax, stack, priority);
    return 0;
}
