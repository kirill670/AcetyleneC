/*
* ==============================================================================
*  Name        : ckncolumnedtext.h
*  Part of     : CKON
*  Interface   : Column Listbox API
*  Description : Column item classes.
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

#ifndef CKNCOLUMNEDTEXT_H
#define CKNCOLUMNEDTEXT_H

// INCLUDES
#include <cknbctrl.h>

class CCknSkinBase;

/**
 * The <code>CCknColumnItem</code> class implements a prompt/value pair with a 
 * column number. It is used by the <code>CCknColumnedText</code> and
 * <code>CCknPropertiesDialog</code> controls.
 * 
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknColumnItem : public CBase
    {
public:
       /**
        * Constructs and returns a pointer to a new <code>CCknColumnItem</code>
        * (non-transparent).
        *
        * @param aPrompt The column item's prompt text
        * @param aValue The column item's value text
        * @param aColumn The number of the column in which to display the 
        *                column item
        * @return the newly instantiated object
        * @remarks 
        * @see
        */
       IMPORT_C static CCknColumnItem* NewL(const TDesC& aPrompt, const TDesC& aValue, TInt aColumn);

       /**
        * Constructs and returns a pointer to a new <code>CCknColumnItem</code>
        * specifying the prompt by resource ID.
        *
        * @param aPromptRid A resource ID used to set the column item's 
        *                   prompt text
        * @param aValue The column item's value text
        * @param aColumn The number of the column in which to display the 
        *                column item
        * @return the newly instantiated object
        * @remarks
        * @see
        */
       IMPORT_C static CCknColumnItem* NewL(TInt aPromptRid, const TDesC& aValue, TInt aColumn);

       /**
        * Constructs and returns a new 
        * blank <code>CCknColumnItem</code>, useful for vertical spacing. 
        *
        * @param aColumn The number of the column in which to display the 
        *                column item
        * @param aTransparent Determines whether or not the item will be 
        *                     transparent. 
        * @return the newly instantiated object
        * @remarks Transparent blank items allow the column space to be used by
        *          the previous column
        * @see
        */
       IMPORT_C static CCknColumnItem* NewL(TInt aColumn, TBool aTransparent);

       /**
        * The object destructor.
        */
       IMPORT_C ~CCknColumnItem();

       /**
        * Returns the item's prompt field text.
        * 
        * @return the prompt text
        * @remarks
        * @see
        */
       IMPORT_C TPtrC Prompt() const;

       /**
        * Returns the item's value field text.
        * 
        * @return the value text
        * @remarks
        * @see
        */
       IMPORT_C TPtrC Value() const;

       /**
        * Returns the column number of this column item.
        *
        * @return the column number
        * @remarks
        * @see
        */
       IMPORT_C TInt Column() const;

       /**
        * Reports whether or not the item is transparent.
        *
        * @return <code>ETrue</code> if the item is transparent; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
       IMPORT_C TBool IsTransparent() const;

       /**
        * Changes the item's value field text to the specified value. 
        *
        * @param aValue The new text for value field
        * @remarks
        * @see
        */  
       IMPORT_C void ResetValueTextL(const TDesC & aValue);

protected:
    void ConstructL(const TDesC& aPrompt, const TDesC& aValue);
    CCknColumnItem(TInt aColumn);
protected:
    HBufC* iPrompt;     ///<String containing text for the prompt item
    HBufC* iValue;      ///<String containing text for the value item
    TInt iColumn;       ///<Number of the column that item should be displayed in starts at 0
    TInt iTransparent;  ///<Whether or not the item is a blank transparent item
private:
    void *iExt;
    };


