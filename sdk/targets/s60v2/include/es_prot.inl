/**
@file ES_PROT.INL

Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
*/

#ifndef SYMBIAN_NETWORKING_RSUBCONNECTION
inline void CServProviderBase::SetNotify(MSocketNotify * aSocket)
/**
Set notification for transport services to a single protocol

@param aSocket, notify the socket server that various events have occurred
*/
	{ iSocket=aSocket; }
#endif

inline TInt CProtocolBase::RefCount() const
/**
Reference counting by protocols created by protocol families.

@return number of protocols
*/
	{ return iRefCount; }

#ifdef SYMBIAN_NETWORKING_RSUBCONNECTION
inline CServProviderBase* CControlledServProviderShim::Provider()
	{
	return iProvider;
	}
#endif

inline void CResolverProvdBase::SetNotify(MResolverNotify * aNotifier)
	{ iNotify=aNotifier; }

