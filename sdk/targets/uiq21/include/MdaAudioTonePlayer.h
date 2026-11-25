// MdaAudioTonePlayer.h 
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

//
// Notes:
//
// This file defines the API for generating various types of audio
// tones on an EPOC device.
//
// Tone types include:
//
// 1. Simple (sine) tone of specified frequency and duration
// 2. DTMF sequence consisting of characters 0-9 A-F * # , and white space
// 3. Fixed sequence from a list (including human readable names)
// 4. Sequence from file or descriptor (data format is platform specific)
//

#ifndef __MDAAUDIOTONEPLAYER_H__
#define __MDAAUDIOTONEPLAYER_H__

#include <Mda\Common\Audio.h>
#include <Mda\Client\Controller.h>

class CMdaServer; // Forward reference

enum TMdaTonePlayerPanic
	{
	EMdaTonePlayerPanicNotReady=0,
	EMdaTonePlayerPanicBusyPreparing=1,
	EMdaTonePlayerPanicBusyPlaying=2,
	EMdaTonePlayerPanicInvalidSequenceNumber=3,
	EMdaTonePlayerPanicVolumeOutOfRange=4,
	EMdaTonePlayerPanicInvalidDuration=5,
	EMdaTonePlayerPanicInvalidRepeatCount=6
	};

enum TMdaAudioToneUtilityState
	{
	EMdaAudioToneUtilityNotReady=0,
	EMdaAudioToneUtilityPrepared,
	EMdaAudioToneUtilityPlaying
	};


//
// Pass KInfiniteDurationDTMFToneOnLength as 
// aToneOnLength parameter to SetDTMFLengths()
// to play only the first DTMF tone of supplied 
// string until CancelPlay() is called
//
const TInt KMdaInfiniteDurationDTMFToneOnLength = -1; 
const TInt KMdaAudioToneRepeatForever = -2;


/**
 *
 * An interface to a set of audio tone player callback functions.
 *
 * The class is a mixin and is intended to be inherited by the client
 * class which is observing the audio tone playing operation. The
 * functions encapsulated by this class are called when specific events
 * occur in the process of preparing to play a tone and during the
 * playing of a tone. A reference to this object is passed as a
 * parameter when constructing an audio tone player utility, using the
 * <code>CMdaAudioToneUtility</code> interface.
 *
 * @since 5.0
 * @lib "MediaClientAudio.lib"
 */
class MMdaAudioToneObserver
	{
public:

/**
 *
 * Defines required client behaviour when an attempt to configure the
 * audio tone player utility has completed, successfully or otherwise.
 *
 * @param     "TInt aError"
 *            <code>KErrNone</code> if successful. One of the system
 *            wide error codes if the attempt failed. The possible
 *            values depend on the EPOC platform.
 */
	virtual void MatoPrepareComplete(TInt aError)=0;

/**
 *
 * Defines required client behaviour when the tone playing operation has
 * completed, successfully or otherwise.
 *
 * @param     "TInt aError"
 *            <code>KErrNone</code> if successful. One of the system
 *            wide error codes if the attempt failed. The possible
 *            values depend on the EPOC platform.
 */
	virtual void MatoPlayComplete(TInt aError)=0;
	};

/**
 *
 * Generates tones on an audio capable EPOC device.
 *
 * The class offers an interface for generating tones on all audio
 * capable EPOC devices.While this class is abstract, the static function
 * constructs, initialises and returns a pointer to an instance of a
 * concrete class derived from this abstract class. This concrete class
 * is part of the Media Server implementation and is private.
 * 
 * To use the tone utility:
 * 1. Create an instance by calling NewL
 * 2. Call the appropriate PrepareToPlay variant for the required tone type
 *    and wait for the callback indicating success
 * 3. Call Play and either wait for the callback to indicate completion, 
 *    or call CancelPlay to end playback early
 * 4. Delete the instance
 *
 * @since 5.0
 * @lib " MediaClientAudio.lib "
 */
