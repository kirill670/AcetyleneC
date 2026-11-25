// CMCOBS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
#ifndef __CMCOBS_H__
#define __CMCOBS_H__


class CCoeControl;


/**
 * Mixin for all classes that needs to respond to the special Contacts events
 * 
 */
class MContactsControlObserver
	{
public:
	/**
	 * Enum for the different Contacts events
	 */
	enum TContactsEvent
		{
		EEventCurrentRecordChanged,
		EEventContactClicked,
		EEventRepeatScrollingStart,
		EEventRepeatScrollingStop,
		EEventSwitchToDetailedView,
		EEventSwitchToListView,
		EEventSwitchToNewEditView,
		EEventDNLClicked,
		EEventEdwinSizeChange,
		EEventHeadlineClicked
		};
public:
	/**
	 * Handle Contacts specific events
	 *
	 * @param aControl the control reporting an event to us
	 * @param aEventType the type of event being reported
	 *
	 */
    virtual void HandleContactsEventL(CCoeControl* aControl,MContactsControlObserver::TContactsEvent aEventType)=0;
	};
#endif // __CMCOBS_H__
