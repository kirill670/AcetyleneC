// Copyright (c) Symbian 2001


#ifndef __MCTTOKENOBJECT_H__
#define __MCTTOKENOBJECT_H__

/**@ingroup ct */
/**@{ */

/** The base class for all token objects. Any object representing
   something managed via a particular token interface should be
   dereived from this class. It provides certain common attributes
   that all objects must have (Label, Type, Token, Handle) and code to
   interact with the token's reference counting code. Token objects
   themselves are not reference counted, but the token will not be
   closed while token objects from it remain in existence. (Token
   objects can implement their own reference counting framework if
   required)

*/
class MCTTokenObject 
	{
public:
	/** Releases the object. */
	IMPORT_C void Release();
	/** Returns the object's human-readable label */
	virtual const TDesC& Label() const = 0;
	/** Returns a reference to the associated token */
	virtual MCTToken& Token() const = 0;
	/** Returns a UID representing the type of the token object. The
		meanings of possible UIDs should be documented in the
		documentation for the interface that returns them. */
	virtual TUid Type() const = 0;
	/** Returns a handle for the object. The primary purpose of the
		handle is to allow token objects to be 'passed' between
		processes. See TCTTokenObjectHandle for more details.
	*/
	virtual TCTTokenObjectHandle Handle() const = 0;
 protected:
	/** Releases the object once the base-class framework work has
		been done. The default implementation simply does a 'delete
		this', but derived classes can substitute their own behaviour,
		for instance to implement reference counting of the token
		objects themselves.*/
	IMPORT_C virtual void DoRelease();
	/* Constructor. This needs a token in order to increment the
	   token's reference count.
	 */
	IMPORT_C MCTTokenObject(MCTToken& aToken);
	/** This destructor is protected as clients should use Release()
		instead. */
	inline virtual ~MCTTokenObject() = 0;
	};

inline MCTTokenObject::~MCTTokenObject()
	{
	}
///@}
#endif
