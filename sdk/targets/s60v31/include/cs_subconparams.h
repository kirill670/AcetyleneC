// cs_subconparams.h
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//
/** @file 
Header file for the Automated Test Tool
@publishedAll
@released
*/

#ifndef __CS_SUBCONPARAMS_H__
#define __CS_SUBCONPARAMS_H__

#include <e32base.h>
#include <e32std.h>
#include <MetaData.h>
#include <MetaType.h>

#include <es_sock.h>

const TInt32 KSubConnQosGenericParamsType = 1;
const TInt32 KSubConnAuthorisationGenericParamsType = 2;
using Meta::SMetaDataECom;

/** Qos generic parameter set.

@publishedAll
@released since v9.1 */
//SMetaDataECom must be the first in the superclasses' list
class CSubConQosGenericParamSet : public CSubConGenericParameterSet
{
public:
	inline static CSubConQosGenericParamSet* NewL(CSubConParameterFamily& aFamily, CSubConParameterFamily::TParameterSetType aType);
	inline static CSubConQosGenericParamSet* NewL();

	inline CSubConQosGenericParamSet();

	inline TInt GetDownlinkBandwidth() const;
	inline TInt GetUplinkBandwidth() const;
	inline TInt GetDownLinkMaximumBurstSize() const;
	inline TInt GetUpLinkMaximumBurstSize() const;
	inline TInt GetDownLinkAveragePacketSize() const;
	inline TInt GetUpLinkAveragePacketSize() const;
	inline TInt GetDownLinkMaximumPacketSize() const;
	inline TInt GetUpLinkMaximumPacketSize() const;
	inline TInt GetDownLinkDelay() const;
	inline TInt GetUpLinkDelay() const;
	inline TInt GetDownLinkDelayVariation() const;
	inline TInt GetUpLinkDelayVariation() const;
	inline TInt GetDownLinkPriority() const;
	inline TInt GetUpLinkPriority() const;
	inline TBool GetHeaderMode() const;
	inline const TName& GetName() const;

	inline void SetDownlinkBandwidth(TInt);
	inline void SetUplinkBandwidth(TInt);
	inline void SetDownLinkMaximumBurstSize(TInt);
	inline void SetUpLinkMaximumBurstSize(TInt);
	inline void SetDownLinkAveragePacketSize(TInt);
	inline void SetUpLinkAveragePacketSize(TInt);
	inline void SetDownLinkMaximumPacketSize(TInt);
	inline void SetUpLinkMaximumPacketSize(TInt);
	inline void SetDownLinkDelay(TInt);
	inline void SetUpLinkDelay(TInt);
	inline void SetDownLinkDelayVariation(TInt);
	inline void SetUpLinkDelayVariation(TInt);
	inline void SetDownLinkPriority(TInt);
	inline void SetUpLinkPriority(TInt);
	inline void SetHeaderMode(TBool);
	inline void SetName(const TName&);

protected:

	DATA_VTABLE

	TInt iDownlinkBandwidth;
	TInt iUplinkBandwidth;
	TInt iDownLinkMaximumBurstSize;
	TInt iUpLinkMaximumBurstSize;
	TInt iDownLinkAveragePacketSize;
	TInt iUpLinkAveragePacketSize;
	TInt iDownLinkMaximumPacketSize;
	TInt iUpLinkMaximumPacketSize;
	TInt iDownLinkDelay;
	TInt iUpLinkDelay;
	TInt iDownLinkDelayVariation;
	TInt iUpLinkDelayVariation;
	TInt iDownLinkPriority;
	TInt iUpLinkPriority;
	TBool iHeaderMode;
	TName iName;
	};

/** Authorisation generic parameter set.

@publishedAll
@released since v9.1 */
//SMetaDataECom must be the first in the superclasses' list
class CSubConAuthorisationGenericParamSet : public CSubConGenericParameterSet
{
public:
	inline static CSubConAuthorisationGenericParamSet* NewL(CSubConParameterFamily& aFamily, CSubConParameterFamily::TParameterSetType aType);
	inline static CSubConAuthorisationGenericParamSet* NewL();

	inline CSubConAuthorisationGenericParamSet();

	inline TInt GetId() const;

	inline void SetId(TInt);

protected:

	DATA_VTABLE

	TInt iId;
	};

/** Sub connection generic parameter set factory.

@internalComponent
@released since v9.1 */
class CSubConGenericParamsFactory : public CBase
	{
public:
	static CSubConGenericParameterSet* NewL(TAny* aConstructionParameters);
	};

#include <cs_subconparams.inl>
// __CS_SUBCONPARAMS_H__
#endif
