// EIKFSO.H
/*
* ============================================================================
*  Name     : MEikFileSelectionObserver
*  Part of  : CKON
*  Description:
*     Interface for file selector
* ============================================================================
*/

//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef EIKFSO_H
#define EIKFSO_H


// INCLUDES


// DATA TYPES


// FORWARD DECLARATIONS


// CLASS DECLARATIONS

/**
*  Interface for file selector.
*
*/
class MEikFileSelectionObserver
    {
	public:  // Declarations
	enum TUpdateEvent
		{
		EPathChanged,
		EFullNameChanged,
		};



	public:
	// Constructors and destructor




	// New methods
        
		/**
		* The framework calls this function on the specified file selection observer, which implements the MEikFileSelectionObserverinterface, when a file name changes.
		* In this case the observer is this class.
		* @param aFullName The name of the file which changed
		* @param aUpdateEvent The type of event to handle.
		*/
		virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged) = 0;



    };


#endif      // EIKFSO_H   
            
// End of File
