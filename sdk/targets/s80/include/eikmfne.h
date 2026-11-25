/*
* ==============================================================================
*  Name        : eikmfne.h
*  Part of     : CKON
*  Interface   : MFN Editor API
*  Description : Base classes for multi-field numeric editors.
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


#ifndef EIKMFNE_H
#define EIKMFNE_H

// INCLUDES
#include <eikbctrl.h>
#include <coedef.h>
#include <coeinput.h>
#include "EikUbgcb.h"
#include <Ckntimepicker.h>
#include <eikCal.h>

// CONSTANTS

/** 
 * The <code>TMfneEditorType</code> enumeration provides the MFNE editor types. 
 * It is not currently used anywhere. 
 */
enum TMfneEditorType
    {
    /** Time-editor */
    EMfneTimeEditor,
    /** Date-editor */
    EMfneDateEditor,
    /** Time-and-date-editor */
    EMfneTimeAndDateEditor,
    /** Time-offset-editor */
    EMfneTimeOffsetEditor,
    /** Duration-editor */
    EMfneDurationEditor,
    /** Range-editor */
    EMfneRangeEditor
    };

/** 
 * This anonymous enumeration provides compass directions used in 
 * <code>TEikCompass</code>. 
 */
enum
    {
    /** North-South */
    EEikOrientationNorthSouth   =0x1000,
    /** West-East */
    EEikOrientationWestEast     =0x2000,
    /** mask for these fields */
    EEikOrientationMask=EEikOrientationNorthSouth|EEikOrientationWestEast
    };


/** 
 * This anonymous enumeration provides the sign of direction used in 
 * <code>TEikCompass</code>. 
 */
enum
    {
    /** negative */
    EEikDirectionNegative,
    /** positive */
    EEikDirectionPositive,
    /** mask for these fields */
    EEikDirectionMask=EEikDirectionNegative|EEikDirectionPositive
    };


/** 
 * The <code>TEikCompass</code> enumeration provides compass directions used 
 * in Latitude- and Longitude-editors. 
 */
enum TEikCompass
    {
    /** North */
    EEikCompassNorth=EEikOrientationNorthSouth|EEikDirectionNegative,
    /** South */
    EEikCompassSouth=EEikOrientationNorthSouth|EEikDirectionPositive,
    /** East */
    EEikCompassEast=EEikOrientationWestEast|EEikDirectionNegative,
    /** West */
    EEikCompassWest=EEikOrientationWestEast|EEikDirectionPositive
    };

// DATA TYPES

/** 
 * The struct <code>SEikDegreesMinutesDirection</code> provides data for the 
 * Latitude- and Longitude-editors. 
 */
struct SEikDegreesMinutesDirection
    {
    /** degrees */
    TInt iDegrees;
    /** minutes */
    TInt iMinutes;
    /** seconds */
    TInt iSeconds;
    /** direction */
    TEikCompass iDirection;
    };

/** 
 * The struct <code>SEikDegreesMinutesDirection</code> provides data for the 
 * Range-editor. */
struct SEikRange
    {
    /** lower limit of range */
    TInt iLowerLimit;
    /** upper limit of range */
    TInt iUpperLimit;
    };

// FORWARD DECLARATIONS
class CEikonEnv;
class CTimeEditor;
class CDateEditor;
class CDurationWithDaysEditor;
class CCknTimePicker;
class CEikMfne;
class CEikCheckBox;
class CGulIcon;
class CEikMfneExtension;
class CCknMfneFepSupport;
class CEikDateEditorExtension;
class CEikTimeAndDateEditorExtension;
class CEikDurationEditorExtension;
class CEikMfneIconExtension;
class CEikMfneFieldExtension;

/**
*  The base class for individual components of a MFNE. For internal use only.
*
*  @internal
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikMfneField : public CBase
    {
    public:
        enum THighlightType
            {
            EInverseVideo,
            ECursor
            };
    protected:

        /**
        * Default constructor.
        */
        IMPORT_C CEikMfneField();

    public:

        IMPORT_C ~CEikMfneField();

        /**
        * Draw the field.
        * @param aGc The graphics context
        * @param aFont The font
        * @param aTopLeft The top left position of the field
        * @param aBrushColor The color of the brush
        */
        IMPORT_C virtual void Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft, const TRgb& aBrushColor) const;

        /**
        * Gets the width of the field, in pixels.
        *
        * @param aFont The font used
        * @return The width of the field in pixels
        */
        IMPORT_C virtual TInt WidthInPixels(const CFont& aFont) const;

        /**
        * The width of the text + margin.
        * @param aFont The font used
        * @return The width of the text + margin
        */
        IMPORT_C virtual TInt DistanceFromStartOfFieldToEndOfTextInPixels(const CFont& aFont) const;

        /**
        * Usually the width of the text + margins.
        * Must be implemeted by derived class.
        * @param aFont The font used
        * @param aShrinkToMinimumSize If <code>ETrue</code>, the returned
        * value will be the minimum size that the control can be while still
        * able to fully display it's contents.
        * @return The maximum width of the control in pixels
        */
        IMPORT_C virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize)=0;

        /**
        * Returns the input capabilities of the field. See CCoeControl.
        * @return The input capabilities
        */
        IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const=0;

        /**
        * Return whether the field is editable.
        * In this base class implementation this always returns
        * <code>EFalse</code>.
        * @return <code>ETrue</code> if the field is editable,
        * <code>EFalse</code> if not
        */
        IMPORT_C virtual TBool IsEditable() const;

        /**
        * Returns the highlight used in the field.
        * This default implementation panics in debug builds.
        * Used a derived class instead.
        * @return The highlight type used.
        * This base implementation returns EInverseVideo
        */
        IMPORT_C virtual THighlightType HighlightType() const;

        /**
        * Handle a key event.
        * This default implementation panics in debug builds.
        * Used a derived class instead.
        * @param aFont The font used
        * @param aKeyEvent The key event
        * @param aInterpretLeftAndRightAsEarEvents Ears are graphical elements
        * that allow sequential movement through a list. If <code>ETrue</code>
        * the field will interpret left and right arrow keys as ear events
        * @param aDataAltered If data is altered in this method call, this will
        * be set to <code>ETrue</code> on return. Otherwise it will retain its
        * initial value
        * @param aHighlightIncrement on return contains the number of fields
        * the highlight should move. Usually this is 0.
        * If the key was an arrow key and this was interpreted as an ear event,
        * it might be 1 or -1
        */
        IMPORT_C virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);

        /**
        * Called when the highlight is moved from the field.
        * @param aFont The font used
        * @param aEikonEnv The eikon environment
        * @param aDataAltered On return will be set to <code>ETrue</code> if
        * the data in the field was altered during the method call.
        * If not it retains its initial value.
        * @param aError On return is <code>ETrue</code> if the field could not
        * be validated. Otherwise retains it's initial value
        */
        IMPORT_C virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);

        /**
        * Handle a pointer event.
        * @param aPointerEvent The pointer event
        * @param aDataAltered On return will be set to <code>ETrue</code> if
        * the data in the field was altered during the method call.
        * If not it retains its initial value.
        */
        IMPORT_C virtual void HandlePointer(const TPointerEvent& aPointerEvent, TBool& aDataAltered);

        /**
        * Returns the size of the horizontal left margin.
        * @return The size of the horizontal left margin in pixels
        */
        IMPORT_C TInt HorizontalLeftMargin() const;

        /**
        * The setter for the horizontal left margin.
        * @param aLeftMargin The new size of the horizontal left margin
        * in pixels
        */
        IMPORT_C void SetHorizontalLeftMargin(TInt aLeftMargin);

        /**
        * Returns the size of the horizontal right margin.
        * @return The size of the horizontal right margin in pixels
        */
        IMPORT_C TInt HorizontalRightMargin() const;

        /**
        * The setter for the horizontal right margin.
        * @param aRightMargin The new size of the horizontal right margin
        * in pixels
        */
        IMPORT_C void SetHorizontalRightMargin(TInt aRightMargin);

        /**
        * Returns the total size of the margins in pixels.
        * @return left margin + right margin in pixels
        */
        IMPORT_C TInt Margins() const;

        /**
        * Returns true if the field is set to be underlined.
        * @return <code>ETrue</code> if the field is underlined,
        * <code>EFalse</code> if not
        */
        IMPORT_C TBool IsUnderlined() const;

        /**
        * Set whether the field should be underlined or not.
        * @param aState <code>ETrue</code> if the field is to be underlined,
        * <code>EFalse</code> if not
        */
        IMPORT_C void SetUnderlining(TBool aState);

        /**
        * Returns <code>ETrue</code> if the field is dimmed.
        * @return <code>ETrue</code> if the field is dimmed,
        * <code>EFalse</code> if it is not
        */
        IMPORT_C TBool IsDimmed() const;

        /**
        * Set whether the field is dimmed or not.
        * @param aState <code>ETrue</code> to dim the field,
        * <code>EFalse</code> to undim the field
        */
        IMPORT_C void SetDimmed(TBool aState);

        /**
        * Returns <code>ETrue</code> if the field is hidden.
        * @return <code>ETrue</code> if hidden; <code>EFalse</code> if visible
        */
        IMPORT_C TBool IsHidden() const;

        /**
        * Set the hidden flag of the field.
        * @param aState <code>ETrue</code> to hide the field,
        * <code>EFalse</code> to unhide
        */
        IMPORT_C void SetHidden(TBool aState);

        /**
        * Returns <code>ETrue</code> if the field is the current field.
        * @return <code>ETrue</code> if current field,
        * <code>EFalse</code> otherwise
        */
        IMPORT_C TBool IsCurrentField() const;

        /**
        * Set this field to be the current field.
        * @param aState <code>ETrue</code> if this is to be the current field,
        * <code>EFalse</code> if not.
        */
        IMPORT_C void SetAsCurrentField(TBool aState);

        /**
        * Set the owner of this field
        * @param aOwner The MFNE that owns this field
        */
        IMPORT_C void SetOwner(CEikMfne& aOwner);

        /**
        * Returns <code>ETrue</code> if this field is pressed
        * @return <code>ETrue</code> if the field is pressed,
        * <code>EFalse</code> otherwise
        */
        IMPORT_C TBool IsPressed() const;

        /**
        * Set whether this field is pressed.
        * @param aState The pressed state.
        */
        IMPORT_C void SetPressed(TBool aState);
    protected:

        /**
        * Called if a left or right arrow key was pressed.
        * @param aKey the key pressed
        * @param aDataAltered contains <code>ETrue</code> after the method call
        * if data was changed, otherwise retains its initial value
        * @param aHighlightIncrement On return, contains the number of fields
        * to move the highlight after this method call
        * This is usually 0, but may be -1 or 1. 
        */
        IMPORT_C void HandleLeftOrRightArrow(TChar aKey, TBool& aDataAltered, TInt& aHighlightIncrement);

        void ReportEventStateChanged() const;

        CEikMfne* Owner() const;

    private:
        virtual const TDesC& Text() const=0;
    protected:
        TInt iMinimumWidthInPixels;
    private:
        enum TMfneFieldFlags
            {
            ENoUnderlining  =0x01,
            EDimmed     =0x02,
            EHidden     =0x04,
            ECurrent    =0x08,
            EPressed    =0x10
            };
    private:
        TUint16 iFieldFlags;
        CEikMfneFieldExtension* iExt;               
    };

