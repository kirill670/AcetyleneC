// CHTSTD.INL
//
// Copyright (c) Nokia Corporation 2001-2004. All rights reserved.
//

// CChartAxes
inline const MChartTable* CChartAxes::ChartTable() const
	{return(iChartTable);}

inline CFont* CChartAxes::Font() const
	{return(iFont);} // it was iLegendFont (correct or bug)


inline TRect CChartAxes::ChartRect() const
	{return(iChartRect);}

inline TRect CChartAxes::DrawableRect() const
	{return(iDrawableRect);}

inline void CChartAxes::SetFont(CFont* aFont)
	{ iFont=aFont;}

inline void CChartAxes::SetTitleFont(CFont* aFont)
	{ iTitleFont=aFont;}

inline void CChartAxes::SetXTitleFont(CFont* aFont)
	{ iXTitleFont=aFont;}

inline void CChartAxes::SetYTitleFont(CFont* aFont)
	{ iYTitleFont=aFont;}

inline void CChartAxes::SetXLabelsFont(CFont* aFont)
	{ iXLabelsFont=aFont;}

inline void CChartAxes::SetYLabelsFont(CFont* aFont)
	{ iYLabelsFont=aFont;}

inline void CChartAxes::SetLegendFont(CFont* aFont)
	{ iLegendFont=aFont;}

inline const TPoint& CChartAxes::AxisCrossPoint() const
	{return(iAxisCrossPoint);}

inline const TDesC* CChartAxes::ChartTitle() const
	{return(iChartTitle);}

inline void CChartAxes::SetPieChart(TBool aPieChart)
	{iPieChart=aPieChart;}

inline TRgb CChartAxes::TextColor() const
	{return(iTextColor);}

inline TRgb CChartAxes::TitleColor() const
	{return(iTitleColor);}

inline TRgb CChartAxes::XTitleColor() const
	{return(iXTitleColor);}

inline TRgb CChartAxes::YTitleColor() const
	{return(iYTitleColor);}

inline TRgb CChartAxes::XLabelsColor() const
	{return(iXLabelsColor);}

inline TRgb CChartAxes::YLabelsColor() const
	{return(iYLabelsColor);}

inline TRgb CChartAxes::LegendColor() const
	{return(iLegendColor);}

inline TRgb CChartAxes::BackgroundColor() const
	{return(iBackgroundColor);}

inline TRgb CChartAxes::FrameColor() const
	{return(iFrameColor);}

inline TBool CChartAxes::HasChanged() const
	{return(iChanged);}

inline TFontUnderline CChartAxes::TitleUnderline()
	{return(iTitleFontUnderline); }

inline TFontUnderline CChartAxes::XTitleUnderline()
	{return(iXTitleFontUnderline); }

inline TFontUnderline CChartAxes::YTitleUnderline()
	{return(iYTitleFontUnderline); }

inline TFontUnderline CChartAxes::XLabelsUnderline()
	{return(iXLabelsFontUnderline); }

inline TFontUnderline CChartAxes::YLabelsUnderline()
	{return(iYLabelsFontUnderline); }

inline TFontUnderline CChartAxes::LegendUnderline()
	{return(iLegendFontUnderline); }

inline TFontStrikethrough CChartAxes::TitleStrikethrough()
	{return(iTitleFontStrikethrough); }

inline TFontStrikethrough CChartAxes::XTitleStrikethrough()
	{return(iXTitleFontStrikethrough); }

inline TFontStrikethrough CChartAxes::YTitleStrikethrough()
	{return(iYTitleFontStrikethrough); }

inline TFontStrikethrough CChartAxes::XLabelsStrikethrough()
	{return(iXLabelsFontStrikethrough); }

inline TFontStrikethrough CChartAxes::YLabelsStrikethrough()
	{return(iYLabelsFontStrikethrough); }

inline TFontStrikethrough CChartAxes::LegendStrikethrough()
	{return(iLegendFontStrikethrough); }

// CChartManager
inline void CChartManager::SetDeviceMap(MGraphicsDeviceMap* aMap)
	{iMap=aMap;}

inline void CChartManager::TitleFontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iTitleFontSpec;}

inline void CChartManager::XTitleFontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iXTitleFontSpec;}

inline void CChartManager::YTitleFontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iYTitleFontSpec;}

inline void CChartManager::XLabelsFontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iXLabelsFontSpec;}

inline void CChartManager::YLabelsFontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iYLabelsFontSpec;}

inline void CChartManager::LegendFontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iLegendFontSpec;}

inline void CChartManager::FontSpec(TFontSpec& aFontSpec) const
	{aFontSpec=iFontSpec;}

inline CChartManager::TLegendType CChartManager::LegendType() const
	{return iLegendType;}

inline CChartAxes* CChartManager::Axes() const
	{return(iChartAxes);}

inline const TDesC* CChartManager::DefaultLegendName() const
	{return iDefaultLegendName;}

inline TRect CChartManager::PhysicalSize() const
	{return(iPhysicalSize);}

inline const TDesC* CChartManager::ChartName() const
	{return(iChartName);}


// CChartDiagram
inline const TDesC* CChartDiagram::Name() const
	{return(iName);}

inline const CChartDiagram::TSymbology& CChartDiagram::Symbology() const
	{return(iSymbology);}

inline CChartDiagram::TDataLabelAlignment CChartDiagram::DataLabelAlignment() const
	{return(iDataLabelAlignment);}

inline CChartDiagram::TDataLabelType CChartDiagram::DataLabelType() const
	{return(iDataLabelType);}

inline TBool CChartDiagram::ShowDiagram() const
	{return(iShowDiagram);}

inline TRangeRef CChartDiagram::LabelRange() const
	{return(iLabelRange);}
	
inline TRangeRef CChartDiagram::DataRange() const
	{return(iDataRange);}
	
inline TInt CChartDiagram::Items() const
	{return(iDataRange.NoCells());}

inline TBool CChartDiagram::HasChanged() const
	{return(iChanged);}

inline void CChartIterator::SetCurrentObject(TInt aObject)
	{iCurrentObject=aObject;iCurrentSeries=0;EchoSelection();}

inline TBool CChartManager::Is3D() const
	{return iIs3D;}

inline CChartDiagram::TDiagramType CChartManager::ChartType() const
	{return (CChartDiagram::TDiagramType)iDiagramType;}

inline TRect CChartManager::LegendRect() const
    {return(iLegendRect);}
