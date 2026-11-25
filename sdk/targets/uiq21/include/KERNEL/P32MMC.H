//
//	P32MMC.H
//	(C) Copyright Symbian Ltd 1999
//

//
//	Generic MMC controller types and standard classes for MMC manipulation
//  This controller follows MMC spec V2.1
//

#if !defined(__P32MMC_H__)
#define __P32MMC_H__

#include <k32std.h>
#include <p32std.h>

#if !defined(__WINS__)
#include <m32std.h>
#endif

//		Forward type declarations

class TMMC;
class TCID;
class TCSD;
class TRCA;
class TDSR;
class TMMCStatus;
class TMMCArgument;
class TMMCCard;
class TMMCCommandDesc;
class TMMCBusConfig;
class TMMCStackConfig;
class TMMCRCAPool;
class TMMCSessRing;
class TMMCStateMachine;
class DMMCController;
class DMMCSession;
class DMMCStack;
class TMMCMediaChange;


//		Typedefs

typedef TUint32 TMMCErr;

//		MMC Enums and inline functions

	enum TMMCCommandEnum
		{
		ECmdGoIdleState			=0,
		ECmdSendOpCond			=1,
		ECmdAllSendCID			=2,
		ECmdSetRelativeAddr		=3,
		ECmdSetDSR				=4,
		ECmd5					=5,
		ECmd6					=6,
		ECmdSelectCard			=7,
		ECmd8					=8,
		ECmdSendCSD				=9,
		ECmdSendCID				=10,
		ECmdReadDatUntilStop	=11,
		ECmdStopTransmission	=12,
		ECmdSendStatus			=13,
		ECmd14					=14,
		ECmdGoInactiveState		=15,
		ECmdSetBlockLen			=16,
		ECmdReadSingleBlock		=17,
		ECmdReadMultipleBlock	=18,
		ECmd19					=19,
		ECmdWriteDatUntilStop	=20,
		ECmd21					=21,
		ECmd22					=22,
		ECmd23					=23,
		ECmdWriteBlock			=24,
		ECmdWriteMultipleBlock	=25,
		ECmdProgramCID			=26,
		ECmdProgramCSD			=27,
		ECmdSetWriteProt		=28,
		ECmdClearWriteProt		=29,
		ECmdSendWriteProt		=30,
		ECmd31					=31,
		ECmdTagSectorStart		=32,
		ECmdTagSectorEnd		=33,
		ECmdUntagSector			=34,
		ECmdTagEraseGroupStart	=35,
		ECmdTagEraseGroupEnd	=36,
		ECmdUntagEraseGroup		=37,
		ECmdErase				=38,
		ECmdFastIO				=39,
		ECmdGoIRQState			=40,
		ECmd41					=41,
		ECmdLockUnlock			=42,
		ECmd43					=43,
		ECmd44					=44,
		ECmd45					=45,
		ECmd46					=46,
		ECmd47					=47,
		ECmd48					=48,
		ECmd49					=49,
		ECmd50					=50,
		ECmd51					=51,
		ECmd52					=52,
		ECmd53					=53,
		ECmd54					=54,
		ECmdAppCmd				=55,
		ECmdGenCmd				=56,
		ECmd57					=57,
		ECmd58					=58,
		ECmd59					=59,
		ECmd60					=60,
		ECmd61					=61,
		ECmd62					=62,
		ECmd63					=63
		};

	enum TMMCCommandTypeEnum
		{
		ECmdTypeUK,				// UnKnown command type
		ECmdTypeBC,				// Broadcast Command
		ECmdTypeBCR,			// Broadcast Command with Response
		ECmdTypeAC,				// Addressed Command
		ECmdTypeACS,			// Addressed Command to a Selected card
		ECmdTypeADTCS			// Addressed Data Transfer Command to a Selected card
		};

	enum TMMCResponseTypeEnum
		{
		ERespTypeNone,
		ERespTypeUnknown,
		ERespTypeR1,			// 32 bits Status
		ERespTypeR1B,			// 32 bits Status with possible busy signal
		ERespTypeR2,			// 128 bits CID or CSD register
		ERespTypeR3,			// 32 bits OCR register
		ERespTypeR4,			// 32 bits Fast I/O
		ERespTypeR5,			// 32 bits IRQ
		ERespTypeR6
		};

	enum TMMCMediaTypeEnum
		{
		EMultiMediaROM,
		EMultiMediaFlash,
		EMultiMediaIO,
		EMultiMediaOther,
		EMultiMediaNotSupported
		};

	enum TMMCSessionTypeEnum
		{
		ECIMNakedSession		=0,
		ECIMUpdateAcq			=1,
		ECIMInitStack			=2,
		ECIMCheckStack			=3,
		ECIMSetupCard			=4,
		ECIMReadBlock			=5,
		ECIMWriteBlock			=6,
		ECIMReadMBlock			=7,
		ECIMWriteMBlock			=8,
		ECIMEraseSector			=9,
		ECIMEraseGroup			=10,
		ECIMReadIO				=11,
		ECIMWriteIO				=12,
		ECIMLockUnlock			=13,
		ECIMLockStack			=14
		};
	const TUint KMMCMaxSessionTypeNumber = 15;
	const TUint KMMCMinCustomSession = 1024;

	const TUint KMMCCmdDirDirBitPosition=	KBit0;			//fixed - dont change it
	const TUint KMMCCmdDirIndBitPosition=	(KBit5-KBit0);	//fixed - dont change it
	const TUint KMMCCmdDirWBitArgument=		KBit5;
	const TUint KMMCCmdDirNegate=			KBit6;
	const TUint KMMCCmdDirWBitDirect=		KBit7;

	enum TMMCCmdDirEnum
		{
		EDirNone = 0,
		EDirRead = KMMCCmdDirWBitDirect,
		EDirWrite = KMMCCmdDirWBitDirect|KMMCCmdDirDirBitPosition,
		EDirWBit0 = KMMCCmdDirWBitArgument + 0,
		EDirRBit0 = (KMMCCmdDirWBitArgument|KMMCCmdDirNegate) + 0
		};

	const TUint8 KMMCLockUnlockErase =		KBit3;			// bits in first byte of
	const TUint8 KMMCLockUnlockLockUnlock =	KBit2;			// CMD42 data block
	const TUint8 KMMCLockUnlockClrPwd =		KBit1;
	const TUint8 KMMCLockUnlockSetPwd =		KBit0;

class TMMC
	{
public:
	static inline TUint32 BigEndian32(const TUint8*);
	static inline void BigEndian4Bytes(TUint8* aPtr, TUint32 aVal);
	};


//		Generic MMC layer constants

const TInt KMaxMMCStacks=1;						// Number of separate MMC buses
const TUint KMaxMMCCardsPerStack=4;				// Limits the number of cards in each stack

const TUint KBroadcastToAllCards=0xFFFFFFFF;

//		MMC Spec related constants

const TUint KMMCMaxResponseLength=16;			// in bytes
const TUint KMMCCIDLength=16;
const TUint KMMCCSDLength=16;
const TUint KMMCBusClockFOD=400;				// Identification clock in kiloherz
const TUint KMMCCommandMask = 63;				// Size of TMMCCommandEnum enumerator

// Command Classes Bit Set
const TUint32 KMMCCmdClassNone=0;
const TUint32 KMMCCmdClassBasic=		  KBit0;
const TUint32 KMMCCmdClassStreamRead=	  KBit1;
const TUint32 KMMCCmdClassBlockRead=	  KBit2;
const TUint32 KMMCCmdClassStreamWrite=	  KBit3;
const TUint32 KMMCCmdClassBlockWrite=	  KBit4;
const TUint32 KMMCCmdClassErase=		  KBit5;
const TUint32 KMMCCmdClassWriteProtection=KBit6;
const TUint32 KMMCCmdClassLockCard=		  KBit7;
const TUint32 KMMCCmdClassApplication=	  KBit8;
const TUint32 KMMCCmdClassIOMode=		  KBit9;
const TUint32 KMMCCmdClassReserved10=	  KBit10;
const TUint32 KMMCCmdClassReserved11=	  KBit11;

