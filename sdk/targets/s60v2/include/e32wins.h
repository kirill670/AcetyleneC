// E32WINS.H
//
// Copyright (c) Symbian Software Ltd 1998-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/


#ifndef __E32WINS_H__
#define __E32WINS_H__

#include <E32STD.H>

enum TEmulatorFlip {EEmulatorFlipRestore,EEmulatorFlipInvert,EEmulatorFlipLeft,EEmulatorFlipRight};

// flip the emulator window
IMPORT_C TInt EmulatorFlip(TEmulatorFlip aEmulatorFlip);

inline TInt EmulatorFlip(TEmulatorFlip aFlip, TInt aScreenNo)
	{return aScreenNo == 0 ? EmulatorFlip(aFlip) : KErrGeneral;}


const TUint KEmulGray2=		0x00000001;
const TUint KEmulGray4=		0x00000002;
const TUint KEmulGray16=	0x00000004;
const TUint KEmulGray256=	0x00000008;
const TUint KEmulColor16=	0x00000010;
const TUint KEmulColor256=	0x00000020;
const TUint KEmulColor4K=	0x00000040;
const TUint KEmulColor64K=	0x00000080;
const TUint KEmulColor16M=	0x00000100;

IMPORT_C void EmulatorColorDepth(TUint& aDepths);

// used by F32
IMPORT_C TPtrC EmulatorDataPath();
IMPORT_C TInt MapEmulatedFileName(TDes& aBuffer,const TDesC& aFileName);

const TInt KMaxLocDrvEnvLength=24;	
IMPORT_C TInt SetLocalDriveMapping(TInt aLocalDriveNum,TChar aDriveNum,const TDesC* aFileSysId=NULL);
IMPORT_C TInt LocalDriveMapping(TInt aLocalDriveNum,TChar& aDriveLetter,TDes* aFileSysId=NULL);
IMPORT_C TInt SetMediaPasswordEnvironmentVar(TInt aLocalDriveNum,TInt aCardNum,const TDesC8& aPasswd);
IMPORT_C TInt SetMediaPasswordEnvironmentVar(const TDesC& anEnvVar,const TDesC& aPasswd);
IMPORT_C TInt MediaPasswordEnvironmentVar(TInt aLocalDriveNum,TInt aCardNum,TDes8& aPasswd);


#endif

