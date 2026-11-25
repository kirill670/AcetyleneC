/**
@file ES_PROT.INL

Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
*/

inline void CServProviderBase::SetNotify(MSocketNotify * aSocket)
/**
Set notification for transport services to a single protocol

@param aSocket, notify the socket server that various events have occurred
*/
	{ iSocket=aSocket; }

inline TInt CProtocolBase::RefCount() const
/**
Reference counting by protocols created by protocol families.

@return number of protocols
*/
	{ return iRefCount; }

inline void CResolverProvdBase::SetNotify(MResolverNotify * aNotifier)
	{ iNotify=aNotifier; }

