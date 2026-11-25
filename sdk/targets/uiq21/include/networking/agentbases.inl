// AGENTBASES.inl
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Inline functions for Base classes in States and State Machines

#if !defined(__AGENTBASES_INL__)
#define __AGENTBASES_INL__

inline TBool CAgentSMBase::IsReconnect() const
	{return iIsReconnect;}

inline TBool CAgentSMBase::CallBack() const
	{return iCallBack;}

#endif