// V32S1110.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

//
// Variant:
// SA1110 and Assabet specific definitions
//

#ifndef __V32S1110_H__
#define __V32S1110_H__

#include <a32sa1100.h>		// SA1100 ASSP

// SA1110 variant additions:
//
//----------------------------------------------------------------------------
// Serial Port 1 (pages 11-80 to 11-83)
//
// GPCLK	Physical base = 8002.0000 - an alias of SA1100 SDLC
const TUint KHoBaseSerial1Gpclk	=	0x02*KHwLinBaseRegSpacing; // offset to KHwLinBaseRegisters

const TUint KHoRwGpclkGpclkr0	=	KHoBaseSerial1Gpclk + 0x60;
const TUint KHoRwGpclkGpclkr1	=	KHoBaseSerial1Gpclk + 0x6c;
const TUint KHoRwGpclkGpclkr2	=	KHoBaseSerial1Gpclk + 0x70;

// GPCLK register0
	const TUint KHtGpclkGpclkr0Sus	=	KBit0;
	const TUint KHtGpclkGpclkr0Sce	=	KBit1;
	const TUint KHtGpclkGpclkr0Scd	=	KBit2;

// GPCLKR1
	const TUint KHmGpclkGpclkr1Brd	=	KBit3|KBit2|KBit1|KBit0;
	const TUint KHsGpclkGpclkr1Brd	=	8;

// GPCLKR1
	const TUint KHmGpclkGpclkr2Brd	=	KBit7|KBit6|KBit5|KBit4|\
										KBit3|KBit2|KBit1|KBit0;

#define _GPLCK_BIT_RATE(Div)			(3686400/(Div+1))
//----------------------------------------------------------------------------
// Memory/PCMCIA (pages 10-9 to 10-28)
//
// MEM		Physical base = A000.0000 - alias SA1100 definitions
const TUint KHoBaseMexp			=	0x0f*KHwLinBaseRegSpacing;	// offset to KHwLinBaseRegisters as mapped by bootstrap

const TUint KHoRwMemMdcnfg		=	KHoBaseMexp + 0x00;
const TUint KHoRwMemMdcas00		=	KHoBaseMexp + 0x04;
const TUint KHoRwMemMdcas01		=	KHoBaseMexp + 0x08;
const TUint KHoRwMemMdcas02		=	KHoBaseMexp + 0x0C;
const TUint KHoRwMemMsc0		=	KHoBaseMexp + 0x10;
const TUint KHoRwMemMsc1		=	KHoBaseMexp + 0x14;
const TUint KHoRwMemMecr		=	KHoBaseMexp + 0x18;
const TUint KHoRwMemMdrefr		=	KHoBaseMexp + 0x1C;
const TUint KHoRwMemMdcas20		=	KHoBaseMexp + 0x20;
const TUint KHoRwMemMdcas21		=	KHoBaseMexp + 0x24;
const TUint KHoRwMemMdcas22		=	KHoBaseMexp + 0x28;
const TUint KHoRwMemMsc2		=	KHoBaseMexp + 0x2C;
const TUint KHoRwMemSmcnfg		=	KHoBaseMexp + 0x30;

// DRAM configuration
	const TUint KHsMemMdcnfgTwr2	=	30;
	const TUint KHmMemMdcnfgTwr2	=	0x00000003<<KHsMemMdcnfgTwr2;
	const TUint KHsMemMdcnfgTdl2	=	28;
	const TUint KHmMemMdcnfgTdl2	=	0x00000003<<KHsMemMdcnfgTdl2;
	const TUint KHsMemMdcnfgTrp2	=	24;
	const TUint KHmMemMdcnfgTrp2	=	0x0000000f<<KHsMemMdcnfgTrp2;
	const TUint KHtMemMdcnfgCdb22	=	KBit23;
	const TUint KHsMemMdcnfgDrac2	=	20;
	const TUint KHmMemMdcnfgDrac2	=	0x00000007<<KHsMemMdcnfgDrac2;
	const TUint KHtMemMdcnfgDwid2	=	KBit19;
	const TUint KHtMemMdcnfgDtim2	=	KBit18;
	const TUint KHsMemMdcnfgDe2		=	16;
	const TUint KHmMemMdcnfgDe2		=	0x00000003<<KHsMemMdcnfgDe2;
	const TUint KHsMemMdcnfgTwr0	=	14;
	const TUint KHmMemMdcnfgTwr0	=	0x00000003<<KHsMemMdcnfgTwr0;
	const TUint KHsMemMdcnfgTdl0	=	12;
	const TUint KHmMemMdcnfgTdl0	=	0x00000003<<KHsMemMdcnfgTdl0;
	const TUint KHsMemMdcnfgTrp0	=	8;
	const TUint KHmMemMdcnfgTrp0	=	0x0000000f<<KHsMemMdcnfgTrp0;
	const TUint KHtMemMdcnfgCdb20	=	KBit7;
	const TUint KHsMemMdcnfgDrac0	=	4;
	const TUint KHmMemMdcnfgDrac0	=	0x00000007<<KHsMemMdcnfgDrac0;
	const TUint KHtMemMdcnfgDwid0	=	KBit3;
	const TUint KHtMemMdcnfgDtim0	=	KBit2;
	const TUint KHsMemMdcnfgDe0		=	0;
	const TUint KHmMemMdcnfgDe0		=	0x00000003<<KHsMemMdcnfgDe0;

	const TUint KHwRwMemMdcnfgRowsMin	=	9;
	const TUint KHwRwMemMdcnfgRowsMax	=	15;

