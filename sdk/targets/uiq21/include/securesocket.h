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
const TInt KMaxProtocolName = 32;

class TSecSocketProtocol
	{
public:
	TBuf<KMaxProtocolName> iName;
	RLibrary iLibrary;
	static inline TInt Offset()
		{return _FOFF(TSecSocketProtocol,iSlink);}
	virtual ~TSecSocketProtocol(){iLibrary.Close();}
private:
    TSglQueLink   iSlink;
	};


class TSecureSocketGlobals
	{
public:
	inline TSecureSocketGlobals():
			iSecureSocketProtocols(TSecSocketProtocol::Offset()),
			iSecureSocketProtocolsIter(iSecureSocketProtocols){};	
	TSglQue<TSecSocketProtocol> iSecureSocketProtocols;
	TSglQueIter<TSecSocketProtocol> iSecureSocketProtocolsIter;
	TInt iUseCount;
	};
//Definition for the entry point function exported by secureSocket modules
typedef TInt (*TSecSockDllLibraryFunction)( RSocket& aSocket, const TDesC& aProtocol );

/**
 * Factory class for creating secure sockets.
 *
 * @since 6.2
 * @version 0.01
 * @date	28/02/2001
 * Create and reference Secure Sockets
 */
class CSecureSocketLibraryLoader : public CBase
	{
public:

	/** 
	 * Open the protocol library.
	 * Attempts to load the secure socket implementation DLL for the requested protocol type.
	 * @param aProtocol A reference to a descriptor containing the protocol name, ie tls1.0, ssl3.0.
	 * Case is ignored.
	 * @param anEntryPoint entry point into the secureSocket plug-in
	 * @retval TInt KErrNone if successful, otherwise another of the system-wide error codes.
	 */
	static  TInt OpenL(const TDesC& aProtocolName,TSecSockDllLibraryFunction& anEntryPoint);
	/** 
	 * Open the Commdb and locate the dll name for a protocol.
	 * @param aProtocol A reference to a descriptor containing the protocol name, ie tls1.0, ssl3.0.
	 * Case is ignored.
	 * @param aLibraryName name of the library will be returned here
	 * @exception This function will leave if the protocol was not found or in OOM conditions
	 */
	static void FindItemInDbL(const TDesC& aProtocolName, TDes& aLibraryName);
	IMPORT_C static	void Unload();

	};
/**
 * Secure sockets class.
 *
 * New secure sockets can be created through the static CSecureSocket::NewL method.
 * @public
 * @since 6.2
 * @version 0.01
 * @date	28/02/2001
 */
class CSecureSocket : public CBase, public MSecureSocket 
	{
public:

	/**
	  * Create and return a pointer to a new secure socket.
	  * A reference to an already open and connected socket should be passed in,
	  * along with a descriptor that contains the 
	  * @param aSocket A reference to a RSocket class.
	  * @param aProtocol A constant descriptor containging the protocol name that 
	  * @retval CSecureSocket* A pointer to the newly created secure socket, or NULL if the
	  */
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

	TSecSockDllLibraryFunction iLibEntryPoint;
	MSecureSocket* iSecureImplementation;
	};


#endif // __SECURESOCKET_H__