class CMdaAudioToneUtility : public CBase
	{
public:
	IMPORT_C static CMdaAudioToneUtility* NewL(MMdaAudioToneObserver& aObserver, CMdaServer* aServer=NULL);

/**
 *
 * Returns the current state of the audio tone utility.
 *
 * @returns   "TMdaAudioToneUtilityState"
 *            The state of the audio tone utility.
 */
	virtual TMdaAudioToneUtilityState State()=0;

/**
 *
 * Returns an integer representing the maximum volume.
 *
 * This is the maximum value which can be passed
 * to<code>CMdaAudioToneUtility::SetVolume()</code>.
 *
 * @returns   "TInt"
 *            The maximum volume. This value is platform dependent
 *            but is always greater than or equal to one.
 */
	virtual TInt MaxVolume()=0;

/**
 *
 * Returns an integer representing the current volume of the audio
 * device.
 *
 * @returns   "TInt"
 *            The volume of the audio device.
 */
	virtual TInt Volume()=0;

/**
 *
 * Changes the volume of the audio device.
 *
 * The volume can be changed before or during play and is effective
 * immediately.
 *
 * @param     "TInt aVolume"
 *            The volume setting. This can be any value from zero to
 *            the value returned by a call to
 *            <code>CMdaAudioToneUtility::MaxVolume()</code>.
 *            Setting a zero value mutes the sound. Setting the
 *            maximum value results in the loudest possible sound.
 */
	virtual void SetVolume(TInt aVolume)=0;

/**
 *
 * Changes the clients priority.
 *
 * @param     "TInt aPriority"
 *            This client's relative priority. This is a value
 *            between -100 and +100 and represents a relative
 *            priority. A higher value indicates a more important
 *            request. The absolute priority at which a client
 *            application runs depends on the EPOC platform.
 * @param     "TMdaPriorityPreference aPref"
 *            The required behaviour if a higher priority client
 *            takes over the sound output device.
 */
	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref)=0;

/**
 *
 * Change the duration of DTMF tones, the gaps between DTMF tones and the
 * pauses.
 *
 * @param     "TTimeIntervalMicroSeconds32 iToneOnLength"
 *            The duration of the DTMF tone in microseconds.
 * @param     "TTimeIntervalMicroSeconds32 iToneOffLength"
 *            The gap between DTFM tones in microseconds.
 * @param     "TTimeIntervalMicroSeconds32 iPauseLength"
 *            Pauses in microseconds
 */
	virtual void SetDTMFLengths(TTimeIntervalMicroSeconds32 aToneOnLength,TTimeIntervalMicroSeconds32 aToneOffLength,TTimeIntervalMicroSeconds32 aPauseLength)=0;

/**
 *
 * Sets the number of times the tone sequence is to be repeated during
 * the play operation.
 *
 * A period of silence can follow each playing of the tone sequence. The
 * tone sequence can be repeated indefinitely.
 *
 * @param     "TInt aRepeatNumberOfTimes"
 *            The number of times the tone sequence, together with
 *            the trailing silence, is to be repeated. If this is
 *            set to <code>KMdaRepeatForever</code>, then the tone
 *            sequence, together with the trailing silence, is
 *            repeated indefinitely. If this is set to zero, then
 *            the tone sequence is not repeated. If this is set to a
 *            negative value other than
 *            <code>KMdaRepeatForever</code>then the function raises
 *            a CMdaAudioToneUtility 6 panic.
 * @param     "const TTimeIntervalMicroSeconds& aTrailingSilence"
 *            The time interval of the training silence. The value
 *            must be zero or positive, otherwise the function
 *            raises a CMdaAudioToneUtility 5 panic.
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence)=0;

/**
 *
 * Defines the period over which the volume level is to rise smoothly
 * from nothing to the normal volume level.
 *
 * @param     "const TTimeIntervalMicroSeconds& aRampDuration"
 *            The period over which the volume is to rise. A zero
 *            value causes the tone to be played at the normal level
 *            for the full duration of the playback. A value which
 *            is longer than the duration of the tone sequence means
 *            that the tone never reaches its normal volume level.
 */
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;

/**
 *
 * Returns the number of available pre-defined tone sequences.
 *
 * @returns   "TInt"
 *            The number of tone sequences
 */
	virtual TInt FixedSequenceCount()=0;

/**
 *
 * Returns the name assigned to a specific pre-defined tone sequence.
 *
 * @param     "TInt aSequenceNumber"
 *            The index identifying the specific pre-defined tone
 *            sequence. Index values are relative to zero.
 * @returns   "const TDesC&"
 *            The name assigned to the tone sequence.
 */
	virtual const TDesC& FixedSequenceName(TInt aSequenceNumber)=0;

