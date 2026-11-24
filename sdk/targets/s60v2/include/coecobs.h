// COECOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COECOBS_H__)
#define __COECOBS_H__

class CCoeControl;

class MCoeControlObserver
/** Interface for a control to send events to its observer control. 

@publishedAll 
@released */
	{
public:
	/** Observer event types. */
	enum TCoeEvent
		{
		/** Request exit. 
		This event is used to indicate exit from a mode when 
		the user has completed an operation 'successfully'. For example, this 
		event might be sent when the user has a choice list open and presses 
		enter to select an item. The UI Control Framework does not use this 
		event itself. */
		EEventRequestExit,
		/** Request cancel.
		This event is used to indicate exit from a mode when the user has cancelled 
		the operation that caused entry into the mode originally. For example, this 
		event might be sent when the user presses escape to close the list and leave 
		the choice as it was. The UI Control Framework does not use this event itself. */
		EEventRequestCancel,
		/** Request focus.
		This event is notified by the UI Control Framework during pointer down event 
		processing after EEventPrepareFocusTransition is handled. */
		EEventRequestFocus,
		/** Prepare focus transition.
		This event is notified by the UI Control Framework during pointer down event 
		processing if the control does not yet have, but could get, focus. */
		EEventPrepareFocusTransition,
		/** State changed.
		This event can be used by a control to report that some piece of internal 
		data has changed, and hence that any observer should be notified accordingly. 
		The UI Control Framework does not use this value itself. */
		EEventStateChanged,
		/** Interaction refused.
		This event is notified by the UI Control Framework during pointer down event 
		processing if the control is dimmed (disabled). */
		EEventInteractionRefused
		};
public:
	/** Handles an event from an observed control.
	
	This function is called when a control for which this control is the observer 
	calls CCoeControl::ReportEventL(). It should be implemented by the observer 
	control, and should handle all events sent by controls it observes.
	
	@param aControl The control that sent the event.
	@param aEventType The event type. */
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)=0;
	};

#endif
