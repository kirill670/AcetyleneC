
// Copyright (c) 2000 By Symbian Ltd. All Rights Reserved.

#ifndef _JAR_ATTRIBUTE_NAME_TABLE_H_
#define _JAR_ATTRIBUTE_NAME_TABLE_H_

#include <e32base.h>

class CJarAttributeName;

class CJarAttributeNameTable: public CBase
	{
public:

	IMPORT_C static CJarAttributeNameTable* NewL();

public:

	virtual ~CJarAttributeNameTable();

    const CJarAttributeName& ManifestVersionAttributeName(void) const;
	const CJarAttributeName& NameAttributeName(void) const;
	const CJarAttributeName& SHA1DigestAttributeName(void) const;
	const CJarAttributeName& SHA1DigestManifestAttributeName(void) const;
	const CJarAttributeName& SignatureVersionAttributeName(void) const;
	
	const CJarAttributeName* InternL(const TDesC&);

protected:
	CJarAttributeNameTable();
	void	ConstructL();
	TUint32	Hash(const TText8*, TUint32);
	TBool	IsValidAttributeName(const TDesC&);

protected:

	CJarAttributeName**			iNames;
	TUint32						iSize;
	const CJarAttributeName*	iMD5DigestAttributeName;
	const CJarAttributeName*	iManifestVersionAttributeName;
	const CJarAttributeName*	iNameAttributeName;
	const CJarAttributeName*	iSHA1DigestAttributeName;
	const CJarAttributeName*	iSHA1DigestManifestAttributeName;
	const CJarAttributeName*	iSignatureVersionAttributeName;
	};

#endif /* !_JAR_ATTRIBUTE_NAME_TABLE_H_ */
