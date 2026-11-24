#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/ac_plugin.h"

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

static const AcHostApi *H;

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} Buf;

static void b_grow(Buf *b, size_t need)
{
    size_t cap = b->cap ? b->cap : 256;
    char *p;
    while (cap < b->len + need + 1)
        cap *= 2;
    p = (char *)realloc(b->data, cap);
    if (!p)
        return;
    b->data = p;
    b->cap = cap;
}

static void b_put(Buf *b, const char *s, size_t n)
{
    if (!s || !n)
        return;
    if (b->len + n + 1 > b->cap)
        b_grow(b, n);
    if (b->len + n + 1 > b->cap)
        return;
    memcpy(b->data + b->len, s, n);
    b->len += n;
    b->data[b->len] = 0;
}

static void b_puts(Buf *b, const char *s)
{
    b_put(b, s, strlen(s));
}

static void b_printf(Buf *b, const char *fmt, ...)
{
    char tmp[512];
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
    va_end(ap);
    if (n < 0)
        return;
    if (n >= (int)sizeof(tmp))
        n = (int)sizeof(tmp) - 1;
    b_put(b, tmp, (size_t)n);
}

static void b_json(Buf *b, const char *s)
{
    b_put(b, "\"", 1);
    if (s) {
        for (; *s; s++) {
            unsigned char c = (unsigned char)*s;
            switch (c) {
            case '"':
                b_puts(b, "\\\"");
                break;
            case '\\':
                b_puts(b, "\\\\");
                break;
            case '\n':
                b_puts(b, "\\n");
                break;
            case '\r':
                b_puts(b, "\\r");
                break;
            case '\t':
                b_puts(b, "\\t");
                break;
            default:
                if (c < 0x20)
                    b_printf(b, "\\u%04x", c);
                else
                    b_put(b, (const char *)&c, 1);
                break;
            }
        }
    }
    b_put(b, "\"", 1);
}

static void b_free(Buf *b)
{
    free(b->data);
    b->data = NULL;
    b->len = b->cap = 0;
}

