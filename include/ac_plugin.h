#ifndef AC_PLUGIN_H
#define AC_PLUGIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define AC_PLUGIN_API_VERSION 1

#define AC_EV_DOC_OPEN 1
#define AC_EV_DOC_SAVE 2
#define AC_EV_DOC_CHANGED 3
#define AC_EV_BUILD_OK 4
#define AC_EV_BUILD_FAIL 5
#define AC_EV_CMD 6

#define AC_SEV_ERROR 1
#define AC_SEV_WARNING 2
#define AC_SEV_INFO 3

typedef void (*AcCommandFn)(void);
typedef void (*AcEventFn)(int event, const char *arg, void *user);
typedef int (*AcCompleteFn)(const char *prefix, char *out_buf, int buf_size, void *user);
typedef int (*AcPaintFn)(void *hdc, int x, int y, int w, int h, const char *path, void *user);

typedef struct AcHostApi AcHostApi;

struct AcHostApi {
    int api_version;

    const char *(*doc_text)(void);
    int (*doc_length)(void);
    int (*cursor_pos)(void);
    void (*insert_text)(const char *text, int len);
    void (*replace_range)(int start, int end, const char *text, int len);
    void (*set_cursor)(int pos);
    const char *(*doc_path)(void);
    int (*doc_line_of)(int pos);
    int (*line_start)(int line);
    int (*line_end)(int line);

    void (*status)(const char *msg);
    void (*output)(const char *line);
    void (*invalidate)(void);

    int (*register_command)(const char *id, const char *label, AcCommandFn fn);
    void (*menu_add)(const char *menu, const char *label, const char *cmd_id);
    int (*add_diagnostic)(int line, int col, int severity, const char *msg);
    void (*clear_diagnostics)(void);

    void (*register_completion)(AcCompleteFn fn, void *user);
    void (*register_viewer)(const char *ext, AcPaintFn fn, void *user);
    void (*subscribe)(int event, AcEventFn fn, void *user);

    const char *(*root_dir)(void);
    void (*log)(const char *line);
    void (*run_command)(const char *id);
    void (*open_file)(const char *path);
    const char *(*plugin_dir)(void);
};

typedef struct {
    const AcHostApi *host;
    const char *plugin_id;
    const char *plugin_dir;
} AcPlugin;

#ifdef __cplusplus
}
#endif

#endif
