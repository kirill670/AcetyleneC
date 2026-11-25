// PushEntry.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

/** @file PushEntry.h
 * WAP Push Message Header File for the Utility class
 */

#ifndef __PUSHENTRY_H__
#define __PUSHENTRY_H__

#include <e32std.h>
#include <msvapi.h>
#include <msvstd.h>


/** Uid defines for Push MTM and Push Message Types */
const TUid KUidMtmWapPush = {0x10009158};
const TUid KUidWapPushMsgSI = {0x10009159};
const TUid KUidWapPushMsgSL = {0x1000915A};
const TUid KUidWapPushMsgMultiPart = {0x1000915B};
const TUid KUidWapPushMsgUnknown = {0x1000915C};


// Defines for Masking values used to extract status information from iMtmData1
const TInt32 KPushMaskOnlyStatus			= 0x0000000F;
const TInt32 KPushMaskEverythingButStatus	= 0xFFFFFFF0;
const TInt32 KPushMaskOnlyAction			= 0x000000F0;
const TInt32 KPushMaskEverythingButAction	= 0xFFFFFF0F;


// Defines for Leave Codes
const TInt KWPushBaseError		 =	-1100;
const TInt KWPushNoMsgIndexEntry =   (KWPushBaseError-1);




//enum for use with both the Server Mtm and its progress object
enum TPushServerMTMState
	{
	EWapPushServerMtmWaiting,
	EWapPushServerMtmChange,
	EWapPushServerMtmCreate,
	EWapPushServerMtmDelete,
	EWapPushServerMtmComplete
	};


/**
 * Progress structure used with asynchronous operations with the Push Server MTM. 
 * Allows error status and ID of current entry to be returned to caller.
 */
//##ModelId=3B659EDF00B6
class TPushMTMProgress
	{
public:
	
	//##ModelId=3B659EDF00EA
	TInt				iError; // client side needs to be informed of an error
	//##ModelId=3B659EDF00E0
	TInt				iTotalMsgs;
	//##ModelId=3B659EDF00D6
	TInt				iMsgsProcessed;
	//##ModelId=3B659EDF00CC
	TMsvId				iMsgId;
	//##ModelId=3B659EDF00C2
	TPushServerMTMState iPushState;// Operation that is currently in progress
	};

// Package buffer used for returning the progress info from the Push Server MTM 
typedef TPckgBuf<TPushMTMProgress> TPushMTMProgressBuf;


// Panic name and codes
_LIT(KPushPanicMoniker, "PUSHENTRY");

enum TPushEntryPanic	{
						EPushEntryNullMsgId,         // Null Ids for entries not valid (Service, &Msg)
						EPushEntryServiceIdMismatch, // Only save messages under the Service Entry
						EPushEntryWrongMTMtype,      // Not a WAP Push  MTM
						EPushEntryWrongMsgtype       // iBioType value in TMsvEntry don't match Uid for Push Entry class
						};


/**
 * Abstract base class for the Push Message Entry family of classes. 
 * The Push Entry class effectively acts as a wrapper for the TMsvEntry
 * class, providing accessors and storage functionality. Key pieces of data
 * are mapped onto certain fields in the TMsvEntry class, to speed up access
 * by the UI and other application. This base class has the generic mappings and
 * storage behaviour. More specialized mappings and storage are defined in each 
 * derived class.
 * 
 * The mappings of data to TMsvEntry fields standard to all classes are:-
 *
 * *     Push Message Type Uid   - iBioUid
 *
 * *     Status                  - an enum, sets Bits 0-3 of iMtmData1
 *
 * The iDetails, and iDescription members of the TMsvEntry are also used   
 * for holding data. The actual manner of usage depends on the data in that particular 
 * type of WAP Push message, and so  is class dependent. 
 * 
 * For a number of derived classes there are more data fields than available 
 * for use in the TMsvEntry, an the Unknown type potentially requires large data capacity. 
 * This  additional data is saved in the message  store associated with the message entry. 
 * Functionality for storing data is present in both SaveL and UpdateL, rather than a StoreL 
 * function, because each has different requirements for the way that they store this data. 
 * A RestoreL function is present because there is only one requirement for loading data. The 
 * ExternalizeL()/InternalizeL() functions are pure virtual, because
 * the implementation is class dependent.It also ensures that the base class can
 * never be instantiated, only the derived classes. All classes store the Message 
 * Header and the From information, to allow later retrieval of the original details
 * of the message, if  these should be required for some reason. The storing/restoring
 * the base class data is performed by the DoBaseExternalizeL() / DoBaseInternalizeL() 
 * functions.  
 */
