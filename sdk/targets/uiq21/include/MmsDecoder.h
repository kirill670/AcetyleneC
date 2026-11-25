// CMmsDecodeMessage.h
//
// Copyright © 2001 Symbian Ltd. All rights reserved.

/** @file CMmsDecodeMessage.
 * API for decoding an MMS message.
 */

#ifndef	__CMmsDecodeMessage_H__
#define	__CMmsDecodeMessage_H__

#include <f32file.h>		// RFs
#include <e32std.h>
#include <e32base.h>
#include <WspDecoder.h>
#include <WspHdrField.h>
#include <MMSUtils.h>
#include <MMSHeaders.h>
#include <MmsMessage.h>
#include <MmsMediaObject.h>
#include <barsread.h>

#include "MmsCharconv.h"

class CMmsMediaObject;
class TMmsCodecMIMEContentType;

/**
 *	CMmsContentTypeValue 
 *	A class to encapsulate the content-type value data in an easy-to-use form.
 */
class CMmsContentTypeValue : public CBase
	{
public:
	/**
	 * A class to encapsulate an MMS parameter in an easy to use form.
	 */
	class CMmsContentTypeParam : public CBase
		{
	public:
		/**
		 * Construct a parameter name/value pair.
		 *
		 * @param aName The name of the parameter
		 * @param aValue The Value of the parameter
		 * @exception Can leave if no memory is available
		 */
		static CMmsContentTypeParam* NewL(const TDesC8& aName, const TDesC8& aValue);

		/**
		 * Returns the parameter name.
		 *
		 * @return The name of the parameter
		 */
		TPtrC Name() const;

		/**
		 * Returns the parameter value.
		 *
		 * @return The parameter value
		 */
		TPtrC Value() const;

		~CMmsContentTypeParam();

	private:
		/**
		 * Part of the 2 phase constructor
		 */
		void ConstructL(const TDesC8& aName, const TDesC8& aValue);

	private:
		HBufC* iName;	///< The name of the parameter
		HBufC* iValue;	///< The parameter value
		};

public:
	/**
	 * 2 Phase constructor
	 *
	 * @excpetion Can leave if there is no available memory.
	 */
	static CMmsContentTypeValue* NewL(const TDesC8& aValue);

	/**
	 * 2 Phase constructor
	 *
	 * @excpetion Can leave if there is no available memory.
	 */
	static CMmsContentTypeValue* NewLC(const TDesC8& aValue);

	/**
	 * Returns the content-type value string, excluding any parameters
	 *
	 * @return The content-type value, excluding any parameters.
	 */
	const TPtrC Value() const;

	/**
	 * Returns the parameter with the given index.
	 *
	 * @param aIndex The index of the parameter to be returned.
	 * @return The parameter at the given index.
	 */
	const CMmsContentTypeParam& Parameter(TInt aIndex) const;

	/**
	 * Returns the number of parameters.
	 *
	 * @return The number of parameters.
	 */
	TInt ParameterCount() const;

	/**
	 * Adds a parameter to the content-type value.
	 *
	 * @param aParamName The name of the parameter to be added.
	 * @param aParamValue The value of the parameter to be added.
	 */
	void AddParameterL(const TDesC8& aParamName, const TDesC8& aParamValue);

	/**
	 * Destructor.
	 */
	~CMmsContentTypeValue();

private:
	/**
	 * Part of the 2 Phase constructor
	 *
	 * @excpetion Can leave if there is no available memory.
	 */
	void ConstructL(const TDesC8& aValue);

private:
	RPointerArray<CMmsContentTypeParam> iParameters; ///< The array of parameters
	HBufC* iValue;									 ///< The main value string (not including the parameters)
	};


/**
 *	CMmsDecodeMessage 
 *  Class providing API for asynchronously decoding an MMS message.
 */
