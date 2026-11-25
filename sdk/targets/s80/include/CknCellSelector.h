/**
* ==============================================================================
*  Name        : ckncellselector.h
*  Part of     : CKON
*  Interface   : Weekday API
*  Description : Widget to provide a weekday selector.
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

#ifndef CKNCELLSELECTOR_H
#define CKNCELLSELECTOR_H


//  INCLUDES
#include <CknBCTRL.H>
#include <barsread.h>

/**
 * The <code>CCknSkinBase</code> implements the skin manager that is used to 
 * access the skin.
 *
 * @lib skin.lib
 * @since Series90 1.0
 */
class CCknSkinBase;

// CLASS DECLARATION

/**
 * The <code>CCknCellSelector</code> class displays a set of cells that
 * represent days of the week. One or more cells may be selected.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknCellSelector : public CCknBorderedControl
    {
    public:  // Data types
        /** The anonymous enumeration provides the cell's state 
		 * (selected or unselected) which is used as an argument in the 
		 * <code>SetClicked()</code> method. */
        enum {
            /** Sets the cell to the selected state */
            EClickSet = 0x1,
            /** Clears the cell state */
            EClickClear = 0x2,
            /** Toggles the cell state */
            EClickInverse = 0x4,
            /** Only the particular cell can be selected. All others are 
             *  cleared */
            EClickSetExclusive = 0x8
            };

        /** The anonymous enumeration defines the separator between names 
		 *  when defining cell names. */
        enum {
            /** defines the separator */
            ECellTextSeparator = 0x9
            };
        
        /** The anonymous enumeration defines the maximum length of day name 
		 *  (not used) and number of cell names or days in a week. */
        enum {
		    /** maximum length of day name (not used) */
			ECellDayNameMaxLen = 2, 
		    /** number of cell names or days in a week */				
			ECellDayNameNoOfDays = 7
            };

    private:  // Data types
        enum {
            ECellSelectorMaxElements=sizeof(TUint32)*8/*bit*/,
            ECellSelectorMinBoxDistance=0,
            ECellSelectorMaxBoxDistance=20,
            ECellSelectorMinBoxWidth=12,
            ECellSelectorMaxBoxWidth=200,
            ECellSelectorMinBoxHeight=12,
            ECellSelectorMaxBoxHeight=100
            };

    public:  // Methods

    // Constructors and destructor


       /**
        * Starts the two-phase object construction. Static constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C static CCknCellSelector* NewL();

       /**
        * The object destructor.
        */
        IMPORT_C ~CCknCellSelector();


    // New methods

       /**
        * Checks if the cell state is selected.
        *
        * @param aPos Position of the cell 
        * @return <code>ETrue</code> if selected, otherwise <code>EFalse</code>
        * @remarks
        * @see      
        */
        IMPORT_C TBool IsClicked(TInt aPos) const;

       /**
        * Sets cell state to selected or unselected
        *
        * @param aPos Position of the cell 
        * @param aClicked State of the cell; one of the enumerations
        * @remarks
        * @see
        */
        IMPORT_C void SetClicked(TInt aPos, TInt  aClicked);

       /**
        * Sets the current cell.
        *
        * @param aCurrenCell The cell to set as current
        * @remarks The particular cell will be highlighted
        * @see
        */
        IMPORT_C void SetCurrentCell(TInt  aCurrenCell);

       /**
        * Returns the current cell.
        *
        * @return the current cell
        * @remarks
        * @see
        */
        IMPORT_C TInt CurrentCell() const;

       /**
        * Sets the control data - takes care of locale settings in weekdays
        * mode.
        *
        * @param aData Data (bit) area
        * @remarks If a bit is set, the corresponding cell is in selected state
        * @see
        */
        IMPORT_C void SetData(TUint32 aData);

       /**
        * Gets the control data - takes care of locale settings in weekdays
        * mode.
        *
        * @return data (bit) area
        * @remarks If a bit is set, the corresponding cell is in selected state
        * @see
        */
        IMPORT_C TUint32 Data() const;

       /**
        * Sets the font to use.
        *
        * @param aFont The font to use
        * @remarks
        * @see
        */
        IMPORT_C void SetFont(const CFont* aFont);

       /**
        * Set language dependent day names - day names separated by tabs.
        *
        * @param aNames The day names  
        * @remarks 
        * @see
        */
        IMPORT_C void SetCellNamesL(TDesC& aNames);

    protected:  // Methods

    // New Methods

        /**
        * C++ default constructor.
        */
        IMPORT_C CCknCellSelector();

    // Methods from base classes

        /**
        * From CCoeControl
        * Handle a pointer event
        *
        * @param aPointerEvent the event to handle
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);


        /**
        * Responds to changes of focus. This method is called when a control 
        * gains or loses focus as a result of a call to <code>SetFocus()</code>. 
        * A typical use of this method is to change the appearance of the 
        * control to indicate whether or not it has focus. 
        *
        * @param aDrawNow Contains the value that was passed to it by 
        *        <code>SetFocus()</code> 
        * @remarks 
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    private: //Methods

        /**
        * The Draw method from CCoeControl.
        * Draws the matrix.
        *
        * @param aRect the rect to draw. Unused.
        */
        void Draw(const TRect& /*aRect*/) const;

        /**
        * construct this control from the spectified resource reader
        *
        * @param aResourceReader The resource reader to use
        */
        void ConstructFromResourceL(TResourceReader& aResourceReader);

        /**
        * Returns the minimum size of the entire matrix control.
        *
        * @return Minimum size of control.
        */
        TSize MinimumSize();

        /**
        * Set the day names
        */
        void SetDayNamesAndEnsureMinimumCellSize();

        /**
        * Activates the context and Draws all cells
        */
        void DrawCells() const;

        /**
        * Draws all cells with passed context.
        *
        * @param aGC the graphics context to use
        */
        void DrawCells(CWindowGc& aGC) const;

        /**
        * Calculates the size of the text in the current font,
        * used to ensure minimum size for cells.
        *
        * @param aText the text whose width is calculated
        */
        TSize GetTextSize(TDesC& aText);

    private:    // Data

        /** Control flags */
        TInt    iFlags;
        /** Cell captions - tabulator separated */
        HBufC*  iText;
        /** week start day (TLocale!) */
        TDay    iStartDay;
        /** cell text font */
        const CFont* iFont;
        /** distance between cells */
        TInt    iCellDistance;
        /** size of a single cell */
        TSize   iCellSize;
        /** current selected cell */
        TInt    iCurrentCell;
        /** number of cells */
        TInt    iCellTotal;
        /** data (bit) area */
        TUint32 iData;
        TBool iMbmDuplicated;
        TAny* iReserved;
    };

#endif      // CKNCELLSELECTOR_H

// End of File
