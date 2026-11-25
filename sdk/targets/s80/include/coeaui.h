// COEAUI.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#if !defined(__COEAUI_H__)
#define __COEAUI_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__VWSDEF_H__)
#include <vwsdef.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COEAUIB_H__)
#include <coeauib.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

#if !defined(__COEVIEW_H__)
#include <coeview.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

class CCoeEnv;
class CCoeControl;

/**
 * creates a FEP interface object
 * @publishedAll
 * @released
 */
typedef CCoeFep* (*TCoeFepFactoryFunctionL)(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll, const CCoeFepParameters& aFepParameters);

/**
 * calls the second ordinal function of the FEP for which the settings dialog 
 * is to be executed
 * @publishedAll
 * @released
 */
typedef void (*TCoeSynchronouslyExecuteFepSettingsDialogFunctionL)(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll);

/** 
 * The enumeration specifies stack priority flags. Controls with higher 
 * priorities get offered key events before controls with lower priorities.
 * @publishedAll 
 * @released 
 */
enum
    {
    /** 0 */
    ECoeStackPriorityDefault=0,
    /** 10 */
    ECoeStackPriorityMenu=10,
    /** 50 */
    ECoeStackPriorityDialog=50,
    /** 60 */
    ECoeStackPriorityCba=60,
    /** 200 */
    ECoeStackPriorityAlert=200,
    /** 250 */
    ECoeStackPriorityFep=250,
    /** 300 */
    ECoeStackPriorityEnvironmentFilter=300
    };


/** 
 * The enumeration specifies control stack flags. Each control on the stack 
 * also has a set of flags that can be used to refuse key events and requests 
 * for focus.
 * @publishedAll 
 * @released 
 */
enum
    {
    /** the default value */
    ECoeStackFlagStandard           = 0,    
    /** the control does not accept key events */
    ECoeStackFlagRefusesAllKeys     = 0x01,
    /** the control does not accept keyboard focus */
    ECoeStackFlagRefusesFocus       = 0x02,
    /** the control is owned and deleted by the stack */
    ECoeStackFlagOwnershipTransfered= 0x04, 
    /** 
    * the control is also added to the stack of any embedded AppUI. For
    * example, an alert dialog added through <code>CEikonEnv</code> will be
    * shared on the stack of all embedded AppUIs that may appear in the
    * application 
    */
    ECoeStackFlagSharable           = 0x08
    };

class CCoeControlStack;
class CCoeViewManager;
class MCoeViewDeactivationObserver;
class MCoeViewActivationObserver;
class MCoeViewObserver;

/** 
 * The <code>CCoeAppUi</code> class specifies a general purpose application 
 * user interface class. This class handles application-wide aspects of the 
 * user interface, such as key press events. The GUI may derive further to 
 * provide its own application user interface class to provide a more concrete 
 * framework for applications. An application derives once more to provide 
 * event handling facilities. The GUI class <code>CEikAppUi</code> is derived 
 * from this class. 
 * 
 * @lib [what]
 * @publishedAll 
 * @released 
 */
