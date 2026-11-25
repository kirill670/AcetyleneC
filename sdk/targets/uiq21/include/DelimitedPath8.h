// DelimitedPath8.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __DELIMITEDPATH8_H__
#define __DELIMITEDPATH8_H__

/**
	@file DelimitedPath8.h
	Comments :	This file contains the API definition for the classes 
				TDelimitedPathParser8 and CDelimitedPath16. 
 */

// System includes
//
#include <e32base.h>

// Local includes
//
#include "DelimitedParser8.h"

/**
	@class TDelimitedPathParser8
	Dependencies : TDelimitedParserBase8
	Comments : Derived class from TDelimitedParserBase providing a class for parsing 
	paths delimited by a '/' as defined in RFC2396.
	@public
	@since 6.0
 */
class TDelimitedPathParser8 : public TDelimitedParserBase8
	{
public:	// Methods

/**
	@fn				TDelimitedPathParser8()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedPathParser8();

/**
	@fn				Parse(const TDesC8& aPath)
	Intended Usage	:	This parses the descriptor into path segments from left to right.
	@since			6.0
	@param			aPath	A descriptor containing the path.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataForward).
 */
	IMPORT_C void Parse(const TDesC8& aPath);

/**
	@fn				ParseReverse(const TDesC8& aPath)
	Intended Usage	:	This parses the descriptor into path segments from right to left.
	@since			6.0
	@param			aPath	A descriptor containing the path.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC8& aPath);
	};

/**
	@class CDelimitedPath8
	Dependencies : CDelimitedStringBase8
	Comments : Provides functionality to create a delimited path where components of the 
	path delimited by '/' as defined in RFC2396.
	@public
	@since 6.0
 */
class CDelimitedPath8 : public CDelimitedDataBase8
	{
public:	// Methods

/**
	@fn				NewL(const TDesC8& aPath)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves nothing
	on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPath	A descriptor with the initial path.
	@return			A pointer to created object.
	@post			Nothing left on the CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPath8* NewL(const TDesC8& aPath);

/**
	@fn				NewLC(const TDesC8& aPath)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves a
	pointer to created object on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPath	A descriptor with the initial path.
	@return			A pointer to created object.
	@post			Pointer to created object left of CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPath8* NewLC(const TDesC8& aPath);

/**
	@fn				~CDelimitedPath8()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedPath8();

/**
	@fn				InsertAndEscapeCurrentL(const TDesC8& aSegment)
	Intended Usage	:	Escape encodes the segment then inserts the escaped version in a 
	position before the current parsed segment. The new segment should only contain a
	single path segment, as any path delimiters in the segment will be converted to an
	escape triple. The parser is left in a state where its current segment is the same
	one as before the insertion.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aSegment	A descriptor with the unescaped path segment.
	@pre 			The path must have been initially parsed.
	@post			The path will have been extended to include the new segment. The 
	current segment will remain as the one before the insertion.
 */
	IMPORT_C void InsertAndEscapeCurrentL(const TDesC8& aSegment);

/**
	@fn				PushAndEscapeFrontL(const TDesC8& aSegment)
	Intended Usage	:	Escape encodes the segment then inserts the escaped version at 
	the front of the path. The new segment should only contain a single path segment, 
	as any path delimiters in the segment will be converted to an escape triple. The 
	parser is left in a state where its current segment is the same one as before 
	the insertion.
	@exception		KErrNoMemory.
	@warning		A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aSegment	A descriptor with the unescaped path segment.
	@pre 			The delimiter must have been set. 
	@post			The path will have been extended to include the new segment.
 */
	IMPORT_C void PushAndEscapeFrontL(const TDesC8& aSegment);

/**
	@fn				PushAndEscapeBackL(const TDesC8& aSegment)
	Intended Usage	:	Escape encodes the segment then inserts the escaped version at 
	the back of the path. The new segment should only contain a single path segment, 
	as any path delimiters in the segment will be converted to an escape triple. The 
	parser is left in a state where its current segment is the same one as before 
	the insertion.
	@exception		KErrNoMemory.
	@warning		A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aSegment	A descriptor with the unescaped path segment.
	@pre 			The delimiter must have been set. 
	@post			The path will have been extended to include the new segment.
 */
	IMPORT_C void PushAndEscapeBackL(const TDesC8& aSegment);

private:	// Methods

/**
	@fn				CDelimitedPath8()
	Intended Usage	:	Constructor. First phase of two-phase construction method. Does
	non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	CDelimitedPath8();

/**
	@fn				ConstructL(const TDesC8& aPath)
	Intended Usage	:	Second phase of two-phase construction method. Does any allocations required
	to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPath	A descriptor with the initial path.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	void ConstructL(const TDesC8& aPath);

	};

#endif	// __DELIMITEDPATH8_H__