#include "ide.h"
#include "../../include/ac_plugin.h"
#include "../../include/ac_version.h"
#include <ctype.h>
#include <stdarg.h>

#define TREE_ROWS_TOP 44
#define TREE_ROW_H 20

Ide g_ide;

static void ide_command(int cmd);
static int path_exists(const char *p);
static void path_normalize(const char *in, char *out, int cap);
static void tree_add_file(const char *path);


#define C_BG        RGB(24, 26, 30)
#define C_PANEL     RGB(32, 35, 40)
#define C_PANEL2    RGB(38, 42, 48)
#define C_BORDER    RGB(52, 57, 64)
#define C_TEXT      RGB(216, 220, 226)
#define C_DIM       RGB(140, 148, 158)
#define C_ACCENT    RGB(86, 156, 214)
#define C_SEL       RGB(38, 79, 120)
#define C_CURLINE   RGB(34, 38, 44)
#define C_GUTTER    RGB(28, 31, 36)
#define C_GUTTERTXT RGB(84, 92, 102)
#define C_KEYWORD   RGB(197, 134, 192)
#define C_TYPE      RGB(78, 201, 176)
#define C_STRING    RGB(206, 145, 120)
#define C_COMMENT   RGB(106, 153, 85)
#define C_PREPROC   RGB(155, 155, 110)
#define C_NUMBER    RGB(181, 206, 168)
#define C_FUNC      RGB(220, 220, 170)
#define C_OP        RGB(180, 186, 196)
#define C_ERR       RGB(244, 135, 113)
#define C_WARN      RGB(220, 200, 120)
#define C_OK        RGB(120, 200, 120)
#define C_HOVER     RGB(48, 53, 60)
#define C_SCROLLBAR RGB(44, 48, 55)
#define C_THUMB     RGB(78, 86, 96)
#define C_MATCHHL   RGB(88, 74, 34)

#define GUTTER_PAD_L 8
#define GUTTER_PAD_R 10
#define EDIT_PAD_X   8

static int gutter_width(Doc *d)
{
    int digits = 1;
    int n = d ? d->nlines : 1;
    if (n < 1)
        n = 1;
    while (n >= 10) {
        n /= 10;
        digits++;
    }
    return GUTTER_PAD_L + digits * g_ide.char_w + GUTTER_PAD_R + EDIT_PAD_X;
}

typedef struct {
    const char *label;
    const char *shortcut;
    int cmd;
    int sep;
} MenuItem;

enum {
    CMD_NONE = 0,
    CMD_NEW_PROJECT = 100,
    CMD_OPEN_PROJECT,
    CMD_OPEN_FILE,
    CMD_SAVE,
    CMD_SAVE_AS,
    CMD_CLOSE_TAB,
    CMD_EXIT,
    CMD_UNDO = 200,
    CMD_REDO,
    CMD_CUT,
    CMD_COPY,
    CMD_PASTE,
    CMD_SELECT_ALL,
    CMD_FIND,
    CMD_GOTO,
    CMD_BUILD = 300,
    CMD_REBUILD,
    CMD_PACKAGE,
    CMD_SIGN,
    CMD_RUN,
    CMD_CLEAN,
    CMD_SET_EMU = 350,
    CMD_TOGGLE_OUTPUT = 400,
    CMD_TOGGLE_TREE,
    CMD_SAVE_ALL = 450,
    CMD_DUP_LINE,
    CMD_DEL_LINE,
    CMD_TOGGLE_COMMENT,
    CMD_FIND_NEXT,
    CMD_FIND_PREV,
    CMD_NEW_FILE,
    CMD_ABOUT = 500,
    CMD_LICENSE
};

static const MenuItem k_file[] = {
    {"New File", "Ctrl+N", CMD_NEW_FILE, 0},
    {"New Project", "Ctrl+Shift+N", CMD_NEW_PROJECT, 0},
    {"Open Project...", "Ctrl+Shift+O", CMD_OPEN_PROJECT, 0},
    {"Open File...", "Ctrl+O", CMD_OPEN_FILE, 0},
    {"", "", 0, 1},
    {"Save", "Ctrl+S", CMD_SAVE, 0},
    {"Save As...", "Ctrl+Shift+S", CMD_SAVE_AS, 0},
    {"Save All", "", CMD_SAVE_ALL, 0},
    {"Close Tab", "Ctrl+W", CMD_CLOSE_TAB, 0},
    {"", "", 0, 1},
    {"Exit", "Alt+F4", CMD_EXIT, 0},
};

static const MenuItem k_edit[] = {
    {"Undo", "Ctrl+Z", CMD_UNDO, 0},
    {"Redo", "Ctrl+Y", CMD_REDO, 0},
    {"", "", 0, 1},
    {"Cut", "Ctrl+X", CMD_CUT, 0},
    {"Copy", "Ctrl+C", CMD_COPY, 0},
    {"Paste", "Ctrl+V", CMD_PASTE, 0},
    {"Select All", "Ctrl+A", CMD_SELECT_ALL, 0},
    {"", "", 0, 1},
    {"Find", "Ctrl+F", CMD_FIND, 0},
    {"Find Next", "F3", CMD_FIND_NEXT, 0},
    {"Find Previous", "Shift+F3", CMD_FIND_PREV, 0},
    {"Go to Line", "Ctrl+G", CMD_GOTO, 0},
    {"", "", 0, 1},
    {"Toggle Line Comment", "Ctrl+/", CMD_TOGGLE_COMMENT, 0},
    {"Duplicate Line", "Ctrl+D", CMD_DUP_LINE, 0},
    {"Delete Line", "Ctrl+Shift+K", CMD_DEL_LINE, 0},
};

static const MenuItem k_build[] = {
    {"Build", "F7", CMD_BUILD, 0},
    {"Rebuild All", "Ctrl+F7", CMD_REBUILD, 0},
    {"Clean", "", CMD_CLEAN, 0},
    {"", "", 0, 1},
    {"Package SISX", "Ctrl+P", CMD_PACKAGE, 0},
    {"Sign Package", "F9", CMD_SIGN, 0},
    {"", "", 0, 1},
    {"Set Emulator...", "", CMD_SET_EMU, 0},
    {"", "", 0, 1},
    {"Run", "F5", CMD_RUN, 0},
};

static const MenuItem k_view[] = {
    {"Toggle Output", "Ctrl+`", CMD_TOGGLE_OUTPUT, 0},
    {"Toggle Project Tree", "Ctrl+B", CMD_TOGGLE_TREE, 0},
};

static const MenuItem k_help[] = {
    {"About AcetyleneC", "", CMD_ABOUT, 0},
    {"License", "", CMD_LICENSE, 0},
};

typedef struct {
    const char *title;
    const MenuItem *items;
    int count;
} MenuDef;

static const MenuItem k_none_items[] = {{"", "", 0, 1}};

static const MenuDef k_menus[] = {
    {"File", k_file, (int)(sizeof(k_file) / sizeof(k_file[0]))},
    {"Edit", k_edit, (int)(sizeof(k_edit) / sizeof(k_edit[0]))},
    {"Build", k_build, (int)(sizeof(k_build) / sizeof(k_build[0]))},
    {"View", k_view, (int)(sizeof(k_view) / sizeof(k_view[0]))},
    {"Help", k_help, (int)(sizeof(k_help) / sizeof(k_help[0]))},
    {"Plugins", k_none_items, 0},
};
static const int k_nmenus = (int)(sizeof(k_menus) / sizeof(k_menus[0]));

static HFONT mkfont(const char *face, int height, int weight)
{
    LOGFONTA lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight = -height;
    lf.lfWeight = weight;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfQuality = CLEARTYPE_QUALITY;
    strncpy(lf.lfFaceName, face, LF_FACESIZE - 1);
    return CreateFontIndirectA(&lf);
}

static void fill(HDC dc, RECT r, COLORREF c)
{
    HBRUSH b = CreateSolidBrush(c);
    FillRect(dc, &r, b);
    DeleteObject(b);
}

static void frame(HDC dc, RECT r, COLORREF c)
{
    HPEN p = CreatePen(PS_SOLID, 1, c);
    HGDIOBJ old = SelectObject(dc, p);
    HGDIOBJ oldb = SelectObject(dc, GetStockObject(NULL_BRUSH));
    Rectangle(dc, r.left, r.top, r.right, r.bottom);
    SelectObject(dc, old);
    SelectObject(dc, oldb);
    DeleteObject(p);
}

static int utf8_to_w(const char *s, int len, wchar_t *out, int max);

static void text_at(HDC dc, int x, int y, const char *s, COLORREF c, HFONT f)
{
    static wchar_t w[8192];
    HFONT old;
    int n;
    if (!s || !s[0])
        return;
    n = utf8_to_w(s, (int)strlen(s), w, (int)(sizeof(w) / sizeof(w[0])));
    if (n <= 0)
        return;
    old = SelectObject(dc, f);
    SetTextColor(dc, c);
    SetBkMode(dc, TRANSPARENT);
    TextOutW(dc, x, y, w, n);
    SelectObject(dc, old);
}

static int text_w(HDC dc, const char *s, HFONT f)
{
    static wchar_t w[8192];
    SIZE sz;
    HFONT old;
    int n;
    if (!s || !s[0])
        return 0;
    n = utf8_to_w(s, (int)strlen(s), w, (int)(sizeof(w) / sizeof(w[0])));
    if (n <= 0)
        return 0;
    old = SelectObject(dc, f);
    GetTextExtentPoint32W(dc, w, n, &sz);
    SelectObject(dc, old);
    return sz.cx;
}

static int utf8_to_w(const char *s, int len, wchar_t *out, int max)
{
    return MultiByteToWideChar(CP_UTF8, 0, s, len, out, max);
}

Doc *doc_active(void)
{
    if (g_ide.active < 0 || g_ide.active >= g_ide.ndocs)
        return NULL;
    return &g_ide.docs[g_ide.active];
}

