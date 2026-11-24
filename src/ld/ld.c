#include "../common/ac.h"

#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define EM_ARM 40
#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_DYNSYM 11
#define SHT_ARM_EXIDX 0x70000001
#define SHT_ARM_ATTRIBUTES 0x70000003
#define SHF_WRITE 1
#define SHF_ALLOC 2
#define SHF_EXECINSTR 4
#define SHF_LINK_ORDER 0x80

#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define SHN_UNDEF 0
#define SHN_ABS 0xfff1
#define SHN_COMMON 0xfff2

#define R_ARM_NONE 0
#define R_ARM_PC24 1
#define R_ARM_ABS32 2
#define R_ARM_REL32 3
#define R_ARM_ABS16 5
#define R_ARM_ABS12 6
#define R_ARM_THM_PC22 10
#define R_ARM_CALL 28
#define R_ARM_JUMP24 29
#define R_ARM_THM_JUMP24 30
#define R_ARM_TARGET1 38
#define R_ARM_V4BX 40
#define R_ARM_PREL31 42
#define R_ARM_MOVW_ABS_NC 43
#define R_ARM_MOVT_ABS 44
#define R_ARM_MOVW_PREL_NC 45
#define R_ARM_MOVT_PREL 46
#define R_ARM_THM_MOVW_ABS_NC 47
#define R_ARM_THM_MOVT_ABS 48

enum { O_TEXT = 0, O_EXIDX, O_RODATA, O_DATA, O_BSS, O_DIRECTIVE, O_ATTR, O_COUNT };

typedef struct {
    const char *name;
    u32 type;
    u32 flags;
    u32 align;
} OutKindInfo;

static const OutKindInfo k_out[O_COUNT] = {
    {".text", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR, 4},
    {".ARM.exidx", SHT_ARM_EXIDX, SHF_ALLOC | SHF_LINK_ORDER, 4},
    {".rodata", SHT_PROGBITS, SHF_ALLOC, 8},
    {".data", SHT_PROGBITS, SHF_ALLOC | SHF_WRITE, 8},
    {".bss", SHT_NOBITS, SHF_ALLOC | SHF_WRITE, 8},
    {".directive", SHT_PROGBITS, 0, 4},
    {".ARM.attributes", SHT_ARM_ATTRIBUTES, 0, 1},
};

typedef struct {
    u32 type;
    u32 flags;
    u32 addr;
    u32 size;
    u32 align;
    u32 off;
    int present;
    Buf data;
} OutSec;

typedef struct {
    char *name;
    u32 type;
    u32 flags;
    u32 size;
    u32 align;
    const u8 *data;
    int out;
    u32 out_off;
} InSec;

typedef struct {
    u32 name_off;
    u32 value;
    u32 size;
    u8 info;
    u16 shndx;
} InSym;

typedef struct Obj {
    char *path;
    Buf file;
    int nsec;
    InSec *secs;
    char *shstr;
    u32 shstr_size;
    int nsym;
    InSym *syms;
    const char *strtab;
    u32 strtab_size;
    int is_member;
    char *marker;
    struct Obj *next;
} Obj;

typedef struct {
    char *sec;
    u32 off;
    u32 type;
    char *sym;
} PendingRel;

typedef struct {
    char *name;
    u32 off;
    u32 size;
} ArMember;

typedef struct Arch {
    char *path;
    Buf file;
    ArMember *members;
    int nmembers;
    int parsed;
    struct Arch *next;
} Arch;

typedef struct GSym {
    char *name;
    Obj *obj;
    int idx;
    u32 addr;
    int defined;
    int weak;
    int is_common;
    u32 common_size;
    u32 common_align;
    u32 common_addr;
    u32 forced_addr;
    int forced;
    struct GSym *next;
} GSym;

#define NBUCKET 16384
static GSym *g_buckets[NBUCKET];
static Obj *g_objs, *g_objs_tail;
static Arch *g_archs, *g_archs_tail;
static OutSec g_out[O_COUNT];
static PendingRel *g_prel;
static int g_nprel, g_cprel;
static u32 g_base;
static char *g_out_path;
static StrVec g_entry_names;
static StrVec g_libdirs;
static int g_verbose;
static int g_allow_undefined;
static int g_map;

static unsigned hash_name(const char *s)
{
    unsigned h = 5381u;
    while (*s)
        h = (h * 33u) ^ (unsigned char)*s++;
    return h & (NBUCKET - 1);
}

static GSym *gsym_find(const char *name)
{
    GSym *g = g_buckets[hash_name(name)];
    for (; g; g = g->next)
        if (strcmp(g->name, name) == 0)
            return g;
    return NULL;
}

static GSym *gsym_get(const char *name)
{
    unsigned h = hash_name(name);
    GSym *g = g_buckets[h];
    for (; g; g = g->next)
        if (strcmp(g->name, name) == 0)
            return g;
    g = ac_calloc(1, sizeof(GSym));
    g->name = ac_strdup(name);
    g->next = g_buckets[h];
    g_buckets[h] = g;
    return g;
}

static const char *sym_str(Obj *o, InSym *s)
{
    if (!o->strtab || s->name_off >= o->strtab_size)
        return "";
    return o->strtab + s->name_off;
}

static int kind_of(const char *name, u32 type, u32 flags)
{
    if (type == SHT_ARM_ATTRIBUTES || strcmp(name, ".ARM.attributes") == 0)
        return O_ATTR;
    if (strcmp(name, ".directive") == 0)
        return O_DIRECTIVE;
    if (strncmp(name, ".debug", 6) == 0 || strcmp(name, ".comment") == 0 ||
        strncmp(name, ".note", 5) == 0 || strncmp(name, ".stab", 5) == 0 ||
        strcmp(name, ".line") == 0 || strcmp(name, ".ident") == 0)
        return -1;
    if (strcmp(name, ".ARM.exidx") == 0)
        return O_EXIDX;
    if (strcmp(name, ".init_array") == 0 || strcmp(name, ".ctors") == 0 ||
        strcmp(name, ".fini_array") == 0 || strcmp(name, ".dtors") == 0)
        return O_RODATA;
    if (type == SHT_NOBITS || strcmp(name, ".bss") == 0 || strncmp(name, ".bss.", 5) == 0)
        return (flags & SHF_ALLOC) ? O_BSS : -1;
    if (strncmp(name, ".rodata", 7) == 0 || strncmp(name, ".data.ro", 8) == 0 ||
        strncmp(name, ".const", 6) == 0)
        return O_RODATA;
    if (flags & SHF_EXECINSTR)
        return O_TEXT;
    if (flags & SHF_ALLOC)
        return (flags & SHF_WRITE) ? O_DATA : O_RODATA;
    return -1;
}

