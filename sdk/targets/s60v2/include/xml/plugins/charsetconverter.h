// CharSetConverter.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __CHARSETCONVERTER_H__
#define __CHARSETCONVERTER_H__

#include <f32file.h>

class CCnvCharacterSetConverter;

namespace Xml
{

class CCharSetConverter : public CBase
/**
The CCharSetConverter class supplies algorithms for character conversion
between a chosen character set and unicode. Memory management
needed to hold the converted data is also handled.

@see CCnvCharacterSetConverter
@see CnvUtfConverter
@see MParser

@publishedPartner
@released
*/
	{
public:

	static CCharSetConverter* NewL();
	virtual ~CCharSetConverter();

	IMPORT_C void PrepareCharConvL(TUint& aCharSetUid, const TDesC8& aEncoding);
	IMPORT_C void PrepareCharConvL(TUint& aCharSetUid, TInt aMibEnum);

	IMPORT_C TInt ConvertToUnicodeL(TUint32 aSrcCharset, const TDesC8& aInputBuffer, 
		                            HBufC16*& aUnicodeConversion);
	IMPORT_C TInt ConvertFromUnicodeL(const TDesC16& aUnicodeConversion, TUint32 aDestCharset, 
		                              HBufC8*& aOutputBuffer);
	IMPORT_C void PrepareToConvertToOrFromL(TUint32 aCharSetUid);
	IMPORT_C TInt ConvertUcs4CharactersToEncodingL(TUint32* aUcs4Src, TInt aUcs4Count, 
		                                           TUint32 aDestCharset, HBufC8*& aConversion);
	IMPORT_C void ConvertCharacterSetIdentifierToStandardNameL(TUint32 aCharSetUid, HBufC8*& aCharSet);
	
private:

	CCharSetConverter();
	CCharSetConverter(const CCharSetConverter& aOriginal);
	CCharSetConverter& operator=(const CCharSetConverter& aRhs);
	
	void ConstructL();

	TText16* Utf32ToUtf16(TText16* aUtf16Out, TUint32 aUtf32);

private:

/**
The CharConv instance that we use to help in the character conversions.
*/
	CCnvCharacterSetConverter* iCnvCharacterSetConverter;

/**
The File Server session handle.
*/
	RFs iFs;

	};
}


#endif //__CHARSETCONVERTER_H__
