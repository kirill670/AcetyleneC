// Mda\Common\Base.h
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

// largely EMPTY - maintained for backwards compatibility

#ifndef __MDA_COMMON_BASE_H__
#define __MDA_COMMON_BASE_H__

/*
Notes:
Header file for information shared between client and server side
Contains UID definitions, function numbers
*/

// Standard EPOC32 includes
#include <e32base.h>
// Public Media Server includes
#include <Mda\Common\Base.hrh>

#ifdef ASSERT
#ifdef _DEBUG
#undef ASSERT

// Redefine assert to be a little more useful to us, i.e. to include file & line number
#define __ASSERT_FILE__(s) _LIT(KPanicFileName,s)
#define __ASSERT_PANIC__(l) User::Panic(KPanicFileName().Right(12),l)
#define ASSERT(x) { __ASSERT_FILE__(__FILE__); __ASSERT_DEBUG(x, __ASSERT_PANIC__(__LINE__) ); }
#endif
#endif

/**
 * @internalComponent
 *
 * Macro for producing different variants of Uids
 */
#define MDA_UID(uid_name)	const TUint uid_name##Value = uid_name##Define; \
							const TUid uid_name = {uid_name##Value};

// Uids
#if defined(UNICODE)

/**
 * @publishedAll
 * @deprecated 
 */
const TInt KUidMediaServerLibraryValue = KUidMediaServerLibraryUnicodeDefine;
#else

/**
 * @publishedAll
 * @deprecated 
 */
const TInt KUidMediaServerLibraryValue = KUidMediaServerLibraryDefine;
#endif

/**
 * @publishedAll
 * @deprecated 
 */
const TUid KUidMediaServerLibrary = {KUidMediaServerLibraryValue};

MDA_UID(KUidMdaTimerFactory)

/** 
 * @publishedAll
 * @deprecated 
 *
 * Default number of message slots
 */
const TInt KMdaServerDefaultMessageSlots=-1;	// Use global pool for messages

/** 
 * @publishedAll
 * @deprecated 
 *
 * Unknown value
 */
const TInt KMdaUnknown = -1;

// Package classes


class TMdaRawPackage
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	inline TPtr8& Package();
	inline const TPtr8& Package() const;
protected:
	TMdaRawPackage(TInt aDerivedSize);
	inline void SetSize(TInt aDerivedSize);
protected:
	TPtr8 iThis;
	friend class RDummyMdaObject;
	};


class TMdaOpenPackage : public TMdaRawPackage
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	inline void SetHandleAddress(TPckgBuf<TInt>* aHandle);
	inline TPckgBuf<TInt>* GetHandleAddress() const;
	inline TMdaOpenPackage(TInt aDerivedSize);
private:
	TPckgBuf<TInt>* iHandle;
	};


class TMdaPackage : public TMdaRawPackage
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	inline TUid Type() const;
	inline TUid Uid() const;
	inline void SetUid(TUid aUid);
	inline TBool operator==(const TMdaPackage& aPackage); // Type&Uid comparison
protected:
	inline TMdaPackage(TUid aType, TUid aUid, TInt aDerivedSize);
private:
	TUid iType;
	TUid iUid;
	};


class TMdaReturnPackage : public TMdaPackage
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	inline TInt ReturnSize() const;
protected:
	inline TMdaReturnPackage(TUid aType, TUid aUid, TInt aDerivedSize);
	inline void SetReturnSize(TInt aReturnSize);
private:
	TInt iRetSize;
	friend class RDummyMdaObject;
	};


class TMdaEvent
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	TInt32 iId;
	TInt32 iArg[3];
	};


class TMdaObjectEvent
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	TInt iHandle;
	TMdaEvent iEvent;
	};


class TMdaEventPackage : public TMdaRawPackage
/** 
 *  
 * @publishedAll
 * @deprecated
 */
	{
public:
	inline TMdaEventPackage(); // For single events
	//
	inline TInt EventCount() const;
	inline TInt MaxEvents() const;
	inline const TMdaEvent& Event(); // First event only
	inline const TMdaEvent& Event(TInt aIndex);
	inline TInt EventFrom(); // first event only
	inline TInt EventFrom(TInt aIndex);
protected:
	inline TMdaEventPackage(TInt aMaxEvents);
protected:
	TInt iMaxEvents;
	TInt iValidEvents;
	TMdaObjectEvent iFirstEvent;
	};

#include <Mda\Common\Base.inl>

#include <mmf\common\mmfbase.h>

#endif
