#include "../../include/ac_plugin.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

static const AcHostApi *H;

typedef struct {
    const char *p;
    const char *end;
    int line;
    int col;
    int errors;
    char msg[128];
} J;

static void j_error(J *j, const char *msg)
{
    if (j->errors == 0)
        snprintf(j->msg, sizeof(j->msg), "%s", msg);
    j->errors++;
}

static void j_ws(J *j)
{
    while (j->p < j->end) {
        char c = *j->p;
        if (c == 10) {
            j->line++;
            j->col = 0;
            j->p++;
        } else if (c == 32 || c == 9 || c == 13) {
            j->col++;
            j->p++;
        } else {
            break;
        }
    }
}

static void j_value(J *j, int depth);

static void j_string(J *j)
{
    if (j->p >= j->end || *j->p != '"') {
        j_error(j, "expected string");
        return;
    }
    j->p++;
    j->col++;
    while (j->p < j->end) {
        char c = *j->p;
        if (c == '\\') {
            j->p += 2;
            j->col += 2;
            continue;
        }
        j->p++;
        j->col++;
        if (c == '"')
            return;
        if (c == 10) {
            j_error(j, "newline inside string");
            return;
        }
    }
    j_error(j, "unterminated string");
}

static void j_number(J *j)
{
    const char *s = j->p;
    if (j->p < j->end && (*j->p == '-' || *j->p == '+')) {
        j->p++;
        j->col++;
    }
    while (j->p < j->end) {
        char c = *j->p;
        if ((c >= '0' && c <= '9') || c == '.' || c == 'e' || c == 'E' || c == '-' || c == '+') {
            j->p++;
            j->col++;
        } else {
            break;
        }
    }
    if (j->p == s)
        j_error(j, "invalid number");
}

static void j_object(J *j, int depth)
{
    j->p++;
    j->col++;
    j_ws(j);
    if (j->p < j->end && *j->p == '}') {
        j->p++;
        j->col++;
        return;
    }
    for (;;) {
        j_ws(j);
        if (j->p >= j->end) {
            j_error(j, "unterminated object");
            return;
        }
        j_string(j);
        if (j->errors)
            return;
        j_ws(j);
        if (j->p >= j->end || *j->p != ':') {
            j_error(j, "expected ':'");
            return;
        }
        j->p++;
        j->col++;
        j_ws(j);
        j_value(j, depth + 1);
        if (j->errors)
            return;
        j_ws(j);
        if (j->p >= j->end) {
            j_error(j, "unterminated object");
            return;
        }
        if (*j->p == ',') {
            j->p++;
            j->col++;
            continue;
        }
        if (*j->p == '}') {
            j->p++;
            j->col++;
            return;
        }
        j_error(j, "expected ',' or '}'");
        return;
    }
}

static void j_array(J *j, int depth)
{
    j->p++;
    j->col++;
    j_ws(j);
    if (j->p < j->end && *j->p == ']') {
        j->p++;
        j->col++;
        return;
    }
    for (;;) {
        j_ws(j);
        j_value(j, depth + 1);
        if (j->errors)
            return;
        j_ws(j);
        if (j->p >= j->end) {
            j_error(j, "unterminated array");
            return;
        }
        if (*j->p == ',') {
            j->p++;
            j->col++;
            continue;
        }
        if (*j->p == ']') {
            j->p++;
            j->col++;
            return;
        }
        j_error(j, "expected ',' or ']'");
        return;
    }
}

static void j_value(J *j, int depth)
{
    if (depth > 64) {
        j_error(j, "nesting too deep");
        return;
    }
    j_ws(j);
    if (j->p >= j->end) {
        j_error(j, "unexpected end of input");
        return;
    }
    switch (*j->p) {
    case '{':
        j_object(j, depth);
        break;
    case '[':
        j_array(j, depth);
        break;
    case '"':
        j_string(j);
        break;
    case 't':
        if ((size_t)(j->end - j->p) >= 4 && memcmp(j->p, "true", 4) == 0) {
            j->p += 4;
            j->col += 4;
        } else {
            j_error(j, "invalid literal");
        }
        break;
    case 'f':
        if ((size_t)(j->end - j->p) >= 5 && memcmp(j->p, "false", 5) == 0) {
            j->p += 5;
            j->col += 5;
        } else {
            j_error(j, "invalid literal");
        }
        break;
    case 'n':
        if ((size_t)(j->end - j->p) >= 4 && memcmp(j->p, "null", 4) == 0) {
            j->p += 4;
            j->col += 4;
        } else {
            j_error(j, "invalid literal");
        }
        break;
    default:
        if (*j->p == '-' || (*j->p >= '0' && *j->p <= '9'))
            j_number(j);
        else
            j_error(j, "unexpected character");
        break;
    }
}

static int has_json_ext(const char *path)
{
    const char *dot;
    if (!path)
        return 0;
    dot = strrchr(path, '.');
    return dot && _stricmp(dot, ".json") == 0;
}

static void lint_now(void)
{
    const char *text = H->doc_text();
    int len = H->doc_length();
    J j;
    H->clear_diagnostics();
    if (!text || len <= 0)
        return;
    j.p = text;
    j.end = text + len;
    j.line = 0;
    j.col = 0;
    j.errors = 0;
    j.msg[0] = 0;
    j_ws(&j);
    j_value(&j, 0);
    if (!j.errors) {
        j_ws(&j);
        if (j.p < j.end)
            j_error(&j, "trailing data after the document");
        else {
            H->add_diagnostic(0, 0, 3, "JSON OK");
            H->status("jsonlint: valid JSON");
            return;
        }
    }
    H->add_diagnostic(j.line, j.col, 1, j.msg);
    {
        char line[160];
        snprintf(line, sizeof(line), "jsonlint: line %d: %s", j.line + 1, j.msg);
        H->output(line);
        H->status(line);
    }
}

static void on_event(int event, const char *arg, void *user)
{
    (void)user;
    (void)arg;
    if (event == AC_EV_DOC_OPEN || event == AC_EV_DOC_SAVE || event == AC_EV_DOC_CHANGED) {
        if (has_json_ext(H->doc_path()))
            lint_now();
    }
}

__declspec(dllexport) int ac_plugin_api(void)
{
    return AC_PLUGIN_API_VERSION;
}

__declspec(dllexport) int ac_plugin_init(AcPlugin *self)
{
    H = self->host;
    H->register_command("jsonlint.run", "JSON: lint current file", lint_now);
    H->menu_add("Build", "JSON: lint current file", "jsonlint.run");
    H->subscribe(AC_EV_DOC_OPEN, on_event, NULL);
    H->subscribe(AC_EV_DOC_SAVE, on_event, NULL);
    H->subscribe(AC_EV_DOC_CHANGED, on_event, NULL);
    H->log("jsonlint ready");
    return 1;
}

__declspec(dllexport) void ac_plugin_shutdown(void)
{
}
