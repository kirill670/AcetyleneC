// QIKNUMERICEDITOR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKNUMERICEDITOR_H__
#define __QIKNUMERICEDITOR_H__

#include <coecntrl.h>

class CQikNumericEditorEdwin;
class CEikEdwin;

/**
 * base class for numeric-edit controls
 * it's inherited by CQikNumberEditor and by CQikFloatingPointEditor
 **/
class CQikNumericEditor : public CCoeControl, public MCoeControlObserver
	{
public:
	IMPORT_C ~CQikNumericEditor();
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C const CEikEdwin& Edwin() const;	
protected:
	IMPORT_C CQikNumericEditor();
	IMPORT_C void BaseConstructL(TInt aTextLimit, TBool aSpinnerArrows=ETrue);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void GetTextL(TDes& aText) const;
	IMPORT_C virtual void IncreaseValueL();
	IMPORT_C virtual void DecreaseValueL();
	IMPORT_C virtual TBool ValidateKeyEvent(const TKeyEvent& aKeyEvent, TEventCode aType) const;
	IMPORT_C virtual TBool ValidateTextL(const TDes& aText) const;
protected: // from CCoeControl
	IMPORT_C void SizeChanged();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;	
protected: //from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void Reserved_3();
	TBool ValidateCopyPasteEvent(const TKeyEvent& aKeyEvent, TEventCode aType);
	void DoPasteL();
	void DrawSpinnerArrow() const;
private:
	CQikNumericEditorEdwin* iEdwin;
	TRect iIncreaseArrowRect;
	TRect iDecreaseArrowRect;
	TBool iSpinnerArrows;
private:
	TInt iQikSpare1;
	};

#endif
