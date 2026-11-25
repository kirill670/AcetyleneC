/*
* ==============================================================================
*  Name        : GrdStd.h
*  Part of     : Grid
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Standard interface for GRID module
*  Version     : ?Version
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef GRDSTD_H
#define GRDSTD_H

//  INCLUDES
#include <e32std.h>
#include <gdi.h>
#include <grdcells.h>
#include <grddef.h>
#include <grdimgBC.h>


// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;
class CStreamStore;
class CGridImg;
class CSparseMap;
class RWindow;
class CWindowGc;

// CLASS DECLARATION


/* \class MGridTable
*    \brief An interface that can be implemented to provide row and column information.
* 
* Note that for grids that have indefinite row boundaries, an implementation is 
* mandatory.
* 
* A concrete implementation is passed to a CGridLay object through its 
* CGridLay::ConstructL() functions or its CGridLay::SetGridTable() function
* 
*  @lib grid
*  @since ?Series90_version
*/
class MGridTable
	{
	public:		// DATA TYPES
		enum
			{
			EDefaultRowExtent=20,EDefaultColumnExtent=20
			};

    public: // New functions
		IMPORT_C virtual TBool RequestRow(TInt aRow,TInt& aReturnRow) const;//If used should be derived from
		IMPORT_C virtual TInt RowExtent() const;
		IMPORT_C virtual TInt ColumnExtent() const;
	};


////////////////////////->
/* \class TGridColors
*    \brief	The grid colour specification.
*
*				An object of this type encapsulates the colours to be used when drawing a grid cell
* 
*  @lib grid
*  @since ?Series90_version
*/
class TGridColors
	{
	public:

		IMPORT_C TGridColors();
		IMPORT_C TGridColors(TRgb aForeground, TRgb aBackground, TRgb aLines, TRgb aLabelSeparators);

    public:     // Data
		TRgb iForeground;			//!< The foreground colour
		TRgb iBackground;			//!< The background colour
		TRgb iLines;				//!< The colour of lines
		TRgb iLabelSeparators;		//!< The colour of label separators
	};
////////////////////////->


