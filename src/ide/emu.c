#include "ide.h"

static const char *settings_path(void)
{
    static char path[512];
    char exe[512];
    int i;
    GetModuleFileNameA(NULL, exe, sizeof(exe));
    for (i = (int)strlen(exe); i > 0 && exe[i] != '\\' && exe[i] != '/'; i--)
        exe[i] = 0;
    snprintf(path, sizeof(path), "%sacetylene.ini", exe);
    return path;
}

void ide_settings_load(void)
{
    Buf b;
    char *line;
    if (ac_read_file(settings_path(), &b) != 0)
        return;
    buf_put(&b, "", 1);
    line = (char *)b.data;
    while (*line) {
        char *nl = strchr(line, '\n');
        char *eq;
        if (nl)
            *nl = 0;
        {
            size_t n = strlen(line);
            while (n > 0 && (line[n - 1] == '\r' || line[n - 1] == ' '))
                line[--n] = 0;
        }
        eq = strchr(line, '=');
        if (eq) {
            *eq = 0;
            if (strcmp(line, "emulator") == 0)
                snprintf(g_ide.emu_path, sizeof(g_ide.emu_path), "%s", eq + 1);
            else if (strcmp(line, "emu_args") == 0)
                snprintf(g_ide.emu_args, sizeof(g_ide.emu_args), "%s", eq + 1);
            else if (strcmp(line, "emu_workdir") == 0)
                snprintf(g_ide.emu_workdir, sizeof(g_ide.emu_workdir), "%s", eq + 1);
            else if (strcmp(line, "sign_cert") == 0)
                snprintf(g_ide.sign_cert, sizeof(g_ide.sign_cert), "%s", eq + 1);
            else if (strcmp(line, "sign_key") == 0)
                snprintf(g_ide.sign_key, sizeof(g_ide.sign_key), "%s", eq + 1);
            else if (strcmp(line, "pkg") == 0)
                snprintf(g_ide.proj.pkg, sizeof(g_ide.proj.pkg), "%s", eq + 1);
        }
        if (!nl)
            break;
        line = nl + 1;
    }
    buf_free(&b);
}

void ide_settings_save(void)
{
    Buf b;
    char line[1600];
    buf_init(&b);
    snprintf(line, sizeof(line),
             "; AcetyleneC settings. The EKA emulator is not shipped with this SDK:\n"
             "; point 'emulator' at the binary you downloaded. Placeholders in emu_args:\n"
             ";   %%e32%% %%sisx%% %%project%%\n");
    buf_put(&b, line, strlen(line));
    snprintf(line, sizeof(line), "emulator=%s\nemu_args=%s\nemu_workdir=%s\npkg=%s\n", g_ide.emu_path,
             g_ide.emu_args[0] ? g_ide.emu_args : "%sisx%", g_ide.emu_workdir, g_ide.proj.pkg);
    buf_put(&b, line, strlen(line));
    ac_write_file(settings_path(), b.data, b.len);
    buf_free(&b);
}

static void subst(char *out, size_t cap, const char *tmpl, const char *e32, const char *sisx)
{
    size_t o = 0;
    const char *p = tmpl;
    while (*p && o + 1 < cap) {
        if (strncmp(p, "%e32%", 5) == 0) {
            snprintf(out + o, cap - o, "%s", e32);
            o = strlen(out);
            p += 5;
        } else if (strncmp(p, "%sisx%", 6) == 0) {
            snprintf(out + o, cap - o, "%s", sisx);
            o = strlen(out);
            p += 6;
        } else if (strncmp(p, "%sis%", 5) == 0) {
            snprintf(out + o, cap - o, "%s", sisx);
            o = strlen(out);
            p += 5;
        } else if (strncmp(p, "%project%", 9) == 0) {
            snprintf(out + o, cap - o, "%s", g_ide.proj.name);
            o = strlen(out);
            p += 9;
        } else {
            out[o++] = *p++;
            out[o] = 0;
        }
    }
    out[o] = 0;
}