class CCoeAppUi : public CCoeAppUiBase
    {
public:
    /** The default object constructor. */
    IMPORT_C CCoeAppUi();

    /** The object destructor. */
    IMPORT_C ~CCoeAppUi();

    /**
    * Completes construction of a <code>CCoeAppUi</code> object. This method
    * creates a control stack for the application and initiates a view server 
    * session.
    *
    * @param aPrevious If not <code>NULL</code>, the new control stack is 
    *                  initialized with the control that existed on the control 
    *                  stack owned by <code>aPrevious</code>. 
    * @remarks
    * @see
    */
    IMPORT_C void ConstructL(CCoeAppUi* aPrevious=NULL);
public: // new functions
   /**
    * Adds a control to the control stack. This method is used by most GUI 
    * applications to add their application view (an application-specific 
    * control) to the stack. 
    *
    * @param aControl The control to add to the stack
    * @param aPriority The control's stack priority. High priority controls are 
    *                  offered key events first. The possible values begin with 
    *                  <code>ECoeStackPriorityDefault</code> 
    * @param aStackingFlags The control's event handling behavior. The possible 
    *                       values begin with <code>ECoeStackFlagStandard</code>
    * @remarks
    * @see
    */    
    IMPORT_C void AddToStackL(CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);

   /**
    * Removes a control from the control stack. The method also handles the 
    * change to the stack. 
    *
    * @param aControl The control to remove from the stack
    * @remarks
    * @see
    */
    IMPORT_C void RemoveFromStack(CCoeControl* aControl);

   /**
    * Updates the value of the flags for a control on the control stack. The 
    * mask defines which flags are modified, while <code>aFlags</code> defines 
    * the values they are set to. The method panics if the control is not on 
    * the stack.
    *
    * @param aControl The control whose flags are updated
    * @param aFlags Contains the required value for each of the flag bits whose 
    *               bit is set in <code>aMask</code>
    * @param aMask Contains a set bit for each flag bit to modify 
    * @remarks
    * @see
    */
    IMPORT_C void UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask);
    
   /**
    * Handles changes in control stack flags. This gives keyboard focus to the 
    * focusable control with the highest priority on the control stack. It 
    * should be called whenever the flag values are modified, for example, 
    * after calling <code>UpdateStackedControlFlags()</code>.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void HandleStackChanged();

    /**
    * Tests whether the application is displaying a menu bar or dialog. 
    * 
    * @return <code>ETrue</code> if the application is currently displaying a
    *         menu bar or a dialog; <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool IsDisplayingMenuOrDialog() const; 

    /**
    * Tests whether the application is displaying a dialog.
    * 
    * @return <code>ETrue</code> if the application is currently displaying a
    *         a dialog; <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool IsDisplayingDialog() const; 

    /**
    * Tests whether the application is displaying a control between given 
    * priorities. It returns <code>ETrue</code> if the application is currently 
    * displaying a control that has a priority on the control stack between 
    * (but not including) <code>aLowerPriority</code> and 
    * <code>aHigherPriority</code>.
    *
    * @param aLowerPriority The lower bound of the control's priority
    * @param aHigherPriority The upper bound of the control's priority
    * @return <code>ETrue</code> if a control with a priority between the 
    *         specified bounds is currently being displayed; <code>EFalse</code>
    *         if no control with the specified priority is currently being 
    *         displayed
    * @remarks
    * @see
    */
    IMPORT_C TBool IsDisplayingControlBetweenPriorities(TInt aLowerPriority, TInt aHigherPriority) const;

    /**
    * Returns a list of relevant contexts within an application help file 
    * appropriate for the current state of the application. The array is 
    * generated from the application user interface and the controls on the 
    * control stack.
    *
    * @return the list of pointers to relevant contexts that provide access 
    *         to context-specific topics
    * @remarks
    * @see
    */
    IMPORT_C CArrayFix<TCoeHelpContext>* AppHelpContextL() const;

    /**
    * Returns the supported input capabilities of the control with focus. 
    * Classes that override <code>CCoeAppUi::HandleKeyEventL()</code> should 
    * also override the <code>InputCapabilities()</code> virtual method, 
    * returning a <code>TCoeInputCapabilities</code> object whose attributes 
    * correspond to the behavior of the <code>HandleKeyEventL()</code> method.
    * Overriding <code>InputCapabilities()</code> methods should do a base-call 
    * and 'merge' the returned input capabilities with its own input 
    * capabilities. If the overriding <code>InputCapabilities()</code> method
    * needs to get the input capabilities of any top-level control, it should 
    * do so by calling <code>CCoeControl::RecursivelyMergedInputCapabilities()</code>
    * on that control.
    * 
    * @return the types of input that can be consumed by the focusable control
    * @remarks
    * @see
    */
    IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;

    /**
    * Handles a change to the application's run-time resources for all controls 
    * on the control stack. These are resources that are shared across the 
    * environment.
    *
    * @param aType Specifies a resource type
    * @remarks
    * @see
    */
    IMPORT_C void HandleStackedControlsResourceChange(TInt aType);

    /**
    * Activates a specified application view, without passing any message. It 
    * leaves if activation of the new view fails.
    *
    * @param aViewId Identifier of the view to activate
    * @remarks
    * @see
    */
    IMPORT_C void ActivateViewL(const TVwsViewId& aViewId);

    /**
    * Activates a specified application view, then passes the message text 
    * descriptor <code>aCustomMessage</code> for a message of type 
    * <code>aCustomMessageId</code>. It leaves if activation of the new view 
    * fails. <b>Note</b>: Activation works synchronously so that, in general, 
    * this method returns when the view is fully activated. 
    * 
    * /An application defines and publishes the message UIDs that it understands.
    * For example, a contacts application activates an email editor view and 
    * passes an email address as a custom message. To do this, the contacts 
    * application must use a message UID, and descriptor encoding, that the 
    * email application has published as being understandable.
    *
    * @param aViewId Identifies the view to activate
    * @param aCustomMessageId Specifies the message type
    * @param aCustomMessage The message passed to the activated view
    * @remarks
    * @see
    */
    IMPORT_C void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);

    /**
    * Registers a view with the view architecture. All views should be 
    * registered in the AppUI's <code>ConstructL()</code>.
    *
    * @param aView The view to be registered
    * @remarks
    * @see
    */
    IMPORT_C void RegisterViewL(MCoeView& aView);

    /**
    * Deregisters the view, <code>aView</code>, which is required before the 
    * application exits. This method panics if there is no connection to the 
    * view server or if the view does not exist.
    *
    * @param aView The view to be deregistered
    * @remarks
    * @see
    */
    IMPORT_C void DeregisterView(const MCoeView& aView);

    /**
    * Sets the default view for this AppUI to <code>aView</code>. The default 
    * view should be constructed, drawn, registered, and set as such, as early 
    * as possible in the AppUI <code>ConstructL()</code>.
    *
    * @since Uikon1.2
    * @remarks
    * @see
    */
    IMPORT_C void SetDefaultViewL(const MCoeView& aView);

    /**
    * Gets the ID of the default view for the AppUI in <code>aViewId</code>. 
    * Returns <code>KErrNotFound</code> if there is no default view for this
    * AppUI.
    *
    * @since Uikon1.2
    * @param aViewId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C TInt GetDefaultViewId(TVwsViewId& aViewId) const;

    /**
    * Gets the ID of the active view in <code>aViewId</code>. Returns 
    * <code>KErrNotFound</code> if this AppUI does not have an active view or
    * if the default view is active.
    *
    * @since Uikon1.2
    * @param aViewId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C TInt GetActiveViewId(TVwsViewId& aViewId) const;

    /**
    * Adds the control <code>aControl</code> to the control stack associated 
    * with the view <code>aView</code>. Sets its stack priority and event 
    * handling flags. High priority controls are offered key events first.
    * 
    * @param aView [what]
    * @param aControl [what]
    * @param aPriority [what]
    * @param aStackingFlags [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddToStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
public: // but not exported
    /** @internal */
    TBool IsControlOnStack(CCoeControl* aControl) const;
    /** @internal */
    void SetCurrentControlStackGroupId(TInt aGroupId);
