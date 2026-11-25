/*
 * =========================================================================
 *  Name     : SenXmlServiceDescription.h
 *  Part of  : SenServiceDescription
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/SenXmlServiceDescription.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.12 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */



#ifndef SEN_XML_SERVICE_DESCRIPTION_H
#define SEN_XML_SERVICE_DESCRIPTION_H


#include <e32base.h>
#include <e32des8.h>
#include <e32std.h>


#include <MSenServiceDescription.h>
#include <MSenProviderPolicy.h>

#include <SenDomFragment.h>

// CONSTANTS
const TInt KStateParsingCredentials			= 12;
const TInt KStateParsingSingleCredential	= 122;
const TInt KStateParsingProviderPolicy		= 1222;


// FORWARD DECLARATIONS
class CSenCredential;
class CSenProviderPolicy;

// TYPE DEFINITIONS
typedef RPointerArray<CSenCredential> RCredentialList;



// CLASS DECLARATION
class CSenXmlServiceDescription : 
	public CSenDomFragment,
	public MSenServiceDescription,
	public MSenProviderPolicy
    {
public: // class type getter
	IMPORT_C const TDescriptionClassType DescriptionClassType();


public: // standard EPOC 2 phase constructors
	IMPORT_C static CSenXmlServiceDescription* NewL();
	IMPORT_C static CSenXmlServiceDescription* NewLC();

	IMPORT_C static CSenXmlServiceDescription* NewL(
		const TDesC& aNamespaceURI);
	IMPORT_C static CSenXmlServiceDescription* NewLC(
		const TDesC& aNamespaceURI);

	IMPORT_C static CSenXmlServiceDescription* NewL(
		const TDesC& aEndPoint, const TDesC& aContract);
	IMPORT_C static CSenXmlServiceDescription* NewLC(
		const TDesC& aEndPoint, const TDesC& aContract);

public: // From MSenProviderPolicy

	// Setter for Internet Access Point (IAP) ID
	IMPORT_C virtual void SetIapIdL(TUint32 aIapId);

	// Getter for IAP ID
	IMPORT_C virtual TInt IapId(TUint32& aCurrentIapId);

	// Setter: overrides current values with the given values from the array
	IMPORT_C virtual void SetIdentityProviderIdsL(
		CSenIdentityProviderIdArray& aList);

	// Adder: adds a new IDP ID value at the end of the current list value(s)
	// Checks for duplicate (does not insert new ID elements with equal content)
	// @return KErrAlreadyExists, if a duplicate is tried to add
	//		   KErrArgument if a zero-length descriptor is tried to add 
	//         (aProviderId.Length() == 0)
	IMPORT_C virtual TInt AddIdentityProviderIdL(TDesC& aProviderId);

	// sets (rebuilds) the IAP ID and IDP ID list values from template 
	IMPORT_C virtual TInt RebuildFrom(MSenProviderPolicy& aTemplate);

	// Getter: return an empty array if no IDP:s have been spesified
	// or a list of IDP arrays if such value(s) have been set.
	IMPORT_C virtual const CSenIdentityProviderIdArray& IdentityProviderIdsL();

	IMPORT_C virtual TBool Accepts(MSenProviderPolicy& aPolicyPattern);


	
public: // From MSenServiceDescription
	IMPORT_C TBool Matches(MSenServiceDescription& aPattern);

	// Getters
	IMPORT_C const TPtrC Contract();
	IMPORT_C const TPtrC EndPoint();
	IMPORT_C const TDesC& FrameworkId();
	IMPORT_C HBufC*	FrameworkVersionL();

	// Setters
	IMPORT_C void SetContractL(TPtrC aContract);
	IMPORT_C void SetEndPointL(TPtrC aEndPoint);

	// The developer may use a FrameworkId to search for a session of 
	// (i.e. connection to) a certain service invokation framework.
	// If not set (or set to NULL), then any matching framework 
	// may be used. 
	
	// NOTE: Basic Web Services MUST provide "NONE" as
	// a FrameworkId in order to obtain connection(!)
	IMPORT_C void SetFrameworkIdL(TDesC* aFrameworkId);

	IMPORT_C TInt WriteAsXMLToL(HBufC*& aTo);
	IMPORT_C TInt WriteAsXMLUtf8ToL(HBufC8*& aTo);

	IMPORT_C virtual ~CSenXmlServiceDescription();

public: // Overridden SenBaseFragment methods:
	IMPORT_C void SetAttributesL(MXMLAttributes* aAttrs);
	IMPORT_C virtual const TDesC& NewElementName();

	IMPORT_C void ResumeParsingFromL(
		const TDesC& aNsUri,
		const TDesC& aLocalName,
		const TDesC& aQName);

public: // New methods
	IMPORT_C  RCredentialList& Credentials();

protected: // Constructors
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(const TDesC& aNamespaceURI); 
	IMPORT_C void ConstructL(const TDesC& aEndPoint, const TDesC& aContract); 
	IMPORT_C CSenXmlServiceDescription(TDescriptionClassType aType);

protected: // Overridden SenBaseFragment methods:
    // These methods are invoked and TRAP-ped by their non-leaving variant.
    IMPORT_C virtual void StartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );
    IMPORT_C virtual void EndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );


protected: // Data
	const TDescriptionClassType iType; // todo: use TInt instead; to support new types

private: // Data

	HBufC*						iFrameworkId;
	CSenCredential*				iCredential;
	RCredentialList				iCredentialList;

	// Note: Using SenDateUtils FromXmlDateTimeL 
	// and ToXmlDateTimeL is recommended..
	TTime						iNotOnOrAfter;

	CSenProviderPolicy*			iProviderPolicy;


   };

#endif // SEN_XML_SERVICE_DESCRIPTION_H

