// QIKTTIMEEDITOR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Header file for the CQikTTimeEditor class. The base class for time, date, time/date and duration editors.
//
// Created for Quartz 6.0
//////////////////////////////////////////////////////////////////////

#ifndef __QIKTTIMEEDITOR_H__
#define __QIKTTIMEEDITOR_H__

#include <eikbctrl.h>
/**
 * this class provides methods and members for time and date handling.
 * The base class for time, date, time/date and duration editors
 * it's inherited by QikTimeEditor, by QikDateEditor, by QikTimeAndDateEditor and by QikDurationEditor
 *
 **/
class CQikTTimeEditor : public CEikBorderedControl
	{
public:
	enum
		{
		EWithoutPopoutCalendar	= 1,
		EWithoutPopoutPicker	= 2,
		EForce24HourFormat		= 4,
		EFiveMinuteSteps		= 8
		};
public:
	virtual ~CQikTTimeEditor();
	IMPORT_C void ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime);
	IMPORT_C void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximumTime) const;
	IMPORT_C void SetTimeL(const TTime& aTime);
	IMPORT_C TTime Time() const;
	IMPORT_C const CFont* Font() const;
	IMPORT_C void SetFont(const CFont* aFont);
public: // from CCoeControl
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C TSize MinimumSize();
protected:
	CQikTTimeEditor();
	IMPORT_C void Draw(const TRect& aRect) const;
	virtual void DrawContent(CWindowGc& aGc, const TRect& aRect) const = 0;

	void PrepareGc(CWindowGc& aGc) const;
	TRect InnerRect(const TRect& aRect) const;
	void DrawText(CWindowGc& aGc, const TDesC& aText, const TRect& aRect) const;
	void UpdateTimeStringL();
	void UpdateDateStringL();
	TInt MaximumTimeWidth() const;
	TInt MaximumDateWidth() const;

	TUint32& Flags();
	const TPtrC TimeString() const;
	const TPtrC DateString() const;
	TTime MinTime() const;
	TTime MaxTime() const;
	TTime CurrentTime() const;
	void SetCurrentTime(TTime aTime);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void Reserved_3();
private:
	TUint32 iFlags;
	TBuf<20> iTimeString;
	TBuf<30> iDateString;
	TTime iMinTime;
	TTime iMaxTime;
	TTime iCurrentTime;
	const CFont* iFont;
private:
	TInt QikSpare1;
	};

#endif
