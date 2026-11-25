// CFragmentedString.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

// A string class implementation which allows quick addition of partial strings
// (no copying) by using an internal array of fragmented strings.
// The class allows comprehensive character based matching functionality 
// along with infinite depth marking.

#ifndef __CFRAGMENTEDSTRING_H__
#define __CFRAGMENTEDSTRING_H__

// includes
#include <e32base.h>
#include <CStack.h>


//
// CFragmentedString
//

//##ModelId=3B666BC6034A
class CFragmentedString : protected CArrayPtrFlat<HBufC>
	{
protected:
	class TStringMark
		{
	public:
		TStringMark(TInt aIndex, TInt aCharacter)
		: iMarkIndex(aIndex), iMarkCharacter(aCharacter)
		{
		}

	public:
		TInt iMarkIndex;
		TInt iMarkCharacter;
		};

	typedef CStack<TStringMark, ETrue> CMarkStack;

public:
	enum TStringMatch 
		{ 
		ENoMatch, 
		EMatch,
		EInsufficientData
		};

public:
	IMPORT_C CFragmentedString();
	//##ModelId=3B666BC700AD
	IMPORT_C ~CFragmentedString();

	//##ModelId=3B666BC70099
	IMPORT_C void AddStringL(HBufC* aString); // this version is more efficient
	//##ModelId=3B666BC700A3
	IMPORT_C void AddStringL(const TDesC& aString);
	
	//##ModelId=3B666BC70090
	IMPORT_C TInt Length() const;
	//##ModelId=3B666BC70071
	IMPORT_C HBufC* StringL() const;
	//##ModelId=3B666BC70068
	IMPORT_C HBufC* ContentL() const;
	//##ModelId=3B666BC70067
	IMPORT_C void Reset();

	//##ModelId=3B666BC7005D
	IMPORT_C TStringMatch Match(const TDesC& aString);
	//##ModelId=3B666BC70049
	IMPORT_C TStringMatch MatchRange(const TUint aLower, const TUint aUpper);
	//##ModelId=3B666BC7003F
	IMPORT_C TStringMatch MatchSelect(const TDesC& aSelection);
	//##ModelId=3B666BC70037
	IMPORT_C TStringMatch MatchNotSelect(const TDesC& aSelection);
	//##ModelId=3B666BC70036
	IMPORT_C void ConsumeMatched();

	//##ModelId=3B666BC70035
	IMPORT_C HBufC* MarkedL();
	//##ModelId=3B666BC7002B
	IMPORT_C HBufC* MarkedWithInitialTextL(const TDesC& aInitialText);
	//##ModelId=3B666BC70022
	IMPORT_C void Mark(); // Mark can leave
	//##ModelId=3B666BC70021
	IMPORT_C void DeleteMark();
	//##ModelId=3B666BC70018
	IMPORT_C void ResetToMark();

	//##ModelId=3B666BC7000E
	IMPORT_C void ReplaceMarkedL(HBufC* aString);
	//##ModelId=3B666BC70005
	IMPORT_C void ReplaceMarkedAndSkipL(HBufC* aString);
	//##ModelId=3B666BC70003
	IMPORT_C void InsertStringL(HBufC* aString);

protected:
	//##ModelId=3B666BC603E1
	IMPORT_C void DeleteToMark(const TStringMark& aStringMark);
	//##ModelId=3B666BC603C4
	IMPORT_C void InsertStringToL(HBufC* aString, TInt aStringIndex, TInt aLengthIntoString);
	//##ModelId=3B666BC70072
	HBufC* StringL(TInt aStartIndex, TInt aStartCharacter, TInt aEndIndex, TInt aEndCharacter, const TDesC* aInitialText=NULL) const;
	//##ModelId=3B666BC603C3
	void StartMatch();
	//##ModelId=3B666BC603B8
	CFragmentedString::TStringMatch DoMatchSelect(const TDesC& aSelection, TBool aInSelection);
	//##ModelId=3B666BC603AE
	TBool FindNextMatchChar(TUint& aChar);

protected:
	//##ModelId=3B666BC603A4
	TStringMatch iMatched;

	//##ModelId=3B666BC6039A
	TInt iMatchedToIndex;
	//##ModelId=3B666BC60390
	TInt iMatchedToCharacter;
	//##ModelId=3B666BC60386
	TInt iCurrentIndex;
	//##ModelId=3B666BC6037C
	TInt iCurrentCharacter;
	//##ModelId=3B666BC60372
	CMarkStack iMarkStack;
	};

#endif // __CFRAGMENTEDSTRING_H__
