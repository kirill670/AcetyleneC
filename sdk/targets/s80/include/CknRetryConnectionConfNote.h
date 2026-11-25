/*
* ==============================================================================
*  Name        : cknretryconnectionconfnote.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : Class for displaying a confirmation note to retry a connection.
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

#ifndef __CKNRETRYCONNECTIONCONFNOTE_H__
#define __CKNRETRYCONNECTIONCONFNOTE_H__

// INCLUDES
#include <eikdialg.h>

// FORWARD DECLARATIONS
class CGulIcon;
class CCknRetryConnectionConfNoteExt;

/**
*  Class for displaying a confirmation note to retry a connection.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CCknRetryConnectionConfNote : public CEikDialog
	{
public:
	/**
	* Runs the dialog with an array of available connection names.
	* @param aConnections - The names of available connections to display in the choice list.
	*		Must contain at least 1 item.
	* @param aRetryConnection - The index of the chosen connection 
	*		The value passed in with this argument is used to set the current connection in the choicelist when
	*		the dialog opens. The value passed in should be between 0 and the highest index of the items in 
	*		aConnections (inclusive).
	*		If the user pressed 'Retry' this argument passes back the index value of the item within aConnections
	*		that should be retried. If the user pressed 'Cancel' this passes back KNoSelectedConnection (-1)
	* @return ETrue if the user presses 'Retry', EFalse if the user presses 'Cancel'
	* <BR><B>Name of return value:</B> (Write name here)
	* <BR><B>Type of return value:</B> TBool
	*/
	IMPORT_C static TBool RunDlgLD(CDesCArray* aConnections, TInt& aRetryConnection);	 
private:
	CCknRetryConnectionConfNote(CDesCArray* aConnections, TInt& aRetryConnection);
	~CCknRetryConnectionConfNote();
	TBool OkToExitL(TInt aButtonId);
	void PreLayoutDynInitL();
private:
	CDesCArray* iConnections;
	TInt& iCurrentConnection;
	CCknRetryConnectionConfNoteExt* iExt;
	};

#endif  //CKNRETRYCONNECTIONCONFNOTE_H

// End of File