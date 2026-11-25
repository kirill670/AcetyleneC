/*
* ==============================================================================
*  Name        : cmdabsorber.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Command absorbing control
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


#ifndef CMDABSORBER_H
#define CMDABSORBER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CEikAppUi;

/**
*  A control which when created will absorb all events
*	
*  This command (event) absorbing control is to be used when you need 
*  to return to the active scheduler, but don't want any events to be 
*  passed through.
* 
*  This was used in messaging quite a lot when starting off operations 
*  (such as launching editors). The absorber is then deleted when it is 
*  no longer needed and following events are passed to the controls as normal.
*
*  @lib uiutil.lib
*  @since ?Series90_version
*/
class CCommandAbsorbingControl : public CCoeControl
	{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CCommandAbsorbingControl* NewLC();

		/**
		* Destructor.
		*/
		virtual ~CCommandAbsorbingControl();

	private:
		virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		CCommandAbsorbingControl();
		void ConstructL();

	private:
		CEikAppUi*	iAppUi;
	};


#endif	// CMDABSORBER_H

// End of File
