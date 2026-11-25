/*
* ==============================================================================
*  Name        : ckndglib.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : CCknDlgLibrary class implements the class to manage the CCknDlgLLibrary
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


#ifndef CKNDGLIB_H
#define CKNDGLIB_H

// INCLUDES
#include <f32file.h>
#include <e32base.h>
#include <eiklibry.h>

// FORWARD DECLARATIONS
class MCknNoteContentsControl;


/**
*  The CCknDlgLibrary class implements the class to manage the CCknDlgLLibrary.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*  @internal
*/
class CCknDlgLibrary : public CBase
	{
	public:

		/**
		* Ckon Dlg Dll initialisation.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void					InitialiseL();
		/**
		* Loads the resource file.
		* @deprecated
		* <BR><B>Type of return value:</B> TFileName
		*/
		IMPORT_C static TFileName ResourceFileL();
		/**
		* Calls/returns CreateByTypeL(...) that creates controls (by type).
		* <BR><B>Type of return value:</B> TCreateByTypeFunction
		*/
		IMPORT_C static TCreateByTypeFunction	ControlFactory();
	public:
		static SEikControlInfo CreateByTypeL(TInt aControlId);
		/**
		* Creates info dialog.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void RequestInfoDialogL();
		/**
		* Creates confirmation/query dialog.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void RequestQueryDialogL();
		/**
		* Creates one CCknNoteContentsControl object.
		* @return Pointer to MCknNoteContentsControl (interface to note contents control).
		* <BR><B>Type of return value:</B> TAny*
		*/
		IMPORT_C static TAny* RequestNoteContentsControlL();
	private:
		CCknDlgLibrary();
	};


#endif	// CKNDGLIB_H

// End of File
