// PushMessage.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

/** @file PushMessage.H
 * This file contains the declaration of the CPushMessage which holds the header and body of a WAP Push Message.
 * Also contains utility classes such as CMultipartIteratorBase, CMultipartBinIterator and CMultipartTextIterator.
 */

#ifndef __PUSHMESSAGE_H__
#define __PUSHMESSAGE_H__

#include <e32std.h>
#include <thttpfields.h>
#include <e32base.h>
#include <wapcli.h>
#include "WapDecoder.h"

class RWriteStream;
class CHTTPResponse;

_LIT(KMultipartText, "multipart/");
_LIT(KMultipartBin, "application/vnd.wap.multipart");



/**
 *
 * CPushMessage is a Container class that holds the header and body of a WAP 
 * Push Message. It provides functions to access the header and body information. These 
 * functions make use of the CHTTPResponse class to parse the fields and return header 
 * field data. There are specific functions to find Application ID, and the Content Type values 
 * as these fields are frequently required. 
 *
 * The class also a function to give Read-Only access to the body of the message. 
 *
 * This is a friend of the CHTTPResponse class, to permit access to two protected functions.
 */

//##ModelId=3B659EEA00DA
class CPushMessage : public CBase
	{
public:
	/** Creates a new push message - taking ownership of aHeader and aBody */
	//##ModelId=3B659EEA0167
	IMPORT_C static CPushMessage* NewL(HBufC8* aHeader, HBufC8* aBody);
	
	//##ModelId=3B659EEA0166
	IMPORT_C virtual ~CPushMessage();  // virtual just in case we want to derive the class
	//##ModelId=3B659EEA0154
	IMPORT_C TBool GetAppID(TPtrC8& aAppURI, TInt& aAppID, TBool& aIsAnInt);
	//##ModelId=3B659EEA0152
	IMPORT_C void  GetContentType(TPtrC& aContentType) const;
	//##ModelId=3B659EEA0136
	IMPORT_C TBool GetHeaderField(THttpHeaderField aField, TPtrC8& aFieldValue) const;
	//##ModelId=3B659EEA012C
	IMPORT_C TBool GetBinaryHeaderField(THttpHeaderField aField, TPtrC8& aFieldValue) const;
	//##ModelId=3B659EEA0140
	IMPORT_C TBool GetHeaderField(THttpHeaderField aField, TTime& aTime) const;
	//##ModelId=3B659EEA012A
	IMPORT_C TBool GetMessageBody(TPtrC8& aMessageBodyPtr) const;
	//##ModelId=3B659EEA0121
	IMPORT_C TBool GetHeader(TPtrC8& aMessageHeaderPtr) const;
private:
	//Constructors
	//##ModelId=3B659EEA0116
	CPushMessage(HBufC8* aHeader);
	//##ModelId=3B659EEA010C
	void ConstructL(HBufC8* aHeader, HBufC8* aBody);
private:
	// Private member data
	//##ModelId=3B666A600185
	CHTTPResponse* iHttpResponse;
	//##ModelId=3B659EEA00F8
	TPtrC8 iPushHeader;
	//##ModelId=3B659EEA00EE
	HBufC8* iPushBody;
	};



/**
 * Multipart Message splitter base class.  
 * This class defines an abstract API for iterating through multipart
 * messages to return the message parts.
 *
 * Next() moves the iterator to the next message part and returns
 * ETrue when there is a next part, EFalse otherwise
 * 
 * First() to reset the iterator the beginning of the message
 * 
 * GetPartL() to extract the message part currently pointed at
 */
//##ModelId=3B659EDE0227
class CMultipartIteratorBase : public CBase
	{
public:
	//##ModelId=3B659EDE025B
	virtual TBool NextL() = 0;
	//##ModelId=3B659EDE025A
	virtual void FirstL() = 0;
	//##ModelId=3B659EDE0259
	virtual CPushMessage* PartL() = 0;
protected:
	//##ModelId=3B659EDE024F
	CMultipartIteratorBase(CPushMessage& aPushMessage);
protected:
	//##ModelId=3B659EDE0247
	CPushMessage& iPushMessage;
	//##ModelId=3B659EDE023D
	TUint iCurrentPartStart;
	};


/**
 * CMultipartBinPushMessage is a utility class for cracking apart WAP Binary 
 * Multipart Messages.
 *
 * Implements the abstract multipart iterator API defined in 
 * CMultipartIteratorBase
 */
//##ModelId=3B659EE10005
class CMultipartBinIterator : public CMultipartIteratorBase
	{
public:
	//##ModelId=3B659EE10037
	IMPORT_C static CMultipartBinIterator* NewL(CPushMessage& aPushMessage);

	// from CMultipartIteratorBase
	//##ModelId=3B659EE1002F
	IMPORT_C virtual TBool NextL();
	//##ModelId=3B659EE1002E
	IMPORT_C virtual void FirstL();
	//##ModelId=3B659EE1002D
	IMPORT_C virtual CPushMessage* PartL();
private:
	//##ModelId=3B659EE10024
	CMultipartBinIterator(CPushMessage& aPushMessage);
	//##ModelId=3B659EE10023
	void ConstructL();
private:
	//##ModelId=3B659EE1001B
	TWapBinCodex::TUintvar iMultiNumEntries;
	//##ModelId=3B659EE10012
	TInt iCurrentPart;
	};


/**
 * CMultipartTextMessage is a utilitiy class for cracking apart text based MIME 
 * Messages.
 * 
 * Implements the abstract multipart iterator API defined in 
 * CMultipartIteratorBase
 * 
 */
//##ModelId=3B659EE4024E
class CMultipartTextIterator : public CMultipartIteratorBase
	{
public:
	//##ModelId=3B659EE4028A
	IMPORT_C static CMultipartTextIterator* NewL(CPushMessage& aPushMessage);
	//##ModelId=3B659EE40282
	IMPORT_C virtual ~CMultipartTextIterator();
		
	// from CMultipartIteratorBase
	//##ModelId=3B659EE40281
	IMPORT_C virtual TBool NextL();
	//##ModelId=3B659EE40280
	IMPORT_C virtual void FirstL();
	//##ModelId=3B659EE40279
	IMPORT_C virtual CPushMessage* PartL();
private:
	//##ModelId=3B659EE40277
	CMultipartTextIterator(CPushMessage& aPushMessage);
	//##ModelId=3B659EE40276
	void BoundaryParamL();
	//##ModelId=3B659EE4026E
	void ConstructL();
private:
	//##ModelId=3B659EE40264
	HBufC8*	iBoundary;
	//##ModelId=3B659EE4025B
	TPtrC8 iIndexPtr;
	};


#endif