void ide_choose_emulator(void)
{
    OPENFILENAMEA ofn;
    char file[512];
    memset(&ofn, 0, sizeof(ofn));
    snprintf(file, sizeof(file), "%s", g_ide.emu_path);
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_ide.hwnd;
    ofn.lpstrFilter = "Emulator\0*.exe\0All Files\0*.*\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (GetOpenFileNameA(&ofn)) {
        snprintf(g_ide.emu_path, sizeof(g_ide.emu_path), "%s", file);
        if (!g_ide.emu_args[0])
            snprintf(g_ide.emu_args, sizeof(g_ide.emu_args), "%%sisx%%");
        ide_settings_save();
        ide_set_status("emulator set: %s", file);
    }
}

static void write_default_pkg(const char *pkg, const char *root)
{
    Buf b;
    char part[1024];
    buf_init(&b);
    buf_put(&b, "&EN", 3);
    buf_u8(&b, 10);
    snprintf(part, sizeof(part), "#{\"%s\"},(%s),1,0,0", g_ide.proj.name, g_ide.proj.uid3);
    buf_put(&b, part, strlen(part));
    buf_u8(&b, 10);
    buf_put(&b, "%{\"AcetyleneC\"}", 16);
    buf_u8(&b, 10);
    buf_put(&b, ":\"AcetyleneC\"", 14);
    buf_u8(&b, 10);
    snprintf(part, sizeof(part), "\"%s/build/%s.e32\"-\"!:", root, g_ide.proj.name);
    buf_put(&b, part, strlen(part));
    buf_put(&b, "\\sys\\bin\\", 9);
    snprintf(part, sizeof(part), "%s.exe\"", g_ide.proj.name);
    buf_put(&b, part, strlen(part));
    buf_u8(&b, 10);
    ac_write_file(pkg, b.data, b.len);
    buf_free(&b);
}

void ide_package(void)
{
    char exe_dir[512];
    char root[512];
    char cmd[2048];
    char pkg[768];
    char out_sisx[768];
    int i;
    int code;

    if (!g_ide.proj.project_path[0]) {
        ide_set_status("package: open or create a project first");
        return;
    }
    GetModuleFileNameA(NULL, exe_dir, sizeof(exe_dir));
    for (i = (int)strlen(exe_dir); i > 0 && exe_dir[i] != 92 && exe_dir[i] != 47; i--)
        exe_dir[i] = 0;
    snprintf(root, sizeof(root), "%s/../..", exe_dir);
    if (g_ide.proj.pkg[0]) {
        if (g_ide.proj.pkg[1] == ':')
            snprintf(pkg, sizeof(pkg), "%s", g_ide.proj.pkg);
        else
            snprintf(pkg, sizeof(pkg), "%s/%s", root, g_ide.proj.pkg);
    } else {
        snprintf(pkg, sizeof(pkg), "%s/build/%s.pkg", root, g_ide.proj.name);
        write_default_pkg(pkg, root);
    }
    snprintf(out_sisx, sizeof(out_sisx), "%s/build/%s.sisx", root, g_ide.proj.name);
    snprintf(cmd, sizeof(cmd), "\"%s/acetylene-sis.exe\" -pkg \"%s\" -o \"%s\" -sdk \"%s/sdk/targets/%s\"",
             exe_dir, pkg, out_sisx, root, g_ide.proj.target);
    buf_put(&g_ide.build_log, cmd, strlen(cmd));
    buf_u8(&g_ide.build_log, 0x0a);
    ide_set_status("Packaging...");
    UpdateWindow(g_ide.hwnd);
    code = run_capture(cmd, NULL, 0);
    if (code != 0) {
        add_msg("packaging failed (exit %d)", code);
        ide_set_status("Package FAILED");
        return;
    }
    snprintf(g_ide.last_sisx, sizeof(g_ide.last_sisx), "%s", out_sisx);
    ide_set_status("package: %s", out_sisx);
}

