// A32EIGER.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __A32EIGER_H__
#define __A32EIGER_H__
#include <e32std.h>
#include <e32hal.h>

//
// Eiger Interrupts
//

_LIT8(KFiqExternal, "FiqExternal");					// Eiger + CL-PS
_LIT8(KFiqBatLow, "FiqBatLow");						// Eiger + CL-PS
_LIT8(KFiqWatchDog, "FiqWatchDog");					// Eiger + CL-PS
_LIT8(KFiqMediaChg, "FiqMediaChg");					// Eiger + CL-PS
_LIT8(KIrqCodec, "IrqCodec");						// Eiger + CL-PS
_LIT8(KIrqExt1, "IrqExt1");							// Eiger + CL-PS
_LIT8(KIrqExt2, "IrqExt2");							// Eiger + CL-PS
_LIT8(KIrqExt3, "IrqExt3");							// Eiger + CL-PS
_LIT8(KIrqTimer1, "IrqTimer1");						// Eiger + CL-PS
_LIT8(KIrqTimer2, "IrqTimer2");						// Eiger + CL-PS
_LIT8(KIrqRtcMatch, "IrqRtcMatch");					// Eiger + CL-PS
_LIT8(KIrqTick, "IrqTick");							// Eiger + CL-PS
_LIT8(KIrqUartTx, "IrqUartTx");						// Eiger + CL-PS
_LIT8(KIrqUartRx, "IrqUartRx");						// Eiger + CL-PS
_LIT8(KIrqUartModem, "IrqUartModem");				// Eiger + CL-PS
_LIT8(KIrqSpi, "IrqSpi");							// Eiger + CL-PS
_LIT8(KIrqKeyPress, "IrqKeyPress");					// Cirrus Logic CL-PS7115
_LIT8(KIrqSpi2Rx, "IrqSpi2Rx");						// Cirrus Logic CL-PS7115
_LIT8(KIrqSpi2Tx, "IrqSpi2Tx");						// Cirrus Logic CL-PS7115
_LIT8(KIrqSpare10, "IrqSpare10");					// Spare/reserved
_LIT8(KIrqSpare09, "IrqSpare09");					// Spare/reserved
_LIT8(KIrqSpare08, "IrqSpare08");					// Spare/reserved
_LIT8(KIrqSpare07, "IrqSpare07");					// Spare/reserved
_LIT8(KIrqSpare06, "IrqSpare06");					// Spare/reserved
_LIT8(KIrqSpare05, "IrqSpare05");					// Spare/reserved
_LIT8(KIrqSpare04, "IrqSpare04");					// Spare/reserved
_LIT8(KIrqSpare03, "IrqSpare03");					// Spare/reserved
_LIT8(KIrqSpare02, "IrqSpare02");					// Spare/reserved
_LIT8(KIrqUart2Tx, "IrqUart2Tx");					// Cirrus Logic CL-PS7115
_LIT8(KIrqUart2Rx, "IrqUart2Rx");					// Cirrus Logic CL-PS7115
_LIT8(KIrqSpare01, "IrqSpare01");					// Spare/reserved
_LIT8(KIrqSpare00, "IrqSpare00");					// Spare/reserved
_LIT8(KIrqExtUartRx, "IrqExtUartRx");				// External
_LIT8(KIrqExtUartTx, "IrqExtUartTx");				// External
_LIT8(KIrqExtUartModem, "IrqExtUartModem");			// External
_LIT8(KIrqExtPcCd0IReq, "IrqExtPcCd0IReq");			// External
_LIT8(KIrqExtPcCd0StsC, "IrqExtPcCd0StsC");			// External
_LIT8(KIrqExtPcCd0RdyC, "IrqExtPcCd0RdyC");			// External
_LIT8(KIrqExtPcCd1IReq, "IrqExtPcCd1IReq");			// External
_LIT8(KIrqExtPcCd1StsC, "IrqExtPcCd1StsC");			// External
_LIT8(KIrqExtPcCd1RdyC, "IrqExtPcCd1RdyC");			// External
_LIT8(KIrqExtPcCd2IReq, "IrqExtPcCd2IReq");			// External
_LIT8(KIrqExtPcCd2StsC, "IrqExtPcCd2StsC");			// External
_LIT8(KIrqExtPcCd2RdyC, "IrqExtPcCd2RdyC");			// External
_LIT8(KIrqExtPcCd3IReq, "IrqExtPcCd3IReq");			// External
_LIT8(KIrqExtPcCd3StsC, "IrqExtPcCd3StsC");			// External
_LIT8(KIrqExtPcCd3RdyC, "IrqExtPcCd3RdyC");			// External
_LIT8(KIrqExtReserved, "IrqExtReserved");			// External

