/*
* ==============================================================================
*  Name        : Chtstd.h
*  Part of     : Chart
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Interface for chart library
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


#ifndef CHTSTD_H
#define CHTSTD_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <bacell.h>
#include <gdi.h>
#include <gulutil.h> 

#include <txtfrmat.h>

#include "chtdef.h"

// CONSTANTS

// MACROS

// DATA TYPES
struct TDrawXLabel 
	{
	public:
		TBuf<32> clipBuf;
		TPoint textPos;
	};

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class MSelectionObserver;
class MChartObserver;
class CChartIterator;

// CLASS DECLARATION


/* \class MChartTable
*    \brief Interface for chart table data sources
*
*
*  @lib chart
*  @since ?Series90_version
*/
class MChartTable
	{
    public: // New functions
		virtual TReal Value(const TCellRef& aCell) const=0;
		virtual const TDesC* Label(const TCellRef& aCell) const=0;
		virtual TRangeRef DataRangeLimits() const=0;
		virtual TBool IsEmpty(const TCellRef& aCell) const=0;
	};


/* \class CChartAxes
*    \brief Implements chart axes
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartAxes : public CBase
	{
		friend class CChartManager;

	public:		// DATA TYPES
		enum TTickName {EMajorTick,EMinorTick};
		enum TTickType {ETickAcross,ETickInside,ETickOutside,ETickNone};
		enum TTickSeparationType {EAutomatic, EManualMajor, EManualMinor, EManual};
		enum TGridPosition {EGridMajor,EGridMinor};
		enum TAxisType {EAxisValue,EAxisLabel,EAxisNone}; 
		enum TAxisFormat {EGeneral,EFixed,EScientific,ECurrency, EMeasurement, EPercent,ETriad,EDate,ETime};
		enum TAxisName {EXAxis,EYAxis};
		enum {EMaxNumber=16};
		enum {EMajorTickLength=10};
		enum {EMinorTickLength=5};
		enum {EMaxAxisTitleLength=32};

    public:  // Constructors and destructor
		IMPORT_C static CChartAxes* NewL(const MChartTable* aChartTable);
		IMPORT_C static CChartAxes* NewL(const CChartAxes* aAxes);
		IMPORT_C virtual ~CChartAxes();

    public: // New functions
		IMPORT_C void PreDraw(CGraphicsContext* aGc) const;
		IMPORT_C void PostDraw(CGraphicsContext* aGc);
		IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
		IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
		IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
		IMPORT_C void InternalizeL(RReadStream& aStream);
		IMPORT_C void SetChartInsets();

    public: // New functions
		IMPORT_C void SetMajorTickType(TAxisName aAxisName,TTickType aTickType);
		IMPORT_C TTickType MajorTickType(TAxisName aAxisName) const;
		IMPORT_C void SetMinorTickType(TAxisName aAxisName,TTickType aTickType);
		IMPORT_C TTickType MinorTickType(TAxisName aAxisName) const;
		IMPORT_C void SetMajorTickSeparation(TAxisName aAxisName,TReal aTickSeparation);
		IMPORT_C TReal MajorTickSeparation(TAxisName aAxisName) const;
		IMPORT_C void SetMinorTicksPerMajorTick(TAxisName aAxisName,TInt aNoMinorTicks);
		IMPORT_C TInt MinorTicksPerMajorTick(TAxisName aAxisName);
		IMPORT_C void SetShowMajorGridLines(TAxisName aAxisName,TBool aState);
		IMPORT_C TBool ShowMajorGridLines(TAxisName aAxisName) const; 
		IMPORT_C void SetShowMinorGridLines(TAxisName aAxisName,TBool aState);
		IMPORT_C TBool ShowMinorGridLines(TAxisName aAxisName) const;
		IMPORT_C void SetShowAxisLine(TAxisName aAxisName,TBool aState);
		IMPORT_C TBool ShowAxisLine(TAxisName aAxisName) const; 
		IMPORT_C void SetShowAxisTitle(TAxisName aAxisName,TBool aState);
		IMPORT_C TBool ShowAxisTitle(TAxisName aAxisName) const;
		IMPORT_C void SetShowChartTitle(TBool aState);
		IMPORT_C TBool ShowChartTitle() const;
		IMPORT_C void SetAxisType(TAxisName aAxisName,TAxisType aAxisType);
		IMPORT_C TAxisType AxisType(TAxisName aAxisName) const;
		IMPORT_C void SetAxisFormat(TAxisName aAxisName,TAxisFormat aAxisFormat);
		IMPORT_C TAxisFormat AxisFormat(TAxisName aAxisName) const;
		IMPORT_C void SetAxisLabelRange(TAxisName aAxisName,const TRangeRef& aRangeRef);
		IMPORT_C TRangeRef AxisLabelRange(TAxisName aAxisName);
		IMPORT_C void SetLabelBetweenTicks(TAxisName aAxisName,TBool aState);
		IMPORT_C TBool LabelBetweenTicks(TAxisName aAxisName) const;
		IMPORT_C void SetAxisTicksPerLabel(TAxisName aAxisName,TInt aTicksPerLabel);
		IMPORT_C TInt AxisTicksPerLabel(TAxisName aAxisName) const;
		IMPORT_C void SetUpperAndLowerLimits(TAxisName aAxisName,TReal aUpperLimit,TReal aLowerLimit);
		IMPORT_C TReal LowerLimit(TAxisName aAxisName) const;
		IMPORT_C TReal UpperLimit(TAxisName aAxisName) const;
		IMPORT_C void SetDecimalPlaces(TAxisName aAxisName,TInt aDecimalPlaces);
		IMPORT_C TInt DecimalPlaces(TAxisName aAxisName) const;
		IMPORT_C void SetCurrencyType(TAxisName aAxisName, const TBuf<KMaxCurrencySymbol>& aCurrencySymbol, const TLocalePos& aSymbolPosition);
		IMPORT_C void CurrencyType(TAxisName aAxisName, TBuf<KMaxCurrencySymbol>& aCurrencySymbol, TLocalePos& aSymbolPosition) const;
		IMPORT_C void SetAxisCrossValue(TAxisName aAxisName,TReal aAxisCrossValue);
		IMPORT_C TReal AxisCrossValue(TAxisName aAxisName) const;
		IMPORT_C void SetAxisTitle(TAxisName aAxisName,HBufC* aTitle);
		IMPORT_C const TDesC* AxisTitle(TAxisName aAxisName)const;
		IMPORT_C void SetChartTitle(HBufC* aTitle);
		inline const TDesC* ChartTitle() const;
		IMPORT_C void SwapAxes();
		IMPORT_C void SetLogarithmicAxis(TAxisName aAxisName,TBool aStatus);
		IMPORT_C TBool LogarithmicAxis(TAxisName aAxisName) const;
		IMPORT_C void SetTitleFontUlSt(TFontUnderline aUnderline,TFontStrikethrough aStrikethrough);
		IMPORT_C void TitleFontUlSt(TFontUnderline& aUnderline,TFontStrikethrough& aStrikethrough) const;
		IMPORT_C void SetFontUlSt(TFontUnderline aUnderline,TFontStrikethrough aStrikethrough);
		IMPORT_C void FontUlSt(TFontUnderline& aUnderline,TFontStrikethrough& aStrikethrough) const;
		inline TRect ChartRect() const;
		IMPORT_C void SetDrawableRect(const TRect& aChartRect);
		inline TRect DrawableRect() const;
		inline void SetFont(CFont* aFont);
		inline void SetTitleFont(CFont* aFont);
		inline void SetXTitleFont(CFont* aFont);
		inline void SetYTitleFont(CFont* aFont);
		inline void SetXLabelsFont(CFont* aFont);
		inline void SetYLabelsFont(CFont* aFont);
		inline void SetLegendFont(CFont* aFont);
		inline const TPoint& AxisCrossPoint() const;
		inline const MChartTable* ChartTable() const;
		IMPORT_C void SetTextColor(TRgb aColor);
		IMPORT_C void SetTitleColor(TRgb aColor);
		IMPORT_C void SetXTitleColor(TRgb aColor);
		IMPORT_C void SetYTitleColor(TRgb aColor);
		IMPORT_C void SetXLabelsColor(TRgb aColor);
		IMPORT_C void SetYLabelsColor(TRgb aColor);
		IMPORT_C void SetLegendColor(TRgb aColor);
		inline TRgb TextColor() const;
		inline TRgb TitleColor() const;
		inline TRgb XTitleColor() const;
		inline TRgb YTitleColor() const;
		inline TRgb XLabelsColor() const;
		inline TRgb YLabelsColor() const;
		inline TRgb LegendColor() const;
        IMPORT_C void SetLineColor(TRgb aColor); // kept for BC!
		IMPORT_C void SetLineColor(TAxisName aAxisName, TRgb aColor);
		IMPORT_C TRgb LineColor(TAxisName aAxisName) const;
        IMPORT_C void SetBackgroundColor(TRgb aColor); // kept for BC!
		IMPORT_C void SetBackgroundColor(TRgb aColor, TBool aSetFrameColour);
		inline TRgb BackgroundColor() const;
		IMPORT_C void SetFrameColor(TRgb aColor);
		inline TRgb FrameColor() const;
		IMPORT_C TInt MapX(TReal aX) const;
		IMPORT_C TInt MapY(TReal aY) const;
		IMPORT_C TInt NoXPixelsBetweenTicks() const;
		IMPORT_C TInt NoYPixelsBetweenTicks() const;
		IMPORT_C TInt PixelBorder() const;
		inline CFont* Font() const;
		inline void SetPieChart(TBool aPieChart);
		inline TBool HasChanged() const;
		IMPORT_C void SetTickSeparationType(const TAxisName aAxisName, const TTickSeparationType aSeparationType);
		IMPORT_C const TTickSeparationType TickSeparationType(const TAxisName aAxisName) const;
		IMPORT_C TRect TitleRect() const;
		IMPORT_C TRect XAxesTitleRect() const;
		IMPORT_C TRect YAxesTitleRect() const;
		IMPORT_C TRect XAxisLabelsRect() const;
		IMPORT_C TRect YAxisLabelsRect() const;
		IMPORT_C void SetTitleUnderline();
		IMPORT_C void SetXTitleUnderline();
		IMPORT_C void SetYTitleUnderline();
		IMPORT_C void SetXLabelsUnderline();
		IMPORT_C void SetYLabelsUnderline();
		IMPORT_C void SetLegendUnderline();
		inline TFontUnderline TitleUnderline();
		inline TFontUnderline XTitleUnderline();
		inline TFontUnderline YTitleUnderline();
		inline TFontUnderline XLabelsUnderline();
		inline TFontUnderline YLabelsUnderline();
		inline TFontUnderline LegendUnderline();
		inline TFontStrikethrough TitleStrikethrough();
		inline TFontStrikethrough XTitleStrikethrough();
		inline TFontStrikethrough YTitleStrikethrough();
		inline TFontStrikethrough XLabelsStrikethrough();
		inline TFontStrikethrough YLabelsStrikethrough();
		inline TFontStrikethrough LegendStrikethrough();
		IMPORT_C void SetTitleStrikethrough();
		IMPORT_C void SetXTitleStrikethrough();
		IMPORT_C void SetYTitleStrikethrough();
		IMPORT_C void SetXLabelsStrikethrough();
		IMPORT_C void SetYLabelsStrikethrough();
		IMPORT_C void SetLegendStrikethrough();

	public:		// New functions			// added by RG for cursor selection jan 2000
		IMPORT_C void SetSelectionObserver(MSelectionObserver* aObserver);
		TRect ClippingRect() const;
		TBool Is3D() const;
		IMPORT_C void SetIs3D(TBool aState);

	private:	// New functions		// added by RG for keyboard selection jan 2000
		MSelectionObserver* iSelectionObserver;

	private:	// private classes
		class TAxisInfo
		{
		public:
			TAxisInfo();

	    public: // New functions
			void InternalizeL(RReadStream& aStream);
			void ExternalizeL(RWriteStream& aStream) const;
			void CopySettingsL(const TAxisInfo& aAxisInfo);
			TReal MajorTickSeparation(TInt aTickCount) const;
			TInt TickCount() const;

		public:     // Data
			enum {	EShowMajorGridLines=0x04,EShowMinorGridLines=0x08,
					EShowAxisTitle=0x10,EShowAxisLine=0x20,
					ELabelBetweenTicks=0x40};
			TUint32 iFlags;
	 		TTickType iMajorTickType;
			TTickType iMinorTickType;
			TAxisType iAxisType;
			TAxisFormat iAxisFormat;
			TInt iDecimalPlaces;
			TBuf<KMaxCurrencySymbol> iCurrencySymbol;
			TLocalePos iSymbolPosition;
			HBufC* iAxisTitle;
			TReal iMajorTickSeparation; 
			TReal iLowerLimit;
			TReal iUpperLimit;
			TReal iAxisCrossValue;
			TInt iMinorTicksPerMajorTick;
			TInt iTicksPerLabel;
			TRangeRef iLabelRange;
			TBool iLogarithmic;
			TTickSeparationType iSeparationType;
			TRgb iLineColor;

		};

	private:
        /**
        * C++ default constructor.
        */
		CChartAxes();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
		void ConstructL(const MChartTable* aChartTable);
		void ConstructL(const CChartAxes* aAxes);

    private:  // New functions
		void SetChartRectForGraphsWithAxes();
		void SetChartRectForPie();
		void SetStateOfFlags(TAxisName aAxisName,TBool aState,TInt aFlagField);
		void FormatValue(TDes& aDes,TReal aValue, const TAxisInfo& aAxisInfo) const; //TAxisFormat aAxisFormat,TInt aDecimalPlaces) const;
		void FormatCurrency(TDes &aDes,TReal aCurrencyAmount, const TAxisInfo& aAxisInfo) const;
		TInt LabelDistance(TTickType aTickType) const;
		void DrawChartTitle(CGraphicsContext* aGc) const;
		void DrawXAxisLine(CGraphicsContext* aGc) const;
		void DrawYAxisLine(CGraphicsContext* aGc) const;
		void Draw3DAxis(CGraphicsContext* aGc,const TPoint& twoDAxisStart,const TPoint& twoDAxisEnd,const TBool aSelected) const;
		void DrawXAxisTicks(CGraphicsContext* aGc) const;
		void DrawYAxisTicks(CGraphicsContext* aGc) const;
		void DrawXTicks(CGraphicsContext* aGc,TPoint& from,TPoint& to,TReal tickValue,TInt aTickCount) const;
		void DrawYTicks(CGraphicsContext* aGc,TPoint& from,TPoint& to,TReal tickValue,TInt aTickCount) const;
		void DrawXAxisLabel(CGraphicsContext* aGc,const TRangeRef::TIter& aIter,TInt aXTickPosition,TInt aXTickSeparation) const;
		void DrawYAxisLabel(CGraphicsContext* aGc,const TRangeRef::TIter& aIter,TInt aYTickPosition) const;
		void DrawXAxisTitle(CGraphicsContext* aGc) const;
		void DrawYAxisTitle(CGraphicsContext* aGc) const;
		void DrawXAxisGridLine(CGraphicsContext* aGc) const;
		void DrawYAxisGridLine(CGraphicsContext* aGc) const;
		void DrawXAxisLabels(CGraphicsContext* aGc) const;
		void DrawYAxisLabels(CGraphicsContext* aGc) const;
		void DrawXAxisDataLabels(CGraphicsContext* aGc) const;
		void DrawYAxisDataLabels(CGraphicsContext* aGc) const;
		void DrawXAxisTextLabelsL(CGraphicsContext* aGc) const;
		void DrawYAxisTextLabels(CGraphicsContext* aGc) const;
		void ClipToFitH(TDes& aBuffer,const CFont& aFont,TInt aMaxHeightInPixels,TChar aAlternativeEnd=KTextUtilClipEndChar)const; 

	private:	// data types
		enum {ETitleFontUl=0x1,ETitleFontSt=0x2,EFontUl=0x4,EFontSt=0x8};

	private:    // Data
		const MChartTable* iChartTable;
		CChartManager* iManager;
		TBool iIs3D;
		TPoint iAxisCrossPoint;
		TRect iChartRect; // diagram drawn in here
		TRect iDrawableRect; // includes diagram and lables
		TInt iWidthY; // used when positioning the y axis title only
		HBufC* iChartTitle;
		TBool iShowChartTitle;
		TAxisInfo iXAxis;
		TAxisInfo iYAxis;
		CFont* iFont;
		CFont* iTitleFont;
		CFont* iXTitleFont;
		CFont* iYTitleFont;
		CFont* iXLabelsFont;
		CFont* iYLabelsFont;
		CFont* iLegendFont;
		TBool iPieChart;
		TRgb iTextColor;
		TRgb iTitleColor;
		TRgb iXTitleColor;
		TRgb iYTitleColor;
		TRgb iXLabelsColor;
		TRgb iYLabelsColor;
		TRgb iLegendColor;
		TRgb iBackgroundColor;
		TRgb iFrameColor;
		TUint32 iFontsUlSt;
		TBool iChanged;
	//	TFontUnderline iFontUnderline;
		TFontUnderline iTitleFontUnderline;
		TFontUnderline iXTitleFontUnderline;
		TFontUnderline iYTitleFontUnderline;
		TFontUnderline iXLabelsFontUnderline;
		TFontUnderline iYLabelsFontUnderline;
		TFontUnderline iLegendFontUnderline;
	//	TFontStrikethrough iFontStrikethrough;
		TFontStrikethrough iTitleFontStrikethrough;
		TFontStrikethrough iXTitleFontStrikethrough;
		TFontStrikethrough iYTitleFontStrikethrough;
		TFontStrikethrough iXLabelsFontStrikethrough;
		TFontStrikethrough iYLabelsFontStrikethrough;
		TFontStrikethrough iLegendFontStrikethrough;

	private:
		__DECLARE_TEST;
	};