static int parse_elf(Obj *o)
{
    const u8 *d = o->file.data;
    size_t len = o->file.len;
    u32 shoff, shentsize, shnum, shstrndx, i;
    u32 *names, *links;
    if (len < 52 || memcmp(d, "\177ELF", 4) != 0 || d[4] != 1 || d[5] != 1)
        return -1;
    if (rd16(d + 18) != EM_ARM)
        return -1;
    shoff = rd32(d + 32);
    shentsize = rd16(d + 46);
    shnum = rd16(d + 48);
    shstrndx = rd16(d + 50);
    if (shentsize != 40 || shnum == 0 || (u64)shoff + (u64)shnum * 40 > len)
        return -1;
    o->nsec = (int)shnum;
    o->secs = ac_calloc(shnum, sizeof(InSec));
    names = ac_calloc(shnum, sizeof(u32));
    links = ac_calloc(shnum, sizeof(u32));
    for (i = 0; i < shnum; i++) {
        const u8 *p = d + shoff + i * 40;
        u32 off = rd32(p + 16), size = rd32(p + 20);
        names[i] = rd32(p);
        links[i] = rd32(p + 24);
        o->secs[i].type = rd32(p + 4);
        o->secs[i].flags = rd32(p + 8);
        o->secs[i].size = size;
        o->secs[i].align = rd32(p + 32);
        o->secs[i].out = -1;
        o->secs[i].out_off = 0;
        if (o->secs[i].type != SHT_NOBITS && o->secs[i].type != SHT_NULL && size) {
            if ((u64)off + size > len) {
                free(names);
                free(links);
                return -1;
            }
            o->secs[i].data = d + off;
        }
    }
    if (shstrndx < shnum && o->secs[shstrndx].data) {
        o->shstr = (char *)o->secs[shstrndx].data;
        o->shstr_size = o->secs[shstrndx].size;
    }
    for (i = 0; i < shnum; i++) {
        if (o->shstr && names[i] < o->shstr_size)
            o->secs[i].name = o->shstr + names[i];
        else
            o->secs[i].name = (char *)"";
    }
    for (i = 0; i < shnum; i++) {
        if (o->secs[i].type == SHT_SYMTAB || o->secs[i].type == SHT_DYNSYM) {
            u32 link = links[i];
            if (link < shnum && o->secs[link].data) {
                int k;
                o->strtab = (const char *)o->secs[link].data;
                o->strtab_size = o->secs[link].size;
                o->nsym = (int)(o->secs[i].size / 16);
                o->syms = ac_calloc((size_t)(o->nsym ? o->nsym : 1), sizeof(InSym));
                for (k = 0; k < o->nsym; k++) {
                    const u8 *p = o->secs[i].data + k * 16;
                    o->syms[k].name_off = rd32(p);
                    o->syms[k].value = rd32(p + 4);
                    o->syms[k].size = rd32(p + 8);
                    o->syms[k].info = p[12];
                    o->syms[k].shndx = rd16(p + 14);
                }
            }
            break;
        }
    }
    free(names);
    free(links);
    return 0;
}

static void obj_append(Obj *o)
{
    if (!g_objs)
        g_objs = g_objs_tail = o;
    else {
        g_objs_tail->next = o;
        g_objs_tail = o;
    }
}

static void obj_add_symbols(Obj *o)
{
    int i;
    for (i = 1; i < o->nsym; i++) {
        InSym *s = &o->syms[i];
        int bind = s->info >> 4;
        const char *name;
        GSym *g;
        if (bind == STB_LOCAL)
            continue;
        name = sym_str(o, s);
        if (!name[0])
            continue;
        if (name[0] == '#' && name[1] == '<') {
            GSym *mg;
            if (!o->marker)
                o->marker = ac_strdup(name);
            mg = gsym_get(name);
            if (!mg->defined) {
                mg->obj = o;
                mg->idx = i;
                mg->forced = 1;
                mg->defined = 1;
            }
            continue;
        }
        g = gsym_get(name);
        if (s->shndx == SHN_UNDEF) {
            if (bind == STB_WEAK)
                g->weak = 1;
            continue;
        }
        if (s->shndx == SHN_COMMON) {
            if (!g->defined && !g->is_common) {
                g->is_common = 1;
                g->common_size = s->size ? s->size : (s->value ? s->value : 4);
                g->common_align = s->value ? s->value : 4;
                g->weak = (bind == STB_WEAK);
            }
            continue;
        }
        if (g->defined && (!g->weak || bind == STB_WEAK))
            continue;
        g->obj = o;
        g->idx = i;
        g->defined = 1;
        g->is_common = 0;
        g->weak = (bind == STB_WEAK);
    }
}

static Obj *obj_parse(const char *path, int member, const u8 *data, size_t len)
{
    Obj *o = ac_calloc(1, sizeof(Obj));
    o->path = ac_strdup(path);
    o->is_member = member;
    buf_init(&o->file);
    buf_put(&o->file, data, len);
    if (parse_elf(o) != 0) {
        buf_free(&o->file);
        free(o->path);
        free(o);
        return NULL;
    }
    return o;
}

static void arch_parse(Arch *a)
{
    const u8 *d = a->file.data;
    size_t len = a->file.len;
    size_t off = 8;
    int cap = 0;
    if (a->parsed)
        return;
    a->parsed = 1;
    if (len < 8 || memcmp(d, "!<arch>\n", 8) != 0)
        ac_die("%s: not an archive", a->path);
    while (off + 60 <= len) {
        const u8 *h = d + off;
        char nm[17];
        long size;
        memcpy(nm, h, 16);
        nm[16] = 0;
        {
            char tmp[11];
            memcpy(tmp, h + 48, 10);
            tmp[10] = 0;
            size = atol(tmp);
        }
        if (size <= 0 || off + 60 + (size_t)size > len)
            break;
        if (a->nmembers == cap) {
            cap = cap ? cap * 2 : 64;
            a->members = ac_realloc(a->members, sizeof(ArMember) * (size_t)cap);
        }
        a->members[a->nmembers].name = ac_strdup(nm);
        a->members[a->nmembers].off = (u32)(off + 60);
        a->members[a->nmembers].size = (u32)size;
        a->nmembers++;
        off += 60 + (size_t)size + (size & 1);
    }
}

