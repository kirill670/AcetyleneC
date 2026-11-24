/*
* ==============================================================================
*  Name        : PluginAdapterInterface.h
*  Part of     :  / Browser Plugin API
*  Interface   : Browser Plugin API, MPluginAdapter
*  Description : The plug-in can use this interface to communicate with the browser.
*  Version     : 1.01
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef MPLUGINADAPTER_H
#define MPLUGINADAPTER_H

//  INCLUDES
#include "coecntrl.h"
#include "coecobs.h"
#include "npupp.h"

// FORWARD DECLARATIONS
class MPluginNotifier;

// CLASS DECLARATION

/**
*  The plug-in can use this interface to communicate with the browser.
*
*  @lib PluginAdapterUtil in Series 80 Platforms and the Nokia 7710 smartphone
*  @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
*/
class MPluginAdapter
    {
    public: // New functions
        
        /**
        * Gets the pointer to the minor version number of the plug-in version number of the Browser Plug-in API.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return Series 60 returns 1. Series 80 and the Nokia 7710 smartphone return 101.
        */
    virtual TUint16 GetVersion()=0;

        /**
        * Called when the plug-in has completed its creation.
        * This function is called from the constructL function of the plug-in.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @param aPluginControl A pointer to the plug-in control window
        * @return None
        */
    virtual void PluginConstructedL(CCoeControl* aPluginControl)=0;

        /**
        * Called after the plug-in has been deleted.
        * This function is called from the destructor of the plug-in.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return None
        */
    virtual void PluginFinishedL()=0;

#ifndef __SERIES60_30__

        /**
        * Called by the plug-in to open a URL in the parent frame.
        * This function is not implemented in Series 60. It is supported in Series 80 and in the Nokia 7710 smartphone.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @param aUrl Name of the URL to open
        * @return None
        */
    virtual void OpenUrlL(const TDesC& aUrl)=0;

        /**
        * Called by the plug-in to open a URL in a named window or frame.
        * This function is not implemented in Series 60. It is supported in Series 80 and in the Nokia 7710 smartphone.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @param aUrl Name of the URL to open
        * @param aNewTargetWindowName The name of the target window or frame
        * @return None
        */
    virtual void OpenUrlInTargetWindowL(const TDesC& aUrl, const TDesC& aNewTargetWindowName)=0;

        /**
        * Specifies whether or not the frame has a previous navigation history item.
        * This function is not implemented in Series 60. It is supported in Series 80 and in the Nokia 7710 smartphone.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return true if the frame has a previous navigation history item false otherwise
        */
    virtual TBool HasNavigationHistoryPrevious() const=0;

        /**
        * Informs the browser to load the next navigation history URL in its parent frame.
        * This function is not implemented in Series 60. It is supported in Series 80 and in the Nokia 7710 smartphone.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return None
        */
    virtual void LoadNavigationHistoryPreviousL()=0;

        /**
        * Returns whether the frame has a next navigation history item. 
        * This function is not implemented in Series 60. It is supported in Series 80 and in the Nokia 7710 smartphone.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return Returns whether the frame has a next navigation history item. 
        */
    virtual TBool HasNavigationHistoryNext() const=0;

        /**
        * Informs the browser to load the next navigation history URL in its parent frame.
        * This function is not implemented in Series 60. It is supported in Series 80 and in the Nokia 7710 smartphone.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return None
        */
    virtual void LoadNavigationHistoryNextL()=0;

#endif
        /**
        * Returns the window system level control object for the plug-in.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return A pointer to the parent control window.
        */
    virtual CCoeControl* GetParentControl()=0;

        /**
        * Returns the observer for the plug-in control.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @return Observer that the plug-in can use to send events to the browser.
        */
    virtual MCoeControlObserver* GetParentControlObserver()=0;

        /**
        * Sets the plug-in notifier allowing the plug-in to control portions of the browser.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @param aNotifier Pointer to an interface that the browser can use to send events to the plug-in.
        * @return None
        */
    virtual void SetPluginNotifier(MPluginNotifier *aNotifier)=0;
        

    };


/**
*  Contains notification ability for plug-ins.
*  These methods are implemented in the plugin.
*
*  @lib
*  @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
*/
class MPluginNotifier
    {
    public:     // Data
        // Types of notifications which can be passed to the plugin.
    enum TNotificationType {
       EEditCut,
       EEditCopy, 
       EEditPaste, 
       EEditDelete, 
       EApplicationFocusChanged, 
       ESystemNotification     };


    public: // New functions
        
        /**
        * Notifies the plugin of an event.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @param aCallType The event type that is passed to the plug-in
        * @param aParam The parameter associated with the event
        * @return Not used
        */
    virtual TInt NotifyL (TNotificationType aCallType, TAny *aParam)=0;

    };

#endif      // MPLUGINADAPTER_H   
            
// End of File