public: // 
    /**
    * Creates an event to be processed to activate the view identified by 
    * <code>aViewId</code> and returns without waiting for the activation to 
    * complete. This method passes the message text descriptor 
    * <code>aCustomMessage</code> to the view for a message of type 
    * <code>aCustomMessageId</code>. It leaves, if activation of the new view 
    * fails. <b>Note</b>: This method may return without error but the 
    * activation may subsequently fail.
    *
    * @publishedPartner 
    * @released  
    * @param aViewId [what]
    * @param aCustomMessageId [what]
    * @param aCustomMessage [what]
    * @remarks
    * @see
    */
    IMPORT_C void CreateActivateViewEventL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);

    /**
    * Activates the top view for this AppUI, which is either the last view to 
    * be active (if a view was previously active) or the default view.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void ActivateTopViewL();

    /**
    * Deactivates the active view. This is necessary before exiting if the 
    * AppUI has the active view.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void DeactivateActiveViewL();

    /**
    * Registers a pseudo-view for the application identified by 
    * <code>aAppUid</code>. The view architecture is notified that a view 
    * exists for this application, which allows it to participate in the system 
    * view-switching mechanism, even though it does not implement any concrete 
    * views of its own. Activating the application view means bringing the 
    * application into the foreground.
    *
    * @param aAppUid The ID of the application for which a view should be 
    *                registered
    * @remarks
    * @see
    */
    IMPORT_C void RegisterApplicationViewL(TUid aAppUid);

    /**
    * Deregisters the application view from the view architecture.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void DeregisterApplicationView();

    /**
    * Checks the set of views registered for the AppUI. Adds an application 
    * view as the default, if no views have been added, so that the application 
    * can participate in the view architecture navigation. This method 
    * initializes a default view if no default view has been set. The method 
    * should be called by the framework after views have been added to an 
    * AppUI by construction.
    * 
    * @param aAppUid The application's third UID
    * @remarks
    * @see
    */
    IMPORT_C void CheckInitializeViewsL(TUid aAppUid);

    /**
    * @internal
    */
    IMPORT_C void SetApplicationViewAsDefaultL(); //internalTechnology

    /**
    * Adds the observer <code>aViewDeactivationObserver</code> to the list to 
    * be notified of view deactivations.
    * 
    * @param aViewDeactivationObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddViewDeactivationObserverL(MCoeViewDeactivationObserver* aViewDeactivationObserver);

    /**
    * Removes the observer <code>aViewDeactivationObserver</code> from the list 
    * to be notified of view deactivations. This method panics if the observer 
    * is not found.
    * 
    * @param aViewDeactivationObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveViewDeactivationObserver(MCoeViewDeactivationObserver* aViewDeactivationObserver);

    /**
    * Requests that the next deactivation of the view identified by 
    * <code>aViewId</code> be notified to the view deactivation observer 
    * <code>aViewDeactivationObserver</code>. The request is cleared after the 
    * next notification. Only the last notification request made is honored.
    * 
    * @param aViewId [what]
    * @param aViewDeactivationObserver The view deactivation observer
    * @remarks
    * @see
    */
    IMPORT_C void NotifyNextDeactivation(const TVwsViewId& aViewId, MCoeViewDeactivationObserver& aViewDeactivationObserver);

    /**
    * An overloaded method that requests that the next view deactivation be 
    * notified to the view deactivation observer 
    * <code>aViewDeactivationObserver</code>.
    * 
    * @param aViewDeactivationObserver The view deactivation observer
    * @remarks
    * @see
    */
    IMPORT_C void NotifyNextDeactivation(MCoeViewDeactivationObserver& aViewDeactivationObserver);

    /**
    * Adds the observer <code>aViewActivationObserver</code> to the list to be 
    * notified of view activations.
    * 
    * @param aViewActivationObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddViewActivationObserverL(MCoeViewActivationObserver* aViewActivationObserver);

    /**
    * Removes the observer <code>aViewActivationObserver</code> from the list 
    * to be notified of view activations. The method panics if the observer is 
    * not found.
    * 
    * @param aViewActivationObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveViewActivationObserver(MCoeViewActivationObserver* aViewActivationObserver);

    /**
    * Requests that the next activation of the view identified by 
    * <code>aViewId</code> be notified to the view activation observer 
    * <code>aViewActivationObserver</code>. The request is cleared after the 
    * next notification. Only the last notification request made is honored.
    * 
    * @param aViewId [what]
    * @param aViewActivationObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void NotifyNextActivation(const TVwsViewId& aViewId, MCoeViewActivationObserver& aViewActivationObserver);

    /**
    * An overloaded method that requests that the next view activation be 
    * notified to the view activation observer <code>aViewActivationObserver</code>.
    * 
    * @param aViewActivationObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void NotifyNextActivation(MCoeViewActivationObserver& aViewActivationObserver);

    /**
    * Adds the specified observer to the list to be notified of view events.
    *
    * @param aViewObserver The observer to be added to the list
    * @remarks
    * @see
    */
    IMPORT_C void AddViewObserverL(MCoeViewObserver* aViewObserver);

    /**
    * Removes the specified observer from the list to be notified of view events.
    * The method panics if the observer is not found.
    * 
    * @param aViewObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveViewObserver(MCoeViewObserver* aViewObserver);

    /**
    * @internal
    */
    IMPORT_C void WriteInternalStateOfStackedControlsL(RWriteStream& aWriteStream) const; //internalTechnology

    /**
    * @internal
    */
    IMPORT_C void SetSystemDefaultViewL(const TVwsViewId& aViewId,TInt aMode); //internalTechnology

    /**
    * @internal
    */
    IMPORT_C void SetSystemDefaultViewL(const TVwsViewId& aViewId); //internalTechnology
