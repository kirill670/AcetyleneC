// Mda\Client\Base.h 
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_BASE_H__
#define __MDA_CLIENT_BASE_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Base.h>

/**
 * @publishedAll 
 * @removed
 */
enum { KDummyMdaSessionNotImplemented = 0 };

/**
 * @publishedAll 
 * @removed
 */
enum { KMediaServerNotImplemented = 0 };

/**
 * @publishedAll 
 * @removed
 */
enum { KDummyMdaObjectNotImplemented = 0 };

/**
 * @publishedAll 
 * @deprecated
 *
 * Dummy functions for BC
 */
IMPORT_C TInt StartMediaServer();
IMPORT_C void StartMediaServerL();
IMPORT_C void StartMediaServer(TRequestStatus& aStatus);

class RDummyMdaObject;

/**
 * 
 * @publishedAll 
 * @removed
 *
 * Dummy class for BC
 */
class RDummyMdaSession : public RSessionBase
	{
public:
	IMPORT_C TInt Connect(TInt aSlots=KMdaServerDefaultMessageSlots);
	IMPORT_C void ConnectL(TInt aSlots=KMdaServerDefaultMessageSlots);
	IMPORT_C void ConnectLC(TInt aSlots=KMdaServerDefaultMessageSlots);
	//
	IMPORT_C void Close();
	//
	IMPORT_C TInt ListenTo(const RDummyMdaObject& aObject);
	IMPORT_C void ListenToL(const RDummyMdaObject& aObject);
	IMPORT_C void StopListeningTo(const RDummyMdaObject& aObject);
	//
	IMPORT_C TInt SetListenerParameters(TMdaEventPackage& aPackage,TInt aMaxPackages);
	IMPORT_C void SetListenerParametersL(TMdaEventPackage& aPackage,TInt aMaxPackages);
	//
	IMPORT_C void GetListenerEvents(TMdaEventPackage& aEvents, TRequestStatus& aStatus);
	IMPORT_C void CancelGetListenerEvents();
private:
	friend class RDummyMdaObject;
	};

class RMdaRegistry;

/**
 * 
 * @publishedAll 
 * @removed
 *
 * Dummy class for BC
 */
class RDummyMdaObject
	{
public:
    IMPORT_C void Close();
protected:
	// Object creation
	IMPORT_C TInt SynchCreateMessage(const RDummyMdaObject& aParent,TInt16 aFunction,TAny* aArg=NULL);
	IMPORT_C void SynchCreateMessageL(const RDummyMdaObject& aParent,TInt16 aFunction,TAny* aArg=NULL);
	IMPORT_C void SynchCreateMessageLC(const RDummyMdaObject& aParent,TInt16 aFunction,TAny* aArg=NULL);
	IMPORT_C void AsynchCreateMessage(const RDummyMdaObject& aParent,TInt16 aFunction,TRequestStatus &aStatus,TAny* aArg=NULL);
	IMPORT_C TInt SynchPackageCreateMessage(const RDummyMdaObject& aParent,TInt16 aFunction,TMdaOpenPackage& aPackage);
	IMPORT_C void SynchPackageCreateMessageL(const RDummyMdaObject& aParent,TInt16 aFunction,TMdaOpenPackage& aPackage);
	IMPORT_C void SynchPackageCreateMessageLC(const RDummyMdaObject& aParent,TInt16 aFunction,TMdaOpenPackage& aPackage);
	IMPORT_C void AsynchPackageCreateMessage(const RDummyMdaObject& aParent,TInt16 aFunction,TRequestStatus &aStatus,TMdaOpenPackage& aPackage);
	IMPORT_C void CancelCreateMessage(/*const RDummyMdaObject& aParent,TInt16 aFunction,*/TRequestStatus &aStatus);
	// Message passing
	IMPORT_C TInt BlindMessage(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C void BlindMessageL(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C TInt SynchMessage(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C void SynchMessageL(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C void AsynchMessage(TInt16 aFunction,TRequestStatus &aStatus,const TAny* aArg1=NULL,const TAny* aArg2=NULL) const;
	IMPORT_C void CancelMessage(/*TInt16 aFunction,*/TRequestStatus &aStatus) const;
	// Package passing
	IMPORT_C TInt SynchPackage(TInt16 aFunction,const TMdaRawPackage& aPackage) const;
	IMPORT_C void SynchPackageL(TInt16 aFunction,const TMdaRawPackage& aPackage) const;
	IMPORT_C void AsynchPackage(TInt16 aFunction,TRequestStatus &aStatus,const TMdaRawPackage& aPackage) const;
	IMPORT_C TInt SynchPackageReturn(TInt16 aFunction,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
	IMPORT_C void SynchPackageReturnL(TInt16 aFunction,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
	IMPORT_C void SynchPackageReturnLC(TInt16 aFunction,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
	IMPORT_C void AsynchPackageReturn(TInt16 aFunction,TRequestStatus &aStatus,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
private:
	RDummyMdaSession iSession;
	TPckgBuf<TInt> iObjectHandle;
	friend class RMdaRegistry;
	friend class RMdaTimer;
	friend class RMdaTimerFactory;
	};

#endif
