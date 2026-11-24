// ETEL.INL
//
// Copyright (c) Symbian Software Ltd. 1997-2004.  All rights reserved.
//
/**
@file
*/
inline TVersion RTelServer::Version() const
/** Gets the version number of the ETel server.
	
@return The server version and build numbers.
@publishedAll
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
@publishedAll
@released
*/
	{ 
	return *iTelSession;
	}

inline void RTelSubSessionBase::SetSessionHandle(RSessionBase& aTelSession)
/**
@publishedAll
@released
*/
	{ 
	iTelSession=&aTelSession;
	}

inline TInt RTelSubSessionBase::SubSessionHandle()
/**
@publishedAll
@released
*/
	{
	return(RSubSessionBase::SubSessionHandle());
	}
