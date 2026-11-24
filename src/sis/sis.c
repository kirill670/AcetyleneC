#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../common/ac.h"

typedef struct {
    char name[128];
    u32 uid;
    int major, minor, build;
    int has_uid;
    StrVec files;
    StrVec targets;
    StrVec langs;
} Pkg;

static void pkg_parse(const char *path, Pkg *p)
{
    Buf b;
    char *line;
    memset(p, 0, sizeof(*p));
    sv_init(&p->files);
    sv_init(&p->targets);
    sv_init(&p->langs);
    sv_push(&p->langs, "EN");
    if (ac_read_file(path, &b) != 0)
        ac_die("cannot read %s", path);
    buf_put(&b, "", 1);
    line = (char *)b.data;
    while (*line) {
        char *nl = strchr(line, '\n');
        char *s = line;
        if (nl)
            *nl = 0;
        while (*s == ' ' || *s == '\t')
            s++;
        if (s[0] && s[0] != ';' && s[0] != '#') {
            if (s[0] == '"' || s[0] == '\'') {
                char *dash = strstr(s, "\"-\"");
                if (dash) {
                    char src[512];
                    int n = (int)(dash - s - 1);
                    if (n > 500)
                        n = 500;
                    memcpy(src, s + 1, (size_t)n);
                    src[n] = 0;
                    sv_push(&p->files, src);
                    sv_push(&p->targets, dash + 3);
                }
            } else if (s[0] == '(') {
                char *comma = strchr(s, ')');
                if (comma) {
                    *comma = 0;
                    p->uid = (u32)strtoul(s + 1, NULL, 0);
                    p->has_uid = 1;
                }
            } else if (strncmp(s, "Languages", 9) == 0) {
                char *eq = strchr(s, '=');
                if (eq) {
                    sv_free(&p->langs);
                    sv_init(&p->langs);
                    {
                        char *tok = eq + 1;
                        while (*tok) {
                            char lang[8];
                            int n = 0;
                            while (*tok == ' ')
                                tok++;
                            while (*tok && *tok != ',' && *tok != ' ' && n < 7)
                                lang[n++] = *tok++;
                            lang[n] = 0;
                            if (n)
                                sv_push(&p->langs, lang);
                            if (*tok == ',')
                                tok++;
                            else
                                break;
                        }
                    }
                }
            } else if (s[0] != '(' && strchr(s, '{')) {
                char *name = strchr(s, '"');
                char *end = name ? strchr(name + 1, '"') : NULL;
                char *comma = NULL;
                if (name && end) {
                    int n = (int)(end - name - 1);
                    if (n > 120)
                        n = 120;
                    memcpy(p->name, name + 1, (size_t)n);
                    p->name[n] = 0;
                    comma = strchr(end, ',');
                }
                if (comma) {
                    comma++;
                    if (comma[0] == '(') {
                        char *close = strchr(comma, ')');
                        if (close) {
                            p->uid = (u32)strtoul(comma + 1, NULL, 0);
                            p->has_uid = 1;
                            comma = close + 1;
                        }
                    }
                    if (*comma == ',') {
                        p->major = atoi(comma + 1);
                        comma = strchr(comma + 1, ',');
                        if (comma) {
                            p->minor = atoi(comma + 1);
                            comma = strchr(comma + 1, ',');
                            if (comma)
                                p->build = atoi(comma + 1);
                        }
                    }
                }
            }
        }
        if (!nl)
            break;
        line = nl + 1;
    }
    buf_free(&b);
}

static int run_tool(const char *exe, const char *args, char *out, size_t outlen)
{
    char cmd[2048];
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    HANDLE rd, wr;
    char buf[2048];
    DWORD got;
    int code = -1;
    snprintf(cmd, sizeof(cmd), "\"%s\" %s", exe, args);
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    CreatePipe(&rd, &wr, &sa, 0);
    SetHandleInformation(rd, HANDLE_FLAG_INHERIT, 0);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = wr;
    si.hStdError = wr;
    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        CloseHandle(rd);
        CloseHandle(wr);
        return -1;
    }
    CloseHandle(wr);
    out[0] = 0;
    for (;;) {
        if (!ReadFile(rd, buf, sizeof(buf) - 1, &got, NULL) || got == 0)
            break;
        buf[got] = 0;
        if (strlen(out) + got < outlen - 1)
            strncat(out, buf, outlen - strlen(out) - 1);
        fputs(buf, stderr);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, (LPDWORD)&code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(rd);
    return code;
}

