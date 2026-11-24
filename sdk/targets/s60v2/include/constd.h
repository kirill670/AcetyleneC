// CONSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONSTD_H__)
#define __CONSTD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/**
@internalComponent
*/
enum TConPanic
	{
	EPanicFindAllConvNotCalled,
	EPanicDriveOutOfRange,
	EPanicConverterNotStored,
	EPanicFindAllCnfNotCalled,
	EPanicConvLangListEmpty
	};

/**
@internalComponent
*/
GLREF_C void Panic(TConPanic aPanic);

/**
@internalComponent
*/
GLREF_C const TDesC& Category();

 
#endif
