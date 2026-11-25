// DelimitedPathSegment8.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __DELIMITEDPATHSEGMENT8_H__
#define __DELIMITEDPATHSEGMENT8_H__

/**
	@file DelimitedPathSegment8.h
	Comments :	This file contains the API definition for the classes TDelimitedPathSegmentParser8
				and CDelimitedPathSegment8. 
 */

// System includes
//
#include <e32base.h>

// Local includes
//
#include "DelimitedParser8.h"

/**
	@class TDelimitedPathSegmentParser8
	Dependencies : TDelimitedParserBase8
	Comments : Derived class from TDelimitedParserBase providing a class for parsing 
	path segments delimited by a ';' as defined in RFC2396.
	@public
	@since 6.0
 */
class TDelimitedPathSegmentParser8 : public TDelimitedParserBase8
	{
public:	// Methods

/**
	@fn				TDelimitedPathSegmentParser8()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedPathSegmentParser8();

/**
	@fn				Parse(const TDesC8& aPathSegment)
	Intended Usage	:	This parses the descriptor into path segment parameters from
	left to right.
	@since			6.0
	@param			aPathSegment	A descriptor containing the path segment.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataForward).
 */
	IMPORT_C void Parse(const TDesC8& aPathSegment);

/**
	@fn				ParseReverse(const TDesC8& aPathSegment)
	Intended Usage	:	This parses the descriptor into path segment parameters from 
	right to left.
	@since			6.0
	@param			aPathSegment	A descriptor containing the path segment.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC8& aPathSegment);
	};

/**
	@class CDelimitedPathSegment8
	Dependencies : CDelimitedStringBase8
	Comments : Provides functionality to create a delimited path segment where components of the 
	path segment delimited by '/' as defined in RFC2396.
	@public
	@since 6.0
 */
class CDelimitedPathSegment8 : public CDelimitedDataBase8
	{
public:	// Methods

/**
	@fn				NewL(const TDesC8& aPathSegment)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves nothing
	on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPathSegment	A descriptor with the initial path segment.
	@return			A pointer to created object.
	@post			Nothing left on the CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPathSegment8* NewL(const TDesC8& aPathSegment);

/**
	@fn				NewLC(const TDesC8& aPathSegment)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves a
	pointer to created object on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPathSegment	A descriptor with the initial path segment.
	@return			A pointer to created object.
	@post			Pointer to created object left of CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPathSegment8* NewLC(const TDesC8& aPathSegment);

/**
	@fn				~CDelimitedPathSegment8()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedPathSegment8();

/**
	@fn				InsertAndEscapeCurrentL(const TDesC8& aParam)
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
	IMPORT_C void InsertAndEscapeCurrentL(const TDesC8& aParam);

/**
	@fn				PushAndEscapeFrontL(const TDesC8& aParam)
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
	IMPORT_C void PushAndEscapeFrontL(const TDesC8& aParam);

/**
	@fn				PushAndEscapeBackL(const TDesC8& aParam)
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
	IMPORT_C void PushAndEscapeBackL(const TDesC8& aParam);

private:	// Methods

/**
	@fn				CDelimitedPathSegment8()
	Intended Usage	:	Constructor. First phase of two-phase construction method. Does
	non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	CDelimitedPathSegment8();

/**
	@fn				ConstructL(const TDesC8& aPathSegment)
	Intended Usage	:	Second phase of two-phase construction method. Does any allocations required
	to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPathSegment	A descriptor with the initial path segment.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	void ConstructL(const TDesC8& aPathSegment);

	};

#endif // __DELIMITEDPATHSEGMENT8_H__