// QikTimeAndDateEditor.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Header file for the CQikTimeEditor class. A display of time, which on tapping on it will pop out a CQikTimePicker.
// Created for Quartz 6.0

#ifndef __QIKTIMEANDDATEEDITOR_H__
#define __QIKTIMEANDDATEEDITOR_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif
#ifndef __QIKTTIMEEDITOR_H__
#include <QikTTimeEditor.h>
#endif
class CQikTimePicker;

#include <eikcal.h>
/**
 * This class derives from CQikTTimeEditor and displays time and date. On a tap a TimePicker or calendar pops up.
 * this control provides time and date.
 * associated resource: QIK_TIME_AND_DATE_EDITOR
 * @since Quartz 6.0
 */
class CQikTimeAndDateEditor : public CQikTTimeEditor, MCoeControlObserver, MEikCalendarObserver
	{
public:
	IMPORT_C CQikTimeAndDateEditor();
	IMPORT_C virtual ~CQikTimeAndDateEditor();
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
public: //from MEikCalendarObserver
	void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
	void SetDateFromCalendarAndDrawNow(const TTime& aDate);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	// from CCoeControl
	IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
private:
	void CreatePopupL();
	void CreateCalendarL();
    void DestroyPopup();
	void DrawContent(CWindowGc& aGc, const TRect& aRect) const;
    void DoCreatePopupL();
	void DoCreateCalendarL();
	TTime ReadTimeDate(TResourceReader& aResourceReader);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CQikTTimeEditor
	IMPORT_C void Reserved_3();
private:
	CQikTimePicker* iTimePicker;
private:
	TInt iQikSpare2;
	};

#endif //__QIKTIMEANDDATEEDITOR_H__