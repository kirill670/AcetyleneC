// CERTIFICATEAPPS.H
//
// Copyright (c) 1998-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CERTIFICATEAPPS_H__
#define __CERTIFICATEAPPS_H__

#include <e32base.h>
#include <f32file.h>
#include <s32file.h>

/**
 * <P>This contains the information about a client. A client is an application that
 * trust or doesn't trust CA certificates in stores.</P>
 * <P>The information about a client is made of a name and a uid.</P>
 */
class TCertificateAppInfo
	{
public:
	IMPORT_C TCertificateAppInfo(const TUid& aUid, const TName& aName);
	TCertificateAppInfo& operator = (const TCertificateAppInfo& aClient);
	TCertificateAppInfo();
	IMPORT_C const TUid& Id() const;
	IMPORT_C const TName& Name() const;
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);

private:
	TUid iUid;                    
	TName iName;
	};

/**
 * This class is used a store which stores the clients.
 * It provides an interface to add and retrieve clients.
 */
class CCertificateAppInfoManager : public CBase
	{
	public:
		IMPORT_C static CCertificateAppInfoManager* NewLC(RFs& aFs, TBool aOpenedForWrite);
		IMPORT_C static CCertificateAppInfoManager* NewL(RFs& aFs, TBool aOpenedForWrite);
		IMPORT_C virtual ~CCertificateAppInfoManager();

	private:
		CCertificateAppInfoManager(RFs& aFs);
		void ConstructL(TBool aOpenedForWrite);

	public:
		/**
		 * Adds a client to the store.
		 */
		IMPORT_C void AddL(const TCertificateAppInfo& aClient);
		IMPORT_C void RemoveL(const TUid& aUid);
		IMPORT_C const TCertificateAppInfo& ApplicationL(const TUid& aUid, TInt& aIndex) const;
		IMPORT_C const RArray<TCertificateAppInfo>& Applications() const;

	private:
		void OpenCopyCreateStoreL(TBool aOpenedForWrite);
		void CreateStoreL();
		void OpenStoreL(TBool aOpenedForWrite);
		void LoadIdL();
		static void RevertStore(TAny* aStore);
		static void DeleteStoreAndFile(TAny* aThis);
		void ReplaceAndCommitL(TInt aExcludedIndex);
		void RestoreClientsL();
		void CopyStoreFromRomL();

	private:
		RFs& iFs;
		// The file for the store
		RFile iFile;
		// The store where the client are stored
		CPermanentFileStore* iStore;
		TStreamId iId;
		// This is a cache of the contents of the store
		RArray<TCertificateAppInfo> iClients;
	};

#endif