static int arch_try_member(Arch *a, ArMember *m, const char *want)
{
    Obj *o;
    int i, hit = 0;
    if (m->size < 52 || a->file.data[m->off] != 0x7f)
        return 0;
    o = obj_parse(a->path, 1, a->file.data + m->off, m->size);
    if (!o)
        return 0;
    for (i = 1; i < o->nsym; i++) {
        InSym *s = &o->syms[i];
        if ((s->info >> 4) == STB_LOCAL || s->shndx == SHN_UNDEF || s->shndx == SHN_COMMON)
            continue;
        if (strcmp(sym_str(o, s), want) == 0) {
            hit = 1;
            break;
        }
    }
    if (!hit) {
        buf_free(&o->file);
        free(o->path);
        free(o->secs);
        free(o->syms);
        free(o);
        return 0;
    }
    obj_append(o);
    obj_add_symbols(o);
    ac_info("pull %s <- %s", want, a->path);
    return 1;
}

static int pull_from_archives(const char *name)
{
    Arch *a;
    for (a = g_archs; a; a = a->next) {
        int k;
        arch_parse(a);
        for (k = 0; k < a->nmembers; k++)
            if (arch_try_member(a, &a->members[k], name))
                return 1;
    }
    return 0;
}

static void resolve_archives(void)
{
    int progress = 1;
    while (progress) {
        int i;
        progress = 0;
        for (i = 0; i < NBUCKET; i++) {
            GSym *g = g_buckets[i];
            for (; g; g = g->next) {
                if (g->defined || g->is_common || g->weak)
                    continue;
                if (pull_from_archives(g->name))
                    progress = 1;
            }
        }
    }
}

static void report_undefined(void)
{
    int i, n = 0;
    for (i = 0; i < NBUCKET; i++) {
        GSym *g = g_buckets[i];
        for (; g; g = g->next) {
            if (g->defined || g->is_common || g->weak)
                continue;
            ac_warn("undefined reference: %s", g->name);
            if (++n >= 25) {
                ac_warn("... suppressed");
                if (!g_allow_undefined)
                    ac_die("%d+ undefined references", n);
                return;
            }
        }
    }
    if (n && !g_allow_undefined)
        ac_die("%d undefined reference(s)", n);
}

static u32 align_up(u32 v, u32 a)
{
    if (a < 2)
        return v;
    return (v + a - 1) & ~(a - 1);
}

static void layout(void)
{
    Obj *o;
    int i;
    u32 addr;
    u32 cbase, cmax;
    int attr_taken = 0;

    for (i = 0; i < O_COUNT; i++) {
        g_out[i].type = k_out[i].type;
        g_out[i].flags = k_out[i].flags;
        g_out[i].align = k_out[i].align;
        g_out[i].addr = 0;
        g_out[i].size = 0;
        g_out[i].off = 0;
        g_out[i].present = 0;
        buf_init(&g_out[i].data);
    }

    for (o = g_objs; o; o = o->next) {
        int k;
        for (k = 1; k < o->nsec; k++) {
            InSec *s = &o->secs[k];
            if (s->type == SHT_NULL || s->type == SHT_SYMTAB || s->type == SHT_STRTAB ||
                s->type == SHT_REL || s->type == SHT_RELA || s->type == SHT_DYNSYM)
                continue;
            s->out = kind_of(s->name, s->type, s->flags);
            if (s->out < 0)
                continue;
            if (s->out == O_ATTR) {
                if (attr_taken || s->size == 0)
                    s->out = -1;
                else
                    attr_taken = 1;
            }
        }
    }

    for (i = 0; i < O_COUNT; i++) {
        u32 cur = 0;
        if (i == O_ATTR)
            continue;
        for (o = g_objs; o; o = o->next) {
            int k;
            for (k = 1; k < o->nsec; k++) {
                InSec *s = &o->secs[k];
                u32 a;
                if (s->out != i || !s->size)
                    continue;
                a = s->align < 2 ? 4 : s->align;
                cur = align_up(cur, a);
                s->out_off = cur;
                cur += s->size;
            }
        }
        g_out[i].size = cur;
        g_out[i].present = cur > 0;
    }
    for (o = g_objs; o; o = o->next) {
        int k;
        for (k = 1; k < o->nsec; k++) {
            if (o->secs[k].out == O_ATTR) {
                g_out[O_ATTR].size = o->secs[k].size;
                g_out[O_ATTR].present = 1;
            }
        }
    }

    addr = align_up(g_base, 4);
    g_out[O_TEXT].addr = addr;
    addr += g_out[O_TEXT].size;
    addr = align_up(addr, 4);
    g_out[O_EXIDX].addr = addr;
    addr += g_out[O_EXIDX].size;
    addr = align_up(addr, 8);
    g_out[O_RODATA].addr = addr;
    addr += g_out[O_RODATA].size;
    addr = align_up(addr, 8);
    g_out[O_DATA].addr = addr;
    addr += g_out[O_DATA].size;
    addr = align_up(addr, 8);
    g_out[O_BSS].addr = addr;
    addr += g_out[O_BSS].size;
    addr = align_up(addr, 4);
    g_out[O_DIRECTIVE].addr = addr;
    addr += g_out[O_DIRECTIVE].size;

    cbase = g_out[O_BSS].addr + g_out[O_BSS].size;
    cmax = cbase;
    for (i = 0; i < NBUCKET; i++) {
        GSym *g = g_buckets[i];
        for (; g; g = g->next) {
            if (!g->is_common)
                continue;
            cmax = align_up(cmax, g->common_align ? g->common_align : 4);
            g->common_addr = cmax;
            cmax += g->common_size;
        }
    }
    if (cmax > cbase) {
        g_out[O_BSS].size += cmax - cbase;
        g_out[O_BSS].present = 1;
    }
}

static u32 insec_addr(Obj *o, u32 shndx)
{
    InSec *s;
    if (shndx >= (u32)o->nsec)
        return 0;
    s = &o->secs[shndx];
    if (s->out < 0)
        return 0;
    return g_out[s->out].addr + s->out_off;
}

static u32 gsym_addr(GSym *g)
{
    InSym *s;
    if (g->is_common)
        return g->common_addr;
    s = &g->obj->syms[g->idx];
    if (s->shndx == SHN_ABS)
        return s->value;
    return insec_addr(g->obj, s->shndx) + s->value;
}