/* \class CChartDiagram
*    \brief Abstract base class for all diagram types
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartDiagram : public CBase
	{
		friend class CChartManager;

	public:		// Data types
		enum TDiagramType {ELine,EColumn,EStackColumn,EBar,EStackBar,EScatter,EPie};

		/**
		 * The order of the point symbols is currently different from Excel.
		 * enum TPointSymbol {ENone, EDiamond, ESquare, ETriangle, EDiagonalCross, [EStar], ECircle, ECross, [ESmallLine], [ELargeLine]};
		 * Types in [] are available in Excel but currently missing in sheet.
		 */
		enum TPointSymbol {ENone, EDiagonalCross, ESquare, EDiamond, ECross, ECircle, ETriangle, ESymbolCount};
		enum TFillStyle {ESolidFill,EHorizontalFill,EVerticalFill,ESquareFill,EForwardFill,ERearwardFill,EDiamondFill};
		enum TDataLabelAlignment {EInside, ECenter, EOutside, ERight};
		enum TDataLabelType {EData,ELabel,ENoDataLabel}; 

		class TSymbology
			{
			public:
				IMPORT_C TSymbology();
				IMPORT_C void InternalizeL(RReadStream& aStream);
				IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
				IMPORT_C CGraphicsContext::TBrushStyle FillStyle() const;
				IMPORT_C void IncSettings();
				IMPORT_C void SetExcelDefaults();
/*xxx*/			IMPORT_C void UpdateForDiagram(const TDiagramType& aType);


				TBool operator!=(const TSymbology& aSymbolgy) const;

			public:
				TRgb iPointColor;
				TPointSymbol iPointSymbol;
				TRgb iLineColor;
				TInt iLineWidth;
				TBool iShowLine;
				TRgb iFillColor;
				TFillStyle iFillStyle;
			};

    public: // New functions
		virtual SChartAxesLimits DataLimits()=0;
		virtual TBool DrawItem(CGraphicsContext* aGc,TInt aItemNumber,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue)=0;
		virtual TDiagramType Type() const=0;
		IMPORT_C virtual void SetScatterDataRange(const TRangeRef& aRange);
		IMPORT_C virtual void ScatterDataRange(TRangeRef& aRange) const;
		IMPORT_C virtual void SetShowDataAsPercentages(TBool aState);
		IMPORT_C virtual TBool ShowDataAsPercentages() const;
		IMPORT_C static CChartDiagram* NewL(TDiagramType aType,const CChartAxes* aChartAxes);
		IMPORT_C virtual ~CChartDiagram();
		IMPORT_C virtual void CopySettings(const CChartDiagram& aDiagram);
		IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
		IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
		IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
		IMPORT_C virtual void InternalizeL(RReadStream& aStream);
		IMPORT_C void SetName(HBufC* aName);
		IMPORT_C void SetLabelRange(const TRangeRef& aDataLabelRange);
		IMPORT_C void SetDataRange(const TRangeRef& aRange);
		IMPORT_C virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);
		IMPORT_C TBool IsRangeValid(const TRangeRef& aRange) const;
		inline TInt Items() const;
		inline const TDesC* Name() const;
		IMPORT_C void SetSymbology(const TSymbology& aSymbology);
		inline const TSymbology& Symbology() const;
		IMPORT_C void SetDataLabelAlignment(TDataLabelAlignment aDataLabelAlignment);
		inline TDataLabelAlignment DataLabelAlignment() const;
		IMPORT_C void SetDataLabelType(TDataLabelType aDataLabelType);
		inline TDataLabelType DataLabelType() const;
		IMPORT_C void SetShowDiagram(TBool aState);
		inline TBool ShowDiagram() const;
		inline TRangeRef LabelRange() const;
		inline TRangeRef DataRange() const;
		inline TBool HasChanged() const;

	public:		// New functions -  new bit to enable keyboard selection - added by RG Jan 2000
		IMPORT_C void  SetSelected(TBool aIsSelected);

	protected:	// Data	 - new bit to enable keyboard selection - added by RG Jan 2000
		TBool iIsSelected;

	protected:	// New functions
		IMPORT_C CChartDiagram(const CChartAxes* aChartAxes);
		IMPORT_C SLimits UpperAndLowerAxisLimits(const TRangeRef& aRange);
		IMPORT_C void Draw3DRectangle(CGraphicsContext* aGc,const TRect& aRect,TBool aDrawTop,TBool aDrawSide) const;
		IMPORT_C void DrawDataLabel(CGraphicsContext* aGc,const TCellRef& aCell,const TPoint& aPosition,TReal aData) const;
		IMPORT_C void DrawDataLabel(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aDrawingRect,TReal aData) const;
		IMPORT_C void DrawLegendSymbol(CGraphicsContext* aGc,const TPoint& aPosition) const;

	private:	// New functions
		TReal Value(TInt aIndex) const;
		static void DrawLegendDiagonalCross(CGraphicsContext* aGc,const TPoint& aPosition,TInt aSize);
		static void DrawLegendSquare(CGraphicsContext* aGc,const TPoint& aPosition,TInt aSize);	
		static void DrawLegendTriangle(CGraphicsContext* aGc,const TPoint& aPosition,TInt aSize);	
		static void DrawLegendDiamond(CGraphicsContext* aGc,const TPoint& aPosition,TInt aSize);	
		static void DrawLegendCross(CGraphicsContext* aGc,const TPoint& aPosition,TInt aSize);	
		static void DrawLegendCircle(CGraphicsContext* aGc,const TPoint& aPosition,TInt aSize);

    protected:  // Data
		TBool iShowDiagram;
		TRangeRef iDataRange;
		TRangeRef iLabelRange;
		TDataLabelAlignment iDataLabelAlignment;
		TDataLabelType iDataLabelType;
		const MChartTable* iChartTable;
		const CChartAxes* iChartAxes;
		TSymbology iSymbology;
		TRangeRef::TIter iRangeIter;
		TRangeRef::TIter iLabelRangeIter;
		HBufC* iName;
		TBool iChanged;
	};