/**
* A MFNE field that contains some static characters.
* For internal use only.
* The field has an associated resource struct MFNE_SEPARATOR.
*
* @internal
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikMfneSeparator : public CEikMfneField
    {
    private:
        CEikMfneSeparator(HBufC* aText);
    public:

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikMfneSeparator();

        /**
        * Starts the two-phase object construction.
        * @param aResourceReader The resource reader from which to read the text
        */
        IMPORT_C static CEikMfneSeparator* NewL(TResourceReader& aResourceReader);

        /**
        * Starts the two-phase object construction.
        * @param aText the text to use. Ownership is transferred when
        * everything that can leave has successfully been done
        */
        IMPORT_C static CEikMfneSeparator* NewL(HBufC* aText);

        /**
        * Set the text.
        * This will panic if the text has previously been set.
        * @param aText The text to use
        * @panic <code>EEikPanicMfneSeparatorTextHasAlreadyBeenSet</code>
        * if the text has already been set
        */
        IMPORT_C void SetText(HBufC* aText); 
    private: // framework
        virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
        virtual TCoeInputCapabilities InputCapabilities() const;
        virtual const TDesC& Text() const;
    private:
        HBufC* iText;
    };

/**
* The <code>CEikMfneNumber</code> class is a MFNE field that can contain a 
* number between a minimum and maximum value.
* The field has an associated resource struct <code>MFNE_NUMBER</code>
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikMfneNumber : public CEikMfneField
    {
    public:
        /** 
         * This anonymous enumeration provides the allowed flags for this MFNE.
         */
        enum
            {
            /** pad the start of number with zeros */
            EFillWithLeadingZeros          =0x1,
            /** the minimum width is preserved */
            EPreserveOldWidthBeforeEditing =0x2,
            /** the number taken to be the nearest year, for example, 5 means 2005 */
            ERepresentsYear                =0x4,
            /** the mask for these fields */
            EPublicallySettableFlags       =EFillWithLeadingZeros
                                           |EPreserveOldWidthBeforeEditing
                                           |ERepresentsYear
            };
    private:
        enum
            {
            EIsBeingEditedWithCursor    =0x8
            };
    private:
        CEikMfneNumber(TInt aMinimumValue, TInt aMaximumValue, TUint32 aFlags);
        void ConstructL();
    public:

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikMfneNumber();

        /**
        * Starts the two-phase object construction.
        *
        * @param aFont The font to use
        * @param aResourceReader The resource reader to use
        * @return a pointer to a newly created <code>CEikMfneNumber</code>
        * @panic <code>EEikPanicMfneBadNumberMinimumAndMaximum1</code> if 
        *        the minimum value is greater than maximum value.
        * @panic <code>EEikPanicMfneBadNumberFlags</code> if any flags are 
        *        invalid
        * @see
        */
        IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TResourceReader& aResourceReader);

        /**
        * Starts the two-phase object construction.
        *
        * @param aFont The font to use
        * @param aMinimumValue The minimum allowable value
        * @param aMaximumValue The maximum allowable value
        * @param aInitialValue The initial value. Must be between 
        *        <code>aMinimumValue</code> and <code>aMaximumValue</code>
        * @param aFlags The flags for the MFNE. Must be one of 
        *        those listed in this class's anonymous enumeration
        * @return a pointer to a newly created <code>CEikMfneNumber</code>
        * @panic <code>EEikPanicMfneBadNumberMinimumAndMaximum1</code> if the 
        *        minimum value is greater than the maximum value.
        * @panic <code>EEikPanicMfneBadNumberFlags</code> if any flags are
        *        invalid.
        * @panic <code>EEikPanicMfneInconsistentNumberFlags</code> if the 
        *        number flags are inconsistent.
        * @panic <code>EEikPanicMfneBadNumberMinimumAndMaximum2</code> if the 
        *        initial value is outside the minimum-maximum range
        * @see
        */
        IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue, TUint32 aFlags);

        /**
        * Sets the minimum and maximum allowable values.
        *
        * @param aMinimumValue The new minimum allowable value
        * @param aMaximumValue The new maximum allowable value
        * @param aFont The font to use
        * @panic <code>EEikPanicMfneBadNumberMinimumAndMaximum3</code> if the 
        *        minimum value is greater than or equal to the maximum value,
        *        or if either value will not fit in the text field
        * @see
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue, const CFont& aFont); 

        /**
        * Gets the current minimum and maximum allowable values.
        *
        * @param aMinimumValue On return, contains the minimum
        * allowable value
        * @param aMaximumValue On return, contains the maximum
        * allowable value
        * @remarks
        * @see
        */
        IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;

        /**
        * Sets the current value stored in the MFNE.
        *
        * @param aValue The new value
        * @param aFont The font to use
        * @remarks
        * @see
        */
        IMPORT_C void SetValue(TInt aValue, const CFont& aFont);

        /**
        * Returns the current value stored in the MFNE.
        *
        * @return the current value
        * @remarks
        * @see
        */
        IMPORT_C TInt Value() const;

        /**
        * Checks if the current value is valid against the minimum and maximum
        * constraints.
        *
        * @return <code>ETrue</code> if the current value is valid, 
        *   <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Gets the width of the field, in pixels.
        *
        * @param aFont The font used
        * @return the width of the field, in pixels
        * @remarks
        * @see
        */
        TInt WidthInPixels(const CFont& aFont) const;

        /** @internal */
        void SetInitialValue(TInt aValue);
        /** @internal */
        const TBool IsTextNull() const;
        /** @internal */
        void SetEditingWithCursor(TBool aEditing);
        /** @internal */
        void SetInlineText(const TDesC& aText);
        /** @internal */
        void CommitInlineText();
    private: // framework
        virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
        virtual TCoeInputCapabilities InputCapabilities() const;
        virtual TBool IsEditable() const;
        virtual THighlightType HighlightType() const;
        virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
        virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
        virtual const TDesC& Text() const;
    public:

        /** @internal */
        void GetContent(TDes& aContent, TInt aStartPos, TInt aLength) const;
        /** @internal */
        TInt MaximumNumberOfDigits() const;
        /** @internal */
        TInt NumberOfDigits() const;
        /** @internal */
        void SetValueAndInitial(TInt aValue, const CFont& aFont);
    private:
        void SetTextToValue(TInt aValue, const CFont& aFont);
        TInt ValueFromText() const;
        TBool ConvertsIntoValidValue(TInt& aValue) const;
        void ResetToInitialValue(const CFont& aFont, CEikonEnv& aEikonEnv);
    private:
        TInt iMinimumValue;
        TInt iMaximumValue;
        TInt iInitialValue;
        TInt iMaxDigits;
        TUint32 iFlags;
        HBufC* iText;
        TChar iNudgeCharMinus;
        TChar iNudgeCharPlus;
        HBufC* iInlineText;
    };

/**
* The <code>CEikMfneSymbol</code> class provides a MFNE field that contains a 
* set of symbols, one of which is selected at any one time. A symbol is a 
* tuple of ID, text, and selecting key. The text of the currently selected 
* symbol is displayed in the field. A particular symbol may be selected when 
* the field is highlighted by pressing the associated key. The field has an 
* associated resource struct <code>MFNE_SYMBOL</code>.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikMfneSymbol : public CEikMfneField
    {
    public:
        /**
        *  The <code>CItem</code> is a utility class for holding the 
        *  symbol tuples.
        *
        *  @lib eikctl.lib
        *  @since Series90 1.0
        */
        class CItem : public CBase
            {
            private:
                CItem(TInt aId, TChar aKeyToMatch, HBufC* aText);
            public:
    
                /**
                * The object destructor.
                */
                IMPORT_C virtual ~CItem();
    
                /**
                * Starts the two-phase object construction.
                *
                * @param aResourceReader The resource reader to use
                * @return a pointer to a newly allocated <code>CItem</code>
                * @remarks
                * @see
                */
                IMPORT_C static CItem* NewL(TResourceReader& aResourceReader);
        
                /**
                * Starts the two-phase object construction.
                *
                * @param aId The item ID
                * @param aKeyToMatch The character to match
                * @param aText The text. Ownership is taken when everything 
                *              that can leave has completed
                * @return a pointer to a newly allocated <code>CItem</code>
                * @remarks
                * @see
                */
                IMPORT_C static CItem* NewL(TInt aId, TChar aKeyToMatch, HBufC* aText); 
            
                /**
                * Sets the text of the item. This method can only be called if 
                * the item's text field was previously <code>NULL</code>.
                *
                * @param aText The text. Ownership is taken when 
                *              everything that can leave has completed
                * @panic <code>EEikPanicMfneSymbolicItemTextHasAlreadyBeenSet</code>
                *        if the text has already been set
                * @see
                */
                IMPORT_C void SetText(HBufC* aText); 
            private:
                friend class CEikMfneSymbol;
            private:
                TInt iId;
                TCharF iKeyToMatch;
                HBufC* iText;
            };
    private:
        CEikMfneSymbol(TInt aNumSymbolicItems);
    public:

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikMfneSymbol();

        /**
        * Starts the two-phase object construction.
        *
        * @param aResourceReader The resource reader to use
        * @return a reference to a newly allocated <code>CEikMfneSymbol</code>
        * @panic <code>EEikPanicMfneTooFewSymbolicItems</code> if there are 
        *        fewer than one symbols
        * @see
        */
        IMPORT_C static CEikMfneSymbol* NewL(TResourceReader& aResourceReader);

        /**
        * Starts the two-phase object construction.
        *
        * @param aNumSymbolicItems The number of symbolic items
        * @return a reference to a newly allocated <code>CEikMfneSymbol</code>
        * @panic <code>EEikPanicMfneTooFewSymbolicItems</code> if there are 
        *        fewer than one symbols
        * @see
        */
        IMPORT_C static CEikMfneSymbol* NewL(TInt aNumSymbolicItems);

        /**
        * Adds a symbolic item. This method is only to be called if not 
        * constructed from resource.
        *
        * @param aSymbolicItem The item to add. Ownership is taken
        * @param aMakeCurrent <code>ETrue</code> to make the item current; 
        *  <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void AddSymbolicItem(CItem* aSymbolicItem, TBool aMakeCurrent); 

        /**
        * Set the current item to the symbol with the supplied ID.
        * 
        * @param aId The ID of the symbol to make current
        * @remarks
        * @see
        */
        IMPORT_C void SetCurrentSymbolicItemToId(TInt aId);

        /**
        * Get the ID of the currently selected symbol.
        *
        * @return the ID of the current symbol
        * @remarks
        * @see
        */
        IMPORT_C TInt IdOfCurrentSymbolicItem() const;

    private: // framework
        virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
        virtual TCoeInputCapabilities InputCapabilities() const;
        virtual TBool IsEditable() const;
        virtual THighlightType HighlightType() const;
        virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
        virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
        virtual void HandlePointer(const TPointerEvent& aPointerEvent, TBool& aDataAltered);
        virtual const TDesC& Text() const;
    private:
        TInt iNumSymbolicItems;
        TInt iCurrentSymbolicItem;
        CItem** iSymbolicItems;
    };


