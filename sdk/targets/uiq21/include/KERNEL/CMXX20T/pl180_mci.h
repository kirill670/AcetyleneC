// PL180_MCI.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// This file contains the class definition for the MCI prime cell 
// described by the ARM technical reference document PL180.
//

#ifndef __PL180_MCI_H__
#define __PL180_MCI_H__


#include "a32integratorLM.h"

class TPL180_MCI
    {
public:
	static const TUint KFifoSizeWords = 16;
	static const TUint KHalfFifoSizeWords = 8;

	enum TPowerState
		{
		EMciPowerOff	= 0,
		EMciPowerUp		= 2,
		EMciPowerOn		= 3,
		EMciPowerMask	= 3
		};

	/**
     * Multimedia Card Interface
     *
     * PrimeCell Technical Reference PL180
     *
     */

    /// Register addresses
    static const TUint KHwMciPower         = 0x0000;
    static const TUint KHwMciClock         = 0x0004;
    static const TUint KHwMciArgument      = 0x0008;
    static const TUint KHwMciCommand       = 0x000C;
    static const TUint KHwMciRespCmd       = 0x0010;
    static const TUint KHwMciResponse0     = 0x0014;
    static const TUint KHwMciResponse1     = 0x0018;
    static const TUint KHwMciResponse2     = 0x001C;
    static const TUint KHwMciResponse3     = 0x0020;
    static const TUint KHwMciDataTimer     = 0x0024;
    static const TUint KHwMciDataLength    = 0x0028;
    static const TUint KHwMciDataCtrl      = 0x002C;
    static const TUint KHwMciDataCnt       = 0x0030;
    static const TUint KHwMciStatus        = 0x0034;
    static const TUint KHwMciClear         = 0x0038;
    static const TUint KHwMciMask0         = 0x003C;
    static const TUint KHwMciMask1         = 0x0040;
    static const TUint KHwMciSelect        = 0x0044;
    static const TUint KHwMciFifoCnt       = 0x0048;
    static const TUint KHwMciFifoStart     = 0x0080;
    static const TUint KHwMciPeriphId0     = 0x0FE0;
    static const TUint KHwMciPeriphId1     = 0x0FE4;
    static const TUint KHwMciPeriphId2     = 0x0FE8;
    static const TUint KHwMciPeriphId3     = 0x0FEC;
    static const TUint KHwMciCellId0       = 0x0FF0;
    static const TUint KHwMciCellId1       = 0x0FF4;
    static const TUint KHwMciCellId2       = 0x0FF8;
    static const TUint KHwMciCellId3       = 0x0FFC;

    /// Power control register bit masks
    static const TUint KMciPower           = 0x00000003;
    static const TUint KMciVoltage         = 0x0000003C;
    static const TUint KMciOpenDrain       = 0x00000040;
    static const TUint KMciRod             = 0x00000080;

    /// Power control register, power ctrl values
    static const TUint KMciPowerOff        = 0x00000000;
    static const TUint KMciPowerUp         = 0x00000002;
    static const TUint KMciPowerOn         = 0x00000003;
	static const TUint KMciPowerOpenDrain	= 0x40;
	static const TUint KMciPowerRod			= 0x80;
	static const TUint KMciPowerMask		= 0x3;	// mask off power bits
	static const TUint KMciVoltageMask		= 0x3C; // mask off voltage bits
	static const TUint KMciVoltageShift		= 2;



    /// Clock control register bits
    static const TUint KMciClkDiv          = 0x000000FF;
    static const TUint KMciClkEnable       = 0x00000100;
    static const TUint KMciPwrSave         = 0x00000200;
    static const TUint KMciBypass          = 0x00000400;
    static const TUint KMciWideBus         = 0x00000800;

    static const TUint KMciClkDivShift     = 0;


    /// Command register bits
    static const TUint KMciCmdIndex        = 0x0000003F;
    static const TUint KMciResponse        = 0x00000040;
    static const TUint KMciLongRsp         = 0x00000080;
    static const TUint KMciInterrupt       = 0x00000100;
    static const TUint KMciPending         = 0x00000200;
    static const TUint KMciEnable          = 0x00000400;

    /// Command response register bits
    static const TUint KMciRespCmd         = 0x0000003F;

    /// Data length register bits
    static const TUint KMciDataLength      = 0x0000FFFF;
    
    /// Data control regsiter bits
    static const TUint KMciDataEnable      = 0x00000001;
    static const TUint KMciDirectionRead   = 0x00000002;
    static const TUint KMciMode            = 0x00000004;
    static const TUint KMciDMAEnable       = 0x00000008;
    static const TUint KMciBlockSize       = 0x000000F0;

    /// Data counter register bits
    static const TUint KMciDataCount       = 0x0000FFFF;

    /// Status register and interrupt mask register bits
    static const TUint KMciCmdCrcFail      = 0x00000001;
    static const TUint KMciDataCrcFail     = 0x00000002;
    static const TUint KMciCmdTimeOut      = 0x00000004;
    static const TUint KMciDataTimeOut     = 0x00000008;
    static const TUint KMciTxUnderrun      = 0x00000010;
    static const TUint KMciRxOverrun       = 0x00000020;
    static const TUint KMciCmdRespEnd      = 0x00000040;
    static const TUint KMciCmdSent         = 0x00000080;
    static const TUint KMciDataEnd         = 0x00000100;
    static const TUint KMciStartBitErr     = 0x00000200;
    static const TUint KMciDataBlockEnd    = 0x00000400;
    static const TUint KMciCmdActive       = 0x00000800;
    static const TUint KMciTxActive        = 0x00001000;
    static const TUint KMciRxActive        = 0x00002000;
    static const TUint KMciTxFifoHalfEmpty = 0x00004000;
    static const TUint KMciRxFifoHalfFull  = 0x00008000;
    static const TUint KMciTxFifoFull      = 0x00010000;
    static const TUint KMciRxFifoFull      = 0x00020000;
    static const TUint KMciTxFifoEmpty     = 0x00040000;
    static const TUint KMciRxFifoEmpty     = 0x00080000;
    static const TUint KMciTxDataAvailable = 0x00100000;
    static const TUint KMciRxDataAvailable = 0x00200000;

	static const TUint KMciStaticFlagsMask	= 0x000007FF;
	static const TUint KMciAllFlagsMask		= 0x003FFFFF;

    /// Clear register bits
    static const TUint KMciCmdCrcFailClr   = 0x00000001;
    static const TUint KMciDataCrcFailClr  = 0x00000002;
    static const TUint KMciCmdTimeOutClr   = 0x00000004;
    static const TUint KMciDataTimeOutClr  = 0x00000008;
    static const TUint KMciTxUnderrunClr   = 0x00000010;
    static const TUint KMciRxOverrunClr    = 0x00000020;
    static const TUint KMciCmdRespEndClr   = 0x00000040;
    static const TUint KMciCmdSentClr      = 0x00000080;
    static const TUint KMciDataEndClr      = 0x00000100;
    static const TUint KMciStartBitErrClr  = 0x00000200;
    static const TUint KMciDataBlockEndClr = 0x00000400;

    /// Secure digital memory card select register bits
    static const TUint KMciSDCard          = 0x0000000F;

    /// FIFO count register bits
    static const TUint KMciFifoDataCount   = 0x00007FFF;
    
    /// Peripheral ID register bits
    static const TUint KMciPartNumber0     = 0x000000FF;
    static const TUint KMciPartNumber1     = 0x00000F00;
    static const TUint KMciDesigner0       = 0x0000F000;
    static const TUint KMciDesigner1       = 0x000F0000;
    static const TUint KMciRevision        = 0x00F00000;
    static const TUint KMciConfiguration   = 0xFF000000;

    /// Cell ID register bits
    static const TUint KMciPCellID0        = 0x000000FF;
    static const TUint KMciPCellID1        = 0x0000FF00;
    static const TUint KMciPCellID2        = 0x00FF0000;
    static const TUint KMciPCellID3        = 0xFF000000;


	/// Read peripheral & prime cell identification registers
	IMPORT_C static TUint TPL180_MCI::PeripheralId();
	IMPORT_C static TUint TPL180_MCI::PrimeCellId();


    /// Read and write the power control register
    IMPORT_C static TUint PowerControl();
    IMPORT_C static void  SetPowerControl( TUint aValue );
    IMPORT_C static void  ModifyPowerControl( TUint aClearMask, TUint aSetMask );
    IMPORT_C static void  SetPowerState( TPowerState aState );
    IMPORT_C static void  SetPowerVoltage( TUint aVoltage );

    /// Read and write the clock control register
    IMPORT_C static TUint ClockControl();
    IMPORT_C static void  SetClockControl( TUint aValue );

    /// Read and write the argument register
    IMPORT_C static TUint Argurment();
    IMPORT_C static void  SetArgument( TUint aValue );

    /// Read and write the command register
    IMPORT_C static TUint Command();
    IMPORT_C static void  SetCommand( TUint aValue );
    IMPORT_C static void  ModifyCommand( TUint aClearMask, TUint aSetMask );

    /// Read the command response register
    IMPORT_C static TUint CommandResponse();

    /// Read the response register
    IMPORT_C static TUint Response0();
    IMPORT_C static TUint Response1();
    IMPORT_C static TUint Response2();
    IMPORT_C static TUint Response3();

    /// Read and write the data timer register
    IMPORT_C static TUint DataTimer();
    IMPORT_C static void  SetDataTimer( TUint aValue );

    /// Read and write the data length register
    IMPORT_C static TUint DataLength();
    IMPORT_C static void  SetDataLength( TUint aValue );

    /// Read and write the data control register
    IMPORT_C static TUint DataControl();
    IMPORT_C static void  SetDataControl( TUint aValue );

    /// Read data count register
    IMPORT_C static TUint DataCounter();

    /// Read status register
    IMPORT_C static TUint Status();

    /// Write to the clear register
    IMPORT_C static void  ClearStatus( TUint aValue );

    /// Read and write to interrupt mask registers
    IMPORT_C static TUint InterruptMask0();
    IMPORT_C static TUint InterruptMask1();
    IMPORT_C static void  SetInterruptMask0( TUint aValue );
    IMPORT_C static void  SetInterruptMask1( TUint aValue );

    /// Read and write the secure digital memory card select register
    IMPORT_C static TUint SDCardSelect();
    IMPORT_C static void  SetSDCardSelect( TUint aValue );

    /// Read the FIFO count register
    IMPORT_C static TUint FifoCount();

    /// Read and write the FIFO register
    IMPORT_C static TUint Fifo();
    IMPORT_C static void  SetFifo( TUint aValue );
	/// Read and write a half-FIFO (8 words), returns updated pointer
	IMPORT_C static TUint32* FifoReadHalf( TUint32* aDest );
	IMPORT_C static const TUint32* FifoWriteHalf( const TUint32* aSrc );

    };

#endif