// CMultiPartPushMsgEntry.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __CMULTIPARTPUSHMSGENTRY_H__
#define __CMULTIPARTPUSHMSGENTRY_H__

#include <pushentry.h>


/** 
Handles storage of multipart WAP Push Messages in the message server.

The message can take a number of forms: Multipart/alternative, Multipart/mixed, 
or Multipart/related. Related entries will be stored as children of the 
current entry. 

The only additional data stored to that in the base class are the Content-Type, and the time
sent.

@see CPushMsgEntryBase
  
@publishedPartner
@released
*/
class CMultiPartPushMsgEntry:public CPushMsgEntryBase
	{
public:
	IMPORT_C static	CMultiPartPushMsgEntry* NewL();
	IMPORT_C static CMultiPartPushMsgEntry* NewL(const TPtrC8& aAppURI);
	IMPORT_C static CMultiPartPushMsgEntry* NewL(TInt& aAppID);
	IMPORT_C ~CMultiPartPushMsgEntry();
	
	IMPORT_C void SetContentTypeL(const TDesC& aContentType);
	inline const TDesC& ContentType() const;
	inline void	SetTimeSent(const TTime& aTime);
	inline const TTime& TimeSent( ) const;
	TInt32 PushMsgType() const;

private:
	CMultiPartPushMsgEntry();
	void SetPushMsgType();
	void ExternalizeL(RMsvWriteStream& aStream);
	void InternalizeL(RMsvReadStream& aStream);

private:
	TTime iTimeSent;
	HBufC* iContentType;   	
	};

#include <cmultipartpushmsgentry.inl>

#endif  // __CMULTIPARTPUSHMSGENTRY_H__


