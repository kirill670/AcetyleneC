// Mda\Client\Utility.h 
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
// maintained for backwards compatibility


#ifndef __MDA_CLIENT_UTILITY_H__
#define __MDA_CLIENT_UTILITY_H__

// Standard EPOC32 includes
#include <e32base.h>
#include <mda\client\port.h>

/**
 * @publishedAll
 * @removed
 */
enum { 
	KDummyMdaControllerNotImplemented = 0,
	KDummyMdaServerNotImplemented,
	KDummyMdaResourceNotImplemented
	};

// Maintained for backwards compatibility
// Some code such as CONE uses constucts such as CMdaServer* iServer = CMdaServer::NewL();

/**
 * 
 * @publishedAll
 * @deprecated
 */
class MMdaObjectEventListener
	{
public:
	virtual const RDummyMdaObject& MoelObject() const =0;
	virtual void MoelEvent(const TMdaEvent& aEvent) =0;
	virtual void MoelEventMissed() =0;
	friend class CMdaServer;
	};

/**
 * 
 * @publishedAll
 * @deprecated
 */
class CMdaServer : public CBase
	{
public:
	IMPORT_C static CMdaServer* NewL();
	IMPORT_C ~CMdaServer();
	IMPORT_C void AddListenerL(MMdaObjectEventListener& aListener);
	IMPORT_C void RemoveListener(MMdaObjectEventListener& aListener);
	};

/**
 * 
 * @publishedAll
 * @deprecated
 */
class MMdaObjectStateChangeObserver
	{
public:
	virtual void MoscoStateChangeEvent(CBase* aObject, TInt aPreviousState, TInt aCurrentState, TInt aErrorCode)=0;
	};

/**
 * 
 * @publishedAll
 * @removed
 */
class MDummyMdaSrcPort
	{
public:
	virtual const RMdaSrcPort& MspSrcPort()=0;
	};

/**
 * 
 * @publishedAll
 * @removed
 */
class MDummyMdaDstPort
	{
public:
	virtual const RMdaDstPort& MdpDstPort()=0;
	};

/**
 * 
 * @publishedAll
 * @removed
 */
class CDummyMdaResource : public CActive, public MDummyMdaSrcPort, public MDummyMdaDstPort
	{
protected:
	IMPORT_C CDummyMdaResource(TInt aPriority);
	};

#endif