static void usage(void)
{
    fprintf(stderr,
            "acetylene-sis - Symbian package builder\n"
            "usage: acetylene-sis -pkg FILE [-o OUT.sisx] -sdk PATH [-sign CERT KEY]\n"
            "  -pkg FILE     .pkg script\n"
            "  -o FILE       output package (default: derived from pkg)\n"
            "  -sdk PATH     target SDK directory (contains tools/makesis.exe)\n"
            "  -sign CERT KEY  sign the package with signsis using CERT/KEY\n"
            "  -uid UID      override UID3\n"
            "  -v            verbose\n");
}

int main(int argc, char **argv)
{
    const char *pkg_path = NULL;
    const char *out_path = NULL;
    const char *sdk = NULL;
    const char *cert = NULL;
    const char *key = NULL;
    int i;
    Pkg pkg;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-pkg") == 0 && i + 1 < argc)
            pkg_path = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            out_path = argv[++i];
        else if (strcmp(argv[i], "-sdk") == 0 && i + 1 < argc)
            sdk = argv[++i];
        else if (strcmp(argv[i], "-sign") == 0 && i + 2 < argc) {
            cert = argv[++i];
            key = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0)
            ac_verbose = 1;
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage();
            return 0;
        }
    }
    if (!pkg_path) {
        usage();
        return 1;
    }
    pkg_parse(pkg_path, &pkg);
    printf("package: %s  uid: 0x%08x  version %d.%d(%d)\n", pkg.name[0] ? pkg.name : ac_basename(pkg_path),
           pkg.uid, pkg.major, pkg.minor, pkg.build);
    printf("files: %d\n", pkg.files.count);
    for (i = 0; i < pkg.files.count; i++)
        printf("  %s -> %s\n", pkg.files.items[i], i < pkg.targets.count ? pkg.targets.items[i] : "?");
    if (!out_path) {
        static char derived[512];
        snprintf(derived, sizeof(derived), "%s", pkg_path);
        {
            char *dot = strrchr(derived, '.');
            if (dot)
                *dot = 0;
        }
        strncat(derived, ".sis", sizeof(derived) - strlen(derived) - 1);
        out_path = derived;
    }
    if (!sdk) {
        fprintf(stderr, "acetylene-sis: no -sdk given, package not built\n");
        return 1;
    }
    {
        char makesis[1024];
        char args[2048];
        char log[4096];
        int code;
        snprintf(makesis, sizeof(makesis), "%s\\tools\\makesis.exe", sdk);
        if (GetFileAttributesA(makesis) == INVALID_FILE_ATTRIBUTES) {
            fprintf(stderr, "acetylene-sis: %s not found\n", makesis);
            return 1;
        }
        snprintf(args, sizeof(args), "\"%s\" \"%s\"", pkg_path, out_path);
        printf("running %s\n", makesis);
        code = run_tool(makesis, args, log, sizeof(log));
        if (code != 0) {
            fprintf(stderr, "acetylene-sis: makesis failed (%d)\n", code);
            return 1;
        }
        printf("wrote %s\n", out_path);
    }
    if (cert && key) {
        char signsis[1024];
        char args[2048];
        char log[4096];
        char signed_path[1024];
        int code;
        snprintf(signsis, sizeof(signsis), "%s\\tools\\signsis.exe", sdk);
        snprintf(signed_path, sizeof(signed_path), "%s.signed.sisx", out_path);
        snprintf(args, sizeof(args), "\"%s\" \"%s\" \"%s\" \"%s\"", out_path, signed_path, cert, key);
        printf("signing with %s\n", signsis);
        code = run_tool(signsis, args, log, sizeof(log));
        if (code != 0) {
            fprintf(stderr, "acetylene-sis: signsis failed (%d)\n", code);
            return 1;
        }
        printf("signed package: %s\n", signed_path);
    }
    return 0;
}
