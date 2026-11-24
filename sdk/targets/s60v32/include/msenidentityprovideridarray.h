/*
* ==============================================================================
*  Name        : MSenIdentityProviderIdArray.h
*  Part of     : Web Services Description
*  Interface   : Abstract interface for ProviderID array classes
*  Description : An abstract class used to reference to some
* 				 CSenIdentityProviderIdArray owned elsewhere.
*  Version     : 
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef M_SEN_IDENTITY_PROVIDER_ID_ARRAY_H
#define M_SEN_IDENTITY_PROVIDER_ID_ARRAY_H

//  INCLUDES
#include <e32base.h>
#include <badesca.h>
#include <e32des8.h>

// CLASS DECLARATION

/**
* Abstract interface for ProviderID array classes
* 
* 
*/
class MSenIdentityProviderIdArray
	{
    public: // New functions
		
		/**
		* Method to check if the array is defined as strict.
        * 
		* @return ETrue if array is strict, EFalse if not
		*/
		IMPORT_C virtual TBool IsStrict() const = 0;

		/**
		* Method for setting the strict flag.
        * 
		* @param aStrict the value the flag should be set.
		*/
		virtual void SetStrict(TBool aStrict) = 0; 
		};

// M_SEN_IDENTITY_PROVIDER_ID_ARRAY_H
#endif

// End of File


