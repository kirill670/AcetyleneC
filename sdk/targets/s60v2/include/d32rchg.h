// D32RCHG.H
//
// Copyright (c) Symbian Software Ltd 1996-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

#ifndef __D32RCHG_H__
#define __D32RCHG_H__
#include <e32std.h>

enum TChargeType
	{
	EChargeNone,
	EChargeFast,
	EChargeTrickle
	};
//

class TChargeInfoV1
    {
public:
    TUint iRawTemperature;
    TUint iTemperatureTicks;
    TUint iSmoothedTemperature;
    TUint iPreviousTemperature;
    TUint iVoltage;
    TUint iReferenceVoltage;
    TChargeType iChargeType;
    TBool iBatteryPack;
    };

typedef TPckgBuf<TChargeInfoV1> TChargeInfoV1Buf;

//
class RDevRecharger : public RBusLogicalChannel
	{
public:
	enum TRequest
		{
		ERequestDummy
		};
	enum TControl
		{
		EGetChargeType,
		ESetChargeType,
		EGetChargeInfo
		};
public:
	inline TInt Open(TInt aUnit=KNullUnit);
	inline TInt ChargeType(TInt& aChargeType);
	inline TInt SetChargeType(TInt aChargeType);
	inline TInt ChargeInfo(TDes8& aChargeInfo);
	};
//
#include <d32rchg.inl>
#endif

