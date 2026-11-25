// Mda\Common\MmfVideo.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MMF_COMMON_VIDEO_H__
#define __MMF_COMMON_VIDEO_H__

#include <mmf\common\MmfUtilities.h>

class CFbsBitmap;

/**
 * @publishedAll
 *
 * The use of this constant as either a parameter for 
 * CVideoRecorderUtility::SetVideoBitRateL or as a return value from
 * CVideoRecorderUtility::VideoBitRateL signifies that a variable
 * video bit rate is being used.
 */
const TInt KMMFVariableVideoBitRate = -1;

/**
 * @publishedAll
 *
 * CVideoRecorderUtility::SetMaxClipSizeL can take this constant 
 * instead of a byte value.  This signifies there should be no max
 * clip size
 */
const TInt KMMFNoMaxClipSize = -1;

/**
 * @publishedAll
 *
 * CVideoPlayerUtility/CVideoRecorderUtility HandleEvent() code :
 * the video source file has been successfully opened
 */
const TUid KMMFEventCategoryVideoOpenComplete = {0x101F7F85};

/**
 * @publishedAll
 */
const TUid KMMFEventCategoryVideoPrepareComplete = {0x101F7F86};
/**
 * @publishedAll
 */
const TUid KMMFEventCategoryVideoLoadingStarted = {0x101F7F87};
/**
 * @publishedAll
 */
const TUid KMMFEventCategoryVideoLoadingComplete = {0x101F7F88};
/**
 * @publishedAll
 */
const TUid KMMFEventCategoryVideoPlayerGeneralError = {0x101F8000};
/**
 * @publishedAll
 */
const TUid KMMFEventCategoryVideoRecorderGeneralError = {0x101F8001};


/**
 * @publishedAll
 * @released
 * Defines an absolute rotation in 90 degree increments
 *
 * @since 7.0s
 */
enum TVideoRotation
	{
	EVideoRotationNone,
	EVideoRotationClockwise90,
	EVideoRotationClockwise180,
	EVideoRotationClockwise270
	};

/**
 * @publishedAll
 * @released
 *
 * class used when sending custom commands from the client API
 * to the video controller to get or set the video configuration
 * 
 */
class TMMFVideoConfig
	{
public:
	inline TMMFVideoConfig();

public:
	/**
	 * Flag indicating whether audio output is enabled
	 */
	TBool						iAudioEnabled;
	/**
	 *
	 */
	TPoint						iTopLeftPt;
	/**
	 * defines the rectangle in which the video clip will be played
	 */
	TRect						iClipRect;
	/**
	 * a handle to the bitmap into which the decoded frame(s) are put
	 */
	TInt						iBitmapHandle;
	/**
	 * the current frame number
	 */
	TInt						iFrameNumber;
	/**
	 * the number of frames per second; may not be an integer
	 */
	TReal32						iFramesPerSecond;  
	/**
	 * the width & height of the video frame
	 */
	TSize						iVideoFrameSize;
	/**
	 * the volume
	 */
	TInt						iVolume;
	/**
	 * the maximum possible volume
	 */
	TInt						iMaxVolume;
	/**
	 * The balance. Zero for normal balance.
	 */
	TInt						iBalance;
	/**
	 * The gain.  This can be any value from zero to iMaxGain
	 */
	TInt						iGain;
	TInt						iMaxGain;
	/**
	 * 
	 */
	TInt						iMetaData;
	/**
	 * 	Set the maximum size of the recording, in bytes.
	 */
	TInt						iMaxFileSize;
	/**
	 * mono/stereo setting
	 */
	TUint						iChannels;
	/**
	 * video bit rate
	 */
	TInt						iVideoBitRate;
	/**
	 * audio bit rate
	 */
	TInt						iAudioBitRate;
	/**
	 * The format uid to be used
	 */
	TUid						iFormatUid;
	/**
	 * the video data type represented as a fourCC code  
	 */
	TFourCC						iVideoCodec;
	/**
	 * the audio data type represented as a fourCC code 
	 */
	TFourCC						iAudioCodec;
	/**
	 * The period over which the volume is to rise
	 */
	TTimeIntervalMicroSeconds	iRampDuration;
	/**
	 *
	 * The start position for playback in micro seconds
	 */
	TTimeIntervalMicroSeconds	iStartPosition;
	/**
	 * The end position for playback in micro seconds
	 */
	TTimeIntervalMicroSeconds	iEndPosition;
	/**
	 * 	Get the (possibly estimated) record time left in the clip.
	 */
	TTimeIntervalMicroSeconds	iRecordTimeAvailable;
	/**
	 * used by RMMFVideoPlayControllerCustomCommands::GetFrame()
	 * to pass a bitmap handle to the video controller
	 */
	TInt						iFrameBitmapServerHandle;
	/**
	 * defines the window in which the video clip will be played
	 */
	TRect						iWindowRect;
	/**
	 * the camera handle
	 */
	TInt						iCameraHandle;
	/**
	 * Whether video display is active
	 */
	TInt						iDSAEvent;
	/**
	 * The percentage of loading/rebuffering complete
	 */
	TInt						iLoadingCompletePercentage;
	/**
	 * The video rotation
	 */
	TVideoRotation				iVideoRotation;
	/**
	 *
	 */
	TReal32						iWidthScalePercentage;
	/**
	 *
	 */
	TReal32						iHeightScalePercentage;
	/**
	 *
	 */
	TBool						iAntiAliasFiltering;
	/**
	 *
	 */
	TRect						iCropRectangle;
	};

inline TMMFVideoConfig::TMMFVideoConfig() {};

/**
 * @publishedAll
 * @released
 *
 * Interface class to provide a callback to the video controller 
 * custom command interface from the controller plug-in
 * (the object that implements the video record controller interface 
 * MMMFVideoPlayControllerCustomCommandImplementor) when a GetFrame()
 * request has been issued
 * 
 * @see RMMFVideoPlayControllerCustomCommands::GetFrame()
 *
 */
class MMMFVideoFrameMessage 
	{
public:
	/**
	 * called when a frame has been successfully decoded
	 */
	virtual void FrameReady(TInt aError) = 0;
	/**
	 * return the decoded frame as a bitmap
	 */
	virtual CFbsBitmap& GetBitmap() = 0;
	};

#endif
