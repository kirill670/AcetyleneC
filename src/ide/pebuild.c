#include "ide.h"
#include <stdio.h>

static void exe_dir_of(char *out, int cap)
{
    GetModuleFileNameA(NULL, out, (DWORD)cap);
    {
        int i;
        for (i = (int)strlen(out); i > 0 && out[i] != '\\' && out[i] != '/'; i--)
            out[i] = 0;
    }
}

int ide_target_is_legacy(const char *target)
{
    char exe[512];
    char path[768];
    Buf b;
    int pe = 0;

    if (!target || !target[0])
        return 0;
    exe_dir_of(exe, sizeof(exe));
    snprintf(path, sizeof(path), "%s../../sdk/targets/%s/target.ini", exe, target);
    if (ac_read_file(path, &b) != 0)
        return 0;
    buf_put(&b, "", 1);
    pe = strstr((const char *)b.data, "format=pe") != NULL;
    buf_free(&b);
    return pe;
}

static void log_cmd(const char *cmd)
{
    buf_put(&g_ide.build_log, cmd, strlen(cmd));
    buf_u8(&g_ide.build_log, 0x0a);
}

static void append_lib(char *cmd, size_t cap, const char *name, int len)
{
    char buf[160];
    if (len <= 0 || len >= (int)sizeof(buf) - 4)
        return;
    memcpy(buf, name, (size_t)len);
    buf[len] = 0;
    if (len > 4 && _stricmp(buf + len - 4, ".lib") == 0)
        buf[len - 4] = 0;
    if (strlen(cmd) + strlen(buf) + 6 >= cap)
        return;
    strcat(cmd, " -l");
    strcat(cmd, buf);
}

static void append_runtime_libs(char *cmd, size_t cap, const char *ini_path)
{
    Buf b;
    char *line;

    if (ac_read_file(ini_path, &b) != 0)
        return;
    buf_put(&b, "", 1);
    line = (char *)b.data;
    while (line && *line) {
        char *nl = strchr(line, 10);
        if (nl)
            *nl = 0;
        if (strncmp(line, "runtime=", 8) == 0) {
            char *p = line + 8;
            while (*p) {
                char *end;
                while (*p == 32 || *p == 9)
                    p++;
                if (!*p)
                    break;
                end = p;
                while (*end && *end != 32 && *end != 9)
                    end++;
                append_lib(cmd, cap, p, (int)(end - p));
                p = end;
            }
        }
        line = nl ? nl + 1 : NULL;
    }
    buf_free(&b);
}

