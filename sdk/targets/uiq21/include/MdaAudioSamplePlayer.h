// MdaAudioSamplePlayer.h 
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOSAMPLEPLAYER_H__
#define __MDAAUDIOSAMPLEPLAYER_H__

/*
Notes:
 This file defines a simple sound data playing utility API.
  
Classes:
CMdaAudioPlayerUtility
 The interface to a simple sound data (file or descriptor) playing utility. 
 It is capable of playing sounds in any format recognised by the Media Server.

MMdaAudioPlayerCallback
 Mixin class that defines callback interface used for asynchronous 
 notification.

Usage:
 "NewFilePlayerL" is used to create an instance of a file player.
 "NewDesPlayerL" is used to create a descriptor player. If a descriptor is 
 used as the data source, it must remain valid until the player object has 
 been destroyed. In either case, the data must be a recognised file format
 such as a WAV, AU, or WVE with a supported encoding scheme.
 
 The player object will call "MMdaAudioPlayerCallback::MapcInitComplete" when 
 it has been initialised and is ready to play the sound.

 "Play" will begin playback.

 "Stop" can be used to end playback.

 If the end of the sound data is reached, playback will terminate 
 automatically and "MMdaAudioPlayerCallback::MapcPlayComplete" will be called 
 with aErr==KErrNone.

 If playback terminates for any other reason (such as interruption by a higher
 priority sound playing event) "MMdaAudioPlayerCallback::MapcPlayComplete" 
 will be called with the appropriate error value.

 "SetVolume" can be used to change the volume both before or during playback.
 The parameter should be between 0 and the result returned by calling 
 "MaxVolume"

*/

#include <e32base.h>
#include <Mda\Common\Controller.h>

class CMdaServer;

const TInt KMdaAudioPlayerUnknownDuration = -1;
const TInt KMdaAudioPlayerRepeatForever = -2;

enum TAudioPlayerUtilityPanics
	{
	EMdaAudioPlayerAPIFileAlreadyPlaying = 0,
	EMdaAudioPlayerAPINotReady = 1,
	EMdaAudioPlayerAPIVolumeOutofRange = 2
	};

/**
 *
 * An interface to a set of audio player callback functions.
 *
 * The class is a mixin and is intended to be inherited by the client
 * class which is observing the audio playing operation. The functions
 * encapsulated by this class are called when specific events occur in
 * the process of initialising and playing an audio sample.A reference to
 * this object is passed as a parameter when constructing an audio player
 * utility object.
 *
 * @since 5.0
 */
class MMdaAudioPlayerCallback
	{
public: 

/**
 *
 * Defines required client behaviour when an attempt to open and
 * initialise an audio sample has completed, successfully or otherwise.
 *
 * @param     "TInt aError"
 *            The status of the audio sample after initialisation.
 *            The following values have the same specific meaning
 *            across all EPOC platforms: <code>KErrNone</code> the
 *            sample is ready to play. <code>KerrNotSupported</code>
 *            the audio format or particular encoding type is not
 *            recognised or not supported. <code>KErrNotFound</code>
 *            the audio sample cannot be found.
 *            <code>KErrNoMemory</code> there is insufficient memory
 *            to play this audio sample. Other values are possible
 *            indicating a problem opening the audio sample. These
 *            values are dependent on the EPOC platform.
 * @param     "const TTimeIntervalMicroSeconds& aDuration"
 *            The duration of the audio sample.
 */
	virtual void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration)=0;

/**
 *
 * Defines required client behaviour when an attempt to playback an audio
 * sample has completed, successfully or otherwise.
 *
 * @param     "TInt aError"
 *            The status of playback. The following values have the
 *            same specific meaning across all EPOC platforms:
 *            <code>KErrNone</code> playing of the audio sample is
 *            complete.<code>KErrCorrupt</code> the sample data is
 *            corrupt. <code>KErrInUse</code> the sound device is in
 *            use by another higher priority client. This can happen
 *            during playback.<code>KErrNoMemory</code> there is
 *            insufficient memory to play this audio sample Other
 *            values are possible indicating a problem opening the
 *            audio sample. These values are dependent on the EPOC
 *            platform.
 */
	virtual void MapcPlayComplete(TInt aError)=0;
	};

/**
 *
 * Plays sampled audio data.
 *
 * The class offers a simple interface to open, play and obtain
 * information from, sampled audio data. The audio data can supplied
 * either in a file (file-based) or as a descriptor
 * (descriptor-based).While this class is abstract, the three static
 * functions construct, initialise and return pointers to instances of
 * concrete classes derived from this abstract class. This concrete class
 * is part of the Media Server implementation and is private.
 *
 * @since 5.0
 * @lib "MediaClientAudio.lib"
 */
