/*
* ==============================================================================
*  Name        : GrdimgBC.h
*  Part of     : Grid
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Class for drawing the contents of the grid
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


#ifndef GRDIMGBC_H
#define GRDIMGBC_H

//  INCLUDES
#include <e32std.h>
#include <gdi.h>
#include <grdcells.h>
#include <grddef.h>


// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;
class CStreamStore;
class CGridImg;
class CGridCellImg;
class CGridLabelImg;
class CSparseMap;
class MGridCursorMoveCallBack;
class RWindow;
class CWindowGc;
class TGridColors;

// CLASS DECLARATION

/* \class CGridImg
*    \brief Draws the contents of the grid
* 
*  @lib grid
*  @since ?Series90_version
*/
class CGridImgBC : public CBase
{
    friend class CGridImg;
    friend class CGridLay;

	public:	// DATA TYPES
		enum
			{
			EIsWithSelect=0x0001,
			EIsWithControl=0x0002,
			EIsWithDrag=0x0004,
			EIsAtBoundary=0x0008,
			EIsAbsoluteMove=0x0010,
			EIsRowSelected=0x0020,
			EIsColumnSelected=0x0040
			};
		enum { EScaleOneToOne=100};
		enum TSelectType
			{ ESelectOverwrite, ESelectAppend };
		// Hildon specific - needs to be public
		enum TDragDim {EXDrag,EYDrag,ENoDrag};

    public: // New functions
		IMPORT_C virtual ~CGridImgBC();
		IMPORT_C static CGridImgBC* NewL_BC(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay);
		IMPORT_C static CGridImgBC* NewL_BC(CGridCellImg* aGridCellImg,CGridLay* aGridLay); //Creates Partial GridImg
		inline void SetGridLay(CGridLay* aGridLay);
		inline void SetWindow(RWindow* aWin);
	////////////////////////->
		IMPORT_C void SetGridLabelImg(CGridLabelImg* aGridLabelImg);
	////////////////////////->
		inline void SetCursorMoveCallBack(MGridCursorMoveCallBack* aCursorMoveCallBack);
		inline MGridCursorMoveCallBack* GetCursorMoveCallBack();
		inline const CGridCellRegion* Selected() const;
		inline const CGridLabelImg* GridLabelImg() const;

		IMPORT_C void ScrollL(const TPoint &aOffset);
		IMPORT_C void MoveCursorL(TMoveDirectionAndAmount aCursorMove,TUint aSelectState);
   		IMPORT_C void SetCursorWithPointerL(const TPoint& aPoint,TUint aFlagList); // deprecated, kept for BC
   		IMPORT_C void SetCursorWithPointerL(const TPoint& aPoint,TUint aFlagList, TBool& aEditRequested);
		IMPORT_C void ResetSelectedL();
		IMPORT_C void AddRangeToSelectedL(const TRangeRef& aRange,TSelectType aType=ESelectOverwrite);
		IMPORT_C void AddRegionToSelectedL(const CArrayFix<TRangeRef>* aCellRegion,TSelectType aType=ESelectOverwrite);
		IMPORT_C void AddRowToSelectedL(TInt aRow,TSelectType aType=ESelectOverwrite);
		IMPORT_C void AddColToSelectedL(TInt aCol,TSelectType aType=ESelectOverwrite);
		IMPORT_C void DrawL(CGraphicsContext* aGc) const;
		IMPORT_C void DrawL(CGraphicsContext* aGc,const TRect& aRect) const;
		IMPORT_C void DrawCellL(const TCellRef& aCell) const;
		IMPORT_C void DrawRangeL(const TRangeRef& aRange) const;
		IMPORT_C void DrawSelectedL() const;
		IMPORT_C void DrawTitleLines() const;
		IMPORT_C void ClearTitleLineRegionL(const TPoint& aCrossPoint) const;
		IMPORT_C void PrintGridLinesAndCellsInRangeL(CGraphicsContext* aPrinterGc,const TRangeRef& aRange,
			TInt aScaleFactor) const;

		inline TCellRef CursorPos() const;
		IMPORT_C void SetCursorPosL(const TCellRef& aCursorPos);
		inline TCellRef NewCursorPos() const;
		inline TCellRef AnchorPos() const;
		IMPORT_C void SetAnchorPosL(const TCellRef& aAnchorPos);
		inline TRect GridRect() const;
		IMPORT_C void SetGridRect(const TRect& aNewRect);
		IMPORT_C void SetPrintGridRect(const TRect& aPrintRect);
		inline TPoint TitlePoint() const;
		inline TPoint MainPoint() const;
		inline TRect MainRect() const;
		IMPORT_C void ResetReferencePoints();
		IMPORT_C void NotifyGridRangeResize();

		IMPORT_C void CheckSideLabelWidthAndScrollL();
		IMPORT_C TInt CheckSideLabelWidth();
		IMPORT_C TInt SideLabelWidthInPixels() const;
		IMPORT_C TInt MaxSideLabelWidthInPixels() const;
		IMPORT_C TInt TopLabelHeightInPixels() const;
		IMPORT_C void FinishLabelDragL();
		IMPORT_C TBool StartLabelDrag(const TPoint &aPoint);
		IMPORT_C TBool UpdateLabelDrag(const TPoint &aPoint);
		IMPORT_C TBool StartLabelResize(TBool aIsColumnLabel, TInt aIndex);
		IMPORT_C TBool UpdateLabelResize(TInt aDelta);
		IMPORT_C void FinishLabelResizeL(TBool aResize);
		// Hildon specific
		IMPORT_C enum TDragDim DragDimension(); // row or column drag
		IMPORT_C TInt DragLabel(); // which row/column

