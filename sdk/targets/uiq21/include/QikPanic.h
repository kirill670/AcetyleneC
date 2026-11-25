// qikpanic.h
//
// Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.

#ifndef __QIKPANIC_H__
#define __QIKPANIC_H__

enum TQikPanic
	{
	EQikPanicNotAValidZoomLevel					= 1,
	EQikPanicIncorrectTabIndex					= 2,
	EQikPanicCategoryHandleNotFound				= 3,
	EQikPanicContainerWindowNotSet				= 4,
	EQikPanicCategoryModelIntegrityCheckFailed	= 5,
	EQikPanicCouldNotReturnToBaseView			= 6,
	EQikPanicToolBarHasNoObserver				= 7,
	EQikPanicToolBarNullControl					= 8,

	// panics defined by the virtual 
	EQikPanicReferencedOutsideKeytopArray		= 10,
	EQikPanicNoRecognizedKeytopType				= 11,
	EQikPanicNotAValidSound						= 12,
	EQikPanicUnexpectedExtensionUid				= 13
	};

GLDEF_C void Panic(TQikPanic aPanic);

#endif