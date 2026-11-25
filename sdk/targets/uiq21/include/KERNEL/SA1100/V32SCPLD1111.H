// V32SCPLD1111.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

//
// Definitions for the Companion Chip sub-board CPLD
//

#ifndef __CPLD1111_H__
#define __CPLD1111_H__
#include <e32std.h>
#include <k32std.h>

//----------------------------------------------------------------------------
// Constant conventions:
//----------------------------------------------------------------------------

// KH		Hardware definition
// KHw		4-byte word definition prefix
// KHb		Byte definition prefix
// KHt		Bit definition prefix
// KHm		Mask definition prefix
// KHs		Shift definition prefix
// KHo		Offset definition prefix
// KHwRo	Read-only register
// KHwWo	Write-only register
// KHwRw	Read/write register
// KHwBase	Base address within memory map
// _i		Input suffix
// _o		Output suffix
// _b		Input/output suffix

//----------------------------------------------------------------------------
// SA1111 board memory map: physical addresses
//
//	Expansion Flash			0x08000000		32Mbyte
//  CPLD System registers	0x10000000		a few locations
//  Ethernet Controller		0x18000000		1KByte
//  PCMCIA					0x20000000		3x64MByte
//  CF						0x30000000		2x2MByte
//  SA1111 registers		0x40000000		8KByte
//  Expansion SDRAM			0xD0000000		16/32/64MByte
//
//----------------------------------------------------------------------------
//
// Useful constants
//
const TUint8 KbBit0= 0x01;
const TUint8 KbBit1= 0x02;
const TUint8 KbBit2= 0x04;
const TUint8 KbBit3= 0x08;
const TUint8 KbBit4= 0x10;
const TUint8 KbBit5= 0x20;
const TUint8 KbBit6= 0x40;
const TUint8 KbBit7= 0x80;

//----------------------------------------------------------------------------
// Development module CPLD: system registers (byte access) 
//----------------------------------------------------------------------------
const TUint32 KHbBaseCpld1111		=	0x10000000;
const TUint8 KHbAllOff				=	0;
const TUint8 KHwAllOff				=	0;
// ID register
const TUint32	KHoRoWhoAmI			=	0x00000000;			// offset to KHbBaseCpld1111
// Switch pack
const TUint32 KHoRoSwitchPack		=	0x00000020;			// offset to KHbBaseCpld1111
	const TUint8 KHtBootImgSel0		=	KbBit0;			// these two bits determine which boot image 
	const TUint8 KHtBootImgSel1		=	KbBit1;			// it jumps to (connect to GPIO 0,1)
	const TUint8 KHmBootImgMask		=	KHtBootImgSel0|KHtBootImgSel1;
	const TUint8 KHtUserDefined0	=	KbBit2;
	const TUint8 KHtUserDefined1	=	KbBit3;
	const TUint8 KHtUserDefined2	=	KbBit4;
	const TUint8 KHtUserDefined3	=	KbBit5;
	const TUint8 KHtUserDefined4	=	KbBit6;
	const TUint8 KHmUserDefinedMask	=	KHtUserDefined0|KHtUserDefined1|KHtUserDefined2|\
										KHtUserDefined3|KHtUserDefined4;
	const TUint8 KHsUserDefShift	=	2;
	const TUint8 KHtFlashBankSel	=	KbBit7;			// this bit determines where Bank 0 (boot bank) is located
// Interrupt Reason Register	-	masks to determine which interrupt(s) are asserted
const TUint32 KHoRoIntReason		=	0x00000024;			// offset to KHbBaseCpld1111
	const TUint8 KHtEnetIrq			=	KbBit0;
	const TUint8 KHtUsarIrq			=	KbBit1;
	const TUint8 KHtSa1111Irq		=	KbBit2;
	const TUint8 KHmIntMask			=	KHtEnetIrq|KHtUsarIrq|KHtSa1111Irq;
// Keypad column read			-	masks to determine which key(s) are pressed
const TUint32 KHoRoKeyCol			=	0x00000080;			// offset to KHbBaseCpld1111
	const TUint8 KHtCol0			=	KbBit0;
	const TUint8 KHtCol1			=	KbBit1;
	const TUint8 KHtCol2			=	KbBit2;
	const TUint8 KHtCol3			=	KbBit3;
	const TUint8 KHmColRegBits		=	KHtCol0|KHtCol1|KHtCol2|KHtCol3;
