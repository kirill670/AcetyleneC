// MmsEncode.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** 
 * @file MmsEncode.h
 * Contains the MMS Encoding utility class. 
 * Used for encoding MMS messages
 */

#ifndef __MMSENCODE_H__
#define __MMSENCODE_H__

#include <f32file.h>		// RFs
#include <badesca.h>
#include <mmsmessage.h>
#include <mmsmediaobject.h>
#include <WSPEncoder.h>
#include <MmsUtils.h>
#include <MmsAddressParser.h>
#include "MmsTypes.h"

// forward declaration
class CMmsMessage;
class CMmsMediaObject;
class TMmsCodecMIMEContentType;

const TUint KMmsBufferIncrementSize = 50; ///< xx. Set to appropriate value later.

/**
 * Encoding class for use by MultiMedia Message object.
 * Allows for asynchronous encoding of MMS messages.
 */
class CMmsEncodeMessage : public CActive 
	{
public:
	/**
	 * Two phase constructor.
	 * @param aFileSession The file session, needed for reading in from a file.
	 */
	IMPORT_C static CMmsEncodeMessage* NewL(RFs& aFileSession);

	/**
	 * Two phase constructor.
	 * @param aFileSession The file session, needed for reading in from a file.
	 */
	IMPORT_C static CMmsEncodeMessage* NewLC(RFs& aFileSession);

	
	/**
	 * ~CMmsEncodeMessage	C++ Destructor.
	 */
	IMPORT_C ~CMmsEncodeMessage();

	/**
	 * EncodeL	Exported asynchronous function for encoding a MMS message.
	 *
	 * @param aStatus Active object status
	 * @param aMessage Message which needs to be encoded.
	 */
	IMPORT_C void EncodeL(TRequestStatus &aStatus, CMmsMessage& aMessage);
	
	/**
	 * EncodedBuffer
	 *
	 * @param aStatus
	 * @return 
	 */
	IMPORT_C TDesC8& EncodedBuffer();

protected:
	// From CActive...
	virtual void DoCancel();
	virtual void RunL();
	virtual TInt RunError(TInt aError);

private:
	/**
	 *	CMmsEncodeMessage Constructor
	 *  Initialises CMsgActive with EPriorityStandard and iFileSession.
	 *
	 * @param aFileSession The file session.
	 */
	CMmsEncodeMessage(RFs& aFileSession);


	/**	
	 * IdleComplete	completes the Active Object's asynchronous open request
	 */
	void IdleComplete();

	/**
	 *	ConstructL function called during construction.
	 */
	void ConstructL();


	// Relating to MMS Header
	
	/**	
	 * EncodeAndAddMMSHeadersL	Encodes a MMS message Header.
	 *		Depending on TransactionID of the MMSMessage,
	 *		creates different type of header.
	 *
	 * @return next state to process.
	 */
	TInt EncodeAndAddMMSHeadersL();

	/**	
	  * AddSendRequestHeadersL	Adds encoded form of header fields and field values to header for SendRequest message.
	  *		Send Request Message Type. Main Message with body parts
	  *
	  *	From From-value Mandatory.
	  *	X-Mms-Message-Class Message-class-value Optional.
	  *	X-Mms-Expiry Expiry-value Optional, default: maximum.
	  *	X-Mms-Delivery-Time Delivery-time-value Optional: default: immediate.
	  *	X-Mms-Priority Priority-value Optional. Default: Normal.
	  *	X-Mms-Sender-Visibility Sender-visibility-value Optional. Default
	  *	X-Mms-Delivery-Report Delivery-report-value Optional. 
	  *	X-Mms-Read-Reply Read-reply-value Optional.
	  *	Content-Type Content-type-value Mandatory. LAST HEADER FIELD
	  */
	void AddSendRequestHeadersL(const CMmsHeaders& aHeaders);

	 /**	
	  * AddDeliveryAcknowledgementHeadersL
	  *		Add Header Fields to iOutputBuffer
	  *		Message Type  : Delivery Acknowledgement
	  *
	  *	X-Mms-Message-Type Message-type-value = m-acknowledge-ind Mandatory.
	  *	X-Mms-Transaction-ID Transaction-id-value Mandatory.
	  *	X-Mms-MMS-Version MMS-version-value Mandatory.
	  *	X-Mms-Report-Allowed Report-allowed-value Optional. 
	  */
	void AddDeliveryAcknowledgementHeadersL(const CMmsHeaders& aHeaders);

	// Relating to MIME parts 
	void AddMultipartHeaderL();
	TInt AddRootMimePartL();

	/**	
	 *	AddNextMimePartL	Add the MIME header and body to iMessage.
	 *  We have the media object, now what. Get Mime header ,then the actual file
	 *	@return	  EEncodingMimePart if more MediaObjects to process, else EFinished; 
	 */
	TInt AddNextMimePartL();

	/**	
	 *	EncodeMimePartL	
	 *	@param		aMediaObject	extract mime header and body(data) to iMessage.
	 *	@return		EEncodingMimePart if more MediaObjects to process, else EFinished; 
	 */
	TInt EncodeMimePartL(CMmsMediaObject& aMediaObject);

	/**	
	 *	EncodeMimeHeaderL	We have the header name and all its parameters. 
	 *		Now encode using the various encoding methods and append onto an 8bit buffer.
	 *	@param aHeaderFieldName Text name of the header field.
	 *	@param aHeaderValuesList Array of all values following the header field name.
	 *	@return buffer containing the encoded field.
	*/
	HBufC8* EncodeMimeHeaderL(const TPtrC aHeaderFieldName, const CDesCArray& aHeaderValuesList);


	/**	
	 *	LookupEncoding	Look up encoding for this string
	 *	@param aHeaderFieldName Text name of the header field.
	 *  @param aPool Opened String pool to look up encoding
	 *	@param aTable which table the lookup should be done with
	 *	@param aEncoding the returned encoding for this header
	 *  @return KErrNone if found else KErrNotFound
	*/
	TInt LookupEncoding(const TDesC8& aFieldName, RStringPool aPool, const TStringTable& aTable, TUint8& aEncoding);

	/**	
	 *	 ExtractMimeHeadersL.	Add each MIME header to the buffer. 
	 *   Preceded by the HEADERS LEN and DATA LEN
	 *   @param aMediaObject headers extracted from this mediaObject.
	 *   @param aBodyLength length of the MIME body(data part).
	 */
	void ExtractMimeHeadersL(CMmsMediaObject& aMediaObject);

	/**	
	 *	ExtractBodyPartL	Open file, and read in data to iOutputBuffer
	 *  @param aMediaObject The media object being added to message.
	 *  @param aBody		buffer to which the body data is extracted.
	 *	@return				Error returned by file read.
	 */
	TInt ExtractBodyPartL(const CMmsMediaObject& aMediaObject, HBufC8* &aBody);

	// Relating to header fields..

	/**	
	 * AddPartContentTypeL	Only add the Content-Type Value. The value can contain (encoded) paramaters.
	 * Will need to be processed beforehand.
	 * @param aValuesList	array of parameters for the content type field.
	 *						Each added as a seperate field.
	 * @return length of content-type field added.
	 */
	TInt AddPartContentTypeL(const CDesCArray& aValuesList);

	/**	
	 * AddStringFieldL		Add field with a string value, encoded according to the MMS spec.
	 * @param aFieldToken	Token of field being added.
	 * @param aFieldValue	Buffer contining the field value to be added.
	 * @param aEncoded.		aEncoding. If field can to be encoded (according to the MMS spec).Defaults to EFalse. 
	 */
	void AddStringFieldL(const TMMSFieldCode aFieldToken, const TDesC& aFieldValue, const TBool aEncoded=EFalse);

	/**	
	 * AddTokenFieldL		Add field with a token value, encoded according to the MMS spec.
	 * @param aFieldToken	Token of field being added.
	 * @param aFieldValue	Value of field.
	 */
	void AddTokenFieldL(const TMMSFieldCode aFieldToken, const TUint aFieldValue);

	/**	
	 * AddDateTimeFieldL	Add field with a Date Time value, encoded according to the MMS spec.
	 * @param aFieldToken	Token of field being added.
	 * @param aTime			Value of field.
	 */
	void AddDateTimeFieldL(const TMMSFieldCode aFieldToken, const TTime& aTime);

	/**	
	 * AddMmsTimeFieldL		Add field with a time value, encoded according to the MMS spec.
	 *						Field value has option of being Absolute ora time Interval.
	 * @param aFieldToken	Token of field being added.
	 * @param aFieldValue	Value of field, stored as a TMmsTime object.
	 */
	void AddMmsTimeFieldL(const TMMSFieldCode aFieldToken, const TMmsTime& aFieldValue);	

	/**	
	 *	AddTextStringL.	Encodes a Unicode text string, and adds to the iOutputBuffer.
	 *  @param aValue. String to be added.
	 */
	void AddTextStringL(const TPtrC aValue);

	/**	
	 *	AddVersionFieldL. Encodes a version field, adding to iOutputBuffer.
	 *  @param aVersion. Value to be encoded.
	 */
	void AddVersionFieldL(const TMmsVersion& aVersion);

	/**	
	 *	AddFromFieldL. Encodes a From field, adding to iOutputBuffer.
	 *  @param aVersion. Value to be encoded.
	 */
	void AddFromFieldL(const TDesC& aFieldValue);

	/**	
	 *	AddContentTypeFieldL. Encodes a Content-Type field of KWapMultipartRelated, 
	 *	adding to iOutputBuffer.
	 */
	void AddContentTypeFieldL();

	/**	
	 *	AddStringArrayFieldL. Encodes a Content-Type field of KWapMultipartRelated, 
	 *	adding to iOutputBuffer.
	 */
	TInt AddStringArrayFieldL(const TMMSFieldCode aFieldToken, const CMmsRecipientArray& aValueArray);

	void AddContentIdValueL(const TDesC& aString);

	void AddStringL(const TDesC& aFieldValue, const TBool aEncoded);
	void AddBufferToMessageL(HBufC8 *aBuffer);
	void AppendToMessageL(const TDesC8& aAddition);
	void IncreaseBufferSizeL(TInt aIncreaseAmount);
	HBufC8* AppendToBufferL(const TDesC8& aAddition, HBufC8* aBuffer);
	HBufC8* InsertInBufferL(TUint aPos, const TDesC8& aAddition, HBufC8* aBuffer);
	HBufC8* IncreaseBufferSizeL(TInt aIncreaseAmount, HBufC8* aBuffer);

	HBufC* AddressStringLC(TPtrC aAddress, MmsAddressParser::TMmsAddressType aAddressType);
	HBufC* AddressTypeStringL(MmsAddressParser::TMmsAddressType aAddressType);

	inline TBool Is8Bit(const TDesC& aString);

private:
	TBool IsBodyBufferUnicode() const;
	void ConvertBodyBufferToUTF8L();
    void LoadMIMEContentTypesL(CArrayFixFlat<TMmsCodecMIMEContentType>& aContentTypes);
    TPtrC MatchContentTypeToExtension(const TDesC& aExt);

private:
	enum TMMSEncodingStates 
		{
		EInitial=0,
		EEncodingHeader,	///< Encoding the MMS main header 
		EEncodingRootPart,
		EEncodingMimePart,  ///< Encoding 
		EFinished
		};


	TInt				iState;			///< Current state of the state machine.
	TRequestStatus*		iEncodeStatus;	///< Not owned
	CMmsMessage*		iMessage;		///<  The message to be encoded, passed in.
	HBufC8*				iOutputBuffer;	///<  Storage for the encoded message.
	RFs&				iFileSession;		
	CWspHeaderEncoder*	iWspEncoder;	///< Utility for encoding header fields.
	HBufC8*				iMimeBuffer;	
	HBufC8*				iBodyBuffer;
	TMmsMediaObjectId	iRootId;

    CArrayFixFlat<TMmsCodecMIMEContentType>* iContentTypes;     ///< content-types
	};


TBool CMmsEncodeMessage::Is8Bit(const TDesC& aString)
	{
		// Check if the string needs encoding.
	TInt ii=aString.Length();
	while (ii--)
		{
		if (aString[ii] > 0xFF)
			return EFalse; 
		}
	return ETrue;
	}


#endif
