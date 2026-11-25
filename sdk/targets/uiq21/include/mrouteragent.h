// mrouteragent.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __MROUTERAGENT_H__
#define __MROUTERAGENT_H__

#ifndef __NIFMAN_H__
#include <nifman.h>
#endif


class RMRouterAgent : public RNif
	{
public:
	enum TConnectType { EDefault };
	IMPORT_C TInt Open();
	IMPORT_C TInt Start(TConnectType aConnectType=EDefault);
	};

_LIT(MROUTER_COMMSPEED,"CommSpeed");
_LIT(MROUTER_COMMDATA,"CommData");
_LIT(MROUTER_COMMHANDSHAKE,"CommHandshake");
_LIT(MROUTER_AUTHENTICATENAME,"AuthenticateName");
_LIT(MROUTER_AUTHENTICATEPASSWORD,"AuthenticatePassword");

_LIT(MROUTER_YESTOCONNECT,"YesToConnect");
_LIT(MROUTER_YESTORECONNECT,"YesToReconnect");

enum EMRouterProgress
	{
	EMRouterAgentUninitialised,          //0
	EMRouterAgentNoConnection,           //1
	EMRouterAgentStartingSelection,      //2
	EMRouterAgentFinishedSelection,      //3
	EMRouterAgentConnectionOpen=10,      //10
	EMRouterAgentStartingHangUp,         //11
	};

#endif
