/**
@file ES_MBMAN.H

Buffer Manager for Protocols

Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
*/

#ifndef __ES_MBMAN_H__
#define __ES_MBMAN_H__

#if !defined(__ES_MBUF_H__)
# include <es_mbuf.h>
#endif


/**
MBuf Private Heap Limits

@internalTechnology
*/
const TUint KMBufMinHeapSize	    = 4 * 1024;
const TUint KMBufMaxHeapSize		= 16 * 1024 * 1024;
const TUint KMBufDefaultHeapSize	= 256 * 1024;

class CMBufPool;
class CMBufManager;

#define ALIGN_MASK    0x03
#define ALIGN_UP(n)   (((n)+(ALIGN_MASK)) & ~ALIGN_MASK)
#define ALIGN_DOWN(n) ((n) & ~ALIGN_MASK)
#define IS_ALIGNED(p) ((((TUint32)(p)) & ALIGN_MASK)==0)

////////////////////////////////////////////////////////////////////////////////
// MBUF MANAGER
////////////////////////////////////////////////////////////////////////////////

/**
@internalTechnology
*/
const TUint KMBufWatchDogTime = 1000000;
const TInt KMBufFreePriority = 20;

class Nif;
class CRequestAsyncAlloc;
class CMBufManager : public CBase
	{
friend class Nif;
friend class CRequestAsyncAlloc;
private:
	CMBufManager();
public:
	IMPORT_C ~CMBufManager();
 	IMPORT_C static CMBufManager *NewL(TInt aHeapSize = KMBufDefaultHeapSize);
 	IMPORT_C void CreateL(TInt aMaxMBufs);
	IMPORT_C RMBuf* AllocL(TInt aSize = KMBufSmallSize);
	IMPORT_C void Free(RMBuf* aChain);
	IMPORT_C static void Panic(TMBufPanic aPanic);
	void StartRequest(RMBufAsyncRequest& aRequest);
	void CancelRequest(RMBufAsyncRequest& aRequest);
	static RHeap& Heap();

	static CDeltaTimer* GetTimer();

	// Used to reference the single process-wide MBufManager from different threads+DLLs
	// Don't try to inline these - if TLS is in use then they need to be in this DLL
	IMPORT_C static CMBufManager* Context(); // Panics if no context!
	// A new thread/DLL needs to call this when the TLS handling is in use, ie in the
	// thread startup function, having obtained a pointer to the CMBufManager somehow 
	// (eg caller passed in). Consider it as the thread/dll introducing itself to the 
	// MBufMgr. "Pleased to meet you..."
	IMPORT_C void SetContext();

private:
	void MergePool(CMBufPool *aPool);
	void WatchDogReset();
//	void WatchDogCancel();
	static TInt WatchDogExpire(TAny* aPtr);
	static TInt FreeCallBack(TAny* aPtr);
	void CompleteSmallRequests();
	void CompleteLargeRequests();
//
private:
	RHeap* iHeap;
	TInt iNumSmallBufs;
	TInt iNumSmallFree;
	TInt iSmallBufSpace;
	TInt iSmallBufTotal;
	RCriticalSection iLock;
	TDblQue<CMBufPool> iPools;
	RMBufQ iSmallBufs;
	TDblQue<RMBufAsyncRequest> iAllocsPending;
	CDeltaTimer* iTimer;					// The global delta timer.
	TThreadId iTimerThreadId;
	TDeltaTimerEntry iWatchDog;
	TBool iWatchDogIsPending;
	CAsyncCallBack *iFreeCB;
	CRequestAsyncAlloc* iRequestAsyncAlloc;
//
public:
	IMPORT_C static void __DbgCheckChain(RMBuf* aChain, TMBufType aType, TInt aLength, TInt aSize);
	IMPORT_C TInt __DbgCheckBuffer(RMBuf* aBuf);
	inline RMBuf* __DbgSmallBufChain() { return iSmallBufs.First(); } 
	inline void __DbgSetPoolLimit(TInt aCount=0) { __iPoolLimit = aCount - (aCount%KMBufSmallSize); }
	inline void __DbgSetFailAfter(TInt aCount=0) { __iFailAfter = aCount; }
	inline TInt __DbgGetBufSpace() { return iSmallBufSpace; }
	inline TInt __DbgGetBufTotal() { return iSmallBufTotal; }
private:
	TInt __iPoolLimit;	// Allows Max Size of pool to be set
	TInt __iFailAfter;	// Alloc Failure Request
	};

////////////////////////////////////////////////////////////////////////////////
// MBUF POOLS
////////////////////////////////////////////////////////////////////////////////


class CMBufPool : public CBase
/**
@internalTechnology
*/
	{
private:
	CMBufPool();
public:
	~CMBufPool();
	static CMBufPool *NewL(TInt aNumBufs);
	void CreateL(TInt aNumBufs);
	void Merge(RMBufQ &aMainPool);
	inline TInt Count();
	static TAny* operator new(TUint aSiz, TLeave aLeave, TUint aExtra);
	static void operator delete(TAny* aPtr);
	static void operator delete(TAny* aPtr, TLeave aLeave, TUint aExtra);
//
private:
	friend class CMBufManager;  // for access to iLink
	TDblQueLink iLink;
	RMBufQ iList;		// List of mbufs in this pool
	TInt iCount;		// Number of mbufs in this pool
	TUint8 *iPool;		// Allocated memory
//
public:
	IMPORT_C TInt __DbgCheckBuffer(RMBuf* aBuf);
	};

////////////////////////////////////////////////////////////////////////////////
// MBUF TIMER
////////////////////////////////////////////////////////////////////////////////
class MBufTimer 
	{
public:
	IMPORT_C static void Queue(TTimeIntervalMicroSeconds32 aTimeInMicroSeconds,TDeltaTimerEntry& aTimer);
	IMPORT_C static void Remove(TDeltaTimerEntry& aTimer);
	};

const TInt KMbufManTimerGranularity = 15500;

enum TMBufMgrActivePriority
	{
	EMBufMgrTimerPriority=50,
	};

#include "es_mbman.inl"

#endif
