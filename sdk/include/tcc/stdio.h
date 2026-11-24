#ifndef AC_STDIO_H
#define AC_STDIO_H
#include <stddef.h>
#include <stdarg.h>
extern int printf(const char *fmt, ...);
extern int sprintf(char *buf, const char *fmt, ...);
extern int snprintf(char *buf, size_t n, const char *fmt, ...);
extern int vprintf(const char *fmt, va_list ap);
extern int puts(const char *s);
extern int putchar(int c);
extern int getchar(void);
typedef struct AcFile FILE;
extern FILE *fopen(const char *path, const char *mode);
extern int fclose(FILE *f);
extern size_t fread(void *p, size_t sz, size_t n, FILE *f);
extern size_t fwrite(const void *p, size_t sz, size_t n, FILE *f);
extern int fflush(FILE *f);
extern int fseek(FILE *f, long off, int whence);
extern long ftell(FILE *f);
extern int remove(const char *path);
extern int rename(const char *a, const char *b);
extern void exit(int code);
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif
