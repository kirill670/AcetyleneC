
// $Revision: 1.1 $

#ifndef _ZIP_FILE_MEMBER_INPUT_STREAM_H_
#define _ZIP_FILE_MEMBER_INPUT_STREAM_H_

#include "zlib.h"
#include "localtypes.h"
#include <s32file.h>

class RZipFileMemberReaderStream : public CBase
	{
friend class CZipFile;

public:
	IMPORT_C ~RZipFileMemberReaderStream();
	IMPORT_C TInt Read(TDes16& aDes, TInt aLength);
	virtual TInt Read(TDes8& aDes, TInt aLength);
	virtual void ReadL(TDes16& aDes, TInt aLength);

	void Release();
	void Close();

private:

	RZipFileMemberReaderStream(CZipFile&, TUint32, TUint32, TUint32);
	virtual TInt Read(void);
	virtual TInt Read(TByte*, TUint32, TUint32*);

	TInt GetBytes(TByte*, TUint32, TUint32*);
	TInt GetBytes(void);
	TInt GetCompressedBytes(void);
	TInt GetStoredBytes(TByte*, TUint32, TUint32*);
	
	void ReadL(TDes8&);
	void ReadL(TDes16&);
	void ReadL(TDes8&, TChar);
	void ReadL(TDes16&, TChar);
	void ReadL(TUint8*, TInt);
	void ReadL(TUint16*, TInt);
	void ReadL(RWriteStream&);
	void ReadL(RWriteStream&, TInt);
	void ReadL(TInt);

	TInt8 ReadInt8L();
	TInt16 ReadInt16L();
	TInt32 ReadInt32L();
	TUint8 ReadUint8L();
	TUint16 ReadUint16L();
	TUint32 ReadUint32L();

	TReal32 ReadReal32L();
	TReal64 ReadReal64L();

	void PushL();
	void Pop();
	void Attach(MStreamBuf*);
	void Detach();
	MStreamBuf* Source();


private:

	enum
		{
		KBytesSize    		 = 192,
		kCompressedBytesSize = 64
		};
		
private:
	
	CZipFile& 	iZipFile;
	TUint32   	iCompressionMethod;
	z_stream  	iStream;
	TUint32     iCompressedSize;
	TUint32     iFileOffset;
	TUint32     iOffset;
	TBool       iDone;
	TByte		iBytes[KBytesSize];
	TUint32     iBytesLength;
	TUint32     iBytesOffset;
	TByte       iCompressedBytes[kCompressedBytesSize];
	TUint32     iCompressedBytesOffset;
	};
	
#endif /* !_ZIP_FILE_MEMBER_INPUT_STREAM_H_ */