/**
*  A <code>CEikMfneIcon</code> is a <code>CEikMfneField</code> that contains a 
*  <code>CGulIcon</code>.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikMfneIcon : public CEikMfneField
    {
    public:

        /**
        * Starts the two-phase object construction.
        *
        * @param aIcon The icon to use. Takes ownership
        * @param aIconDim The icon to use if the field is dimmed. Takes 
        *        ownership
        * @param aIconPressed The icon to use if the field is pressed. Takes
        *        ownership
        * @return a reference to a newly allocated <code>CEikMfneIcon</code> 
        *         object
        * @remarks
        * @see
        */
        IMPORT_C static CEikMfneIcon* NewL(CGulIcon* aIcon, CGulIcon* aIconDim, CGulIcon* aIconPressed);

        /**
        * Draws the field.
        *
        * @param aGc A graphics context
        * @param aFont A font to use
        * @param aTopLeft The top left position of the field
        * @param aBrushColor The brush color to use
        * @remarks
        * @see CEikMfneField
        */
        virtual void Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft, const TRgb& aBrushColor) const;

        /**
        * Gets the width of the icon field, including the margins, in pixels.
        *
        * @param aFont The font to use
        * @return the combined width of the icon and the margins
        * @remarks
        * @see CEikMfneField
        */
        virtual TInt WidthInPixels(const CFont& aFont) const;

        /**
        * Calculate the distance from the start of the 
        * <code>CEikMfneIcon</code> object to the end of the field text. 
        * Because there is never any text in the field, this method simply
        * returns the width of the field.
        *
        * @param aFont The font used. Parameter passed to 
        *              <code>WidthInPixels</code>
        * @return the width of the field, in pixels
        * @remarks This just calls <code>WidthInPixels(aFont)</code>
        * @see CEikMfne::DistanceFromStartOfFieldToEndOfTextInPixels
        */
        virtual TInt DistanceFromStartOfFieldToEndOfTextInPixels(const CFont& aFont) const;

        /**
        * Calculates the maximum width of a <code>CEikMfneIcon</code> object.
        *
        * @param aFont Reference to a font
        * @param aShrinkToMinimumSize <code>ETrue</code> if the width
        *        should be shrunk to the minimum size; <code>EFalse</code> 
        *        otherwise. <b>Note</b>: This parameter is not used. It only 
        *        exists to maintain compatibility with the base class
        * @return the maximum width of the field, in pixels
        * @remarks
        * @see CEikMfneField
        */
        virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);

    protected:

        /**
        * Default constructor.
        * @param aIcon The icon to use. Takes ownership
        * @param aIconDim The icon to use if the field is dimmed. Takes ownership
        * @param aIconPressed The icon to use if the field is pressed.
        * Takes ownership
        */
        IMPORT_C CEikMfneIcon(CGulIcon* aIcon, CGulIcon* aIconDim, CGulIcon* aIconPressed);

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CEikMfneIcon();
    private:
        virtual const TDesC& Text() const;
        virtual TCoeInputCapabilities InputCapabilities() const;
    private:
        CGulIcon* iIcon;
        CGulIcon* iIconDim;
        CGulIcon* iIconPressed;
        TBuf<2> iDummy;
    public:
        /** @deprecated */
        IMPORT_C static CEikMfneIcon* NewL(TInt aBitmapId, TInt aBitmapMaskId=-1);
    protected:

        /**
        * Default constructor.
        * @deprecated
        */
        IMPORT_C CEikMfneIcon(CGulIcon* aIcon);
    };

/// 

/**
*  A <code>CEikMfneCheckBox</code> is a <code>CEikMfneField</code> that 
*  contains a <code>CEikCheckBox</code>.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikMfneCheckBox : public CEikMfneField
    {
    public:

        /**
        * Starts the two-phase object construction.
        *
        * @param aOwner The MFNE that will own this field
        * @return a pointer to a newly allocated <code>CEikMfneCheckBox</code>
        * @remarks
        * @see
        */
        IMPORT_C static CEikMfneCheckBox* NewL(CEikMfne& aOwner);

        /**
        * Completes construction of a <code>CEikMfneCheckBox</code> object.
        */
        IMPORT_C void ConstructL();

        /**
        * The default object constructor.
        *
        * @param aOwner The MFNE that will own this field
        * @remarks
        * @see
        */
        IMPORT_C CEikMfneCheckBox(CEikMfne& aOwner);

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikMfneCheckBox();

        /**
        * Get a pointer to the checkbox control.
        *
        * @return a pointer to the checkbox control
        * @remarks
        * @see
        */
        IMPORT_C CEikCheckBox* CheckBox() const;

        /**
        * Sets the position of the checkbox control. The size is always
        * set to the minimum size of the checkbox.
        *
        * @param aTopLeft The top left position of the checkbox
        * @remarks
        * @see
        */
        IMPORT_C void SetSizeAndPosition(const TPoint& aTopLeft);

        /**
        * Sets the checkbox container window and activates the checkbox 
        * control.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ActivateL();

        /**
        * Gets the maximum width of the control, in pixels.
        *
        * @param aFont A <code>CFont</code> reference. Not used
        * @param aShrinkToMinimumSize Not used
        * @return the width of the control, including margins
        * @remarks
        * @see CEikMfneField
        */
        virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);

        /**
        * The method for calculating the width of a 
        * <code>CEikMfneCheckBox</code> object, including margins.
        *
        * @param aFont A font pointer. Not used
        * @return the width of the field
        * @remarks
        * @see
        */
        virtual TInt WidthInPixels(const CFont& aFont) const;

        /**
        * Draws the field.
        *
        * @param aGc A graphics context
        * @param aFont A font. Not used
        * @param aTopLeft The top left position
        * @param aBrushColor The brush color
        * @remarks
        * @see CEikMfneField
        */
        virtual void Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft, const TRgb& aBrushColor) const;

    private:
        virtual TBool IsEditable() const;
        virtual THighlightType HighlightType() const;
        virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
        virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
        virtual const TDesC& Text() const;
        virtual TCoeInputCapabilities InputCapabilities() const;
    private:
        CEikCheckBox* iCheckBox;
        TBuf<4> iDummy;

    };

