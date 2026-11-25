/**
* ==============================================================================
*  Name        : eikrnged.h
*  Part of     : CKON
*  Interface   : Range Ref Editor API
*  Description : Classes required to implement a cell range editor.
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


#ifndef __EIKRNGED_H__
#define __EIKRNGED_H__

// INCLUDES
#include <bacell.h>
#include <eikmfne.h>

// FORWARD DECLARATIONS
/**
 * The <code>CEikMfneCellRefExt</code> class implements [what].
 *
 * @lib [what]
 * @since [what]
 */
class CEikMfneCellRefExt;

/**
 * The <code>CEikMfneCellRef</code> class implements a multi-field numeric
 * editor field and is derived from <code>CEikMfneField</code> which can be
 * used to edit a <code>TCellRef</code>.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikMfneCellRef : public CEikMfneField
    {
    public:
    /** [what] */
    enum
        {
        /** [what] */
        EPreserveOldWidthBeforeEditing  =0x1,
        /** [what] */
        EPublicallySettableFlags        =EPreserveOldWidthBeforeEditing
        };
    public:
    /** [what] */
    enum TCellRefRevertValue
        {
        /** [what] */
        ERevertToDefault =0x01,
        /** [what] */
        ERevertToMinimum =0x02,
        /** [what] */
        ERevertToMaximum =0x04
        };
    private:
    enum
        {
        EIsBeingEditedWithCursor        =0x2
        };
    private:
        CEikMfneCellRef(const TCellRef& aMinimumCellRef, const TCellRef& aMaximumCellRef, TUint32 aFlags);
    public:

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CEikMfneCellRef();

       /**
        * Static constructor, which reads in minimum and maximum
        * <code>TCellRef</code> values from resources.
        *
        * @param aFont The font to use in this field
        * @param aResourceReader The resource reader to use to read in the
        *                        minimum and maximum values
        * @remarks
        * @see
        */
        IMPORT_C static CEikMfneCellRef* NewL(const CFont& aFont, TResourceReader& aResourceReader);

       /**
        * Static constructor.
        *
        * @param aFont The font to use in this field
        * @param aMinimumCellRef The minimum value of <code>TCellRef</code>
        *                        allowed in this field
        * @param aMaximumCellRef The maximum value of <code>TCellRef</code>
        *                        allowed in this field
        * @param aInitialCellRef The initial value of the field
        * @param aFlags The minimum value of <code>TCellRef</code> allowed
        *               in this field
        * @remarks
        * @see
        */
        IMPORT_C static CEikMfneCellRef* NewL(const CFont& aFont, const TCellRef& aMinimumCellRef, const TCellRef& aMaximumCellRef, const TCellRef& aInitialCellRef, TUint32 aFlags);

       /**
        * Sets the minimum and maximum values which can be inputted in this
        * field, and the font. This function also ensures that the current
        * value is within the new range.
        *
        * @param aMinimumCellRef The minimum value of <code>TCellRef</code>
        *                        allowed in this field
        * @param aMaximumCellRef The maximum value of <code>TCellRef</code>
        *                        allowed in this field
        * @param aFont The font to use in this field
        * @remarks
        * @see
        */
        IMPORT_C void SetMinimumAndMaximum(const TCellRef& aMinimumCellRef, const TCellRef& aMaximumCellRef, const CFont& aFont); // only values inside the initial minimum and maximum are permitted

       /**
        * Gets the minimum and maximum values which can be inputted in this
        * field, and the font.
        *
        * @param aMinimumCellRef When this function returns, this value will be
        *                        the minimum value of <code>TCellRef</code>
        *                        allowed in this field
        * @param aMaximumCellRef When this function returns, this value will be
        *                        the maximum value of <code>TCellRef</code>
        *                        allowed in this field
        * @remarks
        * @see
        */
        IMPORT_C void GetMinimumAndMaximum(TCellRef& aMinimumCellRef, TCellRef& aMaximumCellRef) const;

       /**
        * Sets the current value and font of the field.
        *
        * @param aCellRef The value to be set
        * @param aFont The font to use to draw the new value
        * @remarks
        * @see
        */
        IMPORT_C void SetCellRef(const TCellRef& aCellRef, const CFont& aFont);

       /**
        * Gets the current value displayed in the field.
        *
        * @return the current value
        * @remarks
        * @see
        */
        IMPORT_C TCellRef CellRef() const;
    public:
        /** @internal */
        void SetInlineText(const TDesC& aText);
        /** @internal */
        void CommitInlineText();
        /** @internal */
        void SetEditingWithCursor(TBool aEditing);
        /** @internal */
        void SetRevertMode(TUint aMode);
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
        TInt MaximumNumberOfLetters(TBool aUseMinimumAndMaximumCateredForInFieldWidth) const;
        /** @internal */
        TInt MaximumNumberOfDigits(TBool aUseMinimumAndMaximumCateredForInFieldWidth) const;
        /** @internal */
        TInt NumberOfLetters() const;
        /** @internal */
        TInt NumberOfDigits() const;
    private:
        void ConstructL(const CFont& aFont, const TCellRef& aInitialCellRef);
        void SetTextToCellRef(const TCellRef& aCellRef, const CFont& aFont);
        TCellRef CellRefFromText() const;
        TInt RowFromText() const;
        TInt ColumnFromText() const;
    private:
    enum {ENumLetters=26}; //!! assumes 26 letters in the alphabet
    private:
        TCellRef iMinimumCellRef;
        TCellRef iMaximumCellRef;
        TCellRef iMinimumCellRefCateredForInFieldWidth;
        TCellRef iMaximumCellRefCateredForInFieldWidth;
        TUint32 iFlags;
        CEikMfneCellRefExt* iExt;
    };

