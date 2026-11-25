// PL061_GPIO.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// Based on Arm Technical reference manual 'Arm Prime Cell GPIO (PL061)'
//

#ifndef __PL061_GPIO_H__
#define __PL061_GPIO_H_

#include "a32integratorLM.h"    /// Low level register access routines

class TPL061_GPIO
    {
public:
    /// The base address for this prime cell is defined in the Logic Module header
    /// file.  There are two GPIOs on the prime cess with their base address at
    /// KLM_Gpio0 and KLM_Gpio1.

    /// Each GPIO has the same register set, offset from their base.
    /// These constants provide the required offests.

    static const TUint KDataBase                = 0x0000;
    static const TUint KDirection               = 0x0400;
    static const TUint KInterruptSense          = 0x0404;
    static const TUint KInterruptBothEdges      = 0x0408;
    static const TUint KInterruptEvent          = 0x040C;
    static const TUint KInterruptMask           = 0x0410;
    static const TUint KInterruptRawStatus      = 0x0414;
    static const TUint KInterruptMaskedStatus   = 0x0418;
    static const TUint KInterruptClear          = 0x041C;
    static const TUint KModeControl             = 0x0420;


    /// Data register methods
    IMPORT_C static TUint8 Data(      TUint aGpio, TUint aMask );
    IMPORT_C static void   SetData(   TUint aGpio, TUint8 aSet );
    IMPORT_C static void   ClearData( TUint aGpio, TUint8 aClear );
    
    /// Data direction methods
    IMPORT_C static TUint8 DataDirection(       TUint aGpio );
    IMPORT_C static void   ModifyDataDirection( TUint aGpio, TUint8 aInput, TUint8 aOutput );

    /// Interrupt Sense for detecting edges or levels
    IMPORT_C static TUint8 InterruptSense(       TUint aGpio );
    IMPORT_C static void   ModifyInterruptSense( TUint aGpio, TUint8 aLevels, TUint8 aEdges );

    /// Interrupt both edges when sense is edges
    IMPORT_C static TUint8 InterruptBothEdges(       TUint aGpio );
    IMPORT_C static void   ModifyInterruptBothEdges( TUint aGpio, TUint8 aEdges, TUint8 aEvent );

    /// Interrupt event rising falling edges, high low levels
    IMPORT_C static TUint8 InterruptEvent(       TUint aGpio );
    IMPORT_C static void   ModifyInterruptEvent( TUint aGpio, TUint8 aHigh, TUint8 aLow );

    /// Interrupt mask
    IMPORT_C static TUint8 InterruptMask(       TUint aGpio );
    IMPORT_C static void   ModifyInterruptMask( TUint aGpio, TUint8 aSet, TUint8 aClear );

    /// Interrupt raw status
    IMPORT_C static TUint8 InterruptRawStatus( TUint aGpio );

    /// Interrupt masked status
    IMPORT_C static TUint8 InterruptMaskedStatus( TUint aGpio );

    /// Interrupt clear
    IMPORT_C static void ClearInterrupt( TUint aGpio, TUint8 aData );

    /// Mode control select
    IMPORT_C static TUint8 ModeControl(    TUint aGpio );
    IMPORT_C static void   SetModeControl( TUint aGpio, TUint8 aData );



    /// Note that constants for the specific pins on the GPIO are not provided
    /// as the assignment will vary from hardware to hardware.

    };

#endif