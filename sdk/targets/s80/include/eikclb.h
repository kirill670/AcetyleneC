/*
* =============================================================================
*  Name        : eikclb.h
*  Part of     : CKON
*  Interface   : Column Listbox API
*  Description : Column Listbox widget, plus item drawer and editor
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


#ifndef EIKCLB_H
#define EIKCLB_H


// INCLUDES
#include <eiklbi.h>
#include <eiktxlbx.h>
#include <eiklbed.h>


// FORWARD DECLARATIONS
class CColumnListBoxData;


// CLASS DECLARATIONS

/**
*  The <code>CColumnListBoxItemDrawer</code> class provides the item drawer 
*  for Column Listboxes. This Column Listbox item drawer is for use only with 
*  a <code>CEikColumnListBox</code>.
*
*  @lib eikctl.lib
*  @since 6.0
*/
class CColumnListBoxItemDrawer : public CTextListItemDrawer
    {

    public:
    // Constructors and destructor

        /**
        * The object destructor.
        */
        IMPORT_C ~CColumnListBoxItemDrawer();

    // New methods
        
        /**
        * The object constructor.
        *
        * @param aTextListBoxModel A pointer to the Column Listbox model
        * @param aFont A pointer to the font to draw items in
        * @param aColumnData A pointer to the Column Listbox data to be drawn
        * @remarks 
        * @see eiklbm.h for MTextListBoxModel
        */
        IMPORT_C CColumnListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CColumnListBoxData* aColumnData);

        /**
        * Gets a pointer to the column data. Using this method does not 
        * imply transfer of ownership from the Column Listbox.
        *
        * @return a pointer to the column data
        * @remarks
        * @see
        */
        IMPORT_C CColumnListBoxData* ColumnData() const;

        /**
        * Draws a row of text items. The method <code>CColumnListBoxData::Draw()</code> 
        * is used to draw a row for the calling Column Listbox.
        *
        * @param aItemIndex The index of the row to draw
        * @param aItemTextRect The rectangle to draw the item in
        * @param aItemIsCurrent Whether the item is current, that is, 
        *                       the current position of the selector
        * @param aViewIsEmphasized Whether the item is emphasized
        * @param aItemIsSelected Whether the item is selected, for example, 
        *        as with multiple selection
        * @remarks
        * @see
        */
        IMPORT_C void DrawItemText(TInt aItemIndex,const TRect& aItemTextRect,TBool aItemIsCurrent,TBool aViewIsEmphasized, TBool aItemIsSelected) const;

        /**
        * Sets the search string and column to search for in the Column Listbox.
        *
        * @param aSearchString The new search string
        * @param aSearchStrColumn The search column
        * @remarks
        * @see CTextListItemDrawer
        */
        IMPORT_C void SetSearchStringL(const TDesC* aSearchString,const TInt aSearchStrColumn);

        /**
        * Gets the minimum cell size for a cell in a column, as opposed to the 
        * whole row.
        *
        * @return the minimum cell size in the Column Listbox
        * @remarks
        * @see
        */
        IMPORT_C TSize MinimumCellSize() const;

        /**
        * Gets the screen width of a row.
        * 
        * @param aItemIndex Ignored. All rows have the same width
        * @return the width of a row
        * @remarks
        * @see
        */
        IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const; 


    protected:  // Methods

    // New Methods
        
        /**
        * Draws the background rectangle for the current item.
        *
        * @param aRect The background rectangle
        * @remarks Internal use only
        * @internal
        * @see
        */
        void DrawCurrentItemRect(const TRect& aRect) const;


        IMPORT_C TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;
        IMPORT_C TInt MatcherCursorAscent(TInt aCurrentItemIndex) const;

    private: //Methods
        IMPORT_C TAny* Reserved_1();

    };

