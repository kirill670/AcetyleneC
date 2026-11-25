
// Copyright (c) 2000 By Symbian Ltd. All Rights Reserved.

#ifndef _JAR_ATTRIBUTE_NAME_H_
#define _JAR_ATTRIBUTE_NAME_H_

#include <e32base.h>

class CJarAttributeName: public CBase
	{
friend class CJarAttributeNameTable;

public:
	static CJarAttributeName* NewL(const TDesC&);
	~CJarAttributeName();

	IMPORT_C const HBufC& Name(void) const;

	TBool operator==(const CJarAttributeName&) const;
	TBool operator==(const TDesC&) const;

protected:
	
	void ConstructL(const TDesC&);

/*private:
	static const TBuf<10> KMD5DigestString;
	static const TBuf<16> KManifestVersionString;
	static const TBuf<4> KNameString;
	static const TBuf<11> KSHA1DigestString;
	static const TBuf<20> KSHA1DigestManifestString;
	static const TBuf<17> KSignatureVersionString;*/

private:
	HBufC*			   iName;
	CJarAttributeName* iNext;
	};

#endif /* !_JAR_ATTRIBUTE_NAME_H_ */
