// TSTSVCLI.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __TSTSVCLI_H__
#define __TSTSVCLI_H__

#include <e32std.h>
//#include <e32def.h> 

// A version must be specified when creating a session with the server
const TUint KTestServerMajorVersionNumber=0;
const TUint KTestServerMinorVersionNumber=1;
const TUint KTestServerBuildVersionNumber=1;

const TUint KDefaultTstSrvMessageSlots = 4;

// The server name
_LIT(KLitTestServerName,"NTRasTestServer");

// reasons for panic
enum TTestServerPanic
	{
	EClientBadRequest
	};

enum TTestSrvRequest
	{
	ETstSvChangeContextConfig,
	ETstSvChangeQoSConfig
	};

class RTestServer : public RSessionBase
	{
public:
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt ChangeContextConfig();
	IMPORT_C TInt ChangeQoSConfig();
	};
#endif