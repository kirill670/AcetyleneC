// TaskConfig.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

/**
 * @publishedPartner
 * @released
 */

#ifndef __TASKCONFIG_H__
#define __TASKCONFIG_H__

/**
 * @publishedPartner
 * @released
 */
enum TTaskSampleRate
	{
	ETask8000Hz  = 0x00000001,	///<  8000 Hz Sampling Rate
	ETask11025Hz = 0x00000002,	///< 11025 Hz Sampling Rate
	ETask16000Hz = 0x00000004,	///< 16000 Hz Sampling Rate
	ETask22050Hz = 0x00000008,	///< 22050 Hz Sampling Rate
	ETask32000Hz = 0x00000010,	///< 32000 Hz Sampling Rate
	ETask44100Hz = 0x00000020,	///< 44100 Hz Sampling Rate
	ETask48000Hz = 0x00000040,	///< 48000 Hz Sampling Rate
	ETask88200Hz = 0x00000080,	///< 88200 Hz Sampling Rate
	ETask96000Hz = 0x00000100,	///< 96000 Hz Sampling Rate
	ETask12000Hz = 0x00000200,	///< 12000 Hz Sampling Rate
	ETask24000Hz = 0x00000400,	///< 24000 Hz Sampling Rate
	ETask64000Hz = 0x00000800	///< 64000 Hz Sampling Rate
	};

/**
 * @publishedPartner
 * @released
 */
enum TTaskStereoMode
	{
	ETaskMono			= 0x00000001,
	ETaskInterleaved	= 0x00000002,
	ETaskNonInterleaved	= 0x00000004
	};

/**
 * @publishedPartner
 * @released
 */
class TTaskConfig
	{
	public:
		TInt iRate;
		TInt iStereoMode;
		TInt iUid;
	};

#endif

