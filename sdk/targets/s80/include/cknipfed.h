/*
* ============================================================================
*  Name     : CCknIpFieldEditor from %name%
*  Part of  : CKON
* ============================================================================
*/

#ifndef CKNIPFED_H
#define CKNIPFED_H


// INCLUDES
#include <eikmfne.h>


// FORWARD DECLARATIONS
class TInetAddr;


// CLASS DECLARATIONS

/**
*  The CCknIpFieldEditor class implements an edior for an IP address.
*  
*
*  Link against cknctl.lib
*/
class CCknIpFieldEditor : public CEikMfne
    {
	public:
	// Constructors

		/**
		* Static constructor.
		*/
		IMPORT_C static CCknIpFieldEditor* NewL(TInetAddr& aMinimumAddress,
                                            TInetAddr& aMaximumAddress,
                                            TInetAddr& aInitialAddress);

		IMPORT_C static CCknIpFieldEditor* NewL();



	// New methods
        
		/**
		* Method for setting the editor fields dynamically.
		* @param aAddress Reference to a TInetAddr struct including the new address.
		*/
		IMPORT_C void SetAddress(const TInetAddr& aAddress);

		/**
		* Method for reading the editor value.
		* @return The current editor value.
		* <BR><B>Type of return value:</B> TInetAddr
		* <BR><B>Range of return value:</B> (Strings)
		*/
		IMPORT_C TInetAddr Address() const;

		/**
		* Sets the range of permissible addresses. Only values inside the initial minimum and maximum may be entered by the user.
		* @param const TInetAddr& aMinimumAddress The lowest permissible address.
		* @param const TInetAddr& aMaximumAddress The highest permissible address.
		*/
		IMPORT_C virtual void SetMinimumAndMaximum(const TInetAddr& aMinimumAddress,
                                               const TInetAddr& aMaximumAddress); // only values inside the initial minimum and maximum are permitted
		
		/**
		* Get the range of permissible addresses. These are the maximum and minimum values that the user is able to enter into the editor.
		* @param const TInetAddr& aMinimumAddress The lowest permissible address.
		* @param const TInetAddr& aMaximumAddress The highest permissible address.
		*/		
		IMPORT_C virtual void GetMinimumAndMaximum(TInetAddr& aMinimumAddress,
                                               TInetAddr& aMaximumAddress) const;

		/**
		* Method for reading an IP address from resources.
		* @param aResourceReader Reference to a resource reader associated to the IP address resource.
		* @return The address
		* <BR><B>Type of return value:</B> TInetAddr
		* <BR><B>Range of return value:</B> (Strings)
		*/
		IMPORT_C TInetAddr ReadIPAddress(TResourceReader& aResourceReader);

		/**
		* Method for constructing the control from resources.
		* @param aResourceReader Reference to a resource reader associated to a IP Field Editor control resource.
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);

	// Methods from base classes

		/**
		* Method for handling key events.
		* @param aKeyEvent The key event.
		* @param aType The type of key event (i.e. EEventKey, EEventKeyUp or EEventKeyDown).
		* @return Indicates whether or not the key event was used by this control.
		* <BR><B>Type of return value:</B> TKeyResponse
		* <BR><B>Contents of return value:</B> (EKeyWasConsumed when the key event was handled, otherwise EKeyWasNotConsumed.)
		*/
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    private: //Methods

		/**
		* destructor
		*/
		CCknIpFieldEditor();
		void ConstructL(TInetAddr& aMinimumAddress,
						TInetAddr& aMaximumAddress,
						TInetAddr& aInitialAddress,
						const TInt aFlags=0);
		void SplitAddressIntoFields(
									const TInetAddr& aAddress,
									TUint8 &aFieldA,
									TUint8 &aFieldB,
									TUint8 &aFieldC,
									TUint8 &aFieldD) const;

	private:     // Data
		const CFont* iFont;

    };


#endif      // CKNIPFED_H   
            
// End of File