void ide_set_status(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(g_ide.status, sizeof(g_ide.status), fmt, ap);
    va_end(ap);
    g_ide.status_msg_timer = 200;
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

void ide_init(HWND hwnd)
{
    memset(&g_ide, 0, sizeof(g_ide));
    g_ide.hwnd = hwnd;
    g_ide.active = -1;
    g_ide.split_x = 220;
    g_ide.split_y = 0;
    g_ide.show_output = 1;
    g_ide.menu_index = -1;
    g_ide.selected_msg = -1;
    g_ide.font = mkfont("Consolas", 15, FW_NORMAL);
    g_ide.font_ui = mkfont("Segoe UI", 13, FW_NORMAL);
    g_ide.font_bold = mkfont("Segoe UI", 13, FW_SEMIBOLD);
    {
        HDC dc = GetDC(hwnd);
        HFONT old = SelectObject(dc, g_ide.font);
        SIZE sz;
        GetTextExtentPoint32A(dc, "M", 1, &sz);
        g_ide.char_w = sz.cx ? sz.cx : 8;
        GetTextExtentPoint32A(dc, "Mg", 2, &sz);
        g_ide.line_h = sz.cy + 3;
        SelectObject(dc, old);
        ReleaseDC(hwnd, dc);
    }
    sv_init(&g_ide.proj.sources);
    sv_init(&g_ide.proj.libs);
    sv_init(&g_ide.tree_files);
    buf_init(&g_ide.build_log);
    strcpy(g_ide.proj.name, "untitled");
    strcpy(g_ide.proj.target, "s60v30");
    strcpy(g_ide.proj.uid3, "0xE0000001");
    strcpy(g_ide.proj.caps, "None");
    g_ide.proj.heap = 0x10000;
    g_ide.proj.stack = 0x8000;
    g_ide.dirty_layout = 1;
    ide_settings_load();
    plugins_load();
    if (strcmp(AC_BUILD_TAG, "dev") != 0)
        ide_set_status("%s ready", AC_BUILD_TAG);
}

void ide_layout(void)
{
    RECT rc;
    int top = 26 + 30;
    int tree_w = 0;
    GetClientRect(g_ide.hwnd, &rc);
    if (g_ide.split_x < 120)
        g_ide.split_x = 120;
    if (g_ide.split_x > rc.right - 300)
        g_ide.split_x = rc.right - 300;
    if (!g_ide.hide_tree)
        tree_w = g_ide.split_x;
    if (g_ide.split_y == 0)
        g_ide.split_y = rc.bottom * 62 / 100;
    if (g_ide.split_y < 120)
        g_ide.split_y = 120;
    if (g_ide.split_y > rc.bottom - 120)
        g_ide.split_y = rc.bottom - 120;
    g_ide.rc_toolbar.left = 0;
    g_ide.rc_toolbar.top = 26;
    g_ide.rc_toolbar.right = rc.right;
    g_ide.rc_toolbar.bottom = 26 + 30;
    g_ide.rc_tree.left = 0;
    g_ide.rc_tree.top = top;
    g_ide.rc_tree.right = tree_w;
    g_ide.rc_tree.bottom = g_ide.hide_tree ? top : (rc.bottom - 22);
    g_ide.rc_tabs.left = tree_w + (g_ide.hide_tree ? 0 : 1);
    g_ide.rc_tabs.top = top;
    g_ide.rc_tabs.right = rc.right;
    g_ide.rc_tabs.bottom = top + 26;
    g_ide.rc_editor.left = tree_w + (g_ide.hide_tree ? 0 : 1);
    g_ide.rc_editor.top = top + 26;
    g_ide.rc_editor.right = rc.right;
    g_ide.rc_editor.bottom = g_ide.show_output ? g_ide.split_y : rc.bottom - 22;
    g_ide.rc_output.left = tree_w + (g_ide.hide_tree ? 0 : 1);
    g_ide.rc_output.top = g_ide.show_output ? g_ide.split_y + 1 : rc.bottom - 22;
    g_ide.rc_output.right = rc.right;
    g_ide.rc_output.bottom = rc.bottom - 22;
    g_ide.rc_status.left = 0;
    g_ide.rc_status.top = rc.bottom - 22;
    g_ide.rc_status.right = rc.right;
    g_ide.rc_status.bottom = rc.bottom;
}

static void draw_find_bar(HDC dc);

typedef struct {
    const char *label;
    const char *shortcut;
    int cmd;
    int sep;
} CtxItem;

enum {
    CTX_NONE = 0,
    CTX_TREE = 1,
    CTX_EDITOR,
    CTX_TABS,
    CTX_OUTPUT,
    CTX_FIND
};

static const CtxItem k_ctx_tree[] = {
    {"Open", "Enter", 900, 0},
    {"Open in New Tab", "", 901, 0},
    {"", "", 0, 1},
    {"Save", "Ctrl+S", CMD_SAVE, 0},
    {"", "", 0, 1},
    {"Build Project", "F7", CMD_BUILD, 0},
    {"Package SISX", "Ctrl+P", CMD_PACKAGE, 0},
    {"Sign Package", "F9", CMD_SIGN, 0},
    {"Run", "F5", CMD_RUN, 0},
    {"", "", 0, 1},
    {"Refresh Tree", "", 902, 0},
};

static const CtxItem k_ctx_editor[] = {
    {"Undo", "Ctrl+Z", CMD_UNDO, 0},
    {"Redo", "Ctrl+Y", CMD_REDO, 0},
    {"", "", 0, 1},
    {"Cut", "Ctrl+X", CMD_CUT, 0},
    {"Copy", "Ctrl+C", CMD_COPY, 0},
    {"Paste", "Ctrl+V", CMD_PASTE, 0},
    {"Select All", "Ctrl+A", CMD_SELECT_ALL, 0},
    {"", "", 0, 1},
    {"Find", "Ctrl+F", CMD_FIND, 0},
    {"Go to Line", "Ctrl+G", CMD_GOTO, 0},
    {"", "", 0, 1},
    {"Save", "Ctrl+S", CMD_SAVE, 0},
};

static const CtxItem k_ctx_tabs[] = {
    {"Save", "Ctrl+S", CMD_SAVE, 0},
    {"Close", "Ctrl+W", CMD_CLOSE_TAB, 0},
    {"Close Others", "", 903, 0},
    {"", "", 0, 1},
    {"Save All", "", 904, 0},
};

static const CtxItem k_ctx_output[] = {
    {"Copy Selected Line", "Ctrl+C", 905, 0},
    {"Copy Whole Log", "", 906, 0},
    {"Clear Output", "", 907, 0},
};

static const CtxItem k_ctx_find[] = {
    {"Cut", "Ctrl+X", 908, 0},
    {"Copy", "Ctrl+C", 909, 0},
    {"Paste", "Ctrl+V", 910, 0},
    {"Select All", "Ctrl+A", 911, 0},
    {"", "", 0, 1},
    {"Close", "Esc", 912, 0},
};

static int g_ctx_kind;
static int g_ctx_x, g_ctx_y;
static int g_ctx_hover;
static const CtxItem *g_ctx_items;
static int g_ctx_count;

static void panel_draw(HDC dc, int px, int py, const CtxItem *items, int count, int hover)
{
    int k;
    int wmax = 140;
    int height = 8;
    for (k = 0; k < count; k++) {
        int ww;
        if (items[k].sep) {
            height += 8;
            continue;
        }
        ww = text_w(dc, items[k].label, g_ide.font_ui) + text_w(dc, items[k].shortcut, g_ide.font_ui) + 48;
        if (ww > wmax)
            wmax = ww;
        height += 24;
    }
    {
        RECT r = {px, py, px + wmax, py + height};
        fill(dc, r, C_PANEL2);
        frame(dc, r, C_BORDER);
    }
    {
        int y = py + 4;
        int ty = (24 - 15) / 2;
        for (k = 0; k < count; k++) {
            const CtxItem *it = &items[k];
            if (it->sep) {
                fill(dc, (RECT){px + 8, y + 4, px + wmax - 8, y + 5}, C_BORDER);
                y += 8;
                continue;
            }
            if (k == hover)
                fill(dc, (RECT){px + 2, y, px + wmax - 2, y + 24}, C_SEL);
            text_at(dc, px + 14, y + ty, it->label, C_TEXT, g_ide.font_ui);
            if (it->shortcut[0])
                text_at(dc, px + wmax - text_w(dc, it->shortcut, g_ide.font_ui) - 12, y + ty,
                        it->shortcut, C_DIM, g_ide.font_ui);
            y += 24;
        }
    }
}

static int panel_hit(int x, int y, int px, int py, const CtxItem *items, int count, int *item)
{
    int k;
    int y2 = py + 4;
    int wmax = 140;
    HDC dc = GetDC(g_ide.hwnd);
    for (k = 0; k < count; k++) {
        int ww;
        if (items[k].sep)
            continue;
        ww = text_w(dc, items[k].label, g_ide.font_ui) + text_w(dc, items[k].shortcut, g_ide.font_ui) + 48;
        if (ww > wmax)
            wmax = ww;
    }
    ReleaseDC(g_ide.hwnd, dc);
    for (k = 0; k < count; k++) {
        if (items[k].sep) {
            y2 += 8;
            continue;
        }
        if (x >= px && x < px + wmax && y >= y2 && y < y2 + 24) {
            *item = k;
            return 1;
        }
        y2 += 24;
    }
    return 0;
}

static void ctx_open(int x, int y, const CtxItem *items, int count, int kind)
{
    g_ctx_kind = kind;
    g_ctx_x = x;
    g_ctx_y = y;
    g_ctx_items = items;
    g_ctx_count = count;
    g_ctx_hover = -1;
    g_ide.menu_index = -1;
}

static void ctx_close(void)
{
    g_ctx_kind = CTX_NONE;
    g_ctx_items = NULL;
    g_ctx_count = 0;
}

static void find_cut_cb(int cut)
{
    if (g_ide.find_text[0]) {
        if (OpenClipboard(g_ide.hwnd)) {
            HGLOBAL h;
            EmptyClipboard();
            h = GlobalAlloc(GMEM_MOVEABLE, strlen(g_ide.find_text) + 1);
            if (h) {
                char *p = GlobalLock(h);
                strcpy(p, g_ide.find_text);
                GlobalUnlock(h);
                SetClipboardData(CF_TEXT, h);
            }
            CloseClipboard();
        }
        if (cut)
            g_ide.find_text[0] = 0;
    }
}

static void find_paste_cb(void)
{
    if (OpenClipboard(g_ide.hwnd)) {
        HANDLE h = GetClipboardData(CF_TEXT);
        if (h) {
            char *p = GlobalLock(h);
            if (p) {
                size_t room = sizeof(g_ide.find_text) - strlen(g_ide.find_text) - 1;
                strncat(g_ide.find_text, p, room);
                GlobalUnlock(h);
            }
        }
        CloseClipboard();
    }
}

static void copy_output_line(void)
{
    char line[512];
    int i = g_ide.selected_msg;
    if (i >= 0 && i < g_ide.nmsgs)
        snprintf(line, sizeof(line), "%s", g_ide.msgs[i].message);
    else if (g_ide.build_log.len) {
        const char *p = (const char *)g_ide.build_log.data;
        size_t n = g_ide.build_log.len;
        size_t start = n;
        while (start > 0 && p[start - 1] != '\n')
            start--;
        snprintf(line, sizeof(line), "%.*s", (int)(n - start > 500 ? 500 : n - start), p + start);
    } else {
        return;
    }
    if (OpenClipboard(g_ide.hwnd)) {
        HGLOBAL h;
        EmptyClipboard();
        h = GlobalAlloc(GMEM_MOVEABLE, strlen(line) + 1);
        if (h) {
            char *q = GlobalLock(h);
            strcpy(q, line);
            GlobalUnlock(h);
            SetClipboardData(CF_TEXT, h);
        }
        CloseClipboard();
    }
    ide_set_status("copied: %s", line);
}

static void ctx_execute(int cmd)
{
    Doc *d = doc_active();
    if (cmd <= -1000) {
        plugins_exec_index(-1000 - cmd);
        return;
    }
    switch (cmd) {
    case 900:
        if (g_ide.tree_sel >= 0 && g_ide.tree_sel < g_ide.tree_files.count)
            ide_open_file(g_ide.tree_files.items[g_ide.tree_sel]);
        break;
    case 901:
        if (g_ide.tree_sel >= 0 && g_ide.tree_sel < g_ide.tree_files.count)
            ide_open_file(g_ide.tree_files.items[g_ide.tree_sel]);
        break;
    case 902:
        break;
    case 903:
        if (d) {
            while (g_ide.ndocs > 1) {
                int before = g_ide.ndocs;
                int keep = g_ide.active;
                int victim = (keep == 0) ? 1 : 0;
                ide_close_file(victim);
                if (g_ide.ndocs == before)
                    break;
                g_ide.active = keep - ((victim < keep) ? 1 : 0);
            }
        }
        break;
    case CMD_SAVE_ALL:
    case 904:
        {
            int i;
            int keep = g_ide.active;
            for (i = 0; i < g_ide.ndocs; i++) {
                if (g_ide.docs[i].path && g_ide.docs[i].modified)
                    ide_save_file(i, 0);
            }
            g_ide.active = keep;
            ide_set_status("all saved");
        }
        break;
    case 905:
        copy_output_line();
        break;
    case 906:
        if (g_ide.build_log.len && OpenClipboard(g_ide.hwnd)) {
            HGLOBAL h;
            EmptyClipboard();
            h = GlobalAlloc(GMEM_MOVEABLE, g_ide.build_log.len + 1);
            if (h) {
                char *q = GlobalLock(h);
                memcpy(q, g_ide.build_log.data, g_ide.build_log.len);
                q[g_ide.build_log.len] = 0;
                GlobalUnlock(h);
                SetClipboardData(CF_TEXT, h);
            }
            CloseClipboard();
            ide_set_status("log copied");
        }
        break;
    case 907:
        buf_free(&g_ide.build_log);
        buf_init(&g_ide.build_log);
        g_ide.nmsgs = 0;
        g_ide.selected_msg = -1;
        ide_set_status("output cleared");
        break;
    case 908:
        find_cut_cb(1);
        break;
    case 909:
        find_cut_cb(0);
        break;
    case 910:
        find_paste_cb();
        break;
    case 911:
        break;
    case 912:
        g_ide.find_open = 0;
        break;
    default:
        ide_command(cmd);
        break;
    }
}

static void ctx_show_at(int x, int y)
{
    if (PtInRect(&g_ide.rc_tabs, (POINT){x, y})) {
        ctx_open(x, y, k_ctx_tabs, (int)(sizeof(k_ctx_tabs) / sizeof(k_ctx_tabs[0])), CTX_TABS);
    } else if (g_ide.find_open && PtInRect(&g_ide.rc_editor, (POINT){x, y})) {
        ctx_open(x, y, k_ctx_find, (int)(sizeof(k_ctx_find) / sizeof(k_ctx_find[0])), CTX_FIND);
    } else if (PtInRect(&g_ide.rc_tree, (POINT){x, y})) {
        ctx_open(x, y, k_ctx_tree, (int)(sizeof(k_ctx_tree) / sizeof(k_ctx_tree[0])), CTX_TREE);
    } else if (g_ide.show_output && PtInRect(&g_ide.rc_output, (POINT){x, y})) {
        ctx_open(x, y, k_ctx_output, (int)(sizeof(k_ctx_output) / sizeof(k_ctx_output[0])), CTX_OUTPUT);
    } else if (PtInRect(&g_ide.rc_editor, (POINT){x, y})) {
        Doc *d = doc_active();
        if (d)
            doc_set_caret(d, doc_hit_test(d, x - g_ide.rc_editor.left - gutter_width(d), y - g_ide.rc_editor.top - 2), 0);
        ctx_open(x, y, k_ctx_editor, (int)(sizeof(k_ctx_editor) / sizeof(k_ctx_editor[0])), CTX_EDITOR);
    }
}

static int g_bar_hot = -1;

static void draw_menu_bar(HDC dc, int w)
{
    int x = 8, i;
    fill(dc, (RECT){0, 0, w, 26}, C_PANEL);
    for (i = 0; i < k_nmenus; i++) {
        int tw = text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
        RECT r = {x, 0, x + tw, 26};
        if (g_ide.menu_index == i)
            fill(dc, r, C_SEL);
        else if (g_bar_hot == i)
            fill(dc, r, C_HOVER);
        text_at(dc, x + 10, 5, k_menus[i].title,
                (g_ide.menu_index == i || g_bar_hot == i) ? C_TEXT : C_DIM, g_ide.font_ui);
        x += tw;
    }
    {
        char title[256];
        char tag[64];
        Doc *d = doc_active();
        tag[0] = 0;
        if (strcmp(AC_BUILD_TAG, "dev") != 0) {
            const char *sp = strchr(AC_BUILD_TAG, ' ');
            int n = sp ? (int)(sp - AC_BUILD_TAG) : (int)strlen(AC_BUILD_TAG);
            if (n > (int)sizeof(tag) - 2)
                n = (int)sizeof(tag) - 2;
            tag[0] = ' ';
            memcpy(tag + 1, AC_BUILD_TAG, (size_t)n);
            tag[n + 1] = 0;
        }
        snprintf(title, sizeof(title), "AcetyleneC%s  -  %s%s", tag, d ? d->name : "no file", d && d->modified ? " *" : "");
        text_at(dc, w - text_w(dc, title, g_ide.font_ui) - 14, 5, title, C_DIM, g_ide.font_ui);
    }
    fill(dc, (RECT){0, 25, w, 26}, C_BORDER);
}

static const char *k_tool_btns[] = {"Build", "Rebuild", "Package", "Sign", "Run"};
static const int k_tool_ids[] = {CMD_BUILD, CMD_REBUILD, CMD_PACKAGE, CMD_SIGN, CMD_RUN};
static int g_tool_hot = -1;

static int toolbar_hit(int x, int y)
{
    int bx = 10, i;
    HDC dc;
    if (y < 30 || y > 53)
        return -1;
    dc = GetDC(g_ide.hwnd);
    for (i = 0; i < 5; i++) {
        int tw = text_w(dc, k_tool_btns[i], g_ide.font_ui) + 26;
        if (x >= bx && x < bx + tw) {
            ReleaseDC(g_ide.hwnd, dc);
            return i;
        }
        bx += tw + 7;
    }
    ReleaseDC(g_ide.hwnd, dc);
    return -1;
}

static void draw_toolbar(HDC dc, int w)
{
    int x = 10;
    int i;
    fill(dc, g_ide.rc_toolbar, C_PANEL);
    for (i = 0; i < 5; i++) {
        int tw = text_w(dc, k_tool_btns[i], g_ide.font_ui) + 26;
        RECT r = {x, 30, x + tw, 53};
        COLORREF bg = C_PANEL2;
        if (k_tool_ids[i] == CMD_BUILD)
            bg = RGB(46, 84, 122);
        if (g_tool_hot == i)
            bg = (k_tool_ids[i] == CMD_BUILD) ? RGB(58, 102, 145) : C_HOVER;
        fill(dc, r, bg);
        frame(dc, r, (k_tool_ids[i] == CMD_BUILD) ? RGB(84, 130, 172) : C_BORDER);
        text_at(dc, x + 13, 33, k_tool_btns[i], C_TEXT, g_ide.font_ui);
        x += tw + 7;
    }
    {
        char tgt[128];
        snprintf(tgt, sizeof(tgt), "target: %s", g_ide.proj.target);
        text_at(dc, w - text_w(dc, tgt, g_ide.font_ui) - 14, 33, tgt, C_ACCENT, g_ide.font_ui);
    }
    fill(dc, (RECT){0, 55, w, 56}, C_BORDER);
}

static CtxItem g_menu_items[96];
static int g_menu_count;

static void build_menu(int idx)
{
    const MenuDef *m = &k_menus[idx];
    int n = 0;
    int i;
    for (i = 0; i < m->count && n < 90; i++) {
        g_menu_items[n].label = m->items[i].label;
        g_menu_items[n].shortcut = m->items[i].shortcut;
        g_menu_items[n].cmd = m->items[i].cmd;
        g_menu_items[n].sep = m->items[i].sep;
        n++;
    }
    if (idx == k_nmenus - 1) {
        int c;
        for (c = 0; c < plugins_command_count() && n < 90; c++) {
            g_menu_items[n].label = plugins_command_label(c);
            g_menu_items[n].shortcut = "";
            g_menu_items[n].cmd = -1000 - c;
            g_menu_items[n].sep = 0;
            n++;
        }
    } else {
        int k;
        for (k = 0; k < plugins_menu_count() && n < 90; k++) {
            int ci;
            if (_stricmp(plugins_menu_name(k), m->title) != 0)
                continue;
            ci = plugins_command_find(plugins_menu_cmd(k));
            if (ci < 0)
                continue;
            if (n > 0 && !g_menu_items[n - 1].sep) {
                g_menu_items[n].label = "";
                g_menu_items[n].shortcut = "";
                g_menu_items[n].cmd = 0;
                g_menu_items[n].sep = 1;
                n++;
            }
            g_menu_items[n].label = plugins_menu_label(k);
            g_menu_items[n].shortcut = "";
            g_menu_items[n].cmd = -1000 - ci;
            g_menu_items[n].sep = 0;
            n++;
        }
    }
    g_menu_count = n;
}

static void draw_popup(HDC dc, int w, int h)
{
    int i, k;
    build_menu(g_ide.menu_index);
    int x = 8;
    int px, wmax = 140, y;
    for (i = 0; i < g_ide.menu_index; i++)
        x += text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
    px = x;
    for (k = 0; k < g_menu_count; k++) {
        const CtxItem *it = &g_menu_items[k];
        int ww = text_w(dc, it->label, g_ide.font_ui) + text_w(dc, it->shortcut, g_ide.font_ui) + 48;
        if (it->sep)
            continue;
        if (ww > wmax)
            wmax = ww;
    }
    y = 26;
    {
        int height = 8;
        for (k = 0; k < g_menu_count; k++)
            height += g_menu_items[k].sep ? 8 : 24;
        {
            RECT r = {px, y, px + wmax, y + height};
            fill(dc, r, C_PANEL2);
            frame(dc, r, C_BORDER);
        }
        for (k = 0; k < g_menu_count; k++) {
            const CtxItem *it = &g_menu_items[k];
            if (it->sep) {
                fill(dc, (RECT){px + 8, y + 8, px + wmax - 8, y + 9}, C_BORDER);
                y += 8;
                continue;
            }
            if (g_ide.menu_hover == k)
                fill(dc, (RECT){px + 2, y + 4, px + wmax - 2, y + 28}, C_SEL);
            text_at(dc, px + 14, y + 9, it->label, C_TEXT, g_ide.font_ui);
            if (it->shortcut[0])
                text_at(dc, px + wmax - text_w(dc, it->shortcut, g_ide.font_ui) - 12, y + 9, it->shortcut, C_DIM, g_ide.font_ui);
            y += 24;
        }
    }
    (void)w;
    (void)h;
}

static int g_tree_hot = -1;

static void draw_tree(HDC dc)
{
    RECT r = g_ide.rc_tree;
    int y = r.top + 6;
    int i;
    fill(dc, r, C_PANEL);
    text_at(dc, r.left + 12, y, "PROJECT", C_DIM, g_ide.font_ui);
    y += 18;
    text_at(dc, r.left + 12, y, g_ide.proj.name, C_TEXT, g_ide.font_bold);
    y += 20;
    fill(dc, (RECT){r.left + 8, y, r.right - 8, y + 1}, C_BORDER);
    for (i = g_ide.tree_scroll; i < g_ide.tree_files.count; i++) {
        RECT ir = {r.left + 4, y, r.right - 4, y + 20};
        const char *p = g_ide.tree_files.items[i];
        if (y + 20 > r.bottom)
            break;
        if (i == g_ide.tree_sel)
            fill(dc, ir, C_SEL);
        else if (i == g_tree_hot)
            fill(dc, ir, C_HOVER);
        text_at(dc, r.left + 16, y + 3, ac_basename(p), i == g_ide.tree_sel ? C_TEXT : C_DIM, g_ide.font_ui);
        y += 20;
    }
    fill(dc, (RECT){r.right, r.top, r.right + 1, r.bottom}, C_BORDER);
}

static int g_tab_hot = -1;
static int g_tab_close_hot = -1;

static int tab_rect(HDC dc, int i, RECT *out)
{
    int x = g_ide.rc_tabs.left + 4;
    int k;
    for (k = 0; k < g_ide.ndocs; k++) {
        Doc *d = &g_ide.docs[k];
        char label[300];
        int tw;
        snprintf(label, sizeof(label), "%s%s", d->name, d->modified ? " *" : "");
        tw = text_w(dc, label, g_ide.font_ui) + 34;
        if (k == i) {
            *out = (RECT){x, g_ide.rc_tabs.top + 2, x + tw, g_ide.rc_tabs.bottom - 1};
            return 1;
        }
        x += tw + 2;
    }
    return 0;
}

static void draw_tabs(HDC dc)
{
    int i;
    fill(dc, g_ide.rc_tabs, C_PANEL);
    for (i = 0; i < g_ide.ndocs; i++) {
        Doc *d = &g_ide.docs[i];
        char label[300];
        RECT r;
        if (!tab_rect(dc, i, &r))
            continue;
        snprintf(label, sizeof(label), "%s%s", d->name, d->modified ? " *" : "");
        if (i == g_ide.active) {
            fill(dc, r, C_BG);
            fill(dc, (RECT){r.left, r.top, r.right, r.top + 2}, C_ACCENT);
        } else if (i == g_tab_hot) {
            fill(dc, r, C_HOVER);
        }
        text_at(dc, r.left + 10, r.top + 6, label, i == g_ide.active ? C_TEXT : C_DIM, g_ide.font_ui);
        if (i == g_tab_close_hot)
            fill(dc, (RECT){r.right - 23, r.top + 5, r.right - 7, r.top + 21}, C_SEL);
        text_at(dc, r.right - 18, r.top + 6, "x", i == g_tab_close_hot ? C_TEXT : C_DIM, g_ide.font_ui);
    }
    fill(dc, (RECT){g_ide.rc_tabs.left, g_ide.rc_tabs.bottom - 1, g_ide.rc_tabs.right, g_ide.rc_tabs.bottom}, C_BORDER);
}

static COLORREF tok_color(TokKind k)
{
    switch (k) {
    case TK_KEYWORD: return C_KEYWORD;
    case TK_TYPE: return C_TYPE;
    case TK_STRING: return C_STRING;
    case TK_COMMENT: return C_COMMENT;
    case TK_PREPROC: return C_PREPROC;
    case TK_NUMBER: return C_NUMBER;
    case TK_FUNC: return C_FUNC;
    case TK_OPERATOR: return C_OP;
    default: return C_TEXT;
    }
}

static TokKind span_kind(const Span *spans, int nspans, int offset)
{
    int s;
    for (s = 0; s < nspans; s++) {
        if (offset >= spans[s].start && offset < spans[s].start + spans[s].len)
            return spans[s].kind;
    }
    return TK_PLAIN;
}

static int cols_between(const char *data, int from, int to)
{
    int col = 0;
    int i = from;
    while (i < to) {
        unsigned char c = (unsigned char)data[i];
        if (c == '\t')
            col += TAB_WIDTH - (col % TAB_WIDTH);
        else
            col++;
        i += doc_utf8_len(c);
    }
    return col;
}

static int match_brace(Doc *d, int pos, int *other)
{
    const char *data = (const char *)d->data.data;
    int len = (int)d->data.len;
    int at = -1;
    int dir = 0;
    char open, close;
    if (pos < len && strchr("(){}[]", data[pos]))
        at = pos;
    else if (pos > 0 && pos <= len && strchr("(){}[]", data[pos - 1]))
        at = pos - 1;
    if (at < 0)
        return 0;
    if (strchr("({[", data[at])) {
        dir = 1;
        open = data[at];
    } else {
        dir = -1;
        open = data[at];
    }
    close = (open == '(') ? ')' : (open == '{') ? '}' : (open == '[') ? ']' :
            (open == ')') ? '(' : (open == '}') ? '{' : '[';
    {
        int depth = 0;
        int i = at;
        while (i >= 0 && i < len) {
            char c = data[i];
            if (c == open)
                depth++;
            else if (c == close) {
                depth--;
                if (depth == 0) {
                    *other = i;
                    return 1;
                }
            }
            i += dir;
        }
    }
    return 0;
}

static void highlight_line_range(HDC dc, Doc *d, int line, int a, int b, int x0, int y, COLORREF c)
{
    int start = d->lines[line];
    int end = doc_line_end(d, line);
    int c1, c2;
    if (a < start)
        a = start;
    if (b > end)
        b = end;
    if (a >= b)
        return;
    c1 = cols_between((const char *)d->data.data, start, a);
    c2 = c1 + cols_between((const char *)d->data.data, a, b);
    fill(dc, (RECT){x0 + c1 * g_ide.char_w - d->scroll_x, y,
                    x0 + c2 * g_ide.char_w - d->scroll_x, y + g_ide.line_h}, c);
}

static void draw_editor(HDC dc)
{
    Doc *d = doc_active();
    RECT r = g_ide.rc_editor;
    int gutter = gutter_width(d);
    int x0 = r.left + gutter;
    int y = r.top + 2;
    int i;
    int visible;
    int sel_a = 0, sel_b = 0;
    int has_sel;

    fill(dc, r, C_BG);
    fill(dc, (RECT){r.left, r.top, r.left + gutter - EDIT_PAD_X, r.bottom}, C_GUTTER);
    fill(dc, (RECT){r.left + gutter - EDIT_PAD_X, r.top, r.left + gutter - EDIT_PAD_X + 1, r.bottom}, C_BORDER);
    if (!d) {
        text_at(dc, r.left + 24, r.top + 24, "No file open. Use File > Open File, or create a project.", C_DIM, g_ide.font_ui);
        return;
    }
    {
        void *vuser = NULL;
        AcPaintFn vfn = (AcPaintFn)plugins_viewer_for(d->path, &vuser);
        if (vfn) {
            vfn(dc, r.left + gutter + 2, r.top + 2, r.right - r.left - gutter - 4, r.bottom - r.top - 4, d->path, vuser);
            text_at(dc, r.left + gutter + 8, r.bottom - 20, "image viewer plugin", C_DIM, g_ide.font_ui);
            return;
        }
    }
    if (g_ide.line_h <= 0)
        return;
    visible = (r.bottom - r.top - 4) / g_ide.line_h;
    if (visible < 1)
        visible = 1;
    has_sel = doc_has_selection(d);
    if (has_sel)
        doc_sel_range(d, &sel_a, &sel_b);
    {
        int caret_line = doc_line_of(d, d->caret);
        int cur_y = r.top + 2 + (caret_line - d->top_line) * g_ide.line_h;
        if (caret_line >= d->top_line && caret_line < d->top_line + visible) {
            fill(dc, (RECT){r.left + gutter + 1, cur_y, r.right, cur_y + g_ide.line_h}, C_CURLINE);
        }
    }

    for (i = 0; i < visible; i++) {
        int line = d->top_line + i;
        int start, end, len;
        char ln[16];
        Span spans[512];
        int nspans = 0;
        if (line >= d->nlines)
            break;
        start = d->lines[line];
        end = doc_line_end(d, line);
        len = end - start;
        snprintf(ln, sizeof(ln), "%d", line + 1);
        text_at(dc, r.left + gutter - EDIT_PAD_X - GUTTER_PAD_R - text_w(dc, ln, g_ide.font), y, ln,
                (doc_line_of(d, d->caret) == line) ? C_ACCENT : C_GUTTERTXT, g_ide.font);

        if (has_sel && sel_b > start && sel_a < end)
            highlight_line_range(dc, d, line, sel_a > start ? sel_a : start, sel_b < end ? sel_b : end, x0, y, C_SEL);

        if (g_ide.find_text[0] && !g_ide.find_focus) {
            int nlen = (int)strlen(g_ide.find_text);
            int scan = start;
            while (scan + nlen <= end) {
                int k, ok = 1;
                for (k = 0; k < nlen; k++) {
                    char ca = d->data.data[scan + k];
                    char cb = g_ide.find_text[k];
                    if (ca >= 'A' && ca <= 'Z')
                        ca = (char)(ca - 'A' + 'a');
                    if (cb >= 'A' && cb <= 'Z')
                        cb = (char)(cb - 'A' + 'a');
                    if (ca != cb) {
                        ok = 0;
                        break;
                    }
                }
                if (ok)
                    highlight_line_range(dc, d, line, scan, scan + nlen, x0, y, C_MATCHHL);
                scan++;
            }
        }

        if (len > 0) {
            int cx = x0 - d->scroll_x;
            int col = 0;
            int pos = 0;
            doc_highlight(d, line, spans, 512, &nspans);
            while (pos < len) {
                unsigned char first = (unsigned char)d->data.data[start + pos];
                TokKind kind = span_kind(spans, nspans, pos);
                int run_col = col;
                int nchars = 0;
                char buf[1024];
                int bl = 0;
                if (first == '\t') {
                    col += TAB_WIDTH - (col % TAB_WIDTH);
                    pos++;
                    continue;
                }
                while (pos < len && bl < (int)sizeof(buf) - 5) {
                    unsigned char c = (unsigned char)d->data.data[start + pos];
                    int seq;
                    if (c == '\t' || span_kind(spans, nspans, pos) != kind)
                        break;
                    seq = doc_utf8_len(c);
                    if (pos + seq > len)
                        seq = 1;
                    memcpy(buf + bl, d->data.data + start + pos, (size_t)seq);
                    bl += seq;
                    pos += seq;
                    nchars++;
                }
                if (nchars > 0) {
                    buf[bl] = 0;
                    text_at(dc, cx + run_col * g_ide.char_w, y, buf, tok_color(kind), g_ide.font);
                    col += nchars;
                } else {
                    pos++;
                    col++;
                }
            }
        }
        y += g_ide.line_h;
    }

    if (!doc_has_selection(d)) {
        int at = -1;
        if (d->caret < (int)d->data.len && strchr("(){}[]", d->data.data[d->caret]))
            at = d->caret;
        else if (d->caret > 0 && strchr("(){}[]", d->data.data[d->caret - 1]))
            at = d->caret - 1;
        if (at >= 0) {
            int other = -1;
            if (match_brace(d, d->caret, &other)) {
                int la = doc_line_of(d, at);
                int lb = doc_line_of(d, other);
                if (la >= d->top_line && la < d->top_line + visible) {
                    int yy = r.top + 2 + (la - d->top_line) * g_ide.line_h;
                    highlight_line_range(dc, d, la, at, at + 1, x0, yy, RGB(70, 96, 120));
                }
                if (lb >= d->top_line && lb < d->top_line + visible) {
                    int yy = r.top + 2 + (lb - d->top_line) * g_ide.line_h;
                    highlight_line_range(dc, d, lb, other, other + 1, x0, yy, RGB(70, 96, 120));
                }
            }
        }
    }

    if (g_ide.blink_on) {
        int caret_line = doc_line_of(d, d->caret);
        int cy = r.top + 2 + (caret_line - d->top_line) * g_ide.line_h;
        if (caret_line >= d->top_line && caret_line < d->top_line + visible) {
            int cxp = doc_col_of(d, d->caret) * g_ide.char_w - d->scroll_x + x0;
            if (cxp < r.left + gutter)
                cxp = r.left + gutter;
            fill(dc, (RECT){cxp, cy, cxp + 2, cy + g_ide.line_h}, C_TEXT);
        }
    }
}

static void editor_scrollbar_metrics(Doc *d, int *track_top, int *track_h, int *thumb_top, int *thumb_h)
{
    RECT r = g_ide.rc_editor;
    int total;
    int max;
    *track_top = r.top + 2;
    *track_h = r.bottom - r.top - 4;
    if (*track_h < 20)
        *track_h = 20;
    total = d ? d->nlines : 1;
    if (total < 1)
        total = 1;
    max = total - ((r.bottom - r.top - 4) / (g_ide.line_h ? g_ide.line_h : 16));
    if (max < 1)
        max = 1;
    {
        int vis = (r.bottom - r.top - 4) / (g_ide.line_h ? g_ide.line_h : 16);
        float frac = (float)vis / (float)total;
        int th;
        if (frac > 1.0f)
            frac = 1.0f;
        th = (int)(*track_h * frac);
        if (th < 24)
            th = 24;
        *thumb_h = th;
        *thumb_top = *track_top + (int)((*track_h - th) * ((float)(d ? d->top_line : 0) / (float)max));
    }
}

static void draw_editor_scrollbar(HDC dc)
{
    Doc *d = doc_active();
    RECT r = g_ide.rc_editor;
    int tt, thh, bt, bh;
    RECT track;
    if (!d || g_ide.ndocs <= 0)
        return;
    track = (RECT){r.right - 9, r.top + 2, r.right - 1, r.bottom - 2};
    editor_scrollbar_metrics(d, &tt, &thh, &bt, &bh);
    fill(dc, track, C_SCROLLBAR);
    fill(dc, (RECT){track.left, bt, track.right, bt + bh}, C_THUMB);
}

static void draw_output(HDC dc)
{
    RECT r = g_ide.rc_output;
    int y = r.top + 4;
    int i;
    if (!g_ide.show_output)
        return;
    fill(dc, r, C_PANEL);
    fill(dc, (RECT){r.left, r.top - 1, r.right, r.top}, C_BORDER);
    text_at(dc, r.left + 8, y, "Output", C_DIM, g_ide.font_bold);
    {
        char cnt[64];
        snprintf(cnt, sizeof(cnt), "%d messages", g_ide.nmsgs);
        text_at(dc, r.left + 60, y, cnt, C_DIM, g_ide.font_ui);
    }
    y += 20;
    {
        int dn = plugins_diag_count();
        if (dn > 0) {
            int k;
            for (k = 0; k < dn && y < r.bottom - 18; k++) {
                char line[400];
                snprintf(line, sizeof(line), "line %d: %s", plugins_diag_line(k) + 1, plugins_diag_text(k));
                text_at(dc, r.left + 10, y + 1, line,
                        plugins_diag_severity(k) == 1 ? C_ERR :
                        (plugins_diag_severity(k) == 2 ? C_WARN : C_DIM), g_ide.font_ui);
                y += 18;
            }
            if (dn > 0)
                y += 4;
        }
    }
    if (g_ide.nmsgs > 0) {
        for (i = 0; i < g_ide.nmsgs && y < r.bottom - 18; i++) {
            BuildMsg *m = &g_ide.msgs[i];
            RECT ir = {r.left, y, r.right, y + 18};
            if (i == g_ide.selected_msg)
                fill(dc, ir, C_SEL);
            text_at(dc, r.left + 10, y + 1, m->message, m->is_error ? C_ERR : C_WARN, g_ide.font_ui);
            y += 18;
        }
    } else {
        int line_y = y;
        int total = (int)g_ide.build_log.len;
        int off = g_ide.output_scroll;
        int ls = 0;
        int k;
        for (k = 0; k < off && ls < total; ls++)
            if (g_ide.build_log.data[ls] == '\n')
                k++;
        while (ls < total && line_y < r.bottom - 18) {
            int e = ls;
            while (e < total && g_ide.build_log.data[e] != '\n')
                e++;
            if (e > ls) {
                char buf[512];
                int n = e - ls;
                if (n > 500)
                    n = 500;
                memcpy(buf, g_ide.build_log.data + ls, (size_t)n);
                buf[n] = 0;
                text_at(dc, r.left + 10, line_y + 1, buf, C_DIM, g_ide.font);
            } else {
                text_at(dc, r.left + 10, line_y + 1, "", C_DIM, g_ide.font);
            }
            line_y += 16;
            ls = e + 1;
        }
    }
}

static void draw_status(HDC dc, int w)
{
    RECT r = g_ide.rc_status;
    Doc *d = doc_active();
    char left[512];
    char right[256];
    fill(dc, r, C_PANEL2);
    fill(dc, (RECT){r.left, r.top, r.right, r.top + 1}, C_BORDER);
    if (g_ide.status[0]) {
        snprintf(left, sizeof(left), "%s", g_ide.status);
    } else if (d) {
        snprintf(left, sizeof(left), "%s   line %d, col %d   %s   %d bytes",
                 d->path ? d->path : "untitled", doc_line_of(d, d->caret) + 1, doc_col_of(d, d->caret) + 1,
                 d->modified ? "modified" : "saved", (int)d->data.len);
    } else {
        snprintf(left, sizeof(left), "Ready");
    }
    text_at(dc, 10, r.top + 3, left, C_DIM, g_ide.font_ui);
    snprintf(right, sizeof(right), "%s  |  %s", g_ide.proj.target, g_ide.building ? "building..." : "idle");
    text_at(dc, w - text_w(dc, right, g_ide.font_ui) - 10, r.top + 3, right, C_DIM, g_ide.font_ui);
}

static int g_comp_start;

static void comp_compute_pos(void)
{
    Doc *d = doc_active();
    int line, col;
    if (!d)
        return;
    line = doc_line_of(d, d->caret) - d->top_line;
    col = doc_col_of(d, d->caret);
    g_ide.comp_x = g_ide.rc_editor.left + gutter_width(d) + col * g_ide.char_w - d->scroll_x;
    g_ide.comp_y = g_ide.rc_editor.top + 2 + (line + 1) * g_ide.line_h;
    if (g_ide.comp_y > g_ide.rc_editor.bottom - 40)
        g_ide.comp_y = g_ide.rc_editor.bottom - 40 - 20 * g_ide.comp_count;
}

static void comp_update(void)
{
    Doc *d = doc_active();
    char prefix[64];
    char out[1024];
    int p, s, n;
    int count = 0;
    if (!d)
        return;
    p = d->caret;
    s = p;
    while (s > 0) {
        char ch = d->data.data[s - 1];
        if (isalnum((unsigned char)ch) || ch == '_')
            s--;
        else
            break;
    }
    g_ide.comp_open = 0;
    if (p - s < 2)
        return;
    if (p - s >= (int)sizeof(prefix))
        return;
    memcpy(prefix, d->data.data + s, (size_t)(p - s));
    prefix[p - s] = 0;
    n = plugins_complete(prefix, out, sizeof(out));
    if (n <= 0)
        return;
    g_comp_start = s;
    count = 0;
    {
        char *line = out;
        while (*line && count < 8) {
            char *nl = strchr(line, 10);
            char *cr;
            if (nl)
                *nl = 0;
            cr = strchr(line, 13);
            if (cr)
                *cr = 0;
            if (line[0]) {
                snprintf(g_ide.comp_items[count], 96, "%s", line);
                count++;
            }
            if (!nl)
                break;
            line = nl + 1;
        }
    }
    if (!count)
        return;
    g_ide.comp_count = count;
    g_ide.comp_index = 0;
    g_ide.comp_open = 1;
    comp_compute_pos();
}

static void comp_accept(void)
{
    Doc *d = doc_active();
    if (!d || !g_ide.comp_open)
        return;
    if (g_ide.comp_index < 0 || g_ide.comp_index >= g_ide.comp_count)
        return;
    doc_delete(d, g_comp_start, d->caret - g_comp_start);
    doc_set_caret(d, g_comp_start, 0);
    doc_insert(d, g_comp_start, g_ide.comp_items[g_ide.comp_index], (int)strlen(g_ide.comp_items[g_ide.comp_index]));
    g_ide.comp_open = 0;
}

static void draw_completions(HDC dc)
{
    int i;
    int w = 180;
    int h;
    int x, y;
    if (!g_ide.comp_open || g_ide.comp_count <= 0)
        return;
    for (i = 0; i < g_ide.comp_count; i++) {
        int iw = text_w(dc, g_ide.comp_items[i], g_ide.font) + 20;
        if (iw > w)
            w = iw;
    }
    if (w > 420)
        w = 420;
    x = g_ide.comp_x;
    y = g_ide.comp_y;
    h = g_ide.comp_count * 20 + 6;
    if (x + w > g_ide.rc_editor.right - 12)
        x = g_ide.rc_editor.right - 12 - w;
    if (x < g_ide.rc_editor.left)
        x = g_ide.rc_editor.left;
    {
        RECT box = {x, y, x + w, y + h};
        fill(dc, box, C_PANEL2);
        frame(dc, box, C_ACCENT);
    }
    for (i = 0; i < g_ide.comp_count; i++) {
        RECT row = {x + 2, y + 3 + i * 20, x + w - 2, y + 23 + i * 20};
        if (i == g_ide.comp_index)
            fill(dc, row, C_SEL);
        text_at(dc, x + 10, y + 5 + i * 20, g_ide.comp_items[i], C_TEXT, g_ide.font);
    }
}

void ide_paint(HDC dc, RECT *client)
{
    HDC mem;
    HBITMAP bmp;
    HGDIOBJ old;
    int w = client->right, h = client->bottom;
    mem = CreateCompatibleDC(dc);
    bmp = CreateCompatibleBitmap(dc, w, h);
    old = SelectObject(mem, bmp);

    fill(mem, (RECT){0, 0, w, h}, C_BG);
    draw_menu_bar(mem, w);
    draw_toolbar(mem, w);
    draw_tree(mem);
    draw_tabs(mem);
    draw_editor(mem);
    draw_editor_scrollbar(mem);
    if (g_ide.show_output)
        draw_output(mem);
    draw_find_bar(mem);
    draw_status(mem, w);
    if (g_ide.menu_index >= 0)
        draw_popup(mem, w, h);
    if (g_ctx_kind && g_ctx_items)
        panel_draw(mem, g_ctx_x, g_ctx_y, g_ctx_items, g_ctx_count, g_ctx_hover);
    draw_completions(mem);

    BitBlt(dc, 0, 0, w, h, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteObject(bmp);
    DeleteDC(mem);
}


static int hit_menu(int x, int y)
{
    int px = 8, i;
    if (y < 0 || y > 26)
        return -1;
    for (i = 0; i < k_nmenus; i++) {
        int tw = 20;
        HDC dc = GetDC(g_ide.hwnd);
        tw = text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
        ReleaseDC(g_ide.hwnd, dc);
        if (x >= px && x < px + tw)
            return i;
        px += tw;
    }
    return -1;
}

static int menu_item_hit(int x, int y, int *item)
{
    int i, k;
    build_menu(g_ide.menu_index);
    int px = 8, wmax = 140, py = 26;
    HDC dc;
    if (g_ide.menu_index < 0)
        return 0;
    dc = GetDC(g_ide.hwnd);
    for (i = 0; i < g_ide.menu_index; i++)
        px += text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
    for (k = 0; k < g_menu_count; k++) {
        const CtxItem *it = &g_menu_items[k];
        int ww;
        if (it->sep)
            continue;
        ww = text_w(dc, it->label, g_ide.font_ui) + text_w(dc, it->shortcut, g_ide.font_ui) + 48;
        if (ww > wmax)
            wmax = ww;
    }
    ReleaseDC(g_ide.hwnd, dc);
    for (k = 0; k < g_menu_count; k++) {
        const CtxItem *it = &g_menu_items[k];
        if (it->sep) {
            py += 8;
            continue;
        }
        if (x >= px && x < px + wmax && y >= py + 4 && y < py + 28) {
            *item = k;
            return 1;
        }
        py += 24;
    }
    return 0;
}

static void ide_open_dialog(void)
{
    OPENFILENAMEA ofn;
    char file[512];
    memset(&ofn, 0, sizeof(ofn));
    file[0] = 0;
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_ide.hwnd;
    ofn.lpstrFilter = "All Files\0*.*\0C Sources\0*.c;*.h;*.cpp\0Project\0*.acproj\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (GetOpenFileNameA(&ofn))
        ide_open_file(file);
}

static void ide_save_dialog(int index)
{
    OPENFILENAMEA ofn;
    char file[512];
    Doc *d = &g_ide.docs[index];
    memset(&ofn, 0, sizeof(ofn));
    snprintf(file, sizeof(file), "%s", d->path ? d->path : d->name);
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_ide.hwnd;
    ofn.lpstrFilter = "All Files\0*.*\0C Sources\0*.c;*.h;*.cpp\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.Flags = OFN_OVERWRITEPROMPT;
    if (GetSaveFileNameA(&ofn)) {
        char norm[MAX_PATH];
        path_normalize(file, norm, sizeof(norm));
        free(d->path);
        free(d->name);
        d->path = ac_strdup(norm);
        d->name = ac_strdup(ac_basename(norm));
        tree_add_file(norm);
        if (ac_write_file(d->path, d->data.data, d->data.len) == 0) {
            d->modified = 0;
            d->saved_undo_pos = d->undo_pos;
            plugins_fire(2, d->path);
            ide_set_status("Saved %s (%d bytes)", d->name, (int)d->data.len);
        } else {
            ide_set_status("ERROR: cannot write %s", d->path);
        }
    }
}

static int tree_index_of(const char *path)
{
    int i;
    if (!path)
        return -1;
    for (i = 0; i < g_ide.tree_files.count; i++)
        if (_stricmp(g_ide.tree_files.items[i], path) == 0)
            return i;
    return -1;
}

static void tree_add_file(const char *path)
{
    if (!path || !path[0])
        return;
    if (tree_index_of(path) >= 0)
        return;
    sv_push(&g_ide.tree_files, path);
}

static void tree_ensure_visible(void)
{
    int rows = (g_ide.rc_tree.bottom - g_ide.rc_tree.top - TREE_ROWS_TOP) / 20;
    if (rows < 1)
        rows = 1;
    if (g_ide.tree_sel < g_ide.tree_scroll)
        g_ide.tree_scroll = g_ide.tree_sel;
    else if (g_ide.tree_sel >= g_ide.tree_scroll + rows)
        g_ide.tree_scroll = g_ide.tree_sel - rows + 1;
    if (g_ide.tree_scroll < 0)
        g_ide.tree_scroll = 0;
}

void ide_open_file(const char *path)
{
    int i;
    Buf b;
    Doc *d;
    char norm[MAX_PATH];
    path_normalize(path, norm, sizeof(norm));
    path = norm;
    for (i = 0; i < g_ide.ndocs; i++) {
        if (g_ide.docs[i].path && _stricmp(g_ide.docs[i].path, path) == 0) {
            g_ide.active = i;
            i = tree_index_of(path);
            if (i >= 0)
                g_ide.tree_sel = i;
            tree_ensure_visible();
            return;
        }
    }
    if (g_ide.ndocs >= MAX_DOCS)
        return;
    d = &g_ide.docs[g_ide.ndocs];
    doc_init(d, path);
    if (ac_read_file(path, &b) == 0) {
        buf_put(&d->data, b.data, b.len);
        buf_free(&b);
        doc_reindex(d);
        d->modified = 0;
        d->saved_undo_pos = d->undo_pos;
    }
    d->lex_lang = ac_has_ext(path, ".c") || ac_has_ext(path, ".h") || ac_has_ext(path, ".cpp");
    d->caret = 0;
    d->anchor = 0;
    d->top_line = 0;
    d->scroll_x = 0;
    g_ide.active = g_ide.ndocs;
    g_ide.ndocs++;
    tree_add_file(path);
    i = tree_index_of(path);
    if (i >= 0)
        g_ide.tree_sel = i;
    tree_ensure_visible();
    plugins_fire(1, path);
    ide_set_status("Opened %s", ac_basename(path));
}

void ide_save_file(int index, int save_as)
{
    Doc *d;
    if (index < 0 || index >= g_ide.ndocs)
        return;
    d = &g_ide.docs[index];
    if (!d->path || save_as) {
        ide_save_dialog(index);
        return;
    }
    if (ac_write_file(d->path, d->data.data, d->data.len) == 0) {
        d->modified = 0;
        d->saved_undo_pos = d->undo_pos;
        plugins_fire(2, d->path);
        ide_set_status("Saved %s (%d bytes)", d->name, (int)d->data.len);
    } else {
        ide_set_status("ERROR: cannot write %s", d->path);
    }
}

void ide_close_file(int index)
{
    int i;
    Doc *d;
    if (index < 0 || index >= g_ide.ndocs)
        return;
    d = &g_ide.docs[index];
    if (d->modified) {
        wchar_t wmsg[1024];
        wchar_t wcap[128];
        char msg[900];
        int ans;
        snprintf(msg, sizeof(msg), "%s has unsaved changes.\n\nSave before closing?", d->name ? d->name : "untitled");
        MultiByteToWideChar(CP_UTF8, 0, msg, -1, wmsg, (int)(sizeof(wmsg) / sizeof(wmsg[0])));
        MultiByteToWideChar(CP_UTF8, 0, "Unsaved changes", -1, wcap, (int)(sizeof(wcap) / sizeof(wcap[0])));
        ans = MessageBoxW(g_ide.hwnd, wmsg, wcap, MB_YESNOCANCEL | MB_ICONWARNING);
        if (ans == IDCANCEL)
            return;
        if (ans == IDYES) {
            if (!d->path) {
                ide_save_dialog(index);
                if (index < g_ide.ndocs && g_ide.docs[index].modified)
                    return;
            } else {
                ide_save_file(index, 0);
            }
        }
    }
    doc_free(&g_ide.docs[index]);
    for (i = index; i < g_ide.ndocs - 1; i++)
        g_ide.docs[i] = g_ide.docs[i + 1];
    g_ide.ndocs--;
    if (g_ide.active >= g_ide.ndocs)
        g_ide.active = g_ide.ndocs - 1;
}

void ide_goto_line(int line)
{
    Doc *d = doc_active();
    if (!d)
        return;
    if (line < 1)
        line = 1;
    if (line > d->nlines)
        line = d->nlines;
    doc_set_caret(d, doc_line_start(d, line - 1), 0);
    doc_scroll_to_caret(d);
}

static int find_next_from(Doc *d, int from)
{
    const char *hay = (const char *)d->data.data;
    int hlen = (int)d->data.len;
    int nlen = (int)strlen(g_ide.find_text);
    int i;
    if (nlen <= 0)
        return -1;
    for (i = from; i + nlen <= hlen; i++) {
        int k;
        int ok = 1;
        for (k = 0; k < nlen; k++) {
            char a = hay[i + k];
            char b = g_ide.find_text[k];
            if (a >= 'A' && a <= 'Z')
                a = (char)(a - 'A' + 'a');
            if (b >= 'A' && b <= 'Z')
                b = (char)(b - 'A' + 'a');
            if (a != b) {
                ok = 0;
                break;
            }
        }
        if (ok)
            return i;
    }
    return -1;
}

static int find_prev_from(Doc *d, int from)
{
    const char *hay = (const char *)d->data.data;
    int hlen = (int)d->data.len;
    int nlen = (int)strlen(g_ide.find_text);
    int i;
    if (nlen <= 0)
        return -1;
    if (from > hlen - nlen)
        from = hlen - nlen;
    for (i = from; i >= 0; i--) {
        int k;
        int ok = 1;
        for (k = 0; k < nlen; k++) {
            char a = hay[i + k];
            char b = g_ide.find_text[k];
            if (a >= 'A' && a <= 'Z')
                a = (char)(a - 'A' + 'a');
            if (b >= 'A' && b <= 'Z')
                b = (char)(b - 'A' + 'a');
            if (a != b) {
                ok = 0;
                break;
            }
        }
        if (ok)
            return i;
    }
    return -1;
}

static void find_select(Doc *d, int at)
{
    d->caret = at;
    d->anchor = at + (int)strlen(g_ide.find_text);
    d->sel_active = 1;
    doc_scroll_to_caret(d);
}

static void do_find_dir(int dir)
{
    Doc *d = doc_active();
    int at;
    if (!d || !g_ide.find_text[0])
        return;
    if (dir >= 0) {
        at = find_next_from(d, d->caret + (doc_has_selection(d) ? 1 : 0));
        if (at < 0)
            at = find_next_from(d, 0);
    } else {
        at = find_prev_from(d, d->caret - 1);
        if (at < 0)
            at = find_prev_from(d, (int)d->data.len);
    }
    if (at < 0) {
        ide_set_status("not found: %s", g_ide.find_text);
        return;
    }
    find_select(d, at);
    ide_set_status("found at line %d", doc_line_of(d, at) + 1);
}

static void do_goto(void)
{
    Doc *d = doc_active();
    int line;
    if (!d)
        return;
    line = atoi(g_ide.find_text);
    if (line <= 0) {
        ide_set_status("enter a line number");
        return;
    }
    ide_goto_line(line);
    ide_set_status("line %d", line);
}

static void doc_line_span(Doc *d, int line, int *start, int *end_incl_nl)
{
    int s = doc_line_start(d, line);
    int e;
    if (line + 1 < d->nlines)
        e = d->lines[line + 1];
    else
        e = (int)d->data.len;
    *start = s;
    *end_incl_nl = e;
}

static void op_dup_line(void)
{
    Doc *d = doc_active();
    int line, s, e, len, coff;
    char *tmp;
    if (!d || d->read_only)
        return;
    line = doc_line_of(d, d->caret);
    coff = d->caret - doc_line_start(d, line);
    doc_line_span(d, line, &s, &e);
    len = e - s;
    if (len <= 0)
        return;
    if (e >= (int)d->data.len && d->data.data[e - 1] != '\n') {
        tmp = ac_alloc((size_t)len + 1);
        tmp[0] = '\n';
        memcpy(tmp + 1, d->data.data + s, (size_t)len);
        doc_insert(d, e, tmp, len + 1);
        free(tmp);
    } else {
        tmp = ac_alloc((size_t)len);
        memcpy(tmp, d->data.data + s, (size_t)len);
        doc_insert(d, e, tmp, len);
        free(tmp);
    }
    doc_set_caret(d, doc_line_start(d, line + 1) + coff, 0);
    doc_scroll_to_caret(d);
    ide_set_status("line duplicated");
}

static void op_del_line(void)
{
    Doc *d = doc_active();
    int s, e;
    if (!d || d->read_only)
        return;
    doc_line_span(d, doc_line_of(d, d->caret), &s, &e);
    if (e <= s) {
        if (s > 0) {
            s--;
        } else {
            return;
        }
    }
    if (doc_has_selection(d)) {
        int a, b;
        int la, lb;
        doc_sel_range(d, &a, &b);
        la = doc_line_of(d, a);
        lb = doc_line_of(d, b);
        if (b > a && b == doc_line_start(d, lb) && lb > la)
            lb--;
        doc_line_span(d, la, &s, &e);
        {
            int s2, e2;
            doc_line_span(d, lb, &s2, &e2);
            (void)s2;
            e = e2;
        }
        if (e >= (int)d->data.len && s > 0)
            s--;
    }
    doc_delete(d, s, e - s);
    doc_set_caret(d, s, 0);
    doc_scroll_to_caret(d);
    ide_set_status("line deleted");
}

static void op_toggle_comment(void)
{
    Doc *d = doc_active();
    int la, lb, i;
    int all_commented = 1;
    if (!d || d->read_only)
        return;
    if (!d->lex_lang) {
        ide_set_status("line comments apply to C sources");
        return;
    }
    if (doc_has_selection(d)) {
        int a, b;
        doc_sel_range(d, &a, &b);
        la = doc_line_of(d, a);
        lb = doc_line_of(d, b);
        if (b > a && b == doc_line_start(d, lb) && lb > la)
            lb--;
    } else {
        la = lb = doc_line_of(d, d->caret);
    }
    for (i = la; i <= lb; i++) {
        int s = doc_line_start(d, i);
        int e = doc_line_end(d, i);
        int j = s;
        while (j < e && (d->data.data[j] == ' ' || d->data.data[j] == '\t'))
            j++;
        if (j == e)
            continue;
        if (!(j + 1 < e && d->data.data[j] == '/' && d->data.data[j + 1] == '/')) {
            all_commented = 0;
            break;
        }
    }
    for (i = lb; i >= la; i--) {
        int s = doc_line_start(d, i);
        int e = doc_line_end(d, i);
        int j = s;
        while (j < e && (d->data.data[j] == ' ' || d->data.data[j] == '\t'))
            j++;
        if (j == e)
            continue;
        if (all_commented) {
            if (j + 1 < e && d->data.data[j] == '/' && d->data.data[j + 1] == '/')
                doc_delete(d, j, 2);
        } else {
            doc_insert(d, j, "//", 2);
        }
    }
    ide_set_status(all_commented ? "uncommented" : "commented");
}

static void op_indent(int outdent)
{
    Doc *d = doc_active();
    int la, lb, i;
    if (!d || d->read_only)
        return;
    if (doc_has_selection(d)) {
        int a, b;
        doc_sel_range(d, &a, &b);
        la = doc_line_of(d, a);
        lb = doc_line_of(d, b);
        if (b > a && b == doc_line_start(d, lb) && lb > la)
            lb--;
    } else {
        la = lb = doc_line_of(d, d->caret);
    }
    if (!outdent) {
        for (i = lb; i >= la; i--)
            doc_insert(d, doc_line_start(d, i), "\t", 1);
        ide_set_status("indented %d line(s)", lb - la + 1);
    } else {
        for (i = lb; i >= la; i--) {
            int s = doc_line_start(d, i);
            if (s < (int)d->data.len) {
                if (d->data.data[s] == '\t')
                    doc_delete(d, s, 1);
                else if (d->data.data[s] == ' ')
                    doc_delete(d, s, 1);
            }
        }
        ide_set_status("outdented %d line(s)", lb - la + 1);
    }
}

static void draw_find_bar(HDC dc)
{
    RECT r = g_ide.rc_editor;
    int w = 360;
    int h = 26;
    RECT box;
    char label[64];
    if (!g_ide.find_open)
        return;
    box.left = r.right - w - 12;
    box.top = r.top + 6;
    box.right = r.right - 12;
    box.bottom = box.top + h;
    fill(dc, box, C_PANEL2);
    frame(dc, box, C_ACCENT);
    snprintf(label, sizeof(label), "%s", g_ide.find_focus ? "Go to line:" : "Find:");
    text_at(dc, box.left + 8, box.top + 5, label, C_DIM, g_ide.font_ui);
    {
        int lw = text_w(dc, label, g_ide.font_ui);
        char shown[160];
        char clipped[160];
        int field_w = box.right - (box.left + 8 + lw + 8) - 8;
        int avail;
        int cut = 0;
        snprintf(shown, sizeof(shown), "%s", g_ide.find_text);
        avail = field_w > 8 ? field_w : 8;
        while (shown[cut] && text_w(dc, shown + cut, g_ide.font_ui) > avail)
            cut++;
        snprintf(clipped, sizeof(clipped), "%s", shown + cut);
        fill(dc, (RECT){box.left + 8 + lw + 4, box.top + 3, box.right - 5, box.bottom - 3}, C_BG);
        text_at(dc, box.left + 8 + lw + 8, box.top + 5, clipped, C_TEXT, g_ide.font_ui);
        if (g_ide.blink_on) {
            char pre[160];
            int cw;
            int n = g_ide.find_caret - cut;
            if (n < 0)
                n = 0;
            if (n > (int)strlen(clipped))
                n = (int)strlen(clipped);
            snprintf(pre, sizeof(pre), "%.*s", n, clipped);
            cw = text_w(dc, pre, g_ide.font_ui);
            fill(dc, (RECT){box.left + 8 + lw + 8 + cw, box.top + 6, box.left + 9 + lw + 8 + cw, box.top + 20}, C_TEXT);
        }
    }
}

void ide_find(void)
{
    Doc *d = doc_active();
    g_ide.find_open = 1;
    g_ide.find_focus = 0;
    if (d && doc_has_selection(d)) {
        int a, b;
        doc_sel_range(d, &a, &b);
        if (b - a > 0 && b - a < (int)sizeof(g_ide.find_text) - 1 &&
            memchr(d->data.data + a, '\n', (size_t)(b - a)) == NULL) {
            memcpy(g_ide.find_text, d->data.data + a, (size_t)(b - a));
            g_ide.find_text[b - a] = 0;
        }
    }
    g_ide.find_caret = (int)strlen(g_ide.find_text);
    ide_set_status("type to search, Enter = next, Shift+Enter = prev, Esc = close");
}

int run_capture(const char *cmd, char *log, size_t logcap)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    HANDLE rd, wr;
    char buf[4096];
    DWORD got;
    DWORD code = 1;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&rd, &wr, &sa, 0))
        return 1;
    SetHandleInformation(rd, HANDLE_FLAG_INHERIT, 0);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = wr;
    si.hStdError = wr;
    if (!CreateProcessA(NULL, (char *)cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        CloseHandle(rd);
        CloseHandle(wr);
        return 1;
    }
    CloseHandle(wr);
    for (;;) {
        if (!ReadFile(rd, buf, sizeof(buf) - 1, &got, NULL) || got == 0)
            break;
        buf[got] = 0;
        buf_put(&g_ide.build_log, buf, got);
        if (log && logcap) {
            size_t have = strlen(log);
            if (have + got < logcap - 1)
                strncat(log, buf, logcap - have - 1);
        }
        {
            char *line = buf;
            while (*line) {
                char *nl = strchr(line, '\n');
                if (nl)
                    *nl = 0;
                if ((strstr(line, ": error") || strstr(line, "error:")) && g_ide.nmsgs < 256) {
                    BuildMsg *m = &g_ide.msgs[g_ide.nmsgs++];
                    snprintf(m->message, sizeof(m->message), "%s", line);
                    m->is_error = 1;
                }
                if (!nl)
                    break;
                line = nl + 1;
            }
        }
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(rd);
    return (int)code;
}

void add_msg(const char *fmt, ...)
{
    va_list ap;
    BuildMsg *m;
    if (g_ide.nmsgs >= 256)
        return;
    m = &g_ide.msgs[g_ide.nmsgs++];
    va_start(ap, fmt);
    vsnprintf(m->message, sizeof(m->message), fmt, ap);
    va_end(ap);
    m->is_error = 1;
}

static void run_build_pipeline(void)
{
    Doc *d = doc_active();
    char exe_dir[512];
    char root[512];
    char tcc[768], ld[768], elf2e32[768], cxx[768];
    char build_dir[768];
    char elf_file[768];
    char e32_file[768];
    char objects[4096];
    char cmd[4096];
    int i;
    int code;
    int compiled = 0;

    if (strcmp(g_ide.proj.target, "s60v3") == 0)
        snprintf(g_ide.proj.target, sizeof(g_ide.proj.target), "s60v30");

    if (ide_target_is_legacy(g_ide.proj.target)) {
        run_build_legacy();
        return;
    }

    GetModuleFileNameA(NULL, exe_dir, sizeof(exe_dir));
    for (i = (int)strlen(exe_dir); i > 0 && exe_dir[i] != '\\' && exe_dir[i] != '/'; i--)
        exe_dir[i] = 0;
    snprintf(root, sizeof(root), "%s/../..", exe_dir);
    snprintf(tcc, sizeof(tcc), "%s/acetylene-cc.exe", exe_dir);
    snprintf(ld, sizeof(ld), "%s/acetylene-ld.exe", exe_dir);
    snprintf(cxx, sizeof(cxx), "%s/acetylene-cxx.exe", exe_dir);
    snprintf(elf2e32, sizeof(elf2e32), "%s/sdk/targets/%s/tools/elf2e32.exe", root, g_ide.proj.target);
    snprintf(build_dir, sizeof(build_dir), "%s/build", root);
    CreateDirectoryA(build_dir, NULL);
    snprintf(elf_file, sizeof(elf_file), "%s/%s.elf", build_dir, g_ide.proj.name);
    snprintf(e32_file, sizeof(e32_file), "%s/%s.e32", build_dir, g_ide.proj.name);

    buf_free(&g_ide.build_log);
    buf_init(&g_ide.build_log);
    g_ide.nmsgs = 0;
    g_ide.selected_msg = -1;
    objects[0] = 0;

    if (g_ide.proj.sources.count == 0) {
        if (!d || !d->path) {
            add_msg("open a source file or add source= lines to the .acproj");
            ide_set_status("Build: nothing to compile");
            return;
        }
        compiled = 1;
        {
            char gen_c[768];
            char obj[768];
            const char *base = ac_basename(d->path);
            snprintf(gen_c, sizeof(gen_c), "%s/%s.gen.c", build_dir, g_ide.proj.name);
            snprintf(obj, sizeof(obj), "%s/%.*s.o", build_dir, (int)(strrchr(base, '.') ? (size_t)(strrchr(base, '.') - base) : strlen(base)), base);
            if (ac_has_ext(d->path, ".cpp") || ac_has_ext(d->path, ".cc")) {
                snprintf(cmd, sizeof(cmd), "\"%s\" \"%s\" -o \"%s\"", cxx, d->path, gen_c);
                buf_put(&g_ide.build_log, cmd, strlen(cmd));
                buf_u8(&g_ide.build_log, 10);
                ide_set_status("Translating C++...");
                UpdateWindow(g_ide.hwnd);
                if (run_capture(cmd, NULL, 0) != 0) {
                    add_msg("C++ frontend failed");
                    ide_set_status("C++ FAILED");
                    return;
                }
                snprintf(cmd, sizeof(cmd), "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                         tcc, root, root, gen_c, obj);
            } else {
                snprintf(cmd, sizeof(cmd), "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                         tcc, root, root, d->path, obj);
            }
            buf_put(&g_ide.build_log, cmd, strlen(cmd));
            buf_u8(&g_ide.build_log, 10);
            ide_set_status("Compiling...");
            UpdateWindow(g_ide.hwnd);
            if (run_capture(cmd, NULL, 0) != 0) {
                if (g_ide.nmsgs == 0)
                    add_msg("compiler failed");
                ide_set_status("Compile FAILED");
                return;
            }
            snprintf(objects, sizeof(objects), "\"%s\"", obj);
        }
    } else {
        for (i = 0; i < g_ide.proj.sources.count; i++) {
            const char *src = g_ide.proj.sources.items[i];
            char full[768];
            char gen_c[768];
            char obj[768];
            const char *base;
            char stem[256];
            size_t sl;
            if (src[1] == ':') {
                snprintf(full, sizeof(full), "%s", src);
            } else {
                snprintf(full, sizeof(full), "%s/%s", root, src);
            }
            base = ac_basename(full);
            sl = strlen(base);
            if (strrchr(base, '.'))
                sl = (size_t)(strrchr(base, '.') - base);
            snprintf(stem, sizeof(stem), "%.*s", (int)(sl > 200 ? 200 : sl), base);
            snprintf(obj, sizeof(obj), "%s/%s.o", build_dir, stem);
            if (ac_has_ext(full, ".cpp") || ac_has_ext(full, ".cc")) {
                snprintf(gen_c, sizeof(gen_c), "%s/%s.gen.c", build_dir, stem);
                snprintf(cmd, sizeof(cmd), "\"%s\" \"%s\" -o \"%s\"", cxx, full, gen_c);
                buf_put(&g_ide.build_log, cmd, strlen(cmd));
                buf_u8(&g_ide.build_log, 10);
                if (run_capture(cmd, NULL, 0) != 0) {
                    add_msg("C++ frontend failed for %s", base);
                    ide_set_status("C++ FAILED");
                    return;
                }
                snprintf(cmd, sizeof(cmd), "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                         tcc, root, root, gen_c, obj);
            } else {
                snprintf(cmd, sizeof(cmd), "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                         tcc, root, root, full, obj);
            }
            buf_put(&g_ide.build_log, cmd, strlen(cmd));
            buf_u8(&g_ide.build_log, 10);
            ide_set_status("Compiling %s...", base);
            UpdateWindow(g_ide.hwnd);
            if (run_capture(cmd, NULL, 0) != 0) {
                if (g_ide.nmsgs == 0)
                    add_msg("compiler failed for %s", base);
                ide_set_status("Compile FAILED: %s", base);
                return;
            }
            if (strlen(objects) + strlen(obj) + 4 < sizeof(objects)) {
                if (objects[0])
                    strncat(objects, " ", sizeof(objects) - strlen(objects) - 1);
                strncat(objects, "\"", sizeof(objects) - strlen(objects) - 1);
                strncat(objects, obj, sizeof(objects) - strlen(objects) - 1);
                strncat(objects, "\"", sizeof(objects) - strlen(objects) - 1);
            }
        }
    }
    (void)compiled;

    if (g_ide.proj.is_dll) {
        snprintf(cmd, sizeof(cmd),
                 "\"%s\" -o \"%s\" -L \"%s/sdk/targets/%s/lib\" -e E32Dll %s -lestlib -leuser -ldrtaeabi -lusrt2_2",
                 ld, elf_file, root, g_ide.proj.target, objects);
    } else {
        snprintf(cmd, sizeof(cmd),
                 "\"%s\" -o \"%s\" -L \"%s/sdk/targets/%s/lib\" %s -lecrt0 -lestlib -leuser -ldrtaeabi -lusrt2_2",
                 ld, elf_file, root, g_ide.proj.target, objects);
    }
    buf_put(&g_ide.build_log, cmd, strlen(cmd));
    buf_u8(&g_ide.build_log, 10);
    ide_set_status("Linking...");
    UpdateWindow(g_ide.hwnd);
    code = run_capture(cmd, NULL, 0);
    if (code != 0) {
        add_msg("linker failed with exit code %d (see output)", code);
        ide_set_status("Link FAILED");
        return;
    }

    if (g_ide.proj.is_dll) {
        char def_file[768];
        char dso_file[768];
        char linkas[768];
        snprintf(def_file, sizeof(def_file), "%s/%s.def", build_dir, g_ide.proj.name);
        snprintf(dso_file, sizeof(dso_file), "%s/%s.dso", build_dir, g_ide.proj.name);
        snprintf(linkas, sizeof(linkas), "%s{000a0000}[%s].dll", g_ide.proj.name, g_ide.proj.uid3);
        snprintf(cmd, sizeof(cmd),
                 "\"%s\" --elfinput=\"%s\" --output=\"%s\" --targettype=DLL --uid1=0x10000079 --uid2=0x1000008D "
                 "--uid3=%s --sid=%s --dlldata --uncompressed --defoutput=\"%s\" --dso=\"%s\" --linkas=\"%s\"",
                 elf2e32, elf_file, e32_file, g_ide.proj.uid3, g_ide.proj.uid3, def_file, dso_file, linkas);
    } else {
        snprintf(cmd, sizeof(cmd),
                 "\"%s\" --elfinput=\"%s\" --output=\"%s\" --targettype=EXE --uid1=0x1000007A --uid2=0x100039CE "
                 "--uid3=%s --sid=%s --heap=%d --stack=%d --uncompressed",
                 elf2e32, elf_file, e32_file, g_ide.proj.uid3, g_ide.proj.uid3, g_ide.proj.heap, g_ide.proj.stack);
    }
    buf_put(&g_ide.build_log, cmd, strlen(cmd));
    buf_u8(&g_ide.build_log, 10);
    ide_set_status("Post-linking (elf2e32)...");
    UpdateWindow(g_ide.hwnd);
    code = run_capture(cmd, NULL, 0);
    if (code != 0) {
        add_msg("elf2e32 failed with exit code %d (see output)", code);
        plugins_fire(5, "elf2e32");
        ide_set_status("E32 FAILED");
        return;
    }
    {
        char fix_cmd[2048];
        char fixed_file[768];
        snprintf(fixed_file, sizeof(fixed_file), "%s/%s.imp.e32", build_dir, g_ide.proj.name);
        snprintf(fix_cmd, sizeof(fix_cmd), "\"%s/acetylene-e32fix.exe\" -elf \"%s\" -in \"%s\" -out \"%s\"",
                 exe_dir, elf_file, e32_file, fixed_file);
        buf_put(&g_ide.build_log, fix_cmd, strlen(fix_cmd));
        buf_u8(&g_ide.build_log, 10);
        if (run_capture(fix_cmd, NULL, 0) == 0) {
            DeleteFileA(e32_file);
            MoveFileA(fixed_file, e32_file);
        }
    }
    plugins_fire(4, e32_file);
    ide_set_status("Build OK: %s", e32_file);
}

static int output_log_lines(void);
static int output_max_scroll(void);

void ide_build(void)
{
    g_ide.building = 1;
    ide_set_status("Building...");
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
    UpdateWindow(g_ide.hwnd);
    run_build_pipeline();
    g_ide.building = 0;
    g_ide.output_scroll = output_max_scroll();
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

void ide_host_run_named(const char *id)
{
    if (!id)
        return;
    if (strcmp(id, "build") == 0)
        ide_command(CMD_BUILD);
    else if (strcmp(id, "rebuild") == 0)
        ide_command(CMD_REBUILD);
    else if (strcmp(id, "package") == 0)
        ide_command(CMD_PACKAGE);
    else if (strcmp(id, "sign") == 0)
        ide_command(CMD_SIGN);
    else if (strcmp(id, "run") == 0)
        ide_command(CMD_RUN);
    else if (strcmp(id, "save") == 0)
        ide_command(CMD_SAVE);
    else if (strcmp(id, "save_as") == 0)
        ide_command(CMD_SAVE_AS);
    else if (strcmp(id, "find") == 0)
        ide_command(CMD_FIND);
    else if (strcmp(id, "goto") == 0)
        ide_command(CMD_GOTO);
    else if (strcmp(id, "new_project") == 0)
        ide_command(CMD_NEW_PROJECT);
    else if (strcmp(id, "toggle_output") == 0)
        ide_command(CMD_TOGGLE_OUTPUT);
}

static void msg_utf8(const char *text, const char *caption, UINT flags)
{
    wchar_t wtext[4096];
    wchar_t wcap[128];
    MultiByteToWideChar(CP_UTF8, 0, text, -1, wtext, (int)(sizeof(wtext) / sizeof(wtext[0])));
    MultiByteToWideChar(CP_UTF8, 0, caption, -1, wcap, (int)(sizeof(wcap) / sizeof(wcap[0])));
    MessageBoxW(g_ide.hwnd, wtext, wcap, flags);
}

static int find_license_file(char *out, int cap)
{
    char exe[MAX_PATH];
    int i;
    GetModuleFileNameA(NULL, exe, sizeof(exe));
    for (i = (int)strlen(exe); i > 0 && exe[i] != '\\' && exe[i] != '/'; i--)
        exe[i] = 0;
    snprintf(out, (size_t)cap, "%sLICENSE", exe);
    if (path_exists(out))
        return 1;
    snprintf(out, (size_t)cap, "%s..\\..\\LICENSE", exe);
    if (path_exists(out))
        return 1;
    snprintf(out, (size_t)cap, "%s..\\LICENSE", exe);
    return path_exists(out);
}

static void show_about(void)
{
    char text[2600];
    snprintf(text, sizeof(text),
             AC_APP_NAME " " AC_APP_VERSION "  \xE2\x80\x94  %s\n\n"
             AC_BRAND_LINE1 "\n" AC_BRAND_LINE2 "\n\n"
             AC_COPYRIGHT "\n\n"
             "License: " AC_LICENSE_NAME "\n"
             "Help > License opens the full text.\n\n"
             "%s",
             AC_BUILD_TITLE, AC_ABOUT_COMPONENTS);
    msg_utf8(text, "About " AC_APP_NAME, MB_OK | MB_ICONINFORMATION);
}

static void open_license(void)
{
    char path[MAX_PATH];
    Doc *d;
    if (!find_license_file(path, sizeof(path))) {
        msg_utf8("The LICENSE file was not found next to the IDE.\n\n"
                 "Every build ships it in the package root; the source tree keeps it "
                 "at the repository root.", "License", MB_OK | MB_ICONWARNING);
        return;
    }
    ide_open_file(path);
    d = doc_active();
    if (d) {
        d->read_only = 1;
        d->lex_lang = 0;
    }
    ide_set_status("License: " AC_LICENSE_NAME);
}

static void ide_command(int cmd)
{
    Doc *d = doc_active();
    if (cmd <= -1000) {
        plugins_exec_index(-1000 - cmd);
        InvalidateRect(g_ide.hwnd, NULL, FALSE);
        return;
    }
    switch (cmd) {
    case CMD_NEW_PROJECT:
        ide_new_project();
        break;
    case CMD_OPEN_PROJECT:
        {
            OPENFILENAMEA ofn;
            char file[512];
            memset(&ofn, 0, sizeof(ofn));
            file[0] = 0;
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = g_ide.hwnd;
            ofn.lpstrFilter = "AcetyleneC Project\0*.acproj\0";
            ofn.lpstrFile = file;
            ofn.nMaxFile = sizeof(file);
            ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
            if (GetOpenFileNameA(&ofn))
                ide_open_project(file);
        }
        break;
    case CMD_OPEN_FILE:
        ide_open_dialog();
        break;
    case CMD_SAVE:
        if (d)
            ide_save_file(g_ide.active, 0);
        break;
    case CMD_SAVE_AS:
        if (d)
            ide_save_file(g_ide.active, 1);
        break;
    case CMD_CLOSE_TAB:
        if (d)
            ide_close_file(g_ide.active);
        break;
    case CMD_EXIT:
        PostMessageA(g_ide.hwnd, WM_CLOSE, 0, 0);
        break;
    case CMD_NEW_FILE:
        if (g_ide.ndocs < MAX_DOCS) {
            Doc *nd = &g_ide.docs[g_ide.ndocs];
            doc_init(nd, NULL);
            g_ide.active = g_ide.ndocs;
            g_ide.ndocs++;
            ide_set_status("new file (save with Ctrl+Shift+S)");
        }
        break;
    case CMD_SAVE_ALL:
        {
            int i;
            for (i = 0; i < g_ide.ndocs; i++) {
                if (g_ide.docs[i].path && g_ide.docs[i].modified)
                    ide_save_file(i, 0);
                else if (!g_ide.docs[i].path && g_ide.docs[i].modified) {
                    g_ide.active = i;
                    ide_save_dialog(i);
                }
            }
            ide_set_status("all saved");
        }
        break;
    case CMD_DUP_LINE:
        op_dup_line();
        break;
    case CMD_DEL_LINE:
        op_del_line();
        break;
    case CMD_TOGGLE_COMMENT:
        op_toggle_comment();
        break;
    case CMD_FIND_NEXT:
        if (!g_ide.find_text[0]) {
            ide_find();
        } else {
            g_ide.find_focus = 0;
            do_find_dir(1);
        }
        break;
    case CMD_FIND_PREV:
        if (g_ide.find_text[0]) {
            g_ide.find_focus = 0;
            do_find_dir(-1);
        }
        break;
    case CMD_UNDO:
        if (d) doc_undo(d);
        break;
    case CMD_REDO:
        if (d) doc_redo(d);
        break;
    case CMD_CUT:
        if (d) doc_cut(d);
        break;
    case CMD_COPY:
        if (d) doc_copy(d);
        break;
    case CMD_PASTE:
        if (d) doc_paste(d);
        break;
    case CMD_SELECT_ALL:
        if (d) doc_select_all(d);
        break;
    case CMD_FIND:
        ide_find();
        break;
    case CMD_GOTO:
        g_ide.find_open = 1;
        g_ide.find_focus = 1;
        break;
    case CMD_BUILD:
    case CMD_REBUILD:
        ide_build();
        break;
    case CMD_PACKAGE:
        ide_package();
        break;
    case CMD_SET_EMU:
        ide_choose_emulator();
        break;
    case CMD_SIGN:
        ide_sign();
        break;
    case CMD_RUN:
        ide_run();
        break;
    case CMD_CLEAN:
        ide_set_status("Clean: delete the build folder manually for now");
        break;
    case CMD_TOGGLE_OUTPUT:
        g_ide.show_output = !g_ide.show_output;
        ide_layout();
        break;
    case CMD_TOGGLE_TREE:
        g_ide.hide_tree = !g_ide.hide_tree;
        ide_layout();
        ide_set_status(g_ide.hide_tree ? "project tree hidden (Ctrl+B to show)" : "project tree visible");
        break;
    case CMD_ABOUT:
        show_about();
        break;
    case CMD_LICENSE:
        open_license();
        break;
    default:
        break;
    }
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

static int popup_step(const CtxItem *items, int count, int cur, int dir)
{
    int i = cur;
    int n;
    for (n = 0; n < count; n++) {
        i += dir;
        if (i < 0)
            i = count - 1;
        if (i >= count)
            i = 0;
        if (!items[i].sep && items[i].cmd)
            return i;
    }
    return cur;
}

static int popup_first(const CtxItem *items, int count)
{
    int i;
    for (i = 0; i < count; i++)
        if (!items[i].sep && items[i].cmd)
            return i;
    return -1;
}

int ide_key(int vk, int ctrl, int shift, int alt)
{
    Doc *d = doc_active();
    (void)alt;
    if (g_ctx_kind && g_ctx_items) {
        if (vk == VK_ESCAPE) {
            ctx_close();
            return 1;
        }
        if (vk == VK_DOWN) {
            g_ctx_hover = popup_step(g_ctx_items, g_ctx_count, g_ctx_hover < 0 ? popup_first(g_ctx_items, g_ctx_count) - 1 : g_ctx_hover, 1);
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return 1;
        }
        if (vk == VK_UP) {
            g_ctx_hover = popup_step(g_ctx_items, g_ctx_count, g_ctx_hover < 0 ? 1 : g_ctx_hover, -1);
            if (g_ctx_hover < 0)
                g_ctx_hover = popup_first(g_ctx_items, g_ctx_count);
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return 1;
        }
        if (vk == VK_RETURN) {
            int it = (g_ctx_hover >= 0) ? g_ctx_hover : popup_first(g_ctx_items, g_ctx_count);
            if (it >= 0) {
                int cmd = g_ctx_items[it].cmd;
                ctx_close();
                ctx_execute(cmd);
            }
            return 1;
        }
        return 1;
    }
    if (g_ide.menu_index >= 0) {
        build_menu(g_ide.menu_index);
        if (vk == VK_ESCAPE) {
            g_ide.menu_index = -1;
            return 1;
        }
        if (vk == VK_LEFT || vk == VK_RIGHT) {
            g_ide.menu_index = (g_ide.menu_index + (vk == VK_LEFT ? k_nmenus - 1 : 1)) % k_nmenus;
            g_ide.menu_hover = -1;
            return 1;
        }
        if (vk == VK_DOWN) {
            g_ide.menu_hover = popup_step(g_menu_items, g_menu_count, g_ide.menu_hover, 1);
            return 1;
        }
        if (vk == VK_UP) {
            if (g_ide.menu_hover < 0)
                g_ide.menu_hover = g_menu_count - 1;
            g_ide.menu_hover = popup_step(g_menu_items, g_menu_count, g_ide.menu_hover, -1);
            return 1;
        }
        if (vk == VK_RETURN) {
            int it = (g_ide.menu_hover >= 0) ? g_ide.menu_hover : popup_first(g_menu_items, g_menu_count);
            if (it >= 0 && it < g_menu_count) {
                int cmd = g_menu_items[it].cmd;
                g_ide.menu_index = -1;
                g_ide.menu_hover = -1;
                if (cmd)
                    ide_command(cmd);
            }
            return 1;
        }
        return 1;
    }
    if (g_ide.comp_open && !g_ide.find_open) {
        if (vk == VK_DOWN) {
            g_ide.comp_index = (g_ide.comp_index + 1) % g_ide.comp_count;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return 1;
        }
        if (vk == VK_UP) {
            g_ide.comp_index = (g_ide.comp_index + g_ide.comp_count - 1) % g_ide.comp_count;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return 1;
        }
        if (vk == VK_TAB || vk == VK_RETURN) {
            comp_accept();
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return 1;
        }
        if (vk == VK_ESCAPE) {
            g_ide.comp_open = 0;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return 1;
        }
    }
    if (g_ide.find_open) {
        if (vk == VK_ESCAPE) {
            g_ide.find_open = 0;
            return 1;
        }
        if (vk == VK_RETURN) {
            if (g_ide.find_focus)
                do_goto();
            else
                do_find_dir(shift ? -1 : 1);
            return 1;
        }
        if (vk == VK_BACK) {
            size_t n = strlen(g_ide.find_text);
            if (n) {
                if (g_ide.find_caret <= 0 || (size_t)g_ide.find_caret > n)
                    g_ide.find_caret = (int)n;
                memmove(g_ide.find_text + g_ide.find_caret - 1, g_ide.find_text + g_ide.find_caret,
                        n - (size_t)g_ide.find_caret + 1);
                g_ide.find_caret--;
            }
            return 1;
        }
        if (vk == VK_DELETE) {
            size_t n = strlen(g_ide.find_text);
            if ((size_t)g_ide.find_caret < n)
                memmove(g_ide.find_text + g_ide.find_caret, g_ide.find_text + g_ide.find_caret + 1,
                        n - (size_t)g_ide.find_caret);
            return 1;
        }
        if (vk == VK_LEFT) {
            if (g_ide.find_caret > 0)
                g_ide.find_caret--;
            return 1;
        }
        if (vk == VK_RIGHT) {
            if ((size_t)g_ide.find_caret < strlen(g_ide.find_text))
                g_ide.find_caret++;
            return 1;
        }
        if (vk == VK_HOME) {
            g_ide.find_caret = 0;
            return 1;
        }
        if (vk == VK_END) {
            g_ide.find_caret = (int)strlen(g_ide.find_text);
            return 1;
        }
        if (ctrl && vk == 'A') {
            g_ide.find_caret = (int)strlen(g_ide.find_text);
            g_ide.find_text[0] = 0;
            g_ide.find_caret = 0;
            return 1;
        }
        if (ctrl && vk == 'V') {
            if (OpenClipboard(g_ide.hwnd)) {
                HANDLE h = GetClipboardData(CF_TEXT);
                if (h) {
                    char *clip = GlobalLock(h);
                    if (clip) {
                        size_t n = strlen(g_ide.find_text);
                        size_t room = sizeof(g_ide.find_text) - n - 1;
                        size_t add = strlen(clip);
                        if (add > room)
                            add = room;
                        memmove(g_ide.find_text + g_ide.find_caret + add, g_ide.find_text + g_ide.find_caret,
                                n - (size_t)g_ide.find_caret + 1);
                        memcpy(g_ide.find_text + g_ide.find_caret, clip, add);
                        g_ide.find_caret += (int)add;
                        GlobalUnlock(h);
                    }
                }
                CloseClipboard();
            }
            return 1;
        }
        return 1;
    }
    if (ctrl && vk == 'S') {
        ide_command(shift ? CMD_SAVE_AS : CMD_SAVE);
        return 1;
    }
    if (ctrl && vk == VK_TAB) {
        if (g_ide.ndocs > 1) {
            int i = g_ide.active + (shift ? -1 : 1);
            if (i < 0) i = g_ide.ndocs - 1;
            if (i >= g_ide.ndocs) i = 0;
            g_ide.active = i;
        }
        return 1;
    }
    if (ctrl && vk == VK_F4) {
        ide_command(CMD_CLOSE_TAB);
        return 1;
    }
    if (ctrl && vk == VK_OEM_3) {
        ide_command(CMD_TOGGLE_OUTPUT);
        return 1;
    }
    if (alt && !ctrl && vk >= 'A' && vk <= 'Z') {
        static const char keys[] = {'F', 'E', 'B', 'V', 'H', 'P'};
        int mi;
        for (mi = 0; mi < k_nmenus && mi < 6; mi++) {
            if (vk == keys[mi]) {
                g_ide.menu_index = mi;
                g_ide.menu_hover = -1;
                return 1;
            }
        }
    }
    if (ctrl && vk == 'O') {
        ide_command(shift ? CMD_OPEN_PROJECT : CMD_OPEN_FILE);
        return 1;
    }
    if (ctrl && vk == 'N') {
        ide_command(shift ? CMD_NEW_PROJECT : CMD_NEW_FILE);
        return 1;
    }
    if (ctrl && vk == 'B') {
        ide_command(CMD_TOGGLE_TREE);
        return 1;
    }
    if (ctrl && vk == 'D') {
        ide_command(CMD_DUP_LINE);
        return 1;
    }
    if (ctrl && vk == 'K' && shift) {
        ide_command(CMD_DEL_LINE);
        return 1;
    }
    if (ctrl && (vk == VK_OEM_2 || vk == 0xBF || vk == 0xDC)) {
        ide_command(CMD_TOGGLE_COMMENT);
        return 1;
    }
    if (ctrl && vk == 'W') {
        ide_command(CMD_CLOSE_TAB);
        return 1;
    }
    if (ctrl && vk == 'Z') {
        ide_command(CMD_UNDO);
        return 1;
    }
    if (ctrl && vk == 'Y') {
        ide_command(CMD_REDO);
        return 1;
    }
    if (ctrl && vk == 'X') {
        ide_command(CMD_CUT);
        return 1;
    }
    if (ctrl && vk == 'C') {
        ide_command(CMD_COPY);
        return 1;
    }
    if (ctrl && vk == 'V') {
        ide_command(CMD_PASTE);
        return 1;
    }
    if (ctrl && vk == 'A') {
        ide_command(CMD_SELECT_ALL);
        return 1;
    }
    if (ctrl && vk == 'P') {
        ide_command(CMD_PACKAGE);
        return 1;
    }
    if (ctrl && vk == 'F') {
        ide_command(CMD_FIND);
        return 1;
    }
    if (ctrl && vk == 'G') {
        ide_command(CMD_GOTO);
        return 1;
    }
    if (vk == VK_F3) {
        ide_command(shift ? CMD_FIND_PREV : CMD_FIND_NEXT);
        return 1;
    }
    if (vk == VK_F7) {
        ide_command((shift || ctrl) ? CMD_REBUILD : CMD_BUILD);
        return 1;
    }
    if (vk == VK_F9) {
        ide_command(CMD_SIGN);
        return 1;
    }
    if (vk == VK_F5) {
        ide_command(CMD_RUN);
        return 1;
    }
    if (!d)
        return 0;

    switch (vk) {
    case VK_LEFT:
        if (ctrl) {
            int pos = d->caret;
            while (pos > 0 && (d->data.data[pos - 1] == ' ' || d->data.data[pos - 1] == '\t'))
                pos--;
            while (pos > 0 && d->data.data[pos - 1] != ' ' && d->data.data[pos - 1] != '\t' &&
                   d->data.data[pos - 1] != '\n' && !strchr("(){}[];,+-*/=<>!&|", d->data.data[pos - 1]))
                pos--;
            doc_set_caret(d, pos, shift);
        } else {
            doc_set_caret(d, d->caret - 1, shift);
        }
        doc_scroll_to_caret(d);
        return 1;
    case VK_RIGHT:
        if (ctrl) {
            int pos = d->caret;
            while (pos < (int)d->data.len && d->data.data[pos] != ' ' && d->data.data[pos] != '\t' &&
                   d->data.data[pos] != '\n' && !strchr("(){}[];,+-*/=<>!&|", d->data.data[pos]))
                pos++;
            while (pos < (int)d->data.len && (d->data.data[pos] == ' ' || d->data.data[pos] == '\t'))
                pos++;
            doc_set_caret(d, pos, shift);
        } else {
            doc_set_caret(d, d->caret + 1, shift);
        }
        doc_scroll_to_caret(d);
        return 1;
    case VK_UP: {
        int line = doc_line_of(d, d->caret);
        int col = doc_col_of(d, d->caret);
        if (line > 0)
            doc_set_caret(d, doc_pos_from_col(d, line - 1, col), shift);
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_DOWN: {
        int line = doc_line_of(d, d->caret);
        int col = doc_col_of(d, d->caret);
        if (line + 1 < d->nlines)
            doc_set_caret(d, doc_pos_from_col(d, line + 1, col), shift);
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_HOME: {
        int line = doc_line_of(d, d->caret);
        int ls = doc_line_start(d, line);
        if (ctrl) {
            doc_set_caret(d, 0, shift);
        } else {
            int le = doc_line_end(d, line);
            int fnw = ls;
            while (fnw < le && (d->data.data[fnw] == ' ' || d->data.data[fnw] == '\t'))
                fnw++;
            if (d->caret != fnw)
                doc_set_caret(d, fnw, shift);
            else
                doc_set_caret(d, ls, shift);
        }
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_END: {
        int le = doc_line_end(d, doc_line_of(d, d->caret));
        if (ctrl)
            doc_set_caret(d, (int)d->data.len, shift);
        else
            doc_set_caret(d, le, shift);
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_PRIOR: {
        int visible = (g_ide.rc_editor.bottom - g_ide.rc_editor.top) / (g_ide.line_h ? g_ide.line_h : 16);
        int line = doc_line_of(d, d->caret);
        int col = doc_col_of(d, d->caret);
        int nl = line - visible;
        if (visible < 1)
            visible = 1;
        if (nl < 0)
            nl = 0;
        doc_set_caret(d, doc_pos_from_col(d, nl, col), shift);
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_NEXT: {
        int visible = (g_ide.rc_editor.bottom - g_ide.rc_editor.top) / (g_ide.line_h ? g_ide.line_h : 16);
        int line = doc_line_of(d, d->caret);
        int col = doc_col_of(d, d->caret);
        int nl = line + visible;
        if (visible < 1)
            visible = 1;
        if (nl > d->nlines - 1)
            nl = d->nlines - 1;
        doc_set_caret(d, doc_pos_from_col(d, nl, col), shift);
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_BACK:
        if (doc_has_selection(d)) {
            int a, b;
            doc_sel_range(d, &a, &b);
            doc_delete(d, a, b - a);
        } else if (ctrl) {
            int pos = d->caret;
            int from;
            while (pos > 0 && (d->data.data[pos - 1] == ' ' || d->data.data[pos - 1] == '\t'))
                pos--;
            while (pos > 0 && d->data.data[pos - 1] != ' ' && d->data.data[pos - 1] != '\t' &&
                   d->data.data[pos - 1] != '\n' && !strchr("(){}[];,+-*/=<>!&|", d->data.data[pos - 1]))
                pos--;
            from = pos;
            if (from < d->caret) {
                int c = d->caret;
                doc_delete(d, from, c - from);
            }
        } else if (d->caret > 0) {
            doc_delete(d, d->caret - 1, 1);
        }
        doc_scroll_to_caret(d);
        return 1;
    case VK_DELETE:
        if (doc_has_selection(d)) {
            int a, b;
            doc_sel_range(d, &a, &b);
            doc_delete(d, a, b - a);
        } else if (ctrl) {
            int pos = d->caret;
            while (pos < (int)d->data.len && (d->data.data[pos] == ' ' || d->data.data[pos] == '\t'))
                pos++;
            while (pos < (int)d->data.len && d->data.data[pos] != ' ' && d->data.data[pos] != '\t' &&
                   d->data.data[pos] != '\n' && !strchr("(){}[];,+-*/=<>!&|", d->data.data[pos]))
                pos++;
            if (pos > d->caret)
                doc_delete(d, d->caret, pos - d->caret);
        } else if (d->caret < (int)d->data.len) {
            doc_delete(d, d->caret, 1);
        }
        return 1;
    case VK_RETURN: {
        int ls = doc_line_start(d, doc_line_of(d, d->caret));
        int le = doc_line_end(d, doc_line_of(d, d->caret));
        int indent = 0;
        int extra = 0;
        while (ls + indent < (int)d->data.len && d->data.data[ls + indent] == '\t')
            indent++;
        if (d->caret > ls) {
            int k = d->caret - 1;
            while (k >= ls && (d->data.data[k] == ' ' || d->data.data[k] == '\t' || d->data.data[k] == '\r'))
                k--;
            if (k >= ls && k < (int)d->data.len && d->data.data[k] == '{')
                extra = 1;
        }
        if (d->caret < le && d->data.data[d->caret] == '}' && extra) {
            char nl[130];
            int n = 0;
            int i;
            nl[n++] = '\n';
            for (i = 0; i < indent + extra && n < 120; i++)
                nl[n++] = '\t';
            nl[n++] = '\n';
            for (i = 0; i < indent && n < 126; i++)
                nl[n++] = '\t';
            doc_insert(d, d->caret, nl, n);
            doc_set_caret(d, d->caret - indent - 1, 0);
            doc_scroll_to_caret(d);
            return 1;
        } else {
            char nl[64];
            int n = 0;
            nl[n++] = '\n';
            while (indent-- > 0 && n < 60)
                nl[n++] = '\t';
            if (extra && n < 60)
                nl[n++] = '\t';
            doc_insert(d, d->caret, nl, n);
        }
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_TAB: {
        if (shift || doc_has_selection(d)) {
            op_indent(shift);
        } else {
            doc_insert(d, d->caret, "\t", 1);
        }
        return 1;
    }
    case VK_ESCAPE:
        g_ide.menu_index = -1;
        g_ide.find_open = 0;
        ctx_close();
        return 1;
    default:
        break;
    }
    return 0;
}

void ide_char(wchar_t ch)
{
    Doc *d = doc_active();
    char utf8[8];
    int n;
    if (ch > 0 && ch < 32 && ch != 9 && ch != 10 && ch != 13) {
        switch (ch) {
        case 1: ide_command(CMD_SELECT_ALL); return;
        case 3: ide_command(CMD_COPY); return;
        case 6: ide_command(CMD_FIND); return;
        case 7: ide_command(CMD_GOTO); return;
        case 19: ide_command(CMD_SAVE); return;
        case 22: ide_command(CMD_PASTE); return;
        case 23: ide_command(CMD_CLOSE_TAB); return;
        case 24: ide_command(CMD_CUT); return;
        case 26: ide_command(CMD_UNDO); return;
        default: return;
        }
    }
    if (g_ide.find_open) {
        size_t len = strlen(g_ide.find_text);
        if (ch >= 32 && ch < 127 && len + 1 < sizeof(g_ide.find_text)) {
            if (g_ide.find_caret < 0 || (size_t)g_ide.find_caret > len)
                g_ide.find_caret = (int)len;
            memmove(g_ide.find_text + g_ide.find_caret + 1, g_ide.find_text + g_ide.find_caret,
                    len - (size_t)g_ide.find_caret + 1);
            g_ide.find_text[g_ide.find_caret] = (char)ch;
            g_ide.find_caret++;
        }
        return;
    }
    if (!d)
        return;
    if (ch < 32 && ch != '\t')
        return;
    if (d->read_only) {
        ide_set_status("%s is read-only", d->name ? d->name : "document");
        return;
    }
    if (doc_has_selection(d)) {
        int a, b;
        doc_sel_range(d, &a, &b);
        doc_delete(d, a, b - a);
    }
    if (ch < 128) {
        utf8[0] = (char)ch;
        n = 1;
    } else {
        n = WideCharToMultiByte(CP_UTF8, 0, &ch, 1, utf8, sizeof(utf8), NULL, NULL);
    }
    doc_insert(d, d->caret, utf8, n);
    doc_scroll_to_caret(d);
    comp_update();
}

static int g_scroll_drag;
static int g_scroll_dragging;

void ide_rbutton_down(int x, int y)
{
    ctx_show_at(x, y);
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

void ide_mouse_down(int x, int y, int shift, int button)
{
    int mi;
    if (g_ctx_kind && g_ctx_items) {
        int item = -1;
        if (panel_hit(x, y, g_ctx_x, g_ctx_y, g_ctx_items, g_ctx_count, &item)) {
            int cmd = g_ctx_items[item].cmd;
            ctx_close();
            ctx_execute(cmd);
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return;
        }
        ctx_close();
        InvalidateRect(g_ide.hwnd, NULL, FALSE);
        return;
    }
    if (button == 1) {
        if (PtInRect(&g_ide.rc_tabs, (POINT){x, y})) {
            int i;
            HDC dc = GetDC(g_ide.hwnd);
            RECT tr;
            for (i = 0; i < g_ide.ndocs; i++) {
                if (tab_rect(dc, i, &tr) && PtInRect(&tr, (POINT){x, y})) {
                    ReleaseDC(g_ide.hwnd, dc);
                    ide_close_file(i);
                    InvalidateRect(g_ide.hwnd, NULL, FALSE);
                    return;
                }
            }
            ReleaseDC(g_ide.hwnd, dc);
        }
        return;
    }
    if (button != 0)
        return;
    if (y < 26) {
        mi = hit_menu(x, y);
        if (mi >= 0) {
            g_ide.menu_index = (g_ide.menu_index == mi) ? -1 : mi;
            g_ide.menu_hover = -1;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
            return;
        }
        g_ide.menu_index = -1;
    } else if (g_ide.menu_index >= 0) {
        int item;
        if (menu_item_hit(x, y, &item)) {
            int cmd;
            build_menu(g_ide.menu_index);
            cmd = (item >= 0 && item < g_menu_count) ? g_menu_items[item].cmd : 0;
            g_ide.menu_index = -1;
            g_ide.menu_hover = -1;
            if (cmd)
                ide_command(cmd);
            return;
        }
        g_ide.menu_index = -1;
    }
    {
        int tb = toolbar_hit(x, y);
        if (tb >= 0) {
            ide_command(k_tool_ids[tb]);
            return;
        }
    }
    if (PtInRect(&g_ide.rc_tabs, (POINT){x, y})) {
        int i;
        HDC dc = GetDC(g_ide.hwnd);
        RECT tr;
        for (i = 0; i < g_ide.ndocs; i++) {
            if (tab_rect(dc, i, &tr) && PtInRect(&tr, (POINT){x, y})) {
                ReleaseDC(g_ide.hwnd, dc);
                if (x >= tr.right - 23)
                    ide_close_file(i);
                else
                    g_ide.active = i;
                InvalidateRect(g_ide.hwnd, NULL, FALSE);
                return;
            }
        }
        ReleaseDC(g_ide.hwnd, dc);
        return;
    }
    if (PtInRect(&g_ide.rc_tree, (POINT){x, y})) {
        int row = (y - g_ide.rc_tree.top - TREE_ROWS_TOP) / TREE_ROW_H + g_ide.tree_scroll;
        if (row >= 0 && row < g_ide.tree_files.count) {
            g_ide.tree_sel = row;
            ide_open_file(g_ide.tree_files.items[row]);
        }
        return;
    }
    if (!g_ide.hide_tree && abs(x - g_ide.split_x) <= 3 && y > g_ide.rc_toolbar.bottom) {
        g_ide.dragging_split = 1;
        SetCapture(g_ide.hwnd);
        return;
    }
    if (g_ide.show_output && abs(y - g_ide.split_y) <= 3 && x > g_ide.split_x) {
        g_ide.dragging_split = 2;
        SetCapture(g_ide.hwnd);
        return;
    }
    if (PtInRect(&g_ide.rc_editor, (POINT){x, y})) {
        Doc *d = doc_active();
        if (d) {
            int tt, thh, bt, bh;
            if (x >= g_ide.rc_editor.right - 9 && x < g_ide.rc_editor.right - 1) {
                editor_scrollbar_metrics(d, &tt, &thh, &bt, &bh);
                if (y >= bt && y < bt + bh) {
                    g_scroll_drag = y - bt;
                } else {
                    int visible = thh / (g_ide.line_h ? g_ide.line_h : 16);
                    if (visible < 1)
                        visible = 1;
                    d->top_line += (y < bt ? -visible : visible);
                    if (d->top_line < 0)
                        d->top_line = 0;
                    g_scroll_drag = -1;
                }
                if (g_scroll_drag >= 0)
                    g_scroll_dragging = 1;
                SetCapture(g_ide.hwnd);
                return;
            }
            doc_set_caret(d, doc_hit_test(d, x - g_ide.rc_editor.left - gutter_width(d), y - g_ide.rc_editor.top - 2), shift);
            SetCapture(g_ide.hwnd);
        }
        return;
    }
    if (g_ide.show_output && PtInRect(&g_ide.rc_output, (POINT){x, y})) {
        int row = (y - g_ide.rc_output.top - 24) / 18;
        if (row >= 0 && row < g_ide.nmsgs) {
            g_ide.selected_msg = row;
            if (g_ide.msgs[row].file[0])
                ide_open_file(g_ide.msgs[row].file);
        }
    }
}

void ide_mouse_up(int x, int y)
{
    (void)x;
    (void)y;
    g_ide.dragging_split = 0;
    g_scroll_dragging = 0;
    ReleaseCapture();
}

void ide_mouse_move(int x, int y, int buttons)
{
    if (g_ide.dragging_split == 1) {
        g_ide.split_x = x;
        ide_layout();
        InvalidateRect(g_ide.hwnd, NULL, FALSE);
        return;
    }
    if (g_ide.dragging_split == 2) {
        g_ide.split_y = y;
        ide_layout();
        InvalidateRect(g_ide.hwnd, NULL, FALSE);
        return;
    }
    if (g_scroll_dragging) {
        Doc *d = doc_active();
        if (d) {
            int tt, thh, bt, bh;
            int max;
            int vis = (g_ide.rc_editor.bottom - g_ide.rc_editor.top - 4) / (g_ide.line_h ? g_ide.line_h : 16);
            if (vis < 1)
                vis = 1;
            max = d->nlines - vis;
            if (max < 0)
                max = 0;
            editor_scrollbar_metrics(d, &tt, &thh, &bt, &bh);
            if (thh - bh > 0 && max > 0) {
                float frac = (float)(y - g_scroll_drag - tt) / (float)(thh - bh);
                if (frac < 0.0f)
                    frac = 0.0f;
                if (frac > 1.0f)
                    frac = 1.0f;
                d->top_line = (int)(frac * max + 0.5f);
            }
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
        }
        return;
    }
    if (buttons & 1) {
        Doc *d = doc_active();
        if (d && PtInRect(&g_ide.rc_editor, (POINT){x, y}) && x < g_ide.rc_editor.right - 10) {
            doc_set_caret(d, doc_hit_test(d, x - g_ide.rc_editor.left - gutter_width(d), y - g_ide.rc_editor.top - 2), 1);
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
        }
    }
    {
        int hot = -1;
        int need = 0;
        if (y < 26) {
            hot = hit_menu(x, y);
            if (hot != g_bar_hot) {
                g_bar_hot = hot;
                need = 1;
            }
        } else if (g_bar_hot != -1) {
            g_bar_hot = -1;
            need = 1;
        }
        {
            int tb = toolbar_hit(x, y);
            if (tb != g_tool_hot) {
                g_tool_hot = tb;
                need = 1;
            }
        }
        if (PtInRect(&g_ide.rc_tree, (POINT){x, y})) {
            int row = (y - g_ide.rc_tree.top - TREE_ROWS_TOP) / TREE_ROW_H + g_ide.tree_scroll;
            if (row < 0 || row >= g_ide.tree_files.count)
                row = -1;
            if (row != g_tree_hot) {
                g_tree_hot = row;
                need = 1;
            }
        } else if (g_tree_hot != -1) {
            g_tree_hot = -1;
            need = 1;
        }
        if (PtInRect(&g_ide.rc_tabs, (POINT){x, y})) {
            int i;
            HDC dc = GetDC(g_ide.hwnd);
            RECT tr;
            int th = -1, tc = -1;
            for (i = 0; i < g_ide.ndocs; i++) {
                if (tab_rect(dc, i, &tr) && PtInRect(&tr, (POINT){x, y})) {
                    th = i;
                    if (x >= tr.right - 23)
                        tc = i;
                    break;
                }
            }
            ReleaseDC(g_ide.hwnd, dc);
            if (th != g_tab_hot || tc != g_tab_close_hot) {
                g_tab_hot = th;
                g_tab_close_hot = tc;
                need = 1;
            }
        } else if (g_tab_hot != -1 || g_tab_close_hot != -1) {
            g_tab_hot = -1;
            g_tab_close_hot = -1;
            need = 1;
        }
        if (need)
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
    }
    if (g_ide.menu_index >= 0) {
        int item = -1;
        if (menu_item_hit(x, y, &item) && g_ide.menu_hover != item) {
            g_ide.menu_hover = item;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
        }
    }
    if (g_ctx_kind && g_ctx_items) {
        int item = -1;
        if (panel_hit(x, y, g_ctx_x, g_ctx_y, g_ctx_items, g_ctx_count, &item) && g_ctx_hover != item) {
            g_ctx_hover = item;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
        }
    }
}

static int output_log_lines(void)
{
    int i, n = 0;
    for (i = 0; i < (int)g_ide.build_log.len; i++)
        if (g_ide.build_log.data[i] == '\n')
            n++;
    return n;
}

static int output_visible_lines(void)
{
    int vis = (g_ide.rc_output.bottom - g_ide.rc_output.top - 40) / 16;
    return vis < 1 ? 1 : vis;
}

static int output_max_scroll(void)
{
    int total = output_log_lines();
    int vis = output_visible_lines();
    return total > vis ? total - vis : 0;
}

void ide_wheel(int delta, int keys, int x, int y)
{
    static int acc;
    Doc *d = doc_active();
    int notch;
    int lines = 3;

    acc += delta;
    notch = acc / WHEEL_DELTA;
    acc -= notch * WHEEL_DELTA;
    if (notch == 0)
        return;

    if (!g_ide.hide_tree && x < g_ide.rc_tree.right) {
        int max = g_ide.tree_files.count - 1;
        if (max < 0)
            max = 0;
        g_ide.tree_scroll -= notch * lines;
        if (g_ide.tree_scroll > max)
            g_ide.tree_scroll = max;
        if (g_ide.tree_scroll < 0)
            g_ide.tree_scroll = 0;
    } else if (g_ide.show_output && y >= g_ide.rc_output.top && y < g_ide.rc_output.bottom) {
        if (g_ide.nmsgs == 0) {
            int max = output_max_scroll();
            g_ide.output_scroll -= notch * lines;
            if (g_ide.output_scroll > max)
                g_ide.output_scroll = max;
            if (g_ide.output_scroll < 0)
                g_ide.output_scroll = 0;
        }
    } else if (d && y >= g_ide.rc_editor.top) {
        if (keys & MK_SHIFT) {
            int unit = g_ide.char_w > 0 ? g_ide.char_w : 8;
            d->scroll_x -= notch * 4 * unit;
            if (d->scroll_x < 0)
                d->scroll_x = 0;
        } else {
            int vis = (g_ide.rc_editor.bottom - g_ide.rc_editor.top - 4) / (g_ide.line_h ? g_ide.line_h : 16);
            int max;
            if (vis < 1)
                vis = 1;
            max = d->nlines - vis;
            if (max < 0)
                max = 0;
            d->top_line -= notch * lines;
            if (d->top_line > max)
                d->top_line = max;
            if (d->top_line < 0)
                d->top_line = 0;
        }
    }
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

static void free_all(void)
{
    int i;
    for (i = 0; i < g_ide.ndocs; i++)
        doc_free(&g_ide.docs[i]);
    sv_free(&g_ide.proj.sources);
    sv_free(&g_ide.proj.libs);
    sv_free(&g_ide.tree_files);
    buf_free(&g_ide.build_log);
    DeleteObject(g_ide.font);
    DeleteObject(g_ide.font_ui);
    DeleteObject(g_ide.font_bold);
}

static void paint_caret_timer(HWND hwnd)
{
    g_ide.blink_on = !g_ide.blink_on;
    InvalidateRect(hwnd, &g_ide.rc_editor, FALSE);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_CREATE:
        ide_init(hwnd);
        SetTimer(hwnd, 1, 530, NULL);
        return 0;
    case WM_SIZE:
        ide_layout();
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        RECT rc;
        HDC dc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rc);
        ide_paint(dc, &rc);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_TIMER:
        paint_caret_timer(hwnd);
        return 0;
    case WM_KEYDOWN: {
        int ctrl = ((GetKeyState(VK_CONTROL) & 0x8000) != 0) || ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0);
        int shift = ((GetKeyState(VK_SHIFT) & 0x8000) != 0) || ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0);
        int alt = (GetKeyState(VK_MENU) & 0x8000) != 0;
        if (ide_key((int)wp, ctrl, shift, alt))
            InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }
    case WM_CHAR:
        ide_char((wchar_t)wp);
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    case WM_LBUTTONDOWN:
        SetFocus(hwnd);
        ide_mouse_down((short)LOWORD(lp), (short)HIWORD(lp), (GetKeyState(VK_SHIFT) & 0x8000) != 0, 0);
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    case WM_LBUTTONDBLCLK: {
        Doc *d = doc_active();
        if (d && PtInRect(&g_ide.rc_editor, (POINT){(short)LOWORD(lp), (short)HIWORD(lp)})) {
            int x = (short)LOWORD(lp), y = (short)HIWORD(lp);
            int pos = doc_hit_test(d, x - g_ide.rc_editor.left - gutter_width(d), y - g_ide.rc_editor.top - 2);
            int a = pos, b = pos;
            const char *data = (const char *)d->data.data;
            int len = (int)d->data.len;
            if (pos < len && (isalnum((unsigned char)data[pos]) || data[pos] == '_')) {
                while (a > 0 && (isalnum((unsigned char)data[a - 1]) || data[a - 1] == '_'))
                    a--;
                while (b < len && (isalnum((unsigned char)data[b]) || data[b] == '_'))
                    b++;
                d->anchor = a;
                d->caret = b;
                d->sel_active = 1;
                InvalidateRect(hwnd, NULL, FALSE);
            }
        }
        return 0;
    }
    case WM_MBUTTONDOWN:
        SetFocus(hwnd);
        ide_mouse_down((short)LOWORD(lp), (short)HIWORD(lp), 0, 1);
        return 0;
    case WM_RBUTTONDOWN:
        SetFocus(hwnd);
        ide_rbutton_down((short)LOWORD(lp), (short)HIWORD(lp));
        return 0;
    case WM_LBUTTONUP:
        ide_mouse_up((short)LOWORD(lp), (short)HIWORD(lp));
        return 0;
    case WM_MOUSEMOVE:
        ide_mouse_move((short)LOWORD(lp), (short)HIWORD(lp), (int)wp);
        return 0;
    case WM_MOUSEWHEEL: {
        POINT pt;
        int delta = GET_WHEEL_DELTA_WPARAM(wp);
        int keys = GET_KEYSTATE_WPARAM(wp);
        pt.x = (short)LOWORD(lp);
        pt.y = (short)HIWORD(lp);
        ScreenToClient(hwnd, &pt);
        ide_wheel(delta, keys, pt.x, pt.y);
        return 0;
    }
    case WM_SETCURSOR:
        {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hwnd, &p);
            if (!g_ide.hide_tree && abs(p.x - g_ide.split_x) <= 3 && p.y > g_ide.rc_toolbar.bottom) {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                return TRUE;
            }
            if (g_ide.show_output && abs(p.y - g_ide.split_y) <= 3 && p.x > g_ide.split_x) {
                SetCursor(LoadCursor(NULL, IDC_SIZENS));
                return TRUE;
            }
            if (PtInRect(&g_ide.rc_editor, p))
                SetCursor(LoadCursor(NULL, IDC_IBEAM));
        }
        break;
    case WM_CLOSE:
        free_all();
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

void ide_new_project(void)
{
    BROWSEINFOA bi;
    char path[MAX_PATH];
    char file[MAX_PATH];
    char src[MAX_PATH];
    HANDLE h;
    memset(&bi, 0, sizeof(bi));
    bi.lpszTitle = "Choose a folder for the new AcetyleneC project";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    {
        LPITEMIDLIST idl = SHBrowseForFolderA(&bi);
        if (!idl)
            return;
        if (!SHGetPathFromIDListA(idl, path))
            return;
        CoTaskMemFree(idl);
    }
    {
        const char *nm = ac_basename(path);
        snprintf(g_ide.proj.name, sizeof(g_ide.proj.name), "%s", nm[0] ? nm : "project");
    }
    snprintf(file, sizeof(file), "%s\\%s.acproj", path, g_ide.proj.name);
    snprintf(src, sizeof(src), "%s\\main.c", path);
    snprintf(g_ide.proj.project_path, sizeof(g_ide.proj.project_path), "%s", file);
    {
        const char *stub =
            "#include <e32std.h>\n"
            "\n"
            "GLDEF_C TInt E32Main()\n"
            "    {\n"
            "    return KErrNone;\n"
            "    }\n";
        h = CreateFileA(src, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h != INVALID_HANDLE_VALUE) {
            DWORD wr;
            WriteFile(h, stub, (DWORD)strlen(stub), &wr, NULL);
            CloseHandle(h);
        }
    }
    sv_free(&g_ide.proj.sources);
    sv_init(&g_ide.proj.sources);
    sv_push(&g_ide.proj.sources, src);
    sv_free(&g_ide.tree_files);
    sv_init(&g_ide.tree_files);
    sv_push(&g_ide.tree_files, src);
    ide_save_project();
    ide_open_file(src);
    ide_set_status("Created project %s", g_ide.proj.name);
}

void ide_save_project(void)
{
    Buf b;
    char line[512];
    int i;
    if (!g_ide.proj.project_path[0])
        return;
    buf_init(&b);
    snprintf(line, sizeof(line), "[project]\nname=%s\ntarget=%s\nuid3=%s\ncaps=%s\nheap=%d\nstack=%d\nis_dll=%d\n",
             g_ide.proj.name, g_ide.proj.target, g_ide.proj.uid3, g_ide.proj.caps, g_ide.proj.heap, g_ide.proj.stack, g_ide.proj.is_dll);
    buf_put(&b, line, strlen(line));
    for (i = 0; i < g_ide.proj.sources.count; i++) {
        snprintf(line, sizeof(line), "source=%s\n", g_ide.proj.sources.items[i]);
        buf_put(&b, line, strlen(line));
    }
    for (i = 0; i < g_ide.proj.libs.count; i++) {
        snprintf(line, sizeof(line), "lib=%s\n", g_ide.proj.libs.items[i]);
        buf_put(&b, line, strlen(line));
    }
    ac_write_file(g_ide.proj.project_path, b.data, b.len);
    buf_free(&b);
    ide_set_status("Project saved: %s", g_ide.proj.project_path);
}

static int path_is_abs(const char *p)
{
    if (!p || !p[0])
        return 0;
    if (p[0] == '\\' && p[1] == '\\')
        return 1;
    return p[0] != 0 && p[1] == ':' && (p[2] == '\\' || p[2] == '/');
}

static void path_dir_of(char *p)
{
    int i = (int)strlen(p);
    while (i > 0 && p[i] != '\\' && p[i] != '/')
        i--;
    if (i > 3)
        p[i] = 0;
    else if (i == 2 && p[1] == ':')
        p[3] = 0;
}

static int path_exists(const char *p)
{
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && a != 0xFFFFFFFFu;
}

static void path_normalize(const char *in, char *out, int cap)
{
    if (!in || !in[0]) {
        out[0] = 0;
        return;
    }
    if (!GetFullPathNameA(in, (DWORD)cap, out, NULL))
        snprintf(out, (size_t)cap, "%s", in);
}

static void resolve_relative(const char *dir, const char *rel, char *out, int cap)
{
    char cand[MAX_PATH];
    char cur[MAX_PATH];
    int depth;

    if (path_is_abs(rel)) {
        snprintf(out, (size_t)cap, "%s", rel);
        return;
    }
    snprintf(cand, sizeof(cand), "%s\\%s", dir, rel);
    if (path_exists(cand)) {
        snprintf(out, (size_t)cap, "%s", cand);
        return;
    }
    snprintf(cur, sizeof(cur), "%s", dir);
    for (depth = 0; depth < 8; depth++) {
        int before = (int)strlen(cur);
        path_dir_of(cur);
        if ((int)strlen(cur) == before)
            break;
        snprintf(cand, sizeof(cand), "%s\\%s", cur, rel);
        if (path_exists(cand)) {
            snprintf(out, (size_t)cap, "%s", cand);
            return;
        }
        if (cur[1] == ':' && cur[2] == 0)
            break;
    }
    snprintf(out, (size_t)cap, "%s\\%s", dir, rel);
}

void ide_open_project(const char *path)
{
    Buf b;
    char *p;
    char norm[MAX_PATH];
    path_normalize(path, norm, sizeof(norm));
    path = norm;
    if (ac_read_file(path, &b) != 0)
        return;
    buf_put(&b, "", 1);
    snprintf(g_ide.proj.project_path, sizeof(g_ide.proj.project_path), "%s", path);
    sv_free(&g_ide.proj.sources);
    sv_init(&g_ide.proj.sources);
    sv_free(&g_ide.proj.libs);
    sv_init(&g_ide.proj.libs);
    sv_free(&g_ide.tree_files);
    sv_init(&g_ide.tree_files);
    g_ide.tree_sel = -1;
    g_ide.tree_scroll = 0;
    g_ide.proj.is_dll = 0;
    p = (char *)b.data;
    while (*p) {
        char *nl = strchr(p, '\n');
        char *eq;
        if (nl)
            *nl = 0;
        eq = strchr(p, '=');
        if (eq) {
            *eq = 0;
            if (strcmp(p, "name") == 0)
                snprintf(g_ide.proj.name, sizeof(g_ide.proj.name), "%s", eq + 1);
            else if (strcmp(p, "target") == 0)
                snprintf(g_ide.proj.target, sizeof(g_ide.proj.target), "%s", eq + 1);
            else if (strcmp(p, "uid3") == 0)
                snprintf(g_ide.proj.uid3, sizeof(g_ide.proj.uid3), "%s", eq + 1);
            else if (strcmp(p, "caps") == 0)
                snprintf(g_ide.proj.caps, sizeof(g_ide.proj.caps), "%s", eq + 1);
            else if (strcmp(p, "heap") == 0)
                g_ide.proj.heap = (int)strtol(eq + 1, NULL, 0);
            else if (strcmp(p, "stack") == 0)
                g_ide.proj.stack = (int)strtol(eq + 1, NULL, 0);
            else if (strcmp(p, "is_dll") == 0)
                g_ide.proj.is_dll = (int)strtol(eq + 1, NULL, 0);
            else if (strcmp(p, "source") == 0) {
                char full[MAX_PATH];
                char projdir[MAX_PATH];
                sv_push(&g_ide.proj.sources, eq + 1);
                snprintf(projdir, sizeof(projdir), "%s", path);
                path_dir_of(projdir);
                resolve_relative(projdir, eq + 1, full, sizeof(full));
                tree_add_file(full);
            } else if (strcmp(p, "lib") == 0) {
                sv_push(&g_ide.proj.libs, eq + 1);
            }
        }
        if (!nl)
            break;
        p = nl + 1;
    }
    buf_free(&b);
    if (g_ide.tree_files.count > 0)
        ide_open_file(g_ide.tree_files.items[0]);
    ide_set_status("Opened project %s", g_ide.proj.name);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmdline, int show)
{
    WNDCLASSA wc;
    HWND hwnd;
    MSG msg;
    (void)prev;
    (void)cmdline;
    InitCommonControls();
    CoInitialize(NULL);
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = inst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "AcetyleneCWindow";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassA(&wc))
        return 1;
    {
        RECT wa;
        int w, h;
        SystemParametersInfoA(SPI_GETWORKAREA, 0, &wa, 0);
        w = wa.right - wa.left;
        h = wa.bottom - wa.top;
        hwnd = CreateWindowExA(0, "AcetyleneCWindow", "AcetyleneC", WS_OVERLAPPEDWINDOW,
                               wa.left + 4, wa.top + 4, w - 8, h - 8, NULL, NULL, inst, NULL);
        if (!hwnd)
            return 1;
        ShowWindow(hwnd, show);
        UpdateWindow(hwnd);
        if (cmdline && cmdline[0]) {
            const char *arg = cmdline;
            while (*arg == ' ' || *arg == '"')
                arg++;
            {
                char path[MAX_PATH];
                int n = 0;
                while (arg[n] && arg[n] != '"' && n < MAX_PATH - 1) {
                    path[n] = arg[n];
                    n++;
                }
                path[n] = 0;
                if (ac_has_ext(path, ".acproj"))
                    ide_open_project(path);
                else
                    ide_open_file(path);
                InvalidateRect(hwnd, NULL, FALSE);
            }
        }
    }
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    CoUninitialize();
    return 0;
}
