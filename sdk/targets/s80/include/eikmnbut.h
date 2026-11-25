/*
* ==============================================================================
*  Name        : eikmnbut.h
*  Part of     : CKON
*  Interface   : Menubar API
*  Description : Menu button.
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


#ifndef EIKMNBUT_H
#define EIKMNBUT_H

// INCLUDES
#include <eikmobs.h>
#include <eikcmbut.h>

// FORWARD DECLARATIONS
class CEikMenuPane;

/**
* A menu button enables a user to initiate display of a menu.
*
* @since 6.0
* @lib eikcoctl.lib
*/
class CEikMenuButton : public CEikCommandButton, private MEikMenuObserver
	{
	public:

		/**
		* C++ default constructor.
		* See also <code>ConstructFromResourceL()</code>.
		*/
		IMPORT_C CEikMenuButton();

		/**
		* Destructor. Deletes any popup and removes it from the stack
		*/
		IMPORT_C ~CEikMenuButton();

		/**
		* Completes construction of a menu button from resource.
		*
		* @param aReader The resource reader to use.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Requests the launch of a popup using the specified observer.
		*
		* @param aObserver The observer to use to request launch of the popup.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void LaunchPopupMenuL(MEikMenuObserver* aObserver);

		/**
		* Sets the menu pane id.
		* @param aMenuPaneId The menu pane id
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMenuPaneId(TInt aMenuPaneId);

	protected: //from CCoeControl

		/**
		* Writes the internal state of the control and its components to aStream.
		* Does nothing in release mode.
		* Designed to be overidden and base called by subclasses.
		*
		* @internal
		* @param aWriteStream the stream to use
		*/
		IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

	public: // from CEikButtonBase

		/**
		* Animates a button; showing the control as momentarily depressed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void Animate();
		
	private: // from MEikCommandObserver

		IMPORT_C void ProcessCommandL(TInt aCommandId);
		IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);

	private:
	
		void ClosePopupMenu();
		void DoLaunchPopupMenuL();

	private:
		MEikMenuObserver* iMenuObserver;
		CEikMenuPane* iMenuPopup;
		TInt iMenuPaneId;
	};



#endif	// EIKMNBUT_H

// End of File
