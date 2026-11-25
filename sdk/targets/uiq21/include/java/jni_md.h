
/* 
 * Copyright (c) 1997-99 By Symbian Ltd. All Rights Reserved.
 *
 * $Revision: 1.3 $
 */

#ifndef _EPOC_JNI_MD_H_
#define _EPOC_JNI_MD_H_

#if defined(__VC32__)

#pragma warning( disable : 4514 )	// unreferenced inline function has been removed

#endif /* __VC32__ */

#include "typedefs_md.h"

#define JNIEXPORT __declspec(dllexport)
#define JNICALL

typedef int32_t		jint;
typedef int64_t		jlong;
typedef signed char jbyte;

#endif /* !_EPOC_JNI_MD_H_ */
