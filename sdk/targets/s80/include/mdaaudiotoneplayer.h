// MdaAudioTonePlayer.h
//
// Copyright (c) 2002-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOTONEPLAYER_H__
#define __MDAAUDIOTONEPLAYER_H__


#include <e32std.h>
#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfstandardcustomcommands.h>

class CMdaServer;


/**
 * @publishedAll
 * @released
 */
enum TMdaAudioToneUtilityState
	{
	EMdaAudioToneUtilityNotReady=0,
	EMdaAudioToneUtilityPrepared,
	EMdaAudioToneUtilityPlaying
	};
const TInt KMdaInfiniteDurationDTMFToneOnLength = -1; 
const TInt KMdaAudioToneRepeatForever = -2;
/**
 * @publishedAll
 * @released
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
 */
class MMdaAudioToneObserver
	{
public:

/**
 * Defines required client behaviour when an attempt to configure the
 * audio tone player utility has completed, successfully or otherwise.
 *
 * @param     "TInt aError"
 *            <code>KErrNone</code> if successful. One of the system
 *            wide error codes if the attempt failed. The possible
 *            values depend on the EPOC platform.
 */
	virtual void MatoPrepareComplete(TInt aError) = 0;
	
/**
 * Defines required client behaviour when the tone playing operation has
 * completed, successfully or otherwise.
 *
 * @param     "TInt aError"
 *            <code>KErrNone</code> if successful. One of the system
 *            wide error codes if the attempt failed. The possible
 *            values depend on the EPOC platform.
 */
	virtual void MatoPlayComplete(TInt aError) = 0;
	};


class CMMFMdaAudioToneUtility;

/**
 * @publishedAll
 * @released
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
 */
class CMdaAudioToneUtility : public CBase
	{
public:
/**
 * Create a new instance of the tone player utility
 * @param 	"aObserver"
 *			A class to receive notifications from the tone player
 * @param 	"aServer" 
 *			This parameter is no longer used and should be NULL
 * @since 5.0
 */
	IMPORT_C static CMdaAudioToneUtility* NewL(MMdaAudioToneObserver& aObserver, CMdaServer* aServer = NULL);
	
/**
 * Create a new instance of the tone player utility
 * @param 	"aObserver"
 *			A class to receive notifications from the tone player
 * @param 	"aServer" 
 *			This parameter is no longer used and should be NULL
 * @param 	"aPriority"
 * 			A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param 	"aPref"
 * 			Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @since 5.0
 */
	IMPORT_C static CMdaAudioToneUtility* NewL(MMdaAudioToneObserver& aObserver, CMdaServer* aServer,
											   TInt aPriority, 
											   TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

/**
 * Destructor. Frees any resources held by the tone player
 * @since 5.0
 */
	~CMdaAudioToneUtility();

/**
 * Returns the current state of the audio tone utility.
 *
 * @returns   	"TMdaAudioToneUtilityState"
 *            	The state of the audio tone utility.
 * @since 		5.0
 */
	virtual TMdaAudioToneUtilityState State();
	
/**
 * Return the maximum volume supported by the device
 * @returns 	The maximum volume
 * @since 		5.0
 */
	virtual TInt MaxVolume();
	
/**
 * Return the current volume 
 * @returns 	The current volume
 * @since 		5.0
 */
	virtual TInt Volume();
	
/**
 * Changes the volume of the audio device.
 *
 * The volume can be changed before or during play and is effective
 * immediately.
 *
 * @param     	"TInt aVolume"
 *            	The volume setting. This can be any value from zero to
 *            	the value returned by a call to
 *            	<code>CMdaAudioToneUtility::MaxVolume()</code>.
 *            	Setting a zero value mutes the sound. Setting the
 *            	maximum value results in the loudest possible sound.
 * @since 		5.0
 */
	virtual void SetVolume(TInt aVolume); 
	
	
/**
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
 * @since 	  5.0
 */
	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref);
	

/**
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
	virtual void SetDTMFLengths(TTimeIntervalMicroSeconds32 aToneLength, 
								TTimeIntervalMicroSeconds32 aToneOffLength,
								TTimeIntervalMicroSeconds32 aPauseLength);
								
/**
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
 * @since	  5.0
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);
	
/**
 * Defines the period over which the volume level is to rise smoothly
 * from nothing to the normal volume level.
 *
 * @param     "const TTimeIntervalMicroSeconds& aRampDuration"
 *            The period over which the volume is to rise. A zero
 *            value causes the tone to be played at the normal level
 *            for the full duration of the playback. A value which
 *            is longer than the duration of the tone sequence means
 *            that the tone never reaches its normal volume level.
 * @since	  5.0
 */

	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration);
	