void ide_run(void)
{
    char exe_dir[512];
    char root[512];
    char e32[768];
    char args[2048];
    char cmd[3072];
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    int i;

    GetModuleFileNameA(NULL, exe_dir, sizeof(exe_dir));
    for (i = (int)strlen(exe_dir); i > 0 && exe_dir[i] != 92 && exe_dir[i] != 47; i--)
        exe_dir[i] = 0;
    snprintf(root, sizeof(root), "%s/../..", exe_dir);
    snprintf(e32, sizeof(e32), "%s/build/%s.e32", root, g_ide.proj.name);

    if (!g_ide.emu_path[0]) {
        ide_set_status("Run: no EKA emulator configured. Build > Set Emulator...");
        add_msg("Run needs an external EKA emulator: Build > Set Emulator..., then F5");
        return;
    }
    if (GetFileAttributesA(g_ide.emu_path) == INVALID_FILE_ATTRIBUTES) {
        ide_set_status("Run: emulator not found: %s", g_ide.emu_path);
        add_msg("emulator binary not found: %s", g_ide.emu_path);
        return;
    }
    if (GetFileAttributesA(e32) == INVALID_FILE_ATTRIBUTES) {
        ide_set_status("Run: no build yet, press F7");
        return;
    }
    if (strstr(g_ide.emu_args, "%sisx%") || strstr(g_ide.emu_args, "%sis%")) {
        if (!g_ide.last_sisx[0] || GetFileAttributesA(g_ide.last_sisx) == INVALID_FILE_ATTRIBUTES) {
            ide_package();
            if (!g_ide.last_sisx[0])
                return;
        }
    }
    subst(args, sizeof(args), g_ide.emu_args[0] ? g_ide.emu_args : "%sisx%", e32, g_ide.last_sisx);
    snprintf(cmd, sizeof(cmd), "\"%s\" %s", g_ide.emu_path, args);
    buf_put(&g_ide.build_log, cmd, strlen(cmd));
    buf_u8(&g_ide.build_log, 0x0a);
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL,
                        g_ide.emu_workdir[0] ? g_ide.emu_workdir : NULL, &si, &pi)) {
        ide_set_status("Run: cannot start emulator (%lu)", GetLastError());
        add_msg("cannot start emulator: %s", cmd);
        return;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    ide_set_status("emulator started: %s", cmd);
}

void ide_sign(void)
{
    char exe_dir[512];
    char root[512];
    char cmd[2048];
    int i;
    int code;

    if (!g_ide.sign_cert[0] || !g_ide.sign_key[0]) {
        ide_set_status("sign: set sign_cert and sign_key in acetylene.ini");
        add_msg("signing needs a certificate/key pair (sign_cert, sign_key in acetylene.ini)");
        return;
    }
    if (!g_ide.last_sisx[0] || GetFileAttributesA(g_ide.last_sisx) == INVALID_FILE_ATTRIBUTES) {
        ide_package();
        if (!g_ide.last_sisx[0])
            return;
    }
    GetModuleFileNameA(NULL, exe_dir, sizeof(exe_dir));
    for (i = (int)strlen(exe_dir); i > 0 && exe_dir[i] != 92 && exe_dir[i] != 47; i--)
        exe_dir[i] = 0;
    snprintf(root, sizeof(root), "%s/../..", exe_dir);
    snprintf(cmd, sizeof(cmd),
             "\"%s/acetylene-sis.exe\" -pkg \"%s/build/%s.pkg\" -o \"%s\" -sdk \"%s/sdk/targets/%s\" -sign \"%s\" \"%s\"",
             exe_dir, root, g_ide.proj.name, g_ide.last_sisx, root, g_ide.proj.target,
             g_ide.sign_cert, g_ide.sign_key);
    buf_put(&g_ide.build_log, cmd, strlen(cmd));
    buf_u8(&g_ide.build_log, 0x0a);
    ide_set_status("Signing...");
    UpdateWindow(g_ide.hwnd);
    code = run_capture(cmd, NULL, 0);
    if (code != 0) {
        add_msg("signing failed (exit %d)", code);
        ide_set_status("Sign FAILED");
        return;
    }
    ide_set_status("signed: %s.signed.sisx", g_ide.last_sisx);
}
