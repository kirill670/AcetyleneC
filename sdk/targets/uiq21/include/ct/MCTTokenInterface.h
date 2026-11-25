// Copyright (c) Symbian Ltd 2001

#ifndef __MCTTOKENINTERFACE_H__
#define __MCTTOKENINTERFACE_H__

/**@ingroup ct */
/**@{ */

/** The base class for all token interfaces. This class provides
	functionality to interact with the token's reference counting
	framework. (Interfaces themselves are not reference counted, but
	the token must remain open while it has open interfaces */

class MCTTokenInterface
	{
public:
	/** Returns the associated token */
	virtual MCTToken& Token() = 0;

	/** Destroys the object. Also takes care of reference counting the token.
	 */
	IMPORT_C void Release();

protected:
	/** This function should release the interface and all its owned
		resources. Called by Release. The default implementation
		simply does a 'delete this'. If other behaviour is required
		(for instance to implement a reference counting system for the
		interfaces themselves, interfaces can override this. */
	IMPORT_C virtual void DoRelease();

	/** The interface should be destroyed via the Release
		method. Hence this destructor is protected */
	inline virtual ~MCTTokenInterface() = 0;
	};

inline MCTTokenInterface::~MCTTokenInterface()
	{
	}
///@}
#endif // __MCTTOKENINTERFACE_H__
