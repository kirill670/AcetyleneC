// Mda\Common\MmfAudio.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MMF_COMMON_AUDIO_H__
#define __MMF_COMMON_AUDIO_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes

#include <Mmf\Common\MmfBase.h>
#include <Mmf\Common\MmfUtilities.h>

/**
 * @publishedAll
 * Audio Loading started event. Use by a controller to signal to a 
 * client that audio loading has begun
 * @since 7.0s
 */
const TUid KMMFEventCategoryAudioLoadingStarted = {0x101F8002};
/**
 * @publishedAll
 * Audio Loading completed event.Use by a controller to signal to a 
 * client that audio loading has completed.
 * @since 7.0s
 */
const TUid KMMFEventCategoryAudioLoadingComplete = {0x101F8003};

/**
 * @publishedAll
 * @released
 * class defining callback interface for receiving loading notifications
 *
 * since 7.0s
 */
class MAudioLoadingObserver
	{
public:
	/*
	 * Audio Loading/rebuffering has begun
	 * since 7.0s
	 */
	virtual void MaloLoadingStarted() = 0;
	/*
	 * Audio Loading/rebuffering has completed
	 * since 7.0s
	 */
	virtual void MaloLoadingComplete() = 0;
	};

/**
 * @publishedAll
 * @released
 * class used when sending custom commands from the client API
 * to the audio controller to get or set the audio configuration
 *
 */
class TMMFAudioConfig
	{
public:
	inline TMMFAudioConfig();
	inline void SetReturnSize(TInt aReturnSize);
public:
	// Audio device command parameters
	/** 
	 * The volume setting. This can be any value from zero to iMaxVolume
	 */
	TInt iVolume;
	TInt iMaxVolume;

	/**
	 * The balance. Must be between -100 and 100
	 */
	TInt iBalance;
	/**
	 * The gain.  This can be any value from zero to iMaxGain
	 */
	TInt iGain;
	TInt iMaxGain;
	/**
	 *	If ETrue, remove a portion from the clip from the current position to the end.
	 */
	TBool iCropToEnd ;

	/**
	 * Mono/Stereo setting
	 */
	TUint iChannels;
	/**
	 * indicates the sampling rate.
	 */
	TUint iSampleRate;
	/**
	 * The format uid to be used
	 */
	TUid iFormatUid;
	/**
	 * The data type of the source of the codec
	 */
	TFourCC iSourceDataTypeCode;
	/**
	 * The data type of the sink of the codec.
	 */
	TFourCC iSinkDataTypeCode;
	/**
	 * The start position for playback in micro seconds
	 */
	TTimeIntervalMicroSeconds iStartPosition ;
	/**
	 * The end position for playback in micro seconds
	 */
	TTimeIntervalMicroSeconds iEndPosition ;
	/**
	 * The period over which the volume is to rise. A zero value causes 
	 * the tone sample to be played at the normal level for the full
	 * duration of the playback. 
	 * Supported only during tone playing.
	 */
	TTimeIntervalMicroSeconds iRampDuration ;
	/**
	 * 	Get the (possibly estimated) record time left in the clip.
	 */
	TTimeIntervalMicroSeconds iRecordTimeAvailable ;
	/**
	 * Set the maximum duration of the recorded clip, in microseconds
	 */
	TTimeIntervalMicroSeconds iMaxDuration ;
	/**
	 * 	Set the maximum size of the recorded clip, in bytes.
	 */
	TInt iMaxFileSize ;
	/**
	 *  The current state of the sound device.
	 */
	TInt iState ;
	/**
	 *  The current completion status of loading/rebuffering
	 */
	TInt iLoadingCompletePercentage;
	};

inline TMMFAudioConfig::TMMFAudioConfig() {};

#endif