static void finalize_globals(void)
{
    int i;
    for (i = 0; i < NBUCKET; i++) {
        GSym *g = g_buckets[i];
        for (; g; g = g->next)
            if (g->defined)
                g->addr = gsym_addr(g);
    }
}

static u32 sym_resolve(Obj *o, u32 idx, const char **nm, int *undef)
{
    InSym *s;
    if (idx == 0) {
        *nm = "";
        *undef = 0;
        return 0;
    }
    if (idx >= (u32)o->nsym) {
        *nm = "?";
        *undef = 1;
        return 0;
    }
    s = &o->syms[idx];
    *nm = sym_str(o, s);
    if (o->marker && strcmp(*nm, "theImportedSymbol") == 0) {
        GSym *mg = gsym_find(o->marker);
        *nm = o->marker;
        *undef = 0;
        return mg ? (mg->defined ? mg->forced_addr : 0) : 0;
    }
    if ((*nm)[0] == '#' && (*nm)[1] == '<') {
        *undef = 0;
        return 0;
    }
    if (s->shndx == SHN_UNDEF) {
        GSym *g = gsym_find(*nm);
        if (!g || (!g->defined && !g->is_common)) {
            *undef = 1;
            return 0;
        }
        *undef = 0;
        return g->is_common ? g->common_addr : g->addr;
    }
    *undef = 0;
    if (s->shndx == SHN_ABS)
        return s->value;
    return insec_addr(o, s->shndx) + s->value;
}

static void define_markers(void)
{
    int i;
    for (i = 0; i < NBUCKET; i++) {
        GSym *g = g_buckets[i];
        for (; g; g = g->next) {
            Obj *o;
            int k, found = -1;
            if (!g->forced || !g->obj)
                continue;
            o = g->obj;
            for (k = 1; k < o->nsym; k++) {
                InSym *sym = &o->syms[k];
                if (sym->shndx == SHN_UNDEF)
                    continue;
                if (strcmp(sym_str(o, sym), "theImportedSymbol") == 0) {
                    found = k;
                    break;
                }
            }
            if (found < 0) {
                for (k = 1; k < o->nsym; k++) {
                    InSym *sym = &o->syms[k];
                    if (sym->shndx == SHN_UNDEF || sym->shndx == SHN_ABS)
                        continue;
                    if (strstr(o->secs[sym->shndx].name, "StubCode") || o->secs[sym->shndx].flags & SHF_EXECINSTR) {
                        found = k;
                        break;
                    }
                }
            }
            if (found >= 0)
                g->forced_addr = insec_addr(o, o->syms[found].shndx) + o->syms[found].value;
            else
                g->forced_addr = 0;
            g->addr = g->forced_addr;
        }
    }
}

static void fill_sections(void)
{
    Obj *o;
    int i;
    for (i = 0; i < O_COUNT; i++) {
        if (!g_out[i].present)
            continue;
        buf_zeros(&g_out[i].data, g_out[i].size);
    }
    for (o = g_objs; o; o = o->next) {
        int k;
        for (k = 1; k < o->nsec; k++) {
            InSec *in = &o->secs[k];
            if (in->out < 0 || !in->size || !in->data)
                continue;
            if ((size_t)in->out_off + in->size > g_out[in->out].data.len) {
                ac_die("internal: section overlap");
                return;
            }
            memcpy(g_out[in->out].data.data + in->out_off, in->data, in->size);
        }
    }
}

static int reloc_apply(Obj *o, u32 type, u32 place, u32 s, i32 a, u8 *p, const char *nm)
{
    switch (type) {
    case R_ARM_NONE:
    case R_ARM_V4BX:
        return 0;
    case R_ARM_ABS32:
    case R_ARM_TARGET1:
        wr32(p, s + (u32)a);
        return 0;
    case R_ARM_REL32:
        wr32(p, (u32)((i64)s + a - (i64)place));
        return 0;
    case R_ARM_ABS16: {
        i64 v = (i64)s + a;
        if (v < -32768 || v > 65535)
            ac_warn("%s: R_ARM_ABS16 overflow: %s", o->path, nm);
        wr16(p, (u16)v);
        return 0;
    }
    case R_ARM_ABS12: {
        u32 insn = rd32(p);
        i64 v = (i64)s + a;
        if (v < 0 || v > 4095)
            ac_warn("%s: R_ARM_ABS12 overflow: %s", o->path, nm);
        wr32(p, (insn & ~0xfffu) | ((u32)v & 0xfffu));
        return 0;
    }
    case R_ARM_PC24:
    case R_ARM_CALL:
    case R_ARM_JUMP24: {
        u32 insn = rd32(p);
        u32 cond = insn & 0xf0000000u;
        u32 link = (insn >> 24) & 1u;
        i64 target = (i64)s + a;
        i64 off, imm24;
        if (target & 1) {
            target &= ~1ll;
            off = target - (i64)place;
            imm24 = off >> 2;
            if (imm24 < -(1 << 23) || imm24 >= (1 << 23)) {
                ac_die("%s: branch out of range: %s", o->path, nm);
                return -1;
            }
            wr32(p, cond | 0xfa000000u | 0x01000000u | ((u32)imm24 & 0xffffffu));
            return 0;
        }
        off = target - (i64)place;
        imm24 = off >> 2;
        if (imm24 < -(1 << 23) || imm24 >= (1 << 23)) {
            ac_die("%s: branch out of range: %s (delta %lld)", o->path, nm, (long long)off);
            return -1;
        }
        wr32(p, cond | 0x0a000000u | (link << 24) | ((u32)imm24 & 0xffffffu));
        return 0;
    }
    case R_ARM_PREL31: {
        u32 insn = rd32(p);
        u32 off = (u32)((i64)s + a - (i64)place);
        wr32(p, (insn & 0x80000000u) | (off & 0x7fffffffu));
        return 0;
    }
    case R_ARM_MOVW_ABS_NC:
    case R_ARM_MOVW_PREL_NC: {
        u32 insn = rd32(p);
        u32 v = (type == R_ARM_MOVW_ABS_NC) ? (u32)((i64)s + a) : (u32)((i64)s + a - (i64)place);
        wr32(p, (insn & ~0x000f0fffu) | (((v >> 12) & 0xfu) << 16) | (v & 0xfffu));
        return 0;
    }
    case R_ARM_MOVT_ABS:
    case R_ARM_MOVT_PREL: {
        u32 insn = rd32(p);
        u32 v = (type == R_ARM_MOVT_ABS) ? (u32)((i64)s + a) : (u32)((i64)s + a - (i64)place);
        v >>= 16;
        wr32(p, (insn & ~0x000f0fffu) | (((v >> 12) & 0xfu) << 16) | (v & 0xfffu));
        return 0;
    }
    case R_ARM_THM_MOVW_ABS_NC:
    case R_ARM_THM_MOVT_ABS: {
        u32 v = (u32)((i64)s + a);
        u32 hi, lo;
        if (type == R_ARM_THM_MOVT_ABS)
            v >>= 16;
        hi = rd16(p);
        lo = rd16(p + 2);
        hi = (hi & ~0x000fu) | ((v >> 12) & 0xfu);
        lo = (lo & ~0x70ffu) | (((v >> 11) & 1u) << 10) | (v & 0xffu);
        wr16(p, (u16)hi);
        wr16(p + 2, (u16)lo);
        return 0;
    }
    case R_ARM_THM_PC22:
    case R_ARM_THM_JUMP24: {
        u32 hi = rd16(p), lo = rd16(p + 2);
        i64 off = ((i64)(s & ~1u) + a) - (i64)(place & ~1u);
        i64 imm;
        if (off < -16777216 || off > 16777214) {
            ac_die("%s: thumb branch out of range: %s", o->path, nm);
            return -1;
        }
        imm = off >> 1;
        hi = (hi & ~0x07ffu) | ((u32)(imm >> 11) & 0x07ffu);
        lo = (lo & ~0x2fffu) | ((u32)imm & 0x07ffu) | ((u32)((imm >> 11) & 1) << 13);
        wr16(p, (u16)hi);
        wr16(p + 2, (u16)lo);
        return 0;
    }
    default:
        ac_warn("%s: unsupported relocation %u against %s", o->path, type, nm);
        return -1;
    }
}

