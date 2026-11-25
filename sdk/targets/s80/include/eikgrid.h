/*
* ==============================================================================
*  Name        : eikgrid.h
*  Part of     : CKON / EIKMISC
*  Interface   : Grid API
*  Description : This class implements the grid control
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


#ifndef EIKGRID_H
#define EIKGRID_H

// INCLUDES
#include <eikbctrl.h>
#include <eiksbobs.h>

// FORWARD DECLARATIONS
class TCellRef;
class TRangeRef;
class CEikScrollBarFrame;
class CGridImg;
class CGridLay;

/**
*  This class implements the grid control
*
*  @lib EIKMISC.LIB
*  @since Series90 1.0
*/
class CEikGrid : public CEikBorderedControl, public MEikScrollBarObserver
	{
	public:

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CEikGrid();

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikGrid* NewL(CCoeControl* aControl,CGridLay *aGridLay,CGridImg *aGridImg);

		/**
		* Returns the grid layout object associated with this grid
		* @return A pointer to the grid layout object
		* <BR><B>Type of return value:</B> CGridLay*
		*/
		IMPORT_C CGridLay* GridLay() const;

		/**
		* Returns the grid image object associated with this grid
		* @return A pointer to the grid image object
		* <BR><B>Type of return value:</B> CGridImg*
		*/
		IMPORT_C CGridImg* GridImg() const;

		/**
		* Returns the scroll bar frame object associated with this grid
		* @return A pointer to the scroll bar frame object
		* <BR><B>Type of return value:</B> CEikScrollBarFrame*
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C CEikScrollBarFrame* SBFrame() const;


		/**
		* Draws the specified cell
		* @param aCell The cell to be drawn
		* @return void
		*/
		IMPORT_C void DrawCellL(const TCellRef& aCell) const;

		/**
		* Draw a range of cells as specified by a TRangeRef object
		* @param aRange A TRangeRef object representing the range of cells to be drawn
		* @return void
		*/
		IMPORT_C void DrawRangeL(const TRangeRef& aRange) const;

		/**
		* Draws the currently selected cell
		* @return void
		*/
		IMPORT_C void DrawSelectedL() const;

		/**
		* Returns the cell which the cursor is currently in
		* @return A TCellRef where the cursor is currently positioned
		* <BR><B>Type of return value:</B> TCellRef
		*/
		IMPORT_C TCellRef CursorPos() const;

		/**
		* Sets the cursor position to a specified cell
		* @param aCursorPos The specified cell
		* @return void
		*/
		IMPORT_C void SetCursorPosL(const TCellRef& aCursorPos) const;

		/**
		* Returns the anchor position for the grid
		* @return A TCellRef containing the anchor position
		* <BR><B>Type of return value:</B> TCellRef
		*/
		IMPORT_C TCellRef AnchorPos() const;

		/**
		* Sets the anchor position for the grid
		* @param aAnchorPos The new anchor position
		* @return void
		*/
		IMPORT_C void SetAnchorPosL(const TCellRef& aAnchorPos) const;

		/**
		* Checks whether the datasize and thumb positions of the scrollbars are
		* correct and updates them if not.
		* @return void
		*/
		IMPORT_C virtual void CheckScrollBarPosL() const;

		/**
		* Updates the grid after a zoom operation
		* @return void
		*/
		IMPORT_C virtual void UpdateGridAfterZoomL();

		/**
		* Exposes the specified cell - makes sure it is visible
		* @param aCell The cell to expose
		* @return A TPoint containing the offset of the exposed cell
		* <BR><B>Type of return value:</B> TPoint
		*/
		IMPORT_C TPoint ExposeCellL(const TCellRef& aCell) const;

		/**
		* Exposes a cell and scrolls the grid to its position
		* @param aCell The cell to expose and scroll to
		* @return void
		*/
		IMPORT_C void ExposeCellAndScrollL(const TCellRef& aCell) const;
	public:	// from CCoeControl

		/**
		* Performs the appropriate action on a keypress - See CCoeControl
		* @param aKeyEvent The key event that has happened
		* @param aType The type of event
		* @return A TKeyResponse indicating whether or not the key was consumed (e.g. EKeyWasConsumed)
		* <BR><B>Type of return value:</B> TKeyResponse
		*/
		IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

		/**
		* Returns the input capabilities of the control - See CCoeControl
		* @return A TCoeInputCapabilities object containing the input capabilities of the control
		* <BR><B>Type of return value:</B> TCoeInputCapabilities
		*/
		IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	protected:

		/**
		* Draws the grid.  See CCoeControl
		* @param aRect The size of the grid
		* @return void
		*/
		IMPORT_C virtual void Draw(const TRect& aRect) const;

		/**
		* Handles a pointer event.  See CCoeControl
		* @param aPointerEvent The pointer event to be handled
		* @return void
		*/
		IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		/**
		* Handles the size being changed.  See CCoeControl
		* @return void
		*/
		IMPORT_C virtual void SizeChanged();

		/**
		* Counts the number of component controls.  See CCoeControl.
		* @return The number of component controls
		*/
		IMPORT_C virtual TInt CountComponentControls() const;

		/**
		* Returns a control based on the specified index.  See CCoeControl.
		* @param aIndex The index for the required control
		* @return A control based on the specified index
		*/
		IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
	protected:	// from MEikScrollBarObserver

		/**
		* Handles Scroll events - see MEikScrollBarObserver
		* @param aScrollBar The scroll bar that received the event
		* @param aEventType The event type
		* @return void
		*/
		IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
	protected:

		/**
		* see CCoeControl
		*/
		IMPORT_C void ConstructL(CCoeControl* aControl);

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikGrid(CGridLay *aGridLay,CGridImg *aGridImg);

		/**
		* Returns the next cell to expose
		* @return a TCellRef to the next cell to be exposed
		*/
		IMPORT_C TCellRef CellToExpose() const;
	private:
		IMPORT_C void Dummy1();
		IMPORT_C void Dummy2();
	protected:
		CGridLay* iGridLay;
		CGridImg* iGridImg;
		CEikScrollBarFrame* iSBFrame;
	private:
		TInt iSpare;
	};



#endif	// EIKGRID_H

// End of File