/* \class CChartManager
*    \brief One chart manager object for each chart diagram
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartManager : public CBase
	{
	public:		// Data types
		enum TLimitType {ELimitAutomatic=0x00,ELimitUserDefinedUpper=0x01,ELimitUserDefinedLower=0x02,
						 ELimitUserDefined=ELimitUserDefinedUpper|ELimitUserDefinedLower};
		enum TLegendType {ELegendNone,ELegendTopLeft,ELegendTop,ELegendTopRight,
						  ELegendRight,ELegendBottomRight,ELegendBottom,
						  ELegendBottomLeft,ELegendLeft,ELegendCenter};	

    public:  // Constructors and destructor
		IMPORT_C static CChartManager* NewL(CChartAxes* aChartAxes);
		IMPORT_C static CChartManager* NewL(const CChartManager* aManager);
		IMPORT_C virtual ~CChartManager();

    public: // New functions
		IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
		IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
		IMPORT_C void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap) const;
		IMPORT_C void RestoreComponentsL(const CStreamStore& aStore);
		IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
		IMPORT_C void InternalizeL(RReadStream& aStream);

		IMPORT_C virtual void DrawSetupL(CGraphicsContext* aGc);
		IMPORT_C virtual void Draw();
		IMPORT_C virtual TBool DrawItem();
		IMPORT_C void DrawComplete();
		IMPORT_C void SetDefaultFontsL();

		IMPORT_C void AddDiagramL(CChartDiagram* aDiagram);
		IMPORT_C void RemoveDiagram(TInt aDiagramNumber);
		IMPORT_C void CalculateAxisLimits(TBool aStacked=EFalse);
		IMPORT_C void SetAxisLimitType(CChartAxes::TAxisName aAxisName,TLimitType aType);
		IMPORT_C TLimitType AxisLimitType(CChartAxes::TAxisName aAxisName);
		IMPORT_C void SetShowDiagram(TInt aDiagramNumber,TBool aState);
		IMPORT_C TBool ShowDiagram(TInt aDiagramNumber) const;
		IMPORT_C TInt NoDiagrams() const;
		IMPORT_C CChartDiagram* Diagram(TInt aDiagramNumber) const;
		IMPORT_C void SetChartName(HBufC* aChartName);
		IMPORT_C TBool HasChanged() const;
		inline void SetDeviceMap(MGraphicsDeviceMap* aMap);

        IMPORT_C void SetFontSpec(const TFontSpec& /*aFontSpec*/); // kept for BC!
		IMPORT_C void SetFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);
        IMPORT_C void SetTitleFontSpec(const TFontSpec& /*aFontSpec*/); // kept for BC!
		IMPORT_C void SetTitleFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);
		IMPORT_C void SetXTitleFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);
		IMPORT_C void SetYTitleFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);
		IMPORT_C void SetXLabelsFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);
		IMPORT_C void SetYLabelsFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);
		IMPORT_C void SetLegendFontStyle(const TFontSpec& aFontSpec, const TRgb aNewColor, TBool aUnderlined, TBool aSt);

		IMPORT_C void SetTitleCharFormat(TCharFormat aChar);
		IMPORT_C void SetXTitleCharFormat(TCharFormat aChar);
		IMPORT_C void SetYTitleCharFormat(TCharFormat aChar);
		IMPORT_C void SetXLabelsCharFormat(TCharFormat aChar);
		IMPORT_C void SetYLabelsCharFormat(TCharFormat aChar);
		IMPORT_C void SetLegendCharFormat(TCharFormat aChar);

		IMPORT_C TCharFormat TitleCharFormat();
		IMPORT_C TCharFormat XTitleCharFormat();
		IMPORT_C TCharFormat YTitleCharFormat();
		IMPORT_C TCharFormat XLabelsCharFormat();
		IMPORT_C TCharFormat YLabelsCharFormat();
		IMPORT_C TCharFormat LegendCharFormat();

		inline void FontSpec(TFontSpec& aFontSpec) const;
		inline void TitleFontSpec(TFontSpec& aFontSpec) const;
		inline void XTitleFontSpec(TFontSpec& aFontSpec) const;
		inline void YTitleFontSpec(TFontSpec& aFontSpec) const;
		inline void XLabelsFontSpec(TFontSpec& aFontSpec) const;
		inline void YLabelsFontSpec(TFontSpec& aFontSpec) const;
		inline void LegendFontSpec(TFontSpec& aFontSpec) const;

		inline CChartAxes* Axes() const;
		IMPORT_C void SetPhysicalSize(const TRect& aRect);
		inline TRect PhysicalSize() const;
		inline const TDesC* ChartName() const;
		IMPORT_C void ChangeChartTypeL(CChartDiagram::TDiagramType aNewType);
		inline CChartDiagram::TDiagramType ChartType() const;

		IMPORT_C void SetLegendType(TLegendType aLegendType);
		inline TLegendType LegendType() const;
		IMPORT_C void SetShowLegend(TBool aState);
		IMPORT_C TBool ShowLegend() const;
		IMPORT_C void SetDefaultLegendName(HBufC* aDefaultName);
		inline const TDesC* DefaultLegendName() const;
		virtual void CopySettingsL(const CChartManager* aManager);
		IMPORT_C void SetIs3D(TBool aState);
		inline TBool Is3D() const;
		inline TRect LegendRect() const;

	public:				// added by RG for cursor selection jan 2000
		enum TChartObject{	ENoSelection = 0, ETitle, EXAxisTitle, EYAxisTitle, 
							EXAxisLabels, EYAxisLabels, 
							EXAxisMajorTicks, EYAxisMajorTicks, 
							EXAxisMinorTicks, EYAxisMinorTicks, 
							EXAxisMajorGridlines, EXAxisMinorGridlines, 
							EYAxisMajorGridlines, EYAxisMinorGridlines, 
							EXAxis, EYAxis, ELegend, ESeries, EWholeChart, 
	//	CBRL-5Z498F Sheet/Chartsheet: Select object dialogue includes wrong item Data labels
							EDataLabels,
							ENumObjectTypes }; // this item is just for counting the object types

		IMPORT_C CChartIterator* ChartIterator();
		IMPORT_C TBool DeleteCurrentObjectL();

	private:	// Data - added by RG for cursor selection jan 2000
		TRect iLegendRect;
		TChartObject iCurrentObject;
		CChartIterator* iChartIterator;

	private:
        /**
        * C++ default constructor.
        */
		CChartManager();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
		void ConstructL();

	private:	// New functions
		void CalculateSingleLimit(const CChartAxes::TAxisName aAxisName, SLimits& aLimits, const TBool aStacked, const TBool aZeroBased);
		void DrawLegend();
		SChartAxesLimits UpperAndLowerLimits();
		SChartAxesLimits UpperAndLowerStackedLimits();
		void ModifyLimits(SLimits& aLimits,const SLimits& aTmpLimits);
		void SetUpperAndLowerLimits(CChartAxes::TAxisName aAxisName,TReal aUpperLimit,TReal aLowerLimit);
		static TReal AutoTickSeparation(const TReal& aAxisRange);
		static void RoundToNearestMultiple(TReal& aValue,const TReal& aStep,TBool aRoundUp,TBool aLogAxis);

	private:	// Data
		TLimitType iXAxisLimitType;
		TLimitType iYAxisLimitType;
		TFontSpec iFontSpec;
		TFontSpec iTitleFontSpec;
		TFontSpec iXTitleFontSpec;
		TFontSpec iYTitleFontSpec;
		TFontSpec iXLabelsFontSpec;
		TFontSpec iYLabelsFontSpec;
		TFontSpec iLegendFontSpec;

		CFont* iFont;
		CFont* iTitleFont;
		CFont* iXTitleFont;
		CFont* iYTitleFont;
		CFont* iXLabelsFont;
		CFont* iYLabelsFont;
		CFont* iLegendFont;

		TCharFormatMask iTitleMask;
		TCharFormatMask iXTitleMask;
		TCharFormatMask iYTitleMask;
		TCharFormatMask iXLabelsMask;
		TCharFormatMask iYLabelsMask;
		TCharFormatMask iLegendMask;

		TCharFormat iTitleCharFormat;
		TCharFormat iXTitleCharFormat;
		TCharFormat iYTitleCharFormat;
		TCharFormat iXLabelsCharFormat;
		TCharFormat iYLabelsCharFormat;
		TCharFormat iLegendCharFormat;


		MGraphicsDeviceMap* iMap;
		CChartAxes* iChartAxes;
		CArrayFixFlat<CChartDiagram*>* iDiagramArray;
		TInt iMaxDiagrams;
		TInt iCurrentDiagram;
		TInt iMaxItems;
		TInt iCurrentItem;
		TReal iNegativeBaseValue;
		TReal iPositiveBaseValue;
		TRect iPhysicalSize;
		HBufC* iChartName;

		CGraphicsContext* iGc; 
		TLegendType iLegendType;
		TBool iShowLegend;
		HBufC* iDefaultLegendName;

	private:	// Data
		TStreamId iAxesId;
		TStreamId* iDiagramIds;
		TInt iNoDiagramIds;
		TInt iDiagramType;
		TBool iChanged;
		TBool iIs3D;
	};

