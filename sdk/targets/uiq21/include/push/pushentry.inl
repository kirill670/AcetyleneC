// PushEntry.inl
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// WAP Push Message Inline functions  File for the Utility class

#ifndef __PUSHENTRY_INL__
#define __PUSHENTRY_INL__

#include <msvapi.h>

// *******************************    CPushMsgEntryBase     *******************************


/**
 * Accessor function providing read only access to the TMsvEntry member of the base class.
 * @return Message entry
 */
inline const TMsvEntry& CPushMsgEntryBase::Entry() const
	{
	return iEntry;
	}


/**
 * Returns the value of the Status for the Push Message entry.  Status value is one from 
 * an enumerated set and it is used to set Bits 0-3 of the iMtmData1 member of TMsvEntry.  
 * A bitwise AND is performed with iMtmData1 and a mask with value 0x000F to extract the 
 * Status value.
 * @return Status value (as defined in TPushMsgStatus enumeration)
 */
inline TInt CPushMsgEntryBase::Status() const
	{
	return iEntry.iMtmData1 & KPushMaskOnlyStatus;//bitwise & to get Bits 0-3
	}


// *******************************    CSIPushMsgEntry     *******************************


/**
 * Returns the Id of the SI Push Message.  As a server can send many different versions of the same 
 * SI Push Message, only the latest of which is valid, this allows the UI and WAP Push architecture to 
 * locate any previous instances of the message. .
 * @return Value of the ID of the SI Message
 */
inline const TDesC& CSIPushMsgEntry::Id() const
	{
	return iEntry.iDescription;
	}


/**
 * Returns the Time that the Push Message was created.
 * @return Time of message creation 
 */
inline const TTime& CSIPushMsgEntry::Created() const
	{
	return iEntry.iDate;
	}


/**
 * Sets the Time that the Push Message was created. The value is stored in the iDate field 
 * of the TMsvEntry data member of the class.
 * @param aCreated Time of creation of the SI message
 */
inline void CSIPushMsgEntry::SetCreated(const TTime& aCreated)
	{
	iEntry.iDate = aCreated;
	}


/**
 * Returns the expiry date & time for the Push Message. The value is only set by either the 
 * accessor function SetExpires, or by RetrieveL() on a previously saved message entry.
 * @return Time of message expiration 
 */
inline const TTime& CSIPushMsgEntry:: Expires() const 
	{
	return iExpiryDate;
	}
 

/**
 * Sets the time of that this Push Message expires. The value is stored in the message store when the 
 * rest of the data is saved with StoreL
 * @param aExpires Expiry date & time of the SI message
 */
inline void CSIPushMsgEntry::SetExpires(const TTime& aExpires)
	{
	iExpiryDate=aExpires;
	}


/**
 * Returns the URL of the service to be accessed.  If there is no URL in the message then 
 * a NULL descriptor will be returned.
 * @return URL of the service to access
 */
inline const TDesC& CSIPushMsgEntry::Url() const
	{
	return iEntry.iDetails;
	}








/**
 * Returns the URL of the service to be accessed.  If there is no URL in the message then 
 * a NULL descriptor will be returned.
 * @return URL of the service to access
 */
inline const TDesC& CSLPushMsgEntry::Url() const
	{
	return iEntry.iDetails;
	}




/**
 * Sets the date field of the TMsvEntry to the time that the message was sent. 
 * @param aTime Time that the message was sent
 */
inline void	CSLPushMsgEntry::SetMsgDateTime(const TTime& aTime)
	{
	iEntry.iDate = aTime;
	}


/**
 * Gets the time that message was sent. Returns the iDate field of the TMsvEntry. 
 * @return Time of sending
 */
inline const TTime& CSLPushMsgEntry::MsgDateTime() const 
	{
	return iEntry.iDate;
	}




/**
 * Returns a descriptor with the Content Type of the message. 
 * @return Content Type
 */
inline const TDesC& CMultiPartPushMsgEntry::ContentType() const
	{
	return iEntry.iDetails;
	}

/**
 * Sets the iDate field of the TMsvEntry. 
 * @param aTime Time that the message was sent
 */
inline void	 CMultiPartPushMsgEntry::SetMsgDateTime(const TTime& aTime)
	{
	iEntry.iDate = aTime;
	}

/**
 * Gets the time that the message was sent. Returns the iDate field of the TMsvEntry. 
 * @return Time of sending
 */
inline const TTime& CMultiPartPushMsgEntry::MsgDateTime() const 
	{
	return iEntry.iDate;
	}




/**
 * Returns a descriptor with the Content Type of the message. 
 * @return Content Type
 */
inline const TDesC& CUnknownPushMsgEntry::ContentType() const
	{
	return iEntry.iDetails;
	}

/**
 * Sets the iDate field of the TMsvEntry. 
 * @param aTime Time that the message was sent
 */
inline void	CUnknownPushMsgEntry::SetMsgDateTime(const TTime& aTime)
	{
	iEntry.iDate = aTime;
	}

/**
 * Gets the iDate field of the TMsvEntry. 
 * @return Time of sending
 */
inline const TTime& CUnknownPushMsgEntry::MsgDateTime()  const
	{
	return iEntry.iDate;
	}

#endif