//		Specific MMC implementation constants

const TUint KMaxMMCMachineStackDepth=10;		// TMMCStateMachine stack depth
const TUint KMaxMMCCommandStackDepth=3;			// Session TMMCCommandDesc stack depth
const TUint KMMCIdleCommandsAtRestart=2;		// Number of CMD0s to be issued at initialisation
const TUint KMMCMaxJobsInStackWorkSet=8;		// Number of sessions simultaneously served
const TUint KMMCPollGapInMilliseconds=40;
const TUint KMMCMaxPollAttempts=5;				// 40*5 = 200ms
const TUint KMMCRetryGapInMilliseconds=10;
const TUint KMMCMaxTimeOutRetries=1;
const TUint KMMCMaxCRCRetries=1;
const TUint16 KMMCMaxUnlockRetries=4;
const TUint KMMCMaxGlobalRetries=1;
const TUint16 KMMCMaxOpCondBusyTimeout=100;		// 10*100 = 1000ms

// DMMCStack Modes Bit Set
const TUint32 KMMCModeEnableClientConfig =	KBit0;	// Merge with session iConfig
const TUint32 KMMCModeEnableTimeOutRetry =	KBit1;	// Auto retry on response time-outs
const TUint32 KMMCModeTimeOutRetryGap =		KBit2;	// Force timer delay between retries
const TUint32 KMMCModeEnableCRCRetry =		KBit3;	// Command or response CRC errors
const TUint32 KMMCModeCRCRetryGap =			KBit4;
const TUint32 KMMCModeDataCRCRetry =		KBit5;	// Repeat data transaction from the last valid position
const TUint32 KMMCModeEnableUnlockRetry =	KBit6;	// Resend CMD42 for unreliable cards
const TUint32 KMMCModeEnablePreemption =	KBit7;	// Allow sessions to share the MMC bus
const TUint32 KMMCModePreemptOnBusy =		KBit8;	// Release bus control if busy
const TUint32 KMMCModePreemptOnRetry =		KBit9;	// Release bus control before timeout/crc retries
const TUint32 KMMCModePreemptInGaps =		KBit10;	// Preempt whenever gap timer is invoked
const TUint32 KMMCModeEnqueIfLocked =		KBit11;	// Enque session if DMMCStack is locked
const TUint32 KMMCModeCardControlled =		KBit12;	// Use Session CardP to get RCAs etc.
const TUint32 KMMCModeCompleteInStackDFC =	KBit13;	// Run DMMCStack in DFC when completing
const TUint32 KMMCModeEnableBusyPoll =		KBit14;	// Enables mechanism recovering from busy timeouts
const TUint32 KMMCModeBusyPollGap =			KBit15;
const TUint32 KMMCModeEnableRetries =		KBit16;	// This mode removed disables all retries/polls
const TUint32 KMMCModeMask =				KBit17 - KBit0;

// The following modes are effective for MasterConfig only
const TUint32 KMMCModeClientPollAttempts =			KBit20;
const TUint32 KMMCModeClientTimeOutRetries =		KBit21;
const TUint32 KMMCModeClientCRCRetries =			KBit22;
const TUint32 KMMCModeClientUnlockRetries =			KBit23;
const TUint32 KMMCModeClientBusClock =				KBit24;
const TUint32 KMMCModeClientClockIn =				KBit25;
const TUint32 KMMCModeClientClockOut =				KBit26;
const TUint32 KMMCModeClientResponseTimeOut =		KBit27;
const TUint32 KMMCModeClientDataTimeOut =			KBit28;
const TUint32 KMMCModeClientBusyTimeOut =			KBit29;
const TUint32 KMMCModeClientiOpCondBusyTimeout =	KBit30;
const TUint32 KMMCModeClientMask =	KBit31 - KBit20;

// The following modes cannot be enabled by a client if disabled in MasterConfig
const TUint32 KMMCModeMasterOverrides=
								KMMCModeEnableClientConfig	|
								KMMCModeEnablePreemption	|
								KMMCModeEnqueIfLocked		|
								KMMCModeClientMask;

// The following modes are always effective, even if the ClientConfig is disabled
const TUint32 KMMCModeClientOverrides=
								KMMCModeEnableClientConfig	|
								KMMCModeCardControlled;

// The default MasterConfig modes
const TUint32 KMMCModeDefault=	KMMCModeEnableClientConfig	|
								KMMCModeEnableRetries		|
								KMMCModeEnableTimeOutRetry	|
								KMMCModeTimeOutRetryGap		|
								KMMCModeEnableCRCRetry		|
								KMMCModeCRCRetryGap			|
								KMMCModeDataCRCRetry		|
								KMMCModeEnableUnlockRetry	|
								KMMCModeEnablePreemption	|
								KMMCModePreemptInGaps		|
								KMMCModeEnqueIfLocked		|
								KMMCModeCardControlled		|
								KMMCModeClientMask;


// MMC Error Code Bit Set
const TUint32 KMMCErrNone=0;
const TUint32 KMMCErrResponseTimeOut=KBit0;
const TUint32 KMMCErrDataTimeOut=	 KBit1;
const TUint32 KMMCErrBusyTimeOut=	 KBit2;
const TUint32 KMMCErrBusTimeOut=	 KBit3;
const TUint32 KMMCErrTooManyCards=	 KBit4;
const TUint32 KMMCErrResponseCRC=	 KBit5;
const TUint32 KMMCErrDataCRC=		 KBit6;
const TUint32 KMMCErrCommandCRC=	 KBit7;
const TUint32 KMMCErrStatus=		 KBit8;
const TUint32 KMMCErrNoCard=		 KBit9;
const TUint32 KMMCErrBrokenLock=	 KBit10;
const TUint32 KMMCErrPowerDown=		 KBit11;
const TUint32 KMMCErrAbort=			 KBit12;
const TUint32 KMMCErrStackNotReady=	 KBit13;
const TUint32 KMMCErrNotSupported=	 KBit14;
const TUint32 KMMCErrHardware=		 KBit15;
const TUint32 KMMCErrBusInconsistent=KBit16;
// SM control error codes
const TUint32 KMMCErrBypass=		 KBit17;
const TUint32 KMMCErrInitContext=	 KBit18;
const TUint32 KMMCErrArgument=		 KBit19;
const TUint32 KMMCErrSingleBlock=	 KBit20;
const TUint32 KMMCErrUpdPswd=		 KBit21;
// General error codes
const TUint32 KMMCErrLocked=			KBit22;
const TUint32 KMMCErrNotFound=			KBit23;
const TUint32 KMMCErrAlreadyExists=		KBit24;
const TUint32 KMMCErrGeneral=			KBit25;

const TUint32 KMMCErrAll = (KBit26 - KBit0);
const TUint32 KMMCErrBasic = (KMMCErrAll & ~(
								KMMCErrBypass		|
								KMMCErrUpdPswd		|
								KMMCErrInitContext	|
								KMMCErrArgument		|
								KMMCErrSingleBlock	|
								KMMCErrLocked		|
								KMMCErrNotFound		|
								KMMCErrAlreadyExists|
								KMMCErrGeneral));

// DMMC Stack and Session control bits

// Stack State bits
const TUint32 KMMCStackStateRunning=		KBit0;	// Stack scheduler active
const TUint32 KMMCStackStateWaitingToLock=	KBit1;	//
const TUint32 KMMCStackStateLocked=			KBit2;	//
const TUint32 KMMCStackStateWaitingDFC=		KBit3;
const TUint32 KMMCStackStateInitInProgress=	KBit4;
const TUint32 KMMCStackStateReScheduled=	KBit5;
const TUint32 KMMCStackStateJobChooser=		KBit6;
const TUint32 KMMCStackStateDoDeselect=		KBit7;
const TUint32 KMMCStackStateBusInconsistent=KBit8;
const TUint32 KMMCStackStateInitPending=	KBit9;

