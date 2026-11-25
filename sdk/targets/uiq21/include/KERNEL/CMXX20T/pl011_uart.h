// PL011_UART.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// Based on Arm Technical reference manual 'Arm Prime Cell UART (PL011)'
//

#ifndef __PL011_UART_H__
#define __PL011_UART_H__

#include "a32integratorLM.h"    /// Low level register access routines

class TPL011_UART
    {
public:
    /// Enumerate for the baud rates.  This 32 bit value is used to program
    /// the integer and fractional BRD in the Uart.  The lower word for the
    /// fractional value and the higher word for the integer value.  The are
    /// only valid if the oscillator driving the UART is set at 7.37MHz
    enum TUartBaud
        {
        EBaud50     = 0x13880001,
        EBaud75     = 0x0D050016,
        EBaud110    = 0x08E0002F,
        EBaud134    = 0x0749002B,
        EBaud150    = 0x0682002B,
        EBaud300    = 0x03410016,
        EBaud600    = 0x01A0002B,
        EBaud1200   = 0x00D00016,
        EBaud1800   = 0x008A0039,
        EBaud2000   = 0x007D0001,
        EBaud2400   = 0x0068000B,
        EBaud3600   = 0x0045001D,
        EBaud4800   = 0x00340006,
        EBaud7200   = 0x0022002F,	
        EBaud9600   = 0x001a0003,	
        EBaud19200  = 0x000d0002,	
        EBaud38400  = 0x00060021,	
        EBaud57600  = 0x00040016,	
        EBaud115200 = 0x0002000B,	
        EBaud230400 = 0x00010006,	
        EBaud460800 = 0x00000023	
        };

    /// Enumerate for the parity settings in the LCRH register.
    /// This enumerate is used when writing to the control register
    /// to set or clear specific parity settings.  The lower byte is
    /// used to set parity settings and the upper byte is used to 
    /// clear parity settings.
    enum TUartParity
        {
        EParityOdd  = 0x0602,
        EParityNone = 0x0600,
        EParityEven = 0x0606
        };

    /// TUartDataBits sets 5, 6, 7 or 8 data bits using the LCRH bits 5 and 6.
    /// The enumerate value is used when writing to the Uart registers.  The
    /// lower byte is written to the SET mask whilst the upper byte is written
    /// to the CLEAR mask when modifying the register.
    enum TUartDataBits
		{
		EDataBits5 = 0x6000,
		EDataBits6 = 0x6020,
		EDataBits7 = 0x6040,
		EDataBits8 = 0x6060
		};


    /// Enumerate for the stop bits.  As above, lower byte used to set, upper
    /// byte used to clear in the LCRH.
    enum TUartStopBits
        {
        EOneStopBit  = 0x0800,
        ETwoStopBits = 0x0008
        };

public:
    /// The base address for this prime cell is defined in the Logic Module
    /// header file.  There are two uarts on the prime cell with bases at
    /// KLM_Uart0Base and KLM_Uart1Base.

    /// Each UART has the same register set, offest from their base.  These
    /// constants provide the required offsets.
    static const TUint KData                  = 0x00;
    static const TUint KReceiveStatus         = 0x04;
    static const TUint KErrorClear            = 0x04;
    static const TUint KFlags                 = 0x18;
    static const TUint KIrdaLowPower          = 0x20;
    static const TUint KIntBaudRateDiv        = 0x24;
    static const TUint KFracBaudRateDiv       = 0x28;
    static const TUint KLineControlHigh       = 0x2C;
    static const TUint KControl               = 0x30;
    static const TUint KInterruptFifoSelect   = 0x34;
    static const TUint KInterruptMask         = 0x38;
    static const TUint KRawInterruptStatus    = 0x3C;
    static const TUint KMaskedInterruptStatus = 0x40;
    static const TUint KInterruptClear        = 0x44;
    static const TUint KDMAControl            = 0x48;

    
    /// Data register methods
    IMPORT_C static void    SetDataRegister( TUint aUart, TUint8 aData );
    IMPORT_C static TUint16 DataRegister(    TUint aUart );
    IMPORT_C static void    ClearErrors(     TUint aUart );
    /// Data register constants
    static const TUint16 KDataMask       = 0x00FF;
    static const TUint16 KErrorMask      = 0x0F00;
    static const TUint16 KDRFramingError = 0x0100;
    static const TUint16 KDRParityError  = 0x0200;
    static const TUint16 KDRBreakError   = 0x0400;
    static const TUint16 KDROverrunError = 0x0800;

    /// Flag regsiter method
    IMPORT_C static TUint16 FlagsRegister( TUint aUart );
    /// Flag register constants
    static const TUint16 KFlagCTS           = 0x0001;
    static const TUint16 KFlagDSR           = 0x0002;
    static const TUint16 KFlagDCD           = 0x0004;
    static const TUint16 KFlagUartBusy      = 0x0008;
    static const TUint16 KFlagRxFifoEmpty   = 0x0010;
    static const TUint16 KFlagTxFifoFull    = 0x0020;
    static const TUint16 KFlagRxFifoFull    = 0x0040;
    static const TUint16 KFlagTxFifoEmpty   = 0x0080;
    static const TUint16 KFlagRingIndicator = 0x0100;

    /// Baud rate divisor registers methods
    IMPORT_C static void  SetBaudRateDivisor( TUint aUart, TUartBaud aData );
    IMPORT_C static TUint BaudRateDivisor(    TUint aUart );

    /// Line control register methods
    IMPORT_C static void   ModifyLineControlRegister( TUint aUart, TUint8 aSet, TUint8 aClear );
    IMPORT_C static TUint8 LineControlRegister(       TUint aUart );
    /// Line control register constants
    static const TUint8 KLcrhSendBreak          = 0x01;
    static const TUint8 KLcrhParityEnable       = 0x02;
    static const TUint8 KLcrhEvenParitySelect   = 0x04;
    static const TUint8 KLcrhTwoStopBitSelect   = 0x08;
    static const TUint8 KLcrhEnableFifos        = 0x10;
    static const TUint8 KLcrhDataBits           = 0x60;
    static const TUint8 KLcrhStickyParitySelect = 0x80;
    /// More useful constants
    static const TUint8 KLcrhSetEvenParity      = 0x06;
    static const TUint8 KLchrSetOddParty        = 0x02;
    static const TUint8 KLcrhSetNoParity        = 0x00; // Bit 1 cleared, bit 2 n/a
    static const TUint8 KLcrhSet5DataBits       = 0x00;
    static const TUint8 KLcrhSet6DataBits       = 0x20;
    static const TUint8 KLcrhSet7DataBits       = 0x40;
    static const TUint8 KLcrhSet8DataBist       = 0x60;
    static const TUint8 KLcrhDisableFifos       = 0x00; // Fifo bit not set
    static const TUint8 KLcrhNoBreakStickParity = 0x81; // No break or sticky parity selected

    /// Control register methods
    IMPORT_C static void    ModifyControlRegister( TUint aUart, TUint16 aSet, TUint16 aClear );
    IMPORT_C static TUint16 ControlRegister(       TUint aUart );
    /// Control register constants
    static const TUint16 KCtrlUARTEnable            = 0x0001;
    static const TUint16 KCtrlSIREnable             = 0x0002;
    static const TUint16 KCtrlSIRLowPower           = 0x0004;
    static const TUint16 KCtrlLoopBackEnable        = 0x0080;
    static const TUint16 KCtrlTransmitEnable        = 0x0100;
    static const TUint16 KCtrlReceiveEnable         = 0x0200;
    static const TUint16 KCtrlDTR                   = 0x0400;
    static const TUint16 KCtrlRTS                   = 0x0800;
    static const TUint16 KCtrlDCD                   = 0x1000;
    static const TUint16 KCtrlRI                    = 0x2000;
    static const TUint16 KCtrlRTSEnable             = 0x4000;
    static const TUint16 KCtrlCTSEnable             = 0x8000;

    /// Fifo trigger level methods
    IMPORT_C static void    SetFIFOTriggerLevel( TUint aUart, TUint8 aData );
    IMPORT_C static TUint8  FIFOTriggerLevel(    TUint aUart );
    /// Constants for fifo trigger levels
    static const TUint8 KFifoTransmitLevelMask     = 0x07;
    static const TUint8 KFifoReceiveLevelMask      = 0x38;
    static const TUint8 KFifoCombinedLevelMask     = 0x3F;
    static const TUint8 KFifoTxOneEigthFull        = 0x00;
    static const TUint8 KFifoTxOneQuarterFull      = 0x01;
    static const TUint8 KFifoTxOneHalfFull         = 0x02;
    static const TUint8 KFifoTxThreeQuarterFull    = 0x03;
    static const TUint8 KFifoTxSevenEigthFull      = 0x04;
    static const TUint8 KFifoRxOneEigthFull        = 0x00;
    static const TUint8 KFifoRxOneQuarterFull      = 0x08;
    static const TUint8 KFifoRxOneHalfFull         = 0x10;
    static const TUint8 KFifoRxThreeQuarterFull    = 0x18;
    static const TUint8 KFifoRxSevenEigthFull      = 0x20;

    /// Interrupt register methods
    IMPORT_C static void    SetInterruptMask(   TUint aUart, TUint16 aData );
    IMPORT_C static void    ClearInterruptMask( TUint aUart, TUint16 aData );
    IMPORT_C static TUint16 InterruptMask(      TUint aUart );
    IMPORT_C static TUint16 ReceivedInterrupt(  TUint aUart );
    IMPORT_C static void    ClearInterrupt(     TUint aUart, TUint16 aData );
    /// Interrupt constants
    static const TUint16 KInterruptRI             = 0x0001;
    static const TUint16 KInterruptCTS            = 0x0002;
    static const TUint16 KInterruptDCD            = 0x0004;
    static const TUint16 KInterruptDSR            = 0x0008;
    static const TUint16 KInterruptControlLines   = 0x000F;
    static const TUint16 KInterruptReceive        = 0x0010;
    static const TUint16 KInterruptTransmit       = 0x0020;
    static const TUint16 KInterruptReceiveTimeout = 0x0040;
    static const TUint16 KInterruptFramingError   = 0x0080;
    static const TUint16 KInterruptParityError    = 0x0100;
    static const TUint16 KInterruptBreakError     = 0x0200;
    static const TUint16 KInterruptOverrunError   = 0x0400;





/* TO BE IMPLEMENTED but not required for COM drivers
    IMPORT_C static TUint8  StatusRegister(     TUint aUart );
    IMPORT_C static void    SetIrdaLowPowerCounter( TUint aUart, TUint8 aData );
    IMPORT_C static TUint8  IrdaLowPowerCounter(    TUint aUart );
    IMPORT_C static TUint16 RawInterruptStatus( TUint aUart );
    IMPORT_C static void    SetDMAControl( TUint aUart, TUint16 aData );
    IMPORT_C static TUint16 DMAControl(    TUint aUart );

    /// Constants for the status register - not needed, read from data register with data
    static const TUint8  KSTFramingError            = 0x01;
    static const TUint8  KSTParityError             = 0x02;
    static const TUint8  KSTBreakError              = 0x04;
    static const TUint8  KSTOverrunError            = 0x08;

    /// Constants for the DMA control register
    static const TUint16 KDMAReceiveEnable          = 0x0001;
    static const TUint16 KDMATransmitEnable         = 0x0002;
    static const TUint16 KDMAOnError                = 0x0004;

*/
    };

#endif