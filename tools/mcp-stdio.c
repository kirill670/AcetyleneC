#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static SOCKET connect_to(int port)
{
    SOCKET s;
    struct sockaddr_in a;
    u_long on = 1;
    int err = 0;
    int len = (int)sizeof(err);

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
        return INVALID_SOCKET;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_port = htons((u_short)port);
    a.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(s, (struct sockaddr *)&a, sizeof(a)) != 0) {
        closesocket(s);
        return INVALID_SOCKET;
    }
    ioctlsocket(s, FIONBIO, &on);
    (void)err;
    (void)len;
    return s;
}

static int send_all(SOCKET s, const char *p, int n)
{
    int sent = 0;
    while (sent < n) {
        int w = send(s, p + sent, n - sent, 0);
        if (w <= 0)
            return 0;
        sent += w;
    }
    return 1;
}

static int read_line(SOCKET s, char *out, int cap)
{
    int n = 0;
    DWORD start = GetTickCount();
    for (;;) {
        char c;
        int r = recv(s, &c, 1, 0);
        if (r == 1) {
            if (c == '\n') {
                out[n] = 0;
                return n;
            }
            if (n < cap - 1)
                out[n++] = c;
            continue;
        }
        if (r == 0)
            return -1;
        if (WSAGetLastError() != WSAEWOULDBLOCK)
            return -1;
        if (GetTickCount() - start > 120000)
            return -1;
        Sleep(5);
    }
}

int main(int argc, char **argv)
{
    WSADATA wsa;
    SOCKET s;
    char *line = (char *)malloc(1 << 20);
    char *resp = (char *)malloc(1 << 20);
    int port = argc > 1 ? atoi(argv[1]) : 0;

    if (!line || !resp) {
        fprintf(stderr, "mcp-stdio: out of memory\n");
        return 1;
    }
    if (port <= 0)
        port = getenv("ACETYLENE_MCP_PORT") ? atoi(getenv("ACETYLENE_MCP_PORT")) : 8765;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "mcp-stdio: WSAStartup failed\n");
        return 1;
    }
    s = connect_to(port);
    if (s == INVALID_SOCKET) {
        fprintf(stderr, "mcp-stdio: AcetyleneC is not listening on 127.0.0.1:%d\n", port);
        return 1;
    }
    while (fgets(line, 1 << 20, stdin)) {
        size_t n = strlen(line);
        while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r'))
            line[--n] = 0;
        if (n == 0)
            continue;
        if (!send_all(s, line, (int)n) || !send_all(s, "\n", 1))
            break;
        if (read_line(s, resp, 1 << 20) < 0)
            break;
        fputs(resp, stdout);
        fputc('\n', stdout);
        fflush(stdout);
    }
    closesocket(s);
    WSACleanup();
    free(line);
    free(resp);
    return 0;
}
