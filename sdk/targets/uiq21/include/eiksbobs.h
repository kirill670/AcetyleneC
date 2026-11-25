// EIKSBOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSBOBS_H__)
#define __EIKSBOBS_H__

/**
 * Communicates types of user interaction with scrollbars.
 *
 * To receive notification of scroll bar events, classes must implement
 * the mixin <code>MEikScrollBarObserver</code>. Each scroll bar has a
 * scroll bar observer registered with it in its construction, and will
 * call the <code>HandleScrollEventL()</code> of its observer when the
 * user moves the scroll bar.
 */
enum TEikScrollEvent
	{
	EEikScrollLeft=1,				/** User scrolled leftwards. */
	EEikScrollUp,					/** User scrolled upwards. */
	EEikScrollRight,				/** User scrolled rightwards. */
	EEikScrollDown,					/** User scrolled downwards. */
	EEikScrollPageLeft,				/** User scrolled leftwards by a page. */
	EEikScrollPageUp,				/** User scrolled upwards by a page. */
	EEikScrollPageRight,			/** User scrolled rightwards by a page. */
	EEikScrollPageDown,				/** User scrolled downwards by a page */
	EEikScrollHome,					/** User scrolled to the maximum extent leftwards. */
	EEikScrollTop,					/** User scrolled to the maximum extent upwards. */
	EEikScrollEnd,					/** User scrolled to the maximum extent rightwards. */
	EEikScrollBottom,				/** User scrolled to the maximum extent downwards. */
	EEikScrollThumbDragHoriz,		/** User dragged the thumb horizontally. */
	EEikScrollThumbDragVert,		/** User dragged the scroll thumb vertically. */
	EEikScrollThumbReleaseHoriz,	/** User released the scroll thumb on a horizontal scroll bar. */
	EEikScrollThumbReleaseVert		/** User released the scroll thumb on a vertical scroll bar. */
	};

class CEikScrollBar;

/**
 *
 * This mixin is implemented by classes wishing to receive notification
 * about scroll events from a scroll bar.
 *
 * Each scroll bar has a scroll bar observer registered with it in its
 * construction, and will call the <code>HandleScrollEventL()</code> of
 * its observer when the user moves the scroll bar.Scroll bar observers
 * are not owned by their scroll bar, and must be deleted explicitly. It
 * is possible to register the same scroll bar observer with many scroll
 * bars. This class is intended for derivation by all classes interested
 * in scroll events from <code>CEikScrollBar</code>s.
 *
 * @since 6.0
 * @lib ""
 */
class MEikScrollBarObserver
	{
public:
	/**
	 * Handles scroll events.
	 *
	 * This function is called by the <code>CEikScrollBar</code> object with
	 * which this scroll bar observer object is registered. Implementations
	 * should handle scroll events appropriately.
	 *
	 * @param     "CEikScrollBar* aScrollBar"
	 *            Pointer to the originating scroll bar object.
	 * @param     "TEikScrollEvent aEventType"
	 *            A scroll event.
	 */
	virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType)=0;
	};

#endif
