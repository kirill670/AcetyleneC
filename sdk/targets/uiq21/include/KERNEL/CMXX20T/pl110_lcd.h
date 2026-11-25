// PL110_LCD.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// This file contains the class definition for the LCD prime cell 
// described by the ARM technical reference document PL110.
//

#ifndef __PL110_LCD_H__
#define __PL110_LCD_H__


#include "a32integratorLM.h"

class TPL110_LCD
    {
public:
    /// Register addresses
    static const TUint KHwLCDTiming0    = TIntegratorLM::KLM_LCD + 0x0000;
    static const TUint KHwLCDTiming1    = TIntegratorLM::KLM_LCD + 0x0004;
    static const TUint KHwLCDTiming2    = TIntegratorLM::KLM_LCD + 0x0008;
    static const TUint KHwLCDTiming3    = TIntegratorLM::KLM_LCD + 0x000C;
    static const TUint KHwLCDUPBase     = TIntegratorLM::KLM_LCD + 0x0010;
    static const TUint KHwLCDLPBase     = TIntegratorLM::KLM_LCD + 0x0014;
    static const TUint KHwLCDIntrEnable = TIntegratorLM::KLM_LCD + 0x0018;
    static const TUint KHwLCDControl    = TIntegratorLM::KLM_LCD + 0x001C;
    static const TUint KHwLCDStatus     = TIntegratorLM::KLM_LCD + 0x0020;
    static const TUint KHwLCDInterrupt  = TIntegratorLM::KLM_LCD + 0x0024;
    static const TUint KHwLCDUPCurrent  = TIntegratorLM::KLM_LCD + 0x0028;
    static const TUint KHwLCDLPCurrent  = TIntegratorLM::KLM_LCD + 0x002C;
    static const TUint KHwLCDPalBase    = TIntegratorLM::KLM_LCD + 0x0200;

    /// Constants for use in registers
    static const TUint KTiming0Value     = 0x2040FC9C;
    static const TUint KTiming1Value     = 0x080565DF;
    static const TUint KTiming2Value     = 0x067F1800;
    static const TUint KTiming3Value     = 0x00000000;
    static const TUint KUpperFrameBuffer = 0xC2000000;
    static const TUint KLowerFrameBuffer = 0x00000000;
    static const TUint KLCDNoFlags       = 0x00000000;    
    static const TUint KCtrlLcdEnable    = 0x00000001;
    static const TUint KCtrlLcd1Bpp      = 0x00000000;
    static const TUint KCtrlLcd2Bpp      = 0x00000002;
    static const TUint KCtrlLcd4Bpp      = 0x00000004;
    static const TUint KCtrlLcd8Bpp      = 0x00000006;
    static const TUint KCtrlLcd16Bpp     = 0x00000008;
    static const TUint KCtrlTFT          = 0x00000020;
    static const TUint KCtrlLcdPower     = 0x00000800;
    static const TUint KCtrlBackPorch    = 0x00001000;    

    /// Read / write LCD Timing0 register
    IMPORT_C static TUint LCDTiming0();
    IMPORT_C static void  SetLCDTiming0(    TUint aData );
    IMPORT_C static void  ModifyLCDTiming0( TUint aSetData, TUint aClearData );

    /// Read / write LCD Timing1 register
    IMPORT_C static TUint LCDTiming1();
    IMPORT_C static void  SetLCDTiming1(    TUint aData );
    IMPORT_C static void  ModifyLCDTiming1( TUint aSetData, TUint aClearData );

    /// Read / write LCD Timing2 register
    IMPORT_C static TUint LCDTiming2();
    IMPORT_C static void  SetLCDTiming2(    TUint aData );
    IMPORT_C static void  ModifyLCDTiming2( TUint aSetData, TUint aClearData );

    /// Read / write LCD Timing3 register
    IMPORT_C static TUint LCDTiming3();
    IMPORT_C static void  SetLCDTiming3(    TUint aData );
    IMPORT_C static void  ModifyLCDTiming3( TUint aSetData, TUint aClearData );

    /// Read / write LCD Upper and Lower Panel Base address register
    IMPORT_C static TUint LCDUPBase();
    IMPORT_C static TUint LCDLPBase();
    IMPORT_C static void  SetLCDUPBase( TUint aData );
    IMPORT_C static void  SetLCDLPBase( TUint aData );

    /// Read / write LCD Interrupt enable register
    IMPORT_C static TUint LCDIntrEnable();
    IMPORT_C static void  SetLCDIntrEnable(    TUint aData );
    IMPORT_C static void  ModifyLCDIntrEnable( TUint aSetData, TUint aClearData );
    
    /// Read / write LCD control register
    IMPORT_C static TUint LCDControl();
    IMPORT_C static void  SetLCDControl(    TUint aData );
    IMPORT_C static void  ModifyLCDControl( TUint aSetData, TUint aClearData );

    /// Read / write LCD raw interrupt status register
    IMPORT_C static TUint LCDStatus();
    IMPORT_C static void  SetLCDStatus(    TUint aData );
    IMPORT_C static void  ModifyLCDStatus( TUint aSetData, TUint aClearData );

    /// Read final masked interrupt status register 
    IMPORT_C static TUint LCDInterrupt();

    /// Read LCD upper panel current address value
    IMPORT_C static TUint LCDUPCurrent();

    /// Read LCD lower panel current address value
    IMPORT_C static TUint LCDLPCurrent();

    /// Read / Write LCD palette entry
    IMPORT_C static TUint LCDPaletteEntry(    TUint aIndex );
    IMPORT_C static void  SetLCDPaletteEntry( TUint aIndex, TUint aValue );

    };

#endif
