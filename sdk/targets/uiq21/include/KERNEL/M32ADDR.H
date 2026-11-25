// M32ADDR.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __M32ADDR_H__
#define __M32ADDR_H__

// Rom header linear address
typedef TUint32 TLinAddr;

// Copied in from m32hal.h
typedef TUint32 TPhysAddr;
typedef TUint32 TPhyAddr;
typedef TUint32 TPde;
typedef TUint32 TPte;

// From k32std.h

#if defined(__BIG_ENDIAN__)
const TUint KRomHeaderLinAddr=0x00200000;
#elif defined(__SINGLE__)
#if defined (__MEIG__)
const TUint KRomHeaderLinAddr=0x00000000;
#endif
#else	// not __SINGLE__
#ifdef __CPU_ARM
const TUint KRomHeaderLinAddr=0x50000000;
#endif
#endif

// From m32hal.h

#ifndef __SINGLE__

// #defines required for assembler code
#if	defined(__CPU_ARM)
	// values for the ARM family
#define USER_DATA_SECTION_BASE			0x00400000
#define USER_CODE_SECTION_BASE			0x20000000
#define USER_DLL_SECTION_BASE			0x30000000
#define USER_DATA_SECTION_END			0x40000000
#define SHADOW_ROM_PAGE_TEMP_ADDR		0x40010000
#define PAGE_DIRECTORY_LINEAR_ADDRESS	0x41000000
#define	PAGE_TABLE_INFO_OFFSET			0x00080000
#define	PAGE_TABLE_INFO_LINEAR_ADDRESS	0x41080000
#define	PAGE_TABLE_LINEAR_BASE			0x42000000
#define ROM_LINEAR_BASE					0x50000000
#define ROM_LINEAR_END					0x58000000
#define HW_SECTION_END_ADDRESS			0x5F000000
#define VIDEO_RAM_LINEAR_ADDRESS		0x5F000000
#define VIDEO_RAM_END_ADDRESS			0x60000000
#define RAM_DRIVE_START_ADDRESS			0x60000000
#define RAM_DRIVE_MAX_SIZE				0x20000000
#define RAM_DRIVE_END_ADDRESS			0x80000000
#define HOME_SECTION_BASE_ADDRESS		0x80000000
#define HOME_SECTION_END_ADDRESS		0x00000000
#define HOME_SECTION_SIZE				0x80000000

// shadow rom ignored in this implementation. So this can be
// inside arm only code.
const TLinAddr	KShadowRomPageTempAddr =	SHADOW_ROM_PAGE_TEMP_ADDR;

#else
#error	no suitable __CPU macro defined
#endif

const TLinAddr	KUserDataSectionBase =		USER_DATA_SECTION_BASE;
const TLinAddr	KUserCodeSectionBase =		USER_CODE_SECTION_BASE;
const TLinAddr	KUserDllDataSectionBase =	USER_DLL_SECTION_BASE;
const TLinAddr	KUserDataSectionEnd =		USER_DATA_SECTION_END;

const TLinAddr	KPageDirectoryLinearAddress =	PAGE_DIRECTORY_LINEAR_ADDRESS;
const TInt 	KPageTableInfoOffset =		PAGE_TABLE_INFO_OFFSET;
const TLinAddr	KPageTableInfoLinearAddress =	PAGE_TABLE_INFO_LINEAR_ADDRESS;
const TLinAddr	KPageTableLinearBase =		PAGE_TABLE_LINEAR_BASE;
const TLinAddr	KRomLinearBase =		ROM_LINEAR_BASE;
const TLinAddr	KRomLinearEnd =			ROM_LINEAR_END;
const TLinAddr	KHwSectionLinearBase =		ROM_LINEAR_END;
const TLinAddr	KHwSectionEndAddress =		HW_SECTION_END_ADDRESS;
const TLinAddr	KVideoRamLinearAddress =	VIDEO_RAM_LINEAR_ADDRESS;
const TLinAddr	KVideoRamEndAddress =		VIDEO_RAM_END_ADDRESS;
const TLinAddr	KRamDriveStartAddress =		RAM_DRIVE_START_ADDRESS;
const TInt	KRamDriveMaxSize =		RAM_DRIVE_MAX_SIZE;
const TLinAddr	KRamDriveEndAddress =		RAM_DRIVE_END_ADDRESS;
const TLinAddr	KHomeSectionBaseAddress =	HOME_SECTION_BASE_ADDRESS;
const TLinAddr	KHomeSectionEndAddress =	HOME_SECTION_END_ADDRESS;
const TLinAddr	KHomeSectionSize =		HOME_SECTION_SIZE;

