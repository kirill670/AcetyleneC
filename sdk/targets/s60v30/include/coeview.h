// COEVIEW.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEVIEW_H__)
#define __COEVIEW_H__

#include <vwsdef.h>
#include <coemain.h> // for CCoeStatic

class CCoeAppUi;

class MCoeView
/** Specifies an interface for views. 

This class should be implemented by all application views. 

@publishedAll
@released */
	{
public:	
	/** Returns a TVwsViewId uniquely identifying the view.
	
	@return Represents a view in the server. */
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
	IMPORT_C MCoeView();
	IMPORT_C virtual TVwsViewIdAndMessage ViewScreenDeviceChangedL();
private:
	IMPORT_C virtual void ViewConstructL();
protected:
	IMPORT_C virtual TBool ViewScreenModeCompatible(TInt aScreenMode); // was MCoeView_Reserved_1()
private:
	friend class CCoeViewManager;
	IMPORT_C virtual void PrepareForViewActivation();
	IMPORT_C virtual void MCoeView_Reserved_2();
	IMPORT_C virtual void MCoeView_Reserved_3();
private:
	TInt iMCoeView_Reserved1;
	};


class CCoeScreenDeviceChangeDefaultHandler : public CCoeStatic
//
// Handles any screen device changes that occur while a view is active 
//
/** A default screen device change handler. 

This class is used to activate a default view when a screen "flip" occurs, 
if the currently active view does not implement MCoeView::ViewScreenDeviceChangedL().

@publishedAll 
@released
@see MCoeView::ViewScreenDeviceChangedL() */
	{
public:
	IMPORT_C ~CCoeScreenDeviceChangeDefaultHandler();
	IMPORT_C static CCoeScreenDeviceChangeDefaultHandler* Self();
protected:
	IMPORT_C CCoeScreenDeviceChangeDefaultHandler();
	IMPORT_C CCoeScreenDeviceChangeDefaultHandler(TInt aDestructionPriority);
private:
	IMPORT_C virtual void CCoeStatic_Reserved1();
	IMPORT_C virtual void CCoeStatic_Reserved2();
	IMPORT_C virtual void CCoeScreenDeviceChangeDefaultHandler_Reserved1();
	IMPORT_C virtual void CCoeScreenDeviceChangeDefaultHandler_Reserved2();
public:
	virtual void HandleScreenDeviceChangedL()=0;
	virtual TVwsViewIdAndMessage DefaultViewOnScreenDeviceChanged()=0;
private:
	TInt iCCoeScreenDeviceChangeDefaultHandler;
	};


#endif
