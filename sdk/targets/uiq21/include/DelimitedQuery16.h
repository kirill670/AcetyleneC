// DelimitedQuery16.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __DELIMITEDQUERY16_H__
#define __DELIMITEDQUERY16_H__

/**
	@file DelimitedQuery16.h
	Comments :	This file contains the API definition for the classes TDelimitedQueryParser16
				and CDelimitedQuery16.
 */

// System includes
//
#include <e32base.h>

// Local includes
//
#include "DelimitedParser16.h"

/**
	@class TDelimitedQueryParser16
	Dependencies : TDelimitedParserBase16
	Comments : Derived class from TDelimitedParserBase providing a class for parsing querys
	delimited by '&' as defined in RFC2396.
	@public
	@since 6.0
 */
class TDelimitedQueryParser16 : public TDelimitedParserBase16
	{
public:	// Methods

/**
	@fn				TDelimitedQueryParser16()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TDelimitedQueryParser16();

/**
	@fn				Parse(const TDesC16& aQuery)
	Intended Usage	:	This parses the descriptor into query segments from left to right.
	@since			6.0
	@param			aQuery	A descriptor containing the query.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from left to right (EDelimitedDataFroward).
 */
	IMPORT_C void Parse(const TDesC16& aQuery);

/**
	@fn				ParseReverse(const TDesC16& aQuery)
	Intended Usage	:	This parses the descriptor into query segments from right to left.
	@since			6.0
	@param			aQuery	A descriptor containing the query.
	@pre 			The delimiter must have been set.
	@post			The current segment is the leftmost segment and the direction of 
	parsing is set from right to left (EDelimitedDataReverse).
 */
	IMPORT_C void ParseReverse(const TDesC16& aQuery);
	};

/**
	@class CDelimitedQuery16
	Dependencies : CDelimitedStringBase16
	Comments : Provides functionality to create a delimited query where components of the 
	query delimited by '&' as defined in RFC2396.
	@public
	@since 6.0
 */
class CDelimitedQuery16 : public CDelimitedDataBase16
	{
public:	// Methods

/**
	@fn				NewL(const TDesC16& aQuery)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves nothing
	on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aQuery	A descriptor with the initial query.
	@return			A pointer to created object.
	@post			Nothing left on the CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedQuery16* NewL(const TDesC16& aQuery);

/**
	@fn				NewLC(const TDesC16& aQuery)
	Intended Usage	:	Static factory constructor. Uses two phase construction and leaves a
	pointer to created object on the CleanupStack.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aQuery	A descriptor with the initial query.
	@return			A pointer to created object.
	@post			Pointer to created object left of CleanupStack.
	@cat			Construction and Destruction
 */
	IMPORT_C static CDelimitedQuery16* NewLC(const TDesC16& aQuery);

/**
	@fn				~CDelimitedQuery16()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CDelimitedQuery16();

/**
	@fn				InsertAndEscapeCurrentL(const TDesC16& aSegment)
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
	IMPORT_C void InsertAndEscapeCurrentL(const TDesC16& aSegment);

/**
	@fn				PushAndEscapeFrontL(const TDesC16& aSegment)
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
	IMPORT_C void PushAndEscapeFrontL(const TDesC16& aSegment);

/**
	@fn				PushAndEscapeBackL(const TDesC16& aSegment)
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
	IMPORT_C void PushAndEscapeBackL(const TDesC16& aSegment);

private:	// Methods

/**
	@fn				CDelimitedQuery16()
	Intended Usage	:	Constructor. First phase of two-phase construction method. 
	Does non-allocating construction.
	@since			6.0
	@cat			Construction and Destruction
 */
	CDelimitedQuery16();

/**
	@fn				ConstructL(const TDesC16& aQuery)
	Intended Usage	:	Second phase of two-phase construction method. Does any allocations 
	required to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aQuery	A descriptor with the initial query.
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed.
	@cat			Construction and Destruction
 */
	void ConstructL(const TDesC16& aQuery);

	};

typedef TDelimitedQueryParser16	TDelimitedQueryParser;
typedef CDelimitedQuery16		CDelimitedQuery;

#endif	// __DELIMITEDQUERY16_H__
