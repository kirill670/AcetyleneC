// BIF.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

//
// BIO-message Information File (BIF) Reader and Writer Classes
// 

#if !defined(__BIF_H__)
#define __BIF_H__

#if !defined(__APMREC_H__)
#include <apmrec.h>				// for TRecognitionConfidence
#endif 


#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


// Classes defined
class CBioInfoFileReader;
class CBioInfoFileWriter;

// Classes referenced:
class CFileStore;
class CFbsBitmap;

#include <f32file.h>


//
// Constants
/** 2nd UID of BIF file stores. */
const TUid KUidBioInfoFile={0x10005233};		// unicode Uid, used as 2nd Uid of file store
/** Indicates that when opening the message no application should be launched. */
const TUid KUidBioUseNoApp={0x00000000};			
/** Indicates that when opened the message is to be viewed by the default application. */
const TUid KUidBioUseDefaultApp={0x100052b2};		
/** Maximum length of BIO_INFO_FILE description field. */
const TInt KMaxBioDescription=128;
/** Maximum length of ID text field. */
const TInt KMaxBioIdText=128;
/** Unused from v7.0.

Previously, it specified the maximum length of a command line to BIFTOOL. */
const TInt KMaxBioCommandLine=256;
/** Maximum length of BIO_INFO_FILE file_extension field. */
const TInt KMaxBioFileExtension=10;


//
// Data types
/** Buffer to hold a BIF ID identifier text field. */
typedef TBuf<KMaxBioIdText> TBioMsgIdText;
/** Unused from v7.0.

Previously, it held a command line to BIFTOOL. */
typedef TBuf<KMaxBioCommandLine> TBioCommand;

/** Identifies bearers for the BIF ID type field.

It is the C++ equivalent of the resource enum ID_TYPE. */
enum TBioMsgIdType 
	{
	/** Unknown.
	
	Item will not be used in matching. */
	EBioMsgIdUnknown,
	/** MIME type.
	
	Specifies that a bearer that transports MIME messages (e.g. e-mail) should 
	match the MIME type against the ID text field. */
	EBioMsgIdIana,
	/** Narrow band (SMS).
	
	Specifies that the SMS bearer should match messages against the ID port field. */
	EBioMsgIdNbs,

	//Receive over WDP
	/** WAP WDP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWap,
	/** WAP secure WDP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWapSecure,

	//Receive over WSP
	/** WAP WSP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWsp,
	/** WAP secure WSP.
	
	Specifies that the WAP bearer should match messages against the ID port field. */
	EBioMsgIdWspSecure
	};

class TBioMsgId 
/** Encapsulates an ID from a BIF (BIO_INFO_FILE). 
@internalTechnology
@released
*/
	{
public:
	/** Identifies the bearer that should use this resource to match messages. */
	TBioMsgIdType iType;
	/** Confidence level. */
	CApaDataRecognizerType::TRecognitionConfidence iConfidence;			// from APMREC.H
	/** Text field that can be used to match the message to this BIO type. */
	TBioMsgIdText iText;
	/** Receiving port number that can be used to match the message to this BIO type. */
	TUint16 iPort;
	/** Expected receiving character set of messages. */
	TUid iCharacterSet;
	/** This is available for 3rd party use for BIO message type identity specific 
	data. */
	TInt16 iGeneralIdData;
	};

#if !defined(__BIFBASE_H__)
#include "bifbase.h"				// for CBioInfoFile
#endif 

