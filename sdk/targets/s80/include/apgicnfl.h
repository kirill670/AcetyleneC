// APGICNFL.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __APGICNFL_H__
#define __APGICNFL_H__

#include <apadef.h>
#include <apaid.h>
#include <bitdev.h>
#include <apmstd.h>
#include <badesca.h>

// classes defined:
class CApaMaskedBitmap;
class CApaAppInfoFile;
class CApaAppInfoFileReader;
class CApaAppInfoFileWriter;
//
// classes referenced:
class CPersistentStore;
//

/**
@publishedAll 
@released
*/
#ifdef _UNICODE
#define KUidAppInfoFile KUidAppInfoFile16
#else
#define KUidAppInfoFile KUidAppInfoFile8
#endif

/**
@publishedAll
@deprecated
*/
const TUid KUidAppInfoFile8={268435562};

/**
@publishedAll
@released
*/
const TUid KUidAppInfoFile16={0x10003A38};

/**
@internalComponent
*/
const TUid KUidAppInfoFileVersion2={0x101fb032};

class CApaMaskedBitmap : public CFbsBitmap
/** An application icon.

This is a bitmap and a mask, managed by the Font and Bitmap server.

An object of this type is passed to RApaLsSession::GetAppIcon() to fetch a 
suitable application icon.

@publishedAll
@released
@see RApaLsSession::GetAppIcon() */
	{
public:
	IMPORT_C static CApaMaskedBitmap* NewLC();
	IMPORT_C static CApaMaskedBitmap* NewL(CApaMaskedBitmap* aSourceIcon);
	//
	IMPORT_C CFbsBitmap* Mask() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	//
	IMPORT_C ~CApaMaskedBitmap();
	void SetRomBitmapL(TUint8* aRomPointer);
	IMPORT_C void SetMaskBitmap(CFbsBitmap* aMask);
private:
	CApaMaskedBitmap();
	void ConstructL();
private:
	CFbsBitmap* iMask;
	};

/**
@internalComponent
*/
enum TAifVersion
// The order here is important, only ever APPEND to the list
	{
	EAifVersionOriginal,
	EAifVersionAddsDataType,
	EAifVersionAddsViewData,
	EAifVersionAddsFileOwnershipInfo
	};


class CApaAIFCaption : public CBase
//
// Represents a caption in an AIF during reading and writing of the file.
/**
@internalComponent
*/
	{
public:
	~CApaAIFCaption();
	CApaAIFCaption();
	void ConstructL(TLanguage aLanguage,const TDesC& aCaption);
	static CApaAIFCaption* NewLC(TLanguage aLanguage,const TDesC& aCaption);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TLanguage Language() const;
	TApaAppCaption Caption() const;
public:
	HBufC* iCaption;
	TLanguage iLanguage;
	};

class CApaAIFViewData : public CBase
//
// Represents the data associated with an application view described in an AIF
// during reading and writing of the file.
// implementation class
/**
@internalComponent
*/
	{
public:
	IMPORT_C TApaAppCaption CaptionL(TLanguage aLanguage) const;
	IMPORT_C CApaMaskedBitmap* IconByIndexL(TInt aIndex) const;
	IMPORT_C TInt NumberOfIcons() const;
	IMPORT_C TUid ViewUid() const;
	IMPORT_C TInt ScreenMode() const;
public:
	~CApaAIFViewData();
	static CApaAIFViewData* NewLC();
	static CApaAIFViewData* NewLC(const CApaAIFViewData& aSourceData);
	void InternalizeL(RReadStream& aStream);		
	void ExternalizeL(RWriteStream& aStream) const;
	void SetScreenMode(TInt aScreenMode);
	void AddCaptionL(TLanguage aLanguage,const TDesC& aCaption);
	void AddIconL(CApaMaskedBitmap& aIcon);
	void AddIconIndexL(TInt aIndex);
	void SetViewUid(TUid aUid);
	void LoadIconsL(const TDesC& aFileName, TUint aMbmOffset);
private:
	CApaAIFViewData();
	void ConstructL();
	void ConstructL(const CApaAIFViewData& aSourceData);
private:
	TInt iScreenMode;
	CArrayPtr<CApaMaskedBitmap>* iIconArray;
	CArrayPtr<CApaAIFCaption>* iCaptionArray;
	TUid iViewUid;
	CArrayFixFlat<TInt>* iIconIndexArray;		// used for AIF version 2 format
	};



class CApaAppInfoFile : public CBase
/**
@internalComponent
*/
	{
public:
	~CApaAppInfoFile();
	//
protected:
	CApaAppInfoFile(RFs& aFs);
	void ConstructL();
protected:

	class TCaptionHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<HBufC> iCaption;
		TLanguage iLanguage;
		};
private:
	class TIconHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<CApaMaskedBitmap> iIcon;	// Used for old AIF format Internalize
		TInt iIconSideInPixels;
		TSwizzle<CFbsBitmap> iIconMain;		// Used for new AIF format
		TSwizzle<CFbsBitmap> iIconMask;		// Used for new AIF format
		};
	class TDataTypeHeader
		{
	public:
		// header info only
		void InternalizeL(RReadStream& aStream); 			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<TDataType> iDataType;
		TDataTypePriority iPriority;
		};
	class TViewDataHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<CApaAIFViewData> iViewData;
		};
	class TFileOwnershipInfoHeader
		{
	public:
		void InternalizeL(RReadStream& aStream);			// internalizes the header info only
		void ExternalizeL(RWriteStream& aStream) const;		// externalizes the header info only
	public:
		TSwizzle<HBufC> iOwnedFileName;
		};