/**
* The <code>CEikMfne</code> class is the base class for Multifield Numeric
* Editor controls. All MFNE controls are derived from this class. 
* Derived classes should provide: <code>ConstructL()</code> - to 
* initialize a MFNE control; <code>ConstructFromResourceL()</code>
* - to initialize an MFNE control from a
* resource; A data member to store the editor's value; Methods
* to set and get the editor's value; Methods to set the minimum
* and maximum allowable values
* Derived classes can also override the following virtual methods:
* <code>OfferKeyEventL()</code> - to provide key event processing;
* <code>PrepareForFocusLossL()</code> - to provide validity checking for the 
* whole control; <code>MinimumSize()</code> - to calculate the minimum control 
* size; <code>FocusChanged()</code> - to handle changes in focus; 
* <code>FieldIsAboutToBeDeHighlighted()</code> - to provide validity checking 
* of individual fields
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikMfne : public CEikBorderedControl, public MCoeControlObserver
    {
    friend class CEikMfneField;
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikMfne();

        /**
        * The object destructor
        */
        IMPORT_C virtual ~CEikMfne();

        /**
        * Constructs a field array with <code>aNumFields</code> fields.
        * To be called only if not constructed from resource.
        *
        * @param aNumFields The number of fields in the MFNE
        * @remarks
        * @see
        */
        IMPORT_C void CreateFieldArrayL(TInt aNumFields); 

        /**
        * Adds a field. This method should only be called by the container if 
        * a derived control is not constructed from a resource.
        *
        * @param aField The field to be added. Takes ownership
        * @remarks
        * @see
        */
        IMPORT_C void AddField(CEikMfneField* aField); 

        /**
        * Get the number of fields that have been added so far. Must be less
        * than the <code>aNumFields</code> used in 
        * <code>CreateFieldArrayL</code>.
        *
        * @return the number of fields currently held in the field array
        * @remarks This method can be used in conjunction with 
        *          <code>AddField</code> to determine the index of the last 
        *          field added
        * @see
        */
        IMPORT_C TInt CurrentFieldTotal();

        /**
        * Gets the control's border margins.
        *
        * @return the margins of the border
        * @remarks
        * @see
        */
        IMPORT_C TMargins BorderMargins() const;

        /**
        * Draws immediately, and then leaves with a formatted time/date info
        * message. 
        *
        * @param aResourceId The resource ID of the format string to use for
        *                    the infoprint
        * @param aTimeDate The time and date
        * @remarks This is called as part of the validation done by the 
        *          framework when focus is changed. This method should not be
        *          TRAPped
        * @see
        */
        IMPORT_C void DrawNowAndLeaveWithTimeDateFormatInfoMsgL(TInt aResourceId, const TTime& aTimeDate) const;

        /**
        * Gets the <code>CEikMfneField</code> that was added at a particular 
        * index.
        *
        * @param aField The field index
        * @return pointer to the associated <code>CEikMfneField</code>, or 
        *         <code>NULL</code> if the index is less than zero or greater 
        *         than the number of fields
        * @remarks
        * @see
        */
        IMPORT_C CEikMfneField* Field(TInt aField) const;
        
        /**
        * Gets the state of the checkbox.
        * @internal
        * @deprecated
        * @return the checkbox state.
        * @panic <code>EEikPanicMfneHasNoCheckBoxField</code> if there is no 
        *        checkbox in the MFNE
        */
        IMPORT_C CEikButtonBase::TState CheckBoxState() const;

        /**
        * Sets the checkbox state.
        * @internal
        * @deprecated
        * @param aState The checkbox state
        * @panic EEikPanicMfneHasNoCheckBoxField if there is no checkbox
        * in the MFNE
        */
        IMPORT_C void SetCheckBoxState(CEikButtonBase::TState aState);

        /**
        * True if the MFNE has a checkbox field.
        * @deprecated
        * @internal
        * @return <code>ETrue</code> if the MFNE has a checkbox field,
        * <code>EFalse</code> otherwise
        */
        IMPORT_C TBool HasCheckBox() const;

        /**
        * Add a checkbox field.
        * @internal
        * @deprecated
        */
        IMPORT_C void AddCheckBoxL();

        /**
        * Redraws the MFNE control and displays an infoprint informing the
        * user that the maximum/minimum times have been exceeded.
        * @internal
        * @param aResourceId The ID of the string resource to use for
        * the infoprint
        * @param aTime The max/min values in seconds
        */
        IMPORT_C void DrawNowAndLeaveWithTimeDateFormatInfoMsgL(TInt aResourceId, const TTimeIntervalSeconds& aTime) const;
    public:

        /**
        * Read a time from a resource, returning a <code>TTime</code>.
        *
        * @param aResourceReader The resource reader
        * @return a <code>TTime</code> object with the time-related fields
        *         initialized from the resource
        * @remarks
        * @see
        */
        IMPORT_C static TTime ReadTime(TResourceReader& aResourceReader);

        /**
        * Read a date from a resource, returning a <code>TTime</code>.
        *
        * @param aResourceReader The resource reader
        * @return a <code>TTime</code> object with the date-related fields
        *         initialized from the resource
        * @remarks
        * @see
        */
        IMPORT_C static TTime ReadDate(TResourceReader& aResourceReader);

        /**
        * Read a time and date from a resource, returning a <code>TTime</code>.
        *
        * @param aResourceReader The resource reader
        * @return an object containing the time and date specified in the 
        *         resource
        * @remarks
        * @see
        */
        IMPORT_C static TTime ReadTimeAndDate(TResourceReader& aResourceReader);

        /**
        * Read a time interval from a resource, returning
        * a <code>TTimeIntervalSeconds</code>.
        *
        * @param aResourceReader The resource reader
        * @return a <code>TTimeIntervalSeconds</code> with the specified
        *         time interval
        * @panic <code>EEikPanicMfneNegativeDuration</code> if the duration
        *        is negative
        * @see
        */
        IMPORT_C static TTimeIntervalSeconds ReadDuration(TResourceReader& aResourceReader);

        /**
        * Read a time offset from a resource, returning a 
        * <code>TTimeIntervalSeconds</code>.
        *
        * @param aResourceReader The resource reader
        * @return a <code>TTimeIntervalSeconds</code> with the specified time
        *         offset
        * @remarks
        * @see
        */
        IMPORT_C static TTimeIntervalSeconds ReadTimeOffset(TResourceReader& aResourceReader);

        /**
        * Convert a <code>TTime</code> to a <code>TTimeIntervalSeconds</code>,
        * calculating the number of seconds from the days, hours, minutes, and
        * seconds of the <code>TTime</code>.
        *
        * @param aTime The time to convert from
        * @return a <code>TTimeIntervalSeconds</code> with the specified time
        * @remarks
        * @see
        */
        IMPORT_C static TTimeIntervalSeconds Convert(const TTime& aTime);

        /**
        * Convert a <code>TTimeIntervalSeconds</code> to a <code>TTime</code>,
        * calculating the number of hours, minutes, and seconds from the number
        * of seconds of the <code>TTimeIntervalSeconds</code>. The time part is
        * the valid part. The date fields are initialized to (<code>0</code>, 
        * <code>EJanuary</code>, <code>0</code>).
        *
        * @param aTimeIntervalSeconds The time interval to convert from
        * @return a <code>TTime</code> with the specified time
        * @remarks
        * @see
        */
        IMPORT_C static TTime Convert(const TTimeIntervalSeconds& aTimeIntervalSeconds);

        /**
        * If true, the MFNE will not report cursor change events.
        * @internal
        * @param aDisable <code>ETrue</code> if it is to be disabled.
        */
        IMPORT_C void DisableCursorChangeEvent(TBool aDisable);

        /**
        * Gets the current field.
        *
        * @return the current field
        * @remarks
        * @see
        */
        inline TInt CurrentField() const;

        /**
        * Returns the number of fields.
        * @internal
        * @return The number of fields in the MFNE.
        */
        inline TInt NumFields() const;

        /**
        * Sets the current field.
        * @internal
        * @param aIndex The new current field
        */
        IMPORT_C void SetCurrentField(TInt aIndex);
    public: // from CCoeControl

        /**
        * Called on a key event.
        *
        * @param aKeyEvent The key event
        * @param aType The event type
        * @return indicates whether or not the key event was used by this 
        *         control
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * Called before focus is removed.
        *
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C virtual void PrepareForFocusLossL();

        /**
        * The minimum size of the control.
        *
        * @return the minimum size
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TSize MinimumSize();

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; 

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        *
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

        /**
        * Returns the input capabilities of the control. Typically, called by 
        * the FEP-aware text editor. By default, the control is capable of 
        * handling all text input.
        *
        * @return the input capabilities
        * @remarks <code>TCoeInputCapabilities</code> is defined in coeinput.h
        * @see CCoeControl
        */
        IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;

        /**
        * Called when the control size changes.
        *
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void SizeChanged();

        /**
        * Activate the control.
        *
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();
    public: // from MCoeControlObserver

        /**
        * Handle a control event.
        *
        * @param aControl The control that sent the event
        * @param aEventType The event type
        * @remarks
        * @see MCoeControlObserver
        */
        IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

        /** @internal */
        MCoeFepAwareTextEditor* FepSupport() const;
        /** @internal */
        TBool IsInlineEditing() const;
        /** @internal */
        void StartFepInlineEditL(const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, TInt& aNumCharsInserted);
        /** @internal */
        void UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt aPositionOfInsertionPointInInlineText, TInt& aNumCharsInserted);
        /** @internal */
        void DoCommitFepInlineEditL();
        /** @internal */
        void CancelFepInlineEdit();
        /** @internal */
        void SetGcToInlineEditingVideo(CWindowGc& aGc) const;
        /** @internal */
        TInt FieldLength();
        /** @internal */
        TInt MaximumFieldLength();
        /** @internal */
        void GetEditorContent(TDes& aEditorContent,TInt aDocumentPosition,TInt aLengthToRetrieve);
        /** @internal */
        TBool IsCursorChangeDisabled() const;
    protected:

        /**
        * The base constructor.
        * Derived classes must call this in their ConstructL.
        */
        IMPORT_C void BaseConstructL();

        /**
        * Called when the focus is changed. See CCoeControl.
        * @param aDrawNow A value of EDrawNow causes the editor to be redrawn.
        */
        IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

        /**
        * Handles interaction events.
        * Events resulting from user interaction are handled similarly, but
        * the interaction is passed to the MFNE (for example, through pointer events,
        * key events, or focus loss). This is a utility method which performs
        * the event handling common to all these types of input.
        * 
        * @param aHandleDeHighlight Handle de-highlighting
        * @param aNewCurrentField the index of the new current field
        * @param aOldWidthInPixelsOfOldCurrentField 
        * @param aOldHighlightTypeOfOldCurrentField 
        * @param aDataAltered on return, <code>ETrue</code> if data was altered
        *        during the method call
        * @param aError on return, <code>ETrue</code> if there was an error
        *        during the method call.
        */
        IMPORT_C void HandleInteraction(TBool aHandleDeHighlight, TInt aNewCurrentField, TInt aOldWidthInPixelsOfOldCurrentField, CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, TBool& aDataAltered, TBool& aError);

        /**
        * Field validity checking.
        * This method is called when an attempt is made to move from one
        * field to another. It may be provided in a derived class if field
        * validity checking is required. For example, the Range-editor provides
        * an implementation which resets the upper field value to the same as
        * the lower field value if an attempt is made to move away from the
        * lower field when its value is greater than that of the upper field.
        *
        * This class has an empty implementation for this method.
        * @param aField The field which is about to be dehighlighted
        * @param aDrawAllFields If set to <code>ETrue</code> on return, indicates that all fields need to be redrawn
        */
        IMPORT_C virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields); 

        /**
        * Gets the normal size of the MFNE.
        * @return The size of the MFNE
        */
        IMPORT_C TSize MfneSize() const;

        /**
        * Gets the normal or minimum size of the MFNE.
        * @param aShrinkToMinimumSize <code>ETrue</code> gets the minimum size of the MFNE.
        * @return The size of the MFNE
        */
        IMPORT_C TSize MfneSize(TBool aShrinkToMinimumSize);

        TBool HandleCheckBoxEventL(const TPointerEvent& aPointerEvent, const CFont& aFont);
        void GetAndHighlightField(TInt& aNewField, const TPointerEvent& aPointerEvent, const CFont& aFont);
        TBool PointerOverIconL(const TPointerEvent& aPointerEvent, const CFont& aFont);
        void CheckCurrentField();
        TRect CalcBorderRect() const;
        void DetermineCheckBoxGapL();
        void SendCursorChangeEventIfRequired();
        void SendEventToFepIfRequired(TPointerEvent::TType aType);
        TBool FieldError();
        void ClearFieldError();

        /**
        * Gets the bitfield that holds the MFNE flags.
        * @internal
        * @return The flags bitfield.
        */
        TUint32& FlagsL();

        /**
        * Gets the bitfield that holds the MFNE flags.
        * @internal
        * @return The flags bitfield.
        */
        TUint32 Flags() const;

        /**
        * Return the index of the field that is currently being edited.
        * @internal
        * @return The index of the currently edited field. A reference to iInlineEditField.
        */
        TInt& InlineEditFieldL();

        /**
        * Return the index of the field that is currently being edited.
        * @internal
        * @return The index of the currently edited field. 
        */
        TInt InlineEditField() const;

        /**
        * Draw a field now.
        * @internal
        * @param aField The index of the field
        */
        IMPORT_C void DrawFieldNow(TInt aField) const;

        IMPORT_C virtual void Draw(const TRect& aRect) const;

    private:
        IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        IMPORT_C virtual void CreatePopoutIfRequiredL();
        void DrawRange(CWindowGc& aGc, TInt aFirstField, TInt aLastField) const;
        void DrawInlineEditFieldNow() const;
        CWindowGc& PreparedGc() const;
        void SetGcToNormalVideo(CWindowGc& aGc) const;
        void SetGcToInverseVideo(CWindowGc& aGc) const;
        void SetGcToDimmedVideo(CWindowGc& aGc) const;
        void DrawCursor();
        void HideCursor();
    private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();

    private:
        enum {ENullIndex=KMaxTInt};
    private:
        TInt iNumFields;
        TInt iCurrentField;
        CEikMfneField** iFields;
        CEikMfneExtension* iBaseExt; 
    };

inline TInt CEikMfne::CurrentField() const
    {
        return iCurrentField;
    }

inline TInt CEikMfne::NumFields() const
    {
        return iNumFields;
    }

/**
* The <code>CEikNumberEditor</code> class provides a Number-editor. 
* This control is used to edit a single integer value. If a number is entered
* that is not within the range specified by the maximum and minimum control 
* values, it is automatically reset to the nearest allowable value.
* The editor has an associated resource struct <code>NUMBER_EDITOR</code> and
* control factory identifier <code>EEikCtNumberEditor</code>.
* This class is not intended for developer derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikNumberEditor : public CEikMfne
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikNumberEditor();

        /**
        * Completes construction of a <code>CEikNumberEditor</code> object.
        * To be called only if not constructed from resource.
        *
        * @param aMinimumValue The minimum allowable value
        * @param aMaximumValue The maximum allowable value
        * @param aInitialValue The initial value
        * @remarks
        * @see CEikMfne
        */
        IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue); 

        /**
        * Sets the minimum and maximum allowable values.
        *
        * @param aMinimumValue The minimum allowable value
        * @param aMaximumValue The maximum allowable value
        * @remarks
        * @see CEikMfne
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); 

        /**
        * Gets the minimum and maximum allowable values.
        *
        * @param aMinimumValue On return, holds the minimum allowable value
        * @param aMaximumValue On return, holds the maximum allowable value
        * @remarks
        * @see CEikMfne
        */
        IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;

        /**
        * Sets the Number-editor's initial value. If validation is attempted
        * when the field is empty, this value is restored to the control.
        *
        * @param aValue The initial value. Must be between
        *               <code>iMinimumValue</code> and <code>iMaximumValue</code>
        * @remarks
        * @see CEikMfne
        */
        IMPORT_C void SetInitialValue(TInt aValue);

        /**
        * Sets the Number-editor's current value.
        *
        * @param aNumber The new current value
        * @remarks
        * @see
        */
        IMPORT_C void SetNumber(TInt aNumber);

        /**
        * Checks the validity of the current value against the minimum and
        * maximum constraints.
        *
        * @return <code>ETrue</code> if the entry is valid; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Gets the current integer value stored in the editor. This method
        * can only be called if <code>PrepareForFocusLossL()</code> succeeded.
        *
        * @return the current value stored in the Number-editor
        * @remarks
        * @see
        */
        IMPORT_C TInt Number() const; 

        /**
        * Constructs a Number-editor from a resource file.
        *
        * @param aResourceReader The resource reader
        * @remarks The resource type is <code>NUMBER_EDITOR</code>
        * @see
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
    private:
        void Draw(const TRect& aRect) const;
    private:
        CEikMfneNumber* iNumber;
    };

/**
* The <code>CEikRangeEditor</code> class provides a Range-editor. 
* This numeric editor is used to edit a range of integers. It has two fields,
* the first represents the lower value and the second represents the upper value. The 
* second value must be greater than, or equal to, the first. 
* Maximum and minimum values for the editor are specified during construction. 
* If a number that is not within the range specified by the editor's maximum
* and minimum values is entered, it is automatically reset to the nearest
* allowable value.
* The editor has an associated resource struct <code>RANGE_EDITOR</code> and
* control factory identifier <code>EEikCtRangeEditor</code>.
* This class is not intended for developer derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikRangeEditor : public CEikMfne
    {
    public:

        /**
        * Default constructor.
        */
        IMPORT_C CEikRangeEditor();

        /**
        * Completes construction of a newly allocated Range-editor by setting 
        * the minimum and maximum allowable values, initial 
        * range, and separator text. This method should only be called by the container
        * if the control is not constructed from a resource file.
        * If the initial range values are outside the bounds specified by the 
        * minimum and maximum, they are changed to the nearest valid settings.
        *
        * @param aMinimumValue The minimum allowable value
        * @param aMaximumValue The maximum allowable value
        * @param aInitialRange The initial range
        * @param aSeparatorText The separator character to use. Ownership is
        *        taken when everything that can leave has successfully 
        *        completed
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, const SEikRange& aInitialRange, HBufC* aSeparatorText);

        /**
        * Sets the Range-editor's minimum and maximum allowable values. 
        * These define the maximum and minimum values that the user can enter.
        *
        * @param aMinimumValue The minimum allowable value
        * @param aMaximumValue The maximum allowable value
        * @remarks
        * @see
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue);

        /**
        * Gets the Range-editor's minimum and maximum allowable values.
        *
        * @param aMinimumValue On return, contains the Range-editor's minimum 
        *        allowable value
        * @param aMaximumValue On return, contains the Range-editor's maximum 
        *        allowable value
        * @remarks
        * @see
        */
        IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;

        /**
        * Sets the range, that is, the two current values entered by the user 
        * into the Range-editor.
        *
        * @param aRange The new range
        * @remarks
        * @see
        */
        IMPORT_C void SetRange(const SEikRange& aRange);

        /**
        * Gets the range, that is, the two current values of the Range-editor.
        * The method can only be called if <code>PrepareForFocusLossL()</code> 
        * succeeded.
        *
        * @return the current range
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C SEikRange Range() const; 

        /**
        * Constructs the Range-editor from a resource.
        *
        * @param aResourceReader The resource reader
        * @remarks The resource type is <code>RANGE_EDITOR</code>
        * @see
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
    private:
        virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields);
        void Draw(const TRect& aRect) const;
        TRect CalcLeftHandBorderRect() const;
        TRect CalcRightHandBorderRect() const;
    private:
        CEikMfneNumber* iLowerLimit;
        CEikMfneNumber* iUpperLimit;
    };

/**
* Abstract base class for Time-editors.
* @internal
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikTTimeEditor : public CEikMfne
    {
    public:

        /**
        * Sets the minimum and maximum allowable times.
        * @param aMinimumTime The minimum allowable time
        * @param aMaximumTime The maximum allowable time
        */
        virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime)=0;

        /**
        * Gets the minimum and maximum allowable times.
        * @param aMinimumTime On return, contains the minimum allowable time
        * @param aMaximum On return, contains the maximum allowable time
        */
        virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximum) const=0;

        /**
        * Sets the time.
        * @param aTime The time
        */
        virtual void SetTTime(const TTime& aTime)=0;

        /**
        * Gets the time.
        * Can only be called if <code>PrepareForFocusLossL()</code> succeeded.
        * @return the time in the editor
        */
        virtual TTime GetTTime() const=0;
    };