/* \class CGridLay
*    \brief Handles the layout of a grid, and controls how columns, rows and selections appear
* 
*  @lib grid
*  @since ?Series90_version
*/
class CGridLay : public CBase
	{
		// Friend classes
		friend class CGridImgBC;

	public:	// DATA TYPES
		enum TPageOrder
			{ ERightThenDown,EDownThenRight};
		enum TFixGridRange
			{ EFixGridRange,EAdjustGridRange};

	public:	// New functions

		IMPORT_C CGridLay(MGraphicsDeviceMap* aGraphicsDeviceMap);
		IMPORT_C void ConstructL(CGridLay* aGridLay,CGridImg* aGridImg);//Constructs Partial Copy
		IMPORT_C void ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,TInt aNoOfRows,TInt aNoOfCols);
		IMPORT_C void ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,TInt aNoOfCols);
		IMPORT_C virtual ~CGridLay();

		IMPORT_C TPoint PageScroll(TMoveDirectionAndAmount aPageScroll);
		IMPORT_C TPoint ExposeCell(const TCellRef &aCell);
		IMPORT_C TPoint ExposeCellToTopLeft(const TCellRef &aCell);

		IMPORT_C void SetGridImgL(CGridImg* aGridImg);
		inline void SetGridTable(const MGridTable* aGridTable);
		inline TRangeRef VisibleRange() const;
		IMPORT_C void SetVisibleRange(const TCellRef& aTopLeftCell);
		inline TRangeRef TitleRange() const;
		inline TRangeRef GridRange() const;
		IMPORT_C void SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap);
		IMPORT_C void SetGridToDefault();

		IMPORT_C TInt ColumnWidthInTwips(TInt aCol) const;
		IMPORT_C void SetColumnWidthInTwipsL(TInt aCol,TInt aWidthInTwips);
		IMPORT_C TInt SetColumnWidthInTwipsL(TInt aStartCol,TInt aEndCol,TInt aWidthInTwips);
		IMPORT_C TInt DefaultColumnWidthInTwips() const;
		IMPORT_C void SetDefaultColumnWidthInTwips(TInt aWidthInTwips);
		IMPORT_C void SetColumnWidthsToDefault();
		IMPORT_C TInt MinColumnWidthInPixels() const;
		IMPORT_C void SetMinColumnWidthInPixels(TInt aWidthInPixels);
		IMPORT_C TInt ColumnWidthOfSelectedInTwips() const;
		IMPORT_C void SetColumnWidthOfSelectedInTwipsL(TInt aWidthInTwips);
		IMPORT_C TInt RowHeightInTwips(TInt aRow) const;
		IMPORT_C void SetRowHeightInTwipsL(TInt aRow,TInt aHeightInTwips);
		IMPORT_C TInt SetRowHeightInTwipsL(TInt aStartRow,TInt aEndRow,TInt aHeightInTwips);
		IMPORT_C TInt DefaultRowHeightInTwips() const;
		IMPORT_C void SetDefaultRowHeightInTwips(TInt aHeightInTwips);
		IMPORT_C void SetRowHeightsToDefault();
		IMPORT_C TInt MinRowHeightInPixels() const;
		IMPORT_C void SetMinRowHeightInPixels(TInt aHeightInPixels);
		IMPORT_C TInt RowHeightOfSelectedInTwips() const;
		IMPORT_C void SetRowHeightOfSelectedInTwipsL(TInt aHeightInTwips);
		IMPORT_C void RecalcPixelSparseMaps();
		IMPORT_C void InsertDeleteColumns(TInt aStartCol,TInt aNoOfCols,
			TFixGridRange aFixGridRange=EFixGridRange);
		IMPORT_C void InsertDeleteRows(TInt aStartRow,TInt aNoOfRows,
			TFixGridRange aFixGridRange=EFixGridRange);

		inline TBool IsSideLabels() const;
		IMPORT_C void SetSideLabels(TBool aState);
		inline TBool IsTopLabels() const;
		IMPORT_C void SetTopLabels(TBool aState);
		inline TBool IsVerticalGridLines() const;
		IMPORT_C void SetVerticalGridLines(TBool aState);
		inline TBool IsHorizontalGridLines() const;
		IMPORT_C void SetHorizontalGridLines(TBool aState);
		inline TBool IsGridLabelSeparators() const;
		IMPORT_C void SetGridLabelSeparators(TBool aState);
		inline TBool IsColumnBursting() const;
		IMPORT_C void SetColumnBursting(TBool aState);
		inline TBool IsCursorVisible() const;
		IMPORT_C void SetCursorVisible(TBool aVisible);
		inline TBool IsHighlightVisible() const;
		IMPORT_C void SetHighlightVisible(TBool aVisible);
		inline TBool IsRowPermanentlySelected() const;
		IMPORT_C void SetRowPermanentlySelectedL(TBool aState);
		inline TBool IsTitleLines() const;
		inline TBool IsHorizontalTitleLine() const;
		inline TBool IsVerticalTitleLine() const;
		IMPORT_C void SetTitleLinesL(TBool aState);
		IMPORT_C void SetTitleLinesL(const TCellRef& aCellRef);
		IMPORT_C void ToggleTitleLinesL();
		inline TBool IsIndefiniteRowBoundaries() const;
		inline TBool IsUniformRowHeight() const;
		IMPORT_C void SetUniformRowHeight(TBool aState);
		inline TBool IsUniformColumnWidth() const;
		IMPORT_C void SetUniformColumnWidth(TBool aState);
		inline TBool IsTopLabelDragDisabled() const;
		IMPORT_C void SetTopLabelDragDisabled(TBool aState);
		inline TBool IsSideLabelDragDisabled() const;
		IMPORT_C void SetSideLabelDragDisabled(TBool aState);
		inline TBool IsPrintedLabels() const;
		IMPORT_C void SetPrintedLabels(TBool aState);
		inline TBool IsPrintedGridLines() const;
		IMPORT_C void SetPrintedGridLines(TBool aState);
		inline TBool IsEncroachingCellBorders() const;
		IMPORT_C void SetEncroachingCellBorders(TBool aState);
		inline TBool IsRowSelectionDisabled() const;
		IMPORT_C void SetRowSelectionDisabled(TBool aState);
		inline TBool IsColumnSelectionDisabled() const;
		IMPORT_C void SetColumnSelectionDisabled(TBool aState);
		inline TBool IsAutoClearGridCells() const;
		IMPORT_C void SetAutoClearGridCells(TBool aState);
		inline TBool IsPageBreakLinesHidden() const;
		IMPORT_C void SetPageBreakLinesHidden(TBool aState);
		inline TBool HasChanged() const;
		inline void SetHasChanged(TBool aHasChanged);
		inline void SetGridEdgeColor(TRgb aColor);

		IMPORT_C TInt MinVisibleFromRow() const;
		IMPORT_C TInt MinVisibleFromColumn() const;
		IMPORT_C void ResetVisibleToRow();
		IMPORT_C void ResetVisibleToColumn();
		IMPORT_C void ResetVisibleToCell();
		IMPORT_C TInt RowExtent() const;
		IMPORT_C TInt ColumnExtent() const;

		IMPORT_C TInt RowToYVal(TInt aRow) const;
		IMPORT_C TInt RowToYVal(TInt aStartRow,TInt aEndRow) const;
		IMPORT_C TInt VisibleRowToYVal(TInt aRow) const;
		IMPORT_C TInt TitleRowToYVal(TInt aTitleRow) const;
		IMPORT_C TInt ColumnToXVal(TInt aCol) const;
		IMPORT_C TInt ColumnToXVal(TInt aStartCol,TInt aEndCol) const;
		IMPORT_C TInt VisibleColumnToXVal(TInt aCol) const;
		IMPORT_C TInt TitleColumnToXVal(TInt aTitleCol) const;
		IMPORT_C TInt YValToRow(TInt aYVal) const;
		IMPORT_C TInt YValToRow(TInt aStartRow,TInt aDisp) const;
		IMPORT_C TInt YValToTitleRow(TInt aYVal) const;
		IMPORT_C TInt XValToColumn(TInt aXVal) const;
		IMPORT_C TInt XValToColumn(TInt aStartCol,TInt aDisp) const;
		IMPORT_C TInt XValToTitleColumn(TInt aXVal) const;
		IMPORT_C TCellRef PointToCell(const TPoint &aPoint) const;
		IMPORT_C TCellRef PointToCell(const TCellRef &aStartCell,const TPoint &aPointDisp) const;
		IMPORT_C TPoint CellToPoint(const TCellRef &aCell) const;
		IMPORT_C TPoint CellToPoint(const TCellRef &aStartCell,const TCellRef &aEndCell) const;
		IMPORT_C TPoint TitleCellToPoint(const TCellRef& aTitleCell) const;
		IMPORT_C TRect CellToRect(const TCellRef& aCell) const;
		IMPORT_C TInt YValToNearestRow(TInt aStartRow,TInt aDisp) const;
		IMPORT_C TInt XValToNearestColumn(TInt aStartCol,TInt aDisp) const;
		IMPORT_C TSize TopLeftTitleRangeSize() const;

		IMPORT_C void PaginateL();
		IMPORT_C void ClearPagination();
		IMPORT_C void NotifyPaginationOutOfDateL();
		inline TBool IsPaginated() const;
		IMPORT_C TRangeRef PageToRange(TInt aPageNo,TPageOrder aPageOrder) const;
		inline void SetPrintRange(const TRangeRef& aPrintRange);
		IMPORT_C TInt NoOfPages() const;
		IMPORT_C void SetPageSizeInTwipsL(const TSize& aPageSize);
		inline TSize PageSizeInTwips() const;
		inline TBool IsAutoPagination() const;
		IMPORT_C void SetAutoPagination(TBool aState);
		IMPORT_C TBool IsHardRowPageBreak(TInt aRow) const;
		IMPORT_C TBool IsHardColumnPageBreak(TInt aCol) const;
		IMPORT_C void SetHardRowPageBreakL(TInt aRow);
		IMPORT_C void ClearHardRowPageBreakL(TInt aRow);
		IMPORT_C void SetHardColumnPageBreakL(TInt aCol);
		IMPORT_C void ClearHardColumnPageBreakL(TInt aCol);
		IMPORT_C void ClearAllHardPageBreaksL();

		IMPORT_C void ExternalizeL(RWriteStream &aStream) const;
		IMPORT_C void InternalizeL(RReadStream &aStream);
		IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
		IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
	////////////////////////->
	//	Setting the grid colors
		IMPORT_C void SetGridColors(TGridColors aColors);
	//	Getting the grid colors
		IMPORT_C const TGridColors& GridColors() const;
	////////////////////////->

	private:	// New functions

		void SetIndefiniteRowBoundaries(TBool aState);
		inline TBool IsVisibleToRowFullyVisible() const;
		void SetVisibleToRowFullyVisible(TBool aState);
		inline TBool IsVisibleToColumnFullyVisible() const;
		void SetVisibleToColumnFullyVisible(TBool aState);
		TInt ColumnWidthInPixels(TInt aCol) const;
		void SetColumnWidthInPixelsL(TInt aCol,TInt aWidthInPixels);
		void PreCheckColumnWidthChange(TInt aCol,TBool aNonZeroWidth);
		void PostCheckColumnWidthChange(TInt aCol,TBool aNonZeroWidth);
		TInt DefaultColumnWidthInPixels() const;
		void SetDefaultColumnWidthInPixels(TInt aWidthInPixels);
		TInt RowHeightInPixels(TInt aRow) const;
		void SetRowHeightInPixelsL(TInt aRow,TInt aHeightInPixels);
		void PreCheckRowHeightChange(TInt aRow,TBool aNonZeroHeight);
		void PostCheckRowHeightChange(TInt aRow,TBool aNonZeroHeight);
		TInt DefaultRowHeightInPixels() const;
		void SetDefaultRowHeightInPixels(TInt aHeightInPixels);
		TPoint CalcOffsetBetweenCells(const TCellRef& aCell1,const TCellRef& aCell2) const;
		TBool LimitRow(TInt& aRow) const;
		TBool LimitColumn(TInt &aColumn) const;
		void LimitRow(TInt& aRow,TInt aLowerLimit,TInt aUpperLimit) const;
		void LimitColumn(TInt& aCol,TInt aLowerLimit,TInt aUpperLimit) const;
		TBool LimitCell(TCellRef& aCell) const;
		void LimitRowToVisible(TInt& aRow) const;
		void LimitColumnToVisible(TInt& aCol) const;
		void LimitCellToVisible(TCellRef& aCell) const;
		TBool IsCellOutOfVisibleRange(const TCellRef &aCell) const;
		TBool IsCellOutOfGridRange(const TCellRef& aCell) const;
		void StepRowForward(TInt& aRow) const;
		void StepRowBackward(TInt& aRow) const;
		void StepColumnForward(TInt& aCol) const;
		void StepColumnBackward(TInt& aCol) const;
		void CalcVisibleFromRow(TInt aVisibleToRow,TInt& aNewVisibleFromRow) const;
		TBool CalcVisibleToRow(TInt aVisibleFromRow,TInt& aNewVisibleToRow) const;
		void CalcVisibleFromColumn(TInt aVisibleToCol,TInt& aNewVisibleFromCol) const;
		TBool CalcVisibleToColumn(TInt aVisibleFromCol,TInt& aNewVisibleToCol) const;
		TInt CalcVisibleFromRowAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const;
		TInt CalcVisibleFromColumnAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const;
		TCellRef CalcVisibleFromCellAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const;
		TBool FindNextRowPageBreak(TInt aSearchStart,TInt& aFoundRow) const;
		TBool FindNextColumnPageBreak(TInt aSearchStart,TInt& aFoundCol) const;
		void DoMainPaginationLoopL(TInt aPageSpan,CSparseMap* aCellSpanMap,CSparseMap* aPageMap,
			CArrayFix<TInt>* aHardPageBreaks,TInt aStartId);
		TBool RequestRow(TInt aRow,TInt& aReturnRow) const;

		void ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,const TRangeRef& aGridRange);

	private:	// DATA TYPES
		enum 
			{
			EMaxArrayChanges=256,
			EInitialDefaultRowHeightInTwips = 266,
			EInitialDefaultColumnWidthInTwips = 700
			};
		enum
			{
			EIsTopLabels = 0x1,
			EIsSideLabels = 0x2,
			EIsHorizontalGridLines =  0x4,
			EIsVerticalGridLines = 0x8,
			EIsColumnBursting = 0x10,
			EIsCursorVisible = 0x20,
			EIsRowPermanentlySelected = 0x40,
			EIsHorizontalTitleLine = 0x80,
			EIsVerticalTitleLine = 0x100,
			EIsIndefiniteRowBoundaries = 0x200,
			EIsUniformRowHeight = 0x400,
			EIsUniformColumnWidth = 0x800,
			EIsTopLabelDragDisabled = 0x1000,
			EIsSideLabelDragDisabled = 0x2000,
			EIsPaginated = 0x4000,
			EIsAutoPagination = 0x8000,
			EIsPrintedLabels = 0x10000,
			EIsPrintedGridLines = 0x20000,
			EIsVisibleToRowFullyVisible = 0x40000,
			EIsVisibleToColumnFullyVisible = 0x80000,
			EIsEncroachingCellBorders = 0x100000,
			EIsColumnSelectionDisabled = 0x200000,
			EIsRowSelectionDisabled = 0x400000,
			EIsAutoClearGridCells = 0x800000,
			EIsGridLabelSeparators = 0x1000000,
			EIsHighlightVisible = 0x2000000,
			EIsPageBreakLinesHidden = 0x4000000
			};

    private:    // Data

		const MGridTable* iGridTable;
		const MGraphicsDeviceMap* iGraphicsDeviceMap;		//*
		CGridImg*   iGridImg;								//*
	// persistent
		TRangeRef   iGridRange;								//*
		TRangeRef   iVisibleRange;
		TRangeRef   iTitleRange;
		CSparseMap* iColumnWidthMap;						//*
		CSparseMap* iRowHeightMap;							//*
		CSparseMap* iColumnPageMap;							//*
		CSparseMap* iRowPageMap;							//*
		CArrayFix<TInt>* iHardRowPageBreaks;
		CArrayFix<TInt>* iHardColumnPageBreaks;
		TRgb		iGridEdgeColor;
		TInt        iMinRowHeightInPixels;
		TInt        iMinColumnWidthInPixels;
		TSize       iPageSizeInTwips;						//*
		TUint32		iFlags;									//* Starred items are used in printing
	////////////////////////->
		TGridColors iColors;
	////////////////////////->
	// End of persistent data
		TBool		iHasChanged;
	};



