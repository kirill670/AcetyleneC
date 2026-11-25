// WSPDecoder.h
//
// Copyright © 2001 Symbian Ltd. All rights reserved.

#ifndef	__WSPDECODER_H__
#define	__WSPDECODER_H__

#include <e32base.h>
#include <stringpool.h>


/** 
* This file contains the following classes:
*	TWspField 
*	TWspHeaderSegmenter 
*	TWspPrimitiveDecoder  
*	
*/


enum TWspDecoderPanic
	{
	EWspDecoderLongIntOverflow,
	EWspDecoderDateOverflow
	};


/**
 * TWspField class holds the pair <HeaderName, ValueBuffer>
 * This is a simple class that associates these values.
 * No ownership is handed to this class.  It is up to user of this class to
 * open and close all resources used.
 */ 
class TWspField 
	{
public:
	/**
	* Default constructor
	*/
	inline TWspField();

	/**
	* Constructor
	* @param aHdrName: In - The Header Name.  This must be an opened RStringF
	* @param aValBuf: In - the Buffer containing the header value in its raw format
	*/
	inline TWspField(RStringF aHdrName, TPtrC8 aValBuf);

	/**
	The header name of a opened RStringF - *Not Owned*
	This is externally opened.  It must be externally 
	closed.
	*/
	RStringF iHdrName;
	/* The raw value buffer - Note: Not owned by this */
	TPtrC8	 iValBuffer;
	};

/** 
* TWspHeaderSegmenter segments a WSP buffer into WSP header/value pairs.  
* It detects boundaries between header/values based on the WAP-WSP spec.
*	* To construct, buffer and string pool is passed in
*	* Call to NextL() to iterate through the buffer - this returns a TWspField
*   * NextL() returns KErrNotFound when done
* 
*/ 
class TWspHeaderSegmenter
	{
public:
	/**
	* Constructor
	* @param aPool: In - an opened RStringPool - owned by the caller
	* @param aStringTable: In - the string table in the string pool to use
	* @param aBuffer: In - the buffer containing the WSP header data - owned by the caller
	* @pre The string table must be opened with the WSP Sting constants table
	*/
	inline TWspHeaderSegmenter(RStringPool aPool, const TStringTable& aStringTable, TPtrC8 aBuffer); 

	/**
	* NextL iterates through the buffer.  Each call returns a TWspField in the paramater.
	* @param aWspHeader: Out - a TWspField containing the header <name,value> pair.  
	* @warning The TWspField::iHdrName will be opened internally.
	*			It must be closed by the caller before this class is destroyed.
	* @return	KErrNone if next field is returned
	*			KErrNotFound at the end of the buffer - no TWspField param returned
	*			KErrCorrupt if segmenting does not parse correctly
	* @Leave	StringPool leave code if opening string fails.
	*/
	IMPORT_C TInt NextL(TWspField& aWspHeader);

	/**
	* Offset	returns the current offset into the buffer being parsed.
	* @return	TInt offset value. It will point to beginning of next segmented field.
	*			If NextL has not been called it will be set to 0. The beginning of the buffer.
	*			If buffer has been completely parsed, will return KErrNotFound.
	*/
	inline TInt Offset() const;

private:
	/** Raw buffer that will be segmented - Not Owned */
	TPtrC8		iBuffer;

	/** Segment offset into the buffer. */
	TInt		iOffset;

	/** Opened string pool to use with the string table already loaded - Not Owned */
	RStringPool iPool;

	/** The string table to use in the string pool - Not Owned */
	const TStringTable& iStringTable;
	};


