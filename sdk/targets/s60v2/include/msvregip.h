// MSVREGIP.H
//
// Copyright (c) Symbian Software Ltd 1998-2004.  All rights reserved.
//

#ifndef __MSVREGIP_H__
#define __MSVREGIP_H__

#include <e32base.h>

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__ // forcibly hide the API
#undef __SUPPORT_MESSAGING_API_V1__ // forcibly turn off support
#endif //  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif // __SUPPORT_MESSAGING_API_V1__


#ifdef __MESSAGING_API_V2__
class RWriteStream;
class RReadStream;
#endif // __MESSAGING_API_V2__

class CMtmGroupData;
class CRegisteredMtmDllArray;
class MRegisteredMtmDllObserver;

#ifndef __HIDE_MESSAGING_API_V1__

class RFs;


class TMsvPackedMtmGroupData
/**
@internalComponent
@released
*/
	{
public:
	IMPORT_C TMsvPackedMtmGroupData(HBufC8*& aBuffer);
	IMPORT_C TInt PackMtmGroupData(const CMtmGroupData& aMtmGroupData);
	IMPORT_C CMtmGroupData* UnpackMtmGroupDataL() const;
private:
	HBufC8*& iBuffer;
	};

#endif // __HIDE_MESSAGING_API_V1__

class TMsvPackedRegisteredMtmDllArray
/**
@internalComponent
@released
*/
	{
public:
#ifdef __MESSAGING_API_V2__
	IMPORT_C static void PackRegisteredMtmDllArrayL(RWriteStream& aWriteStream, const CRegisteredMtmDllArray& aRegisteredMtmDllArray);
	IMPORT_C static void UnpackRegisteredMtmDllArrayL(RReadStream& aReadStream, CRegisteredMtmDllArray& aRegisteredMtmDllArray, const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32, MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
#endif // __MESSAGING_API_V2__
#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C TMsvPackedRegisteredMtmDllArray(HBufC8*& aBuffer);
	IMPORT_C TInt PackRegisteredMtmDllArray(const CRegisteredMtmDllArray& aRegisteredMtmDllArray);
	IMPORT_C void UnpackRegisteredMtmDllArrayL(CRegisteredMtmDllArray& aRegisteredMtmDllArray,const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
private:
	void DoUnpackRegisteredMtmDllArrayL(CRegisteredMtmDllArray& aRegisteredMtmDllArray,const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
#endif // __HIDE_MESSAGING_API_V1__
#ifndef __REMOVE_MESSAGING_API_V1__
private:
	HBufC8*& iBuffer;
#endif // __REMOVE_MESSAGING_API_V1__
	};

#endif	// __MSVREGIP_H__
