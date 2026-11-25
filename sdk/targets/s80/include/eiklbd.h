/*
* ==============================================================================
*  Name        : eiklbd.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox data.
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

#ifndef EIKLBD_H
#define EIKLBD_H

// INCLUDES
#include <e32base.h>
#include <gdi.h>
#include <w32std.h>
#include <eiklbx.h>

// FORWARD DECLARATIONS
class TListItemProperties;

// CLASS DECLARATIONS

/**
 * The <code>TListFontBoundValues</code> class holds global properties for the
 * fonts used in Listboxes.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class TListFontBoundValues
    {
    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        */
        IMPORT_C TListFontBoundValues();
        
    public:     // Data
        /** the width of the maximum width normal character, in pixels */
        TInt iMaxNormalCharWidthInPixels;
        /** the height of the font, in pixels */
        TInt iHeightInPixels;
    };

/**
 * The <code>CListBoxData</code> class is the base class for Listbox data 
 * classes. This class stores one or more instances of fonts in normal, bold, 
 * and italic styles. Text alignment is also taken care of within this class,
 * and by default is set to left-alignment.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CListBoxData : public CBase
    {
    public: 
friend class CListItemDrawer;

    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        * Sets text as left-aligned by default.
        */
        IMPORT_C CListBoxData();

        /**
        * The object destructor.
        */
        IMPORT_C ~CListBoxData();


    // New methods
        
        /**
        * Completes construction of the <code>CListBoxData</code> object.
        * Constructs normal, bold, italic and bold italic fonts based on the
        * specified <code>aBaseFont</code>.
        *
        * @param aBaseFont The font on which the constructed fonts are based
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const CFont* aBaseFont);

        /**
        * Gets the font that the Listbox item is using.
        *
        * @param aItemProperties The properties of the Listbox item
        * @return the Listbox item's font
        * @remarks
        * @see
        */
        IMPORT_C virtual CFont* Font(const TListItemProperties& aItemProperties) const;

        /**
        * Sets the underline style, pen color, and font for the Listbox items.
        *
        * @param aItemProperties The Listbox item properties
        * @param aGc The graphics context
        * @remarks
        * @see
        */
        IMPORT_C void SetupGc(const TListItemProperties& aItemProperties, CWindowGc& aGc) const;

        /**
        * Gets the font bound values. These are global font properties 
        * consisting of the normal character width, and the height of the font, 
        * in pixels. These values are used to calculate item cell sizes, etc.
        * 
        * @return the font bound values
        * @remarks
        * @see TListFontBoundValues in eiklbd.h
        */
        IMPORT_C const TListFontBoundValues& FontBoundValues() const;

        /**
        * Sets the font height for Listbox items, in twips.
        *
        * @param aFontHeightInTwips The required font height, in twips
        * @return an error value
        * @remarks
        * @see
        */
        IMPORT_C TInt SetFontHeight(TInt aFontHeightInTwips);

        /**
        * Sets a search string.
        * This method allows text in the list items displayed
        * that contains the specified search string to be highlighted.
        * 
        * @param aSearchString The required search string
        * @remarks The developer must supply an interface to use this method
        * @see
        */
        IMPORT_C void SetSearchStringL(const TDesC* aSearchString);

        /**
        * Determines whether a search string has been set for this Listbox.
        * 
        * @return <code>ETrue</code> if a search string with a non-zero
        *         length has been set for this Listbox; otherwise
        *         <code>EFalse</code>
        * @remarks
        * @see
        */
        IMPORT_C TBool IsSearchString() const;

        /**
        * Draws list item text into the graphics context, 
        * <code>CWindowGc& aGc</code>, 
        * in the rectangle <code>const TRect& aItemTextRect</code>.
        * Depending on the string, it will either be
        * responsible for drawing a normal text string or a search text
        * string in a rectangle.
        * This method supports different drawing for the search string.
        *
        * @param aGc The graphics context
        * @param aItemTextRect The item's text rectangle
        * @param aItemText The item's text
        * @param aItemFont The item's font
        * @param aBaseLineOffset The item's base line offset
        * @param aMargin  The item's margin
        * @param aAlign The text alignment
        * @remarks This method should be overridden, and is only called by
        *          the item drawer if the search string has been set.
        *          <code>aItemFont</code> is only used to 
        *          calculate the width of the item text and does not override 
        *          the font set used by <code>SetupGc()</code>
        * @see
        */
        IMPORT_C void DrawItem(CWindowGc& aGc,const TRect& aItemTextRect,const TDesC& aItemText,const CFont& aItemFont, const TInt aBaseLineOffset, TInt aMargin, const CGraphicsContext::TTextAlign aAlign=CGraphicsContext::ELeft) const;

        /**
        * Draws list item text into the graphics context, 
        * <code>CWindowGc& aGc</code>, 
        * in the rectangle <code>const TRect& aItemTextRect</code>.
        *
        * @param aGc The graphics context
        * @param aItemTextRect The item's text rectangle
        * @param aItemText The item's text
        * @param aItemFont The item's font
        * @param aBaseLineOffset The item's base line offset
        * @param aAlign The text alignment
        * @remarks <code>aItemFont</code> is only used to 
        *          calculate the width of the item text and does not override 
        *          the font set used by <code>SetupGc()</code>
        * @see
        */
        IMPORT_C void DrawItem(CWindowGc& aGc,const TRect& aItemTextRect,const TDesC& aItemText,const CFont& aItemFont, const TInt aBaseLineOffset,const CGraphicsContext::TTextAlign aAlign=CGraphicsContext::ELeft) const;

        /**
        * Sets the text alignment for list items.
        *
        * @param aAlign The required text alignment
        * @remarks
        * @see <code>CGraphicsContext::TTextAlign</code> in gdi.h
        */
        inline void SetAlignmentL(CGraphicsContext::TTextAlign aAlign);

        /**
        * Gets the text alignment.
        *
        * @return the text alignment
        * @remarks <code>DrawItem()</code> uses this method to retrieve 
        *          alignment settings
        * @see CGraphicsContext::TTextAlign in gdi.h
        */
        inline CGraphicsContext::TTextAlign Alignment() const;

