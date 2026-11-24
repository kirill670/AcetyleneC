#include "ide.h"
#include <ctype.h>

static const char *k_keywords[] = {
    "if", "else", "for", "while", "do", "switch", "case", "default", "break", "continue",
    "return", "goto", "sizeof", "typedef", "struct", "union", "enum", "extern", "static",
    "const", "volatile", "register", "auto", "inline", "void", "char", "short", "int",
    "long", "float", "double", "signed", "unsigned", "_Bool", "class", "public", "private",
    "protected", "virtual", "override", "new", "delete", "this", "namespace", "using",
    "template", "typename", "try", "catch", "throw", "operator", "friend", "explicit",
    "mutable", "const_cast", "static_cast", "reinterpret_cast", "dynamic_cast", "nullptr",
    "true", "false", "IMPORT_C", "EXPORT_C", "GLDEF_C", "GLREF_C", "LOCAL_C", "NONSHARABLE_CLASS",
    "IMPORT_CDECL", "TInt", "TUint", "TBool", "TChar", "TReal", "TText8", "TText16",
    "TDesC", "TDes", "TBuf", "TPtr", "TPtrC", "HBufC", "RBuf", "CBufBase",
    "CBase", "CActive", "CArrayFix", "CArrayPtr", "RArray", "RPointerArray",
    "TRequestStatus", "RSessionBase", "RServer2", "TVersion", "TSecurityPolicy",
    "User", "RProcess", "RThread", "RHeap", "RFs", "RFile", "RDir",
    "TTime", "TTimeIntervalMicroSeconds", "TPoint", "TSize", "TRect",
    "MActive", "MObjectProvider", "CCoeControl", "CAknAppUi", "CEikAppUi",
    "CAknViewAppUi", "CAknDocument", "CAknApplication", "CAknView",
    "HandleCommandL", "ConstructL", "NewL", "NewLC", "TUid", "TInt64", "TUint64",
    "EBoolTrue", "EBoolFalse", "ETrue", "EFalse", "KErrNone", "KErrNotFound",
    "NULL", "MAP_SYMBIAN", "SYMBIAN", "__declspec", "__asm__", "__attribute__",
};
static const int k_nkeywords = (int)(sizeof(k_keywords) / sizeof(k_keywords[0]));

static int is_ident_start(int c) { return isalpha(c) || c == '_' || c == '$'; }
static int is_ident_char(int c) { return isalnum(c) || c == '_' || c == '$'; }

void doc_init(Doc *d, const char *path)
{
    memset(d, 0, sizeof(*d));
    buf_init(&d->data);
    if (path) {
        d->path = ac_strdup(path);
        {
            const char *b = ac_basename(path);
            d->name = ac_strdup(b);
        }
    } else {
        d->path = NULL;
        d->name = ac_strdup("untitled");
    }
    doc_reindex(d);
}

void doc_free(Doc *d)
{
    int i;
    free(d->path);
    free(d->name);
    buf_free(&d->data);
    free(d->lines);
    free(d->bstate);
    for (i = 0; i < d->undo_count; i++)
        free(d->undo[i].text);
    free(d->undo);
    memset(d, 0, sizeof(*d));
}

void doc_reindex(Doc *d)
{
    int i, n = 1;
    int in_block = 0;
    size_t pos;
    free(d->lines);
    free(d->bstate);
    for (i = 0; i < (int)d->data.len; i++)
        if (d->data.data[i] == '\n')
            n++;
    d->lines = ac_calloc((size_t)n + 1, sizeof(int));
    d->bstate = ac_calloc((size_t)n + 1, sizeof(int));
    d->nlines = n;
    d->lines[0] = 0;
    n = 1;
    for (i = 0; i < (int)d->data.len; i++)
        if (d->data.data[i] == '\n')
            d->lines[n++] = i + 1;
    d->lines[d->nlines] = (int)d->data.len;
    pos = 0;
    for (i = 0; i < d->nlines; i++) {
        int start = d->lines[i];
        int end = (i + 1 < d->nlines) ? d->lines[i + 1] - 1 : (int)d->data.len;
        int j = start;
        d->bstate[i] = in_block;
        while (j < end) {
            if (in_block) {
                if (d->data.data[j] == '*' && j + 1 < end && d->data.data[j + 1] == '/') {
                    in_block = 0;
                    j += 2;
                    continue;
                }
                j++;
            } else {
                if (d->data.data[j] == '/' && j + 1 < end && d->data.data[j + 1] == '/')
                    break;
                if (d->data.data[j] == '/' && j + 1 < end && d->data.data[j + 1] == '*') {
                    in_block = 1;
                    j += 2;
                    continue;
                }
                if (d->data.data[j] == '"' || d->data.data[j] == '\'') {
                    char q = d->data.data[j];
                    j++;
                    while (j < end) {
                        if (d->data.data[j] == '\\') {
                            j += 2;
                            continue;
                        }
                        if (d->data.data[j] == q) {
                            j++;
                            break;
                        }
                        j++;
                    }
                    continue;
                }
                j++;
            }
        }
    }
    (void)pos;
}