// Session Blocking bits definition
const TUint32 KMMCBlockOnASSPFunction=	KBit0;
const TUint32 KMMCBlockOnPollTimer=		KBit1;
const TUint32 KMMCBlockOnRetryTimer=	KBit2;
const TUint32 KMMCBlockOnNoRun=			KBit3;
const TUint32 KMMCBlockOnDoor=			KBit4;
const TUint32 KMMCBlockOnWaitToLock=	KBit5;
const TUint32 KMMCBlockOnCardInUse=		KBit6;
const TUint32 KMMCBlockOnPgmTimer=		KBit7;
const TUint32 KMMCBlockOnAsynchMask =
	KMMCBlockOnASSPFunction | KMMCBlockOnPollTimer | KMMCBlockOnRetryTimer | KMMCBlockOnPgmTimer;

const TUint32 KMMCBlockOnGapTimersMask = KMMCBlockOnPollTimer | KMMCBlockOnRetryTimer | KMMCBlockOnPgmTimer;

// Session State bits definition
const TUint32 KMMCSessStateEngaged=		 KBit0;	// Processed by DMMCStack
const TUint32 KMMCSessStateInProgress=	 KBit1;	// No longer safe to restart
const TUint32 KMMCSessStateCritical=	 KBit2;	// Re-initialise the stack if aborted
const TUint32 KMMCSessStateSafeInGaps=	 KBit3;
const TUint32 KMMCSessStateDoReSchedule= KBit4;
const TUint32 KMMCSessStateDoDFC=		 KBit5;
const TUint32 KMMCSessStateBlockOnDoor=	 KBit6;
const TUint32 KMMCSessStateCardIsGone=	 KBit7;
const TUint32 KMMCSessStateASSPEngaged=	 KBit8;

class TCID
	{
public:
	inline TCID() {}					// Default constructor
	inline TCID(const TUint8*);
	inline TCID& operator=(const TCID&);
	inline TCID& operator=(const TUint8*);
	inline TBool operator==(const TCID&) const;
	inline TBool operator==(const TUint8*) const;
	inline void Copy(TUint8*) const;		// Copies big endian 16 bytes CID
	inline TUint8 At(TUint anIndex) const;	// Byte from CID at anIndex
private:
	TUint8 iData[KMMCCIDLength];		// Big endian 128 bit bitfield representing CID
	};


class TCSD
	{
public:
	inline TCSD() {}					// Default constructor
	inline TCSD(const TUint8*);
	inline TCSD& operator=(const TCSD&);
	inline TCSD& operator=(const TUint8*);
	inline void Copy(TUint8*) const;		// Copies big endian 16 bytes CSD
	inline TUint8 At(TUint anIndex) const;	// Byte from CSD at anIndex
public:
	inline TUint CSDStructure() const;
	inline TUint SpecVers() const;
	inline TUint Reserved120() const;
	inline TUint TAAC() const;
	inline TUint NSAC() const;
	inline TUint TranSpeed() const;
	inline TUint CCC() const;
	inline TUint ReadBlLen() const;
	inline TBool ReadBlPartial() const;
	inline TBool WriteBlkMisalign() const;
	inline TBool ReadBlkMisalign() const;
	inline TBool DSRImp() const;
	inline TUint Reserved74() const;
	inline TUint CSize() const;
	inline TUint VDDRCurrMin() const;
	inline TUint VDDRCurrMax() const;
	inline TUint VDDWCurrMin() const;
	inline TUint VDDWCurrMax() const;
	inline TUint CSizeMult() const;
	inline TUint EraseGrpSize() const;
	inline TUint EraseGrpMult() const;
	inline TUint WPGrpSize() const;
	inline TBool WPGrpEnable() const;
	inline TUint DefaultECC() const;
	inline TUint R2WFactor() const;
	inline TUint WriteBlLen() const;
	inline TBool WriteBlPartial() const;
	inline TUint Reserved16() const;
	inline TBool FileFormatGrp() const;
	inline TBool Copy() const;
	inline TBool PermWriteProtect() const;
	inline TBool TmpWriteProtect() const;
	inline TUint FileFormat() const;
	inline TUint ECC() const;
	inline TUint CRC() const;
public:
	IMPORT_C TUint DeviceSize() const;		// Uses functions above to calculate device capacity
	IMPORT_C TMMCMediaTypeEnum MediaType() const;
	IMPORT_C TUint ReadBlockLength() const;	// Read Block Length in bytes
	IMPORT_C TUint WriteBlockLength() const;// Write Block Length in bytes
	IMPORT_C TUint EraseSectorSize() const;	// Erase sector size (default 512 bytes)
	IMPORT_C TUint EraseGroupSize() const;	// Erase group size (default 16*<sector size> bytes)
	IMPORT_C TUint MinReadCurrentInMilliamps() const;
	IMPORT_C TUint MinWriteCurrentInMilliamps() const;
	IMPORT_C TUint MaxReadCurrentInMilliamps() const;
	IMPORT_C TUint MaxWriteCurrentInMilliamps() const;
	IMPORT_C TUint MaxTranSpeedInKilohertz() const;
public:
	IMPORT_C TUint CSDField(const TUint& aTopBit, const TUint& aBottomBit) const;
	TUint8 iData[KMMCCSDLength];		// Big endian 128 bit bitfield representing CSD
	};


//	32 bit MMC card status field (response R1)

const TUint32 KMMCStatAppCmd=			KBit5;
const TUint32 KMMCStatReadyForData=		KBit8;
const TUint32 KMMCStatCurrentStateMask=	(KBit13-KBit9);
const TUint32 KMMCStatEraseReset=		KBit13;
const TUint32 KMMCStatCardECCDisabled=	KBit14;
const TUint32 KMMCStatWPEraseSkip=		KBit15;
const TUint32 KMMCStatErrCSDOverwrite=	KBit16;
const TUint32 KMMCStatErrOverrun=		KBit17;
const TUint32 KMMCStatErrUnderrun=		KBit18;
const TUint32 KMMCStatErrUnknown=		KBit19;
const TUint32 KMMCStatErrCCError=		KBit20;
const TUint32 KMMCStatErrCardECCFailed=	KBit21;
const TUint32 KMMCStatErrIllegalCommand=KBit22;
const TUint32 KMMCStatErrComCRCError=	KBit23;
const TUint32 KMMCStatErrLockUnlock=	KBit24;
const TUint32 KMMCStatCardIsLocked=		KBit25;
const TUint32 KMMCStatErrWPViolation=	KBit26;
const TUint32 KMMCStatErrEraseParam=	KBit27;
const TUint32 KMMCStatErrEraseSeqError=	KBit28;
const TUint32 KMMCStatErrBlockLenError=	KBit29;
const TUint32 KMMCStatErrAddressError=	KBit30;
const TUint32 KMMCStatErrOutOfRange=	KBit31;

const TUint32 KMMCStatErrorMask=		KMMCStatErrOutOfRange	|
										KMMCStatErrAddressError	|
										KMMCStatErrBlockLenError|
										KMMCStatErrEraseSeqError|
										KMMCStatErrEraseParam	|
										KMMCStatErrWPViolation	|
										KMMCStatErrLockUnlock	|
										KMMCStatErrCardECCFailed|
										KMMCStatErrCCError		|
										KMMCStatErrUnknown		|
										KMMCStatErrUnderrun		|
										KMMCStatErrOverrun		|
										KMMCStatErrCSDOverwrite;


const TUint32 KMMCStatClearByReadMask=	KMMCStatErrOutOfRange	|
										KMMCStatErrAddressError	|
										KMMCStatErrBlockLenError|
										KMMCStatErrEraseSeqError|
										KMMCStatErrEraseParam	|
										KMMCStatErrWPViolation	|
										KMMCStatErrLockUnlock	|
										KMMCStatErrCardECCFailed|
										KMMCStatErrCCError		|
										KMMCStatErrUnknown		|
										KMMCStatErrUnderrun		|
										KMMCStatErrOverrun		|
										KMMCStatErrCSDOverwrite	|
										KMMCStatWPEraseSkip		|
										KMMCStatEraseReset		|
										KMMCStatAppCmd;

