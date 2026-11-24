#include "../../include/ac_plugin.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const AcHostApi *H;

static const char *const k_keys[] = {
    "if", "else", "for", "while", "do", "switch", "case", "default", "break", "continue",
    "return", "sizeof", "typedef", "struct", "union", "enum", "extern", "static", "const",
    "volatile", "void", "char", "short", "int", "long", "float", "double", "signed", "unsigned",
    "TInt", "TUint", "TBool", "TInt64", "TReal", "TDesC", "TDes", "TBuf", "TPtr", "HBufC",
    "GLDEF_C", "IMPORT_C", "EXPORT_C", "LOCAL_C", "NONSHARABLE_CLASS", "class", "public",
    "private", "protected", "virtual", "new", "delete", "this", "namespace", "using",
    "true", "false", "NULL", "KErrNone", "ConstructL", "NewL", "NewLC", "E32Main", NULL};

static int prefix_match(const char *word, int wlen, const char *prefix, int plen)
{
    int i;
    if (wlen <= plen)
        return 0;
    for (i = 0; i < plen; i++)
        if (tolower((unsigned char)word[i]) != tolower((unsigned char)prefix[i]))
            return 0;
    return 1;
}

static int already(const char *out, const char *word, int wlen)
{
    const char *p = out;
    while (*p) {
        const char *nl = strchr(p, 10);
        int len = nl ? (int)(nl - p) : (int)strlen(p);
        if (len == wlen && memcmp(p, word, (size_t)wlen) == 0)
            return 1;
        if (!nl)
            break;
        p = nl + 1;
    }
    return 0;
}

static void push(char *out, int cap, int *off, const char *word, int wlen, int *count)
{
    if (*off + wlen + 2 >= cap)
        return;
    if (already(out, word, wlen))
        return;
    memcpy(out + *off, word, (size_t)wlen);
    *off += wlen;
    out[(*off)++] = 10;
    out[*off] = 0;
    (*count)++;
}

static int complete(const char *prefix, char *out, int cap, void *user)
{
    const char *text;
    int plen = (int)strlen(prefix);
    int off = 0;
    int count = 0;
    int i;
    (void)user;
    out[0] = 0;
    if (plen < 2)
        return 0;
    for (i = 0; k_keys[i] && count < 24; i++)
        if (strcmp(k_keys[i], prefix) != 0 && prefix_match(k_keys[i], (int)strlen(k_keys[i]), prefix, plen))
            push(out, cap, &off, k_keys[i], (int)strlen(k_keys[i]), &count);
    text = H->doc_text();
    while (*text && count < 24) {
        if (isalpha((unsigned char)*text) || *text == '_') {
            const char *s = text;
            while (*text && (isalnum((unsigned char)*text) || *text == '_'))
                text++;
            if (prefix_match(s, (int)(text - s), prefix, plen))
                push(out, cap, &off, s, (int)(text - s), &count);
        } else {
            text++;
        }
    }
    return count;
}

static void cmd_dump(void)
{
    char buf[512];
    int n = complete("TIn", buf, sizeof(buf), NULL);
    H->status("autocomplete: provider ready");
    (void)n;
}

__declspec(dllexport) int ac_plugin_api(void)
{
    return AC_PLUGIN_API_VERSION;
}

__declspec(dllexport) int ac_plugin_init(AcPlugin *self)
{
    H = self->host;
    H->register_completion(complete, NULL);
    H->register_command("autocomplete.dump", "Autocomplete: self test", cmd_dump);
    H->menu_add("Edit", "Autocomplete: self test", "autocomplete.dump");
    H->log("autocomplete ready");
    return 1;
}

__declspec(dllexport) void ac_plugin_shutdown(void)
{
}
