// ASCLIDEFINITIONS.H
//
// Copyright (c) Symbian Software Ltd 1999-2004. All rights reserved.
//
#ifndef __ASCLIDEFINITIONS_H__
#define __ASCLIDEFINITIONS_H__

// System includes
#include <e32base.h>

// User includes

// Type definitions

// Constants
#if defined(__WINS__) && !defined(EKA2)
const TInt KAlarmServerStackSize			= 0x0002000;	//  8KB
const TInt KAlarmServerHeapSizeInit			= 0x0001000;	//  4KB
const TInt KAlarmServerHeapSizeMaximum		= 0x1000000;	// 16MB
#endif

// Enumerations


///////////////////////////////////////////////////////////////////////////////////////
// ----> ASCliDefinitions (header)
///////////////////////////////////////////////////////////////////////////////////////
class ASCliDefinitions
/** This is a utility class that retrieves the name and version number of the alarm 
server. 
@publishedAll
@released
*/
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
