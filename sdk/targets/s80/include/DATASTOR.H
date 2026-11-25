// DATASTOR.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#if !defined(__DATASTOR_H__)
#define __DATASTOR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__S32FILE_H__)
#include <s32file.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif

class RReadStream;
class RWriteStream;

/**
@internalComponent
*/
const TUid KUidDatastor = {0x1000071E};

/**
@internalComponent
*/
const TUid KUidDatastorSettings = {0x10000790};

/**
@internalComponent
*/
_LIT(KIniFileName,"c:\\System\\Data\\Dtstor.ini");


class TMappingDataTypeToApp
/**
@publishedAll
@deprecated
*/
	{
public:
	IMPORT_C TMappingDataTypeToApp();
	IMPORT_C TMappingDataTypeToApp(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TDataType iDataType;
	TDataTypePriority iPriority;
	TUid iAppUid; // Uid [2] of the target application
	};

					   
class CTypeStoreManager : public CBase
/** A store of mappings between data types, the UIDs of applications that 
can handle them and the priority at which the application handles them.

@publishedAll
@deprecated
*/
	{
public:
	IMPORT_C static CTypeStoreManager* NewL(RFs& aFs);
	IMPORT_C ~CTypeStoreManager();
	// Persistence
	IMPORT_C void StoreL();
	IMPORT_C void RestoreL();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	// Enquiry
	IMPORT_C void GetAppByDataType(const TDataType& aDataType, TUid& aUid) const;
	IMPORT_C void GetDataTypesByAppL(TUid aUid, CArrayFix<TDataType>* aTypeArray) const;
	IMPORT_C const CArrayFixFlat<TMappingDataTypeToApp>& MappingArray() const;
	// Management
	IMPORT_C void InsertDataMappingL(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C TBool InsertIfHigherL(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C void DeleteDataMapping(const TDataType& aDataType);
	inline TPtrC IniFileName() const;
private:
	CDictionaryStore* OpenIniFileLC() const;
	CTypeStoreManager(RFs& aFs);
	TInt FindDataMapping(const TDataType& aDataType) const;
private:
	CArrayFixFlat<TMappingDataTypeToApp> iAppMappings;
	RFs& iFs;
	};


inline TPtrC CTypeStoreManager::IniFileName() const
//	return name of dtstor's ini file
	{
	TPtrC KDatastorIniFileName(KIniFileName);
	return KDatastorIniFileName;
	}

#endif
