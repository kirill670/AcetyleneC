/*
 * =========================================================================
 *  Name     : MSenProviderPolicy.h
 *  Part of  : MSenProviderPolicy
 *  Created  : 2004-08-05 by Nokia
 *  Descr.   :
 *
 *  Version : 
 *   $Source: /projects/serene/sen/ServiceDescription/inc/MSenProviderPolicy.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.4 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef M_SEN_PROVIDER_POLICY_H
#define M_SEN_PROVIDER_POLICY_H

//  INCLUDES
#include <e32base.h> // for CActive
#include <badesca.h>

#include <SenDomFragment.h>

// FORWARD DECLARATION
class CSenIdentityProviderIdArray;


 /**********************************************************************
	Example structure of ProviderPolicy XML fragment:

	<ProviderPolicy>
		<Transport>
			<IapId>
				1234567890
			</IapId>
		</Transport>
		<IdentityProviderIDs strict="true">
		    <IdentityProviderID>
			  urn:first.id.example.com
			</IdentityProviderID>
		    <IdentityProviderID>
			  urn:second.id.example.com
			</IdentityProviderID>
		</IdentityProviderIDs>
	</ProviderPolicy>
  **********************************************************************/

// CLASS DECLARATION
class MSenProviderPolicy
    {
public: 

	// setter for Internet Access Point (IAP) ID
	IMPORT_C virtual void SetIapIdL(TUint32 aIapId) = 0;

	// getter for IAP ID
	IMPORT_C virtual TInt IapId(TUint32& aCurrentIapId) = 0;

	// Setter: overrides current values with the given values from the array
	IMPORT_C virtual void SetIdentityProviderIdsL(CSenIdentityProviderIdArray& aList) = 0;

	// Adder: adds a new IDP ID value at the end of the current list value(s)
	// Does not insert duplicate values. 
	//
	// @return KErrAlreadyExists, if a duplicate is tried to add
	//		   KErrArgument if a zero-length descriptor is tried to add 
	//         (aProviderId.Length() == 0)
	IMPORT_C virtual TInt AddIdentityProviderIdL(TDesC& aProviderId) = 0;

	// initializes the state of the policy from another policy
	IMPORT_C virtual TInt RebuildFrom(MSenProviderPolicy& aTemplate) = 0;

	// Getter: return an empty array if no IDP:s have been spesified
	// or a list of IDP arrays if such value(s) have been set.
	IMPORT_C virtual const CSenIdentityProviderIdArray& IdentityProviderIdsL() = 0;

	IMPORT_C virtual TBool Accepts(MSenProviderPolicy& aPolicyPattern) = 0;

    };

#endif //M_SEN_PROVIDER_POLICY_H
            
// End of File
