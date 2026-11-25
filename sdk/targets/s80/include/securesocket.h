//
// SECURESOCKET.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __SECURESOCKET_H__
#define __SECURESOCKET_H__

#include <e32base.h>
#include <e32cons.h>
#include <c32comm.h>
#include <es_sock.h>
#include <in_sock.h>
#include <ssl.h>

#include <sslerr.h>
#include <x509cert.h>

#include <securesocketinterface.h>
//Secure Socket specific panic
_LIT(KSecureSocketPanic,"SecureSocket Panic");

/** 
 * Maximum length of the protocol name. 
 * 
 * @internalComponent
 */
const TInt KMaxProtocolName = 32;

class TSecSocketProtocol
/** 
 * The secure socket protocol class. 
 * 
 * @internalComponent
 *
 * @since v7.0 
 */
	{
public:
	/** Protocol name. */
	TBuf<KMaxProtocolName> iName;
	/** Handle to the DLL. */
	RLibrary iLibrary;
	static inline TInt Offset()
	/** 
	* Gets the offset to the iSlink member.
	* 
	* @return The offset to the iSlink member. */
		{return _FOFF(TSecSocketProtocol,iSlink);}
	// Moved to imeplementation to cpp file
	virtual ~TSecSocketProtocol();
private:
    TSglQueLink   iSlink;
	};


class TSecureSocketGlobals
/** 
 * Class to store the Secure Sockets Globals. 
 * 
 * @internalComponent
 * 
 * @since v7.0 
 */
	{
public:
	inline TSecureSocketGlobals():
			iSecureSocketProtocols(TSecSocketProtocol::Offset()),
	/** Constructor. */
			iSecureSocketProtocolsIter(iSecureSocketProtocols){};	
	/** List of supported protocols. */
	TSglQue<TSecSocketProtocol> iSecureSocketProtocols;
	/** A templated class that provides for iterating through the list of supported 
	* protocols. */
	TSglQueIter<TSecSocketProtocol> iSecureSocketProtocolsIter;
	/** Use counter. */
	TInt iUseCount;
	};

/** 
 * Definition for the entry point function exported by Secure Socket modules. 
 * 
 * @internalComponent
 */
typedef TInt (*TSecSockDllLibraryFunction)( RSocket& aSocket, const TDesC& aProtocol );

/** 
 * Definition for the entry point for the cleanup function exported by secureSocket modules
 * 
 * @internalComponent
 */
typedef void (*TSecSockDllUnloadFunction)( TAny* );

//Added new clearing function header
IMPORT_C void UnloadDll(TAny* aPtr);  

class CSecureSocketLibraryLoader : public CBase
/** 
 * Factory class for creating secure sockets. 
 * 
 * @internalAll
 *
 * @since v6.2 */
 // Create and reference Secure Sockets
	{
public:
	static  TInt OpenL(const TDesC& aProtocolName,TSecSockDllLibraryFunction& anEntryPoint);
	static void FindItemInDbL(const TDesC& aProtocolName, TDes& aLibraryName);
	IMPORT_C static	void Unload();

	};
class CSecureSocket : public CBase, public MSecureSocket 
/** 
 * Secure sockets class. 
 * 
 * @publishedAll
 * @released
 *
 * @since v6.2 */
 // New secure sockets can be created through the static CSecureSocket::NewL method.
 // @public
	{
public:
	IMPORT_C static CSecureSocket* NewL(RSocket& aSocket,const TDesC& aProtocol);

	/** Standard destructor. */
	~CSecureSocket();
 
	//////////////////////////////////
	// Methods from MSecureSocket
	TInt AvailableCipherSuites( TDes8& aCiphers );
	void CancelAll();
	void CancelHandshake();	
	void CancelRecv();
	void CancelSend();
	const CX509Certificate* ClientCert();
	TClientCertMode ClientCertMode();
	TDialogMode DialogMode();
	void Close();
	TInt CurrentCipherSuite( TDes8& aCipherSuite );
	void FlushSessionCache();
	TInt GetOpt(TUint aOptionName, TUint aOptionLevel, TDes8& aOption);
    TInt GetOpt(TUint aOptionName, TUint aOptionLevel, TInt& aOption);
	TInt Protocol(TDes& aProtocol);
	void Recv (TDes8& aDesc, TRequestStatus& aStatus );
	void RecvOneOrMore( TDes8& aDesc, TRequestStatus& aStatus, TSockXfrLength& aLen );
	void RenegotiateHandshake(TRequestStatus& aStatus );
	void Send( const TDesC8& aDesc, TRequestStatus& aStatus, TSockXfrLength& aLen );
	void Send( const TDesC8& aDesc, TRequestStatus& aStatus );
	const CX509Certificate* ServerCert();
	TInt SetAvailableCipherSuites(const TDesC8& aCiphers);
	TInt SetClientCert(const CX509Certificate& aCert);
	TInt SetClientCertMode(const TClientCertMode aClientCertMode);
	TInt SetDialogMode(const TDialogMode aDialogMode);
	TInt SetProtocol(const TDesC& aProtocol);
	TInt SetOpt(TUint aOptionName, TUint aOptionLevel, const TDesC8& aOption=TPtrC8(NULL,0));
	TInt SetOpt(TUint aOptionName, TUint aOptionLevel, TInt aOption);
	TInt SetServerCert(const CX509Certificate& aCert);	
	void StartClientHandshake(TRequestStatus& aStatus);
	void StartServerHandshake(TRequestStatus& aStatus);	

private:
	void ConstructL(RSocket& aSocket,const TDesC& aProtocol);

	enum {ESecureSocketStateOpen, ESecureSocketStateClosed};

	TUint iSecureSocketState;

	TSecSockDllLibraryFunction iLibEntryPoint;
	MSecureSocket* iSecureImplementation;
	};

#endif // __SECURESOCKET_H__
