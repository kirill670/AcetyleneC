// ET_STRUC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
/**
@file ET_STRUC.H
@publishedAll
*/

#if !defined(__ET_STRUC_H__)
#define __ET_STRUC_H__

#if !defined(__ETEL_H__)
#include "ETEL.H"
#endif
/**
@internalComponent
*/
struct TCallInfoIndex
	{
	TInt iIndex;
	RLine::TCallInfo iInfo;
	};
/**
@internalComponent
*/
struct TLineInfoIndex
	{
	TInt iIndex;
	RPhone::TLineInfo iInfo;
	};
/**
@internalTechnology
*/
#define KChunkName _L ("FaxProgress")

#endif
