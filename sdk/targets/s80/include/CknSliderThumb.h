// CknSliderThumb.h
//
// Copyright (c) Nokia Corporation 2002. All rights reserved.
//

#if !defined(__CKNSLIDERTHUMB_H__)
#define __CKNSLIDERTHUMB_H__

#include <coecntrl.h>

/**
 * The <code>CCknSliderThumb</code> class [what].
 *
 * @lib [what]
 * @since Series 90 1.0
 */
class CCknSliderThumb : public CCoeControl
    {
public:
    /** The enumeration <code>TMovementDirection</code> specifies [what]. */
    enum TMovementDirection
        {
        /** [what] */
        EHorizontal,
        /** [what] */
        EVertical
        };

    /** @internal */
    CCknSliderThumb(TMovementDirection aOrientation,TInt aThickness,TInt aHeight);
    
    /** @internal */
    void SetBitmaps(const CFbsBitmap* aThumbBitmap, const CFbsBitmap* aThumbMask, const CFbsBitmap* aDimmedThumbBitmap, const CFbsBitmap* aDimmedThumbMask);
    
    /** @internal */
    void SetZeroPosition(TPoint aZeroPosition);
    
    /** @internal */
    TBool SetThumbPosition(TInt aNewPosition); //updates Rect
    
    /** @internal */
    TInt ThumbPosition();
    
    /** @internal */
    void SetThumbRange(TInt aRangeInPixels);
    
        /** @internal */
    TInt ThumbRange();
    
    /** @internal */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /** @internal */
    TRect OldRect() { return iOldRect; };
public:// from CCoeControl

    /** @internal */
    void ActivateL();

    /** @internal */
    void Draw(const TRect& aRect) const;
private:
    TMovementDirection iOrientation;
    TInt iThickness;
    TInt iHeight;
    TPoint iZeroPosition; //the position of the thumb at its leftmost/topmost position
    TInt iRelPosition; //the relative position of left/top of the thumb
    TInt iRange;
    TBool iDragging;
    TPoint iDragStartPosition;
    TRect iOldRect;
    const CFbsBitmap* iBitmap;
    const CFbsBitmap* iMask;
    const CFbsBitmap* iBitmapDimmed;
    const CFbsBitmap* iMaskDimmed;
    };
    

#endif