static void apply_relocs(void)
{
    Obj *o;
    int i;
    for (o = g_objs; o; o = o->next) {
        for (i = 1; i < o->nsec; i++) {
            InSec *rs = &o->secs[i];
            u32 info, n, k;
            InSec *ts;
            if (rs->type != SHT_REL && rs->type != SHT_RELA)
                continue;
            {
                u32 idx = (u32)i;
                const u8 *p = o->file.data + rd32(o->file.data + 32) + idx * 40;
                info = rd32(p + 28);
            }
            if (info == 0 || info >= (u32)o->nsec)
                continue;
            ts = &o->secs[info];
            if (ts->out < 0 || ts->type == SHT_NOBITS)
                continue;
            n = rs->size / (rs->type == SHT_RELA ? 12 : 8);
            for (k = 0; k < n; k++) {
                const u8 *rp = rs->data + k * (rs->type == SHT_RELA ? 12 : 8);
                u32 r_off = rd32(rp);
                u32 r_info = rd32(rp + 4);
                u32 type = r_info & 0xffu;
                u32 symidx = r_info >> 8;
                i32 addend = rs->type == SHT_RELA ? (i32)rd32(rp + 8) : 0;
                u32 s;
                const char *nm;
                int undef;
                u8 *place;
                u32 paddr;
                if ((u64)r_off + 4 > ts->size)
                    continue;
                s = sym_resolve(o, symidx, &nm, &undef);
                if (undef) {
                    if (!g_allow_undefined)
                        ac_die("%s: undefined symbol %s", o->path, nm);
                    s = 0;
                }
                place = g_out[ts->out].data.data + ts->out_off + r_off;
                paddr = g_out[ts->out].addr + ts->out_off + r_off;
                reloc_apply(o, type, paddr, s, addend, place, nm);
                if ((type == R_ARM_ABS32 || type == R_ARM_TARGET1) && !undef &&
                    nm[0] &&
                    (ts->out == O_TEXT || ts->out == O_RODATA || ts->out == O_DATA)) {
                    PendingRel *pr;
                    if (g_nprel == g_cprel) {
                        g_cprel = g_cprel ? g_cprel * 2 : 64;
                        g_prel = ac_realloc(g_prel, sizeof(PendingRel) * (size_t)g_cprel);
                    }
                    pr = &g_prel[g_nprel++];
                    pr->sec = (char *)(ts->out == O_DATA ? ".rel.data" : ".rel.text");
                    pr->off = ts->out_off + r_off;
                    pr->type = R_ARM_ABS32;
                    pr->sym = ac_strdup(nm);
                }
            }
        }
    }
}

typedef struct {
    const char *name;
    u32 value;
    u32 size;
    u8 info;
    u16 shndx;
} OutSym;