enum TMMCCardStateEnum
	{
	ECardStateIdle = 0,
	ECardStateReady =	(1 << 9),
	ECardStateIdent =	(2 << 9),
	ECardStateStby =	(3 << 9),
	ECardStateTran =	(4 << 9),
	ECardStateData =	(5 << 9),
	ECardStateRcv =		(6 << 9),
	ECardStatePrg =		(7 << 9),
	ECardStateDis =		(8 << 9)
	};

class TMMCStatus
	{
public:
	inline TMMCStatus() {}
	inline TMMCStatus(const TUint8*);
	inline TMMCStatus(const TUint32&);
	inline operator TUint32() const;
	inline TUint32 Error() const;
	inline TMMCCardStateEnum State() const;
private:
	TUint32 iData;				//	32 bit bitfield representing status register
	};




const TUint32 KMMCOCRBusy=KBit31; // 32bit MMC OCR (response R3)
#define KMMCAdjustableOpVoltage KMMCOCRBusy // Use same bit to flag ASSP PSU supports voltage adjustment.


class TMMCArgument
	{
public:
	inline TMMCArgument() {}
	inline TMMCArgument(const TUint32&);
	inline TMMCArgument(TRCA);
	inline TMMCArgument(TDSR);
	inline operator TUint32() const;
	inline void SetRCA(TRCA);
private:
	TUint32 iData;				//	32 bit bitfield representing the argument
	};


class TRCA
	{
public:
	inline TRCA() {}
	inline TRCA(TUint16);
	inline TRCA(TInt);
	inline TRCA(TMMCArgument);
	inline operator TUint16() const;
private:
	TUint16	iData;	// 16 bit bitfield representing MultiMedia Card's RCA
	};


class TDSR
	{
public:
	inline TDSR() {}
	inline TDSR(TUint16);
	inline operator TUint16() const;
private:
	TUint16	iData;	// 16 bit bitfield representing MultiMedia Card's DSR
	};


// Card specific information and context
const TUint32 KMMCCardHasPassword=		KBit0;
const TUint32 KMMCCardIsWriteProtected=	KBit1;
const TUint32 KMMCCardMMCFlagMask=		0x0000ffff;

const TUint32 KMMCCardFirstCustomFlag=	KBit16;
const TUint32 KMMCCardCustomFlagMask=	0xffff0000;

class TMMCCard
	{
public:
	TMMCCard();
	inline TBool IsPresent() const;
	IMPORT_C TBool IsReady() const;
	IMPORT_C TBool IsLocked() const;
	inline TMMCMediaTypeEnum MediaType() const;
	inline TUint DeviceSize() const;
	inline const TCID& CID() const;
	inline const TCSD& CSD() const;
	inline TRCA RCA() const;
	inline TBool HasPassword() const;
	inline TBool IsWriteProtected() const;	// Always EFalse in MMC build
	virtual TUint32 PreferredWriteGroupLength() const;
	virtual TInt GetFormatInfo(TLDFormatInfo& aFormatInfo) const;
	virtual TUint32 MinEraseSectorSize() const;
private:
	inline TInt Number() const;
public:
	TInt iIndex;
	TMMCStatus iStatus;				// last card's status
	TUint32 iSetBlockLen;			// current block length set for the card
	TMMCCommandEnum iLastCommand;	// Last Command code issued for the card
	TCID iCID;
	TCSD iCSD;
	TRCA iRCA;
	DMMCSession* iUsingSessionP;	// session which has this card attached
	TUint32 iFlags;
	friend class DMMCStack;
	friend class TMmcCardArray;
	};

class TMmcCardArray
	{
public:
	inline TMmcCardArray(DMMCStack* anOwningStack) {iOwningStack=anOwningStack;}
	virtual TInt AllocCards();
	void InitNewCardScan();
	void AddNewCard(const TUint8* aCID,TRCA* aNewRCA);
	inline TUint NewCardCount();
	inline TInt CardsPresent();
	inline TMMCCard* NewCardP(TUint aNewCardNumber);
	inline TMMCCard* CardP(TUint aCardNumber);
	inline TMMCCard& Card(TUint aCardNumber);
	inline TMMCCard& NewCard(TUint aCardNumber);
	TInt MergeCards(TBool aFirstPass);
	void UpdateAcquisitions(TUint* aMaxClock);
	virtual void DeclareCardAsGone(TUint aCardNumber);
protected:										// initialized by AllocCards()
	void MoveCardAndLockRCA(TMMCCard& aSrc,TMMCCard& aDest,TInt aDestIndex);
	DMMCStack* iOwningStack;
	TInt iCardsPresent;
	TUint iNewCardsCount;
	TMMCCard* iCards[KMaxMMCCardsPerStack];
	TMMCCard* iNewCards[KMaxMMCCardsPerStack];
	};

// MMC Command descriptor

const TUint32 KMMCCmdFlagBytesValid=	KBit0;	// iBytesDone has a valid data
const TUint32 KMMCCmdFlagTransStopped=	KBit1;	// CMD12 has been successfully issued
const TUint32 KMMCCmdFlagStatusReceived=KBit2;	// Raised by ASSP layer, cleared by ExecCommandSM()
const TUint32 KMMCCmdFlagExecTopBusy=	KBit3;	// ExecCommandSM() flag
const TUint32 KMMCCmdFlagExecSelBusy=	KBit4;	// ExecCommandSM() flag

const TUint32 KMMCCmdFlagASSPFlags=	KMMCCmdFlagBytesValid	|
									KMMCCmdFlagTransStopped	|
									KMMCCmdFlagStatusReceived;

class TMMCCommandSpec
	{
public:
	TUint32 iCommandClass;
	TMMCCommandTypeEnum iCommandType;
	TMMCCmdDirEnum iDirection;		// Data transfer direction
	TBool iMultipleBlocks;			// More than one data block to be tranferred
	TBool iUseStopTransmission;		// CMD12 has to be used in the end
	TMMCResponseTypeEnum iResponseType;
	TUint iResponseLength;			// Expected response length (currently 4 or 16 bytes)
	};

class TMMCIdxCommandSpec
	{
public:
	TInt iIdx;
	TMMCCommandSpec iSpec;
	};

class TMMCCommandDesc
	{
public:
	TInt Direction() const;			// returns -1/0/+1 for read/none/write
public:
	TUint32 iFlags;
	TMMCCommandEnum iCommand;		// Command code
	TMMCArgument iArgument;			// Argument to be supplied with the command
	TUint32 iTotalLength;			// Of the data to be tranferred
	TUint8* iDataMemoryP;			// Where the data to be taken from/put to
	TUint32 iBlockLength;			// To be used in data transaction
	TMMCCommandSpec iSpec;			// MMC spec command description
	TUint32 iBytesDone;				// Bytes transferred since the last time the card was selected
	TUint iPollAttempts;			// Retry counters
	TUint iTimeOutRetries;
	TUint iCRCRetries;
	TUint16 iUnlockRetries;
	TUint16 iOpCondBusyTimeout;		// Units of 10mS
	TUint iCustomRetries;
	TUint32 iExecNotHandle;			// error codes to not handle in ExecCommandSM()
	TUint8 iResponse[KMMCMaxResponseLength];	// a big endian response
	};


class TMMCBusConfig
	{
public:
	TUint iBusClock;
	TUint iClockIn;
	TUint iClockOut;
	TUint iResponseTimeOut;
	TUint iDataTimeOut;
	TUint iBusyTimeOut;
	};


