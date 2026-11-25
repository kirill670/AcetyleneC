// DelimitedPath16.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __DELIMITEDPATH16_H__
#define __DELIMITEDPATH16_H__

/**
	@file DelimitedPath16.h
	Comments :	This file contains the API definition for the classes 
				TDelimitedPathParser16 and CDelimitedPath16. 
 */

// System includes
//
#include <e32base.h>

// Local includes
//
#include "delimitedparser16.h"

class TDelimitedPathParser16 : public TDelimitedParserBase16
/**
@class TDelimitedPathParser16
Dependencies : TDelimitedParserBase16
Comments : Derived class from TDelimitedParserBase providing a class for parsing paths
delimited by '/' as defined in RFC2396.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				TDelimitedPathParser16()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedPathParser16();

/**
	@fn				Parse(const TDesC16& aPath)
	Intended Usage	:	This parses the descriptor into path segments from left to right.
	@since			6.0
	@param			aPath	A descriptor containing the path.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataFroward).
 */
	IMPORT_C void Parse(const TDesC16& aPath);

/**
	@fn				ParseReverse(const TDesC16& aPath)
	Intended Usage	:	This parses the descriptor into path segments from right to left.
	@since			6.0
	@param			aPath	A descriptor containing the path.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC16& aPath);
	};

class CDelimitedPath16 : public CDelimitedDataBase16
/**
@class CDelimitedPath16
Dependencies : CDelimitedStringBase16
Comments : Provides functionality to create a delimited path where components of the 
path delimited by '/' as defined in RFC2396.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				NewL(const TDesC16& aPath)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves nothing
	on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPath	A descriptor with the initial path.
	@return			A pointer to created object.
	@post			Nothing left on the CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPath16* NewL(const TDesC16& aPath);

/**
	@fn				NewLC(const TDesC16& aPath)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves a
	pointer to created object on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPath	A descriptor with the initial path.
	@return			A pointer to created object.
	@post			Pointer to created object left of CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedPath16* NewLC(const TDesC16& aPath);

/**
	@fn				~CDelimitedPath16()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedPath16();

/**
	@fn				InsertAndEscapeCurrentL(const TDesC16& aSegment)
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
	IMPORT_C void InsertAndEscapeCurrentL(const TDesC16& aSegment);

/**
	@fn				PushAndEscapeFrontL(const TDesC16& aSegment)
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
	IMPORT_C void PushAndEscapeFrontL(const TDesC16& aSegment);

/**
	@fn				PushAndEscapeBackL(const TDesC16& aSegment)
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
	IMPORT_C void PushAndEscapeBackL(const TDesC16& aSegment);

private:	// Methods

/**
	@fn				CDelimitedPath16()
	Intended Usage	:	Constructor. First phase of two-phase construction method. 
	Does non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	CDelimitedPath16();

/**
	@fn				ConstructL(const TDesC16& aPath)
	Intended Usage	:	Second phase of two-phase construction method. Does any allocations 
	required to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aPath	A descriptor with the initial path.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	void ConstructL(const TDesC16& aPath);

	};

typedef TDelimitedPathParser16 TDelimitedPathParser;
typedef CDelimitedPath16 CDelimitedPath;

#endif	// __DELIMITEDPATH16_H__


