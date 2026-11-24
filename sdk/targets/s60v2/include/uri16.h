// Uri16.h
//
// Copyright (c) Symbian Software Ltd 2001-2004. All rights reserved.
//

/**
	@file Uri16.h
	Comments :	This file contains the API definition for the classes TUriC16 and 
				CUri16. These classes provide non-modifying (TUriC16) and modifying
				(CUri16) functionality for the components of a Uri as described in 
				RFC2396.
 */

#ifndef __URI16_H__
#define __URI16_H__

// System includes
//
#include <e32base.h>
#include <f32file.h> 

// Local includes
//
#include "uricommon.h"

class TUriC16
/**
	Dependencies : TUriComponent.
	Comments : Provides non-modifying functionality on the components of a uri object as
	defined in RFC2396. There are 5 components; scheme, authority, path, query and fragment.

The	object holds descriptor pointers to the parsed uri components and a descriptor pointer 
to the uri. It is non-owning. It uses 16-bit descriptors.

	The functionality provided by this API allows the uri components to be extracted from the 
	parsed uri, checked for their presence in the uri and be compared with those in another 
	TUriC16 object.
	@publishedAll
	@released
	@since 6.0
*/
	{
public:	// Methods

	IMPORT_C HBufC* GetFileNameL() const;
	IMPORT_C HBufC* GetFileNameL(TUriFileName aType) const;
/**
	@fn				Extract(TUriComponent aComponent) const
	Intended Usage	:	Retrieves the specified component in the uri.
	@since			6.0
	@param			aComponent	The enum specifying the component.
	@return			A constant reference to a descriptor pointer to the specified component.
 */
	IMPORT_C const TDesC16& Extract(TUriComponent aComponent) const;

/**
	@fn				UriWithoutFragment(TPtrC16& aUriNoFrag) const
	Intended Usage	:	Retrieves the uri without the fragment component.
	@since			6.0
	@param			aUriNoFrag	An output parameter which is set the non-reference 
	version of the uri.
 */
	IMPORT_C void UriWithoutFragment(TPtrC16& aUriNoFrag) const;

/**
	@fn				IsPresent(TUriComponent aComponent) const
	Intended Usage	:	Indicates whether the specified component is present in the uri.
	@since			6.0
	@param			aComponent	The enum specifying the component.
	@return			A boolean value of ETrue if the desired component is present, 
	or EFalse if the desired component is not present.
 */
	IMPORT_C TBool IsPresent(TUriComponent aComponent) const;

/**
	@fn				IsSchemeValid() const
	Intended Usage	:	Checks to see if the scheme is valid. If there is no scheme then
	the return value indicates an invalid scheme (EFalse).
	@since			6.0
	@return			A boolean value of ETrue if the scheme is valid, or EFalse if
	the scheme is not.
 */
	IMPORT_C TBool IsSchemeValid() const;

/**
	@fn				Compare(const TUriC16& aUri, TUriComponent aComponent) const
	Intended Usage	:	Compares the specified component against the one in the uri passed in.
	@since			6.0
	@param			aUri		The uri to compare components against.
	@param			aComponent	The enum specifying the component to compare.
	@return			An integer value of zero if the components are the same, any other
	value if the components are not the same.
 */
	IMPORT_C TInt Compare(const TUriC16& aUri, TUriComponent aComponent) const;

/**
	@fn				UriDes() const
	Intended Usage	:	Retrieves the descriptor for the entire uri.
	@since			6.0
	@return			A const reference to a descriptor pointer to the uri.
 */
	IMPORT_C const TDesC16& UriDes() const;

	IMPORT_C TInt Validate() const;
	IMPORT_C TBool Equivalent(const TUriC16& aUri) const;

protected:	// Methods

/**
	@fn				TUriC16()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TUriC16();

/**
	@fn				Reset()
	Intended Usage	:	Resets the descriptor pointers for the uri components and the uri.
	@since			6.0
	@post			All uri component information is removed and the uri descriptor is 
	set to NULL.
 */
	void Reset();
	
private:	// Methods
	
	TInt ValidateL() const;
	TInt EquivalentL(const TDesC16& aUri) const;

protected:	// Attributes

	/** The array of descriptor pointers to the uri components.
	 */
	TPtrC16		iComponent[EUriMaxComponents];

	/** The descriptor pointer to the uri.
	 */
	TPtrC16		iUriDes;

/**
	A friend class.
	@see		CUri16 
	@since		6.0
	@cat		Friend class
 */
	friend class CUri16;

/**
	A friend class used for testing.
	@see		TUriC16StateAccessor
	@since		6.0
	@cat		Friend class
	@internal
 */
	friend class TUriC16StateAccessor;

	};