protected:

/**
*  The <code>CFontsWithStyle</code> class stores all fonts used on this 
*  screen device and the current font style.
*
*  @since 6.0
*  @lib eikcoctl.lib
*/
    class CFontsWithStyle : public CBase
        {
    public:
        CFontsWithStyle();
        ~CFontsWithStyle();
    public:

        /**
        * Releases all the member fonts from the screen device.
        */
        IMPORT_C void ReleaseFonts();

        /**
        * Gets the font style.
        * @return The font style.
        * <BR><B>Type of return value:</B> TFontStyle
        */
        IMPORT_C TFontStyle FontStyle();

        /**
        * Sets the font style.
        * @param aFontStyle The font style to be set.
        */
        IMPORT_C void SetFontStyle(TFontStyle aFontStyle);

        /** CArrayPtrFlat<CFont> is used instead of CFont*,
         * because in some subclasses this structure
         * can contain more than 1 font.
     */
        CArrayPtrFlat<CFont>* iFonts;
    private:
        TFontStyle iFontStyle;
        };
    protected:  // Methods

    // New Methods
        
        /**
        * Constructs a font based on the specified font.
        *
        * This function is called by <code>CListBoxData::ConstructL()</code>.
        * @param aBaseFont The font on which the constructed font is based.
        * @param aFontStyle The font style.
        * @param aFonts Font array.
        */
        IMPORT_C void ConstructFontL(const CFont* aBaseFont, TFontStyle aFontStyle, CFontsWithStyle& aFonts);

        /**
        * Updates the font bound values.
        *
        * These are global font properties such as the normal character width in
        * pixels.
        * @param aFont The font for which bound values are updated.
        */
        IMPORT_C void UpdateFontBoundValues(const CFont& aFont);

        /**
        * Regenerates a font based on the font height.
        * @param aFonts The style of font to regenerate.
        * @param aFontHeightInTwips The font height in twips.
        * @return Error value
        * <BR><B>Type of return value:</B> TInt
        */
        IMPORT_C TInt RegenerateFonts(CFontsWithStyle& aFonts, TInt aFontHeightInTwips);

    private: //Methods
        IMPORT_C virtual void Reserved_1();
        IMPORT_C virtual void Reserved_2();

    protected:     // Data
        CFontsWithStyle iNormalFont;
        CFontsWithStyle iBoldFont;
        CFontsWithStyle iItalicFont;
        CFontsWithStyle iBoldItalicFont;
        HBufC* iSearchString;

    private:     // Data
        TListFontBoundValues iFontBoundValues;
        CGraphicsContext::TTextAlign iAlign;
        TAny* iSpare;
    };

// INLINE FUNCTION DEFINITIONS
inline void CListBoxData::SetAlignmentL(CGraphicsContext::TTextAlign aAlign)
    {iAlign=aAlign;}

inline CGraphicsContext::TTextAlign CListBoxData::Alignment() const
    {return iAlign;}

#endif      // EIKLBD_H   
            
// End of File
