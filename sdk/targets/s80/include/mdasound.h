// MDASOUND.H
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __MDASOUND_H__
#define __MDASOUND_H__

#ifndef __E32VER_H__
#include <e32ver.h>
#endif

#define MDADEVSOUNDNAME _L8("RMdaDevSound")


class RMdaDevSound : public RBusLogicalChannel
/**
*@publishedPartner
*@released
*/
	{
public:
	enum TVer {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=KE32BuildVersionNumber};
	enum TMdaRequest
		{
		EMdaRequestPlayData,
		EMdaRequestPlayErrorNotification,
		EMdaRequestRecordData,
		EMdaRequestRecordErrorNotification
		};
	enum TMdaControl
		{
		EMdaControlPlayFormatsSupported,
		EMdaControlGetPlayFormat,
		EMdaControlSetPlayFormat,
		EMdaControlGetPlayVolume,
		EMdaControlSetPlayVolume,
		EMdaControlRecordFormatsSupported,
		EMdaControlGetRecordFormat,
		EMdaControlSetRecordFormat,
		EMdaControlGetRecordLevel,
		EMdaControlSetRecordLevel,
		EMdaControlFlushPlayBuffer,
		EMdaControlFlushRecordBuffer,
		EMdaControlBytesPlayed,
		EMdaControlResetBytesPlayed,
		EMdaControlIsMdaSound,
		EMdaControlPausePlayBuffer,
		EMdaControlResumePlaying
		};
	enum TMdaSoundEncoding
		{
		EMdaSoundEncoding8BitPCM		= 0x00000001,
		EMdaSoundEncoding16BitPCM		= 0x00000002,
		EMdaSoundEncoding8BitALaw		= 0x00000004,
		EMdaSoundEncoding8BitMuLaw		= 0x00000008,
		};


	class TSoundFormatsSupported
	/**
	*@publishedPartner
	*@released
	*/
		{
	public:
		TInt iMinRate;
		TInt iMaxRate;
		TUint32 iEncodings;
		TInt iChannels;
		TInt iMinBufferSize;
		TInt iMaxBufferSize;
		TInt iMinVolume;
		TInt iMaxVolume;
		};
	typedef TPckgBuf<TSoundFormatsSupported> TSoundFormatsSupportedBuf;


	class TCurrentSoundFormat
	/**
	*@publishedPartner
	*@released
	*/
		{
	public:
		TInt iRate;
		TMdaSoundEncoding iEncoding;
		TInt iChannels;
		TInt iBufferSize;
		};
	typedef TPckgBuf<TCurrentSoundFormat> TCurrentSoundFormatBuf;
public:
	inline TInt Open(TInt aUnit=KNullUnit);
	inline TVersion VersionRequired() const;
	inline TInt IsMdaSound();

	inline void PlayFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported);
	inline void GetPlayFormat(TCurrentSoundFormatBuf& aFormat);
	inline TInt SetPlayFormat(const TCurrentSoundFormatBuf& aFormat);
	inline TInt PlayVolume();
	inline void SetPlayVolume(TInt aVolume);
	inline void PlayData(TRequestStatus& aStatus,const TDesC8& aData);
	inline void CancelPlayData();
	inline void NotifyPlayError(TRequestStatus& aStatus);
	inline void CancelNotifyPlayError();

	inline void RecordFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported);
	inline void GetRecordFormat(TCurrentSoundFormatBuf& aFormat);
	inline TInt SetRecordFormat(const TCurrentSoundFormatBuf& aFormat);
	inline TInt RecordLevel();
	inline void SetRecordLevel(TInt aLevel);
	inline void RecordData(TRequestStatus& aStatus,TDes8& aData);
	inline void CancelRecordData();
	inline void NotifyRecordError(TRequestStatus& aStatus);
	inline void CancelNotifyRecordError();

	inline void FlushPlayBuffer();
	inline void FlushRecordBuffer();
	inline TInt BytesPlayed();
	inline void ResetBytesPlayed();
	inline void PausePlayBuffer();
	inline void ResumePlaying();
	};

#include "mdasound.inl"

#endif

