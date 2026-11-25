// Authority8.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file Authority8.h
	Comments :	This file contains the API definition for the classes TAuthorityC8 and
				CAuthority8. These classes provide non-modifying (TAuthorityC8) and 
				modifying (CAuthority8) functionality for the components of an
				Authority as described in RFC2396.
 */

#ifndef __AUTHORITY8_H__
#define __AUTHORITY8_H__

// System includes
//
#include <e32base.h>

// Local includes
//
#include "authoritycommon.h"

class TAuthorityC8
/**
@class TAuthorityC8
Dependencies : TAuthorityComponent.
Comments : Provides non-modifying functionality on the components of an authority 
object as defined in RFC2396. There are 3 components; userinfo, host and port.

The	object holds descriptor pointers to the parsed authority components and a descriptor 
pointer to the authority. It is non-owning. It uses 8-bit descriptors.

The functionality provided by this API allows the authority components to be extracted
from the parsed authority, checked for their presence in the authority and be compared 
with those in another TAuthorityC8 object.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				Extract(TAuthorityComponent aComponent) const
	Intended Usage	:	Retrieves the specified component in the authority.
	@since			6.0
	@param			aComponent	The enum specifying the component.
	@return			A constant reference to a descriptor pointer to the specified component.
 */
	IMPORT_C const TDesC8& Extract(TAuthorityComponent aComponent) const;

/**
	@fn				IsPresent(TComponent aComponent) const
	Intended Usage	:	Indicates whether the specified component is present in the authority.
	@since			6.0
	@param			aComponent	The enum specifying the component.
	@return			A boolean value of ETrue if the desired component is present, 
	or EFalse if the desired component is not present.
 */
	IMPORT_C TBool IsPresent(TAuthorityComponent aComponent) const;

/**
	@fn				Compare(const TAuthorityC8& aAuthority, TAuthorityComponent aComponent) const
	Intended Usage	:	Compares the specified component against the one in the authority passed in.
	@since			6.0
	@param			aAuthority	The authority to compare components against.
	@param			aComponent	The enum specifying the component to compare.
	@return			An integer value of zero if the components are the same, any other
	value if the components are not the same.
 */
	IMPORT_C TInt Compare(const TAuthorityC8& aAuthority, TAuthorityComponent aComponent) const;

/**
	@fn				AuthorityDes() const
	Intended Usage	:	Retrieves the descriptor for the entire authority.
	@since			6.0
	@return			A const reference to a descriptor pointer to the authority.
 */
	IMPORT_C const TDesC8& AuthorityDes() const;

protected:	// Methods

/**
	@fn				TAuthorityC8()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TAuthorityC8();

/**
	@fn				Reset()
	Intended Usage	:	Resets the descriptor pointers for the authority components 
	and the authority.
	@since			6.0
	@post			All authority component information is removed and the authority 
	descriptor is set to NULL.
 */
	void Reset();

protected:	// Attributes

	/** The array of descriptor pointers to the authority components.
	 */
	TPtrC8	iComponent[EAuthorityMaxComponents];

	/** The descriptor pointer to the authority.
	 */
	TPtrC8	iAuthorityDes;

/**
	A friend class.
	@see		CAuthority8
	@since		6.0
	@cat		Friend class
 */
	friend class CAuthority8;

/**
	A friend class used for testing.
	@see		TAuthorityC8StateAccessor
	@since		6.0
	@cat		Friend class
 */
	friend class TAuthorityC8StateAccessor;	

	};

class TAuthorityParser8 : public TAuthorityC8
/**
@class TAuthorityParser8
Dependencies : TAuthorityC8
Comments : Provides functionality to parse a descriptor into the components of an 
authority as defined in RFC2396. There are 3 components; userinfo, host and port.

This uses 8-bit descriptors.

Format of an authority is; [userinfo@]host[:port]

@warning The descriptor that is parsed by an object of this class will be referenced 
by that object. If the original descriptor is no longer in scope there will be undefined 
behaviour.
@publishedAll
@released
@since 6.0
*/
	{
public:	// Methods

/**
	@fn				TAuthorityParser8()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TAuthorityParser8();

/**
	@fn				Parse(const TDesC8& aAuthority)
	Intended Usage	:	Parses the descriptor aAuthority into authority components.
	@since			6.0
	@param			aAuthoritiy A reference to a descriptor pointer to be parsed.
	@return			KErrNone if the descriptor has been parsed into its authority components.
	@post			The object references the input descriptor.
 */
	IMPORT_C TInt Parse(const TDesC8& aAuthority);

	};

