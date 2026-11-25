// HCIPROXY.H 
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// BT HCI Extension Wrapper

#ifndef HCIPROXY_H__
#define HCIPROXY_H__

#include <es_sock.h>
#include <bt_sock.h>
#include <e32test.h>
#include <c32comm.h>
#include <f32file.h>
#include <e32std.h>

/**
This class provides a mixin interface for reception of command completions for vendor
specific commands and vendor specific events.
**/
class MVendorSpecificHciConduit
	{
public:	
/**
CommandCompleted is called when a vendor specific command issued through the conduit
receives a completion from the hardware.
@param aError	:	The error code with which the command completed.
**/	
	virtual void CommandCompleted(TInt aError)=0;
/**
CommandCompleted is called when a vendor specific command issued through the conduit
receives a completion from the hardware.

@param aEvent	:	Returns raw vendor specific debug event data generated from the hardware 
(with no HCTL framing)
@param aError	:	An error indicating that the conduit did not successfully receive the event.
@return If ETrue, the conduit will continue to listen for vendor specific debug events, 
If EFalse, the conduit stops listening for these events.
**/	
	virtual TBool ReceiveEvent(TDesC8& aEvent, TInt aError)=0;
	};

/**
This class acts as a wrapper for a group of Ioctls which used together provide a means 
for licensees to pass proprietary commands direct to the hardware at the bottom of the 
stack, and to receive events elicited by these commands back from the hardware.

On construction, the CHciExtensionConduit registers itself with the Bluetooth stack,
which  ensures that there can be only one HCI Extension Conduit in existance on a machine 
at one time. This means that the first such conduit constructed after bootup has sole
access to issue vendor specific commands and more importantly receive back vendor specific
events.

It works in conjunction with the MVendorSpecificHciConduit class, which provides a mixin
interface for reception of command completions for vendor specific commands and vendor 
specific events.
**/
class CHciExtensionConduit : public CActive
	{
public:
	// Construct/destruct
	IMPORT_C static CHciExtensionConduit* NewL(MVendorSpecificHciConduit& aConduit);
	IMPORT_C ~CHciExtensionConduit();

	// Commands
	IMPORT_C TInt IssueCommandL(TDesC8& aCommand);
	IMPORT_C TInt WaitForEvent();
	IMPORT_C void StopWaitingForEvent();

protected:
	IMPORT_C void ConstructL();

private:
	// Construct/destruct
	CHciExtensionConduit(MVendorSpecificHciConduit& aConduit);
	

	// From CActive
	void RunL();
	void DoCancel();

private:
	TUint						iCurrentIoctl;
	TBool						iWaitForEvent;
	RSocketServ					iSocketServ;
	RSocket						iSocket;
	MVendorSpecificHciConduit&	iConduit;
	TProtocolDesc				iL2CapProtoDesc;
	TBuf8<255>					iBuf;
	};

#endif
