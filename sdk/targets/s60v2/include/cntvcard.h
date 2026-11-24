// CNTVCARD.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//
#ifndef __CNTVCARD_H__
#define __CNTVCARD_H__

// System includes
#include <cntdb.h>
#include <vcard.h>

// Classes referenced
class CVCardAddress;
class CVCardItemAndLabel;
class CVCardToContactsAppConverter;

// Enumerations
/**
@internalComponent
@released
*/
enum TCntVCardImportType
	{
	ECntVCardImportTypeFirstSync,
	ECntVCardImportTypeMerge
	};
		
#ifdef SYMBIAN_COREAPPS_PLUGIN_API_V2
class CContactVCardConverter : public CContactEcomConverter
#else
class CContactVCardConverter : public CContactConverter
#endif
/**
Plug-in vCard to CContactItem converter.
@publishedAll
@released
*/
	{
public:
	// Ideally each converter should be able to define its own flags relevant 
	// to its own mode of operation. Due to the legacy design (defining flags 
	// in CContactDatabase) they have to be redeclared here. Long term we hope 
	// to deprecate the CContactDatabase flags and rely on those declared in 
	// the converter implementation.
	/**
	@publishedAll
	@released
	*/
	enum TOptions 
  		{
  		EDefault = CContactDatabase::EDefault,
		EIncludeX = CContactDatabase::EIncludeX,
  		ETTFormat = CContactDatabase::ETTFormat ,
		EExcludeUid = CContactDatabase::EExcludeUid,
		EDecreaseAccessCount = CContactDatabase::EDecreaseAccessCount,
		EImportSingleContact = CContactDatabase::EImportSingleContact,
		EIncreaseAccessCount = CContactDatabase::EIncreaseAccessCount,
		ELocalTime = CContactDatabase::ELocalTime,
		ENullTemplateId = CContactDatabase::ENullTemplateId,
		EConnectWhitespace=0x0100,		// Used to correctly manage the TimeIS protocol for syncing.
  		};
  		
	/**
	@internalComponent
	@released
	*/
	enum TVersitPropertyType
		{
		EPropertyValueSingle,
		EPropertyValueComposite,
		EPropertyValueHandlingNotImplemented
		};
public: // from CContactConverter
#ifdef SYMBIAN_COREAPPS_PLUGIN_API_V2
	static CContactVCardConverter* NewL();
#endif
	CArrayPtr<CContactItem>* ImportL(CContactDatabase& aDb,RReadStream& aReadStream,TBool& aImportSuccessful,TInt aOptions,TBool aImportSingle);
	void ExportL(CContactDatabase& aDb,const CContactIdArray& aSelectedContactIds,RWriteStream& aWriteStream,TInt aOptions,const Versit::TVersitCharSet aCharSet, TBool aExportPrivateFields, TInt aCommitNumber);
public: // Utility
	static TBool ContainsExportableData(const TDesC& aText);
	static TBool ContainsImportableData(const TDesC& aText, TVersitPropertyType aType, TCntVCardImportType aImportType);
private:
	static TBool ContainsData(const TDesC& aText);
	void doImportL(CVCardToContactsAppConverter& aConverter, CParserVCard& aVCard, CContactDatabase& aDb, TInt aOption, TBool aIncAccessCount, TBool aDecAccessCount, TBool& aImportSuccessful, CArrayPtr<CContactItem>* aContactItems, TBool aIsInTransaction);
 	};

#endif