/**
*  The <code>CEikColumnListBox</code> class provides the Column Listbox 
*  control. The Column Listbox has rows that consist of cells that are grouped 
*  vertically into columns. The columns can contain either text or graphics, 
*  and column widths and fonts can be set explicitly via 
*  <code>CColumnListBoxData</code>. The Column Listbox has an associated control 
*  factory identifier <code>EEikCtColListBox</code>. It has no associated 
*  resource struct.
*
*  @lib eikctl.lib
*  @since 6.0
*/
class CEikColumnListBox : public CEikTextListBox
    {
    public:
    // Constructors and destructor
        /**
        * The default constructor.
        */
        IMPORT_C CEikColumnListBox();

    // New methods
        
        /**
        * Constructs a Column Listbox from a resource file.
        *
        * @param aReader A resource file reader
        * @remarks
        * @see TResourceReader for barsread.h
        */
        IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

        /**
        * Completes construction of a Column Listbox object.
        *
        * @param aParent The parent control of this control
        * @param aFlags Flags for this control. A subset of 
        *        <code>CEikListBox::TFlag</code>, including: 
        *        <code>EMultipleSelection</code>
        *        <code>ENoExtendedSelection</code>
        *        <code>EIncrementalMatching</code>
        *        <code>ENoFirstLetterMatching</code>
        *        <code>EPaintedSelection</code>
        * @param aFont The font for the Column Listbox. If <code>NULL</code>, 
        *        <code>CEikonEnv::NormalFont()</code> is used
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL( CCoeControl* aParent,TInt aFlags=0,const CFont* aFont=NULL );

        /**
        * Creates an item editor.  This allows a user to edit the text
        * in the specified column.
        * 
        * @param aColumn The column in which the editor is to be
        *        created
        * @param aMaxLength The maximum length of the item to be 
        *                                edited, in characters
        * @remarks
        * @see
        */
        IMPORT_C void EditItemL(TInt aColumn, TInt aMaxLength);

        /**
        * Gets the Column Listbox model.  For more information on this,
        * refer to the Listbox base class.
        *
        * @return a pointer to the model used by this Column Listbox
        * @remarks
        * @see eiktxlbm.h for CTextListBoxModel
        */
        IMPORT_C CTextListBoxModel* Model() const;

        /**
        * Gets the object used by this Column Listbox to draw its items.
        * 
        * @return a pointer to the Column Listbox drawer
        * @remarks
        * @see
        */
        IMPORT_C CColumnListBoxItemDrawer* ItemDrawer() const;

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        *
        * @param aColorUseList Not used
        * @remarks
        * @see
        */
        IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        *
        * @param aType The type of resource change
        * @remarks
        * @see
        */
        IMPORT_C void HandleResourceChange(TInt aType);
        
    protected:  // Methods

    // New Methods
        
        /**
        * Creates the object used by this Column Listbox to draw its items.
        */
        IMPORT_C virtual void CreateItemDrawerL();
    };

/**
*  The <code>CEikColumnListBoxEditor</code> class provides the Column Listbox 
*  item editor. This is a Column Listbox item editor meant for use with a 
*  <code>CEikColumnListBox</code>.  It allows a user to inline edit the text 
*  in a cell.
*
*  @lib eikcoctl.lib
*  @since 6.0
*/
class CEikColumnListBoxEditor : public CEikListBoxTextEditor
    {
    public:
    // Constructors and destructor

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikColumnListBoxEditor();

    // New methods
        
        /**
        * The object constructor.
        *
        * @param aModel The Column Listbox model
        * @remarks
        * @see eiklbm.h for MListBoxModel
        */
        IMPORT_C CEikColumnListBoxEditor(MListBoxModel* aModel);

        /**
        * Completes construction of a Column Listbox item editor object.
        *
        * @param aColumn The index of the column
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(TInt aColumn);

        /**
        * Gets the pointer to the current editable item text.
        *
        * @return the pointer to the editable item text
        * @remarks
        * @see
        */
        IMPORT_C TPtrC ItemText();

        /**
        * Updates the Column Listbox model with the new item contents. If 
        * editing is not currently on, this method has no effect. The data
        * model has an increase in memory size if a new item is added.
        *
        * @return <code>ETrue</code> if successful; <code>EFalse</code> if 
        *          editing is not currently on
        * @remarks
        * @see
        */
        IMPORT_C TBool UpdateModelL();

    protected:  // Methods

    // New Methods
        
        /**
        * Gets the index of the column.
        *
        * @return the index of the column
        * @remarks
        * @see
        */
        IMPORT_C TInt Column() const;

    private:     // Data
        TInt iColumnIndex; // refers to Column Listbox column

    };


#endif      // EIKCLB_H   
            
// End of File
