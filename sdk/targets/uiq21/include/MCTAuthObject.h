// Copyright (c) Symbian Ltd 2001

#ifndef __MCTAOSTORE_H__
#define __MCTAOSTORE_H__

#include <ct.h>

///@file


/** The UID for the authentication object interface */
const TInt KCTInterfaceAuthenticationObject = 0x101F51AE;

/** @ingroup interfaces */
/* @{ */

/** The status of an authentication object */
enum TCTAuthenticationStatus
	{
	/** The authentication object is enabled. If false, the objects
		protected by this authentication object can be accessed without
		authentication */
	EEnabled		= 0x80,
	/** The reference data cannot be changed */
	EChangeDisabled	= 0x40,
	/** The authentication cannot be unblocked */
	EUnblockDisabled	= 0x20,
	/** The authentication object can be diabled */
	EDisableAllowed	= 0x10
	};	
///@}
/** @ingroup interfaces */
/* @{ */

/**
This class allows authentication objects to be queried and
manipulated. Authentication objects are obtained from the
MCTAuthenticationObjectList class, which is the class returned as the
token interface.
*/
class MCTAuthenticationObject: public MCTTokenObject
	{
public:
	/** Constructor */
	inline MCTAuthenticationObject(MCTToken& aToken);
	///@name Listing Protected Objects
	///@{
    /**
	   Returns a list of all the objects which this authentication
	   object protects.
	   @param aObjects The returned objects will be appended to this array.
	   @param aStatus Completed with the return code when the
	   operation completes.
	*/
	virtual void ListProtectedObjects(RMPointerArray<MCTTokenObject>& aObjects, TRequestStatus& aStatus) = 0;
	/** Cancel an ongoing ListProtectedObjects operation
	 */
	virtual void CancelListProtectedObjects() = 0;
	///@}

	///@name Changing the reference data
	///@{
    /**
	   Change the reference data (e.g. PIN value).  The security
	   dialog component will prompt for the old and new reference
	   data.
	   @param aStatus Completed with the return code when the
	   operation completes.
	*/
	virtual void ChangeReferenceData(TRequestStatus &aStatus) = 0;
	/** Cancel an ongoing ChangeReferenceData operation
	 */
	virtual void CancelChangeReferenceData() = 0;
	///@}

	///@name Unblocking
	///@{
   /**
	  Unblock the authentication object.  The security dialog
	  component will prompt for the unblocking authentication object.
	   @param aStatus Completed with the return code when the
	   operation completes.
   */
	virtual void Unblock(TRequestStatus &aStatus) = 0;
	/** Cancel an ongoing Unblock operation
	 */
	virtual void CancelUnblock() = 0;
	///@}

    /**
	   Get the status of the authentication object. See
	   TCTAuthenticationStatus for the format of the return value.
	*/
	virtual TUint32 Status() const = 0;

	///@name Enabling and Disabling
	///@{
    /**
	   Disables the authentication object.
	   @param aStatus Completed with the return code when the
	   operation completes.
	*/
	virtual void Disable(TRequestStatus &aStatus) = 0;
	/** Cancel an ongoing Disable operation
	 */
	virtual void CancelDisable() = 0;
    /**
	   Enables the authentication object.
	   @param aStatus Completed with the return code when the
	   operation completes.
	*/
	virtual void Enable(TRequestStatus &aStatus) = 0;
	/** Cancel an ongoing Enable operation
	 */
	virtual void CancelEnable() = 0;
	///@}
	};
///@}
/** @ingroup interfaces */
/* @{ */

/** 
This interface enables clients to list all the authentication objects on a token, find out which objects they protect,
 and change/unblock/enable/disable them. 

It may be used to implement a 'PIN manager' control panel item. This could list the PINs (by label), 
allow one to be selected, list what it is used for (including information such as what operations on that object 
are protected by that PIN), and then allow the user to change, enable, disable and unblock the PIN.

Note that no PINs appear anywhere in this API. The code implementing this API will display a PIN dialog via the 
secure dialog interface when a PIN is required. 

The main advantage of this is that if some hostile code does capture a PIN, it can't do anything with it as none 
of the APIs take a PIN. A secondary benefit is that the same API would work with biometrics or other methods of 
authentication.
*/
class MAuthenticationObjectList
	{
public:	
	/** List all the authenticaiton objects in the token.
		@param aAuthObjects The returned authentication objects will
		be appended to this array
		@param aStatus This will be completed with the final status code
		*/
	virtual void List(RMPointerArray<MCTAuthenticationObject>& aAuthObjects,	TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing List operation */
	virtual void CancelList() = 0;
	};


class MCTAuthenticationObjectList : public MCTTokenInterface, 
									public MAuthenticationObjectList
	{
	};

inline MCTAuthenticationObject::MCTAuthenticationObject(MCTToken& aToken)
		: MCTTokenObject(aToken)
	{
	}
///@}
#endif //__MCTAOSTORE_H__


