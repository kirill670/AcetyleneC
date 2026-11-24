#include "../include/ac_plugin.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char id[96];
    char label[128];
    AcCommandFn fn;
} TCommand;

typedef struct {
    char menu[32];
    char label[128];
    char cmd[96];
} TMenu;

typedef struct {
    int sev;
    int line;
    int col;
    char text[256];
} TDiag;

typedef struct {
    AcCompleteFn fn;
    void *user;
} TComp;

typedef struct {
    char ext[16];
    AcPaintFn fn;
    void *user;
} TView;

typedef struct {
    int event;
    AcEventFn fn;
    void *user;
} TSub;

static char g_text[65536];
static int g_len;
static int g_caret;
static char g_path[512];
static char g_pdir[512];

static TCommand g_cmds[64];
static int g_ncmds;
static TMenu g_menus[64];
static int g_nmenus;
static TDiag g_diags[128];
static int g_ndiags;
static TComp g_comps[8];
static int g_ncomps;
static TView g_views[16];
static int g_nviews;
static TSub g_subs[32];
static int g_nsubs;
static int g_fail;

static void set_text(const char *s)
{
    size_t n = strlen(s);
    if (n >= sizeof(g_text))
        n = sizeof(g_text) - 1;
    memcpy(g_text, s, n);
    g_text[n] = 0;
    g_len = (int)n;
    g_caret = 0;
}

static const char *h_doc_text(void) { return g_text; }
static int h_doc_length(void) { return g_len; }
static int h_cursor(void) { return g_caret; }

static void h_insert(const char *t, int n)
{
    int pos = g_caret;
    if (!t || n <= 0)
        return;
    if (pos < 0)
        pos = 0;
    if (pos > g_len)
        pos = g_len;
    if (pos + n >= (int)sizeof(g_text))
        n = (int)sizeof(g_text) - pos - 1;
    memmove(g_text + pos + n, g_text + pos, (size_t)(g_len - pos));
    memcpy(g_text + pos, t, (size_t)n);
    g_len += n;
    g_text[g_len] = 0;
    g_caret = pos + n;
}

static void h_replace(int start, int end, const char *t, int n)
{
    if (start < 0)
        start = 0;
    if (end > g_len)
        end = g_len;
    if (start > end)
        return;
    g_caret = start;
    memmove(g_text + start, g_text + end, (size_t)(g_len - end));
    g_len -= end - start;
    g_text[g_len] = 0;
    h_insert(t, n);
}

static void h_cursor_set(int pos)
{
    if (pos < 0)
        pos = 0;
    if (pos > g_len)
        pos = g_len;
    g_caret = pos;
}

static const char *h_path(void) { return g_path; }

static int h_line_of(int pos)
{
    int i, line = 0;
    for (i = 0; i < pos && i < g_len; i++)
        if (g_text[i] == 10)
            line++;
    return line;
}

static int h_line_start(int line)
{
    int i, l = 0, last = 0;
    for (i = 0; i < g_len; i++) {
        if (l == line)
            return last;
        if (g_text[i] == 10) {
            l++;
            last = i + 1;
        }
    }
    return last;
}

static int h_line_end(int line)
{
    int i = h_line_start(line);
    while (i < g_len && g_text[i] != 10)
        i++;
    return i;
}

static void h_status(const char *m) { printf("status: %s\n", m ? m : ""); fflush(stdout); }

static void h_output(const char *m) { printf("output: %s\n", m ? m : ""); fflush(stdout); }
static void h_invalidate(void) {}

static int h_register_command(const char *id, const char *label, AcCommandFn fn)
{
    if (g_ncmds >= 64 || !id || !fn)
        return 0;
    snprintf(g_cmds[g_ncmds].id, sizeof(g_cmds[g_ncmds].id), "%s", id);
    snprintf(g_cmds[g_ncmds].label, sizeof(g_cmds[g_ncmds].label), "%s", label ? label : id);
    g_cmds[g_ncmds].fn = fn;
    g_ncmds++;
    return 1;
}

static void h_menu_add(const char *menu, const char *label, const char *cmd)
{
    if (g_nmenus >= 64 || !menu || !label || !cmd)
        return;
    snprintf(g_menus[g_nmenus].menu, sizeof(g_menus[g_nmenus].menu), "%s", menu);
    snprintf(g_menus[g_nmenus].label, sizeof(g_menus[g_nmenus].label), "%s", label);
    snprintf(g_menus[g_nmenus].cmd, sizeof(g_menus[g_nmenus].cmd), "%s", cmd);
    g_nmenus++;
}

static int h_add_diagnostic(int line, int col, int sev, const char *msg)
{
    if (g_ndiags >= 128)
        return 0;
    g_diags[g_ndiags].line = line;
    g_diags[g_ndiags].col = col;
    g_diags[g_ndiags].sev = sev;
    snprintf(g_diags[g_ndiags].text, sizeof(g_diags[g_ndiags].text), "%s", msg ? msg : "");
    g_ndiags++;
    return 1;
}

