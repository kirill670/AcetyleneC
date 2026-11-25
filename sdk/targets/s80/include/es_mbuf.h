/**
@file ES_MBUF.H

Buffer Manager for Protocols

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
*/

#if !defined(__ES_MBUF_H__)
#define __ES_MBUF_H__

#include <e32base.h>

#ifdef _DEBUG
// Include special test code
# define _MBUF_TEST
// Enables Alloc/Free sanity checks
#define _MBUF_CHECKS
#endif


////////////////////////////////////////////////////////////////////////////////
// General class Cleanup stack support

#define __DECLARE_CLEANUP \
	public: inline operator TCleanupItem() { return TCleanupItem(__Cleanup,this); } \
	private: IMPORT_C static void __Cleanup(TAny *aPtr);

/**
General class Cleanup stack support
*/
#define __IMPLEMENT_CLEANUP(Class, Function) \
	EXPORT_C void Class::__Cleanup(TAny *aPtr) { ((Class*)aPtr)->Function(); }

/**
Small MBufs
*/
const TInt KMBufSmallSize = 128;

// MBuf Manager Error codes - using ESock range
const TInt KErrNoMBufs = -17200;

// iType field of an MBuf
enum TMBufType
	{
	EMBufFree, EMBufData, EMBufHeader
	};

/**
MBuf Manager Panics

@internalComponent
*/
enum TMBufPanic
	{
	EMBuf_NoHeap = 0,
	EMBuf_CheckFailSize = 1,
	EMBuf_CheckFailType = 2,
	EMBuf_CheckFailLength = 3,
	EMBuf_VCPPFault = 4,
	EMBuf_AlreadyInit = 5,
	EMBuf_NoManager = 6,
	EMBuf_BadBufferSize = 7,
	EMBuf_AllreadyAlloc = 8,
	EMBuf_AllreadyFree = 9,
	EMBuf_NegativeLength = 10,
	EMBuf_NegativeOffset = 11,
	EMBuf_BadOffset = 12,
	EMBuf_EmptyChain = 13,
	EMBuf_NotAligned = 14,
	EMBuf_CircularRef = 15,
	EMBuf_SillyAlloc = 16,
	EMBuf_PrematureDestruct = 17,
	EMBuf_BadNewInPlace = 18,
	EMBuf_NotEmptyChain = 19,
	EMBuf_IllegalAlign = 20,
	EMBuf_NotAnMBuf = 21,
	EMBuf_CorruptMBuf = 22,
	EMBuf_NoHeader = 23,
	EMBuf_TooBig = 24,
	EMBuf_AlreadyActive = 25
	};

/**
Constant to indicate as much as possible, or whole chain
@internalComponent
*/
const TInt KMBufAll = KMaxTInt;

// Request Flags to MBuf Alloc
const TUint KMBufNormal   = 0x00;	// Wait	and dont zero-fill
const TUint KMBufZeroFill = 0x01;	// Zero fill allocated mbufs
const TUint KMBufDontWait = 0x02;	// Prevent pool alloc if no mbufs

const TInt KMBufMaxAllocSize = 0x10000;  // Just to keep things sensible

class RMBuf;
class TMBufIter;
class RMBufChain;
class RMBufQ;
class RMBufPktQ;
class TMBufPktQIter;

/**
MBUF CHAIN

@internalComponent
*/
#define MBUF_TODATA(chain, type) \
	(chain.Align(sizeof(type)), (type *)chain.First()->Ptr())

