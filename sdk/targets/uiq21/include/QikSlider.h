// QIKSLIDER.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKSLIDER_H__
#define __QIKSLIDER_H__

#include <coecntrl.h>

/**
 * This class provides a slider control that can be used to set the value of a parameter such as contrast, brightness, volume, etc.
 * associated resource: QIK_SLIDER
 **/
class CQikSlider : public CCoeControl
	{
public:
	enum TFlags
		{
		ESnapToMarkers = 0x0001,
		EVerticalLayout = 0x0002
		};

	IMPORT_C CQikSlider();
	IMPORT_C ~CQikSlider();
	IMPORT_C void ConstructL(TInt aMinValue, TInt aMaxValue, TInt aFlags = 0);
	IMPORT_C TInt CurrentValue() const;
	IMPORT_C void SetNumberOfMarkersL(TInt aNumberOfMarkers);
	IMPORT_C void SetValue(TInt aValue);
	IMPORT_C void SetMinValueL(TInt aMinValue);
	IMPORT_C void SetMaxValueL(TInt aMaxValue);
public:	// from CoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader &aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
protected: // from CCoeControl
	IMPORT_C void SizeChanged();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
private:
	void DrawRailTrack() const;
	void DrawIndicator() const;
	void DrawMarkers() const;
	void PlotMarker(TInt aMarkerOffset) const;
	void CalculateMarkersL();
	TInt PixelToValueSnap(TInt aPixel) const;
	TInt PixelToValue(TInt aPixel) const;
	TInt ValueToPixelSnap(TInt aValue)const;
	TInt ValueToPixel(TInt aValue)const;
	void UpdateIndicatorNow() const;
private:
	CArrayFix<TInt>* iMarkerPosArray;
	CArrayFix<TInt>* iValuePosArray;
	TInt iCurrentValue;
	mutable TInt iOldXPixel;
	TInt iNumberOfMarkers;
	TInt iRailTrackOffset;
	TInt iSliderFlags;
	TInt iMinValue;
	TInt iMaxValue;
private:
	TInt iSpare;
	};

#endif



