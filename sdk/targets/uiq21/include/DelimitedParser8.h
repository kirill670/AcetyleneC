// DelimitedParser8.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file DelimitedParser8.h
	Comments :	This file contains the API definition for the classes TDelimitedParserBase8
				and CDelimitedData8. 
 */

#ifndef __DELIMITEDPARSER8_H__
#define __DELIMITEDPARSER8_H__

// System includes
//
#include <e32base.h>

// Local includes
//
#include "DelimitedParserCommon.h"

/**
	@class TDelimitedParserBase8

  Comments : Provides non-modifying functionality for parsing data delimited by 
	a single character. The data is delimited into segments. Uses 8-bit descriptors.

	The object contains a descriptor with the data which can be parsed from left 
	to right, or right to left. It is non-owning. The current segment can be extracted, 
	which then parses the string for the next segment.
	
	This is a base class and an object of this type cannot be instantiated. It should
	be derived. The derived class should ensure that the data iDataDes is set before 
	calling one of the protected parsing functions. The derived class should also ensure 
	that the delimiting character has been set.
	
	If the data iDataDes has not been parsed, then calling any functionality that 
	requires the data to have been parsed will result in a panic 
	KDelimitedParserErrNotParsed. The data can only be parsed by calling one of the
	protected parsing functions from the derived class.
	
	If the delimiting character iDelimiter has not been set, then calling the protected
	parsing functions and some of the other public functionality that requires the 
	delimiter to be set will result in a panic KDelimitingParserErrNoDelimiter.
	@public
	@since 6.0
	@lib euser.lib
 */
