#ifndef AC_STDLIB_H
#define AC_STDLIB_H
#include <stddef.h>
extern void *malloc(size_t n);
extern void *calloc(size_t n, size_t sz);
extern void *realloc(void *p, size_t n);
extern void free(void *p);
extern int atoi(const char *s);
extern long atol(const char *s);
extern unsigned long strtoul(const char *s, char **end, int base);
extern long strtol(const char *s, char **end, int base);
extern int abs(int v);
extern void abort(void);
#endif
