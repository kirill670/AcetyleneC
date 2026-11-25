// Mda\Server\Resource.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//


#ifndef __MDA_SERVER_RESOURCE_H__
#define __MDA_SERVER_RESOURCE_H__

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
#include <F32File.h>
#include <BaRsRead.h>

// Public Media Server includes
#include <Mda\Common\Resource.h>
#include <Mda\Server\Base.h>
#include <Mda\Server\Environment.h>
#include <Mda\Server\Port.h>

class CMdaRootResourceObject; // Forward reference
class CMdaResourceManager : public CMdaObject, public MMdaProcessor, public MMdaMessage
	{
public:
	IMPORT_C CMdaResourceManager();
	virtual ~CMdaResourceManager();
	// From CMdaObject
	virtual void OperationL(CMdaMessage* aMessage);
	virtual void OperationCancel(CMdaMessage* aMessage);
	// from MMdaProcessor
	virtual void ProcessL();
	virtual void ProcessFailed(TInt aError);
	// from MMdaMessage
	virtual void MessageDoComplete(TInt aVal);
	virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
	// New
	static inline void ConfigResource(CMdaMessage* aMessage, TMdaPackage* aConfigArg, TBool aFromDest);
private:
	// New
	static inline TBool ConfigResourceFromDest(CMdaMessage* aMessage);
	static inline TMdaPackage* ConfigResourcePackage(CMdaMessage* aMessage);
	//
	void ManageResource(CMdaRootResourceObject& aResource);
	void CompleteAndNextMessage(TInt aReturn);
private:
	enum TManagerState
		{
		ENewRequest,
		ECreatingResource,
		EConfiguringResource
		};
private:
	TDblQue<CMdaRootResourceObject> iObjects;
	CMdaTargetedMessage iMsg;
	CMdaMessageProcessor iProc;
	TManagerState iManagerState;
	CMdaRootResourceObject* iCurrentResource;
	};

class CMdaResourceObject : public CMdaObject	
	{
public:
	inline TUid Type();
	inline TUid Uid();
	static inline void Config(CMdaMessage* aMessage, TMdaPackage* aConfigArg, TBool aFromDest);
	static inline void CreatePort(CMdaMessage* aMessage, TBool aIsSource);
protected:
	IMPORT_C CMdaResourceObject(TUid aType,TUid aUid);
	//
	IMPORT_C virtual void AddEventListenerL(MMdaEventListener& aListener);
	IMPORT_C virtual void RemoveEventListener(MMdaEventListener& aListener);
	//
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	//
	static inline TBool ConfigFromDest(CMdaMessage* aMessage);
	static inline TMdaPackage* ConfigPackage(CMdaMessage* aMessage);
	IMPORT_C virtual void ConfigL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelConfig(CMdaMessage* aMessage);
	//
	static inline TBool CreatePortFromDest(CMdaMessage* aMessage);
	IMPORT_C virtual void CreatePortL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelCreatePort(CMdaMessage* aMessage);
	//
	IMPORT_C virtual void CompleteMessage(CMdaMessage* aMessage, TInt aReturn);
	IMPORT_C void PropagateMessageL(CMdaMessage* aMessage, CMdaObject* aObject);
	IMPORT_C virtual void DelegateMessageHandling(CMdaMessage* aMessage);
protected:
	CMdaEventBroadcaster iEvents;
private:
	TUid iType;
	TUid iUid;
	};

class CMdaRootResourceObject : public CMdaResourceObject
	{
	friend class CMdaResourceManager;
public:
	IMPORT_C virtual ~CMdaRootResourceObject();
	inline CMdaRootResourceObject(TUid aType,TUid aUid);
	virtual TBool Match(const TMdaPackage* aPackage, TBool aFromDest)=0;
public:
	TDblQueLink iLink;
private:
	CMdaResourceManager* iManager;
	};
	
