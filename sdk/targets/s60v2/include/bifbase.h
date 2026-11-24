// BifBase.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd. All rights reserved.
//

//
// Base classes for BIO-message Information File (BIF) Reader and Writer
// 

#ifndef __BIFBASE_H__
#define __BIFBASE_H__


#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


#include <s32std.h>				// for TSwizzle


//////////////////////////////////////////////////////////////////////////////////////////
// Base Class for Reader and Writer classes
//////////////////////////////////////////////////////////////////////////////////////////
class CBioInfoFile : public CBase
/**
@internalTechnology
@released
*/
	{
public:
	//
	// Destruction
	~CBioInfoFile();

protected:
	//
	// Construction
	CBioInfoFile(RFs& aFs);
	void ConstructL();

protected:
	
	//
	// Classes for complex data structures within BIF file
	class CIdHeader : public CBase
		{
	public:
		CIdHeader();
		~CIdHeader();

		void InternalizeL(RReadStream& aStream);			
		void ExternalizeL(RWriteStream& aStream) const;		

	public:
		TBioMsgIdType iType;
		CApaDataRecognizerType::TRecognitionConfidence iConfidence;			// from APMREC.H
		TSwizzle<HBufC> iText;
		TUint16 iPort;
		TUid iCharacterSet;
		TInt16 iGeneralIdData;
		};

	class TIconZoomLevel
		{
	public:
		void InternalizeL(RReadStream& aStream);			
		void ExternalizeL(RWriteStream& aStream) const;		

	public:
		TInt16 iZoomLevel;
		};
	// End of complex data structure classes
	//


protected:
	RFs& iFs;

	//
	// Simple data to be read/write to/from BIF file
	TUid iMessageTypeUid;
	
#ifndef __REMOVE_MESSAGING_API_V1__	
	TUid iMessageParserUid;
#endif // __REMOVE_MESSAGING_API_V1__

#ifdef __MESSAGING_API_V2__
	TFileName iMessageParserName;
#ifndef __REMOVE_MESSAGING_API_V1__
	TBool iSecureBIF;
#endif // __REMOVE_MESSAGING_API_V1__
#endif // __MESSAGING_API_V2__
	
	TUid iMessageAppUid;
	TUid iMessageAppCtrlUid;
	TBuf<KMaxBioDescription> iDescription;
	TInt16 iGeneralData1;
	TInt16 iGeneralData2;
	TInt16 iGeneralData3;
	TBuf<KMaxBioFileExtension> iFileExtension;
	
	TBuf<KMaxFileName> iIconsFilename;
		
	//
	// Complex data to be read/write to/from BIF file
	CArrayPtrFlat<CIdHeader>* iIdHeaderArray;
	CArrayFix<TIconZoomLevel>* iIconZoomLevelArray;
	};

#endif
