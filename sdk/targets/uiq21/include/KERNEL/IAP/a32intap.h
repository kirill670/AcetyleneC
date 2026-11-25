// A32INTEGRATORAP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// This file is part of the IntegratorAP Base port
//
// This declares the ASSP access class (TIntegratorAP), which is
// used to protect the code from direct access to hardware addresses
//
// TIntegratorAP provides various functions through which the hardware
// is accessed. This also allows the variant layer to link to the
// kernel and use TIntegratorAP for hardware access.
//

#ifndef __A32INTAP_H__
#define __A32INTAP_H__
#include <e32std.h>
#include <k32std.h>


/**
 * CLASS : TRtcClock
 *
 * This class provides the implementation of a real time clock for the 
 * Integrator board.  Since the Integrator RTC only has a granularity of one 
 * second the clock is simulated in software, driven by the system tick.  The
 * RTC hardware is used for restoring the time after a power down.
 *
 * The class has six public methods, which hide the implementation from the 
 * users and a further three private methods which are used to talk to the 
 * actual RTC hardware (through the ASSP class).
 *
 * The class has one private member that is used to store the time.  This is 
 * used to return the time in all cases except the call to get the stored RTC 
 * value from the hardware.
 *
 * IMPLEMENTATION NOTES
 *
 * When writing to the hardware or reading from it, the class uses the TTime
 * representing the year 2000 as a datum.  Thus writes to the hardware have
 * the year 2000 subtracted from them, whilst reads from it have the datum 
 * added.
 *
 * In order to allow the RTC hardware to be loaded with a date that is prior 
 * to the year 2000 a Hardware offset is provided.  Dates prior to the year 
 * 2000 will appear as negative numbers of seconds to be written to the 
 * hardware.  Since the hardware is an unsigned counter this negative number 
 * needs to be made positive.  This is achieved by adding the hardware offset
 * value to the provided seconds before writing to the hardware, and 
 * subtracting the hardware offset from the counter value when reading the 
 * hardware.
 *
 * The current value of the hardware offset is 2^31, (half the possible max 
 * value of the counter ) which gives our RTC the ability to count about 68 
 * years either side of the year 2000.
 * 
 * REMEMBER to ensure that the system tick service routine calls TickTheRtc 
 * and that it is incremented by a value matching the system tick period.
 *
 */

class TRtcClock
    {
public:
    /// Initialise the RTC with no interrupts, and the value of time supplied
    TInt InitialiseRtcWithTime( TTime aTime );

    /// Get the time from the RTC
    TTime CurrentTime() const;

    /// Set the RTC to the time provided
    TInt SetCurrentTime( TTime aTime );

    /// Tick the clock
    void TickTheRtc();

    /// Get the current time in seconds since 2000
    TInt CurrentTimeInSecondsSince2000( TTimeIntervalSeconds &aSeconds );

    /// Return the stored RTC value from the hardware
    TTime StoredRtcValue() const;

private:
    /// The time held by the RTC class.
    TTime iTime;

    /// Get the value from the RTC which is in seconds
    static TInt ReadRtcHardwareSeconds();
   
    /// Write a value to the RTC which is in seconds
    static void WriteRtcHardwareSeconds( TInt aSeconds );
    static void WriteRtcMatchHardwareSeconds( TInt aSeconds );
    };








/**
 * Each interrupt must have a name by which other code refers to it.
 * These were taken from my original KA_PIC.CPP file.
 */

_LIT8( KSoftwareInt     , "Software"         );
_LIT8( KUartInt0        , "Uart0"            );
_LIT8( KUartInt1        , "Uart1"            );
_LIT8( KKeyboardInt     , "Keyboard"         );
_LIT8( KMouseInt        , "Mouse"            );
_LIT8( KTimerInt0       , "Timer0"           );
_LIT8( KTimerInt1       , "Timer1"           );
_LIT8( KTimerInt2       , "Timer2"           );
_LIT8( KRealTimeClockInt, "RealTimeClock"    );
_LIT8( KLogicModule0    , "LogicModule0"     );
_LIT8( KLogicModule1    , "LogicModule1"     );
_LIT8( KLogicModule2    , "LogicModule2"     );
_LIT8( KLogicModule3    , "LogicModule3"     );
_LIT8( KPciBusInt0      , "PciBus0"          );
_LIT8( KPciBusInt1      , "PciBus1"          );
_LIT8( KPciBusInt2      , "PciBus2"          );
_LIT8( KPciBusInt3      , "PciBus3"          );
_LIT8( KPciBridgeInt    , "PciBridge"        );
_LIT8( KDegInt          , "AuxPciDeg"        );
_LIT8( KEnumInt         , "AuxPciEnum"       );
_LIT8( KPciLocaBusInt   , "PciLocalBusFault" );
_LIT8( KApcInt          , "ExternalAutoPC"   );
_LIT8( KCMSoftwareInt   , "CoreSoftware"     );
_LIT8( KCMDebugCommRx   , "CoreDebugCommRx"  );
_LIT8( KCMDebugCommTx   , "CoreDebugCommTx"  );


    // Timers can run in one of these modes defined below.
    enum TTimerMode
		{
		ETimerModeIdle,
		ETimerModeFreeRunning
		};

    // Timers can have one of these pre-scale values.
    enum TTimerPreScale
        {
        ETimerPreScaleNone,
        ETimerPreScaleDiv16,
        ETimerPreScaleDiv256,
        ETimerPreScaleUndefined
        };


/**
 * CLASS: TIntegratorAP
 *
 * This is the ASSP class for the IntegratorAP port.  It is based on 
 * information from the following documentation (available from the ARM 
 * website)
 *
 * Integrator/AP User Guide
 * Integrator/CM720T User Guide
 *
 * ARM PrimeCell Technical Reference Manuals
 *   PS2 Keyboard/Mouse Interface (PL050)
 *   UART (PL010)
 *   RTC (PL030)
 *   Color LDC Controller (PL110)
 *   Multimedia Card Interface (PL180)
 *
 * 
 * It is organised by block of functionality, with constants first and 
 * methods after these.
 *
 */
