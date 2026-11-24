// cs_subconparams.inl
//
// Copyright (c) Symbian Software Ltd. 2004.
//

/**
@file
@publishedAll
*/

#ifndef __CS_SUBCONPARAMS_INL__
#define __CS_SUBCONPARAMS_INL__

CSubConQosGenericParamSet* CSubConQosGenericParamSet::NewL(CSubConParameterFamily& aFamily, CSubConParameterFamily::TParameterSetType aType)
	{
	CSubConQosGenericParamSet* obj = NewL();
	CleanupStack::PushL(obj);
	aFamily.SetGenericSetL(*obj, aType);
	CleanupStack::Pop(obj);
	return obj;
	}

CSubConQosGenericParamSet* CSubConQosGenericParamSet::NewL()
	{
	STypeId typeId(KSubConnGenericParamsImplUid, KSubConnQosGenericParamsType);
	return static_cast<CSubConQosGenericParamSet*>(CSubConParameterSet::NewL(typeId));
	}

CSubConQosGenericParamSet::CSubConQosGenericParamSet()
	: CSubConGenericParameterSet(),
	iDownlinkBandwidth(0),
	iUplinkBandwidth(0),
	iDownLinkMaximumBurstSize(0),
	iUpLinkMaximumBurstSize(0),
	iDownLinkAveragePacketSize(0),
	iUpLinkAveragePacketSize(0),
	iDownLinkMaximumPacketSize(0),
	iUpLinkMaximumPacketSize(0),
	iDownLinkDelay(0),
	iUpLinkDelay(0),
	iDownLinkDelayVariation(0),
	iUpLinkDelayVariation(0),
	iDownLinkPriority(0),
	iUpLinkPriority(0),
	iHeaderMode(EFalse)
	{
	}

TInt CSubConQosGenericParamSet::GetDownlinkBandwidth() const
	{
	return iDownlinkBandwidth;
	}

TInt CSubConQosGenericParamSet::GetUplinkBandwidth() const
	{
	return iUplinkBandwidth;
	}

TInt CSubConQosGenericParamSet::GetDownLinkMaximumBurstSize() const
	{
	return iDownLinkMaximumBurstSize;
	}

TInt CSubConQosGenericParamSet::GetUpLinkMaximumBurstSize() const
	{
	return iUpLinkMaximumBurstSize;
	}

TInt CSubConQosGenericParamSet::GetDownLinkAveragePacketSize() const
	{
	return iDownLinkAveragePacketSize;
	}

TInt CSubConQosGenericParamSet::GetUpLinkAveragePacketSize() const
	{
	return iUpLinkAveragePacketSize;
	}

TInt CSubConQosGenericParamSet::GetDownLinkMaximumPacketSize() const
	{
	return iDownLinkMaximumPacketSize;
	}

TInt CSubConQosGenericParamSet::GetUpLinkMaximumPacketSize() const
	{
	return iUpLinkMaximumPacketSize;
	}

TInt CSubConQosGenericParamSet::GetDownLinkDelay() const
	{
	return iDownLinkDelay;
	}

TInt CSubConQosGenericParamSet::GetUpLinkDelay() const
	{
	return iUpLinkDelay;
	}

TInt CSubConQosGenericParamSet::GetDownLinkDelayVariation() const
	{
	return iDownLinkDelayVariation;
	}

TInt CSubConQosGenericParamSet::GetUpLinkDelayVariation() const
	{
	return iUpLinkDelayVariation;
	}

TInt CSubConQosGenericParamSet::GetDownLinkPriority() const
	{
	return iDownLinkPriority;
	}

TInt CSubConQosGenericParamSet::GetUpLinkPriority() const
	{
	return iUpLinkPriority;
	}

TBool CSubConQosGenericParamSet::GetHeaderMode() const
	{
	return iHeaderMode;
	}

const TName& CSubConQosGenericParamSet::GetName() const
	{
	return iName;
	}

void CSubConQosGenericParamSet::SetDownlinkBandwidth(TInt aDownlinkBandwidth)
	{
	iDownlinkBandwidth = aDownlinkBandwidth;
	}

