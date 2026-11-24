// cs_subconevents.h
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//
/** @file 
Header file for the Automated Test Tool
@publishedAll
@released
*/

#ifndef __CS_SUBCONEVENTS_H__
#define __CS_SUBCONEVENTS_H__
#include <e32base.h>
#include <e32std.h>
#include <MetaData.h>
#include <MetaType.h>

#include <es_sock.h>
using Meta::RMetaDataEComContainer;

const TUint32 KSubConGenericEventParamsGranted      =  0x1;
const TUint32 KSubConGenericEventDataClientJoined   =  0x2;
const TUint32 KSubConGenericEventDataClientLeft     =  0x4;
const TUint32 KSubConGenericEventSubConDown         =  0x8;
const TUint32 KSubConGenericEventParamsChanged      = 0x10;
const TUint32 KSubConGenericEventParamsRejected     = 0x20;


/** Subconnection parameters granted event.

@publishedAll
@released since v9.1 */
class CSubConGenEventParamsGranted : public CSubConNotificationEvent
{
public:
	inline static CSubConGenEventParamsGranted* NewL();

	inline CSubConGenEventParamsGranted();

	inline const CSubConGenericParameterSet* const GetGenericSet() const;
	inline void SetGenericSet(CSubConGenericParameterSet* aGenericSet);

	inline const CSubConExtensionParameterSet* const GetExtensionSet(TUint aIndex) const;
	inline void AddExtensionSetL(CSubConExtensionParameterSet* aExtensionSet);
	inline TInt GetNumExtensionSets();

	inline TUint32 GetFamily() const;
	inline void SetFamily(TUint32 aFamily);

	virtual ~CSubConGenEventParamsGranted();

protected:
	DATA_VTABLE

	TUint32 iFamily;
	CSubConGenericParameterSet* iGenericSet;
	RMetaDataEComContainer iExtensionSets;
	};

/** Subconnection parameters changed event.

@publishedAll
@released since v9.1 */
class CSubConGenEventParamsChanged : public CSubConGenEventParamsGranted
	{
public:
	inline static CSubConGenEventParamsChanged* NewL();

	inline CSubConGenEventParamsChanged();

	inline TInt Error() const;
	inline void SetError(TInt aError);

	virtual ~CSubConGenEventParamsChanged();

protected:
	DATA_VTABLE

	TInt iError;
	};

/** Subconnection parameters rejected event.

@publishedAll
@released since v9.1 */
class CSubConGenEventParamsRejected : public CSubConNotificationEvent
	{
public:
	inline static CSubConGenEventParamsRejected* NewL();

	inline CSubConGenEventParamsRejected();

	inline TInt Error() const;
	inline void SetError(TInt aError);
	inline TInt FamilyId() const;
	inline void SetFamilyId ( TInt aFamilyId );

	virtual ~CSubConGenEventParamsRejected();

protected:
	DATA_VTABLE

	TInt iError;
	TInt iFamilyId;
	};

/** Data client event base.

@internalComponent
@released since v9.1 */
class CSubConGenEventDataClientBase : public CSubConNotificationEvent
	{
public:
	inline CSubConGenEventDataClientBase();
	inline TUint GetIap() const;
	inline void SetIap(TUint aIap);

	inline const TSockAddr& GetSourceAdress() const;
	inline void SetSourceAddress(const TSockAddr& aSourceAddress);

	inline const TSockAddr& GetDestAdress() const;
	inline void SetDestAddress(const TSockAddr& aDestAddress);

	virtual ~CSubConGenEventDataClientBase();

protected:
	DATA_VTABLE

	TSockAddr iSourceAddress;
	TSockAddr iDestAddress;
	TUint	  iIap;
	};

/** Data client joined event.

@publishedAll
@released since v9.1 */
class CSubConGenEventDataClientJoined : public CSubConGenEventDataClientBase
	{
public:
	inline static CSubConGenEventDataClientJoined* NewL();

	inline CSubConGenEventDataClientJoined();
	virtual ~CSubConGenEventDataClientJoined();

protected:
	DATA_VTABLE
	};

/** Data client left event.

@publishedAll
@released since v9.1 */
class CSubConGenEventDataClientLeft : public CSubConGenEventDataClientBase 
{
public:
	inline static CSubConGenEventDataClientLeft* NewL();

	inline CSubConGenEventDataClientLeft();

	virtual ~CSubConGenEventDataClientLeft();

protected:
	DATA_VTABLE
	};

/** Subconnection down event.

@publishedAll
@released since v9.1 */
class CSubConGenEventSubConDown : public CSubConNotificationEvent
{
public:
	inline static CSubConGenEventSubConDown* NewL();

	inline CSubConGenEventSubConDown();

	inline TInt Error() const;
	inline void SetError(TInt aError);

	virtual ~CSubConGenEventSubConDown();

protected:
	DATA_VTABLE

	TInt iError;
	};

/** Sub connection generic event factory.

@internalComponent
@released since v9.1 */
class CSubConGenEventsFactory : public CBase
	{
public:
	static CSubConNotificationEvent* NewL(TAny* aConstructionParameters);
	};

#include <cs_subconevents.inl>
// __CS_SUBCONEVENTS_H__
#endif
