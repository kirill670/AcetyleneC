// COEVIEW.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEVIEW_H__)
#define __COEVIEW_H__

#include <vwsdef.h>
#include <coemain.h> // for CCoeStatic

class CCoeAppUi;

/** 
 * The <code>MCoeView</code> class specifies an interface for views. This 
 * class should be implemented by all application views. 
 * 
 * @lib
 * @publishedAll
 * @released 
 */
class MCoeView

    {
public: 
    /** Returns a TVwsViewId uniquely identifying the view.
    * @internal 
    * @return Represents a view in the server. 
    */
    virtual TVwsViewId ViewId() const=0;
private:
    /** Takes any action required when a view is activated. Reimplemented versions 
    should read the contents of aCustomMessage for any message type identified 
    by aCustomMessageId that the view understands.
    
    The ID of the previously active view aPrevViewId is supplied so that the activated 
    view can subsequently switch back to the caller if required.
    
    @param aPrevViewId The UID of the previously active view.
    @param aCustomMessageId Message type.
    @param aCustomMessage Message contents. 

    @publishedAll
    @released */
    virtual void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)=0;
    /** Takes any action that is required following deactivation of the view. 
    
    This reduces the work required of the window server.

    @publishedAll
    @released */
    virtual void ViewDeactivated()=0;

protected:
    IMPORT_C virtual TVwsViewIdAndMessage ViewScreenDeviceChangedL();
private:
    IMPORT_C virtual void ViewConstructL();
protected:
    IMPORT_C virtual TBool ViewScreenModeCompatible(TInt aScreenMode); // was MCoeView_Reserved_1()
private:
    friend class CCoeViewManager;
    IMPORT_C virtual void MCoeView_Reserved_2();
    };


/** 
 * The <code>CCoeScreenDeviceChangeDefaultHandler</code> class specifies a 
 * default screen device change handler. This class is used to activate a 
 * default view when a screen 'flip' occurs, if the currently active view does 
 * not implement <code>MCoeView::ViewScreenDeviceChangedL()</code>. See also 
 * <code>MCoeView::ViewScreenDeviceChangedL()</code>.
 *
 * @lib [what]
 * @publishedAll 
 * @released
 */
class CCoeScreenDeviceChangeDefaultHandler : public CCoeStatic

    {
public:
   /**
    * The object destructor.
    */
    IMPORT_C ~CCoeScreenDeviceChangeDefaultHandler();

   /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C static CCoeScreenDeviceChangeDefaultHandler* Self();
protected:
    IMPORT_C CCoeScreenDeviceChangeDefaultHandler();
public:
    virtual void HandleScreenDeviceChangedL()=0;
    virtual TVwsViewIdAndMessage DefaultViewOnScreenDeviceChanged()=0;
    };


#endif