class TMMCStackConfig
	{
public:
	inline TMMCStackConfig();
	inline void SetMode(TUint32 aMask);
	inline void RemoveMode(TUint32 aMask);
	inline void UseDefault(TUint32 aMask);
	inline void SetPollAttempts(TUint aData);
	inline void SetTimeOutRetries(TUint aData);
	inline void SetCRCRetries(TUint aData);
	inline void SetBusClockInKhz(TUint aParam);			// In kilohertz
	inline void SetTicksClockIn(TUint aParam);			// Number of clock ticks in ClockIn phase
	inline void SetTicksClockOut(TUint aParam);			// Number of clock ticks in ClockOut phase
	inline void SetResponseTimeOutInTicks(TUint aParam);	// Timeout in bus clock ticks
	inline void SetDataTimeOutInMcs(TUint aParam);		// in microseconds
	inline void SetBusyTimeOutInMcs(TUint aParam);		// in microseconds
	inline void SetOpCondBusyTimeout(TUint16 aData);	// Units of 10mS
	inline TInt OpCondBusyTimeout();
private:
	TUint iPollAttempts;
	TUint32 iModes;
	TUint32 iUpdateMask;
	TUint32 iClientMask;
	TUint iTimeOutRetries;
	TUint iCRCRetries;
	TUint16 iUnlockRetries;
	TUint16 iOpCondBusyTimeout;							// Units of 10mS
	TMMCBusConfig iBusConfig;
	friend class DMMCStack;
	};


class TMMCRCAPool
	{
public:
	inline TMMCRCAPool();
	TRCA GetFreeRCA();
	inline void LockRCA(TRCA);
	inline void UnlockRCA(TRCA);
	inline void ReleaseUnlocked();
private:
	TUint32 iPool;
	TUint32 iLocked;
	};


class TMMCSessRing
	{
public:
	TMMCSessRing();
	inline TBool IsEmpty() const;
	void Erase();
	inline void SetMarker();				// Sets Marker into Point position
	inline void AdvanceMarker();			// Moves Marker one position forward
	inline void Point();					// Sets Point into Marker position
	TBool Point(DMMCSession* aSessP);		// Finds aSessP and sets Point to it
	void Add(DMMCSession* aSessP);			// Inserts aSessP before the Marker; Point moves to Marker
	void Add(TMMCSessRing& aRing);
	DMMCSession* Remove();					// Removes at Point; Point moves forward
	void Remove(DMMCSession* aSessP);		// Points aSessP first, then remove()
	inline TUint Size() const;
	inline operator DMMCSession*() const;
	DMMCSession* operator++(TInt);			// returns Point and moves it forward; stops at Marker
private:
	DMMCSession* iPMark;
	DMMCSession* iPoint;
	DMMCSession* iPrevP;
	TUint iSize;
	};


