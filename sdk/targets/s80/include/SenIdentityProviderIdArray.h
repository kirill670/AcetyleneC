/*
* =========================================================================
*  Name     : SenIdentityProviderIdArray.h
*  Part of  : SenServiceDescription
*  Created  : 2004-08-04 by Nokia
*  Descr.   :
*
*  Version :
*   $Source: /projects/serene/sen/ServiceDescription/inc/SenIdentityProviderIdArray.h,v $
*   $Date: 2004/10/26 07:41:24 $
*   $Revision: 1.2 $
*   $Author: matmatt $
*
*  Copyright (c) 2004 Nokia Corporation. All rights reserved.
* =========================================================================
*/


#ifndef SEN_IDENTITY_PROVIDER_ID_ARRAY_H
#define SEN_IDENTITY_PROVIDER_ID_ARRAY_H


#include <e32base.h>
#include <badesca.h>
#include <e32std.h>	

#include <MSenIdentityProviderIdArray.h>


class CSenIdentityProviderIdArray : public CDesC16ArraySeg, public MSenIdentityProviderIdArray
{
public:
	// argument-less constructors create non-strict arrays.. (iStrict = EFalse)
	IMPORT_C static CSenIdentityProviderIdArray* NewL();
	// argument-less constructors create non-strict arrays.. (iStrict = EFalse)
	IMPORT_C static CSenIdentityProviderIdArray* NewLC();


	IMPORT_C static CSenIdentityProviderIdArray* NewL(const TBool aStrict);
	IMPORT_C static CSenIdentityProviderIdArray* NewLC(const TBool aStrict);

	IMPORT_C virtual ~CSenIdentityProviderIdArray();

	IMPORT_C virtual const TBool IsStrict() const;
	IMPORT_C void SetStrict(TBool aStrict);


protected:
	void ConstructL();
	CSenIdentityProviderIdArray(const TBool aStrict);

private: // date
	TBool iStrict;
};
#endif // SEN_IDENTITY_PROVIDER_ID_ARRAY_H