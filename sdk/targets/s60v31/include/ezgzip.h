// EZGzip.h
//
// Copyright (c) 2003-2004 Symbian Software Ltd. All rights reserved.
//

#ifndef __GZIP_H__
#define __GZIP_H__

#include <EZDecompressor.h>
#include <EZCompressor.h>
#include <EZFilebuffer.h>

/**
 * @publishedAll 
 * @released
 */
class TEZGZipHeader
	{

public:
	IMPORT_C TEZGZipHeader();
	IMPORT_C ~TEZGZipHeader();
	
public:
	TUint8 iId1;
	TUint8 iId2;
	TUint8 iCompressionMethod;
	TUint8 iFlags;
	TInt32 iTime;
	TUint8 iExtraFlags;
	TUint8 iOs;
	TInt16 iXlen;
	HBufC8* iExtra;
	HBufC8* iFname;
	HBufC8* iComment;
	TInt16 iCrc;
	};

/**
 * @publishedAll 
 * @released
 */
class TEZGZipTrailer
	{
public:
	IMPORT_C TEZGZipTrailer();
	IMPORT_C TEZGZipTrailer(TInt32 aCrc, TInt32 aSize);
public:
	TInt32 iCrc32;
	TInt32 iSize;
	};

/**
 * @publishedAll 
 * @released
 */
class EZGZipFile
	{
public:
	
	enum { 	ENotGZipFile = KEZlibErrNotGZipFile, 					
			EInvalidCompressionMethod = KEZlibErrInvalidCompression,
			EBadGZipHeader= KEZlibErrBadGZipHeader, 				
			EBadGZipTrailer = KEZlibErrBadGZipTrailer, 				
			EBadGZipCrc = KEZlibErrBadGZipCrc };					
	enum { EFText = 0, EFHcrc = 1, EFExtra = 2, EFName = 3, EFComment = 4};

public:
	IMPORT_C static void ReadHeaderL(RFile &aFile, TEZGZipHeader &aHeader);
	IMPORT_C static void WriteHeaderL(RFile &aFile, TEZGZipHeader &aHeader);
	IMPORT_C static void ReadTrailerL(RFile &aFile, TEZGZipTrailer &aTrailer);
	IMPORT_C static void WriteTrailerL(RFile &aFile, TEZGZipTrailer &aTrailer);
	IMPORT_C static void LocateAndReadTrailerL(RFs &aRfs, const TDesC &aFname, TEZGZipTrailer &aTrailer);
	IMPORT_C static TBool IsGzipFile(RFs &aRfs, const TDesC &aFname);
	IMPORT_C static TBool IsGzipFileL(RFs &aRfs, const TDesC &aFname);

private:
	static void ReadStringIntoDescriptorL(RFile &aFile, HBufC8 **aDes);

public:
	static const TUint8 ID1;
	static const TUint8 ID2;
	};

/**
 * @publishedAll 
 * @released
 */
NONSHARABLE_CLASS(CEZFileToGzipBM) : public CEZFileBufferManager
	{
public:

	static CEZFileToGzipBM* NewLC(RFile &aInput, RFile &aOutput, TInt aBufferSize);
	static CEZFileToGzipBM* NewL(RFile &aInput, RFile &aOutput, TInt aBufferSize);

	virtual void InitializeL(CEZZStream &aZStream);
	virtual void NeedInputL(CEZZStream &aZStream);
	TInt32 Crc() const { return iCrc; } ;

private:
	CEZFileToGzipBM(RFile &aInput, RFile &aOutput);
private:
	TInt32 iCrc;
	};

/**
 * @publishedAll 
 * @released
 */
NONSHARABLE_CLASS(CEZGzipToFileBM) : public CEZFileBufferManager
	{
public:

	static CEZGzipToFileBM* NewLC(RFile &aInput, RFile &aOutput, TInt aBufferSize);
	static CEZGzipToFileBM* NewL(RFile &aInput, RFile &aOutput, TInt aBufferSize);

	virtual void FinalizeL(CEZZStream &aZStream);
	virtual void NeedOutputL(CEZZStream &aZStream);
	TInt32 Crc() const { return iCrc; } ;

private:
	CEZGzipToFileBM(RFile &aInput, RFile &aOutput);
private:
	TInt32 iCrc;
	};


/**
 * @publishedAll 
 * @released
 */
class CEZGZipToFile : public CBase
	{
public:
	~CEZGZipToFile();

	IMPORT_C static CEZGZipToFile* NewLC(RFs &aRfs, const TDesC &aGzFileName, RFile &aOutput, TInt aBufferSize = 0x8000);
	IMPORT_C static CEZGZipToFile* NewL(RFs &aRfs, const TDesC &aGzFileName, RFile &aOutput, TInt aBufferSize = 0x8000);

	IMPORT_C void ResetL(RFs &aRfs, const TDesC &aGzFileName, RFile &aOutput, TInt aBufferSize = 0x8000);

	IMPORT_C TBool InflateL();

private:
	CEZGZipToFile();
	void ConstructL(RFs &aRfs, const TDesC &aGzFileName, RFile &aOutput, TInt aBufferSize);
	void InitialiseBufManL(RFs &aRfs, const TDesC &aGzFileName, RFile &aOutput, TInt aBufferSize);
private:
	CEZDecompressor *iDecompressor;
	CEZGzipToFileBM *iBufferManager;
	TEZGZipTrailer iTrailer;
	RFile iGZipFile;
	TEZGZipHeader iHeader;
	};

/**
 * @publishedAll 
 * @released
 */
class CEZFileToGZip : public CBase
	{
public:
	~CEZFileToGZip();

	IMPORT_C static CEZFileToGZip* NewLC(RFs &aRfs, const TDesC &aGzFileName, RFile &aInput, TInt aBufferSize = 0x8000);
	IMPORT_C static CEZFileToGZip* NewL(RFs &aRfs, const TDesC &aGzFileName, RFile &aInput, TInt aBufferSize = 0x8000);

	IMPORT_C void ResetL(RFs &aRfs, const TDesC &aGzFileName, RFile &aInput, TInt aBufferSize = 0x8000);

	IMPORT_C TBool DeflateL();

private:
	CEZFileToGZip();
	void ConstructL(RFs &aRfs, const TDesC &aGzFileName, RFile &aInput, TInt aBufferSize);
	void InitialiseBufManL(RFs &aRfs, const TDesC &aGzFileName, RFile &aInput, TInt aBufferSize);
private:
	CEZCompressor *iCompressor;
	CEZFileToGzipBM *iBufferManager;
	TInt iUncompressedDataSize;
	RFile iGZipFile;
	TEZGZipHeader iHeader;
	};


#endif