//                               
// Eiger Hardware Addresses and constants
//
#ifndef __SINGLE__
const TUint KEigerBaseAddress=0x58000000;
#define EIGER_BASE_ADDRESS 0x58000000
#else
const TUint KEigerBaseAddress=0x80000000;
#define EIGER_BASE_ADDRESS 0x80000000
#endif

const TUint KEigerPortABCD32=0x00000000;
const TUint KEigerPortA8=0x00000000;
const TUint KEigerPortB8=0x00000001;
const TUint KEigerPortC8=0x00000002;
const TUint KEigerPortD8=0x00000003;
const TUint KEigerPortE4=0x00000080;
const TUint KEigerDdrABCD32=0x00000040;
const TUint KEigerDdrA8=0x00000040;
const TUint KEigerDdrB8=0x00000041;
const TUint KEigerDdrC8=0x00000042;
const TUint KEigerDdrD8=0x00000043;
const TUint KEigerDdrE4=0x000000C0;
const TUint KEigerControl21=0x00000100;
const TUint   KEigerControlKeyDrive=0x0000000F;
const TUint   KEigerControlTimer1PreOrFree=0x00000010;
const TUint   KEigerControlTimer1K512OrK2=0x00000020;
const TUint   KEigerControlTimer2PreOrFree=0x00000040;
const TUint   KEigerControlTimer2K512OrK2=0x00000080;
const TUint   KEigerControlUartEnable=0x00000100;
const TUint   KEigerControlBuzzerToggle=0x00000200;
const TUint   KEigerControlBuzzerTimer1OrToggle=0x00000400;
const TUint   KEigerControlDebugEnable=0x00000800;
const TUint   KEigerControlLcdEnable=0x00001000;
const TUint   KEigerControlCodecTxEnable=0x00002000;
const TUint   KEigerControlCodecRxEnable=0x00004000;
const TUint   KEigerControlUartSirEnable=0x00008000;
const TUint   KEigerControlExpClockEnable=0x00040000;
const TUint   KEigerControlWakeupDisable=0x00080000;
const TUint   KEigerControlIrDAWidthEnable=0x00100000;
const TUint KEigerStatus32=0x00000140;
const TUint   KEigerStatusMediaChangedState=0x00000001;
const TUint   KEigerStatusDcPresent=0x00000002;
const TUint   KEigerStatusWakeUpState=0x00000004;
const TUint   KEigerStatusWakeUpFlag=0x00000008;
const TUint   KEigerStatusCts=0x00000100;
const TUint   KEigerStatusDsr=0x00000200;
const TUint   KEigerStatusDcd=0x00000400;
const TUint   KEigerStatusUartTxBusy=0x00000800;
const TUint   KEigerStatusBatteryChangedFlag=0x00001000;
const TUint   KEigerStatusResetFlag=0x00002000;
const TUint   KEigerStatusPowerFailFlag=0x00004000;
const TUint   KEigerStatusColdStartFlag=0x00008000;
const TUint   KEigerStatusUartRxFifoEmpty=0x00400000;
const TUint   KEigerStatusUartTxFifoFull=0x00800000;
const TUint   KEigerStatusCodecRxFifoEmpty=0x01000000;
const TUint   KEigerStatusCodecTxFifoFull=0x02000000;
const TUint   KEigerStatusSpiBusy=0x04000000;
const TUint   KEigerStatusRomBootBusWidth=0x18000000;   // 7211
const TUint   KEigerStatus7211ID=0x20000000;            // 7211
const TUint   KEigerStatusVersionIDLsb=0xC0000000;      // 7211
const TUint KEigerMemConfigLCS32=0x00000180;
const TUint KEigerMemConfigHCS32=0x000001C0;
const TUint KEigerDramRefresh8=0x00000200;
const TUint KEigerIntStatus16=0x00000240;
const TUint KEigerIntMask16=0x00000280;
const TUint   KEigerFiqExt=0x00000001;
const TUint   KEigerFiqBatteryLow=0x00000002;
const TUint   KEigerFiqWatchDog=0x00000004;
const TUint   KEigerFiqMediaChange=0x00000008;
const TUint   KEigerIrqCodec=0x00000010;
const TUint   KEigerIrqExt1=0x00000020;
const TUint   KEigerIrqExt2=0x00000040;
const TUint   KEigerIrqExt3=0x00000080;
const TUint   KEigerIrqTimer1=0x00000100;
const TUint   KEigerIrqTimer2=0x00000200;
const TUint   KEigerIrqRtcMatch=0x00000400;
const TUint   KEigerIrqTick=0x00000800;
const TUint   KEigerIrqUartTx=0x00001000;
const TUint   KEigerIrqUartRx=0x00002000;
const TUint   KEigerIrqUartModem=0x00004000;
const TUint   KEigerIrqSpi=0x00008000;
const TUint KEigerLcdControl32=0x000002C0;
const TUint KEigerTimer1Data16=0x00000300;
const TUint KEigerTimer2Data16=0x00000340;
const TUint KEigerRtcData32=0x00000380;
const TUint KEigerRtcMatch32=0x000003C0;
const TUint KEigerPumpControl12=0x00000400;
const TUint KEigerCodecData8=0x00000440;
const TUint KEigerUartTxData8=0x00000480;
const TUint KEigerUartRxData11=0x00000480;
const TUint   KEigerUartRxDataData=0x000000FF;
const TUint   KEigerUartRxDataError=0x00000700;
const TUint   KEigerUartRxDataFrameErr=0x00000100;
const TUint   KEigerUartRxDataParityErr=0x00000200;
const TUint   KEigerUartRxDataOverrunErr=0x00000400;
const TUint KEigerUartControl19=0x000004C0;
const TUint KEigerSpiData16=0x00000500;
const TUint KEigerPaletteLSW32=0x00000540;
const TUint KEigerPaletteMSW32=0x00000580;
const TUint KEigerStartFlagClear=0x000005C0;
const TUint KEigerBatteryLowEOI=0x00000600;
const TUint KEigerMediaChangedEOI=0x00000640;
const TUint KEigerTickEOI=0x00000680;
const TUint KEigerTimer1EOI=0x000006C0;
const TUint KEigerTimer2EOI=0x00000700;
const TUint KEigerRtcMatchEOI=0x00000740;
const TUint KEigerUartEOI=0x00000780;
const TUint KEigerCodecEOI=0x000007C0;
const TUint KEigerHalt=0x00000800;
const TUint KEigerStandby=0x00000840;