//
// DMMCStack State Machine Functions are supported by TMMCStateMachine class
//
// The structure of state machine functions is assumed to be as follows
//
// TMMCErr DMMCStack::FunctionNameSMST( TAny* aPtr )
//	{ return( STATIC_CAST(DMMCStack*,aPtr)->FunctionNameSM() ); }
//
// TMMCErr DMMCStack::FunctionNameSM()
//	{
//		enum states {EStBegin=0, ..., EStEnd };
//		DMMCSession& s = Session();
//		TMMCStateMachine& m = Machine();
//		const TMMCErr err = m.SetExitCode( 0 );
//
//		for(;;)
//		{
//			switch(m.State())
//			{
//			case EStBegin:
//				{
//					....
//				}
//			case EStNext:
//				{
//					.....
//				}
//			case EStEnd: break;
//			default: Panic(...);
//			}
//			break;
//		}
//		return(m.Pop());
//	}
//
// State Machine remembers the next state number and function name and goes there as soon
// as the control is returned to the session. To release the control and wait for the next
// re-entrance (which will happen immediately if the session is not blocked or, as soon as
// an asynchronous event removes the blocking condition), a state machine function has to
// return( 0 ); Returning non-zero exit code will result in the session being completed with
// that error code unless a caller state machine function has explicitly intercepted such
// an error with m.SetTraps( TMMCErr aMask ).
//
// To make a state machine function code more readable, the following macros are provided:
//
// SMF_NEXTS(nexts)				- set the next state to "nexts"
// SMF_CALL(func)				- invoke SM function "func", then go to the next state
// SMF_CALLWAIT(func)			- the same as above, but sleep at the entry point
// SMF_CALLMYS(nexts,retst)		- invoke current SM function at "nexts" entry point
// SMF_CALLMEWR(retst)			- invoke me right here with return state retst
// SMF_INVOKES(func,nexts)		- invoke SM function "func", then go to the state "nexts"
// SMF_INVOKEWAITS(func,nexts)	- the same as above, but sleep at the entry point
// SMF_WAIT						- sleep at the next state
// SMF_WAITS(nexts)				- set next state to "nexts", then sleep
// SMF_RETURN(value)			- return an error to the caller SM function
// SMF_EXIT						- return to the caller SM function
// SMF_EXITWAIT					- the same as above, but sleep at the exit point
// SMF_JUMP(func)				- transfer the control to SM function "func"
// SMF_JUMPWAIT(func)			- the same as above, but sleep at the entry point
// SMF_GOTONEXTS				- goto the next state
// SMF_GOTOS(nexts)				- set the next state to "nexts", then go to it
// SMF_STATE(sname)				- declare the state name "sname"
// SMF_BPOINT(sname)			- declare the state "sname" and sleep here if blocked statically
//
#define SMF_BEGIN TMMCStateMachine& m=Machine();const TMMCErr err=m.SetExitCode(0);\
				for(;;){switch(m.State()){case EStBegin:{if(err) (void)0;
#define SMF_END }case EStEnd:break;default:DMMCController::Panic(DMMCController::EMMCMachineState);}break;}\
				return(m.Pop());
#define SMF_NEXTS(nexts) m.SetState(nexts);
#define SMF_CALL(func) return(m.Push(func));
#define SMF_CALLWAIT(func) return(m.Push(func,ETrue));
#define SMF_CALLMYS(nexts,retst) {m.SetState(retst);m.PushMe();m.SetState(nexts);continue;}
#define SMF_CALLMEWR(retst) {m.SetState(retst);m.PushMe();}
#define SMF_INVOKES(func,nexts) {m.SetState(nexts);return(m.Push(func));}
#define SMF_INVOKEWAITS(func,nexts) {m.SetState(nexts);return(m.Push(func,ETrue));}
#define SMF_WAIT return(0);
#define SMF_WAITS(nexts) return(m.SetState(nexts));
#define SMF_RETURN(value) {m.Pop();return(value);}
#define SMF_EXIT break;
#define SMF_EXITWAIT return(m.Pop(ETrue));
#define SMF_JUMP(func) return(m.Jump(func));
#define SMF_JUMPWAIT(func) return(m.Jump(func,ETrue));
#define SMF_GOTONEXTS continue;
#define SMF_GOTOS(nexts) {m.SetState(nexts);continue;}
#define SMF_STATE(sname) }case sname:{
#define SMF_BPOINT(sname) }case sname: if(StaticBlocks()) return(m.SetState(sname));{

class TMMCStateMachine
	{
public:
	inline void Setup(TMMCErr (*anEntry)(TAny*), TAny* aContextP);
	IMPORT_C void Reset();
	IMPORT_C TMMCErr Dispatch();
	inline TMMCErr ExitCode();
	inline TMMCErr SetExitCode(TMMCErr aCode);
	inline TUint State();
	inline TMMCErr SetState(TUint aState);
	inline void SuppressSuspension();
	inline void SetTraps(TMMCErr aMask);
	inline void ResetTraps();
	inline void Abort();
	inline TMMCErr Pop(TBool aSuspend=EFalse);
	inline TMMCErr PushMe();
	IMPORT_C TMMCErr Push(TMMCErr (*anEntry)(TAny*), TBool aSuspend=EFalse);
	IMPORT_C TMMCErr Jump(TMMCErr (*anEntry)(TAny*), TBool aSuspend=EFalse);
private:
	class TMMCMachineStackEntry
		{
	public:
		TMMCErr (*iFunction)(TAny*);
		TUint iState;
		TMMCErr iTrapMask;
		};
	TBool iAbort;
	TBool iSuspend;
	TAny* iContextP;
	TMMCErr iExitCode;
	TInt iSP;
	TMMCMachineStackEntry iStack[KMaxMMCMachineStackDepth];
	};


// DMMCStack serves an incoming queue of session requests.
// Each queue element is represented by an instance of the following class

typedef TMMCErr (*TMMCSMSTFunc)(TAny*);

class DMMCSession : public CBase
	{
public:
	IMPORT_C virtual ~DMMCSession();
	IMPORT_C DMMCSession(const TCallBack& aCallBack);

	// Object initialisation
	inline void SetStack(DMMCStack* aStackP);
	IMPORT_C void SetCard(TMMCCard* aCardP);

	// Control macros setup
	inline void SetupCIMUpdateAcq();
	inline void SetupCIMInitStack();
	inline void SetupCIMCheckStack();
	inline void SetupCIMSetupCard();
	inline void SetupCIMLockStack();

	// Data transfer macros setup
	IMPORT_C void SetupCIMReadBlock(TMMCArgument aDevAddr, TUint32 aLength, TUint8* aMemoryP);
	IMPORT_C void SetupCIMWriteBlock(TMMCArgument aDevAddr, TUint32 aLength, TUint8* aMemoryP);
	IMPORT_C void SetupCIMReadMBlock(TMMCArgument aDevAddr, TUint32 aLength, TUint8* aMemoryP, TUint32 aBlkLen);
	IMPORT_C void SetupCIMWriteMBlock(TMMCArgument aDevAddr, TUint32 aLength, TUint8* aMemoryP, TUint32 aBlkLen);
	IMPORT_C void SetupCIMEraseSector(TMMCArgument aDevAddr, TUint32 aLength);
	IMPORT_C void SetupCIMEraseGroup(TMMCArgument aDevAddr, TUint32 aLength);
	IMPORT_C void SetupCIMReadIO(TUint8 aRegAddr, TUint32 aLength, TUint8* aMemoryP);
	IMPORT_C void SetupCIMWriteIO(TUint8 aRegAddr, TUint32 aLength, TUint8* aMemoryP);
	IMPORT_C void SetupCIMLockUnlock(TUint32 aLength, TUint8* aMemoryP);

	// Raw commands (must be used in the locked bus state only)
	// Known commands with or without (with a default) argument
	IMPORT_C void SetupCommand(TMMCCommandEnum aCommand, TMMCArgument anArgument=0);

	// Generic unknown command with unknown response type
	IMPORT_C void SetupRSCommand(TMMCCommandEnum aCommand, TMMCArgument anArgument,
								TUint32 aResponseLength, TMMCCommandTypeEnum aCommandType=ECmdTypeUK,
								TMMCResponseTypeEnum aResponseType=ERespTypeUnknown,
								TUint32 aCommandClass=KMMCCmdClassNone);

	// Generic data transfer command
	IMPORT_C void SetupDTCommand(TMMCCommandEnum aCommand, TMMCArgument anArgument,
								TUint32 aTotalLength, TUint8* aMemoryAddress, TUint32 aBlockLength=0,
								TBool aStopTransmission=EFalse, TMMCCmdDirEnum aDir=EDirNone,
								TUint32 aCommandClass=KMMCCmdClassNone);
	// Actions
	IMPORT_C TInt Engage();					// Enque session for execution
	inline void UnlockStack();				// Unlock the bus
	inline void Stop();						// Signal session to complete (stop and complete)
	inline void Abort();					// Abort only (no completion)

	// Info retrieval
	IMPORT_C TInt EpocErrorCode() const;	// Derived from MMCExitCode and LastStatus
	inline TMMCSessionTypeEnum SessionID() const;
	inline DMMCStack* StackP() const;		// DMMCStack serving this session
	inline TMMCCard* CardP() const;			// The current card pointer
	inline TBool IsEngaged() const;			// Session is being served by DMMCStack
	inline TMMCErr MMCExitCode() const;		// MMC specific error code returned by DMMCStack
	inline TMMCStatus LastStatus() const;	// Last R1 response received from the card
	inline TUint32 BytesTransferred() const;// The actual amount of data transferred in this session
	inline TUint8* ResponseP();				// Current command response (&iCommand[iCmdSP].iResponse)
	inline TUint32 EffectiveModes() const;	// Modes which DMMCStack will consider as effective
	//
	inline void ResetCommandStack();
private:
	void SetupCIMControl(TInt aSessNum);
protected:
	virtual TMMCSMSTFunc GetMacro(TInt aSessNum) const;
private:
#ifdef __EPOC32__
	static TInt PollTimerCallBack(TAny* aSessP);
	static TInt RetryTimerCallBack(TAny* aSessP);
	static TInt ProgramTimerCallBack(TAny* aSessP);
#endif
	inline void Block(TUint32 aFlag);
	inline void UnBlock(TUint32 aFlag, TMMCErr anExitCode);
	inline void SwapMe();
	void SynchBlock(TUint32 aFlag);
	void SynchUnBlock(TUint32 aFlag);
public:
	static const TMMCCommandSpec& FindCommandSpec(const TMMCIdxCommandSpec aSpecs[], TInt aIdx);
	void FillCommandDesc();
	void FillCommandDesc(TMMCCommandEnum aCommand);
	void FillCommandDesc(TMMCCommandEnum aCommand, TMMCArgument anArgument);
	void FillCommandArgs(TMMCArgument anArgument, TUint32 aLength, TUint8* aMemoryP, TUint32 aBlkLen);
	inline TMMCCommandDesc& Command();	// The current command descriptor
	TMMCStatus iLastStatus;			// Last R1 response
	inline void PushCommandStack();
	inline void PopCommandStack();
	TMMCCard* iCardP;				// Pointer to Card Info object
	TRCA CardRCA();						// Checks that card is still ready - otherwise returns 0
	TMMCSessionTypeEnum iSessionID;
private:
	DMMCSession* iLinkP;			//
	TCallBack iCallBack;			// Where to report the completion
	DMMCStack* iStackP;				// Pointer to Stack Controller
	TCID iCID;						// Card ID to ensure we are still talking to the same card
	TUint32 iBytesTransferred;		// The actual amount of data transferred in this session
	TMMCErr iMMCExitCode;			// State Machine exit code (MMC specific)
public:
	TUint32 iState;					// Session state flags (synchronous)
private:
	TUint iInitContext;				// Stack Initialiser pass number
	TUint iGlobalRetries;			// Global retry counter

	// Asynchronous flags analysed by scheduler
	TBool volatile iDoAbort;		// Marks the session for abort
	TBool volatile iDoStop;			// Stop the session as soon as it's safe
	TBool volatile iDoComplete;		// Completion callback is now to be invoked
	TBool iBrokenLock;				// Stack lock is broken by force major
	//
	TUint32 iBlockOn;				// blocking reasons
	TInt iCmdSP;					// Current Command stack index
	TMMCCommandDesc iCommand[KMaxMMCCommandStackDepth];	// Command stack
	TMMCStateMachine iMachine;		// State Machine context
#ifdef __EPOC32__
	TMilliSecondCallBack iPollTimer;
	TMilliSecondCallBack iRetryTimer;
	TMilliSecondCallBack iProgramTimer;
#endif
public:
	TMMCStackConfig iConfig;		// Client configuration parameters
	friend class DMMCStack;
	friend class TMMCSessRing;
	friend class TMmcCardArray;
	};

class DMMCStack : public CBase
	{
public:
	DMMCStack(TPBusNum aBus, DMMCController* anMMCController);
	virtual TInt Init();
	//
	// Actions
	inline void ReportPowerUp();
	inline void ReportPowerDown();
	TBool PowerEvent(TPBusPwrEvent anEvent,TInt anInfo);
	IMPORT_C void PowerUpStack(DThread *aThread, TRequestStatus *aReqStat);
	IMPORT_C void PowerDownStack(TBool aMediaChange=EFalse);
	inline void Reset();					// Discard all requests and clear up
	inline void CompleteAll(TMMCErr aCode);	// Complete all operations with an error
	IMPORT_C TInt Stop(TMMCCard* aCardP);
	//
	// Inquiries
	inline TUint MaxCardsInStack() const;
	inline TMMCCard* CardP(TUint aCardNumber);
	inline DMMCController* MMCControllerP() const;
	inline TBool InitStackInProgress() const;
	inline TBool HasSessionsQueued() const;
	inline TBool HasCardsPresent();

protected:
	// Platform layer service
	inline TMMCBusConfig& BusConfig();
	inline DMMCSession& Session();				// Current session
	inline TMMCCommandDesc& Command();			// Current command descriptor of current session
	inline TMMCStateMachine& Machine();			// State machine of current session
	inline void BlockCurrentSession(TUint32 aFlag);
	inline void UnBlockCurrentSession(TUint32 aFlag, TMMCErr anExitCode);
	inline void ReportInconsistentBusState();
	inline void ReportASSPEngaged();
	inline void ReportASSPDisengaged();
	inline void SetDoorOpened();
	inline TRCA CurrentSessCardRCA();			// Checks that card is still ready - otherwise returns 0
	inline void CurrentSessPushCmdStack();
	inline void CurrentSessPopCmdStack();
	inline void CurrentSessFillCmdDesc(TMMCCommandEnum aCommand);
	inline void CurrentSessFillCmdDesc(TMMCCommandEnum aCommand,TMMCArgument anArgument);
	inline void CurrentSessFillCmdArgs(TMMCArgument anArgument,TUint32 aLength,TUint8* aMemoryP,TUint32 aBlkLen);

	// Stack service provided by platform/variant layer.
	virtual void SetBusConfigDefaults(TMMCBusConfig&, TUint aClock)=0;
	virtual void InitClockOff()=0;
	virtual void ASSPReset()=0;
	virtual void ASSPDisengage()=0;
	virtual void DoPowerDown()=0;
	virtual TBool CardDetect(TUint aCardNumber);
	virtual TBool WriteProtected(TUint aCardNumber);
	//
	// State Machine functions implemented in platform layer.
	virtual TMMCErr DoPowerUpSM()=0;
	virtual TMMCErr InitClockOnSM()=0;
	virtual TMMCErr IssueMMCCommandSM()=0;
	TBool StaticBlocks();

private:
	//
	// Session service
	void Add(DMMCSession* aSessP);
	void Abort(DMMCSession* aSessP);
	void Stop(DMMCSession* aSessP);
	void Block(DMMCSession* aSessP, TUint32 aFlag);
	void UnBlock(DMMCSession* aSessP, TUint32 aFlag, TMMCErr anExitCode);
	void UnlockStack(DMMCSession* aSessP);
	void MarkComplete(DMMCSession* aSessP, TMMCErr anExitCode);
	inline void StackSessionNotifier(DThread* aNotifierThread, TRequestStatus* aNotifierReqStat);
	//
	//	Stack control and operations support
	// Scheduler and its supplementary functions
	enum TMMCStackSchedStateEnum
		{
		ESchedContinue=0,
		ESchedLoop=1,
		ESchedExit,
		ESchedChooseJob
		};
	void Scheduler(volatile TBool& aFlag);
	void DoSchedule();
	TMMCStackSchedStateEnum SchedGetOnDFC();
	void SchedSetContext(DMMCSession* aSessP);
	void SchedDoAbort(DMMCSession* aSessP);
	TMMCStackSchedStateEnum SchedResolveStatBlocks(DMMCSession* aSessP);
	TMMCStackSchedStateEnum SchedGroundDown(DMMCSession* aSessP, TMMCErr aReason);
	TMMCStackSchedStateEnum SchedEnqueStackSession(TMMCSessionTypeEnum aSessID);
	void SchedGrabEntries();
	void SchedDisengage();
	inline TMMCStackSchedStateEnum SchedAbortPass();
	inline TMMCStackSchedStateEnum SchedCompletionPass();
	inline TMMCStackSchedStateEnum SchedInitStack();
	inline TBool SchedPreemptable();
	inline TMMCStackSchedStateEnum SchedSession();
	inline TMMCStackSchedStateEnum SchedChooseJob();
	//
	// Miscellaneous SM function service
	void MergeConfig(DMMCSession* aSessP);
	inline void DeselectsToIssue(TUint aNumber);

	// Static Completion routines.
	static TInt StackDFC(TAny* aStackP);
	static TInt StackSessionCBST(TAny* aStackP);
	TInt StackSessionCB();
	static TInt AutoUnlockCBST(TAny *aStackP);
	TInt AutoUnlockCB();
	
	inline TInt AddPowerEvent(TPBusCallBack& aCallBack,TPBusNum aBus,TInt anEventNum); 
	inline void RemovePowerEvent(CBase *aClientID);

protected:
	// State machines.  The adapter functions just call the non-static versions.
	// Top-level state machines.
	static TMMCErr NakedSessionSMST(TAny* aStackP);				// ECIMNakedSession
	inline TMMCErr NakedSessionSM();
	static TMMCErr CIMUpdateAcqSMST(TAny* aStackP);				// ECIMUpdateAcq
	       TMMCErr CIMUpdateAcqSM();
	static TMMCErr CIMInitStackSMST(TAny* aStackP);				// ECIMInitStack
	inline TMMCErr CIMInitStackSM();
	static TMMCErr CIMCheckStackSMST(TAny* aStackP);			// ECIMCheckStack
	inline TMMCErr CIMCheckStackSM();
	static TMMCErr CIMSetupCardSMST(TAny* aStackP);				// ECIMSetupCard
	inline TMMCErr CIMSetupCardSM();
	static TMMCErr CIMReadWriteBlocksSMST(TAny* aStackP);		// ECIMReadBlock, ECIMWriteBlock, ECIMReadMBlock, ECIMWriteMBlock
	virtual TMMCErr CIMReadWriteBlocksSM();
	static TMMCErr CIMEraseSMST(TAny* aStackP);					// ECIMEraseSector, ECIMEraseGroup
	inline TMMCErr CIMEraseSM();
	static TMMCErr CIMReadWriteIOSMST(TAny* aStackP);			// ECIMReadIO, ECIMWriteIO
	inline TMMCErr CIMReadWriteIOSM();
	static TMMCErr CIMLockUnlockSMST(TAny *aStackP);			// ECIMLockUnlock
	inline TMMCErr CIMLockUnlockSM();
	static TMMCErr NoSessionSMST(TAny* aStackP);				// ECIMLockStack
	inline TMMCErr NoSessionSM();
	static TMMCErr AcquireStackSMST(TAny* aStackP);
	virtual TMMCErr AcquireStackSM();
	static TMMCErr CheckStackSMST(TAny* aStackP);			// ECIMCheckStack
	inline TMMCErr CheckStackSM();
	static TMMCErr DoPowerUpSMST(TAny* aStackP);
	static TMMCErr InitClockOnSMST(TAny* aStackP);
	static TMMCErr IssueMMCCommandSMST(TAny* aStackP);

	static TMMCErr AttachCardSMST(TAny* aStackP);
	inline TMMCErr AttachCardSM();
	static TMMCErr ExecCommandSMST(TAny* aStackP);
	inline TMMCErr ExecCommandSM();
	static TMMCErr IssueCommandCheckResponseSMST(TAny* aStackP);
	inline TMMCErr IssueCommandCheckResponseSM();
	static TMMCErr PollGapTimerSMST(TAny* aStackP);
	inline TMMCErr PollGapTimerSM();
	static TMMCErr RetryGapTimerSMST(TAny* aStackP);
	inline TMMCErr RetryGapTimerSM();
	static TMMCErr ProgramTimerSMST(TAny *aStackP);
	inline TMMCErr ProgramTimerSM();

	//	----------- Data Members -------------
private:
	//
	TPBusEventArrayBase iPwrEventArray;
	// Synchronous status, data structures and control info.
	TUint32 iStackState;
	TUint iInitContext;				// Stack Initialiser pass number
	DMMCSession* iLockingSessionP;
	TMMCSessRing iWorkSet;
	TMMCSessRing iReadyQueue;
	TMMCSessRing iEntryQueue;
	TDfc iStackDFC;
	TRCA iSelectedCard;
	DMMCController* iMMCControllerP;
	DMMCSession iStackSession;
	DMMCSession iAutoUnlockSession;
	TInt iAutoUnlockIndex;			// index into iCards
	TUint8 iAutoUnlockData[1 + 1 + KMaxMediaPassword];
	DThread* iNotifierThread;
	TRequestStatus* iNotifierReqStat;
	enum TInitState {EISPending, EISDone};
	TInitState iInitState;
	//
	//	Stack and Scheduler control
	// Asynchronous sheduler attention flags
	TBool volatile iAttention;	// There are ready sessions
	TBool volatile iAbortReq;	// There are sessions marked for abort
	TBool volatile iCompReq;	// There are sessions to complete
	TBool volatile iInitialise;	// Enforce InitStack (after enforced PowerDown)
	TBool volatile iUpdate;		// Enque InitStack into iWorkSet
	// Other asynchronous flags
	TBool volatile iDoorOpened;	// Only set when a media change has occured while the stack scheduler is active
	TBool volatile iPoweredUp;
	TBool volatile iDFCRunning;
	TBool volatile iAbortAll;
	TMMCErr volatile iCompleteAllExitCode;
	//
	// Session context
protected:
	DMMCSession* iSessionP;
private:
	//
	// Bus control
	TDSR iCurrentDSR;
	//
	// Stack data structures and Session/StateMachine miscellaneous
	TUint iDeselectsToIssue;
	TInt iCxDeselectCount;
	TUint8 iCMD42CmdByte;
	TMediaPassword iMPTgt;
public:
	IMPORT_C TUint32 EffectiveModes(const TMMCStackConfig& aClientConfig);
	TUint32 iCurrentOpRange;
	TInt iCxCardCount;
	TInt iCxPollRetryCount;
	TMMCStackConfig iConfig;
	TUint iMaxCardsInStack;
	TMMCRCAPool iRCAPool;
	TMmcCardArray* iCardArray;
	TMMCStackConfig iMasterConfig;
	friend class DMMCController;
	friend class DMMCSession;
	friend class TMmcCardArray;
	};

class TMmcCardMachineInfo
	{
public:
	TInt iTotalSockets;
	TInt iTotalMediaChanges;
	TInt iTotalPrimarySupplies;
	TBool iSPIMode;						// SPI mode not yet supported
    TInt iBaseBusNumber;
	};
typedef TPckg<TMmcCardMachineInfo> TMmcCardMachineInfoPckg;


class TMMCPsu : public TPBusPsuBase 
    {
public:
	TMMCPsu(TInt aPsuNum);
    virtual TInt ResetEvent(TPBusPwrEvent anEvent,TInt anInfo,TResetMode aMode);
	inline void SetVoltage(TUint32 aVoltage);
protected:		  
	TUint32 iVoltageSetting; // OCR register format
private:
	friend class DMMCController;
    };

class TMMCMediaChange : public TMediaChangeBase
	{
public:
	TMMCMediaChange(TInt aMediaChangeNum);
	virtual TInt Init()=0;
	virtual TMediaState MediaState() = 0;
private:
	virtual void MediaChangeEvent(TPBusPwrEvent anEvent);
	};

class DMMCController : public DPeriphBusController
	{
public:
	DMMCController();
	// Functions inherited from DPeriphBusController
    virtual TPBusControllerType ControllerType();
	virtual void PowerUpBus(TPBusNum aBus,DThread *aThread,TRequestStatus *aReqStat);
	virtual TInt RegisterPowerNotification(TPBusNum aBus,TPBusCallBack& aCallBack,TUint aFlag=0);
	virtual void DeregisterPowerNotification(TPBusNum aBus,CBase* aClientID,TPBusCallBack* aCallBack=NULL);
	virtual TInt SetPowerEvent(TPBusNum aBus,TPBusPwrEvent anEvent,TInt anInfo=0);
	virtual TInt DeregisterClient(CBase *aClientID);
	virtual TInt DeviceIsReady(TPBusNum aBus);
	virtual TInt TotalSupportedBuses();
	virtual TPBusNum BaseBusNumber();
	virtual TInt ReadPasswordData(TDes8 &aBuf);
	virtual TInt WritePasswordData(TDesC8 &aBuf);
	virtual TInt PasswordStoreLengthInBytes();
	virtual TInt PrepareStore(TPBusNum aBus, TPBusPasswordFunc aFunc, TPBusPasswordData &aData, DThread *aThread);
	// MMC specific functions
	inline DMMCStack* Stack(TPBusNum aBus);
    inline void ResetInactivity(TPBusNum aBus);
	virtual void AdjustPartialRead(const TMMCCard* aCard, TUint32 aStart, TUint32 aEnd, TUint32* aPhysStart, TUint32* aPhysEnd) const = 0;
	virtual void GetBufferInfo(TUint8** aMDBuf, TInt* aMDBufLen) = 0;
	IMPORT_C TBool IsMappingIncorrect(const TCID& aCID, const TMediaPassword& aPWD);
	virtual DMMCSession* AllocSession(const TCallBack& aCallBack) const;
	inline TPBusPsuBase* AccessPrimaryPsu(TPBusNum aBus);
protected:
	// Functions inherited from DPeriphBusController
	virtual void DoCreateL();
    virtual TInt PowerOn();
    virtual void PowerStandby();
    virtual void PowerEmergencyStandby();
	virtual TInt EnableEvent(TPBusNum aBus,TInt anEvent);
	virtual TInt DisableEvent(TPBusNum aBus,CBase *aClientID,TInt anEvent);
	virtual TInt ClearEvent(TPBusNum aBus,TInt anEvent);
	virtual TMediaChangeBase *MediaChange(TPBusNum aBus);
	virtual TPBusPsuBase *PrimaryPsu(TPBusNum aBus);
	// MMC specific functions
	virtual void InitL()=0;
	virtual void SetMachineInfo()=0;
#ifdef __EPOC32__
	virtual TInt ProgramPeriodInMilliSeconds() const = 0;
#endif
private:
	class TMapping
		{
	public:
		TBuf8<KMMCCIDLength> iCID;
		TMediaPassword iPWD;
		enum TState {EStPending, EStValid, EStInvalid};
		TState iState;
		};
	CArrayFixSeg<TMapping> *iStore;
	TKeyArrayFix iStoreKey;

	TInt PasswordControlStart(const TCID &aCID, const TMediaPassword *aPWD);
	void PasswordControlEnd(DMMCSession *aSessP, TInt aResult);

	TBool RefreshStore();
	TMapping *FindMappingInStore(const TCID &aCID);
	TInt InsertMapping(const TCID &aCID, const TMediaPassword &aPWD, TMapping::TState aState);
protected:
	DMMCStack* iStacks[KMaxMMCStacks];
    TMmcCardMachineInfo iMachineInfo;
public:
	TMMCMediaChange *iMediaChange;
	TMMCPsu* iPsu;
	enum TMMCPanic
		{
		EMMCMachineStack=0,
		EMMCMachineState=1,
		EMMCSessRingNoSession=2,
		EMMCStackSessionEngaged=3,
		EMMCInitStackBlocked=4,
		EMMCNoFreeRCA=5,
		EMMCCommandStack=6,
		EMMCRWSessionID=7,
		EMMCEraseSessionID=8,
		EMMCIOSessionID=9,
		EMMCSessionNoPswdCard=10,
		EMMCSessionPswdCmd=11,
		EMMCSessionBadSessionID=12
		};
    static void Panic(TMMCPanic aPanic);
	friend class DMMCStack;
	friend class DMMCSession;
	friend class TMMCMediaChange;
	};

#if defined(__WINS__)
class TMMCControllerInterface
	{
public:
	IMPORT_C static TInt Create(); 
	};
#endif

#include "p32mmc.inl"

#endif	// __P32MMC_H__

