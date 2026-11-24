/*
* ============================================================================
*  Name     : AknPanic.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
// EIKPANIC.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNPANIC_H__)
#define __AKNPANIC_H__

#include <e32def.h>

enum TAknPanic
	{
	EAknPanicFormattedCellListInvalidBitmapIndex,
	EAknPanicNoSuchControlInStack,
	EAknPanicListboxUndefined,
	EAknPanicListboxSizeIsNotAccordingToLAFSpec,
	EAknPanicListboxShortcutValueNotHandled,
	EAknPanicListboxShortcutInvalidValue,
	EAknPanicOutOfRange,
	EAknPanicListboxLayoutProblem,
	EAknPanicLAF,
	EAknPanicLayoutResourceProblem,
	EAknPopupCorrupt, // Added for Release 16
    EAknPanicNullPointer,
	EAknPanicLayoutMismatchBetweenMarginsAndParentRect,
	EAknPanicLayoutTextResourceProblem,
	EAknPanicLayoutRectResourceProblem,
	EAknPanicLayoutEdwinResourceProblem,
	EAknPanicLayoutMfneResourceProblem,
	EAknPanicLayoutControlResourceProblem,
	EAknPanicLayoutIncorrectEdwinSize,
	EAknPanicLayoutControlSetRectChangedControlSize,
	EAknPanicNoAnimationData,
	EAknPanicUnknownAnimationType,
	EAknPanicNoUserAnimation,
	EAknPanicAnimationCorrupt,
	EAknPanicDCADecoratorIndexOutOfRange,
	EAknPanicPopupFieldListInvalidDecorator,
	EAknPanicPopupFieldInvalidValue,
	EAknPanicPopupFieldUninitialisedMember,
	EAknPanicPopupFieldEditComboInsufficientSize,
	EAknPanicQueryTimeArrayTimeFormatLeave,
	EAknPanicLayoutTextNotCalled,
	EAknPanicLayoutRectNotCalled,
	EAknStatusPaneUidIndic,
	EAknPanicLayoutDoesNotExists,
	EAknPanicListBoxLayoutDecoratorMemoryAllocation,
	EAknPanicPopupFieldUndefinedMode,
	EAknPanicPopupFieldWrongMode,
	EAknPanicPopupFieldSelectionListDoesntExist,
	EAknPanicPopupFieldSelectionListAlreadyExists,
	EAknPanicPopupFieldListNotImplemented,
	EAknPanicPopupFieldArrayIsEmpty,
	EAknPanicLayoutPopupFieldResourceProblem,
	EAknPanicInvalidResourceData,
	EAknPanicListBoxNotSupportedByListQuery,
	EAknPanicQueryDateArrayTimeFormatLeave,
	EAknPanicPopupFieldCBADoesntExist,
	EAknPanicPopupSettingListMenuListDoesntExist,
	EAknPanicPopupSettingListMenuListAlreadyExists,
	EAknPanicPopupSettingListListNotImplemented,
	EAknPanicLayoutPopupSettingListResourceProblem,
	EAknPanicPopupSettingListInvalidValue,
	EAknPanicPopupSettingListUninitialisedMember,
	EAknPanicOverflow,
	EAknPanicKeyLockObserverAlreadyExists,
	EAknPanicKeyLockObserverNotFound,
	EAknPanicQueryValueInvalidMode,
    EAknPanicNotSupported,
	EAknPanicWrongListBoxTypeUsedInPopupWindow,
	EAknPanicInvalidValue,
	EAknPanicObjectNotFullyConstructed,
	EAknPanicSelfCheckFailure,
	EAknPanicLayoutMissing_AknLayout,
	EAknPanicLayoutMissing_ApacLayout,
    EAknPanicInconsistentDescriptors,
    EAknPanicListBoxItemDrawerNotCreated,
    EAknPanicLayoutMissing_CdlFont, 
    EAknPanicFontProvisionFailure,
    EAknPanicNotifierPluginCreationFailure,
	EAknPanicPopupFieldNoFieldRectSet,
	EAknPanicWindowGroupNotInTaskList,
	EAknPanicInconsistentUnits,
    EAknPanicRadioButtonSettingPageListDoesntExist,
	EAknPanicLayoutConfigBadScreenModeIndex,
	EAknPanicLayoutConfigBadHardwareStateIndex,
	EAknPanicSgccLayoutConfigNull,
	EAknPanicLayoutConfigUnpackFail,
	EAknPanicSgccNull
	};

GLREF_C void Panic(TAknPanic aPanic);

#endif
