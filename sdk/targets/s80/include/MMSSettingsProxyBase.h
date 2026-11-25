// MMSSettingProxyBase.h
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
// 
//
// Header file for base MMS Settings Proxy

#ifndef __MMSSETTINGSPROXYBASE_H__
#define __MMSSETTINGSPROXYBASE_H__

#include <e32base.h>
#include <ecom.h>
#include <msventry.h>

const TUid KMMSSettingsProxyBaseUid = {0x101F9421};

_LIT(KMMSUrl, "MMSUrl");
_LIT(KCommDbRecordId, "CommDbRecordId");
_LIT(KMsvServerEntry, "CMsvServerEntry");

class TMMSSettingsPair
/**
@publishedPartner
@released
*/
	{
public:
		TPtrC iName;
		TAny* iValue;
		TSglQueLink iLink;
	};

class CMMSSettingsProxyBase : public CBase
/**
@publishedPartner
@released
*/
{

public:
	// delegates construction to an ECom static method and casts return value to the correct type. 
	static CMMSSettingsProxyBase* NewL(TUid aInterfaceImplUid);	
	virtual ~CMMSSettingsProxyBase();
	virtual void SetMMSValuesL(TSglQue<TMMSSettingsPair>& aMMSSettingsList) = 0;

private:
	TUid iDtor_ID_Key;	// required for destruction identification within the ECom framework
};

#include "mmssettingsproxybase.inl"

#endif //__MMSSETTINGSPROXYBASE_H__
