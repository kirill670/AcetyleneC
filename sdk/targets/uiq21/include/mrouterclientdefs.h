////////////////////////////////////////////////////////////////////////////////
//
// Project: mRouterClient
// -------
//
// File:	mRouterClientDefs.h - Common mRouter Declarations
// ----
//
//
// History of Changes:
// ------------------
// o 16/07/2002 - Pierre Heler-Caruel - Intuwave, Ltd.
//   -------------------------------------------------
//   Added TmRUSBProperties Structure to handle USB Connection Properties
//
// Legal notices:
// -------------
// Copyright © 2001, 2002 Intuwave, Ltd. All rights reserved
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MROUTERCLIENTDEFS_H
#define __MROUTERCLIENTDEFS_H

#include <nifman.h>
#ifndef DONT_BUILD_BLUETOOTH
	#include <btregistry.h>
#endif

// m-Router connection configuration
enum TBearer
	{
	EmR_RS232,
	EmR_IRCOMM,
	EmR_RFCOMM,
	EmR_USB,
	EmR_EMULATOR,
	EmR_OTA,
	EmR_Bearer_Unknown
	};
enum TBTProfile	// BT profile to use for m-Router connection (should be SPP for now)
	{
	EBT_SerialPort=0x1101,
	EBT_LANAccess=0x1102,
	EBT_DialupNetworking=0x1103,
	};
enum TRoutePref	// Not implemented
	{
	EmR_RouteGenConn,
	EmR_RoutemRouter
	};

// Connection attempts
const TInt KAttemptForever= KMaxTInt;

// Structure used for getting/setting config information
struct TmRConfig
	{
	enum TBearer	iBearer;	// Choose your bearer

	enum TBTProfile	iBTProfile;	// Setup for BT.CSY
#ifndef DONT_BUILD_BLUETOOTH
	TBTDevAddr		iBDAddr;
#endif
	enum TRoutePref	iRoutePref;	// Configure default route - genconn or m-Router (Not Implemented)

	TInfoName		iUser;		// Logon for m-Router Access Point
	TPassword		iPass;

	THostName		iHost;		// Address for m-Router Access Point (only used if bearer set to OTA)
	TUint			iPort;

	// Bearer information
	TUint			iBearerUnit;	// The Unit for the bearer, for cable this is the COM port to use
	TUint			iBearerSpeed;	// The speed of the bearer
	};

// Structure used for Passing USB Connection Properties (PHC - Intuwave, Ltd. - 16/07/2002)
struct TmRUSBProperties
{
	TTimeIntervalMicroSeconds32 iInitialDelay;		// The initial delay after the Cable is plugged in
	TTimeIntervalMicroSeconds32 iAttemptInterval;	// The interval between subsequent Connection Attempts
	TUint						iTries;				// The maximum Number of times to try connecting.
};

// Connection status monitoring
enum TmRSimpleConnectState
	{
	EmRConnecting,
	EmRConnected,
	EmRDisconnected
	};
struct TmRConnectState
	{
	enum TmRSimpleConnectState	iConnectState;	// Interpretation of RNif result
	TNifProgress		iNifProgress;	// Raw value from RNif
	};

// m-Router Connect Status
struct TmRStatus
	{
	enum TBearer	iBearer;		// Bearer in use
	TmRConnectState	iConnectState;	// Connection status
	};

// Bluetooth listener status 
enum TBTListenStatus { EStopped, EStarted, ENotSupported };

// USB listener status 
enum TUSBListenStatus { EUSBStopped, EUSBStarted, EUSBNotSupported };

const TInt KMaxServiceNameLength = 40;

// Service details
struct TmRServiceEntry
	{
	TBuf<KMaxServiceNameLength> iName;
	TInt	iPort;
	};

#endif
