//
//Copyright (c) 2003 Symbian Software Ltd.  All rights reserved.
//

/**
@file 
Generic Connection Agent external errors and error strings

@internalComponent

*/

#ifndef __GENCONNERROR_H__
#define __GENCONNERROR_H__


const TInt KGenConnErrorBase = -3600;	///< GenConn database error
const TInt KErrGenConnDatabaseDefaultUndefined = KGenConnErrorBase - 6; ///< GenConn database error: database default undefined
const TInt KErrGenConnDatabaseTypeUnknown = KGenConnErrorBase - 7; ///< GenConn database error: database type unknown
const TInt KErrGenConnDatabaseNotFound = KGenConnErrorBase - 8; ///< GenConn database error: database not found
const TInt KErrGenConnNoGPRSNetwork = KGenConnErrorBase -9; ///< GenConn database error: no GPRS network
const TInt KErrGenConnIncorrectMSClass = KGenConnErrorBase -10; ///< GenConn database error: incorrect MS class

#endif

