// TPL021_SSP.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// Based on Arm Technical reference manual 'Arm Prime Cell SSP (PL021)'
//

#ifndef __TPL021_SSP_H__
#define __TPL021_SSP_H_

#include "a32integratorLM.h"    /// Low level register access routines

class TPL021_SSP
    {
public:
    /// Register indexed from the base
    static const TUint KControl0       = TIntegratorLM::KLM_SSP + 0x0000;
    static const TUint KControl1       = TIntegratorLM::KLM_SSP + 0x0004;
    static const TUint KData           = TIntegratorLM::KLM_SSP + 0x0008;
    static const TUint KStatus         = TIntegratorLM::KLM_SSP + 0x000C;
    static const TUint KClockPreScale  = TIntegratorLM::KLM_SSP + 0x0010;
    static const TUint KInterruptRead  = TIntegratorLM::KLM_SSP + 0x0014;
    static const TUint KInterruptClear = TIntegratorLM::KLM_SSP + 0x0014;
    
    /// Control Register 0
    IMPORT_C static TUint Control0();
    IMPORT_C static void  ModifyControl0( TUint aSetBits, TUint aClearBits );
    static const TUint K4BitData        = 0x0003;
    static const TUint K5BitData        = 0x0004;
    static const TUint K6BitData        = 0x0005;
    static const TUint K7BitData        = 0x0006;
    static const TUint K8BitData        = 0x0007;
    static const TUint K9BitData        = 0x0008;
    static const TUint K10BitData       = 0x0009;
    static const TUint K11BitData       = 0x000A;
    static const TUint K12BitData       = 0x000B;
    static const TUint K13BitData       = 0x000C;
    static const TUint K14BitData       = 0x000D;
    static const TUint K15BitData       = 0x000E;
    static const TUint K16BitData       = 0x000F;
    static const TUint KMotorolaFormat  = 0x0000;
    static const TUint KTIFormat        = 0x0010;
    static const TUint KNationalFormat  = 0x0020;
    static const TUint KSClkOutPolarity = 0x0040;
    static const TUint KSClkOutPhase    = 0x0080;
    static const TUint KSerialClockRate = 0x0000;


    /// Control Register 1
    IMPORT_C static TUint Control1();
    IMPORT_C static void  ModifyControl1( TUint aSetBits, TUint aClearBits ); 
    static const TUint KRxFifoIntEn        = 0x0001;
    static const TUint KTxFifoIntEn        = 0x0002;
    static const TUint KRxFifoOverrunIntEn = 0x0004;
    static const TUint KLoopBackMode       = 0x0008;
    static const TUint KSyncSerialPortEn   = 0x0010;
    static const TUint KSlaveModeSelect    = 0x0020;
    static const TUint KSlaveOutputDisable = 0x0040;


    /// Data register
    IMPORT_C static TUint Data();
    IMPORT_C static void  SetData( TUint aData );


    /// Status register
    IMPORT_C static TUint16 Status();
    static const TUint KTransmitFifoEmpty   = 0x0001;
    static const TUint KTransmitFifoNotFull = 0x0002;
    static const TUint KReceiveFifoNotEmpty = 0x0004;
    static const TUint KReceiveFifoFull     = 0x0008;
    static const TUint KBusy                = 0x0010;


    /// Clock pre-scale register
    IMPORT_C static TUint8 ClockPreScale();
    IMPORT_C static void   SetClockPreScale( TUint8 aData );
    static const TUint KPreScaleCPSDVR2 = 0x0002;

    
    /// Interrupt ID
    IMPORT_C static TUint8 PendingInterrupts();
    IMPORT_C static void   ClearOverRunInterrupt();
    static const TUint KTransmitFifoInterrupt = 0x0001;
    static const TUint KReceiveFifoInterrupt  = 0x0002;
    static const TUint KReceiveFifoOverrun    = 0x0004;

    };

#endif