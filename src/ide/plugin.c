#include "ide.h"
#include "../../include/ac_plugin.h"
#include <stdarg.h>

typedef struct {
    char id[96];
    char label[128];
    AcCommandFn fn;
} PCommand;

typedef struct {
    char menu[32];
    char label[128];
    char cmd[96];
} PMenuItem;

typedef struct {
    AcCompleteFn fn;
    void *user;
} PCompleter;

typedef struct {
    char ext[16];
    AcPaintFn fn;
    void *user;
} PViewer;

typedef struct {
    int event;
    AcEventFn fn;
    void *user;
} PSub;

typedef struct {
    int line;
    int col;
    int severity;
    char msg[256];
} PDiag;

typedef struct {
    char id[96];
    char name[128];
    char entry[128];
    char dir[512];
    HMODULE h;
    int loaded;
} PPlugin;

static PCommand g_cmds[64];
static int g_ncmds;
static PMenuItem g_menus[64];
static int g_nmenus;
static PCompleter g_comps[8];
static int g_ncomps;
static PViewer g_views[16];
static int g_nviews;
static PSub g_subs[32];
static int g_nsubs;
static PDiag g_diags[128];
static int g_ndiags;
static PPlugin g_plugins[16];
static int g_nplugins;
static char g_plugin_root[512];
static char g_cur_plugin_dir[512];
static char g_cur_plugin_id[96];

int plugins_command_count(void) { return g_ncmds; }
const char *plugins_command_id(int i) { return (i >= 0 && i < g_ncmds) ? g_cmds[i].id : ""; }
const char *plugins_command_label(int i) { return (i >= 0 && i < g_ncmds) ? g_cmds[i].label : ""; }
int plugins_menu_count(void) { return g_nmenus; }
const char *plugins_menu_name(int i) { return (i >= 0 && i < g_nmenus) ? g_menus[i].menu : ""; }
const char *plugins_menu_label(int i) { return (i >= 0 && i < g_nmenus) ? g_menus[i].label : ""; }
const char *plugins_menu_cmd(int i) { return (i >= 0 && i < g_nmenus) ? g_menus[i].cmd : ""; }
int plugins_diag_count(void) { return g_ndiags; }
int plugins_diag_severity(int i) { return (i >= 0 && i < g_ndiags) ? g_diags[i].severity : 0; }
const char *plugins_diag_text(int i) { return (i >= 0 && i < g_ndiags) ? g_diags[i].msg : ""; }
int plugins_diag_line(int i) { return (i >= 0 && i < g_ndiags) ? g_diags[i].line : 0; }

static void plog(const char *fmt, ...)
{
    char path[512];
    char msg[1024];
    char exe[512];
    va_list ap;
    FILE *f;
    int i;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);
    OutputDebugStringA(msg);
    OutputDebugStringA("\n");
    GetModuleFileNameA(NULL, exe, sizeof(exe));
    for (i = (int)strlen(exe); i > 0 && exe[i] != 92 && exe[i] != 47; i--)
        exe[i] = 0;
    snprintf(path, sizeof(path), "%sacetylene-ide.log", exe);
    f = fopen(path, "a");
    if (f) {
        fprintf(f, "%s\n", msg);
        fclose(f);
    }
}

static int host_api_version(void) { return AC_PLUGIN_API_VERSION; }

static const char *host_doc_text(void)
{
    Doc *d = doc_active();
    return d ? (const char *)d->data.data : "";
}

static int host_doc_length(void)
{
    Doc *d = doc_active();
    return d ? (int)d->data.len : 0;
}

static int host_cursor(void)
{
    Doc *d = doc_active();
    return d ? d->caret : 0;
}

static void host_insert(const char *text, int len)
{
    Doc *d = doc_active();
    if (d && text && len > 0)
        doc_insert(d, d->caret, text, len);
}

static void host_replace(int start, int end, const char *text, int len)
{
    Doc *d = doc_active();
    if (!d)
        return;
    if (start < 0)
        start = 0;
    if (end > (int)d->data.len)
        end = (int)d->data.len;
    if (start > end)
        return;
    doc_delete(d, start, end - start);
    if (text && len > 0)
        doc_insert(d, start, text, len);
}