class TUriParser16 : public TUriC16
/**
@class TUriParser16
Dependencies : TUriC16
Comments : Provides functionality to parse a descriptor into the components of a uri as 
defined in RFC2396. There are 5 components; scheme, authority, path, query and fragment.

It uses 16-bit descriptors.

Format of a uri is; scheme://authority path?query\#fragment

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
	@fn				TUriParser16()
	Intended Usage	:	Constructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C TUriParser16();

/**
	@fn				Parse(const TDesC16& aUri)
	Intended Usage	:	Parses the descriptor aUri into uri components.
	@since			6.0
	@param			aUri A reference to a descriptor pointer to be parsed.
	@return			KErrNone if the descriptor has been parsed into uri components.
	EUriParserErrInvalidUri if the descriptor is an invalid uri.
	@post			The object references the input descriptor.
 */
	IMPORT_C TInt Parse(const TDesC16& aUri);

	};

class CUri16 : public CBase
/**
	Dependencies : CBase, TUriC16.
	Comments : Provides modifying functionality on the components of a uri object, as
	defined in RFC2396. There are 5 components; scheme. authority, path, query and fragment.

	The	object holds parsed uri information. It is owning. It uses 16-bit descriptors.

	The functionality provided by this API allows the uri components to be set or removed 
	from this parsed uri. Also, it provides a reference to TUriC16 object so that the non-modifying 
	functionality can be used.
	@publishedAll
	@released
	@since 6.0
*/
	{
public: // Methods
	IMPORT_C static CUri16* CreateFileUriL(const TDesC& aFullFileName, TUint aFlags = 0);

	IMPORT_C static CUri16* CreatePrivateFileUriL(const TDesC& aRelativeFileName, TDriveNumber aDrive, TInt aFlags = 0);

/**
	@fn				NewL(const TUriC16& aUri)
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves nothing on the CleanupStack. Creates a uri object which is a copy of the 
	input parameter aUri.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aUri	A reference to a parsed uri object.
	@return			A pointer to the newly created CUri16 object. 
	@post			A fully constructed and initialized CUri16 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CUri16* NewL(const TUriC16& aUri);

/**
	@fn				NewLC(const TUriC16& aUri)
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves a pointer to created object on the CleanupStack. Creates a uri object which 
	is a copy of the input parameter aUri.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aUri	A reference to a parsed uri object.
	@return			A pointer to the newly created CUri16 object. 
	@post			A fully constructed and initialized CUri16 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CUri16* NewLC(const TUriC16& aUri);

/**
	@fn				NewL()
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves nothing on the CleanupStack. Creates a uri object which is empty.
	@exception		KErrNoMemory.
	@since			6.0
	@return			A pointer to the newly created CUri16 object. 
	@post			A fully constructed and initialized CUri16 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CUri16* NewL();

/**
	@fn				NewLC()
	Intended Usage	:	Static factory constructor. Uses two phase construction and 
	leaves a pointer to created object on the CleanupStack. Creates a uri object which 
	is empty.
	@exception		KErrNoMemory.
	@since			6.0
	@return			A pointer to the newly created CUri16 object. 
	@post			A fully constructed and initialized CUri16 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CUri16* NewLC();

/**
	@fn				ResolveL(const TUriC16& aBaseUri, const TUriC16& aRefUri)
	Intended Usage	:	Static factory constructor. This creates a CUri16 object that is 
	an absolute uri resulting from a reference uri being resolved against a base uri.
	@warning		Ownership of created CUri16 object is transferred to caller.
	@exception		KErrNoMemory, KUriErrBadBasePath.
	@since			6.0
	@param			aBaseUri	A referece to the parsed base uri.
	@param			aRefUri		A referece to the parsed reference uri.
	@return			A pointer to the newly created CUri16 object.
	@pre 			The base uri must have an absolute or empty path, otherwise will leave
	with KUriErrBadBasePath.
	@post			A fully constructed and initialized CUri16 object.
	@cat			Construction and Destruction
 */
	IMPORT_C static CUri16* ResolveL(const TUriC16& aBaseUri, const TUriC16& aRefUri);

/**
	@fn				~CUri16()
	Intended Usage	:	Destructor.
	@since			6.0
	@cat			Construction and Destruction
 */
	IMPORT_C ~CUri16();

/**
	@fn				Uri() const
	Intended Usage	:	Provides a reference to the parsed uri. Allows access to the 
	non-modifying API for TUriC16.
	@since			6.0
	@return			A const reference to the parsed uri object.
 */
	IMPORT_C const TUriC16& Uri() const;

/**
	@fn				SetComponentL(const TDesC16& aData, TUriComponent aComponent)
	Intended Usage	:	Sets the specified component in the uri. The component is set 
	to the value given in the argument aData. If the specified component already exists  
	then it is replaced with the new value.
	@warning		The userinfo and port components can only be set if the host component
	is present. Setting these components without a host component present will have no 
	effect on the uri.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aData		A descriptor pointer to the new value for the uri component.
	@param			aComponent	An enum specifying the component to be set.
	@pre 			Object is fully constructed.
	@post			The uri has the specified component set to the new value.
 */
	IMPORT_C void SetComponentL(const TDesC16& aData, TUriComponent aComponent);

/**
	@fn				RemoveComponentL(TUriComponent aComponent)
	Intended Usage	:	Removes the specified component from the uri. If the component
	does not exist then this function does nothing.
	@warning		If host is removed, then userinfo and port components will also
	be removed.
	@exception		KErrNoMemory.
	@since			6.0
	@param			aComponent	An enum specifying the component to be removed.
	@pre 			Object is fully constructed.
	@post			The uri is updated to exclude the specified component.
 */
	IMPORT_C void RemoveComponentL(TUriComponent aComponent);

private:	// Methods

/**
	@fn				CUri16(const TUriC16& aNewUri)
	Intended Usage	:	Constructor. First phase of two-phase construction method. Does
	non-allocating construction.
	@since			6.0
	@param			aNewUri	The parsed uri component information from which to create
	the uri.
	@cat			Construction and Destruction
 */
	CUri16(const TUriC16& aNewUri);

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
	@fn				FormUriL()
	Intended Usage	:	Forms the uri from the parsed uri information. A copy of the 
	parsed uri is created. The parsed uri is changed to refer to the copy.
	@exception		KErrNoMemory.
	@since			6.0
	@pre 			The parsed uri information is set.
	@post			The uri buffer is updated with the parsed uri information.
 */
	void FormUriL();

	void InitializeFileUriComponentsL(const TDesC& aFileName, TDriveNumber aDrive, TUint aFlags);

private:	// Attributes

	/** The descriptor buffer that contains the uri.
	 */
	HBufC16*	iUriBuf;

	/** The parsed uri object.
	 */
	TUriC16	iUri;

/**
	A friend class used for testing.
	@see		TUri16StateAccessor
	@since		6.0
	@cat		Friend class
	@internal
 */
	friend class TUri16StateAccessor;

	};

typedef TUriC16			TUriC;
typedef TUriParser16	TUriParser;
typedef CUri16			CUri;

#endif	// __URI16_H__