static void emit(const char *path)
{
    Buf img, strtab, shstr;
    Buf relb[2];
    OutSym *syms = NULL;
    u32 *sym_name_off = NULL;
    int nsyms = 0, cap = 0;
    u32 first_global;
    int i, k, j;
    int sec_list[O_COUNT];
    int nsec_list = 0;
    u32 sec_off[O_COUNT];
    u32 sec_nm[O_COUNT];
    u32 pos, symtab_off, strtab_off, shstrtab_off, shoff;
    u32 nm_symtab, nm_strtab, nm_shstrtab, nm_rel[2];
    u32 rel_off[2];
    int rel_present[2];
    int nrel = 0;
    u32 entry = 0;
    u16 shnum;
    static const char *rel_names[2] = {".rel.text", ".rel.data"};

    buf_init(&img);
    buf_init(&strtab);
    buf_init(&shstr);
    buf_init(&relb[0]);
    buf_init(&relb[1]);
    buf_zeros(&strtab, 1);
    buf_zeros(&shstr, 1);

    for (k = 0; k < g_entry_names.count; k++) {
        GSym *g = gsym_find(g_entry_names.items[k]);
        if (g && (g->defined || g->is_common)) {
            entry = g->is_common ? g->common_addr : g->addr;
            break;
        }
    }

    for (i = 0; i < O_COUNT; i++)
        if (g_out[i].present)
            sec_list[nsec_list++] = i;

    cap = nsec_list + 128;
    syms = ac_calloc((size_t)cap, sizeof(OutSym));
    for (i = 0; i < nsec_list; i++) {
        syms[i].name = "";
        syms[i].value = g_out[sec_list[i]].addr;
        syms[i].size = 0;
        syms[i].info = (STB_LOCAL << 4) | STT_SECTION;
        syms[i].shndx = (u16)(i + 1);
    }
    nsyms = nsec_list;
    first_global = (u32)nsyms + 1;
    for (i = 0; i < NBUCKET; i++) {
        GSym *g = g_buckets[i];
        for (; g; g = g->next) {
            InSym *is;
            u16 shndx = SHN_ABS;
            if (!g->defined || g->is_common)
                continue;
            if (nsyms == cap) {
                cap *= 2;
                syms = ac_realloc(syms, sizeof(OutSym) * (size_t)cap);
            }
            if (g->forced) {
                syms[nsyms].name = g->name;
                syms[nsyms].value = g->forced_addr;
                syms[nsyms].size = 0;
                syms[nsyms].info = (STB_GLOBAL << 4) | STT_NOTYPE;
                syms[nsyms].shndx = SHN_ABS;
                nsyms++;
                continue;
            }
            is = &g->obj->syms[g->idx];
            if (is->shndx != SHN_ABS && is->shndx < (u16)g->obj->nsec) {
                int oi = g->obj->secs[is->shndx].out;
                if (oi >= 0)
                    for (j = 0; j < nsec_list; j++)
                        if (sec_list[j] == oi) {
                            shndx = (u16)(j + 1);
                            break;
                        }
            }
            syms[nsyms].name = g->name;
            syms[nsyms].value = g->addr;
            syms[nsyms].size = is->size;
            syms[nsyms].info = (u8)((((is->info >> 4) == STB_WEAK) ? STB_WEAK : STB_GLOBAL) << 4) | (is->info & 0xfu);
            syms[nsyms].shndx = shndx;
            nsyms++;
        }
    }

    sym_name_off = ac_calloc((size_t)nsyms, sizeof(u32));
    for (i = 0; i < nsyms; i++) {
        if ((syms[i].info >> 4) == STB_LOCAL || !syms[i].name[0]) {
            sym_name_off[i] = 0;
        } else {
            sym_name_off[i] = (u32)strtab.len;
            buf_put(&strtab, syms[i].name, strlen(syms[i].name) + 1);
        }
    }

    for (i = 0; i < 2; i++)
        rel_present[i] = 0;
    for (k = 0; k < g_nprel; k++) {
        int idx = -1;
        int which = strcmp(g_prel[k].sec, ".rel.data") == 0 ? 1 : 0;
        for (i = 0; i < nsyms; i++) {
            if (syms[i].name[0] && strcmp(syms[i].name, g_prel[k].sym) == 0) {
                idx = i;
                break;
            }
        }
        if (idx < 0)
            continue;
        buf_u32(&relb[which], g_prel[k].off);
        buf_u32(&relb[which], ((u32)idx << 8) | (g_prel[k].type & 0xffu));
        rel_present[which] = 1;
    }
    for (i = 0; i < 2; i++)
        if (rel_present[i])
            nrel++;

    for (i = 0; i < nsec_list; i++) {
        sec_nm[i] = (u32)shstr.len;
        buf_put(&shstr, k_out[sec_list[i]].name, strlen(k_out[sec_list[i]].name) + 1);
    }
    for (i = 0; i < 2; i++) {
        nm_rel[i] = 0;
        if (!rel_present[i])
            continue;
        nm_rel[i] = (u32)shstr.len;
        buf_put(&shstr, rel_names[i], strlen(rel_names[i]) + 1);
    }
    nm_symtab = (u32)shstr.len;
    buf_put(&shstr, ".symtab", 8);
    nm_strtab = (u32)shstr.len;
    buf_put(&shstr, ".strtab", 8);
    nm_shstrtab = (u32)shstr.len;
    buf_put(&shstr, ".shstrtab", 11);

    pos = 52 + 3 * 32;
    for (i = 0; i < nsec_list; i++) {
        OutSec *sc = &g_out[sec_list[i]];
        if (sc->type == SHT_NOBITS) {
            sec_off[i] = 0;
            continue;
        }
        pos = (u32)align_up(pos, sc->align ? sc->align : 1);
        sec_off[i] = pos;
        pos += (u32)sc->data.len;
    }
    for (i = 0; i < 2; i++) {
        rel_off[i] = 0;
        if (!rel_present[i])
            continue;
        pos = (u32)align_up(pos, 4);
        rel_off[i] = pos;
        pos += (u32)relb[i].len;
    }
    symtab_off = (u32)align_up(pos, 4);
    strtab_off = symtab_off + (u32)nsyms * 16;
    shstrtab_off = strtab_off + (u32)strtab.len;
    shoff = (u32)align_up(shstrtab_off + (u32)shstr.len, 4);
    shnum = (u16)(1 + nsec_list + nrel + 3);

    buf_zeros(&img, 52 + 3 * 32);
    for (i = 0; i < nsec_list; i++) {
        OutSec *sc = &g_out[sec_list[i]];
        if (sc->type == SHT_NOBITS || sc->data.len == 0)
            continue;
        while (img.len < sec_off[i])
            buf_u8(&img, 0);
        buf_put(&img, sc->data.data, sc->data.len);
    }
    for (i = 0; i < 2; i++) {
        if (!rel_present[i])
            continue;
        while (img.len < rel_off[i])
            buf_u8(&img, 0);
        buf_put(&img, relb[i].data, relb[i].len);
    }
    while (img.len < symtab_off)
        buf_u8(&img, 0);
    for (i = 0; i < nsyms; i++) {
        buf_u32(&img, sym_name_off[i]);
        buf_u32(&img, syms[i].value);
        buf_u32(&img, syms[i].size);
        buf_u8(&img, syms[i].info);
        buf_u8(&img, 0);
        buf_u16(&img, syms[i].shndx);
    }
    while (img.len < strtab_off)
        buf_u8(&img, 0);
    buf_put(&img, strtab.data, strtab.len);
    while (img.len < shstrtab_off)
        buf_u8(&img, 0);
    buf_put(&img, shstr.data, shstr.len);
    while (img.len < shoff)
        buf_u8(&img, 0);

    {
        u32 text_off = 0, ro_end = 0, text_va = g_base;
        u32 data_off = 0, data_va = 0, data_sz = 0, data_mem = 0;
        u32 ex_off = 0, ex_va = 0, ex_sz = 0;
        int have_data = 0;
        for (i = 0; i < nsec_list; i++) {
            OutSec *sc = &g_out[sec_list[i]];
            if ((sc->flags & SHF_ALLOC) == 0)
                continue;
            if (sc->flags & SHF_WRITE) {
                if (sc->type == SHT_NOBITS) {
                    if (!have_data)
                        data_va = sc->addr;
                    data_mem = sc->addr + sc->size - data_va;
                } else {
                    if (!have_data) {
                        data_off = sec_off[i];
                        data_va = sc->addr;
                    }
                    have_data = 1;
                    data_sz = sc->addr + sc->size - data_va;
                    data_mem = data_sz;
                }
                continue;
            }
            if (sc->type == SHT_ARM_EXIDX) {
                ex_off = sec_off[i];
                ex_va = sc->addr;
                ex_sz = sc->size;
                continue;
            }
            if (sec_off[i] + sc->size > ro_end)
                ro_end = sec_off[i] + sc->size;
        }
        for (i = 0; i < nsec_list; i++)
            if (sec_list[i] == O_TEXT) {
                text_off = sec_off[i];
                text_va = g_out[O_TEXT].addr;
            }
        wr32(img.data + 28, 52);
        wr16(img.data + 42, 32);
        wr16(img.data + 44, 3);
        {
            u32 ph = 52;
            wr32(img.data + ph + 0, 1);
            wr32(img.data + ph + 4, text_off);
            wr32(img.data + ph + 8, text_va);
            wr32(img.data + ph + 12, text_va);
            wr32(img.data + ph + 16, ro_end - text_off);
            wr32(img.data + ph + 20, ro_end - text_off);
            wr32(img.data + ph + 24, 5);
            wr32(img.data + ph + 28, 4);
            ph += 32;
            wr32(img.data + ph + 0, 1);
            wr32(img.data + ph + 4, have_data ? data_off : 0);
            wr32(img.data + ph + 8, data_va);
            wr32(img.data + ph + 12, data_va);
            wr32(img.data + ph + 16, data_sz);
            wr32(img.data + ph + 20, data_mem);
            wr32(img.data + ph + 24, 6);
            wr32(img.data + ph + 28, 4);
            ph += 32;
            wr32(img.data + ph + 0, 0x70000001u);
            wr32(img.data + ph + 4, ex_off);
            wr32(img.data + ph + 8, ex_va);
            wr32(img.data + ph + 12, ex_va);
            wr32(img.data + ph + 16, ex_sz);
            wr32(img.data + ph + 20, ex_sz);
            wr32(img.data + ph + 24, 4);
            wr32(img.data + ph + 28, 4);
        }
    }

    buf_zeros(&img, 40);
    for (i = 0; i < nsec_list; i++) {
        OutSec *sc = &g_out[sec_list[i]];
        buf_u32(&img, sec_nm[i]);
        buf_u32(&img, sc->type);
        buf_u32(&img, sc->flags);
        buf_u32(&img, sc->addr);
        buf_u32(&img, sc->type == SHT_NOBITS ? 0 : sec_off[i]);
        buf_u32(&img, sc->size);
        {
            u32 link = 0;
            if (sc->type == SHT_ARM_EXIDX) {
                int q;
                for (q = 0; q < nsec_list; q++)
                    if (sec_list[q] == O_TEXT)
                        link = (u32)q + 1;
            }
            buf_u32(&img, link);
        }
        buf_u32(&img, 0);
        buf_u32(&img, sc->align ? sc->align : 1);
        buf_u32(&img, 0);
    }
    {
        u32 symtab_idx = 1 + (u32)nsec_list + (u32)nrel;
        for (i = 0; i < 2; i++) {
            u32 info = 0;
            int q;
            if (!rel_present[i])
                continue;
            if (i == 1) {
                for (q = 0; q < nsec_list; q++)
                    if (sec_list[q] == O_DATA)
                        info = (u32)q + 1;
            } else {
                for (q = 0; q < nsec_list; q++)
                    if (sec_list[q] == O_TEXT)
                        info = (u32)q + 1;
            }
            buf_u32(&img, nm_rel[i]);
            buf_u32(&img, SHT_REL);
            buf_u32(&img, 0);
            buf_u32(&img, 0);
            buf_u32(&img, rel_off[i]);
            buf_u32(&img, (u32)relb[i].len);
            buf_u32(&img, symtab_idx);
            buf_u32(&img, info);
            buf_u32(&img, 4);
            buf_u32(&img, 8);
        }
        buf_u32(&img, nm_symtab);
        buf_u32(&img, SHT_SYMTAB);
        buf_u32(&img, 0);
        buf_u32(&img, 0);
        buf_u32(&img, symtab_off);
        buf_u32(&img, (u32)nsyms * 16);
        buf_u32(&img, symtab_idx + 1);
        buf_u32(&img, first_global);
        buf_u32(&img, 4);
        buf_u32(&img, 16);
        buf_u32(&img, nm_strtab);
        buf_u32(&img, SHT_STRTAB);
        buf_u32(&img, 0);
        buf_u32(&img, 0);
        buf_u32(&img, strtab_off);
        buf_u32(&img, (u32)strtab.len);
        buf_u32(&img, 0);
        buf_u32(&img, 0);
        buf_u32(&img, 1);
        buf_u32(&img, 0);
        buf_u32(&img, nm_shstrtab);
        buf_u32(&img, SHT_STRTAB);
        buf_u32(&img, 0);
        buf_u32(&img, 0);
        buf_u32(&img, shstrtab_off);
        buf_u32(&img, (u32)shstr.len);
        buf_u32(&img, 0);
        buf_u32(&img, 0);
        buf_u32(&img, 1);
        buf_u32(&img, 0);
    }

    memcpy(img.data, "\177ELF", 4);
    img.data[4] = 1;
    img.data[5] = 1;
    img.data[6] = 1;
    img.data[7] = 0;
    wr16(img.data + 16, ET_EXEC);
    wr16(img.data + 18, EM_ARM);
    wr32(img.data + 20, 1);
    wr32(img.data + 24, entry);
    wr32(img.data + 28, 52);
    wr32(img.data + 32, shoff);
    wr32(img.data + 36, 0x04000210u);
    wr16(img.data + 40, 52);
    wr16(img.data + 42, 32);
    wr16(img.data + 44, 3);
    wr16(img.data + 46, 40);
    wr16(img.data + 48, shnum);
    wr16(img.data + 50, (u16)(1 + nsec_list + nrel + 2));

    if (ac_write_file(path, img.data, img.len) != 0)
        ac_die("cannot write %s", path);

    buf_free(&img);
    buf_free(&strtab);
    buf_free(&shstr);
    buf_free(&relb[0]);
    buf_free(&relb[1]);
    free(sym_name_off);
    free(syms);
}

