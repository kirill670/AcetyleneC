// zipfile.h
//
// Copyright (c) 2003-2005 Symbian Software Ltd.  All rights reserved.
//

// $Revision: 1.1 $

#ifndef _ZIP_FILE_H_
#define _ZIP_FILE_H_

#include <e32std.h>
#include <s32file.h>

#include "LocalTypes.h"
#include "ZipArchive.h"
#include "ZipFileMemberInputStream.h"
#include "ZipFileMemberIterator.h"
#include "ZipFileMember.h"

// Forward Class Declaration(s)

class CFileInputStream;
class CZipFileMemberIterator;
class CZipFileMember;


/**
 * @publishedAll 
 * @released
 */
namespace ContentAccess
	{
	class CData;
	}

// End of Forward Class Declaration(s)


/**
 * @publishedAll 
 * @released
 * A CZipFile represents a ZIP archive contained in a single file.
 */
class CZipFile : public CZipArchive
	{
	friend class RZipFileMemberReaderStream;
	friend class CZipFileMemberIterator;

	public:
		enum
			{
			KZipFileError 		= KZipArchiveMinError - 1,
			KZipFileNotFound	= KZipFileError - 1,
			KZipFileIOError 	= KZipFileError - 2
			};

	public:
#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE
		IMPORT_C static CZipFile* NewL(RFs& aFs, RFile& aFile);
#endif
		
		IMPORT_C static CZipFile* NewL(RFs& aFs, const TDesC& aFileName);
		 /** @deprecated in 7.0 */
		IMPORT_C CZipFile(RFs& aFs, const TDesC& aFileName);
		 /** @deprecated in 7.0 */
		IMPORT_C TInt OpenL(void);
		 /** @deprecated in 7.0 */
		IMPORT_C void Close(void);
		IMPORT_C virtual ~CZipFile();

	protected:
		IMPORT_C void ConstructL(const TDesC& aFileName);
		
#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE
		IMPORT_C void ConstructL(RFile& aFile);
#endif

	public:
		IMPORT_C TInt Size(TInt& aSize) const;
    
		IMPORT_C CZipFileMember* MemberL(const TDesC&);
		IMPORT_C CZipFileMember* CaseInsensitiveMemberL(const TDesC&);
		IMPORT_C CZipFileMember* CaseSensitiveOrCaseInsensitiveMemberL(const TDesC&);
		IMPORT_C TInt GetInputStreamL(const CZipFileMember*, RZipFileMemberReaderStream*&);

  		IMPORT_C CZipFileMemberIterator* GetMembersL(void);
	
    
protected:

	/**
	 * @publishedAll 
	 * @released
	 */
	struct TMemberPointer
		{
		TFileName*  iName;
		TUint32		iCentralHeaderOffset;
		TUint32	iLocalHeaderOffset;
		TUint32 iCRC32;
		TUint32	iCompressedSize;
		TUint32	iUncompressedSize;
		};
		
protected:
	TInt FindCentralDirectoryTrailer(TUint32& offset);
    TInt ReadCentralDirectoryTrailer(TUint32 offset, TCentralDirectoryTrailer&);
    TInt ReadCentralDirectoryHeaderL(TCentralDirectoryHeader&, TMemberPointer&);

	TInt ReadLocalHeader(TUint32, TLocalHeader&);
	
	const TMemberPointer* FindMemberPointer(const TDesC&, TBool);
	
    TInt LoadMemberPointersL(void);
    
	RZipFileMemberReaderStream*   MakeInputStreamL(TUint32, TUint32, TUint32, TUint32);
    CZipFileMember* MakeMemberL(TInt);
    CZipFileMember* MakeMemberL(const TMemberPointer&, const TLocalHeader&);
    
    // File I/O Support
    void OpenFileL(const TDesC& aFileName);
  
    TInt Read(TByte*, TUint32);
    TInt Read(TUint16&);
    TInt Read(TUint32&);
    
    TInt Seek(TInt);

	// Misc
	void DeleteMemberPointers(void);

private:
    const TDesC&				iFileName;
    TUint32 iFileLength;
	TCentralDirectoryTrailer iTrailer;
	TMemberPointer*	iMemberPointers;
	RFs& iFs;
	ContentAccess::CData* iData;
	};

#endif /* !_ZIP_FILE_H_ */
