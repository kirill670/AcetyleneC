/*
* ==============================================================================
*  Name        : lafpublc.h
*  Part of     : App-Framework / UIKLAFGT
*  Interface   : LAF API
*  Description : Consts and enum flags for various controls.
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


#ifndef LAFPUBLC_H
#define LAFPUBLC_H

// INCLUDES
#include <e32std.h>

// CONSTANTS
const TInt KLafScrollBarButtonPositionMask = 0x00C0;	// sets all bits in EButtonsXxx range for SLafScrollBar::TEikScrollBarFlags

struct SLafScrollButton
	{
	enum TType
		{
		ENudgeLeft,
		ENudgeUp,
		ENudgeRight,
		ENudgeDown,
		EPageLeft,
		EPageUp,
		EPageRight,
		EPageDown,
		EHome,
		ETop,
		EEnd,
		EBottom
		};
	};

struct SLafScrollBar
	{
	enum TEikScrollBarFlags
		{
		EEikScrollBarDefaultBehaviour	=0x0000,
		EEikScrollBarNoNudgeButtons		=0x0001,
		EEikScrollBarHasPageButtons		=0x0002,
		EEikScrollBarHasHomeEndButtons  =0x0004,
		EEikScrollBarNoShaftOrThumb 	=0x0008,
		EEikScrollBarShaftButNoThumb 	=0x0010,
		EButtonsAtStartOfShaft  		=0x0040,
		EButtonsAtEndOfShaft 			=0x0080,
		EButtonsEitherSideOfShaft 		=EButtonsAtStartOfShaft|EButtonsAtEndOfShaft,
		ENoAutoDimming					=0x0100
		};

	enum TOrientation
		{
		EVertical,
		EHorizontal
		};

	};

struct SLafListBox
	{
	enum TFlags
		{
		EMultipleSelection			= 0x0001,
		ENoExtendedSelection		= 0x0002,
		EIncrementalMatching		= 0x0004,
		EPopout						= 0x0008,
		ELeftDownInViewRect			= 0x0010,
		EItemDoubleClicked			= 0x0020,
		EKeepModel					= 0x0040,
		EScrollBarSizeExcluded		= 0x0080,
		EStateChanged				= 0x0100,
		ECreateOwnWindow			= 0x0200,
        ENoFirstLetterMatching      = 0x0400,
		EPaintedSelection			= 0x0800,
		EHiddenHighlight			= 0x1000
		};
    enum TListItemAttribute
        {
		ECurrent    = 0x0001,		// may be drawn with a frame
		EEmphasized = 0x0002,		// special highlight (not selected)
		ESelected   = 0x0004,		// usually different than emphasized
		// This last attribute is used to control that one can use only
		// valid attributes above. So do not use it at all.
		EMask		= 0x0007 // sum of all others attributes
        };
	enum TListItemFlags
		{
		EItemDrawMarkSelection			= 0x0001,
		EItemPaintedSelection			= 0x0002,
		EItemDrawOnlyActiveSelection	= 0x0004,
		EDataWidthClippedToViewRect		= 0x0008
		};
	};

struct SLafScrollThumb
	{
	enum TOrientation
		{
		EVertical,
		EHorizontal
		};
	};

struct SLafScrollBarFrame
	{
	enum TScrollBarVisibility
		{
		EOff,
		EOn,
		EAuto
		};

	enum TScrollBarSide
		{
		EBottomOrRight,
		ETopOrLeft
		};

	enum TScrollBarManagement
		{
		EComponent,
		EFloating,
		EApplicationScrollBar
		};
	};

struct SLafControlGroup
	{
	enum TStartCorner
		{
		EFromTopLeft=0x1,
		EFromTopRight=0x2,
		EFromBottomLeft=0x3,
		EFromBottomRight=0x4
		};
	enum TOrientation
		{
		ELayHorizontally=0x10,
		ELayVertically=0x20
		};
	};

struct SLafButtonGroupContainer
	{
	enum TUse
		{
		EView,
		EDialog,
		EToolbar,
		ECba,
		EDialogButtons
		};
	enum TOrientation
		{
		EVertical,
		EHorizontal
		};
	enum TLocation
		{
		EInternal,	// E.g. dialog buttons.
		EExternal	// E.g. toolbar or cba.
		};
	};

struct SLafMenuBar
	{
	enum { ENominalTextLength = 40 };
	};

struct SLafMenuPane
	{
	enum THighlightType
		{
		ENoHighlight,
		EDrawHighlight,
		ERemoveHighlight
		};
	enum TSuperHotKey
		{
		ESuperHotKeyOffsetNotSet = 0
		};
	};

struct SLafButtonBase
	{
	enum TDrawState
		{
		EDrawClear					=0x00,
		EDrawSet					=0x01,
		EDrawIndeterminate			=0x02,
		EDrawClearPressed			=0x10,
		EDrawSetPressed				=0x11,
		EDrawIndeterminatePressed	=0x12
		};
	};


#endif	// LAFPUBLC_H

// End of File
