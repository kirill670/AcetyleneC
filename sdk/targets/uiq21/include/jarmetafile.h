
// Copyright (c) 2000 By Symbian Ltd. All Rights Reserved.

#ifndef _JAR_META_FILE_H_
#define _JAR_META_FILE_H_

#include <e32base.h>
#include <JarAttributes.h>

// Forward Class Declaration(s)

class CJarAttributeIterator;
class CJarAttributeName;
class CJarMetaFileEntryIterator;
class CJarMetaFileEntry;
class CJarMetaFileSectionIterator;
class CJarMetaFileSection;
class CUTF8Buffer;
class CUTF8String;

// End of Forward Class Declaration(s)

class CJarMetaFile: public CBase
	{
friend class CJarMetaFileParser;

public:
	static CJarMetaFile* NewL();
	virtual ~CJarMetaFile();

	CJarMetaFileEntry* Entry(const TDesC&) const;
	
	TUint32				   GetMainAttributesSize(void) const;
	
	const TDesC* MainAttribute(const CJarAttributeName&) const;
	IMPORT_C const TDesC* MainAttribute(const TDesC&) const;
	IMPORT_C const CArrayPtrFlat<CJarAttribute>& MainAttributes() const;
	
	CJarMetaFileEntryIterator* 	 GetEntriesL(void) const;
	CJarMetaFileSectionIterator* GetSectionsL(void) const;

protected:
	
	CJarMetaFile();

	void ConstructL();

	void AddMainAttributeL(const CJarAttributeName&, TDesC*);

	CJarMetaFileEntry* AddEntryL(const TDesC&);
	
	void AddSectionL(CJarMetaFileEntry*, TUint32, TUint32);
	
protected:

	CJarAttributes*			iMainAttributes;
	CJarMetaFileEntry*		iHead;
	CJarMetaFileEntry*		iTail;
	CJarMetaFileSection*	iSectionsHead;
	CJarMetaFileSection*	iSectionsTail;
	};

#endif /* !_JAR_META_FILE_H_ */