class CMmsDecodeMessage : public CActive 
	{
public:
    /**
     * 2-phase constructor
     *
     * @param aFileSession file session.
     * @exception KErrXxx Leaves if an out-of-memory condition occurs.
     * @return returns a newly created CMmsDecodeMessage
     */
	IMPORT_C static CMmsDecodeMessage* NewL(RFs& aFileSession);

    /**
     * 2-phase constructor
     *
     * @param aFileSession file session.
     * @exception KErrXxx Leaves if an out-of-memory condition occurs.
     * @return returns a newly created CHeaderArray, left on the cleanup stack
     */
	IMPORT_C static CMmsDecodeMessage* NewLC(RFs& aFileSession);
	IMPORT_C ~CMmsDecodeMessage();


    /**
     * Class destructor
     */
    /**
     * DecodeMessageL	Decodes an MMS message.
     * @param			aInputBuffer. 8bit buffer containing the encode form of the message.
     * @param			aMmsMessage. Object used for storeing the decoded message.
     */
	IMPORT_C void DecodeL(TRequestStatus& aStatus, const TDesC8& aInputBuffer, CMmsMessage& aMmsMessage);


protected:
	// From CActive...
	virtual void DoCancel();
	virtual void RunL();
	virtual TInt RunError(TInt aError);

private:
	/**	
	 * IdleComplete	completes the Active Object's asynchronous open request
	 */
	void IdleComplete();


    /**
     * ConstructL	
     * @exception
     */
	void ConstructL();


    /**
     * CMmsDecodeMessage	constructor	
     * @param				aFileSession
     */
	CMmsDecodeMessage(RFs& aFileSession);

    /**
     * DecodeL		Decodes the MMS MimeHeader and multipart header (if present)
	 *				Determines if the message has a body to decode as well.
	 *				Sets iBuffer to the MMS body (if any)
     * @exception
	 * @return		Returns length of remaining buffer left to decode, else KErrNotFound.
     */
	TInt DecodeHeadersL();

    /**
     * DecodeMmsHeadersL		Decodes the MMS MimeHeader fields.
     * @param
	 * @return		Returns length of remaining buffer left to decode, else KErrNotFound.
     */
	void DecodeMmsHeadersL(CWspHeaders* aWspHeaders);

//Fix for the defect LOO-5AVCNL
	void RemoveTypeInfoIfNeeded(HBufC& aBuf);

	void ProcessRecipientFieldL
     (CMmsHeaders& aMmsHdrs,CMmsHeaders::TMmsRecipientType aRecipientType,
	  TWspPrimitiveDecoder& aDecoder);
//end fix for the defect LOO-5AVCNL
	
	TInt DecodeMimePartL();

	/**
	 * StoreMediaObjectHeaderL		Stores the header field values contained 
	 *								in the input buffer, into media object.
	 * @param	aInputBuffer
	 * @param	aMediaObject
	 * @return	Returns length of buffer left to process.
	 */
	void StoreMediaObjectHeaderL(const TDesC8&  aInputBuffer, CMmsCodecMediaObjectCreator& aMediaObject);

	/**
	 * LookupMediaTypeL		Match the input meida type in the string pool.
	 * @param	aMediaType	The value to be checked.
	 * @return	Returns RStringF constructed using the input value 
	 *			and associated with the WSPContentTypes::Table
	 */
	RStringF LookupMediaTypeL(TUint8 aMediaType) const;

	/**
	 * LookupCharset		Convert Wap Wsp Table 42 charset  token to string
	 * @param	aCharsetToken	The token value of the charset.
	 * @param	aCharsetStr	The string representation of the charset value.
	 * @return	Returns KErrNone if found, KErrNotFound if not
	 */
	TInt LookupCharsetStr(TUint8 aCharsetToken, TDes8& aCharsetStr);

	/**
	 * ProcessMessageFieldL	  Extract, decode and store Message MMS header field.
	 * @param	aDecoder	The value to be checked.
	 * @param	aMmsHdrs	The value to be checked.
	 */
	void ProcessMessageFieldL(TWspPrimitiveDecoder& aDecoder, CMmsHeaders& aMmsHdrs);

	/**
	 * DecodeFromFieldLC	  
	 * @param	aDecoder currently pointng to the from field
	 * @return	String buffer placed on the cleanup stack. NULL if decoding failed.
	 */
	HBufC* DecodeFromFieldLC(TWspPrimitiveDecoder& aDecoder);

//Fix for the defect CKH-5BADBE: Duplicate code and potential memory leak in CMmsDecoder
	HBufC* CopyDecoderStrLC(TWspPrimitiveDecoder& aDecoder);

	/**
	 * DecodeEncodedStringValueLC	  Decodes a MMS defined encoded-string.
	 * @param	aDecoder currently pointng to the encoded string
	 * @return	String buffer placed on the cleanup stack,
	 *			returns NULL if decoding failed, or invalid input.
	 */
	HBufC* DecodeEncodedStringValueLC(TWspPrimitiveDecoder& aDecoder);
	

	/**
	 * ProcessTimeValueFieldL. Extracts/decodes Time-value field from iBuffer.
	 * @param	aDecoder. Object used to decode the value.		
	 * @return	TMmsTime value.
	 */
	TMmsTime ProcessTimeValueFieldL(TWspPrimitiveDecoder& aDecoder);

	/**
	 * IsRootPart. Checks MimeHeader to see if it is the root part of the multipart message.
	 * @param	aBuffer. Buffer containing the MIME header for the current media object.
	 * @return	TBool indicating the truth or falsity of the function statement.
	 */
	TBool IsRootPartL(const TPtrC8 aBuffer);

	/**
	 * SetMediaObjectUriL. Finds the URI from the given headers and sets the iUri member.
	 * @param	aInputBuffer The header data
	 */
	void SetMediaObjectUriL(const TDesC8&  aInputBuffer);

	/**
	 * ParseContentTypeValueLC. Parses and decodes the content-type value..
	 * @param	aInputBuffer The header data
	 * @return A CMmsContentTypeValue structure containing the decoded parts of the given content-type value. NULL if the content-type value is invalid.
	 * @exception Can leave if no memory is available.
	 */
	CMmsContentTypeValue* ParseContentTypeValueLC(const TDesC8& aContentTypeValue, TInt& aContentTypeLength);


private:		
	void WriteBodyToFileL(CMmsCodecMediaObjectCreator& aMediaObjCreator, TDesC8& aBodyText, const CMmsContentTypeValue& aContentType);
	void ConvertFromUTFToUnicodeL(TBool aUTF8, const TDesC8& aUTFText, HBufC* aUnicodeText);

	void LoadMIMEContentTypesL();
	void CalculateFileExtensionL(TDes& aFileExtension, const TDesC& aContentType);
    TBool CalculateFileNameL(TDes& aFileName, CMmsCodecMediaObjectCreator& aMediaObjCreator, const CMmsContentTypeValue& aContentType);
    TBool FindFileNameInMimeHeader(TDes& aFileName, CMmsCodecMediaObjectCreator& aMediaObjCreator, const TDesC& aHeaderName);
    TPtrC ValidateFilename(const TDesC& aFilename);

private:

	enum TMMSDecodingStates 
		{
		EDecodeMimeHeaders,
		EDecodeMimePart,  
		EFinished
		};
	
	TInt				iState;			///< Current state of the state machine.
	TRequestStatus*		iDecodeStatus;	///< Not owned
	CMmsMessage*		iMmsMessage;	///< Not owned
	RFs&				iFileSession;	///< Not owned
	TPtrC8				iBuffer;
	HBufC8*				iStartParam;	///< value determines which MIME part is the "start"
	TBool				iFirstMimePart;	///< If there is no start param, the first part is the root
	TBool				iWapMultipart;
	HBufC*				iCurrentUri;	///< The URI of the MIME part being parsed (if any)
	RStringPool			iStringPool;	///< Used for matching strings with associated encoded 7bit values.
	CMmsCharconv*		iCharconv;		///< Object for character set conversion.

	CArrayFixFlat<TMmsCodecMIMEContentType>* iContentTypes;
    TBool               iRelated;       ///< used to determine if a multipart message has a presentation part
	};



#endif //__CMmsDecodeMessage_H__
