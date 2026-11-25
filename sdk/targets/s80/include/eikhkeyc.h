/*
* ==============================================================================
*  Name        : eikhkeyc.h
*  Part of     : ckon
*  Interface   : Hotkey API
*  Description : Hotkeys
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


#ifndef EIKHKEYC_H
#define EIKHKEYC_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CEikHotKeyTable;
class MEikCommandObserver;


/**
*  Hotkey event processing
*
*  @lib EIKCOCTL.LIB
*  @since 6.0
*/
class CEikHotKeyControl : public CCoeControl
	{
	public:

		/**
		* C++ default constructor.
		* @param aTable An array for hotkey commands and their associated key codes and modifiers.
		* @param aObserver The observer to pass the hotkey commands on to.
		*/
		CEikHotKeyControl(CEikHotKeyTable* aTable,MEikCommandObserver* aObserver);

		/**
		* Destructor.
		*/
		~CEikHotKeyControl();
	protected: //from CCoeControl
	
		/**
		* Writes the internal state of the control and its components to aStream.
		* Does nothing in release mode.
		* Designed to be overidden and base called by subclasses.
		* @param aWriteStream stream to write to
		* @return
		*/
		IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	private: // framework
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	private:
		CEikHotKeyTable* iTable;
		MEikCommandObserver* iObserver;
	};


#endif	// EIKHKEYC_H

// End of File
