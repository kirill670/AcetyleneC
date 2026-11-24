// f32\inc\f32image.h
//
// Copyright (c) 1996-2001 Symbian Ltd. All rights reserved.
//
/**
@file f32\inc\f32image.h
@internalTechnology
*/

#ifndef __F32IMAGE_H__
#define __F32IMAGE_H__
#include <e32cmn.h>

enum TCpu
/**
@internalTechnology
@released
*/
	{
	ECpuUnknown=0, ECpuX86=0x1000, ECpuArmV4=0x2000, ECpuArmV5=0x2001, ECpuArmV6=0x2002, ECpuMCore=0x4000
	};
//
/**
@internalTechnology
@released
*/
const TInt KOrdinalBase=1;
/**
@internalTechnology
@released
*/
const TUint KImageDll				= 0x00000001u;
/**
@internalTechnology
@released
*/
const TUint KImageNoCallEntryPoint	= 0x00000002u;
/**
@internalTechnology
@released
*/
const TUint KImageFixedAddressExe	= 0x00000004u;

/**
@internalTechnology
@released
*/
const TUint KImageOldJFlag			= 0x00000008u;	// so we can run binaries built with pre 2.00 tools (hdrfmt=0)
/**
@internalTechnology
@released
*/
const TUint KImageOldElfFlag		= 0x00000010u;	// so we can run binaries built with pre 2.00 tools (hdrfmt=0)
/**
@internalTechnology
@released
*/
const TUint KImageABIMask			= 0x00000018u;	// only if hdr fmt not zero
/**
@internalTechnology
@released
*/
const TInt	KImageABIShift			= 3;
const TUint	KImageABI_GCC98r2		= 0x00000000u;	// for ARM
/**
@internalTechnology
@released
*/
const TUint	KImageABI_EABI			= 0x00000008u;	// for ARM

/**
@internalTechnology
@released
*/
const TUint KImageEptMask			= 0x000000e0u;	// entry point type
/**
@internalTechnology
@released
*/
const TInt	KImageEptShift			= 5;
/**
@internalTechnology
@released
*/
const TUint KImageEpt_Eka1			= 0x00000000u;
/**
@internalTechnology
@released
*/
const TUint KImageEpt_Eka2			= 0x00000020u;

/**
@internalTechnology
@released
*/
const TUint KImageUnpaged			= 0x00000100u;

/**
@internalTechnology
@released
*/
const TUint KImagePaged				= 0x00000200u;

/**
@internalTechnology
@released
*/
const TUint KImageHdrFmtMask		= 0x0f000000u;
/**
@internalTechnology
@released
*/
const TInt	KImageHdrFmtShift		= 24;
const TUint KImageHdrFmt_Original	= 0x00000000u;	// without compression support
/**
@internalTechnology
@released
*/
const TUint KImageHdrFmt_J			= 0x01000000u;	// with compression support
const TUint KImageHdrFmt_V			= 0x02000000u;	// with versioning support

/**
@internalTechnology
@released
*/
const TUint KImageImpFmtMask		= 0xf0000000u;
/**
@internalTechnology
@released
*/
const TInt	KImageImpFmtShift		= 28;
const TUint KImageImpFmt_PE			= 0x00000000u;	// PE-derived imports
/**
@internalTechnology
@released
*/
const TUint KImageImpFmt_ELF		= 0x10000000u;	// ELF-derived imports
const TUint KImageImpFmt_PE2		= 0x20000000u;	// PE-derived imports without redundant copy of import ordinals

/**
@internalTechnology
@released
*/
const TUint KImageHWFloatMask		= 0x00f00000u;
const TInt	KImageHWFloatShift		= 20;
const TUint	KImageHWFloat_None		= EFpTypeNone << KImageHWFloatShift; // No hardware floating point used
const TUint KImageHWFloat_VFPv2		= EFpTypeVFPv2 << KImageHWFloatShift; // ARM VFPv2 floating point used

/**
@internalTechnology
@released
*/
const TUint KFormatNotCompressed=0;
/**
@internalTechnology
@released
*/
const TUint KUidCompressionDeflate=0x101F7AFC;


const TUint KUidCompressionBytePair=0x102822AA;


const TUint32 KImageCrcInitialiser	= 0xc90fdaa2u;

// Relocation types
/**
@internalTechnology
@released
*/
const TUint16 KReservedRelocType        = (TUint16)0x0000;
/**
@internalTechnology
@released
*/
const TUint16 KTextRelocType            = (TUint16)0x1000;
/**
@internalTechnology
@released
*/
const TUint16 KDataRelocType            = (TUint16)0x2000;
/**
@internalTechnology
@released
*/
const TUint16 KInferredRelocType        = (TUint16)0x3000;