class CMdaResourceHandle : public CMdaIOFactory, public MMdaProcessor, public MMdaMessage, public MMdaEventListener
	{
protected:
	IMPORT_C void BaseConstructL();
	IMPORT_C virtual ~CMdaResourceHandle();
	// Event Listeners
	IMPORT_C virtual void AddEventListenerL(MMdaEventListener& aListener);
	IMPORT_C virtual void RemoveEventListener(MMdaEventListener& aListener);
	//
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	//
	IMPORT_C virtual void NewIOL(CMdaMessage* aMessage);
	// from MMdaProcessor
	IMPORT_C virtual void ProcessL();
	IMPORT_C virtual void ProcessFailed(TInt aError);
	// from MMdaMessage
	IMPORT_C virtual void MessageDoComplete(TInt aVal);
	IMPORT_C virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
	IMPORT_C virtual void MessageDoReadDesL(TInt aArg, TDes8& aDes);
	IMPORT_C virtual void MessageDoWriteDesL(TInt aArg, const TDesC8& aDes);
	// from MMdaEventListener
	IMPORT_C virtual void Event(const TMdaEvent& aEvent);
	// New
	// Actions
	IMPORT_C virtual TBool ProcessMessageL();
	IMPORT_C virtual TBool CreateManagerL();
	virtual TBool ConfigL()=0;
	IMPORT_C virtual TBool CreatePortL();
	IMPORT_C virtual TBool CreateIOL();
	IMPORT_C virtual TBool DoPortConfigL();
	// Message processing
	IMPORT_C virtual TBool ProcessConfigL();
	IMPORT_C virtual TBool ProcessNewIOL();
	IMPORT_C virtual TBool ProcessPortConfigL();
	// Identification
	virtual TUid ResourceType()=0; // Must be supplied by derived class
	// Utilities
	IMPORT_C void CompleteAndNextMessage(TInt aReturn);
protected:
	enum TReadyState
		{
		EClosed=0,
		EHaveManager,
		EHavePort
		};
	enum TProcessingState
		{
		EProcessMessage=0,
		ECreateManager,
		EConfig,
		ECreatePort,
		ECreateIO,
		EPortConfig
		};
protected:
	inline CMdaResourceHandle(TBool aSource);
private:
	void DoProcessFailedL(TInt aError);
protected:
	CMdaEventBroadcaster iEvents;
	//
	TReadyState iReadyState;
	TProcessingState iProcState;
	TInt iSubState;
	TBool iNewMessage;
	//
	CMdaResourceManager* iManager;
	CMdaRootResourceObject* iResource;
	CMdaIOFactory* iPort;
	CMdaTargetedMessage iMsg;
	CMdaMessageProcessor iProc;
	TBool iSource;
	//
	CMdaObject* iReturned;
	TInt iCompleted;
	//
	TMdaPackage* iCurrentPackage;
	//
	friend class CMdaResourceManager;
	};

// Classes for parsing resource entries

class TMdaResourceEntryParser
	{
public:
	enum TType
		{
		EConfigDef,
		ESignature,
		ECapabilities,
		EExtension,
		EStrings
		};
public:
	IMPORT_C void Set(const TDesC8& aResource);
	IMPORT_C TUint Count(TType aType) const;
	IMPORT_C const TPtrC8 Entry(TType aType, TInt aIndex) const;
private:
	TPtrC8 iPtr;
	TUint iIndices[EStrings+1];
	TUint iCounts[EStrings+1];
	};

class TMdaResourceMatcher
	{
public:
	// Returns KNullUid if no match - leaves on e.g. OOM
	IMPORT_C TUid MatchL(TUid aType, const TDesC8* aData, const TDesC* aName, const TDesC8* aMimeType); 
	};

inline void CMdaResourceManager::ConfigResource(CMdaMessage* aMessage, TMdaPackage* aConfigArg, TBool aFromDest)
	{ aMessage->iFunction = EMLbResourceObjectConfig; aMessage->iArg[0] = (TInt)aConfigArg; aMessage->iArg[1] = aFromDest; }
inline TBool CMdaResourceManager::ConfigResourceFromDest(CMdaMessage* aMessage)
	{ return aMessage->iArg[1]; }
inline TMdaPackage* CMdaResourceManager::ConfigResourcePackage(CMdaMessage* aMessage)
	{ return STATIC_CAST(TMdaPackage*,(TAny*)aMessage->iArg[0]); }

inline TUid CMdaResourceObject::Type() 
	{ return iType; }
inline TUid CMdaResourceObject::Uid() 
	{ return iUid; }

inline void CMdaResourceObject::Config(CMdaMessage* aMessage, TMdaPackage* aConfigArg, TBool aFromDest)
	{ aMessage->iFunction = EMLbResourceObjectConfig; aMessage->iArg[0] = (TInt)aConfigArg; aMessage->iArg[1] = aFromDest; }
inline void CMdaResourceObject::CreatePort(CMdaMessage* aMessage, TBool aIsSource)
	{ aMessage->iFunction = EMLbResourceObjectCreatePort; aMessage->iArg[0] = aIsSource; }
inline TBool CMdaResourceObject::CreatePortFromDest(CMdaMessage* aMessage)
	{ return !(aMessage->iArg[0]); }
inline TBool CMdaResourceObject::ConfigFromDest(CMdaMessage* aMessage)
	{ return aMessage->iArg[1]; }
inline TMdaPackage* CMdaResourceObject::ConfigPackage(CMdaMessage* aMessage)
	{ return STATIC_CAST(TMdaPackage*,(TAny*)aMessage->iArg[0]); }

inline CMdaRootResourceObject::CMdaRootResourceObject(TUid aType,TUid aUid) :
CMdaResourceObject(aType,aUid) {}

inline CMdaResourceHandle::CMdaResourceHandle(TBool aSource)
#pragma warning( disable : 4355 )	// 'this' : used in base member initializer list
: iMsg(this),iProc(CMdaActive::ENonCriticalTaskPriorityBase,*this),iSource(aSource)
	{}

#endif
