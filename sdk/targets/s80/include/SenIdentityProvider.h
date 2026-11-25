/*
 * =========================================================================
 *  Name     : SenIdentityProvider.h
 *  Part of  : SenServiceDescription
 *  Created  : 2004-06-07 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/SenIdentityProvider.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.2 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * ======================================================================= =
 */

#ifndef SEN_IDENTITY_PROVIDER_H
#define SEN_IDENTITY_PROVIDER_H

#include <SenXmlServiceDescription.h>

// DEFINES
_LIT(KIdentityProvider, "IdentityProvider");
//_LIT8(KIdentityProviderName, "IdentityProvider");
_LIT(KSomeIMEI, "012345678901234");

_LIT(KContract, "urn:liberty:as:2004-04");

_LIT8(KImei, "IMEI");
_LIT8(KType, "type");
_LIT(KAuthzID, "AuthzID");
_LIT(KAdvisoryAuthnID, "AdvisoryAuthnID");
_LIT(KPassword, "Password");
_LIT(KProviderID, "ProviderID");

//FORWARD DECLARATIONS
class MSenCoreServiceManager;
class CSenHttpChannel;

class CSenIdentityProvider :
    public CSenXmlServiceDescription
{
public:

    /**
     * Two-phased constructor.
     */
	// TODO: comment these out and use the ref constructors instead (next below)
	IMPORT_C static CSenIdentityProvider* NewL(TDesC* aEndPoint=NULL, TDesC* aContract=NULL);
	IMPORT_C static CSenIdentityProvider* NewLC(TDesC* aEndPoint=NULL, TDesC* aContract=NULL);

    /**
     * Two-phased constructor.
     *
	 * Note: contract defaults here to "urn:liberty:as:2004-04"
     * @param		aEndpoint the service endpoint.
     */
	IMPORT_C static CSenIdentityProvider* NewL( TDesC& aEndpoint );
	IMPORT_C static CSenIdentityProvider* NewLC( TDesC& aEndpoint );

    /**
     * Two-phased constructor.
     *
     * @param		aEndpoint a service endpoint.
     * @param		aContract a service.
     */
	IMPORT_C static CSenIdentityProvider* NewL( TDesC& aEndpoint, TDesC& aContract );
	IMPORT_C static CSenIdentityProvider* NewLC( TDesC& aEndpoint, TDesC& aContract );

	IMPORT_C const TDesC& NewElementName();
    /**
     * Default destructor.
     *
	 */
	IMPORT_C virtual ~CSenIdentityProvider();

    /**
     * A getter.
     *
	 * @return a pointer to authorization id
     */
	IMPORT_C virtual const TPtrC AuthzID();

    /**
     * A getter.
     *
	 * @return a pointer to advisory authentication id
     */
	IMPORT_C virtual const TPtrC AdvisoryAuthnID();

    /**
     * A getter.
     *
	 * @return a pointer to provider id
     */
	IMPORT_C const TPtrC ProviderID();

    /**
     * A getter.
     *
	 * @return a pointer to password
     */
	IMPORT_C virtual const TPtrC Password();

    /**
     * A getter.
     *
	 * @return a pointer to IMEI
     */
	IMPORT_C const TDesC* IMEI();

    /**
     * A getter.
     *
	 * @return a pointer to username
     */
	IMPORT_C const TPtrC UserName();


	/**
	 * Setter
	 *
	 * @param aProviderID the setted id
	 * @return Status/error code
	 */
	IMPORT_C TInt SetProviderID( const TDesC& aProviderID );

	/**
	 * Return true if the ServiceDescription, i.e. its endpoint
	 * or contract, is associated to this IdentityProvider.
	 * Also return true if the ServiceDescription is about this
	 * IdentityProvider.
	 *
	 * @param aService
	 * @return
	 */
	IMPORT_C TBool IsTrustedByL( MSenServiceDescription& aServiceDescription );

	/**
	 * Return true if the ServiceDescription, i.e. its endpoint
	 * or contract, is associated to this IdentityProvider.
	 * Also return true if the ServiceDescription is about this
	 * IdentityProvider.
	 *
	 * @param aService
	 * @return
	 */
	IMPORT_C TBool IsTrustedByL( TDesC8& aProviderID );

    /**
     * Checks the default value.
     *
	 * @return bolean value indicating the state.
     */
	IMPORT_C TBool IsDefault();

    /**
     * Sets the user information.
     *
     * Status codes:
     * KErrNone						ok
	 *
     * Other codes are system error codes
	 *
	 * @param aAuthzID Authorization id.
	 * @param aAdvisoryAuthnID Advisory authorization id.
	 * @param aPassword Password.
	 *
	 * @return status/error code.
     */
	IMPORT_C TInt SetUserInfo( const TDesC& aAuthzID, 
							   const TDesC& aAdvisoryAuthnID, 
							   const TDesC& aPassword );
	
	IMPORT_C HBufC8* HttpCredentialsL(MSenCoreServiceManager& aMgr);

protected:
	IMPORT_C CSenIdentityProvider(TDescriptionClassType aType);
	IMPORT_C void ConstructL(TDesC* aEndPoint=NULL, TDesC* aContract=NULL);

	void ConstructL(TDesC& aEndPoint);
	void ConstructL(TDesC& aEndPoint, TDesC& aContract);

private: // date
};

#endif // SEN_IDENTITY_PROVIDER_H