class RFile;
class E32ImageHeader
/**
@internalTechnology
@released
*/
	{
public:
	inline static TUint ABIFromFlags(TUint aFlags)
		{
		if (aFlags&KImageHdrFmtMask)
			return aFlags & KImageABIMask;
		if (aFlags&KImageOldElfFlag)
			return KImageABI_EABI;
		return KImageABI_GCC98r2;
		}
	inline static TUint EptFromFlags(TUint aFlags)
		{
		if (aFlags&KImageHdrFmtMask)
			return aFlags & KImageEptMask;
		if (aFlags&KImageOldJFlag)
			return KImageEpt_Eka2;
		return KImageEpt_Eka1;
		}
	inline static TUint HdrFmtFromFlags(TUint aFlags)
		{
		if (aFlags&KImageHdrFmtMask)
			return aFlags & KImageHdrFmtMask;
		if (aFlags&KImageOldJFlag)
			return KImageHdrFmt_J;
		return KImageHdrFmt_Original;
		}
	inline static TUint ImpFmtFromFlags(TUint aFlags)
		{
		if (aFlags&KImageHdrFmtMask)
			return aFlags & KImageImpFmtMask;
		if (aFlags&KImageOldElfFlag)
			return KImageImpFmt_ELF;
		return KImageImpFmt_PE;
		}
	inline TUint32 CompressionType() const
		{
		if (HdrFmtFromFlags(iFlags) >= KImageHdrFmt_J)
			return iCompressionType;
		return 0;
		}
	inline TUint32 ModuleVersion() const
		{
		if ((iFlags & KImageHdrFmtMask) >= KImageHdrFmt_V)
			return iModuleVersion;
		return 0x00000000u;
		}
	inline TInt TotalSize() const;
	inline TInt UncompressedFileSize() const;
	inline TUint HeaderFormat() const
		{ return HdrFmtFromFlags(iFlags); }
	inline TUint EntryPointFormat() const
		{ return EptFromFlags(iFlags); }
	inline TUint ImportFormat() const
		{ return ImpFmtFromFlags(iFlags); }
	inline TUint ABI() const
		{ return ABIFromFlags(iFlags); }
	inline void GetSecurityInfo(SSecurityInfo& aInfo) const;
	inline TCpu CpuIdentifier() const;
	inline TProcessPriority ProcessPriority() const;
	inline TUint32 ExceptionDescriptor() const;
	TInt IntegrityCheck(TInt aFileSize);
	static TInt New(E32ImageHeader*& aHdr, RFile& aFile);
public:
	TUint32	iUid1;
	TUint32	iUid2;
	TUint32	iUid3;
	TUint32 iUidChecksum;
	TUint iSignature;			// 'EPOC'
	TUint32	iHeaderCrc;			// CRC-32 of entire header
	TUint32 iModuleVersion;		// Version number for this executable (used in link resolution)
	TUint32 iCompressionType;	// Type of compression used (UID or 0 for none)
	TVersion iToolsVersion;		// Version of PETRAN/ELFTRAN which generated this file
	TUint32 iTimeLo;
	TUint32 iTimeHi;
	TUint iFlags;				// 0 = exe, 1 = dll, 2 = fixed address exe
	TInt iCodeSize;				// size of code, import address table, constant data and export dir
	TInt iDataSize;				// size of initialised data
	TInt iHeapSizeMin;
	TInt iHeapSizeMax;
	TInt iStackSize;
	TInt iBssSize;
	TUint iEntryPoint;			// offset into code of entry point
	TUint iCodeBase;			// where the code is linked for	
	TUint iDataBase;			// where the data is linked for
	TInt iDllRefTableCount;		// filling this in enables E32ROM to leave space for it
	TUint iExportDirOffset;		// offset into the file of the export address table
	TInt iExportDirCount;
	TInt iTextSize;				// size of just the text section, also doubles as the offset for the iat w.r.t. the code section
	TUint iCodeOffset;			// file offset to code section, also doubles as header size
	TUint iDataOffset;			// file offset to data section
	TUint iImportOffset;		// file offset to import section
	TUint iCodeRelocOffset;		// relocations for code and const
	TUint iDataRelocOffset;		// relocations for data
	TUint16 iProcessPriority;	// executables priority
	TUint16 iCpuIdentifier;		// 0x1000 = X86, 0x2000 = ARM
	};

// In KImageHdrFmt_J this extra information is present if and only if iCompressionType != 0
// For subsequent formats it's always there
class E32ImageHeaderComp : public E32ImageHeader
/**
@internalTechnology
@released
*/
	{
public:
	TUint32 iUncompressedSize;	// Uncompressed size of file
								// For J format this is file size - sizeof(E32ImageHeader)
								//  and this is included as part of the compressed data :-(
								// For other formats this is file size - total header size
	};

