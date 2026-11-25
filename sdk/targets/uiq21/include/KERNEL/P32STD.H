// P32STD.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __P32STD_H__
#define __P32STD_H__

#include <e32std.h>
#include <e32base.h>

enum TPBusControllerType {EPBusCntrlNone,EPBusCntrlPcCard,EPBusCntrlMultiMedia,EPBusCntrlUSB};
//const TInt KMaxPBusSockets=4;  // Defined in E32STD.H
//
const TInt KMaxPEvents=4;
const TInt KMaxPEventsMinusOne=(KMaxPEvents-1);
const TInt KMultiplePEvent=01000000;
const TUint KPEventAllowMultiple=0x0000000F;
//
const TUint KPEventPwrDownEmergency=0x00000001;
const TUint KPEventPwrDownNormal=0x00000002;
const TUint KPEventPwrUp=0x00000004;
const TUint KPEventMediaChange=0x00000008;

enum TPBusPwrEvent {EPEventPwrDownEmergency,EPEventPwrDownNormal,EPEventPwrUp,EPEventMediaChange};
enum TPwrDownReason {EPwrDownMachine,EPwrDownEmergency,EPwrDownPsuFail,
	EPwrDownInactivity,EPwrDownNotInUse};
//
const TInt KInvalidPBusNum=(KMaxPBusSockets<<1);

class TPBusCallBack
	{
public:
	inline TPBusCallBack(CBase *anOwner,const TCallBack &aCallBack);
	inline TPBusCallBack(CBase *anOwner,const TCallBack &aCallBack,TUint anEventMask);
	IMPORT_C TInt Enable();
	IMPORT_C TInt Disable();
	IMPORT_C TInt Clear();
	TInt CallBack(TInt aReason,TInt anInfo);
	inline TInt CallBackReason();
	inline TInt CallBackInfo();
    inline void SetEventMask(TUint anEventMask);
protected: 
	TSglQueLink iLink;
	CBase* iOwner;
    TUint iEventMask;
	TCallBack iCallBack;
	TInt iCallBackReason;
	TInt iCallBackInfo;
	TPBusNum iBus;
	TInt iSglEvent;
	DPeriphBusController* iController;
    friend class TPBusEventArrayBase;
	};
//
class TPBusEventArrayBase
    {
public:
	TPBusEventArrayBase();
	TInt Add(TPBusCallBack &aCallBack,DPeriphBusController* aController,TPBusNum aBus,TInt anEventNum);
	TBool Remove(CBase *aClientID);
	void CallBack(TInt aReason,TInt anInfo);
	void CallBack(TUint anEventMask,TInt aReason,TInt anInfo);
	TInt ContainsOtherClients(CBase *aClientID);
	static TInt VerifyEventMask(TPBusCallBack& aCallBack);
	inline TBool IsEmpty() {return(iCallBacks.IsEmpty());}
	inline static void SetMaxEventMask(TUint aMaxEventMask) {MaxEventMask=aMaxEventMask;}
private:
	TSglQue<TPBusCallBack> iCallBacks;
    static TUint MaxEventMask;
    };
//
class DPeriphBusPowerHandler;
class TPBusPsuBase;
class TMediaChangeBase;
class DPeriphBusController : public CBase
	{
public:
	virtual void CreateL();
    virtual TPBusControllerType ControllerType()=0;
	virtual void PowerUpBus(TPBusNum aBus,DThread *aThread,TRequestStatus *aReqStat)=0;
	virtual TInt RegisterPowerNotification(TPBusNum aBus,TPBusCallBack& aCallBack,TUint aFlag=0)=0;
	virtual void DeregisterPowerNotification(TPBusNum aBus,CBase* aClientID,TPBusCallBack* aCallBack=NULL)=0;
	virtual TInt SetPowerEvent(TPBusNum aBus,TPBusPwrEvent anEvent,TInt anInfo=0)=0;
	virtual TInt DeregisterClient(CBase *aClientID)=0;
	virtual TInt DeviceIsReady(TPBusNum aBus)=0;
	virtual TInt TotalSupportedBuses()=0;
	virtual TPBusNum BaseBusNumber()=0;
	virtual TInt ForceMediaChange(TPBusNum aBus);
	virtual TInt PrepareStore(TPBusNum aBus,TPBusPasswordFunc aFunc,TPBusPasswordData& aPasswordData,DThread* aThread);
	virtual TInt ReadPasswordData(TDes8 &aBuf);
	virtual TInt WritePasswordData(TDesC8 &aBuf);
	virtual TInt PasswordStoreLengthInBytes();
	static DPeriphBusController* NewL();
    inline DPeriphBusPowerHandler& PowerHandler();
protected:
	virtual void DoCreateL()=0;
    virtual TInt PowerOn()=0;
    virtual void PowerStandby()=0;
    virtual void PowerEmergencyStandby()=0;
	virtual TInt EnableEvent(TPBusNum aBus,TInt anEvent)=0;
	virtual TInt DisableEvent(TPBusNum aBus,CBase *aClientID,TInt anEvent)=0;
	virtual TInt ClearEvent(TPBusNum aBus,TInt anEvent)=0;
	virtual TMediaChangeBase *MediaChange(TPBusNum aBus)=0;
	virtual TPBusPsuBase *PrimaryPsu(TPBusNum aBus)=0;
private:
    DPeriphBusPowerHandler* iPowerHandler;
    friend class DPeriphBusPowerHandler;
    friend class TPBusCallBack;
	};
