// CMultiPartPushMsgEntry.inl
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#include <msvapi.h>


/** 
Gets the Content Type of the message.

If Content Type does not exist, a null descriptor is returned.

@return 
The Content Type of the message.
*/
inline const TDesC& CMultiPartPushMsgEntry::ContentType() const
	{
	if (iContentType)
		return *iContentType;
	else
		return KNullDesC;
	}


/**
Sets the time that the message was sent.

@param aTime
The time that the message was sent.
*/
inline void	 CMultiPartPushMsgEntry::SetTimeSent(const TTime& aTime)
	{
	iTimeSent=aTime;
	}


/**
Gets the time that the message was sent.

@return 
The time that the message was sent
*/
inline const TTime& CMultiPartPushMsgEntry::TimeSent() const 
	{
	return iTimeSent;
	}

