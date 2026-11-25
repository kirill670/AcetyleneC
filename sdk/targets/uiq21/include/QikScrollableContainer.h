// QikScrollableContainer.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz


#ifndef __QIKSCROLLABLECONTAINER_H__
#define __QIKSCROLLABLECONTAINER_H__

#include <coecntrl.h>		// class CCoeControl
#include <eikscrlb.h>		// class CEikScrollBar & MEikScrollBarObserver
#include <coeccntx.h>		// class MCoeControlContext


class CQikScrollableContainerPage;
class CEikScrollBarFrame;

/**
 * This is a container for CCoeControl-derived controls that adds horizontal and/or vertical scrollbar(s)
 * when needed. To use this container, simply add the controls to it, position them relative the upper left corner
 * of the scrolling page, and call the MinimumPageSize() method to find the size needed to hold all the controls.
 * Use the SetPageSize() method to set the size of the scrolling page. A margin is added to the size given
 * when a scrollbar is needed (can be changed with the SetBottomRightMargin() method).
 *
 * @since Quartz 6.0
 */
class CQikScrollableContainer : public CEikBorderedControl, public MEikScrollBarObserver, public MCoeControlContext
	{
public:
	IMPORT_C CQikScrollableContainer();
	IMPORT_C ~CQikScrollableContainer();
	IMPORT_C void ConstructL(TBool aPreAllocScrollBar);
	IMPORT_C CEikScrollBarFrame* const ScrollBarFrame();

	IMPORT_C void AddControlL( CCoeControl* aControl );
	IMPORT_C TInt DeleteControl( const CCoeControl* aControl );
	IMPORT_C void ResetAndDestroy();

	IMPORT_C TSize MinimumPageSize() const;
	IMPORT_C void SetPageSize( TSize aSize );
	IMPORT_C TSize PageSize() const;
	IMPORT_C const CCoeControl& Page() const;	// Use this as ContainerWindow for all controls (and their subcontrols) that you add to the scrollable container.
	IMPORT_C TBool ControlsFitOnPage() const;
	IMPORT_C void UpdateScrollBarsL();

	IMPORT_C void ScrollToMakeVisible( const CCoeControl* aControl ) const;
	IMPORT_C TPoint ScrollOffset() const;
	IMPORT_C void ScrollTo( TPoint aTopLeft ) const;
	IMPORT_C void Scroll(TInt aDeltaX, TInt aDeltaY) const;

	IMPORT_C void SetBottomRightMargin( TSize aMargin );
	IMPORT_C TSize BottomRightMargin() const;
	IMPORT_C void SetScrollObserver( MEikScrollBarObserver* aObserver );
	IMPORT_C void ScrollBarsNeeded(TBool& aVerticalScrollBar, TBool& aHorizontalScrollBar ) const;
public:
	// from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
	IMPORT_C void MakeVisible(TBool aVisible);
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	// from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
protected:
	// from MEikScrollBarObserver
	IMPORT_C void HandleScrollEventL( CEikScrollBar* aScrollBar, TEikScrollEvent aEventType );
	//from CCoeControl
	IMPORT_C void SizeChanged();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
private:
	CQikScrollableContainerPage* iScrollablePage;
	CEikScrollBarFrame* iScrollBarFrame;
	MEikScrollBarObserver* iScrollObserver;
private:
	TInt iQikSpare1;
	};


#endif // __QIKSCROLLABLECONTAINER_H__