class TDelimitedParserBase8
	{
public:	// Methods

/**
	@fn				GetNext(TPtrC8& aSegment) const
	Intended Usage	:	Retrieves the current segment and then parses the data to the
	next one.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@param			aSegment	This is an output argument that is set to the current segment.
	@return			A error value of KErrNotFound if there is current segment. The 
	value KErrNone if there is a current segment.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
	@post			The current segment is updated to the next one.
 */
	IMPORT_C TInt GetNext(TPtrC8& aSegment) const;

/**
	@fn				Inc() const
	Intended Usage	:	Parses to the next segment.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@return			A error value of KErrNotFound if there is current segment. The 
	value KErrNone if there is a current segment.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
	@post			The current segment is updated to the next one.
 */	
	IMPORT_C TInt Inc() const;

/**
	@fn				Dec() const
	Intended Usage	:	Parses back to the previous segment.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@return			A error value of KErrNotFound if the current segment is the initial 
	segment. The value KErrNone if the data has been parsed to the previous segment.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
	@post			If the parse was successful then the  current segment is updated 
	to the previous one. Otherwise there is no change.
 */
	IMPORT_C TInt Dec() const;

/**
	@fn				Peek(TPtrC8& aSegment) const
	Intended Usage	:	Retrieves the current segment.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@param			aSegment	This is an output argument that is set to the current segment.
	@return			A error value of KErrNotFound if there is current segment. The 
	value KErrNone if there is a current segment.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
 */
	IMPORT_C TInt Peek(TPtrC8& aSegment) const;

/**
	@fn				Eos() const
	Intended Usage	:	Indicates whether the end of the data has been reached and 
	there are no more segments to parse.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@return			A boolean value of ETrue if the end of the data has been reached,
	or EFalse if there are more segements to parse.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
 */
	IMPORT_C TBool Eos() const;

/**
	@fn				FrontDelimiter() const
	Intended Usage	:	Checks for a delimiter at the front (left) of the data.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@return			A boolean of value ETrue if there is a front delimiter, or EFalse 
	if there is no front delimiter.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
 */
	IMPORT_C TBool FrontDelimiter() const;

/**
	@fn				BackDelimiter() const
	Intended Usage	:	Checks for a delimiter at the back (right) of the data.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@return			A boolean of value ETrue if there is a back delimiter, or EFalse 
	if there is no back delimiter.
	@pre 			The string must have been initially parsed by Parse() or ParseReverse(). 
 */
	IMPORT_C TBool BackDelimiter() const;

/**
	@fn				Des() const
	Intended Usage	:	Retrieves the descriptor reference with the data
	@since			6.0
	@return			A const descriptor reference with the data.
 */
	IMPORT_C const TDesC8& Des() const;

/**
	@fn				Remainder(TPtrC8& aRemainder) const
	Intended Usage	:	Gives the remainder of the data from (and including) the current
	segment. Any other segments that have parsed through are not included.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@param			aRemainder	This is an output argument that is set to the remaining data.
	@return			An error value of KErrNotFound if there is no remaining data, or 
	value of KErrNone if there is remaining data.
	@pre 			The data must have been initially parsed by Parse() or ParseReverse().
 */
	IMPORT_C TInt Remainder(TPtrC8& aRemainder) const;

protected:	// Methods

/**
	@fn				TDelimitedParserBase8()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedParserBase8();

/**
	@fn				Parse(const TDesC8& aData)
	Intended Usage	:	This parses the data into segments from left to right.
	@warning		There will be a KDelimitedParserErrNoDelimiter panic if the delimiter
	has not been set.
	@since			6.0
	@param			aData	A descriptor containing the data.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataFroward).
 */
	IMPORT_C void Parse(const TDesC8& aData);

/**
	@fn				ParseReverse(const TDesC8& aData)
	Intended Usage	:	This parses the data into segments from lright to left.
	@warning		There will be a KDelimitedParserErrNoDelimiter panic if the delimiter
	has not been set.
	@since			6.0
	@param			aData	A descriptor containing the data.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC8& aData);

/**
	@fn				SetDelimiter(TChar aDelimiter)
	Intended Usage	:	Sets the delimiting character.
	@since			6.0
	@param			aDelimiter	The delimiting character.
	@post			The delimiting character is set.
 */
	IMPORT_C void SetDelimiter(TChar aDelimiter);

private:	// Methods

/**
	@fn				DoParse(const TDesC8& aData)
	Intended Usage	:	Initialises the parsing of the data.
	@since			6.0
	@param			aData	A descriptor reference with the data.
	@pre 			The delimiting character has been set.
	@post			The data descriptor is set to the input argument. The current 
	segment refers to the initial segment of the data.
 */
	void DoParse(const TDesC8& aData);

/**
	@fn				FindNextSegment(TInt aStartPos) const
	Intended Usage	:	Finds the next segment from the given start position.
	@since			6.0
	@param			aStartPos	The position from where to start the search for the
	next segment.
	@return			The position of delimiter after the specified start position, or 
	an error value of KErrNotFound if no more delimiters are found.
 */
	TInt FindNextSegment(TInt aStartPos) const;

/**
	@fn				FindPrevSegment(TInt aStartPos) const
	Intended Usage	:	Finds the previous segment from the given start position.
	@since			6.0
	@param			aStartPos	The position from where to start the search for the
	previous segment.
	@return			The position of delimiter before the specified start position, or 
	an error value of KErrNotFound if no more delimiters are found.
*/
	TInt FindPrevSegment(TInt aStartPos) const;

private:	// Attributes

	/** Descriptor with the string
	 */
	TPtrC8						iDataDes;

	/** Descriptor with the current segment.
	 */
	mutable TPtrC8				iCurrentSegment;

	/** Position of next segment.
	 */
	mutable TInt				iNextSegmentPos;

	/** Direction of parsing.
	 */
	TDelimitedDataParseMode		iMode;

	/** Delimiting character
	*/
	TInt						iDelimiter;

/**
	A friend class.
	@see		CDelimitedDataBase8
	@since		6.0
	@cat		Friend class
 */
	friend class CDelimitedDataBase8;

	};

/**
	@class CDelimitedDataBase8
	Dependencies : CBase, TDelimitedParserBase8
	Comments : Provides functionality for creating and editing a delimited data object.
	Uses 8-bit descriptors
	
	The object contains a descriptor buffer with the data. Functionality is provided 
	to allow segments to be added or removed from the data. There is access to the 
	internal delimited data parser to provide parsing functionality to be excercised 
	on the created data.

	This a base class that cannot be instantiated. It should be derived. The derived 
	class must set the delimited data parser, which is an object derived from 
	TDelimitedParserBase. This helper class must set the delimiting object

	If the delimiting character has not been set, then calling any of the functionality 
	will cause a panic KDelimitedParserErrNoDelimiter.
	@public
	@since 6.0
	@lib euser.lib
 */
