// GRDSTD.INL
//
// Copyright (c) Nokia Corporation 2001-2004. All rights reserved.
//

// CGridLay

/**
* Sets the specified grid table object
*
* @param  "const MGridTable* aGridTable"
*			The grid table object
*/
inline void CGridLay::SetGridTable(const MGridTable* aGridTable)
	{ iGridTable = aGridTable; }

/**
* Gets the range of cells that are currently visible
*
* @returns	"TRangeRef"
*			The visible cell range. Note that the TRangeRef::iFrom member is the cell 
*			that is visible at the top of the window, and the TRangeRef::iTo member 
*			is the cell that is partially visible at the bottom right of the window
*/
inline TRangeRef CGridLay::VisibleRange() const
	{ return iVisibleRange; }

/**
* Gets the range of cells that form the grid titles
*
* @returns	"TRangeRef"
*			The range of cells that form the grid titles
*/
inline TRangeRef CGridLay::TitleRange() const
	{ return iTitleRange; }

/**
* Gets the range of cells that defines the grid boundary
*
* @returns	"TRangeRef"
*			The range of cells that defines the grid boundary
*/
inline TRangeRef CGridLay::GridRange() const
	{ return iGridRange; }

/**
* Tests whether side grid labels are printed
*
* @returns	"TBool"
*			True, if the side labels are printed; false, otherwise
*/
inline TBool CGridLay::IsSideLabels() const
	{ return (iFlags&EIsSideLabels); }

/**
* Tests whether top labels are printed
*
* @returns	"TBool"
*			True, if the top labels are printed; false, otherwise
*/
inline TBool CGridLay::IsTopLabels() const
	{ return (iFlags&EIsTopLabels); }

/**
* Tests whether vertical grid lines are to be drawn
*
* @returns	"TBool"
*			True, if vertical grid lines are to be drawn; false, otherwise
*/
inline TBool CGridLay::IsVerticalGridLines() const
	{ return (iFlags&EIsVerticalGridLines); }

/**
* Tests whether horizontal grid lines are to be drawn
*
* @returns	"TBool"
*			True, if horizontal grid lines are to be drawn; false, otherwise
*/
inline TBool CGridLay::IsHorizontalGridLines() const
	{ return (iFlags&EIsHorizontalGridLines); }

/**
* Tests whether label separators are to be drawn
*
* @returns	"TBool"
*			True, if label separators are to be drawn; false, otherwise
*/
inline TBool CGridLay::IsGridLabelSeparators() const
	{ return (iFlags&EIsGridLabelSeparators); }

/**
* Tests whether column bursting is permitted.
* 
* Column bursting occurs when the contents of a cell are too wide; 
* adjacent cells are then overwritten, provided they are empty
*
* @returns	"TBool"
*			True, if column bursting is permitted; false, otherwise
*/
inline TBool CGridLay::IsColumnBursting() const
	{ return (iFlags&EIsColumnBursting); }

/**
* Tests whether the cursor is visible
*
* @returns	"TBool"
*			True, if the cursor is visible; false, otherwise
*/
inline TBool CGridLay::IsCursorVisible() const
	{ return (iFlags&EIsCursorVisible); }

/**
* Tests whether selected cells are highlighted
*
* @returns	"TBool"
*			True, if selected cells are highlighted; false, otherwise
*/
inline TBool CGridLay::IsHighlightVisible() const
	{ return (iFlags&EIsHighlightVisible); }

/**
* Tests whether rows are permanently selected
*
* @returns	"TBool"
*			True, if rows are permanently selected; false, otherwise
*/
inline TBool CGridLay::IsRowPermanentlySelected() const
	{ return (iFlags&EIsRowPermanentlySelected); }

/**
* Tests whether the grid has both horizontal and vertical title lines
*
* @returns	"TBool"
*			True, if the grid has both a horizontal and vertical title line; false, otherwise
*/
inline TBool CGridLay::IsTitleLines() const
	{ return (iFlags&(EIsHorizontalTitleLine|EIsVerticalTitleLine)); }

/**
* Tests whether the grid has a horizontal title line
*
* @returns	"TBool"
*			True, if the grid is to have a horizontal title line; false otherwise
*/
inline TBool CGridLay::IsHorizontalTitleLine() const
	{ return (iFlags&EIsHorizontalTitleLine); }