public:
    /**
    * @deprecated
    */
    IMPORT_C void RegisterViewAndAddStackL(MCoeView& aView);

    /**
    * @deprecated
    */
    IMPORT_C void DeregisterViewAndRemoveStack(const MCoeView& aView);

    /**
    * @deprecated
    */
    IMPORT_C void RemoveFromViewStack(const MCoeView& aView,CCoeControl* aControl);

    /**
    * @deprecated
    * @internal
    */
    IMPORT_C void UpdateViewStackedControlFlags(const MCoeView& aView,CCoeControl* aControl,TInt aFlags,TInt aMask);

    /**
    * @deprecated
    */
    IMPORT_C void AddToViewStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);

protected: // from CCoeAppUiBase
    IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
    IMPORT_C void HandleScreenDeviceChangedL();
    IMPORT_C void Reserved_2();
private: // new functions
    IMPORT_C virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    IMPORT_C virtual void HandleForegroundEventL(TBool aForeground);
    IMPORT_C virtual void HandleSwitchOnEventL(CCoeControl* aDestination);
    IMPORT_C virtual void HandleSystemEventL(const TWsEvent& aEvent);
    IMPORT_C virtual void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
    IMPORT_C virtual void SetAndDrawFocus(TBool aFocus);
    IMPORT_C virtual CArrayFix<TCoeHelpContext>* HelpContextL() const;
