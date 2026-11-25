/*
* ==============================================================================
*  Name        : eiklibry.h
*  Part of     : UIKON
*  Interface   : Library API
*  Description : Base class for a library interface.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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

#ifndef EIKLIBRY_H
#define EIKLIBRY_H

// INCLUDES
#include <f32file.h>
#include <e32base.h>
#include <eikfctry.h>

// FUNCTION PROTOTYPES

/**
@publishedPartner
@released
*/typedef SEikControlInfo (*TCreateByTypeFunction)(TInt);

/**
*  Abstract base class specifying the interface for a dynamically-loaded DLL
*  which goes on to configure other Uikon statically-loaded DLLs.
*
*  @lib eikcore.lib
*  @since Series90 1.0
*/
class CEikLibrary : public CBase
/**
Abstract base class specifying the interface for a dynamically-loaded DLL
which goes on to configure other Uikon statically-loaded DLLs.

@publishedPartner
@released 
*/
	{
	public:
		/**
		* When EikEnv dynamically loads a DLL, it calls its InitializeL function
		* which will set up any variables which EikEnv requires. 
		* <BR><B>Type of return value:</B> void
		*/
		virtual void InitializeL() = 0;

		/**
		* Gives the EikEnv access to the library's resources.
		* @return Array of a library resource files.
		* <BR><B>Type of return value:</B> CArrayFix<TFileName>*
		*/
		virtual CArrayFix<TFileName>*				ResourceFileArrayL() const = 0;

		/**
		* Gives the EikEnv access to the library's control factories.
		* @return Array of control factories.
		* <BR><B>Type of return value:</B> CArrayFix<TCreateByTypeFunction>*
		*/
		virtual CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const = 0;

		/**
		* When EikEnv dynamically loads a DLL, it calls its PostAppUiInitializeL function
		* after loading the application UI.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void PostAppUiInitializeL();
	};


#endif	// EIKLIBRY_H

// End of File
