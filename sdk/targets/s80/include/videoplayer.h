// VideoPlayer.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __VIDEOPLAYER_H__
#define __VIDEOPLAYER_H__

#include <w32std.h>
#include <fbs.h>
#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfcontroller.h>
#include <mmf\common\mmfstandardcustomcommands.h>
#include <mda\common\base.h>
#include <mmf\common\mmfUtilities.h>
#include <mmf\common\mmfControllerFrameworkBase.h>

/**
 * @publishedAll
 * @released
 *
 * An interface to a set of video player callback functions.
 *
 * The class is a mixin and is intended to be inherited by the client
 * class which is observing the video playing operation. The functions
 * encapsulated by this class are called when specific events occur in
 * the process of initialising and playing an video clip. A reference to
 * this object is passed as a parameter when constructing an audio player
 * utility object.
 *
 * @since 7.0s
 */
class MVideoPlayerUtilityObserver
	{
public:
/**
 *
 * Notification to the client that the opening of the video clip has completed, 
 * successfully, or otherwise.
 *
 * The client must now call Prepare() on the video player utility before the
 * video clip can be played or any of its properties (e.g. duration) can be
 * queried.
 * 
 *
 * @param	"aError"
 *          The status of the video player after initialisation.
 *			This is either KErrNone if the open has completed successfully,
 *			or one of the system wide error codes
 @ since	7.0s
 */
	virtual void MvpuoOpenComplete(TInt aError) = 0;

/**
 *
 * Notification to the client that the opening of the video clip has been prepared, 
 * successfully, or otherwise.  This callback is called in response to a call to
 * CVideoPlayerUtility::Prepare().
 *
 * The video clip may now be played, or have any of its properties (e.g. duration) queried.
 *
 * @param	"aError"
 *          The status of the video player after initialisation.
 *			This is either KErrNone if the open has completed successfully,
 *			or one of the system wide error codes
 @ since	7.0s
 */
	virtual void MvpuoPrepareComplete(TInt aError) = 0;


/**
 *
 * Notification that the frame requested by a call to GetFrameL is ready
 *
 * @param	"aFrame" The returned frame. The bitmap will contain
 *			the requested frame if the the error code is KErrNone (success)
 * @param	"aError"
 *          The status of the frame request.
 *			This is either KErrNone if the frame request was successful,
 *			or one of the system wide error codes
 @ since	7.0s
 */
	virtual void MvpuoFrameReady(CFbsBitmap& aFrame,TInt aError) = 0;

/**
 * Notification that video playback has completed. This is not called if 
 * playback is explicitly stopped by calling Stop.
 *
 * @param	"aError"
 *          The status of playback
 *			This is either KErrNone if the playback was completed successfully,
 *			or one of the system wide error codes
 * @since	7.0s
 */
	virtual void MvpuoPlayComplete(TInt aError) = 0;
	
/**
 * General event notification from controller. These events are specified by
 * the supplier of the controller
 *
 * @param	"aEvent"
 *          The event sent by the controller
 * @since	7.0s
 */
	virtual void MvpuoEvent(const TMMFEvent& aEvent) = 0;
	};
	
/**
 * @publishedAll
 * @released
 *
 * This is a mixin class to allow a client to receive notification of rebuffering
 * operations occurring in the video player
 *
 * @since 7.0s
 */
class MVideoLoadingObserver
	{
public:
/**
 * Notification that video clip loading/rebuffering has started
 *
 * @since	7.0s
 */
	virtual void MvloLoadingStarted() = 0;
/**
 * Notification that video clip loading/rebuffering has completed
 *
 * @since	7.0s
 */
	virtual void MvloLoadingComplete() = 0;
	};

class CMMFVideoPlayerCallback;

/**
 * @publishedAll
 * @released
 *
 * CVideoPlayerUtility. This class provides the main client API for video playback
 * functionality
 *
 * @since 7.0s	
 */