/**
* This class should not be used by user clients. Use CEikTimeEditor.
* @deprecated 
* @internal
* @lib eikctl.lib
*/
class CEikTimeEditorBC : public CEikTTimeEditor
    {
    public:

        /**
        * Default constructor.
        */
        IMPORT_C CEikTimeEditorBC();

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikTimeEditorBC();

        /**
        * The second phase object constructor.
        * @param aMinimumTime The minimum allowable time
        * @param aMaximumTime The maximum allowable time
        * @param aInitialTime The initial time shown
        * @param aFlags The flags
        */
        IMPORT_C void ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags); // to be called by container only if not constructed from resource

        /**
        * Sets the currently displayed time.
        * @param aTime The time to set. Must be between the minimum and
        * maximum allowable times
        */
        IMPORT_C void SetTime(const TTime& aTime);

        /**
        * Returns the currently displayed time.
        * @return the currently displayed time
        * @see TTime
        */
        IMPORT_C TTime Time() const;

        /**
        * Sets the minimum and maximum values. See <code>CEikTTime Editor</code>.
        * @param aMinimumTime The minimum allowable time
        * @param aMaximumTime The maximum allowable time
        * @panic <code>EEikPanicTimeEditorBadMinimumAndMaximum2</code> if the 
        *        minimum is greater than the maximum
        */
        IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime); 

        /**
        * Gets the minimum and maximum values. See <code>CEikTTime Editor</code>.
        * @param aMinimumTime On return, holds the minimum allowable time
        * @param aMaximumTime On return, holds the maximum allowable time
        */
        IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximumTime) const;

        /**
        * Construct from a resource. See <code>CCoeControl</code>.
        * @param aResourceReader The resource reader
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Called before focus is removed. See <code>CCoeControl</code>.
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C virtual void PrepareForFocusLossL();
    private:
        IMPORT_C virtual void SetTTime(const TTime& aTime);
        IMPORT_C virtual TTime GetTTime() const;
    protected:
        void DoSetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime);
        void doConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime);
    protected:
        CTimeEditor* iTimeEditor;
        TTime iMinimumTime;
        TTime iMaximumTime;
    };

/**
* The <code>CEikTimeEditor</code> class provides the Time-editor control. The 
* Time-editor allows a time value to be displayed and edited. 
* By default the editor has fields for hours, minutes, and seconds, although the
* seconds and hours fields can be omitted. Both 12- and 24-hour formats are 
* supported. When 12-hour format is used, am or pm text will be included as
* another field, either before or after the time, as determined by the locale. 
* Locale information is also used to determine the time separator characters. 
* Locale information is set and retrieved using class <code>TLocale</code>.
* The upper and lower field bounds are set depending on the format, and times 
* outside these bounds are invalid. 
* The editor has an associated resource struct <code>TIME_EDITOR</code> and 
* control factory identifier <code>EEikCtTimeEditor</code>.
* This class is not intended for user derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikTimeEditor : public CEikTimeEditorBC, private MCknTimePickerObserver
    {
    public:

        /**
        * Completes construction of a newly allocated Time-editor by setting 
        * its minimum,
        * maximum, and initial values. The
        * am/pm text settings and time separator characters specified in class
        * <code>TLocale</code> are honored. This method should only be called by the 
        * container if the control is not constructed from a resource file.
        * If the initial time is outside the specified bounds, it is reset to
        * the nearest available setting.
        * The <code>aFlags</code> parameter is used to determine whether the
        * seconds or hours fields are required (the minutes field is always 
        * present). It may also be used to specify whether or not to force 
        * 24-hour time format, overriding the locale's setting. 
        * A panic occurs if the minimum time is later than the maximum 
        * time.
        *
        * @param aMinimumTime Minimum allowable time
        * @param aMaximumTime Maximum allowable time
        * @param aInitialTime The initial time
        * @param aFlags Determines which fields are required and whether or not
        *               to force 24-hour formatting. Specify 
        *               <code>CTimeEditor::EWithoutSecondsField</code> for no 
        *               seconds field, 
        *               <code>CTimeEditor::EWithoutHoursField</code> for no 
        *               hours field, and 
        *               <code>CTimeEditor::EForce24HourFormat</code> to force 
        *               24 hour clock format, overriding the locale setting
        * @remarks
        * @see 
        * @panic <code>EEikPanicTimeEditorBadMinimumAndMaximum2</code>
        *        if <code>aMinimumTime</code> is greater than <code>aMaximumTime</code>
        */
        IMPORT_C void ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags);

        /**
        * Sets the dimming state of the control.
        *
        * @param aState <code>ETrue</code> to dim the control; 
        *               <code>EFalse</code> not to dim the control
        * @remarks
        * @see
        */
        IMPORT_C void Dim(TBool aState);

        /**
        * Sets the hidden state of the control.
        *
        * @param aState <code>ETrue</code> to hide the control. 
        *               <code>EFalse</code> not to hide the control
        */
        IMPORT_C void SetHidden(TBool aState);

        /**
        * Checks if the current value is valid against the minimum and maximum
        * values.
        *
        * @return <code>ETrue</code> if valid; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Called when there is a key event.
        *
        * @param aKeyEvent The key event
        * @param aType The event type
        * @return indicates whether or not the key event was used by this 
        *         control
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * Constructs a Time-editor from a resource.
        *
        * @param aResourceReader The resource reader
        * @remarks The resource type is <code>TIME_EDITOR</code> 
        * @see CCoeControl
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
    
        /**
        * Draws the control.
        *
        * @param aRect The rectangle in which to draw
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Creates a time picker pop-out if required.
        *
        * @remarks
        * @see CEikMfne
        */
        IMPORT_C virtual void CreatePopoutIfRequiredL();
    private:
        IMPORT_C virtual void GetMinimumAndMaximumAndInitialTimeForTimePickerL(TTime& aMinimumTime, TTime& aMaximumTime, TTime& aInitialTime) const;
        IMPORT_C virtual void SetTimeFromTimePickerAndDrawNow(const TTime& aTime);
    };