static void host_set_cursor(int pos)
{
    Doc *d = doc_active();
    if (d)
        doc_set_caret(d, pos, 0);
}

static const char *host_doc_path(void)
{
    Doc *d = doc_active();
    return (d && d->path) ? d->path : "";
}

static int host_line_of(int pos)
{
    Doc *d = doc_active();
    return d ? doc_line_of(d, pos) : 0;
}

static int host_line_start(int line)
{
    Doc *d = doc_active();
    return d ? doc_line_start(d, line) : 0;
}

static int host_line_end(int line)
{
    Doc *d = doc_active();
    return d ? doc_line_end(d, line) : 0;
}

static void host_status(const char *msg)
{
    ide_set_status("%s", msg ? msg : "");
}

static void host_output(const char *line)
{
    if (!line)
        return;
    buf_put(&g_ide.build_log, line, strlen(line));
    buf_u8(&g_ide.build_log, 0x0a);
}

static void host_invalidate(void)
{
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

static int host_register_command(const char *id, const char *label, AcCommandFn fn)
{
    if (!id || !fn || g_ncmds >= 64)
        return 0;
    snprintf(g_cmds[g_ncmds].id, sizeof(g_cmds[g_ncmds].id), "%s", id);
    snprintf(g_cmds[g_ncmds].label, sizeof(g_cmds[g_ncmds].label), "%s", label ? label : id);
    g_cmds[g_ncmds].fn = fn;
    g_ncmds++;
    return 1;
}

static void host_menu_add(const char *menu, const char *label, const char *cmd_id)
{
    if (!menu || !label || !cmd_id || g_nmenus >= 64)
        return;
    snprintf(g_menus[g_nmenus].menu, sizeof(g_menus[g_nmenus].menu), "%s", menu);
    snprintf(g_menus[g_nmenus].label, sizeof(g_menus[g_nmenus].label), "%s", label);
    snprintf(g_menus[g_nmenus].cmd, sizeof(g_menus[g_nmenus].cmd), "%s", cmd_id);
    g_nmenus++;
}

static int host_add_diagnostic(int line, int col, int severity, const char *msg)
{
    if (g_ndiags >= 128)
        return 0;
    g_diags[g_ndiags].line = line;
    g_diags[g_ndiags].col = col;
    g_diags[g_ndiags].severity = severity;
    snprintf(g_diags[g_ndiags].msg, sizeof(g_diags[g_ndiags].msg), "%s", msg ? msg : "");
    g_ndiags++;
    return 1;
}

static void host_clear_diagnostics(void)
{
    g_ndiags = 0;
}

static void host_register_completion(AcCompleteFn fn, void *user)
{
    if (fn && g_ncomps < 8) {
        g_comps[g_ncomps].fn = fn;
        g_comps[g_ncomps].user = user;
        g_ncomps++;
    }
}

static void host_register_viewer(const char *ext, AcPaintFn fn, void *user)
{
    if (!ext || !fn || g_nviews >= 16)
        return;
    snprintf(g_views[g_nviews].ext, sizeof(g_views[g_nviews].ext), "%s", ext);
    g_views[g_nviews].fn = fn;
    g_views[g_nviews].user = user;
    g_nviews++;
}

static void host_subscribe(int event, AcEventFn fn, void *user)
{
    if (!fn || g_nsubs >= 32)
        return;
    g_subs[g_nsubs].event = event;
    g_subs[g_nsubs].fn = fn;
    g_subs[g_nsubs].user = user;
    g_nsubs++;
}

static const char *host_root_dir(void)
{
    static char root[512];
    char exe[512];
    int i;
    GetModuleFileNameA(NULL, exe, sizeof(exe));
    for (i = (int)strlen(exe); i > 0 && exe[i] != 92 && exe[i] != 47; i--)
        exe[i] = 0;
    snprintf(root, sizeof(root), "%s..\\..", exe);
    return root;
}

static void host_log(const char *line)
{
    if (line)
        plog("plugin: %s", line);
}

static void host_run_command(const char *id)
{
    if (id)
        ide_host_run_named(id);
}

static void host_open_file(const char *path)
{
    if (!path || !path[0])
        return;
    if (ac_has_ext(path, ".acproj"))
        ide_open_project(path);
    else
        ide_open_file(path);
}

static const char *host_plugin_dir(void)
{
    return g_cur_plugin_dir;
}

static AcHostApi g_host_api;

static void host_init_api(void)
{
    g_host_api.api_version = AC_PLUGIN_API_VERSION;
    g_host_api.doc_text = host_doc_text;
    g_host_api.doc_length = host_doc_length;
    g_host_api.cursor_pos = host_cursor;
    g_host_api.insert_text = host_insert;
    g_host_api.replace_range = host_replace;
    g_host_api.set_cursor = host_set_cursor;
    g_host_api.doc_path = host_doc_path;
    g_host_api.doc_line_of = host_line_of;
    g_host_api.line_start = host_line_start;
    g_host_api.line_end = host_line_end;
    g_host_api.status = host_status;
    g_host_api.output = host_output;
    g_host_api.invalidate = host_invalidate;
    g_host_api.register_command = host_register_command;
    g_host_api.menu_add = host_menu_add;
    g_host_api.add_diagnostic = host_add_diagnostic;
    g_host_api.clear_diagnostics = host_clear_diagnostics;
    g_host_api.register_completion = host_register_completion;
    g_host_api.register_viewer = host_register_viewer;
    g_host_api.subscribe = host_subscribe;
    g_host_api.root_dir = host_root_dir;
    g_host_api.log = host_log;
    g_host_api.plugin_dir = host_plugin_dir;
    g_host_api.run_command = host_run_command;
    g_host_api.open_file = host_open_file;
    (void)host_api_version;
}

static int json_get(const char *text, const char *key, char *out, size_t cap)
{
    char pat[64];
    const char *p;
    snprintf(pat, sizeof(pat), "\"%s\"", key);
    p = strstr(text, pat);
    if (!p)
        return 0;
    p += strlen(pat);
    while (*p == ' ' || *p == '\t' || *p == 10 || *p == 13)
        p++;
    if (*p != ':')
        return 0;
    p++;
    while (*p == ' ' || *p == '\t' || *p == 10 || *p == 13)
        p++;
    if (*p == '"') {
        size_t n = 0;
        p++;
        while (*p && *p != '"' && n < cap - 1)
            out[n++] = *p++;
        out[n] = 0;
        return 1;
    }
    {
        size_t n = 0;
        while (*p && *p != ',' && *p != '}' && *p != 10 && n < cap - 1)
            out[n++] = *p++;
        out[n] = 0;
        return out[0] != 0;
    }
}

static void load_one(const char *dir)
{
    char manifest[600];
    char dll[700];
    Buf b;
    char id[96], name[128], entry[128];
    PPlugin *pl;
    HMODULE h;
    int (*api)(void);
    int (*init_fn)(AcPlugin *);

    snprintf(manifest, sizeof(manifest), "%s/plugin.json", dir);
    if (ac_read_file(manifest, &b) != 0)
        return;
    buf_put(&b, "", 1);
    id[0] = name[0] = entry[0] = 0;
    json_get((const char *)b.data, "id", id, sizeof(id));
    json_get((const char *)b.data, "name", name, sizeof(name));
    json_get((const char *)b.data, "entry", entry, sizeof(entry));
    buf_free(&b);
    if (!entry[0]) {
        plog("plugin in %s has no entry in plugin.json", dir);
        return;
    }
    snprintf(dll, sizeof(dll), "%s/%s", dir, entry);
    h = LoadLibraryA(dll);
    if (!h) {
        plog("plugin %s: cannot load %s (error %lu)", dir, dll, GetLastError());
        return;
    }
    api = (int (*)(void))(void *)GetProcAddress(h, "ac_plugin_api");
    init_fn = (int (*)(AcPlugin *))(void *)GetProcAddress(h, "ac_plugin_init");
    if (!api || !init_fn) {
        plog("plugin %s: missing ac_plugin_api/ac_plugin_init", dir);
        FreeLibrary(h);
        return;
    }
    if (api() != AC_PLUGIN_API_VERSION) {
        plog("plugin %s: api version %d, host wants %d", dir, api(), AC_PLUGIN_API_VERSION);
        FreeLibrary(h);
        return;
    }
    if (g_nplugins >= 16) {
        FreeLibrary(h);
        return;
    }
    pl = &g_plugins[g_nplugins];
    snprintf(pl->id, sizeof(pl->id), "%s", id[0] ? id : "unknown");
    snprintf(pl->name, sizeof(pl->name), "%s", name[0] ? name : pl->id);
    snprintf(pl->entry, sizeof(pl->entry), "%s", entry);
    snprintf(pl->dir, sizeof(pl->dir), "%s", dir);
    pl->h = h;
    snprintf(g_cur_plugin_dir, sizeof(g_cur_plugin_dir), "%s", dir);
    snprintf(g_cur_plugin_id, sizeof(g_cur_plugin_id), "%s", pl->id);
    {
        AcPlugin self;
        self.host = &g_host_api;
        self.plugin_id = pl->id;
        self.plugin_dir = pl->dir;
        if (!init_fn(&self)) {
            plog("plugin %s: init refused", pl->id);
            FreeLibrary(h);
            return;
        }
    }
    pl->loaded = 1;
    g_nplugins++;
    plog("plugin loaded: %s (%s)", pl->name, pl->id);
}

void plugins_load(void)
{
    char base[600];
    char pattern[700];
    WIN32_FIND_DATAA fd;
    HANDLE h;
    char exe[512];
    int i;

    host_init_api();
    GetModuleFileNameA(NULL, exe, sizeof(exe));
    for (i = (int)strlen(exe); i > 0 && exe[i] != 92 && exe[i] != 47; i--)
        exe[i] = 0;
    snprintf(g_plugin_root, sizeof(g_plugin_root), "%s..\\..\\plugins", exe);
    snprintf(base, sizeof(base), "%s", g_plugin_root);
    snprintf(pattern, sizeof(pattern), "%s\\*", base);
    h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        plog("no plugins directory at %s", base);
        return;
    }
    do {
        char dir[700];
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            continue;
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
            continue;
        snprintf(dir, sizeof(dir), "%s\\%s", base, fd.cFileName);
        load_one(dir);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
    plog("plugins loaded: %d", g_nplugins);
}

int plugins_command_find(const char *cmd)
{
    int i;
    if (!cmd || !cmd[0])
        return -1;
    for (i = 0; i < g_ncmds; i++)
        if (strcmp(g_cmds[i].id, cmd) == 0)
            return i;
    return -1;
}

void plugins_exec_index(int i)
{
    if (i >= 0 && i < g_ncmds && g_cmds[i].fn)
        g_cmds[i].fn();
}

void plugins_fire(int event, const char *arg)
{
    int i;
    for (i = 0; i < g_nsubs; i++)
        if (g_subs[i].event == event && g_subs[i].fn)
            g_subs[i].fn(event, arg ? arg : "", g_subs[i].user);
}

void plugins_doc_changed(void)
{
    if (g_nsubs)
        plugins_fire(AC_EV_DOC_CHANGED, host_doc_path());
}

int plugins_complete(const char *prefix, char *out, int cap)
{
    int i;
    int total = 0;
    if (!prefix || !prefix[0])
        return 0;
    out[0] = 0;
    for (i = 0; i < g_ncomps; i++) {
        int n = g_comps[i].fn(prefix, out, cap, g_comps[i].user);
        if (n > 0)
            total += n;
    }
    return total;
}

void *plugins_viewer_for(const char *path, void **user)
{
    int i;
    const char *dot;
    if (!path)
        return NULL;
    dot = strrchr(path, '.');
    if (!dot)
        return NULL;
    for (i = 0; i < g_nviews; i++) {
        if (_stricmp(dot, g_views[i].ext) == 0) {
            if (user)
                *user = g_views[i].user;
            return (void *)g_views[i].fn;
        }
    }
    return NULL;
}