/**
 * The <code>CEikRangeRefEditor</code> class implements a multi-field numeric
 * editor, a <code>TCellRef</code> range editor with 3 fields. It contains
 * upper and lower values that can be edited, and a separator.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikRangeRefEditor : public CEikMfne
    {
    public:
    // miscellaneous functions

        /**
        * C++ default constructor.
        */
        IMPORT_C CEikRangeRefEditor();
    // ConstructL to be called by container only if not constructed from resource, also ownership of aSeparatorText is transferred when everything that can leave has successfully been done

       /**
        * Completes construction of the editor. This creates the editor's
        * fields and sets the initial values (two-phase construction).
        *
        * @param aMinimumCellRef The minimum <code>TCellRef</code> which is
        *                        allowed in the editor
        * @param aMaximumCellRef The maximum <code>TCellRef</code> which is
        *                        allowed in the editor
        * @param aInitialRangeRef The initial upper and lower values for the 
        *                         editor
        * @param aSeparatorText The text to be displayed in the separator
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const TCellRef& aMinimumCellRef, const TCellRef& aMaximumCellRef, const TRangeRef& aInitialRangeRef, HBufC* aSeparatorText);

       /**
        * Sets the maximum and minimum allowed values in the editor.
        *
        * @param aMinimumCellRef The minimum allowed value
        * @param aMaximumCellRef The maximum allowed value
        * @remarks
        * @see
        */
        IMPORT_C void SetMinimumAndMaximum(const TCellRef& aMinimumCellRef, const TCellRef& aMaximumCellRef); // only values inside the initial minimum and maximum are permitted

       /**
        * Gets the maximum and minimum allowed values in the editor.
        *
        * @param aMinimumCellRef On return, this contains the minimum allowed 
        *                        value
        * @param aMaximumCellRef On return, this contains the maximum allowed
        *                        value
        * @remarks
        * @see  
        */
        IMPORT_C void GetMinimumAndMaximum(TCellRef& aMinimumCellRef, TCellRef& aMaximumCellRef) const;

       /**
        * Sets the upper and lower values displayed in the editor.
        *
        * @param aRangeRef The values to be set
        * @remarks
        * @see
        */
        IMPORT_C void SetRangeRef(const TRangeRef& aRangeRef);

       /**
        * Gets the upper and lower values displayed in the editor.
        *
        * @return the current values in the editor
        * @remarks
        * @see
        */
        IMPORT_C TRangeRef RangeRef() const; // can only be called if PrepareForFocusLossL() succeeded
    // framework

       /**
        * Constructs an editor from a resource file. This uses an object of
        * type <code>EEikCtRangeRefEditor</code> with struct 
        * <code>CELL_RANGE_EDITOR</code>.
        * 
        * @param aResourceReader A resource reader
        * @remarks The resource type is <code>[what]</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
    private:
        virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields);
        void Draw(const TRect& aRect) const;
    private:
    // none of these pointers owns anything
        CEikMfneCellRef* iFrom;
        CEikMfneCellRef* iTo;
    };


#endif  // __EIKRNGED_H__

// End of File