//##ModelId=3B659EE1016D
class CPushMsgEntryBase: public CBase
	{
public:
	enum TPushMsgStatus	{
						EPushMsgStatusValid = 0,
						EPushMsgStatusExpired,
						EPushMsgStatusDeleted,
						EPushMsgStatusCorrupt
						};

	//##ModelId=3B659EE10253
	IMPORT_C virtual ~CPushMsgEntryBase();
	/** Creates its own CMsvStore from the CMsvSession & calls StoreL() */
	//##ModelId=3B659EE10240
	IMPORT_C virtual TMsvId SaveL(CMsvSession& aSession, TMsvId aParent);
	//##ModelId=3B659EE10235
	IMPORT_C virtual void UpdateL(CMsvSession& aSession);
	/** Creates its own CMsvStore from the CMsvSession & calls RestoreL() */
	//##ModelId=3B659EE1022B
	IMPORT_C virtual void RetrieveL(CMsvSession& aSession, TMsvId aMsgId);
	
	//##ModelId=3B659EE10221
	IMPORT_C void SetEntry(const TMsvEntry& aEntry);
	//##ModelId=3B659EE10217
	IMPORT_C void SetStatus(TInt aStatusFlags);
	//##ModelId=3B659EE1020D
	IMPORT_C const TDesC8&  Header() const;
	//##ModelId=3B659EE10204
	IMPORT_C void SetHeaderL(const TDesC8& aHeader);
	//##ModelId=3B659EE10203
	IMPORT_C const TDesC8& From() const; 
	//##ModelId=3B659EE101FA
	IMPORT_C void SetFromL(const TDesC8& aFrom);
	//##ModelId=3B659EE101F9
	virtual TInt32 PushMsgType() const =0;
	//##ModelId=3B659EE101F1
	inline const TMsvEntry& Entry() const;
	//##ModelId=3B659EE101F0
	inline TInt Status() const;

protected:
	//##ModelId=3B659EE101EF
	CPushMsgEntryBase();
	//##ModelId=3B659EE101E6
	IMPORT_C virtual void ConstructL();
	// No  matching StoreL due to different needs for saving & updating msg's
	//##ModelId=3B659EE101DC
	IMPORT_C void RestoreL(CMsvStore& aStore );
	//##ModelId=3B659EE101D1
	IMPORT_C virtual void ExternalizeL(RMsvWriteStream& aStream);
	//##ModelId=3B659EE101C8
	IMPORT_C virtual void InternalizeL(RMsvReadStream& aStream);
	//##ModelId=3B659EE101C7
	virtual void SetPushMsgType()=0;// Only the object can set it's push type - class dependent 
	//##ModelId=3B659EE101BD
	void DoSaveL(CMsvEntry& aMsvEntry);

protected:
	//##ModelId=3B659EE101B5
	TMsvEntry	 iEntry;

	// Both following descriptors needed required as the TPtrC's in TMsvEntry 
	// point to temporary buffers - exist as long as interface to Msg Server 
	// (ie the CMsvEntry) must keep a copy to make the object persistant.
	//##ModelId=3B659EE101AB
	HBufC*		 iMsgDetails;    
	//##ModelId=3B659EE1019F
	HBufC*		 iMsgDescription;
								
							    
	//##ModelId=3B659EE10195
	HBufC8*		 iHeader;
	//##ModelId=3B659EE10183
	HBufC8*		 iFrom;
	//##ModelId=3B659EE1017A
	TBool		 iHasServerEntry;
	};


/**
 * A specialisation of the CPushMsgEntryBase class specifically for 
 * Service Indication Push Messages.
 * Has single factory function that creates the object.  Accessor 
 * functions to allow access to all the fields holding data for the 
 * SI push messages.  The additional information for a SI message is :
 *
 * Action	-	5 possible action levels, use an enum to set Bits 4-7 
 *				of TMsvEntry::iMtmData1
 * SI Id	-	Unique identifier for this SI Message. 
 *				TMsvEntry::iDescription holds this value
 * URL		-	Location of the content to present to the user, stored 
 *				in TMsvEntry::iDetails
 * Creation	-	Date and Time of creation of the message, held in 
 *				TMsvEntry::iData
 * Expires	-	Date and Time after which the message is invalid 
 *				and should be discarded
 *
 * Text		-	Additional information sent with the message, stored in
 *				the Message Store.
 *
 */
