/*
* ==============================================================================
*  Name        : eiklabel.h
*  Part of     : CKON
*  Interface   : Label API
*  Description : Label control class.
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

#ifndef EIKLABEL_H
#define EIKLABEL_H

//** INCLUDES *
#include <eikalign.h>
#include <coeccntx.h>

//** FORWARD DECLARATIONS *
class CEikLabelExtra;
class MCknLabelObserver;

/**
 * The <code>CEikLabel</code> class displays one or more lines of text. It 
 * provides methods to set the text and font that is used when displaying the 
 * Label control. This control is usually used as a compound control by buttons 
 * or by specific type of Labels.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikLabel : public CEikAlignedControl, public MCoeControlContext
    {
    public: //** New functions *

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikLabel();

        /**
        * The default object constructor.
        */
        IMPORT_C CEikLabel();

    public:

        /**
        * Gets the minimum size of the Label.
        *
        * @return the width and height of the Label
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Constructs a <code>CEikLabel</code> from a resource file.
        *
        * @param aReader A resource reader
        * @remarks The resource type is <code>LABEL</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks Not available before Release 005u
        * @see CCoeControl
        * @see TCoeColorUse
        */
        IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        *
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks Not available before Release 005u
        * @see CCoeControl
        */
        IMPORT_C void HandleResourceChange(TInt aType);

    protected: //** From CCoeControl *

        /**
        * Draws the Label control on request
        * @param aRect Optional. If supplied, the rectangle in which to draw the Label
        * @return none
        * @see CCoeControl.
        */
        IMPORT_C void Draw(const TRect& aRect) const;

    protected: //** From MCoeControlContext *

        /**
        * Do not use.
        */
        IMPORT_C void PrepareContext(CWindowGc& aGc) const;

    public:
        /**
         * The enumeration <code>TTextEmphasis</code> determines text emphasis.
         * The Label pen and brush colors are modified depending on the
         * state of the emphasis.
         */
        enum TTextEmphasis
            {
            /**
             * the text is drawn with no emphasis.
             * The colors are set to reflect that the Label is not selected
             * and does not have focus
             */
            ENoEmphasis      =0x00,
            /**
             * the text is drawn partially emphasized.
             * The colors are set to reflect that the Label is selected but
             * does not have focus
             */
            EPartialEmphasis =0x10,
            /** 
             * the text is drawn with full emphasis.
             * The colors are set to reflect that the Label is selected and
             * has focus
             */
            EFullEmphasis    =0x20
            };

        /**
        * The enumeration <code>TEikLabelColors</code> stores background and 
        * text colors for the Label.
        */
        struct TEikLabelColors
            {
            /** the background color */
            TRgb iBrush;
            /** the text color */
            TRgb iPen;
            };

    public: //** New functions *

        /**
        * Set the text of the Label.
        *
        * @param aText The Label's text
        * @remark If the total number of lines after formatting exceeds 
        *         <code>MaxNumberOfLines()</code>, the method leaves with the 
        *         error <code>KErrOverflow</code>
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Gets the text of the Label.
        *
        * @return a pointer to the text of the Label
        * @remarks
        * @see
        */
        inline const TDesC* Text() const;

        /**
        * Sets the length of the buffer reserve. This method pre-allocates 
        * memory for the text buffer to the specified length, as opposed to 
        * setting the length of the buffer to the length of the text passed in 
        * via <code>SetTextL()</code>.
        *
        * @param aLength The buffer reserve length
        * @remarks
        * @see
        */
        IMPORT_C void SetBufferReserveLengthL(TInt aLength);

        /**
        * Gets the buffer reserve length.
        *
        * @return the buffer reserve length
        * @remarks
        * @see
        */
        IMPORT_C TInt BufferReserveLength() const;

        /**
        * Sets the font of the Label.
        * Ownership of the font does not transfer to <code>CEikLabel</code>.
        *
        * @param aFont The Label's font
        * @remarks
        * @see CFont
        */
        IMPORT_C void SetFont(const CFont* aFont);

        /**
        * Gets the font of the Label.
        *
        * @return the font of the Label
        * @remarks
        * @see
        */
        inline const CFont* Font() const;

        /**
        * Sets the emphasis of the Label's text.
        *
        * @param aEmphasis The emphasis of the text 
        * @remarks
        * @see TTextEmphasis
        */
        IMPORT_C void SetEmphasis(TTextEmphasis aEmphasis);

        /**
        * Sets the gap between the text lines of the Label, in pixels.
        *
        * @param aGap The number of pixels between two lines of text
        * @remarks
        * @see
        */
        IMPORT_C void SetPixelGapBetweenLines(TInt aGap);

        /**
        * Gets the number of pixels between two lines of text.
        *
        * @return the number of pixels between two lines of text
        * @remarks
        * @see
        */
        IMPORT_C TInt PixelGapBetweenLines() const;

        /**
        * Determines whether the Label is underlined.
        *
        * @return <code>ETrue</code> if the Label is set as underlined; 
        *         <code>EFalse</code> if the Label is not set as underlined
        * @remarks This property can be set in the Label's resource via the 
        *          flag <code>EikLabelUnderline</code>
        * @see
        */
        inline TBool IsUnderlined() const;

        /**
        * Sets whether the Label is underlined.
        *
        * @param aUnderLining <code>ETrue</code> to set the Label as 
        *        underlined; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetUnderlining(TBool aUnderLining);

        /**
        * Determines whether the Label has the strike-through attribute.
        *
        * @return <code>ETrue</code> if the Label is set to be drawn
        *         with a line through it; <code>EFalse</code> otherwise
        * @remarks This property is set in the Label's resource via the 
        *          flag <code>EikLabelStrikeThrough</code>
        * @see
        */
        inline TBool IsStrikethrough() const;

        /**
        * Sets whether the Label has the strike-through attribute.
        *
        * @param aStrikethrough <code>ETrue</code> if the Label is set to be 
        *        drawn with a line through it; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetStrikethrough(TBool aStrikethrough);

        /**
        * Gets the minimum size required to draw the specified text.
        *
        * @param aText The text to be drawn
        * @return the minimum size required to draw the text
        * @remarks
        * @see
        */
        IMPORT_C TSize CalcMinimumSize(TPtrC& aText) const;

        /**
        * Gets the number of lines of text in the Label.
        *
        * @return the number of lines of text
        * @remarks This method takes into account wrapping and any
        *          line breaks marked by '\n'
        * @see
        */
        inline TUint8 NumberOfLines();

        /**
        * Specifies whether or not the Label should automatically wrap text.
        * 
        * @param aAutoWrapping <code>ETrue</code> if the Label should wrap;  
        *        <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetAutoWrapping(TBool aAutoWrapping);

        /**
        * Determines whether the Label automatically wraps.
        *
        * @return <code>ETrue</code> if the Label has the auto-wrapping flag 
        *         set
        * @remarks This property can be set in the Label's resource via the 
        *          flag <code>EikLabelAutoWrappingOn</code>
        * @see
        */
        inline TBool IsAutoWrapping() const;

        /**
        * Sets the wrapping width of the Label's text.
        * 
        * @param aWidth The width, in pixels
        * @remarks
        * @see
        */
        IMPORT_C void SetWrappingWidthL(TInt aWidth);

        /**
        * Sets the maximum number of lines that are displayed by the Label.
        * If there are more lines than are specified here, they are not 
        * displayed.
        * 
        * @param aMaxNumberOfLines The number of lines
        * @remarks
        * @see
        */
        IMPORT_C void SetNumberOfVisibleLines(TInt aMaxNumberOfLines);

        /**
        * Determines the maximum number of visible lines the Label can have.
        *
        * @return the maximum number of lines that can be displayed
        *         <b>Note</b>: This is not the same as the value set in 
        *         <code>SetNumberOfVisibleLines</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt MaxNumberOfLines() const;

        /**
        * Sets the height of each line and the baseline offset.
        * 
        * @param aLineHeight The height of each line of the text
        * @param aBaseline The offset at which the text is drawn
        * @remarks The baseline offset is the height from the top
        *          of the Label to the text's baseline, that is, the ascent
        * @see
        */
        IMPORT_C void SetLineHeightAndBaseline(TInt aLineHeight, TInt aBaseline);

        /**
        * Gets the height of each line and the baseline offset.
        * 
        * @param aLineHeight The height of each line of the text
        * @param aBaseline The offset at which the text is drawn
        * @remarks The baseline offset is the height from the top
        *          of the Label to the text's baseline, that is, the ascent
        * @see
        */
        IMPORT_C void GetLineHeightAndBaseline(TInt &aLineHeight, TInt &aBaseline) const;

        /**
        * Sets the special wrapping mode for Labels, so that the Label will
        * try to wrap its text to fit a specified width. Special wrapping does 
        * not wrap long words, but clips them. Setting the special wrapping to 
        * be on, turns off the alternative auto-wrapping feature.
        * 
        * @param aSpecialWrapping <code>ETrue</code> to set that the Label 
        *                         wraps its text; <code>EFalse</code> to set 
        *                         that the Label does not perform any wrapping
        * @remarks
        * @see
        */
        IMPORT_C void SetSpecialWrapping(TBool aSpecialWrapping);

        /**
        * Determines the special wrapping setting.
        *
        * @return <code>ETrue</code> if the Label uses special wrapping; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsSpecialWrapping() const;

        /**
        * Sets line breaks to be inserted after the first occurrence of a '?'. 
        * Special wrapping must be turned on first.
        *
        * @param aAutoLineBreaking <code>ETrue</code> to set insert line breaks
        * @remarks
        * @see
        */
        IMPORT_C void SetAutoLineBreaking(TBool aAutoLineBreaking);

        /**
        * Sets the maximum number of lines that a Label wraps to. If 
        * <code>aMaxLines</code> is set to zero, the Label wraps until the end of
        * the text.
        * 
        * @param aMaxLines The maximum number of lines
        * @remarks
        * @see
        */
        IMPORT_C void SetMaxWrappingLines(TInt aMaxLines);

        /**
        * Sets the colors used by the Label.
        * 
        * @param aLabelColors The brush and pen colors
        * @remarks
        * @see
        */
        IMPORT_C void SetColors(TEikLabelColors *aLabelColors);

        /**
        * Gets the colors used by the Label.
        * 
        * @return the brush and pen colors
        * @remarks
        * @see
        */
        IMPORT_C const TEikLabelColors* GetLabelColors() const;

        /**
        * Sets the observer of pointer events in a Label.
        * Allows controls to watch for pointer events in Labels.
        * 
        * @param aObserver The observer
        * @remarks
        * @see MCknLabelObserver
        */
        IMPORT_C void SetLabelObserver(MCknLabelObserver* aObserver);

        /**
        * Gets the observer of the Label.
        * Allows controls to watch for pointer events in Labels.
        *
        * @return the Label's observer
        * @remarks
        * @see MCknLabelObserver
        */
        IMPORT_C MCknLabelObserver* LabelObserver() const;

    public:
        /**
        * Sets the hotkey of the Label - only used if the Label is
        * part of a dialog button.
        *
        * @param aHotKeyCode The hotkey for the Label
        * @remarks
        * @see
        * @internal
        */
        void SetHotKeyCode(TInt aHotKeyCode);

    protected:
        /**
        * Writes the internal state of the control and its components to aStream.
        * Does nothing in release mode.
        * Designed to be overidden and base called by subclasses.
        *
        * @internal
        * @since App-Framework_6.1
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

        /**
        * @see CCoeControl
        */
        IMPORT_C void SizeChanged();

    private:
        IMPORT_C void Reserved_2();

    private: //** New functions *
        TInt HeightInPixels() const;
        TInt WidthInPixels(TPtrC& aText) const;
        void SetupGcForEmphasis(CGraphicsContext& aGc) const;
        void CheckCreateExtensionL();
        TInt WrapText(TInt aMaximumWidth);
        void RevertAnyWrappingChanges();
        void TryWrappingText();

        TBool OverrideSpecialWrapping() const;
        void TrySpecialWrapText();
        TInt SpecialWrapText(TInt aMaximumWidth);
        TBool TextContainsLineBreaks() const;
        TInt InsertLineBreaksInText();

    protected:
        /**
        * Determines whether text is drawn with underlining and strike-through.
        */
        enum TLabelFlags
            {
            EUnderlining                = 0x02,     /** Text is drawn with underlining. */
            EStrikethrough              = 0x04,     /** Text is drawn with strike-through. */
            ETextBufferReserveLength    = 0x08,
            // cannot use 10 and 20 since they are used by TTextEmphasis
            EAutoWrapping               = 0x40,
            ELineHeightIsFixed          = 0x80
            };

        enum TSpecialWrapFlags
            {
            ESpecialWrapping            =0x01,  /** Text is wrapped **/
            EAutoLineBreaking           =0x02,  /** Line Breaks are inserted after certain chars */
            };

        HBufC* iText;
        const CFont* iFont;
        TUint8 iNumberOfLines;
        TUint8 iLabFlags;
        TInt iGapBetweenLines;

    private:
        CEikLabelExtra* iExtra;
        TInt iHotKeyCode;
    };

inline const TDesC* CEikLabel::Text() const
    { return(iText); }

inline const CFont* CEikLabel::Font() const
    { return(iFont); }

inline TBool CEikLabel::IsUnderlined() const
    {return iLabFlags&EUnderlining;}

inline TBool CEikLabel::IsStrikethrough() const
    {return iLabFlags&EStrikethrough;}

inline TUint8 CEikLabel::NumberOfLines()
    {return iNumberOfLines;}

inline TBool CEikLabel::IsAutoWrapping() const
    {return iLabFlags&EAutoWrapping;}

#endif  //** EIKLABEL_H *

//** End of File *
