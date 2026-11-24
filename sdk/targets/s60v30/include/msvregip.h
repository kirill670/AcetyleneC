// MSVREGIP.H
//
// Copyright (c) Symbian Software Ltd 1998-2004.  All rights reserved.
//

#ifndef __MSVREGIP_H__
#define __MSVREGIP_H__

#include <e32base.h>




class RWriteStream;
class RReadStream;

class CMtmGroupData;
class CRegisteredMtmDllArray;
class MRegisteredMtmDllObserver;


class TMsvPackedRegisteredMtmDllArray
/**
@internalComponent
@released
*/
	{
public:
	IMPORT_C static void PackRegisteredMtmDllArrayL(RWriteStream& aWriteStream, const CRegisteredMtmDllArray& aRegisteredMtmDllArray);
	IMPORT_C static void UnpackRegisteredMtmDllArrayL(RReadStream& aReadStream, CRegisteredMtmDllArray& aRegisteredMtmDllArray, const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32, MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
	};

#endif	// __MSVREGIP_H__
