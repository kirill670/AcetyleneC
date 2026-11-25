// Mda\Server\Dispatcher.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_DISPATCHER_H__
#define __MDA_SERVER_DISPATCHER_H__

#include <Mda\Server\Environment.h>

class CMdaDispatchActive;	// forward declaration 
class CMdaDispatchMessage;	// forward declaration 

class CMdaDispatcher : public CBase
	{
public:
	IMPORT_C ~CMdaDispatcher();
	IMPORT_C static CMdaDispatcher* NewL(TInt aPriority);
	IMPORT_C virtual void RunL();
	IMPORT_C virtual CMdaDispatchMessage* NewMessageL(MMdaMessage* aMessage);
	IMPORT_C virtual void QueueMessage(CMdaMessage& aMessage);
	IMPORT_C virtual TBool CancelMessage(CMdaMessage& aMessage);
	IMPORT_C void SetPriority(TInt aPriority);
	IMPORT_C TInt Priority();
	IMPORT_C virtual void Error(TInt aErr);
protected:
	IMPORT_C CMdaDispatcher();
	IMPORT_C virtual void ConstructL(TInt aPriority);
	IMPORT_C virtual void FreeMessage(CMdaDispatchMessage* aMessage);
	IMPORT_C TBool InFifo(CMdaMessage& aMessage);
protected:	
	CMdaMessage* iOppMessage;	// Keep for error recovery
    TSglQue<CMdaMessage> iFifo;
    TSglQueIter<CMdaMessage> iIter;
	CMdaDispatchActive* iActive;
	friend class CMdaDispatchMessage;
	};

class CMdaDispatchActive : public CMdaActive
	{
public:
	CMdaDispatchActive(CMdaDispatcher& iDispatcher, TInt aPriority);
	~CMdaDispatchActive();
	virtual void RunL();
	virtual void DoCancel();
	virtual void Queue();
	inline void Error(TInt aErr);
protected:
	CMdaDispatcher& iDispatcher;
	};

class CMdaDispatchMessage : public CMdaMessage
	{
public:
	IMPORT_C static CMdaDispatchMessage* NewL(MMdaMessage* aMessage, CMdaDispatcher& aDispatcher);
	IMPORT_C virtual void Close();
	inline void DeliverL();
	IMPORT_C virtual void Cancel();
	IMPORT_C virtual void Complete(TInt aVal);
	IMPORT_C virtual void SetData(CMdaMessage* aMessage);
protected:
	CMdaDispatchMessage(MMdaMessage* aMessage, CMdaDispatcher& aDispatcher);
	~CMdaDispatchMessage();
	IMPORT_C virtual void DoPostL(CMdaObject* aTo); 
public:
	CMdaDispatcher& iDispatcher;
	CMdaObject* iTarget;
	friend class CMdaDispatcher;
	};

inline void CMdaDispatchMessage::DeliverL()
	{
	ASSERT(iTarget);
	DoOperationL(iTarget);
	}

#endif
