#ifndef AC_IDE_H
#define AC_IDE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shlobj.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/ac.h"

#define MAX_DOCS 24
#define TAB_WIDTH 4

typedef enum {
    TK_PLAIN = 0,
    TK_KEYWORD,
    TK_TYPE,
    TK_STRING,
    TK_COMMENT,
    TK_PREPROC,
    TK_NUMBER,
    TK_FUNC,
    TK_OPERATOR,
    TK_COUNT
} TokKind;

typedef struct {
    int start;
    int len;
    TokKind kind;
} Span;

typedef struct UndoRec {
    int op;
    int pos;
    int len;
    char *text;
    int caret_before;
    int caret_after;
} UndoRec;

typedef struct {
    char *path;
    char *name;
    Buf data;
    int *lines;
    int nlines;
    int caret;
    int anchor;
    int sel_active;
    int scroll_y;
    int scroll_x;
    int modified;
    int top_line;
    int undo_pos;
    int undo_count;
    struct UndoRec *undo;
    int lex_lang;
    int read_only;
    int *bstate;
} Doc;

typedef struct {
    char message[512];
    char file[260];
    int line;
    int col;
    int is_error;
} BuildMsg;

typedef struct {
    char name[128];
    char target[32];
    char uid3[16];
    char caps[128];
    char pkg[260];
    char icon[260];
    StrVec sources;
    StrVec libs;
    int heap;
    int stack;
    char out_dir[260];
    char project_path[260];
    int is_dll;
} Project;

typedef struct {
    HWND hwnd;
    Doc docs[MAX_DOCS];
    int ndocs;
    int active;
    HFONT font;
    HFONT font_ui;
    HFONT font_bold;
    int char_w;
    int line_h;
    int caret_visible;
    int blink_on;
    RECT rc_tree;
    RECT rc_tabs;
    RECT rc_editor;
    RECT rc_output;
    RECT rc_status;
    RECT rc_toolbar;
    int tree_scroll;
    int split_x;
    int split_y;
    int dragging_split;
    int output_scroll;
    BuildMsg msgs[256];
    int nmsgs;
    int selected_msg;
    Buf build_log;
    int building;
    HANDLE build_proc;
    Project proj;
    int show_output;
    int menu_open;
    int menu_index;
    int menu_hover;
    int status_msg_timer;
    char status[256];
    char emu_path[512];
    char emu_args[512];
    char emu_workdir[512];
    char last_sisx[768];
    char sign_cert[512];
    char sign_key[512];
    int dirty_layout;
    int find_open;
    char find_text[128];
    char replace_text[128];
    int find_focus;
    int find_caret;
    int comp_open;
    int comp_index;
    int comp_count;
    char comp_items[8][96];
    int comp_x;
    int comp_y;
    int viewer_mode;
    int tree_sel;
    StrVec tree_files;
} Ide;

extern Ide g_ide;

void ide_init(HWND hwnd);
void ide_layout(void);
void ide_paint(HDC dc, RECT *client);
int ide_key(int vk, int ctrl, int shift, int alt);
void ide_char(wchar_t ch);
void ide_rbutton_down(int x, int y);
void ide_mouse_down(int x, int y, int shift, int button);
void ide_mouse_up(int x, int y);
void ide_mouse_move(int x, int y, int buttons);
void ide_wheel(int delta, int keys, int x, int y);
void ide_build(void);
void ide_new_project(void);
void ide_open_project(const char *path);
void ide_save_project(void);
void ide_open_file(const char *path);
void ide_save_file(int index, int save_as);
void ide_close_file(int index);
void ide_goto_line(int line);
void ide_find(void);
void ide_set_status(const char *fmt, ...);
int run_capture(const char *cmd, char *log, size_t logcap);
void add_msg(const char *fmt, ...);
void ide_settings_load(void);
void ide_settings_save(void);
void ide_choose_emulator(void);
void ide_package(void);
void ide_run(void);
void ide_sign(void);

Doc *doc_active(void);
void doc_init(Doc *d, const char *path);
void doc_free(Doc *d);
void doc_reindex(Doc *d);
void doc_insert(Doc *d, int pos, const char *text, int len);
void doc_delete(Doc *d, int pos, int len);
void doc_undo(Doc *d);
void doc_redo(Doc *d);
void doc_set_caret(Doc *d, int pos, int extend);
int doc_line_of(Doc *d, int pos);
int doc_line_start(Doc *d, int line);
int doc_line_end(Doc *d, int line);
int doc_col_of(Doc *d, int pos);
int doc_utf8_len(unsigned char c);
int doc_pos_from_col(Doc *d, int line, int col);
int doc_hit_test(Doc *d, int x, int y);
void doc_highlight(Doc *d, int line, Span *out, int max, int *count);
void doc_select_all(Doc *d);
void doc_copy(Doc *d);
void doc_cut(Doc *d);
void doc_paste(Doc *d);
int doc_has_selection(Doc *d);
void doc_sel_range(Doc *d, int *a, int *b);
void doc_scroll_to_caret(Doc *d);


void ide_host_run_named(const char *id);

void plugins_load(void);
int plugins_command_count(void);
const char *plugins_command_id(int i);
const char *plugins_command_label(int i);
int plugins_menu_count(void);
const char *plugins_menu_name(int i);
const char *plugins_menu_label(int i);
const char *plugins_menu_cmd(int i);
int plugins_command_find(const char *cmd);
void plugins_exec_index(int i);
void plugins_fire(int event, const char *arg);
void plugins_doc_changed(void);
int plugins_complete(const char *prefix, char *out, int cap);
void *plugins_viewer_for(const char *path, void **user);
int plugins_diag_count(void);
int plugins_diag_severity(int i);
const char *plugins_diag_text(int i);
int plugins_diag_line(int i);

#endif