class RMBufChain
/**
@publishedPartner
@released
*/
	{
	__DECLARE_CLEANUP
public:
	inline RMBufChain();
	inline RMBufChain(RMBuf* aChain);
	//
	inline void Init();
	inline TBool IsEmpty() const;
	inline RMBufChain& Next();
	inline const RMBufChain& Next() const;
	inline void Link(RMBufChain &aChain);
	inline void Unlink();
	inline RMBuf* First();
	inline const RMBuf* First() const;
	IMPORT_C RMBuf* Last() const;
	inline RMBufChain &operator =(RMBuf* aChain);
	//
	IMPORT_C RMBuf* Remove();
	IMPORT_C void Assign(RMBufQ &aQueue);
	IMPORT_C void Assign(RMBufChain &aChain);
	IMPORT_C void Append(RMBufChain &aChain);
	IMPORT_C void AppendL(TInt aLen);
	IMPORT_C void PrependL(TInt aLen);
	IMPORT_C void Prepend(RMBuf* aBuf);
	IMPORT_C void Prepend(RMBufChain &aChain);
	IMPORT_C void AllocL(TInt aLen = 0);
	IMPORT_C void ReAllocL(TInt aLen);
	IMPORT_C void CreateL(const TDesC8& aDes, TInt aHdrLen=0);
 	IMPORT_C void SplitL(TInt anOffset, RMBufChain &newChain);
	IMPORT_C TInt Align(TInt aSize);
	IMPORT_C void Free();
	IMPORT_C void FillZ(TInt aLen=KMBufAll);
	IMPORT_C void CopyL(RMBufChain &newChain, TInt aOffset=0, TInt aLen=KMBufAll) const;
 	IMPORT_C void CopyIn(const TDesC8 &aDes, TInt aOffset=0);
	IMPORT_C void CopyOut(TDes8 &aDes, TInt aOffset=0) const;
	IMPORT_C void TrimStart(TInt nBytes);
	IMPORT_C void TrimEnd(TInt anOffset);
	IMPORT_C TBool Goto(TInt anOffset, RMBuf* &resBuf, TInt &resOffset, TInt &resLength, RMBuf* &resPrevBuf) const;
	inline TBool Goto(TInt anOffset, RMBuf* &resBuf, TInt &resOffset, TInt &resLength) const;
	IMPORT_C TInt NumBufs() const;
	IMPORT_C TInt Length() const;
protected:
	RMBuf* iNext;
	};


class RMBuf
/**
MBUF
@publishedPartner
@released
*/
	{
	friend class CMBufManager;
	friend class CMBufPool;
public:
	IMPORT_C void Init(TMBufType aType);
	IMPORT_C RMBuf* Last();
	//
	IMPORT_C static RMBuf* AllocL();
	IMPORT_C void Free();
	inline void FillZ();
	//
	inline TUint8 *Buffer();
	inline TUint8 *Ptr();
	inline TUint8 *EndPtr();
	inline RMBuf* Next();
	inline RMBufChain& NextPkt();

	inline TInt Size() const;
	inline TInt Offset() const;
	inline TInt Length() const;
	inline TInt End() const;
	inline TMBufType Type() const;

	inline const TUint8 *Buffer() const;
	inline const TUint8 *Ptr() const;
	inline const TUint8 *EndPtr() const;
	inline const RMBuf* Next() const;
	inline const RMBufChain& NextPkt() const;
	//
	inline void Link(RMBuf* aBuf);
	inline void Unlink();
	inline void LinkPkt(RMBufChain &aChain);
	inline void UnlinkPkt();
	inline void SetType(TMBufType aType);
	inline void SetOffset(TInt aOffset);
	inline void SetLength(TInt aLength);
	inline void SetData(TInt aOffset, TInt aLength);
	inline void AdjustStart(TInt aLen);
	inline void AdjustEnd(TInt aLen);

	inline void Put(TUint8 aVal, TInt aOffset=0);
	inline TUint8 Get(TInt aOffset=0) const;

private:
	TAny *operator new(TUint aSize, RMBuf* aPtr);
	void operator delete(TAny *aPtr);
	void operator delete(TAny *aPtr, RMBuf*);
	RMBuf(TUint8 *aBuffer, TInt aSize);
// Forbidden ops
	RMBuf();
	RMBuf(const RMBuf &);
	RMBuf& operator=(const RMBuf &);
//
private:
	RMBuf* iNext;
	RMBufChain iNextPkt;	
	TInt iOffset;
	TInt iLength;
	TMBufType iType;
	const TInt iSize;
	TUint8* const iBuffer;
//
private:
	IMPORT_C void __DbgPut(TUint8 aVal, TInt aOffset=0);
	IMPORT_C TUint8 __DbgGet(TInt aOffset=0) const;
	};


