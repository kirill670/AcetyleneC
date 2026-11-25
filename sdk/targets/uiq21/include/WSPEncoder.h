// WspEncoder.h	
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __WSPENCODER_H__
#define __WSPENCODER_H__

#include <e32base.h>
#include <f32file.h>		// RFs
#include <badesca.h>		// arrays etc.
#include <stringpool.h>

enum TWspCodecPanic {
	/** Due to failure to call StartValueLength function */
	EWspCodecPanicStartValueLengthNotCalled=0,
	/** Due to failure to call EndValueLength matching a call to StartValueLength */
	EWspCodecPanicEndValueLengthNotCalled,
	/** Due to failure to call StartHeaderL function */
	EWspCodecPanicStartHeaderLNotCalled,
	/** Due to StartHeaderL function being called twice without EndHeaderL */
	EWspCodecPanicStartHeaderCalledTwice,
	/** Due to parameter Token not having the top bit set */
	EWspCodecPanicInvalidToken
};
 
/** 
 *  This class can be used to encode one header field at a time,
 *  with all its values and parameters.
 * 
 *  It has no knowledge of encoding the BNF of a particular header field, but
 *  the functions provided can be used in combination, producing an 8-bit buffer 
 *  containing the encoded header.
 *
 *  Intended usage would be to call a series of functions. The first one being StartHeader,
 *  The final one being EndHeader, which would return a buffer containing 
 *  the complete encoded header field.
 *  eg:
 *		encoder->StartHeaderL();
 *		encoder->AddLongIntL();
 *		encoder->AddTextStringL();
 *		HBufC8* output = encoder->EndHeaderL();
 *
 */
class CWspHeaderEncoder : public CBase
	{
public:
	/**
	 * @fn			    NewL()
	 * Intended Usage : Static factory constructor.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static CWspHeaderEncoder* NewL();

	/**
	 * @fn			    NewLC()
	 * Intended Usage : Static factory constructor.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static CWspHeaderEncoder* NewLC();

	/**
	 * @fn			    ~CWspHeaderEncoder
	 * Intended Usage : Default destructor
	 */
    IMPORT_C virtual ~CWspHeaderEncoder(); 

	/**
	 * @fn				StartHeaderL(TUint8 aToken)
	 * Intended Usage : Starts a new encoded header. 
	 * @param aToken	field name being encoded as a Token value.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void StartHeaderL(TUint8 aToken);	

	/**
	 * @fn				StartHeaderL(const TDesC8& aString)
	 * Intended Usage : Starts a new encoded header.
	 * @param aString	Fieldname parameter is encoded as a TextString.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void StartHeaderL(const TDesC8& aString);	

	/**
	 * @fn				StartHeaderL(const RStringF aString)
	 * Intended Usage : Starts a new encoded header.
	 * @param aString	Fieldname parameter is encoded as a TextString.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void StartHeaderL(const RStringF aString);	


	/**
	 * @fn				EndHeaderL();
	 * Intended Usage : Completes and returns encoded field 8 bit buffer. This method
						will panic if an EndValueLengthL() is not called after a
						StartValueLength().
	 * @return			Pointer to buffer containing the entire encoded field.
	 *					Responsibility for deallocating the memory is also passed.
	 * @pre 			The function StartHeaderL should have been called.
	 * @post			Encoder is reset ready to be used again.
	 * @leave			leaves, if the new 8 bit heap descriptor cannot be created.
	 */
	IMPORT_C HBufC8* EndHeaderL();


	/**
	 * @fn				AddIntegerL(const TUint aInt)
	 * Intended Usage : Encodes input Integer value and adds it to the encoded field.
	 *					Choice of encoded form dependent on the size of the input.
	 *					Either ShortInt or LongInt method chosen.
	 * @param aInt		Integer value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddIntegerL(const TUint aInt);

	/**
	 * @fn				AddShortIntL(const TUint8 aValue)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP ShortInt method.
	 * @param aValue	value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddShortIntL(const TUint8 aValue);

	/**
	 * @fn				AddShortLengthL(const TUint8 aValue)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					For short length the value must be between octet 0 - 31.
	 * @param aValue	value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory, KErrOverflow if the value is greater than 31
	 */
	IMPORT_C void AddShortLengthL(const TUint8 aValue);

	/**
	 * @fn				AddLongIntL(const TUint32 aValue);
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP LongInt method.
	 * @param aValue	value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddLongIntL(const TUint32 aValue);
	
	/**
	 * @fn				AddUintVarL(const TUint aInt)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP UIntVar method.
	 * @param aInt		value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddUintVarL(const TUint aInt);

	/**
	 * @fn				AddTextStringL(const RString& aText)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP TextString method.
	 * @param aText		value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddTextStringL(const RString& aText);

	/**
	 * @fn				AddTextStringL(const TDesC8& aText)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP TextString method.
	 * @param aText		value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddTextStringL(const TDesC8& aText);

	/**
	 * @fn				AddDateL(const TDateTime aDate)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP Date method.
	 * @param aDate		value to be encoded.
	 * @pre				StartHeaderL needs to have been called.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddDateL(const TDateTime aDate);

	/**
	 * @fn				AddTokenL(const TUint8 aToken)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Adds value as-is to the encoded field.
	 * @param aToken	parameter added without encodeing. Should be a valid
	 *					WSP token, a 8 bit number > 0x7F (i.e. top bit set)
	 * @pre 			StartHeaderL and StartValueLengthL should have been called.
	 * @post			EndValueLengthL needs to be called subsequently.
	 */
	IMPORT_C void AddTokenL(const TUint8 aToken);

	/**
	 * @fn				AddTokenTextL(const TDesC8& aTokenText)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Encodes parameter value using WSP TokenText method.
	 * @param aToken	value to be encoded.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddTokenTextL(const TDesC8& aTokenText);

	/**
	 * @fn				AddDataL(const TDesC8& aData)
	 * Intended Usage : Encodes input and adds it to the encoded field.
	 *					Adds value as-is to the encoded field.
	 * @param aData		value to be encoded.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void AddDataL(const TDesC8& aData);

	/**
	 * @fn				StartValueLengthL()
	 * Intended Usage : From calling this function, the length in bytes of all
	 *					encodings added subsequently will be calculated and stored
	 *                  as part of the encoded string, as specified in WSP spec.
	 *					Can be nested. i.e.
	 *						 encoder->StartHeaderL();
	 *						 encoder->StartValueLengthL();
	 *						 encoder->StartValueLengthL();
	 *						 encoder->AddLongIntL();
	 *						 encoder->EndValueLengthL();
	 *						 encoder->AddTextStringL();
	 *						 encoder->EndValueLengthL();
	 *						 HBufC8* output = encoder->EndHeaderL();
	 *
	 * @pre 			StartHeaderL should have been called.
	 * @post			EndValueLengthL needs to be called subsequently.
	 * @leave			KErrNoMemory
	 */

	IMPORT_C void StartValueLengthL();

	/**
	 * @fn				EndValueLengthL()
	 * Intended Usage : Needs to be called at the point in the construction of 
	 *					a header when ValueLength can be calculated.
	 * @pre 			StartHeaderL and StartValueLengthL should have been called.
	 * @post			ValueLength has been calculated and added, together with the
	 *					encoded header, to the internal representation of the header buffer.
	 * @leave			KErrNoMemory
	 */
	IMPORT_C void EndValueLengthL();

private:
	/** Default constructor. */
	CWspHeaderEncoder();

	void Init();

	/** Standard second phase construction. */
	void ConstructL();

private:
	/**
	Array for storing the partial encoded header.
	Each time StartValueLength is called a new array
	element is used. When EndValueLength is called,
	the array is decremented, data from the last 
	element being added to the one before.
	*/
	RPointerArray<CDesC8Array> iArray;

	/**
	Value incremented as the encoded header increases in size.
	Used to allocate the buffer for storing the final	
	encoded header, output when EndHeader is called.
	*/
	TInt iTotalLength;
	};

