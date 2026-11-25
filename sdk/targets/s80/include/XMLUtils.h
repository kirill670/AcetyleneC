/*
* ==============================================================================
*  Name        : XMLUtils.h
*  Part of     : XMLInterface.dll
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Contains XML datatype definitions
*  Version     : ?Version
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef __XMLUTILS_H
#define __XMLUTILS_H


// Error Codes
const TInt KErrDictionaryInitFailed=(-90);
const TInt KErrParseFailed=(-91);
enum TXMLErrorCodeSeverity
	{
		EXMLFatal,
		EXMLIndeterminate,
		EXMLWorkable,
		EXMLNone
	};

// Features
enum TXMLFeature
	{
		EXMLValidation,
		EXMLBinary
	};


#endif      // __XMLUTILS_H   
            
// End of File
