/* SIGNAL.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SIGNAL_H_
#define _SIGNAL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"
#include <sys/signal.h>
/**
@publishedAll
@released
*/
typedef int	sig_atomic_t;		/* Atomic entity type (ANSI) */
/**
@publishedAll
@released
*/
#define SIG_DFL ((void (*)())0)		/* Default action */
#define SIG_IGN ((void (*)())1)		/* Ignore action */
#define SIG_ERR ((void (*)())-1)	/* Error return */
/**
@publishedAll
@released
*/
typedef void (*_sig_func_ptr) ();
/**
@publishedAll
@released
*/
extern _sig_func_ptr signal(int, _sig_func_ptr);
extern int raise(int);

#ifdef __cplusplus
}
#endif
#endif /* _SIGNAL_H_ */
