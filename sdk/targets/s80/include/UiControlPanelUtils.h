/*
* ==============================================================================
*  Name        : uicontrolpanelutils.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Control Panel utilities
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


#ifndef UICONTROLPANELUTILS_H
#define UICONTROLPANELUTILS_H

// INCLUDES
#include <E32STD.H>

// FORWARD DECLARATIONS
class RFs;


/**
*  A static class to allow simple actions with control panel items
*
*  @lib ututils.lib
*  @since ?Series90_version
*/
class ControlPanelUtils
	{
	public:

		/**
		* Launch the control panel
		* @since ?Series90_version
		* @param aControlPanelType The type of control panel
		* @param aFs The file system used
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void LaunchPanelL(TUid aControlPanelType, RFs& aFs);
	};


#endif	// UICONTROLPANELUTILS_H

// End of File