// DRAM refresh control register
	const TUint KHsMemMdrefrTrasr	=	0;
	const TUint KHmMemMdrefrTrasr	=	0x0000000f<<KHsMemMdrefrTrasr;
	const TUint KHsMemMdrefrDri		=	4;
	const TUint KHmMemMdrefrDri		=	0x00000fff<<KHsMemMdrefrDri;
	const TUint KHtMemMdrefrE0pin	=	KBit16;
	const TUint KHtMemMdrefrK0run	=	KBit17;
	const TUint KHtMemMdrefrK0db2	=	KBit18;
	const TUint KHtMemMdrefrE1pin	=	KBit20;
	const TUint KHtMemMdrefrK1run	=	KBit21;
	const TUint KHtMemMdrefrK1db2	=	KBit22;
	const TUint KHtMemMdrefrK2run	=	KBit25;
	const TUint KHtMemMdrefrK2db2	=	KBit26;
	const TUint KHtMemMdrefrEapd	=	KBit28;
	const TUint KHtMemMdrefrKapd	=	KBit29;
	const TUint KHtMemMdrefrSlfrsh	=	KBit31;

// Static memory control (2 per register/3 registers)
	const TUint KHsMemMsc012Rrr		=	13;
	const TUint KHmMemMsc012Rrr		=	0x00000007<<KHsMemMsc012Rrr;
	const TUint KHsMemMsc012Rdn		=	8;
	const TUint KHmMemMsc012Rdn		=	0x0000001f<<KHsMemMsc012Rdn;
	const TUint KHsMemMsc012Rdf		=	3;
	const TUint KHmMemMsc012Rdf		=	0x0000001f<<KHsMemMsc012Rdf;
	const TUint KHtMemMsc012Rbw		=	KBit2;
	const TUint KHsMemMsc012Rt		=	0;
	const TUint KHmMemMsc012Rt		=	0x00000003<<KHsMemMsc012Rt;

// Number of static chip selects
	const TUint KHwMemMaxCS			=	6;

// Expansion memory configuration (2 per register)
	const TUint KHtMemMecrFast0		=	KBit15;

	const TUint KHtMemMecrFast1		=	KBit31;

// SMROM configuration register
	const TUint KHsMemSmcnfgSm0		=	0;
	const TUint KHmMemSmcnfgSm0		=	0x00000003<<KHsMemSmcnfgSm0;
	const TUint KHsMemSmcnfgRa0		=	4;
	const TUint KHmMemSmcnfgRa0		=	0x00000007<<KHsMemSmcnfgRa0;
	const TUint KHsMemSmcnfgCl0		=	12;
	const TUint KHmMemSmcnfgCl0		=	0x00000007<<KHsMemSmcnfgCl0;
	const TUint KHtMemSmcnfgRl0		=	KBit15;
	const TUint KHsMemSmcnfgSm2		=	16;
	const TUint KHmMemSmcnfgSm2		=	0x00000003<<KHsMemSmcnfgSm2;
	const TUint KHsMemSmcnfgRa2		=	20;
	const TUint KHmMemSmcnfgRa2		=	0x00000007<<KHsMemSmcnfgRa2;
	const TUint KHsMemSmcnfgCl2		=	28;
	const TUint KHmMemSmcnfgCl2		=	0x00000007<<KHsMemSmcnfgCl2;
	const TUint KHtMemSmcnfgRl2		=	KBit31;

