// MSVAPI.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

//**********************************
// CMsvSession
//**********************************

inline RMsvServerSession& CMsvSession::Session() 
	{
	return iSession;
	};

inline RFs& CMsvSession::FileSession() 
/** Allows a Server-side MTM to access the file session handle created by the Message 
Server. 

This is preferable, as more efficient, to creating another handle.

@return File session handle */
	{
	return iFs;
	}

inline TInt CMsvSession::OperationId()
	{
	return iOperationId++;
	}

inline TInt CMsvSession::StopService(TMsvId aServiceId)
/** Stops any operations that a Server-side MTM for the specified service is running, 
and then unloads the Server-side MTM. 

The current operation and any queued operations are cancelled.

@param aServiceId The ID of the service to stop 
@return KErrNone - success; */
	{
	return iSession.StopService(aServiceId);
	}

inline TBool CMsvSession::ServiceActive(TMsvId aServiceId)
/** Tests whether a Server-side MTM for a particular service is loaded by the Message 
Server.

The Server-side MTM does not have to be executing a command  -  it may be 
waiting for another command.

@param aServiceId The ID of the relevant service 
@return ETrue if the Server-side MTM for the service is loaded, otherwise EFalse */
	{
	return iSession.ServiceActive(aServiceId);
	}

inline TInt CMsvSession::ServiceProgress(TMsvId aServiceId, TDes8& aProgress)
/** Gets the current progress information from the Server-side MTM for the specified 
service.

It is typically used by User Interface MTMs. The format of the progress information 
returned in the aProgress buffer is MTM-specific.

Calling this function results in the Message Server calling CBaseServerMtm::Progress() 
on the relevant Server-side MTM. 

Note that the progress information is independent of which message client 
application started the current operation. 

@param aServiceId The ID of the service from which to get the progress information 

@param aProgress On return, a descriptor holding progress information. It is 
the caller's responsibility to ensure the descriptor is large enough for this 
information. 
@return KErrNone - success; KErrNotFound - The service is not active (the relevant Server-side MTM is not loaded 
by the Message Server); KErrOverflow - The descriptor was too small for the progress information */
	{
	return iSession.ServiceProgress(aServiceId, aProgress);
	}

inline void CMsvSession::CloseMessageServer()
/** Closes down the Message Server.

Normal clients should not use this function, as it will affect other message 
clients.

The function results in the session sending a shutdown session notification 
(TMsvSessionEvent::EMsvCloseSession) to all current sessions. The Message 
Server closes when all sessions have been closed. */
	{
	iSession.CloseMessageServer();
	}

inline void CMsvSession::RemoveEntry(TMsvId aId)
/** Deletes the specified entry from the Message Server. 

The call is guaranteed not to fail. If the entry cannot be deleted immediately, 
it will be deleted later. This call should only be used in preference to the 
normal deleting mechanism when no error reporting is required, typically in 
a destructor.

@param aId The ID of the entry to remove */
	{
	iSession.RemoveEntry(aId);
	}

inline TInt CMsvSession::InstallMtmGroup(const TDesC& aFullName)
/** Installs a new group of MTMs. 

It is used by specialised MTM-installation programs. 

@param aFullName The full path name of the MTM group file 
@return KErrNone - success; KErrAlreadyExists - MTM already installed */
	{
	return iSession.InstallMtmGroup(aFullName);
	}

inline TInt CMsvSession::DeInstallMtmGroup(const TDesC& aFullName)
/** Removes an installed MTM. 

It is used by specialised MTM-deinstallation programs. 

@param aFullName The full path name of the MTM group file 
@return KErrNone - success; KErrInUse - The MTM is currently being used */
	{
	return iSession.DeInstallMtmGroup(aFullName);
	}

inline CMsvEntry* CMsvSession::GetEntryL(TMsvId aId)
/** Accesses the entry with the specified ID.

If a client is unaware of the entries that exist, it can set aId to KMsvRootIndexEntryId 
to obtain the root entry, from where all other entries can be obtained.

The CMsvEntry object must be deleted by the client when it is no longer required. 

@return	A new entry object 		
@param aId  The ID of the entry to access
@leave KErrNotFound The requested entry does not exist
*/
	{
	return CMsvEntry::NewL(*this, aId, TMsvSelectionOrdering());
	}

inline TInt CMsvSession::GetEntry(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry)
/** Gets the index entry for the specified entry ID.

@param aId The ID of the entry to access 
@param aService On return, the ID of the service that owns the entry
@param aEntry On return, the index entry
@return KErrNone if successful, otherwise one of the system-wide error codes */
	{
	return iSession.GetEntry(aId, aService, aEntry);
	}

//**********************************
// CMsvEntry
//**********************************

inline TMsvId CMsvEntry::EntryId() const
/** Gets the ID of the context.

@return Current context's entry ID */
	{
	return iEntryPtr->Id();
	}

inline const TMsvEntry& CMsvEntry::Entry() const
/** Gets the index entry for the context.

@return Current context's index entry */
	{
	return *iEntryPtr;
	}

inline CMsvSession& CMsvEntry::Session()
/** Gets the Message Server session used by this object. This is the same session 
passed by the client in NewL(). 

@return The session used by the object */
	{
	return iMsvSession;
	}

inline const TMsvSelectionOrdering& CMsvEntry::SortType() const
/** Gets the current sort order of children of the entry. The sort order is initially 
set through NewL().

@return Current sort order */
	{
	return iOrdering;
	}

inline TInt CMsvEntry::Count() const
/** Gets the number of children of the context.

@return Count of the child entries for the current context */
	{
	return iSortedChildren->Count();
	}

inline TMsvId CMsvEntry::OwningService() const
/** Gets the ID of the service entry that owns the context. 

Local entries are considered as being members of the local service: 

@return ID of the service entry that the context is under. */
	{
	return iOwningService;
	}


//**********************************
// CMsvOperation
//**********************************

inline TMsvOp CMsvOperation::Id() const
/** Gets the operation ID. 

This ID is unique within a Message Server session. The ID allows the client 
to keep track of different operations. 

@return The ID of the operation */
	{
	return iId;
	}

inline TMsvId CMsvOperation::Service() const
/** Gets the ID of the service that is associated with this operation.

If the operation is not associated with a service, the function returns KMsvLocalServiceIndexEntryId.

@return ID of the service associated with the operation */
	{
	return iService;
	}