/* \class CGridLabelImg
*    \brief Draws a grid cell's label
*
* 
*  @lib Grid
*  @since ?Series90_version
*/
class CGridLabelImg : public CBase
	{
		friend class CGridImgBC;

    public:  // Constructors and destructor

		IMPORT_C virtual ~CGridLabelImg();
		IMPORT_C void ConstructL();

	public:	// New functions
		inline void SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap);
		inline TFontSpec FontSpec() const;
		IMPORT_C void ReleaseFont();
		IMPORT_C void NotifyGraphicsDeviceMapChangeL();
		inline void SetGridColors(const TGridColors& aGridColors);

	protected:	// New functions

		IMPORT_C CGridLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap);
	////////////////////////->
		IMPORT_C void DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect, TRgb aColor) const;
	////////////////////////->

	private:	// New functions

		virtual void DrawRowLabelL(CGraphicsContext* aGc,TInt aRow,const TRect& aRect) const=0;
		virtual void DrawColLabelL(CGraphicsContext* aGc,TInt aCol,const TRect& aRect) const=0;
		IMPORT_C virtual void DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const;
		IMPORT_C virtual TInt SideLabelWidthInPixels(TInt aStartRow,TInt aEndRow) const;
		IMPORT_C virtual TInt TopLabelHeightInPixels() const;
		IMPORT_C virtual void DrawRowCursorL(CGraphicsContext* aGc,const TRect& aRect) const;

	protected:	// DATA TYPES
		enum
			{
			EDefaultSideLabelWidthInTwips=300,
			EDefaultTopLabelHeightInTwips=300
			};

    protected:  // Data

		CFont* iFont;
		TFontSpec iFontSpec;
		MGraphicsDeviceMap* iGraphicsDeviceMap;
		TGridColors iGridColors;

    private:    // Data

		TInt iSpare;
	};