void CSubConQosGenericParamSet::SetUplinkBandwidth(TInt aUplinkBandwidth)
	{
	iUplinkBandwidth = aUplinkBandwidth;
	}

void CSubConQosGenericParamSet::SetDownLinkMaximumBurstSize(TInt aDownLinkMaximumBurstSize)
	{
	iDownLinkMaximumBurstSize = aDownLinkMaximumBurstSize;
	}

void CSubConQosGenericParamSet::SetUpLinkMaximumBurstSize(TInt aUpLinkMaximumBurstSize)
	{
	iUpLinkMaximumBurstSize = aUpLinkMaximumBurstSize;
	}

void CSubConQosGenericParamSet::SetDownLinkAveragePacketSize(TInt aDownLinkAveragePacketSize)
	{
	iDownLinkAveragePacketSize = aDownLinkAveragePacketSize;
	}

void CSubConQosGenericParamSet::SetUpLinkAveragePacketSize(TInt aUpLinkAveragePacketSize)
	{
	iUpLinkAveragePacketSize = aUpLinkAveragePacketSize;
	}

void CSubConQosGenericParamSet::SetDownLinkMaximumPacketSize(TInt aDownLinkMaximumPacketSize)
	{
	iDownLinkMaximumPacketSize = aDownLinkMaximumPacketSize;
	}

void CSubConQosGenericParamSet::SetUpLinkMaximumPacketSize(TInt aUpLinkMaximumPacketSize)
	{
	iUpLinkMaximumPacketSize = aUpLinkMaximumPacketSize;
	}

void CSubConQosGenericParamSet::SetDownLinkDelay(TInt aDownLinkDelay)
	{
	iDownLinkDelay = aDownLinkDelay;
	}

void CSubConQosGenericParamSet::SetUpLinkDelay(TInt aUpLinkDelay)
	{
	iUpLinkDelay = aUpLinkDelay;
	}

void CSubConQosGenericParamSet::SetDownLinkDelayVariation(TInt aDownLinkDelayVariation)
	{
	iDownLinkDelayVariation = aDownLinkDelayVariation;
	}

void CSubConQosGenericParamSet::SetUpLinkDelayVariation(TInt aUpLinkDelayVariation)
	{
	iUpLinkDelayVariation = aUpLinkDelayVariation;
	}

void CSubConQosGenericParamSet::SetDownLinkPriority(TInt aDownLinkPriority)
	{
	iDownLinkPriority = aDownLinkPriority;
	}

void CSubConQosGenericParamSet::SetUpLinkPriority(TInt aUpLinkPriority)
	{
	iUpLinkPriority = aUpLinkPriority;
	}

void CSubConQosGenericParamSet::SetHeaderMode(TBool aHeaderMode)
	{
	iHeaderMode = aHeaderMode;
	}

void CSubConQosGenericParamSet::SetName(const TName& aName)
	{
	iName = aName;
	}

//=============
CSubConAuthorisationGenericParamSet* CSubConAuthorisationGenericParamSet::NewL(CSubConParameterFamily& aFamily, CSubConParameterFamily::TParameterSetType aType)
	{
	CSubConAuthorisationGenericParamSet* obj = NewL();
	CleanupStack::PushL(obj);
	aFamily.SetGenericSetL(*obj, aType);
	CleanupStack::Pop(obj);
	return obj;
	}

CSubConAuthorisationGenericParamSet* CSubConAuthorisationGenericParamSet::NewL()
	{
	STypeId typeId(KSubConnGenericParamsImplUid, KSubConnAuthorisationGenericParamsType);
	return static_cast<CSubConAuthorisationGenericParamSet*>(CSubConParameterSet::NewL(typeId));
	}

CSubConAuthorisationGenericParamSet::CSubConAuthorisationGenericParamSet()
	: CSubConGenericParameterSet(), 
	iId(0)
	{
	}

TInt CSubConAuthorisationGenericParamSet::GetId() const
	{
	return iId;
	}

void CSubConAuthorisationGenericParamSet::SetId(TInt aId)
	{
	iId = aId;
	}
// __CS_SUBCONPARAMS_INL__
#endif
