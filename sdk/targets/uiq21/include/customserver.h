// CUSTOMSERVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__CUSTOMSERVER_H__)
#define __CUSTOMSERVER_H__

#include <e32base.h>
#include <customservershared.h>

// Custom Server version info
const TUint KCustomServerMajorVer = 1;
const TUint KCustomServerMinorVer = 0;
const TUint KCustomServerBuildVer = 1;
const TUint8 KUnicodeCustomServerVersion = 16; // was unicodeplpversion
const TUint8 KNarrowCustomServerVersion = 6; // was eraplpversion
const TUint8 KMaxCustomServerVersion = 31;
//
enum TCustomServerErrorResult
    { 
    ECustomServerResultObjectFatal, ECustomServerResultObjectOk
    };

////////////////////////////////////////////////////////////////////////////////////////
//
//	TCustomServerServInfo
//
////////////////////////////////////////////////////////////////////////////////////////
class TCustomServerServInfo 
    {
public:
    TInt iDeleterPriority;
    TInt iReaderPriority;
    TInt iServerPriority;
    TInt iWriterPriority;
    TInt iMaxSessions;
    TInt iMaxPduSize;
    TPtrC8 iServerName;
    };


class CCustomServer;
////////////////////////////////////////////////////////////////////////////////////////
//
//	MCustomServerManager
//
////////////////////////////////////////////////////////////////////////////////////////
class MCustomServerManager
    {
public:
    virtual void AddToServerList(CCustomServer &aServer)=0;
    virtual void FatalServerError(CCustomServer &aServ, TInt aError, TInt aErrorEvent)=0; 
    };


////////////////////////////////////////////////////////////////////////////////////////
//
//	MCustomServerWriter
//
////////////////////////////////////////////////////////////////////////////////////////
class MCustomServerWriter
	{
public:
	virtual void OnSessionWrite(TDes8* aPdu, TRequestStatus &aStatus)=0;
	virtual void OnSessionDeleting()=0;
	};


class CCustomServerSession;
class CCustomServerDeleter;
////////////////////////////////////////////////////////////////////////////////////////
//
//	CCustomServer
//
////////////////////////////////////////////////////////////////////////////////////////
class CCustomServer : public CActive
    {
friend class CCustomServerSession;

public:
    IMPORT_C static void Delete(CCustomServer *aServ);

    inline TInt SessionCount() const;
    inline MCustomServerManager& Manager() const;
    inline void SetLib(const RLibrary &aLib);
    inline void DeferredDelete();
    inline TCustomServerServInfo& Info() const;
	inline RLibrary& Library() const;
    IMPORT_C virtual TCustomServerErrorResult Error(TInt aStatus, TInt aRemErrorEvent);
    virtual CCustomServerSession *NewSessionL(MCustomServerWriter *aCSWriter,TVersion aVersion)=0;

protected: 
    IMPORT_C void ConstructL(MCustomServerManager &aManager);
    IMPORT_C CCustomServer();
    IMPORT_C ~CCustomServer();

    IMPORT_C virtual void RunL();   
    IMPORT_C virtual void DoCancel();
    
    virtual TCustomServerServInfo *NewInfoL()=0;

private:
    void ClearAllSessions();
    void DoStartL();

public:
    TDblQueLink iDblLink;

private: 
    TDblQue<CCustomServerSession> iSessionList;
    TInt iSessionCount;
    TCustomServerServInfo *iInfo;
    MCustomServerManager *iManager;
    CCustomServerDeleter *iDeleter;
    RLibrary iLib;

protected:
	TDblQueIter<CCustomServerSession> iSessionIter;
    };


