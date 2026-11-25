// TcpListener.h
//
// Copyright (c) 2001 Intuwave Ltd.  All rights reserved.
//

#ifndef _TCPLISTENER_CLIENT_H_
#define _TCPLISTENER_CLIENT_H_

struct TListenerDetails
{
	TFileName	iProcessorName;
	TUint16		iPort;
	TInt		iMaxConcurrentConnections;
	TInt		iCurrentConnections;
	TInt		iTotalConnections;
	TInt		iFlags;
};

class RTcpListener : public RSessionBase
	{
public:
	IMPORT_C RTcpListener();
	IMPORT_C ~RTcpListener();

	IMPORT_C void ConnectL(TBool aStartIfNeeded);
	IMPORT_C TInt CountListenersL();
	IMPORT_C void GetListenerDetailsL(TInt index, TListenerDetails *aDetails);
	IMPORT_C void GetListenerDetailsFromPortL(TUint16 aPort, TListenerDetails *aDetails);
	IMPORT_C void AddListenerDetailsL(const TListenerDetails &aDetails);
	IMPORT_C void ModifyListenerDetailsL(const TListenerDetails &aDetails);
	};

const TInt KTcpListenerMajorVersion = 1;
const TInt KTcpListenerMinorVersion = 0;

#endif //_TCPLISTENER_CLIENT_H_
