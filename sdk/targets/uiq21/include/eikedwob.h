// EIKEDWOB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKEDWOB_H__)
#define __EIKEDWOB_H__

class CEikEdwin;

/**
 *
 * Interface class describing the functionality expected of an observer
 * for <code>CEikEdwin</code>s.
 *
 * Edwin observers are informed by the edwin whenever its content is
 * changed, or whenever the user changes the cursor position.This class
 * should be derived from by all observers of edwins.
 *
 * @since 6.0
 * @lib ""
 */
class MEikEdwinObserver
	{
public:
	/**
	 * Events from an editor.
	 */
	enum TEdwinEvent
		{
		EEventFormatChanged,	/** Sent whenever the formatting of the content of the edwin changes. */
		EEventNavigation		/** Sent when cursor position changes. */
		};
public:
	/**
	 * This pure virtual function is invoked by <code>CEikEdwin</code> to
	 * report an event to its observer.
	 *
	 * The observer may respond appropriately.
	 *
	 * @param     "	CEikEdwin* aEdwin	"
	 *            The originating edwin.
	 * @param     "	TEdwinEvent aEventType	"
	 *            The event being reported.
	 */
	virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType)=0;
	};

/**
 *
 * Interface to handle changes to an edwin's size.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class MEikEdwinSizeObserver
	{
public:
	/**
	 * Specifies the type of event reported to the edwin observer.
	 */
	enum TEdwinSizeEvent
		{
		/** Specifies a change in edwin size. When the edwin observer receives an
		event of this type, it handles it by making its view bigger or smaller
		according to the new edwin size. */
		EEventSizeChanging
		};
public:
	/**
	 * Handles a change in the edwin's size.
	 *
	 * If you implement this function, ensure it returns <code>ETrue</code>
	 * if you wish to redraw the edwin.
	 *
	 * @param     " CEikEdwin* aEdwin"
	 *            The edwin for which the size event is being handled.
	 * @param     " TEdwinSizeEvent aEventType"
	 *            The event type.
	 * @param     " TSize aDesirableEdwinSize"
	 *            The desired size for the edwin identified by
	 *            <code>aEdwin</code>.
	 * @returns   " TBool"
	 *            The return value depends on your implementation.
	 *            Return <code>ETrue</code> if you wish to redraw the
	 *            edwin. <code>EFalse</code> otherwise.
	 */
	virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize)=0;
	};


/**
 * The MEikEdwinClipboardObserver class defines an interface for classes to implement clipboard 
 * feedback functions.
 *  
 * @public
 * @since App-Framework_6.2
 */
class MEikEdwinClipboardObserver
	{
public:
	enum TClipboardFunc
		{
		ENoClipboard,
		ECut,
		ECopy,
		EPaste
		};
public:
	virtual void Release() = 0;
	virtual void HandleNothingSelected(TClipboardFunc aClipboardFunc)=0;
	virtual void HandleCopiedToClipboard()=0;
private:
	virtual void MEikEdwinClipboardObserver_Reserved_1() = 0;
	};



#endif

