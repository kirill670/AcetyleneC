// CONLIST.H
//
// Copyright (c) Symbian Software Ltd 1997-2005.  All rights reserved.
//

#if !defined(__CONLIST_H__)
#define __CONLIST_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__CONARC_H__)
#include <conarc.h>
#endif

#if !defined(__CONCNF_H__)
#include <concnf.h>
#endif

#ifdef USING_ECOM_CONARC
#if !defined(__IMPLEMENTATION_INFORMATION_H__)
#include <ImplementationInformation.h>
#endif
#if !defined(__ECOM_H__)
#include <ecom.h>
#endif
#endif


/** Creates a converter dll's factory interface object.

@publishedAll
@released
*/
typedef CConverterLibrary* (*CreateCConverterLibrary)(); 

struct SConverterInfo
/** Describes a converter, as obtained from a converter list (CCnaConverterList).

@publishedAll
@released
@see CCnaConverterList */
	{
	/** Localised name of the data type. */
	TTranslation iTranslation;
	/** Converter UID. */
	TUid iUid;
	/** Position of the converter in the list. */
	TInt iIndex;
	};

// classes referenced
class CCnaFoundConverter;


class CCnaConverterList : public CBase
/** Provides a list of available converters, allowing clients to search for and 
obtain converters for specific source and target data types. 

@publishedAll
@released */
	{
public:
	IMPORT_C static CCnaConverterList* NewL();
	IMPORT_C static CCnaConverterList* NewLC();
	IMPORT_C void Release();
	IMPORT_C ~CCnaConverterList();
//
	IMPORT_C TInt CountL();
	inline TInt Count();
	IMPORT_C CConverterBase* NewConverterL(TUid aUid);
	IMPORT_C void UpdateL();
	IMPORT_C TUid ConvFromL(const TDataType& aMimeType); // searches for a particular converter
	IMPORT_C TUid ConvToL(const TDataType& aMimeType);
	IMPORT_C TUid ConverterL(const TDataType& aFrom,const TDataType& aTo);
	IMPORT_C void ConvFromListL(const TDataType& aMimeType,CArrayFix<SConverterInfo>* aSConverterInfoArray);
	IMPORT_C void ConvToListL(const TDataType& aMimeType,CArrayFix<SConverterInfo>* aSConverterInfoArray);
	IMPORT_C TInt MimeTypeFrom(TDataType& aDataType,const SConverterInfo& aConverterInfo) const;
	IMPORT_C TInt MimeTypeTo(TDataType& aDataType,const SConverterInfo& aConverterInfo) const;
private:
	CCnaConverterList();
	void ConstructL();
	CConverterBase* LoadConverterL(CCnaFoundConverter& aConverter);
	CConverterBase* LoadConverterL(TUid aImplUid);
private:
#ifndef SYMBIAN_REMOVE_UI_FRAMEWORKS_V1
	CArrayPtr<CCnaFoundConverter>* iConverterList;
	CArrayFix<RLibrary>* iLoadedDlls;
#endif
	TBool iDoneScan;
	CArrayPtr<CCnaConverter>* iConverters;
#ifdef USING_ECOM_CONARC
	RImplInfoPtrArray iImplementationArray;
#endif
	};

class ConverterListUtil
/** @internalComponent */
	{
public:
	static CConverterBase* UtilityConverterL(TUid aUid);
	static TInt CountUtilityConverters();
	};

inline TInt CCnaConverterList::Count()
/** @deprecated

Deprecated - Use CCnaConverterList::CountL instead. 
Rescan of the disk to refresh the list of converters could leave. */
	{
	return CountL();
	}

#endif
