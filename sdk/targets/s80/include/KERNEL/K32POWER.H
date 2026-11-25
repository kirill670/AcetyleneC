// K32POWER.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __K32POWER_H__
#define __K32POWER_H__

#include <e32base.h>
#include <e32svr.h>

const TUint KPowerUserCpu=0x80000000u;

enum TPowerState
	{
	EPoweredDown,
	EDoingPowerUp,
	EDoingPowerDown,
	EPoweredUp
	};

class DPowerHandler : public CBase
	{
public:
	IMPORT_C TInt SetRequirement(TUint32 aState);
	IMPORT_C void SetCurrentConsumptionInMilliAmps(TInt aValue);
	IMPORT_C TBool PowerGood();
	IMPORT_C TInt PowerOn();
	IMPORT_C void PowerStandby();
	IMPORT_C void PowerEmergencyStandby();
	inline   void PowerTransition(TUint32 aNewState);
protected:
	virtual TInt DoPowerOn() =0;
	virtual void DoPowerStandby() =0;
	virtual void DoPowerEmergencyStandby() =0;
	virtual void DoPowerTransition(TUint32 /*aNewState*/) {};
	IMPORT_C ~DPowerHandler();
public:
	TDblQueLink iLink;
	TPowerState iState;
	TUint32 iRequirement;
	TInt iCurrentConsumptionInMilliAmps;
	};

/**
 * DPowerModel class
 */
class DPowerModel : public CBase
	{
public:
	IMPORT_C DPowerModel();
	IMPORT_C virtual TInt PowerOn();
	IMPORT_C virtual TInt PowerStandby();
	IMPORT_C virtual void PowerEmergencyStandby();
	IMPORT_C virtual void NotifyEvent(const TRawEvent &aEvent);
	//
	void PowerEmergencyStandbyDfc();
protected:
	virtual TInt DoPowerOn() =0;
	virtual void DoPowerStandby() =0;
	virtual void DoPowerStandby(const TTimeIntervalSeconds& aWakeUp) =0;
	virtual void DoPowerEmergencyStandby() =0;
	virtual TInt DoPowerTransition(TUint32 aState) =0;
private:
	TInt PowerTransition(TUint32 aState);
	TUint32 GetPowerRequirement();
	TInt AddPowerHandler(DPowerHandler &aHandler);
	void RemovePowerHandler(DPowerHandler &aHandler);
	friend class DPowerHandler;
	friend class Power;
	TInt iLock;
public:
	TInt iCurrentConsumptionInMilliAmps;
	TUint32 iPowerRequirement;
	TDblQue<DPowerHandler> iPowerHandlers;
	};

class Power
	{
public:
	IMPORT_C static void SwitchOn();						// user switch on, send ESwitchOn event
	IMPORT_C static void SwitchOn(const TRawEvent &aEvent);	// user switch on with specific event
	static void SwitchOff();								// user switch off, UserHal::SwitchOff()
	static TInt PowerOn();									// kernel power on

	IMPORT_C static void SetPowerModel(const DPowerModel *aModel);
	IMPORT_C static TInt AddPowerHandler(DPowerHandler &aHandler);
	IMPORT_C static void RemovePowerHandler(DPowerHandler &aHandler);
	//
	IMPORT_C static void LockPowerState();
	IMPORT_C static void UnlockPowerState();
	};

inline void DPowerHandler::PowerTransition(TUint32 aNewState)
	{ DoPowerTransition(aNewState); }

#endif