/**
* The <code>CEikDateEditor</code> class provides the Date-editor control.
* A Date-editor has five fields - day, month and year, and two separator
* characters. The order of the fields varies depending on the locale's date
* format setting. Locale information, which is set and retrieved using class
* <code>TLocale</code>, is used to determine field order and the characters 
* used to separate the date components. The upper and lower field bounds are 
* set, and any dates outside these bounds are invalid. 
* The editor can be configured to launch a pop-out calendar dialog, 
* <code>CEikCalendar</code>. This is used to set the day, month, 
* and year values directly. 
* The editor has an associated resource struct <code>DATE_EDITOR</code> and 
* control factory identifier <code>EEikCtDateEditor</code>.
* This class is not intended for user derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikDateEditor : public CEikTTimeEditor, private MEikCalendarObserver, public MEikUpdatingBgContainerBase
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikDateEditor();

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikDateEditor();

        /**
        * Completes the construction
        * of a newly allocated Date-editor. This method should be used instead
        * of <code>ConstructFromResourceL()</code> when not initializing from a
        * resource file. The editor's minimum, maximum, and initial date values 
        * are set, and the date format and date separator characters specified
        * in class <code>TLocale</code> are honored. If the initial date is 
        * outside the bounds specified, it is set to the nearest available 
        * setting.
        *
        * @param aMinimumDate The minimum allowable date
        * @param aMaximumDate The maximum allowable date
        * @param aInitialDate The initial date
        * @param aFlags If <code>aFlags=0</code>, the editor has a pop-out 
        *        calendar and an icon. Set 
        *        <code>EEikDateWithoutPopoutCalendar</code> to disable the 
        *        calendar pop-out, and/or <code>EEikHideDateIcon</code> to 
        *        hide the icon
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const TTime& aMinimumDate, const TTime& aMaximumDate, const TTime& aInitialDate, TUint32 aFlags); // to be called by container only if not constructed from resource

        /**
        * Sets the Date-editor's year, month, and day values.
        * <b>Note:</b> The dates are specified as <code>TTime</code> objects. 
        * These can be created by constructing <code>TDateTime</code> objects
        * and letting the compiler cast them. The Date-editor ignores the time
        * portions of the <code>TDateTime</code> object.
        *
        * @param aDate The Date-editor's new value
        * @remarks
        * @see
        */
        IMPORT_C void SetDate(const TTime& aDate);

        /**
        * Gets the Date-editor's current value.
        *
        * @return the Date-editor's value
        * @remarks
        * @see
        */
        IMPORT_C TTime Date() const;

        /**
        * Sets the control's dim state.
        *
        * @param aState <code>ETrue</code> to dim the control; 
        *   <code>EFalse</code> to undim it
        * @remarks
        * @see
        */
        IMPORT_C void Dim(TBool aState);

        /**
        * Sets the control's hidden state.
        *
        * @param aState <code>ETrue</code> to hide the control; 
        *   <code>EFalse</code> to show it
        * @remarks
        * @see
        */
        IMPORT_C void SetHidden(TBool aState);

        /**
        * Checks if the current value is valid.
        *
        * @return <code>ETrue</code> if the current value is valid; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Sets the minimum and maximum values.
        *
        * @param aMinimumDate The minimum allowable date
        * @param aMaximumDate The maximum allowable date
        * @panic <code>EEikPanicTimeEditorBadMinimumAndMaximum2</code> if 
        *        the minimum is greater than or equal to the maximum
        * @see CEikTTimeEditor
        */
        IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate);

        /**
        * Gets the minimum and maximum values.
        *
        * @param aMinimumDate On return, holds the minimum allowable date
        * @param aMaximumDate On return, holds the maximum allowable date
        * @see CEikTTimeEditor
        */
        IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumDate, TTime& aMaximumDate) const;

        /**
        * Called when a key event occurs.
        *
        * @param aKeyEvent The key event
        * @param aType The event type
        * @return indicates whether or not the key event was used by this 
        *         control
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * Constructs a Date-editor from a resource file.
        * This method reads the maximum and minimum date values, and 
        * whether or not the editor should support a pop-out calendar 
        * and/or date icon, from a <code>DATE_EDITOR</code> resource. It sets 
        * the initial date to be the same as the maximum date.
        *
        * @param aResourceReader The resource reader
        * @remarks The resource type is <code>DATE_EDITOR</code> 
        * @see
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Prepares the Date-editor for loss of focus. This method is called when an 
        * attempt is made to remove focus from a Date-editor. If the control 
        * value is not within the bounds specified by the minimum and maximum 
        * date values, it is reset to the nearest allowable value, the 
        * method leaves, and an appropriate info message describing 
        * the problem is displayed.
        *
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C virtual void PrepareForFocusLossL();

        /**
        * Handles focus changes.
        * This method ensures that the CBA button for the calendar 
        * pop-out is active if the Date-editor is focused.
        *
        * @param aDrawNow A value of <code>EDrawNow</code> causes the editor to
        *         be redrawn
        * @remarks
        * @see
        */
        IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

        /**
        * Handles the pop-out button.
        * This method is called when the CBA button for the calendar 
        * pop-out is selected. It causes the calendar pop-out to be launched if 
        * this option is enabled.
        *
        * @remarks This is only used in Series 80
        * @see MEikUpdatingBgContainerBase
        */
        IMPORT_C void HandleChangeButtonL();

        /**
        * Tests whether the calendar pop-out is displayed. This implementation
        * always returns <code>EFalse</code> as this is a <code>MEikUpdatingBgContainerBase</code>
        * method. It is only required on Series 80.
        *
        * @return always returns <code>EFalse</code>
        * @remarks
        * @see
        */
        IMPORT_C TBool PopupDisplayed();

        /**
        * Displays the calendar pop-out. This overrides the pop-out-disable flag
        * in the resource file.
        *
        * @remarks
        * @see
        */
        IMPORT_C void DisplayPopoutL();
    private:
        void Draw(const TRect& aRect) const;
        virtual void CreatePopoutIfRequiredL();
        virtual void SetTTime(const TTime& aDate);
        virtual TTime GetTTime() const;
    private:
        virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
        virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
        void DoSetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate);
    private:
        TTime iMinimumDate;
        TTime iMaximumDate;
        CEikDateEditorExtension* iExt;
    };

/**
* Base class for Time-and-date-editors.
* For internal use.
* This class should not be used by user clients.
* @internal
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikTimeAndDateEditorBC : public CEikTTimeEditor, protected MEikCalendarObserver, public MEikUpdatingBgContainerBase
    {
    public:

        /**
        * Default constructor.
        */
        IMPORT_C CEikTimeAndDateEditorBC();

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikTimeAndDateEditorBC();

        /**
        * 2nd phase constructor.
        * ConstructL to be called by container only if not constructed from resource, 
        * also ownership of aInterveningText is transferred when everything that can 
        * leave has successfully been done
        * @param aMinimumTimeAndDate The minimum allowable value
        * @param aMaximumTimeAndDate The maximum allowable value
        * @param aInitialTimeAndDate The initial value
        * @param aFlags the flags
        * @param aInterveningText Text between the time and date.
        */
        IMPORT_C void ConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate, const TTime& aInitialTimeAndDate, TUint32 aFlags, HBufC* aInterveningText=NULL);

        /**
        * Set the value.
        * @param aTimeAndDate the value
        */
        IMPORT_C void SetTimeAndDate(const TTime& aTimeAndDate);

        /**
        * Get the value
        * Can only be called if PrepareForFocusLossL() has successfully completed.
        * @return the value
        */
        IMPORT_C TTime TimeAndDate() const;

        /**
        * Set the minimum and maximum values. See CEikTTime Editor
        * @param aMinimumTimeAndDate The minimum allowable value
        * @param aMaximumTimeAndDate The maximum allowable value
        * @panic <code>EEikPanicTimeEditorBadMinimumAndMaximum2</code> if the 
        *        minimum is greater than or equal to the maximum
        */
        IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate); 

        /**
        * Get the minimum and maximum values. See CEikTTime Editor
        * @param aMinimumTimeAndDate On return holds the minimum allowable value
        * @param aMaximumTimeAndDate On return holds the maximum allowable value.
        */
        IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTimeAndDate, TTime& aMaximumTimeAndDate) const;

        /**
        * Handles keyboard events.
        * @param aKeyEvent The key event
        * @param aType The event type
        * @return Indicates whether or not the key event was used by this control.
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * Constructs the control from a resource. See CCoeControl.
        * @param aResourceReader The resource reader to use
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Editor validation.
        *
        * This method will be called when an attempt is made to 
        * remove focus from an editor. If the control value is not 
        * within the bounds specified by the minimum and maximum 
        * values, it is reset to the nearest allowable value, the 
        * method will leave and will display an appropriate info 
        * message.
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C virtual void PrepareForFocusLossL();

        /**
        * Called when focus is about to change. See CCoeControl.
        * @param aDrawNow A value of EDrawNow causes the editor to be redrawn
        */
        IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

        /**
        * Handles the pop-out button.
        *
        * Does nothing in this class.
        * From MEikUpdatingBgContainerBase
        */
        IMPORT_C void HandleChangeButtonL();

        /**
        * Determine if the pop-out is displayed. Always returns <code>EFalse</code> in this class.
        * @return <code>EFalse</code>
        */
        IMPORT_C TBool PopupDisplayed();

    private:
        IMPORT_C virtual void CreatePopoutIfRequiredL();
        IMPORT_C virtual void SetTTime(const TTime& aTimeAndDate);
        IMPORT_C virtual TTime GetTTime() const;
        IMPORT_C virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
        IMPORT_C virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
    protected:
        void doConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate, const TTime& aInitialTimeAndDate, TUint32 aFlags, HBufC* aInterveningText);
        void DoSetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate);
    protected:
        class CExtraData : public CBase
            {
        public:
            TInt iTimeEditorFieldTotal;
            TInt iFirstDateField;
            TInt iLastDateField;
            CDateEditor* iDateEditor;
            CCknTimePicker* iTimePicker;
            CEikMfneField* iInterveningText;
            };
    protected:
        CTimeEditor* iTimeEditor;
        CExtraData* iExt;
        TTime iMinimumTimeAndDate;
        TTime iMaximumTimeAndDate;
    };

