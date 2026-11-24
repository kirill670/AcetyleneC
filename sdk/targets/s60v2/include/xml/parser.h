// Parser.h
// Copyright (c) 2003-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __PARSER_H__
#define __PARSER_H__


#include <Xml/ContentProcessorUids.h> // needed for the typedef
#include <Xml/Plugins/ElementStack.h> // needed for the typedef

class RFs;

namespace Xml
{

class MContentHandler;
class RStringDictionaryCollection;
class TParserImpl;


/** 
If you need to parse xml this is the class you need to use.
@publishedAll
@released
*/
class CParser : public CBase
	{
public:
	static IMPORT_C CParser* NewL(const TDesC8& aParserMimeType, MContentHandler& aCallback);
	static IMPORT_C CParser* NewLC(const TDesC8& aParserMimeType, MContentHandler& aCallback);
	virtual ~CParser();


	IMPORT_C void ParseBeginL();
	IMPORT_C void ParseBeginL(const TDesC8& aDocumentMimeType);
	IMPORT_C void ParseL(const TDesC8& aFragment);
	IMPORT_C void ParseEndL();
	
	IMPORT_C void SetProcessorChainL(const RContentProcessorUids& aPlugins);

	IMPORT_C TInt EnableFeature(TInt aParserFeature);
	IMPORT_C TInt DisableFeature(TInt aParserFeature);
	IMPORT_C TBool IsFeatureEnabled(TInt aParserFeature) const;

	IMPORT_C void AddPreloadedDictionaryL(const TDesC8& aPublicId);

	IMPORT_C RStringPool& StringPool();
	IMPORT_C RStringDictionaryCollection& StringDictionaryCollection();
	
private:
	CParser();
	void ConstructL(const TDesC8& aParserMimeType, MContentHandler& aCallback);
	TParserImpl* iImpl;
	};

IMPORT_C void ParseL(CParser& aParser, const TDesC8& aDocument);
IMPORT_C void ParseL(CParser& aParser, RFs& aFs, const TDesC& aFilename);
}

#endif //__PARSER_H__
