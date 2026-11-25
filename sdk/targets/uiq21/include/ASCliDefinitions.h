// ASCLIDEFINITIONS.H
//
// Copyright (c) 1999-2001 Symbian Ltd. All rights reserved.
//
#ifndef __ASCLIDEFINITIONS_H__
#define __ASCLIDEFINITIONS_H__

// System includes
#include <e32base.h>

// User includes

// Type definitions

// Constants
#ifdef __WINS__
const TInt KAlarmServerStackSize			= 0x0002000;	//  8KB
const TInt KAlarmServerHeapSizeInit			= 0x0001000;	//  4KB
const TInt KAlarmServerHeapSizeMaximum		= 0x1000000;	// 16MB
#endif

// Enumerations


///////////////////////////////////////////////////////////////////////////////////////
// ----> ASCliDefinitions (header)
///////////////////////////////////////////////////////////////////////////////////////
class ASCliDefinitions
	{
///////////////////////////////////////////////////////////////////////////////////////
public:										// STATIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C static const TDesC&			ServerAndThreadName();

	static const TDesC&						ServerImageName();

	static TUidType							ServerUidType();

	static TVersion							Version();

	};

#endif