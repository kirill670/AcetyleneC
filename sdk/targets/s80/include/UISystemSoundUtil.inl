/*
* ==============================================================================
*  Name        : UISystemSoundUtil.inl
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : System Sound Utilities
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef __UISYSSOUNDUTIL_INL__
#define __UISYSSOUNDUTIL_INL__

const TInt KDefaultRepeat = 0;

inline void CUISysSoundPlayer::PlayFileL(TFileName& aFileName, TInt aVolume)
	{
	PlayFileL(aFileName, aVolume, EMdaPriorityNormal, EMdaPriorityPreferenceTimeAndQuality, KDefaultRepeat, TTimeIntervalMicroSeconds32(KUIUtilDefaultGap));
	}

inline void CUISysSoundPlayer::PlaySystemSoundL(const TBaSystemSoundType& aType, TInt aVolume)
	{
	PlaySystemSoundL(aType, aVolume, KDefaultRepeat, KUIUtilDefaultGap);
	}

#endif	//__UISYSSOUNDUTIL_INL__

// End of file