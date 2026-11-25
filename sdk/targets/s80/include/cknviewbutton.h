/*
* =============================================================================
*  Name        : cknviewbutton.h
*  Part of     : CKON
*  Interface   : View Button API
*  Description : View button class
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* =============================================================================
*/


#ifndef CKNVIEWBUTTON_H
#define CKNVIEWBUTTON_H

// INCLUDES
#include <cknbuttonbase.h>

class CCknSkinBase;
/**
*  The <code>CCknViewButton</code> class provides a standard View Button, 
*  which can be used in a view or a dialog. A View Button can resize both 
*  horizontally and vertically. <b>Note</b>: This control is not used to 
*  create the command bar buttons in a view. It is used to create additional 
*  buttons within the application area.
*
*  @lib cknctl.lib 
*  @since Series 90 1.0
*/
class CCknViewButton : public CCknButtonBase
    {
    public: 
    /**
     * The enumeration <code>THighlightType</code> specifies whether the 
     * View Button is drawn with a highlight.
     */
    enum THighlightType
        {
        /** no highlight, the button is drawn as normal */
        EHighlightNone=0x00,
        /** a highlight is displayed within the button border */
        EHighlightInside=0x01,
        /** a highlight is displayed around the outside of the button */
        EHighlightOutside=0x02
        };
    
    /** 
     * The enumeration <code>TType</code> specifies the shape of the View 
     * Button. 
     */
    enum TType
        {
        /** no rounded corners */
        EType1,
        /** rounded corners on the left-hand side only */
        EType2,
        /** rounded corners on the right-hand side only */
        EType3,
         /** all four corners are rounded */
        EType4 
        };

    public:

        /**
        * Starts the two-phase object construction. This method calls the 
        * constructor 
        * that sets up the View Button's skin-dependent top and bottom margins 
        * and then calls the protected method, <code>ConstructL()</code>. 
        *
        * @return a pointer to the new <code>CCknViewButton</code> object
        * @remarks Sets the default type to <code>EType4</code>
        * @see
        */
        IMPORT_C static CCknViewButton* NewL();

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknViewButton();

        /**
        * Sets the type and margin of the View Button. The left
        * and right margins of View Buttons are different, depending on the 
        * button type.
        *
        * @param aViewButtonType The type of View Button. The shape types are: 
        *        <code>EType1</code>, <code>EType2</code>, <code>EType3</code>,
        *        or <code>EType4</code>
        * @remarks
        * @see
        */
        IMPORT_C void SetType(TType aViewButtonType);

        /**
        * Sets the highlight type for the View Button.
        *
        * @param aHighlightType Sets the highlight type:
        *        <code>EHighlightNone</code>, <code>EHighlightInside</code>, or 
        *        <code>EHighlightOutside</code>
        * @remarks
        * @see
        */
        IMPORT_C void SetHighlightType(TUint32 aHighlightType);

        /**
        * Gets the minimum size of this View Button control.
        *
        * @return the size of the View Button
        * @remarks
        * @see
        */
        IMPORT_C TSize MinimumSize();		

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CCknViewButton();
    protected: // from CCoeControl

        /**
        * Draws this control. See CCoeControl.
        * @param aRect The region of the control to be redrawn. 
        * Co-ordinates are relative to the control's origin (top left corner).
        */
        IMPORT_C void Draw(const TRect& aRect) const;

	protected: 
		// From CCoeControl
		IMPORT_C void FocusChanged(TDrawNow aDrawNow);

    protected:
        IMPORT_C void ConstructL();

        void GetTopLeftCorner(TInt& aBitmapIndex) const;
        void GetBottomRightCorner(TInt& aBitmapIndex) const;
        void GetTopRightCorner(TInt& aBitmapIndex) const;
        void GetBottomLeftCorner(TInt& aBitmapIndex) const;
        void GetTopMidSection(TInt& aBitmapIndex) const;
        void GetBottomMidSection(TInt& aBitmapIndex) const;
        void GetLeftMidSection(TInt& aBitmapIndex) const;
        void GetRightMidSection(TInt& aBitmapIndex) const;
        void GetCenterRectColor(TRgb& aColor) const;
        TRect InnerRect(const TRect& aOuterRect) const;
        void DrawToScreen(const TRect& aRect) const;
        void DrawBorder(CWindowGc* aBitmapGc, TRect& aRect) const;
    protected:
        TType iType; 
        TUint32 iHighlightType;
        CCknSkinBase& iSkin;

    private:
        TBool iMbmDuplicated;
        void *iReserved;
    };


#endif  // CKNVIEWBUTTON_H

// End of File