//
class DPeriphBusPowerHandler : public DPowerHandler
	{
public:
	DPeriphBusPowerHandler(DPeriphBusController* aBusController) : iBusController(aBusController) {}
	virtual TInt DoPowerOn() { return(iBusController->PowerOn()); }
	virtual void DoPowerStandby() { iBusController->PowerStandby(); }
	virtual void DoPowerEmergencyStandby() { iBusController->PowerEmergencyStandby(); }
public:
	DPeriphBusController *iBusController;
	};
//
class DPBusMediaDriver : public DMediaDriver
	{
public:
	IMPORT_C DPBusMediaDriver();
	IMPORT_C ~DPBusMediaDriver();
	IMPORT_C virtual TInt DoCreate(TMediaDevice aMediaDevice,const TDesC* anInfo);
	IMPORT_C virtual TInt Enlarge(TInt aLength);
	IMPORT_C virtual TInt ReduceSize(TInt64 &aPos,TInt aLength);
protected:
	TPBusNum iSocket;
	DPeriphBusController* iController;
	};
//
enum TPBusPsuState {EPsuOff,EPsuOnCurLimit,EPsuOnFull};
enum TPBusPsuStatus {EPsuStatOff,EPsuStatOn,EPsuStatError};
const TInt KPBusPsuTickInterval=1000000;		// Units 1uS
//
const TUint KPsuChkWhileOn=0x00000001;	
const TUint KPsuChkOnPwrUp=0x00000002;	
enum TPsuVoltChkMethod {EPsuChkComparator,EPsuChkADCType1,EPsuChkADCType2};
class TPBusPsuInfo
	{
public:
	TUint iVoltageSupported;
	TInt iMaxCurrentInMicroAmps;
	TUint iVoltCheckInterval;
	TPsuVoltChkMethod iVoltCheckMethod;
    TInt iNotLockedTimeOut;
    TInt iInactivityTimeOut;
	};
//
class TPBusPsuBase
	{
public:
	enum TResetMode {ENormalAndRestorable,EQuickButRestorable,EQuickAndNotRestorable};
public:
	TPBusPsuBase(TInt aPsuNum);
    virtual void Init();
	TInt SetState(TPBusPsuState aState);
	TPBusPsuStatus Status();
	TInt CheckVoltage(TUint aCheckStatus);
	void Reset();
    virtual TInt ResetEvent(TPBusPwrEvent anEvent, TInt anInfo, TResetMode aMode); 
	virtual TBool IsLocked();
	virtual void DoSetState(TPBusPsuState aState)=0;
	virtual TInt VoltageInMilliVolts()=0;
	inline TUint VoltageSupported();
	inline void SetCurrLimited();
	inline TBool IsOff();
	inline TInt MaxCurrentInMicroAmps();
protected:
	inline void ResetInactivityTimer();
    virtual void DoTickService();
private:		  
	void PwrDownCheck();
	virtual TInt DoCheckVoltage()=0;
    virtual void PsuInfo(TPBusPsuInfo &anInfo)=0;
    static void Tick(TAny *aPtr,TInt);
protected:		  
	TInt iPsuNum;
	TPsuVoltChkMethod iVoltCheckMethod;
private:
	TPBusPsuState iState;
	TBool iCurrLimited; 
	TTickLink iTickLink;
	TUint iVoltageSupported;
	TInt iMaxCurrentInMicroAmps;
	TUint iVoltCheckInterval;
	TInt iInactivityCount;
	TInt iNotLockedCount;
    TInt iInactivityTimeout;
    TInt iNotLockedTimeout;
	};
//
class TMediaChangeBase
	{
public:
	TMediaChangeBase(TInt aMediaChangeNum);
	virtual TMediaState MediaState()=0;
	TInt Postpone(CBase *aClientID);
	void PostponeEnd(CBase *aClientID);
	inline TBool IsPostponed();
	inline TBool IsPostponed(CBase *aClientID);
	inline TInt Number();
	virtual void DoorOpenService(); // ???
protected:
	void DoorClosedService();
private:
	virtual void MediaChangeEvent(TPBusPwrEvent anEvent)=0;
	virtual void DoDoorOpen()=0;
	virtual void DoDoorClosed()=0;
protected:
	TInt iMediaChangeNum;
private:
	TBool iPostponedAMediaChange;
	TBool iPostponed;
	CBase *iPostponeClientID;
	friend class DPeriphBusController;
	};

#include <p32std.inl>

#endif

