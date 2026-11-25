// QIKCOLORSELECTOR.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
// Created for Quartz 6.0


#ifndef __QIKCOLORSELECTOR_H__
#define __QIKCOLORSELECTOR_H__

#include <eikchlst.h>	// class CEikChoiceListBase

/**
 * this class provides a Colour selector control that allows the user to select a colour from a colour or grey-scale palette.
 * associated resource QIK_COLOR_SEL
 * The palette is available as its own control, CQikColorPicker.
 *
 **/
class CQikColorPicker;

class CQikColorSelector : public CEikChoiceListBase
	{
public:
	IMPORT_C CQikColorSelector();
	IMPORT_C ~CQikColorSelector();
	IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags);
	IMPORT_C TRgb SelectedColor() const;
	IMPORT_C void SetSelectedColor(TRgb aColor);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
protected: // from CEikChoiceListBase
	IMPORT_C void CreatePopoutL();
	IMPORT_C void DestroyPopout();
	IMPORT_C void DrawContent() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikChoiceListBase
	IMPORT_C void Reserved_3();
private:
	void DoCreatePopoutL();
	void CreateStandardPaletteL();
	void CreateCustomPaletteL(TResourceReader& aReader);
private:
	TInt iSelectorFlags;
	CPalette* iPalette;
	CQikColorPicker* iPicker;
	};

#endif // __QIKCOLORSELECTOR_H__
