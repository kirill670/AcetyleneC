#ifndef AC_COMMON_H
#define AC_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;

typedef struct {
    u8 *data;
    size_t len;
    size_t cap;
} Buf;

void *ac_alloc(size_t n);
void *ac_calloc(size_t n, size_t sz);
void *ac_realloc(void *p, size_t n);
char *ac_strdup(const char *s);

void buf_init(Buf *b);
void buf_free(Buf *b);
void buf_reserve(Buf *b, size_t extra);
void buf_put(Buf *b, const void *p, size_t n);
void buf_u8(Buf *b, u8 v);
void buf_u16(Buf *b, u16 v);
void buf_u32(Buf *b, u32 v);
void buf_zeros(Buf *b, size_t n);
size_t buf_align(Buf *b, size_t a);

int ac_read_file(const char *path, Buf *out);
int ac_write_file(const char *path, const void *data, size_t len);

void ac_die(const char *fmt, ...);
void ac_warn(const char *fmt, ...);
void ac_info(const char *fmt, ...);

extern int ac_verbose;

const char *ac_basename(const char *p);
const char *ac_ext(const char *p);
int ac_has_ext(const char *p, const char *e);

static inline u16 rd16(const u8 *p) { return (u16)(p[0] | (p[1] << 8)); }
static inline u32 rd32(const u8 *p) { return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24); }
static inline void wr16(u8 *p, u16 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8); }
static inline void wr32(u8 *p, u32 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8); p[2] = (u8)(v >> 16); p[3] = (u8)(v >> 24); }

typedef struct {
    char **items;
    int count;
    int cap;
} StrVec;

void sv_init(StrVec *v);
void sv_push(StrVec *v, const char *s);
void sv_free(StrVec *v);

#endif