/* \class CGridCellImg
*    \brief Draws a grid cell's contents
* 
*  @lib Grid
*  @since ?Series90_version
*/
class CGridCellImg : public CBase
	{
		friend class CGridImgBC;

    public:  // Constructors and destructor

		IMPORT_C virtual ~CGridCellImg();


	public:	// New functions

		inline TInt BurstColOffset() const;
		inline TInt BurstLeft() const;
		inline TInt BurstRight() const;
		inline TBool IsHorizontalGridLines() const;
		inline TBool IsVerticalGridLines() const;
		inline void SetGridColors(const TGridColors& aGridColors);

	protected:

		IMPORT_C CGridCellImg();

	private:	// New functions

		virtual void DrawL(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aDrawRect,
			const TRect& aClipRect) const=0;
		IMPORT_C virtual TInt DataWidthInPixelsL(const TCellRef& aCell) const;
		IMPORT_C virtual TBool DoesCellContainDataL(const TCellRef& aCell) const;
	// reserved virtual function
		IMPORT_C virtual void Reserved_1();

	private:	// New functions

		void SetBurstingData(TInt aBurstColOffset=0,TInt aBurstLeft=0,TInt aBurstRight=0);

	private:	// DATA TYPES

		enum { EIsHorizontalGridLines = 0x1, EIsVerticalGridLines = 0x2 };

    protected:  // Data
		TGridColors iGridColors;

    private:    // Data
		TInt iBurstColOffset;
		TInt iBurstLeft;
		TInt iBurstRight;
		TUint32 iGridLineFlags;
	};