// Keypad Row Write
const TUint32 KHoRwKeyRow			=	0x00000090;			// offset to KHbBaseCpld1111
	const TUint8 KHtRow0			=	KbBit0;
	const TUint8 KHtRow1			=	KbBit1;
	const TUint8 KHtRow2			=	KbBit2;
	const TUint8 KHtRow3			=	KbBit3;
	const TUint8 KHtRow4			=	KbBit4;
	const TUint8 KHmRowRegBits		=	KHtRow0|KHtRow1|KHtRow2|KHtRow3|KHtRow4;
// Control Register 0
const TUint32 KHoRwControl0			=	0x000000A0;			// offset to KHbBaseCpld1111
	const TUint8 KHtGpio01OnOff		=	KbBit0;			// allows swicth pack's SW1 and SW2 to select boot image 
	const TUint8 KHtTkPadPower		=	KbBit1;
	const TUint8 KHtMousePower		=	KbBit2;
	const TUint8 KHtEnetOsc			=	KbBit3;
	const TUint8 KHtSpiKbWkUp		=	KbBit4;
	const TUint8 KHtPcCardA0Vpp		=	KbBit5;			// these 2 bits control the the supply and programming 
	const TUint8 KHtPcCardA1Vpp		=	KbBit6;			// voltage for the PCMCIA slot (cf MAX1600 datasheet)
	const TUint8 KHmPcCardVppBits	=	KHtPcCardA0Vpp|KHtPcCardA1Vpp;
	const TUint8 KHsPcCardVppShift	=	5;
// Modem Control Register 0
const TUint32 KHoRwModCtrl0			=	0x000000B0;			// offset to KHbBaseCpld1111
	const TUint8 KHtRts1			=	KbBit0;
	const TUint8 KHtDtr1			=	KbBit1;
	const TUint8 KHtRts2			=	KbBit2;
	const TUint8 KHtDtr2			=	KbBit3;
	const TUint8 KHmCtrl0Bits		=	KHtRts1|KHtDtr1|KHtRts2|KHtDtr2;
// Modem Control Register 1 - Note: Intel's data sheet's wrong! Gathered this address from CPLD's VHDL
const TUint32 KHoRoModCtrl1			=	0x000000B4;			// offset to KHbBaseCpld1111
	const TUint8 KHtCts1			=	KbBit0;
	const TUint8 KHtDsr1			=	KbBit1;
	const TUint8 KHtDcd1			=	KbBit2;
	const TUint8 KHtCts2			=	KbBit3;
	const TUint8 KHtDsr2			=	KbBit4;
	const TUint8 KHtDcd2			=	KbBit5;
// Audio Control
const TUint32 KHoRwAudioCtrl		=	0x000000C0;			// offset to KHbBaseCpld1111
	const TUint8 KHtCodecSel		=	KbBit0;
	const TUint8 KHmCodecSel		=	KHtCodecSel;
	const TUint8 KHtMuteI2sCodec	=	KbBit1;
	const TUint8 KHmMuteI2sCodec	=	KHtMuteI2sCodec;
// Leds
const TUint32 KHoBaseLeds			=	0x00000010;			// offset to KHbBaseCpld1111
	const TUint32 KHtLed0			=	KBit0;
	const TUint32 KHtLed1			=	KBit1;
	const TUint32 KHtLed2			=	KBit2;
	const TUint32 KHtLed3			=	KBit3;
	const TUint32 KHtLed4			=	KBit4;
	const TUint32 KHtLed5			=	KBit5;
	const TUint32 KHtLed6			=	KBit6;
	const TUint32 KHtLed7			=	KBit7;
	const TUint32 KHtLed8			=	KBit8;
	const TUint32 KHtLed9			=	KBit9;
	const TUint32 KHtLed10			=	KBit10;
	const TUint32 KHtLed11			=	KBit11;
	const TUint32 KHtLed12			=	KBit12;
	const TUint32 KHtLed13			=	KBit13;
	const TUint32 KHtLed14			=	KBit14;
	const TUint32 KHtLed15			=	KBit15;
	const TUint32 KHtLed16			=	KBit16;
	const TUint32 KHtLed17			=	KBit17;
	const TUint32 KHtLed18			=	KBit18;
	const TUint32 KHtLed19			=	KBit19;
	const TUint32 KHtLed20			=	KBit20;
	const TUint32 KHtLed21			=	KBit21;
	const TUint32 KHtLed22			=	KBit22;
	const TUint32 KHtLed23			=	KBit23;
	const TUint32 KHtLed24			=	KBit24;
	const TUint32 KHtLed25			=	KBit25;
	const TUint32 KHtLed26			=	KBit26;
	const TUint32 KHtLed27			=	KBit27;
	const TUint32 KHtLed28			=	KBit28;
	const TUint32 KHtLed29			=	KBit29;
	const TUint32 KHtLed30			=	KBit30;
	const TUint32 KHtLed31			=	KBit31;

