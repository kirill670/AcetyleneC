// QIKDATEEDITOR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Header file for the CQikDateEditor class. A display of time, which on tapping on it will pop out a calendar
// Created for Quartz 6.0

#ifndef __QIKDATEEDITOR_H__
#define __QIKDATEEDITOR_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif
#ifndef __QIKTTIMEEDITOR_H__
#include <QikTTimeEditor.h>
#endif

#include <eikcal.h>
/**
 *
 * @short This class derives from CQikTTimeEditor and simply displays date.
 * On a tap a calendar/date picker is popped up.
 * associated resource: QIK_DATE_EDITOR
 * @since Quartz 6.0
 */
class CQikDateEditor : public CQikTTimeEditor, MEikCalendarObserver
	{
public:
	IMPORT_C CQikDateEditor();
	IMPORT_C ~CQikDateEditor();
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // from CQikTTimeEditor
	void DrawContent(CWindowGc& aGc, const TRect& aRect) const;
public: // from MEikCalendarObserver
	void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
	void SetDateFromCalendarAndDrawNow(const TTime& aDate);
protected: // from CCoeControl
	IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CQikTTimeEditor
	IMPORT_C void Reserved_3();
private:
	void CreatePopupL();
	void DoCreatePopupL();
	TTime ReadDate(TResourceReader& aResourceReader);
	};

#endif

