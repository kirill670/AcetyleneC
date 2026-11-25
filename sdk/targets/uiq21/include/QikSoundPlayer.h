// QIKSOUNDPLAYER.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKSOUNDPLAYER_H__
#define __QIKSOUNDPLAYER_H__

#include <e32base.h>
#include <eikenv.h>
#include <asshdalarm.h>
#include <mda\client\utility.h> // workaroud missing forward declaration in MediaSvr
#include <MdaAudioTonePlayer.h>
#include <MdaAudioSamplePlayer.h>

/**
* Mixin class for the observer of the class CQikSoundPlayer
*/
class MQikSoundPlayerObserver
	{
	public:
	/**
	* Called when playing has ended of any reason
	*/
	virtual void PlayComplete() = 0;
	};

/**
 * this class provides methos to play sounds
 * @since Quartz 7.0
 **/
class CQikSoundPlayer : public CBase, public MMdaAudioToneObserver, public MMdaAudioPlayerCallback
	{
public:
	IMPORT_C static CQikSoundPlayer* NewL(CEikonEnv& aEnv);
	IMPORT_C ~CQikSoundPlayer();
	IMPORT_C void StartPlayL(const TDesC& aFileName);
	IMPORT_C void StopPlay();
	IMPORT_C TBool IsPlaying() const;
	IMPORT_C void SetObserver(MQikSoundPlayerObserver* aObserver);
	IMPORT_C void PlayOrStopIfSameIsPlayingL(const TDesC& aFileName, CBase* aObjectWantingToPlay);
	IMPORT_C void StopPlayIfOwner(CBase* aObjectWantingToStop);
	IMPORT_C void SetSoundVolume(TInt aVolume);
	IMPORT_C void SetSoundPriority(const TInt aPriority, const TMdaPriorityPreference aPriorityPreference);
private:
	CQikSoundPlayer(CEikonEnv& aEnv);
	void ConstructL();
	void PlaySoundL();
	void UpdateVolume();
	TInt FindFixedSequenceSound() const;
private: // from MMdaAudioToneObserver
	void MatoPrepareComplete(TInt aError);
	void MatoPlayComplete(TInt aError);
private: // from MMdaAudioPlayerCallback
	void MapcInitComplete(TInt aError,const TTimeIntervalMicroSeconds& aDuration);
	void MapcPlayComplete(TInt aError);
private:
	CMdaAudioToneUtility* iSequencePlayer;
	CMdaAudioPlayerUtility* iFilePlayer;
	MQikSoundPlayerObserver* iQikSoundPlayerObserver;
	TInt iCurrentVolume;
	CEikonEnv& iEikEnv;
	TBuf<KMaxFileName> iFileName;
	TBool iIsPlaying;
	TInt iCurrentPlayer;
	TBool iSequencePlayerReady;
	enum TSoundPlayer
		{
		ENone,
		ESequencePlayer,
		EFilePlayer
		};
	CBase* iObjectCurrentlyPlaying;
	TInt iPriority;
	TMdaPriorityPreference iPriorityPreference;
	};

#endif
