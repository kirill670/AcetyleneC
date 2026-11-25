// V32SIB.H
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __V32SIB_H__
#define __V32SIB_H__

#if defined(_DEBUG)
//#define __DEBUG_INT__ 1
//#define __DEBUG_RAW__ 1
//#define __DEBUG_SMOOTH__ 1
#define __DEBUG_CONFIDENCE__ 1
#define __DEBUG_VOLTAGE__ 1
#define __DEBUG_CONTINUOUS__ 1
#define __DEBUG_ADJUST__ 1
#define __DEBUG_STATUS__ 1
#define __DEBUG_SWITCH_ON__ 1
#define __DEBUG_CHANGE_BATTERY__ 1
#endif


class TSIB
	{
public:
	IMPORT_C static void Initialise();
	IMPORT_C static void WriteMCDR0(TUint aValue);
	IMPORT_C static void WriteMCDR1(TUint aValue);
	IMPORT_C static void WriteMCDR2(TUint aValue);
	IMPORT_C static void WriteMCCR(TUint aValue);
	IMPORT_C static void WriteMCSR(TUint aValue);
	IMPORT_C static TUint ReadMCDR0();
	IMPORT_C static TUint ReadMCDR1();
	IMPORT_C static TUint ReadMCDR2();
	IMPORT_C static TUint ReadMCSR();
	IMPORT_C static TUint ReadMCCR();
	};

struct DigitiserResults
	{
	TInt					yValue;
	TInt					xValue;
	TBool					penDown;
	};

#if 0										// MAC!

class TDigitiserUCB1200;
class TouchScreenInterrupt : public TInterrupt, public DPowerHandler
	{
	friend class TDigitiserUCB1200;
public:
	TouchScreenInterrupt();
	// pure virtual in class TInterrupt
	IMPORT_C virtual void	Service();
	// Repeat timer handler
	static TInt				RepeatComplete(TAny* aPtr);
	// the dfc handler
	static TInt				DfcDespatch(TAny* aPtr);

private:	// from DPowerHandler
	TInt DoPowerOn();
	void DoPowerStandby();
	void DoPowerRestart();
	void DoPowerEmergencyStandby();

private:
	TMilliSecondCallBack	*iRepeatTimerCallBack;
	TDfc					iTouchScreenDfc;
	TDigitiserUCB1200*		iDigitiser;
	TBool					iTouchScreenDfcPending;
	static const TInt KRepeatTimeInMs;
	};

#endif										// /MAC!

//MAC! const TInt TouchScreenInterrupt::KRepeatTimeInMs	= 10;

#if 0										// MAC!

class TDigitiserUCB1200 : public TXYInput
	{
	friend class TouchScreenInterrupt;
public:
	TDigitiserUCB1200();
	virtual ~TDigitiserUCB1200();

	// pure virtual in class TXYInput
	virtual void Init3();
    virtual void CausedSwitchOn();
	virtual TInt SetCalibration(const TDigitizerCalibration& aCalibration);
    virtual void SwitchOn();

private:
	void PointerDown(DigitiserResults& aResults);
	void PointerMove(DigitiserResults& aResults);
	void PointerUp(DigitiserResults& aResults);

	// utilities
	TInt DigitiserToScreen(const TPoint &aDigitiserPoint,TPoint &aScreenPoint);

	void GetResults(DigitiserResults& aResults);
	void ResetTouchISR();
	void ClearTouchISR();

	TouchScreenInterrupt	iTouchScreenInt;
	void					Process();
	DigitiserResults		iSentResults;
	DigitiserResults		iLastResults;
	TInt					iLastCalib;

	enum TSwitchOnSequence
		{
		ESwitchOnNormal,
		ESwitchOnPen
		}					iSwitchOnState;
	};

#endif										// /MAC!

class TUCB1200
	{
public:
	IMPORT_C static void DataRegisterWrite(TInt aReg, TInt aValue);
	IMPORT_C static TInt DataRegisterRead(TInt aReg);
	};


// Audio Sample Rate Divisor
#define bwMCCR_ASD 7
#define bsMCCR_ASD 0
#define bmMCCR_ASD BIT_MASK(MCCR_ASD)

// Telecom Sample Rate Divisor
#define bwMCCR_TSD 7
#define bsMCCR_TSD 8
#define bmMCCR_TSD BIT_MASK(MCCR_TSD)

// SIB Enable
#define bwMCCR_MCE 1
#define bsMCCR_MCE 16		
#define bmMCCR_MCE BIT_MASK(MCCR_MCE)

// External Clock Select
#define bwMCCR_ECS 1
#define bsMCCR_ECS 17	
#define bmMCCR_ECS	 BIT_MASK(MCCR_ECS)