	private:	// DATA TYPES
		// Changed public for Hildon
		enum TRefPoint {ETitleRef,EMainRef};
		enum TDragDraw {EDragDrawWithBitmap,EDragDrawWithoutBitmap};
		enum TArrows {EBothArrows,ESecondArrowOnly};
		enum
			{
			EIsLabelDraggingIgnored = 0x1,
			EIsSidewaysScrollIgnored = 0x2
			};

    protected:
		CGridImgBC(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay);
		CGridImgBC(CGridCellImg* aGridCellImg,CGridLay* aGridLay);

    private:  // New functions

		void DrawResizingDragHiglights(const TRect& aRect);
		void DrawAllGridLabelsL() const;
		void DrawTopLeftGridLabelL() const;
		void DrawTopGridLabelsL(TInt aStartCol,TInt aEndCol,TRefPoint aXRef=EMainRef) const;
		void DrawSideGridLabelsL(TInt aStartRow,TInt aEndRow,TRefPoint aYRef=EMainRef) const;
		void DrawSideGridLabelIfOnScreenL(TInt aRow) const;
		void DrawAllGridLinesAndCellsL() const;
		void DrawGridLinesAndCellsInRangeL(const TRangeRef& aRange,const TRect& aClipRect,
			TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
		void DrawCellsToGcL(CGraphicsContext* aGc,const TRangeRef& aRange,const TRect& aClipRect,
			const TPoint& aStartPoint,TInt aScaleFactor=EScaleOneToOne) const;
		void DrawBurstingCellL(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aRect,const TRect& aClipRect,
			TInt aScaleFactor,TInt aBurstLeft,const TCellRef& aBurstCell) const;
		TInt CalcBurstLeftL(TCellRef& aBurstCell,TInt aScaleFactor) const;
		TInt CalcBurstRightL(const TCellRef& aCell,TInt aExcessRight,TInt aScaleFactor) const;
		void DrawVerticalTitleLine() const;
		void DrawHorizontalTitleLine() const;
		void BeginRedrawAndDrawL() const;
		void BeginRedrawAndDrawL(const TRect& aRect) const;

		void AppendTotalHighlightRegionL(TRegion& aRegion) const;
		void AppendPartialHighlightRegionL(TRegion& aRegion,const TRect& aClipRect,
			TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
		void RemoveRowLabelFromRegionL(TInt aRow,TRegion& aRegion) const;
		void HighlightMinRegion(const TRegion &aOldRegion,const TRegion &aNewRegion);
		void HighlightRegion(const TRegion &aRegion) const;
		void HighlightNewRegionFromOldL(const TRegion& aOldRegion);
		void DrawCursorOrRegionL(TUint aMoveFlags);
		void UpdateSelectedRegion(TInt aSelectCount,TUint aMoveFlags);
		void AddLabelToRegionL(TUint aMoveFlags);
		void StartSelectedRegionL(TUint aMoveFlags);
		TBool ScanColumnsForDrag(TInt aFromColumn,TInt aToColumn,TInt aPointerPos,TInt& aPrevious,TInt& aCurrent);
		TBool ScanRowsForDrag(TInt aFromRow,TInt aToRow,TInt aPointerPos,TInt& aPrevious,TInt& aCurrent);
		void DrawDraggingHighlight(const TRect aLine,TDragDraw aDragDraw);
		void DrawArrowsToInMemoryBitmap(TArrows aArrows);
		TPoint RelativeCellToPoint(const TCellRef& aCell,TRefPoint aXRef=EMainRef,
			TRefPoint aYRef=EMainRef) const;
		TCellRef RelativePointToCell(const TPoint& aPoint,TRefPoint aXRef=EMainRef,
			TRefPoint aYRef=EMainRef) const;
		TRect PartialCellRectL(const TCellRef& aCell,const TRect& aClipRect,
			TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
		TRect PartialRangeRect(const TRangeRef& aRange,const TRect& aClipRect,
			TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
		void CreateGc(CGraphicsContext* aGc);
		void DeleteGc();
		static void CleanupGc(TAny* aObject);
		void ResetGcToDefault(CGraphicsContext* aGc) const;
		void ScaleDown(TPoint& aPoint,TInt aScaleFactor) const;
		void ConstructSelectedL(const TRangeRef& aGridRange);

		void ConstructL();
		void LoadResourceL();

	////////////////////////->
		void SetGridColors(const TGridColors& aGridColors);
	////////////////////////->

    private:    // Data

		TRect		iGridRect;
		TPoint		iTitlePoint;
		TPoint		iMainPoint;
		TCellRef	iCursorPos;							// Persisted
		TCellRef 	iNewCursorPos;
		TCellRef	iAnchorPos;

		CGraphicsDevice*	iGraphicsDevice;
		CGraphicsContext*	iGcPtr;
		CWindowGc*			iGc;
		RWindow*			iWin;
		CGridCellImg*		iGridCellImg;				//*
		CGridLabelImg*		iGridLabelImg;              //*
		CGridLay*			iGridLay;					//* Starred items are used in printing
		CGridCellRegion*		iSelected;
		MGridCursorMoveCallBack*	iCursorMoveCallBack;
		TBool		iDrawResizeLines;
		TInt 		iDragLabel;
		TInt		iCurrentDragPos;
		TInt		iDragDiff;
		TInt		iDragFlags;
		TDragDim	iDragDim;
		CFbsBitmap*	iDragBmp;
		TRefPoint 	iXRefPoint;
		TRefPoint	iYRefPoint;
	};

#endif      // GRDIMGBC_H
            
// End of File
