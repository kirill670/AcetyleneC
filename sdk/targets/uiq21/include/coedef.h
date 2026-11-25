// COEDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEDEF_H__)
#define __COEDEF_H__

#include <e32std.h> 
#include <guldef.h> // only requried for linited source compatability with releases prior to 250

/**
 * Event handling flags.
 *
 * These should be returned by <code>CCoeControl::OfferKeyEventL()</code>
 * to indicate whether or not a key event was processed by the control.
 */
enum TKeyResponse
	{
	EKeyWasNotConsumed,		/** The key event was not handled. */
	EKeyWasConsumed			/** The key event was handled. */
	};

/**
 * Control redraw flags.
 *
 * Passed to <code>CCoeControl::SetFocus()</code> to indicate the
 * requirements for control redrawing.
 */
enum TDrawNow
	{
	ENoDrawNow,		/** Redraw of the control is not required immediately. */
	EDrawNow		/** Redraw control immediately. */
	};

/**
 * Window priority values.
 *
 * These are passed in the <code>aOrdinalPriority</code> argument to
 * <code>RWindowTreeNode::SetOrdinalPosition()</code>.
 */
enum TCoeWinPriority
	{
	ECoeWinPriorityNeverAtFront		=-1000,		/** -1000 */
	ECoeWinPriorityLow				=-750,		/** -750 */
	ECoeWinPriorityNormal			=0,			/** 0 */
	ECoeWinPriorityMedium			=500,		/** 500 */
	ECoeWinPriorityHigh				=750,		/** 750 */
	ECoeWinPriorityFep				=900,		/** 900 */
	ECoeWinPriorityAlwaysAtFront	=1000		/** 1000 */
	};


// UID number generated, when a colour scheme change event is called
const TInt KUidValueCoeColorSchemeChangeEvent	=0x100056C4;


#if defined(_DEBUG)
#define __DEBUG_CHECK_HEAP_INTEGRITY User::Heap().Check()
#else
#define __DEBUG_CHECK_HEAP_INTEGRITY
#endif

#define CTRL(x) ((x)-'a'+1) // not an inline function since that can't be put as the case of a switch statement

#define EAllStdModifiers (EModifierFunc|EModifierCtrl|EModifierShift)

#endif
