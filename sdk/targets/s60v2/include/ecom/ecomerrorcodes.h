//
// EComErrorCodes.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file EComErrorCodes.h
	Comments : All the error codes returned by
			 the ECOM framework to a client 
			 are defined here.
 */ 

#ifndef __ECOMERRORCODES_H__
#define __ECOMERRORCODES_H__

// Shared Error codes for the ECOM framework and client
/** The base value for ECom Frmework errors */
const TInt KEComErrBase								= -17000;

/** The last value for ECom Frmework errors */
//	This must be modified when error codes are added/deleted
const TInt KEComErrLast								= -17030;

////////////////////////////////////////////////////////////
// Error codes which may be received by a client application
////////////////////////////////////////////////////////////
/** 
The call to instantiate an Interface Implementation failed 
because no registrations exist for this interface. 
@internalComponent
*/
const TInt KEComErrNoInterfaceIdentified			= -17004;

/** 
The Non-Default resolver could not be instantiated.  The most likely
situation is that an incorrect implementation uid was supplied. 
@internalComponent
*/
const TInt KEComErrNoResolver						= -17014;

/** 
The client has requested too many notifications.  ECom can only support
a finite number of notifications 
@internalComponent
*/
const TInt KEComErrTooManyNotificationsOutstanding	= -17026;

/** 
An ECom service was requested with an essential parameter missing.  For example,
this error code will be supplied when calling an overload of CreateImplementationL 
which uses a non-default resolver if you fail to supply the resolver 
@internalComponent
*/
const TInt KEComErrMissingParameter					= -17028;

/** The registry index is invalid but the client has requested notifications - so
they will receive a notification when the index is ready again 
@internalComponent
*/
const TInt KEComErrListInvalidAwaitNotification		= -17029;

/** 
The registry index is invalid and the client has not requested notifications.
They will have to try again later after discoveries have completed. 
@internalComponent
*/
const TInt KEComErrListCurrentlyUnavailable			= -17030;


////////////////////////////////////////////////////////////
// Error codes for internal use only
////////////////////////////////////////////////////////////
/** 
The Client requested a service which is not supplied by this framework 
@internalComponent
*/
const TInt KEComErrInvalidUnloadPolicy				= -17003;

/** 
An attempt has been made to load an implementation contained within a dll
which no longer exists (deleted or is on a CF card that has been removed). 
@internalComponent
*/
const TInt KEComErrInvalidIIC						= -17008;

/** 
An attempt has been made to update registry information for a dll on a
drive that does not exist. 
@internalComponent
*/
const TInt KEComErrDriveNotFound					= -17019;


////////////////////////////////////////////////////////////
// Codes which are only used for Panics
////////////////////////////////////////////////////////////
/** 
The Client requested a service which is not supplied by this framework 
@internalComponent
*/
const TInt KEComErrUnknownService					= -17002;

/** 
The Interface Implementation reference count is invalid 
@internalComponent
*/
const TInt KEComErrReferenceCountInvalid			= -17013;

/** 
The Interface Implementations destruction could not be recorded 
@internalComponent
*/
const TInt KEComErrDestructionFailed				= -17017;

/** 
An attempt has been made to update the registry information for a
non-existent DLL.  An ECom internal error. 
@internalComponent
*/
const TInt KEComErrInvalidRegistryData				= -17022;

/** 
The client called DestroyedImplementation with a destruction
key of NULL.  This is an irrecoverable error because the object
cannot be deleted. 
@internalComponent
*/
const TInt KEComErrDestroyingWithNullDtorKey		= -17027;


////////////////////////////////////////////////////////////
// Codes which are currently unused but reserved for future expansion
////////////////////////////////////////////////////////////
/**
@internalComponent
*/
const TInt KEComErrAlreadyReceiving					= -17001;

/** 
The call to Enable the registered Interface Implementation failed 
@internalComponent
*/
const TInt KEComErrEnableFailed						= -17005;

/** 
The call to Disable the registered Interface Implementation failed 
@internalComponent
*/
const TInt KEComErrDisableFailed					= -17006;

/** 
The call to instantiate an Interface Implementation failed 
because no appropriate implementation was found. 
@internalComponent
*/
const TInt KEComErrNoRegistrationsFound				= -17007;

/** 
The call to Remove the registered Interface Implementation failed 
@internalComponent
*/
const TInt KEComErrUninstallFailed					= -17009;

/** 
The call to Re-register an Interface Implementation failed 
@internalComponent
*/
const TInt KEComErrReinstallFailed					= -17010;

/** 
The call to Register an Interface Implementation failed 
@internalComponent
*/
const TInt KEComErrRegistrationFailed				= -17011;

/** 
The client does not have a session open with the framework 
@internalComponent
*/
const TInt KEComErrNotConnected						= -17012;

/** 
The call to Suspend registration activities failed 
@internalComponent
*/
const TInt KEComErrSuspendFailed					= -17015;

/** 
The call to Resume registration activities failed 
@internalComponent
*/
const TInt KEComErrResumeFailed						= -17016;

/** 
An attempt has been made to add a drive to the registry which
already exists 
@internalComponent
*/
const TInt KEComErrDriveAlreadyInstalled			= -17018;

/**
@internalComponent
*/
const TInt KEComErrIndexEntryNotFound				= -17020;

/** 
An IIC has been found which does not have a corresponding 
registration information file 
@internalComponent
*/
const TInt KEComErrNoRegistrationData				= -17021;

/**
@internalComponent
*/
const TInt KEComErrMismatchedTags					= -17023;

/**
@internalComponent
*/
const TInt KEComErrInstantiationPointerNotFound		= -17024;

/**
@internalComponent
*/
const TInt KEComErrInstantiationPointerNotAvailable = -17025;

#endif	// __ECOMERRORCODES_H__