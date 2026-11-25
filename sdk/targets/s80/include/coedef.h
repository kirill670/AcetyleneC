// COEDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEDEF_H__)
#define __COEDEF_H__

#include <e32std.h> 
#include <guldef.h> // only requried for limited source compatability with releases prior to 250

/** 
 * The enumeration <code>TKeyResponse</code> specifies the event-handling flags.
 * These should be returned by <code>CCoeControl::OfferKeyEventL()</code> to 
 * indicate whether or not a key event was processed by the control. 
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
enum TKeyResponse
    {
    /** The key event was not handled. */
    EKeyWasNotConsumed,
    /** The key event was handled. */
    EKeyWasConsumed
    };

/** 
 * The enumeration <code>TDrawNow</code> specifies the control redraw flags.
 * These are passed to <code>CCoeControl::SetFocus()</code> to 
 * indicate the requirements for control redrawing. 
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
enum TDrawNow
    {
    /** Redraw of the control is not required immediately. */
    ENoDrawNow,
    /** Redraw control immediately. */
    EDrawNow
    };

/** 
 * The enumeration <code>TCoeWinPriority</code> specifies the window priority 
 * values. These are passed in the <code>aOrdinalPriority</code> argument to 
 * <code>RWindowTreeNode::SetOrdinalPosition()</code>.
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
enum TCoeWinPriority
    {
    /** -1000 */
    ECoeWinPriorityNeverAtFront     =-1000,
    /** -750 */
    ECoeWinPriorityLow              =-750,
    /** 0 */
    ECoeWinPriorityNormal           =0,
    /** 500 */
    ECoeWinPriorityMedium           =500,
    /** 750 */
    ECoeWinPriorityHigh             =750,
    /** 900 */
    ECoeWinPriorityFep              =900,
    /** 1000 */
    ECoeWinPriorityAlwaysAtFront    =1000
    };

/** 
 * The message UID sent when a colour scheme change event occurs. 
 * @internal Technology 
 */
const TInt KUidValueCoeColorSchemeChangeEvent   =0x100056C4;

/** @internal Technology */
#if defined(_DEBUG)
#define __DEBUG_CHECK_HEAP_INTEGRITY User::Heap().Check()
#else
#define __DEBUG_CHECK_HEAP_INTEGRITY
#endif

/** 
 * the control key modifier. Key codes get changed when the Ctrl key modifier 
 * is pressed at the same time as the key. The <code>CTRL</code> macro is used 
 * to shift the key character appropriately. <b>Note</b>: This is not an inline 
 * method because that can't be used as the case of a switch statement.
 * @publishedAll
 * @released 
 */
#define CTRL(x) ((x)-'a'+1)

/** 
 * the constant that represents all standard keyboard modifier keys. 
 * @publishedAll
 * @released 
 */
#define EAllStdModifiers (EModifierFunc|EModifierCtrl|EModifierShift)

#endif