/** 
 *  Class encapsulating primitive encoding methods which are defined in the WSP standard.
 *  Input will be encoded and returned in an 8 bit buffer.
 *  
 */
class TWspPrimitiveEncoder
	{
public:
	/**
	 * @fn				ShortInt(const TUint8 aValue)
	 * Intended Usage : Takes a TUint8 parameter, and sets the top bit.
	 *					As specified for the WSP ShortInt encoding method.
	 * @param 			aValue number to be encoded.
	 * @return 			Output, encoded as a TUint8, representation of the header buffer.
	 *					If input greater that 127 (invalid input), returns 0
	 */
	IMPORT_C static TUint8  ShortInt(const TUint8 aValue);

	/**
	 * @fn				LongIntL(const TUint32 aValue)
	 * Intended Usage : Takes a TUint32 parameter and encodes it using 
	 *					the WSP specified LongInt method.
	 * @param 			aValue number to be encoded.
	 * @return 			Output, encoded HBufC8 buffer. 
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static HBufC8* LongIntL(const TUint32 aValue);

	/**
	 * @fn				UintVarL(const TUint32 aInt)
	 * Intended Usage : Takes a TUint32 parameter and encodes it using 
	 *					the WSP specified UintVar method.
	 * @param 			aInt number to be encoded.
	 * @return 			Output, encoded HBufC8 buffer. 
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static HBufC8* UintVarL(const TUint32 aInt);

	/**
	 * @fn				TextStringL(const RString aText)
	 * Intended Usage : Takes a RString parameter and encodes it using 
	 *					the WSP specified TextString method.
	 * @param 			aText string to be encoded.
	 * @return 			Output, encoded HBufC8 buffer. 
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static HBufC8* TextStringL(const RString aText);

	/**
	 * @fn				TextStringL(const TDesC8& aText)
	 * Intended Usage : Takes a TDesC8 parameter and encodes it using 
	 *					the WSP specified TextString method.
	 * @param 			aText string to be encoded.
	 * @return 			Output, encoded HBufC8 buffer. 
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static HBufC8* TextStringL(const TDesC8& aText);

	/**
	 * @fn				DateL(const TDateTime aDate)
	 * Intended Usage : Takes a TDateTime parameter and encodes it using 
	 *					the WSP specified Date encoding method.
	 * @param 			aDate value to be encoded.
	 * @return 			Output, encoded HBufC8 buffer. 
	 * @leave			KErrNoMemory
	 */
	IMPORT_C static HBufC8* DateL(const TDateTime aDate);
	};

#endif	// __WSPENCODER_H__