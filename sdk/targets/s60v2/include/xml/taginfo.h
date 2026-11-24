// TagInfo.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __TAGINFO_H__
#define __TAGINFO_H__

#include <stringpool.h>

namespace Xml
{

class RTagInfo
/**
The RTagInfo class holds information that describes an element or attribute.
@see MContentHandler
@see RAttribute

@publishedAll
@released
*/
	{
public:

/**
@publishedPartner
@released
*/
	IMPORT_C RTagInfo();

/**
@publishedPartner
@released
*/
	IMPORT_C RTagInfo Copy();

/**
@publishedPartner
@released
*/
	IMPORT_C void Close();

/**
@publishedPartner
@released
*/
	IMPORT_C void Open(const RString& aUri, const RString& aPrefix, const RString& aLocalName);
	
/**
@publishedAll
@released
*/
	IMPORT_C const RString& Uri() const;
	
/**
@publishedAll
@released
*/
	IMPORT_C const RString& LocalName() const;
	
/**
@publishedAll
@released
*/
	IMPORT_C const RString& Prefix() const;

private:

/**
Holds the namespace uri of the object it represents.
*/
	RString iUri;

/**
Holds the namespace prefix of the object it represents.
*/
	RString iPrefix;

/**
Holds the local name of the object it represents.
*/
	RString iLocalName;

	};

}

#endif //__TAGINFO_H__