////////////////////////////////////////////////////////////////////////////////////////
//
//	CCustomServerSession
//
////////////////////////////////////////////////////////////////////////////////////////
class CCustomServerSession : public CActive
    {
friend class CCustomServer;

public:    
    IMPORT_C ~CCustomServerSession();
    IMPORT_C virtual void Free(TDes8 *aPdu);
    virtual TDes8* AllocL(TInt aLen)=0;

protected: 
    IMPORT_C void ConstructL(MCustomServerWriter *aCSWriter,CCustomServer& aServ);
    IMPORT_C CCustomServerSession();
    IMPORT_C virtual void WriteCompleteL(TDes8 *aPdu);    
    IMPORT_C virtual TCustomServerErrorResult Error(TInt aStatus, TInt aRemErrorEvent);

    inline CCustomServer &Server() const;
    IMPORT_C virtual void RunL();   
    virtual void DoCancel();

    inline void Write(TDes8 *aDes);
    inline TBool IsWriting() const;
public:
    virtual void ReadCompleteL(TDes8 *aPdu)=0;
//
private:   

	enum {ECSIdle, ECSReading, ECSWriting} iMode;
	MCustomServerWriter *iCSWriter;
    CCustomServer *iServer;
    TDblQueLink iDblLink;
    };


////////////////////////////////////////////////////////////////////////////////////////
//
//	CCustomServerDeleter
//
////////////////////////////////////////////////////////////////////////////////////////
class CCustomServerDeleter : public CAsyncOneShot
    {
friend class CCustomServer;

private:
    CCustomServerDeleter(CCustomServer &aServ, TInt aPriority);
    CCustomServer *iServ;
    virtual void RunL();    
    }; 


//
////////////////////////////////////////////////////////////////////////////////////////
//
//	Misc
//
////////////////////////////////////////////////////////////////////////////////////////
class TRemSvPtr : public TPtr8
    {
public:

    inline TRemSvPtr();
    inline TRemSvPtr(TUint8* iBuf, TInt aLength);
	inline TUint32 GetLong(TInt anOffset) const;
	inline TUint16 GetWord(TInt anOffset) const;
	inline void PutLong(TInt anOffset, TUint32 aVal);
	inline void PutWord(TInt anOffset, TUint16 aVal);
    inline void WSet(TRemSvPtr& aPtr, TInt anOffset);
//
    inline void SetDesLength32(TInt aOffset, TInt aLength); 
    inline TInt64 GetInt64(TInt aOffset);
    inline void PutInt64(TInt aOffset, TInt64 aVal);
    IMPORT_C TPtrC8 GetDes32(TInt aOffset);
    IMPORT_C TPtrC16 GetDes16(TInt aOffset);
    IMPORT_C TBool VerifyLength32() const;
    IMPORT_C void WSet(TRemSvPtr& aPtr, TInt anOffset, TInt aLength);
	};
//
class SiboUtil
    {
public:
    IMPORT_C static void Put16(TUint8* aPtr, TUint16 aVal);
    IMPORT_C static void Put32(TUint8* aPtr, TUint32 aVal);
    IMPORT_C static TUint16 Get16(const TUint8* aPtr);
	IMPORT_C static TUint32 Get32(const TUint8* aPtr);
    IMPORT_C static void PutFloat(TAny* aPtr, const TReal64& aFloat);
    IMPORT_C static TReal64 GetFloat(TAny* aPtr);
  };
//
class TCustomServerCharConv
	{
public:
#ifdef _UNICODE
	enum TBehaviour {EUnicodeAndEscape, EAnsiAndEscape, EAnsiOnly};
	IMPORT_C static void CopyDes16ToDes8L(const TDesC16& aSrc, TDes8& aTrg);
	IMPORT_C static void CopyDes8ToDes16L(const TDesC8& aSrc, TDes16& aTrg);
	IMPORT_C static void AppendDes16ToDes8L(const TDesC16& aSrc, TDes8& aTrg);
	IMPORT_C static void AppendDes8ToDes16L(const TDesC8& aSrc, TDes16& aTrg);
#endif
    };
//
//
// Various priorities for remote services thread
//
enum TCustomServerServicesPriority
    {
    ECustomServerConnectPriority = CActive::EPriorityStandard,
    ECustomServerIpcPriority = CActive::EPriorityUserInput,
    ECustomServerTimerPriority = ECustomServerIpcPriority + 10,
    ECustomServerReadPriority = ECustomServerIpcPriority + 20, 
    ECustomServerWritePriority = ECustomServerIpcPriority + 30,
    ECustomServerLibDeleterPriority = ECustomServerIpcPriority + 40,
    };
#include "customserver.inl"
#endif
