
// Copyright (c) 2000 By Symbian Ltd. All Rights Reserved.

#ifndef _JAR_ATTRIBUTE_H_
#define _JAR_ATTRIBUTE_H_

#include <e32std.h>
#include <e32base.h>

// Forward Class Declaration(s)

class CJarAttributeName;

// End of Forward Class Declaration(s)

class CJarAttribute : public CBase
	{
friend class CJarAttributes;
friend class CJarAttributeIterator;

public:
	CJarAttribute(const CJarAttributeName& aName, TDesC* aValue);
	virtual ~CJarAttribute();
	IMPORT_C const CJarAttributeName&	Name(void) const;
	IMPORT_C const TDesC*				Value(void) const;

private:
	const CJarAttributeName& iName;
	TDesC*			 iValue;
	};

#endif /* !_JAR_ATTRIBUTE_H_ */
