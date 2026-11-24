// CFSTokenTypeClient.h
//
// Copyright (c) 2004 Symbian Ltd.  All rights reserved.

#ifndef __CFSTOKENTYPECLIENT_H__
#define __CFSTOKENTYPECLIENT_H__

#include <ct/CCTTokenType.h>

class CFSTokenTypeSession;	//	Forward declaration

//! Filetokens client side implementation of CCTTokenType, provides ListTokens and
//!	OpenToken functionality (though it passes calls straight through to the CFSTokenTypeSession
//!	instance it creates to provide asynchronous access to the server).
//!	Only accessed by ECom.

NONSHARABLE_CLASS(CFSTokenTypeClient) :  public CCTTokenType
{
public:
	/** Creates a client side representation of the CCTTokenType represented by the UID parameter
	*	Called by ECom or directly accessible.  Initiates a session with the filetokens server, and
	*	corresponding token type access server-side
	*	@param aUid The UID of the appropriate token type (filecertstore, filekeystore or certapps)
	*/
	IMPORT_C static CCTTokenType* NewL(TUid aUid);
public:
	virtual ~CFSTokenTypeClient();
public:	//	From MCTTokenType
	virtual void List(RCPointerArray<HBufC>& aTokens, TRequestStatus& aStatus);
	virtual void CancelList();
	virtual void OpenToken(const TDesC& aTokenInfo, MCTToken*& aToken, TRequestStatus& aStatus);
	virtual void OpenToken(TCTTokenHandle aHandle, MCTToken*& aToken, TRequestStatus& aStatus);
	virtual void CancelOpenToken();
private:
	void OpenToken(MCTTokenType* aTokenType);
private:
	CFSTokenTypeClient();
	void ConstructL(TUid aUid);
private:
	CFSTokenTypeSession* iClientSession;
};

//	__CFSTOKENTYPECLIENT_H__
#endif
