/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Rob Gregson, Keith Hollis
*/

#ifndef __EPOCABSTRACTDOCWIN_H
#define __EPOCABSTRACTDOCWIN_H

#include <e32std.h>

#include "epocprefs.h"
#include "epocabstractframe.h"

class MOperaDocWindow;

/*************************************************************************

	class MOperaDocWindowObserver

  	This class is implemented in Opera base code - not for porting
*/

class MOperaDocWindowObserver
	{
public:
	virtual void SizeChanged()=0;
	};

/*************************************************************************

	class MOperaDocWindowAdapter

  	This class is implemented in Opera base code - not for porting
	- calls from UI to the base document window
*/

class MOperaDocWindowAdapter
	{
public:
	// general
    virtual const TDesC* Url()=0; // get current URL
    virtual const TDesC* Title()=0; // get current title
    virtual TSecurityLevel SecurityLevel() const=0;
    virtual TImageDisplayMode ImageDisplayMode() const=0;
    virtual TCSSDisplayMode CSSDisplayMode() const=0;
	// loading
	virtual void Reload()=0;
	virtual void LoadAllImages()=0;
	virtual void StopLoading()=0;
	virtual void OpenUrlL(const TDesC &aUrl,TBool aNewWindow=EFalse)=0;	// replace contents with specified URL
	virtual void DestroyDocWindow()=0;
	// navigation within window
	virtual void FocusNextFrame()=0;
	virtual void FocusPreviousFrame()=0;
	virtual void HighlightNextLink()=0;
	virtual void HighlightPreviousLink()=0;
	virtual void HighlightNextItem()=0;
	virtual void HighlightPreviousItem()=0;	
	virtual void HighlightNextHeading()=0;
	virtual void HighlightPreviousHeading()=0;
	virtual void FollowCurrentLink()=0;
	virtual void OpenCurrentLinkInNewWindow()=0;
	// display settings
    virtual void SetImageDisplayMode(TImageDisplayMode aMode)=0;
    virtual void ToggleImageDisplayMode()=0;
	virtual void SetCSSDisplayMode(TCSSDisplayMode aMode)=0;
	virtual void ToggleCSSDisplayMode()=0;
    virtual void SetZoom(TInt aScale)=0;
    virtual TInt GetZoom()=0;
	virtual void SetScrollBars(TBool aScrollBars=ETrue)=0;
	virtual TBool ScrollBarsIsOn()=0;
    virtual void SetDefaultEncodingL(const TDesC8& aCharset)=0;
    virtual void SetBaseFontL(const TFontSpec& aFontSpec)=0;
	// misc
	virtual TBool IsBusy()=0;
    virtual void SetAsEmail()=0;
    virtual TPtrC SuggestedFileName()=0; // get suggested save as filename
	};

/*************************************************************************

	class MOperaDocWindowMediator

		This class is implemented in Opera base code - not for porting
	- handles observation of UI (concrete) document windows and 
	control messages passed from UI to base code

*/

class MOperaDocWindowMediator : public MOperaDocWindowObserver, public MOperaDocWindowAdapter
	{};

/*************************************************************************

	class MOperaDocWindowFactory

   	This class is a template for porting
*/

class MOperaDocWindowFactory
	{
public:
    virtual TBool AllowNewDocWindowL(const TDesC& aUrl,const TDesC& aName)=0;
    virtual MOperaDocWindow* CreateDocWindowL(MOperaDocWindowMediator *aObserver)=0;
    virtual void DeleteDocWindow(MOperaDocWindow* aDocWindow)=0;
    virtual MOperaDocWindow* ActiveDocWindow() const=0;
	};

/*************************************************************************

	class MOperaDocWindow

   	This class is a template for porting
*/

class MOperaDocWindow : public MOperaFrameFactory
	{
public:
	virtual TRect Rect() const=0;
public: // mirrored from OPIWindow
	virtual void Raise()=0;
	virtual void Lower()=0;
	virtual void UrlChangedL()=0;
	virtual void TitleChangedL()=0;
	virtual void ScaleChangedL()=0;
    virtual void SecurityLevelChangedL()=0;
    virtual void ImageDisplayModeChangedL()=0;
    virtual void CSSDisplayModeChangedL()=0;
	virtual void SetLoading(TBool aLoading)=0;
	virtual void SetProgress(TInt bytes,TInt secs)=0;
	virtual void SetDocProgress(TInt size,TInt total)=0;
	virtual void SetProgressText(const TDesC& aText)=0;
	virtual void SetImagesLoaded(TInt num,TInt total)=0;
	virtual void SetInfoText(const TDesC& aStr)=0;
	// history list
	virtual void AddHistory(const TDesC& aStr)=0;
	virtual void DelHistoryTop(TInt num)=0;
	virtual void DelHistoryBottom(TInt num)=0;
	virtual void UpdateHistoryItem(TInt aPos,const TDesC& aUrl,const TDesC& aName)=0;
	virtual void SelectHistoryItem(TInt pos)=0;
    // misc
    virtual void ShowScrollBars(TBool aShow)=0;
    virtual void ResetFocus()=0;
    virtual void SetCursor(TCursorType aCursor)=0;
	/**
	  * Called to customise a shortcut icon.
	  *
	  * @param (in) aBitmap
	  * @param (in) aMaskBitmap
	  */
    IMPORT_C virtual void PageContainsShortcutIconL(const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
    /**
    * Called when Javascript encounters an alert.
    * @param (in) aAlert The Javascript alert string
    */
    virtual void JavascriptAlertL(const TDesC& /*aAlert*/) const {}
	};

#endif
