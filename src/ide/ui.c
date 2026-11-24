#include "ide.h"
#include <stdarg.h>

Ide g_ide;

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
    CMD_TOGGLE_OUTPUT = 400,
    CMD_TOGGLE_TREE,
    CMD_ABOUT = 500
};

static const MenuItem k_file[] = {
    {"New Project", "Ctrl+N", CMD_NEW_PROJECT, 0},
    {"Open Project...", "Ctrl+O", CMD_OPEN_PROJECT, 0},
    {"Open File...", "", CMD_OPEN_FILE, 0},
    {"", "", 0, 1},
    {"Save", "Ctrl+S", CMD_SAVE, 0},
    {"Save As...", "", CMD_SAVE_AS, 0},
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
    {"Find / Replace", "Ctrl+F", CMD_FIND, 0},
    {"Go to Line", "Ctrl+G", CMD_GOTO, 0},
};

static const MenuItem k_build[] = {
    {"Build", "F7", CMD_BUILD, 0},
    {"Rebuild All", "Ctrl+F7", CMD_REBUILD, 0},
    {"Clean", "", CMD_CLEAN, 0},
    {"", "", 0, 1},
    {"Package SISX", "", CMD_PACKAGE, 0},
    {"Sign Package", "", CMD_SIGN, 0},
    {"", "", 0, 1},
    {"Run", "F5", CMD_RUN, 0},
};

static const MenuItem k_view[] = {
    {"Toggle Output", "Ctrl+`", CMD_TOGGLE_OUTPUT, 0},
    {"Toggle Project Tree", "", CMD_TOGGLE_TREE, 0},
};

static const MenuItem k_help[] = {
    {"About AcetyleneC", "", CMD_ABOUT, 0},
};

typedef struct {
    const char *title;
    const MenuItem *items;
    int count;
} MenuDef;