class CDelimitedDataBase8 : public CBase
	{
public: // Methods

/**
	@fn				~CDelimitedDataBase8()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedDataBase8();

/**
	@fn				InsertCurrentL(const TDesC8& aSegment)
	Intended Usage	:	Inserts the new segment in a position before the current parsed
	segment. The new segment can be made up of several segments and have delimiters at 
	either extreme. The insert functionality will ensure that there is always a 
	delimiter at the front of the new segment. The parser is left in a state where its
	current segment is the same one as before the insertion.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@param			aSegment	A descriptor with the new segment to be inserted.
	@pre 			The data must have been initially parsed by Parse() or ParseReverse().
	@post			The data will have been extended to include the new segment. The 
	current segment will remain as the one before the insertion.
 */
	IMPORT_C void InsertCurrentL(const TDesC8& aSegment);

/**
	@fn				RemoveCurrentL()
	Intended Usage	:	Removes the current segment. After removing the segment, the 
	parser's new current segment will be the next segment. If the last segment is the 
	one that is removed then the parser will be set to the end of the data.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set.
	@since			6.0
	@pre 			The data must have been initially parsed by Parse() or ParseReverse().
	@post			The data will have been reduced to exclude the removed segment.
	The current segment will be set to what was the next segment. If the removed segment 
	was the last segment, the parser is at the end of the data.
 */
	IMPORT_C void RemoveCurrentL();

/**
	@fn				PushBackL(const TDesC8& aSegment)
	Intended Usage	:	Adds a new segment to the end of the data. The new segment 
	can be made up of several segments and have  delimiters at either extreme. The 
	insert functionality will ensure that there is always a delimiter at the front 
	of the new segment. The data must re-parsed to ensure that the parser is valid.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aSegment	A descriptor with the new segment to be inserted.
	@pre 			The delimiter must have been set. 
	@post			The data will have been extended to include the new segment.
 */
	IMPORT_C void PushBackL(const TDesC8& aSegment);

/**
	@fn				PopBackL()
	Intended Usage	:	Removes the last segment from the data. The data must be
	re-parsed to ensure that the parser is valid.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The data will have been reduced to exclude the last segment. 
 */
	IMPORT_C void PopBackL();

/**
	@fn				PushFrontL(const TDesC8& aSegment)
	Intended Usage	:	Adds a new segment to the front of the data. The new segment 
	can be made up of several segments and have  delimiters at either extreme. The 
	insert functionality will ensure that there is always a delimiter at the front 
	of the new segment. The data must re-parsed to ensure that the parser is valid.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aSegment	A descriptor with the new segment to be inserted.
	@pre 			The delimiter must have been set. 
	@post			The data will have been extended to include the new segment.
 */
	IMPORT_C void PushFrontL(const TDesC8& aSegment);

/**
	@fn				PopFrontL()
	Intended Usage	:	Removes the first segment from the data. The data must be
	re-parsed to ensure that the parser is valid.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The data will have been reduced to exclude the last segment. 
 */
	IMPORT_C void PopFrontL();

/**
	@fn				TrimFrontDelimiterL()
	Intended Usage	:	Removes the front delimiter (if exists) from the data.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The data might have been reduced to exclude the front delimiter. 
 */
	IMPORT_C void TrimFrontDelimiterL();

/**
	@fn				AddFrontDelimiterL()
	Intended Usage	:	Adds a delimiter to the front of the data (if it doesn't exist).
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The data might have been extended to include a front delimiter. 
 */
	IMPORT_C void AddFrontDelimiterL();

/**
	@fn				TrimBackDelimiterL()
	Intended Usage	:	Removes the back delimiter (if exists) from the data.
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The data might have been reduced to exclude the front delimiter. 
 */
	IMPORT_C void TrimBackDelimiterL();

/**
	@fn				AddBackDelimiterL()
	Intended Usage	:	Adds a delimiter to the back of the data (if it doesn't exist).
	@exception		KErrNoMemory.
	@warning		There will be a KDelimitedParserErrNotParsed panic if the data has 
	not been parsed, and a KDelimitedParserErrNoDelimiter panic if the delimiter has 
	not been set. A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The data might have been extended to include a front delimiter. 
 */
	IMPORT_C void AddBackDelimiterL();

/**
	@fn				Parse()
	Intended Usage	:	This parses the data into segments from left to right.
	@warning		There will be a KDelimitedParserErrNoDelimiter panic if the delimiter
	has not been set.
	@since			6.0
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataFroward).
 */
	IMPORT_C void Parse();

/**
	@fn				ParseReverse()
	Intended Usage	:	This parses the string into segments from right to left.
	@since			6.0
	@pre 			The delimiter must have been set. Will get a KDelimitedParserErrNoDelimiter panic if 
	the delimiter has not been initialized.
	@post			The current segment is the leftmost segment and the direction of parsing is right to left.
 */
	IMPORT_C void ParseReverse();

/**
	@fn				Parser() const
	Intended Usage	:	Retrieves a const reference to the delimited data parser. 
	@since			6.0
	@return			A const reference to the delimited data parser. 
 */
	IMPORT_C const TDelimitedParserBase8& Parser() const;

protected:	// Methods

/**
	@fn				CDelimitedDataBase8()
	Intended Usage	:	Constructor. First phase of two-phase construction method. 
	Does non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C CDelimitedDataBase8();

/**
	@fn				ConstructL(const TDesC8& aData)
	Intended Usage	:	Second phase of two-phase construction method. Does any 
	allocations required to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aData	A descriptor with the initial string.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	IMPORT_C void ConstructL(const TDesC8& aData);

/**
	@fn				SetDelimiter(TChar aDelimiter)
	Intended Usage	:	Sets the delimiting character.
	@since			6.0
	@param			aDelimiter	The delimiting character.
	@post			The delimiting character is updated.
 */
	IMPORT_C void SetDelimiter(TChar aDelimiter);

private:	// Methods

/**
	@fn				SetDataL(const TDesC8& aData)
	Intended Usage	:	Updates internal data buffer with the new data. Creates a copy
	of the new data.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aData	A descriptor with the new string.
	@post			The internal data buffer now contains a copy of the new data and the 
	parser is set to the new data.
 */
	void SetDataL(const TDesC8& aData);

/**
	@fn				SetData(HBufC8* aDataBuf)
	Intended Usage	:	Sets internal data buffer and parser. Cleans up the old data and 
	uses the data buffer. The parser is set to the new data.
	@since			6.0
	@param			aDataBuf	A pointer to a decriptor buffer with the new data.
	@post			The internal data buffer now points to the new buffer and the parser 
	is set to the data in the new buffer..
 */
	void SetData(HBufC8* aDataBuf);

/**
	@fn				DoInsertL(const TDesC8& aSegment)
	Intended Usage	:	Inserts the new segment in a position before the current segment. 
	The new segment can be made up of several segments and have delimiters at either extreme.
	The insert functionality will ensure that there is always a delimiter at the front of the
	new segment. The parser will be left in a state where its current segment is the same one
	as before the insertion.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aSegment	The descriptor with the segment to be inserted.
	@pre 			The string must have been parsed.
	@post			The string will have been extended to include the new segment. The current segment will
	remain as the one before the insertion.
 */
	void DoInsertL(const TDesC8& aSegment);

/**
	@fn				DoRemoveL()
	Intended Usage	:	Removes the current segment. After removing the segment, the 
	parser's new current segment will be the next segment. If the last segment is the 
	one that is removed then the parser will be set to the end of the data.
	@exception		KErrNoMemory.
	@since			6.0
	@pre 			The data must have been parsed.
	@post			The data will have been reduced to exclude the removed data. The 
	current segment is set to what was the next segment. If the removed segment was 
	the last segment, the parser is at the end of the data.
 */
	void DoRemoveL();

private:	// Attributes

	/** Descriptor buffer.
	 */
	HBufC8*					iDataBuf;

	/** Parser object
	 */
	TDelimitedParserBase8	iParser;

	};

#endif	// __DELIMITEDPARSER8_H__