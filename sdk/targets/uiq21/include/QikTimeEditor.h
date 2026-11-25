// QIKTIMEEDITOR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Header file for the CQikTimeEditor class. A display of time, which on tapping on it will pop out a CQikTimePicker.
// Created for Quartz 6.0

#ifndef __QIKTIMEEDITOR_H__
#define __QIKTIMEEDITOR_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif
#ifndef __QIKTTIMEEDITOR_H__
#include <QikTTimeEditor.h>
#endif
class CQikTimePicker;


/**
 * @Short This class derives from CQikTTimeEditor and simply displays time.
 * On a tap a TimePicker is popped up. this class provides time on its own.
 * associated resource: QIK_TIME_EDITOR
 *
 * @since Quartz 6.0
 */
class CQikTimeEditor : public CQikTTimeEditor, MCoeControlObserver
	{
public:
	// miscellaneous functions
	IMPORT_C CQikTimeEditor();
	IMPORT_C ~CQikTimeEditor();
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
protected:
	void CreatePopupL();
    void DestroyPopup();
	void DrawContent(CWindowGc& aGc, const TRect& aRect) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
    void DoCreatePopupL();
	// from CCoeControl
	IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
	// miscellaneous functions
	TTime ReadTime(TResourceReader& aResourceReader);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CQikTTimeEditor
	IMPORT_C void Reserved_3();
private:
	CQikTimePicker* iTimePicker;
private:
	TInt iQikSpare2;
	};

#endif

