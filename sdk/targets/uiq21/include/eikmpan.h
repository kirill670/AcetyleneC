// EIKMISC.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__EIKMISC_PAN__)
#define __EIKMISC_PAN__

enum TEikMiscPanic
	{
	EEikPanicDuplicateWindowButtonId
	};

GLREF_C void Panic(TEikMiscPanic aPanic);

#endif
