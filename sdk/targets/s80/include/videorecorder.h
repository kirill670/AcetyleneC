// VideoRecorder.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __VIDEORECORDER_H__
#define __VIDEORECORDER_H__

#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfutilities.h>
#include <mmf\common\mmfcontroller.h>
#include <mmf\common\mmfstandardcustomcommands.h>
#include <mmf\common\mmfcontrollerframeworkbase.h>
#include <mda\common\base.h>      

class CMMFVideoRecorderCallback;

/**
 * @publishedAll
 * @released
 *
 * An interface to a set of video recorder callback functions.
 *
 * The class is a mixin and is intended to be inherited by the client
 * class which is observing the video recording operation. The functions
 * encapsulated by this class are called when specific events occur in
 * the process of initialising and recording an video clip. A reference to
 * this object is passed as a parameter when constructing a video recorder
 * utility object.
 *
 * @since 7.0s
 */
class MVideoRecorderUtilityObserver
	{
public:
/**
 * Notification to the client that the opening of the video clip has completed, 
 * successfully, or otherwise
 *
 * @param	"aError"
 *          The status of the video recorder after initialisation.
 *			This is either KErrNone if the open has completed successfully,
 *			or one of the system wide error codes
 */
	virtual void MvruoOpenComplete(TInt aError) = 0;  

/**
 * Notification that video recorder is ready to begin recording. This callback
 * is generated in response to a call to Prepare.
 *
 * @param	"aError"
 *          This is either KErrNone if the video recorder has been prepared for
 *			recording successfully, or one of the system wide error codes
 */
	virtual void MvruoPrepareComplete(TInt aError) = 0;  

/**
 * Notification that video recording has completed. This is not called if 
 * recording is explicitly stopped by calling Stop.
 *
 * @param	"aError"
 *			This is either KErrNone if recording was completed successfully,
 *			or one of the system wide error codes
 */
	virtual void MvruoRecordComplete(TInt aError) = 0;
	
/**
 * General event notification from controller. These events are specified by
 * the supplier of the controller
 *
 * @param	"aEvent"
 *          The event sent by the controller
 */
	virtual void MvruoEvent(const TMMFEvent& aEvent) = 0;
	};

/**
 * @publishedAll
 * @released
 *
 * CVideoRecorderUtility. This class provides the main client API for video playback
 * functionality
 *
 * @since 7.0s	
 */