/* \class MGridCursorMoveCallBack
*    \brief	An interface to a callback function that is intended to be called 
*				whenever there is a change to the cursor position.
* 
*				If such a callback is needed, a concrete implementation is defined, 
*				instantiated and passed to CGridImg::SetCursorMoveCallBack().
* 
*  @lib Grid
*  @since ?Series90_version
*/
class MGridCursorMoveCallBack
	{
    public: // New functions
		virtual void HandleCursorMoveL()=0;
	};


/* \class CGridImg
*    \brief Draws the contents of the grid
* 
*  @lib Grid
*  @since ?Series90_version
*/
class CGridImg : public CGridImgBC
	{
    public: // New functions
		IMPORT_C virtual ~CGridImg();
		IMPORT_C static CGridImg* NewL(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay);
		IMPORT_C static CGridImg* NewL(CGridCellImg* aGridCellImg,CGridLay* aGridLay); //Creates Partial GridImg

		IMPORT_C TBool StartLabelDrag(const TPoint &aPoint);

    private:
		CGridImg(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay);
		CGridImg(CGridCellImg* aGridCellImg,CGridLay* aGridLay);

		void ConstructL();

        void LoadResourceL();
        void DeleteResource();

    private:    // Data
        TInt iResFileOffset;
	};

/* \class TGridUtils
*    \brief A collection of Grid utilities
*
* 
*  @lib Grid
*  @since ?Series90_version
*/
class TGridUtils
	{
    public: // New functions
		IMPORT_C static void FillRect(CGraphicsContext* aGc,TRgb aColor,const TRect &aRect);
	};


#include <grdstd.inl>

#endif      // GRDSTD_H   
            
// End of File
