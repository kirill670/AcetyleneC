// UNIFIEDKEYSTORE.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __UNIFIEDKEYSTORE_H__
#define __UNIFIEDKEYSTORE_H__

#include <f32file.h>
#include <e32base.h>

#include <mctkeystore.h>

class CUnifiedKeyStore : public CActive, public MKeyStore
	{
public:
	IMPORT_C static CUnifiedKeyStore* NewL(RFs& aFs);
	IMPORT_C static CUnifiedKeyStore* NewLC(RFs& aFs);
	IMPORT_C ~CUnifiedKeyStore();
	IMPORT_C void Initialize(TRequestStatus& aStatus);
	IMPORT_C void CancelInitialize();

public:	// from MKeyStore
	IMPORT_C virtual void List(RMPointerArray<CCTKeyInfo>& aKeys, 
		const TCTKeyAttributeFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C virtual void CancelList();
	IMPORT_C virtual void GetKeyInfo(TCTTokenObjectHandle aHandle, CCTKeyInfo*& aInfo,
							TRequestStatus& aStatus);
	IMPORT_C virtual void CancelGetKeyInfo();

public:
	IMPORT_C TInt KeyStoreCount() const;
	IMPORT_C MCTKeyStore& KeyStore(TInt aIndex);

private:
	CUnifiedKeyStore(RFs& aFs);
	void ConstructL();
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();

	void InitializeL(); // Helper for Initialize

private:
	enum TState
		{
		EInitializeGetTokenList,
		EInitializeGetToken,
		EInitializeGetReadableInterface,
		EInitializeGetReadableInterfaceFinished,
		EInitializeFinished,

		EList
		};

private:
	RFs& iFs;
	RPointerArray<MCTKeyStore> iKeyStores;
	
	RCPointerArray<CCTTokenTypeInfo> iTokenTypes;
	TInt iIndexTokenTypes;

	MCTTokenType* iTokenType;
	RCPointerArray<HBufC> iTokens;
	TInt iIndexTokens;
	
	MCTToken* iToken;
	MCTTokenInterface* iTokenInterface;

	RMPointerArray<CCTKeyInfo>* iKeyInfos;
	const TCTKeyAttributeFilter* iFilter;
	TInt iIndex;	// TODO : we probably can reuse one of the indexes defined previously
	
	TState iState;

	TRequestStatus* iOriginalRequestStatus;

	MCTKeyStore* iKeyStoreInterface;

	TInt iLastGetKey;
	};

#endif