static int load_archive(const char *name)
{
    Buf b;
    Arch *a;
    int found = 0;
    char path[1024];
    int i;
    if (strchr(name, '/') || strchr(name, '\\')) {
        found = ac_read_file(name, &b) == 0;
        if (found)
            snprintf(path, sizeof(path), "%s", name);
    } else {
        for (i = 0; i < g_libdirs.count && !found; i++) {
            snprintf(path, sizeof(path), "%s/%s", g_libdirs.items[i], name);
            found = ac_read_file(path, &b) == 0;
        }
    }
    if (!found)
        return 0;
    if (b.len < 8 || memcmp(b.data, "!<arch>\n", 8) != 0) {
        buf_free(&b);
        return 0;
    }
    a = ac_calloc(1, sizeof(Arch));
    a->path = ac_strdup(path);
    a->file = b;
    if (g_archs_tail)
        g_archs_tail->next = a;
    else
        g_archs = a;
    g_archs_tail = a;
    return 1;
}

static void usage(void)
{
    fprintf(stderr,
            "acetylene-ld - ARM ELF linker for Symbian OS\n"
            "usage: acetylene-ld -o OUT -L DIR -l LIB [options] objects...\n"
            "  -o FILE            output ELF image\n"
            "  -e SYM             entry symbol (repeatable, first found wins)\n"
            "  -L DIR             library search path\n"
            "  -l NAME            archive (adds .lib when no dot present)\n"
            "  --base ADDR        image base (default 0x0)\n"
            "  --allow-undefined  tolerate unresolved symbols\n"
            "  --map              print memory map\n"
            "  -v                 verbose\n");
}