/**
 * The <code>CCknColumnedText</code> class implements a control that places 
 * prompt/value pairs into columns. The control is used by the Properties 
 * Dialog.
 * 
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknColumnedText : public CCknBorderedControl
    {
public: 
       /**
        * Constructs and returns a pointer to a new <code>CCknColumnedText</code>
        * object. 
        *
        * @return the newly instantiated object
        * @remarks
        * @see
        */
       IMPORT_C static CCknColumnedText* NewL();

       /**
        * Constructs a new <code>CCknColumnedText</code> object and returns 
        * a pointer to it.
        *
        * @param aColumnNumber The number of columns that the control should 
        *                      have
        * @param aColumnMaximumSize The maximum size for the columns
        *                           in the control, in pixels 
        * @return the newly instantiated object
        * @remarks
        * @see
        */
       IMPORT_C static CCknColumnedText* NewL(TInt aColumnNumber, TInt aColumnMaximumSize);

       /**
        * The object destructor. <code>CCknColumnedText</code> does not own 
        * the items in its array and so does not destroy them.
        * 
        * @remarks
        * @see
        */
       ~CCknColumnedText();

       /**
        * Appends <code>CCknColumnItems</code> onto the list of items to 
        * display.
        *
        * @param aItemArray An array of <code>CCknColumnItems</code> that are 
        *                   appended to the list of items to display
        * @return <code>KErrNone</code>, if all items are appended successfully;
        *         otherwise, another of the system-wide error codes
        * @remarks
        * @see
        */
       IMPORT_C TInt AddFieldItems(const RPointerArray<CCknColumnItem>& aItemArray);

       /**
        * Updates the value text for the <code>CCknColumnItem</code> at the 
        * row and column specified co-ordinates.
        *
        * @param aRowNumber The row of the item to update
        * @param aColumnNumber The column of the item to update
        * @param aNewText The new value field text in 
        *                 the item specified by the supplied row and column
        * @remarks
        * @see
        */
       IMPORT_C void UpdateFieldItemValueTextL(TInt aRowNumber, TInt aColumnNumber, const TDesC& aNewText);

       /**
        * Determines the column widths required by the current items and fixes 
        * the column widths to this size.
        *
        * @remarks This method should be called after any changes to items, or 
        *          their text, that might affect the column width
        * @see
        */
       IMPORT_C void FixSizeForCurrentItemsL();

public: 
    // from CCoeControl
    /** @internal */
    TSize MinimumSize();
protected: 
    CCknColumnedText(TInt aColumnNumber, TInt aColumnMaximumSize);
    void BaseConstructL();
    // from CCoeControl
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

/**
 * Draws all items that have a column number less than iColumns
 * truncating them to iMaxColumnWidth
 *
 * @param aRect The invalidated rect which is unused. The control is redrawn completely.
 */
    IMPORT_C void Draw(const TRect& aRect) const;


/**
 *
 * Calculates the available width in pixels for the value field in the given position
 * Takes into account any right adjacent transparent fields - these allow this item to
 * overwrite into the next column space.
 *
 * @param aColumnNumber The number of the column that the item appears in
 * @param aRowNumber The number of the row that the item appears in
 * @param aUsedWidth The column width already used (by prompt text and gaps)
 * @return The width in pixels available for the given items value text
 *            to be displayed in.
 */
    TInt CalculateAvailableWidthInPixelsForValueField(TInt aColumnNumber, 
                                                      TInt aRowNumber, 
                                                      TInt aUsedWidth) const;
private: 
    //from CCoeControl
    void SizeChanged();
    void Reserved_1();
    void Reserved_2();  
private:
    enum EColumnItemType
        {
        EPrompt=0,
        EValue
        };
private:
/**
 *
 * Calculates the maximum width in pixels of either the prompt strings or the value strings in a column
 *
 * @param aColumnNumber The number of the column that the calculation is performed for
 * @param aType Determines whether the calculation is performed on Prompt or Value items
 * @return Width in pixels of the longest string from all given items in this column
 */
    TInt MaximumWidthInPixels(TInt aColumnNumber, EColumnItemType aType) const;

/**
 * Calculates the width in pixels of a column 
 *
 * @param aColumnNumber The number of the column that the calculation is performed for
 * @return Width in pixels of the column including prompt text, value text and inter text spacing
 *            Value limited to a maximum of iMaxColumnWidth
 */
    TInt ColumnWidthInPixels(TInt aColumnNumber) const;

/**
 *
 * Compares the number of rows in each column and returns the maximum 
 *
 * @return The number of rows in the longest column
 */
    TInt MaximumRows() const;
protected:
    TInt iColumns;                           ///<Number of columns in the control
    TInt iMaxColumnWidth;                    ///<Maximum width in pixels of each column
    RPointerArray<CCknColumnItem> iItemArray;///<An array containing prompt/value pairs each with a column number
    TInt iMinimumValueWidth;                 ///<The minimum width in pixels allowed for the value items
    CArrayFixFlat<TInt>* iFixedColumnWidths; ///<The widths of the columns if fixed
    TBool iFixedWidth;                       ///<Whether or not the column widths will change if the text is updated
private:
    TAny* iExtra;
    };

#endif      // CKNCOLUMNEDTEXT_H   
            
// End of File