/**
* The <code>CEikTimeAndDateEditor</code> class provides a Time-and-date-editor.
* This control allows both a time and date to be displayed and edited on a 
* single dialog line. 
* It contains the time fields (hours, minutes, and seconds), two 
* time separator characters, am/pm text, the date 
* fields (year, month, and day), and two date separator characters. 
* The seconds and hours fields are optional, and the order of the date 
* fields and the separator characters are locale-dependent. The upper 
* and lower field bounds are set, and dates and times outside these bounds 
* are invalid. 
* Date field values may be edited directly or via a pop-out calendar dialog.
* The editor has an associated resource struct <code>TIME_AND_DATE_EDITOR</code> and control
* factory identifier <code>EEikCtTimeAndDateEditor</code>.
* This class is not intended for user derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikTimeAndDateEditor : public CEikTimeAndDateEditorBC, private MCknTimePickerObserver
    {
    public:

        /**
        * Completes the construction of a newly allocated 
        * Time-and-date-editor by setting the minimum, maximum, and 
        * initial date and time values. This method should only be called by the 
        * container if the control is not constructed from a resource file.
        * The <code>aFlags</code> parameter is used to set whether the seconds 
        * or hours fields are required (the minutes field is always 
        * present). It may also be used to specify whether or not to 
        * force 24-hour time format, overriding the locale's setting, 
        * and whether the editor should have a calendar pop-out.
        * The locale-dependant date and time settings specified in class 
        * <code>TLocale</code> are honored.
        * If the initial date/time is outside the bounds specified by 
        * the minimum and maximum, it is set to the nearest valid setting.
        * A panic occurs if the minimum date/time is later than the maximum
        * date/time.
        *
        * @param aMinimumTimeAndDate The minimum allowable value
        * @param aMaximumTimeAndDate The maximum allowable value
        * @param aInitialTimeAndDate The initial value
        * @param aFlags A bitmask of the following flags. Specify 
        *        <code>CTimeEditor::EWithoutSecondsField</code> for no seconds 
        *        field, <code>CTimeEditor::EWithoutHoursField</code> for no 
        *        hours field, <code>CTimeEditor::EForce24HourFormat</code> to 
        *        force 24-hour clock format (overriding the locale setting), 
        *        and <code>CTimeEditor::EWithoutPopoutCalendar</code> for no 
        *        calendar pop-out
        * @param aInterveningText A descriptor containing the text character 
        *        to use to separate the time and date portions of the editor.
        *        Ownership of <code>aInterveningText</code> is transferred
        * @remarks
        * @see
        * @panic <code>EEikPanicTimeAndDateEditorBadMinimumAndMaximum2</code> if 
        *        <code>aMinimumTimeAndDate</code> is greater than <code>aMaximumTimeAndDate</code>
        */
        IMPORT_C void ConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate, const TTime& aInitialTimeAndDate, TUint32 aFlags, HBufC* aInterveningText=NULL);

        /**
        * Dims the time field.
        *
        * @param aState <code>ETrue</code> to dim; <code>EFalse</code> to undim
        * @remarks
        * @see
        */
        IMPORT_C void DimTime(TBool aState);

        /**
        * Dims the date field.
        *
        * @param aState <code>ETrue</code> to dim; <code>EFalse</code> to undim
        * @remarks
        * @see
        */
        IMPORT_C void DimDate(TBool aState);

        /**
        * Hides the time field.
        *
        * @param aState <code>ETrue</code> to hide; <code>EFalse</code> to 
        *        unhide
        * @remarks
        * @see
        */
        IMPORT_C void HideTime(TBool aState);

        /**
        * Hides the date field.
        *
        * @param aState <code>ETrue</code> to hide; <code>EFalse</code> to 
        *        unhide
        * @remarks
        * @see
        */
        IMPORT_C void HideDate(TBool aState);

        /**
        * Checks the validity of the current value.
        *
        * @return <code>ETrue</code> if valid; <code>EFalse</code> if invalid
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;
    private:
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
        IMPORT_C void Draw(const TRect& aRect) const;
        IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    private:
        IMPORT_C virtual void GetMinimumAndMaximumAndInitialTimeForTimePickerL(TTime& aMinimumTime, TTime& aMaximumTime, TTime& aInitialTime) const;
        IMPORT_C virtual void SetTimeFromTimePickerAndDrawNow(const TTime& aTime);
        TRect CalcBorderRect(TBool aIsTimePart) const;
    };

/**
*  The base class for Duration-editors.
*  For internal use
*
* This class should not be used by user clients.
* @internal
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikDurationEditorBC : public CEikMfne
    {
    public:

        /**
        * Default constructor.
        */
        IMPORT_C CEikDurationEditorBC();

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikDurationEditorBC();

        /**
        * 2nd phase constructor.
        * ConstructL to be called by container only if not constructed from resource.
        * @param aMinimumDuration The minimum allowable value
        * @param aMaximumDuration The maximum allowable value
        * @param aInitialDuration The initial value
        * @param aFlags may be one ofEMfneDurationAbsoluteTimeWithDays or EMfneDurationRelativeTimeWithDays.
        * @panic EEikPanicDurationBadDurationEditorWithDaysType if flags try to set both absolute and relative time.
        */
        IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration, const TTimeIntervalSeconds& aInitialDuration, TUint32 aFlags);

        /**
        * Set the minimum and maximum values. See CEikTTime Editor
        * @param aMinimumDuration The minimum allowable value
        * @param aMaximumDuration The maximum allowable value
        * @panic EEikPanicDurationEditorBadMinimumAndMaximum2 if min value >= max value.
        */
        IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); 

        /**
        * Get the minimum and maximum values. See CEikTTime Editor
        * @param aMinimumDuration On return holds the minimum allowable value
        * @param aMaximumDuration On return holds the maximum allowable value.
        */
        IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumDuration, TTimeIntervalSeconds& aMaximumDuration) const;

        /**
        * Set the value.
        * @param aDuration the value
        */
        IMPORT_C void SetDuration(const TTimeIntervalSeconds& aDuration);

        /**
        * Get the value
        * Can only be called if PrepareForFocusLossL() has successfully completed.
        * @return the value
        */
        IMPORT_C TTimeIntervalSeconds Duration() const; 

        /**
        * Check if the control has a day field.
        * @return <code>ETrue</code> if it has a day field; <code>EFalse</code> if not
        */
        IMPORT_C TBool HasDayField() const;

        /**
        * Constructs the control from a resource. See CCoeControl.
        * @param aResourceReader The resource reader to use
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Editor validation.
        *
        * This method will be called when an attempt is made to 
        * remove focus from an editor. If the control value is not 
        * within the bounds specified by the minimum and maximum 
        * values, it is reset to the nearest allowable value, the 
        * method will leave and will display an appropriate info 
        * message.
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C void PrepareForFocusLossL();
    protected:
        void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration);
    protected:
        class CExtraData : public CBase
            {
        public:
            TTimeIntervalSeconds iMinimumDuration;
            TTimeIntervalSeconds iMaximumDuration;
            };
    protected:
        CTimeEditor* iTimeEditor;
        CDurationWithDaysEditor* iDurationWithDaysEditor;
        CExtraData* iExt;
    };

/**
* The <code>CEikDurationEditor</code> class provides the Duration-editor control. 
* The Duration-editor allows a duration to be displayed and edited. The
* editor has a clock icon and an edit field with separators for hours, minutes, 
* and seconds. These fields can all be suppressed using the appropriate flags 
* in the resource declaration. Unlike the Time-editor control, by 
* default, the Duration-editor has no am/pm text. This is because the duration 
* is a length of time (from 0 to 23:59:59 hours), rather than a point in time. This is referred to as a relative time. However, the flag
* <code>EEikDurationAbsoluteTimeWithDays</code> can be used to force the 
* Duration-editor to show absolute times, with am/pm text.
* The upper and lower field bounds are set and values outside these bounds are
* invalid.
* The editor has an associated resource struct <code>DURATION_EDITOR</code> and
* control factory identifier <code>EEikCtDurationEditor</code>. This class is 
* not intended for user derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikDurationEditor : public CEikDurationEditorBC, public MCknTimePickerObserver
    {
    public:

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikDurationEditor();

        /**
        * If the Duration-editor specifies absolute time, this method sets the 
        * value of the Time-editor control.
        * <b>Note:</b> The dates are specified as <code>TTime</code> objects, 
        * which can be created by constructing <code>TDateTime</code> objects
        * and letting the compiler cast them. The Time-editor ignores the date
        * and microsecond portions of the <code>TDateTime</code> object.
        *
        * @param aTime The time to set the editor to
        * @panic <code>EEikPanicDurationEditorBadAbsoluteTime</code> if this 
        *        method is called on an editor that does not have an absolute 
        *        time part
        * @see
        */
        IMPORT_C void SetTime(const TTime& aTime); 
    
        /**
        * Gets the absolute time part of the Duration-editor's current value.
        *
        * @return the absolute time part of the current value
        * @panic <code>EEikPanicDurationEditorBadAbsoluteTime</code> if this method is 
        *        called on an editor that does not have an absolute time part
        * @see
        */
        IMPORT_C TTime Time() const; 

        /**
        * Determines if this editor uses absolute time.
        *
        * @return <code>ETrue</code> if absolute time; <code>EFalse</code> if 
        *         relative
        * @remarks
        * @see
        */
        IMPORT_C TBool HasAbsoluteTime() const;

        /**
        * Set the control's dim state.
        *
        * @param aState <code>ETrue</code> to dim the control;
        *               <code>EFalse</code> to undim it
        * @remarks
        * @see
        */
        IMPORT_C void Dim(TBool aState);

        /**
        * Set the control's hidden state.
        *
        * @param aState <code>ETrue</code> to hide the control;
        *   <code>EFalse</code> to show it
        * @remarks
        * @see
        */
        IMPORT_C void SetHidden(TBool aState);

        /**
        * Check if the current value is valid against the minimum and maximum
        * durations.
        *
        * @return <code>ETrue</code> if it is valid; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;
    private:
        IMPORT_C virtual void CreatePopoutIfRequiredL();
        IMPORT_C virtual void GetMinimumAndMaximumAndInitialTimeForTimePickerL(TTime& aMinimumTime, TTime& aMaximumTime, TTime& aInitialTime) const;
        IMPORT_C virtual void SetTimeFromTimePickerAndDrawNow(const TTime& aTime);
        IMPORT_C void Draw(const TRect& aRect) const;
        TRect CalcBorderRect(TBool aTimeEditor) const;
    };

/**
* The <code>CEikTimeOffsetEditor</code> class provides a Time-offset-editor. 
* This control allows a signed time offset to be displayed and edited. It has 
* the same fields as the Time-editor control <code>CEikTimeEditor</code>, 
* except there is no am/pm text because the value is a time offset rather than 
* a point in time. The value can be either positive or negative, from 0 to 
* 23:59:59 hours. The Time-offset-editor has an associated resource struct 
* <code>TIME_OFFSET_EDITOR</code>
* and control factory identifier <code>EEikCtTimeOffsetEditor</code>. 
* This class is not intended for user derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikTimeOffsetEditor : public CEikMfne
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikTimeOffsetEditor();

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CEikTimeOffsetEditor();

        /**
        * Completes construction of a Time-offset-editor, by 
        * setting its minimum, maximum, and initial values. The time separator 
        * characters specified in class 
        * <code>TLocale</code> are honored. This method should only be called by the 
        * container if the control is not constructed from a resource file. 
        * The <code>aFlags</code> parameter is used to determine whether the 
        * seconds or hours fields are displayed by the editor (the minutes 
        * field is always displayed). This method forces 24-hour time 
        * format for the Time-offset-editor, overriding the locale's setting.
        * If the initial time offset is outside the bounds specified, 
        * it is invalid and will be reset to the upper or lower bound.
        * The minimum value for a Time-offset-editor is -23:59:59, and the 
        * maximum value is 23:59:59.
        * A panic occurs if the minimum time offset specified is greater 
        * than the maximum time offset.
        *
        * @param aMinimumTimeOffset The minimum allowable value, in seconds
        * @param aMaximumTimeOffset The maximum allowable value, in seconds
        * @param aInitialTimeOffset The initial value, in seconds
        * @param aFlags Determines the fields that are required. Specify 
        *        <code>CTimeEditor::EWithoutSecondsField</code> for no seconds
        *        field, <code>CTimeEditor::EWithoutHoursField</code> for no 
        *        hours field. 24-hour clock format is set, regardless of the 
        *        flag setting specified in this parameter
        * @remarks
        * @see
        * @panic <code>EEikPanicTimeOffsetEditorBadMinimumAndMaximum2</code>
        *        if <code>aMinimumTimeOffset</code> is greater than
        *        <code>aMaximumTimeOffset</code>
        */
        IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset, const TTimeIntervalSeconds& aInitialTimeOffset, TUint32 aFlags);

        /**
        * Sets the range of allowable offset values. These define the maximum 
        * and minimum values that may be entered by the user. If the existing 
        * offset value is outside the bounds set by this method, it is reset 
        * to the nearest boundary value.
        *
        * @param aMinimumTimeOffset The minimum allowable value
        * @param aMaximumTimeOffset The maximum allowable value
        * @panic <code>EEikPanicTimeOffsetEditorBadMinimumAndMaximum2</code>
        *        if the minimum value is greater than or equal to the maximum
        *        value
        * @remarks
        * @see
        */
        IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); 

        /**
        * Gets the range of allowable values. The values obtained define 
        * the maximum and minimum values that can be entered by the user.
        *
        * @param aMinimumTimeOffset On return, contains the Time-offset-editor’s
        *                           minimum allowable value
        * @param aMaximumTimeOffset On return, contains the Time-offset-editor’s
        *                           maximum allowable value
        * @remarks
        * @see
        */
        IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumTimeOffset, TTimeIntervalSeconds& aMaximumTimeOffset) const;

        /**
        * Sets the Time-offset-editor's value. The sign is set according 
        * to whether the value specified is positive or negative. This method 
        * is called by <code>PrepareForFocusLossL()</code> after the entered 
        * value has either been validated or moved into the valid range.
        *
        * @param aTimeOffset The new offset value to assign to the editor
        * @remarks
        * @see
        */
        IMPORT_C void SetTimeOffset(const TTimeIntervalSeconds& aTimeOffset);

        /**
        * Gets the Time-offset-editor's value. Can only be called after a call
        * to <code>PrepareForFocusLossL()</code> has completed successfully.
        *
        * @return the editor's value
        * @remarks
        * @see
        */
        IMPORT_C TTimeIntervalSeconds TimeOffset() const; 

        /**
        * Sets the control's dim state.
        *
        * @param aState <code>ETrue</code> to dim the control, 
        *   <code>EFalse</code> to undim it
        * @remarks
        * @see
        */
        IMPORT_C void Dim(TBool aState);

        /**
        * Sets the control's hidden state.
        *
        * @param aState <code>ETrue</code> to hide the control;
        *   <code>EFalse</code> to show it
        * @remarks
        * @see
        */
        IMPORT_C void SetHidden(TBool aState);

        /**
        * Check if the current value is valid.
        *
        * @return <code>ETrue</code> if it is valid; <code>EFalse</code> 
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Constructs a Time-offset-editor from a resource file. This method 
        * completes the construction of a newly constructed 
        * Time-offset-editor from a <code>TIME_OFFSET_EDITOR</code> resource. 
        * The minimum and maximum time offsets and the flag settings are read 
        * from the resource, and <code>ConstructL()</code> is called with 
        * these settings. The initial time offset is set to the maximum time 
        * offset value.
        * 
        * @param aResourceReader The resource reader
        * @remarks The resource type is <code>TIME_OFFSET_EDITOR</code> 
        * @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Prepares the editor for loss of focus. This method is called when an 
        * attempt is made to remove focus from a Date-editor. If the control 
        * value is not within the bounds specified by the minimum and maximum 
        * values, it is reset to the nearest allowable value, the 
        * method leaves and an appropriate info message is displayed.
        *
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C void PrepareForFocusLossL();
    private:
        void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset);
        void Draw(const TRect& aRect) const;
    private:
        CTimeEditor* iTimeEditor;
        TTimeIntervalSeconds iMinimumTimeOffset;
        TTimeIntervalSeconds iMaximumTimeOffset;
    // this object does not own iSign
        CEikMfneSymbol* iSign;
    };

/**
*  Base class for Latitude- and Longitude-editors. Internal use only.
* @internal
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikLatitudeLongitudeEditorBase : public CEikMfne
    {
    protected:

        CEikLatitudeLongitudeEditorBase(TInt aMaximumDegrees);
        void DoConstructL(HBufC* aDegreeSign, HBufC* aMinuteSign, HBufC* aSecondSign, HBufC* aTextForFirstDirection, TChar aKeyToMatchForFirstDirection, HBufC* aTextForSecondDirection,
                TChar aKeyToMatchForSecondDirection, const SEikDegreesMinutesDirection& aDegreesMinutesDirection, TInt aFlags);
        void SetDegreesMinutesDirection(const SEikDegreesMinutesDirection& aDegreesMinutesDirection);
        SEikDegreesMinutesDirection DegreesMinutesDirection() const;
        void Draw(const TRect& aTRect) const;
        TRect CalcBorderRect() const;
    private:
        void AddSpaceL();
        void AddDirectionL(CEikMfneSymbol::CItem*& aFirstDirection, CEikMfneSymbol::CItem*& aSecondDirection, TChar aKeyToMatchForFirstDirection, TChar aKeyToMatchForSecondDirection, const SEikDegreesMinutesDirection& aDegreesMinutesDirection);
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    protected:
        TInt iMaximumDegrees;
        CEikMfneNumber* iDegrees;
        CEikMfneNumber* iMinutes;
        CEikMfneNumber* iSeconds;
        CEikMfneSymbol* iDirection;
    };

/**
* The <code>CEikLatitudeEditor</code> class provides the Latitude-editor 
* control, which is used to display and edit latitude values.
* It has the following components: a degrees field with a maximum value of 90,
* a minutes field with a maximum value of 59, and a direction field
* indicating North or South. The editor has an associated resource struct 
* <code>LATITUDE_EDITOR</code> and control factory identifier 
* <code>EEikCtLatitudeEditor</code>. This method is not intended for user 
* derivation. 
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikLatitudeEditor : public CEikLatitudeLongitudeEditorBase
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikLatitudeEditor();

        /**
        * Completes construction of a newly allocated Latitude-editor. It 
        * should be used instead of 
        * <code>ConstructFromResourceL()</code> when not initializing from a 
        * resource file.
        * The following values are initialized: the text to use for the 
        * degrees, minutes, and seconds signs, the text to indicate North
        * and South, the keys to change the direction field, and the 
        * initial latitude value, in degrees and minutes. 
        * Ownership of <code>aDegreeSign</code>, <code>aMinuteSign</code>, 
        * <code>aSecondSign</code>, <code>aTextForNorth</code> and
        * <code>aTextForSouth</code> is transferred.
        *
        * @param aDegreeSign The degrees sign text
        * @param aMinuteSign The minutes sign text
        * @param aSecondSign The seconds sign text
        * @param aTextForNorth The text indicating North
        * @param aKeyToMatchForNorth The key press that changes the 
        *                            direction to North
        * @param aTextForSouth The text indicating South
        * @param aKeyToMatchForSouth The key press that changes the
        *                            direction to South
        * @param aLatitude The initial latitude value, in degrees and minutes,
        *                  and the direction (<code>EEikCompassNorth</code> or 
        *                  <code>EEikCompassSouth</code>)
        * @param aFlags Possible flags are defined in eikon.hrh. These include
        *        <code>EEikMfneLatLongFlagAddSecondsField</code> to display a 
        *        seconds field, <code>EEikMfneLatLongFlagAddTrailingSign</code>
        *        to have a trailing sign on the last editor field, and
        *        <code>EEikMfneLatLongFlagDirectionIsPrefix</code> to have the
        *        direction displayed as a prefix (by default the editor 
        *        displays the direction field as a suffix)
        * @panic <code>EEikPanicLatitudeLongitudeEditorBaseBadValues1</code> - 
        *        a panic occurs if any of the values contained in 
        *        <code>aLatitude</code> are invalid. The degrees value must be 
        *        between 0 and 90 inclusive, and the minutes between 0 and 
        *        59 inclusive
        * @see
        */
        IMPORT_C void ConstructL(HBufC* aDegreeSign, HBufC* aMinuteSign, HBufC* aSecondSign, HBufC* aTextForNorth, TChar aKeyToMatchForNorth, HBufC* aTextForSouth, TChar aKeyToMatchForSouth, const SEikDegreesMinutesDirection& aLatitude, TInt aFlags=0);

        /**
        * Sets the value of the Latitude-editor.
        *
        * @param aLatitude The new latitude value to set the editor to
        * @remarks
        * @see
        */
        IMPORT_C void SetLatitude(const SEikDegreesMinutesDirection& aLatitude);

        /**
        * Gets the Latitude-editor's value. This method can only be called if
        * <code>PrepareForFocusLossL()</code> succeeded.
        *
        * @return the Latitude-editor's value
        * @remarks
        * @see
        */
        IMPORT_C SEikDegreesMinutesDirection Latitude() const;

        /**
        * Check if the current value is valid.
        *
        * @return <code>ETrue</code> if it is valid; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Constructs a Latitude-editor from a resource file.
        * The editor's fields are initialized to the values read by 
        * <code>aResourceReader</code> from a <code>LATITUDE_EDITOR</code> 
        * resource. The initial Latitude-editor value is set as follows: the 
        * degrees value is set to 90, the minutes and seconds to 0, and 
        * the direction to <code>EEikCompassNorth</code>.
        * Use this method in preference to <code>ConstructL()</code> when the
        * editor's field values should be read from a resource file.
        *
        * @param aResourceReader A resource file reader
        * @panic If any of the values contained in <code>aLatitude</code> are 
        *        invalid, panic <code>EEikPanicLatitudeLongitudeEditorBaseBadValues1</code>
        *        occurs. The degrees value must be between 0 and 90 inclusive, 
        *        and the minutes between 0 and 59 inclusive
        * @remarks The resource type is <code>LATITUDE_EDITOR</code>. 
        * @see CCoeControl::ConstructFromResourceL()
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Prepares the editor for loss of focus. This method is called 
        * when an attempt is made to remove focus from the Latitude-editor. It 
        * handles the redrawing associated with the loss of focus and performs 
        * validity checking, ensuring that if the degrees value is set to 90, 
        * the minutes and seconds values are both reset to
        * zero.
        *
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C virtual void PrepareForFocusLossL();
    };

/**
* The <code>CEikLongitudeEditor</code> class provides the Longitude-editor 
* control, which is used to display and edit longitude values.
* It has the following components: a degrees field with maximum value
* 180, a minutes field with maximum value 59, and a direction
* field indicating East or West.
* The editor has an associated resource struct <code>LONGITUDE_EDITOR</code> 
* and control factory identifier <code>EEikCtLongitudeEditor</code>. This 
* class is not intended for user derivation.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikLongitudeEditor : public CEikLatitudeLongitudeEditorBase
    {
    public:
    // miscellaneous functions

        /**
        * The default object constructor.
        */
        IMPORT_C CEikLongitudeEditor();

        /**
        * Completes construction of a newly allocated Longitude-editor. It 
        * should be used instead of <code>ConstructFromResourceL()</code> when 
        * not initializing from a resource file. 
        * The following values are initialized: the text to use for the 
        * degrees, minutes and seconds signs, the text to indicate East
        * and West, the keys to change the direction field, and the 
        * initial longitude value, in degrees and minutes. 
        * Ownership of <code>aDegreeSign</code>, <code>aMinuteSign</code>, 
        * <code>aSecondSign</code>, <code>aTextForEast</code> and
        * <code>aTextForWest</code> is transferred when everything that can 
        * leave has successfully completed.
        *
        * @param aDegreeSign The degrees sign text
        * @param aMinuteSign The minutes sign text
        * @param aSecondSign The seconds sign text
        * @param aTextForEast The text indicating East
        * @param aKeyToMatchForEast The key press that changes the 
        *                           direction to East
        * @param aTextForWest The text indicating West
        * @param aKeyToMatchForWest The key press that changes the 
        *                           direction to West
        * @param aLongitude The initial longitude value, in degrees and 
        *        minutes, and the direction (<code>EEikCompassEast</code> or 
        *        <code>EEikCompassWest</code>)
        * @param aFlags Possible flags are defined in eikon.hrh. These include:
        *               <code>EEikMfneLatLongFlagAddSecondsField</code> to 
        *               display a seconds field, 
        *               <code>EEikMfneLatLongFlagAddTrailingSign</code> to 
        *               have a trailing sign on the last editor field, and 
        *               <code>EEikMfneLatLongFlagDirectionIsPrefix</code> to 
        *               have the direction displayed as a prefix (by default, 
        *               the editor displays the direction field as a suffix)
        * @panic <code>EEikPanicLatitudeLongitudeEditorBaseBadValues1</code> - 
        *        a panic occurs if any of the values contained in 
        *        <code>aLongitude</code> are invalid. The degrees value must 
        *        be between 0 and 180 inclusive, and the minutes between 
        *        0 and 59 inclusive
        * @see
        */
        IMPORT_C void ConstructL(HBufC* aDegreeSign, HBufC* aMinuteSign, HBufC* aSecondSign, HBufC* aTextForEast, TChar aKeyToMatchForEast, HBufC* aTextForWest, TChar aKeyToMatchForWest, const SEikDegreesMinutesDirection& aLongitude, TInt aFlags=0);

        /**
        * Sets the value of the Longitude-editor.
        *
        * @param aLongitude The value to which to set the Longitude-editor
        * @remarks
        * @see

        */
        IMPORT_C void SetLongitude(const SEikDegreesMinutesDirection& aLongitude);

        /**
        * Gets the Longitude-editor's value. This method can only be called
        * if <code>PrepareForFocusLossL()</code> succeeded.
        *
        * @return the Longitude-editor's value
        * @remarks
        * @see
        */
        IMPORT_C SEikDegreesMinutesDirection Longitude() const; 

        /**
        * Check if the current value is valid.
        *
        * @return <code>ETrue</code> if it is valid; <code>EFalse</code> 
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsValid() const;

        /**
        * Constructs a Longitude-editor from a resource file. 
        * The editor's fields are initialized to the values read by 
        * <code>aResourceReader</code> from a <code>LONGITUDE_EDITOR</code> 
        * resource. The initial Longitude-editor value is set as follows: the 
        * degrees value is set to 180, the minutes and seconds to zero, and the
        * direction to <code>EEikCompassEast</code>.
        * Use this method in preference to <code>ConstructL()</code> when the
        * editor's field values are read from a resource file.
        * 
        * @param aResourceReader A resource file reader
        * @panic If any of the values contained in <code>aLongitude</code> are 
        *        invalid, the panic <code>EEikPanicLatitudeLongitudeEditorBaseBadValues1</code> 
        *        occurs. The degrees value must 
        *        be between 0 and 180 inclusive, and the minutes between 
        *        0 and 59 inclusive
        * @remarks The resource type is <code>LONGITUDE_EDITOR</code>.
        * @see CCoeControl::ConstructFromResourceL()
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Prepares the editor for loss of focus. This method is called 
        * when an attempt is made to remove focus from the Longitude-editor. 
        * It handles the redrawing associated 
        * with the loss of focus and performs validity checking, ensuring 
        * that if the degrees value has been set to 180, the minutes and 
        * seconds values are both reset to zero.
        *
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C virtual void PrepareForFocusLossL();
    };

#endif  // EIKMFNE_H

// End of File