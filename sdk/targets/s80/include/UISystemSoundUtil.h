/*
* ==============================================================================
*  Name        : UISystemSoundUtil.h
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

#ifndef __UISYSTEMSOUNDUTIL_H__
#define __UISYSTEMSOUNDUTIL_H__

#include <bassnd.h>
#include <MdaAudioSamplePlayer.h>
#include <lafcknsd.h>

const TInt KUIUtilUseSystemPriority = -101;
const TInt KUIUtilDefaultGap = 0;

class MUISysSoundPlayerCallback
	{
public:
	virtual void UISysSoundInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration)=0;
	virtual void UISysSoundPlayComplete(TInt aError)=0;
	};

class CUISysSoundPlayer : public CBase, public MMdaAudioPlayerCallback
	{
public:
	enum TPlaybackEffect
		{
		EPlaybackSilent,
		EPlaybackOnce,
		EPlaybackRepeated,
		EPlaybackERROR
		};
public:
	IMPORT_C static CUISysSoundPlayer* NewL(MUISysSoundPlayerCallback* aObserver=NULL);
	IMPORT_C void PlayFileL(TFileName& aFileName, TInt aVolume, TInt aPriority, TMdaPriorityPreference aPref, TInt aRepeat, const TTimeIntervalMicroSeconds32& aGap);
	IMPORT_C TPlaybackEffect PlaySystemSoundL(const TBaSystemSoundType& aType, TInt aVolume, TInt aRepeat, const TTimeIntervalMicroSeconds32& aGap, TInt aPriority = KUIUtilUseSystemPriority, TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);
	IMPORT_C void StopPlaying();
	inline void PlayFileL(TFileName& aFileName, TInt aVolume);
	inline void PlaySystemSoundL(const TBaSystemSoundType& aType, TInt aVolume);
	~CUISysSoundPlayer();
private:
	CUISysSoundPlayer(MUISysSoundPlayerCallback* aObserver = NULL);
	void ConstructL();
	void GetSystemSoundL(const TBaSystemSoundType& aType, TFileName& aFileName, TInt& aVolume, TInt &aRepeats, TInt& aPriority, TMdaPriorityPreference& aPref);
	TInt ProfilesSound(TUid aSoundUid, TBool aDefaultSound, TFileName& aFileName, TInt& aVolume, TInt& aRepeats, TInt& aPriority, TMdaPriorityPreference& aPref);
private:
	//from MMdaAudioPlayerCallback
	void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
	void MapcPlayComplete(TInt aError);
private:
	MUISysSoundPlayerCallback* iObserver;
	CMdaAudioPlayerUtility* iPlayerUtility;
	TBaSystemSoundType iSystemSound;		// Set up if playing a system sound, rather than a specified file
	TInt iPriority;
	TMdaPriorityPreference iPref;
	TInt iPercentageVolume;
	TInt iRepeatCount;
	TTimeIntervalMicroSeconds32 iGap;
	TInt	iResourceFileOffset;
	TBool iActive;
	};

#include <UISystemSoundUtil.inl>

#endif	__UISYSTEMSOUNDUTIL_H__

// End of file