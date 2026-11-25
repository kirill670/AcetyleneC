// D_MMCIF.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
// This header provides the interface to MMCIF.LDD, which provides a set of
// direct interface functions with the kernel MultiMediaCard Controller
//

#if !defined(__D_MMCIF_H__)
#define __D_MMCIF_H__
#include "e32svr.h" 

// General definitions
const TInt KMaxCardsPerStack=2;
const TInt KSectorSizeInBytes=512;
const TInt KSectorSizeShift=9;
const TInt KDrvBufSizeInSectors=8;
const TInt KDrvBufSizeInBytes=(KDrvBufSizeInSectors<<KSectorSizeShift); // 4K

// Power notification
const TUint KMmcPEventPwrDownEmergency=0x00000001;
const TUint KMmcPEventPwrDownNormal=0x00000002;
const TUint KMmcPEventPwrUp=0x00000004;
const TUint KMmcPEventMediaChange=0x00000008;
enum TMmcPwrEventReason {EMmcPEventPwrDownEmergency,EMmcPEventPwrDownNormal,EMmcPEventPwrUp,EMmcPEventMediaChange};

//
class TMmcStackInfo
	{
public:
	inline TMmcStackInfo()
		  {Mem::FillZ(this,sizeof(TMmcStackInfo));}
public:
	TUint iMaxMMCCardsInStack;
	TBool iHasCardsPresent;
	TUint iCardsPresentMask;
	TBool iInitStackInProgress;
	TBool iHasSessionsQueued;
	};
	
// Copy of the beginning of the TMMCStackConfig class
class TMmcConfig
	{
public:	
	inline TMmcConfig()
		  	{Mem::FillZ(this,sizeof(TMmcConfig));}
	inline TMmcConfig& operator=(const TUint8* aPtr)
			{Mem::Copy(&iPollAttempts,aPtr,sizeof(TMmcConfig)); return(*this);}
public:
	TUint iPollAttempts;
	TUint32 iModes;
	TUint32 iUpdateMask;
	TUint32 iClientMask;
	TUint iTimeOutRetries;
	TUint iCRCRetries;
	TUint16 iUnlockRetries;
	TUint16 iOpCondBusyTimeout;							// Units of 10mS
	};
//
enum TMmcMediaType {EMmcROM,EMmcFlash,EMmcIO,EMmcOther,EMmcNotSupported};
const TUint32 KMMCCardFlgHasPassword=0x01;
const TUint32 KMMCCardFlgIsWriteProtected=0x02;
const TUint32 KMMCCardFlgIsLockable=0x04;
class TMmcCardInfo
	{
public:
	inline TMmcCardInfo()
		  {Mem::FillZ(this,sizeof(TMmcCardInfo)); iMediaType=EMmcNotSupported;}
public:
	TBool iIsReady;
	TBool iIsLocked;
	TUint8 iCID[16];
	TUint8 iCSD[16];
	TUint16 iRCA;
	TMmcMediaType iMediaType;
    TInt iCardSizeInBytes;
    TUint32 iPrefWrGrpLen;
    TUint32 iPreferredEraseUnitSize;
	TUint32 iMinEraseSectorSize;
    TUint32 iFlags;
	};

// Read/Write Block info flags
const TUint KMMCCsdReadBlPartial=0x01;
const TUint KMMCCsdReadBlkMisalign=0x02;
const TUint KMMCCsdWriteBlPartial=0x04;
const TUint KMMCCsdWriteBlkMisalign=0x08;
			
// Command Classes Bit Set
const TUint KMMCCCNone=0x00;
const TUint KMMCCCBasic=0x01;
const TUint KMMCCCStreamRead=0x02;
const TUint KMMCCCBlockRead=0x04;
const TUint KMMCCCStreamWrite=0x08;
const TUint KMMCCCBlockWrite=0x10;
const TUint KMMCCCErase=0x20;
const TUint KMMCCCWriteProtection=0x40;
const TUint KMMCCCLockCard=0x80;
const TUint KMMCCCApplication=0x100;
const TUint KMMCCCIOMode=0x200;

class TMmcCSDInfo
	{
public:
	inline TMmcCSDInfo()
		  {Mem::FillZ(this,sizeof(TMmcCSDInfo));}
public:	
	TUint iCCC;
	TUint iReadBlLen;
	TUint iWriteBlLen;
	TUint iRdWrInfo;
	TUint iEraseSectorSize;
	TUint iEraseGroupSize;
	TUint iSpecVers;
	TUint iTAAC;
	TUint iNSAC;
	TUint iTransferSpeed;
	};	
//
const TUint KBTDTypeMultipleBlocks = 0x01;
class TBlockTransferData
    {
public:
	inline TBlockTransferData(TUint32 aDevAddr,TUint32 aCommandLength,TAny* aMemoryP,TUint32 aBlockLen,TUint aTransferType)
    	: iDevAddr(aDevAddr),iCommandLength(aCommandLength),iMemoryP(aMemoryP),iBlockLen(aBlockLen),iTransferType(aTransferType)
        {}
public:
    TUint32 iDevAddr;
    TUint32 iCommandLength;
    TAny* iMemoryP;
    TUint32 iBlockLen;
    TUint iTransferType;
    };
