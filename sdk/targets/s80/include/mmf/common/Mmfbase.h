// MmfBase.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MMFBASE_H__
#define __MMFBASE_H__

// Standard EPOC32 includes
#include <e32base.h>


/** 
 * @publishedAll
 * @released
 *
 * Audio device client priority numbers
 *
 * Used by the policy component to arbitrate between different 
 * clients that are attempting to use the same hardware 
 * resource simultaneously.
 */
enum TMdaPriority
	{
    EMdaPriorityMin = -100,
    EMdaPriorityNormal = 0,
    EMdaPriorityMax = 100
	};

/** 
 * @publishedAll
 * @released
 *
 * A set of priority values which define the behaviour to be adopted by an
 * audio client if a higher priority client takes over the device.
 */
enum TMdaPriorityPreference
	{
    EMdaPriorityPreferenceNone =	0x00000000,
    EMdaPriorityPreferenceTime =	0x00000001,
    EMdaPriorityPreferenceQuality = 0x00000002,
    EMdaPriorityPreferenceTimeAndQuality = EMdaPriorityPreferenceTime|EMdaPriorityPreferenceQuality
	};

/** 
 * @publishedAll
 * @released
 *
 * Holds the current state of DevSound
 */
enum TMMFState
{
	EMMFStateIdle,
	EMMFStatePlaying,
	EMMFStateTonePlaying,
	EMMFStateRecording,
	EMMFStatePlayingRecording,
	EMMFStateConverting
};

/**
 * @publishedAll
 * @released
 *
 * A class type representing the audio client's priority, 
 * priority preference and state.
 *
 */
class TMMFPrioritySettings
	{
public:
	TInt iPriority;
	TMdaPriorityPreference iPref;
	TMMFState iState;
	};

/**
 * @publishedAll
 */
typedef TPckgBuf<TMMFPrioritySettings> TMMFPrioritySettingsPckg;


#endif