// Extra header information in KImageHdrFmt_V
class E32ImageHeaderV : public E32ImageHeaderComp
	{
public:
	SSecurityInfo iS;

	// Use iSpare1 as offset to Exception Descriptor
	TUint32 iExceptionDescriptor;   // Offset in bytes from start of code section to Exception Descriptor, bit 0 set if valid
	TUint32 iSpare2;
	TUint16	iExportDescSize;	// size of bitmap section
	TUint8	iExportDescType;	// type of description of holes in export table
	TUint8	iExportDesc[1];		// description of holes in export table - extend
	};

// export description type
const TUint	KImageHdr_ExpD_NoHoles			=0x00;	// no holes, all exports present
const TUint	KImageHdr_ExpD_FullBitmap		=0x01;	// full bitmap present
const TUint	KImageHdr_ExpD_SparseBitmap8	=0x02;	// sparse bitmap present, granularity 8
const TUint	KImageHdr_ExpD_Xip				=0xff;	// XIP file


inline TInt E32ImageHeader::TotalSize() const
	{
	if (HeaderFormat() == KImageHdrFmt_J && iCompressionType != 0)
		return sizeof(E32ImageHeaderComp);
	return iCodeOffset;
	}

inline TInt E32ImageHeader::UncompressedFileSize() const
	{
	TUint hdrfmt = HeaderFormat();
	if (hdrfmt == KImageHdrFmt_Original || iCompressionType == 0)
		return -1;			// not compressed
	else if (hdrfmt == KImageHdrFmt_J)
		return ((E32ImageHeaderComp*)this)->iUncompressedSize + sizeof(E32ImageHeader);
	else
		return ((E32ImageHeaderComp*)this)->iUncompressedSize + iCodeOffset;
	}

extern const SSecurityInfo KDefaultSecurityInfo;
inline void E32ImageHeader::GetSecurityInfo(SSecurityInfo& aInfo) const
	{
	if (HeaderFormat() >= KImageHdrFmt_V)
		aInfo = ((E32ImageHeaderV*)this)->iS;
	else
		aInfo = KDefaultSecurityInfo;
	}

inline TCpu E32ImageHeader::CpuIdentifier() const
	{
	if (HeaderFormat() >= KImageHdrFmt_V)
		return (TCpu)iCpuIdentifier;
	return (TCpu)iHeaderCrc;
	}

inline TProcessPriority E32ImageHeader::ProcessPriority() const
	{
	if (HeaderFormat() >= KImageHdrFmt_V)
		return (TProcessPriority)iProcessPriority;
	return *(const TProcessPriority*)&iProcessPriority;
	}

inline TUint32 E32ImageHeader::ExceptionDescriptor() const
	{
	if (HeaderFormat() >= KImageHdrFmt_V)
		{
		TUint32 xd = ((E32ImageHeaderV*)this)->iExceptionDescriptor;
		if ((xd & 1) && (xd != 0xffffffffu))
			return (xd & ~1);
		}
	return 0;
	}

class E32ImportBlock
/**
@internalTechnology
@released
*/
	{
public:
	inline const E32ImportBlock* NextBlock(TUint aImpFmt) const;
	inline TInt Size(TUint aImpFmt) const;
	inline const TUint* Imports() const;	// import list if present
public:
	TUint32	iOffsetOfDllName;	// offset of name of dll importing from
	TInt	iNumberOfImports;	// no of imports from this dll
//	TUint	iImport[iNumberOfImports];	// list of imported ordinals, omitted in PE2 import format
	};

inline TInt E32ImportBlock::Size(TUint aImpFmt) const
	{
	TInt r = sizeof(E32ImportBlock);
	if (aImpFmt!=KImageImpFmt_PE2)
		r += iNumberOfImports * sizeof(TUint);
	return r;
	}

inline const E32ImportBlock* E32ImportBlock::NextBlock(TUint aImpFmt) const
	{
	const E32ImportBlock* next = this + 1;
	if (aImpFmt!=KImageImpFmt_PE2)
		next = (const E32ImportBlock*)( (TUint8*)next + iNumberOfImports * sizeof(TUint) );
	return next;
	}

inline const TUint* E32ImportBlock::Imports() const
	{
	return (const TUint*)(this + 1);
	}

class E32ImportSection
/**
@internalTechnology
@released
*/
	{
public:
	TInt iSize;					// size of this section
//	E32ImportBlock[iDllRefTableCount];
	};

class E32RelocSection
/**
@internalTechnology
@released
*/
	{
public:
	TInt iSize;					// size of this relocation section
	TInt iNumberOfRelocs;		// number of relocations in this section
	};

// __F32IMAGE_H__
#endif


