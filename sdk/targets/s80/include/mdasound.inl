// MDASOUND.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TInt RMdaDevSound::Open(TInt aUnit)
	{const TPtrC8 name = MDADEVSOUNDNAME; return DoCreate(_L("Sound"),VersionRequired(),NULL,aUnit,NULL,&name);}

inline TVersion RMdaDevSound::VersionRequired() const
	{return TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber);}

inline TInt RMdaDevSound::IsMdaSound()
	{return DoControl(EMdaControlIsMdaSound);}

inline void RMdaDevSound::PlayFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported)
	{DoControl(EMdaControlPlayFormatsSupported,(TAny*)&aFormatsSupported);}

inline void RMdaDevSound::GetPlayFormat(TCurrentSoundFormatBuf& aFormat)
	{DoControl(EMdaControlGetPlayFormat,(TAny*)&aFormat);}

inline TInt RMdaDevSound::SetPlayFormat(const TCurrentSoundFormatBuf& aFormat)
	{return DoSvControl(EMdaControlSetPlayFormat,(TAny*)&aFormat);}

inline TInt RMdaDevSound::PlayVolume()
	{return DoControl(EMdaControlGetPlayVolume);}

inline void RMdaDevSound::SetPlayVolume(TInt aVolume)
	{DoControl(EMdaControlSetPlayVolume,(TAny*)aVolume);}

inline void RMdaDevSound::PlayData(TRequestStatus& aStatus,const TDesC8& aData)
	{DoRequest(EMdaRequestPlayData,aStatus,(TAny*)&aData);}

inline void RMdaDevSound::CancelPlayData()
	{DoCancel(1 << EMdaRequestPlayData);}

inline void RMdaDevSound::NotifyPlayError(TRequestStatus& aStatus)
	{DoRequest(EMdaRequestPlayErrorNotification,aStatus);}

inline void RMdaDevSound::CancelNotifyPlayError()
	{DoCancel(1 << EMdaRequestPlayErrorNotification);}

inline void RMdaDevSound::RecordFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported)
	{DoControl(EMdaControlRecordFormatsSupported,(TAny*)&aFormatsSupported);}

inline void RMdaDevSound::GetRecordFormat(TCurrentSoundFormatBuf& aFormat)
	{DoControl(EMdaControlGetRecordFormat,(TAny*)&aFormat);}

inline TInt RMdaDevSound::SetRecordFormat(const TCurrentSoundFormatBuf& aFormat)
	{return DoSvControl(EMdaControlSetRecordFormat,(TAny*)&aFormat);}

inline TInt RMdaDevSound::RecordLevel()
	{return DoControl(EMdaControlGetRecordLevel);}

inline void RMdaDevSound::SetRecordLevel(TInt aLevel)
	{DoControl(EMdaControlSetRecordLevel,(TAny*)aLevel);}

inline void RMdaDevSound::RecordData(TRequestStatus& aStatus,TDes8& aData)
	{DoRequest(EMdaRequestRecordData,aStatus,(TAny*)&aData);}

inline void RMdaDevSound::CancelRecordData()
	{DoCancel(1 << EMdaRequestRecordData);}

inline void RMdaDevSound::NotifyRecordError(TRequestStatus& aStatus)
	{DoRequest(EMdaRequestRecordErrorNotification,aStatus);}

inline void RMdaDevSound::CancelNotifyRecordError()
	{DoCancel(1 << EMdaRequestRecordErrorNotification);}

inline void RMdaDevSound::FlushPlayBuffer()
	{DoControl(EMdaControlFlushPlayBuffer);}

inline void RMdaDevSound::FlushRecordBuffer()
	{DoControl(EMdaControlFlushRecordBuffer);}

inline TInt RMdaDevSound::BytesPlayed()
	{return DoControl(EMdaControlBytesPlayed);}

inline void RMdaDevSound::ResetBytesPlayed()
	{DoControl(EMdaControlResetBytesPlayed);}

inline void RMdaDevSound::PausePlayBuffer()
	{DoControl(EMdaControlPausePlayBuffer);}

inline void RMdaDevSound::ResumePlaying()
	{DoControl(EMdaControlResumePlaying);}