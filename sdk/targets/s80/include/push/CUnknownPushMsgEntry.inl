// CUnknownPushMsgEntry.inl
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//


#include <msvapi.h>


/** 
Gets the Content Type of the message.

@return 
The Content Type of the message. 
*/
inline const TDesC& CUnknownPushMsgEntry::ContentType() const
	{
	if (iContentType)
		return *iContentType;
	else
		return KNullDesC;
	}


/**
Sets the time that the message was sent. 

@param aTime
The time the message was sent.
*/
inline void	CUnknownPushMsgEntry::SetTimeSent(const TTime& aTime)
	{
	iTimeSent=aTime;
	}


/**
Gets the time that the message was sent. 

@return 
The time the message was sent
*/
inline const TTime& CUnknownPushMsgEntry::TimeSent()  const
	{
	return iTimeSent;
	}
