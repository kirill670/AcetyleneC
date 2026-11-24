// ETEL.INL
//
// Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
//
/**
@file
*/
inline TVersion RTelServer::Version() const
/** Gets the version number of the ETel server.
	
@return The server version and build numbers.
@publishedPartner
@released
*/
	{
	return(TVersion(KEtelMajorVersionNumber,
					KEtelMinorVersionNumber,
					KEtelBuildVersionNumber));
	}

//
// RTelSubSessionBase
//
inline RSessionBase& RTelSubSessionBase::SessionHandle() const
/**
@publishedPartner
@released
*/
	{ 
	return *iTelSession;
	}

inline void RTelSubSessionBase::SetSessionHandle(RSessionBase& aTelSession)
/**
@publishedPartner
@released
*/
	{ 
	iTelSession=&aTelSession;
	}

inline TInt RTelSubSessionBase::SubSessionHandle()
/**
@publishedPartner
@released
*/
	{
	return(RSubSessionBase::SubSessionHandle());
	}
