/*
* ==============================================================================
*  Name        : eikchmap.h
*  Part of     : CKON
*  Interface   : Character Map Dialog API
*  Description : Character map control.
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


#ifndef EIKCHMAP_H
#define EIKCHMAP_H


// INCLUDES
#include <coecntrl.h>
#include <eikscrlb.h>

// CLASS DECLARATIONS

/**
*  A character map control which provides special characters and symbols.
*
*  Link against EIKCDLG.LIB
*  @since Series90 1.0
*/
class CEikCharMap : public CCoeControl, public MEikScrollBarObserver
	{
	private:  // Declarations

	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		CEikCharMap();


		/**
		* Destructor.
		*/
		~CEikCharMap();


	// New methods
        
		/**
		* Second phase construction
		*/
		void ConstructL();

		/**
		* Changes the currently chosen character in the char map.
		* @param aChar The unicode character code of the character to select
		*/
		IMPORT_C void SetChar(TInt aChar);

		/**
		* Gets the unicode value of the character selected
		* @return The character selected
		*/
		IMPORT_C TInt GetChar() const;
public: // from CCoeContrl

		// Methods from base classes

		/**
		* From CCoeControl Returns the minimum size required by the control, overriding CCoeControl
		* @return the minimum size required
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TSize
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		TSize MinimumSize();

		/**
		* From CCoeControl Handles key events, overriding CCoeControl
		* @param aKeyEvent The key event
		* @return A TKeyResponce, whether the key was coonsumed or not
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TKeyResponse
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);

		/**
		* From CCoeControl Overriddes CCoeControl GetColorUseListL with an empty function
		* @param aColorUseList Not used
		*/
		void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* From CCoeControl Handles a change to the control's resources of type aType which are shared across the environment, e.g. colors or fonts, Currently calls CCoeControl
		* @param aType UID indicating the type of change
		*/
		void HandleResourceChange(TInt aType);			// not available before Release 005u

		/**
		* From CCoeControl the supported input capabilities of the control 
		* @return The input that can be consumed by the control.
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TCoeInputCapabilities
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		TCoeInputCapabilities InputCapabilities() const;


    protected:  // Methods
        

		// Methods from base classes
        
		/**
		* From CCoeControl initialise the character map.
		* @param aReader The resource reader
		*/
		void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* From CCoeControl Handles TPointerEvent::EButton1Down.
		* @param aPointerEvent The pointer event type to handle
		*/
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		/**
		* From CCoeControl Draw the control.
		* @param aRect Not used currently 
		*/
		void Draw(const TRect& aRect) const;

		/**
		* From CCoeControl Called whenever focus is changed
		* @param aDrawNow If ETrue, draw or hide cursor depending on whether control has focus
		*/
		void FocusChanged(TDrawNow aDrawNow);

		/**
		* From CCoeControl Sets the size and position of contents of control after a resize
		*/
		void SizeChanged();

		/**
		* From CCoeControl Returns the amount of controls in a compound control.
		* @return If there is a scrollbar return 1 otherwise 0
		*/
		TInt CountComponentControls() const;

		/**
		* From CCoeControl Gets a specified component
		* @param aIndex Not used. A scrollbar is returned.
		*/
		CCoeControl* ComponentControl(TInt aIndex) const;

	protected:	// from MEikScrollBarObserver
		/**
		* From MEikScrollBarObserver Handle scrollbar events
		* @param aScrollBar Not used currently
		* @param aEventType The scroll event
		*/
		virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);


    private: //Methods

private: //from CCoeContrl

		void Reserved_1();
		void Reserved_2();	
private:
		void CommonConstructL();
private:
		void GetRowColFromPointerPos(const TPoint& aPosition);
		TPoint GetCursorPosFromRowCol() const;
		void DrawCursor();
		void ClearCursor();
		void DoDrawCursor(CWindowGc& aGc, TBool aCursorActive) const;
		void MoveCursor(TInt aX, TInt aY);
		void CheckStateChangedL(TInt aOldPos);
		TInt DisplayCharacter(TInt aRet) const;
		void SetMapPos(TInt aChar);
		void UpdateScrollPosition();

	private:     // Data
		const CFont* iFont;
		TInt iCharWidth;
		TInt iCharHeight;
		TInt iRows;
		TPoint iOffset;
		TPoint iCursorRowCol;
		CEikScrollBar* iScrollBar;
		TEikScrollBarModel iScrollBarModel;
		TInt iVerticalScrollPos;
		HBufC* iCharacters;
		TInt iColumns;
		TInt iVisibleRows;

    };


#endif      // EIKCHMAP_H   
            
// End of File
