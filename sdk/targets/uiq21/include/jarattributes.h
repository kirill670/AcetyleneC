
// Copyright(c) 2000 By Symbian Ltd. All Rights Reserved.

#ifndef _JAR_ATTRIBUTES_H_
#define _JAR_ATTRIBUTES_H_

// Forward Class Declaration(s)

class CJarAttributeIterator;
class CJarAttributeName;
class CJarAttribute;
class CUTF8Buffer;
class CUTF8String;

// End of Forward Class Declaration(s)

const TUint32 kDefaultSize = 4;

class CJarAttributes: public CBase
	{
public:

	static CJarAttributes* NewL(TUint32 = kDefaultSize);

public:
	virtual ~CJarAttributes();

	const TDesC* Attribute(const CJarAttributeName&) const;
	const TDesC* Attribute(const TDesC&) const;
	const CArrayPtrFlat<CJarAttribute>& Attributes() const;
	void PutAttributeL(const CJarAttributeName&, TDesC* aValue);//const CUTF8Buffer&);
	
private:
	CJarAttributes();
	void ConstructL(TUint32);

private:
	CArrayPtrFlat<CJarAttribute>*	iAttributes;
	};

#endif /* !_JAR_ATTRIBUTES_H_ */
