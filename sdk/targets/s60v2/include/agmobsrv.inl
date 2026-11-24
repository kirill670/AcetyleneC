// AGMOBSRV.INL
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

inline CAgnObserver2* CAgnObserver2::NewL(TUid aImplementationUid)
	{
	TAny* ptr = REComSession::CreateImplementationL(aImplementationUid,
													_FOFF(CAgnObserver2,			
														  iDtor_ID_Key));
	return reinterpret_cast<CAgnObserver2*>(ptr);	
	}


inline CAgnObserver2::~CAgnObserver2()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);	
	}