static const char *skip_ws(const char *p, const char *end)
{
    while (p < end && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'))
        p++;
    return p;
}

static const char *scan_string(const char *p, const char *end)
{
    if (p >= end || *p != '"')
        return NULL;
    p++;
    while (p < end) {
        if (*p == '\\') {
            p += 2;
            continue;
        }
        if (*p == '"')
            return p + 1;
        p++;
    }
    return NULL;
}

static const char *scan_value(const char *p, const char *end)
{
    p = skip_ws(p, end);
    if (p >= end)
        return NULL;
    if (*p == '"')
        return scan_string(p, end);
    if (*p == '{' || *p == '[') {
        int depth = 0;
        while (p < end) {
            if (*p == '"') {
                p = scan_string(p, end);
                if (!p)
                    return NULL;
                continue;
            }
            if (*p == '{' || *p == '[')
                depth++;
            else if (*p == '}' || *p == ']') {
                depth--;
                if (depth == 0)
                    return p + 1;
            }
            p++;
        }
        return NULL;
    }
    while (p < end && *p != ',' && *p != '}' && *p != ']' && *p != ' ' && *p != '\n' && *p != '\r' && *p != '\t')
        p++;
    return p;
}

static int obj_get(const char *obj, const char *end, const char *key, const char **vs, const char **ve)
{
    const char *p;
    if (!obj || obj >= end || *obj != '{')
        return 0;
    p = obj + 1;
    for (;;) {
        const char *ks, *ke;
        p = skip_ws(p, end);
        if (p >= end || *p == '}')
            return 0;
        ks = p;
        ke = scan_string(p, end);
        if (!ke)
            return 0;
        p = skip_ws(ke, end);
        if (p >= end || *p != ':')
            return 0;
        p = skip_ws(p + 1, end);
        {
            const char *vend = scan_value(p, end);
            int klen = (int)(ke - ks) - 2;
            if (!vend)
                return 0;
            if ((int)strlen(key) == klen && memcmp(ks + 1, key, (size_t)klen) == 0) {
                *vs = p;
                *ve = vend;
                return 1;
            }
            p = skip_ws(vend, end);
            if (p < end && *p == ',')
                p++;
        }
    }
}

static int as_string(const char *vs, const char *ve, char *out, int cap)
{
    int n = 0;
    vs = skip_ws(vs, ve);
    if (vs >= ve || *vs != '"')
        return 0;
    vs++;
    ve = (ve > vs && ve[-1] == '"') ? ve - 1 : ve;
    while (vs < ve && n < cap - 1) {
        if (*vs == '\\' && vs + 1 < ve) {
            vs++;
            switch (*vs) {
            case 'n':
                out[n++] = '\n';
                break;
            case 't':
                out[n++] = '\t';
                break;
            case 'r':
                out[n++] = '\r';
                break;
            case 'b':
                out[n++] = '\b';
                break;
            case 'f':
                out[n++] = '\f';
                break;
            case 'u':
                if (vs + 4 < ve) {
                    char hex[5];
                    unsigned v;
                    memcpy(hex, vs + 1, 4);
                    hex[4] = 0;
                    v = (unsigned)strtoul(hex, NULL, 16);
                    vs += 4;
                    if (v < 0x80)
                        out[n++] = (char)v;
                    else if (v < 0x800) {
                        if (n + 2 <= cap - 1) {
                            out[n++] = (char)(0xC0 | (v >> 6));
                            out[n++] = (char)(0x80 | (v & 0x3F));
                        }
                    } else {
                        if (n + 3 <= cap - 1) {
                            out[n++] = (char)(0xE0 | (v >> 12));
                            out[n++] = (char)(0x80 | ((v >> 6) & 0x3F));
                            out[n++] = (char)(0x80 | (v & 0x3F));
                        }
                    }
                }
                break;
            default:
                out[n++] = *vs;
                break;
            }
            vs++;
            continue;
        }
        out[n++] = *vs++;
    }
    out[n] = 0;
    return 1;
}

static int as_int(const char *vs, const char *ve, int *out)
{
    char tmp[32];
    int n = 0;
    vs = skip_ws(vs, ve);
    while (vs < ve && n < (int)sizeof(tmp) - 1 && ((*vs >= '0' && *vs <= '9') || *vs == '-'))
        tmp[n++] = *vs++;
    tmp[n] = 0;
    if (!n)
        return 0;
    *out = atoi(tmp);
    return 1;
}

typedef struct Job {
    void (*fn)(struct Job *);
    volatile LONG abandoned;
    char *out;
    int i1;
    int i2;
    const char *s1;
} Job;

static HWND g_marshal;
static WNDCLASSW g_mcls;

static LRESULT CALLBACK marshal_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    (void)hwnd;
    (void)wp;
    if (msg == WM_APP + 0x51) {
        Job *j = (Job *)lp;
        if (InterlockedExchange(&j->abandoned, -1) != 1)
            j->fn(j);
        free(j);
        return 0;
    }
    if (msg == WM_APP + 0x52) {
        struct PJob {
            void (*fn)(void *);
            void *arg;
        } *p = (struct PJob *)lp;
        p->fn(p->arg);
        free(p);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static int ui_call(Job *j)
{
    DWORD_PTR r = 0;
    j->abandoned = 0;
    if (SendMessageTimeoutA(g_marshal, WM_APP + 0x51, 0, (LPARAM)j,
                            SMTO_ABORTIFHUNG | SMTO_BLOCK, 8000, &r))
        return 1;
    if (InterlockedExchange(&j->abandoned, 1) == 0)
        free(j);
    return 0;
}

static void ui_post(void (*fn)(void *), void *arg)
{
    struct PJob {
        void (*fn)(void *);
        void *arg;
    } *p = (struct PJob *)calloc(1, sizeof(struct PJob));
    if (!p)
        return;
    p->fn = fn;
    p->arg = arg;
    if (!PostMessageA(g_marshal, WM_APP + 0x52, 0, (LPARAM)p))
        free(p);
}

static void jf_doc_text(Job *j)
{
    const char *t = H->doc_text();
    int len = H->doc_length();
    int a = j->i1;
    int b = j->i2;
    char *copy;
    if (!t)
        t = "";
    if (a < 0)
        a = 0;
    if (b < 0 || b > len)
        b = len;
    if (a > b)
        a = b;
    copy = (char *)malloc((size_t)(b - a) + 1);
    if (!copy)
        return;
    memcpy(copy, t + a, (size_t)(b - a));
    copy[b - a] = 0;
    j->out = copy;
}

static void jf_insert(Job *j)
{
    H->insert_text(j->s1 ? j->s1 : "", (int)strlen(j->s1 ? j->s1 : ""));
    j->i1 = 1;
}

static void jf_path(Job *j)
{
    const char *p = H->doc_path();
    size_t n;
    if (!p)
        p = "";
    n = strlen(p);
    j->out = (char *)malloc(n + 1);
    if (j->out)
        memcpy(j->out, p, n + 1);
}

static void jf_status(Job *j)
{
    H->status(j->s1 ? j->s1 : "");
    j->i1 = 1;
}

static void jf_open(Job *j)
{
    H->open_file(j->s1 ? j->s1 : "");
    j->i1 = 1;
}

static void do_build(void *arg)
{
    (void)arg;
    H->run_command("build");
}

static char *dup_job_out(Job *j, const char *fallback)
{
    char *r = j->out;
    j->out = NULL;
    if (!r) {
        size_t n = strlen(fallback);
        r = (char *)malloc(n + 1);
        if (r)
            memcpy(r, fallback, n + 1);
    }
    return r;
}

static char *get_doc_text(int start, int end)
{
    Job *j = (Job *)calloc(1, sizeof(Job));
    char *r;
    if (!j)
        return NULL;
    j->fn = jf_doc_text;
    j->i1 = start;
    j->i2 = end;
    if (!ui_call(j))
        return NULL;
    r = dup_job_out(j, "");
    return r;
}

static char *tool_text_ex(const char *s, int is_err)
{
    Buf b;
    char *out;
    memset(&b, 0, sizeof(b));
    b_puts(&b, "{\"content\":[{\"type\":\"text\",\"text\":");
    b_json(&b, s ? s : "");
    b_printf(&b, "}],\"isError\":%s}", is_err ? "true" : "false");
    out = b.data;
    return out;
}

static char *tool_text(const char *s)
{
    return tool_text_ex(s, 0);
}

static char *get_doc_path(void)
{
    Job *j = (Job *)calloc(1, sizeof(Job));
    char *r;
    if (!j)
        return NULL;
    j->fn = jf_path;
    if (!ui_call(j))
        return NULL;
    r = dup_job_out(j, "");
    free(j);
    return r;
}

static char *tool_text_owned(char *s)
{
    char *r = tool_text(s);
    free(s);
    return r;
}

static char *tool_no_ui(void)
{
    return tool_text_ex("the IDE did not answer the request in time", 1);
}

static char *rpc_result(const char *idraw, char *result)
{
    Buf b;
    char *out;
    memset(&b, 0, sizeof(b));
    b_puts(&b, "{\"jsonrpc\":\"2.0\",\"id\":");
    b_puts(&b, idraw && idraw[0] ? idraw : "null");
    b_puts(&b, ",\"result\":");
    b_puts(&b, result ? result : "null");
    b_puts(&b, "}");
    free(result);
    out = b.data;
    return out;
}

static char *rpc_error(const char *idraw, int code, const char *msg)
{
    Buf b;
    char *out;
    memset(&b, 0, sizeof(b));
    b_puts(&b, "{\"jsonrpc\":\"2.0\",\"id\":");
    b_puts(&b, idraw && idraw[0] ? idraw : "null");
    b_printf(&b, ",\"error\":{\"code\":%d,\"message\":", code);
    b_json(&b, msg ? msg : "");
    b_puts(&b, "}}");
    out = b.data;
    return out;
}

static const char *k_tools =
    "{\"tools\":["
    "{\"name\":\"ide_get_text\",\"description\":\"Read the active editor buffer, optionally a byte range\","
    "\"inputSchema\":{\"type\":\"object\",\"properties\":{\"start\":{\"type\":\"integer\"},\"end\":{\"type\":\"integer\"}}}},"
    "{\"name\":\"ide_insert_text\",\"description\":\"Insert text at the caret of the active editor\","
    "\"inputSchema\":{\"type\":\"object\",\"properties\":{\"text\":{\"type\":\"string\"}},\"required\":[\"text\"]}},"
    "{\"name\":\"ide_get_path\",\"description\":\"Return the path of the active editor\","
    "\"inputSchema\":{\"type\":\"object\",\"properties\":{}}},"
    "{\"name\":\"ide_build\",\"description\":\"Start the project build pipeline\","
    "\"inputSchema\":{\"type\":\"object\",\"properties\":{}}},"
    "{\"name\":\"ide_status\",\"description\":\"Write a message to the IDE status bar\","
    "\"inputSchema\":{\"type\":\"object\",\"properties\":{\"message\":{\"type\":\"string\"}},\"required\":[\"message\"]}},"
    "{\"name\":\"ide_open_file\",\"description\":\"Open a file in the IDE\","
    "\"inputSchema\":{\"type\":\"object\",\"properties\":{\"path\":{\"type\":\"string\"}},\"required\":[\"path\"]}}"
    "]}";

static char *call_tool(const char *ps, const char *pe)
{
    const char *vs, *ve;
    char name[64];
    const char *as = NULL, *ae = NULL;
    if (!obj_get(ps, pe, "name", &vs, &ve) || !as_string(vs, ve, name, sizeof(name)))
        return tool_text_ex("missing tool name", 1);
    if (obj_get(ps, pe, "arguments", &vs, &ve) && vs < pe && *skip_ws(vs, ve) == '{') {
        as = vs;
        ae = ve;
    }
    if (strcmp(name, "ide_get_text") == 0) {
        int start = -1, end = -1;
        char *t;
        if (as && obj_get(as, ae, "start", &vs, &ve))
            as_int(vs, ve, &start);
        if (as && obj_get(as, ae, "end", &vs, &ve))
            as_int(vs, ve, &end);
        t = get_doc_text(start, end);
        if (!t)
            return tool_no_ui();
        return tool_text_owned(t);
    }
    if (strcmp(name, "ide_get_path") == 0) {
        char *r = get_doc_path();
        if (!r)
            return tool_no_ui();
        return tool_text_owned(r);
    }
    if (strcmp(name, "ide_insert_text") == 0) {
        char text[16384];
        Job *j;
        char *path;
        if (!as || !obj_get(as, ae, "text", &vs, &ve) || !as_string(vs, ve, text, sizeof(text)))
            return tool_text_ex("missing text", 1);
        path = get_doc_path();
        if (!path)
            return tool_no_ui();
        if (!path[0]) {
            free(path);
            return tool_text_ex("no document is open in the IDE", 1);
        }
        free(path);
        j = (Job *)calloc(1, sizeof(Job));
        if (!j)
            return tool_text_ex("out of memory", 1);
        j->fn = jf_insert;
        j->s1 = text;
        if (!ui_call(j))
            return tool_no_ui();
        free(j);
        return tool_text("inserted");
    }
    if (strcmp(name, "ide_build") == 0) {
        ui_post(do_build, NULL);
        return tool_text("build queued");
    }
    if (strcmp(name, "ide_status") == 0) {
        char msg[1024];
        Job *j;
        if (!as || !obj_get(as, ae, "message", &vs, &ve) || !as_string(vs, ve, msg, sizeof(msg)))
            return tool_text_ex("missing message", 1);
        j = (Job *)calloc(1, sizeof(Job));
        if (!j)
            return tool_text_ex("out of memory", 1);
        j->fn = jf_status;
        j->s1 = msg;
        if (!ui_call(j))
            return tool_no_ui();
        free(j);
        return tool_text("status updated");
    }
    if (strcmp(name, "ide_open_file") == 0) {
        char path[1024];
        Job *j;
        if (!as || !obj_get(as, ae, "path", &vs, &ve) || !as_string(vs, ve, path, sizeof(path)))
            return tool_text_ex("missing path", 1);
        j = (Job *)calloc(1, sizeof(Job));
        if (!j)
            return tool_text_ex("out of memory", 1);
        j->fn = jf_open;
        j->s1 = path;
        if (!ui_call(j))
            return tool_no_ui();
        free(j);
        return tool_text("opened");
    }
    {
        char msg[160];
        snprintf(msg, sizeof(msg), "unknown tool: %.100s", name);
        return tool_text_ex(msg, 1);
    }
}

static char *handle_request(const char *req)
{
    const char *end = req + strlen(req);
    const char *id_s = NULL, *id_e = NULL;
    const char *ms = NULL, *me = NULL;
    const char *ps = NULL, *pe = NULL;
    char method[96];
    char idraw[128];
    const char *p = skip_ws(req, end);

    idraw[0] = 0;
    if (p < end && *p == '{') {
        if (obj_get(p, end, "id", &id_s, &id_e)) {
            int n = (int)(id_e - id_s);
            if (n > (int)sizeof(idraw) - 1)
                n = (int)sizeof(idraw) - 1;
            memcpy(idraw, id_s, (size_t)n);
            idraw[n] = 0;
            while (n > 0 && (idraw[n - 1] == ' ' || idraw[n - 1] == '\n' || idraw[n - 1] == '\r'))
                idraw[--n] = 0;
        }
        if (obj_get(p, end, "params", &ps, &pe))
            ;
        if (!obj_get(p, end, "method", &ms, &me))
            return idraw[0] ? rpc_error(idraw, -32600, "missing method") : NULL;
    } else {
        return NULL;
    }
    if (!as_string(ms, me, method, sizeof(method)))
        return idraw[0] ? rpc_error(idraw, -32600, "bad method") : NULL;

    if (strcmp(method, "notifications/initialized") == 0)
        return NULL;
    if (strcmp(method, "initialize") == 0) {
        static const char *init_json =
            "{\"protocolVersion\":\"2024-11-05\",\"capabilities\":{\"tools\":{}},"
            "\"serverInfo\":{\"name\":\"acetylene-ide\",\"version\":\"1.0.0\"}}";
        return rpc_result(idraw, _strdup(init_json));
    }
    if (strcmp(method, "ping") == 0)
        return rpc_result(idraw, _strdup("{}"));
    if (strcmp(method, "tools/list") == 0)
        return rpc_result(idraw, _strdup(k_tools));
    if (strcmp(method, "tools/call") == 0) {
        if (!ps)
            return rpc_error(idraw, -32602, "missing params");
        return rpc_result(idraw, call_tool(ps, pe));
    }
    if (strcmp(method, "resources/list") == 0)
        return rpc_result(idraw, _strdup("{\"resources\":[]}"));
    if (strcmp(method, "prompts/list") == 0)
        return rpc_result(idraw, _strdup("{\"prompts\":[]}"));

    return rpc_error(idraw, -32601, "method not found");
}

static volatile LONG g_run;
static SOCKET g_listen = INVALID_SOCKET;
static int g_port;
static volatile LONG g_clients;

static int send_all(SOCKET s, const char *data, int len)
{
    int sent = 0;
    while (sent < len) {
        int n = send(s, data + sent, len - sent, 0);
        if (n <= 0)
            return 0;
        sent += n;
    }
    return 1;
}

static int send_response(SOCKET s, char *body, int framed)
{
    int ok;
    if (!body)
        return 1;
    if (framed) {
        char hdr[64];
        int hl = snprintf(hdr, sizeof(hdr), "Content-Length: %d\r\n\r\n", (int)strlen(body));
        ok = send_all(s, hdr, hl) && send_all(s, body, (int)strlen(body));
    } else {
        ok = send_all(s, body, (int)strlen(body)) && send_all(s, "\n", 1);
    }
    free(body);
    return ok;
}

static DWORD WINAPI client_thread(LPVOID p)
{
    SOCKET s = (SOCKET)(DWORD_PTR)p;
    Buf in;
    int framed = 0;
    char chunk[4096];
    int alive = 1;

    InterlockedIncrement(&g_clients);
    memset(&in, 0, sizeof(in));
    while (alive) {
        int n = recv(s, chunk, sizeof(chunk), 0);
        if (n <= 0)
            break;
        b_put(&in, chunk, (size_t)n);
        for (;;) {
            const char *start = in.data;
            const char *hdr_end;
            if (!start || in.len == 0)
                break;
            if (in.len >= 15 && _strnicmp(start, "Content-Length:", 15) == 0) {
                size_t body_len = 0;
                char *nl = strstr(in.data, "\r\n\r\n");
                if (!nl)
                    break;
                body_len = (size_t)atoi(in.data + 15);
                hdr_end = nl + 4;
                if (in.len < (size_t)(hdr_end - in.data) + body_len)
                    break;
                {
                    char *req = (char *)malloc(body_len + 1);
                    if (!req) {
                        alive = 0;
                        break;
                    }
                    memcpy(req, hdr_end, body_len);
                    req[body_len] = 0;
                    framed = 1;
                    if (!send_response(s, handle_request(req), 1))
                        alive = 0;
                    free(req);
                }
                {
                    size_t used = (size_t)(hdr_end - in.data) + body_len;
                    memmove(in.data, in.data + used, in.len - used);
                    in.len -= used;
                    in.data[in.len] = 0;
                }
                continue;
            }
            {
                char *nl = (char *)memchr(in.data, '\n', in.len);
                size_t used;
                size_t len;
                char *req;
                if (!nl)
                    break;
                used = (size_t)(nl - in.data) + 1;
                len = used - 1;
                while (len > 0 && (in.data[len - 1] == '\r' || in.data[len - 1] == ' '))
                    len--;
                req = (char *)malloc(len + 1);
                if (!req) {
                    alive = 0;
                    break;
                }
                memcpy(req, in.data, len);
                req[len] = 0;
                if (len > 0) {
                    framed = 0;
                    if (!send_response(s, handle_request(req), 0))
                        alive = 0;
                }
                free(req);
                memmove(in.data, in.data + used, in.len - used);
                in.len -= used;
                in.data[in.len] = 0;
            }
        }
        if (!alive)
            break;
    }
    b_free(&in);
    closesocket(s);
    InterlockedDecrement(&g_clients);
    return 0;
}

static DWORD WINAPI accept_thread(LPVOID p)
{
    (void)p;
    while (InterlockedCompareExchange(&g_run, 1, 1)) {
        SOCKET c = accept(g_listen, NULL, NULL);
        HANDLE h;
        if (c == INVALID_SOCKET)
            break;
        h = CreateThread(NULL, 0, client_thread, (LPVOID)(DWORD_PTR)c, 0, NULL);
        if (h)
            CloseHandle(h);
        else
            closesocket(c);
    }
    return 0;
}

static int read_port(void)
{
    const char *env = getenv("ACETYLENE_MCP_PORT");
    char path[600];
    char line[64];
    FILE *f;
    int port = 0;

    if (env && env[0]) {
        port = atoi(env);
        if (port > 0 && port < 65536)
            return port;
    }
    snprintf(path, sizeof(path), "%s/mcp.port", H->plugin_dir());
    f = fopen(path, "r");
    if (f) {
        if (fgets(line, sizeof(line), f))
            port = atoi(line);
        fclose(f);
        if (port > 0 && port < 65536)
            return port;
    }
    return 8765;
}

static void server_stop(void)
{
    if (InterlockedExchange(&g_run, 0)) {
        if (g_listen != INVALID_SOCKET) {
            closesocket(g_listen);
            g_listen = INVALID_SOCKET;
        }
    }
}

static int server_start(void)
{
    WSADATA wsa;
    struct sockaddr_in addr;
    HANDLE h;
    int yes = 1;

    if (InterlockedCompareExchange(&g_run, 1, 1))
        return 1;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        H->status("mcp: WSAStartup failed");
        return 0;
    }
    g_port = read_port();
    g_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_listen == INVALID_SOCKET) {
        H->status("mcp: socket() failed");
        WSACleanup();
        return 0;
    }
    setsockopt(g_listen, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)g_port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(g_listen, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        char msg[128];
        snprintf(msg, sizeof(msg), "mcp: cannot bind port %d (error %d)", g_port, WSAGetLastError());
        H->status(msg);
        closesocket(g_listen);
        g_listen = INVALID_SOCKET;
        WSACleanup();
        InterlockedExchange(&g_run, 0);
        return 0;
    }
    if (listen(g_listen, 8) != 0) {
        H->status("mcp: listen failed");
        closesocket(g_listen);
        g_listen = INVALID_SOCKET;
        WSACleanup();
        InterlockedExchange(&g_run, 0);
        return 0;
    }
    InterlockedExchange(&g_run, 1);
    h = CreateThread(NULL, 0, accept_thread, NULL, 0, NULL);
    if (!h) {
        H->status("mcp: cannot spawn server thread");
        closesocket(g_listen);
        g_listen = INVALID_SOCKET;
        WSACleanup();
        InterlockedExchange(&g_run, 0);
        return 0;
    }
    CloseHandle(h);
    return 1;
}