class TMBufIter
/**
MBUF ITERATOR
@publishedPartner
@released
*/
	{
public:
	TMBufIter();
	inline TMBufIter(RMBuf* aChain);
	inline TMBufIter(RMBufChain &aChain);
	inline TMBufIter& operator =(RMBuf* aChain);
	inline TMBufIter& operator =(RMBufChain &aChain);
	inline RMBuf* operator++(TInt);
	inline operator RMBuf* ();
	inline TBool More();
	inline RMBuf* MBuf();
	//
protected:
	RMBuf* iCurrent;
	};



class RMBufQ
/**
MBUF QUEUE
@publishedPartner
@released
*/
	{
friend class CMBufManager;
	__DECLARE_CLEANUP
public:
	inline RMBufQ();
	IMPORT_C RMBufQ(RMBuf* aChain);
	inline RMBufQ(RMBuf* aFirst, RMBuf* aLast);
	inline TBool IsEmpty();
	inline RMBuf* First();
	inline RMBuf* Last();
	IMPORT_C void Init();
	IMPORT_C void Assign(RMBufQ &aQueue);
	IMPORT_C void Assign(RMBufChain &aChain);
	IMPORT_C void Append(RMBuf* aBuf);
	IMPORT_C void Append(RMBufQ &aQueue);
	IMPORT_C void Append(RMBufChain &aChain);
	IMPORT_C void Prepend(RMBuf* aBuf);
	IMPORT_C void Prepend(RMBufQ &aQueue);
	IMPORT_C void Prepend(RMBufChain &aChain);
	IMPORT_C RMBuf* Remove();
	IMPORT_C void Free();
//
protected:
	RMBuf* iNext;
	RMBuf* iLast;

private:
	TInt Transfer(RMBufQ& aQueue, TInt aSize);
	};

class RMBufPktQ
/**
MBUF PACKET QUEUE
@publishedPartner
@released
*/
	{
	__DECLARE_CLEANUP
public:
	inline TBool IsEmpty() const;
	inline const RMBufChain& First() const;
	inline const RMBufChain& Last() const;
	IMPORT_C void Init();
	IMPORT_C void Assign(RMBufPktQ &aQueue);
	IMPORT_C void Free();
	IMPORT_C TBool Remove(RMBufChain &aChain);
	IMPORT_C void Append(RMBufChain &aChain);
	IMPORT_C void Append(RMBufPktQ &aQueue);
	IMPORT_C void Prepend(RMBufChain& aChain);
private:
	friend class TMBufPktQIter;
	void Insert(RMBufChain& aNew, RMBufChain& aPrev);
	void Remove(RMBufChain& aNew, RMBufChain& aPrev);
	//
protected:
	RMBufChain iNext;
	RMBufChain iLast;
	};

class TMBufPktQIter
/**
MBUF PACKET QUEUE ITERATOR
@publishedPartner
@released
*/
	{
public:
	inline TMBufPktQIter(RMBufPktQ& aQueue);
	inline void Set(RMBufPktQ& aQueue);
	inline void SetToFirst();
	inline TBool More() const;
	inline const RMBufChain& Current() const;
	IMPORT_C const RMBufChain& operator++(TInt);
	IMPORT_C void Insert(RMBufChain& aNewChain);
	IMPORT_C void Remove(RMBufChain& aNewChain);
	IMPORT_C void TidyAfterUpdate();
	//
protected:
	// Must be regarded as a const chain, hence the const API
	RMBufChain iPrev;
	RMBufPktQ* iQueue;
	RMBufChain iCurrent;
	};

class CMBufAsyncReq;
class RMBufAsyncRequest
/**
ASYNC ALLOCATOR SUPPORT
@publishedPartner
@released
*/
	{
	friend class CMBufAsyncReq;
	friend class CMBufManager;
public:
	IMPORT_C RMBufAsyncRequest();
	IMPORT_C ~RMBufAsyncRequest();
	IMPORT_C void Alloc(RMBufChain& aChain, TInt aLength, TRequestStatus& aStatus);
	IMPORT_C void Cancel();
protected:
	void Complete(TInt aCode);
protected:
	TInt iLength;
	RMBufQ iMBufs;
	RMBufChain* iChain;
	TRequestStatus* iStatusPtr;
	RThread iThread;
	TDblQueLink iLink;
	};

#include "es_mbuf.inl"

#endif
