/*
* ==============================================================================
*  Name        : cknborder.h
*  Part of     : CKON/CKNCTL
*  Interface   : Border Controls API
*  Description : This class implements the borders for controls and pop-out windows.
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


#ifndef CKNBORDER_H
#define CKNBORDER_H

// INCLUDES
#include <e32def.h>
#include <guldef.h>
#include <gdi.h>

class CCknSkinBase;
/**
*  The <code>TCknBorder</code> class implements the borders for controls and 
*  pop-out windows.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class TCknBorder
    {

    public:
    /** 
     * The enumeration <code>TCknBorder</code> defines the possible border types.
     * The style of the borders is skin-dependant. 
     */
    enum TCknBorderType
        {
        /** no border */
        ENone,
        /** the pop-out window border type for the selected skin */
        EPopoutWindow,
        /** the control border type for the selected skin */
        EControl,
        /** the application border type for the selected skin */
        EApplicationView
        };
    

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C TCknBorder();

        /**
        * The C++ object constructor. This constructor sets a border.
        *
        * @param aType The border type
        * @remarks
        * @see TCknBorderType
        */
        IMPORT_C TCknBorder(TCknBorderType aType);

        /**
        * Returns the usable inner rectangle area enclosed by the border,
        * given an outer rectangle <code>aOuterRect</code>, in which the 
        * border will be drawn.
        *
        * @param aOuterRect The outer rectangle area
        * @return the usable inner rectangle area
        * @remarks
        * @see
        */
        IMPORT_C TRect InnerRect(const TRect& aOuterRect) const;

        /**
        * Returns the outer rectangular area required to accommodate the
        * border and an inner rectangular area <code>aInnerRect</code>.
        *
        * @param aInnerRect The inner rectangle area
        * @return the outer rectangle area including the border
        * @remarks
        * @see
        */
        IMPORT_C TRect OuterRect(const TRect& aInnerRect) const;

        /**
        * Sets the type of the border.
        * 
        * @param aType The type of border
        * @remarks
        * @see
        */
        IMPORT_C void SetType(TCknBorderType aType);

        /**
        * Returns the size difference between the inner and outer rectangles of 
        * the border.
        * 
        * @return a variable containing the size difference
        * @remarks
        * @see
        */
        IMPORT_C TSize SizeDelta() const;

        /**
        * Returns margins based on the skin settings.
        *
        * @return a variable containing the parameters of the margins
        * @remarks The margins depend on the type of border control. If the 
        *          type is not set, the margins will be set to zero.
        *          The current skin determines the margin value. See the Skin 
        *          API for further information
        * @see
        */
        IMPORT_C TMargins Margins() const;

        /**
        * Returns the type of border.
        *
        * @return the type of border. The values are defined in the enum 
        *         <code>TCknBorderType</code>.
        * @remarks
        * @see
        */
        IMPORT_C TInt Type() const;

        /**
        * Draws a border relative to the currently selected skin border. 
        * 
        * @param aGc The graphics context
        * @param aRect The outer edges of the border
        * @remarks
        * @see
        */
        IMPORT_C void Draw(CGraphicsContext& aGc,const TRect& aRect) const;

        /**
        * Draws a masked version of a pop-out window border. If the type is set
        * to anything other than <code>EPopoutWindow</code>, the border is 
        * drawn without a mask. See the Skin API <code>DrawWindowBorder()</code> 
        * method for a complete description of the functionality.
        *
        * @param aGc The graphics context
        * @param aRect The outer edges of the border
        * @remarks
        * @see
        */
        IMPORT_C void DrawMasked(CGraphicsContext& aGc, const TRect& aRect) const;

        /**
        * Draws the border for both <code>EPopoutWindow</code>,
        * <code>EControl</code> and <code>EApplicationView</code>. Types set to 
        * <code>ENone</code> are ignored.
        *
        * @param aGc The graphics context
        * @param aRect The outer edges of the border
        * @param aDimmed Only used by <code>EControl</code>. 
        *        Determines whether the control is dimmed
        * @remarks
        * @see
        */
        IMPORT_C void Draw(CBitmapContext& aGc,const TRect& aRect, TBool aDimmed=EFalse) const;

    private:
        TCknBorderType iType;
        CCknSkinBase* iSkin;
    };



#endif  // CKNBORDER_H

// End of File
