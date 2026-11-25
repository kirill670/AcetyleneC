/*
 * =========================================================================
 *  Name     : SenCredential.h
 *  Part of  : SenServiceDescription
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/SenCredential.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.7 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */



#ifndef SEN_CREDENTIAL_H
#define SEN_CREDENTIAL_H

#include <e32base.h>
#include <s32strm.h>

#include <SenBaseFragment.h>

//typedef RPointerArray<CCredential> RCredentialList;

// FORWARD DECLARATIONS
class SenDateUtils;


_LIT(KCredentialsName, "Credentials");
_LIT(KEndpointName, "Endpoint");
_LIT(KSecurityMechIdName, "SecurityMechID");
_LIT(KNotOnOrAfterName, "NotOnOrAfter");
_LIT(KConditionsName, "Conditions");

class CSenCredential : public CSenBaseFragment
    {
public:
	IMPORT_C static CSenCredential* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs);
	
	IMPORT_C static CSenCredential* NewLC(
		const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs);

	IMPORT_C static CSenCredential* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs,
		CSenElement& aParent
        );

	IMPORT_C static CSenCredential* NewL(const CSenCredential& aCredential);

	IMPORT_C TDesC* Id();

	IMPORT_C TTime& ValidUntil();

	IMPORT_C void SetValidUntil(TTime& aTime);
	
	IMPORT_C TBool SupportsMechanismL(const TDesC& aURI);

	IMPORT_C void CopyFromL(const CSenCredential& aCredential);

	IMPORT_C virtual ~CSenCredential();

protected: // data
    // These methods are invoked and TRAP-ped by their non-leaving variant.
    IMPORT_C virtual void StartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );


private:
	IMPORT_C void ConstructL(const TDesC& aNsUri, const TDesC& aLocalName,
					const TDesC& aQName, MXMLAttributes* aAttrs);
	IMPORT_C void ConstructL(const TDesC& aNsUri, const TDesC&  aLocalName,
					const TDesC& aQName, MXMLAttributes* aAttrs, CSenElement& aParent);

	IMPORT_C void ConstructL(CSenCredential& aCredential);
	IMPORT_C CSenCredential();

	// Setter for Credential ID
	void SetIdL(TPtrC aId);


	HBufC* iId;
	TTime iNotOnOrAfter; // note: Use SenDateUtils to convert from xml string val to ttime

	};


#endif // SEN_CREDENTIAL_H