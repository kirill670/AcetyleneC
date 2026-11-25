// BARSC.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __BARSC_H__
#define __BARSC_H__

#include <e32std.h>
#include <f32file.h>

struct SDictionaryCompressionData;
class RDictionaryCompressionBitStream;

/**
 *
 * Accesses a resource file and reads the resource data into a buffer.
 *
 * Interpretation of the data is achieved using the
 * <code>TResourceReader</code> class.
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class RResourceFile
	{
public:
	IMPORT_C RResourceFile();
	IMPORT_C void Close();
	IMPORT_C void OpenL(RFs &aFs,const TDesC &aName);
	IMPORT_C TUidType UidType() const;
	IMPORT_C void ReadL(TDes8 &aDes,TInt aResourceId) const;
	IMPORT_C HBufC8 *AllocReadL(TInt aResourceId) const;
	IMPORT_C HBufC8 *AllocReadLC(TInt aResourceId) const;
	IMPORT_C void ConfirmSignatureL(TInt aSignature);
	IMPORT_C TInt SignatureL() const; // not available before Release 005
	IMPORT_C TBool OwnsResourceId(TInt aResourceId) const;
	inline TInt Offset() const;
private:
	enum
		{
		EFlagIsRomFile																=0x80000000,
		EFlagPotentiallyContainsCompressedUnicode									=0x40000000,
		EFlagDictionaryCompressed													=0x20000000,
		EFlagThirdUidIsOffset														=0x10000000,
		EFlagGenerate_RSS_SIGNATURE_ForFirstUserResource							=0x08000000,
		EFlagFirstResourceIsGeneratedBitArrayOfResourcesContainingCompressedUnicode	=0x04000000,
		EAllFlags																	=0xff000000
		};
	struct SSigRecord
		{
		TInt signature;
		TInt offset;
		};
	class CExtra;
private:
	static void AppendDecompressedUnicode(TDes8& aBuffer,const TDesC8& aCompressedUnicode);
	static HBufC8* DecompressUnicodeL(const TDesC8& aDictionaryDecompressedResourceData,TInt aSizeOfLargestResourceWhenCompletelyUncompressed);
	static HBufC8* DictionaryDecompressedResourceDataLC(TInt aResourceIndex,TUint aFlags,TAny* aFile,TInt aSizeOfLargestResourceWhenCompletelyUncompressed,const SDictionaryCompressionData& aDictionaryCompressionData,const TDesC16& aIndex);
	static void AppendDictionaryCompressionBitStreamL(RArray<RDictionaryCompressionBitStream>& aStackOfDictionaryCompressionBitStreams,TUint aFlags,TAny* aFile,const SDictionaryCompressionData& aDictionaryCompressionData,TInt aStartOfBitData,TInt aStartOfIndex,TInt aIndexEntry);
	static void CloseArrayOfDictionaryCompressionBitStreams(TAny* aArrayOfDictionaryCompressionBitStreams);
	static TInt LittleEndianTwoByteInteger(const TDesC8& aBuffer,TInt aIndexOfFirstByte);
	static void CloseAndDeleteFile(TAny* aFile);
	static void ReadL(TUint aFlags,TAny* aFile,TInt aPos,TDes8& aDes,TInt aLength);
	void ReadL(TInt aPos,TDes8& aDes,TInt aLength) const;
	SSigRecord FirstRecordL() const;
private:
	TAny* iFile; // either an RFile*, or a const TUint8* pointing into ROM
	TInt iSizeOfLargestResourceWhenCompletelyUncompressed;
	HBufC16* iIndex; // basically an array of (unsigned) 16-bit file-positions - this is only used for non-dictionary-compressed resource files
	TInt iOffset; // the position of this member in the class is exposed because Offset is an inline function accessing iOffset
	CExtra* iExtra;
	TUint iFlagsAndNumberOfResources;
private:
	enum
		{
		EOffsetBits	=0xfffff000,
		EIdBits		=0x00000fff
		};
	};

/**
 *
 * Returns the offset value defined for this resource file.
 *
 * This function must not be called until a call to
 * <code>ConfirmSignatureL()</code> has completed successfully, otherwise
 * the value returned by this function may be meaningless.
 *
 * @returns   "TInt"
 *			The offset value defined for this resource file.
 */
inline TInt RResourceFile::Offset() const { return(iOffset); }

#endif
