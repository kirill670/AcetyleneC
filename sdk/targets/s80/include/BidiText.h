// BidiText.h
//
// Copyright (C) 2002 Symbian Ltd. All rights reserved.
//

#ifndef BIDITEXT_H_
#define BIDITEXT_H_

#include <e32std.h>
#include <gdi.h>
enum CGraphicsContext::TTextAlign;
class MLineBreaker;

class TBidiText
/** 
This class works as a replacement for HBufC in those cases where a small 
amount of text is being formatted simply. The text must be all of one style 
and broken into lines of all the same length. The number of lines and the text 
itself is specified on construction, and the text may then be re-broken, 
re-truncated and re-drawn with non-leaving functions. 
@publishedAll
@released
*/
	{
public:
	/** Overall directionality of the text. */
	enum TDirectionality
		{
		/** Text reading begins on the left. */
		ELeftToRight = 0,
		/** Text reading begins on the right. */
		ERightToLeft = 1
		};
	IMPORT_C static TDirectionality ScriptDirectionality(TLanguage aLanguage);
	IMPORT_C static TDirectionality TextDirectionality(
		const TDesC& aText, TBool* aFound = 0);
protected:
	/** Constructor. */
	TBidiText();
public:
	IMPORT_C static TBidiText* NewL(const TDesC& aText, TInt aMaxLines);
	IMPORT_C static TBidiText* NewL(const TDesC& aText, TInt aMaxLines,
		TDirectionality aDirectionality);
	IMPORT_C void SetTruncationChar(TChar aTruncateWith);
	IMPORT_C void WrapText(TInt aWrappingWidth, const CFont& aFont,
		const MLineBreaker* aBreaker);
	IMPORT_C TPtrC Text() const;
	IMPORT_C TPtrC DisplayText() const;
	IMPORT_C TInt WrappingWidth() const;
	IMPORT_C TDirectionality Directionality() const;
	IMPORT_C void DrawText(CGraphicsContext& aGc, const TPoint& aLeft) const;
	IMPORT_C void DrawText(CGraphicsContext& aGc,
		const TPoint& aLeft, TInt aBaseLineSpacing,
		CGraphicsContext::TTextAlign aAlignment) const;
	IMPORT_C void DrawText(CGraphicsContext& aGc,
		const TPoint& aLeft, TInt aBaseLineSpacing) const;
	};

#endif
