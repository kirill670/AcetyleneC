// cs_subconevents.inl
//
// Copyright (c) Symbian Software Ltd. 2004.
//

/**
@file
@publishedAll
*/

#ifndef __CS_SUBCONEVENTS_INL__
#define __CS_SUBCONEVENTS_INL__


CSubConGenEventParamsGranted* CSubConGenEventParamsGranted::NewL()
	{
	STypeId typeId(KSubConnGenericEventsImplUid, KSubConGenericEventParamsGranted);
	return static_cast<CSubConGenEventParamsGranted*>(CSubConNotificationEvent::NewL(typeId));
	}

CSubConGenEventParamsGranted::CSubConGenEventParamsGranted()
	: CSubConNotificationEvent(), iFamily(KSubConGlobalFamily), iGenericSet(NULL)
	{
	}

const CSubConGenericParameterSet* const CSubConGenEventParamsGranted::GetGenericSet() const
	{
	return iGenericSet;
	}

void CSubConGenEventParamsGranted::SetGenericSet(CSubConGenericParameterSet* aGenericSet)
	{
	if (iGenericSet != NULL)
		{
		delete iGenericSet;
		}
	iGenericSet = aGenericSet;
	}

const CSubConExtensionParameterSet* const CSubConGenEventParamsGranted::GetExtensionSet(TUint aIndex) const
	{
	return static_cast<CSubConExtensionParameterSet*>(iExtensionSets[aIndex]);
	}

void CSubConGenEventParamsGranted::AddExtensionSetL(CSubConExtensionParameterSet* aExtensionSet)
	{
	iExtensionSets.AppendL(aExtensionSet);
	}

TInt CSubConGenEventParamsGranted::GetNumExtensionSets()
	{
	return iExtensionSets.Count();
	}

TUint32 CSubConGenEventParamsGranted::GetFamily() const
	{
	return iFamily;
	}

void CSubConGenEventParamsGranted::SetFamily(TUint32 aFamily)
	{
	iFamily = aFamily;
	}

//====================================
CSubConGenEventParamsChanged* CSubConGenEventParamsChanged::NewL()
	{
	STypeId typeId(KSubConnGenericEventsImplUid, KSubConGenericEventParamsChanged);
	return static_cast<CSubConGenEventParamsChanged*>(CSubConNotificationEvent::NewL(typeId));
	}

CSubConGenEventParamsChanged::CSubConGenEventParamsChanged()
	: CSubConGenEventParamsGranted()
	{
	}

TInt CSubConGenEventParamsChanged::Error() const
	{
	return iError;
	}

void CSubConGenEventParamsChanged::SetError(TInt aError)
	{
	iError = aError;
	}

//====================================
CSubConGenEventParamsRejected* CSubConGenEventParamsRejected::NewL()
	{
	STypeId typeId(KSubConnGenericEventsImplUid, KSubConGenericEventParamsRejected);
	return static_cast<CSubConGenEventParamsRejected*>(CSubConNotificationEvent::NewL(typeId));
	}

CSubConGenEventParamsRejected::CSubConGenEventParamsRejected()
	: CSubConNotificationEvent()
	{
	}

TInt CSubConGenEventParamsRejected::Error() const
	{
	return iError;
	}

void CSubConGenEventParamsRejected::SetError(TInt aError)
	{
	iError = aError;
	}

TInt CSubConGenEventParamsRejected::FamilyId() const
	{
	return iFamilyId;
	}

void CSubConGenEventParamsRejected::SetFamilyId(TInt aFamilyId)
	{
	iFamilyId = aFamilyId;
	}	
	
//====================================
CSubConGenEventDataClientBase::CSubConGenEventDataClientBase()
	: CSubConNotificationEvent()
	{
	}

TUint CSubConGenEventDataClientBase::GetIap() const
	{
	return iIap;
	}

void CSubConGenEventDataClientBase::SetIap(TUint aIap)
	{
	iIap = aIap;
	}

const TSockAddr& CSubConGenEventDataClientBase::GetSourceAdress() const
	{
	return iSourceAddress;
	}

void CSubConGenEventDataClientBase::SetSourceAddress(const TSockAddr& aSourceAddress)
	{
	iSourceAddress = aSourceAddress;
	}

const TSockAddr& CSubConGenEventDataClientBase::GetDestAdress() const
	{
	return iDestAddress;
	}

void CSubConGenEventDataClientBase::SetDestAddress(const TSockAddr& aDestAddress)
	{
	iDestAddress = aDestAddress;
	}

//====================================
CSubConGenEventDataClientJoined* CSubConGenEventDataClientJoined::NewL()
	{
	STypeId typeId(KSubConnGenericEventsImplUid, KSubConGenericEventDataClientJoined);
	return static_cast<CSubConGenEventDataClientJoined*>(CSubConNotificationEvent::NewL(typeId));
	}

CSubConGenEventDataClientJoined::CSubConGenEventDataClientJoined()
	: CSubConGenEventDataClientBase()
	{
	}

//=====================================
CSubConGenEventDataClientLeft* CSubConGenEventDataClientLeft::NewL()
	{
	STypeId typeId(KSubConnGenericEventsImplUid, KSubConGenericEventDataClientLeft);
	return static_cast<CSubConGenEventDataClientLeft*>(CSubConNotificationEvent::NewL(typeId));
	}

CSubConGenEventDataClientLeft::CSubConGenEventDataClientLeft()
	: CSubConGenEventDataClientBase()
	{
	}

//====================================
CSubConGenEventSubConDown* CSubConGenEventSubConDown::NewL()
	{
	STypeId typeId(KSubConnGenericEventsImplUid, KSubConGenericEventSubConDown);
	return static_cast<CSubConGenEventSubConDown*>(CSubConNotificationEvent::NewL(typeId));
	}

CSubConGenEventSubConDown::CSubConGenEventSubConDown()
	: CSubConNotificationEvent()
	{
	}

TInt CSubConGenEventSubConDown::Error() const
	{
	return iError;
	}

void CSubConGenEventSubConDown::SetError(TInt aError)
	{
	iError = aError;
	}

// __CS_SUBCONEVENTS_INL__
#endif
