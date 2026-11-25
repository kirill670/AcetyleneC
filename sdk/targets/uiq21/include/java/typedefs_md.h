/*
 * Copyright (c) 1997-99 By Symbian Ltd. All Rights Reserved.
 *
 * $Revision: 1.3 $
 * 
 */

#ifndef _EPOC_TYPEDEF_MD_H_
#define _EPOC_TYPEDEF_MD_H_

#include "bool.h"	/* shared definition of bool_t */


#define PLATFORMCHAR	wchar_t

typedef unsigned int	uint_t;
typedef long			int32_t;
typedef unsigned long	uint32_t;

/* Some generic #defines */

#define INT_OP(x,op,y)  (((#op[0]=='/')||(#op[0]=='%')) ?                  \
			 ( (((x)==0x80000000)&&((y)==-1)) ?            \
			     ((x) op 1) :                              \
			     ((x) op (y))) :                           \
			 ((x) op (y)))
#define NAN_CHECK(l,r,x) (!isnan((l))&&!isnan((r))) ? (x : 0)
#define IS_NAN(x) isnan(x)


/* 
 * 64-bit arithmetic
 *
 * EPOC32 compilers support a native 64-bit integer type, but don't necessarily
 * implement all of the functions directly. EUSER.LIB doesn't supply all of the
 * support functions for 64-bit integer, so we have to supply some of them.
 */

/* C structure which is the same size and shape as a TInt64 */
struct int64 { 
	uint32_t iLow; 
	uint32_t iHigh;
};

#ifdef __VC32__
typedef __int64	int64_t;
typedef unsigned __int64 uint64_t;
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif



#if defined(__MARM__)
/* MARM builds store doubles in a way which isn't compatible with int64_t.
 * If you load up the memory representation of a double as though it was an int64_t,
 * the top and bottom 32 bits of the IEEE representation will have been swapped
 * over. This affects java\runtime\classloader.c and java\lang\math.c
 */
#define ll_swap32(x) ll_or(ll_ushr(x,32),ll_shl(x,32))

#define ll_ieee2double(x)	ll_swap32(x)
#define ll_double2ieee(x)	ll_swap32(x)

#else

/* default for sensible hosts! 
 */
#define ll_ieee2double(x)	(x)
#define ll_double2ieee(x)	(x)

#endif

#ifdef __GCC32__
#define llval(a) int64_t(a##LL)
#else
#define llval(a) int64_t(a)
#endif

#define ll_low(a)	((long)a)

#define uint2ll(a)	((int64_t)(unsigned long)(a))	// can't end up negative anyway
#define int2ll(a)	((int64_t)(a))
#define ll2int(a)	((int)(a))

#define ll_add(a, b)	((a) + (b))
#define ll_sub(a, b)	((a) - (b))
#define ll_neg(a)	(-(a))

#define ll_and(a, b)	((a) & (b))
#define ll_or(a, b)	((a) | (b))
#define ll_xor(a, b)	((a) ^ (b))
#define ll_not(a)	(~(a))

#ifdef __WINS__
extern int64_t ll_mul(int64_t a, int64_t b);
extern int64_t ll_div(int64_t a, int64_t b);
extern int64_t ll_rem(int64_t a, int64_t b);
extern int64_t ll_shl(int64_t a, int n);
extern int64_t ll_shr(int64_t a, int n);
extern int64_t ll_ushr(int64_t a, int n);
#else
#define ll_mul(a, b) ((a) * (b))
#define ll_div(a, b) ((a) / (b))
#define ll_shl(a, n) ((a) << (n))
#define ll_shr(a, n) ((a) >> (n))
#define ll_rem(a, b) ((a) % (b))
#define ll_ushr(a, n) (((uint64_t)(a)) >> (n))
#endif

#ifdef __WINS__
#define float2l(f)	double2l(f)
#else
#define float2l(f)	((int32_t) (f))
#endif
extern int64_t float2ll(float f);
extern float ll2float(int64_t a);

#ifdef __WINS__
extern int32_t double2l(double f);
#else
#define double2l(f)	((int32_t) (f))
#endif
extern double ll2double(int64_t a);
extern int64_t double2ll(double f);

#define ll_zero_const	((int64_t)0)
#define ll_one_const	((int64_t)1)

/* comparison operators */

#define ll_ltz(ll)	((ll) < ll_zero_const)
#define ll_gez(ll)	((ll) >= ll_zero_const)
#define ll_eqz(a)	((a) == ll_zero_const)
#define ll_eq(a, b)	((a) == (b))
#define ll_ne(a,b)	((a) != (b))
#define ll_ge(a,b)	((a) >= (b))
#define ll_le(a,b)	((a) <= (b))
#define ll_lt(a,b)	((a) < (b))
#define ll_gt(a,b)	((a) > (b))

extern void ll2str(int64_t a, char *s, char *limit);

#include <stdlib.h>	/* For malloc() and free() */

struct stat;	/* there is such a thing at global scope - trust me! */

// KLUDGE -- FIX ME sjL: 20.i.99

#define ll_high(a)	((long)ll_shr(a, 32))
#define ll2ptr(a) ((void*)(a))
#define ll2double_bits(a) 
#define ptr2ll(a) ((jlong)(a))
// END OF KLUDGE

#endif /* !_EPOC_TYPEDEF_MD_H_ */
