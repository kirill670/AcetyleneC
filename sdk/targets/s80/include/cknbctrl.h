/*
* ==============================================================================
*  Name        : cknbctrl.h
*  Part of     : CKON / CKNCTL
*  Interface   : Bordered Controls API
*  Description : This class implements a bordered control relative to the current
*                skin settings. Another usefull aspect of this class is it has a
*                protected member variable iSkin (reference to the skin manager).
*                Any class derived from this will have access to the skin manager
*                via the iSkin member variable.
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


#ifndef CKNBCTRL_H
#define CKNBCTRL_H

// INCLUDES
#include <cknborder.h>
#include <coecntrl.h>

class CCknSkinBase;

/**
*  The <code>CCknBorderedControl</code> class implements a Bordered Control.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknBorderedControl : public CCoeControl
    {
    public:

        /**
        * The default object constructor. This constructor does not set the 
        * border.
        *
        * @remarks
        * @see
        */
        IMPORT_C CCknBorderedControl();

        /**
        * The object constructor. This constructor sets the border.
        *
        * @param aBorder A reference to a <code>TCknBorder</code> border type
        * @remarks
        * @see TCknBorderType in cknborder.h
        */
        IMPORT_C CCknBorderedControl(const TCknBorder& aBorder);
    public: // new function

        /**
        * Sets the type of border for the control.
        *
        * @since Series90 1.0
        * @param aBorderType The type of border
        * @remarks
        * @see TCknBorder::TCknBorderType
        */
        IMPORT_C void SetBorder(TCknBorder::TCknBorderType aBorderType);

        /**
        * Returns the border for the bordered control.
        *
        * @since Series90 1.0
        * @return the <code>TCknBorder</code> object
        * @remarks
        * @see
        */
        IMPORT_C TCknBorder Border() const;
    protected: // from CCoeControl

        /**
        * From CCoeControl.  Draws the border
        * @param aRect This parameter is ignored
        */
        IMPORT_C void Draw(const TRect& aRect) const;
    protected:
        TCknBorder iBorder;

        CCknSkinBase& iSkin;

    private:
        TAny* iReserved;
    };


#endif  // CKNBCTRL_H

// End of File
