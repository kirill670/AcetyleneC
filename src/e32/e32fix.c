#include "../common/ac.h"

static int g_ndll_out;

typedef struct {
    u32 site;
    char dll[256];
    u32 ordinal;
} Import;

static u32 crc32_bytes(const u8 *data, size_t len)
{
    u32 c = 0;
    size_t i;
    int k;
    for (i = 0; i < len; i++) {
        c ^= data[i];
        for (k = 0; k < 8; k++)
            c = (c & 1) ? (c >> 1) ^ 0xEDB88320u : c >> 1;
    }
    return c;
}

static void fix_header_crc(u8 *img)
{
    u8 copy[0x9c];
    memcpy(copy, img, 0x9c);
    memset(copy + 0x14, 0, 4);
    wr32(img + 0x14, crc32_bytes(copy, 0x9c) ^ 0x7601236au);
}

static int is_id_char(int ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') ||
           ch == '_' || ch == '$' || ch == '.';
}

static int collect_imports(const char *elf_path, Import *out, int max)
{
    Buf f;
    const u8 *d;
    u32 shoff, es, n, si;
    const u8 *symtab = NULL, *strtab = NULL;
    u32 nsym = 0, strsz = 0;
    u32 i;
    int count = 0;
    if (ac_read_file(elf_path, &f) != 0)
        return -1;
    d = f.data;
    if (f.len < 52 || memcmp(d, "\177ELF", 4) != 0) {
        buf_free(&f);
        return -1;
    }
    shoff = rd32(d + 32);
    es = rd16(d + 46);
    n = rd16(d + 48);
    si = rd16(d + 50);
    for (i = 0; i < n; i++) {
        const u8 *p = d + shoff + i * es;
        if (rd32(p + 4) == 2) {
            u32 link = rd32(p + 24);
            symtab = d + rd32(p + 16);
            nsym = rd32(p + 20) / 16;
            if (link < n) {
                const u8 *sp = d + shoff + link * es;
                strtab = d + rd32(sp + 16);
                strsz = rd32(sp + 20);
            }
            break;
        }
    }
    if (!symtab || !strtab) {
        buf_free(&f);
        return -1;
    }
    for (i = 1; i < n; i++) {
        const u8 *p = d + shoff + i * es;
        u32 type = rd32(p + 4), info = rd32(p + 28), size = rd32(p + 20);
        u32 off = rd32(p + 16);
        u32 k, cnt;
        if (type != 9)
            continue;
        (void)info;
        cnt = size / 8;
        for (k = 0; k < cnt; k++) {
            u32 r_off = rd32(d + off + k * 8);
            u32 r_info = rd32(d + off + k * 8 + 4);
            u32 symi = r_info >> 8;
            const char *nm;
            if (symi >= nsym)
                continue;
            nm = (const char *)strtab + rd32(symtab + symi * 16);
            if (nm[0] != '#' || nm[1] != '<')
                continue;
            if (count < max) {
                const char *p2 = nm;
                char tmp[256];
                int tn = 0;
                u32 ord = 0;
                if (strncmp(p2, "#<DLL>", 6) == 0)
                    p2 += 6;
                while (*p2 && *p2 != '#' && tn < 250)
                    tmp[tn++] = *p2++;
                tmp[tn] = 0;
                if (*p2 == '#') {
                    const char *q = p2 + 1;
                    while (*q && !(*q >= '0' && *q <= '9') && !(*q >= 'a' && *q <= 'f'))
                        q++;
                    ord = (u32)strtoul(q, NULL, 16);
                }
                out[count].site = r_off;
                snprintf(out[count].dll, sizeof(out[count].dll), "%s", tmp);
                out[count].ordinal = ord;
                count++;
            }
        }
    }
    buf_free(&f);
    return count;
}

static void usage(void)
{
    fprintf(stderr,
            "acetylene-e32fix - add the import table to an E32 image produced by elf2e32\n"
            "usage: acetylene-e32fix -elf FILE.elf -in IN.e32 -out OUT.e32\n");
}