static const MenuDef k_menus[] = {
    {"File", k_file, (int)(sizeof(k_file) / sizeof(k_file[0]))},
    {"Edit", k_edit, (int)(sizeof(k_edit) / sizeof(k_edit[0]))},
    {"Build", k_build, (int)(sizeof(k_build) / sizeof(k_build[0]))},
    {"View", k_view, (int)(sizeof(k_view) / sizeof(k_view[0]))},
    {"Help", k_help, (int)(sizeof(k_help) / sizeof(k_help[0]))},
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

static void text_at(HDC dc, int x, int y, const char *s, COLORREF c, HFONT f)
{
    HFONT old = SelectObject(dc, f);
    SetTextColor(dc, c);
    SetBkMode(dc, TRANSPARENT);
    TextOutA(dc, x, y, s, (int)strlen(s));
    SelectObject(dc, old);
}

static int text_w(HDC dc, const char *s, HFONT f)
{
    SIZE sz;
    HFONT old = SelectObject(dc, f);
    GetTextExtentPoint32A(dc, s, (int)strlen(s), &sz);
    SelectObject(dc, old);
    return sz.cx;
}

static int utf8_to_w(const char *s, int len, wchar_t *out, int max)
{
    return MultiByteToWideChar(CP_UTF8, 0, s, len, out, max);
}

static char *utf8_from_w(const wchar_t *s)
{
    int n = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
    char *out = ac_alloc((size_t)n + 1);
    WideCharToMultiByte(CP_UTF8, 0, s, -1, out, n, NULL, NULL);
    return out;
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
}

void ide_layout(void)
{
    RECT rc;
    int top = 26 + 30;
    GetClientRect(g_ide.hwnd, &rc);
    if (g_ide.split_x < 120)
        g_ide.split_x = 120;
    if (g_ide.split_x > rc.right - 300)
        g_ide.split_x = rc.right - 300;
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
    g_ide.rc_tree.right = g_ide.split_x;
    g_ide.rc_tree.bottom = rc.bottom - 22;
    g_ide.rc_tabs.left = g_ide.split_x + 1;
    g_ide.rc_tabs.top = top;
    g_ide.rc_tabs.right = rc.right;
    g_ide.rc_tabs.bottom = top + 26;
    g_ide.rc_editor.left = g_ide.split_x + 1;
    g_ide.rc_editor.top = top + 26;
    g_ide.rc_editor.right = rc.right;
    g_ide.rc_editor.bottom = g_ide.show_output ? g_ide.split_y : rc.bottom - 22;
    g_ide.rc_output.left = g_ide.split_x + 1;
    g_ide.rc_output.top = g_ide.show_output ? g_ide.split_y + 1 : rc.bottom - 22;
    g_ide.rc_output.right = rc.right;
    g_ide.rc_output.bottom = rc.bottom - 22;
    g_ide.rc_status.left = 0;
    g_ide.rc_status.top = rc.bottom - 22;
    g_ide.rc_status.right = rc.right;
    g_ide.rc_status.bottom = rc.bottom;
}

static void draw_find_bar(HDC dc);

static void draw_menu_bar(HDC dc, int w)
{
    int x = 8, i;
    fill(dc, (RECT){0, 0, w, 26}, C_PANEL);
    for (i = 0; i < k_nmenus; i++) {
        int tw = text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
        RECT r = {x, 0, x + tw, 26};
        if (g_ide.menu_index == i)
            fill(dc, r, C_PANEL2);
        text_at(dc, x + 10, 5, k_menus[i].title, g_ide.menu_index == i ? C_TEXT : C_DIM, g_ide.font_ui);
        x += tw;
    }
    {
        char title[256];
        Doc *d = doc_active();
        snprintf(title, sizeof(title), "AcetyleneC  -  %s%s", d ? d->name : "no file", d && d->modified ? " *" : "");
        text_at(dc, w - text_w(dc, title, g_ide.font_ui) - 14, 5, title, C_DIM, g_ide.font_ui);
    }
    fill(dc, (RECT){0, 25, w, 26}, C_BORDER);
}

static void draw_toolbar(HDC dc, int w)
{
    int x = 8;
    static const char *btns[] = {"Build", "Rebuild", "Package", "Sign", "Run"};
    static const int ids[] = {CMD_BUILD, CMD_REBUILD, CMD_PACKAGE, CMD_SIGN, CMD_RUN};
    int i;
    fill(dc, g_ide.rc_toolbar, C_PANEL);
    for (i = 0; i < 5; i++) {
        int tw = text_w(dc, btns[i], g_ide.font_ui) + 24;
        RECT r = {x, 31, x + tw, 51};
        fill(dc, r, (ids[i] == CMD_BUILD) ? RGB(46, 84, 122) : C_PANEL2);
        frame(dc, r, C_BORDER);
        text_at(dc, x + 12, 32, btns[i], C_TEXT, g_ide.font_ui);
        x += tw + 6;
    }
    {
        char tgt[128];
        snprintf(tgt, sizeof(tgt), "target: %s", g_ide.proj.target);
        text_at(dc, w - text_w(dc, tgt, g_ide.font_ui) - 14, 32, tgt, C_ACCENT, g_ide.font_ui);
    }
    fill(dc, (RECT){0, 55, w, 56}, C_BORDER);
}

static void draw_popup(HDC dc, int w, int h)
{
    int i, k;
    int x = 8;
    int px, wmax = 140, y;
    for (i = 0; i < g_ide.menu_index; i++)
        x += text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
    px = x;
    for (k = 0; k < k_menus[g_ide.menu_index].count; k++) {
        const MenuItem *it = &k_menus[g_ide.menu_index].items[k];
        int ww = text_w(dc, it->label, g_ide.font_ui) + text_w(dc, it->shortcut, g_ide.font_ui) + 48;
        if (it->sep)
            continue;
        if (ww > wmax)
            wmax = ww;
    }
    y = 26;
    {
        int height = 8;
        for (k = 0; k < k_menus[g_ide.menu_index].count; k++)
            height += k_menus[g_ide.menu_index].items[k].sep ? 8 : 24;
        {
            RECT r = {px, y, px + wmax, y + height};
            fill(dc, r, C_PANEL2);
            frame(dc, r, C_BORDER);
        }
        for (k = 0; k < k_menus[g_ide.menu_index].count; k++) {
            const MenuItem *it = &k_menus[g_ide.menu_index].items[k];
            RECT r = {px + 1, y + 4, px + wmax - 1, y + 4 + 24};
            if (it->sep) {
                fill(dc, (RECT){px + 8, y + 8, px + wmax - 8, y + 9}, C_BORDER);
                y += 8;
                continue;
            }
            if (g_ide.menu_hover == k)
                fill(dc, r, C_SEL);
            text_at(dc, px + 12, y + 7, it->label, C_TEXT, g_ide.font_ui);
            if (it->shortcut[0])
                text_at(dc, px + wmax - text_w(dc, it->shortcut, g_ide.font_ui) - 12, y + 7, it->shortcut, C_DIM, g_ide.font_ui);
            y += 24;
        }
    }
    (void)w;
    (void)h;
}

static void draw_tree(HDC dc)
{
    RECT r = g_ide.rc_tree;
    int y = r.top + 6;
    int i;
    int pad = 6;
    fill(dc, r, C_PANEL);
    text_at(dc, r.left + 10, y, g_ide.proj.name, C_TEXT, g_ide.font_bold);
    y += 24;
    text_at(dc, r.left + 10, y, g_ide.proj.target, C_DIM, g_ide.font_ui);
    y += 20;
    fill(dc, (RECT){r.left + 8, y, r.right - 8, y + 1}, C_BORDER);
    y += 8;
    for (i = 0; i < g_ide.tree_files.count; i++) {
        RECT ir = {r.left + 4, y, r.right - 4, y + 20};
        const char *p = g_ide.tree_files.items[i];
        if (i == g_ide.tree_sel)
            fill(dc, ir, C_SEL);
        text_at(dc, r.left + 14, y + 2, ac_basename(p), i == g_ide.tree_sel ? C_TEXT : C_DIM, g_ide.font_ui);
        y += 20;
    }
    fill(dc, (RECT){r.right, r.top, r.right + 1, r.bottom}, C_BORDER);
}

static void draw_tabs(HDC dc)
{
    int x = g_ide.rc_tabs.left + 2;
    int i;
    fill(dc, g_ide.rc_tabs, C_PANEL);
    for (i = 0; i < g_ide.ndocs; i++) {
        Doc *d = &g_ide.docs[i];
        char label[300];
        int tw;
        RECT r;
        snprintf(label, sizeof(label), "%s%s", d->name, d->modified ? " *" : "");
        tw = text_w(dc, label, g_ide.font_ui) + 28;
        r = (RECT){x, g_ide.rc_tabs.top + 2, x + tw, g_ide.rc_tabs.bottom - 1};
        if (i == g_ide.active) {
            fill(dc, r, C_BG);
            fill(dc, (RECT){r.left, r.top, r.right, r.top + 2}, C_ACCENT);
        }
        text_at(dc, x + 10, r.top + 5, label, i == g_ide.active ? C_TEXT : C_DIM, g_ide.font_ui);
        text_at(dc, x + tw - 18, r.top + 5, "x", C_DIM, g_ide.font_ui);
        x += tw + 2;
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

static void draw_editor(HDC dc)
{
    Doc *d = doc_active();
    RECT r = g_ide.rc_editor;
    int gutter = 52;
    int x0 = r.left + gutter;
    int y = r.top + 2;
    int i;
    int visible;
    int sel_a = 0, sel_b = 0;
    int has_sel;

    fill(dc, r, C_BG);
    fill(dc, (RECT){r.left, r.top, r.left + gutter, r.bottom}, C_GUTTER);
    fill(dc, (RECT){r.left + gutter, r.top, r.left + gutter + 1, r.bottom}, C_BORDER);
    if (!d) {
        text_at(dc, r.left + 24, r.top + 24, "No file open. Use File > Open File, or create a project.", C_DIM, g_ide.font_ui);
        return;
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
        int k;
        if (line >= d->nlines)
            break;
        start = d->lines[line];
        end = doc_line_end(d, line);
        len = end - start;
        snprintf(ln, sizeof(ln), "%d", line + 1);
        text_at(dc, r.left + gutter - 8 - text_w(dc, ln, g_ide.font), y, ln, C_GUTTERTXT, g_ide.font);

        if (has_sel && sel_b > start && sel_a < end) {
            int sx = sel_a > start ? sel_a : start;
            int ex = sel_b < end ? sel_b : end;
            int c1 = 0, c2 = 0;
            int q;
            for (q = start; q < sx; q++)
                c1 += (d->data.data[q] == '\t') ? TAB_WIDTH - (c1 % TAB_WIDTH) : 1;
            c2 = c1;
            for (q = sx; q < ex; q++)
                c2 += (d->data.data[q] == '\t') ? TAB_WIDTH - (c2 % TAB_WIDTH) : 1;
            fill(dc, (RECT){x0 + c1 * g_ide.char_w - d->scroll_x, y, x0 + c2 * g_ide.char_w - d->scroll_x, y + g_ide.line_h}, C_SEL);
        }

        if (len > 0) {
            int cx = x0 - d->scroll_x;
            int col = 0;
            doc_highlight(d, line, spans, 512, &nspans);
            for (k = 0; k < len; k++) {
                char ch = d->data.data[start + k];
                int w = 1;
                if (ch == '\t') {
                    w = TAB_WIDTH - (col % TAB_WIDTH);
                    col += w;
                    continue;
                }
                {
                    TokKind kind = TK_PLAIN;
                    int s;
                    for (s = 0; s < nspans; s++) {
                        if (k >= spans[s].start && k < spans[s].start + spans[s].len) {
                            kind = spans[s].kind;
                            break;
                        }
                    }
                    {
                        char one[2] = {ch, 0};
                        text_at(dc, cx + col * g_ide.char_w, y, one, tok_color(kind), g_ide.font);
                    }
                }
                col++;
            }
        }
        y += g_ide.line_h;
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
    if (g_ide.show_output)
        draw_output(mem);
    draw_find_bar(mem);
    draw_status(mem, w);
    if (g_ide.menu_index >= 0)
        draw_popup(mem, w, h);

    BitBlt(dc, 0, 0, w, h, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteObject(bmp);
    DeleteDC(mem);
}

static void ide_command(int cmd);

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
    int px = 8, wmax = 140, py = 26;
    HDC dc;
    if (g_ide.menu_index < 0)
        return 0;
    dc = GetDC(g_ide.hwnd);
    for (i = 0; i < g_ide.menu_index; i++)
        px += text_w(dc, k_menus[i].title, g_ide.font_ui) + 20;
    for (k = 0; k < k_menus[g_ide.menu_index].count; k++) {
        const MenuItem *it = &k_menus[g_ide.menu_index].items[k];
        int ww;
        if (it->sep)
            continue;
        ww = text_w(dc, it->label, g_ide.font_ui) + text_w(dc, it->shortcut, g_ide.font_ui) + 48;
        if (ww > wmax)
            wmax = ww;
    }
    ReleaseDC(g_ide.hwnd, dc);
    for (k = 0; k < k_menus[g_ide.menu_index].count; k++) {
        const MenuItem *it = &k_menus[g_ide.menu_index].items[k];
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
    ofn.lpstrFilter = "All Files\0*.*\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
    if (GetSaveFileNameA(&ofn))
        ide_save_file(index, 0);
}

void ide_open_file(const char *path)
{
    int i;
    Buf b;
    Doc *d;
    for (i = 0; i < g_ide.ndocs; i++) {
        if (g_ide.docs[i].path && strcmp(g_ide.docs[i].path, path) == 0) {
            g_ide.active = i;
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
    }
    d->lex_lang = ac_has_ext(path, ".c") || ac_has_ext(path, ".h") || ac_has_ext(path, ".cpp");
    g_ide.active = g_ide.ndocs;
    g_ide.ndocs++;
    g_ide.tree_sel = g_ide.tree_files.count;
    sv_push(&g_ide.tree_files, path);
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
        ide_set_status("Saved %s (%d bytes)", d->name, (int)d->data.len);
    } else {
        ide_set_status("ERROR: cannot write %s", d->path);
    }
}

void ide_close_file(int index)
{
    int i;
    if (index < 0 || index >= g_ide.ndocs)
        return;
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

static void do_find(void)
{
    Doc *d = doc_active();
    int at;
    if (!d || !g_ide.find_text[0])
        return;
    at = find_next_from(d, d->caret + (doc_has_selection(d) ? 1 : 0));
    if (at < 0)
        at = find_next_from(d, 0);
    if (at < 0) {
        ide_set_status("not found: %s", g_ide.find_text);
        return;
    }
    d->anchor = at;
    d->caret = at + (int)strlen(g_ide.find_text);
    d->sel_active = 1;
    d->caret = at;
    d->sel_active = 1;
    d->anchor = at + (int)strlen(g_ide.find_text);
    doc_scroll_to_caret(d);
    ide_set_status("found at offset %d", at);
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
        snprintf(shown, sizeof(shown), "%s", g_ide.find_text);
        text_at(dc, box.left + 8 + lw + 6, box.top + 5, shown, C_TEXT, g_ide.font_ui);
        if (g_ide.blink_on) {
            int tw = text_w(dc, shown, g_ide.font_ui);
            fill(dc, (RECT){box.left + 8 + lw + 6 + tw, box.top + 6, box.left + 9 + lw + 6 + tw, box.top + 20}, C_TEXT);
        }
    }
    text_at(dc, box.left + 8, box.top + 18, "", C_DIM, g_ide.font_ui);
}

void ide_find(void)
{
    g_ide.find_open = 1;
    g_ide.find_focus = 0;
    g_ide.find_text[0] = 0;
    ide_set_status("type to search, Enter = next, Esc = close");
}

static int run_capture(const char *cmd, char *log, size_t logcap)
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

static void join_path(char *out, size_t cap, const char *a, const char *b)
{
    snprintf(out, cap, "%s/%s", a, b);
}

static void add_msg(const char *fmt, ...)
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
    ide_set_status("Build OK: %s", e32_file);
}

void ide_build(void)
{
    g_ide.building = 1;
    ide_set_status("Building...");
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
    UpdateWindow(g_ide.hwnd);
    run_build_pipeline();
    g_ide.building = 0;
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

static void ide_command(int cmd)
{
    Doc *d = doc_active();
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
        ide_set_status("Packaging: configure a .pkg in the project, then Build > Package SISX");
        break;
    case CMD_SIGN:
        ide_set_status("Signing: run acetylene-makekeys once, then acetylene-sign (see Help > About)");
        break;
    case CMD_RUN:
        ide_set_status("Run: build first; device binary is written to build\\");
        break;
    case CMD_CLEAN:
        ide_set_status("Clean: delete the build folder manually for now");
        break;
    case CMD_TOGGLE_OUTPUT:
        g_ide.show_output = !g_ide.show_output;
        ide_layout();
        break;
    case CMD_TOGGLE_TREE:
        g_ide.split_x = g_ide.split_x > 10 ? 0 : 220;
        ide_layout();
        break;
    case CMD_ABOUT:
        MessageBoxA(g_ide.hwnd,
                    "AcetyleneC 1.0\n\nUnofficial Symbian S60 SDK IDE (S60v2..S60v5)\n"
                    "C compiler: inside-tcc (ARM EABI)\n"
                    "Linker: acetylene-ld\n"
                    "Signing: acetylene-makekeys / acetylene-sign\n\n"
                    "Kirill / kirill670",
                    "About AcetyleneC", MB_OK | MB_ICONINFORMATION);
        break;
    default:
        break;
    }
    InvalidateRect(g_ide.hwnd, NULL, FALSE);
}

int ide_key(int vk, int ctrl, int shift, int alt)
{
    Doc *d = doc_active();
    if (g_ide.find_open) {
        if (vk == VK_ESCAPE) {
            g_ide.find_open = 0;
            return 1;
        }
        if (vk == VK_RETURN) {
            if (g_ide.find_focus)
                do_goto();
            else
                do_find();
            return 1;
        }
        if (vk == VK_BACK) {
            size_t n = strlen(g_ide.find_text);
            if (n)
                g_ide.find_text[n - 1] = 0;
            return 1;
        }
        return 1;
    }
    if (ctrl && vk == 'S') {
        ide_command(CMD_SAVE);
        return 1;
    }
    if (ctrl && vk == 'O') {
        ide_command(CMD_OPEN_FILE);
        return 1;
    }
    if (ctrl && vk == 'N') {
        ide_command(CMD_NEW_PROJECT);
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
    if (ctrl && vk == 'F') {
        ide_command(CMD_FIND);
        return 1;
    }
    if (ctrl && vk == 'G') {
        ide_command(CMD_GOTO);
        return 1;
    }
    if (vk == VK_F7) {
        ide_command(shift ? CMD_REBUILD : CMD_BUILD);
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
        int ls = doc_line_start(d, doc_line_of(d, d->caret));
        if (ctrl)
            doc_set_caret(d, 0, shift);
        else
            doc_set_caret(d, ls, shift);
        return 1;
    }
    case VK_END: {
        int le = doc_line_end(d, doc_line_of(d, d->caret));
        if (ctrl)
            doc_set_caret(d, (int)d->data.len, shift);
        else
            doc_set_caret(d, le, shift);
        return 1;
    }
    case VK_PRIOR: {
        int visible = (g_ide.rc_editor.bottom - g_ide.rc_editor.top) / g_ide.line_h;
        d->top_line -= visible;
        if (d->top_line < 0)
            d->top_line = 0;
        return 1;
    }
    case VK_NEXT: {
        int visible = (g_ide.rc_editor.bottom - g_ide.rc_editor.top) / g_ide.line_h;
        if (d->top_line + visible < d->nlines)
            d->top_line += visible;
        return 1;
    }
    case VK_BACK:
        if (doc_has_selection(d)) {
            int a, b;
            doc_sel_range(d, &a, &b);
            doc_delete(d, a, b - a);
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
        } else if (d->caret < (int)d->data.len) {
            doc_delete(d, d->caret, 1);
        }
        return 1;
    case VK_RETURN: {
        int ls = doc_line_start(d, doc_line_of(d, d->caret));
        int indent = 0;
        while (ls + indent < (int)d->data.len && d->data.data[ls + indent] == '\t')
            indent++;
        {
            char nl[64];
            int n = 0;
            nl[n++] = '\n';
            while (indent-- > 0 && n < 60)
                nl[n++] = '\t';
            doc_insert(d, d->caret, nl, n);
        }
        doc_scroll_to_caret(d);
        return 1;
    }
    case VK_TAB: {
        if (doc_has_selection(d)) {
            int a, b;
            doc_sel_range(d, &a, &b);
            doc_delete(d, a, b - a);
        }
        doc_insert(d, d->caret, "\t", 1);
        return 1;
    }
    case VK_ESCAPE:
        g_ide.menu_index = -1;
        g_ide.find_open = 0;
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
        if (ch >= 32 && ch < 127 && len < sizeof(g_ide.find_text) - 1) {
            g_ide.find_text[len] = (char)ch;
            g_ide.find_text[len + 1] = 0;
        }
        return;
    }
    if (!d)
        return;
    if (ch < 32 && ch != '\t')
        return;
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
}

void ide_mouse_down(int x, int y, int shift, int button)
{
    int mi;
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
            int cmd = k_menus[g_ide.menu_index].items[item].cmd;
            g_ide.menu_index = -1;
            ide_command(cmd);
            return;
        }
        g_ide.menu_index = -1;
    }
    if (y >= 31 && y <= 51) {
        int bx = 8, i;
        static const int ids[] = {CMD_BUILD, CMD_REBUILD, CMD_PACKAGE, CMD_SIGN, CMD_RUN};
        static const char *btns[] = {"Build", "Rebuild", "Package", "Sign", "Run"};
        HDC dc = GetDC(g_ide.hwnd);
        for (i = 0; i < 5; i++) {
            int tw = text_w(dc, btns[i], g_ide.font_ui) + 24;
            if (x >= bx && x < bx + tw) {
                ReleaseDC(g_ide.hwnd, dc);
                ide_command(ids[i]);
                return;
            }
            bx += tw + 6;
        }
        ReleaseDC(g_ide.hwnd, dc);
    }
    if (PtInRect(&g_ide.rc_tabs, (POINT){x, y})) {
        int tx = g_ide.rc_tabs.left + 2;
        int i;
        HDC dc = GetDC(g_ide.hwnd);
        for (i = 0; i < g_ide.ndocs; i++) {
            char label[300];
            int tw;
            snprintf(label, sizeof(label), "%s%s", g_ide.docs[i].name, g_ide.docs[i].modified ? " *" : "");
            tw = text_w(dc, label, g_ide.font_ui) + 28;
            if (x >= tx && x < tx + tw) {
                ReleaseDC(g_ide.hwnd, dc);
                if (x >= tx + tw - 20)
                    ide_close_file(i);
                else
                    g_ide.active = i;
                InvalidateRect(g_ide.hwnd, NULL, FALSE);
                return;
            }
            tx += tw + 2;
        }
        ReleaseDC(g_ide.hwnd, dc);
        return;
    }
    if (PtInRect(&g_ide.rc_tree, (POINT){x, y})) {
        int row = (y - g_ide.rc_tree.top - 56) / 20;
        if (row >= 0 && row < g_ide.tree_files.count) {
            g_ide.tree_sel = row;
            ide_open_file(g_ide.tree_files.items[row]);
        }
        return;
    }
    if (abs(x - g_ide.split_x) <= 3 && y > g_ide.rc_toolbar.bottom) {
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
            doc_set_caret(d, doc_hit_test(d, x - g_ide.rc_editor.left - 52, y - g_ide.rc_editor.top - 2), shift);
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
    if (g_ide.dragging_split) {
        g_ide.dragging_split = 0;
        ReleaseCapture();
    } else {
        ReleaseCapture();
    }
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
    if (buttons & 1) {
        Doc *d = doc_active();
        if (d && PtInRect(&g_ide.rc_editor, (POINT){x, y})) {
            doc_set_caret(d, doc_hit_test(d, x - g_ide.rc_editor.left - 52, y - g_ide.rc_editor.top - 2), 1);
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
        }
    }
    if (g_ide.menu_index >= 0) {
        int item = -1;
        if (menu_item_hit(x, y, &item) && g_ide.menu_hover != item) {
            g_ide.menu_hover = item;
            InvalidateRect(g_ide.hwnd, NULL, FALSE);
        }
    }
}

void ide_wheel(int delta, int ctrl)
{
    Doc *d = doc_active();
    if (!d)
        return;
    if (ctrl) {
        d->scroll_x -= delta / 40;
        if (d->scroll_x < 0)
            d->scroll_x = 0;
    } else if (g_ide.show_output && g_ide.nmsgs == 0) {
        g_ide.output_scroll -= delta / 120;
        if (g_ide.output_scroll < 0)
            g_ide.output_scroll = 0;
    } else {
        d->top_line -= delta / 120;
        if (d->top_line < 0)
            d->top_line = 0;
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
    case WM_LBUTTONUP:
        ide_mouse_up((short)LOWORD(lp), (short)HIWORD(lp));
        return 0;
    case WM_MOUSEMOVE:
        ide_mouse_move((short)LOWORD(lp), (short)HIWORD(lp), (int)wp);
        return 0;
    case WM_MOUSEWHEEL: {
        int delta = GET_WHEEL_DELTA_WPARAM(wp);
        ide_wheel(delta, (GET_KEYSTATE_WPARAM(wp) & MK_CONTROL) != 0);
        return 0;
    }
    case WM_SETCURSOR:
        {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hwnd, &p);
            if (abs(p.x - g_ide.split_x) <= 3 && p.y > g_ide.rc_toolbar.bottom) {
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

void ide_open_project(const char *path)
{
    Buf b;
    char *p;
    if (ac_read_file(path, &b) != 0)
        return;
    buf_put(&b, "", 1);
    snprintf(g_ide.proj.project_path, sizeof(g_ide.proj.project_path), "%s", path);
    sv_free(&g_ide.proj.sources);
    sv_init(&g_ide.proj.sources);
    sv_free(&g_ide.proj.libs);
    sv_init(&g_ide.proj.libs);
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
                sv_push(&g_ide.proj.sources, eq + 1);
                {
                    char full[MAX_PATH];
                    if (eq[1] && eq[2] == ':')
                        sv_push(&g_ide.tree_files, eq + 1);
                    else {
                        const char *dir = path;
                        char base[MAX_PATH];
                        int i;
                        snprintf(base, sizeof(base), "%s", dir);
                        for (i = (int)strlen(base); i > 0 && base[i] != '\\'; i--)
                            base[i] = 0;
                        snprintf(full, sizeof(full), "%s%s", base, eq + 1);
                        sv_push(&g_ide.tree_files, full);
                    }
                }
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
