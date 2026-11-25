// A32INTEGRATORPL.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// This file contains static constants defining the location of the
// various prime cells that reside on the logic module
//

#ifndef __A32INTEGRATORLM_H__
#define __A32INTEGRATORLM_H__

#include "a32integratorap.h"


/**
 * CLASS: TIntegratorLM
 *
 * Provides constants for the base addresses of the peripherals on the logic module.
 * Provides constants and methods for accessing registers on the logic module that are
 * not part of other prime cell peripherals.
 *
 * Uses the ASSP class to access registers.
 */
class TIntegratorLM
    {
public:

	/* 
	 * philk - L999 
	 * Use correct LM base vaddr (maps to paddr 0xC000.0000)
	 * shown as 0x5803.0000 by bootstrap debug. Note that the order of
	 * these defines depends on the order of IO banks defined in the 
	 * file /base/integratorap/bootstrap/integratorap.s
	 */


    static const TUint KLM_BaseAddress = 0x58030000;

    static const TUint KLM_AACI       = KLM_BaseAddress + 0x0000;
    static const TUint KLM_MMC        = KLM_BaseAddress + 0x1000;
    static const TUint KLM_Oscillator = KLM_BaseAddress + 0x2000;
    static const TUint KLM_Uart0      = KLM_BaseAddress + 0x3000;
    static const TUint KLM_SCI        = KLM_BaseAddress + 0x4000;
    static const TUint KLM_SSP        = KLM_BaseAddress + 0x5000;
    static const TUint KLM_Uart1      = KLM_BaseAddress + 0x6000;
    static const TUint KLM_LCD        = KLM_BaseAddress + 0x7000;
    /// VIC is accessed through the ASSP class
    static const TUint KLM_Gpio0      = KLM_BaseAddress + 0x9000;
    static const TUint KLM_Gpio1      = KLM_BaseAddress + 0xA000;
    static const TUint KLM_Tsci       = KLM_BaseAddress + 0xB000;
    static const TUint KLM_UsbHost    = KLM_BaseAddress + 0xC000;
    static const TUint KLM_UsbSlave   = KLM_BaseAddress + 0xD000;

public:
    /// Constants for logic module registers
    static const TUint KLM_OscillatorClk1   = KLM_Oscillator + 0x00;
    static const TUint KLM_OscillatorClk2   = KLM_Oscillator + 0x04;
    static const TUint KLM_OscillatorLock   = KLM_Oscillator + 0x08;
    static const TUint KLM_LEDS             = KLM_Oscillator + 0x0C;
    static const TUint KLM_ButtonInterrupt  = KLM_Oscillator + 0x10;
    static const TUint KLM_Switches         = KLM_Oscillator + 0x14;
    static const TUint KLM_LCDMuxControl    = KLM_Oscillator + 0x1C;

    static const TUint KLMOscUnlockValue    = 0x0000A05F;
    static const TUint KLMOscLockValue      = 0xFFFFFFFF;

    /// Generate a LcdClk input signal of 12.5MHz.  This signal is used to
    /// drive the following prime cells on the logic module
    /// LCD only
    static const TUint KClk1OscLoadValue    = 0x00012C11; 

    /// Generate a UartClk input signal of 16MHz.  This signal is used to
    /// drive the following prime cells on the logic module
    /// UART 0
    /// UART 1
    /// SSP
    /// SCI
    /// TSCI
    /// USB Host
    static const TUint KClk2OscLoadValue    = 0x00015C18; 

    /// LCD Mux Control register constants
    static const TUint EnableSharpDisplay   = 0x04;
    static const TUint EnableVGAMonitor     = 0x05;
    static const TUint EnableLCD1Connector  = 0x06;
    static const TUint DisableDisplay       = 0x00;


    /// Accessors for the above registers
    IMPORT_C static TUint32 OscillatorClk1();
    IMPORT_C static void    SetOscialltorClk1( TUint aData );
    
    IMPORT_C static TUint32 OscillatorClk2();
    IMPORT_C static void    SetOscillatorClk2( TUint aData );

    IMPORT_C static void    UnlockOscillators();
    IMPORT_C static void    LockOscillators();

    IMPORT_C static TUint32 LCDSelector();
    IMPORT_C static void    SetLCDSelector( TUint aData );
    };



#endif
