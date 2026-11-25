/* RESOURCE.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#include <sys/time.h>
/**
@publishedAll
@released
*/
#define	RUSAGE_SELF	0		/* calling process */
#define	RUSAGE_CHILDREN	-1		/* terminated child processes */
/**
@publishedAll
@released
*/
struct rusage {
  	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
};

#endif

