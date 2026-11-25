// MdaAudioSamplePlayer.h 
//
// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __MDAAUDIOSAMPLEPLAYER_H
#define __MDAAUDIOSAMPLEPLAYER_H

#include <e32std.h>
#include <mmf\common\mmfaudio.h>
#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfcontrollerframeworkbase.h>
#include <mmf\common\mmfstandardcustomcommands.h>

class CMdaServer;

/**
 * @publishedAll
 * @released
 *
 * An interface to a set of audio player callback functions.
 *
 * The class is a mixin and is intended to be inherited by the client
 * class which is observing the audio playing operation. The functions
 * encapsulated by this class are called when specific events occur in
 * the process of initialising and playing an audio sample. A reference to
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
 * @param	"TInt aError"
 *          The status of the audio sample after initialisation.
 *          The following values have the same specific meaning
 *          across all EPOC platforms: <code>KErrNone</code> the
 *          sample is ready to play. <code>KErrNotSupported</code>
 *          the audio format or particular encoding type is not
 *          recognised or not supported. <code>KErrNotFound</code>
 *          the audio sample cannot be found.
 *          <code>KErrNoMemory</code> there is insufficient memory
 *          to play this audio sample. Other values are possible
 *          indicating a problem opening the audio sample. These
 *		    values are dependent on the EPOC platform.
 * @param   "const TTimeIntervalMicroSeconds& aDuration"
 *          The duration of the audio sample.
 */
	virtual void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration) = 0;
/**
 *
 * Defines required client behaviour when an attempt to playback an audio
 * sample has completed, successfully or otherwise.
 *
 * @param   "TInt aError"
 *          The status of playback. The following values have the
 *			same specific meaning across all EPOC platforms:
 *          <code>KErrNone</code> playing of the audio sample is
 *          complete.<code>KErrCorrupt</code> the sample data is
 *          corrupt. <code>KErrInUse</code>, <code>KErrDied</code> or
 *          <code>KErrAccessDenied</code> the sound device is in use 
 *          by another higher priority client. This can happen during playback.
 *          <code>KErrNoMemory</code> there is insufficient memory to play this 
 *          audio sample Other values are possible indicating a problem opening 
 *          the audio sample. These values are dependent on the EPOC platform.
 */
	virtual void MapcPlayComplete(TInt aError) = 0;
	};


class CMMFMdaAudioPlayerUtility;
/**
 * @publishedAll
 * @released
 *
 * Plays sampled audio data.
 *
 * The class offers a simple interface to open, play and obtain
 * information from, sampled audio data. The audio data can be supplied
 * either in a file (file-based), as a descriptor
 * (descriptor-based) or as a Url reference (since version 7.0s). While 
 * this class is abstract, the three static functions construct, initialise 
 * and return pointers to instances of concrete classes derived from this 
 * abstract class. This concrete class is part of the Media Server implementation 
 * and is private.
 *
 * @since	5.0
 */