// Cirrus Logic CL-PS7111 extensions
const TUint KEigerLcdFrameBuffer4=0x00001000;		// FRBADDR
const TUint KEigerControl2_15=0x00001100;			// SYSCON2
const TUint   KEigerControl2CodecEnable=0x00000001;
const TUint   KEigerControl2Keyboard6Lines=0x00000002;
const TUint   KEigerControl2DramWidth16=0x00000004;
const TUint   KEigerControl2KeyboardWakeupEnable=0x00000008;
const TUint   KEigerControl2Ssi2TxEnable=0x00000010;
const TUint   KEigerControl2PCMCIA1Enable=0x00000020;
const TUint   KEigerControl2PCMCIA2Enable=0x00000040;
const TUint   KEigerControl2Ssi2RxEnable=0x00000080;
const TUint   KEigerControl2Uart2Enable=0x00000100;
const TUint   KEigerControl2Ssi2Master=0x00000200;
const TUint   KEigerControl2SnoozePolarity=0x00000400;
const TUint   KEigerControl2LcdSnooze=0x00000800;
const TUint   KEigerControl2OsTiming=0x00001000;
const TUint   KEigerControl2ClkOutputEnable=0x00002000;
const TUint   KEigerControl2BuzzEnable=0x00004000;
const TUint KEigerStatus2_24=0x00001140;			// SYSFLG2
const TUint   KEigerStatus2Ssi2RxOverflow=0x00000001;
const TUint   KEigerStatus2Ssi2ResidualByte=0x00000002;
const TUint   KEigerStatus2Ssi2ResidualFrame=0x00000004;
const TUint   KEigerStatus2Ssi2RxFifoEmpty=0x00000008;
const TUint   KEigerStatus2Ssi2TxFifoFull=0x00000010;
const TUint   KEigerStatus2Ssi2TxUnderflow=0x00000020;
const TUint   KEigerStatus2Clock13MHz=0x00000040;
const TUint   KEigerStatus2Uart2TxBusy=0x00000800;
const TUint   KEigerStatus2Uart2RxFifoEmpty=0x00400000;
const TUint   KEigerStatus2Uart2TxFifoFull=0x00800000;
const TUint KEigerInt2Status14=0x00001240;			// INTSR2
const TUint KEigerInt2Mask14=0x00001280;			// INTMR2
const TUint KEigerInt2Mask14CLPS7115=0x00003007;	// Implemented register bits in CL-PS7111
const TUint   KEigerIrqKeyboard=0x00000001;
const TUint   KEigerIrqSpi2Rx=0x00000002;
const TUint   KEigerIrqSpi2Tx=0x00000004;
const TUint   KEigerIrqSpare10=0x00000008;			// Reserved
const TUint   KEigerIrqSpare09=0x00000010;			// Reserved
const TUint   KEigerIrqSpare08=0x00000020;			// Reserved
const TUint   KEigerIrqSpare07=0x00000040;			// Reserved
const TUint   KEigerIrqSpare06=0x00000080;			// Reserved
const TUint   KEigerIrqSpare05=0x00000100;			// Reserved
const TUint   KEigerIrqSpare04=0x00000200;			// Reserved
const TUint   KEigerIrqSpare03=0x00000400;			// Reserved
const TUint   KEigerIrqSpare02=0x00000800;			// Reserved
const TUint   KEigerIrqUart2Tx=0x00001000;
const TUint   KEigerIrqUart2Rx=0x00002000;
const TUint   KEigerIrqSpare01=0x00004000;			// Reserved
const TUint   KEigerIrqSpare00=0x00008000;			// Reserved
const TUint KEigerLcdSnoozeDisplay=0x000012C0;		// SNZDISP
const TUint KEigerUart2TxData8=0x00001480;			// UARTDR2
const TUint KEigerUart2RxData11=0x00001480;			// UARTDR2
const TUint   KEigerUart2RxDataData=0x000000FF;
const TUint   KEigerUart2RxDataError=0x00000700;
const TUint   KEigerUart2RxDataFrameErr=0x00000100;
const TUint   KEigerUart2RxDataParityErr=0x00000200;
const TUint   KEigerUart2RxDataOverrunErr=0x00000400;
const TUint KEigerUart2Control19=0x000014C0;		// UBLCR2
const TUint KEigerSpi2Data16=0x00001500;			// SS2DR
const TUint KEigerSpi2OverflowFlagClear=0x00001600;	// SRXEOF
const TUint KEigerSpi2Pop=0x000016C0;				// SS2POP
const TUint KEigerKeyboardEOI=0x00001700;			// KBDEOI
const TUint KEigerSnoozeEnter=0x00001800;			// SNOOZE