/**
* Tests whether the grid has a vertical title line
*
* @returns	"TBool"
*			True, if the grid is to have a vertical title line; false otherwise
*/
inline TBool CGridLay::IsVerticalTitleLine() const
	{ return (iFlags&EIsVerticalTitleLine); }

/**
* Tests whether the grid has indefinite row boundaries
*
* @returns	"TBool"
*			True, if the grid has indefinite row boundaries; false, otherwise
*/
inline TBool CGridLay::IsIndefiniteRowBoundaries() const
	{ return (iFlags&EIsIndefiniteRowBoundaries); }

/**
* Tests whether all the rows have the same height
*
* @returns	"TBool"
*			True, if all rows have the same height; false, otherwise
*/
inline TBool CGridLay::IsUniformRowHeight() const
	{ return (iFlags&EIsUniformRowHeight); }

/**
* Tests whether all columns have the same width
*
* @returns	"TBool"
*			True, if all columns have the same width; false, otherwise
*/
inline TBool CGridLay::IsUniformColumnWidth() const
	{ return (iFlags&EIsUniformColumnWidth); }

/**
* Tests whether a drag operation on the boundary between two columns is permitted
*
* @returns	"TBool"
*			True, if a drag operation on a column boundary is permitted; false otherwise
*/
inline TBool CGridLay::IsTopLabelDragDisabled() const
	{ return (iFlags&EIsTopLabelDragDisabled); }

/**
* Tests whether a drag operation on the boundary between two rows is permitted
*
* @returns	"TBool"
*			True, if a drag operation on a row boundary is permitted; false otherwise
*/
inline TBool CGridLay::IsSideLabelDragDisabled() const
	{ return (iFlags&EIsSideLabelDragDisabled); }

/**
* Tests whether labels are printed
*
* @returns	"TBool"
*			True, if labels are printed; false, otherwise
*/
inline TBool CGridLay::IsPrintedLabels() const
	{ return (iFlags&EIsPrintedLabels); }

/**
* Tests whether grid lines are printed
*
* @returns	"TBool"
*			True, if grid lines are printed; false, otherwise
*/
inline TBool CGridLay::IsPrintedGridLines() const
	{ return (iFlags&EIsPrintedGridLines); }

/**
* Checks if the last visible row is fully visible
*
* @returns	"TBool"
*			Returns ETrue if the last visible row is fully visible
*/
inline TBool CGridLay::IsVisibleToRowFullyVisible() const
	{ return (iFlags&EIsVisibleToRowFullyVisible); }

/**
* Checks if the last visible column is fully visible
*
* @returns	"TBool"
*			Returns ETrue if the last visible column is fully visible
*/
inline TBool CGridLay::IsVisibleToColumnFullyVisible() const
	{ return (iFlags&EIsVisibleToColumnFullyVisible); }

/**
* Tests whether encroaching cell borders are permitted.
* 
* Encroaching cell borders are where cell borders wider than one pixel are 
* drawn inside the cell, as opposed to outside
*
* @returns	"TBool"
*			True, if encroaching cells borders are permitted; false, otherwise
*/
inline TBool CGridLay::IsEncroachingCellBorders() const
	{ return (iFlags&EIsEncroachingCellBorders); }

/**
* Tests whether row selection is disabled
*
* @returns	"TBool"
*			True, if row selection is disabled; false, otherwise
*/
inline TBool CGridLay::IsRowSelectionDisabled() const
	{ return (iFlags&EIsRowSelectionDisabled); }

/**
* Tests whether column selection is disabled
*
* @returns	"TBool"
*			True, if column selection is disabled; false, otherwise
*/
inline TBool CGridLay::IsColumnSelectionDisabled() const
	{ return (iFlags&EIsColumnSelectionDisabled); }

/**
* Tests whether automatic clearing of grid cells is done.
* 
* Automatic clearing of grid cells is where all cells are cleared on redraw, 
* in case drawing the contents doesn't guarantee to write to every pixel 
* (the usual way of doing flicker-free redraws).
*
* @returns	"TBool"
*			True, if automatic clearing of grid cells is done; false, otherwise
*/
inline TBool CGridLay::IsAutoClearGridCells() const
	{ return (iFlags&EIsAutoClearGridCells); }

