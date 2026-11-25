// A32I80200.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __A32I80200_H__
#define __A32I80200_H__
#include <e32std.h>
#include <k32std.h>


// Maximum number of interrupt sources
const TInt KMaxInterrupts = 34;
const TInt KMaxIntInterrupts=2;
const TInt KMaxExtInterrupts=32;

/**
 * Each interrupt must have a name by which other code refers to it.
 */

_LIT8(KInterruptBCU, "BCU");
_LIT8(KInterruptPMU, "PMU");

_LIT8(KInterruptExt00,	"EXT00");	// DMA0
_LIT8(KInterruptExt01,	"EXT01");	// DMA1
_LIT8(KInterruptExt02,	"EXT02");	// DMA2
_LIT8(KInterruptExt03,	"EXT03");	// reserved
_LIT8(KInterruptExt04,	"EXT04");	// PMON
_LIT8(KInterruptExt05,	"EXT05");	// AAU
_LIT8(KInterruptExt06,	"EXT06");	// reserved
_LIT8(KInterruptExt07,	"EXT07");	// IIC
_LIT8(KInterruptExt08,	"EXT08");	// MU
_LIT8(KInterruptExt09,	"EXT09");	// MCU error
_LIT8(KInterruptExt0A,	"EXT0A");	// PATU error
_LIT8(KInterruptExt0B,	"EXT0B");	// SATU error
_LIT8(KInterruptExt0C,	"EXT0C");	// PPCI error
_LIT8(KInterruptExt0D,	"EXT0D");	// SPCI error
_LIT8(KInterruptExt0E,	"EXT0E");	// DMA0 error
_LIT8(KInterruptExt0F,	"EXT0F");	// DMA1 error
_LIT8(KInterruptExt10,	"EXT10");	// DMA2 error
_LIT8(KInterruptExt11,	"EXT11");	// MU error
_LIT8(KInterruptExt12,	"EXT12");	// reserved
_LIT8(KInterruptExt13,	"EXT13");	// AAU error
_LIT8(KInterruptExt14,	"EXT14");	// CIU error
_LIT8(KInterruptExt15,	"EXT15");	// reserved
_LIT8(KInterruptExt16,	"EXT16");	// reserved
_LIT8(KInterruptExt17,	"EXT17");	// reserved
_LIT8(KInterruptExt18,	"EXT18");	// timer
_LIT8(KInterruptExt19,	"EXT19");	// ethernet
_LIT8(KInterruptExt1A,	"EXT1A");	// uart 0
_LIT8(KInterruptExt1B,	"EXT1B");	// uart 1
_LIT8(KInterruptExt1C,	"EXT1C");	// spci
_LIT8(KInterruptExt1D,	"EXT1D");	// reserved
_LIT8(KInterruptExt1E,	"EXT1E");	// reserved
_LIT8(KInterruptExt1F,	"EXT1F");	// reserved


class T80200
	{
public:
	IMPORT_C static TUint IntCtl();
	IMPORT_C static void SetIntCtl(TUint);
	IMPORT_C static void ModifyIntCtl(TUint aClear, TUint aSet);
	IMPORT_C static TUint IntSrc();
	IMPORT_C static TUint IntStr();
	IMPORT_C static void SetIntStr(TUint);
	IMPORT_C static void Idle();
	IMPORT_C static TUint CClkCfg();
	IMPORT_C static void SetCClkCfg(TUint aValue);
	IMPORT_C static TUint CoreClockInKHz();
	};

#endif