/* \class CChartLineBase
*    \brief Abstract base class for all line based diagram types
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartLineBase : public CChartDiagram
	{
	protected:	// Constructors and destructor
		IMPORT_C CChartLineBase(const CChartAxes* aChartAxes);
		IMPORT_C ~CChartLineBase();

    protected:  // Functions from base classes
		IMPORT_C virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);

	protected:	// Data
		TPoint iLastPoint;
	};

/* \class CChartLine
*    \brief Implementation for line diagram type
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartLine : public CChartLineBase
	{
	public:	// Constructors and destructor
		IMPORT_C CChartLine(const CChartAxes* aChartAxes);

	public:	// Functions from base classes
		virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);
		virtual SChartAxesLimits DataLimits();
		virtual TBool DrawItem(CGraphicsContext* aGc,TInt aItemNumber,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);
		virtual TDiagramType Type() const {return(ELine);}

	private:	// Data
		TInt iPosition;
		TInt i3dLineWidth;
	};

/* \class CChartScatter
*    \brief Implementation for scatter diagram type
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartScatter : public CChartLineBase
	{
	public:	// Constructors and destructor
		IMPORT_C CChartScatter(const CChartAxes* aChartAxes);

	public:	// Functions from base classes
		virtual void CopySettings(const CChartDiagram& aDiagram);
		virtual TBool DrawItem(CGraphicsContext* aGc,TInt aItemNumber,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);
		virtual SChartAxesLimits DataLimits();
		virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);
		virtual void SetScatterDataRange(const TRangeRef& aRange);
		virtual void ScatterDataRange(TRangeRef& aRange) const;
		virtual TDiagramType Type() const {return(EScatter);}
		virtual void ExternalizeL(RWriteStream& aStream) const;
		virtual void InternalizeL(RReadStream& aStream);

	private:	// Data
		TRangeRef iScatterDataRange;
		TRangeRef::TIter iScatterDataIter;
        TInt iPosition;
        TInt i3dLineWidth;
	};

/* \class CChartColumn
*    \brief Implementation for column diagram type
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartColumn : public CChartDiagram
	{
	public:	// Constructors and destructor
		IMPORT_C CChartColumn(const CChartAxes* aChartAxes,TBool aStackColumn=EFalse);

	public:	// Functions from base classes
		virtual SChartAxesLimits DataLimits();
		virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);
		virtual TBool DrawItem(CGraphicsContext* aGc,TInt aItemNumber,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);
		virtual TDiagramType Type() const {return(iStackColumn?EStackColumn:EColumn);}

	private:	// New functions
		void DrawColumn(CGraphicsContext* aGc,TInt aXPos);
		void DrawStack(CGraphicsContext* aGc,TInt aXPos,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);

	private:	// Data
		TInt iColumnWidth;
		TInt iPositionOffset;
		TBool iStackColumn;
	};

/* \class CChartBar
*    \brief Implementation for bar diagram type
*
*		This class also implements the stacked bar diagram type
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartBar : public CChartDiagram
	{
	public:	// Constructors and destructor
		IMPORT_C CChartBar(const CChartAxes* aChartAxes,TBool aStackBar=EFalse);

	public:	// Functions from base classes
		virtual SChartAxesLimits DataLimits();
		virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);
		virtual TBool DrawItem(CGraphicsContext* aGc,TInt aItemNumber,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);
		virtual TDiagramType Type() const {return(iStackBar?EStackBar:EBar);}

	private:	// New functions
		void DrawBar(CGraphicsContext* aGc,TInt aYPos);
		void DrawStack(CGraphicsContext* aGc,TInt aYPos,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);

	private:	// Data
		TInt iBarHeight;
		TInt iPositionOffset;
		TBool iStackBar;
	};

/* \class CChartPieBC
*    \brief Implementation for pie diagram type
*
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartPieBC : public CChartDiagram
	{
		friend class CChartPie;

	public:	// Constructors and destructor
		IMPORT_C CChartPieBC(const CChartAxes* aChartAxes);
		~CChartPieBC();

	public:	// Functions from base classes
		virtual void CopySettings(const CChartDiagram& aDiagram);
		virtual SChartAxesLimits DataLimits();
		virtual void DrawSetup(TInt aTotalNumberOfDiagrams,TInt aDiagramCount);
		virtual TBool DrawItem(CGraphicsContext* aGc,TInt aItemNumber,TReal& aPositiveBaseValue,TReal& aNegativeBaseValue);
		virtual void SetShowDataAsPercentages(TBool aState);
		virtual TBool ShowDataAsPercentages() const;
		virtual TDiagramType Type() const {return(EPie);}
		virtual void ExternalizeL(RWriteStream& aStream) const;
		virtual void InternalizeL(RReadStream& aStream);

	private:	// New functions
		TInt MaxLabelWidth();
		void DrawWholePie(CGraphicsContext* aGc,TInt a3dDepth);
		void DrawDataLabelsL(CGraphicsContext* aGc,TReal aTheta,TReal aData,TReal aRadius) const;
		TPoint SetTextPosition(TReal aTheta,TReal aRadius,TInt aOffset) const;
		void ScaleForPerspective(TReal& aX,TReal& aY) const;
		static void SetSinAndCosForTheta(TReal& aSinTheta,TReal& aCosTheta,TReal aTheta);

	private:	// Data
		TRect iPieRect;
		TReal iStartX;
		TReal iStartY;
		TReal iSum;
		TBool iShowDataAsPercentages;
		TReal iThetaTotal;
	};


/* \class MChartObserver
*    \brief This class observes the chart manager and reports if it changes
*
*
*  @lib chart
*  @since ?Series90_version
*/
class MChartObserver
	{
	public:	// Data types
		enum TChartEvent
			{
			EEventGeneralUpdate,		// refreshes all areas
			EEventSeriesChanged,		// this refers to the "diagrams" within a chart
			EEventAxesChanged,			// and all associated objects
			EEventLegendChanged		
			};

	public:	// New functions
		// Handles an event of type TChartEvent reported by the chart manager
	//	virtual void UpdateL(TChartEvent aEventType=EEventGeneralUpdate)=0;
		virtual void UpdateL()=0;
	};