class CMdaAudioPlayerUtility : public CBase
	{
public:
	IMPORT_C static CMdaAudioPlayerUtility* NewFilePlayerL(const TDesC& aFileName, 
								MMdaAudioPlayerCallback& aCallback, 
								TInt aPriority = EMdaPriorityNormal, 
								TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality,
								CMdaServer* aServer = NULL);
	IMPORT_C static CMdaAudioPlayerUtility* NewDesPlayerL(const TDesC8& aData, 
								MMdaAudioPlayerCallback& aCallback, 
								TInt aPriority = EMdaPriorityNormal, 
								TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality,
								CMdaServer* aServer = NULL);
	IMPORT_C static CMdaAudioPlayerUtility* NewDesPlayerReadOnlyL(const TDesC8& aData, 
								MMdaAudioPlayerCallback& aCallback, 
								TInt aPriority = EMdaPriorityNormal, 
								TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality,
								CMdaServer* aServer = NULL);

	// new export from version 7.0
	IMPORT_C static CMdaAudioPlayerUtility* NewL(MMdaAudioPlayerCallback& aCallback,
								TInt aPriority = EMdaPriorityNormal,
								TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

	~CMdaAudioPlayerUtility();

/**
 *
 * Begins playback of the initialised audio sample at the current volume
 * and priority levels.
 *
 * When playing of the audio sample is complete, successfully or
 * otherwise, the callback function
 * <code>MMdaAudioPlayerCallback::MapcPlayComplete()</code> is
 * called. This function raises a CMdaAudioPlayerUtility 1 panic if the
 * audio player utility is not initialised.
 *
 * @since	5.0
 */

	virtual void Play();
/**
 *
 * Stops playback of the audio sample as soon as possible.
 *
 * If the audio sample is playing, playback is stopped as soon as
 * possible. If playback is already complete, nothing further happens as
 * a result of calling this function. The callback function
 * <code>MMdaAudioPlayerCallback::MapcPlayComplete()</code> is not
 * called.The function raises a CMdaAudioPlayerUtility 1 panic if the
 * audio player utility is not initialised.
 *
 * @since	5.0
 */
	virtual void Stop();

/**
 *
 * Changes the current playback volume to a specified value.
 *
 * The volume can be changed before or during playback and is effective
 * immediately. The function raises a CMdaAudioPlayerUtility 1 panic if
 * the audio player utility is not initialised.
 *
 * @param	"TInt aVolume"
 *          The volume setting. This can be any value from zero to
 *          the value returned by a call to
 *          <code>CMdaAudioPlayerUtility::MaxVolume()</code>.
 *          Setting a zero value mutes the sound. Setting the
 *          maximum value results in the loudest possible sound.
 *
 * @since	5.0
 */
	virtual void SetVolume(TInt aVolume);

/**
 *
 * Sets the number of times the audio sample is to be repeated during the
 * playback operation.
 *
 * A period of silence can follow each playing of the sample. The audio
 * sample can be repeated indefinitely.
 *
 * @param	"TInt aRepeatNumberOfTimes"
 *          The number of times the audio sample, together with
 *          the trailing silence, is to be repeated. If this is
 *          set to <code>KMdaRepeatForever</code>, then the audio
 *          sample, together with the trailing silence, is
 *          repeated indefinitely or until <code>Stop()</code> is
 *          called. If this is set to zero, then the audio sample
 *          is not repeated.
 * @param   "const TTimeIntervalMicroSeconds& aTrailingSilence"
 *          The time interval of the trailing silence.
 *
 * @since	5.0
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);

/**
 *
 * Defines the period over which the volume level is to rise smoothly
 * from nothing to the normal volume level.
 *
 * @param	"const TTimeIntervalMicroSeconds& aRampDuration"
 *          The period over which the volume is to rise. A zero
 *          value causes the audio sample to be played at the
 *          normal level for the full duration of the playback. A
 *          value which is longer than the duration of the audio
 *          sample means that the sample never reaches its normal
 *          volume level.
 *
 * @since	5.0
 */
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration);

/**
 *
 * Returns the duration of the audio sample.
 *
 * The function raises a CMdaAudioPlayerUtility 1 panic if the audio
 * player utility is not initialised.
 *
 * @returns "TTimeIntervalMicroSeconds&"
 *          The duration in microseconds
 *
 * @since	5.0
 */
	virtual const TTimeIntervalMicroSeconds& Duration();

/**
 *
 * Returns an integer representing the maximum volume.
 *
 * This is the maximum value which can be passed to
 * <code>CMdaAudioPlayerUtility::SetVolume()</code>. The function raises a
 * CMdaAudioPlayerUtility 1 panic if the audio player utility is not
 * initialised.
 *
 * @returns "TInt"
 *          The maximum volume. This value is platform dependent
 *          but is always greater than or equal to one.
 *
 * @since	5.0
 */
	virtual TInt MaxVolume();

/**
 *
 * Open a clip from a file
 *
 * @param	"const TDesC& aFileName" 
 *			File to open
 * @leave	Leaves with one of the system wide error codes if a problem is encountered
 *			opening the file
 * @since	7.0s
 */
	IMPORT_C void OpenFileL(const TDesC& aFileName);
/**
 *
 * Open a clip from a descriptor
 *
 * @param	"const TDesC8& aDescriptor" 
 *			Descriptor containing audio clip
 * @leave	Leaves with one of the system wide error codes if a problem is encountered
 *			opening the file
 * @since	7.0s
 */
	IMPORT_C void OpenDesL(const TDesC8& aDescriptor);
/**
 *
 * Open a clip from a URL
 *
 * @param	"const TDesC& aUrl" 
 *			URL to open
 * @param 	"TInt aIapId"
 *			Internet access point(IAP) Id to use. KUseDefaultIap selects the default IAP.
 * @param   "const TDesC8& aMimeType=KNullDesC8"
 *			Mime type of the Url source
 * @leave	Leaves with one of the system wide error codes if a problem is encountered
 *			opening the file
 * @since	7.0s
 */
	IMPORT_C void OpenUrlL(const TDesC& aUrl, TInt aIapId = KUseDefaultIap, const TDesC8& aMimeType=KNullDesC8);

/**
 * Pauses playback of the audio clip
 * @returns One of the system-wide error codes
 * @since	7.0s
 */
	IMPORT_C TInt Pause();

/**
 * Closes the current audio clip (allowing another clip to be opened)
 * @since	7.0s
 */
	IMPORT_C void Close();

/**
 *
 * Returns the current playback position in microseconds
 *
 * @retval "TTimeIntervalMicroSeconds& aPosition"
 *          The current time position in microseconds from the start of the file
 * @returns One of the global error codes
 * @since	7.0s
 */
	IMPORT_C TInt GetPosition(TTimeIntervalMicroSeconds& aPosition);

/**
 *
 * Set the current playback position in microseconds from the start of the file
 *
 * @param "TTimeIntervalMicroSeconds& aPosition"
 *          The position to move to in microseconds past the start of the file
 * @since	7.0s
 */
	IMPORT_C void SetPosition(const TTimeIntervalMicroSeconds& aPosition);

/**
 *
 * Set the priority for playback. This is used to arbitrate between multiple 
 * objects trying to access a single sound device
 *
 * @param	"TInt aPriority"

 * @param	"TMdaPriorityPreference aPref"
 *			Quality/time preference tradeoff
 *          
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt SetPriority(TInt aPriority, TMdaPriorityPreference aPref);

/**
 *
 * Returns the current playback volume
 *
 * @retval "TInt& aVolume"
 *          A volume value between 0 and the value returned by <code>MaxVolume()</code>
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt GetVolume(TInt& aVolume);

/**
 *
 * Returns the number of meta data entries in the current clip
 *
 * @retval "TInt& aNumEntries"
 *          The number of meta data entries in the header of the current clip
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt GetNumberOfMetaDataEntries(TInt& aNumEntries);

/**
 *
 * Returns the requested meta data entry
 *
 * @param "TInt aMetaDataIndex"
 *          The index number of the meta data to retrieve
 * @returns "CMMFMetaDataEntry*" The meta data entry to return
 * @leave	Leaves with KErrNotFound if the meta data entry does not exist or
 *			KErrNotImplemented if the controller does not support meta data 
 *			information for this format. Other errors indicate more general system
 *			failure.
 *
 * @since	7.0s
 */
	IMPORT_C CMMFMetaDataEntry* GetMetaDataEntryL(TInt aMetaDataIndex);

/**
 *
 * Set the current playback window
 *
 * @param	"const TTimeIntervalMicroSeconds& aStart"
 *			Start time of playback window relative to start of file
 * @param	"const TTimeIntervalMicroSeconds& aEnd"
 *			End time of playback window relative to start of file
 *
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt SetPlayWindow(const TTimeIntervalMicroSeconds& aStart,
								const TTimeIntervalMicroSeconds& aEnd);

/**
 *
 * Clear the current playback window
 *
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt ClearPlayWindow();

/**
 *
 * Sets the current playback balance
 *
 * @param "TInt& aBalance"
 *          A value between <code>KMMFBalanceMaxLeft</code> 
 *			and <code>KMMFBalanceMaxRight</code>. The default value is 
 *			<code>KMMFBalanceCenter</code>
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt SetBalance(TInt aBalance = KMMFBalanceCenter);

/**
 *
 * Returns the current playback balance
 *
 * @retval "TInt& aBalance"
 *          A value between <code>KMMFBalanceMaxLeft</code> 
 *			and <code>KMMFBalanceMaxRight</code>
 * @returns "TInt" One of the global error codes
 *
 * @since	7.0s
 */
	IMPORT_C TInt GetBalance(TInt& aBalance);
	
	
/**
 * Register to receive notifications of audio loading/rebuffering
 * @param "aCallback" object to receive audio loading notifications
 * @since 7.0s
 */
	IMPORT_C void RegisterForAudioLoadingNotification(MAudioLoadingObserver& aCallback);
	
/** 
 * Get the current progress of audio loading
 * @retval "aPercentageComplete" The percentage of the audio clip loaded
 * @since 7.0s
 */
	IMPORT_C void GetAudioLoadingProgressL(TInt& aPercentageComplete);


/**
 * Return the controller implementation information associated with the current controller
 * @return The controller implementation structure
 * @since 7.0s
 */
	IMPORT_C const CMMFControllerImplementationInformation& ControllerImplementationInformationL();

/**
 * Send a synchronous custom command to the controller
 * @param 	"aDestination"	"The destination of the message, consisting of the uid of
 *							the interface of this message."
 * @param	"aFunction"		"The function number to indicate which function is to be called
 *							on the interface defined in the aDestination parameter."
 * @param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param	"aDataFrom"		"A reference to an area of memory to which the controller framework will 
 *	 						write any data to be passed back to the client.  Can't be KNullDesC8."
 * @return					"The result of the request.  Exact range of values is dependent on the interface."
 * @since					7.0s
 */
	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom);