class CVideoRecorderUtility : public CBase
	{
friend class CTestStepUnitMMFVidClient;

	class CBody;

public: 

/**
 * Destructor. Closes the current clip, if one is open, and frees resources.
 * @since 7.0s
 */
	~CVideoRecorderUtility();

/**
 * Create an instance of the Video Recorder Utility.
 * @param "aObserver" An object to receive video recorder notifications
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @returns New instance of video recorder
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C static CVideoRecorderUtility* NewL(MVideoRecorderUtilityObserver& aObserver,TInt aPriority=EMdaPriorityNormal,TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality);

/**
 * Open a video clip from a file source
 * @param "aFileName" The file containing the video clip
 * @param "aCameraHandle" The handle of the camera to record from
 * @param "aControllerUid" Controller to use for recording
 * @param "aVideoFormat" The UID of the video format to record to.
 * @param "aVideoType" The descriptor containing the video mime type.
 * @param "aAudioType" A four character code representing the encoding to be used for audio data
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void OpenFileL(const TDesC& aFileName,
							TInt aCameraHandle,
							TUid aControllerUid,
							TUid aVideoFormat,
							const TDesC8& aVideoType = KNullDesC8,
							TFourCC aAudioType = KMMFFourCCCodeNULL);

/**
 * Open a video clip from a descriptor source
 * @param "aDescriptor" The descriptor containing the video clip
 * @param "aCameraHandle" The handle of the camera to record from
 * @param "aControllerUid" Controller to use for recording
 * @param "aVideoFormat" The UID of the video format to record to.
 * @param "aVideoType" The descriptor containing the video mime type.
 * @param "aAudioType" A four character code representing the encoding to be used for audio data
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void OpenDesL(TDes8& aDescriptor,
							TInt aCameraHandle,
							TUid aControllerUid,
							TUid aVideoFormat,
							const TDesC8& aVideoType = KNullDesC8,
							TFourCC aAudioType = KMMFFourCCCodeNULL);

/**
 * Open a video clip from a URL
 * @param "aUrl" The URL containing the video clip
 * @param "aIapId" The Id of the internet access point to use
 * @param "aCameraHandle" The handle of the camera to record from
 * @param "aControllerUid" Controller to use for recording
 * @param "aVideoFormat" The UID of the video format to record to.
 * @param "aVideoType" The descriptor containing the video mime type.
 * @param "aAudioType" A four character code representing the encoding to be used for audio data
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void OpenUrlL(const TDesC& aUrl,
							TInt aIapId,
							TInt aCameraHandle,
							TUid aControllerUid,
							TUid aVideoFormat,
							const TDesC8& aVideoType = KNullDesC8,
							TFourCC aAudioType = KMMFFourCCCodeNULL);

/**
 * Close a video clip. 
 * @since 7.0s
 */
	IMPORT_C void Close();

/**
 * Prepare the recorder for recording. This should be called before the first call to
 * Record. The client will receive a MvruoPrepareComplete when the prepare operation is
 * complete
 * @since 7.0s
 */
	IMPORT_C void Prepare();

/**
 * Start recording a video clip. The client will receive a MvruoRecordComplete on completion of recording,
 * unless it explicitly ends recording with Stop. Prepare should be called before the first
 * call to Record.
 * @since 7.0s
 */
	IMPORT_C void Record();

/**
 * Video recording is stopped, without sending the MvruoRecordComplete
 * message to the client. 
 * @returns with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt Stop();

/** 
 * Video recording is paused.
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void PauseL();

/**
 * Set the recording priority. This is used to arbitrate between simultaneous accesses of
 * the sound hardware.
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetPriorityL(TInt aPriority, TMdaPriorityPreference aPref);

/**
 * Get the current recording priority. This is used to arbitrate between simultaneous accesses of
 * the sound hardware.
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetPriorityL(TInt& aPriority, TMdaPriorityPreference& aPref) const;

/**
 * Set the video frame rate
 * @param "aFrameRate" The video frame rate, in frames/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetVideoFrameRateL(TReal32 aFrameRate);

/**
 * Get the video frame rate
 * @returns Frame rate in frames/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TReal32 VideoFrameRateL() const;

/**
 * Set the video frame size
 * @param "aSize" The video frame size, in pixels
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetVideoFrameSizeL(const TSize& aSize);

/**
 * Get the video frame size
 * @param "aSize" The video frame size, in pixels
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetVideoFrameSizeL(TSize& aSize) const;

/**
 * Set the video bit rate 
 * @param "aBitRate" video bit rate in bits/second
 *		  This can be called with the parameter KMMFVariableVideoBitRate
 *		  which specifies a variable bit rate.
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetVideoBitRateL(TInt aBitRate);

/**
 * Get the video bit rate 
 * @returns video bit rate in bits/second or KMMFVariableVideoBitRate
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt VideoBitRateL();

/**
 * Set the audio bit rate 
 * @param "aBitRate" video bit rate in bits/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetAudioBitRateL(TInt aBitRate);

/**
 * Get the audio bit rate 
 * @returns audio bit rate in bits/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt AudioBitRateL() const;

/**
 * Set whether the current clip has an audio stream
 * @param "aEnabled" if an audio stream is to have an audio stream
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetAudioEnabledL(TBool aEnabled);

/**
 * Return whether the current clip has an audio stream
 * @returns ETrue if an audio stream is present
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TBool AudioEnabledL() const;

/**
 * Retrieve duration of video clip
 * @returns duration of clip in microseconds
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TTimeIntervalMicroSeconds DurationL() const;

/**
 * Set the maximum recording size for a video clip
 * @param "aClipSizeInBytes" The maximum file size of a video clip.
 *		  This can be called with the parameter KMMFNoMaxClipSize 
 *		  which signifies no maximum clip size.
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetMaxClipSizeL(TInt aClipSizeInBytes);

/**
 * Set the audio recording gain
 * @param "aGain" The recording gain, between 0 and MaxGain()
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetGainL(TInt aGain);

/**
 * Return the current recording Gain
 * @returns Current recording gain, between 0 and MaxGain()
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt GainL() const;

/**
 * Return the maximum recording Gain
 * @returns Maximum recording gain
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt MaxGainL() const;

/**
 * Get the number of meta data entries associated with this clip
 * @returns the number of meta data entries
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt NumberOfMetaDataEntriesL() const;

/**
 * Retrieve a meta data entry from the current clip
 * @param "aIndex" The index of the entry to retrieve. The index is between 0
 *		  and NumberOfMetaDataEntriesL()-1
 * @returns The meta data entry requested
 * @leave KErrArgument if the index is out of range, or with one of the other
 *			system-wide error codes
 * @since 7.0s
 */
	IMPORT_C CMMFMetaDataEntry* MetaDataEntryL(TInt aIndex) const;

/**
 * Add a meta data entry
 * @param "aNewEntry" The meta data entry to add
 * @leave Can leave with one of the system-wide error codes
 * @since 7.0s
 **/ 
	IMPORT_C void AddMetaDataEntryL(const CMMFMetaDataEntry& aNewEntry);

/**
 * Remove a meta data entry
 * @param "aIndex" The index of the meta data entry to remove
 * @leave Can leave with one of the system-wide error codes
 * @since 7.0s
 **/ 
	IMPORT_C void RemoveMetaDataEntryL(TInt aIndex);

/**
 * Replace a meta data entry
 * @param "aIndex" The index of the meta data entry to replace
 * @param "aNewEntry" The meta data entry to replace the previous entry
 * @leave Can leave with one of the system-wide error codes
 * @since 7.0s
 **/ 
	IMPORT_C void ReplaceMetaDataEntryL(TInt aIndex,const CMMFMetaDataEntry& aNewEntry);

/**
 * Get the audio type. This represents the encoding of audio
 * data within the current format.
 * @returns Four Character Code representing the AudioType
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TFourCC AudioTypeL() const;

/**
 * Set the video type. This represents the encoding of the video
 * data within the current format.
 * @param "aType" The descriptor containing the video mime type.
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetVideoTypeL(const TDesC8& aType);

/**
 * Set the audio type. This represents the encoding of the audio
 * data within the current format.
 * @param "aType" Four Character Code representing the Audio Type
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetAudioTypeL(TFourCC aType);

/**
 * Get a list of the video types that are supported for recording to.
 * @param "aVideoTypes" Array of Four Character Codes representing the video types 
 *		supported
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetSupportedVideoTypesL(CDesC8Array& aVideoTypes) const;

/**
 * Get a list of the audio types that are supported for recording to.
 * @param "aAudioTypes" Array of Four Character Codes representing the audio types 
 *		supported
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetSupportedAudioTypesL(RArray<TFourCC>& aAudioTypes) const;

/**
 * Get the (possibly estimated) record time left in the clip.
 * @returns	"The record time available, in microseconds."
 * @since 7.0s
 */
	IMPORT_C TTimeIntervalMicroSeconds RecordTimeAvailable() const;

/**
 * Get the video format's MIME type.
 * @returns Video Clip's MIME type
 * @since 7.0s
 */
	IMPORT_C const TDesC8& VideoFormatMimeType() const;

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
	enum TMMFVideoRecorderState
		{
		EStopped,
		EOpening,
		EPaused,
		ERecording		
		};

private:
	CBody* iBody;
	friend class CBody;
	};

#endif
