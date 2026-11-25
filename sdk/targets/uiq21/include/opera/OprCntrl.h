/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2001-2002 Opera Software AS.  All rights reserved.
 *
 * This file is part of the Opera web browser.  It may not be distributed
 * under any circumstances.
 *
 * @file OprCntrl.h
 *
 * Contains wrap-around engine class for interfacing Opera from external EPOC
 * applications.
 *
 * For more information, see: http://www.opera.com/symbian or email symbian@opera.com
 *
 * @author Keith Hollis
 */

#ifndef __OPRCNTRL_H
#define __OPRCNTRL_H

#include <coecntrl.h>

#include "oprdocwin.h"

/*************************************************************************

	class MOperaControlViewAdapter
*/

class MOperaControlViewAdapter
	{
public:
	virtual void DisplayContextPopoutL(TObjectType aType,const TPoint& aScreenPoint,const TPoint& aOffsetPoint)=0;
	};

/*************************************************************************

	class COperaControl
*/

class COperaControl : public CCoeControl, public MCoeControlObserver, public MOperaDocWindowFactory,
                      public MOperaDocWindowViewAdapter
{
public:	// enums
	enum TScrollBarVisibility
		{
		EOff,
		EOn,
		EAuto
		};
	enum TClipboardFunc
		{
		ENoClipboard,
		ECut,
		ECopy,
		EPaste
		};
public: // new - public interface
    static IMPORT_C COperaControl* NewL(CCoeControl*aParent);
    IMPORT_C ~COperaControl();
    IMPORT_C void SetOperaViewAdapter(MOperaControlViewAdapter*aAdapter);
    IMPORT_C COperaModel* Model() { return iModel; }
    // query functions
    /** Get the virtual size of the entire page. */
    IMPORT_C TSize DocumentSize() const;
    /** Get the coords of the visible portion of the page. */
    IMPORT_C TRect ViewRect() const;
    // action functions
    /** Set the visibility for each scrollbar.
        Note: Only one parameter used at the moment for turning both on/off. */
	IMPORT_C void SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility/*,TScrollBarVisibility aVVisibility*/);
    /** Open and display a URL within the entire control. */
    IMPORT_C void OpenUrlL(const TDesC& aUrl,TBool aNewWindow=EFalse);
    /** Set the top-left coord for the visible portion of the entire page. */
    IMPORT_C void SetViewPosition(TPoint aViewPosition);
    /** Set the default charset encoding for the entire page. */
    IMPORT_C void SetDefaultEncodingL(const TDesC8& aCharset);
    /** Set the base font for the entire page. */
    IMPORT_C void SetBaseFontL(const TFontSpec& aFontSpec);
    /** Action a cut/copy/paste command. */
    IMPORT_C TBool DoClipboardFunctionL(TClipboardFunc aFunction);
    //* Set scaling factor. */
    IMPORT_C void SetZoomFactorL(TZoomFactor* aZoomFactor);
    /** Find text in page. */
    IMPORT_C TBool FindL(SEdwinFindModel& aFindModel);
    /** Find next text in page. */
    IMPORT_C TBool FindAgainL(SEdwinFindModel& aFindModel);
    /** Select and highlight all text in a page. */
    IMPORT_C void SelectAllTextL();
    /** Get the type of object under the cursor. */
    IMPORT_C TObjectType ObjectContext(const TPoint &aPoint);
    /** Get the type of object that is currently selected. */
    IMPORT_C TObjectType SelectedObjectContext();
private: // new
    COperaControl();
    void ConstructL(CCoeControl*aParent);
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
    void SizeChanged();
private: // from MCoeControlObserver
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
private: // from MOperaDocWindowFactory
    TBool AllowNewDocWindowL(const TDesC& aUrl,const TDesC& aName);
    MOperaDocWindow* CreateDocWindowL(MOperaDocWindowMediator *aObserver);
    void DeleteDocWindow(MOperaDocWindow* aDocWindow);
    MOperaDocWindow* ActiveDocWindow() const;
private: // from MOperaDocWindowViewAdapter
	void DisplayContextPopoutL(TObjectType aType,const TPoint& aScreenPoint,const TPoint& aOffsetPoint);
private: // new
    TBool IsActiveDocWindow(MOperaDocWindow* aDocWindow) const;
    void SetFocusControl(CCoeControl *aControl);
private: // new
    CCoeControl* iParent;
    MOperaControlViewAdapter* iControlViewAdapter;
    COperaModel* iModel;
	CArrayFixFlat<COperaDocWindow*> *iDocWindowList;
    COperaDocWindow* iActiveDocWindow;
    CCoeControl* iFocusControl;
    };

#endif
