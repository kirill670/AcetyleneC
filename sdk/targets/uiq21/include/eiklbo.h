// EIKLBO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLBO_H__)
#define __EIKLBO_H__

class CEikListBox; 

/**
 *
 * List box observer interface.
 *
 * Each list box observer may be registered with a number of list boxes;
 * each of these send events to the list box observer through its
 * <code>HandeListBoxEventL()</code> method.Writing derived classes:
 * Application authors should implement a class which derives from this
 * interface to receive events from list boxes.
 *
 * @since 6.0
 * @lib ""
 */
class MEikListBoxObserver
	{
public:
	/**
	 * List box event codes.
	 */
	enum TListBoxEvent
		{
		EEventEnterKeyPressed,		/** Keypress event. */
		EEventItemClicked,			/** Item single-tap event. */
		EEventItemDoubleClicked,	/** Item two-taps event. */

		/** Special event: reported by directory tree and directory contents list
		boxes. */
		EEventItemActioned,
		EEventEditingStarted,		/** Editing started. */
		EEventEditingStopped,		/** Editing stopped. */
		EEventSelectionChanged		/** Selection changed. */
		};
public:
	/**
	 * Handles list box events.
	 *
	 * This pure virtual function is invoked by <code>CEikListBox</code> to
	 * notify the observer of list box events.
	 *
	 * @param     "	CEikListBox* aListBox	"
	 *            The originating list box.
	 * @param     "	TListBoxEvent aEventType	"
	 *            A code for the event. Further information may be
	 *            obtained by accessing the list box itself.
	 */
	virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)=0;
	};

#endif
