// SAVEPRIV.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd. All rights reserved.
//

#if !defined(__SAVEPRIV_H__)
#define __SAVEPRIV_H__


_LIT(__SHUTDOWN_SERVER_NAME,"!ShutdownServer");

/**
@internalTechnology
*/
const TInt KShutdownMajorVN			=6;
const TInt KShutdownMinorVN			=0;
const TInt KShutdownBuildVN			=1;
const TInt KShutdownMessageSlots	=1;

/**
@internalTechnology
*/
const TUid KUidNotifierSaveFail		={123456};

/**
@internalTechnology
*/
enum TSaveNotifierOpCode
	{
	TSaveOpCodeNotify,
	TSaveOpCodeNotifyCancel,
	TSaveOpCodeHandleError,
	TSaveOpCodePowerOff        //Only in debug mode
	};

/**
@internalTechnology
*/
struct TErrorAndClientId
	{
	TInt iError;
	TUint iClientId;
	};

//
// TShutdownServerStart
//
/**
@internalTechnology
*/
class TShutdownServerStart
	{
public:
	TShutdownServerStart(TRequestStatus& aStatus);
	TPtrC AsCommand() const;
//
	TShutdownServerStart();
	TInt GetCommand();
	void SignalL();
private:
	TThreadId iId;
	TRequestStatus* iStatus;
	};


#endif
