// POSSOCK.H
// Written by JP, June 1999
// Copyright (c) 1994-1999 Symbian Ltd. All rights reserved.
//

#if !defined __POSSOCK_H__
#define __POSSOCK_H__

#include <sys/types.h>
#include <es_sock.h>

const TInt KPosixSocketServerDefaultMessageSlots=4;

class TUSockAddr : public TSockAddr
	{
public:
	TUSockAddr() : TSockAddr() {}
	TUSockAddr(TAny* addr);
	TUSockAddr(TAny* addr, TUint len);
	void Prepare(TAny* addr);
	void Set(TAny* addr, TUint len);
	void Get(TAny* addr, unsigned long* len);
	};

struct TPosixParams
	{
	TPosixParams() : ptr(NULL,0) {};
	int fid;
	int intVal[3];
	TPtr8 ptr;
	TUSockAddr addr;
	};

IMPORT_C TInt StartPosixSocketServer();

extern "C"
{

IMPORT_C void WriteLog(const char* aFileName,const char* aString);
IMPORT_C void PossockFreeTls();

}

class RPosSockSession : public RSessionBase
	{
public:
	IMPORT_C TInt Connect(TInt aMessageSlots=KPosixSocketServerDefaultMessageSlots);
	IMPORT_C TVersion Version() const;
public:
	IMPORT_C TInt socket(TInt family, TInt style, TInt protocol);
	IMPORT_C TInt close(TInt aFid);
	IMPORT_C TInt getsockname(TInt aFid, struct sockaddr* anAddr, size_t* aSize);
	IMPORT_C TInt recvfrom(TInt aFid, char* aBuf, size_t aCnt, int aFlags, struct sockaddr* aFrom, size_t* aFromSize);
	IMPORT_C TInt sendto(TInt aFid, const char* aBuf, size_t aBufLen, TInt aFlags, struct sockaddr* aTo, size_t aTosize);
	IMPORT_C TInt bind(TInt aFid, struct sockaddr* anAddr, size_t aSize);
	IMPORT_C TInt select(TInt /*nfds*/,fd_set* readfds,fd_set* /*writefds*/,fd_set* /*errorfds*/,struct timeval* timeout);
	IMPORT_C TInt select(fd_set* readfds,struct timeval* timeout);
	IMPORT_C TInt shutdown(TInt aFid, TInt aHow);
private:
	TInt Request(TInt aFunction);
private:	
	TPosixParams iParams;
	};

#endif
