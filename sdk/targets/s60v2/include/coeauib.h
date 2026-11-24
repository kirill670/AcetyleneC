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

#if !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)

/////////////////////////////////////////////////////////////
//                                                         //
// PLEASE TURN ON SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1 RATHER THAN //
// USE CCoeAppUiBase_CLASS_NAME OR CCoeAppUiBase_hidden    //
//                                                         //
/////////////////////////////////////////////////////////////

#if defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)
#define CCoeAppUiBase_CLASS_NAME CCoeAppUiBase
#else
#define CCoeAppUiBase_CLASS_NAME CCoeAppUiBase_hidden // change the name of the class to hide it - not bulletproof, but should be good enough
#endif

class CCoeAppUiBase_CLASS_NAME : public CBase
/** Application UI abstract base class.

CCoeAppUiBase is the base class for the two concrete app UI classes, CCoeAppUiSimple 
and CCoeAppUi. 

@publishedAll
@deprecated */
    {
public:
/** Handles standard window server events.

This function is called (by CCoeEnv::RunL()) when the application receives 
a standard event from the window server. Implementations are provided by CCoeAppUiSimple 
and CCoeAppUi, but this function may also be overridden by derived classes.

This function is also called by CCoeEnv::SimulateKeyEventL().

Note: a standard event is any window server event that is not a redraw event or a 
priority key event.

@param aEvent The event that occurred.
@param aDestination The control that the event occurred in. (For key events 
this is the application's window group.) */
    virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)=0;
	IMPORT_C virtual void PrepareToExit();
protected:
	IMPORT_C virtual void HandleScreenDeviceChangedL(); // was Reserved_1()
private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_2();
    };
#endif

#endif
