// Mda\Common\MmfVideo.h
//
// Copyright (c) Symbian Software Ltd 2002-2005.  All rights reserved.
//

#ifndef __MMF_COMMON_VIDEO_H__
#define __MMF_COMMON_VIDEO_H__

#include <mmf\common\MmfUtilities.h>

class CFbsBitmap;

/**
@publishedAll
@released

The use of this constant as either a parameter for
CVideoRecorderUtility::SetVideoBitRateL or as a return value from
CVideoRecorderUtility::VideoBitRateL signifies that a variable
video bit rate is being used.
*/
const TInt KMMFVariableVideoBitRate = -1;

/**
@publishedAll
@released

CVideoRecorderUtility::SetMaxClipSizeL can take this constant
instead of a byte value.  This signifies there should be no max
clip size
*/
const TInt KMMFNoMaxClipSize = -1;

/**
@publishedAll
@released

CVideoPlayerUtility/CVideoRecorderUtility HandleEvent() code :
the video source file has been successfully opened
*/
const TUid KMMFEventCategoryVideoOpenComplete = {0x101F7F85};

/**
@publishedAll
@released

The unique identifier for the event that indicates that the video has been prepared for recording.
*/
const TUid KMMFEventCategoryVideoPrepareComplete = {0x101F7F86};

/**
@publishedAll
@released
*/
const TUid KMMFEventCategoryVideoLoadingStarted = {0x101F7F87};

/**
@publishedAll
@released
*/
const TUid KMMFEventCategoryVideoLoadingComplete = {0x101F7F88};

/**
@publishedAll
@released
*/
const TUid KMMFEventCategoryVideoPlayerGeneralError = {0x101F8000};

/**
@publishedAll
@released
*/
const TUid KMMFEventCategoryVideoRecorderGeneralError = {0x101F8001};


/**
@publishedAll
@released

Defines an absolute rotation in 90 degree increments

@since  7.0s
*/
enum TVideoRotation
	{
	EVideoRotationNone,
	EVideoRotationClockwise90,
	EVideoRotationClockwise180,
	EVideoRotationClockwise270
	};

/**
@publishedAll
@released

Class used when sending custom commands from the client API
to the video controller to get or set the video configuration.
*/
class TMMFVideoConfig
	{
public:
	inline TMMFVideoConfig();

public:
	/**
	A flag indicating whether audio output is enabled. ETrue if teh audio is to be enabled, false if
	not.
	*/
	TBool						iAudioEnabled;
	/**
	The location of the top left corner of the video window.
	*/
	TPoint						iTopLeftPt;
	/**
	Defines the rectangle in which the video clip will be played.
	*/
	TRect						iClipRect;
	/**
	A handle to the bitmap into which the decoded frame(s) are put.
	*/
	TInt						iBitmapHandle;
	/**
	The current frame number in the video clip.
	 */
	TInt						iFrameNumber;
	/**
	The number of frames per second; may not be an integer.
	*/
	TReal32						iFramesPerSecond;
	/**
	The width & height of the video frame.
	*/
	TSize						iVideoFrameSize;
	/**
	The volume setting of the video device.

	Should be between 0 and iMaxVolume.
	*/
	TInt						iVolume;
	/**
	The maximum volume setting of the video device.

	This value is platform dependent but is always greater than or equal to one. This is the maximum
	value that should be passed to iVolume.
	*/
	TInt						iMaxVolume;
	/**
	The balance of the audio channels for the video device. Zero for normal balance.
	*/
	TInt						iBalance;
	/**
	The gain of the audio channels for the video device. This can be any value from zero to
	iMaxGain.
	*/
	TInt						iGain;
	/**
	The maximum gain of the audio channels for the video device.
	*/
	TInt						iMaxGain;
	/**
	Unused.

	Meta data is often contained in the header of multimedia clips and is used to define attributes
	such as the author and copyright details.
	*/
	TInt						iMetaData;
	/**
	Set the maximum size of the recording, in bytes.
	*/
	TInt						iMaxFileSize;
	/**
	The number of channels (mono/stereo) that can be read by the video device.
	*/
	TUint						iChannels;
	/**
	The video bit rate of the video device.
	*/
	TInt						iVideoBitRate;
	/**
	The audio bit rate of the video device.
	*/
	TInt						iAudioBitRate;
	/**
	The unique identifier of the video format handled by the video device.
	*/
	TUid						iFormatUid;
	/**
	The video data type represented as a fourCC code.
	*/
	TFourCC						iVideoCodec;
	/**
	The audio data type represented as a fourCC code.
	*/
	TFourCC						iAudioCodec;
	/**
	The period over which the volume is to rise.
	*/
	TTimeIntervalMicroSeconds	iRampDuration;
	/**
	The start position for playback in micro seconds.
	 */
	TTimeIntervalMicroSeconds	iStartPosition;
	/**
	The end position for playback in micro seconds.
	 */
	TTimeIntervalMicroSeconds	iEndPosition;
	/**
	The (possibly estimated) record time left in the clip.
	*/
	TTimeIntervalMicroSeconds	iRecordTimeAvailable;
	/**
	Handle to the bitmap of the current video frame.

	Used by RMMFVideoPlayControllerCustomCommands::GetFrame()
	to pass a bitmap handle to the video controller.
	*/
	TInt						iFrameBitmapServerHandle;
	/**
	Defines the window in which the video clip will be played.
	 */
	TRect						iWindowRect;
	/**
	A handle to the video camera being used.
	*/
	TInt						iCameraHandle;
	/**
	Whether the video display is active
	*/
	TInt						iDSAEvent;
	/**
	The percentage of loading/rebuffering completed.
	*/
	TInt						iLoadingCompletePercentage;
	/**
	The video rotation.
	*/
	TVideoRotation				iVideoRotation;
	/**
	The percentage (100 = original size) by which the width of the video image is scaled.
	*/
	TReal32						iWidthScalePercentage;
	/**
	The percentage (100 = original size) by which the height of the video image is scaled.
	*/
	TReal32						iHeightScalePercentage;
	/**
	A boolean indicating if anti-aliasing filtering should be used.
	*/
	TBool						iAntiAliasFiltering;
	/**
	The crop region currently applied to the image.
	*/
	TRect						iCropRectangle;
private:
	/**
	This member is internal and not intended for use.
	*/
	TInt iReserved1;
	TInt iReserved2;
	TInt iReserved3;
	};

/**
Initialises the object with arbitrary values.
*/
inline TMMFVideoConfig::TMMFVideoConfig() {};

/**
@publishedAll
@released

Interface class to provide a callback to the video controller
custom command interface from the controller plug-in
(the object that implements the video record controller interface
MMMFVideoPlayControllerCustomCommandImplementor) when a GetFrame()
request has been issued.

@see RMMFVideoPlayControllerCustomCommands::GetFrame()
*/
class MMMFVideoFrameMessage 
	{
public:
	/**
	Called when a frame has been successfully decoded.

	@param  aError
	        The result code to be given to the client.
	*/
	virtual void FrameReady(TInt aError) = 0;
	/**
	Returns the decoded frame as a bitmap.

	@return A reference to the video frame.
	*/
	virtual CFbsBitmap& GetBitmap() = 0;
	};

#endif