TPde* const PageDirectory = ((TPde*)KPageDirectoryLinearAddress);

#else	// Single-process build
#ifdef __MEIG__   // This is the SARM build really
const TLinAddr KUserDataSectionBase=0x400000u;
const TLinAddr KUserCodeSectionBase=0x20000000u;
const TLinAddr KUserDllDataSectionBase=0x30000000u;
const TLinAddr KUserDataSectionEnd=0x40000000u;

const TLinAddr KShadowRomPageTempAddr=0x40010000u;
const TLinAddr KPageDirectoryLinearAddress=0x41000000u;
const TInt KPageTableInfoOffset=0x80000;
const TLinAddr KPageTableInfoLinearAddress=0x41080000u;
const TLinAddr KPageTableLinearBase=0x42000000u;
const TLinAddr KRomLinearBase=0x00000000u;
const TLinAddr KRomLinearEnd=0x08000000u;
const TLinAddr KHwSectionEndAddress=0x5F000000u;
const TLinAddr KVideoRamLinearAddress=0x90000000u;
const TLinAddr KVideoRamEndAddress=0x91000000u;
const TLinAddr KRamDriveStartAddress=0x60000000u;
const TInt KRamDriveMaxSize=0x1F000000;
const TLinAddr KRamDriveEndAddress=0x80000000u;
const TLinAddr KHomeSectionBaseAddress=0x80000000u;
const TLinAddr KHomeSectionEndAddress=0x00000000u;
const TLinAddr KHomeSectionSize=0x80000000u;

#endif

// #defines required for assembler code
#define USER_DATA_SECTION_BASE			0x00400000
#define USER_CODE_SECTION_BASE			0x20000000
#define USER_DATA_SECTION_END			0x40000000
#define SHADOW_ROM_PAGE_TEMP_ADDR		0x40010000
#define PAGE_DIRECTORY_LINEAR_ADDRESS	0x41000000
#define	PAGE_TABLE_LINEAR_BASE			0x42000000
#define ROM_LINEAR_BASE					0x00000000
#define ROM_LINEAR_END					0x08000000
#define HW_SECTION_END_ADDRESS			0x5F000000
#define VIDEO_RAM_LINEAR_ADDRESS		0x90000000
#define VIDEO_RAM_END_ADDRESS			0x91000000
#define RAM_DRIVE_START_ADDRESS			0x60000000
#define RAM_DRIVE_MAX_SIZE				0x1F000000
#define RAM_DRIVE_END_ADDRESS			0x80000000
#define HOME_SECTION_BASE_ADDRESS		0x80000000
#define HOME_SECTION_END_ADDRESS		0x00000000
#define HOME_SECTION_SIZE				0x80000000

#endif

// Superpage address

#if defined(__BIG_ENDIAN__)
const TUint KSuperPageLinAddr=0x00101000;
#elif defined(__SINGLE__)
# if defined (__MEIG__)
const TUint KSuperPageLinAddr=0xC0013000;
# endif
#else
# ifdef __CPU_ARM
const TUint KSuperPageLinAddr=0x40000000;
# endif
#endif




#endif // __M32ADDR_H__
