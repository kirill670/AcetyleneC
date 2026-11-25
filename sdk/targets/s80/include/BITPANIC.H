// BITPANIC.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __BITPANIC_H__
#define __BITPANIC_H__

#include <e32def.h>
/**
@internalTechnology
*/
enum TBitgdiPanic
	{
	EBitgdiPanicNoDevicePresent=1,
	EBitgdiPanicNoFBSConnection,
	EBitgdiPanicNoFontSelected,
	EBitgdiPanicNoSpriteSet,
	EBitgdiPanicInvalidScreenDeviceLibrary,
	EBitgdiPanicInvalidParameter,
	EBitgdiPanicInvalidColor,
	EBitgdiPanicInvalidDrawMode,
	EBitgdiPanicInvalidDisplayMode,
	EBitgdiPanicInvalidRegion,
	EBitgdiPanicInvalidWindowHandle,
	EBitgdiPanicInvalidFont,
	EBitgdiPanicInvalidBitmap,
	EBitgdiPanicOutOfBounds,
	EBitgdiPanicReadOnly,
	EBitgdiPanicPolygonFiller,
	EBitgdiPanicZeroLength,
	EBitgdiPanicNullPointer,
	EBitgdiPanicInvalidPointer,
	EBitgdiPanicCharacterTooBig,
	EBitgdiPanicInvalidHalValue,
	EBitgdiPanicInvalidArg,
	EBitgdiPanicNegativeShift
	};

/**
@internalComponent
*/
GLREF_C void Panic(TBitgdiPanic aPanicCode);

/**
Required to ensure BC between NGage and 7.0S platforms.  
Functions are exported at ordinal corresponding to where NGage platform
has extended this library and must not be moved.
@since 7.0S
@internalComponent
*/
IMPORT_C void DummyReserved1();
IMPORT_C void DummyReserved2();
IMPORT_C void DummyReserved3();
IMPORT_C void DummyReserved4();
IMPORT_C void DummyReserved5();
IMPORT_C void DummyReserved6();
IMPORT_C void DummyReserved7();
IMPORT_C void DummyReserved8();
IMPORT_C void DummyReserved9();
IMPORT_C void DummyReserved10();

#endif

