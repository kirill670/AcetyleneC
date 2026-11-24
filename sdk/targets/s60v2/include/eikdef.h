// EIKDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDEF_H__)
#define __EIKDEF_H__

#include <e32std.h>

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
const TInt KEikMessageColorSchemeChange			=0x100056C4;
const TInt KEikMessageWindowsFadeChange			=0x10006890;

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

// added by LMB [20/6/00] for CEikCaptionedControl 
const TInt KEikMessageCaptionedControlEditableStateChange			=0x10008E99;
const TInt KEikMessageCaptionedControlNotEditableStateChange		=0x10008E9A;
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithGraphic			=0x101F5FBA;
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic			=0x101F5FBB;
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic			=0x101F5FBC;
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic		=0x101F5FBD;

const TInt KEikPartialForegroundFade			=0x101f538d;	// deprecated
const TInt KEikPartialForegroundNoFade			=0x101f538e;	// deprecated
const TInt KEikRequestPartialForegroundEvent	=0x101f53c5;	// deprecated
const TInt KEikClearPartialForegroundState		=0x101f54f4;
const TInt KEikPartialForeground				=0x101f6aab;

//UID Name: KUidDynamicLayoutVariantSwitch
//Number Allocation (Hexadecimal): 101F8121 To 101F8184 Inclusive.
const TInt KEikDynamicLayoutVariantSwitch	= 0x101F8121;
const TInt KEikDynamicLayoutVariantSwitch_ELAF	= 0x101F8122;
const TInt KEikDynamicLayoutVariantSwitch_ABRW	= 0x101F8123;
const TInt KEikDynamicLayoutVariantSwitch_APAC	= 0x101F8124;
//const TInt KEikDynamicLayoutVariantSwitch_LAST	= 0x101F8184

const TInt KEikInputLanguageChange = 0x101F8519;
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

#define KAknPhoneIdleViewId TVwsViewId(TUid::Uid(0x100058b3), TUid::Uid(0x100058b3))
#define KAknApplicationShellViewId TVwsViewId(TUid::Uid(0x101F4CD2), TUid::Uid(0x00000001))
/**
@internalTechnology
*/
#define COMPARE_BOOLS(a,b) (((a) && (b)) || (!(a) && !(b)))


// temporary change while TBitFlags is moved to bafl
#define private public
#include <ASShdBitFlags.h>
#undef private
// end of temporary change while TBitFlags is moved to bafl

#if !defined(__ASSERT_ALWAYS_NO_LEAVE)
#define __ASSERT_ALWAYS_NO_LEAVE(statements) { TRAPD(err, {statements;}); if (err) { _LIT(KCategory, "Unexpected leave"); User::Panic(KCategory, err); } }
#endif

#if !defined(__ASSERT_DEBUG_NO_LEAVE)
#ifdef _DEBUG
#define __ASSERT_DEBUG_NO_LEAVE(statements) __ASSERT_ALWAYS_NO_LEAVE(statements)
#else
#define __ASSERT_DEBUG_NO_LEAVE(statements) statements
#endif
#endif

#endif
