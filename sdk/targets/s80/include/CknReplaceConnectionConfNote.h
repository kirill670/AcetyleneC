/*
* ==============================================================================
*  Name        : cknreplaceconnectionconfnote.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : Class for displaying a confirmation note to replace a connection.
*  Version     : 1.0
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

#ifndef __CKNREPLACECONNECTIONCONFNOTE_H__
#define __CKNREPLACECONNECTIONCONFNOTE_H__

// INCLUDES
#include <eikdialg.h>

// FORWARD DECLARATIONS
class CGulIcon;
class CCknReplaceConnectionConfNoteExt;

/**
*  Class for displaying a confirmation note to replace a connection.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CCknReplaceConnectionConfNote : public CEikDialog
	{
public:
	/**
	* Runs the dialog with an array of current connection names.
	* @param aCurrentConnections - The names of current connections to display in the choice list.
	*		Must contain at least 1 item.
	* @param aReplaceConnection - The index of the chosen connection 
	*		If the user pressed 'drop' this holds the index value of the item within aCurrentConnections
	*		that should be dropped. If the user pressed 'cancel' this contains  KNoSelectedConnection (-1)
	* @return ETrue if the user presses Drop, EFalse if the user presses Cancel
	* <BR><B>Name of return value:</B> (Write name here)
	* <BR><B>Type of return value:</B> TBool
	*/
	IMPORT_C static TBool RunDlgLD(CDesCArray* aCurrentConnections, TInt& aReplaceConnection);	 
private:
	CCknReplaceConnectionConfNote(CDesCArray* aCurrentConnections, TInt& aReplaceConnection);
	~CCknReplaceConnectionConfNote();
	TBool OkToExitL(TInt aButtonId);
	void PreLayoutDynInitL();
private:
	CDesCArray* iCurrentConnections;
	TInt& iConnection;
	CCknReplaceConnectionConfNoteExt* iExt;
	};

#endif  //CKNREPLACECONNECTIONCONFNOTE_H

// End of File