// Cirrus Logic 7211 extensions
const TUint KEigerMultiMediaCodecControl24=0x00002000;  // MCCR
const TUint KEigerMultiMediaCodecData0_16=0x00002040;   // MCDR0
const TUint KEigerMultiMediaCodecData1_16=0x00002080;   // MCDR1
const TUint KEigerMultiMediaCodecData2_21=0x000020C0;   // MCDR2
const TUint KEigerMultiMediaCodecStatus16=0x00002100;   // MCSR
const TUint KEigerControl3_9=0x00002200;			    // SYSCON3
const TUint   KEigerControl3ADCConfigExtension=0x00000001;
const TUint   KEigerControl3ClockControl=0x00000006;
const TUint   KEigerControl3MultiMediaCodecSel=0x00000008;
const TUint   KEigerControl3ADCClockSense=0x00000010;
const TUint   KEigerControl3VersionIDMsb=0x000000E0;
const TUint   KEigerControl3FastWake=0x00000100;
const TUint KEigerInt3Status1=0x00002240;			    // INTSR3
const TUint KEigerInt3Mask1=0x00002280;			        // INTMR3
const TUint KEigerLedFlashControl7=0x000022C0;			// LEDFLSH

class TEiger
    {
public:
    enum TKeyDriveMode
        {
        EKeyDriveModeAllHigh,
        EKeyDriveModeAllLow,
        EKeyDriveModeAllTri,
        EKeyDriveModeSingleColumn
        };
    enum TSpiFrequency
        {
        ESpiFrequency8KHz=0x00000000,
        ESpiFrequency32KHz=0x00010000,
        ESpiFrequency128KHz=0x00020000,
        ESpiFrequency256KHz=0x00030000
        };
    enum TLcdId
        {
        ELcdIdNormal
        };
    enum TChipSelect
        {
        EChipSelect0=0,
        EChipSelect1=8,
        EChipSelect2=16,
        EChipSelect3=24,
        EChipSelect4=32,
        EChipSelect5=40,
        EChipSelect6=48,
        EChipSelect7=56
        };
    enum TBusWidth
        {
        EBusWidth32=0x00,
        EBusWidth16=0x01,
        EBusWidth8=0x02,
        EBusWidthPCMCIA=0x03
        };
    enum TRanWaitState
        {
        ERanWaitState4=0x00,
        ERanWaitState3=0x04,
        ERanWaitState2=0x08,
        ERanWaitState1=0x0C
        };
    enum TSeqWaitState
        {
        ESeqWaitState3=0x00,
        ESeqWaitState2=0x10,
        ESeqWaitState1=0x20,
        ESeqWaitState0=0x30
        };
    enum TSeqMode
        {
        ESequentialModeOff=0x00,
        ESequentialModeOn=0x40
        };
    enum TExpClock
        {
        EExpClockOff=0x00,
        EExpClockOn=0x80
        };
	enum TLcdType					// (Values for LCDCON, actually 2bpp)
        {
        ELcd640x240	=0x5814e95f,
        ELcd640x200	=0x581ce7cf,
		ELcd320x240	=0x5a2a64af,
		ELcd320x200	=0x5a3a63E7
        };
    enum TBitsPerPixel
        {
        EBitsPerPixel1=0,
        EBitsPerPixel2=1,
        EBitsPerPixel4=3
        };
    enum TPumpType
        {
        EPumpType0Battery=0,
        EPumpType0Mains=4,
        EPumpType1=8
        };
    enum TBaudRate
        {
        EBaudRate115200=0x001,
        EBaudRate76800=0x002,
        EBaudRate57600=0x003,
        EBaudRate38400=0x005,
        EBaudRate19200=0x00B,
        EBaudRate14400=0x00F,
        EBaudRate9600=0x017,
        EBaudRate4800=0x02F,
        EBaudRate2400=0x05F,
        EBaudRate1200=0x0BF,
        EBaudRate600=0x17F,
        EBaudRate300=0x2FF,
        EBaudRate150=0x5FF,
        EBaudRate110=0x82E
        };
    enum TBreak
        {
        EBreakOff=0x00000000,
        EBreakOn=0x00001000
        };
    enum TParity
        {
        EParityNone=0x00000000,
        EParityOdd=0x00002000,
        EParityEven=0x00006000
        };
    enum TStopBit
        {
        EStopBitOne=0x00000000,
        EStopBitTwo=0x00008000
        };
    enum TFifo
        {
        EFifoOff=0x00000000,
        EFifoOn=0x00010000
        };
    enum TDataLength
        {
        EDataLength5=0x00000000,
        EDataLength6=0x00020000,
        EDataLength7=0x00040000,
        EDataLength8=0x00060000
        };
    enum TGreyScale
        {
        EGreyScale0=0,
        EGreyScale1=4,
        EGreyScale2=8,
        EGreyScale3=12,
        EGreyScale4=16,
        EGreyScale5=20,
        EGreyScale6=24,
        EGreyScale7=28,
        EGreyScale8=32,
        EGreyScale9=36,
        EGreyScale10=40,
        EGreyScale11=44,
        EGreyScale12=48,
        EGreyScale13=52,
        EGreyScale14=56,
        EGreyScale15=60
        };
    enum TSpiClock
        {
        ESpiClockOff=0x0000,
        ESpiClockOn=0x2000
        };
public:
    IMPORT_C static void SetKeyDriveMode(TKeyDriveMode aKeyDriveMode,TInt aColumn=0);
    IMPORT_C static void SetSpiFrequency(TSpiFrequency aFrequency);
    IMPORT_C static TLcdId LcdId();
    IMPORT_C static TInt RtcTickCount();
    IMPORT_C static TInt CpuVersionId();
    IMPORT_C static void SetChipSelectConfig(TChipSelect aChipSelect,TBusWidth aWidth,TRanWaitState aRan,TSeqWaitState aSeq,TSeqMode aMode,TExpClock aClock);
    IMPORT_C static void SetDramRefresh(TInt aValue);
    IMPORT_C static void SetLcdType(TLcdType anLcdType);
    IMPORT_C static void SetGreyScale(TBitsPerPixel aNumber);
    IMPORT_C static void SetPump(TPumpType aPump,TInt aValue);
    IMPORT_C static void SetTimer1Data(TUint aValue);
    IMPORT_C static TUint Timer1Data();
    IMPORT_C static void SetTimer2Data(TUint aValue);
    IMPORT_C static TUint Timer2Data();
    IMPORT_C static void SetRtcData(TUint aValue);
    IMPORT_C static TUint RtcData();
    IMPORT_C static void SetRtcMatch(TUint aValue);
    IMPORT_C static TUint RtcMatch();
    IMPORT_C static void SetCodecData(TUint aValue);
    IMPORT_C static TUint CodecData();
    IMPORT_C static void SetUartData(TUint aValue);
    IMPORT_C static TUint UartData();
    IMPORT_C static void SetUartConfig(TBaudRate aRate,TParity aParity,TStopBit aStopBit,TDataLength aDataLength);
    IMPORT_C static TBaudRate UartBaudRate();
    IMPORT_C static TParity UartParity();
    IMPORT_C static TStopBit UartStopBit();
    IMPORT_C static TDataLength UartDataLength();
    IMPORT_C static void SetUartBreak(TBreak aBreak);
    IMPORT_C static TBreak UartBreak();
    IMPORT_C static void SetUartFifo(TFifo aFifo);
    IMPORT_C static TFifo UartFifo();
    IMPORT_C static void SetSpiClock(TSpiClock anSpiClock);
    IMPORT_C static void RequestSpiSample(TInt aFrameLength,TInt aConfig);
    IMPORT_C static TUint SpiSample();
    IMPORT_C static void SetPalette(TGreyScale aGreyScale, TInt aValue);
	IMPORT_C static void BootWaitMilliSeconds(TInt aDuration);
//
    IMPORT_C static TUint Status32();
    IMPORT_C static TInt TestStatus32(TUint aMask);
    IMPORT_C static TUint PortABCD32();
    IMPORT_C static TUint PortA8();
    IMPORT_C static TUint PortB8();
    IMPORT_C static TUint PortC8();
    IMPORT_C static TUint PortD8();
    IMPORT_C static TUint PortE4();
    IMPORT_C static void QuickSetPortABCD32(TUint aValue);
    IMPORT_C static void QuickSetPortE4(TUint aValue);
    IMPORT_C static void SetPortABCD32(TUint aValue);
    IMPORT_C static void SetPortA8(TUint aValue);
    IMPORT_C static void SetPortB8(TUint aValue);
    IMPORT_C static void SetPortC8(TUint aValue);
    IMPORT_C static void SetPortD8(TUint aValue);
    IMPORT_C static void SetPortE4(TUint aValue);
    IMPORT_C static void ModifyPortABCD32(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortA8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortB8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortC8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortD8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortE4(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrABCD32(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrA8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrB8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrC8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrD8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrE4(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void SetDdrABCD32(TUint aValue);
    IMPORT_C static void SetDdrA8(TUint aValue);
    IMPORT_C static void SetDdrB8(TUint aValue);
    IMPORT_C static void SetDdrC8(TUint aValue);
    IMPORT_C static void SetDdrD8(TUint aValue);
    IMPORT_C static void SetDdrE4(TUint aValue);
    IMPORT_C static TUint Control21();
    IMPORT_C static void SetControl21(TUint aValue);
    IMPORT_C static void ModifyControl21(TUint aClearMask,TUint aSetMask);
    IMPORT_C static TUint IntStatus16();
    IMPORT_C static TInt TestIntStatus16(TUint aMask);
    IMPORT_C static void ModifyIntMask16(TUint aClearMask,TUint aSetMask);
    IMPORT_C static TUint IntMask16();
    IMPORT_C static void SetIntMask16(TUint aValue);
	IMPORT_C static TMachineStartupType StartupReason();
    IMPORT_C static void SetStartFlagClear();
    IMPORT_C static void SetBatteryLowEOI();
    IMPORT_C static void SetMediaChangedEOI();
    IMPORT_C static void SetTickEOI();
    IMPORT_C static void SetTimer1EOI();
    IMPORT_C static void SetTimer2EOI();
    IMPORT_C static void SetRtcMatchEOI();
    IMPORT_C static void SetUartEOI();
    IMPORT_C static void SetCodecEOI();
    IMPORT_C static void SetHalt();
    IMPORT_C static void SetStandby();
// Cirrus Logic CL-PS7111 extensions
    IMPORT_C static TUint8 LcdFrameBuffer();
    IMPORT_C static void SetLcdFrameBuffer(TUint8 aBufStart);
    IMPORT_C static TUint Control2_15();
    IMPORT_C static void SetControl2_15(TUint aValue);
    IMPORT_C static void ModifyControl2_15(TUint aClearMask,TUint aSetMask);
    IMPORT_C static TUint Status2_24();
    IMPORT_C static TInt TestStatus2_24(TUint aMask);
    IMPORT_C static TUint Int2Status14();
    IMPORT_C static TInt TestInt2Status14(TUint aMask);
    IMPORT_C static void ModifyInt2Mask14(TUint aClearMask,TUint aSetMask);
    IMPORT_C static TUint Int2Mask14();
    IMPORT_C static void SetInt2Mask14(TUint aValue);
    IMPORT_C static TUint LcdSnoozeSize();
    IMPORT_C static void SetLcdSnoozeSize(TUint aNumWords);
    IMPORT_C static void SetUart2Data(TUint aValue);
    IMPORT_C static TUint Uart2Data();
    IMPORT_C static void SetUart2Config(TBaudRate aRate,TParity aParity,TStopBit aStopBit,TDataLength aDataLength);
    IMPORT_C static TBaudRate Uart2BaudRate();
    IMPORT_C static TParity Uart2Parity();
    IMPORT_C static TStopBit Uart2StopBit();
    IMPORT_C static TDataLength Uart2DataLength();
    IMPORT_C static void SetUart2Break(TBreak aBreak);
    IMPORT_C static TBreak Uart2Break();
    IMPORT_C static void SetUart2Fifo(TFifo aFifo);
    IMPORT_C static TFifo Uart2Fifo();
    IMPORT_C static void SetSpi2Clock(TSpiClock anSpiClock);
    IMPORT_C static void RequestSpi2Sample(TInt aFrameLength,TInt aConfig);
    IMPORT_C static TUint Spi2Sample();
    IMPORT_C static void SetKeyboardEOI();
    IMPORT_C static void SetSnoozeEnter();
// Cirrus Logic 7211 extensions
    IMPORT_C static TUint MCPControl_24();
    IMPORT_C static void SetMCPControl_24(TUint aValue);
    IMPORT_C static void ModifyMCPControl_24(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void SetMCPData0(TUint aValue);
    IMPORT_C static TUint MCPData0();
    IMPORT_C static void SetMCPData1(TUint aValue);
    IMPORT_C static TUint MCPData1();
    IMPORT_C static void SetMCPData2(TUint aValue);
    IMPORT_C static TUint MCPData2();
    IMPORT_C static TUint MCPStatus16();
    IMPORT_C static TInt TestMCPStatus16(TUint aMask);
    IMPORT_C static TUint Control3_9();
    IMPORT_C static void SetControl3_9(TUint aValue);
    IMPORT_C static void ModifyControl3_9(TUint aClearMask,TUint aSetMask);
    IMPORT_C static TUint Int3Status1();
    IMPORT_C static TUint Int3Mask1();
    IMPORT_C static void SetInt3Mask1(TUint aValue);
    IMPORT_C static TUint LedFlashControl();
    IMPORT_C static void SetLedFlashControl(TUint aValue);
//
    static void Init3();
    };

#endif

