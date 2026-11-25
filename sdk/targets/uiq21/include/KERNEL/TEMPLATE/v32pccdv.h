// V32PCCDV.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __V32PCCDV_H__
#define __V32PCCDV_H__
#include <p32pccd.h>

class TPcCardControllerArmPlatInterface
	{
public:
	IMPORT_C TInt Create();
    // The Controller itself
	virtual TUint32 MemPhysicalAddress(TInt aCard,TPccdMemType aType)=0;
	virtual TInt Init()=0;
	virtual TInt Indicators(TInt aCard,TSocketIndicators &anInd)=0;
	virtual void InterfaceOn(TInt aCard)=0;
	virtual void InterfaceOff(TInt aCard)=0;
    virtual void CardReset(TInt aCard,TBool anAssert)=0;
    virtual TBool CardReady(TInt aCard)=0;
	virtual TInt MemConfig(TInt aCard,TPccdMemType aMemType,TPccdAccessSpeed aSpeed,TBool aWaitSig,TUint aFlag)=0;
    virtual void SocketInfo(TSocket aSocket,TPcCardSocketInfo& anInfo)=0;
	virtual const TDesC8& SocketIntSource(TSocket aSocket,TPccdEvent anEvent)=0;
	virtual void InitSocketInt(TSocket aSocket,TPccdEvent anEvent)=0;
	virtual void ClearSocketInt(TSocket aSocket,TPccdEvent anEvent)=0;
	virtual void PeriphBusMachineInfo(TDes8* anInfo)=0;
	virtual TInt MediaChangeFromPeriphBus(TPBusNum aBus)=0;
	virtual TInt MediaChangeFromPrimaryPsu(TInt aPsuNum)=0;
    // Pc Card PSUs
	virtual void VccInfo(TInt aPsu,TPBusPsuInfo &aninfo)=0;
    virtual void VccOff(TInt aPsu)=0;
    virtual void VccOnFull(TInt aPsu,TPccdSocketVcc aVoltageSetting)=0;
    virtual void VccOnCurrentLimit(TInt aPsu,TPccdSocketVcc aVoltageSetting)=0;
    virtual TInt VccInMilliVolts(TInt aPsu)=0;
	virtual TInt VccVoltCheck(TInt aPsu)=0;
	virtual TInt VccSupplyFromSocket(TSocket aSocket)=0;
	// Pc Card MediaChange
	virtual TPtrC8 MediaChangeIntSource(TInt aMediaChange)=0;
	virtual void ClearMediaChangeInt(TInt aMediaChange)=0;
	virtual TMediaState MediaState(TInt aMediaChange)=0;
    };

#endif
