// e32\include\e32debug.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#ifndef __E32DEBUG_H__
#define __E32DEBUG_H__
#include <e32std.h>			// TThreadId

/**	@publishedPartner
	@removed
*/
const TInt KMaxProfiles=64;

/**	@publishedPartner
	@removed
*/
class TProfile
    {
public:
    TInt iTime;
    TInt iCount;
    };
//

/**	
@publishedPartner


A class that provides functions to print arbitrary data to the debug port. 

These fuctions are used at the user context only.

On Emulator these functions can be used to print the formatted text to a log file called epocwind.out, 
which is created in the Windows Temp directory.  

On hardware, the trace log is sent to the debug port, from where 
it can be viewed using a terminal emulator on a connected PC.
*/
class RDebug
	{
public:
    IMPORT_C static void Printf(const char*, ...);
    IMPORT_C static void RawPrint(const TDesC8& aDes);
    IMPORT_C static TInt Print(TRefByValue<const TDesC> aFmt,...);
    IMPORT_C static void RawPrint(const TDesC16& aDes);
	};

#endif

