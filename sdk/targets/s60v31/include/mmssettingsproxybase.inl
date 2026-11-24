// MMSSettingProxyBase.inl
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
// 
//
// Base MMS Settings Proxy

#include "mmssettingsproxybase.h"

CMMSSettingsProxyBase* CMMSSettingsProxyBase::NewL(TUid aInterfaceImplUid)
	{
	TAny* ptr = NULL;
	ptr = REComSession::CreateImplementationL(aInterfaceImplUid, _FOFF(CMMSSettingsProxyBase, iDtor_ID_Key));
	return REINTERPRET_CAST(CMMSSettingsProxyBase*, ptr);
	}

CMMSSettingsProxyBase::~CMMSSettingsProxyBase()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}