//----------------------------------------------------------------------------
// Test Unit Control Register (appendix D, address as in Specification update page 18)
//
// Test Unit	Physical base = 9003.0000 - an alias of SA1100 Reset control 
const TUint KHoBaseTestUnit		=	0x0b*KHwLinBaseRegSpacing; // offset to KHwLinBaseRegisters

const TUint KHoRwTestUnitTucr	=	KHoBaseTestUnit + 0x08;

// TUCR
	const TUint KHtTestUnitTucrPmd	=	KBit9;
	const TUint KHtTestUnitTucrMr	=	KBit10;
	const TUint KHsTestUnitTucrTsel	=	29;
	const TUint KHmTestUnitTucrTsel	=	0x00000007<<KHsTestUnitTucrTsel;
	const TUint KHtTestUnitTucrTsel0=	KBit29;
	const TUint KHtTestUnitTucrTsel1=	KBit30;
	const TUint KHtTestUnitTucrTsel2=	KBit31;

//----------------------------------------------------------------------------
// Real Time Clock
const TUint KHoBaseRtc			=	0x09*KHwLinBaseRegSpacing; // offset to KHwLinBaseRegisters

const TUint KHoRwRtcRtsr		=	KHoBaseRtc + 0x10;
	
	// Status - already defined in a32sa1100.h - but, strangely, never used...
//	const TUint KHtRtcRtsrHze		=	KBit3;
//	const TUint KHtRtcRtsrAle		=	KBit2;

//----------------------------------------------------------------------------

