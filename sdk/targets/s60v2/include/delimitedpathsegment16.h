// DelimitedPathSegment16.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __DELIMITEDPATHSEGMENT16_H__
#define __DELIMITEDPATHSEGMENT16_H__

/**
	@file DelimitedPathSegment16.h
	Comments :	This file contains the API definition for the classes TDelimitedPathSegmentParser16
				and CDelimitedPathSegment16.
 */

// System includes
//
#include <e32base.h>

// Local includes
//
#include "delimitedparser16.h"

class TDelimitedPathSegmentParser16 : public TDelimitedParserBase16
/**
@class TDelimitedPathSegmentParser16
Dependencies : TDelimitedParserBase16
Comments : Derived class from TDelimitedParserBase providing a class for parsing path segments
delimited by '/' as defined in RFC2396.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				TDelimitedPathSegmentParser16()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedPathSegmentParser16();

/**
	@fn				Parse(const TDesC16& aPathSegment)
	Intended Usage	:	This parses the descriptor into path segment segments from left to right.
	@since			6.0
	@param			aPathSegment	A descriptor containing the path segment.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataFroward).
 */
	IMPORT_C void Parse(const TDesC16& aPathSegment);

/**
	@fn				ParseReverse(const TDesC16& aPathSegment)
	Intended Usage	:	This parses the descriptor into path segment segments from right to left.
	@since			6.0
	@param			aPathSegment	A descriptor containing the path segment.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC16& aPathSegment);
	};

class CDelimitedPathSegment16 : public CDelimitedDataBase16
/**
@class CDelimitedPathSegment16
Dependencies : CDelimitedStringBase16
Comments : Provides functionality to create a delimited path segment where components of the 
path segment delimited by '/' as defined in RFC2396.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				NewL(const TDesC16& aPathSegment)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves nothing
	on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPathSegment	A descriptor with the initial path segment.
	@return			A pointer to created object.
	@post			Nothing left on the CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPathSegment16* NewL(const TDesC16& aPathSegment);

/**
	@fn				NewLC(const TDesC16& aPathSegment)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves a
	pointer to created object on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPathSegment	A descriptor with the initial path segment.
	@return			A pointer to created object.
	@post			Pointer to created object left of CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPathSegment16* NewLC(const TDesC16& aPathSegment);

/**
	@fn				~CDelimitedPathSegment16()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedPathSegment16();

/**
	@fn				InsertAndEscapeCurrentL(const TDesC16& aParam)
	Intended Usage	:	Escape encodes the parameter then inserts the escaped version
	in a position before the current parsed parameter. The new parameter should only 
	contain a single path segment parameter, as any parameter delimiters in the 
	parameter will be converted to an escape triple. The parser is left in a state 
	where its current parameter is the same one as before the insertion.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aParam	A descriptor with the unescaped path segment parameter
	@pre 			The path segment must have been initially parsed.
	@post			The path segment will have been extended to include the new 
	parameter. The current segment will remain as the one before the insertion.
 */
	IMPORT_C void InsertAndEscapeCurrentL(const TDesC16& aParam);

/**
	@fn				PushAndEscapeFrontL(const TDesC16& aParam)
	Intended Usage	:	Escape encodes the parameter then inserts the escaped version
	at the front of the path segment. The new parameter should only contain a single 
	path segment parameter, as any parameter delimiters in the parameter will be 
	converted to an escape triple. The parser is left in a state where its current 
	parameter is the same one as before the insertion.
	@exception		KErrNoMemory.
	@warning		A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aParam	A descriptor with the unescaped path segment parameter
	@pre 			The path segment must have been initially parsed.
	@post			The path segment will have been extended to include the new 
	parameter. The current segment will remain as the one before the insertion.
 */
	IMPORT_C void PushAndEscapeFrontL(const TDesC16& aParam);

/**
	@fn				PushAndEscapeBackL(const TDesC16& aParam)
	Intended Usage	:	Escape encodes the parameter then inserts the escaped version
	at the back of the path segment. The new parameter should only contain a single 
	path segment parameter, as any parameter delimiters in the parameter will be 
	converted to an escape triple. The parser is left in a state where its current 
	parameter is the same one as before the insertion.
	@exception		KErrNoMemory.
	@warning		A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aParam	A descriptor with the unescaped path segment parameter.
	@pre 			The path segment must have been initially parsed.
	@post			The path segment will have been extended to include the new 
	parameter. The current segment will remain as the one before the insertion.
 */
	IMPORT_C void PushAndEscapeBackL(const TDesC16& aParam);

private:	// Methods

/**
	@fn				CDelimitedPathSegment16()
	Intended Usage	:	Constructor. First phase of two-phase construction method. 
	Does non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	CDelimitedPathSegment16();

/**
	@fn				ConstructL(const TDesC16& aPathSegment)
	Intended Usage	:	Second phase of two-phase construction method. Does any allocations 
	required to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPathSegment	A descriptor with the initial path segment.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	void ConstructL(const TDesC16& aPathSegment);

	};

typedef TDelimitedPathSegmentParser16	TDelimitedPathSegmentParser;
typedef CDelimitedPathSegment16			CDelimitedPathSegment;

#endif	// __DELIMITEDPATHSEGMENT16_H__
