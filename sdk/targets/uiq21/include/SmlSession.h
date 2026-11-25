// SmlSession.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

#ifndef __SMLSESSION_H__
#define __SMLSESSION_H__


#ifndef __E32BASE_H__
#include <e32base.h>
#endif

// Transport specific error codes.
// KErrTelephonyError    - Problem in communication layer
// KErrTransportEncode   - Problem in encoding the data
// KErrTransportDecode   - Problem in decoding the data
// KErrTransportRequest  - Problem with the request
// KErrTransportHeader   - Problem with the headers provided
// KErrTransportSvrNoUri - The URI does not exist
// KErrTransportSvrError - Server problem

namespace SmlSession
{
const TInt KErrTransportErrorBase						= -8321;
const TInt KErrTelephonyError							= KErrTransportErrorBase;
const TInt KErrTransportEncode							= KErrTransportErrorBase - 1;
const TInt KErrTransportDecode							= KErrTransportErrorBase - 2;
const TInt KErrTransportRequest							= KErrTransportErrorBase - 3;
const TInt KErrTransportHeader							= KErrTransportErrorBase - 4;
const TInt KErrTransportSvrNoUri						= KErrTransportErrorBase - 5;
const TInt KErrTransportSvrError						= KErrTransportErrorBase - 6;
const TInt KErrTransportAuthenticationFailure			= KErrTransportErrorBase - 7;
const TInt KErrTransportDisconnected					= KErrTransportErrorBase - 8; // Used when the transport has disconnected the session for some reason
}


/**

The CSmlSession  class Header definition for CSmlSession

*/
class CSmlSession : public CActive
//
// Session abstract class
//
	{
public:
	// Session Callback interface
	class MSmlSessionCallBack
		{
	public:
		virtual void OnConnect(void)       = 0;
		virtual void OnDisconnect(void)       = 0;
		virtual void OnSendData(void)      = 0;
		virtual void OnReceiveData(void)   = 0;
		virtual void OnError(TInt aError)  = 0;
		virtual void OnServerConnect(void) = 0;
		virtual void OnMaxPacketSize(TInt aSize) = 0;
		};

public:

	enum TMaxPacketSizeKnown
		{
		EMaxPacketSizeYes,
		EMaxPacketSizeNo,
		EMaxPacketSizeUnknown
		};

	static CSmlSession* NewL(const TUid& aImplementationUid);

	virtual ~CSmlSession();

	// Used to Initalise the transport
	virtual void InitialiseL()								 = 0;

	// The engine will now set the fields before calling ConnectL
	virtual void ConnectL(const TDesC& aUri)                 = 0;

	virtual void SetUriL(const TDesC& aUri)					 = 0;

	virtual void DisconnectL()								 = 0;

	virtual void SetFieldL(const TDesC& aField,
						   const TDesC& aValue)              = 0;

	virtual void ClearFields(void)                           = 0;

	virtual void SendDataL(const TDesC8& aData )			 = 0;

	virtual void ReceiveData(CBufBase*& aData)               = 0;

	virtual void SetCallBack(MSmlSessionCallBack* aCallback) = 0;

	virtual void Listen(void)                                = 0;

	virtual void CancelSession(void)                         = 0;

	virtual TVersion Version() const						 = 0;

	// Set the default max packet size. The transport can request a smaller packet by calling OnMaxPacket()
	virtual void SetMaxPacketSize(TInt aMaxPacketSize) = 0;

	virtual TMaxPacketSizeKnown IsMaxPacketSize()			 = 0;

protected: 
	//CActive functions
	
	virtual void RunL();

	virtual void DoCancel();

	CSmlSession();

private:
	TUid	  iDtorKey; 
	};

#include <SmlSession.inl>

#endif
