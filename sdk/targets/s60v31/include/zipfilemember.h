
// Copyright (c) 2000-2003 By Symbian Ltd. All Rights Reserved.

// $Revision: 1.1 $

#ifndef _ZIP_FILE_MEMBER_H_
#define _ZIP_FILE_MEMBER_H_

#include "LocalTypes.h"

/**
 * @publishedAll 
 * @released
 */
class CZipFileMember: public CBase
	{
friend class CZipFile;

public:

    IMPORT_C TUint32       CRC32(void) const;
	IMPORT_C TUint32		  CompressedSize(void) const;
	IMPORT_C const TFileName*	Name(void) const;
	IMPORT_C TUint32       UncompressedSize(void) const;
	IMPORT_C virtual ~CZipFileMember();
	
private:

	TFileName*	  iName;
	TUint16		  iCompressionMethod;
	TUint32       iCompressedSize;
	TUint32       iUncompressedSize;
	TUint32		  iCRC32;
	TUint32	      iDataOffset;
	};
	
#endif /* !_ZIP_FILE_MEMBER_H_ */

