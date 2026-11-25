/*
 * =========================================================================
 *  Name     : SenBaseServiceDescription.h
 *  Part of  : SenServiceDescription
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/SenBaseServiceDescription.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.6 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */


#ifndef BASE_SERVICE_DESCRIPTION_H
#define BASE_SERVICE_DESCRIPTION_H

#include <MSenServiceDescription.h>

#include <e32base.h>
#include <e32des8.h>	// HBufC8
#include <e32std.h>		// RPointerArray

class CBaseServiceDescription : public MSenServiceDescription
    {
public:

IMPORT_C static CBaseServiceDescription* NewL(TDesC* aContract, 
										 TDesC* aEndPoint,
										 TDesC* aFrameworkId);

IMPORT_C static CBaseServiceDescription* NewLC(TDesC* aContract, 
										 TDesC* aEndPoint,
										 TDesC* aFrameworkId);


IMPORT_C TBool Matches(MSenServiceDescription& aPattern);


IMPORT_C const TPtrC Contract();
IMPORT_C const TPtrC EndPoint();
IMPORT_C const TDesC& FrameworkId();
IMPORT_C HBufC* FrameworkVersionL();

IMPORT_C void SetContractL(TPtrC aContract);
IMPORT_C void SetEndPointL(TPtrC aEndPoint);

	// The developer may use this to search for a session of 
	// (i.e. connection to) a certain service invokation framework.
	// If set to NULL, then any matching framework is used.
	// Vanilla web services have NULL framework id.
IMPORT_C void SetFrameworkIdL(TDesC* aFrameworkId);

	// the serverside implementations like ServiceSession 
	// could have use for this:
	//void SetFrameworkVersionL(TVersion& aVersion);

IMPORT_C TInt WriteAsXMLToL(HBufC*& aTo);
IMPORT_C TInt WriteAsXMLUtf8ToL(HBufC8*& aTo);

IMPORT_C virtual ~CBaseServiceDescription();

public: // class type getter
IMPORT_C const TDescriptionClassType DescriptionClassType();

private: // Data

	void ConstructL(TDesC* aContract, 
					TDesC* aEndPoint,
					TDesC* aFrameworkId
					//,TDesC8* aFrameworkVersion
					);

	CBaseServiceDescription();

	HBufC*	iContract;
	HBufC*	iEndPoint;
	HBufC*	iFrameworkId;

	
	// A SenServiceSession could have use for this:
	HBufC*	iFrameworkVersion;


	const TDescriptionClassType iType;

    };


#endif // BASE_SERVICE_DESCRIPTION_H

