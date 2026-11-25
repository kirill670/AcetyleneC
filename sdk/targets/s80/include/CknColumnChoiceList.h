/*
* ==============================================================================
*  Name        : CknColumnChoiceList.h
*  Part of     : CKON / CKNCTL
*  Interface   : CknColumnChoiceList API
*  Description : Choice list with icon capability
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

#ifndef CKNCOLUMNCHOICELIST_H
#define CKNCOLUMNCHOICELIST_H

// INCLUDES
#include <eikchlst.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  Choice list with icon capability
*  A choice list for icons only or icons with text.
*
*  @lib CKNCTL
*  @since Series90 1.1
*/
class CCknColumnChoiceList : public CEikChoiceList
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        * @since Series90 1.1
        *
        * @param aParent This choice list's parent control.
        * @param aFlags Flags from CEikChoiceListBase.
        * @param aMaxDisplayChar The maximum number of characters to display in the text column of the choice list.
        *
        * @return Pointer to 2 phase constructed CCknColumnChoiceList.
        */
        IMPORT_C static CCknColumnChoiceList* NewL(CCoeControl* aParent, TInt aFlags = 0, TInt aMaxDisplayChar = 0);
        
        /**
        * C++ default constructor.
        * @since Series90 1.1
        */
        IMPORT_C CCknColumnChoiceList();

        /**
        * Destructor.
        * @since Series90 1.1
        */
        IMPORT_C ~CCknColumnChoiceList();

    public: // New functions
        
        /**
        * 2nd phase constructor
        * @since Series90 1.1
        *
        * @param aParent This choice list's parent control.
        * @param aFlags Flags from CEikChoiceListBase.
        * @param aMaxDisplayChar The maximum number of characters to display in the text column of the choice list.
        */
        IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags = 0, TInt aMaxDisplayChar = 0);

        /**
        * 2nd phase constructor from resource
        * @since Series90 1.1
        *
        * @param aReader A resource reader to read the ICONCHOICELIST resource data.
        */
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Sets the array of icons used in the choice list.
        * @since Series90 1.1
        *
        * @param aResourceId The resource ID of the icon array to be constructed.
        */
		IMPORT_C void SetIconArrayL(TInt aResourceId);

        /**
        * Sets the array of icons used in the choice list.
        * @since Series90 1.1
        *
        * @param aIconArray The new bitmap array. Passes ownership.
        */
		IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aIconArray);

        /**
        * Sets the array of items based on the icons and text required in the choice list.
        * @since Series90 1.1
        *
        * @param aResourceId The resource ID of the item array to be constructed.
        */
		IMPORT_C void SetItemIconAndTextArrayL(TInt aResourceId);

        /**
        * Sets the array of items based on the icons and text required in the choice list.
        * @since Series90 1.1
        *
        * @param aItemIconArray The new array of icon items. Passes ownership.
        * @param aItemTextArray The new array of text items. Passes ownership. If NULL then only icon items are used in the choice list
        */
		IMPORT_C void SetItemIconAndTextArrayL(CArrayFix<TInt>* aItemIconArray, MDesCArray* aItemTextArray = NULL);

    public: // Functions from base classes

        /**
        * From CCoeControl. Activates the choice list control.
        * @since Series90 1.1
        */
		IMPORT_C void ActivateL();        

        /**
        * From CCoeControl. Offers a key event to the choice list control.
        * @since Series90 1.1
        *
        * @param aKeyEvent The key event
        * @param aEventCode The event code
        *
        * @return A response.
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aEventCode);

        /**
        * From CCoeControl. Gets the minimum size of the choice list control.
        * @since Series90 1.1
        * 
        * @return The minimum size of the control.
        */
        IMPORT_C TSize MinimumSize();

        /**
        * From CEikChoiceListBase. Returns the width of the maximum list item.
        * @since Series90 1.1
        *
        * @return The width of the maximum list item.
        */
        IMPORT_C TInt CalculateTextWidth() const;

        /**
        * From CEikChoiceListBase. Destroys the choicelist popout.
        * @since Series90 1.1
        */
        IMPORT_C void DestroyPopout();

		/**
        * From CEikChoiceListBase. This function should draw the content of the choicelist.
        * @since Series90 1.1
        */
        IMPORT_C void DrawContent() const;

        /**
        * From CEikChoiceList. Creates the list box popout.
        * @since Series90 1.1
        */
        IMPORT_C void CreateListBoxL();

        /**
        * From CEikChoiceList. Initialises the list box popout.
        * @since Series90 1.1
        */
        IMPORT_C void InitializeListBoxL();

        /**
        * From CEikChoiceList. Sets the extent of the list box.
        * @since Series90 1.1
        */
        IMPORT_C void SetListBoxExtentL();

    protected:  // New functions
        
    protected:  // Functions from base classes
        
    private:
		void CreateIconArrayFromResourceL(TInt aResourceId);
		void CreateItemArrayFromResourceL(TInt aResourceId);

		void DestroyIconArray();
		void DestroyItemIconArray();
		void DestroyItemArray();

		void ValidateIconIndex(TInt& aIconIndex);

		void DoDrawContent(const TDesC& aDes) const;

    public:     // Data
    
    protected:  // Data

    private:    // Data
        // Widths of the icons and/or text columns in the choice list
		TInt iIconColumnWidth;
		TInt iTextColumnWidth;

		// Icons used in the choice list
		CArrayPtr<CGulIcon>* iIconArray;

		// Icons to be shown as items in the choice list
		CArrayFix<TInt>* iItemIconArray;

		// Items in the choice list
		MDesCArray* iItemArray;

        // Reserved pointer for future extension
        TAny* iReserved;

    public:     // Friend classes

    protected:  // Friend classes

    private:    // Friend classes

    };

#endif      // CKNCOLUMNCHOICELIST_H
            
// End of File
