// TextInputServerParameters.h
//
// Copyright (c) 1997-2001 Symbian Ltd. All rights reserved.
//

#ifndef __TEXTINPUTSERVERPARAMETERS_H__
#define __TEXTINPUTSERVERPARAMETERS_H__

#if !defined(__E32Base_H__)
#include <e32base.h>
#endif

// opcodes used between the Server and the Handanim.dll. They have to be implemented by the Handanim.dll
enum TTextInputServerHwrOpCodes
	{
	EHwOpActivate,
	EHwOpDeactivate,
	EHwFirstAvailableOp = 100
	};

#endif // __TEXTINPUTSERVERPARAMETERS_H__