//////////////////////////////////////////////////////////////////////////////////////////
// BIF Reader Class
//
// Allows reading (all but the icons) from an existing BIF file.
//////////////////////////////////////////////////////////////////////////////////////////
class CBioInfoFileReader : public CBioInfoFile
/** BIO information file (BIF) reader. 
@publishedAll
@released
*/
	{
public:
	//
	// Construction/destruction
	IMPORT_C static CBioInfoFileReader* NewLC(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid=KNullUid);
	IMPORT_C static CBioInfoFileReader* NewL(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid=KNullUid);
	IMPORT_C ~CBioInfoFileReader();

	//
	// Data getters
	IMPORT_C TUid MessageTypeUid() const;
#ifndef __HIDE_MESSAGING_API_V1__		
	IMPORT_C TUid MessageParserUid() const; // Replaced by MessageParserName()
#endif // __HIDE_MESSAGING_API_V1__
#ifdef __MESSAGING_API_V2__	
	IMPORT_C const TPtrC MessageParserName() const;
#ifndef __HIDE_MESSAGING_API_V1__		
	IMPORT_C TBool IsSecureBIF() const;
#endif // __HIDE_MESSAGING_API_V1__
#endif // __MESSAGING_API_V2__
	IMPORT_C TUid MessageAppUid() const;
	IMPORT_C TUid MessageAppCtrlUid() const;
	IMPORT_C TInt16 GeneralData1() const;
	IMPORT_C TInt16 GeneralData2() const;
	IMPORT_C TInt16 GeneralData3() const;
	IMPORT_C const TPtrC Description() const;			
	IMPORT_C const TPtrC FileExtension() const;			

	IMPORT_C const TPtrC IconsFilename() const;			
	IMPORT_C const CArrayFixFlat<TInt16>* ZoomLevelsLC() const;
	IMPORT_C TInt ZoomLevelsCount() const;			

	IMPORT_C const CArrayFixFlat<TBioMsgId>* IdsLC() const;
	
	inline const TEntry& FileEntry() const;

protected:
	//
	// Construction/destruction
	CBioInfoFileReader(RFs& aFs);
	void ConstructL(const TDesC& aFileName,TUid aMsgTypeUid);

private:
	void InternalizeL(RReadStream& aStream);
	void LoadResourceL(TUid aMsgTypeUid);
	void LoadDataL(TUid aMsgTypeUid);
	TBool IsResFileL() const;
	TBool IsDatFile() const;
#ifdef __MESSAGING_API_V2__
#ifndef __HIDE_MESSAGING_API_V1__	
    TInt FindFullName(TUid aUid, TDes& aFullName) const;
#endif	// __HIDE_MESSAGING_API_V1__
    //
#ifndef __REMOVE_MESSAGING_API_V1__
    TBool iSecureBIF;
#endif // __REMOVE_MESSAGING_API_V1__
#endif // __MESSAGING_API_V2__
	TEntry iEntry;
	HBufC* iFileName;
	};


#ifndef __HIDE_MESSAGING_API_V1__	
//////////////////////////////////////////////////////////////////////////////////////////
// BIF Writer Class
//
// Allows writing of all data to a new BIF file. On construction a new BIF file is always
// created. If on construction the BIF file already exists then it is deleted and a new 
// one created. BIF files are intended to be Write-Once-Read-Many in nature.
//////////////////////////////////////////////////////////////////////////////////////////
class CBioInfoFileWriter : public CBioInfoFile
/** BIO information file (BIF) writer. 

This allows writing of data to a new BIF file. On construction, a new BIF file is always
created. If on construction the BIF file already exists, then it is deleted and a new 
one created. BIF files are intended to be Write-Once-Read-Many in nature.

@internalTechnology

@deprecated
*/
	{
public:
	//
	// Construction/destruction
	IMPORT_C static CBioInfoFileWriter* NewLC(RFs& aFs,const TDesC& aFileName,TUid aMsgTypeUid);
	IMPORT_C ~CBioInfoFileWriter();

	IMPORT_C void StoreL();

	//
	// Data setters
	IMPORT_C void SetMessageTypeUid(TUid aValue);
	IMPORT_C void SetMessageParserUid(TUid aValue); // Replaced by SetMessageParserName()
#ifdef __MESSAGING_API_V2__	
	IMPORT_C void SetMessageParserName(const TPtrC& aValue);
#endif
	IMPORT_C void SetMessageAppUid(TUid aValue);
	IMPORT_C void SetMessageAppCtrlUid(TUid aValue);
	IMPORT_C void SetGeneralData1(TInt16 aValue);
	IMPORT_C void SetGeneralData2(TInt16 aValue);
	IMPORT_C void SetGeneralData3(TInt16 aValue);
	IMPORT_C void SetDescription(const TPtrC& aValue);
	IMPORT_C void SetFileExtension(const TPtrC& aValue);
	IMPORT_C void SetIconsFilename(const TFileName& aValue);
	IMPORT_C void SetZoomLevelsL(const CArrayFix<TInt16>& aZoomLevelArray);
	IMPORT_C void AddIdL(const TBioMsgId& aValue);	
	
private:
	//
	// Construction/destruction
	CBioInfoFileWriter(RFs& aFs);
	void ConstructL(const TDesC& aFileName,TUid aMsgTypeUid);

	void ExternalizeL(RWriteStream& aStream) const;

private:
	CStoreMap* iMap;	
	CFileStore* iStore;
#ifdef __MESSAGING_API_V2__	
	HBufC* iFileName;
#endif
	};
#endif // __HIDE_MESSAGING_API_V1__	

#include "bif.inl"

#endif

