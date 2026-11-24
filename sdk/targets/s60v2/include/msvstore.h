// MSVSTORE.H
//
// Copyright (c) Symbian Sofwtare Ltd 1998-2004.  All rights reserved.
//

#if !defined(__MSVSTORE_H__)
#define __MSVSTORE_H__

#include <e32base.h>
#include <s32file.h>
#include "msvstd.h"

class CMsvCachedStore;
class CMsvBodyText;

//**********************************
// MMsvStoreObserver
//**********************************
//
// 
//

class MMsvStoreObserver
/** Observer interface to get events relating to a message store.

This is used in the derivation of CMsvServerEntry and CMsvEntry.

@publishedAll
@released
*/
	{
public:
/**
Defines message store event types.

@publishedAll
@released
*/
	enum TMsvStoreEvent {	/** A read-only message store was closed. */
							EMsvReadStoreClosed,	// read only CMsvStore closed
							/** An editable message store was closed. */
							EMsvEditStoreClosed		// edit only CMsvStore closed
							};	
public:
	/** Receives a message store event.

	@param aEvent Event type
	@param aId ID of the message to which the event relates
	*/
	virtual void HandleStoreEvent(TMsvStoreEvent aEvent, TMsvId aId)=0;
	};


//**********************************
// CMsvStore
//**********************************
//
// The entry structure that the client uses
//

/*
Uid which are not needed to be known outside CMsvStore
@internalComponent
@deprecated 
*/
const TUid KMsvEntryRichTextBody={0x10000F70};

#ifdef __MESSAGING_API_V2__
class MMsvAttachmentManager;
class MMsvAttachmentManagerSync;
class CMsvAttachmentManager;
class MMsvStoreManager;
#endif // ____MESSAGING_API_V2__

class CMsvStore : public CBase
/** Provides an interface over the message store that is associated with a message 
entry. It is similar to the dictionary store in supporting the concept of 
streams referenced by UID. 

This class is intended for use by MTM implementations. Message client applications 
access the store through the higher-level functions provided by Client-side 
and User Interface MTMs.

A CMsvStore object is created by a CMsvEntry object and passed to a client 
process. The client process then becomes responsible for deleting the CMsvStore 
object. The store can be opened in two modes, read or edit, and only one CMsvStore 
object can have edit access to a store. 

CMsvStore provides functions for general manipulation of the store, and for 
accessing the standard body text stream. RMsvReadStream and RMsvWriteStream 
must be used to access other streams. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C ~CMsvStore();
	//
	IMPORT_C void StoreBodyTextL(const CRichText& aRichTextBody);
	IMPORT_C void RestoreBodyTextL(CRichText& aRichTextBody);
	IMPORT_C void DeleteBodyTextL();
	IMPORT_C TBool HasBodyTextL() const;
	//
	IMPORT_C void DeleteL(); // deletes the message store
	IMPORT_C TInt SizeL(); // the size of the store
	//
	// The following give the Dictionary store interface
	IMPORT_C TBool IsNullL() const;
	IMPORT_C TBool IsPresentL(TUid aUid) const;
	IMPORT_C void Remove(TUid aUid);
	IMPORT_C void RemoveL(TUid aUid);
	IMPORT_C void Revert();
	IMPORT_C void RevertL();
	IMPORT_C TInt Commit(); 
	IMPORT_C void CommitL();
	
#ifdef __MESSAGING_API_V2__
	// Attachment Management
	IMPORT_C MMsvAttachmentManager& AttachmentManagerL();
	IMPORT_C MMsvAttachmentManagerSync& AttachmentManagerExtensionsL();

#endif // ____MESSAGING_API_V2__

protected:

#ifdef __MESSAGING_API_V2__
	IMPORT_C CMsvStore(MMsvStoreObserver& aObserver, RFs& aFs, TMsvId aId, MMsvStoreManager& aStoreManager);
	IMPORT_C static CMsvStore* OpenForReadL(MMsvStoreObserver& aObserver, RFs& aFs, MMsvStoreManager& aStoreManager, TMsvId aId);
	IMPORT_C static CMsvStore* OpenForWriteL(MMsvStoreObserver& aObserver, RFs& aFs, MMsvStoreManager& aStoreManager, TMsvId aId);
#else // __MESSAGING_API_V2__
	IMPORT_C CMsvStore(MMsvStoreObserver& aObserver, RFs& aFs, TMsvId aId);
	IMPORT_C static CMsvStore* OpenForReadL(MMsvStoreObserver& aObserver, RFs& aFs, const TDesC& aFileName, TMsvId aId);
	IMPORT_C static CMsvStore* OpenForWriteL(MMsvStoreObserver& aObserver, RFs& aFs, const TDesC& aFileName, TMsvId aId);
#endif // ____MESSAGING_API_V2__

private:
	
	
#ifdef __MESSAGING_API_V2__
	void ConstructL(TBool aReadOnly);
#else // ____MESSAGING_API_V2__
	void ConstructL(const TDesC& aFileName);
#endif // ____MESSAGING_API_V2__
	
	void Lock();
	inline const CMsvCachedStore& Store() const;
	inline CMsvCachedStore& Store();
	//
private:
	enum {EMsvStoreUnlocked, EMsvStoreLocked} iLockStatus;
	RFs& iFs;
	MMsvStoreObserver& iObserver;
	
#ifndef __MESSAGING_API_V2__
	HBufC* iFileName;
#endif // __MESSAGING_API_V2__

	const TMsvId iId;
	CMsvCachedStore* iStore;
	TBool iConstructed;
	CMsvBodyText* iBodyText;
	
#ifdef __MESSAGING_API_V2__
	MMsvStoreManager& iStoreManager;
	CMsvAttachmentManager* iAttachmentManager;
#endif // ____MESSAGING_API_V2__

friend class CMsvEntry;
friend class CMsvServerEntry;
friend class RMsvReadStream;
friend class RMsvWriteStream;
	};


class RMsvReadStream : public RReadStream
/** Accesses the streams in a message store with read access. 

Before it is used, 
a CMsvStore must have been opened on the message store with read or read/write 
access.

This class is intended for use by MTM implementations to store MTM-specific 
information. Message client applications access the store through the higher-level 
functions provided by Client-side and User Interface MTMs.

Most of its functionality is provided by the base class RReadStream. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C void OpenL(const CMsvStore& aMsvStore, TUid aUid);
	IMPORT_C void OpenLC(const CMsvStore& aMsvStore,TUid aUid);
	void OpenLC(CMsvCachedStore& aStore,TUid aUid);
	};


class RMsvWriteStream : public RWriteStream
/** Accesses the streams in a message store with write access, or creates new streams. 
Before it is used, a CMsvStore must have been opened on the message store 
with write access.

This class is intended for use by MTM implementations to store MTM-specific 
information. Message client applications access the store through the higher-level 
functions provided by Client-side and User Interface MTMs.

Most of its functionality is provided by the base class RWriteStream. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C void AssignLC(CMsvStore &aMsvStore, TUid aUid);
	IMPORT_C void AssignL(CMsvStore &aMsvStore, TUid aUid);
	void AssignLC(CMsvCachedStore &aStore, TUid aUid);
	};



#endif
