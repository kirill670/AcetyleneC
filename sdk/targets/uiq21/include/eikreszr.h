// EIKRESZR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKRESZR_H__
#define __EIKRESZR_H__

#include<coecntrl.h>

/**
 * The MEikResizerObserver class defines an iterface which must be implemented by a control
 * wishing to be informed of CEikResizer associated events.
 *
 * @since ER5
 */
class MEikResizerObserver
	{
public:
	enum TEvent
		{
		EResizedByPointer,
		EDismissedByPointer
		};
public:
	IMPORT_C virtual void HandleResizerEvent(TEvent aEvent, TRect aCurrentRect)=0; 
	};

/**
 * The CEikResizer class implements a resizeable rectangular object which is intended to be used
 * in the resizing of an owning control. It can handle pointer events, or have pointer events,
 * and/or 'GrowL' calls made to it.
 *
 * @since ER5
 */

class CEikResizer : public CBase
	{
public:
	/**
	 * The TScaleMode enum is used to determines whether the resizer should use its own(Auto)
	 * or Client set ratios. The ratios are used to scale the amount to grow in calls to GrowL().
	 *
 	 */
	enum TScaleMode
		{
		EAuto,
		EUseClientRatios
		};
	/**
	 * The TUpperBoundMode enum determines the bounding type to use for the upper limit of the resizer's size.
	 *
	 */
	enum TUpperBoundMode
		{
		ENoUpperBound,
		EClipToMaximumRect, //grows until it meets maximum rect.
		EClipToMaximumSize //grows until it is same size as maximum rect
		};
	/**
	 * The TFixedEdges enum determines the edges of the resizer which are locked
	 * in position(but not neccesarily length).
	 *
 	 */
	enum TFixedEdges // Fixed in Position not length
		{
		ETopEdge=0x1,
		ERightEdge=0x2,
		EBottomEdge=0x4,
		ELeftEdge=0x8
		};
public://C'tor/D'tor
	IMPORT_C static CEikResizer* NewL(CCoeControl& aResizableControl, TInt aFixedEdges);
	IMPORT_C ~CEikResizer();
private:
	CEikResizer(CCoeControl& aResizable, TInt aFixedEdges);
	void ConstructL();
public:
	IMPORT_C static TBool PointerEventWouldStartResize(CCoeControl& aResizableControl,const TPointerEvent& aPointerEvent); 
	IMPORT_C void SetNonFixedEdgesPositionL(const TPoint& aPoint);
	IMPORT_C void GrowL(TSize aDelta);
	IMPORT_C void SetClientScaleRatios(TSize aHorizontalAndVertical);
	IMPORT_C void SetScaleMode(TScaleMode aMode);
	IMPORT_C void SetUpperBoundMode(TUpperBoundMode aUpperBoundMode);
	IMPORT_C void SetFixedEdges(TInt aFixedEdges);
	IMPORT_C void SetMaximumRect(const TRect& aRect);
	IMPORT_C void SetMinimumSize(const TSize& aSize);
	IMPORT_C TInt FixedEdges() const;
	IMPORT_C TUpperBoundMode UpperBoundMode() const;
	IMPORT_C TScaleMode ScaleMode() const;
	IMPORT_C TSize ClientScaleRatios() const;
	IMPORT_C TRect MaximumRect() const;
	IMPORT_C TSize MinimumSize() const;
	IMPORT_C TRect ResizerRect() const;
	IMPORT_C void SetResizerRect(const TRect& aRect);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void SetHandlesPointerEventsL(TBool aBool);
	IMPORT_C TBool HandlesPointerEvents();
	IMPORT_C void SetResizerObserver(MEikResizerObserver* aObserver);
private:
	void DoGrow(TSize aSize, TRect& aRect) const;
	TBool CheckRedrawIsNeededAndClipRectIfNeccessary(TRect& aRect) const;
	void GrowHorSpritesL(const TRect& aRect);
	void GrowVerSpritesL(const TRect& aRect);
	void DrawSpritesL(const TRect& aRect);
	void PositionVerSprites(const TRect& aRect);
	void PositionHorSprites(const TRect& aRect);
	TSpriteMember CreateSpriteMember(TInt aBmpIndex);
	void ResizeAndDrawBitmapL(const TRect& aRect, CFbsBitmapDevice* aDevice);
	void PositionSprites();
	void ClipRectToMaximumRect(TRect& aRect) const;
	void LockAppropriateEdges(TPoint aPoint);
	//TBool PointerEventInValidRegion(TPoint aPosition);
private:
	class CControlForPointerEvents : public CCoeControl
		{
	public:
		CControlForPointerEvents(CEikResizer& aResizer);
		~CControlForPointerEvents();
	public:
		void SetHandlesPointerEvents(TBool aBool);
		TBool HandlesPointerEvents();
	protected://From CCoeControl
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	private:
		CEikResizer& iResizer;
		TBool iHandlesPointerEvents;
		};
private:
	CControlForPointerEvents*		 iControl;
	TFixedArray<RWsSprite,4>		 iSprites;
	TFixedArray<CFbsBitmap*,2>		 iBitmaps;
	TFixedArray<CFbsBitmapDevice*,2> iBmpDevices;
	MEikResizerObserver*			 iResizerObserver;
	CFbsBitGc*		iFbsBitGc;
	TSize			iClientScale;
	TSize			iAutoScale;
	TScaleMode		iScaleMode;
	TInt			iFixedEdges;
	TUpperBoundMode	iUpperBoundMode;
	TRect			iMaximumRect;
	TSize			iMinimumSize;
	TRect			iCurrentRect;
	TBool			iDragWillBeValid;
	};

#endif