// SAVEPRIV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__SAVEPRIV_H__)
#define __SAVEPRIV_H__

_LIT(__SHUTDOWN_SERVER_NAME,"ShutdownServer");
_LIT(__SHUTDOWN_SERVER_SEMAPHORE_NAME,"ShutdownServerSemaphore");

const TInt KShutdownMajorVN			=6;
const TInt KShutdownMinorVN			=0;
const TInt KShutdownBuildVN			=1;
const TInt KShutdownMessageSlots	=1;

const TUid KUidNotifierSaveFail		={123456};

enum TSaveNotifierOpCode
	{
	TSaveOpCodeNotify,
	TSaveOpCodeNotifyCancel,
	TSaveOpCodeHandleError,
	};

struct TErrorAndClientId
	{
	TInt iError;
	TUint iClientId;
	};

//
// TShutdownServerStart
//
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
