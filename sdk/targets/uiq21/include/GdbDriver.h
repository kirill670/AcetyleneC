// GdbDriver.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
// Interface of CGdbDriver
//

#ifndef __GDBDRIVER_H__
#define __GDBDRIVER_H__

#ifndef __E32BASE_H__
#include "e32base.h"
#endif

#ifndef __GDBERRORHANDLER_H__
#include "GdbErrorHandler.h"
#endif

class CGdbDriverImp;
class CGdbMarshallingLayer;

class CGdbDriver : public CBase
//
// main control point of the stub: start/stop handling of incoming
// messages
// 
	{

public:
	class MEventHandler : public MGdbErrorHandler
	//
	// Callback interface used to inform client of asynchronous
	// events.
	// 
		{
	public:
		enum TState
			{
			ENotListening,
			ENoDebuggee,
			EDebuggeeStopped,
			EDebuggeeRunning,
			};

	public:
		virtual void HandleStateTransition(TState aOldState, TState aNewState) = 0;
		virtual void HandlePanic(TThreadId aThreadId, TBool aIsDebuggee, const TDesC& aCategory, TInt aReason) = 0;
		};

public:
	// Ctor & Dtor
	static CGdbDriver* NewLC(CGdbMarshallingLayer* aMarshallingLayer);
	static CGdbDriver* NewL(CGdbMarshallingLayer* aMarshallingLayer);
	~CGdbDriver();

	// Starting/Stopping incoming msgs handling
	IMPORT_C TBool Start(MEventHandler* aEventHandler, TUint32 aDebugLowLimit = 0x60000000);
	IMPORT_C void Stop();

	// Getters/Setters
	IMPORT_C MEventHandler::TState State() const;
	void SetHandler(MEventHandler* aEventHandler);

	IMPORT_C void InterruptDebuggee();

private:
	CGdbDriver();
	void ConstructL(CGdbMarshallingLayer* aMarshallingLayer);

private:
	CGdbDriverImp* iImp;
	};


#endif // __GDBDRIVER_H__
