/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Rob Gregson, Keith Hollis
*/

#ifndef __EPOCABSTRACTFRAME_H
#define __EPOCABSTRACTFRAME_H

#include <e32std.h>
#include <eikscrlb.h>
#include <eiksbfrm.h>

#include "epocprefs.h"
#include "epocabstractformcontrols.h"

struct SEdwinFindModel;
class MOperaPlugin;

/*************************************************************************

    class MOperaFormControlFactory
*/

class MOperaFormControlFactory 
    {
public:
    virtual MOperaFormControl* NewControlL(MOperaFormControl::TType aObjectType,
    									   MOperaFormControlObserver* aFormControlObserver)=0;
    };

/*************************************************************************

    class MOperaFrameObserver

    This class is implemented in Opera base code - not for porting
    - is informed when any changes are made in the UI
*/

class MOperaFrameObserver
	{
public: 
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)=0;
	// returns ETrue if pointer event has been handled
	virtual TBool OfferPointerEventL(const TPointerEvent& aPointerEvent)=0;
	virtual void SizeChanged()=0;
	virtual void PosChangedX(TInt aX)=0;
	virtual void PosChangedY(TInt aY)=0;
    virtual void HandleChangeInFocus(TBool aFocus)=0;
	};

/*************************************************************************

    class MOperaFrameAdapter

    These classes are implemented in Opera base code - not for porting
    - makes changes to control selection
*/

class MOperaFrameAdapter
    {
public:
    // query functions
	virtual const TDesC* Url()=0;	// get current URL
	virtual const TDesC* Title()=0;	// get current title
    virtual TObjectType ObjectContext(const TPoint &aPoint/*,MOperaFormControl::TType& aInputType*/)=0;
    virtual TObjectType ObjectContextL(const TPoint &aPoint, HBufC* &aUrl)=0;
    virtual TObjectType SelectedObjectContext(/*MOperaFormControl::TType& aInputType*/)=0;
    virtual TObjectType SelectedObjectContextL(HBufC* &aUrl)=0;
	virtual TBool HistoryHasPrevious()=0;
	virtual TBool HistoryHasNext()=0;
	virtual TBool IsInline()=0;
    // action functions
    virtual void OpenUrlL(const TDesC& aUrl,TBool aNewWindow=EFalse)=0;
	virtual void SaveDocWindowL(const TFileName &aFileName,TBool aWithImages)=0;
	virtual TBool SaveSelectedImageL()=0;
	virtual TBool SaveImageL(TPoint aPoint)=0;
	virtual TBool LoadSelectedImageL()=0;
	virtual TBool LoadImageL(TPoint aPoint)=0;
	virtual void SelectAllText()=0;
	virtual TBool SearchTextL(SEdwinFindModel *aFindModel)=0;
	virtual HBufC* GetTextSelectionInHBufLC()=0;
	virtual TBool HighlightNextFormControl(MOperaFormControl* aFormControl)=0;
	virtual TBool HighlightPreviousFormControl(MOperaFormControl* aFormControl)=0;
	virtual void HistoryLoadPrevious()=0;
	virtual void HistoryLoadNext()=0;
	virtual void ReloadFrame()=0;
	virtual TBool SubmitFormL()=0; // tries to submit current html element (if it's an input image)
	// effectively a redraw/invalidate command via the model
	virtual void RedrawRect(const TRect& aRect) const=0;
	};

/*************************************************************************

    class MOperaFrameMediator

    This class is implemented in Opera base code - not for porting
    - handles observation of and control of UI (concrete) frames
*/

class MOperaFrameMediator : public MOperaFrameObserver, public MOperaFrameAdapter
    {};
 
/*************************************************************************

	class MOperaFrameFactory
*/

class MOperaFrameFactory
	{
public:
	virtual MOperaFrame* CreateFrameL(MOperaFrameMediator* aFrameMediator)=0;
	virtual void DeleteFrame(MOperaFrame* aFrame)=0;
	};

/*************************************************************************

    class MOperaFrame

    This class is a template for porting
*/

class MOperaFrame : public MOperaFrameFactory, public MOperaFormControlFactory
    {
public:
	virtual void SetExtent(const TPoint& aPoint,const TSize& aSize)=0;
    virtual void MakeVisible(TBool aVisible)=0;
	virtual TRect ClientRect() const=0;
	virtual CWindowGc* GetGraphicsContext()=0;
	virtual void Invalidate(const TRect& aRect)=0;
	virtual void SetFocused()=0;
	// NB NewControlL (from MOperaFormControlFactory) is assumed also to add 
	//    the control to the frame 
	virtual void RemoveControl(MOperaFormControl* aFormControl)=0;
	virtual void ControlSetFocusedL(MOperaFormControl* aFormControl)=0;
    virtual MOperaPlugin* CreatePluginWindowL(const TRect&aRect)=0;
	virtual void DeletePluginWindow(MOperaPlugin*aPlugin)=0;

	virtual void AddRadioButtonToCurrentGroupL(TBool aNewGroup,MOperaFormControl* aRadioButton)=0;
	virtual TRect Rect() const=0;
	virtual void Invalidate()=0;
	virtual void SetScrollBars(TInt aVirtualWidth,TInt aVirtualHeight,TInt aXOffset,TInt aYOffset,TScrollingMode aScrollingMode)=0;
	virtual void SetXScrollBar(TInt aX)=0;
	virtual void SetYScrollBar(TInt aY)=0;
	virtual void Scroll(TInt aDx,TInt aDy)=0;

	// Core extensions.
	virtual void HighlightLinkRegion(const TRegion& aRegion,TInt aBorder,const TDesC&aUrl,TBool aClear)=0;
	virtual void HighlightLinkRect(const TRect& aRect,TInt aBorder,const TDesC&aUrl,TBool aClear)=0;
	virtual void HighlightLinkEllipse(const TRect& aRect,TInt aBorder,const TDesC&aUrl,TBool aClear)=0;
	virtual void HighlightLinkPolygon(const CArrayFix<TPoint>* aPointList,TInt aBorder,const TDesC&aUrl,TBool aClear)=0;
	};

#endif
