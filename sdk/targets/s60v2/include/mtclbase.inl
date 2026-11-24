// MTCLBASE.INL
//
// Copyright (c) Symbian Softwaer Ltd 1998-2004.  All rights reserved.
//

#if defined(_DEBUG)
_LIT(KMtclPanicString, "MSGS");
#endif

inline TUid CBaseMtm::Type() const
/** Gets the Type UID of the message type associated with the Client-side MTM.

@return UID of the message type associated with the MTM */
	{
	return iRegisteredMtmDll.MtmTypeUid();
	}

inline CRichText& CBaseMtm::Body()
/** Gets the body text of the context, that must be a message. For non-message 
contexts, an empty CRichText is returned. 

@return Body text of the context 
@see StoreBodyL()
@see RestoreBodyL() */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275)); 
	return *iRichTextBody;
	}

inline const CRichText& CBaseMtm::Body() const
/** Gets the read-only body text of the context, that must be a message. For non-message 
contexts, an empty CRichText is returned. 

@return Read-only body text of the context 
@see StoreBodyL()
@see RestoreBodyL() */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275));
	return *iRichTextBody;
	}

inline CMsvEntry& CBaseMtm::Entry() const
/** Gets a CMsvEntry for the current context. The message client application can 
then use this to manipulate the entry.

Implementers should note that this function returns the value of the protected 
data member iMsvEntry.

@return CMsvEntry for the current context */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275));
	return *iMsvEntry;
	};

#ifndef __MESSAGING_API_V2__
inline const CDesCArray& CBaseMtm::AddresseeList() const
/** Gets the list of intended recipients for the current context, which must be 
a message. 

In the case of protocols that allow different classes of recipient (such as 
To, Cc and Bcc), the list returned is whatever the protocol defines as the 
default recipient list. 

Requirements:

The default implementation simply returns the value of the protected data 
member iAddresseeList. As a consequence, Client-side MTM implementations should 
update this member whenever the address list is modified.

@return Array of recipients */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275));
	return *iAddresseeList;
	}
#endif // __MESSAGING_API_V2__

inline TBool CBaseMtm::HasContext() const
/** Tests if an MTM context has been set.

A Client-side MTM has no context until one is set through SwitchCurrentEntryL() 
or SetCurrentEntryL() . 

@return ETrue: context has been set EFalse: context has not been set */
	{
	return (iMsvEntry!=NULL);
	}

inline CMsvSession& CBaseMtm::Session()
/** Gets a reference to the session object passed by the creator of the Client-side 
MTM.

@return Session object used by the Client-side MTM */
	{
	return iSession;
	}