/**
 *
 * Configures the audio tone player utility to play a single tone.
 *
 * This function is asynchronous. On completion, the observer callback
 * function <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is
 * called, indicating the success or failure of the configuration
 * operation.The configuration operation can be cancelled by calling
 * <code>CMdaAudioToneUtility::CancelPrepare()</code>.The configuration
 * operation cannot be started if a play operation is in progress.
 *
 * @param     "TInt aFrequency"
 *            The frequency (pitch) of the tone.
 * @param     "const TTimeIntervalMicroSeconds& aDuration"
 *            The duration of the tone in microseconds.
 */
	virtual void PrepareToPlayTone(TInt aFrequency, const TTimeIntervalMicroSeconds& aDuration)=0;

/**
 *
 * Configures the audio tone utility player to play a DTMF (Dual-Tone
 * Multi-Frequency) string.
 *
 * This function is asynchronous. On completion, the observer callback
 * function <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is
 * called, indicating the success or failure of the configuration
 * operation.The configuration operation can be cancelled by calling
 * <code>CMdaAudioToneUtility::CancelPrepare()</code>.The configuration
 * operation cannot be started if a play operation is in progress.
 *
 * @param     "const TDesC& aDTMF"
 *            A descriptor containing the DTMF string.
 */
	virtual void PrepareToPlayDTMFString(const TDesC& aDTMF)=0;

/**
 *
 * Configures the audio tone player utility to play a tone sequence
 * contained in a descriptor.
 *
 * This function is asynchronous. On completion, the observer callback
 * function <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is
 * called, indicating the success or failure of the configuration
 * operation.The configuration operation can be cancelled by calling
 * <code>CMdaAudioToneUtility::CancelPrepare()</code>.The configuration
 * operation cannot be started if a play operation is in progress.
 *
 * @param     "const TDesC8& aSequence"
 *            The descriptor containing the tone sequence. The
 *            format of the data is unspecified but is expected to
 *            be platform dependent. A device might support more
 *            than one form of sequence data.
 */
	virtual void PrepareToPlayDesSequence(const TDesC8& aSequence)=0;

/**
 *
 * Configures the audio tone player utility to play a tone sequence
 * contained in a file.
 *
 * This function is asynchronous. On completion, the observer callback
 * function <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is
 * called, indicating the success or failure of the configuration
 * operation.The configuration operation can be cancelled by calling
 * <code>CMdaAudioToneUtility::CancelPrepare()</code>.The configuration
 * operation cannot be started if a play operation is in progress.
 *
 * @param     "const TDesC& aFilename"
 *            The full path name of the file containing the tone
 *            sequence. The format of the data is unspecified but is
 *            expected to be platform dependent. A device might
 *            support more than one form of sequence data.
 */
	virtual void PrepareToPlayFileSequence(const TDesC& aFilename)=0;

/**
 *
 * Configures the audio tone player utility to play the specified
 * pre-defined tone sequence.
 *
 * This function is asynchronous. On completion, the observer callback
 * function <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is
 * called, indicating the success or failure of the configuration
 * operation.The configuration operation can be cancelled by calling
 * <code>CMdaAudioToneUtility::CancelPrepare()</code>.The configuration
 * operation cannot be started if a play operation is in progress.
 *
 * @param     "TInt aSequenceNumber"
 *            An index into the set of pre-defined tone sequences.
 *            Index values are relative to zero.
 */
	virtual void PrepareToPlayFixedSequence(TInt aSequenceNumber)=0;

/**
 *
 * Cancels the configuration operation.
 *
 * The observer callback function
 * <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is not
 * called.
 *
 */
	virtual void CancelPrepare()=0;

/**
 *
 * Plays the tone.
 *
 * The tone played depends on the current configuration.This function is
 * asynchronous. On completion, the observer callback function
 * <code>MMdaAudioToneObserver::MatoPlayComplete()</code> is called,
 * indicating the success or failure of the play operation.The play
 * operation can be cancelled by
 * calling<code>CMdaAudioToneUtility::CancelPlay()</code>.
 *
 */
	virtual void Play()=0;

/**
 *
 * Cancels the tone playing operation.
 *
 * The observer callback
 * function<code>MMdaAudioToneObserver::MatoPlayComplete()</code> is not
 * called.
 *
 */
	virtual void CancelPlay()=0;
	};

#endif
