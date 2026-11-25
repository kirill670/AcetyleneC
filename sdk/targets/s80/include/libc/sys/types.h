/* TYPES.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

# include <stddef.h>	
# include <machine/types.h>

# ifndef	_POSIX_SOURCE
/**
@internalComponent
*/
#  define	physadr		physadr_t
#  define	quad		quad_t
/**
@publishedAll
@released
*/
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
typedef	unsigned short	ushort;		/* System V compatibility */
typedef	unsigned int	uint;		/* System V compatibility */
# endif	/*!_POSIX_SOURCE */
/**
@publishedAll
@released
*/
#ifndef __time_t_defined
typedef _TIME_T_ time_t;
#define __time_t_defined
#endif
/**
@publishedAll
@released
*/
typedef	long	daddr_t;
typedef	char *	caddr_t;
/**
@publishedAll
@released
*/
#ifdef __go32_types__
typedef	unsigned long	ino_t;
#else
#ifdef __sparc__
typedef	unsigned long	ino_t;
#else
typedef	unsigned short	ino_t;
#endif
#endif
/**
@publishedAll
@released
*/
typedef	short	dev_t;
/**
@publishedAll
@released
*/
typedef	long	off_t;
/**
@publishedAll
@released
*/
typedef	unsigned short	uid_t;
typedef	unsigned short	gid_t;
typedef int pid_t;
typedef	long	key_t;
typedef int mode_t;
/**
@publishedAll
@released
*/
typedef unsigned int nlink_t;

# ifndef	_POSIX_SOURCE
/**
@internalComponent
*/
#  define	NBBY	8		/* number of bits in a byte */
/**
Select uses bit masks of file descriptors in longs.
These macros manipulate such bit fields (the filesystem macros use chars).
FD_SETSIZE may be defined by the user, but the default here
should be >= NOFILE (param.h).
@internalComponent
*/
#  ifndef	FD_SETSIZE
#	define	FD_SETSIZE	60
#  endif
/**
@internalComponent
*/
typedef	long	fd_mask;
#  define	NFDBITS	(sizeof (fd_mask) * NBBY)	/* bits per mask */
#  ifndef	howmany
#	define	howmany(x,y)	(((x)+((y)-1))/(y))
#  endif
/**
@publishedAll
@released
*/
typedef	struct fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

/**
@internalAll
*/
#  define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#  define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#  define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#  define	FD_ZERO(p)	bzero((caddr_t)(p), sizeof (*(p)))


# endif	/* _POSIX_SOURCE */
#undef __go32_types__
#endif	/* _SYS_TYPES_H */
