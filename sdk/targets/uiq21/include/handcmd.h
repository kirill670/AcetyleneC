// HANDCMD.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
// Command Code for handwriting AnimDLL
//

#if !defined(__HANDCMD_H__)
#define __HANDCMD_H__

#include <gdi.h>
#include <TextInputServerParameters.h>

enum THandWritingOpcodes
	{
	// some codes are reserved by the Text Input framework
	EHwOpSetDrawData = EHwFirstAvailableOp,
	EHwOpGetLastChar,
	};

struct THandwritingDrawData
	{
	TRgb	iInitialBitmapColor;		// Color for the Background (This will be the color of Mask)
	TRgb	iLineColor;					// Color of the stroke line
	TRgb	iModeMarkerColor;			// Color of the Mode Marker (triangle)
	TInt	iModeMarkerSize;			// Size of the Mode Marker (triangle)
	TInt	iModeMarkerPercentage;		// Screen splitting (by Mode Marker) in percentage
	TInt	iLineWidth;					// Width of the stroke line
	TInt	iMaskLineWidth;				// Width of the Mask (if any) under the stroke line
										// This one has to/should depend on iLineWidth
	TInt	iEndPointWidth;				// Size of the EndPoint
										// This one has to/should depend on iLineWidth and iMaskLineWidth (if any)
	TInt	iHandShakingValueX;			// Shaking that is allowed, before a movement is seen as movement (X direction)
	TInt	iHandShakingValueY;			// Shaking that is allowed, before a movement is seen as movement (Y direction)
	TInt	iNormalModeTimer;			// Timer that regulates the access ot the UI
	TInt	iClearTimer;				// Timer that determines how long the character should stay on the screen
	TInt	iFlushTimer;				// Timer that gets called if the cleartimer is 0, and you want to write a "ae", "oe", ...
	TInt	iClearExtendedTimer;		// As iClearTimer, but for (eventual) 2 Stroke characters, like x, t, f, ...
	TInt	iExtendedModeTimer;			// Timer that determines when to leave automaticly the Extended Mode
	TBool	iHorizontalSeparation;		// Horizontal (ETrue) or Vertical (EFalse) split of the screen (in Numeric
										// and Alpha Field).
	TBool	iLeftNumericField;			// if Vertical Split (iHorizontalSeparation == EFalse), put NumericField on the
										// left (ETrue), or right (EFalse) side.
	TBool	iAllowShortCuts;			// Enables/Disables shortcut keys like Cut, Copy, Paste, ...
	};

#endif	// __HANDCMD_H__
