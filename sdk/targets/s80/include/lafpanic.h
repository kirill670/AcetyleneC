/*
* ==============================================================================
*  Name        : lafpanic.h
*  Part of     : CUIKLAF
*  Interface   : LAF API
*  Description : Constants for LAF Panics
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef LAFPANIC_H
#define LAFPANIC_H


enum TLafPanic
	{
	ELafPanicPointerCursorIndexOutOfRange,
	ELafPanicFontIndexOutOfRange,
	ELafPanicConstantNotKnown,
	ELafPanicMsgWinBadHorizontalAlignment,
	ELafPanicMsgWinBadVerticalAlignment,
	ELafPanicBitmapIndexOutOfRange,
	ELafPanicThumbBitmapsNotEqualHeight,
	ELafPanicShaftBitmapsNotEqualWidth,
    ELafPanicNoEikonEnvironment,
    ELafPanicSkinNotAvailable
	};


#endif	// LAFPANIC_H

// End of File
