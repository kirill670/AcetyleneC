// WTLSKEYS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined (__WTLSKEYS_H__)
#define __WTLSKEYS_H__

#include <e32base.h>
#include <e32std.h>
#include <cryptalg.h>

//RSA public key
class CWTLSRSAPublicKey : public CRSAPublicKey
	{
public:
	IMPORT_C static CWTLSRSAPublicKey* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSRSAPublicKey* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSRSAPublicKey* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSRSAPublicKey* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

#endif