static void h_clear_diagnostics(void) { g_ndiags = 0; }

static void h_register_completion(AcCompleteFn fn, void *user)
{
    if (!fn || g_ncomps >= 8)
        return;
    g_comps[g_ncomps].fn = fn;
    g_comps[g_ncomps].user = user;
    g_ncomps++;
}

static void h_register_viewer(const char *ext, AcPaintFn fn, void *user)
{
    if (!ext || !fn || g_nviews >= 16)
        return;
    snprintf(g_views[g_nviews].ext, sizeof(g_views[g_nviews].ext), "%s", ext);
    g_views[g_nviews].fn = fn;
    g_views[g_nviews].user = user;
    g_nviews++;
}

static void h_subscribe(int ev, AcEventFn fn, void *user)
{
    if (!fn || g_nsubs >= 32)
        return;
    g_subs[g_nsubs].event = ev;
    g_subs[g_nsubs].fn = fn;
    g_subs[g_nsubs].user = user;
    g_nsubs++;
}

static const char *h_root(void) { return "."; }
static void h_log(const char *m) { printf("log: %s\n", m ? m : ""); fflush(stdout); }
static void h_run_command(const char *id) { printf("run-command: %s\n", id ? id : ""); fflush(stdout); }
static void h_open_file(const char *p) { printf("open-file: %s\n", p ? p : ""); fflush(stdout); }
static const char *h_pdir(void) { return g_pdir; }

static void fire(int ev, const char *arg)
{
    int i;
    for (i = 0; i < g_nsubs; i++)
        if (g_subs[i].event == ev && g_subs[i].fn)
            g_subs[i].fn(ev, arg ? arg : "", g_subs[i].user);
}

static int find_cmd(const char *id)
{
    int i;
    for (i = 0; i < g_ncmds; i++)
        if (strcmp(g_cmds[i].id, id) == 0)
            return i;
    return -1;
}

static int read_entry(const char *dir, char *out, int cap)
{
    char path[700];
    char buf[4096];
    FILE *f;
    size_t n;
    char *p;

    snprintf(path, sizeof(path), "%s/plugin.json", dir);
    f = fopen(path, "rb");
    if (!f)
        return 0;
    n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[n] = 0;
    p = strstr(buf, "\"entry\"");
    if (!p)
        return 0;
    p += 7;
    while (*p && *p != ':')
        p++;
    p++;
    while (*p && *p != '"')
        p++;
    p++;
    n = 0;
    while (*p && *p != '"' && n < (size_t)cap - 1)
        out[n++] = *p++;
    out[n] = 0;
    return n > 0;
}

static void pump_for(int seconds)
{
    DWORD end = GetTickCount() + (DWORD)seconds * 1000;
    printf("pump: %d seconds\n", seconds);
    fflush(stdout);
    while ((long)(end - GetTickCount()) > 0) {
        MSG m;
        while (PeekMessageA(&m, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&m);
            DispatchMessageA(&m);
        }
        MsgWaitForMultipleObjects(0, NULL, FALSE, 50, QS_ALLINPUT);
    }
}