//----------------------------------------------------------------------------
// Ethernet Controller SMSC9196 registers (byte access)
//----------------------------------------------------------------------------
const TUint32 KHbBaseEther			=	0x18000000;
// Its register descritpion should go here


class TCpld1111
	{
public:
// General
	enum TOnOff
		{
		EOn,
		EOff
		};
// Interrupts
	enum TCpldInts
		{
		EIrqNone=0,
		EIrqEnet=KHtEnetIrq,
		EIrqUsar=KHtUsarIrq,
		EIrqEnetUsar=KHtEnetIrq|KHtUsarIrq,
		EIrqSa1111=KHtSa1111Irq,
		EIrqEnetSa1111=KHtEnetIrq|KHtSa1111Irq,
		EIrqUsarSa1111=KHtUsarIrq|KHtSa1111Irq,
		EIrqAll=KHtEnetIrq|KHtUsarIrq|KHtSa1111Irq
		};
// Switch Pack
	enum TBootImage
		{
		EBootImage1,
		EBootImage2,
		EBootImage3,
		EBootImage4
		};
	enum TBank0Location
		{
		ESa1110DevBoard,
		ESa1111DevBoard
		};
// NCR0 Control Register 0
	enum TBootImageSel
		{
		EBootImageSelOn,
		EGpio01FuncRestored
		};
	enum TPcCardVpp
		{
		EA0A1BothOff,
		EA0OnA1Off,
		EA0OffA1On,
		EA0A1BothOn
		};
// Audio Control Register
	enum TCodec
		{
		EAc97Codec,
		EI2sCodec
		};
	enum TMuteState
		{
		EMute,
		EUnMute
		};
// Modem Control Registers 0/1
	enum TCommChannel
		{
		EChannel1,
		EChannel2
		};
	enum TModemSignals
		{
		EChannel1Dtr=KHtDtr1,
		EChannel2Dtr=KHtDtr2,
		EChannel1Rts=KHtRts1,
		EChannel2Rts=KHtRts2
		};
// Keypad
	enum TRow
		{
		ERow1=KHtRow0,
		ERowBeg=ERow1,
		ERow2=KHtRow1,
		ERow3=KHtRow2,
		ERow4=KHtRow3,
		ERowEnd=ERow4,
		ERow5=KHtRow4
		};
	enum TColumn
		{
		EColumn1=KHtCol0,
		EColumnBeg=EColumn1,
		EColumn2=KHtCol1,
		EColumn3=KHtCol2,
		EColumn4=KHtCol3,
		EColumnEnd=EColumn4,
		};
// Leds
	enum TLed
		{
		ELed1=KHtLed0,
		ELed2=KHtLed1,
		ELed3=KHtLed2,
		ELed4=KHtLed3,
		ELed5=KHtLed4,
		ELed6=KHtLed5,
		ELed7=KHtLed6,
		ELed8=KHtLed7,
		ELed9=KHtLed8,
		ELed10=KHtLed9,
		ELed11=KHtLed10,
		ELed12=KHtLed11,
		ELed13=KHtLed12,
		ELed14=KHtLed13,
		ELed15=KHtLed14,
		ELed16=KHtLed15,
		ELed17=KHtLed16,
		ELed18=KHtLed17,
		ELed19=KHtLed18,
		ELed20=KHtLed19,
		ELed21=KHtLed20,
		ELed22=KHtLed21,
		ELed23=KHtLed22,
		ELed24=KHtLed23,
		ELed25=KHtLed24,
		ELed26=KHtLed25,
		ELed27=KHtLed26,
		ELed28=KHtLed27,
		ELed29=KHtLed28,
		ELed30=KHtLed29,
		ELed31=KHtLed30,
		ELed32=KHtLed31
		};

public:
	TCpld1111();					// Constructor
	// Initialisation
	static void Init3();

	// General
	IMPORT_C static TUint8 GetId();
	// SA1111 Development Card Interrupts
	IMPORT_C static TCpldInts GetIntSource();
	// Switch Pack SW2
	IMPORT_C static TBootImage WhichBootImage();
	IMPORT_C static TUint8 GetUserDefBits();
	IMPORT_C static TBank0Location WhereIsBank0();
	// NCR_0: Control Register 0
	IMPORT_C static void ResetNCR0();				// register not initialised by reset
	IMPORT_C static void EnableBootImageSel();
	IMPORT_C static void RestoreGPIO01Function();
	IMPORT_C static TBootImageSel ReadBootImageSelBit();
	IMPORT_C static void TrackpadPower(TOnOff aValue);
	IMPORT_C static TBool IsTrackpadPowerOn();
	IMPORT_C static void MousePower(TOnOff aValue);
	IMPORT_C static TBool IsMousePowerOn();
	IMPORT_C static void SetENetOscSTate(TOnOff aState);
	IMPORT_C static TBool IsEnetOscOn();
	IMPORT_C static void SendSpiKbdWakeUp();
	IMPORT_C static void SetPcCardPwrCtrlBits(TPcCardVpp aBitmask);
	IMPORT_C static TPcCardVpp ReadPcCardPwrCtrlBits();
	// Audio Control Register
	IMPORT_C static void ResetAudioCtrlReg();		// register not initialised by reset
	IMPORT_C static void SelectCodec(TCodec aCodec);
	IMPORT_C static TCodec WhichCodec();
	IMPORT_C static void MuteI2sCodec(TMuteState aState);
	IMPORT_C static TMuteState IsI2sCodecMute();
	// Modem Control Registers 0/1
	IMPORT_C static void ResetModemCtrlReg0();
	IMPORT_C static void SetChannelRts(TCommChannel aChannel);
	IMPORT_C static void SetChannelDtr(TCommChannel aChannel);
	IMPORT_C static void ClearChannelRts(TCommChannel aChannel);
	IMPORT_C static void ClearChannelDtr(TCommChannel aChannel);
	IMPORT_C static TUint8 ReadModemCtrl0Bits();
	IMPORT_C static TBool IsChannelCtsSet(TCommChannel aChannel);
	IMPORT_C static TBool IsChannelDsrSet(TCommChannel aChannel);
	IMPORT_C static TBool IsChannelDcdSet(TCommChannel aChannel);
	// Keypad
	IMPORT_C static void ResetKeypad();				// row register not initialised by reset
	IMPORT_C static void ActivateSingleRow(TRow aRow);
	IMPORT_C static void DeactivateAllRows();
	IMPORT_C static TUint8 GetCols();				// get current state of columns
	IMPORT_C static TUint8 GetdColsWDebounce(TUint aRowIndex);		// incorporates filtering for bouncing keys
													// needs to be called every few ms
	// Leds
	IMPORT_C static void ResetLeds();				// led registers not initialised by reset
	IMPORT_C static void TurnLedOn(TLed aLed);		// on a Led basis
	IMPORT_C static void TurnLedOff(TLed aLed);
	IMPORT_C static void ToggleLed(TLed aLed);
	IMPORT_C static TBool IsLedOn(TLed aLed);
	IMPORT_C static void ModifyLedStatus(TUint32 aOffMask, TUint32 aOnMask); // on all Leds
	IMPORT_C static TUint32 WhichLedsAreOn();

private:
	static inline TUint8 Register8(TUint32 anAddr);
	static inline void SetRegister8(TUint8 aValue,TUint32 anAddr);
	static inline void ModifyRegister8(TUint8 aClearMask,TUint8 aSetMask,TUint32 anAddr);
	static inline void SetLed(TUint32 aValue);
	static inline void ModifyLed(TUint32 aClearMask,TUint32 aSetMask);

private:
	static const TCpldInts IntSourceArray[8];
	static const TBootImage BootImageArray[4];
	static const TPcCardVpp PcCardVppArray[4];
	TUint8 KbColPreviousState[5];			// holds the previous Kbd columns state for debouncing keyboard 
	TUint8 KbColPreviousMaskKeep[5];		// holds a record of the changes on the state of columns
	TUint32 PreviousLedState;			// holds a record of the state of all 32 leds
    TUint32 iHwChunkLinAddr;
};

#endif