void run_build_legacy(void)
{
    char exe[512];
    char root[1024];
    char tcc[1024], cxx[1024], pe[1024];
    char build_dir[1100];
    char app_file[1100];
    char lib_dir[1100];
    char objects[4096];
    char cmd[4096];
    char uid2[32];
    int i;
    int code;
    int compiled = 0;

    exe_dir_of(exe, sizeof(exe));
    snprintf(root, sizeof(root), "%s../..", exe);
    snprintf(tcc, sizeof(tcc), "%sacetylene-cc.exe", exe);
    snprintf(cxx, sizeof(cxx), "%sacetylene-cxx.exe", exe);
    snprintf(pe, sizeof(pe), "%sacetylene-pe.exe", exe);
    snprintf(build_dir, sizeof(build_dir), "%s/build", root);
    snprintf(lib_dir, sizeof(lib_dir), "%s/sdk/targets/%s/lib", root, g_ide.proj.target);
    snprintf(app_file, sizeof(app_file), "%s/%s.app", build_dir, g_ide.proj.name);
    CreateDirectoryA(build_dir, NULL);

    buf_free(&g_ide.build_log);
    buf_init(&g_ide.build_log);
    g_ide.nmsgs = 0;
    g_ide.selected_msg = -1;
    objects[0] = 0;

    if (g_ide.proj.sources.count == 0) {
        add_msg("add source= lines to the .acproj");
        ide_set_status("Build: nothing to compile");
        return;
    }

    for (i = 0; i < g_ide.proj.sources.count; i++) {
        const char *src = g_ide.proj.sources.items[i];
        char full[768];
        char obj[768];
        char base[128];
        const char *dot;
        int r;

        if (src[0] && src[1] == ':')
            snprintf(full, sizeof(full), "%s", src);
        else
            snprintf(full, sizeof(full), "%s/%s", root, src);

        snprintf(base, sizeof(base), "%s", ac_basename(full));
        dot = strrchr(base, '.');
        if (dot)
            ((char *)dot)[0] = 0;

        if (ac_has_ext(full, ".cpp") || ac_has_ext(full, ".cxx") || ac_has_ext(full, ".cc")) {
            char cfile[768];
            snprintf(cfile, sizeof(cfile), "%s/%s.gen.c", build_dir, base);
            snprintf(cmd, sizeof(cmd), "\"%s\" \"%s\" -o \"%s\"", cxx, full, cfile);
            log_cmd(cmd);
            ide_set_status("Translating %s...", base);
            UpdateWindow(g_ide.hwnd);
            if (run_capture(cmd, NULL, 0) != 0) {
                add_msg("C++ front-end failed for %s (see output)", base);
                ide_set_status("C++ FAILED: %s", base);
                return;
            }
            snprintf(obj, sizeof(obj), "%s/%s.o", build_dir, base);
            snprintf(cmd, sizeof(cmd),
                     "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                     tcc, root, root, cfile, obj);
        } else {
            snprintf(obj, sizeof(obj), "%s/%s.o", build_dir, base);
            snprintf(cmd, sizeof(cmd),
                     "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                     tcc, root, root, full, obj);
        }
        log_cmd(cmd);
        ide_set_status("Compiling %s...", base);
        UpdateWindow(g_ide.hwnd);
        r = run_capture(cmd, NULL, 0);
        if (r != 0) {
            add_msg("compiler failed for %s", base);
            ide_set_status("Compile FAILED: %s", base);
            return;
        }
        compiled++;
        if (strlen(objects) + strlen(obj) + 4 < sizeof(objects)) {
            if (objects[0])
                strncat(objects, " ", sizeof(objects) - strlen(objects) - 1);
            strncat(objects, "\"", sizeof(objects) - strlen(objects) - 1);
            strncat(objects, obj, sizeof(objects) - strlen(objects) - 1);
            strncat(objects, "\"", sizeof(objects) - strlen(objects) - 1);
        }
    }

    if (!compiled)
        return;

    {
        char shim_src[768];
        char shim_obj[768];
        snprintf(shim_src, sizeof(shim_src), "%s/sdk/runtime/e32main_shim_legacy.c", root);
        snprintf(shim_obj, sizeof(shim_obj), "%s/legacy_entry.o", build_dir);
        snprintf(cmd, sizeof(cmd),
                 "\"%s\" -I\"%s/sdk/include\" -I\"%s/sdk/include/tcc\" -c \"%s\" -o \"%s\"",
                 tcc, root, root, shim_src, shim_obj);
        log_cmd(cmd);
        if (run_capture(cmd, NULL, 0) != 0) {
            add_msg("cannot build the legacy entry shim");
            ide_set_status("Build FAILED: entry shim");
            return;
        }
        if (strlen(objects) + strlen(shim_obj) + 4 < sizeof(objects)) {
            strncat(objects, " \"", sizeof(objects) - strlen(objects) - 1);
            strncat(objects, shim_obj, sizeof(objects) - strlen(objects) - 1);
            strncat(objects, "\"", sizeof(objects) - strlen(objects) - 1);
        }
    }

    {
        const char *u = g_ide.proj.uid3[0] ? g_ide.proj.uid3 : "0xE0000001";
        if (strncmp(u, "0x", 2) == 0 || strncmp(u, "0X", 2) == 0)
            snprintf(uid2, sizeof(uid2), "%s", u);
        else
            snprintf(uid2, sizeof(uid2), "0x%s", u);
    }

    snprintf(cmd, sizeof(cmd),
             "\"%s\" -o \"%s\" %s -entry _E32Startup -uid1 0x100039CE -uid2 %s -uid3 0x0 "
             "-heap %d %d -stack %d -L \"%s\"",
             pe, app_file, objects, uid2,
             g_ide.proj.heap, g_ide.proj.heap * 16, g_ide.proj.stack, lib_dir);
    for (i = 0; i < g_ide.proj.libs.count; i++) {
        const char *lib = g_ide.proj.libs.items[i];
        char name[128];
        size_t n = strlen(lib);
        snprintf(name, sizeof(name), "%s", lib);
        if (n > 4 && _stricmp(name + n - 4, ".lib") == 0)
            name[n - 4] = 0;
        if (strlen(cmd) + strlen(name) + 8 < sizeof(cmd)) {
            strncat(cmd, " -l", sizeof(cmd) - strlen(cmd) - 1);
            strncat(cmd, name, sizeof(cmd) - strlen(cmd) - 1);
        }
    }
    {
        char ini[1100];
        snprintf(ini, sizeof(ini), "%s/sdk/targets/%s/target.ini", root, g_ide.proj.target);
        append_runtime_libs(cmd, sizeof(cmd), ini);
    }
    log_cmd(cmd);
    ide_set_status("Linking...");
    UpdateWindow(g_ide.hwnd);
    code = run_capture(cmd, NULL, 0);
    if (code != 0) {
        add_msg("legacy linker failed with exit code %d (see output)", code);
        ide_set_status("Link FAILED");
        return;
    }

    add_msg("%s", app_file);
    g_ide.msgs[g_ide.nmsgs - 1].is_error = 0;
    plugins_fire(4, app_file);
    ide_set_status("Build OK: %s", app_file);
}