protected:
	RFs& iFs;
	CPersistentStore* iStore;
	CArrayFix<TCaptionHeader>* iCaptionHeaderArray;
	CArrayFix<TIconHeader>* iIconHeaderArray;
	CArrayFix<TDataTypeHeader>* iDataTypeHeaderArray;
	CArrayFix<TViewDataHeader>* iViewDataHeaderArray;
	CArrayFix<TFileOwnershipInfoHeader>* iFileOwnershipInfoHeaderArray;
	TApaAppCapability iCapability;
	};


class CApaAppInfoFileReader : public CApaAppInfoFile
/** Aif file reader.

Aif files contain information about an application, including its icons and 
captions.

An application can get a reader for its own aif file by calling CEikApplication::OpenAppInfoFileLC(). 

@publishedAll
@released */
	{
public:
	IMPORT_C static CApaAppInfoFileReader* NewLC(RFs& aFs, const TDesC& aFileName,TUid aApplicationUid=KNullUid);
	IMPORT_C static CApaAppInfoFileReader* NewL(RFs& aFs, const TDesC& aFileName,TUid aApplicationUid=KNullUid);
	//
	IMPORT_C void Capability(TDes8& aInfo) const;
	IMPORT_C TApaAppCaption CaptionL(TLanguage aLanguage);
	
	IMPORT_C CApaMaskedBitmap* CreateMaskedBitmapL(TInt aIconSideInPixels); // If there are no bitmaps in the file this method leaves with KErrNotFound
	// Not available until ER6
	CApaMaskedBitmap* CreateMaskedBitmapByIndexLC(TInt aIndex); // If there are no bitmaps in the file this method leaves with KErrNotFound
	IMPORT_C TInt NumberOfBitmaps() const;

	// Not available till ER5
	IMPORT_C void DataTypesSupportedL(CArrayFix<TDataTypeWithPriority>& aTypeList) const;
	//

	// Not available till ER6.1
	IMPORT_C void GetViewsL(CArrayPtr<CApaAIFViewData>& aViewList) const;
	IMPORT_C void GetOwnedFilesL(CDesCArray& aOwnedFilesList) const;
	//	

	// utility function
	IMPORT_C static void StretchDrawL(CFbsBitmap* aSource,CFbsBitmap* aTarget,TSize aSizeInPixels);
	//
	IMPORT_C ~CApaAppInfoFileReader();
public:
	static void GetAifFileNameL(const TDesC& aFullName,TDes& aAifName);
private:
	CApaAppInfoFileReader(RFs& aFs);
	void InternalizeL(RReadStream& aStream);
	void ConstructL(const TDesC& aFileName,TUid aUid);
	void LoadAifFileVersionTwoL(const TDesC& aFileName, TUid aMostDerivedUid);
	void AddIconHeadersL(const TDesC& aFileName, TInt32 aFileOffset, TInt aNumIcons);
private:
	HBufC* iDefaultCaption;
	TUint8* iRomPointer;
	TInt iMbmOffset;
	HBufC* iAifFileName;
	};

class CApaAppInfoFileWriter : public CApaAppInfoFile
/**
Aif file writer.

This class writes application information, including icons and captions into the aif file.

@publishedAll
@deprecated */
	{
public:
	IMPORT_C static CApaAppInfoFileWriter* NewLC(RFs& aFs, const TDesC& aFileName,TUid aApplicationUid);
	//
	IMPORT_C TInt SetCapability(const TDesC8& aInfo);
	IMPORT_C void AddCaptionL(TLanguage aLanguage,const TDesC& aCaption);
	IMPORT_C void AddIconL(const TDesC& aIconFileName);
	IMPORT_C void AddIconL(CApaMaskedBitmap& aIcon);
	
	// Not available till ER5
	IMPORT_C void AddDataTypeL(const TDataTypeWithPriority& aTypePriority);
	//

	// Not available till ER6.1
	IMPORT_C void AddViewL(TUid aViewUid);
	IMPORT_C void AddViewL(TUid aViewUid,TInt aScreenMode);
	IMPORT_C void AddViewCaptionL(TLanguage aLanguage,const TDesC& aCaption,TUid aViewUid);
	IMPORT_C void AddViewIconL(CApaMaskedBitmap& aIcon,TUid aViewUid);
	IMPORT_C void StoreViewL(TUid aViewId);
	IMPORT_C void AddOwnedFileL(const TDesC& aOwnedFileName);
	//
	
	IMPORT_C void StoreL();
	//
	IMPORT_C ~CApaAppInfoFileWriter();
private:
	CApaAppInfoFileWriter(RFs& aFs);
	void ExternalizeL(RWriteStream& aStream) const;
	void ConstructL(const TDesC& aFileName,TUid aUid);
private:
	CStoreMap* iMap;
	};


class CApaAppCaptionFileReader : public CBase
/**
@internalComponent
*/
	{
public:
	CApaAppCaptionFileReader(RFs& aFs,const TDesC& iAppFileName);
	void GetCaptionsL(TApaAppCaption& aCaption,TApaAppCaption& aShortCaption);
private:	
	RFs& iFs;
	TFileName iCaptionFileName;
	};

class AppInfoFileUtils
// Internal utilities providing helper functions for non-ROM localisation
/**
@internalComponent
*/
	{
public: // For internal use only
	IMPORT_C static void GetAifFileName(const RFs& aFs,TDes& aAifName);
public:
	static void GetAifFileNameL(const RFs& aFs,const TDesC& aFullName,TDes& aAifName);
	};

#endif