//
class TCapsMmcIfV01
	{
public:
	TVersion version;
	};
//
class RMmcCntrlIf : public RBusLogicalChannel
	{
public:
	enum {EMajorVersionNumber=1,EMinorVersionNumber=1,EBuildVersionNumber=0};
	enum TRequest
		{EReqReadBlk=0x0,EReqReadBlkCancel=0x1,
		EReqWriteBlk=0x1,EReqWriteBlkCancel=0x2,
		EReqRegisterEvent=0x2,EReqRegisterEventCancel=0x4,
		EReqEraseSect=0x3,EReqEraseSectCancel=0x8,
		EReqEraseGrp=0x4,EReqEraseGrpCancel=0x10
		};
	enum TControl
        {ESvReset,ESvPwrUp,ESvPwrDown,ESvSelectCard,EExecStackInfo,
        EExecCardInfo,EExecCSDInfo,EExecSetTransferBufferLen,EExecForceMediaChange};
public:
	inline void Cancel();
	inline TInt Open(TInt aStack,const TVersion& aVer)
		{return(DoCreate(_L("MmcIf"),aVer,NULL,(TInt)aStack,NULL,NULL));}
	inline TVersion VersionRequired() const
		{return(TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber));}
	inline void Reset()
		{DoSvControl(ESvReset);}
	inline void PwrUpAndInitStack(TRequestStatus& aReqStat)
		{DoSvControl(ESvPwrUp,(TAny*)&aReqStat);}
	inline void PwrDownStack()
		{DoSvControl(ESvPwrDown);}
	inline TInt StackInfo(TMmcStackInfo& anInfo,TMmcConfig& aMasterConfig)
		{return(DoControl(EExecStackInfo,&anInfo,&aMasterConfig));}
	inline TInt SelectCard(TInt aCard)
		{return(DoSvControl(ESvSelectCard,(TAny*)aCard));}
	inline TInt CardInfo(TMmcCardInfo& anInfo)
		{return(DoControl(EExecCardInfo,&anInfo));}
	inline TInt CSDInfo(TMmcCSDInfo& anInfo)
		{return(DoControl(EExecCSDInfo,&anInfo));}
	inline TInt SetTransferBufferLength(TInt aLength)
		{return(DoControl(EExecSetTransferBufferLen,(TAny*)aLength));}
	inline TInt ForceMediaChange()
		{return(DoControl(EExecForceMediaChange));}	
	inline void RegisterEvent(TRequestStatus& aStatus,TInt& aNotificationReason,TUint anEventMask)
		{DoRequest(EReqRegisterEvent,aStatus,&aNotificationReason,(TAny*)anEventMask);}	
	inline void ReadBlock(TRequestStatus &aStatus,TUint32 aDevAddr,TUint32 aLength,TDes8 &aDes)	
		{
		TBlockTransferData btd(aDevAddr,aLength,(TAny*)&aDes,0,0);
		DoRequest(EReqReadBlk,aStatus,(TAny*)&btd);
		}
	inline void WriteBlock(TRequestStatus &aStatus,TUint32 aDevAddr,TUint32 aLength,const TDesC8 &aDes)	
		{
		TBlockTransferData btd(aDevAddr,aLength,(TAny*)&aDes,0,0);
		DoRequest(EReqWriteBlk,aStatus,(TAny*)&btd);
		}
	inline void ReadMBlock(TRequestStatus &aStatus,TUint32 aDevAddr,TUint32 aLength,TUint32 aBlkLen,TDes8 &aDes)	
		{
		TBlockTransferData btd(aDevAddr,aLength,(TAny*)&aDes,aBlkLen,KBTDTypeMultipleBlocks);
		DoRequest(EReqReadBlk,aStatus,(TAny*)&btd);
		}
	inline void WriteMBlock(TRequestStatus &aStatus,TUint32 aDevAddr,TUint32 aLength,TUint32 aBlkLen,const TDesC8 &aDes)	
		{
		TBlockTransferData btd(aDevAddr,aLength,(TAny*)&aDes,aBlkLen,KBTDTypeMultipleBlocks);
		DoRequest(EReqWriteBlk,aStatus,(TAny*)&btd);
		}
	inline void EraseSector(TRequestStatus &aStatus,TUint32 aDevAddr,TUint32 aLength)	
		{DoRequest(EReqEraseSect,aStatus,(TAny*)aDevAddr,(TAny*)aLength);}
	inline void EraseGroup(TRequestStatus &aStatus,TUint32 aDevAddr,TUint32 aLength)	
		{DoRequest(EReqEraseGrp,aStatus,(TAny*)aDevAddr,(TAny*)aLength);}
	};
//
#endif