private:
    enum TRemoveCondition
        {
        ERemoveUnconditionally,
        ERemoveOnlyIfSharable
        };
private:
    CCoeControl* TopFocusableControl() const;
    CCoeControl* TopFocusedControl() const;
    TInt FindPos(CCoeControlStack* aStack,CCoeControl* aControl) const;
    void SetFocusToControl(CCoeControl* aControl,TBool aFocus);
    void DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags);
    void DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags, TInt aGroupId);
    void DoRemoveFromStack(CCoeControlStack* aStack,CCoeControl* aControl,TRemoveCondition aRemoveCondition=ERemoveUnconditionally);
    void DoUpdateStackedControlFlags(CCoeControlStack* aStack,CCoeControl* aControl,TInt aFlags,TInt aMask);
private:
    class CExtra;
    friend class CExtra;
    friend class CTestDriver;
protected:
    CCoeEnv* iCoeEnv;
private:
    CCoeViewManager* iViewManager;
    CCoeControlStack* iStack;
    CExtra* iExtra;
    };

/**  
 * The <code>MCoeViewDeactivationObserver</code> class specifies an interface 
 * through which view deactivations can be notified to an observer. Dialogs, 
 * and other floating windows such as virtual keyboards which should be 
 * dismissed when a view is deactivated, can implement this interface and take 
 * any action required. 
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
class MCoeViewDeactivationObserver

    {
public:

    /**
    * Handles the deactivation of the view identified by 
    * <code>aViewIdToBeDeactivated</code> before the newly activated view with 
    * ID <code>aNewlyActivatedViewId</code> is marked as current.
    * 
    * @param aViewIdToBeDeactivated [what]
    * @param aNewlyActivatedViewId [what]
    * @remarks
    * @see
    */
    virtual void HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated,const TVwsViewId& aNewlyActivatedViewId)=0;

private:
    IMPORT_C virtual void MCoeViewDeactivationObserver_Reserved_1();
    IMPORT_C virtual void MCoeViewDeactivationObserver_Reserved_2();
    };

/**  
 * The <code>MCoeViewActivationObserver</code> class specifies an interface 
 * through which view activations can be notified to an observer.
 * 
 * @lib [what]
 * @publishedAll
 * @released
 */
class MCoeViewActivationObserver

    {
public:

    /**
    * Handles the activation of the view <code>aNewlyActivatedViewId</code>
    * before the old view <code>aViewIdToBeDeactivated</code> is to be 
    * deactivated.
    * 
    * @param aNewlyActivatedViewId [what]
    * @param aViewIdToBeDeactivated [what]
    * @remarks
    * @see
    */
    virtual void HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated)=0;

private:
    IMPORT_C virtual void MCoeViewActivationObserver_Reserved_1();
    IMPORT_C virtual void MCoeViewActivationObserver_Reserved_2();
    };

/**  
 * The <code>MCoeViewObserver</code> class specifies an interface through which 
 * view events can be notified to an observer.
 *
 * @lib [what]
 * @publishedPartner
 * @released 
 */
class MCoeViewObserver

    {
public:
    /**
    * [what]
    * 
    * @param aEvent [what]
    * @remarks
    * @see
    */
    virtual void HandleViewEventL(const TVwsViewEvent& aEvent)=0;
    };


#endif