/* \class MSelectionObserver
*    \brief This class simply reports if the current item is current
*
*
*  @lib chart
*  @since ?Series90_version
*/
class MSelectionObserver
	{
	public:	// New functions
		virtual TBool IsSelectedItem(const CChartManager::TChartObject aChartObject)=0;
		virtual TBool IsSelectedSeries(const TInt aSeries)=0;
	};



/* \class CChartIterator
*    \brief	This class keeps track of the objects on the current chart manager
*				and the currently selected object. It passes instructions to the 
*				chart manager to draw the selection markers.
*
*  @lib chart
*  @since ?Series90_version
*/
class CChartIterator : public CBase , public MChartObserver, public MSelectionObserver
	{
    public:  // Constructors and destructor
		static CChartIterator* NewL(const CChartManager* aChartManager);
		~CChartIterator();

	private:
		CChartIterator(const CChartManager* aChartManager);

        /**
        * By default Symbian 2nd phase constructor is private.
        */
		void ConstructL();

    public: // Functions from base classes
		// from MChartObserver
		void UpdateL();

		// from MSelectedReporter
		TBool IsSelectedItem(const CChartManager::TChartObject aChartObject);
		TBool IsSelectedSeries(const TInt aSeries);

	public:	// New functions
		IMPORT_C void Next();
		IMPORT_C void Previous();
		IMPORT_C void Reset();
		IMPORT_C TInt CurrentObject();
		IMPORT_C TInt CurrentSeries();
		inline void SetCurrentObject(TInt aObject);

	private:	// Functions from base classes
		virtual void EchoSelection();

    private:    // Data
		const CChartManager* iChartManager;
		TInt iNumberOfSeries;
		TInt iCurrentObject;
		TInt iCurrentSeries;
		TBool iObjectPresent [CChartManager::ENumObjectTypes];
	};


#include <chtstd.inl>

#endif      // CHTSTD_H
            
// End of File


