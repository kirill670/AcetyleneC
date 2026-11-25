/*
 * =========================================================================
 *  Name     : SenServicePattern.h
 *  Part of  : SenServicePattern
 *  Created  : 2004-07-27 by Nokia
 *
 *  Descr.   : This class extends the functionality of XML service description
 *             by offering the consumer policy interface methods. This class
 *             is typically used by Basic (Vanilla) Web Service frameworks,
 *             which _know_ (often strictly), which policy to use with the
 *             communication with custom WSP. For example, a Basic Web Service
 *             consumer application might want to strictly define certain 
 *             Internet Access Point (IAP) to be used for the connection being
 *             intialized. Such an application can simply instantiate new 
 *             ServicePattern and set the (often pre-known) IAP into it.
 *
 *             The main purpose of this class is to simplify the initialization
 *             of service connections for Vanilla Web Services.
 *
 *             It is important to note, that all the policy information entered
 *             via ServicePattern extending the MSenConsumerPolicy is treated
 *             in "policy-per-client" terms. In other words, any consumer
 *             policy information will not be stored for latter use of other
 *             applications (even they might happen to use same WSP and contract!).
 *
 *             This is due the nature of Service Pattern: it acts as a consumer
 *             originated filter, after which a service will be resolved. 
 *             Any service which "meets" the Service Pattern "constraints", is
 *             considered as a "match", because such service accepts this
 *             (search) pattern used.
 *              
 *             
 *
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/SenServicePattern.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.5 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */


#ifndef SEN_SERVICE_PATTERN_H
#define SEN_SERVICE_PATTERN_H

#include <e32base.h>
#include <s32strm.h>

#include <SenXmlServiceDescription.h>
#include <MSenConsumerPolicy.h>

// FORWARD DECLARATIONS
class CSenConsumerPolicy;

class CSenServicePattern 
:		public CSenXmlServiceDescription, 
		public MSenConsumerPolicy
	
    {
public: // standard EPOC 2 phase constructors
	IMPORT_C static CSenServicePattern* NewL();
	IMPORT_C static CSenServicePattern* NewLC();

	IMPORT_C static CSenServicePattern* NewL(
		const TDesC& aNamespaceURI);
	IMPORT_C static CSenServicePattern* NewLC(
		const TDesC& aNamespaceURI);

	IMPORT_C static CSenServicePattern* NewL(
		const TDesC& aEndPoint, const TDesC& aContract);
	IMPORT_C static CSenServicePattern* NewLC(
		const TDesC& aEndPoint, const TDesC& aContract);	

public: // destructor
	IMPORT_C virtual ~CSenServicePattern();

public: // overrides from MSenServiceDescription
	IMPORT_C TBool Matches(MSenServiceDescription& aServicePattern);

public: // overrides CSenXmlServiceDescription
	IMPORT_C void StartElementL(const TDesC& aNsUri,
							const TDesC& aLocalName,
							const TDesC& aQName,
							MXMLAttributes* apAttrs);

	// convenience method for writing out the consumer policy as XML 
public:
	IMPORT_C HBufC* ConsumerPolicyAsXml();

//public: // from MSenServicePattern
//	IMPORT_C virtual TBool MatchesWith(MSenServicePattern& aServicePattern);
//	IMPORT_C MSenServiceDescription& AsServiceDescription();
// 	IMPORT_C MSenConsumerPolicy& AsConsumerPolicy();

public: // from MSenConsumerPolicy
		// setter for Internet Access Point (IAP) ID
	IMPORT_C virtual void SetConsumerIapIdL(TUint32 aIapId);

	// getter for IAP ID
	IMPORT_C virtual TInt ConsumerIapId(TUint32& aCurrentIapId);

	// Setter: overrides current values with the given values from the array
	IMPORT_C virtual void SetConsumerIdentityProviderIdsL(
								CSenIdentityProviderIdArray& aList);

	// Adder: adds a new IDP ID value at the end of the current list value(s)
	// Does not insert duplicate values. 
	//
	// @return KErrAlreadyExists, if a duplicate is tried to add
	//		   KErrArgument if a zero-length descriptor is tried to add 
	//         (aProviderId.Length() == 0)
	IMPORT_C virtual TInt AddConsumerIdentityProviderIdL(TDesC& aProviderId);

	// Getter: return an empty array if no IDP:s have been spesified
	// or a list of IDP arrays if such value(s) have been set.
	IMPORT_C virtual const CSenIdentityProviderIdArray& ConsumerIdentityProviderIdsL();

	IMPORT_C virtual TBool AcceptsConsumerPolicy(MSenConsumerPolicy& aPolicyPattern);

	IMPORT_C virtual TInt RebuildFromConsumerPolicy(MSenConsumerPolicy& aTemplate);


protected: // constructors
	IMPORT_C CSenServicePattern(MSenServiceDescription::TDescriptionClassType aType);
	IMPORT_C void BaseConstructL();
	IMPORT_C void BaseConstructL(const TDesC& aNamespaceURI);
	IMPORT_C void BaseConstructL(const TDesC& aEndPoint, const TDesC& aContract);

protected: // data
	CSenConsumerPolicy* iConsumerPolicy;
	};

#endif SEN_SERVICE_PATTERN_H