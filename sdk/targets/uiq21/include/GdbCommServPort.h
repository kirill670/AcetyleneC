// GdbCommServPort.h
//
// Copyright (c) 2000-2002 Symbian Ltd.  All rights reserved.
//
// Interface of CGdbCommServPort
//

#ifndef __GDBCOMMSERVPORT_H__
#define __GDBCOMMSERVPORT_H__

#ifndef __C32COMM_H__
#include <c32comm.h>
#endif

#ifndef __GDBCOMMPORT_H__
#include "GdbCommPort.h"
#endif

class CGdbCommServPort : public CGdbCommPort
//
// Implementation of the CGdbCommPort interface that drives
// serial-like devices supported by the RCommServ API.
// 
	{

public:
	// Open() Error Codes
	enum
		{
		KNoError = 0,
		KPDDLoadingFailed,
		KLDDLoadingFailed,
		KServerConnectionFailed,
		KCSYLoadingFailed,
		KUnknownUnit,
		KOpenFailed,
		KUnknownRate,
		KConfigFailed,
		};

public:
	// Ctors & Dtors
	IMPORT_C static CGdbCommServPort* NewL();
	IMPORT_C static CGdbCommServPort* NewLC();
	IMPORT_C ~CGdbCommServPort();

	// Getters & Setters
	IMPORT_C void SetPhysicalDeviceL(const TDesC& aPDD);
	const TDesC& PhysicalDevice() const;
	IMPORT_C void SetLogicalDeviceL(const TDesC& aLDD);
	const TDesC& LogicalDevice() const;
	IMPORT_C void SetCommModuleL(const TDesC& aCSY);
	const TDesC& CommModule() const;
	void SetUnitNumber(TUint aUnit);
	TUint UnitNumber() const;
	void SetRate(TUint aRate);
	TUint Rate() const;

	// Name returned by CommType()
	IMPORT_C static const TDesC8& RefCommType();

	// From CGdbCommPort - intended to be used by engine clients
	IMPORT_C const TDesC8& CommType() const;
	IMPORT_C TBool Open(TInt& aPortError, TInt& aEpocError);
	IMPORT_C void Close();

	// From CGdbCommPort - for internal engine use only
	TBool IsOpened() const;
	void SendBufferL(const TDesC8& aBuffer);
	void Listen(MByteHandler* aByteHandler, MGdbErrorHandler* aErrorHandler);
	void StopListening();

protected:
	// From CActive
	void DoCancel();
	void RunL();

private:
	CGdbCommServPort();
	void ConstructL();
	void DoOpenL(TInt& aPortError);
	void ClosePortIfOpened();
	void IssueReadRequest();

private:
	HBufC* iPDD;
	HBufC* iLDD;
	HBufC* iCSY;
	TUint  iUnitNumber;			// Port Number
	TUint  iRate;				// Link Speed in bauds
	TUint  iFlags;				// Bitmasks defined in cpp file

	RCommServ iServer;
	RComm  iPort;

	MByteHandler* iByteHandler;	// uses - nul when not listening
	MGdbErrorHandler* iErrorHandler; // uses - nul when not listening

	//
	// Bytes are fetched from the comms server in batch to improve
	// performance.
	//

	TBuf8<KMaxPacketSize> iReceivedChars;
	TInt iNextReadChar;	// < iReceivedChars.Length() if available char

	class CTimerResetter;
	CTimerResetter* iInactivityTimerDisabler;
	};

////////////////////////////////////////////////////////////////////////

inline const TDesC& CGdbCommServPort::PhysicalDevice() const
	{

	return *iPDD;
	}


inline const TDesC& CGdbCommServPort::LogicalDevice() const
	{

	return *iLDD;
	}


inline const TDesC& CGdbCommServPort::CommModule() const
	{

	return *iCSY;
	}


inline void CGdbCommServPort::SetUnitNumber(TUint aUnitNumber)
	{

	iUnitNumber = aUnitNumber;
	}


inline TUint CGdbCommServPort::UnitNumber() const
	{

	return iUnitNumber;
	}


inline void CGdbCommServPort::SetRate(TUint aRate)
	{

	iRate = aRate;
	}


inline TUint CGdbCommServPort::Rate() const
	{

	return iRate;
	}

#endif // __GDBCOMMSERVPORT_H__
