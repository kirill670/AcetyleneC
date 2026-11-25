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
 *
 * Specifies an interface for views.
 *
 * This class should be implemented by all application views.
 *
 * @since 6.0
 * @lib "cone.lib"
 */
class MCoeView
	{
public:	
	/**
	 *
	 * Returns a <code>TVwsViewId</code> uniquely identifying the view.
	 *
	 * @returns   "TVwsViewId"
	 *            Represents a view in the server.
	 */
	virtual TVwsViewId ViewId() const=0;
private:
	/**
	 *
	 * Takes any action required when a view is activated.
	 *
	 * Reimplemented versions should read the contents of
	 * <code>aCustomMessage</code> for any message type identified by
	 * <code>aCustomMessageId</code> that the view understands.The ID of the
	 * previously active view <code>aPrevViewId</code> is supplied so that
	 * the activated view can subsequently switch back to the caller if
	 * required.
	 *
	 * @param     "const TVwsViewId& aPrevViewId"
	 *            The UID of the previously active view.
	 * @param     "TUid aCustomMessageId"
	 *            Message type.
	 * @param     "Const TDesC8& aCustomMessage"
	 *            Message contents.
	 */
	virtual void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)=0;

	/**
	 *
	 * Takes any action that is required following deactivation of the view.
	 *
	 * This reduces the work required of the window server.
	 *
	 */
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
 * Handles any screen device changes that occur while a view is active 
 *  
 * @since App-Frameworks 6.2
 * @internal
 */
class CCoeScreenDeviceChangeDefaultHandler : public CCoeStatic
	{
public:
	IMPORT_C ~CCoeScreenDeviceChangeDefaultHandler();
	IMPORT_C static CCoeScreenDeviceChangeDefaultHandler* Self();
protected:
	IMPORT_C CCoeScreenDeviceChangeDefaultHandler();
public:
	virtual void HandleScreenDeviceChangedL()=0;
	virtual TVwsViewIdAndMessage DefaultViewOnScreenDeviceChanged()=0;
	};


#endif
