// QIKNUMBEREDITOR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKNUMBEREDITOR_H__
#define __QIKNUMBEREDITOR_H__

#include <qiknumericeditor.h>

/**
 * this class provides a control to edit single integer value.
 * associated resource: QIK_NUMBER_EDITOR
 **/
class CQikNumberEditor : public CQikNumericEditor
	{
public:
	IMPORT_C CQikNumberEditor();
	IMPORT_C ~CQikNumberEditor();
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue);
	IMPORT_C TInt Value() const;
	IMPORT_C void SetValueL(TInt aValue);
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimum, TInt& aMaximum) const;
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimum, TInt aMaximum);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
protected: // from CQikNumericEditor
	IMPORT_C void IncreaseValueL();
	IMPORT_C void DecreaseValueL();
	IMPORT_C TBool ValidateKeyEvent(const TKeyEvent& aKeyEvent, TEventCode aType) const;
	IMPORT_C TBool ValidateTextL(const TDes& aText) const;
protected: // from CCoeControl
	IMPORT_C void PrepareForFocusLossL();
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void ChangeValueL(TInt aOffset);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CQikNumericEditor
	IMPORT_C void Reserved_3();
private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	mutable TInt iCurrentValue;
private:
	TInt iQikSpare2;
	};

#endif
