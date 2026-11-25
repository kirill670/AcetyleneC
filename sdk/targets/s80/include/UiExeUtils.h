/*
* ==============================================================================
*  Name        : uiexeutils.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : EXE utilities
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


#ifndef UIEXEUTILS_H
#define UIEXEUTILS_H

// INCLUDES
#include <e32std.h>
#include <eikappui.h>

// FORWARD DECLARATIONS
class CEikonEnv;

/**
*  A static class for creating and destroying an EikonEnv. This class should NOT be run from applications,
*  it should only be used in dlls which do not have an EikonEnv.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class CExeEikonEnvUtils
	{
	public:

		/**
		* Create Eikon environment
		* @since ?Series90_version
		* @return Pointer to the new Eikon Environment
		* <BR><B>Type of return value:</B> CEikonEnv*
		*/
		IMPORT_C static CEikonEnv* CreateEikonEnv();

		/**
		* Leaving version of creating Eikon Environment
		* @since ?Series90_version
		* @return Pointer to the new Eikon environment
		* <BR><B>Type of return value:</B> CEikonEnv*
		*/
		IMPORT_C static CEikonEnv* CreateEikonEnvL();

		/**
		* Destroys the Eikon environment
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void DestroyEikonEnv();
	};


#endif	// UIEXEUTILS_H

// End of File