class CAuthority8 : public CBase
/**
@class CAuthority8
Dependencies : CBase, TAuthorityC8.
Comments : Provides modifying functionality on the components of an authority object, as
defined in RFC2396. There are 3 components; userinfo, host and port.

The	object holds parsed authority information. It is owning. It uses 8-bit descriptors.

The functionality provided by this API allows the authority components to be set or removed 
from this parsed authority. Also, it provides a reference to TAuthorityC8 object so that 
the non-modifying functionality can be used.
@publishedAll
@released
@since 6.0
*/
	{
public: // Methods

/**
	@fn				NewL(const TAuthorityC8& aAuthority)
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves nothing on the CleanupStack. Creates an authority object which is a copy 
	of the input parameter aAuthority.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aAuthority	A reference to a parsed authority object.
	@return			A pointer to the newly created CAuthority8 object. 
	@post			A fully constructed and initialized CAuthority8 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CAuthority8* NewL(const TAuthorityC8& aAuthority);

/**
	@fn				NewLC(const TAuthorityC8& aAuthority)
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves a pointer to created object on the CleanupStack. Creates an authority object 
	which is a copy of the input parameter aAuthority.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aAuthority	A reference to a parsed authority object.
	@return			A pointer to the newly created CAuthority8 object. 
	@post			A fully constructed and initialized CAuthority8 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CAuthority8* NewLC(const TAuthorityC8& aAuthority);

/**
	@fn				NewL()
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves nothing on the CleanupStack. Creates an authority object which is empty.
	@exception		KErrNoMemory.
	@since			6.0
	@return			A pointer to the newly created CAuthority8 object. 
	@post			A fully constructed and initialized CAuthority8 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CAuthority8* NewL();

/**
	@fn				NewLC()
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves a pointer to created object on the CleanupStack. Creates an authority object 
	which is empty.
	@exception		KErrNoMemory.
	@since			6.0
	@return			A pointer to the newly created CAuthority8 object. 
	@post			A fully constructed and initialized CAuthority8 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CAuthority8* NewLC();

/**
	@fn				~CAuthority8()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CAuthority8();

/**
	@fn				Authority() const
	Intended Usage	:	Provides a reference to the parsed authority. Allows access to the 
	non-modifying API for TAuthorityC8.
	@since			6.0
	@return			A const reference to the parsed authority object.
 */
	IMPORT_C const TAuthorityC8& Authority() const;

/**
	@fn				SetComponentL(const TDesC8& aData, TAuthorityComponent aComponent)
	Intended Usage	:	Sets the specified component in the authority. The component is set 
	to the value given in the argument aData. If the specified component already exists then 
	it is replaced with the new value.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aData		A descriptor pointer to the new value for the authority component.
	@param			aComponent	An enum specifying the component to be set.
	@pre 			Object is fully constructed.
	@post			The authority has the specified component set to the new value.
 */
	IMPORT_C void SetComponentL(const TDesC8& aData, TAuthorityComponent aComponent);

/**
	@fn				SetAndEscapeComponentL(const TDesC8& aData, TAuthorityComponent aComponent)
	Intended Usage	:	Escape encodes the component then sets the specified component
	in the authority. The component is set to the value given in the argument aData. 
	If the specified component already exists then it is replaced with the new value.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aData		A descriptor pointer to the new value for the authority component.
	@param			aComponent	An enum specifying the component to be set.
	@pre 			Object is fully constructed.
	@post			The authority has the specified component set to the new value.
 */
	IMPORT_C void SetAndEscapeComponentL(const TDesC8& aData, TAuthorityComponent aComponent);

/**
	@fn				RemoveComponentL(TAuthorityComponent aComponent)
	Intended Usage	:	Removes the specified component from the authority. If the component
	does not exist then this function does nothing.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aComponent	An enum specifying the component to be removed.
	@pre 			Object is fully constructed.
	@post			The authority is updated to exclude the specified component.
 */
	IMPORT_C void RemoveComponentL(TAuthorityComponent aComponent);

private:	// Methods

/**
	@fn				CAuthority8(const TAuthorityC8& aAuthority)
	Intended Usage	:	Constructor. First phase of two-phase construction method. 
	Does non-allocating construction.
	@param			aAuthority	The parsed authority component information from which 
	to create the authority.
	@since			6.0
	@cat			Construction and Destruction
 */
	CAuthority8(const TAuthorityC8& aAuthority);

/**
	@fn				ConstructL()
	Intended Usage	:	Second phase of two-phase construction method. Does any 
	allocations required to fully construct the object.
	@exception		KErrNoMemory.
	@since			6.0
	@pre 			First phase of construction is complete.
	@post			The object is fully constructed and initialized.
	@cat			Construction and Destruction
 */
	void ConstructL();

/**
	@fn				FormAuthorityL()
	Intended Usage	:	Forms the authority from the parsed authority information. 
	A copy of the parsed authority is created. The parsed authority is changed to 
	refer to the copy.
	@exception		KErrNoMemory.
	@since			6.0
	@pre 			The parsed authority information is set.
	@post			The authority buffer is a copy of the parsed authority, and the 
	parsed authority now refers to the copy.
 */
	void FormAuthorityL();

private:	// Attributes

	/** The descriptor buffer that contains the authority.
	 */
	HBufC8*			iAuthorityBuf;

	/** The parsed authority object.
	 */
	TAuthorityC8	iAuthority;

/**
	A friend class used for testing.
	@see		TAuthority8StateAccessor
	@since		6.0
	@cat		Friend class
 */
	friend class TAuthority8StateAccessor;

	};

#endif	// __AUTHORITY8_H__