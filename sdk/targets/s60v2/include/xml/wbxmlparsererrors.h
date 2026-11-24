// WbxmlParserErrors.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//
// This file contains generic Panic error messages and the Panic function
//

#ifndef __WBXMLPARSERERRORS_H__
#define __WBXMLPARSERERRORS_H__

#include <e32base.h>


// Error constants

enum TWbxmlParserError
/**
Indicates various Panic error conditions within the parser.

@internalTechnology
@interim This is the first drop of this component.
*/
	{
	/**
	Indicates that a leave code other than that expected was received.
	*/
	EWbxmlParserErrorUnexpectedLeaveCode		= 7000,

	/**
	Indicates that a state other than that expected was reached.
	*/
	EWbxmlParserErrorUnexpectedState			= 7001,

	/**
	Indicates that logic other than that expected was reached.
	*/
	EWbxmlParserErrorUnexpectedLogic			= 7002,

	};


void Panic(TWbxmlParserError aError);


#endif // __WBXMLPARSERERRORS_H__