static void undo_push(Doc *d, int op, int pos, int len, const char *text, int before, int after)
{
    if (d->undo_pos < d->undo_count) {
        int i;
        for (i = d->undo_pos; i < d->undo_count; i++)
            free(d->undo[i].text);
        d->undo_count = d->undo_pos;
    }
    d->undo = ac_realloc(d->undo, sizeof(UndoRec) * (size_t)(d->undo_count + 1));
    d->undo[d->undo_count].op = op;
    d->undo[d->undo_count].pos = pos;
    d->undo[d->undo_count].len = len;
    d->undo[d->undo_count].text = text ? ac_strdup(text) : NULL;
    d->undo[d->undo_count].caret_before = before;
    d->undo[d->undo_count].caret_after = after;
    d->undo_count++;
    d->undo_pos = d->undo_count;
    if (d->undo_count > 500) {
        int i;
        free(d->undo[0].text);
        memmove(d->undo, d->undo + 1, sizeof(UndoRec) * (size_t)(d->undo_count - 1));
        d->undo_count--;
        d->undo_pos--;
        (void)i;
    }
}

void doc_insert(Doc *d, int pos, const char *text, int len)
{
    if (len <= 0)
        return;
    if (pos < 0)
        pos = 0;
    if (pos > (int)d->data.len)
        pos = (int)d->data.len;
    buf_reserve(&d->data, (size_t)len);
    memmove(d->data.data + pos + len, d->data.data + pos, d->data.len - (size_t)pos);
    memcpy(d->data.data + pos, text, (size_t)len);
    d->data.len += (size_t)len;
    undo_push(d, 1, pos, len, text, d->caret, pos + len);
    doc_reindex(d);
    d->modified = 1;
    d->caret = pos + len;
    d->anchor = d->caret;
    d->sel_active = 0;
    plugins_doc_changed();
}

void doc_delete(Doc *d, int pos, int len)
{
    char *tmp;
    if (len <= 0)
        return;
    if (pos < 0)
        pos = 0;
    if (pos + len > (int)d->data.len)
        len = (int)d->data.len - pos;
    if (len <= 0)
        return;
    tmp = ac_alloc((size_t)len + 1);
    memcpy(tmp, d->data.data + pos, (size_t)len);
    tmp[len] = 0;
    memmove(d->data.data + pos, d->data.data + pos + len, d->data.len - (size_t)pos - (size_t)len);
    d->data.len -= (size_t)len;
    undo_push(d, 0, pos, len, tmp, d->caret, pos);
    free(tmp);
    doc_reindex(d);
    d->modified = 1;
    d->caret = pos;
    d->anchor = d->caret;
    d->sel_active = 0;
    plugins_doc_changed();
}

void doc_undo(Doc *d)
{
    UndoRec *r;
    if (d->undo_pos <= 0)
        return;
    r = &d->undo[d->undo_pos - 1];
    if (r->op == 1) {
        memmove(d->data.data + r->pos, d->data.data + r->pos + r->len, d->data.len - (size_t)r->pos - (size_t)r->len);
        d->data.len -= (size_t)r->len;
        d->caret = r->caret_before;
    } else {
        buf_reserve(&d->data, (size_t)r->len);
        memmove(d->data.data + r->pos + r->len, d->data.data + r->pos, d->data.len - (size_t)r->pos);
        memcpy(d->data.data + r->pos, r->text, (size_t)r->len);
        d->data.len += (size_t)r->len;
        d->caret = r->caret_before;
    }
    d->anchor = d->caret;
    d->sel_active = 0;
    d->undo_pos--;
    doc_reindex(d);
    d->modified = 1;
}

