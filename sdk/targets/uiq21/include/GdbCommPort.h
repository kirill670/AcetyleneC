// GdbCommPort.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
// Interface of CGdbCommPort
//

#ifndef __GDBCOMMPORT_H__
#define __GDBCOMMPORT_H__

#ifndef __E32BASE_H__
#include <e32base.h>
#endif

class MGdbErrorHandler;

class CGdbCommPort : public CActive
//
// Abstract Base Class for communication ports manipulated by GDBSTUB
// engine.
//
	{

public: 
	//
	// Maximum size of packets sent by GDB
	//
	enum { KMaxPacketSize = 400 };

public:
	class MByteHandler
	//
	// Interface used to inform asynchronously the client of bytes
	// received.
	// 
		{

	public:
		virtual void HandleByte(TUint8 aByte) = 0;
		};

public:
	IMPORT_C virtual ~CGdbCommPort();

	//
	// return string identifying uniquely the kind of communication
	// port supported.
	// 
	virtual const TDesC8& CommType() const = 0;

	//
	// Set-up the communication port.  Return ETrue if the operation
	// succeeded.
	//
	// aPortError - port-specific error code (defined in children).
	// aEpocError - standard EPOC error code.
	//
	// PRECOND:
	// ! this->IsOpened()
	//
	// POSTCOND:
	//    (return ETrue && this->IsOpened())
	// || (return EFalse && ! this->IsOpened())
	// 
	virtual TBool Open(TInt& aPortError, TInt& aEpocError) = 0;

	//
	// Close the previously opened communication port.
	//
	// PRECOND:
	// this->IsOpened()
	//
	// POSTCOND:
	// ! this->IsOpened()
	// 
	virtual void Close() = 0;

	//
	// Is the port opened?
	// 
	virtual TBool IsOpened() const = 0;

	//
	// Send synchronously a packet through the communication port.
	// Return a standard EPOC error code.
	//
	// PRECOND:
	// aBuffer.Length() > 0 && this->IsOpened()
	// 
	virtual void SendBufferL(const TDesC8& aBuffer) = 0;

	//
	// Start listening asynchronously for incoming bytes on the port.
	// Received bytes and errors are communicated via the callbacks.
	//
	// PRECOND:
	// aByteHandler != 0 && aErrorHandler != 0
	// && this->IsOpened() && not already listening
	// 
	virtual void Listen(MByteHandler* aByteHandler, MGdbErrorHandler* aErrorHandler) = 0;

	//
	// Stop listening.
	//
	// PRECOND:
	// already listening
	// 
	virtual void StopListening() = 0;

protected:
	IMPORT_C CGdbCommPort(TInt aPriority);
	};

#endif // __GDBCOMMPORT_H__
