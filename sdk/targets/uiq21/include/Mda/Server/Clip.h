// Mda\Server\Clip.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_CLIP_H__
#define __MDA_SERVER_CLIP_H__

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
#include <F32File.h>
#include <BaRsRead.h>

// Public Media Server includes
#include <Mda\Common\Resource.h>

#include <Mda\Server\Base.h>
#include <Mda\Server\Environment.h>
#include <Mda\Server\Port.h>
#include <Mda\Server\Resource.h>

class CMdaClipResourceHandle : public CMdaResourceHandle
	{
public:
	IMPORT_C static CMdaClipResourceHandle* NewL(TBool aIsSource);
protected:
	inline CMdaClipResourceHandle(TBool aIsSource)
		:CMdaResourceHandle(aIsSource) {};
	virtual TBool ConfigL();
	virtual TUid ResourceType(); 
private:
	enum TClipState
		{
		ENoResource,
		ECreatingResource,
		EConfigSent,
		EConfigured
		};
private:
	TClipState iClipState;
	};

class CMdaClipFormatMatcher;
class CMdaClipFormat;
class CMdaClipLocation : public CMdaRootResourceObject
	{
public:
	// Asynchronous function parameter setup
	static inline void Read(CMdaMessage* aMessage,TDes8& aBuffer,TInt aOffset);
	static inline void Write(CMdaMessage* aMessage,const TDes8& aData,TInt aOffset);
	// Synchronous functions
	inline TInt ClipLength();
	inline TInt ClipVisible();
	IMPORT_C virtual void CropL(TInt aNewLength);
	IMPORT_C virtual void SynchWriteL(const TDes8& aData,TInt aOffset);
	virtual void BytesFree(TInt64& aValue)=0;
protected:
	inline CMdaClipLocation(TUid aUid, TMdaResourceUsage aUsage);
	IMPORT_C virtual ~CMdaClipLocation();
	// Asynchronous functions
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	IMPORT_C virtual void ConfigL(CMdaMessage* aMessage);
	virtual void ConfigThisL(const TMdaPackage* aConfigPackage, TBool aFromDest)=0;
	IMPORT_C virtual void CancelConfig(CMdaMessage* aMessage);
	IMPORT_C virtual void CreatePortL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelCreatePort(CMdaMessage* aMessage);
	IMPORT_C virtual TBool Match(const TMdaPackage* aPackage, TBool aFromDest);
	static inline TDes8* GetBuffer(CMdaMessage* aMessage);
	static inline TInt GetOffset(CMdaMessage* aMessage);
	virtual void ReadL(CMdaMessage* aMessage)=0;
	IMPORT_C virtual void CancelRead(CMdaMessage* aMessage);
	virtual void WriteL(CMdaMessage* aMessage)=0;
	IMPORT_C virtual void CancelWrite(CMdaMessage* aMessage);
	// Matching functions
	virtual void SetMatchDataL()=0;
	// Utility functions
	IMPORT_C void SetLength(TInt aLength,TInt aVisible);
	IMPORT_C void DataHasChanged();
	IMPORT_C void SizeHasChanged();
protected:
	enum TState
		{
		EClosed=0,
		EOpen,
		EReading,
		EWriting
		};
protected:
	CMdaClipFormatMatcher* iMatcher;
	CMdaClipFormat* iFormat;
	TMdaClipLocation* iConfigPtr;
	TState iState;
	//
	TUid iMatchUid; // Allowed to specify format
	TPtrC8 iMatchData;
	TPtrC  iMatchName;
	TPtrC8 iMatchMimeType;
	//
private:
	friend class CMdaClipFormatMatcher;
	TMdaResourceUsage iUsage;
	};

class CMdaClipFormat : public CMdaResourceObject
	{
public:
	inline void SetLocation(CMdaClipLocation* aLocation);
protected:
	inline CMdaClipFormat(TUid aUid);
protected:
	CMdaClipLocation* iLocation;
	};

