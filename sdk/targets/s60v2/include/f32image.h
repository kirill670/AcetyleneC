// F32IMAGE.H
//
// Copyright (c) Symbian Software Ltd 1996-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/


enum TCpu {ECpuX86=0x1000, ECpuArm=0x2000, ECpuUnknown=0};

const TUint KImageDll				= 0x00000001u;
const TUint KImageNoCallEntryPoint	= 0x00000002u;
const TUint KImageFixedAddressExe	= 0x00000004u;

const TUint KImageHdrFmtMask		= 0x0f000000u;
const TUint KImageHdrFmt_Original	= 0x00000000u;	// without compression support
const TUint KImageHdrFmt_J			= 0x01000000u;	// with compression support

const TUint KImageImpFmtMask		= 0xf0000000u;
const TUint KImageImpFmt_PE			= 0x00000000u;	// PE-derived imports
const TUint KImageImpFmt_ELF		= 0x10000000u;	// ELF-derived imports

const TUint KFormatNotCompressed=0;
const TUint KUidCompressionDeflate=0x101F7AFC;

class E32ImageHeader
	{
public:
	TUint32	iUid1;
	TUint32	iUid2;
	TUint32	iUid3;
	TUint32	iCheck;
	TUint iSignature;			// 'EPOC'
	TCpu iCpu;					// 0x1000 = X86, 0x2000 = ARM
	TUint iCheckSumCode;		// sum of all 32 bit words in .text
	TUint32 iFormat;
	TVersion iVersion;
	TInt64 iTime;
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
	TUint iCodeOffset;			// file offset to code section
	TUint iDataOffset;			// file offset to data section
	TUint iImportOffset;		// file offset to import section
	TUint iCodeRelocOffset;		// relocations for code and const
	TUint iDataRelocOffset;		// relocations for data
	TProcessPriority iPriority;  // executables priority
	};
//
class E32ImageHeaderComp : public E32ImageHeader
	{
public:
	TUint32 iUncompressedSize;	// Uncompressed size of file (excludes this)
	};

class E32ImportBlock
	{
public:
	TInt Size();
public:
	TUint32	iOffsetOfDllName;	// offset of name of dll importing from
	TInt	iNumberOfImports;	// no of imports from this dll
//	TUint32 iImport[iNumberOfImports];
	};

class E32ImportSection
	{
public:
	TInt iSize;					// size of this section
//	E32ImportBlock[iDllRefTableCount];
	};

class E32RelocSection
	{
public:
	TInt iSize;					// size of this relocation section
	TInt iNumberOfRelocs;		// number of relocations in this section
	};

