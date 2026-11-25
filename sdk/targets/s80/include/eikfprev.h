/*
* ==============================================================================
*  Name        : eikfprev.h
*  Part of     : CKON
*  Interface   : Label API
*  Description : Font preview Label widget.
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

#ifndef EIKFPREV_H
#define EIKFPREV_H

//** INCLUDES *
#include <eiklabel.h>

//** FORWARD DECLARATIONS *
class TResourceReader;

/**
* The <code>CEikFontPreviewLabel</code> class is derived from 
* <code>CEikLabel</code> used for previewing a font.
* It is constructed as an auto-wrapping Label with only two lines. It 
* has methods for modifying the displayed text, for example, for setting 
* underline and strikethrough options and colors. 
*
* Used internally and not intended to be used for application development.
* Used by the Font Preview dialog.
*
* @internal
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikFontPreviewLabel : public CEikLabel
    {
    public:

        /**
        * The C++ default object constructor.
        */
        IMPORT_C CEikFontPreviewLabel();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikFontPreviewLabel();

        /**
        * Sets the minimum size of the font preview Label.
        *
        * @param aSize The minimum size.
        * @return 
        * @remarks
        * @see CCoeControl
        */
        inline void SetMinimumSize(const TSize& aSize);

        /**
        * Sets the background color of the font preview Label.
        *
        * @param aColor The background color
        * @return
        * @remarks
        * @see
        */
        inline void SetBackgroundColor(TRgb aColor);

        /**
        * Sets the text color of the font preview Label.
        *
        * @param aColor The text color
        * @return 
        * @remarks
        * @see
        */
        inline void SetPenColor(TRgb aColor);

        /**
        * Sets whether underline should be on or off.
        *
        * @param aUnderline Either <code>EUnderlineOff</code> or 
        *        <code>EUnderlineOn</code>
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetUnderline(TFontUnderline aUnderline);

        /**
        * Sets whether strike-through should be on or off.
        *
        * @param aStrikethrough Either <code>EStrikethroughOff</code> or 
        *        <code>EStrikethroughOn</code>
        * @return 
        * @remarks
        * @see
        */
        IMPORT_C void SetStrikethrough(TFontStrikethrough aStrikethrough);

        /**
        * Sets the text of the font preview Label.
        *
        * @param aText The Label's text
        * @return 
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

    public: //** Framework *

        /**
        * Constructs a Label from a resource file. 
        * 
        * @param aReader A resource reader
        * @return
        * @remarks The resource type is <code>FPREV</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Gets the minimum size of this Label for automatic layout control
        * contexts such as dialogs.
        *
        * @return the width and height of the Label
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Draws the Label control on request.
        *
        * @param aRect Optional. If supplied, the rectangle in which to draw 
        *              the Label
        * @return
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        // Not available before Release 005u
        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @return
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        // Not available before Release 005u
        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        *
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @return
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

    protected:
        TSize iMinSize;
        TEikLabelColors iColors;
    private:
        TInt iSpare;
    };


inline void CEikFontPreviewLabel::SetMinimumSize(const TSize& aSize)
    { iMinSize=aSize; }
inline void CEikFontPreviewLabel::SetBackgroundColor(TRgb aColor)
    { iColors.iBrush=aColor; }
inline void CEikFontPreviewLabel::SetPenColor(TRgb aColor)
    { iColors.iPen=aColor; }


#endif //** EIKFPREV_H *

//** End of File *
