/*
* ==============================================================================
*  Name        : wngpanic.h
*  Part of     : Word engine
*  Interface   : 
*  Description : Word engine Panic number and function
*  Version     : 
*
*  Copyright (c) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#if !defined(__WNGPANIC_H__)
#define __WNGPANIC_H__

//  INCLUDES
#include <e32std.h>

// CONSTANTS
// MACROS

// DATA TYPES
enum TWpengPanic
	{
	EStyleIntegrityError
	};

// FUNCTION PROTOTYPES
GLREF_C void Panic(TWpengPanic aPanic);

// FORWARD DECLARATIONS
// CLASS DECLARATION



#endif      // __WNGPANIC_H__
            
// End of File
