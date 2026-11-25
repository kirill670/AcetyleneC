// TCTTOKENHANDLE.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __TCTTOKENHANDLE_H__
#define __TCTTOKENHANDLE_H__

#include <e32std.h>

/**@ingroup ct */
/**@{ */

/**
 * This class defines a handle to a subclass of the MCTToken class. 
 *
 * The handle identifies the class, not a particular instance of that class.
 * It is guaranted to be unique within the context of a specific device
 * (i.e. mobile phone, ...).
 *
 * The handle is especially useful for communication across process boundaries.
 * A process A can open a token T, get a handle to it, give that handle to process B.
 * B can then try to open the token T using that handle.
 */
class TCTTokenHandle
	{
public:
	/**
	 * This creates an invalid handle. An invalid handle has a iTokenTypeUid and
	 * a iTokenId equal to 0.
	 */
	IMPORT_C TCTTokenHandle();
	/**
	 * This creates a handle.
	 * @param aTokenTypeUid The value of the TokenType Uid.
	 * @param aTokenId The id of the Token.
	 */
	IMPORT_C TCTTokenHandle(TUid aTokenTypeUid, TInt aTokenId);
	/**
	 * The copy constructor.
	 */
	IMPORT_C TCTTokenHandle(const TCTTokenHandle& aTokenHandle);

	/** Equality operator */
	IMPORT_C TBool operator ==(const TCTTokenHandle& aTokenHandle) const;
	/** Inequality operator */
	inline TBool operator !=(const TCTTokenHandle& aTokenHandle) const;

public:
	/**
	 * The uid of the TokenType. This identifies which TokenType the Token
	 * belongs to.
	 */
	TUid iTokenTypeUid;
	/**
	 * The id of the Token. This id is unique within the context of a TokenType.
	 */
	TInt iTokenId;
	};

inline TBool TCTTokenHandle::operator !=(const TCTTokenHandle& aTokenHandle) const
	{
	return !(*this == aTokenHandle);
	}
///@}
#endif