class TSa1110
	{
public:
// General
	enum TState
		{
		EEnable,
		EDisable
		};

// DRAM configuration enumerations
	enum TDramClockDiv01
		{
		EDram01ClockCpu=KClear32,
		EDram01ClockMem=KHtMemMdcnfgCdb20
		};
	enum TDramClockDiv23
		{
		EDram23ClockCpu=KClear32,
		EDram23ClockMem=KHtMemMdcnfgCdb22
		};
	enum TTimingType01
		{
		EAsynchDram01=KClear32,
		ESdram01=KHtMemMdcnfgDtim0
		};
	enum TTimingType23
		{
		EAsynchDram23=KClear32,
		ESdram23=KHtMemMdcnfgDtim2
		};
	enum TBusWidth01
		{
		E32BitBus01=KClear32,
		E16BitBus01=KHtMemMdcnfgDwid0
		};
	enum TBusWidth23
		{
		E32BitBus23=KClear32,
		E16BitBus23=KHtMemMdcnfgDwid2
		};

// ROM/SRAM configuration enumerations
	enum TRomType
		{
		ERomTypeNoBurstFlash=0<<KHsMemMsc012Rt,
		ERomTypeNoBurstSram=1<<KHsMemMsc012Rt,
		ERomTypeBurst4Rom=2<<KHsMemMsc012Rt,
		ERomTypeBurst8Rom=3<<KHsMemMsc012Rt
		};
	enum TRomWidth
		{
		ERomWidth32=KClear32,
		ERomWidth16=KHtMemMsc012Rbw
		};

// Expansion memory configuration enumerations
	enum TSlotSel
		{
		ESlot0=KHtMemMecrFast0,
		ESlot1=KHtMemMecrFast1
		};

	// Expansion memory configuration enumerations
	enum TExpansionType
		{
		EExpansionIo=KHsMemMecrBsio,
		EExpansionAttribute=KHsMemMecrBsa,
		EExpansionCommon=KHsMemMecrBsm,
		EExpansionIoSlot2=KHsMemMecrBsioSlot2,
		EExpansionAttributeSlot2=KHsMemMecrBsaSlot2,
		EExpansionCommonSlot2=KHsMemMecrBsmSlot2
		};

// Serial Port 1 enumeration
	enum TUart1OperationMode
		{
		EGpclkModeSelect=KClear32,
		EUart1ModeSelect=KHtGpclkGpclkr0Sus
		};

	enum TClockDirection
		{
		EGpclkIsInput=KClear32,
		EGpclkIsOutput=KHtGpclkGpclkr0Scd
		};

// TUCR enumerations
	enum TTucrClock
		{
		E32Khz=KClear32,
		E36864Khz=KHtTestUnitTucrTsel0,
		EVddRingOscDiv16=KHtTestUnitTucrTsel1,
		E96MhzDiv4=KHtTestUnitTucrTsel0|KHtTestUnitTucrTsel1,
		E32KhzAndRclk=KHtTestUnitTucrTsel2,
		EMainPllDiv16=KHtTestUnitTucrTsel2|KHtTestUnitTucrTsel1,
		EVddRingOscDiv4=KHmTestUnitTucrTsel
		};

// RTC enumerations
	enum TRtcIntSource
		{
		EDisableAll=0,
		ERtcAlarm=KHtRtcRtsrAle,
		E1Hz=KHtRtcRtsrHze,
		EEnableAll=KHtRtcRtsrHze|KHtRtcRtsrAle
		};

public:
	static void Init3();
// Uart 1 Operation
	IMPORT_C static void SetUart1Mode(TUart1OperationMode aMode);
	IMPORT_C static void EnableSampleClock(TState aState);
	IMPORT_C static void SetClockDir(TClockDirection aDirection);
	IMPORT_C static void SetGpclkBitRateDivisor(TUint aDivisor);// aDivisor=BRD as per formulae 
	IMPORT_C static TUint GetGpclkBitRate();				// return the Bit-rate not BRD

// Mem operations
	IMPORT_C static void SetMemDramConfig01(TUint aRows,TDramClockDiv01 aClockDiv,TUint aRasPrechg,
											TUint aRasCbr,TUint aLatchTiming,TUint aRefresh,
											TTimingType01 aType, TBusWidth01 aWidth, TUint aWriteRecovery);
	IMPORT_C static void SetMemDramConfig23(TUint aRows,TDramClockDiv23 aClockDiv,TUint aRasPrechg,
											TUint aRasCbr,TUint aLatchTiming,TUint aRefresh,
											TTimingType23 aType, TBusWidth23 aWidth, TUint aWriteRecovery);
	IMPORT_C static TUint GetRasCbr();
	IMPORT_C static TUint GetDramRefresh();
// masks for E1PIN, K1RUN, K1DB2, K2RUN, K2DB2, EAPD, KAPD, SLFRSH bits
	IMPORT_C static void ModifySdramClockControlBits(TUint aClearMask, TUint aSetMask);

// override similarly named function of TSa1100
	IMPORT_C static void SetMemStaticConfig(TRomType aType,TRomWidth aWidth,TUint aDelayFirst,
											TUint aDelayNext,TUint aRecover,TUint aChipSelect);

	IMPORT_C static void SetMemExpansionConfig(TExpansionType aType,TUint aTimeInPicoseconds);
	IMPORT_C static void EnableFastModeAccess(TSlotSel aSlot, TState aState);
	IMPORT_C static TUint ReadMemExpansionConfig();


// TUCR operation
	IMPORT_C static void SelectOutpuClock(TTucrClock aClock);
	IMPORT_C static void EnableMemoryRequestMode(TState aState);
	IMPORT_C static void EnablePowerManagement(TState aState);
	IMPORT_C static TUint ReadTucr();

// RTC complement
	IMPORT_C static void EnableRtcInt(TRtcIntSource aSource);

private:
	static inline TUint Register32(TUint anAddr);
	static inline void SetRegister32(TUint aValue,TUint anAddr);
	static inline void ModifyRegister32(TUint aClearMask,TUint aSetMask,TUint anAddr);

private:
	static TUint iRefreshInterval;			// holds the Refresh Interval (common to all banks)
	static TUint iRasCbr;					// holds the RAS assertion during CBR (common to all banks)
	static TUint iMECRShadow;				// MECR shadow register (it seems that a read followed by a write to this
											// register causes an exception
	};


//----------------------------------------------------------------------------
//
// Assabet CPLD registers
//
//	Note: this needs to be mapped in Linear memory in the Bootstrap
//
const TUint KHoLinBaseCpld1110		=	0x11*KHwLinBaseRegSpacing;			// offset to KHwLinBaseRegisters

