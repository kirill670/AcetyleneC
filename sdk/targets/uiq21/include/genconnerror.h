// GENCONNERROR.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Generic Connection Agent external errors and error strings

#ifndef __GENCONNERROR_H__
#define __GENCONNERROR_H__

//
// GenConn database errors
//

const TInt KGenConnErrorBase = -3600;
const TInt KErrGenConnDatabaseDefaultUndefined = KGenConnErrorBase - 6;
const TInt KErrGenConnDatabaseTypeUnknown = KGenConnErrorBase - 7;
const TInt KErrGenConnDatabaseNotFound = KGenConnErrorBase - 8;
const TInt KErrGenConnNoGPRSNetwork = KGenConnErrorBase -9;
const TInt KErrGenConnIncorrectMSClass = KGenConnErrorBase -10;
const TInt KErrGenConnInadequateSignalStrengh = KGenConnErrorBase -11;
const TInt KErrGenConnStateMachineNotAvailable = KGenConnErrorBase -12;

#endif

