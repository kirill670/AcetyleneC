// COEAUIB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEAUIB_H__)
#define __COEAUIB_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CCoeControl;
class TWsEvent;

/**
 *
 * Application UI abstract base class.
 *
 * <code>CCoeAppUiBase</code> is the base class for the two concrete app
 * UI classes, <code>CCoeAppUiSimple</code> and <code>CCoeAppUi</code>.
 *
 * @since 5.0
 * @lib "cone.lib"
 */
class CCoeAppUiBase : public CBase
    {
public:
	/**
	 *
	 * Handles standard window server events.
	 *
	 * This function is called (by <code>CCoeEnv::RunL()</code>) when the
	 * application receives a standard event from the window server.
	 * Implementations are provided by <code>CCoeAppUiSimple</code> and
	 * <code>CCoeAppUi</code>, but this function may also be overridden by
	 * derived classes.This function is also called by
	 * <code>CCoeEnv::SimulateKeyEventL()</code>.Note:A standard even is any
	 * window server event that is not a redraw event or a priority key
	 * event.
	 *
	 * @param     "const TWsEvent& aEvent"
	 *            The event that occurred.
	 * @param     "CCoeControl* aDestination"
	 *            The control that the event occurred in. (For key
	 *            events this is the applications window group.)
	 */
    virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)=0;
	IMPORT_C virtual void PrepareToExit();
protected:
	IMPORT_C virtual void HandleScreenDeviceChangedL(); // was Reserved_1()
private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_2();
    };

#endif