class TIntegratorAP
	{
public:

    // The one and only instance of the RTC clock.
    static TRtcClock           theRtc;

public:
    /**
     * Initialisation of ASSP class
     *
     */
	static void Init3();



    /** 
     * Utility functions
     * 
     * These methods are used by all the other methods to actually access
     * the registers on the hardware.  There are methods for accessing
     * 32 bit, 16 bit and 8 bit registers
     *
     * The parameter names have the following meaning:
     * aAddr      - register address
     * aValue     - value to be written
     * aClearMask - bit mask for bits to be cleared in register
     * aSetMask   - bit mask for bits to be set in register
     */

    /// Read register
	inline static TUint  Register32( TUint aAddr )
        {
        return (*(volatile TUint32 *)(aAddr)); 
        };
	
    inline static TUint  Register16( TUint aAddr )
        {
        return (*(volatile TUint16 *)(aAddr)); 
        };

	inline static TUint8 Register8( TUint aAddr )
        {
        return (*(volatile TUint8 *)(aAddr)); 
        };

    /// Write value into register
	inline static void   SetRegister32( TUint aValue, TUint aAddr )
        { 
        *(volatile TUint32 *)(aAddr) = aValue; 
        };

	inline static void   SetRegister16( TUint aValue, TUint aAddr )
        { 
        *(volatile TUint16 *)(aAddr) = aValue; 
        };

	inline static void   SetRegister8( TUint8 aValue, TUint aAddr )
        { 
        *(volatile TUint8 *)(aAddr) = aValue; 
        };

    /// Modify register
	inline static void   ModifyRegister32( TUint aClearMask, TUint aSetMask, TUint aAddr )
        {
        TInt irqLevel=Hal::DisableIrqsToLevel2();
	    SetRegister32(((Register32(aAddr)&(~aClearMask)) | aSetMask ),   aAddr);
        Hal::RestoreIrqs(irqLevel);
        };


	inline static void   ModifyRegister16( TUint aClearMask, TUint aSetMask, TUint aAddr )
        {
        TInt irqLevel=Hal::DisableIrqsToLevel2();
	    SetRegister16(((Register16(aAddr)&(~aClearMask)) | aSetMask ),   aAddr);
        Hal::RestoreIrqs(irqLevel);
        };

	inline static void   ModifyRegister8( TUint8 aClearMask, TUint8 aSetMask, TUint aAddr )
        {
        TInt irqLevel=Hal::DisableIrqsToLevel2();
	    SetRegister8(((Register8(aAddr)&(~aClearMask)) | aSetMask ),   aAddr);
        Hal::RestoreIrqs(irqLevel);
        };




    /**
     * Base Addresses for the various components
     *
     */
    static const TUint KHwBasePeripherals  = 0x58000000;
    static const TUint KHwBaseCoreSysCtrl  = KHwBasePeripherals;
    static const TUint KHwBaseSysCtrl      = KHwBasePeripherals + 0x1000;
    static const TUint KHwBaseEBI          = KHwBasePeripherals + 0x2000;
    static const TUint KHwBaseCounterTimer = KHwBasePeripherals + 0x3000;
    static const TUint KHwBaseInterrupts   = KHwBasePeripherals + 0x4000;
    static const TUint KHwBaseRtc          = KHwBasePeripherals + 0x5000;
    static const TUint KHwBaseSerial0      = KHwBasePeripherals + 0x6000;
    static const TUint KHwBaseSerial1      = KHwBasePeripherals + 0x7000;
    static const TUint KHwBaseKeyboard     = KHwBasePeripherals + 0x8000;
    static const TUint KHwBaseMouse        = KHwBasePeripherals + 0x9000;
    static const TUint KHwBaseLEDs         = KHwBasePeripherals + 0xA000;
    static const TUint KHwBaseGpio         = KHwBasePeripherals + 0xB000;
    static const TUint KHwBaseColourLCD    = KHwBasePeripherals; // TO DO:

    /**
     * System Control Registers
     *
     * There is a system control register on the core module itself and 
     * another on the motherboard.
     */

    /// Core System Control Registers (Integrator/CM720T page 4.7)
    static const TUint KHwRoCoreID         = KHwBaseCoreSysCtrl + 0x000;
    static const TUint KHwRoCoreProc       = KHwBaseCoreSysCtrl + 0x004;
    static const TUint KHwRwCoreOsc        = KHwBaseCoreSysCtrl + 0x008;
    static const TUint KHwRwCoreCtrl       = KHwBaseCoreSysCtrl + 0x00C;
    static const TUint KHwRoCoreStat       = KHwBaseCoreSysCtrl + 0x010;
    static const TUint KHwRwCoreLock       = KHwBaseCoreSysCtrl + 0x014;
    static const TUint KHwRwCoreSDRam      = KHwBaseCoreSysCtrl + 0x020;
    static const TUint KHwRoCoreIrqStat    = KHwBaseCoreSysCtrl + 0x040;
    static const TUint KHwRoCoreIrqRStat   = KHwBaseCoreSysCtrl + 0x044;
    static const TUint KHwRwCoreIrqEnSet   = KHwBaseCoreSysCtrl + 0x048;
    static const TUint KHwWoCoreIrqEnClr   = KHwBaseCoreSysCtrl + 0x04C;
    static const TUint KHwRwCoreSoftIntSet = KHwBaseCoreSysCtrl + 0x050;
    static const TUint KHwWoCoreSoftIntClr = KHwBaseCoreSysCtrl + 0x054;
    static const TUint KHwRoCoreFiqStat    = KHwBaseCoreSysCtrl + 0x060;
    static const TUint KHwRoCoreFiqRStat   = KHwBaseCoreSysCtrl + 0x064;
    static const TUint KHwRwCoreFiqEnSet   = KHwBaseCoreSysCtrl + 0x068;
    static const TUint KHwWoCoreFiqEnClr   = KHwBaseCoreSysCtrl + 0x06C;
    static const TUint KHwRoCoreSPD        = KHwBaseCoreSysCtrl + 0x100;

    /// System Control Registers (Integrator/AP page 4.7)
    static const TUint KHwRoId             = KHwBaseSysCtrl + 0x00;
    static const TUint KHwRwOsc            = KHwBaseSysCtrl + 0x04;
    static const TUint KHwRwCtrls          = KHwBaseSysCtrl + 0x08;
    static const TUint KHwRwCtrlc          = KHwBaseSysCtrl + 0x0C;
    static const TUint KHwRoDec            = KHwBaseSysCtrl + 0x10;
    static const TUint KHwRwArb            = KHwBaseSysCtrl + 0x14;
    static const TUint KHwRwPci            = KHwBaseSysCtrl + 0x18;
    static const TUint KHwRwLock           = KHwBaseSysCtrl + 0x1C;
    static const TUint KHwRoLbfAddr        = KHwBaseSysCtrl + 0x20;
    static const TUint KHwRoLbdCode        = KHwBaseSysCtrl + 0x24;


    /// Accessor methods for the system controller registers.
    IMPORT_C static TUint SystemControlSet();
    IMPORT_C static TUint SystemControlClear();
    IMPORT_C static void  SetSystemControlSet( TUint aData );
    IMPORT_C static void  SetSystemControlClear( TUint aData );






    /**
     * Timers
     *
     * There are three timers on the integrator.  They can run in either
     * periodic mode, where when they reach zero they restart with the value
     * in the LOAD register, or free running where they start from the LOAD
     * register value and stop when they hit zero.
     *
     * Timer 0 is clocked by the system bus whilst the other two timers
     * are clocked by a 24MHz input.
     */
    
    /// Base addresses of the three timers on the Integrator
    static const TUint KHwBaseTimer0       = KHwBaseCounterTimer + 0x0000;
    static const TUint KHwBaseTimer1       = KHwBaseCounterTimer + 0x0100;
    static const TUint KHwBaseTimer2       = KHwBaseCounterTimer + 0x0200;

    /// Timer 0 register addresses
    static const TUint KHwTimer0Load        = KHwBaseTimer0 + 0x00;
    static const TUint KHwTimer0Value       = KHwBaseTimer0 + 0x04;
    static const TUint KHwTimer0Ctrl        = KHwBaseTimer0 + 0x08;
    static const TUint KHwTimer0Clear       = KHwBaseTimer0 + 0x0C;

    /// Timer 1 register addresses
    static const TUint KHwTimer1Load        = KHwBaseTimer1 + 0x00;
    static const TUint KHwTimer1Value       = KHwBaseTimer1 + 0x04;
    static const TUint KHwTimer1Ctrl        = KHwBaseTimer1 + 0x08;
    static const TUint KHwTimer1Clear       = KHwBaseTimer1 + 0x0C;

    /// Timer 2 register addresses
    static const TUint KHwTimer2Load        = KHwBaseTimer2 + 0x00; 
    static const TUint KHwTimer2Value       = KHwBaseTimer2 + 0x04; 
    static const TUint KHwTimer2Ctrl        = KHwBaseTimer2 + 0x08; 
    static const TUint KHwTimer2Clear       = KHwBaseTimer2 + 0x0C; 

    /// Timer control register constants
    static const TUint KHwRwTimerEnabledFlag    = 0x80;
    static const TUint KHwRwTimerModeFlag       = 0x40;
    static const TUint KHwRwTimerPreScaleFlags  = 0x0C;
    static const TUint KHwRwPreScaleNone        = 0x00;
    static const TUint KHwRwPreScaleDiv16       = 0x04;
    static const TUint KHwRwPreScaleDiv256      = 0x08;
    static const TUint KHwRwPreScaleUndefined   = 0x0C;
    static const TUint KHwRwPeriodic            = 0x40;

    /// Set the starting count value for a timer
    IMPORT_C static void           SetTimer0Load( TUint aValue );
    IMPORT_C static void           SetTimer1Load( TUint aValue );
    IMPORT_C static void           SetTimer2Load( TUint aValue );

    /// Read the load register (starting count value)
    IMPORT_C static TUint          Timer0Load();
    IMPORT_C static TUint          Timer1Load();
    IMPORT_C static TUint          Timer2Load();

    /// Read the actual timer value
    IMPORT_C static TUint          Timer0Value();
    IMPORT_C static TUint          Timer1Value();
    IMPORT_C static TUint          Timer2Value();

    /// Clear the timer interrupt
    IMPORT_C static void           ClearTimer0();
    IMPORT_C static void           ClearTimer1();
    IMPORT_C static void           ClearTimer2();

    /// Enquire as to whether the timer is enabled
    IMPORT_C static TBool          Timer0Enabled();
    IMPORT_C static TBool          Timer1Enabled();
    IMPORT_C static TBool          Timer2Enabled();

    /// Enable the timer (start it running)
    IMPORT_C static void           EnableTimer0();
    IMPORT_C static void           EnableTimer1();
    IMPORT_C static void           EnableTimer2();

    /// Disable the timer (stop it running)
    IMPORT_C static void           DisableTimer0();
    IMPORT_C static void           DisableTimer1();
    IMPORT_C static void           DisableTimer2();

    /// Find out what mode the timer is running in
    IMPORT_C static TTimerMode     Timer0Mode();
    IMPORT_C static TTimerMode     Timer1Mode();
    IMPORT_C static TTimerMode     Timer2Mode();

    /// Set the timer mode (periodic or free running)
    IMPORT_C static void           SetTimer0Mode( TTimerMode aValue );
    IMPORT_C static void           SetTimer1Mode( TTimerMode aValue );
    IMPORT_C static void           SetTimer2Mode( TTimerMode aValue );

    /// Find out the timer prescale value
    IMPORT_C static TTimerPreScale Timer0PreScale();
    IMPORT_C static TTimerPreScale Timer1PreScale();
    IMPORT_C static TTimerPreScale Timer2PreScale();

    /// Set the timer prescale value
    IMPORT_C static void           SetTimer0PreScale( TTimerPreScale aValue );
    IMPORT_C static void           SetTimer1PreScale( TTimerPreScale aValue );
    IMPORT_C static void           SetTimer2PreScale( TTimerPreScale aValue );













    /**
     * Interrupts
     *
     * Constants are provided for all four sets of interrupts (from four
     * core modules) but we'll only be using those for core module 0.
     */

    /// IRQ Interrupt register addresses
    static const TUint KHwRoIrq0Stat       = KHwBaseInterrupts + 0x00;
    static const TUint KHwRoIrq0RawStat    = KHwBaseInterrupts + 0x04;
    static const TUint KHwRwIrq0EnableSet  = KHwBaseInterrupts + 0x08;
    static const TUint KHwWoIrq0EnableClr  = KHwBaseInterrupts + 0x0C;
    static const TUint KHwRoIrq1Stat       = KHwBaseInterrupts + 0x40;
    static const TUint KHwRoIrq1RawStat    = KHwBaseInterrupts + 0x44;
    static const TUint KHwRwIrq1EnableSet  = KHwBaseInterrupts + 0x48;
    static const TUint KHwWoIrq1EnableClr  = KHwBaseInterrupts + 0x4C;
    static const TUint KHwRoIrq2Stat       = KHwBaseInterrupts + 0x80;
    static const TUint KHwRoIrq2RawStat    = KHwBaseInterrupts + 0x84;
    static const TUint KHwRwIrq2EnableSet  = KHwBaseInterrupts + 0x88;
    static const TUint KHwWoIrq2EnableClr  = KHwBaseInterrupts + 0x8C;
    static const TUint KHwRoIrq3Stat       = KHwBaseInterrupts + 0xC0;
    static const TUint KHwRoIrq3RawStat    = KHwBaseInterrupts + 0xC4;
    static const TUint KHwRwIrq3EnableSet  = KHwBaseInterrupts + 0xC8;
    static const TUint KHwWoIrq3EnableClr  = KHwBaseInterrupts + 0xCC;

    /// FIQ Interrupt register addresses
    static const TUint KHwRoFiq0Stat       = KHwBaseInterrupts + 0x20;
    static const TUint KHwRoFiq0RawStat    = KHwBaseInterrupts + 0x24;
    static const TUint KHwRwFiq0EnableSet  = KHwBaseInterrupts + 0x28;
    static const TUint KHwWoFiq0EnableClr  = KHwBaseInterrupts + 0x2C;
    static const TUint KHwRoFiq1Stat       = KHwBaseInterrupts + 0x60;
    static const TUint KHwRoFiq1RawStat    = KHwBaseInterrupts + 0x64;
    static const TUint KHwRwFiq1EnableSet  = KHwBaseInterrupts + 0x68;
    static const TUint KHwWoFiq1EnableClr  = KHwBaseInterrupts + 0x6C;
    static const TUint KHwRoFiq2Stat       = KHwBaseInterrupts + 0xA0;
    static const TUint KHwRoFiq2RawStat    = KHwBaseInterrupts + 0xA4;
    static const TUint KHwRwFiq2EnableSet  = KHwBaseInterrupts + 0xA8;
    static const TUint KHwWoFiq2EnableClr  = KHwBaseInterrupts + 0xAC;
    static const TUint KHwRoFiq3Stat       = KHwBaseInterrupts + 0xE0;
    static const TUint KHwRoFiq3RawStat    = KHwBaseInterrupts + 0xE4;
    static const TUint KHwRwFiq3EnableSet  = KHwBaseInterrupts + 0xE8;
    static const TUint KHwWoFiq3EnableClr  = KHwBaseInterrupts + 0xEC;

    /// Software interrupt register addresses
    static const TUint KHwRwSoftInt0Set    = KHwBaseInterrupts + 0x10;
    static const TUint KHwRwSoftInt1Set    = KHwBaseInterrupts + 0x50;
    static const TUint KHwRwSoftInt2Set    = KHwBaseInterrupts + 0x90;
    static const TUint KHwRwSoftInt3Set    = KHwBaseInterrupts + 0xD0;
    static const TUint KHwWoSoftInt0Clear  = KHwBaseInterrupts + 0x14;
    static const TUint KHwWoSoftInt1Clear  = KHwBaseInterrupts + 0x54;
    static const TUint KHwWoSoftInt2Clear  = KHwBaseInterrupts + 0x94;
    static const TUint KHwWoSoftInt3Clear  = KHwBaseInterrupts + 0xD4;

    /// IRQ and FIQ register bit assignments
    static const TUint KHwIntSoftInt       = 0x000001;
    static const TUint KHwIntUartInt0      = 0x000002;
    static const TUint KHwIntUartInt1      = 0x000004;
    static const TUint KHwIntKeyboard      = 0x000008;
    static const TUint KHwIntMouse         = 0x000010;
    static const TUint KHwIntTimer0        = 0x000020;
    static const TUint KHwIntTimer1        = 0x000040;
    static const TUint KHwIntTimer2        = 0x000080;
    static const TUint KHwIntRealTimeClock = 0x000100;
    static const TUint KHwIntExpInt0       = 0x000200;
    static const TUint KHwIntExpInt1       = 0x000400;
    static const TUint KHwIntExpInt2       = 0x000800;
    static const TUint KHwIntExpInt3       = 0x001000;
    static const TUint KHwIntPciInt0       = 0x002000;
    static const TUint KHwIntPciInt1       = 0x004000;
    static const TUint KHwIntPciInt2       = 0x008000;
    static const TUint KHwIntPciInt3       = 0x010000;
    static const TUint KHwIntLInt          = 0x020000;
    static const TUint KHwIntDegInt        = 0x040000;
    static const TUint KHwIntEnumInt       = 0x080000;
    static const TUint KHwIntPcilbInt      = 0x100000;
    static const TUint KHwIntApcInt        = 0x200000;
    static const TUint KHwInterruptsMask   = 0x3FFFFF;

    /// Core Module Interrupt Related static constants 
    static const TUint KHwInterruptCommTx    = 0x04;  // Debug comm tx int
    static const TUint KHwInterruptCommRx    = 0x02;  // Debug comm rx int
    static const TUint KHwInterruptSoft      = 0x01;  // Software interrupt
    static const TUint KHwCoreInterruptsMask = 0x07;

    /// Read the interrupt status register on the core
    IMPORT_C static TUint CoreIrqStatus();
    IMPORT_C static TUint CoreFiqStatus();

    /// Read the raw interrupt status register on the core
    IMPORT_C static TUint CoreIrqRawStatus();
    IMPORT_C static TUint CoreFiqRawStatus();

    /// Enable the specified core interrupts
    IMPORT_C static void  EnableCoreIrq( TUint aInts );
    IMPORT_C static void  EnableCoreFiq( TUint aInts );

    /// Find out which core interrupts are enabled
    IMPORT_C static TUint CoreIrqEnable();
    IMPORT_C static TUint CoreFiqEnable();

    /// Disable the specified core interrupts
    IMPORT_C static void  DisableCoreIrq( TUint aInts );
    IMPORT_C static void  DisableCoreFiq( TUint aInts );

    /// Core software interrupt enable, query and clear
    IMPORT_C static void  EnableCoreSoftInt();
    IMPORT_C static TBool CoreSoftInt();
    IMPORT_C static void  ClearCoreSoftInt();

    /// Read motherboard interrupt status and raw status
    IMPORT_C static TUint Irq0Status();
    IMPORT_C static TUint Fiq0Status();
    IMPORT_C static TUint Irq0RawStatus();
    IMPORT_C static TUint Fiq0RawStatus();

    /// Enable specified motherboard interrupts
    IMPORT_C static void  EnableIrq0( TUint aInts );
    IMPORT_C static void  EnableFiq0( TUint aInts );

    /// Find out which motherboard interrupts are enabled
    IMPORT_C static TUint Irq0Enable();
    IMPORT_C static TUint Fiq0Enable();

    /// Disable specified motherboard interrupts
    IMPORT_C static void  DisableIrq0( TUint aInts );
    IMPORT_C static void  DisableFiq0( TUint aInts );











    /**
     * UARTS - PrimeCell
     *
     * The Integrator motherboard contains two UARTs, numbered here 0 and 1.
     *
     */
    
    /// Uart Register descriptions for UARTs 0 and 1.
    static const TUint KHwUartDr    = 0x00; // Data Register
    static const TUint KHwUartRsr   = 0x04; // Receive Status Register
    static const TUint KHwUartEcr   = 0x04; // Error Clear Register
    static const TUint KHwUartLcrh  = 0x08; // Line control register, hi byte
    static const TUint KHwUartLcrm  = 0x0C; // Line control register, mid byte
    static const TUint KHwUartLcrl  = 0x10; // Line control register, low byte
    static const TUint KHwUartCr    = 0x14; // Control Register
    static const TUint KHwUartFr    = 0x18; // Flag Register
    static const TUint KHwUartIir   = 0x1C; // Interrupt Id Register
    static const TUint KHwUartIcr   = 0x1C; // Interrupt Clear Register


    /// Receive status register bit flags
    /// These are the various bits that can be set in the receive register 
    /// when a character has been read from the data register
    enum TUartReceiveStatus
        {
        EUartErrNone    = 0x00,
        ERxFramingError = 0x01,
        ERxParityError  = 0x02,
        ERxBreakError   = 0x04,
        ERxOverrunError = 0x08,
        ERxUndefined    = 0xF0
        };

    /// TUartBaud is the baud rate settings that are to be written to the LCRM
    /// and LCRL.  Support only provided for rates of 1200 upto and including
    /// 230400 baud.
    /// The enumerate value is used when writing to the Uart registers.  The
    /// LSB is written to the Lcrl and the MSB is written to the Lcrm
    enum TUartBaud	
		{
		EBaud1200   = 0x02FF,
		EBaud2400   = 0x017F,
		EBaud9600   = 0x005F,
        EBaud19200  = 0x002F,
		EBaud38400  = 0x0017,
		EBaud57600  = 0x000F,
        EBaud76800  = 0x000B,
		EBaud115200 = 0x0007,
		EBaud230400 = 0x0003
		};

    /// TUartParity defines the parity settings for the UART  
    /// The enumerate value is used when writing to the Uart registers.  The
    /// LSB is written to the SET mask whilst the MSB is written to the CLEAR
    /// mask when modifying the register
    enum TUartParity
		{
		EParityOdd  = 0x0402,
		EParityNone = 0x0600,
		EParityEven = 0x0006
		};

    ///TUartDataBits sets 5, 6, 7 or 8 data bits using the LCRH bits 5 and 6.
    /// The enumerate value is used when writing to the Uart registers.  The
    /// LSB is written to the SET mask whilst the MSB is written to the CLEAR
    /// mask when modifying the register
    enum TUartDataBits
		{
		EDataBits5 = 0x6000,
		EDataBits6 = 0x4020,
		EDataBits7 = 0x2040,
		EDataBits8 = 0x0060
		};

    /// TUartStopBits sets or clears the two stop bits flag in the LCRH.
	enum TUartStopBits
		{
        EClearTwoStopBits,
        ESetTwoStopBits
		};

    /// TUartFifoSetting either enables or disables the Fifo for the Uart
    enum TUartFifoSetting
        {
        EIntFifoDisable,
        EIntFifoEnable
        };

    /// Uart Control Register (CR) bit descriptions
    /// These are used to enable or disable various types of interrupt that
    /// the Uart will generate
    enum TUartCrBits
        {
		ECrLoopBackEnable		= 0x80,
        ECrRxTimeoutInterrupt	= 0x40,
        ECrTxInterrupt			= 0x20,
        ECrRxInterrupt			= 0x10,
		ECrModemStatusInterrupt	= 0x08,
		ECrSIRLowPowerMode		= 0x04,
		ECrSIREnable			= 0x02,
        ECrEnableInterrupts		= 0x01
        };

    /// Uart status flags register bit descriptions
    /// These flags identify the status of the uart
    enum TUartStatusFlags
        {
        ETransmitFifoEmpty   = 0x80,
        EReceiveFifoFull     = 0x40,
        ETransmitFifoFull    = 0x20,
        EReceiveFifoEmpty    = 0x10,
        EUartBusy            = 0x08,
        EDataCarrierDetect   = 0x04,
        EDataSetReady        = 0x02,
        EClearToSend         = 0x01
        };

    /// Uart Interrupt Identification register bit descriptions
    /// When the IIR indicates that an interrupt has occured, these bits will
    /// show what type of interrupt occurred.
    enum TUartInterruptIdentification
        {
        ERxTimeoutInterrupt = 0x08,
        ETxInterrupt        = 0x04,
        ERxInterrupt        = 0x02,
        EModemInterrupt     = 0x01
        };


    /// Bit flags for the system control registers that hold modem
    /// control flags
    enum TUartModemFlags
        {
        EUart0Rts         = 0x80,
        EUart0Dtr         = 0x40,
        EUart1Rts         = 0x20,
        EUart1Dtr         = 0x10
        };


    /// Methods for reading and writing characters
    IMPORT_C static TUint8 UartData(    const TUint UartBase );
    IMPORT_C static void   SetUartData( const TUint UartBase, TUint8 aChar );

    /// Methods for reading and clearing the received status register to be 
    /// done after a character has been read
    IMPORT_C static TUint8 UartReceiveStatus(      const TUint UartBase );
    IMPORT_C static void   UartClearReceiveStatus( const TUint UartBase );

    /// Methods for setting the baud, parity, data and stop bits.  For
    /// enabling or disabling the fifo
	IMPORT_C static void   SetUartBaud(     const TUint UartBase, TUartBaud        aBaud );
	IMPORT_C static void   SetUartParity(   const TUint UartBase, TUartParity      aParity );
	IMPORT_C static void   SetUartDataBits( const TUint UartBase, TUartDataBits    aBits );
	IMPORT_C static void   SetUartStopBits( const TUint UartBase, TUartStopBits    aBits );
    IMPORT_C static void   SetUartFifo(     const TUint UartBase, TUartFifoSetting aSetting );

    /// Methods for checking the status of the fifo and see whether the Uart
    /// is transmitting or not.
	IMPORT_C static TBool  UartRxFifoEmpty(  const TUint UartBase );
	IMPORT_C static TBool  UartTxFifoFull(   const TUint UartBase );
	IMPORT_C static TBool  UartTxInProgress( const TUint UartBase );

    /// Methods for reading and writing to the control register
    IMPORT_C static void   SetUartControlRegister(   const TUint UartBase, TUint8 aCombinedControlFlags );
    IMPORT_C static void   ClearUartControlRegister( const TUint UartBase, TUint8 aCombinedControlFlags );
    IMPORT_C static TUint8 UartControlRegister( const TUint UartBase );

    /// Methods for reading the flag register
    IMPORT_C static TUint8 UartFlagRegister( const TUint UartBase );

    /// Methods for checking interrupts and clearing them
    IMPORT_C static TUint8 UartReceivedInterrupts( const TUint UartBase );
    IMPORT_C static void   ClearUartReceivedInterrupts( const TUint UartBase );










    /**
     * Real Time Clock - PrimeCell
     *
     */

    /// RTC registers
    static const TUint KHwRoRtcDr      = KHwBaseRtc + 0x00;    // Data 
    static const TUint KHwRwRtcMr      = KHwBaseRtc + 0x04;    // Match 
    static const TUint KHwRoRtcStat    = KHwBaseRtc + 0x08;    // Int status
    static const TUint KHwWoRtcEoi     = KHwBaseRtc + 0x08;    // Int clear
    static const TUint KHwRwRtcLr      = KHwBaseRtc + 0x0C;    // Load
    static const TUint KHwRwRtcCr      = KHwBaseRtc + 0x10;    // Control

    // RTC interrupt masking constants
    static const TUint KHwRtcIntAssert = 0x01;   // Bit 0 of RTC_STAT register
    static const TUint KHwRtcIntEnable = 0x01;   // Bit 0 of RTC_CR register

    /// Read RTC data, match, status, load and interrupt registers
	IMPORT_C static TUint RtcData();
    IMPORT_C static TUint RtcMatch();
    IMPORT_C static TBool RtcStat();
    IMPORT_C static TUint RtcLoad();
    IMPORT_C static TBool RtcMatchInt();

    /// Set match register value (for raising an interrupt)
    IMPORT_C static void  SetRtcMatch( TUint aCount );

    /// Clear an RTC interrupt
    IMPORT_C static void  SetRtcEoi();

    /// Load RTC with a value (this can take upto 1 second)
    IMPORT_C static void  SetRtcLr( TUint aCount );

    /// Enable RTC interrupts
    IMPORT_C static void  EnableRtcMatchInt( TBool aValue );













    /**
     * Keyboard and Mouse Controller - PrimeCell
     *
     * We're only interested in the keyboard controller.
     *
     */

    /// Keyboard register definitions
    static const TUint KHwKeyboardControl   = KHwBaseKeyboard + 0x00;
    static const TUint KHwKeyboardStatus    = KHwBaseKeyboard + 0x04;
    static const TUint KHwKeyboardDataRead  = KHwBaseKeyboard + 0x08;
    static const TUint KHwKeyboardDataWrite = KHwBaseKeyboard + 0x08;
    static const TUint KHwKeyboardClockDiv  = KHwBaseKeyboard + 0x0C;
    static const TUint KHwKeyboardInterrupt = KHwBaseKeyboard + 0x10;

    /// Control register constants and masks
    static const TUint KHwKeyForceClockLow  = 0x01;
    static const TUint KHwKeyForceDataLow   = 0x02;
    static const TUint KHwKeyEnableKMI      = 0x04;
    static const TUint KHwKeyEnableTxInt    = 0x08;
    static const TUint KHwKeyEnableRxInt    = 0x10;
    static const TUint KHwKeyType           = 0x20;
    static const TUint KHwKeyCtrkReserved   = 0xC0; // top two bits reserved

    /// Status register constants and masks
    static const TUint KHwKeyDataIn         = 0x01;
    static const TUint KHwKeyClockIn        = 0x02;
    static const TUint KHwKeyRxParity       = 0x04;
    static const TUint KHwKeyRxBusy         = 0x08;
    static const TUint KHwKeyRxFull         = 0x10;
    static const TUint KHwKeyTxBusy         = 0x20;
    static const TUint KHwKeyTxEmpty        = 0x40;
    static const TUint KHwKeyStatReserved   = 0x80;

    /// Clock divisor values
    static const TUint KHwKeyClkDivByOne    = 0x00;
    static const TUint KHwKeyClkDivByTwo    = 0x01;
    static const TUint KHwKeyClkDivByThree  = 0x02;
    static const TUint KHwKeyClkDivByFour   = 0x03;
    static const TUint KHwKeyClkDivByFive   = 0x04;
    static const TUint KHwKeyClkDivBySix    = 0x05;
    static const TUint KHwKeyClkDivBySeven  = 0x06;
    static const TUint KHwKeyClkDivReserved = 0xF8;

    /// Interrupt identification constants and masks
    static const TUint KHwKeyRxInterrupt    = 0x01;
    static const TUint KHwKeyTxInterrupt    = 0x02;
    static const TUint KHwKeyIntReserved    = 0xFC;

    /// Read the keyboard control register
    IMPORT_C static TUint KeyboardControl();

    /// Set the specified keyboard control register bits
    IMPORT_C static void  SetKeyboardControl( TUint aData );

    /// Clear the  specified keyboard control register bits
    IMPORT_C static void  ClearKeyboardControl( TUint aData );

    /// Read the keyboard status register
    IMPORT_C static TUint KeyboardStatus();

    /// Read the keyboard data (key presses or control data from keyboard)
    IMPORT_C static TUint KeyboardData();

    /// Send data to the keyboard
    IMPORT_C static void  SetKeyboardData( TUint aData );

    /// Read the keyboard clock divisor rate
    IMPORT_C static TUint KeyboardClockDiv();

    /// Set the keyboard clock divisor rate
    IMPORT_C static void  SetKeyboardClockDiv( TUint aData );

    /// Read the keyboard interrupt register (Received or sent)
    IMPORT_C static TUint KeyboardInterrupt();

    










    /**
     * Colour LCD Controller - PrimeCell
     *
     */

    /// Register addresses
    static const TUint KHwLCDTiming0    = KHwBaseColourLCD + 0x0000;
    static const TUint KHwLCDTiming1    = KHwBaseColourLCD + 0x0004;
    static const TUint KHwLCDTiming2    = KHwBaseColourLCD + 0x0008;
    static const TUint KHwLCDTiming3    = KHwBaseColourLCD + 0x000C;
    static const TUint KHwLCDUPBase     = KHwBaseColourLCD + 0x0010;
    static const TUint KHwLCDLPBase     = KHwBaseColourLCD + 0x0014;
    static const TUint KHwLCDIntrEnable = KHwBaseColourLCD + 0x0018;
    static const TUint KHwLCDControl    = KHwBaseColourLCD + 0x001C;
    static const TUint KHwLCDStatus     = KHwBaseColourLCD + 0x0020;
    static const TUint KHwLCDInterrupt  = KHwBaseColourLCD + 0x0024;
    static const TUint KHwLCDUPCurrent  = KHwBaseColourLCD + 0x0028;
    static const TUint KHwLCDLPCurrent  = KHwBaseColourLCD + 0x002C;
    static const TUint KHwLCDPalBase    = KHwBaseColourLCD + 0x0200;

    static const TUint KLCDNoFlags      = 0x0000;    

    // Constants for the LCD panel pixel parameters register
    static const TUint KLCDWaterMark        = 0x00010000;
    static const TUint KLCDLDMATestMode     = 0x00004000;
    static const TUint KLCDVComp            = 0x00003000;
    static const TUint KLCDPowerEnable      = 0x00000800;
    static const TUint KLCDBigEndianByte    = 0x00000400;
    static const TUint KLCDBigEndianByteOrd = 0x00000200;
    static const TUint KLCDBlueGreenRed     = 0x00000100;
    static const TUint KLCDDualPanel        = 0x00000080;
    static const TUint KLCDEightBitMono     = 0x00000040;
    static const TUint KLCDTFT              = 0x00000020;
    static const TUint KLCDSTNMono          = 0x00000010;
    static const TUint KLCDBitsPerPixel     = 0x0000000E;
    static const TUint KLCDControllerEnable = 0x00000001;


    /// Read / write LCD Timing0 register
    IMPORT_C static TUint LCDTiming0();
    IMPORT_C static void  SetLCDTiming0( TUint aData );
    IMPORT_C static void  ModifyLCDTiming0( TUint aSetData, TUint aClearData );

    /// Read / write LCD Timing1 register
    IMPORT_C static TUint LCDTiming1();
    IMPORT_C static void  SetLCDTiming1( TUint aData );
    IMPORT_C static void  ModifyLCDTiming1( TUint aSetData, TUint aClearData );

    /// Read / write LCD Timing2 register
    IMPORT_C static TUint LCDTiming2();
    IMPORT_C static void  SetLCDTiming2( TUint aData );
    IMPORT_C static void  ModifyLCDTiming2( TUint aSetData, TUint aClearData );

    /// Read / write LCD Timing3 register
    IMPORT_C static TUint LCDTiming3();
    IMPORT_C static void  SetLCDTiming3( TUint aData );
    IMPORT_C static void  ModifyLCDTiming3( TUint aSetData, TUint aClearData );

    /// Read / write LCD Upper and Lower Panel Base address register
    IMPORT_C static TUint LCDUPBase();
    IMPORT_C static TUint LCDLPBase();
    IMPORT_C static void  SetLCDUPBase( TUint aData );
    IMPORT_C static void  SetLCDLPBase( TUint aData );

    /// Read / write LCD Interrupt enable register
    IMPORT_C static TUint LCDIntrEnable();
    IMPORT_C static void  SetLCDIntrEnable( TUint aData );
    IMPORT_C static void  ModifyLCDIntrEnable( TUint aSetData, TUint aClearData );
    
    /// Read / write LCD panel pixel parameters register
    IMPORT_C static TUint LCDControl();
    IMPORT_C static void  SetLCDControl( TUint aData );
    IMPORT_C static void  ModifyLCDControl( TUint aSetData, TUint aClearData );
    
    /// Read / write LCD raw interrupt status register
    IMPORT_C static TUint LCDStatus();
    IMPORT_C static void  SetLCDStatus( TUint aData );
    IMPORT_C static void  ModifyLCDStatus( TUint aSetData, TUint aClearData );

    /// Read final masked interrupt status register 
    IMPORT_C static TUint LCDInterrupt();

    /// Read LCD upper panel current address value
    IMPORT_C static TUint LCDUPCurrent();

    /// Read LCD lower panel current address value
    IMPORT_C static TUint LCDLPCurrent();

    /// Read / Write LCD palette entry
    IMPORT_C static TUint LCDPaletteEntry( TUint aIndex );
    IMPORT_C static void  SetLCDPaletteEntry( TUint aIndex, TUint aValue );
















    /**
     * General Purpose IO
     *
     * The following text describes the use of these four registers.  It is 
     * taken from the Integrator/AP User Guide, section 4.7.
     *
     * The GPIO DATASET location is used to set individual GPIO output bits as
     * follows :
     *   1 = SET the associated GPIO output bit
     *   0 = leave the associated GPIO output bit unchanged.
     *
     * The GPIO DATAIN location is used to read the current state of the GPIO
     * intput bits from this location.
     *
     * The GPIO DATACLR location is used to clear individual GPIO output 
     * bits as follows :
     *   1 = CLEAR the associated GPIO output bit.
     *   0 = leave the associated GPIO output bit unchanged.
     *
     * The GPIO DIRN location is used to set the direction of each GPIO pin,
     * as follows :
     *   1 = pin is an OUTPUT
     *   0 = pin is an INPUT (default)
     *
     */

    /// GPIO Register Definitions
    static const TUint KHwGpioDataset      = KHwBaseGpio + 0x00;
    static const TUint KHwGpioDataIn       = KHwBaseGpio + 0x00;
    static const TUint KHwGpioDataClr      = KHwBaseGpio + 0x04;
    static const TUint KHwGpioDataOut      = KHwBaseGpio + 0x04;
    static const TUint KHwGpioDataDir      = KHwBaseGpio + 0x08;

    /// There are currently no methods defined for the GPIO registers


    /**
     * Fast IR 
     *
     * Currently not implemented in port but included to enable building
     *
     */

	enum FirControlFlags
		{
		KFirCtrlEnable = 0x1,
		KFirCtrlRxEnable = 0x2,
		KFirCtrlTxEnable = 0x3,
		KFirCtrlRxError = 0x40,
		KFirCtrlTxError = 0x80
		};
	
	IMPORT_C static void FirEnable();
	IMPORT_C static void FirDisable();
	IMPORT_C static void FirRxEnable();
	IMPORT_C static void FirTxEnable();
	IMPORT_C static void FirRxDisable();
	IMPORT_C static void FirTxDisable();
	IMPORT_C static TUint8 FirData();
	IMPORT_C static void SetFirData( TUint8 aByte );
	IMPORT_C static TUint FirInterruptFlags();
	IMPORT_C static TBool FirRxFailed();
	IMPORT_C static TBool FirTxFailed();


    /** 
     * Battery and Power stuff
     *
     * Not implemented but included to enable building
     *
     */

	enum TPowerFlags
		{
		KPowerFlagBatteryChanged,
		KPowerFlagExternalPresent,
		KPowerFlagMainGood,
		KPowerFlagBackupGood
		};

	IMPORT_C static TBool BatteryChanged();
	IMPORT_C static TBool ExternalPowerPresent();
	IMPORT_C static TBool MainBatteryGood();
	IMPORT_C static TBool BackupBatteryGood();
	IMPORT_C static TInt MainBatteryVoltage();
	IMPORT_C static TInt BackupBatteryVoltage();



    /**
     * Digitiser
     *
     * Not implemented but included to enable building
     *
     */

	enum TDigitiserFlags
		{
		KDigitiserFlagPenDown = 0x1,
		KDigitiserFlagXDone = 0x2,
		KDigitiserFlagYDone = 0x4
		};

	enum TDigitiserControl
		{
		KDigitiserControlStartX,
		KDigitiserControlStartY
		};

	IMPORT_C static TBool IsDigitiserPenDown();
	IMPORT_C static void StartDigitiserXConversion();
	IMPORT_C static void StartDigitiserYConversion();
	IMPORT_C static TBool DigitiserXConversionFinished();
	IMPORT_C static TBool DigitiserYConversionFinished();
	IMPORT_C static TInt DigitiserXData();
	IMPORT_C static TInt DigitiserYData();


    /**
     * Direct Memory Access
     *
     * Not implemented but included to enable building
     *
     */

	enum TDmaChannel
		{
		EDmaChannel0,
		EDmaChannel1
		};

	enum { KNumDmaChannels = 2 };

	enum TDmaAction
		{
		EDmaIdle,
		EDmaRunning
		};

	enum TDmaInterruptMode
		{
		EDmaInterruptOff,
		EDmaInterruptOnComplete
		};

	enum TDmaOffsets
		{
		KHwOffsetDmaSource	= 0x00,
		KHwOffsetDmaDest	= 0x04,
		KHwOffsetDmaSrcInc	= 0x08,
		KHwOffsetDmaDestInc	= 0x0C,
		KHwOffsetDmaSize	= 0x10,
		KHwOffsetDmaCount	= 0x18,
		KHwOffsetDmaMode	= 0x1C
		};

	enum TDmaFlags
		{
		KDmaFlagRunning = 0x1,
		KDmaFlagInterrupt = 0x2,
		KDmaFlagError = 0x4
		};


	/**
     * Misc bits and bobs
     *
     */
    IMPORT_C static void EnterIdle();
	IMPORT_C static void Sleep();
	IMPORT_C static void ResetWatchdog();
	IMPORT_C static TMachineStartupType StartupReason();

    
    };









#endif