// Board Control Register
const TUint	KHoWoBcr			=	KHoLinBaseCpld1110;
	const TUint KHtBcrCf_Pwr		=	KBit0;
	const TUint KHtBcrCf_Rst		=	KBit1;
	const TUint KHtBcrSoft_Rst		=	KBit2;
	const TUint KHtBcrIrda_Fsel		=	KBit3;
	const TUint KHsBcrMd			=	4;
	const TUint KHmBcrMd			=	KBit4|KBit5;
	const TUint KHtBcrStereo_Lb		=	KBit6;
	const TUint KHtBcrCf_Bus_On		=	KBit7;
	const TUint KHtBcrAudio_On		=	KBit8;
	const TUint KHtBcrLight			=	KBit9;
	const TUint KHtBcrLcd12or16		=	KBit10;
	const TUint KHtBcrLcdOn			=	KBit11;
	const TUint KHtBcrRs232En		=	KBit12;
	const TUint KHsBcrLeds			=	13;
	const TUint KHtBcrD9_Led		=	KBit13;
	const TUint KHtBcrD8_Led		=	KBit14;
	const TUint KHtBcrVib_On		=	KBit15;
	const TUint KHtBcrCom_Dtr		=	KBit16;
	const TUint KHtBcrCom_Rts		=	KBit17;
	const TUint KHtBcrRad_Wu		=	KBit18;
	const TUint KHtBcrI2cEnab		=	KBit19;
	const TUint KHtBcrIrDecode		=	KBit20;
	const TUint KHtBcrQmute			=	KBit21;
	const TUint KHtBcrRad_On		=	KBit22;
	const TUint KHtBcrSpk_Off		=	KBit23;
	const TUint KHmBcrBits			=	0x00FFFFFF;

// Board Status Register
const TUint	KHoRoBsr			=	KHoLinBaseCpld1110;
	const TUint KHtBsrRs232_Valid	=	KBit24;
	const TUint KHtBsrCom_Dcd		=	KBit25;
	const TUint KHtBsrCom_Cts		=	KBit26;
	const TUint KHtBsrCom_Dsr		=	KBit27;
	const TUint KHtBsrRad_Cts		=	KBit28;
	const TUint KHtBsrRad_Dsr		=	KBit29;
	const TUint KHtBsrRad_Dcd		=	KBit30;
	const TUint KHtBsrRad_Ri		=	KBit31;
	const TUint KHmBsrBits			=	0xFF000000;

//----------------------------------------------------------------------------

class TCpld1110
	{
public:
// General
	enum TState
		{
		EEnable,
		EDisable
		};

// IrDA enumerations
	enum TIrdaFrequencySel
		{
		ESir=KClear32,
		EMirFir=KHtBcrIrda_Fsel
		};
	enum TIrdaRangeSel
		{
		EMaxRange=0<<KHsBcrMd,
		EIrdaShutdown=1<<KHsBcrMd,
		ETwoThirds=2<<KHsBcrMd,
		EOneThird=3<<KHsBcrMd
		};
// LCD enumerations
	enum TRgbFormat
		{
		E12Rgb=KClear32,
		E16Rgb=KHtBcrLcd12or16
		};

public:
	IMPORT_C static void UpdateLeds(TUint aLedMask);		// assume LedMask to be right-aligned (1 to turn on)
	IMPORT_C static void EnableUcb1300(TState aState);
	IMPORT_C static void EnableCfBus(TState aState);
	IMPORT_C static void SetRts();
	IMPORT_C static void SetDtr();
	IMPORT_C static void ClearRts();
	IMPORT_C static void ClearDtr();
	IMPORT_C static TUint ReadModemOutCtrl();
	IMPORT_C static void SelectIrFrequency(TIrdaFrequencySel aSelection);
	IMPORT_C static void EnableIrDecode(TState aState);
	IMPORT_C static void SetIrdaMode(TIrdaRangeSel aMode);
	IMPORT_C static void EnableRs232(TState aState);
	IMPORT_C static void EnableBacklight(TState aState);
	IMPORT_C static void EnableLcdPower(TState aState);
	IMPORT_C static void SelectRgbFormat(TRgbFormat aFormat);
	IMPORT_C static void ModifyBcr(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint ReadBcr();
	IMPORT_C static TBool IsCtsSet();
	IMPORT_C static TBool IsDsrSet();
	IMPORT_C static TBool IsDcdSet();
	IMPORT_C static TBool IsRs232Valid();
	IMPORT_C static TUint ReadBsr();

private:
	static inline TUint Register32(TUint anAddr);
	static inline void SetRegister32(TUint aValue,TUint anAddr);

private:
	static TUint BCRShadow;		// shadow register for BCR (write-only)
};
#endif