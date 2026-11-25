// EIKTIME.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKTIMED_H__
#define __EIKTIMED_H__

#include <eikdialg.h>
#include <t32wld.h>
#include <asshddefs.h>
#include <badesca.h>

enum TEikTimeViewChoice
	{
	EEikTimeViewMap,
	EEikTimeViewClock,
	EEikTimeViewLast
	};


class TEikTimeOptions
	{
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TDateFormat iDate;
	TTimeFormat iTime;
	TChar iDateSeparator;
	TChar iTimeSeparator;
	TClockFormat iClock;
	TInt iDefaultAlarmHour;
	TInt iDefaultAlarmMinute;
	TBool iUseDefaultAlarmTime;
	TWldDistanceUnits iDistance;
	TAlarmSoundName iDefaultSound;
	TEikTimeViewChoice iCurrentView;
	TBool iToolbarVisible;
	};

const TInt KEikTimeDefaultBufferLength=0xa0;
typedef TBuf<KEikTimeDefaultBufferLength> TEikTimeBuffer;

class CEikTimeDialog : public CEikDialog
	{
public:
	IMPORT_C CEikTimeDialog();
protected:
	IMPORT_C void DoSetLabelText(TInt aTagId,TInt aMessageId);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TInt iSpare;
	};


class CEikTimeDialogSetCity : public CEikTimeDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(
									TCityName&		aCity,
									TCountryName&	aCountry,
									TInt			aTitleResource, 
									TInt			aDescriptResource);
	IMPORT_C ~CEikTimeDialogSetCity();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	// from CEikDialog
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);

private: 
	CEikTimeDialogSetCity();
	void UpdateCountryListL(const TDesC* aCountry);
	void UpdateCityListL(const TDesC* aCountry, const TDesC* aCity = NULL);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();

private:
	TBool* iChanged;
	TInt iTitleResourceId;
	TInt iDescriptResourceId;
	TCityName* iCity;
	TCountryName* iCountry;
	TCountryName iCurrentCountry;
	CDesCArray* iCountryList;
	CDesCArray* iCityList;
	RWorldServer iWorldServer;
	};


class CEikTimeDialogSetTime : public CEikTimeDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(TTime& aTime);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	CEikTimeDialogSetTime();
	// from CEikDialog
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);
	void GetHelpContext(TCoeHelpContext& aContext) const;
private: 
	void GetTimeAndDateL(TTime& aTime);
	void SetTimeAndDateL(const TTime& aTime);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TTime* iTime;
	TLocale iLocale;
	};


class CEikTimeDialogSetDst : public CEikTimeDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(TUint& aDstZones,TDaylightSavingZone aHomeZone);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	CEikTimeDialogSetDst();
	// from CEikDialog
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TUint* iDstZones;
	};


class CEikTimeDialogOptionFormat : public CEikTimeDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(TEikTimeOptions& aOptions);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CEikDialog
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
private:
	CEikTimeDialogOptionFormat();
	void Data(TEikTimeOptions& aOptions) const;
	void SetData(const TEikTimeOptions& aOptions);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TBool* iChanged;
	TEikTimeOptions* iOptions;
	};


class CEikTimeDialogOptionWorkday : public CEikTimeDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(TUint& aWorkdaysFlags, TDay& aStartOfWeek);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	CEikTimeDialogOptionWorkday();
	// from CEikDialog
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TBool* iChanged;
	TUint* iWorkdayFlags;
	TDay* iStartOfWeek;
	};


#endif