/**
 * Send a synchronous custom command to the controller
 * @param 	"aDestination"	"The destination of the message, consisting of the uid of
 *							the interface of this message."
 * @param	"aFunction"		"The function number to indicate which function is to be called
 *							on the interface defined in the aDestination parameter."
 * @param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @return					"The result of the request.  Exact range of values is dependent on the interface."
 * @since					7.0s
 */
	IMPORT_C TInt CustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2);

/**
 * Send a asynchronous custom command to the controller
 * Note: This method will return immediately.  The RunL of the active object owning the 
 * <code>aStatus<\code> parameter will be called when the command is completed by the 
 * controller framework.
 * @param 	"aDestination"	"The destination of the message, consisting of the uid of
 *							the interface of this message."
 * @param	"aFunction"		"The function number to indicate which function is to be called
 *							on the interface defined in the aDestination parameter."
 * @param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param	"aDataFrom"		"A reference to an area of memory to which the controller framework will 
 *	 						write any data to be passed back to the client.  Can't be KNullDesC8."
 * @param 	"aStatus"		"The TRequestStatus of an active object.  This will contain the 
 *							result of the request on completion.  The exact range of 
 * 							result values is dependent on the interface."
 * @since					7.0s
 */
	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus);

/**
 * Send a asynchronous custom command to the controller
 * Note: This method will return immediately.  The RunL of the active object owning the 
 * <code>aStatus<\code> parameter will be called when the command is completed by the 
 * controller framework.
 * @param 	"aDestination"	"The destination of the message, consisting of the uid of
 *							the interface of this message."
 * @param	"aFunction"		"The function number to indicate which function is to be called
 *							on the interface defined in the aDestination parameter."
 * @param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
 *							framework. The exact contents of the data are dependent on the 
 *							interface being called.  Can be KNullDesC8."
 * @param 	"aStatus"		"The TRequestStatus of an active object.  This will contain the 
 *							result of the request on completion.  The exact range of 
 * 							result values is dependent on the interface."
 * @since					7.0s
 */
	IMPORT_C void CustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus);
	
protected:
	CMMFMdaAudioPlayerUtility* iProperties;
	}; 


#endif
