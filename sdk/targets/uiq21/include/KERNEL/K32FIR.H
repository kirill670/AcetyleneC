// K32Fir.H
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

// Kernel side header for Fast IR device driver
#if !defined(__FASTIR_H__)
#define __FASTIR_H__

#include <k32std.h>
#include <k32power.h>
#include <k32comm.h>
#include <m32std.h>
#include <m32hal.h>
#include <D32Fir.h>

const TInt KFirMajorVersion=1;
const TInt KFirMinorVersion=0;
const TInt KFirBuildVersion=1;

const TInt KMaxXferSz      =2052;	//bytes
const TInt KMaxSzFrameStore=8;		//Irda window size is 8 - so shouldn't need to hold more(except - VFIR!!)
const TInt KDmaBufferSz    =12288;	//size in bytes of dma buffers
const TUint32 KRoundMask   =0xfffffffc;

enum TFirStopMode {EFirStopNormal,EFirStopPwrDown,EFirStopEmergency};
enum TXferType{EWriteXfer,EReadXfer};
//
// Template LDD factory
//
class DFirLogDevice : public DLogicalDevice
      {
public:
      DFirLogDevice();
//override pure virtual
      virtual TInt Install();
      virtual void GetCaps(TDes8& aDes) const;
      virtual DLogicalChannel* CreateL();
      };

class DFirPhysDevice : public DPhysicalDevice
	{
public:
	DFirPhysDevice();
	virtual TInt Install();
	virtual TInt Remove();
	virtual void GetCaps(TDes8 &aDes) const;
	virtual CBase *CreateL(TInt aUnit,const TDesC *anInfo,const TVersion &aVer);
	};

/**********************Dma Buffers*********************************/

class DFirPhysChannel;//forward declaration
class TFrame
	{
public:
	TFrame(TInt aStartPos=0,TInt aFrameSize=0,TInt aErrorCode=0);
	TInt iStartPos;
	TInt iFrameSize;
	TInt iErrorCode;
	};

class TDmaBuf//Handicapped Circular Buffer
	{
public:
	TDmaBuf();
	void SetDriver(DFirPhysChannel* aDriver);
	void Init(TUint8* aBase,TInt aSize);

	void Flush();
	void SetActive();
	void SetInActive();
	TBool IsActive();
	TBool IsCancelled();
	TBool IsEnoughSpace(TInt aSize);
	TInt NoFrames();

protected:
	void AdvanceTail(TInt aSize);
	void AdvanceHead();

	DFirPhysChannel* iDriver;
	TInt iNoFrames;
	TInt iInsertPt;
	TInt iRemovePt;
	TInt iHead;
	TInt iTail;

	TBool iOpCancelled;
	TBool iActive;
	TFrame iFrameStore[KMaxSzFrameStore];

	TUint8* iBufBasePtr;//Linear address of start of HwChunk
	TInt iBufSz;
	};

class TDmaRxBuf : public TDmaBuf
	{
public:
	TBool IsReaderEmpty();
	void ReadXferComplete(TInt aNoBytesRecv,TInt aErrorCode);
	TInt CopyFrameToClient(DThread* aThread,TAny* aRxPtr,TInt aRxLength);
	TInt GetNextXfer(TFrame& aFrame);
	void CancelFrame();
	};

class TDmaTxBuf : public TDmaBuf
	{
public:
	TInt StoreFrame(DThread* aThread,TAny* aTxPtr, TInt aTxLength);
	TInt RemoveFrame();
	TInt GetNextXfer(TFrame& aFrame);
	};

/********************Phys Driver********************************/

//Physical Driver
class DLddFirChannel;//forward declaration
class DFirPhysChannel : public CBase
	{
public:
	virtual TInt CreateStorageL(TInt aBytes)=0;
	virtual TInt SetUpWrite(TFrame* aFrame)=0;
	virtual TInt SetUpRead(TFrame* aFrame)=0;
	virtual TInt DisableIrqs()=0;
	virtual void RestoreIrqs(TInt)=0;

	virtual TUint8* GetReadChunkBase()=0;
	virtual TUint8* GetWriteChunkBase()=0;
	virtual void TurnOffPort()=0;
	virtual void CancelXfer(TInt xferType)=0;
	virtual void Stop(TFirStopMode aMode)=0;

	virtual TInt Configure(TFirConfigV01 &aConfig)=0;
	virtual TInt Validate(const TFirConfigV01 &aConfig) const =0;
	virtual void GetCaps(TDes8 &aDes) const =0;
	virtual void CompleteXfer(TInt xferType,TInt err) =0;
	virtual TUint32 PowerRequirement()=0;

	inline virtual TInt SetIrRange(TUint aRange);
	inline void SetComm(DLddFirChannel *aLDD);
	inline void SetCurrent(TInt aCurrent);
public:
	DLddFirChannel* iLDD;
	};

/*********************Logical Driver********************************/

class DFirPowerHandler : public DPowerHandler
	{
public:
	DFirPowerHandler(DLddFirChannel *aLdd);
	virtual TInt DoPowerOn();
	virtual void DoPowerStandby();
	virtual void DoPowerEmergencyStandby();

	void RequestComplete();
	void RequestPending();
	static void Timeout(TAny *, TInt);
public:
	DLddFirChannel *iLdd;
	TTickLink iTimer;
	};

class DLddFirChannel : public DLogicalChannel
      {
public:
	enum TReqOpts{EWriteReq=0,EReadReq=1,ETimerReq=2};

      DLddFirChannel(DLogicalDevice* aLogicalDevice);
	  ~DLddFirChannel();
	  virtual void CompleteIt(TInt aXfer,TInt aError,TInt aReq);

	  virtual void DoPowerUp();
	  virtual void DoPowerDown();
	  virtual void DoEmergencyPowerDown();
	  inline void SetCurrentConsumptionInMilliAmps(TInt aValue);
//protected:
//override pure virtual
      virtual void DoCancel(TInt aReqNo);
      virtual void DoRequest(TInt aReqNo,TAny* a1,TAny* a2);

      virtual void DoCreateL(TInt aUnit,CBase* aPdd,const TDesC* anInfo,const TVersion& aVer);
      virtual TInt DoControl(TInt aFunction,TAny* a1,TAny* a2);
private:
	  void TryToStartWrite();
	  void TryToStartRead();

	  static TInt TxCompleteDfc(TAny* aDLddFirChannel);
	  static TInt RxCompleteDfc(TAny* aDLddFirChannel);
	  static TInt EmergencyCompleteDfc(TAny* aDLddFirChannel);
	  inline void AddTxDfc() { Kern::Add(iTxCompleteDfc); }
	  inline void AddRxDfc() { Kern::Add(iRxCompleteDfc); }
	  inline void AddEmergencyDfc() { Kern::Add(iEmergencyCompleteDfc); }
	  TInt DoTxComplete();
	  TInt DoRxComplete();
	  TInt DoEmergencyComplete();

	  TFirConfigV01 iConfig;
	  DFirPhysChannel*  iDriver;
	  DFirPowerHandler* iPowerHandler;
	  TDmaRxBuf    iRxBuf;
	  TDmaTxBuf    iTxBuf;

	  TDfc	iTxCompleteDfc;
	  TDfc	iRxCompleteDfc;
	  TDfc  iEmergencyCompleteDfc;

	  TInt	iRxPendingLen;
	  TAny*	iRxPendingPtr;
	  TBool iClientReadPending;
	  TBool iClientWritePending;

	  TInt iError;
	  friend class DFirPowerHandler;
      };

#include <K32Fir.inl>

#endif	// __FASTIR_H__


