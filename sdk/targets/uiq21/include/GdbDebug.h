// GdbDebug.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
// Debugging Facilities
//

#ifndef __GDBDEBUG_H__
#define __GDBDEBUG_H__

#ifndef __E32STD_H__
#include <e32std.h>
#endif


// Under WINS the default EPOC assertion mechanism is OK because there
// is JIT Debugging.  But on target devices it is useful to dump the
// file and line of the failed assertion.
//

IMPORT_C void GdbPanic(TInt aReason = 0);

#if defined(__WINS__)

#define ASSERTA(expr) __ASSERT_ALWAYS((expr), GdbPanic())
#define ASSERTD(expr) __ASSERT_DEBUG((expr), GdbPanic())
#define CANT_HAPPEN() GdbPanic()

#else

IMPORT_C void GdbAssertFailed(const char*, TInt);

#define ASSERTA(expr) __ASSERT_ALWAYS((expr), GdbAssertFailed(__FILE__, __LINE__))
#define ASSERTD(expr) __ASSERT_DEBUG((expr), GdbAssertFailed(__FILE__, __LINE__))
#define CANT_HAPPEN() GdbAssertFailed(__FILE__, __LINE__)

#endif // defined(__WINS__)


class Trace
//
// Static class containing functions to log debug traces
//
	{

public:
	IMPORT_C static void InitL(TBool aIsEnabled);
	IMPORT_C static void Cleanup();
	IMPORT_C static void Msg(TRefByValue<const TDesC> aFmt, ...);
	IMPORT_C static void Enter(const TDesC& aFunction, TRefByValue<const TDesC> aFmt, ...);
	IMPORT_C static void Exit(const TDesC& aFunction, TRefByValue<const TDesC> aFmt, ...);
	IMPORT_C static void BytePacket(const TDesC& aName, const TDesC8& aPacket);
	};

#ifdef _DEBUG
#define D(statement) statement;
#else
#define D(statement)
#endif

#endif // __GDBDEBUG_H__
