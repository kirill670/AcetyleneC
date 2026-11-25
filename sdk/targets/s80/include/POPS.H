// POPS.H
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved. 
// 

#ifndef __POPS_H__
#define __POPS_H__

#include <e32base.h>
#include <imsk.h>
#include <msvstd.h>

const TInt KImPopSessionPriority = 1;

class CImPop3Settings;
class CPop3IdleTimer;
class CImIAPPreferences;

/**
@internalComponent
@released
*/
class CImPop3Session : public CMsgActive
    {
public:
	~CImPop3Session();		// destructor kills socket server
	static CImPop3Session* NewL();

	void ConnectL(CImPop3Settings* aPopSettings, const CImIAPPreferences& aPrefs,TRequestStatus& aStatus);
	void Quit(TRequestStatus&);
	void Waiting(TRequestStatus&);

	void SetMessageArray(TInt32* aIdArray, TUint aNoMessages);
	TInt32* MessageArray();
	
	TInt MessageNo(TMsvId);
	CImTextServerSession* TextServerSession();

	void SetPending();
	TBool IsPending();
	void SetOpNotPending();
	TBool IsConnectedToInternet();

private:
	CImPop3Session();	// constructor
	void ConstructL();

	void DoRunL();
	void DoCancel();
	void DoComplete(TInt&);

    void ChangeStateL();				// the state machine engine
	void ConstructApopL();
	void SetOpPending();
	TInt GetPopError();

private:
	enum				// States of "session" state machine
		{
		EConnectingToPop,
		EWaitingForReply,
		EAuthorisingUser,
		EAuthorisingPass,
		EAuthorisingApop,
		EPopConnected,
		EStopPop,
		ERequestingTLS,
		ESettingTLS,
		ELoggingEvent
		};
private:
	TInt				iState;
	TInt				iNextState;
	TInt				iCompleted;
	TBool				iOpPending;

	TBool				iSocketConnected;

	HBufC8*				iPopApop;
	HBufC8*				iConnectReply;

	CImPop3Settings*	iPopSettings;

	TInt				iNoMessages;
	TInt32*				iIdTab;

    CImTextServerSession*			iSocket;
public:
	TInt MaxHeaders();
    };

#endif