int main(int argc, char **argv)
{
    int i;
    sv_init(&g_entry_names);
    sv_init(&g_libdirs);
    g_out_path = "a.out";
    sv_push(&g_entry_names, "E32Main");
    sv_push(&g_entry_names, "_Z7E32Mainv");
    sv_push(&g_entry_names, "_E32Startup");
    sv_push(&g_entry_names, "main");
    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        if (strcmp(a, "-o") == 0 && i + 1 < argc) {
            g_out_path = argv[++i];
        } else if ((strcmp(a, "-e") == 0 || strcmp(a, "--entry") == 0) && i + 1 < argc) {
            StrVec tmp;
            sv_init(&tmp);
            sv_push(&tmp, argv[++i]);
            {
                int k;
                for (k = 0; k < g_entry_names.count; k++)
                    sv_push(&tmp, g_entry_names.items[k]);
            }
            sv_free(&g_entry_names);
            g_entry_names = tmp;
        } else if (strcmp(a, "-L") == 0 && i + 1 < argc) {
            sv_push(&g_libdirs, argv[++i]);
        } else if (strncmp(a, "-L", 2) == 0 && a[2]) {
            sv_push(&g_libdirs, a + 2);
        } else if ((strcmp(a, "-l") == 0) && i + 1 < argc) {
            char nm[512];
            snprintf(nm, sizeof(nm), "%s", argv[++i]);
            if (!strchr(nm, '.'))
                strncat(nm, ".lib", sizeof(nm) - strlen(nm) - 1);
            if (!load_archive(nm))
                ac_die("cannot open library %s", nm);
        } else if (strncmp(a, "-l", 2) == 0 && a[2]) {
            char nm[512];
            snprintf(nm, sizeof(nm), "%s", a + 2);
            if (!strchr(nm, '.'))
                strncat(nm, ".lib", sizeof(nm) - strlen(nm) - 1);
            if (!load_archive(nm))
                ac_die("cannot open library %s", nm);
        } else if (strcmp(a, "--base") == 0 && i + 1 < argc) {
            g_base = (u32)strtoul(argv[++i], NULL, 0);
        } else if (strcmp(a, "--allow-undefined") == 0) {
            g_allow_undefined = 1;
        } else if (strcmp(a, "--map") == 0) {
            g_map = 1;
        } else if (strcmp(a, "-v") == 0 || strcmp(a, "--verbose") == 0) {
            g_verbose = 1;
            ac_verbose = 1;
        } else if (strcmp(a, "-h") == 0 || strcmp(a, "--help") == 0) {
            usage();
            return 0;
        } else if (a[0] == '-' && a[1]) {
            ac_die("unknown option %s", a);
        } else {
            if (ac_has_ext(a, ".lib") || ac_has_ext(a, ".a")) {
                if (!load_archive(a))
                    ac_die("cannot open archive %s", a);
            } else {
                Buf b;
                Obj *o;
                if (ac_read_file(a, &b) != 0)
                    ac_die("cannot read %s", a);
                o = obj_parse(a, 0, b.data, b.len);
                buf_free(&b);
                if (!o)
                    ac_die("%s: not an ELF ARM object", a);
                obj_append(o);
                obj_add_symbols(o);
            }
        }
    }
    if (!g_objs && !g_archs) {
        usage();
        return 1;
    }
    {
        int k;
        for (k = 0; k < g_entry_names.count; k++) {
            GSym *g = gsym_get(g_entry_names.items[k]);
            if (g->defined || g->is_common)
                break;
            g->weak = 0;
            resolve_archives();
            if (!g->defined && !g->is_common)
                g->weak = 1;
            else
                break;
        }
    }
    resolve_archives();
    report_undefined();
    layout();
    fill_sections();
    finalize_globals();
    define_markers();
    apply_relocs();
    if (g_map) {
        ac_info("text   %08x-%08x", g_out[O_TEXT].addr, g_out[O_TEXT].addr + g_out[O_TEXT].size);
        ac_info("rodata %08x-%08x", g_out[O_RODATA].addr, g_out[O_RODATA].addr + g_out[O_RODATA].size);
        ac_info("data   %08x-%08x", g_out[O_DATA].addr, g_out[O_DATA].addr + g_out[O_DATA].size);
        ac_info("bss    %08x-%08x", g_out[O_BSS].addr, g_out[O_BSS].addr + g_out[O_BSS].size);
    }
    emit(g_out_path);
    return 0;
}