// A/D Data Sampling Mode
#define bwMCCR_ADM 1
#define bsMCCR_ADM 18	
#define bmMCCR_ADM	 BIT_MASK(MCCR_ADM)

// Pin multiplexor control
#define bwMCCR_PMC 1
#define bsMCCR_PMC 26
#define bmMCCR_PMC BIT_MASK(MCCR_PMC)

// Audio control register A
#define bwAUDA_DIV	7
#define bsAUDA_DIV	0
#define bmAUDA_DIV	BIT_MASK(AUDA_DIV)

#define bwAUDA_GAIN	5
#define bsAUDA_GAIN	7
#define bmAUDA_GAIN	BIT_MASK(AUDA_GAIN)

// Telecom control register A
#define bwTELA_DIV	7
#define bsTELA_DIV	0
#define bmTELA_DIV	BIT_MASK(TELA_DIV)

#define bwTELA_LOOP	1
#define bsTELA_LOOP	7
#define bmTELA_LOOP	BIT_MASK(TELA_LOOP)

// MODE register
#define bwDYN_VFLAG_ENA	1
#define bsDYN_VFLAG_ENA	12
#define bmDYN_VFLAG_ENA	BIT_MASK(DYN_VFLAG_ENA)

// IO Direction register
#define bwIO_DIR	10
#define bsIO_DIR	0
#define bmIO_DIR	BIT_MASK(IO_DIR)

#define bwSIB_ZERO	1
#define bsSIB_ZERO	15
#define bmSIB_ZERO	BIT_MASK(SIB_ZERO)

// Status register
// Read/write bits are "sticky"; write 1 to clear them
#define bmMCSR_ATS (1 << 0)		// Audio Tx Service Request (read only)
#define bmMCSR_ARS (1 << 1)		// Audio Rx Service Request (read only)
#define bmMCSR_TTS (1 << 2)		// Telecom Tx Service Request (read only)
#define bmMCSR_TRS (1 << 3)		// Telecom Rx Service Request (read only)
#define bmMCSR_ATU (1 << 4)		// Audio Tx Underrun (rw)
#define bmMCSR_ARO (1 << 5)		// Audio Rx Overrun (rw)
#define bmMCSR_TTU (1 << 6)		// Telecom Tx Underrun (rw)
#define bmMCSR_TRO (1 << 7)		// Telecom Rx Overrun (rw)
#define bmMCSR_ANF (1 << 8)		// Audio Tx FIFO not full (read only)
#define bmMCSR_ANE (1 << 9)		// Audio Rx FIFO not empty (read only)
#define bmMCSR_TNF (1 << 10)	// Telecom Tx FIFO not full (read only)
#define bmMCSR_TNE (1 << 11)	// Telecom Rx FIFO not empty (read only)
#define bmMCSR_CWC (1 << 12)	// Codec Write Completed (read only)
#define bmMCSR_CRC (1 << 13)	// Codec Read Completed (read only)
#define bmMCSR_ACE (1 << 14)	// Audio Codec Enabled (read only)
#define bmMCSR_TCE (1 << 15)	// Telecom Codec Enabled (read only)

// Data Register 2	16-bit data
#define bwMCDR2_DATA 16
#define bsMCDR2_DATA 0
#define bmMCDR2_DATA BIT_MASK(MCDR2_DATA)

// 0 for read, 1 for write
#define bwMCDR2_rW 1
#define bsMCDR2_rW 16
#define bmMCDR2_rW BIT_MASK(MCDR2_rW)

// Register Address 0-16
#define bwMCDR2_ADDRESS 4
#define bsMCDR2_ADDRESS 17
#define bmMCDR2_ADDRESS BIT_MASK(MCDR2_ADDRESS)

// Bit patterns for the UCB1200 registers
typedef enum
{
	UCB_IO 			= 0,	// I/O data
	UCB_IODIR		= 1,	// I/O directions and SIB_ZERO
	UCB_RIS			= 2,	// Rising edge interrupts
	UCB_FAL			= 3,	// Falling edge interrupts
	UCB_INT			= 4,	// Interrupt clear/status
	UCB_TCRA		= 5,	// Telecom control register A
	UCB_TCRB		= 6,	// Telecom control register B
	UCB_ACRA		= 7,	// Audio control register A
	UCB_ACRB		= 8,	// Audio control register B
	UCB_TSCR		= 9,	// Touch screen control register
	UCB_ADCCR		= 10,	// ADC control register
	UCB_ADCDR		= 11,	// ADC data register
	UCB_ID			= 12,	// ID register
	UCB_MODE		= 13,	// MODE register
	UCB_RESERVED    = 14,   // RESERVED register
	UCB_NULL        = 15    // returns all 1's
} tUCB_Register;


#endif

