/*
* ==============================================================================
*  Name        : eikbctrl.h
*  Part of     : CKON / COCTLINC
*  Interface   : Bordered Controls API
*  Description : A control that is drawn surrounded by a rectangular border.
*                This class is used as the basis for most Uikon controls.
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
* ==============================================================================
*/


#ifndef EIKBCTRL_H
#define EIKBCTRL_H

// INCLUDES
#include <gulbordr.h>
#include <coecntrl.h>

/**
 * Where possible the <code>CCknBorderedControl</code> class should be used
 * instead of <code>CEikBorderedControl</code>.
 * The <code>CEikBorderedControl</code> class provides a control that is drawn 
 * surrounded by a rectangular border. 
 * This class is used as the basis for most Uikon controls. The screen
 * appearance of derived classes can be changed by overriding the
 * protected method <code>Draw()</code>. By default, this draws a border
 * of the appropriate type around the control.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */

class CEikBorderedControl : public CCoeControl
    {
    public:

        /**
        * The default object constructor. This constructor does not set the 
        * border.
        *
        * @see
        * @remarks
        */
        IMPORT_C CEikBorderedControl();

        /**
        * The object constructor. This constructor sets the border.
        *
        * @param aBorder The border type
        * @see
        * @remarks
        */
        IMPORT_C CEikBorderedControl(const TGulBorder& aBorder);

    public: // from CCoeControl

        /**
        * Tests whether the control has a border. 
        * This method overrides <code>CCoeControl::HasBorder()</code>.
        *
        * @return <code>ETrue</code> if the control has a border; 
        *         <code>EFalse</code> otherwise
        * @remarks Returns <code>ETrue</code> if the border type is not
        *                  <code>ENone</code>
        * @see
        */
        IMPORT_C TBool HasBorder() const;

        /**
        * Sets the adjacency of the control.
        * This method declares that a control abuts another control along one 
        * edge and does not need to be drawn with a full border along that
        * side. This is for use by layout engines or any developer code that 
        * lays out controls next to one another.
        * 
        * @param aAdjacent A <code>TInt</code> value from <code>TCoeAdjacent</code> 
        *                  declaring which edge of this control is shared
        * @remarks
        * @see
        */
        IMPORT_C void SetAdjacent(TInt aAdjacent);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across the
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource that 
        *              has changed
        * @remarks 
        * @see
        */
        IMPORT_C void HandleResourceChange(TInt aType);

    public: // new function

        /**
        * Sets the border type from the enumeration <code>TGulBorder::TBorderType</code>.
        * This overloaded method sets the border type to
        * <code>aBorderType</code> for a value from the enumeration.
        * 
        * @param aBorderType The new value for the border type
        * @remarks
        * @see
        */
        IMPORT_C void SetBorder(TGulBorder::TBorderType aBorderType);

        /**
        * Sets the border type to <code>aBorderType</code>.
        * 
        * @param aBorderType Valid border types are specified by the values
        * from the enums <code>TGulBorder::TBorderType</code> or 
        * <code>TGulBorder::TLogicalType</code>. Custom border types can be 
        * created by selecting one of the following and OR-ing these values
        * together: 
        * <ul>
        * <li> One value from each of the enums <code>TGulBorder::T3DStyle</code>
        *      and <code>TGulBorder::TConstructionStyle</code>
        * <li> At most one value from the enums <code>TGulBorder::TOutlineStyle</code>
        *      and <code>TGulBorder::TInlineStyle</code>
        * <li> At least one value from the enums <code>TGulBorder::TThickness</code>
        *      and <code>TGulBorder::TRounding</code>
        * </ul>
        *
        * @remarks
        * @see
        */
        IMPORT_C void SetBorder(TInt aBorderType);

        /**
        * Gets the border type.
        * 
        * @return the border type
        * @remarks
        * @see
        */
        IMPORT_C TGulBorder Border() const;

    protected: // from CCoeControl

        /**
        * Draws the border around the control.
        * This function also clears the central area if the
        * <code>IsBlank()</code> method returns <code>ETrue</code>.
        * 
        * @param aRect Optional. If supplied, the screen rectangle to be updated.
        *                        (you may well have to overide this method to make
        *                        use od the aRect param).
        * @return void
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Writes the internal state of the control and its components to aStream.
        * Does nothing in release mode.
        * Designed to be overidden and base called by subclasses.
        *
        * @param aWriteStream The aWriteStream object to write to
        * @return void
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    protected:
        TGulBorder iBorder;
    };




#endif  // EIKBCTRL_H

// End of File
