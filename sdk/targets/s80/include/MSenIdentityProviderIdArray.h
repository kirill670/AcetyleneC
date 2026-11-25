/*
 * =========================================================================
 *  Name     : MSenIdentityProviderIdArray.h
 *  Part of  : SenServiceDescription
 *  Created  : 2004-08-04 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceDescription/inc/MSenIdentityProviderIdArray.h,v $
 *   $Date: 2004/09/29 08:15:37 $
 *   $Revision: 1.2 $
 *   $Author: jomlaak $
 *
 *  Description: An abstract class used to reference to some 
 *  CSenIdentityProviderIdArray owned elsewhere.
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * ======================================================================= =
 */

#ifndef M_SEN_IDENTITY_PROVIDER_ID_ARRAY_H
#define M_SEN_IDENTITY_PROVIDER_ID_ARRAY_H


#include <e32base.h>
#include <badesca.h>
#include <e32des8.h>


class MSenIdentityProviderIdArray
	{
	IMPORT_C virtual const TBool IsStrict() const = 0;
	IMPORT_C virtual void SetStrict(TBool aStrict)= 0;
	};

#endif // M_SEN_IDENTITY_PROVIDER_ID_ARRAY_H