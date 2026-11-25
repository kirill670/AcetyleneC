// EIKDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDEF_H__)
#define __EIKDEF_H__

#include <e32std.h>
#include <coedef.h>

/**
 *
 * This is used in combination with a specified position to place a
 * popout on the display.
 *
 * The <code>TPopupTargetPosType</code> enum identifies which corner of
 * the popout will be placed in the given target position. The default is
 * the top left corner.
 * 
 */
enum TPopupTargetPosType
	{
	EPopupTargetTopLeft,		/** Places the popout with the top left corner in the specified position. */
	EPopupTargetTopRight,		/** Places the popout with the top right corner in the specified position. */
	EPopupTargetBottomLeft,		/** Places the popout with the bottom left corner in the specified position. */
	EPopupTargetBottomRight		/** Places the popout with the bottom right corner in the specified position. */
	};

#define iEikonEnv (STATIC_CAST(CEikonEnv*,iCoeEnv))

#define KEikEditableControlBorder TGulBorder::EShallowSunken
#if defined(_DEBUG)
#define __UHEAP_CHECK_INTEGRITY User::Heap().Check()
#else
#define __UHEAP_CHECK_INTEGRITY
#endif

#define PROFILE_POINT_EIKON_FIRST		32
#define PROFILE_POINT_EIKON_LAST		39

#define PROFILE_POINT_EIKON_SIMPLE		32
#define PROFILE_POINT_EIKON_DIALOG_LOAD	33
#define PROFILE_POINT_EIKON_APP_LAUNCH	34
#define PROFILE_POINT_EIKON_CLOCK		35
#define PROFILE_POINT_EIKON_CALENDER	35
#define PROFILE_POINT_EIKON_LIBS_LOAD	36
#define PROFILE_POINT_EIKON_ADD_RES		37

#define KEikEikonBitmapStore		KNullDesC
_LIT(KEikDefaultAppBitmapStore,"*");

const TInt KUidValueEikColorSchemeChangeEvent	=0x10006956;
const TInt KEikCustomColorsArrayValue			=0x100057C2;

const TInt KEikMessageFadeAllWindows			=0x100056C2;
const TInt KEikMessageUnfadeWindows				=0x100056C3;
const TInt KEikMessageColorSchemeChange			=KUidValueCoeColorSchemeChangeEvent;
#define KEikColorResourceChange KEikMessageColorSchemeChange // for source compatibility
const TInt KEikMessageZoomChange				=0x100057C3;
const TInt KEikMessageVirtualCursorStateChange	=0x10005D0A;
const TInt KEikMessageCapsLock					=0x100048F9;
const TInt KEikMessagePrepareForSave			=0x100069FD;
const TInt KEikMessageEmbedLevelChange			=0x1000A4AA;


const TInt KEikResIdQueryDialog	=0;
const TInt KEikResIdInfoDialog	=1;

#define COMPARE_BOOLS(a,b) (((a) && (b)) || (!(a) && !(b)))

#endif
