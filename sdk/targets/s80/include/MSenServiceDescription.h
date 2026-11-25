/*
 * =========================================================================
 *  Name     : MSenServiceDescription.h
 *  Part of  : SenServiceDescription
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/MSenServiceDescription.h,v $
 *   $Date: 2004/09/13 07:41:58 $
 *   $Revision: 1.7 $
 *   $Author: marmink $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */


#ifndef M_SEN_SERVICE_DESCRIPTION_H
#define M_SEN_SERVICE_DESCRIPTION_H

#include <e32base.h>
#include <e32des8.h>	// HBufC8

class MSenServiceDescription
    {

public: // DescriptionClassType enumeration. TODO: use TInt instead for extensability
	IMPORT_C enum TDescriptionClassType
		{
		ERoot = 0,
		EBaseServiceDescription,
		EXmlServiceDescription,
		EIdentityProvider,
		EServicePattern,
		EServiceSession,
		EWebServiceSession,
		EBasicWebServiceSession,
		EIdWSFServiceSession,
		EIdWsfServiceInstance,
		ECoreServiceConsumer,
		ESenInternalServiceConsumer,
		EIdWsfAuthenticationServiceClient, 
		EIdWsfDiscoveryServiceClient
		};

public:
	// The DescriptionClassType() method is used to resolve the real
	// derivant class type in the cases, where a derivant is seen
	// through some of its root interfaces.
	IMPORT_C virtual const TDescriptionClassType DescriptionClassType() = 0;


public:
	/**
	 * Matches()
	 * Return ETrue if this service description matches the given pattern.
	 * 
	 * The bits of information that are in the pattern are read and compared
	 * to corresponding fields in this service description. Note that a pattern
	 * may have far fewer fields and that only the non-null and non-zero-length 
	 * fields are compared.
	 *
	 * For example, assume that a pattern with only a contract was defined; with 
	 * the contract set to "urn:example.com:service". Each service description with
	 * the same contract will match the pattern, even if such a service description 
	 * has non-null/non-zero-length fields for other aspects.
	 * 
	 * @param	aPattern is a Service Description, typically with partial information.
	 * @return TBool
	 */
	IMPORT_C virtual TBool Matches(MSenServiceDescription& aPattern) = 0;

	IMPORT_C virtual const TPtrC Contract() = 0;
	IMPORT_C virtual const TPtrC EndPoint() = 0;
	IMPORT_C virtual const TDesC& FrameworkId() = 0;
	IMPORT_C virtual HBufC* FrameworkVersionL() = 0;


	IMPORT_C virtual void SetContractL(TPtrC aContract) = 0;
	IMPORT_C virtual void SetEndPointL(TPtrC aEndPoint) = 0;

	IMPORT_C virtual TInt WriteAsXMLToL(HBufC*& aTo) = 0;
	IMPORT_C virtual TInt WriteAsXMLUtf8ToL(HBufC8*& aTo) = 0;
	};

#endif // M_SEN_SERVICE_DESCRIPTION_H

