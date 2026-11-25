////////////////////////////////////////////////////////////////////////////////
//
// Project: mRouterClient
// -------
//
// File:	mRouterClient.h - Interface for the RmRouterClient Class
// ----
//
//
// History of Changes:
// ------------------
// o 16/07/2002 - Pierre Heler-Caruel - Intuwave, Ltd.
//   -------------------------------------------------
//   Changed handling of USB Connection. Now uses 3 parameters:
//   - number of Attempts
//   - initial Delay before the first Attempt
//   - Interval between each Attempt
//   Functions impacted:
//   - USBListenStartL()
//
//
// Legal notices:
// -------------
// Copyright © 2002 Intuwave, Ltd. All rights reserved
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _mRouterClient_H_
#define _mRouterClient_H_

#include <mrouterclientdefs.h>

class RmRouterClient : public RSessionBase
	{
public:
	IMPORT_C RmRouterClient();
	IMPORT_C ~RmRouterClient();
	IMPORT_C void ConnectL(TBool aStartIfNeeded);

	// Call to connect (via m-Router, using currently set config)
	// Attempt to connect for the specified number of attempts (or infinite with KAttemptForever)
	IMPORT_C TInt				MRConnectL(TInt aAttempts);
	// Call to disconnect whatever connection is up at the time and cancel connection attempts
	IMPORT_C void				MRDisconnectL();

	// Get and set the connection configuration parameters
	IMPORT_C void				MRConfigL(TmRConfig* aConfig);
	IMPORT_C void				MRSetConfigL(const TmRConfig& aConfig);

	// Get the connection status
	IMPORT_C void				MRStatusL(TmRStatus* aStatus);

	// Start, stop and get status of BT listener
	IMPORT_C void				BTListenStartL();
	IMPORT_C void				BTListenStopL();
	IMPORT_C void				BTListenStatusL(TBTListenStatus* aStatus);

	// Start, stop and get status of USB listener
	IMPORT_C void				USBListenStartL(const TmRUSBProperties &aUSBProperties);
	IMPORT_C void				USBListenStopL();
	IMPORT_C void				USBListenStatusL(TUSBListenStatus* aStatus);

	};

const TInt KmRouterClientMajorVersion = 1;
const TInt KmRouterClientMinorVersion = 0;

#endif //_mrouterclient_H_
