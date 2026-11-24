// hal\inc\hal_int.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#ifndef __HAL_INT_H__
#define __HAL_INT_H__

#include <hal.h>
#include <e32svr.h>

/**
@publishedPartner


The signature for accessor functions for derived attributes
*/
typedef TInt (*THalImplementation)(TInt aDeviceNumber, TInt aAttrib, TBool aSet, TAny* aInOut);

/**
@internalComponent
*/
class HalInternal
	{
public:
	static const TUint8 Properties[HAL::ENumHalAttributes];
	static const TInt Offset[HAL::ENumHalAttributes];
	static const TInt InitialValue[HAL::ENumHalAttributes];
	static const THalImplementation Implementation[HAL::ENumHalAttributes];
	static const TInt HalDataSize;

	enum THalPanic
		{
		EReadOffsetInvalid=0,
		EWriteOffsetInvalid=1,
		EInitialAllocFailed1=2,
		EInitialAllocFailed2=3,
		EInitialWriteFailed=4,
		EInitialWriteFailed2=5,
		ETlsSizeInvalid=6,
		ENoSuchHalProp=7,
		EGetPropFailed=8,
		ESetPropFailed=9
		};

	static void Panic(THalPanic aPanic);
	static void InitialiseData();
	static TInt ReadWord(TInt anOffset);
	static TInt WriteWord(TInt anOffset, TInt aValue);
	};

#endif
