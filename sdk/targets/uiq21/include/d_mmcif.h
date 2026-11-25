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
//
enum TMmcMediaType {EMmcROM,EMmcFlash,EMmcIO,EMmcOther,EMmcNotSupported};
//
const TInt KMaxCardsPerStack=2;
const TInt KSectorSizeInBytes=512;
const TInt KSectorSizeShift=9;
const TInt KDrvBufSizeInSectors=8;
const TInt KDrvBufSizeInBytes=(KDrvBufSizeInSectors<<KSectorSizeShift); // 4K
//
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
	};
//
class TMmcCSDInfo
	{
public:
	inline TMmcCSDInfo()
		  {Mem::FillZ(this,sizeof(TMmcCSDInfo));}
public:	
	TUint iReadBlLen;
	TUint iWriteBlLen;
	TBool iReadBlPartial;
	TBool iWriteBlPartial;
	TBool iReadBlkMisalign;
	TBool iWriteBlkMisalign;    
	TUint iSpecVers;
	TUint iTAAC;
	TUint iNSAC;
	TUint iTransferSpeed;
	TUint iCommandRegister;
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
		EReqWriteBlk=0x1,EReqWriteBlkCancel=0x2
		};
	enum TControl
        {ESvReset,ESvPwrUp,ESvPwrDown,ESvRegisterEvent,ESvSelectCard,EExecStackInfo,
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
//	inline TInt StackInfo(TUint& aCardsPresentMask,TMMCStackConfig& aConfig) ???
//		{return(DoControl(EExecStackInfo,&aCardsPresentMask,&aConfig));}
	inline TInt StackInfo(TUint& aCardsPresentMask)
		{return(DoControl(EExecStackInfo,&aCardsPresentMask));}
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
	inline TInt RegisterEvent(TUint anEventMask,TRequestStatus *aReqStat)
		{return(DoSvControl(ESvRegisterEvent,(TAny*)anEventMask,(TAny*)aReqStat));}	
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
	};
//
#endif