void doc_redo(Doc *d)
{
    UndoRec *r;
    if (d->undo_pos >= d->undo_count)
        return;
    r = &d->undo[d->undo_pos];
    if (r->op == 1) {
        buf_reserve(&d->data, (size_t)r->len);
        memmove(d->data.data + r->pos + r->len, d->data.data + r->pos, d->data.len - (size_t)r->pos);
        memcpy(d->data.data + r->pos, r->text, (size_t)r->len);
        d->data.len += (size_t)r->len;
    } else {
        memmove(d->data.data + r->pos, d->data.data + r->pos + r->len, d->data.len - (size_t)r->pos - (size_t)r->len);
        d->data.len -= (size_t)r->len;
    }
    d->caret = r->caret_after;
    d->anchor = d->caret;
    d->sel_active = 0;
    d->undo_pos++;
    doc_reindex(d);
    d->modified = 1;
}

int doc_line_of(Doc *d, int pos)
{
    int lo = 0, hi = d->nlines - 1;
    if (pos <= 0)
        return 0;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (d->lines[mid] <= pos)
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

int doc_line_start(Doc *d, int line)
{
    if (line < 0)
        line = 0;
    if (line >= d->nlines)
        line = d->nlines - 1;
    return d->lines[line];
}

int doc_line_end(Doc *d, int line)
{
    int e;
    if (line < 0)
        line = 0;
    if (line >= d->nlines)
        line = d->nlines - 1;
    e = (line + 1 < d->nlines) ? d->lines[line + 1] - 1 : (int)d->data.len;
    while (e > d->lines[line] && (d->data.data[e - 1] == '\r' || d->data.data[e - 1] == '\n'))
        e--;
    return e;
}

int doc_col_of(Doc *d, int pos)
{
    int line = doc_line_of(d, pos);
    int start = d->lines[line];
    int col = 0, i;
    for (i = start; i < pos && i < (int)d->data.len; i++) {
        if (d->data.data[i] == '\t')
            col += TAB_WIDTH - (col % TAB_WIDTH);
        else
            col++;
    }
    return col;
}

int doc_pos_from_col(Doc *d, int line, int col)
{
    int start = doc_line_start(d, line);
    int end = doc_line_end(d, line);
    int c = 0, i;
    for (i = start; i < end; i++) {
        int w = (d->data.data[i] == '\t') ? TAB_WIDTH - (c % TAB_WIDTH) : 1;
        if (c + w > col)
            return i;
        c += w;
    }
    return end;
}

int doc_hit_test(Doc *d, int x, int y)
{
    int line;
    int col;
    if (!g_ide.line_h || !g_ide.char_w)
        return d->caret;
    line = d->top_line + y / g_ide.line_h;
    if (line < 0)
        line = 0;
    if (line >= d->nlines)
        line = d->nlines - 1;
    col = (x + d->scroll_x) / g_ide.char_w;
    if (col < 0)
        col = 0;
    return doc_pos_from_col(d, line, col);
}

void doc_set_caret(Doc *d, int pos, int extend)
{
    if (pos < 0)
        pos = 0;
    if (pos > (int)d->data.len)
        pos = (int)d->data.len;
    if (!extend) {
        d->caret = pos;
        d->anchor = pos;
        d->sel_active = 0;
    } else {
        if (!d->sel_active)
            d->anchor = d->caret;
        d->caret = pos;
        d->sel_active = 1;
        if (d->anchor == d->caret)
            d->sel_active = 0;
    }
}

void doc_sel_range(Doc *d, int *a, int *b)
{
    int s = d->anchor, e = d->caret;
    if (s > e) {
        int t = s;
        s = e;
        e = t;
    }
    *a = s;
    *b = e;
}

int doc_has_selection(Doc *d)
{
    return d->sel_active && d->anchor != d->caret;
}

void doc_select_all(Doc *d)
{
    d->anchor = 0;
    d->caret = (int)d->data.len;
    d->sel_active = 1;
}

void doc_copy(Doc *d)
{
    int a, b;
    if (!doc_has_selection(d))
        return;
    doc_sel_range(d, &a, &b);
    if (OpenClipboard(g_ide.hwnd)) {
        HGLOBAL h;
        EmptyClipboard();
        h = GlobalAlloc(GMEM_MOVEABLE, (SIZE_T)(b - a + 1));
        if (h) {
            char *p = GlobalLock(h);
            memcpy(p, d->data.data + a, (size_t)(b - a));
            p[b - a] = 0;
            GlobalUnlock(h);
            SetClipboardData(CF_TEXT, h);
        }
        CloseClipboard();
    }
}

void doc_cut(Doc *d)
{
    int a, b;
    if (!doc_has_selection(d))
        return;
    doc_sel_range(d, &a, &b);
    doc_copy(d);
    doc_delete(d, a, b - a);
}

void doc_paste(Doc *d)
{
    if (OpenClipboard(g_ide.hwnd)) {
        HANDLE h = GetClipboardData(CF_TEXT);
        if (h) {
            char *p = GlobalLock(h);
            if (p) {
                int len = (int)strlen(p);
                if (doc_has_selection(d)) {
                    int a, b;
                    doc_sel_range(d, &a, &b);
                    doc_delete(d, a, b - a);
                }
                doc_insert(d, d->caret, p, len);
                GlobalUnlock(h);
            }
        }
        CloseClipboard();
    }
}

void doc_scroll_to_caret(Doc *d)
{
    int line = doc_line_of(d, d->caret);
    int visible;
    if (!g_ide.line_h)
        return;
    visible = (g_ide.rc_editor.bottom - g_ide.rc_editor.top) / g_ide.line_h;
    if (visible < 1)
        visible = 1;
    if (line < d->top_line)
        d->top_line = line;
    if (line >= d->top_line + visible)
        d->top_line = line - visible + 1;
    if (d->top_line < 0)
        d->top_line = 0;
}

static int kw_lookup(const char *s, int len)
{
    int i;
    for (i = 0; i < k_nkeywords; i++) {
        if ((int)strlen(k_keywords[i]) == len && memcmp(k_keywords[i], s, (size_t)len) == 0)
            return 1;
    }
    return 0;
}

void doc_highlight(Doc *d, int line, Span *out, int max, int *count)
{
    int n = 0;
    int start = d->lines[line];
    int end = (line + 1 < d->nlines) ? d->lines[line + 1] - 1 : (int)d->data.len;
    int i = start;
    const char *p = (const char *)d->data.data;
    int in_block = d->bstate[line];
    int first = 1;
    while (i < end && n < max) {
        if (in_block) {
            int s = i;
            while (i < end) {
                if (p[i] == '*' && i + 1 < end && p[i + 1] == '/') {
                    i += 2;
                    in_block = 0;
                    break;
                }
                i++;
            }
            out[n].start = s - start;
            out[n].len = i - s;
            out[n].kind = TK_COMMENT;
            n++;
            continue;
        }
        if (p[i] == '/' && i + 1 < end && p[i + 1] == '/') {
            out[n].start = i - start;
            out[n].len = end - i;
            out[n].kind = TK_COMMENT;
            n++;
            i = end;
            continue;
        }
        if (p[i] == '/' && i + 1 < end && p[i + 1] == '*') {
            int s = i;
            i += 2;
            in_block = 1;
            while (i < end) {
                if (p[i] == '*' && i + 1 < end && p[i + 1] == '/') {
                    i += 2;
                    in_block = 0;
                    break;
                }
                i++;
            }
            out[n].start = s - start;
            out[n].len = i - s;
            out[n].kind = TK_COMMENT;
            n++;
            continue;
        }
        if (p[i] == '#' && first) {
            out[n].start = i - start;
            out[n].len = end - i;
            out[n].kind = TK_PREPROC;
            n++;
            i = end;
            continue;
        }
        if (p[i] == '"' || p[i] == '\'') {
            char q = p[i];
            int s = i;
            i++;
            while (i < end) {
                if (p[i] == '\\') {
                    i += 2;
                    continue;
                }
                if (p[i] == q) {
                    i++;
                    break;
                }
                i++;
            }
            out[n].start = s - start;
            out[n].len = i - s;
            out[n].kind = TK_STRING;
            n++;
            continue;
        }
        if (isdigit((unsigned char)p[i])) {
            int s = i;
            while (i < end && (isalnum((unsigned char)p[i]) || p[i] == '.' || p[i] == '_'))
                i++;
            out[n].start = s - start;
            out[n].len = i - s;
            out[n].kind = TK_NUMBER;
            n++;
            continue;
        }
        if (is_ident_start((unsigned char)p[i])) {
            int s = i;
            int k;
            int isfn = 0;
            while (i < end && is_ident_char((unsigned char)p[i]))
                i++;
            for (k = i; k < end; k++) {
                if (p[k] == ' ' || p[k] == '\t')
                    continue;
                isfn = (p[k] == '(');
                break;
            }
            out[n].start = s - start;
            out[n].len = i - s;
            if (kw_lookup(p + s, i - s))
                out[n].kind = TK_KEYWORD;
            else if (isfn)
                out[n].kind = TK_FUNC;
            else
                out[n].kind = TK_PLAIN;
            n++;
            continue;
        }
        if (strchr("+-*/%=<>!&|^~?:;,.()[]{}", p[i])) {
            out[n].start = i - start;
            out[n].len = 1;
            out[n].kind = TK_OPERATOR;
            n++;
            i++;
            continue;
        }
        i++;
        first = 0;
    }
    *count = n;
}