//##ModelId=3B659EE20150
class CSIPushMsgEntry:public CPushMsgEntryBase
	{
public:
	// Enum specifically for SI Messages.
	// Note that these values get bit-shifted so that they set Bits 4-7 of iMtmData1
	enum TSIPushMsgAction 
			{
			ESIPushMsgDelete = 0,	// effectively  Bit 4 = 0
			ESIPushMsgSignalNone,	//              Bit 4 = 1, i.e. 16   
			ESIPushMsgSignalLow,	//              Bit 4 = 0, 5 =1. i.e. 32
			ESIPushMsgSignalMedium,
			ESIPushMsgSignalHigh
			};

	//##ModelId=3B659EE201C1
	IMPORT_C static	CSIPushMsgEntry* NewL();
	//##ModelId=3B659EE201C0
	IMPORT_C ~CSIPushMsgEntry();
	//##ModelId=3B659EE201BF
	inline const TDesC& Id() const;
	//##ModelId=3B659EE201B6
	IMPORT_C void SetIdL(const TDesC& aID);
	//##ModelId=3B659EE201B5
	IMPORT_C TInt Action() const;
	//##ModelId=3B659EE201AC
	IMPORT_C void SetAction(TInt aActionFlags);
	//##ModelId=3B659EE201AB
	inline const TTime& Created() const;
	//##ModelId=3B659EE201A3
	inline void	SetCreated(const TTime& aCreated);
	//##ModelId=3B659EE201A2
	inline const TTime& Expires() const;
	//##ModelId=3B659EE20199
	inline void	SetExpires(const TTime& aExpires);
	//##ModelId=3B659EE20198
	inline const TDesC&  Url() const;
	//##ModelId=3B659EE2018F
	IMPORT_C void SetUrlL(const TDesC& aUrl);
	//##ModelId=3B659EE2018E
	IMPORT_C const TDesC& Text() const;
	//##ModelId=3B659EE20186
	IMPORT_C void SetTextL(const TDesC& aText);
	//##ModelId=3B659EE20185
	TInt32 PushMsgType() const;
private:  //functions
	//##ModelId=3B659EE20184
	CSIPushMsgEntry();
	//##ModelId=3B659EE2017B
	void ExternalizeL(RMsvWriteStream& aStream);
	//##ModelId=3B659EE20179
	void InternalizeL(RMsvReadStream& aStream);
	//##ModelId=3B659EE20178
	void SetPushMsgType();
private: //data
	//##ModelId=3B659EE20170
	TTime	iExpiryDate;
	//##ModelId=3B659EE20166
	HBufC*	iText;
	};


/**
 * Class for storing the data in Service Loading Push Messages. 
 * It is derived from CPushMsgEntryBase. 
 * There are two items of data that are stored in addition to the data 
 * held by the base class. These are :
 *
 * Action  - message priority, 3 states represented by an enum used to 
 *			 set Bits 4-7 of TMsvEntry::iMtmData1
 * URL     - the location of the service to load, saved in TMsvEntry::iDetails
 *
 * Functions have been provided to access the members in the TMsvEntry where 
 * this data is held.
 */
//##ModelId=3B659EE202B9
class CSLPushMsgEntry:public CPushMsgEntryBase
	{
public:
	//Public enumeration used for the action level for a SL Push Message.
	//Note that these values get bit-shifted so that they set Bits 4-7 of iMtmData1.
	enum TSLPushMsgAction { ESLPushMsgExecuteCache	 = 0,	// effectively Bit 4 = 0
							ESLPushMsgExecuteLow,	//			  Bit 4 = 1, i.e. 16   
							ESLPushMsgExecuteHigh };		//	  Bit 4 = 0, 5 =1. i.e. 32

	//##ModelId=3B659EE202E2
	IMPORT_C static	CSLPushMsgEntry* NewL();
	//##ModelId=3B659EE202E1
	IMPORT_C ~CSLPushMsgEntry();
	//##ModelId=3B659EE202DB
	IMPORT_C TInt Action() const;
	//##ModelId=3B659EE202D9
	IMPORT_C void SetAction(TInt aActionFlags);
	//##ModelId=3B659EE202D8
	inline const TDesC&	Url() const;
	//##ModelId=3B659EE202D1
	IMPORT_C void SetUrlL(const TDesC& aUrl);
	//##ModelId=3B659EE202CF
	inline void	SetMsgDateTime(const TTime& aTime);
	//##ModelId=3B659EE202CE
	inline const TTime& MsgDateTime() const;
	//##ModelId=3B659EE202CD
	TInt32 PushMsgType() const;
private:
	//##ModelId=3B659EE202C5
	CSLPushMsgEntry();
	//##ModelId=3B659EE202C4
	inline void SetPushMsgType();
	};