/**
* Tests whether lines marking page breaks are hidden
*
* @returns	"TBool"
*			True, if lines marking page breaks are hidden; false, otherwise
*/
inline TBool CGridLay::IsPageBreakLinesHidden() const
	{ return (iFlags&EIsPageBreakLinesHidden); }

/**
* Tests whether any change has occurred to the grid layout.
* 
* Such changes include:
* 
*		- alterations to height of a row or the width of a column
* 
*		- additions or deletions of rows or columns
* 
*		- changes to the visibility of grid lines
* 
* Note that this list is not exhaustive
* 
*
* @returns	"TBool"
*			True, if the grid layout has changed; false, otherwise
*/
inline TBool CGridLay::HasChanged() const
	{ return iHasChanged; }

/**
* Sets whether any change has occurred to the grid layout
*
* @param  "TBool aHasChanged"
*			ETrue, if any change has occurred to the grid layout; EFalse, otherwise
*/
inline void CGridLay::SetHasChanged(TBool aHasChanged)
	{ iHasChanged=aHasChanged; }

/**
* Defines the colour that the edges of the grid beyond the grid range are to have.
* 
* If not changed by this function, the default colour is white
*
* @param  "TRgb aColor"
*			The colour value
*/
inline void CGridLay::SetGridEdgeColor(TRgb aColor)
	{ iGridEdgeColor=aColor; }

/**
* Tests whether the grid has been paginated
*
* @returns	"TBool"
*			True, if the grid has been paginated; false, otherwise
*/
inline TBool CGridLay::IsPaginated() const
	{ return (iFlags&EIsPaginated); }

/**
* Sets the range of cells that are visible for printing
*
* @param  "const TRangeRef& aPrintRange"
*			The cell range
*/
inline void CGridLay::SetPrintRange(const TRangeRef& aPrintRange) 
	{ iVisibleRange=aPrintRange; }

/**
* Gets the size of a page
*
* @returns	"TSize"
*			The size of a page, in twips
*/
inline TSize CGridLay::PageSizeInTwips() const
	{ return iPageSizeInTwips; }

/**
* Tests whether automatic pagination is in effect
*
* @returns	"TBool"
*			True, if automatic pagination is in effect, false, otherwise
*/
inline TBool CGridLay::IsAutoPagination() const
	{ return (iFlags&EIsAutoPagination); }

// CGridLabelImg

/**
* Sets the graphics device map to be used
*
* @param  "MGraphicsDeviceMap* aGraphicsDeviceMap"
*			The graphics device map, an interface for mapping between twips and 
*			device-specific units
*/
inline void CGridLabelImg::SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap)
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

/**
* Gets the current font spec
*
* @returns	"TFontSpec"
*			Font spec
*/
inline TFontSpec CGridLabelImg::FontSpec() const
	{
	return iFontSpec;
	}

/**
* Gets the collection of colours used to draw the grid
*
* @param  "const TGridColors& aGridColors"
*			The grid colour definitions
*/
inline void CGridLabelImg::SetGridColors(const TGridColors& aGridColors)
	{
	iGridColors = aGridColors;
	}

// CGridCellImg

/**
* Gets the bursting column offset
*
* @returns	"TInt"
*			The burst column offset
*/
inline TInt CGridCellImg::BurstColOffset() const
	{ return iBurstColOffset; }

/**
* Gets the left hand bursting value
*
* @returns	"TInt"
*			The burst value
*/
inline TInt CGridCellImg::BurstLeft() const
	{ return iBurstLeft; }

/**
* Gets the right hand bursting value
*
* @returns	"inline TInt"
*			The burst value
*/
inline TInt CGridCellImg::BurstRight() const
	{ return iBurstRight; }

/**
* Tests whether horizontal grid lines are drawn.
* 
* This function is set by the CGridImg object and allows classes derived from 
* CGridCellImg to modify or restrict the area into which they draw
* 
*
* @returns	"TBool"
*			True, if horizontal grid lines are drawn; false, othe
*/
inline TBool CGridCellImg::IsHorizontalGridLines() const
	{ return iGridLineFlags&EIsHorizontalGridLines; }

/**
* Tests whether vertical grid lines are drawn.
* 
* This function is set by the CGridImg object and allows classes derived from 
* CGridCellImg to modify or restrict the area into which they draw
* 
*
* @returns	"TBool"
*			True, if vertical grid lines are drawn; false, otherwise
*/
inline TBool CGridCellImg::IsVerticalGridLines() const
	{ return iGridLineFlags&EIsVerticalGridLines; }

