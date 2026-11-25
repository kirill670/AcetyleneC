// D32SND.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __D32SND_H__
#define __D32SND_H__
#ifndef __E32STD_H__
#include <e32std.h>
#endif
#ifndef __E32VER_H__
#include <e32ver.h>
#endif

const TInt KAlawSamplesPerSecond=8000;
const TInt KAlawSilence=0x55;
const TInt KMaxSineWaveVolume=100;

enum TSoundVolume {EVolumeNone,EVolumeSoft,EVolumeMedium,EVolumeLoud,EVolumeByValue};


class TSoundConfigV01
/**
*@publishedPartner
*@released
*/
    {
public:
	TSoundVolume iVolume;
	TInt iVolumeValue;
	TTimeIntervalMicroSeconds32 iDtmfToneOnLength;
	TTimeIntervalMicroSeconds32 iDtmfToneOffLength;
	TTimeIntervalMicroSeconds32 iDtmfPauseLength;
	TInt iAlawBufferSize;
	};
typedef TPckgBuf<TSoundConfigV01> TSoundConfig;
//
const TUint KCapsVolumeNone=0x00000001;
const TUint KCapsVolumeSoft=0x00000002;
const TUint KCapsVolumeMedium=0x00000004;
const TUint KCapsVolumeLoud=0x00000008;
const TUint KCapsVolumeByValue=0x00000010;
//
const TUint KCapsDtmfAvailable=0x00000001;
const TUint KCapsFallBackAlarmSoundAvailable=0x00000002;
const TUint KCapsPlayAlawDataAvailable=0x00000004;
const TUint KCapsRecordAlawDataAvailable=0x00000008;
const TUint KCapsSimultaneousPlayAndRecordAvailable=0x00000010;


class TSoundCapsV01
/**
*@publishedPartner
*@released
*/
	{
public:
	TUint iService;
	TUint iVolume;
	TInt iMaxVolume;
	TInt iMaxFrequency;
	};
typedef TPckgBuf<TSoundCapsV01> TSoundCaps;


class TCapsDevSoundV01
/**
*@publishedPartner
*@released
*/
	{
public:
	TVersion version;
	};


class TSineInfo
/**
*@publishedPartner
*@released
*/
	{
public:
	inline TSineInfo(TInt aFrequency,TInt aVolume,TTimeIntervalMicroSeconds32 aDuration);
	TInt iFrequency;
	TInt iVolume;//0 to KMaxSineWaveVolume
	TTimeIntervalMicroSeconds32 iDuration;
	};

//This was the ER5 interface to the sound driver
//this is no longer used except for some methods
//that use some of the structures defined by this class.
//This class is no longer derived from RBusLogicalChannel as a result
//This class is only an 'R' class for backwards compatibility
class RDevSound
/**
*@publishedPartner
*@released
*/
	{
public:
	enum TVer {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=KE32BuildVersionNumber};
	enum TRequest
		{
		ERequestPlay=0x0,ERequestRecord=0x1,
		ERequestPlayCancel=0x1,ERequestRecordCancel=0x2
		};
	enum TControl
		{
		EControlGetAlarmSoundCount,EControlGetAlarmSoundName,
		EControlConfig,EControlSetConfig,EControlCaps,
		EControlPreparePlayAlawBuffer,EControlPrepareRecordAlawBuffer,
		EControlFlushPlayBuffer,EControlFlushRecordBuffer,
		EControlBytesPlayed,EControlResetBytesPlayed
		};
	enum TPlayType
		{
		EPlayAlawData,EPlayAlarmSound,EPlayFallBackAlarmSound,EPlayDtmf,EPlaySineWave
		};
//The methods for ER5 interface to the sound drivers have been removed
//as they are no longer used.
	};
#endif

