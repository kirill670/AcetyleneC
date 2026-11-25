// MdaAudioSampleEditor.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOSAMPLEEDITOR_H__
#define __MDAAUDIOSAMPLEEDITOR_H__



#include <e32std.h>
#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfaudio.h>
#include <mmf\common\mmfstandardcustomcommands.h>

#include <Mda\Client\Resource.h>
#include <Mda\Client\Utility.h>
#include <Mda\Common\Audio.h>

class CMdaServer;

/**
 * @publishedAll
 * @deprecated
 *
 * Dummy class - not supported in 7.0s
 */
class CMdaAudioType : public CBase
	{
public:
	IMPORT_C ~CMdaAudioType();
	};

/** 
 * @publishedAll
 * @released
 *
 * This class is used by both the audio recorder and audio converter. This class should not be used,
 * other than the TState enum
 */
class CMdaAudioClipUtility : public CBase
	{
public:
/**
 * Internal state enum for both audio recorder and converter
 */
	enum TState
		{
		ENotReady = 0,
		EOpen,
		EPlaying,
		ERecording
		};

public:
/**
 * Return the state variable
 * @internalTechnology
 * @returns one of the operation states
 * @since 5.0
 */
	virtual TState State()=0;

/**
 * Close the audio clip
 * @internalTechnology
 * @since 5.0
 */
	virtual void Close()=0;
/**
 * Start Playback
 * @internalTechnology
 * @since 5.0
 */
	virtual void PlayL()=0;

/**
 * Start recording
 * @internalTechnology
 * @since 5.0
 */
	virtual void RecordL()=0;

/**
 * Stop the current operation
 * @internalTechnology
 * @since 5.0
 */
	virtual void Stop()=0;
/**
 * Crop the end of the video clip
 * @internalTechnology
 * @since 5.0
 */
	virtual void CropL()=0;

/**
 * Set the position
 * @internalTechnology
 * @since 5.0
 */
	virtual void SetPosition(const TTimeIntervalMicroSeconds& aPosition)=0;

/**
 * Return the position
 * @internalTechnology
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& Position()=0;

/**
 * Return the recording time available
 * @internalTechnology
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& RecordTimeAvailable()=0;

/**
 * Return the duration of the clip
 * @internalTechnology
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& Duration()=0;

/**
 * Set the Play window
 * @internalTechnology
 * @since 5.0
 */
	virtual void SetPlayWindow(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd)=0;

/**
 * Clear the play window
 * @internalTechnology
 * @since 5.0
 */
	virtual void ClearPlayWindow()=0;

/**
 * Set the number of times playback will be repeated
 * @internalTechnology
 * @since 5.0
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence)=0;

/**
 * Return the audio type
 * @internalTechnology
 * @since 5.0
 */
 	virtual CMdaAudioType* TypeL();

/**
 * Set the maximum write length
 * @internalTechnology
 * @since 5.0
 */
	virtual void SetMaxWriteLength(TInt aMaxWriteLength = KMdaClipLocationMaxWriteLengthNone)=0;

/**
 * Crop the beginning of the clip
 * @internalTechnology
 * @since 5.0
 */
	virtual void CropFromBeginningL()=0;
public:
	// Reserved functions - do not call - to allow virtual additional functions to be added to class
/**
 * Reserved function
 * @internalTechnology
 */
	virtual void ClipUtil_Reserved3();

/**
 * Reserved function
 * @internalTechnology
 */
	virtual void ClipUtil_Reserved4();
	};


class CMMFMdaAudioRecorderUtility;
/**
 * @publishedAll
 * @released
 *
 * Audio recorder public API class
 */
