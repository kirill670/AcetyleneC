// DelimitedQuery8.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __DELIMITEDQUERY8_H__
#define __DELIMITEDQUERY8_H__

/**
	@file DelimitedQuery8.h
	Comments :	This file contains the API definition for the classes TDelimitedQueryParser8
				and CDelimitedQuery8. 
 */

// System includes
//
#include <e32base.h>

// Local includes
//
#include "delimitedparser8.h"

class TDelimitedQueryParser8 : public TDelimitedParserBase8
/**
@class TDelimitedQueryParser8
Dependencies : TDelimitedParserBase8
Comments : Derived class from TDelimitedParserBase providing a class for parsing 
querys delimited by a '&' as defined in RFC2396.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				TDelimitedQueryParser8()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedQueryParser8();

/**
	@fn				Parse(const TDesC8& aQuery)
	Intended Usage	:	This parses the descriptor into query segments from left to right.
	@since			6.0
	@param			aQuery	A descriptor containing the query.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataForward).
 */
	IMPORT_C void Parse(const TDesC8& aQuery);

/**
	@fn				ParseReverse(const TDesC8& aQuery)
	Intended Usage	:	This parses the descriptor into query segments from right to left.
	@since			6.0
	@param			aQuery	A descriptor containing the query.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC8& aQuery);
	};

class CDelimitedQuery8 : public CDelimitedDataBase8
/**
@class CDelimitedQuery8
Dependencies : CDelimitedStringBase8
Comments : Provides functionality to create a delimited query where components of the 
query delimited by '&' as defined in RFC2396.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				NewL(const TDesC8& aQuery)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves nothing
	on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aQuery	A descriptor with the initial query.
	@return			A pointer to created object.
	@post			Nothing left on the CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedQuery8* NewL(const TDesC8& aQuery);

/**
	@fn				NewLC(const TDesC8& aQuery)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves a
	pointer to created object on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aQuery	A descriptor with the initial query.
	@return			A pointer to created object.
	@post			Pointer to created object left of CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedQuery8* NewLC(const TDesC8& aQuery);

/**
	@fn				~CDelimitedQuery8()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedQuery8();

/**
	@fn				InsertAndEscapeCurrentL(const TDesC8& aSegment)
	Intended Usage	:	Escape encodes segment then inserts the escaped version in a 
	position before the current parsed segment. The new segment should only contain a
	single query segment, as any query delimiters in the segment will be converted to an
	escape triple. The parser is left in a state where its current segment is the same
	one as before the insertion.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aSegment	A descriptor with the unescaped query segment.
	@pre 			The query must have been initially parsed.
	@post			The query will have been extended to include the new segment. The 
	current segment will remain as the one before the insertion.
 */
	IMPORT_C void InsertAndEscapeCurrentL(const TDesC8& aSegment);

/**
	@fn				PushAndEscapeFrontL(const TDesC8& aSegment)
	Intended Usage	:	Escape encodes segment then inserts the escaped version at 
	the front of the query. The new segment should only contain a single query segment, 
	as any query delimiters in the segment will be converted to an escape triple. The 
	parser is left in a state where its current segment is the same one as before 
	the insertion.
	@exception		KErrNoMemory.
	@warning		A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aSegment	A descriptor with the unescaped query segment.
	@pre 			The delimiter must have been set. 
	@post			The query will have been extended to include the new segment.
 */
	IMPORT_C void PushAndEscapeFrontL(const TDesC8& aSegment);

/**
	@fn				PushAndEscapeBackL(const TDesC8& aSegment)
	Intended Usage	:	Escape encodes segment then inserts the escaped version at 
	the back of the query. The new segment should only contain a single query segment, 
	as any query delimiters in the segment will be converted to an escape triple. The 
	parser is left in a state where its current segment is the same one as before 
	the insertion.
	@exception		KErrNoMemory.
	@warning		A re-parse is required to ensure that the parser is valid.
	@since			6.0
	@param			aSegment	A descriptor with the unescaped query segment.
	@pre 			The delimiter must have been set. 
	@post			The query will have been extended to include the new segment.
 */
	IMPORT_C void PushAndEscapeBackL(const TDesC8& aSegment);

private:	// Methods

/**
	@fn				CDelimitedQuery8()
	Intended Usage	:	Constructor. First phase of two-phase construction method. Does
	non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	CDelimitedQuery8();

/**
	@fn				ConstructL(const TDesC8& aQuery)
	Intended Usage	:	Second phase of two-phase construction method. Does any allocations required
	to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aQuery	A descriptor with the initial query.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	void ConstructL(const TDesC8& aQuery);

	};

#endif	// __DELIMITEDQUERY8_H__