int main(int argc, char **argv)
{
    const char *dir;
    char entry[128];
    char dll[800];
    HMODULE h;
    int (*api)(void);
    int (*init_fn)(AcPlugin *);
    AcHostApi host;
    AcPlugin self;
    int i;
    const char *mode;

    if (argc < 2) {
        printf("usage: plugin-host <plugin-dir> [probe|serve] [seconds]\n");
        return 2;
    }
    dir = argv[1];
    mode = argc > 2 ? argv[2] : "probe";
    snprintf(g_pdir, sizeof(g_pdir), "%s", dir);

    if (!read_entry(dir, entry, sizeof(entry))) {
        printf("FAIL: no entry in %s/plugin.json\n", dir);
        return 1;
    }
    snprintf(dll, sizeof(dll), "%s/%s", dir, entry);
    h = LoadLibraryA(dll);
    if (!h) {
        printf("FAIL: LoadLibrary %s error %lu\n", dll, GetLastError());
        return 1;
    }
    api = (int (*)(void))(void *)GetProcAddress(h, "ac_plugin_api");
    init_fn = (int (*)(AcPlugin *))(void *)GetProcAddress(h, "ac_plugin_init");
    if (!api || !init_fn) {
        printf("FAIL: missing exports in %s\n", dll);
        return 1;
    }
    if (api() != AC_PLUGIN_API_VERSION) {
        printf("FAIL: api version %d, want %d\n", api(), AC_PLUGIN_API_VERSION);
        return 1;
    }

    memset(&host, 0, sizeof(host));
    host.api_version = AC_PLUGIN_API_VERSION;
    host.doc_text = h_doc_text;
    host.doc_length = h_doc_length;
    host.cursor_pos = h_cursor;
    host.insert_text = h_insert;
    host.replace_range = h_replace;
    host.set_cursor = h_cursor_set;
    host.doc_path = h_path;
    host.doc_line_of = h_line_of;
    host.line_start = h_line_start;
    host.line_end = h_line_end;
    host.status = h_status;
    host.output = h_output;
    host.invalidate = h_invalidate;
    host.register_command = h_register_command;
    host.menu_add = h_menu_add;
    host.add_diagnostic = h_add_diagnostic;
    host.clear_diagnostics = h_clear_diagnostics;
    host.register_completion = h_register_completion;
    host.register_viewer = h_register_viewer;
    host.subscribe = h_subscribe;
    host.root_dir = h_root;
    host.log = h_log;
    host.run_command = h_run_command;
    host.open_file = h_open_file;
    host.plugin_dir = h_pdir;

    self.host = &host;
    self.plugin_id = dir;
    self.plugin_dir = dir;

    printf("plugin: %s\n", entry);
    if (!init_fn(&self)) {
        printf("FAIL: ac_plugin_init refused\n");
        return 1;
    }
    printf("commands: %d\n", g_ncmds);
    for (i = 0; i < g_ncmds; i++)
        printf("  cmd %s | %s\n", g_cmds[i].id, g_cmds[i].label);
    printf("menus: %d\n", g_nmenus);
    for (i = 0; i < g_nmenus; i++)
        printf("  menu %s: %s -> %s\n", g_menus[i].menu, g_menus[i].label, g_menus[i].cmd);
    printf("completers: %d viewers: %d subs: %d\n", g_ncomps, g_nviews, g_nsubs);
    printf("diags: %d\n", g_ndiags);
    fflush(stdout);

    if (strcmp(mode, "serve") == 0) {
        int secs = argc > 3 ? atoi(argv[3]) : 5;
        snprintf(g_path, sizeof(g_path), "buffer.c");
        pump_for(secs);
        for (i = 0; i < g_ncmds; i++)
            if (strcmp(g_cmds[i].id, "mcp.status") == 0)
                g_cmds[i].fn();
        printf("DONE\n");
        fflush(stdout);
        return g_fail ? 1 : 0;
    }

    set_text("{\"a\": [1, 2, 3], \"b\": {\"c\": true}}\n");
    snprintf(g_path, sizeof(g_path), "sample.json");
    fire(AC_EV_DOC_OPEN, g_path);
    printf("valid json diags: %d\n", g_ndiags);
    for (i = 0; i < g_ndiags; i++)
        printf("  diag sev=%d line=%d col=%d %s\n", g_diags[i].sev, g_diags[i].line, g_diags[i].col, g_diags[i].text);
    {
        int ok = g_ndiags == 1 && g_diags[0].sev == AC_SEV_INFO;
        if (find_cmd("jsonlint.run") >= 0) {
            if (!ok) {
                printf("FAIL: valid json not accepted\n");
                g_fail = 1;
            }
        }
    }

    set_text("{\"a\": 1,}\n");
    fire(AC_EV_DOC_OPEN, g_path);
    printf("invalid json diags: %d\n", g_ndiags);
    for (i = 0; i < g_ndiags; i++)
        printf("  diag sev=%d line=%d col=%d %s\n", g_diags[i].sev, g_diags[i].line, g_diags[i].col, g_diags[i].text);
    if (find_cmd("jsonlint.run") >= 0 && (g_ndiags != 1 || g_diags[0].sev != AC_SEV_ERROR)) {
        printf("FAIL: invalid json not flagged\n");
        g_fail = 1;
    }

    if (g_ncomps > 0) {
        char out[1024];
        int n = g_comps[0].fn("TIn", out, sizeof(out), g_comps[0].user);
        int hit = 0;
        char *line = out;
        printf("completions for TIn: %d\n", n);
        while (*line) {
            char *nl = strchr(line, 10);
            int len = nl ? (int)(nl - line) : (int)strlen(line);
            printf("  cand %.*s\n", len, line);
            if (len == 6 && memcmp(line, "TInt64", 6) == 0)
                hit = 1;
            if (!nl)
                break;
            line = nl + 1;
        }
        if (!hit) {
            printf("FAIL: TInt64 not suggested\n");
            g_fail = 1;
        }
    }

    if (g_nviews > 0) {
        printf("viewers:");
        for (i = 0; i < g_nviews; i++)
            printf(" %s", g_views[i].ext);
        printf("\n");
    }

    if (g_ndiags > 0)
        h_clear_diagnostics();

    printf("%s\n", g_fail ? "FAIL" : "OK");
    fflush(stdout);
    return g_fail ? 1 : 0;
}
