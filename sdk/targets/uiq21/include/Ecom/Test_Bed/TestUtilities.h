//
// TestUtilities.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@internal
	@file TestUtilities.h
	@since 7.0
	Comments : A set of utilities available for testing / debugging /
			developing components.
			Some macros and a stress test class
			CMemoryLeakTest implements a utility class to assist in 
			 stress testing the memory use of a component
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
			
			 Also intended for use in combination with the TestBed 
			 components only.
 */ 

#ifndef  __TESTUTILITIES_H__
#define  __TESTUTILITIES_H__

#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

// __________________________________________________________________________
// Enforce ANSI compliance upon the Microsoft compiler!
#if defined(__VC32__) && _MSC_VER>=1100
#pragma warning(disable : 4127)		// warning C4127 : conditional expression is constant
#define for if(false);else for		// Enforce the definition of a loop variable to local scope
#endif

// __________________________________________________________________________
// A useful macro for TODO messages
#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)

// Use __FILE__LINE__ as a string containing "File.x(line#)" for example:
//     #pragma message( __FILE__LINE__ "Remove this line after testing.")
// The above example will display the file name and line number in the build window
// in such a way as to allow you to double click on it to go to the line in MSDev 6.0.
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "

// __________________________________________________________________________
// 
#if defined _DEBUG
/**
	@internal
	Use the memory test fail on alloc macros, (__UHEAP_SETFAIL, etc.), to
	debug non-memory leaves by placing this just before to
	simulate a leave.
 */
#define __DEBUG_TEST_LEAVE {HBufC* buf=HBufC::NewL(sizeof(TInt)); delete buf;}
/**
	@internal
	Use the memory test fail on alloc macros, (__UHEAP_SETFAIL, etc.), to
	debug non-memory leaves by placing this just before to
	simulate a leave, and return the error code.
	However if called with the error code set already do nothing.
 */
#define __DEBUG_CAPTUREDTEST_LEAVE(errorCode)	{ \
												if(errorCode == KErrNone) \
													{ \
													HBufC* buf = NULL; \
													TRAP(errorCode, (buf=HBufC::NewL(sizeof(TInt)))); \
													delete buf; \
													} \
												}
#else
#define __DEBUG_TEST_LEAVE
#define __DEBUG_CAPTUREDTEST_LEAVE(errorCode)
#endif


#endif __TESTUTILITIES_H__