static void cmd_toggle(void)
{
    if (InterlockedCompareExchange(&g_run, 1, 1)) {
        server_stop();
        H->status("mcp: server stopped");
        H->output("mcp: server stopped");
    } else if (server_start()) {
        char msg[128];
        snprintf(msg, sizeof(msg), "mcp: listening on 127.0.0.1:%d", g_port);
        H->status(msg);
        H->output(msg);
    }
}

static void cmd_status(void)
{
    char msg[160];
    if (InterlockedCompareExchange(&g_run, 1, 1))
        snprintf(msg, sizeof(msg), "mcp: listening on 127.0.0.1:%d (%d clients)", g_port, (int)g_clients);
    else
        snprintf(msg, sizeof(msg), "mcp: stopped");
    H->status(msg);
    H->output(msg);
}

__declspec(dllexport) int ac_plugin_api(void)
{
    return AC_PLUGIN_API_VERSION;
}

__declspec(dllexport) int ac_plugin_init(AcPlugin *self)
{
    H = self->host;
    memset(&g_mcls, 0, sizeof(g_mcls));
    g_mcls.lpfnWndProc = marshal_proc;
    g_mcls.hInstance = GetModuleHandleA(NULL);
    g_mcls.lpszClassName = L"AcetyleneMcpMarshal";
    RegisterClassW(&g_mcls);
    g_marshal = CreateWindowExW(0, g_mcls.lpszClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, g_mcls.hInstance, NULL);
    if (!g_marshal) {
        H->log("mcp: cannot create marshal window");
        return 0;
    }
    H->register_command("mcp.toggle", "MCP: start/stop server", cmd_toggle);
    H->register_command("mcp.status", "MCP: show server status", cmd_status);
    H->menu_add("Plugins", "MCP: start/stop server", "mcp.toggle");
    H->menu_add("Plugins", "MCP: show server status", "mcp.status");
    if (!server_start()) {
        H->log("mcp: autostart failed, use the Plugins menu");
        return 1;
    }
    {
        char msg[128];
        snprintf(msg, sizeof(msg), "mcp: listening on 127.0.0.1:%d", g_port);
        H->log(msg);
    }
    return 1;
}

__declspec(dllexport) void ac_plugin_shutdown(void)
{
    server_stop();
    Sleep(30);
    if (g_marshal) {
        DestroyWindow(g_marshal);
        g_marshal = NULL;
    }
    UnregisterClassW(g_mcls.lpszClassName, g_mcls.hInstance);
    WSACleanup();
}
