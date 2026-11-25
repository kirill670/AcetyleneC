/*
* ==============================================================================
*  Name        : eikdef.h
*  Part of     : UIKON
*  Interface   : Define API
*  Description : UIKON constants
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


#ifndef EIKDEF_H
#define EIKDEF_H

// INCLUDES
#include <e32std.h>
#include <coedef.h>
// CONSTANTS

/** This is used in combination with a specified position to place a popout on 
the display. 

The TPopupTargetPosType enum identifies which corner of the popout 
will be placed in the given target position. The default is the top left corner. 

@publishedAll
@released */
enum TPopupTargetPosType
	{
	/** Places the popout with the top left corner in the specified position. */
	EPopupTargetTopLeft,
	/** Places the popout with the top right corner in the specified position. */
	EPopupTargetTopRight,
	/** Places the popout with the bottom left corner in the specified position. */
	EPopupTargetBottomLeft,
	/** Places the popout with the bottom right corner in the specified position. */
	EPopupTargetBottomRight
	};

/**
@publishedAll
@released
*/
#define iEikonEnv (STATIC_CAST(CEikonEnv*,iCoeEnv))

/**
@publishedPartner
@released
*/
#define KEikEditableControlBorder TGulBorder::EShallowSunken

/**
@internalComponent
*/
#if defined(_DEBUG)
#define __UHEAP_CHECK_INTEGRITY User::Heap().Check()
#else
#define __UHEAP_CHECK_INTEGRITY
#endif

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_FIRST		32

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_LAST		39

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_SIMPLE		32

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_DIALOG_LOAD	33

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_APP_LAUNCH	34

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_CLOCK		35

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_CALENDER	35

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_LIBS_LOAD	36

/**
@internalComponent
*/
#define PROFILE_POINT_EIKON_ADD_RES		37

/**
@internalComponent
*/
#define KEikEikonBitmapStore		KNullDesC

/**
@publishedPartner
@released
*/
_LIT(KEikDefaultAppBitmapStore,"*");

/**
@publishedPartner
@released
*/
const TInt KUidValueEikColorSchemeChangeEvent	=0x10006956;

/**
@internalComponent
*/
const TInt KEikCustomColorsArrayValue			=0x100057C2;

/**
@publishedAll
@released
*/
const TInt KEikMessageFadeAllWindows			=0x100056C2;

/**
@publishedAll
@released
*/
const TInt KEikMessageUnfadeWindows				=0x100056C3;

/**
@publishedAll
@released
*/
const TInt KEikMessageColorSchemeChange			=KUidValueCoeColorSchemeChangeEvent;

/**
@publishedAll
@released
*/
#define KEikColorResourceChange KEikMessageColorSchemeChange // for source compatibility

/**
@publishedAll
@released
*/
const TInt KEikMessageZoomChange				=0x100057C3;

/**
@publishedAll
@released
*/
const TInt KEikMessageVirtualCursorStateChange	=0x10005D0A;

/**
@publishedAll
@released
*/
const TInt KEikMessageCapsLock					=0x100048F9;

/**
@publishedAll
@released
*/
const TInt KEikMessagePrepareForSave			=0x100069FD;

/**
@publishedAll
@released
*/
const TInt KEikMessageEmbedLevelChange			=0x1000A4AA;

/**
@publishedPartner
@released
*/
const TInt KEikResIdQueryDialog	=0;

/**
@publishedPartner
@released
*/
const TInt KEikResIdInfoDialog	=1;

/**
@internalTechnology
*/
#define COMPARE_BOOLS(a,b) (((a) && (b)) || (!(a) && !(b)))

#endif	// EIKDEF_H

// End of File
