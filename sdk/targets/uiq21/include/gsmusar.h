// GSMUSAR.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

/**
 * @file gsmusar.h Segmentation and reassembly utility classes
 */

#if !defined(__GSMUSAR_H__)
#define __GSMUSAR_H__

#include <charconv.h>
#include "gsmubuf.h"
#include "gsmuelem.h"


class CSmsBufferSegmenter : public CBase
/**
 * Segments unpacked data from a CsmsBufferBase
 */
	{
friend class CSmsUserData;
public:
// Construction / destruction methods
	IMPORT_C static CSmsBufferSegmenter* NewLC(CSmsAlphabetConverter& aAlphabetConverter,const CSmsBufferBase& aBuffer,TInt aSegmentSize=0);
	IMPORT_C ~CSmsBufferSegmenter();

// Segmentation methods
	void Reset();
	IMPORT_C TBool SegmentNextL(TDes8& aSegmentBuffer);
	IMPORT_C TInt TotalConvertedLengthL();
	TBool MoreL();

protected:
// Protected construction methods
	CSmsBufferSegmenter(CSmsAlphabetConverter& aAlphabetConverter,const CSmsBufferBase& aBuffer,TInt aSegmentSize);
	void ConstructL();

// Protected helper methods
	virtual TBool DoSegmentNextL(TDes8& aSegmentBuffer,TInt aSegmentSize);
	void CheckConvertedBufferAllocL(TInt aMaxLength);
	TInt ElementsToReturnFromConvertedBufferL(TInt aSegmentSize);

protected:
// Private data
	CSmsAlphabetConverter& iAlphabetConverter;
	const CSmsBufferBase& iSmsBuffer;
	TInt iElementsExtracted;
	TInt iSegmentSize;
	HBufC8* iConvertedBuffer;
	TPtr8 iConvertedBufferPtr;
	};

class CSmsEMSBufferSegmenter : public CSmsBufferSegmenter
	{
public:
	IMPORT_C static CSmsEMSBufferSegmenter* NewLC(CSmsAlphabetConverter& aAlphabetConverter,const CSmsBufferBase& aBuffer, TInt aSegmentSize=0);

	/**
	 * Extracts Segment size out of the Sms Buffer and converts it into aSegmentBuffer
	 *
	 * @param aNativeChars Number of native chars to encode.
	 * @param aSegement Size of the FOREIGN segment to extract
	 * @param TBool returns ETrue if last segment.
	 */
	IMPORT_C TBool SegmentNextL(TDes8& aSegmentBuffer,TInt aSegmentSize);

	/**
	 * unlike SegmentNextL Segment will encode the amout of native chars into a SegmentBuffer
	 * WARNING: This method can not be used after a SegmentNextL
	 *
	 * @param aSegmentBuffer Buffer to convert into.
	 * @param aNativeChars Number of native chars to encode.
	 * @param aSegmentMax The Ceiling the encode will not go past.
	 * @returns TInt the number of NATIVE characters added
	 */
	TInt SegmentL(TDes8& aSegmentBuffer, TInt aNativeChars, TInt aSegmentMax);

protected:
	CSmsEMSBufferSegmenter(CSmsAlphabetConverter& aAlphabetConverter,const CSmsBufferBase& aBuffer,TInt aSegmentSize);

	};

//
// TSmsBufferReassembler - reassembles (unpacked) data to CSmsBufferBase
//

class TSmsBufferReassembler
/**
 * TSmsBufferReassembler - reassembles (unpacked) data to CSmsBufferBase
 */
	{
public:
// Construction / destruction methods
	IMPORT_C TSmsBufferReassembler(CSmsAlphabetConverter& aAlphabetConverter,CSmsBufferBase& aBuffer);

// Reassembly methods
	IMPORT_C void ReassembleNextL(const TDesC8& aSegmentBuffer,TBool aIsLast);

private:
	CSmsAlphabetConverter& iAlphabetConverter;
	CSmsBufferBase& iSmsBuffer;
	};

#endif