class CMdaLinearClipFormat : public CMdaClipFormat
	{
public:
	IMPORT_C virtual void ReadBlockL(CMdaMessage* aMessage, TDes8& aBuffer, TInt aPosition);
	IMPORT_C virtual void WriteBlockL(CMdaMessage* aMessage, TDes8& aData, TInt aPosition);
	IMPORT_C virtual void CropL(TInt aBytesToCrop);
protected:
	CMdaLinearClipFormat(TUid aType)
		: CMdaClipFormat(aType) {};
protected:
	TInt iStartPosition;
	TInt iDataLength;
	};

class CMdaClipFormatMatcher : public CMdaObject, public MMdaProcessor, public MMdaMessage
	{
public:
	IMPORT_C static CMdaClipFormatMatcher* NewL(CMdaClipLocation& aParent);
	// From CMdaObject
	virtual void OperationL(CMdaMessage* aMessage);
	virtual void OperationCancel(CMdaMessage* aMessage);
	// New
	IMPORT_C void Start(TUid aType, const TDesC8* aData, const TDesC* aName, const TDesC8* aMimeType);
	IMPORT_C void Start(TUid aUid);
protected:
#pragma warning( disable : 4355 )	// 'this' : used in base member initializer list
	CMdaClipFormatMatcher(CMdaClipLocation& aParent)
		: iParent(aParent), 
		  iMsg(CMdaActive::EHardwarePriorityBase,this), 
		  iProcessor(CMdaActive::EHardwarePriorityBase,*this)
#pragma warning( default : 4355 )
		{};
	~CMdaClipFormatMatcher();
	// From MMdaProcessor
	virtual void ProcessL();
	virtual void ProcessFailed(TInt aError);
	// From MMdaMessage
	virtual void MessageDoComplete(TInt aVal);
	virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
	// New
	void CompleteAndNextMessage(TInt aVal);
private:
	enum TState 
		{
		ENewMessage = 0,
		EMatchStart,
		EMatchComplete,
		EFormatCreated,
		EFormatConfigured
		};
private:
	TState iMatchState;
	CMdaClipLocation& iParent;
	CMdaTargetedMessage iMsg;
	CMdaMessageProcessor iProcessor;
	CMdaMessage* iProcessing;
	CMdaClipFormat* iFormat;
	//
	TUid iType;
	TUid iUid;
	const TDesC8* iData;
	const TDesC* iName;
	const TDesC8* iMime;
	};

inline CMdaClipLocation::CMdaClipLocation(TUid aUid, TMdaResourceUsage aUsage) : 
CMdaRootResourceObject(KUidMdaClipLocation,aUid), 
iUsage(aUsage)
	{
	}

inline void CMdaClipLocation::Read(CMdaMessage* aMessage,TDes8& aBuffer,TInt aOffset)
	{
	aMessage->iFunction = EMLbClipLocRead;
	aMessage->iArg[0] = (TInt)&aBuffer;
	aMessage->iArg[1] = (TInt)aOffset;
	}

inline void CMdaClipLocation::Write(CMdaMessage* aMessage,const TDes8& aData,TInt aOffset)
	{
	aMessage->iFunction = EMLbClipLocWrite;
	aMessage->iArg[0] = (TInt)&aData;
	aMessage->iArg[1] = (TInt)aOffset;
	}


inline TInt CMdaClipLocation::ClipLength()
	{
	return iConfigPtr->iSize;
	}

inline TInt CMdaClipLocation::ClipVisible()
	{
	return iConfigPtr->iVisible;
	}

inline TDes8* CMdaClipLocation::GetBuffer(CMdaMessage* aMessage)
	{
	ASSERT((aMessage->iFunction == EMLbClipLocRead)||(aMessage->iFunction == EMLbClipLocWrite));
	return (TDes8*)(aMessage->iArg[0]);
	}

inline TInt CMdaClipLocation::GetOffset(CMdaMessage* aMessage)
	{
	ASSERT((aMessage->iFunction == EMLbClipLocRead)||(aMessage->iFunction == EMLbClipLocWrite));
	return (aMessage->iArg[1]);
	}


inline CMdaClipFormat::CMdaClipFormat(TUid aUid) :
CMdaResourceObject(KUidMdaClipFormat,aUid)
	{
	}

inline void CMdaClipFormat::SetLocation(CMdaClipLocation* aLocation)
	{
	iLocation = aLocation;
	}

#endif
