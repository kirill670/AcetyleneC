// Etel3rdParty.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

// Etel3rdParty.dll interface, using CTelephony class defined here.

#ifndef ETEL3RDPARTY_H__
#define ETEL3RDPARTY_H__

/** @file Etel3rdParty.h */

#include <e32base.h>
#include <etel.h>

const TInt	KTelephonyMajorVersionNumber=7; ///< Major version-number
const TInt	KTelephonyMinorVersionNumber=0; ///< Minor version-number
const TInt	KTelephonyBuildVersionNumber=0; ///< Build version-number
// Note: held internally as TInt8, TInt8, TInt16, see E32STD.H

// Panic numbers returned to applications. 0 upwards...
const TInt KTelephonyPanicIllegalReuse = 0;	///< Client code has attempted to re-post an asynchronous request before the original request has completed.

class CTelephonyFunctions;		// forward declaration

/**
 * @class CTelephony
 *
 * Provides an easy-to-use layer which hides Etel DLL complexities.
 *
 * CTelephony.h is as simple as possible, and the size of instantiated
 * CTelephony class objects will remain constant, so future versions of
 * Telephony.DLL should remain backwards compatible with earlier
 * versions.
 *
 * Synchronous and Asynchronous functions are available. Users must
 * use the Active Object paradigm if using the asynchronous functions.
 *
 * The real work is done by an instance of CTelephonyFunctions class,
 * which is not exported from the DLL, so can change in size/design
 * without affecting clients who use a CTelephony object.
 *
 * Users create an RComm object which is passed to the CTelephony
 * object. CTelephony keeps a pointer to this RComm object, in order to
 * Open() and Close() it. So, the RComm object must not be destroyed
 * until after TerminateCall() has been called.
 */

class CTelephony : public CBase
	{
	
public:		// non-virtual, inline/exported functions here ARE part of the API.
		// virtual functions here ARE part ot the API.
		
		// Constructors
	
	IMPORT_C static CTelephony* NewLC();
	
	IMPORT_C static CTelephony* NewL();
	
		// Destructor - virtual and class not intended
		// for derivation, so not exported
	
	~CTelephony();
	
		// general functions - inline, so not exported
	
	inline TVersion Version() const;
	
		// general functions - exported
	
	IMPORT_C TInt FindDeviceStatus(RCall::TStatus& aCallStatus);

	IMPORT_C TInt EstablishDataCall(RComm& aDataChannel, const TDesC& aDialNumber);

	IMPORT_C void EstablishDataCall(TRequestStatus& aRequestStatus, RComm& aDataChannel, const TDesC& aDialNumber);

	IMPORT_C TInt TerminateDataCall();

	IMPORT_C TInt ReceiveDataCall(RComm& aDataChannel);

	IMPORT_C void ReceiveDataCall(TRequestStatus& aRequestStatus, RComm& aDataChannel);

	IMPORT_C void CancelEstablishDataCall();

	IMPORT_C void CancelReceiveDataCall();

private:	// non-virtual functions here are NOT part of the API.
		// virtual functions here COULD be over-ridden by derived-classes,
		// so ARE part of the API.
		// Functions here COULD be EXPORTed for use by inline functions.

	CTelephony();	// C++ constructor - not exported. Called from NewLC()

	void ConstructL();	// second-phase constructor

	void NewTeleFindDeviceStatusL(RCall::TStatus& aCallStatus);

// private data here are NOT part of the API

	CTelephonyFunctions*	iTelephonyFunctions;	///< Object to do the real work

	};
	
#include "telephony.inl"	// trivial functions which don't need to
		// be built into the DLL. So, they don't get EXPORTed, and they don't
		// have any associated ordinal at link-time.

#endif	// ETEL3RDPARTY_H__