// RedirCli.H
//
// Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.
//

// EPOC Server for redirecting stdin/stdout/stderr to a stream-like object 
// (console, file or serial port)
//
#ifndef _REDIRCLI_H_
#define _REDIRCLI_H_

#include <e32std.h>
#include <e32base.h>
#include <redirstr.h>

#ifndef __HIDE_IPC_V1__ 
/** Messages suported by server.*/
enum TRedirStream 
	{
	ERedirRead,
	ERedirWrite,
	ERedirFlush
	};

/**
reasons for server panic
@internalComponent
*/
enum TRedirServPanic
	{
	EBadRequest,
	EBadDescriptor,
	EMainSchedulerError,
	ESvrCreateServer,
	ESvrStartServer,
	ECreateTrapCleanup,
	ENotImplementedYet,
	};

/**
server name
@internalComponent
*/
_LIT(KRedirServerName,"RedirServer");

/**
A version must be specified when creating a session with the server
@internalComponent
*/
const TUint KRedirServMajorVersionNumber=1;
const TUint KRedirServMinorVersionNumber=0;
const TUint KRedirServBuildVersionNumber=0;

//******************************************************************************************
// RRedirSession  
//***********************************************
/**
client side session for Redirection server
@internalComponent
*/
class RRedirSession : public RSessionBase
	{
public:
	IMPORT_C TInt Connect(); // connects to server
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes, TInt aLength);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes, TInt aLength);
	IMPORT_C void Flush(TRequestStatus& aStatus);
private:
//TODO: do we really need this function??
	TInt CheckEOF(TRequestStatus& aStatus);
	};

class CStreamFactoryBase;
class CStreamBase;

//************************************
// CRedirServer 
//***********************************
/**
This class represents the Redir server itself.
It is created through the factory function
two class declarations to break cyclic dependencies between classes  
@internalComponent
*/
class CRedirServer : public CServer
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	IMPORT_C static CRedirServer* NewL(CStreamFactoryBase* aStreamFactory);
	IMPORT_C void SetStreamFactory(CStreamFactoryBase* aStreamFactory);
	virtual CSharableSession *NewSessionL(const TVersion &aVersion) const;
protected:
	CRedirServer(CStreamFactoryBase* aStreamFactory);
private:
	CStreamFactoryBase* iStreamFactory;
	};
#else
// needed to replace above exports so def file does not need reordering.
IMPORT_C void DummyReserved1();
IMPORT_C void DummyReserved2();
IMPORT_C void DummyReserved3();
IMPORT_C void DummyReserved4();
IMPORT_C void DummyReserved5();
IMPORT_C void DummyReserved6();
IMPORT_C void DummyReserved7();
IMPORT_C void DummyReserved8();

#endif //__HIDE_IPC_V1__ 


class CStreamFactoryBase2;
class CStreamBase2;

/** 
Redirection server class.
 
This class represents the Redir server itself. It is created through the 
factory function NewL. It is not intended for user derivation.

@internalAll
*/
class CRedirServer2 : public CServer2
	{
private:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	IMPORT_C static CRedirServer2* NewL(CStreamFactoryBase2* aStreamFactory);
	IMPORT_C void SetStreamFactory(CStreamFactoryBase2* aStreamFactory);
	virtual ~CRedirServer2();
private:
	CRedirServer2(CStreamFactoryBase2* aStreamFactory);
	virtual	CSession2* NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const;
private:
	CStreamFactoryBase2* iStreamFactory;
	};

/**
Client side session for Redirection server

@internalAll
*/
class RRedirSession2 : public RSessionBase
	{
public:
	IMPORT_C TInt Connect();
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes, TInt aLength);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes, TInt aLength);
	IMPORT_C void Flush(TRequestStatus& aStatus);
private:
//TODO: do we really need this function??
	TInt CheckEOF(TRequestStatus& aStatus);
	};


#endif