/**
 * Returns the number of available pre-defined tone sequences.
 *
 * @returns   "TInt"
 *            The number of tone sequences
 * @since	  5.0
 */
	virtual TInt FixedSequenceCount();
	
/**
 * Returns the name assigned to a specific pre-defined tone sequence.
 *
 * @param     "TInt aSequenceNumber"
 *            The index identifying the specific pre-defined tone
 *            sequence. Index values are relative to zero.
 * @returns   "const TDesC&"
 *            The name assigned to the tone sequence.
 * @since	  5.0
 */
	virtual const TDesC& FixedSequenceName(TInt aSequenceNumber);
	
/**
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
 * @since 	  5.0
 */
	virtual void PrepareToPlayTone(TInt aFrequency, const TTimeIntervalMicroSeconds& aDuration);
	
/**
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
 * @since 	  5.0
 */
	virtual void PrepareToPlayDTMFString(const TDesC& aDTMF);
	
/**
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
 * @since 	  5.0
 */
	virtual void PrepareToPlayDesSequence(const TDesC8& aSequence);
	
/**
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
 * @since 	  5.0
 */
	virtual void PrepareToPlayFileSequence(const TDesC& aFileName);
	
/**
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
 * @since 	  5.0
 */
	virtual void PrepareToPlayFixedSequence(TInt aSequenceNumber);
	
	
/**
 * Cancels the configuration operation.
 *
 * The observer callback function
 * <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is not
 * called.
 * @since 	  5.0
 */
	virtual void CancelPrepare();
	
/**
 * Plays the tone.
 *
 * The tone played depends on the current configuration.This function is
 * asynchronous. On completion, the observer callback function
 * <code>MMdaAudioToneObserver::MatoPlayComplete()</code> is called,
 * indicating the success or failure of the play operation.The play
 * operation can be cancelled by
 * calling<code>CMdaAudioToneUtility::CancelPlay()</code>.
 * @since 	  5.0
 */
	virtual void Play();
	
/**
 * Cancels the tone playing operation.
 *
 * The observer callback
 * function<code>MMdaAudioToneObserver::MatoPlayComplete()</code> is not
 * called.
 * @since 	  5.0
 */
	virtual void CancelPlay();
	
/**
 * Set the stereo balance for playback. 
 * @param 	"aBalance" 
 *			The balance. Should be between <code>KMMFBalanceMaxLeft</code> and <code>KMMFBalanceMaxRight</code>
 * @since 7.0s
 */
	IMPORT_C void SetBalanceL(TInt aBalance=KMMFBalanceCenter);
/**
 * Get the stereo balance 
 * @returns The balance. Should be between <code>KMMFBalanceMaxLeft</code> and <code>KMMFBalanceMaxRight</code>
 * @since 7.0s
 */
	IMPORT_C TInt GetBalanceL();

/**
 * Configures the audio tone player utility to play a dual tone.
 * The generated tone consists of two sine waves of different 
 * frequencies summed together.
 *
 * This function is asynchronous. On completion, the observer callback
 * function <code>MMdaAudioToneObserver::MatoPrepareComplete()</code> is
 * called, indicating the success or failure of the configuration
 * operation.The configuration operation can be cancelled by calling
 * <code>CMdaAudioToneUtility::CancelPrepare()</code>.The configuration
 * operation cannot be started if a play operation is in progress.
 *
 * @param     "TInt aFrequencyOne"
 *            The first frequency (pitch) of the tone.
 * @param     "TInt aFrequencyTwo"
 *            The second frequency (pitch) of the tone.
 * @param     "const TTimeIntervalMicroSeconds& aDuration"
 *            The duration of the tone in microseconds.
 * @since 	  7.0sy
 */
	IMPORT_C void PrepareToPlayDualTone(TInt aFrequencyOne, TInt aFrequencyTwo, const TTimeIntervalMicroSeconds& aDuration);
	
protected:
	CMMFMdaAudioToneUtility* iProperties;
	};


#endif