/**
 * Specialisation of the Push Entry base class that acts as a place holder for the start of a multipart 
 * WAP Push Message.  The message can take a number of forms, Multipart/alternative, Multipart/mixed, 
 * or Multipart/Alternative. Related entries will be stored as children of the current entry, so this class
 * acts as the top of the hierarchical structure.  The only additional data to that in the base class 
 * is the Content-Type. The iDetails field of the TMsvEntry is used to store this data.
 */
//##ModelId=3B659EE8031C
class CMultiPartPushMsgEntry:public CPushMsgEntryBase
	{
public:
	//##ModelId=3B659EE80347
	IMPORT_C static	CMultiPartPushMsgEntry* NewL();
	//##ModelId=3B659EE80346
	IMPORT_C ~CMultiPartPushMsgEntry();
	//##ModelId=3B659EE80344
	IMPORT_C void SetContentTypeL(const TDesC& aContentType);
	//##ModelId=3B659EE8033B
	inline const TDesC& ContentType() const;
	//##ModelId=3B659EE80333
	inline void	SetMsgDateTime(const TTime& aTime);
	//##ModelId=3B659EE80332
	inline const TTime& MsgDateTime( ) const;
	//##ModelId=3B659EE80331
	TInt32 PushMsgType() const;
private:
	//##ModelId=3B659EE80330
	CMultiPartPushMsgEntry();
	//##ModelId=3B659EE80327
	void SetPushMsgType();
	};


/* This specialisation of the Push Entry class is used where the message is a type that cannot be
 * processed by the WAP Push Message Handlers.  The content type of the message given in the header 
 * does not correspond to  any of the registered Push Message types. Nor does it match any recognised 
 * BIO Message types, otherwise it would have been converted to the relevant message format and stored
 * in the usual manner. Apart from the data stored by the base class, the only data stored is
 * 
 * * Content Type  -  this is mapped to TMsvEntry::iDetails as for the multipart subclass 
 *
 * * Message Body  -  this is the binary data contained in the message. No data conversion is performed
 *
 * Though message body has the potential to be very large, the limiting factor will be the memory of 
 * the device, as the descriptors and the Serialisation functions are capable of handling very
 * large data. 
 */
//##ModelId=3B659EDF0020
class CUnknownPushMsgEntry:public CPushMsgEntryBase
	{
public:
	//##ModelId=3B659EDF008F
	IMPORT_C static	CUnknownPushMsgEntry* NewL();
	//##ModelId=3B659EDF008E
	IMPORT_C ~CUnknownPushMsgEntry();
	//##ModelId=3B659EDF0085
	IMPORT_C TMsvId SaveL(CMsvSession& aSession, TMsvId aParent);
	//##ModelId=3B659EDF007D
	IMPORT_C void UpdateL(CMsvSession& aSession);
	//##ModelId=3B659EDF007A
	IMPORT_C void RetrieveL(CMsvSession& aSession, TMsvId aMsgId);
	//##ModelId=3B659EDF0072
	inline const TDesC&	ContentType() const;
	//##ModelId=3B659EDF0070
	IMPORT_C void SetContentTypeL(const TDesC& aContentType);
	//##ModelId=3B659EDF0069
	IMPORT_C const TDesC8& MessageData() const;
	//##ModelId=3B659EDF0067
	IMPORT_C void SetMessageDataL(const TDesC8& aMessageData);
	//##ModelId=3B659EDF005E
	inline void	SetMsgDateTime(const TTime& aTime);
	//##ModelId=3B659EDF005D
	inline const TTime& MsgDateTime( ) const;
	//##ModelId=3B659EDF005C
	TInt32 PushMsgType() const;
private:
	//##ModelId=3B659EDF0055
	void ConstructL();
	//##ModelId=3B659EDF0054
	CUnknownPushMsgEntry();
	//##ModelId=3B659EDF0053
	void SetPushMsgType();
	//##ModelId=3B659EDF004A
	void SaveMessageBodyL(const CMsvEntry& aEntry, TFileName& aFileName);
	//##ModelId=3B659EDF0048
	const TDesC& ContentTypeExtension(const TDesC& aContentType);
	//##ModelId=3B659EDF003E
	void DoRetrieveAttachmentL(const CMsvEntry& aEntry);
private:
	//##ModelId=3B659EDF0036
	HBufC8* iMessageData;
	//##ModelId=3B659EDF002D
	RFs     iRFs;
	};


#include "pushentry.inl"

#endif
