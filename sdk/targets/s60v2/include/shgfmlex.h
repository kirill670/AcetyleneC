// SHGFMLEX.H  
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGFMLEX_H__)
#define __SHGFMLEX_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__SHGAPI_H__)
#include <shgapi.h>
#endif

#if !defined(__SHGCOORD_H__)
#include <shgcoord.h>
#endif

#if !defined(__SHGTOKEN_H__)
#include <shgtoken.h>
#endif

struct SLexToken
/** A token that represents part of a formula. 
@publishedAll
@released
*/
	{
public:
	/** Formula token ID. */
	TFormulaToken			iType;
	/** Formula token class (operator, function, etc.) and argument information. */
	Token::TLexTokenClass	iClass;
	/** Integer value. */
	TInt					iValInt;
	/** Real number value. */
	TReal					iValReal;
	/** Worksheet number. */
	TInt					iWorkSheetNo;
	/** Cell reference. */
	TShgCellRef				iValCell;
	/** Range reference. */
	TShgRangeRef			iValRange;
	/** Name. */
	TInt32					iValNameId;
	/** Text. */
	HBufC*					iValText;
	};

class CShgFormulaTextLexer : public CBase
/** Breaks down a formula stored as text into formula tokens. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C virtual ~CShgFormulaTextLexer();
	IMPORT_C static CShgFormulaTextLexer* NewL(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,const CShgFormulaViewer* aFormulaViewer);
	static CShgFormulaTextLexer* NewLC(const CShgNameSet* aNameSet,const CShgWorkBook* aShengMap,const CShgFormulaViewer* aFormulaViewer);
private:
	CShgFormulaTextLexer(const CShgNameSet* aNameSet,const CShgWorkBook* aShengMap,const CShgFormulaViewer* aFormulaViewer);
	void ConstructL();
public:
	IMPORT_C void Start(const TDesC& aDes,const TCellRef& aCurrentCell);
	IMPORT_C TBool GetNextTokenL();
	IMPORT_C const SLexToken& Token() const;
	IMPORT_C void UnGetToken(const SLexToken& aToken); // previously was exported for test code
	IMPORT_C TInt Offset() const; // previously was exported for test code
	TBool IsMoreText() const;
	void LocaleHasChanged();
public:
	TBool LexRow(TShgCellRef& aResult,const TCellRef& aRelOrigin);
	TBool LexColumn(TShgCellRef& aResult,const TCellRef& aRelOrigin);
	TBool LexCell(TShgCellRef& aResult,const TCellRef& aRelOrigin);
	IMPORT_C TBool LexCellOrRange();
	TBool LexNumberL();
	TBool LexStringL();
	TBool LexOperator();
private:
	struct SOpTab
	/**
	@internalComponent
	@released
	*/
		{
		TInt iOperatorSymbol;
		TFormulaToken iOperatorToken;
		};
	SOpTab OperatorList(TInt aPos) const;
	static TInt MakeRelative(TInt& aRef,TInt aRel);
	TBool IsName();
	TBool IsWorkSheetName();
	TBool IsLogicalOperator();
	TBool IsFunction();
private:
	const CShgNameSet* const iNameSet;
	const CShgWorkBook*	iWorkBook;
	const CShgFormulaViewer* const iFormulaViewer;
	TLex iLex;
	TChar iDecimalSeparator;
	TFormulaToken iPreviousTokenType;
	TFormulaToken iSavedTokenType;
	SLexToken iCurrentToken;
	TCellRef iRelativeCell;
	__DECLARE_TEST;
	};

class TShgCellRefAndRangeRefAndNameTokenLexer
/**
@internalComponent
@released
*/
	{
public:
	TShgCellRefAndRangeRefAndNameTokenLexer(const TDesC8& aFormula,const TCellRef& aRelativeCell);
	TShgCellRefAndRangeRefAndNameTokenLexer(const TDesC8& aFormula,TDes8& aNewFormula,const TCellRef& aRelativeCell);
	void GetNextTokenWithoutMakingAbsolute();
	inline const SLexToken& CurrentToken() const {return iCurrentToken;}
	void AppendCurrentTokenToNewFormula();
	void AppendErrorToNewFormula(TShgCell::TErrorType aError);
	void AppendCellRefToNewFormula(const TShgCellRef& aShgCellRef);
	void AppendRangeRefToNewFormula(TFormulaToken aRangeToken,const TShgRangeRef& aShgRangeRef);
private:
	TLex8 iFormula;
	TDes8* iNewFormula;
	TCellRef iRelativeCell;
	SLexToken iCurrentToken;
	};

#endif
