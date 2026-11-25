/* DIRENT.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_DIRENT_H_
#define _SYS_DIRENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
/**
@publishedAll
@released
*/
typedef struct __EPOC32_DIR DIR;
typedef struct __EPOC32_WDIR WDIR;
/**
@publishedAll
@released
*/
IMPORT_C DIR *opendir (const char *);
IMPORT_C WDIR *wopendir (const wchar_t *);
IMPORT_C struct dirent *readdir (DIR *);
IMPORT_C struct wdirent *wreaddir (WDIR *);
IMPORT_C void rewinddir (DIR *);
IMPORT_C int closedir (DIR *);
IMPORT_C void wrewinddir (WDIR *);
IMPORT_C int wclosedir (WDIR *);

/** 
telldir and seekdir aren't required by POSIX 
@publishedAll
@released
*/
IMPORT_C off_t telldir(const DIR *);
IMPORT_C void seekdir(DIR *,off_t);
IMPORT_C off_t wtelldir(const WDIR *);
IMPORT_C void wseekdir(WDIR *,off_t);
/**
@publishedAll
@released
*/
#define __MAXNAMLEN	255
/**
@publishedAll
@released
*/
#define d_ino	d_fileno	/* compatibility */
/**
@publishedAll
@released
*/
struct dirent {
	unsigned long	d_fileno;
	unsigned short	d_namlen;
	char*		d_name;
};
/**
@publishedAll
@released
*/
struct wdirent {
	unsigned long	d_fileno;
	unsigned short	d_namlen;
	wchar_t*		d_name;
};
/**
@publishedAll
@released
*/
#include <sys/reent.h>
IMPORT_C DIR *_opendir_r (struct _reent*, const char *);
IMPORT_C WDIR *_wopendir_r (struct _reent*, const wchar_t *);
IMPORT_C struct dirent *_readdir_r(struct _reent*, DIR *);
#ifdef __cplusplus
}
#endif
#endif /* !_SYS_DIRENT_H_ */