int main(int argc, char **argv)
{
    const char *elf = NULL, *in = NULL, *out = NULL;
    Buf eb, fb;
    Import imps[128];
    int nimp, i;
    u8 *img;
    size_t len;
    u32 code_off, imp_off, base;
    Buf sec;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-elf") == 0 && i + 1 < argc)
            elf = argv[++i];
        else if (strcmp(argv[i], "-in") == 0 && i + 1 < argc)
            in = argv[++i];
        else if (strcmp(argv[i], "-out") == 0 && i + 1 < argc)
            out = argv[++i];
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage();
            return 0;
        }
    }
    if (!elf || !in || !out) {
        usage();
        return 1;
    }
    nimp = collect_imports(elf, imps, 128);
    if (nimp < 0) {
        fprintf(stderr, "acetylene-e32fix: cannot read %s\n", elf);
        return 1;
    }
    if (nimp == 0) {
        if (ac_read_file(in, &eb) == 0) {
            ac_write_file(out, eb.data, eb.len);
            buf_free(&eb);
        }
        printf("acetylene-e32fix: no imports, copied image\n");
        return 0;
    }
    if (ac_read_file(in, &fb) != 0) {
        fprintf(stderr, "acetylene-e32fix: cannot read %s\n", in);
        return 1;
    }
    img = ac_alloc(fb.len + 4096);
    memcpy(img, fb.data, fb.len);
    len = fb.len;
    code_off = rd32(img + 0x64);
    imp_off = (u32)len;

    buf_init(&sec);
    {
        char dlls[16][256];
        u32 counts[16];
        int ndll = 0;
        int k, d;
        for (k = 0; k < nimp; k++) {
            int found = -1;
            for (d = 0; d < ndll; d++)
                if (strcmp(dlls[d], imps[k].dll) == 0) {
                    found = d;
                    break;
                }
            if (found < 0 && ndll < 16) {
                snprintf(dlls[ndll], sizeof(dlls[ndll]), "%s", imps[k].dll);
                counts[ndll] = 0;
                found = ndll++;
            }
            if (found >= 0)
                counts[found]++;
        }
        g_ndll_out = ndll;
        for (d = 0; d < ndll; d++) {
            u32 block = (u32)sec.len;
            u32 addr_off, ord_off, name_off, rec_size;
            buf_zeros(&sec, 20);
            addr_off = (u32)sec.len;
            for (k = 0; k < nimp; k++)
                if (strcmp(imps[k].dll, dlls[d]) == 0)
                    buf_u32(&sec, imps[k].site);
            ord_off = (u32)sec.len;
            for (k = 0; k < nimp; k++)
                if (strcmp(imps[k].dll, dlls[d]) == 0)
                    buf_u32(&sec, imps[k].ordinal);
            name_off = (u32)sec.len;
            buf_put(&sec, dlls[d], strlen(dlls[d]) + 1);
            while (sec.len % 4)
                buf_u8(&sec, 0);
            rec_size = (u32)sec.len - block;
            wr32(sec.data + block + 0, rec_size);
            wr32(sec.data + block + 4, name_off - block);
            wr32(sec.data + block + 8, counts[d]);
            wr32(sec.data + block + 12, (imp_off + addr_off) - code_off);
            wr32(sec.data + block + 16, (imp_off + ord_off) - code_off);
        }
        while (sec.len % 4)
            buf_u8(&sec, 0);
        buf_u32(&sec, 0);
    }
    memcpy(img + len, sec.data, sec.len);
    len += sec.len;
    wr32(img + 0x6c, imp_off);
    wr32(img + 0x54, (u32)g_ndll_out);
    fix_header_crc(img);
    if (ac_write_file(out, img, len) != 0) {
        fprintf(stderr, "acetylene-e32fix: cannot write %s\n", out);
        return 1;
    }
    printf("acetylene-e32fix: %d import(s) added, %u bytes\n", nimp, (unsigned)len);
    for (i = 0; i < nimp; i++)
        printf("  %s ordinal 0x%x at code offset 0x%x\n", imps[i].dll, imps[i].ordinal, imps[i].site);
    buf_free(&sec);
    buf_free(&fb);
    free(img);
    return 0;
}
