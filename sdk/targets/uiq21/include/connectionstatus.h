// connectionstatus.h
//
// Engine to allow monitoring
// of connection status

#ifndef __CONNECTIONSTATUS_H
#define __CONNECTIONSTATUS_H

#include <e32std.h>
#include <mrouteragent.h>
#include <nifman.h>

#include "mrouterclientdefs.h"

// Interface used for monitoring connection state
class MmRConnectionStateObserver
	{
public:
	virtual void HandleConnectionStatusChange(TmRConnectState aState)=0;
	};

// Connection status monitoring class
class CConnectionStatus : public CActive
	{
public:
	IMPORT_C static CConnectionStatus* NewL(
							RSocketServ& aSS, RNif& aNif,
		                    MmRConnectionStateObserver& aObserver);
	IMPORT_C virtual ~CConnectionStatus();

	IMPORT_C TmRConnectState ConnectionStatus();
	IMPORT_C void Start();
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();

protected:
	CConnectionStatus(	RSocketServ& aSS, RNif& aNif,
						MmRConnectionStateObserver& aObserver);
	void HandleConnectionStatusChange();
protected:
	RNif& iNif;
private:
	RSocketServ& iSS;
	MmRConnectionStateObserver& iObserver;
	TNifProgressBuf iProgress;
	TmRConnectState iOldConnStatus;
	};

#endif
