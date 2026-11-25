// KEYCLICKREF.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

//
// Reference Key Click Plug-in DLL commands
//

#ifndef __KEYCLICKREF_H__

#include <MdaAudioTonePlayer.h>
#include <MdaAudioSamplePlayer.h>
#include <bassnd.h>
#include <coesndpy.h>
#include <eikenv.h>
#include <w32click.h>
#include <e32def.h>


// const literals
_LIT(KSysSndDatPath,"c:\\system\\data\\syssnd.dat");

// froward class declaration
class CEventPlayer;
//
// CSystemSoundConfigNotifier
//
class CSystemSoundConfigNotifier : public CActive
	{
public: //new 
	static CSystemSoundConfigNotifier* NewL(CEventPlayer* aEventPlayer, TBaSystemSoundUid aEventsUid);
	~CSystemSoundConfigNotifier();
public:
	// request
	void UpdateSystemSoundInfo();
private:
	void ConstructL(TBaSystemSoundUid aEventsUid);
	CSystemSoundConfigNotifier(CEventPlayer* aEventPlayer);
	// from CActive
	void DoCancel();
	void RunL();
private:
	TBaSystemSoundUid iSoundUid;
	RFs iFsSession;
	CEventPlayer* iEventPlayer;
	};

// 
// CEventPlayer
//
class CEventPlayer : public CBase, public MMdaAudioToneObserver, public MMdaAudioPlayerCallback
	{
public:
	void UpdateCurrentSystemSoundInfo(const TBaSystemSoundInfo& aSystemSoundInfo);
	void PreparePlayUtilityL();
	void SetIPrepare(TBool aState);
protected:
	//new functions
	void ConstructL(TBaSystemSoundUid aEventsUid);
	void Beep(TInt aRepeats = 0);
	void InitialiseCurrentSystemSoundInfoL(RFs& aFsSession, TBaSystemSoundUid aEventsUid);
	void PreparePlayOperationL();	
	void CancelPlay();
	TBool IsSoundEnabled();
	~CEventPlayer();
private:
	// From MMdaAudioToneObserver
	virtual void MatoPrepareComplete(TInt aError);
	virtual void MatoPlayComplete(TInt aError);
	// From MMdaAudioPlayerCallback
	virtual void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
	virtual void MapcPlayComplete(TInt aError); 
private:
	CMdaAudioToneUtility* iToneFixedUtility;
	CMdaAudioPlayerUtility* iFileUtility;
	CSystemSoundConfigNotifier* iSystemSoundNotifier;
	TBool iPrepared;
	TBool iPlaying;
	TInt iRepeats;
	// current system sound info
	TBaSystemSoundInfo iCurrentSystemSoundInfo;
	TBaSystemSoundInfo iOldSystemSoundInfo;
	TBool iSoundEnabled;
	};

//
// CPointerClickPlayer
//
class CPointerClickPlayer : public CEventPlayer
	{
public: 
	static CPointerClickPlayer* NewL();
public:
	void PointerEvent(const TPointerEvent& aEvent);
private:
	};

//
// CKeyClickPlayer
//
class CKeyClickPlayer : public CEventPlayer
	{
public: 
	static CKeyClickPlayer* NewL();
public:
	void KeyEvent(TEventCode aType,const TKeyEvent& aEvent);
private:
	};

// 
// CRefClickMaker
//
class CRefClickMaker : public CClickMaker
	{
public:
	static CClickMaker* NewL();
private:
	// New functions
	void ConstructL();
	// From CBase
	virtual ~CRefClickMaker();
	// From CClickMaker
	virtual void KeyEvent(TEventCode aType,const TKeyEvent& aEvent);
	virtual void PointerEvent(const TPointerEvent& aEvent);
	virtual void OtherEvent(TInt aType,TAny* aParam=NULL);
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs);
private:
	CPointerClickPlayer* iPointerPlay;
	CKeyClickPlayer* iKeyPlay;
	};



enum TReferenceKeyClickPluginCommand
	{
	EReferenceKeyClickPluginCommandQuery = 0,
	EReferenceKeyClickPluginCommandDisable = 1,
	EReferenceKeyClickPluginCommandEnableKeyClicks = 3,
	EReferenceKeyClickPluginCommandEnablePenClicks = 5,
	EReferenceKeyClickPluginCommandEnableBoth = 7
	};

enum TReferenceKeyClickPluginQueryResult
	{
	EReferenceKeyClickPluginCommandKeyClicksEnabled = 1,
	EReferenceKeyClickPluginCommandPenClicksEnabled = 2
	};



#endif