class CMdaAudioRecorderUtility : public CMdaAudioClipUtility
	{
public:
	
/**
 * Device mode. Used by SetAudioDeviceMode method which is not used from 7.0s
 * @since 5.0
 */
	enum TDeviceMode
		{
		EDefault = 0,
		ETelephonyOrLocal = EDefault,
		ETelephonyMixed = 1,
		ETelephonyNonMixed = 2,
		ELocal = 3
		};

/**
 * Destructor. Closes the audio clip and frees resources
 * @since 5.0
 */
	virtual ~CMdaAudioRecorderUtility();

/**
 * Create a new instance of CMdaAudioRecorderUtility
 * @param "aObserver" Class to receive state change events from recorder
 * @param "aServer" No longer used, should be NULL
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @returns Instance of CMdaAudioRecorderUtility
 * @since 5.0
 */
	IMPORT_C static CMdaAudioRecorderUtility* NewL(
		MMdaObjectStateChangeObserver& aObserver, 
		CMdaServer* aServer = NULL, 
		TInt aPriority = EMdaPriorityNormal, 
		TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

/**
 * Open audio clip from a file
 * @param "aFileName" File containing audio clip
 * @since 5.0
 */
	virtual void OpenFileL(const TDesC& aFileName);

/**
 * Open audio clip from a descriptor
 * @param "aDescriptor" Descriptor containing audio clip
 * @since 5.0
 */
	virtual void OpenDesL(const TDesC8& aDescriptor);

/**
 * Open audio clip from a descriptor
 * @param "aDescriptor" Descriptor containing audio clip
 * @since 7.0s
 */
	IMPORT_C void OpenDesL(TDes8& aDescriptor);

/**
 * Open audio clip from specified location
 * @param "aLocation" Location of the audio clip
 * @param "aFormat" Format of the audio clip
 * @param "aArg1" Usually codec/data type to use
 * @param "aArg2" Usually audio settings
 * @since 5.0
 */
	virtual void OpenL(TMdaClipLocation* aLocation,	
						TMdaClipFormat* aFormat,		
						TMdaPackage* aArg1 = NULL,	
						TMdaPackage* aArg2 = NULL);

/**
 * Set the audio device mode. This function is provided for binary compatibility, but
 * does not have any effect from 7.0s
 * @param "aMode" One of the TDeviceMode settings
 * @since 5.0
 */
	virtual void SetAudioDeviceMode(TDeviceMode aMode);

/**
 * Return the maximum volume setting
 * @returns Value of the maximum volume setting
 * @since 5.0
 */
	virtual TInt MaxVolume();

/**
 * Return the maximum value for the gain
 * @returns Maximum gain setting
 * @since 5.0
 */
	virtual TInt MaxGain();

/**
 * Set the volume for playback
 * @param "aVolume" The volume for playback. Should be between 0 and MaxVolume
 * @since 5.0
 */
	virtual void SetVolume(TInt aVolume);

/**
 * Set the recording gain.
 * @param "aGain" The recording gain. should be between 0 and MaxGain()
 * @since 5.0
 */
	virtual void SetGain(TInt aGain);
/**
 * Set a volume ramp
 * @param "aRampDuration" The duration of the volume ramp, the time over which the sound will rise to
 *		the current volume.
 * @since 5.0
 */
 	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration);

/**
 * Open an audio clip from a file
 * @param "aFileName" The file name of the audio clip
 * @param "aRecordControllerUid" The Uid of the controller to use for recording
 * @param "aPlaybackControllerUid" The Uid of the controller to use for playback, if KNullUid, the 
 *		same controller is used for playback and recording.
 * @param "aDestinationFormatUid" Uid of record format
 * @param "aDestinationDataType" Data type for recording
 * @since 7.0s
 */
	IMPORT_C void OpenFileL(const TDesC& aFileName,
						TUid aRecordControllerUid,				// controller to use
						TUid aPlaybackControllerUid=KNullUid,	// playback controller (if different)
						TUid aDestinationFormatUid=KNullUid,	// Data format
						TFourCC aDestinationDataType = KFourCCNULL);	// data type for recording

/**
 * Open an audio clip from a descriptor
 * @param "aDescriptor" The descriptor containing the audio clip
 * @param "aRecordControllerUid" The Uid of the controller to use for recording
 * @param "aPlaybackControllerUid" The Uid of the controller to use for playback, if KNullUid, the 
 *		same controller is used for playback and recording.
 * @param "aDestinationFormatUid" Uid of record format
 * @param "aDestinationDataType" Data type for recording
 * @since 7.0s
 */

	IMPORT_C void OpenDesL(TDes8& aDescriptor,
						TUid aRecordControllerUid,				// controller to use
						TUid aPlaybackControllerUid=KNullUid,	// playback controller (if different)
						TUid aDestinationFormatUid=KNullUid,	// Data format
						TFourCC aDestinationDataType = KFourCCNULL);	// data type for recording


/**
 * Open an audio clip from a Url
 * @param "aUrl" The Url of the audio clip
 * @param "aIapId" The ID of the internet access point to use. KUseDefaultIap selects the default Internet access point. 
 * @param "aRecordControllerUid" The Uid of the controller to use for recording
 * @param "aPlaybackControllerUid" The Uid of the controller to use for playback, if KNullUid, the 
 *		same controller is used for playback and recording.
 * @param "aDestinationFormatUid" Uid of record format
 * @param "aDestinationDataType" Data type for recording
 * @since 7.0s
 */
	IMPORT_C void OpenUrlL(const TDesC& aUrl, 
						TInt aIapId,						// internet access point
						TUid aRecordControllerUid,				// controller to use
						TUid aPlaybackControllerUid=KNullUid,	// playback controller (if different)
						TUid aDestinationFormatUid=KNullUid,	// Data format
						TFourCC aDestinationDataType = KFourCCNULL);	// data type for recording

/**
 * Open audio clip from a URL
 * @param "aUrl" Url of the audio clip
 * @param "aIapId" The ID of the internet access point to use. KUseDefaultIap selects the default Internet access point. 
 * @param "aMimeType" MimeType of the audio clip
 * @since 7.0s
 */
	IMPORT_C void OpenUrlL(const TDesC& aUrl, 
							TInt aIapId =KUseDefaultIap, 
							const TDesC8& aMimeType = KNullDesC8);

/**
 * Get the current recording gain
 * @param "aGain" The recording gain, between 0 and MaxGain()
 * @returns One of the system-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt GetGain(TInt& aGain);

/**
 * Get the current volume
 * @param "aVolume" The playback volume, between 0 and MaxVolume()
 * @returns One of the system-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt GetVolume(TInt& aVolume);

/**
 * Set the playback balance
 * @param "aBalance" The playback balance, between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
 * @returns One of the system-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt SetPlaybackBalance(TInt aBalance = KMMFBalanceCenter);

/**
 * Get the playback balance
 * @param "aBalance" The playback balance, between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
 * @returns One of the system-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt GetPlaybackBalance(TInt& aBalance);

/**
 * Set the record balance
 * @param "aBalance" The recording balance, between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
 * @returns One of the system-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt SetRecordBalance(TInt aBalance = KMMFBalanceCenter);

/**
 * Get the record balance
 * @param "aBalance" The recording balance, between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
 * @returns One of the system-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt GetRecordBalance(TInt& aBalance);

/**
 * Get the number of meta data entries associated with this clip
 * @param "aNumEntries" the number of meta data entries
 * @returns One of the System-wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt GetNumberOfMetaDataEntries(TInt& aNumEntries);

/**
 * Retrieve a meta data entry from the current clip
 * @param "aMetaDataIndex" The index of the entry to retrieve. The index is between 0
 *		  and GetNumberOfMetaDataEntries()-1
 * @returns The meta data entry requested
 * @since 7.0s
 */
	IMPORT_C CMMFMetaDataEntry* GetMetaDataEntryL(TInt aMetaDataIndex);

/**
 * Add a meta data entry
 * @param "aMetaDataEntry" The meta data entry to add
 * @since 7.0s
 */ 
	IMPORT_C void AddMetaDataEntryL(CMMFMetaDataEntry& aMetaDataEntry);

/**
 * Remove a meta data entry
 * @param "aMetaDataIndex" The index of the meta data entry to remove
 * @since 7.0s
 */ 
	IMPORT_C TInt RemoveMetaDataEntry(TInt aMetaDataIndex);

/**
 * Replace a meta data entry
 * @param "aMetaDataIndex" The index of the meta data entry to replace
 * @param "aMetaDataEntry" The meta data entry to replace the previous entry
 * @since 7.0s
 */ 
	IMPORT_C void ReplaceMetaDataEntryL(TInt aMetaDataIndex, CMMFMetaDataEntry& aMetaDataEntry);

/**
 * Set the recording priority. This is used to arbitrate between simultaneous accesses of
 * the sound hardware.
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @since 7.0s
 */
	IMPORT_C void SetPriority(TInt aPriority, TMdaPriorityPreference aPref); 

//DataType support
/**
 * Return a list of the supported data types for the conversion destination
 * @param "aSupportedDataTypes" list of four character codes, representing supported data 
 *		encodings for the conversion destination.
 * @since 7.0s
 */
	IMPORT_C void GetSupportedDestinationDataTypesL(RArray<TFourCC>& aSupportedDataTypes);

/**
 * Set the data type of the destination audio clip
 * @param "aDataType" four character code, representing the encoding of the destination audio clip
 * @since 7.0s
 */
	IMPORT_C void SetDestinationDataTypeL(TFourCC aDataType);

/**
 * Return the data type of the destination audio clip
 * @returns four character code, representing the encoding of the destination audio clip
 * @since 7.0s
 */
	IMPORT_C TFourCC DestinationDataTypeL();
	// Bit rate support	

/**
 * Set the bit rate for recording
 * @param "aBitRate" destination bit rate in bits/second
 * @since 7.0s
 */
	IMPORT_C void SetDestinationBitRateL(TUint aBitRate);
/**
 * Return the recording bit rate
 * @returns destination bit rate in bits/second
 * @since 7.0s
 */
	IMPORT_C TUint DestinationBitRateL();
/**
 * Return a list of the supported bit rates for recording
 * @param "aSupportedBitRates" List of bit rates supported for the conversion destination
 * @since 7.0s
 */
	IMPORT_C void GetSupportedBitRatesL(RArray<TUint>& aSupportedBitRates);	
	
	// Sample rate support

/**
 * Set the sample rate for the conversion destination
 * @param "aSampleRate" The sample rate of the conversion destination
 * @since 7.0s
 */
	IMPORT_C void SetDestinationSampleRateL(TUint aSampleRate);

/**
 * Return the sample rate of the conversion destination
 * @returns The sample rate of the conversion destination
 * @since 7.0s
 */
	IMPORT_C TUint DestinationSampleRateL();

/**
 * Get a list of supported recording sample rates. 
 * @param "aSupportedSampleRates" List of the sample rates that are supported for recording
 * @since 7.0s
 */
	IMPORT_C void GetSupportedSampleRatesL(RArray<TUint>& aSupportedSampleRates);
	// Format support
/**
 * Set the format of the audio clip. This can only be done if the audio clip does not exist
 * @param "aFormatUid" Uid of the audio clip format
 * @since 7.0s
 */
	IMPORT_C void SetDestinationFormatL(TUid aFormatUid);
	
	// Number of channels
/**
 * Return the format of the audio clip
 * @returns Uid of the audio clip format
 * @since 7.0s
 */
	IMPORT_C TUid DestinationFormatL();


/**
 * Set the number of channels for the recorded audio clip
 * @param "aNumberOfChannels" The number of channels to record
 * @since 7.0s
 */
	// Number of channels
	IMPORT_C void SetDestinationNumberOfChannelsL(TUint aNumberOfChannels);

/**
 * Return the number of channels in audio clip
 * @returns number of channels supported by audio clip
 * @since 7.0s
 */
	IMPORT_C TUint DestinationNumberOfChannelsL();

/**
 * Return a list of the supported number of channels for recording
 * @param "aSupportedNumChannels" List of the number of channels supported for recording
 * @since 7.0s
 */
	IMPORT_C void GetSupportedNumberOfChannelsL(RArray<TUint>& aSupportedNumChannels);


/**
 * Return the current utility state
 * @returns One of the states defined by CMdaAudioClipUtility::TState
 * @since 5.0
 */
	virtual TState State();

/**
 * Close the current audio clip
 * @since 5.0
 */
	virtual void Close();

/**
 * Play the current audio clip.
 * @since 5.0
 */
	virtual void PlayL();

/**
 * Record to the current audio clip.
 * @since 5.0
 */
	virtual void RecordL();

/**
 * Stop the current operation (playback/recording/conversion)
 * @since 5.0
 */
	virtual void Stop();

/**
 * Crop the current clip from the current position. The remainder of the clip is discarded
 * @since 5.0
 */
	virtual void CropL();

/**
 * Set the current position in the audio clip
 * @param "aPosition" The position in the audio clip, in microseconds
 * @since 5.0
 */
	virtual void SetPosition(const TTimeIntervalMicroSeconds& aPosition);

/**
 * Get the current position in the audio clip
 * @returns The current position in the audio clip, in microseconds
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& Position();

/**
 * Return the amount of recording time available to the current clip
 * @returns The current position in the audio clip, in microseconds
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& RecordTimeAvailable();

/**
 * Return the duration of the audio clip
 * @returns the duration in microseconds
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& Duration();

/**
 * Set a window for playback
 * @param "aStart" The position in the clip to start playback, in microseconds
 * @param "aEnd" The position in the clip to end playback, in microseconds
 * @since 5.0
 */
	virtual void SetPlayWindow(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd);

/**
 * Clear the playback window. Playback returns to playing the entire clip
 * @since 5.0
 */
	virtual void ClearPlayWindow();

/**
 * Set the number of repetitions for playback. 
 * @param "aRepeatNumberOfTimes" Number of times to repeat the audio clip, after the first playback
 * @param "aTrailingSilence" A delay to wait before each repetition
 * @since 5.0
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);

/**
 * Set the maximum size of an audio clip
 * @param "aMaxWriteLength" The maximum size of the audio clip, in bytes
 * @since 7.0
 */
	virtual void SetMaxWriteLength(TInt aMaxWriteLength = KMdaClipLocationMaxWriteLengthNone);
/**
 * Crop the audio clip from the start of the file to the current position. The audio data
 * prior to the current position is discarded.
 * @since 7.0s
 */
	virtual void CropFromBeginningL();

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
 * Return the controller implementation information associated with the playback controller
 * @return The controller implementation structure associated with the controller					
 * @since 7.0s
 */
	IMPORT_C const CMMFControllerImplementationInformation& AudioPlayControllerImplementationInformationL();
	
/**
 * Return the controller implementation information associated with the recording controller
 * @return The controller implementation structure associated with the controller					
 * @since 7.0s
 */
	IMPORT_C const CMMFControllerImplementationInformation& AudioRecorderControllerImplementationInformationL();
	
/**
 * Send a synchronous custom command to the recording controller
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
	IMPORT_C TInt RecordControllerCustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom);

/**
 * Send a synchronous custom command to the recording controller
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
	IMPORT_C TInt RecordControllerCustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2);

/**
 * Send a asynchronous custom command to the recording controller
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
	IMPORT_C void RecordControllerCustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus);
/**
 * Send a asynchronous custom command to the recording controller
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
	IMPORT_C void RecordControllerCustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus);
	
/**
 * Send a synchronous custom command to the playback controller
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
	IMPORT_C TInt PlayControllerCustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom);
	
/**
 * Send a synchronous custom command to the playback controller
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
	IMPORT_C TInt PlayControllerCustomCommandSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2);
	
/**
 * Send a asynchronous custom command to the recording controller
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
	IMPORT_C void PlayControllerCustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus);
	
/**
 * Send a asynchronous custom command to the recording controller
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
	IMPORT_C void PlayControllerCustomCommandAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus);

private:
	CMMFMdaAudioRecorderUtility* iProperties;
	
	};

class CMMFMdaAudioConvertUtility;

/**
 * @publishedAll
 * @released
 *
 * Audio converter public API class.
 */
class CMdaAudioConvertUtility : public CMdaAudioClipUtility
	{
public:
/**
 * Create a new instance of CMdaAudioConvertUtility
 * @param "aObserver" Class to receive state change events from converter
 * @param "aServer" No longer used, should be NULL
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @returns instance of CMdaAudioConvertUtility
 * @since 5.0
 */
	IMPORT_C static CMdaAudioConvertUtility* NewL(
		MMdaObjectStateChangeObserver& aObserver, 
		CMdaServer* aServer = NULL, 
		TInt aPriority = EMdaPriorityNormal, 
		TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

/**
 * Destructor. Closes audio clip and frees resources
 * @since 5.0
 */
	virtual ~CMdaAudioConvertUtility();

/**
 * Open an audio clip for conversion.
 * @param "aPrimaryFile" File to convert from
 * @param "aSecondaryFile" File to convert to
 * @since 5.0
 */
	virtual void OpenL(const TDesC& aPrimaryFile, const TDesC& aSecondaryFile);

/**
 * Open an audio clip for conversion.
 * @param "aPrimaryFile" File to convert from
 * @param "aLocation" location of audio clip to convert to
 * @param "aFormat" format of audio file
 * @param "aArg1" usually codec to use
 * @param "aArg2" usually audio settings
 * @since 5.0
 */
	virtual void OpenL(const TDesC& aPrimaryFile,
						TMdaClipLocation* aLocation,	// Normally file or descriptor
						TMdaClipFormat* aFormat,		// Data format
						TMdaPackage* aArg1 = NULL,		// Normally codec to use
						TMdaPackage* aArg2 = NULL);		// Normally audio settings


/**
 * Open an audio clip for conversion
 * @param "aPriLocation" The location of the source audio clip
 * @param "aSecLocation" The location of the destination audio clip
 * @param "aPriFormat" The source audio clip's format
 * @param "aSecFormat" The destination audio clip's format
 * @param "aPriArg1" Usually the source codec
 * @param "aPriArg2" Usually source audio settings
 * @param "aSecArg1" Usually the destination codec
 * @param "aSecArg2" Usually destination audio settings
 * @since 5.0
 */
	virtual void OpenL(TMdaClipLocation* aPriLocation, 
						TMdaClipLocation* aSecLocation, 
						TMdaClipFormat* aPriFormat, 
						TMdaClipFormat* aSecFormat, 
						TMdaPackage* aPriArg1 = NULL, 
						TMdaPackage* aPriArg2 = NULL, 
						TMdaPackage* aSecArg1 = NULL, 
						TMdaPackage* aSecArg2 = NULL);

	// new controller based open
	// N.B. this override is new and must NOT be made virtual. This is because
	// it will break BC on the WINS build (due to the MS compiler grouping and
	// reordering the overrides together in the vtable and _not_ using the 
	// declaration order!)
/**
 * Open an audio clip for conversion
 * @param "aPriLocation" The location of the source audio clip
 * @param "aSecLocation" The location of the destination audio clip
 * @param "aControllerUid" The Uid of the controller to used for conversion
 * @param "aDestFormatUid" Uid of the destination format
 * @param "aDestDataType" Four character code representing conversion destination
 * @since 7.0s
 */
	IMPORT_C void OpenL(TMdaClipLocation* aPriLocation, 
						TMdaClipLocation* aSecLocation, 
						TUid aControllerUid, 
						TUid aDestFormatUid,
						TFourCC aDestDataType);

	//Data type support
/**
 * Return a list of the supported data types for the conversion destination
 * @param "aSupportedDestinationDataTypes" list of four character codes, representing supported data 
 *		encodings for the conversion destination.
 * @since 7.0s
 */
	IMPORT_C void GetSupportedDestinationDataTypesL(RArray<TFourCC>& aSupportedDestinationDataTypes);

/**
 * Set the data type of the destination audio clip
 * @param "aDataType" four character code, representing the encoding of the destination audio clip
 * @since 7.0s
 */
	IMPORT_C void SetDestinationDataTypeL(TFourCC aDataType);

/**
 * Return the data type of the destination audio clip
 * @returns four character code, representing the encoding of the destination audio clip
 * @since 7.0s
 */
	IMPORT_C TFourCC DestinationDataTypeL();

/**
 * Return the data type of the source audio clip
 * @returns four character code, representing the encoding of the source audio clip
 * @since 7.0s
 */
	IMPORT_C TFourCC SourceDataTypeL();
	// Bit rate support	

/**
 * Set the bit rate of the destination audio clip
 * @param "aBitRate" destination bit rate in bits/second
 * @since 7.0s
 */
	IMPORT_C void SetDestinationBitRateL(TUint aBitRate);

/**
 * Return the bit rate of the destination audio clip
 * @returns destination bit rate in bits/second
 * @since 7.0s
 */
	IMPORT_C TUint DestinationBitRateL();

/**
 * Return a list of the supported bit rates for the conversion destination
 * @param "aSupportedBitRates" list of bit rates supported for the conversion destination
 * @since 7.0s
 */
	IMPORT_C void GetSupportedConversionBitRatesL(RArray<TUint>& aSupportedBitRates);

/**
 * Return the bit rate of the source audio clip
 * @returns source bit rate in bits/second
 * @since 7.0s
 */
	IMPORT_C TInt SourceBitRateL();

	// Sample rate support
/**
 * Set the sample rate for the conversion destination
 * @param "aSampleRate" the sample rate of the conversion destination
 * @since 7.0s
 */
	IMPORT_C void SetDestinationSampleRateL(TUint aSampleRate);

/**
 * Return the sample rate of the conversion destination
 * @returns the sample rate of the conversion destination
 * @since 7.0s
 */
	IMPORT_C TUint DestinationSampleRateL();

/**
 * Get a list of supported conversion sample rates. This is a list of the sample rates that 
 * the conversion destination can take
 * @param "aSupportedSampleRates" list of the sample rates that are supported for the conversion
 * @since 7.0s
 */
	IMPORT_C void GetSupportedConversionSampleRatesL(RArray<TUint>& aSupportedSampleRates);

/**
 * Return the sample rate of the source audio clip
 * @returns source sample rate in samples/second
 * @since 7.0s
 */
	IMPORT_C TUint SourceSampleRateL();

/**
 * Set the format of the destination audio clip
 * @param "aFormatUid" Uid of the destination format
 * @since 7.0s
 */
	// Format support
	IMPORT_C void SetDestinationFormatL(TUid aFormatUid);

/**
 * Return the format of the destination audio clip
 * @returns Uid of the destination format
 * @since 7.0s
 */
	IMPORT_C TUid DestinationFormatL();

/**
 * Return the format of the source audio clip
 * @returns TUid of the source format
 * @since 7.0s
 */
	IMPORT_C TUid SourceFormatL();

	// Number of channels

/**
 * Set the number of channels the destination audio clip contains
 * @param "aNumberOfChannels" the number of channels
 * @since 7.0s
 */
	IMPORT_C void SetDestinationNumberOfChannelsL(TUint aNumberOfChannels);

/**
 * Return the number of channels the destination audio clip contains
 * @returns the number of channels
 * @since 7.0s
 */
	IMPORT_C TUint DestinationNumberOfChannelsL();

/**
 * Return a list of the supported number of channels for conversion
 * @param "aSupportedNumChannels" List of the number of channels supported for the conversion 
 *		destination
 * @since 7.0s
 */
	IMPORT_C void GetSupportedConversionNumberOfChannelsL(RArray<TUint>& aSupportedNumChannels);

/**
 * Return the number of channels used by the conversion source
 * @returns number of channels
 * @since 7.0s
 */
	IMPORT_C TUint SourceNumberOfChannelsL();
	// New function ConvertL (PlayL and RecordL now deprecated for CMdaAudioConvertUtility)
/**
 * This functions starts conversion. 
 * @since 7.0s
 */
	IMPORT_C void ConvertL();

/**
 * Return the current utility state
 * @returns One of the states defined by CMdaAudioClipUtility::TState
 * @since 5.0
 */
	virtual TState State();

/**
 * Close the current audio clip
 * @since 5.0
 */
	virtual void Close();

/**
 * This function is mapped to ConvertL. ConvertL should be called in preference.
 * @since 5.0
 */
	virtual void PlayL();

/**
 * This function is mapped to ConvertL. ConvertL should be called in preference.
 * @since 5.0
 */
	virtual void RecordL();

/**
 * Stop the current operation (playback/recording/conversion)
 * @since 5.0
 */
	virtual void Stop();

/**
 * Crop the current clip from the current position. The remainder of the clip is discarded
 * @since 5.0
 */
	virtual void CropL();

/**
 * Set the current position in the audio clip
 * @param "aPosition" The position in the audio clip, in microseconds
 * @since 5.0
 */
	virtual void SetPosition(const TTimeIntervalMicroSeconds& aPosition);

/**
 * Get the current position in the audio clip
 * @returns The current position in the audio clip, in microseconds
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& Position();

/**
 * Return the amount of recording time available to the current clip
 * @returns The current position in the audio clip, in microseconds
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& RecordTimeAvailable();

/**
 * Return the duration of the audio clip
 * @returns the duration in microseconds
 * @since 5.0
 */
	virtual const TTimeIntervalMicroSeconds& Duration();

/**
 * Set a window for playback
 * @param "aStart" The position in the clip to start playback, in microseconds
 * @param "aEnd" The position in the clip to end playback, in microseconds
 * @since 5.0
 */
	virtual void SetPlayWindow(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd);

/**
 * Clear the playback window. Playback returns to playing the entire clip
 * @since 5.0
 */
	virtual void ClearPlayWindow();

/**
 * Set the number of repetitions for playback. This is unsupported for CMdaConvertUtility as there is
 * no playback facility.
 * @param "aRepeatNumberOfTimes" Number of times to repeat the audio clip, after the first playback
 * @param "aTrailingSilence" A delay to wait before each repetition
 * @since 5.0
 */
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);

/**
 * Set the maximum size of an audio clip
 * @param "aMaxWriteLength" The maximum size of the audio clip, in bytes
 * @since 7.0
 */
	virtual void SetMaxWriteLength(TInt aMaxWriteLength = KMdaClipLocationMaxWriteLengthNone);

/**
 * Crop the audio clip from the start of the file to the current position. The audio data
 * prior to the current position is discarded.
 * @since 7.0s
 */
	virtual void CropFromBeginningL();

/**
 * Return the controller implementation information associated with the current controller
 * @return The controller implementation structure associated with the controller					
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
	
private:
	CMMFMdaAudioConvertUtility* iProperties;
	
	};

#endif