class CVideoPlayerUtility : public CBase
	{
	class CBody;
public:
/**
 * Destructor. Closes any open video clips and frees any resources held by the Video Player
 * @since 7.0s
 */
	~CVideoPlayerUtility();

/**
 * Factory function to return a new instance of CVideoPlayerUtility.
 * @param "aObserver" A client class to receive notifications
 *			from the video player
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Priority preference setting. 
 *			One of the values defined by TMdaPriorityPreference
 * @returns New instance of video player
 * @since 7.0s
 */
	IMPORT_C static CVideoPlayerUtility* NewL(MVideoPlayerUtilityObserver& aObserver,
											  TInt aPriority,
											  TMdaPriorityPreference aPref,
											  RWsSession& aWs,
											  CWsScreenDevice& aScreenDevice,
											  RWindowBase& aWindow,
											  const TRect& aScreenRect,
											  const TRect& aClipRect);

/**
 * Open a video clip from a file. The MvpuoOpenComplete callback will be returned to notify 
 * the client whether the clip was opened successfully.
 * @param "aFileName" The file to open
 * @param "aControllerUid" If specified, it will force the video player to use the 
 *			controller with the given Uid.
 * @leave Function can leave with one of the specified error codes. Most open failures
 *			will however be reported through the MVideoPlayerUtilityObserver interface.
 * @since 7.0s
 */
	IMPORT_C void OpenFileL(const TDesC& aFileName,TUid aControllerUid = KNullUid);

/**
 * Open a video clip from a descriptor. The MvpuoOpenComplete callback will be returned to notify 
 * the client whether the clip was opened successfully.
 * @param "aDescriptor" The descriptor containing the video clip
 * @param "aControllerUid" If specified, it will force the video player to use the 
 *			controller with the given Uid.
 * @leave Function can leave with one of the specified error codes. Most open failures
 *			will however be reported through the MVideoPlayerUtilityObserver interface.
 * @since 7.0s
 */
	IMPORT_C void OpenDesL(const TDesC8& aDescriptor,TUid aControllerUid = KNullUid);

/**
 * Open a video clip from a URL. The MvpuoOpenComplete callback will be returned to notify 
 * the client whether the clip was opened successfully.
 * @param "aUrl" The URL to open
 * @param "aIapId" The Id of the internet access point to use
 * @param "aMimeType" The MIME type associated with this video clip. This is
 *			used to determine the format of the video clip.
 * @param "aControllerUid" If specified, it will force the video player to use the 
 *			controller with the given Uid.
 * @leave Function can leave with one of the specified error codes. Most open failures
 *			will however be reported through the MVideoPlayerUtilityObserver interface.
 * @since 7.0s
 */
	IMPORT_C void OpenUrlL(const TDesC& aUrl, TInt aIapId = KUseDefaultIap, const TDesC8& aMimeType=KNullDesC8, TUid aControllerUid = KNullUid);

/**
 * Prepare the video clip to be accessed.
 * 
 * A call to this method tells the loaded controller plugin to finalise its configuration
 * and to prepare to start reading the video clip.  It is not possible to play the video clip
 * or query any of its properties (e.g. duration, meta data etc.) until this method has signified
 * its completion (successful or otherwise) via the callback MvpuoPrepareComplete.
 * 
 * @since 7.0s
 */
	IMPORT_C void Prepare();

/**
 * Close a video clip. 
 * @since 7.0s
 */
	IMPORT_C void Close();

/**
 * Play a video clip. The client will receive a MvpuoPlayComplete on completion of playback,
 * unless it cancels the playback with Stop.
 * @since 7.0s
 */
	IMPORT_C void Play();
	
/**
 * Play a video clip. The client will receive a MvpuoPlayComplete on completion of playback,
 * unless it cancels the playback with Stop.
 * @param "aStartPoint" Point at which to start playback
 * @param "aEndPoint" Point at which to terminate playback
 * @since 7.0s
 */
	IMPORT_C void Play(const TTimeIntervalMicroSeconds& aStartPoint, const TTimeIntervalMicroSeconds& aEndPoint);
/**
 * Stop video playback. Video playback is stopped, without sending the MvpuoPlayComplete
 * message to the client. The position is reset to the beginning of the file.
 * @returns with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt Stop();

/**
 * Video playback is paused. The current position is maintained and playback can be
 * resumed by calling Play.
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void PauseL();

/**
 * Set the playback priority. This is used to arbitrate between simultaneous accesses of
 * the sound hardware.
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetPriorityL(TInt aPriority, TMdaPriorityPreference aPref);

/**
 * Get the current playback priority. This is used to arbitrate between simultaneous accesses of
 * the sound hardware.
 * @param "aPriority" A priority between EMdaPriorityMin and EMdaPriorityMax
 * @param "aPref" Time vs Quality priority preferences, enumerated in TMdaPriorityPreference
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void PriorityL(TInt& aPriority, TMdaPriorityPreference& aPref) const;

/**
 * Set the Display Window. This is used to provide the video controller with an area of 
 * the display to render the current video frame.
 * @param "aWs" A session with the window server
 * @param "aScreenDevice" The screen device
 * @param "aWindow" The window to display
 * @param "aWindowRect" The rectangle to display
 * @param "aClipRect" The clip rectangle
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetDisplayWindowL(RWsSession& aWs,CWsScreenDevice& aScreenDevice,RWindowBase& aWindow,const TRect& aWindowRect,const TRect& aClipRect);
/**
 * Register to receive notifications of video clip loading/rebuffering
 * @param "aCallback" Object to receive video loading notifications
 * @since 7.0s
 */
	IMPORT_C void RegisterForVideoLoadingNotification(MVideoLoadingObserver& aCallback);
/**
 * Get the progress of video clip loading/rebuffering
 * @retval "aPercentageComplete" The percentage of loading/rebuffering complete. The parameter
 * 		   is zero if loading has not begun and 100 if loading has already completed
 * @since 7.0s
 */
	IMPORT_C void GetVideoLoadingProgressL(TInt& aPercentageComplete);

/**
 * Retrieve the current frame. The current frame is requested, and will be sent to
 * the client asynchrynously via the MvpuoFrameReady callback
 * @param "aDisplayMode" The display mode for the retrieved frame
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetFrameL(TDisplayMode aDisplayMode);
	
/**
 * Request the video controller to redraw the current frame
 * @since 7.0s
 */
	IMPORT_C void RefreshFrameL();
/**
 * Get the video frame rate
 * @returns Frame rate in frames/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TReal32 VideoFrameRateL() const;

/**
 * Set the video frame rate
 * @param "aFramesPerSecond" The number of frames per second to request
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetVideoFrameRateL(TReal32 aFramesPerSecond);

/**
 * Get the video frame size
 * @param "aSize" The video frame size
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void VideoFrameSizeL(TSize& aSize) const;

/**
 * Get the video format's MIME type.
 * @returns Video Clip's MIME type
 * @since 7.0s
 */
	IMPORT_C const TDesC8& VideoFormatMimeType() const;

/**
 * Get the video bit rate 
 * @returns video bit rate in bits/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt VideoBitRateL() const;

/**
 * Get the audio bit rate 
 * @returns audio bit rate in bits/second
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt AudioBitRateL() const;

/**
 * Get the audio type
 * @returns Four Character Code representing the VideoType
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TFourCC AudioTypeL() const;

/**
 * Return whether the current clip has an audio stream
 * @returns ETrue if an audio stream is present
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TBool AudioEnabledL() const;

/**
 * Set the current playback position
 * @param "aPosition" position in clip in microseconds
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetPositionL(const TTimeIntervalMicroSeconds& aPosition);

/**
 * Retrieve current playback position
 * @returns position in clip in microseconds
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TTimeIntervalMicroSeconds PositionL() const;

/**
 * Retrieve duration of video clip
 * @returns duration of clip in microseconds
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TTimeIntervalMicroSeconds DurationL() const;

/**
 * Set the playback volume
 * @param "aVolume" The volume, between 0 and MaxVolume()
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetVolumeL(TInt aVolume);

/**
 * Get the playback volume
 * @returns Volume, between 0 and MaxVolume()
 * @since 7.0s
 */
	IMPORT_C TInt Volume() const;

/**
 * Get the maximum playback volume
 * @returns Maximum playback volume
 * @since 7.0s
 */
	IMPORT_C TInt MaxVolume() const;

/**
 * Set the audio stereo balance
 * @param "aBalance" Balance between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetBalanceL(TInt aBalance);

/**
 * Retrieve audio stereo balance
 * @returns Balance between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
 * @since 7.0s
 */
	IMPORT_C TInt Balance()const;

/**
 * Rotate the video image on the screen
 * @param "aRotation" The desired rotation to apply
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetRotationL(TVideoRotation aRotation);

/**
 * Query the rotation that is currently applied to the video image
 * @leave  Can leave with one of the system wide error codes
 * @return The applied rotation
 * @since 7.0s
 */
	IMPORT_C TVideoRotation RotationL() const;

/**
 * Scale the video image to a specified percentage of its original size
 * @param "aWidthPercentage"	The percentage (100 = original size) to be used to scale the 
 *								width of the video image
 * @param "aHeightPercentage"	The percentage (100 = original size) to be used to scale the 
 *								height of the video image. If this is not equal to aWidthPercentage
 *								then the image may be distorted
 * @param "aAntiAliasFiltering" True if anti-aliasing filtering should be used.  If the plugin does not
 *								support this kind of processing, this value will be ignored
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetScaleFactorL(TReal32 aWidthPercentage, TReal32 aHeightPercentage, TBool aAntiAliasFiltering);

/**
 * Get the scale factor currently applied to the video image
 * @param "aWidthPercentage"	The percentage (100 = original size) used to scale the 
 *								width of the video image will be copied into here
 * @param "aHeightPercentage"The percentage (100 = original size) used to scale the 
 *								height of the video image will be copied into here
 * @param "aAntiAliasFiltering" True if anti-aliasing filtering is being used
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetScaleFactorL(TReal32& aWidthPercentage, TReal32& aHeightPercentage, TBool& aAntiAliasFiltering) const;

/**
 * Select a region of the video image to be displayed
 * @param "aCropRegion"	The dimensions of the crop region, relative to the video image
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void SetCropRegionL(const TRect& aCropRegion);

/**
 * Gets the crop region currently applied to the image
 * 
 * @param "aCropRegion"	The dimensions of the crop region, relative to the video image. If no
 *						crop region has been applied, the full dimensions of the video image will
						be returned.
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C void GetCropRegionL(TRect& aCropRegion) const;

/**
 * Get the number of meta data entries associated with this clip
 * @returns number of meta data entries
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C TInt NumberOfMetaDataEntriesL() const;

/**
 * Retrieve a meta data entry from the clip
 * @param "aIndex" The index of the meta data entry to retrieve
 * @returns The metadata entry requested
 * @leave Can leave with one of the system wide error codes
 * @since 7.0s
 */
	IMPORT_C CMMFMetaDataEntry* MetaDataEntryL(TInt aIndex) const;
	
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
	enum TMMFVideoPlayerState
		{
		EStopped,
		EOpening,
		EPaused,
		EPlaying		
		};

private:
	CBody* iBody;

	friend class CBody;
	friend class CTestStepUnitMMFVidClient;
public:
	class CTestView;
	friend class CTestView;
	};

#endif
