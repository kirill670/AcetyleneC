// D32SND.INL
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//



inline TSineInfo::TSineInfo(TInt aFrequency,TInt aVolume,TTimeIntervalMicroSeconds32 aDuration)
	: iFrequency(aFrequency),iVolume(aVolume),iDuration(aDuration)
	{}

_LIT(KRDevSound,"Sound");
inline TInt RDevSound::Open(TInt aUnit)
	{return DoCreate(KRDevSound,VersionRequired(),NULL,aUnit,NULL,NULL);}

inline TVersion RDevSound::VersionRequired() const
	{return TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber);}

inline void RDevSound::PlaySineWave(TRequestStatus& aStatus,TInt aFrequency,TInt aVolume,TTimeIntervalMicroSeconds32 aDuration)
	{TSineInfo sineInfo(aFrequency,aVolume,aDuration);DoRequest(ERequestPlay,aStatus,(TAny*)EPlaySineWave,&sineInfo);}

inline void RDevSound::PlayDtmf(TRequestStatus& aStatus,const TDesC& aDes)
	{DoRequest(ERequestPlay,aStatus,(TAny*)EPlayDtmf,(TAny*)&aDes);}

inline void RDevSound::PlayAlarmSound(TRequestStatus& aStatus,TInt aAlarm)
	{DoRequest(ERequestPlay,aStatus,(TAny*)EPlayAlarmSound,(TAny*)aAlarm);}

inline void RDevSound::PlayFallBackAlarmSound(TRequestStatus& aStatus)
	{DoRequest(ERequestPlay,aStatus,(TAny*)EPlayFallBackAlarmSound);}

inline void RDevSound::PlayAlawData(TRequestStatus& aStatus,const TDesC8& aData)
	{DoRequest(ERequestPlay,aStatus,(TAny*)EPlayAlawData,(TAny*)&aData);}

inline void RDevSound::FlushPlayBuffer()
	{DoControl(EControlFlushPlayBuffer);}

inline void RDevSound::PlayCancel()
	{DoCancel(ERequestPlayCancel);}

inline void RDevSound::RecordAlawData(TRequestStatus& aStatus,TDes8& aData)
	{DoRequest(ERequestRecord,aStatus,(TAny*)&aData);}

inline void RDevSound::FlushRecordBuffer()
	{DoControl(EControlFlushRecordBuffer);}

inline void RDevSound::RecordCancel()
	{DoCancel(ERequestRecordCancel);}

inline TInt RDevSound::AlarmSoundCount()
	{return DoControl(EControlGetAlarmSoundCount);}

inline TInt RDevSound::AlarmSoundName(TInt anIndex,TName& aName)
	{return DoControl(EControlGetAlarmSoundName,&anIndex,&aName);}

inline void RDevSound::Config(TDes8& aConfig)
	{DoControl(EControlConfig,&aConfig);}

inline TInt RDevSound::SetConfig(const TDesC8& aConfig)
	{return DoControl(EControlSetConfig,(TAny*)&aConfig);}

inline void RDevSound::Caps(TDes8& aCaps)
	{DoControl(EControlCaps,&aCaps);}

inline TInt RDevSound::PreparePlayAlawBuffer()
	{return DoSvControl(EControlPreparePlayAlawBuffer);}

inline TInt RDevSound::PrepareRecordAlawBuffer()
	{return DoSvControl(EControlPrepareRecordAlawBuffer);}

inline TInt RDevSound::BytesPlayed()
	{return DoControl(EControlBytesPlayed);}

inline void RDevSound::ResetBytesPlayed()
	{DoControl(EControlResetBytesPlayed);}
