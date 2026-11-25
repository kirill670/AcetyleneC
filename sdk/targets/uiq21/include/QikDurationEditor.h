// QikDurationEditor.h: interface for the CQikDurationEditor class.
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Header file for the CQikDurationEditor class. A display of duration, which on tapping on it will pop out a CQikTimePicker.
// Created for Quartz 6.0

#ifndef __QIKDURATIONEDITOR_H__
#define __QIKDURATIONEDITOR_H__

#include <eikbctrl.h>
#include <QikTTimeEditor.h>

class CQikDurationPicker;

/**
 *
 * @short This class derives from CQikTTimeEditor and simply displays time. On a tap a TimePicker is popped up.
 * associated resource: QIK_DURATION_EDITOR
 * @since Quartz 6.0
 */
class CQikDurationEditor : public CQikTTimeEditor, MCoeControlObserver
	{
public:
	IMPORT_C CQikDurationEditor();
	IMPORT_C ~CQikDurationEditor();
	IMPORT_C void ConstructL(TTimeIntervalSeconds aMinimumDuration, TTimeIntervalSeconds aMaximumDuration, TTimeIntervalSeconds aInitialDuration, TUint32 aFlags);
public: // additional functions for backwards compatibility...
	IMPORT_C void SetMinimumAndMaximum(TTimeIntervalSeconds aMinimumDuration, TTimeIntervalSeconds aMaximumDuration);
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumDuration, TTimeIntervalSeconds& aMaximumDuration) const;
	IMPORT_C void SetDurationL(TTimeIntervalSeconds aDuration);
	IMPORT_C TTimeIntervalSeconds Duration() const;
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CQikTTimeEditor
	IMPORT_C void Reserved_3();
private:
	void CreatePopupL();
	void DestroyPopup();
	void DrawContent(CWindowGc& aGc, const TRect& aRect) const;
	void DoCreatePopupL();

	// miscellaneous functions
	TTime ReadDuration(TResourceReader& aResourceReader);
	TTime ConvertInterval(const TTimeIntervalSeconds& aInterval) const;
	TTimeIntervalSeconds ConvertInterval(const TTime& aInterval) const;
private:
	CQikDurationPicker* iTimePicker;
	};

#endif
