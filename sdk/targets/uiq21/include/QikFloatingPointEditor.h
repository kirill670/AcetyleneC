// QIKFLOATINGPOINTEDITOR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKFLOATINGPOINTEDITOR_H__
#define __QIKFLOATINGPOINTEDITOR_H__

#include <qiknumericeditor.h>
/**
 * this class provides a control to edit single floating point value.
 * associated resource: QIK_FLOATING_POINT_EDITOR
 *
 **/
class CQikFloatingPointEditor : public CQikNumericEditor
	{
public:
	IMPORT_C CQikFloatingPointEditor();
	IMPORT_C ~CQikFloatingPointEditor();
	IMPORT_C void ConstructL(TReal aMinimumValue, TReal aMaximumValue, TInt aTextLimit);
	IMPORT_C TReal Value() const;
	IMPORT_C void SetValueL(TReal aValue);
	IMPORT_C void GetMinimumAndMaximum(TReal& aMinimum, TReal& aMaximum) const;
	IMPORT_C void SetMinimumAndMaximum(TReal aMinimum, TReal aMaximum);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
protected: // from CQikNumericEditor
	IMPORT_C TBool ValidateKeyEvent(const TKeyEvent& aKeyEvent, TEventCode aType) const;
	IMPORT_C TBool ValidateTextL(const TDes& aText) const;
protected: // from CCoeControl
	IMPORT_C void PrepareForFocusLossL();
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CQikNumericEditor
	IMPORT_C void Reserved_3();
private:
	TReal iMinimumValue;
	TReal iMaximumValue;
	mutable TReal iCurrentValue;
private:
	TReal iQikSpare2;
	};

#endif