/**
* Sets the colours to be used when drawing
*
* @param  "const TGridColors& aGridColors"
*			The object containing the grid colours specification
*/
inline void CGridCellImg::SetGridColors(const TGridColors& aGridColors)
	{
	iGridColors = aGridColors;
	}

// CGridImg

/**
* Sets the specified grid layout object
*
* @param  "CGridLay* aGridLay"
*			A pointer to the object that controls the layout of rows and columns
*/
inline void CGridImgBC::SetGridLay(CGridLay* aGridLay)
	{ iGridLay = aGridLay; }

/**
* Sets the specified window
*
* @param  "RWindow * aWin"
*			A pointer to the currently active window
*/
inline void CGridImgBC::SetWindow(RWindow *aWin)
	{ iWin = aWin; }

////////////////////////->
//inline void CGridImgBC::SetGridLabelImg(CGridLabelImg *aGridLabelImg)
//	{ iGridLabelImg =  aGridLabelImg; }
////////////////////////->

/**
* Sets the cursor moved call-back object.
* 
* The call-back object encapsulates the implementation of a call-back function 
* that is called whenever there is a change to the cursor position
* 
*
* @param  "MGridCursorMoveCallBack * aCursorMoveCallBack"
*			A pointer to the callback object
*/
inline void CGridImgBC::SetCursorMoveCallBack(MGridCursorMoveCallBack *aCursorMoveCallBack)
	{ iCursorMoveCallBack = aCursorMoveCallBack; }

/**
* Gets the cursor moved call-back object.
* 
* The call-back object encapsulates the implementation of a call-back function 
* that is called whenever there is a change to the cursor position
* 
*
* @returns	"MGridCursorMoveCallBack*"
*			Pointer to the current call-back object.
*/
inline MGridCursorMoveCallBack* CGridImgBC::GetCursorMoveCallBack()
	{ return iCursorMoveCallBack; }

/**
* Gets the currently selected region
*
* @returns	"const CGridCellRegion*"
*			A pointer to the selected region object.
*/
inline const CGridCellRegion* CGridImgBC::Selected() const
	{ return iSelected; }

/**
* Gets the the object that is used to draw a cell label
*
* @returns	"const CGridLabelImg*"
*			A pointer to the object that is used to draw a cell label
*/
inline const CGridLabelImg* CGridImgBC::GridLabelImg() const
	{ return iGridLabelImg; }

/**
* Gets the current cursor position
*
* @returns	"TCellRef"
*			Current cursor position
*/
inline TCellRef CGridImgBC::CursorPos() const
	{ return iCursorPos; }

/**
* Gets the cursor anchor position. 
* 
* This is the cell reference of the position that the cursor must return to after 
* a series of selected movements have been made
* 
*
* @returns	"TCellRef"
*			The cell reference of the cursor anchor position
*/
inline TCellRef CGridImgBC::AnchorPos() const
	{ return iAnchorPos; }

/**
* Gets the new position of the cursor
*
* @returns	"TCellRef"
*			The cell reference of the new cursor position
*/
inline TCellRef CGridImgBC::NewCursorPos() const
	{ return iNewCursorPos; }

/**
* Gets the rectangle containing the grid
*
* @returns	"TRect"
*			The rectangle containing the grid
*/
inline TRect CGridImgBC::GridRect() const
	{ return iGridRect; }

/**
* Gets the position of the title.
* 
* This is the point at the top left of the grid excluding the labels
* 
*
* @returns	"TPoint"
*			The position of the title
*/
inline TPoint CGridImgBC::TitlePoint() const
// Returns the point of the top left cell in the grid;
	{ return iTitlePoint; }

/**
* Gets the position at which the visible range starts
*
* @returns	"TPoint"
*			The position at which the visible range starts
*/
inline TPoint CGridImgBC::MainPoint() const
// Returns the most commonly used point in the grid (usually same as TitlePoint()).
	{ return iMainPoint; }

/**
* Gets the rectangle that corresponds to the visible range
*
* @returns	"TRect"
*			The rectangle that corresponds to the visible range
*/
inline TRect CGridImgBC::MainRect() const
	{ return TRect(iMainPoint,iGridRect.iBr); }
