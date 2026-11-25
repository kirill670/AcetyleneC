// CONCNF.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONCNF_H__)
#define __CONCNF_H__

#include <e32base.h>
#include <f32file.h>
#include <s32stor.h>
#include <apmstd.h>
#include <barsc.h>
#include <barsread.h>

/**
@publishedAll 
@released 
*/
#define KMaxTranslation 50

/** Buffer to contain a localised data type name. 

@publishedAll 
@released */
typedef TBuf<KMaxTranslation> TTranslation;


class TLanguageInfo
/** Holds a localised name for a data type. 

@publishedAll 
@released */
	{
public:
	TLanguageInfo();
	IMPORT_C TLanguageInfo(TLanguage aLanguage,TTranslation aTranslation);
public:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TLanguage Language();
	TTranslation Translation();
public:
	TLanguage	iLanguage;
	TTranslation iTranslation;
	};

class CMimeInfo : public CBase
/** Holds the localised names for a data type.

@publishedAll
@released */
	{
public:
	IMPORT_C ~CMimeInfo();
	IMPORT_C static CMimeInfo* NewLC(TDataType& aMime);
	static CMimeInfo* NewL();
	static CMimeInfo* NewLC(const CMimeInfo* aInfo);
public:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TDataType Mime();
	TTranslation Text();
	IMPORT_C void AddLanguageL(TLanguageInfo aLang);
private:
	void ConstructL();
private:
	TDataType iMime;
	CArrayFixFlat<TLanguageInfo> *iLanguageInfo;
	};

class CCnaConverter : public CBase
/** Holds the inherent properties of a converter. 

These are its UID and the data types it supports.

Note that the setter functions affect only the current object, not the stored 
information for the converter.

@publishedAll
@released */
	{
public:
	static CCnaConverter* NewLC();
	static CCnaConverter* NewL();
	IMPORT_C static CCnaConverter* NewL(TUid aUid);
	IMPORT_C static CCnaConverter* NewLC(TUid aUid);
	IMPORT_C static CCnaConverter* NewL(const CCnaConverter& aConverter);
	IMPORT_C static CCnaConverter* NewLC(const CCnaConverter& aConverter);
	IMPORT_C ~CCnaConverter();
	IMPORT_C void AddMimeFromL(const CMimeInfo* aMimeInfo);
	IMPORT_C void AddMimeToL(const CMimeInfo* aMimeInfo);
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool MimeFrom(const TDataType& aMimeType) const;
	IMPORT_C TBool MimeTo(const TDataType& aMimeType) const;
	IMPORT_C TTranslation MimeFromText(const TDataType& aMimeType) const;
	IMPORT_C TTranslation MimeToText(const TDataType& aMimeType) const;
	IMPORT_C TInt CountFrom() const;
	IMPORT_C TInt CountTo() const;
	IMPORT_C TDataType MimeFrom(TInt aIndex) const;
	IMPORT_C TDataType MimeTo(TInt aIndex) const;
	IMPORT_C TTranslation MimeFromText(TInt aIndex) const;
	IMPORT_C TTranslation MimeToText(TInt aIndex) const;
	inline TUid Uid() const;
private:
	CCnaConverter();
	void ConstructL();
	TBool FindMime(const TDataType& aMimeType, const CArrayPtrFlat<CMimeInfo>* aList) const;
	TTranslation FindMimeText(const TDataType& aMimeType, const CArrayPtrFlat<CMimeInfo>* aList) const;
private:
	TUid iUid;
	CArrayPtrFlat<CMimeInfo>* iMimeFrom;
	CArrayPtrFlat<CMimeInfo>* iMimeTo;
	};


class CCnaConvInfoFile : public CBase
/**
implementation class
@internalComponent
*/
	{
public:
	~CCnaConvInfoFile();
	//
protected:
	void ConstructL();
protected:
	RFs iFs;
	CPersistentStore* iStore;
	CArrayPtr<CCnaConverter>* iConverters;
	};

class CCnaConvInfoFileReader : public CCnaConvInfoFile
/** Encapsulates a collection of converter properties (CCnaConverter) read from a converter 
information (.cnf) file.

@publishedAll
@released
*/
// classes CCnaConvInfoFileReader and CCnaConvInfoFileWriter are collection classes
// for CCnaConverter.  

// Each CNF file contains CCnaConverter information for each
// available CConverterBase derived class in its associated DLL.

// In addition there may be INI files for each converter which supply run time extended
// CCnaConverter information such as additional mime types.
	{
public:
	IMPORT_C static CCnaConvInfoFileReader* NewLC(const TDesC& aFileName,TUid aDllUid=KNullUid);
	IMPORT_C static CCnaConvInfoFileReader* NewL(const TDesC& aFileName,TUid aDllUid=KNullUid);
	IMPORT_C ~CCnaConvInfoFileReader();
	IMPORT_C TInt Count();
	IMPORT_C CCnaConverter* AtL(TInt anIndex);
	//
	IMPORT_C void RestoreL();
private:
	void RestoreConverterL(TUid aUid, const CStreamDictionary& aDict);
	void ConstructL(const TDesC& aFileName,TUid aUid);

#ifdef __CNF_FORMAT_V2__
	void AddMimeTypesL(CCnaConverter& aConverter, TResourceReader& aReader, TBool aIsFromList);
private:
	RResourceFile iResourceFile;
#endif // __CNF_FORMAT_V2__
	};



class CCnaConvInfoFileWriter : public CCnaConvInfoFile
/** Allows a converter information (.cnf) file to be written.

@publishedAll
@see CCnaConvInfoFileReader
@deprecated
*/
	{
public:
	IMPORT_C static CCnaConvInfoFileWriter* NewLC(const TDesC& aFileName,TUid aUid);
	IMPORT_C static CCnaConvInfoFileWriter* NewL(const TDesC& aFileName,TUid aUid);
	IMPORT_C ~CCnaConvInfoFileWriter();
	//
	IMPORT_C void AddConverterL(const CCnaConverter& aConverter);
	//
	IMPORT_C void StoreL() const;
private:
	TStreamId StoreConverterL(const CCnaConverter& aConverter)const;
	TStreamId StoreHeaderL()const;
	void ConstructL(const TDesC& aFileName,TUid aUid);
private:
	CStoreMap* iMap;
	};


inline TUid CCnaConverter::Uid() const
/** Gets the converter UID.

@return Converter UID */
	{return iUid;}

#endif