class CMdaAudioPlayerUtility : public CBase
	{
public:
	IMPORT_C static CMdaAudioPlayerUtility* NewFilePlayerL(const TDesC& aFileName, MMdaAudioPlayerCallback& aCallback, TInt aPriority=EMdaPriorityNormal, TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality, CMdaServer* aServer=NULL);
	IMPORT_C static CMdaAudioPlayerUtility* NewDesPlayerL(TDes8& aData, MMdaAudioPlayerCallback& aCallback, TInt aPriority=EMdaPriorityNormal, TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality, CMdaServer* aServer=NULL);	
	IMPORT_C static CMdaAudioPlayerUtility* NewDesPlayerReadOnlyL(const TDesC8& aData, MMdaAudioPlayerCallback& aCallback, TInt aPriority=EMdaPriorityNormal, TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality, CMdaServer* aServer=NULL);	

/**
 *
 * Begins playback of the initialised audio sample at the current volume
 * and priority levels.
 *
 * When playing of the audio sample is complete, successfully or
 * otherwise, the callback function
 * <code>MMdaAudioPlayerCallback::MapcPlayComplete()</code> is
 * called.This function raises a CMdaAudioPlayerUtility 1 panic if the
 * audio player utility is not initialised.
 *
 */
	virtual void Play()=0;

/**
 *
 * Stops playback of the audio sample as soon as possible.
 *
 * If the audio sample is playing, playback is stopped as soon as
 * possible. If playback is already complete, nothing further happens as
 * a result of calling this function.The callback function
 * <code>MMdaAudioPlayerCallback::MapcPlayComplete()</code> is not
 * called.The function raises a CMdaAudioPlayerUtility 1 panic if the
 * audio player utility is not initialised.
 *
 */
	virtual void Stop()=0;

/**
 *
 * Changes the current playback volume to a specified value.
 *
 * The volume can be changed before or during playback and is effective
 * immediately.The function raises a CMdaAudioPlayerUtility 1 panic if
 * the audio player utility is not initialised.
 *
 * @param     "TInt aVolume"
 *            The volume setting. This can be any value from zero to
 *            the value returned by a call to
 *            <code>CMdaAudioPlayerUtility::MaxVolume()</code>.
 *            Setting a zero value mutes the sound. Setting the
 *            maximum value results in the loudest possible sound.
 */
	virtual void SetVolume(TInt aVolume)=0;

/**
 *
 * Sets the number of times the audio sample is to be repeated during the
 * playback operation.
 *
 * A period of silence can follow each playing of the sample. The audio
 * sample can be repeated indefinitely.
 *
 * @param     "TInt aRepeatNumberOfTimes"
 *            The number of times the audio sample, together with
 *            the trailing silence, is to be repeated. If this is
 *            set to <code>KMdaRepeatForever</code>, then the audio
 *            sample, together with the trailing silence, is
 *            repeated indefinitely or until <code>Stop()</code> is
 *            called. If this is set to zero, then the audio sample
 *            is not repeated.
 * @param     "const TTimeIntervalMicroSeconds&
				  aTrailingSilence"
 *            The time interval of the training silence.
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence)=0;

/**
 *
 * Defines the period over which the volume level is to rise smoothly
 * from nothing to the normal volume level.
 *
 * @param     "const TTimeIntervalMicroSeconds& aRampDuration"
 *            The period over which the volume is to rise. A zero
 *            value causes the audio sample to be played at the
 *            normal level for the full duration of the playback. A
 *            value which is longer than the duration of the audio
 *            sample means that the sample never reaches its normal
 *            volume level.
 */
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;

/**
 *
 * Returns the duration of the audio sample.
 *
 * The function raises a CMdaAudioPlayerUtility 1 panic if the audio
 * player utility is not initialised.
 *
 * @returns   "TTimeIntervalMicroSeconds&"
 *            The duration in microseconds
 */
	virtual const TTimeIntervalMicroSeconds& Duration()=0;

/**
 *
 * Returns an integer representing the maximum volume.
 *
 * This is the maximum value which can be passed to
 * <code>CMdaAudioPlayerUtility::SetVolume()</code>.The function raises a
 * CMdaAudioPlayerUtility 1 panic if the audio player utility is not
 * initialised.
 *
 * @returns   "TInt"
 *            The maximum volume. This value is platform dependent
 *            but is always greater than or equal to one.
 */
	virtual TInt MaxVolume()=0;
	};

#endif