/** 
*	Decoder for WSP Primitves - WAP-WSP Section 8.4.1
*/ 
class TWspPrimitiveDecoder 
	{
  public:

	/**
	* TWspHeaderType describe the types from WAP-WSP Section 8.4.1.2
	*/
	 enum TWspHeaderType
		{
		ENotSet,		// The type has not been set
		ELengthVal,		// 0-31 -  octet is a value length
		EQuotedString,	// 34 - value is a quoted text string, terminated by a '\0'
		EString,		// 32-127 - value is a text string, terminated by a '\0' 
		E7BitVal		// 128-255 - encoded 7 bit value, this header has no more data
		};

			
	/**
	* Constructor
	* @param aBuffer: In - the buffer containing the value in its raw format
	*/
	inline TWspPrimitiveDecoder(TPtrC8 aBuffer);
	
	/**
	* Looks at the byte currently pointed at in this buffer and returns the type.
	* @return TWspHeaderType - the type of this data octet
	*/
	IMPORT_C TWspHeaderType VarType() const;
	
	/**
	* LengthVal() returns length of the data following this byte.  
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::ELengthVal
	* @post internal offset gets updated to move past this primitive 
	* @param aVal: Out - the length encoded in this byte that indicates the size of the
	*			   data that follows.
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt LengthVal(TInt& aVal);
	
	/**
   	* String() returns a TPtrC holding the string the buffer currently points at without 
   	* the NULL termination. If the String type is a quoted string then the quotes are not
	* included in the returned buffer.
   	* @pre iBuffer[iOffset] must be valid, VarType() == TWspType::EString
   	* @post internal offset gets updated to move past this primitive 
   	* @param aString: Out - the string
   	* @return postive number indicating the number of bytes read from the buffer
   	*		  KErrCorrupt if data is not formatted correctly.
   	*/
	IMPORT_C TInt String(TPtrC8& aString);

	/**
	* Val7Bit() returns a token, a short int or an octet value with the top bit cleared
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::E7BitVal
	* @post internal offset gets updated to move past this primitive 
	* @param aVal: Out - the 7 bit value with top bit cleared
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt Val7Bit(TUint8& aVal);

	/**
	* Integer() returns an Integer - could be short or long.
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::ELengthVal or
	*	   VarType() == TWspHeaderType::E7BitVal
	* @post internal offset gets updated to move past this primitive 
	* @param aVal: Out - the long int
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt Integer(TUint32& aVal);

	/**
	* LongInt() returns a long int the buffer is currently pointing at. 
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::ELengthVal  
	* @post internal offset gets updated to move past this primitive 
	* @param aVal: Out - the long int
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt LongInt(TUint32& aVal);

	/**
	* UintVar() returns a TUint32 
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::ELengthVal or
	*	   VarType() == TWspHeaderType::E7BitVal 
	* @post internal offset gets updated to move past this primitive 
	* @param aVal: Out - the TUint32 decoded 
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt UintVar(TUint32& aVal);

	/**
	* Version() returns a formatted version string 
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::ELengthVal  
	* @post internal offset gets updated to move past this primitive 
	* @param aPool: In - an opened string pool
	* @param aVer: Out - a formatted version string.  Caller must close this string.
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt VersionL(RStringPool aPool, RStringF& aVer);

	/**
	* Date() returns a TDateTime offset from January 1, 1970 - WAP WSP Section 8.4.2.3 
	* Panics if the time val is greater then the maximum allowable integer size (32 bits).
	* @pre iBuffer[iOffset] must be valid, VarType() == TWspHeaderType::ELengthVal  
	* @post internal offset gets updated to move past this primitive 
	* @param aDateTime: Out - a WAP Date
	* @return postive number indicating the number of bytes read from the buffer
	*		  KErrCorrupt if data is not formatted correctly.
	*/
	IMPORT_C TInt Date(TDateTime& aDateTime);
  
  private:
	/** The raw buffer */
	TPtrC8 iBuffer;

	/** The current offset */
	TInt   iOffset;
	};

//	Inlines

inline TWspField::TWspField()
	{
	}


inline TWspField::TWspField(RStringF aHdrName, TPtrC8 aValBuf) : 
		iHdrName(aHdrName), 
		iValBuffer(aValBuf) 
	{
	}


inline TWspHeaderSegmenter::TWspHeaderSegmenter(RStringPool aPool, const TStringTable& aStringTable, TPtrC8 aBuffer) : 
		iBuffer(aBuffer), 
		iOffset(0),
		iPool(aPool),
		iStringTable(aStringTable)
	{
	}

inline TInt TWspHeaderSegmenter::Offset() const
	{
	return (iOffset < iBuffer.Length()) ? iOffset : KErrNotFound;	
	}

inline TWspPrimitiveDecoder::TWspPrimitiveDecoder(TPtrC8 aBuffer) : 
		iBuffer(aBuffer), 
		iOffset(0) 
	{
	}


#endif // __WSPDECODER_H__


