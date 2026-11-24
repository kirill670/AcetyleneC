/*
* ============================================================================
*  Name         : CFindItemEngine from FindItemEngine.h
*  Part of      : CommonEngine
*
*  Description  : Find Item Engine parses the given text for the following:
*                     Phone numbers
*                     E-mail addresses
*                     URI addresses 
*  Version      : %version:ou1cfspd#8 %"
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef FINDITEMENGINE_H
#define FINDITEMENGINE_H

//  INCLUDES
#include <e32base.h>

// CLASS DECLARATION

/**
* Find Item API.
*
* Find Item API offers methods for parsing phone numbers, 
* e-mail addresses or URI addresses from the given text.
*
*  Usage:
*
*  #include <finditemengine.h>
*
*  // SFoundItem instance
*  CFindItemEngine::SFoundItem item;
*
*  // Some text
*  TBufC<256> strSomeText(_L("Mail to me@someplace.com or call 040 1234567. 
*  You can also tune in to audio feed at rtsp://someplace.com/somefeed.ra."));
*	
*  // Create an instance of FindItemEngine and search for selected items.
*  // strSometext is a text that will be parsed as a descriptor and 
*  // second parameter defines what we are looking for.
*  CFindItemEngine* singleSearch = CFindItemEngine::NewL(strSomeText, 
*                   CFindItemEngine::EFindItemSearchMailAddressBin);
*
*  // Get count of found items.
*  TInt count(singleSearch->ItemCount());
*
*  // Get currently selected item (me@someplace.com) to the result1 variable.
*  singleSearch->Item(item);
*  TPtrC16 result1(strSomeText.Mid(item.iStartPos, item.iLength));
*
*  // Deallocate memory
*  delete singleSearch;
*
*  // Create an instance of FindItemEngine and look for all possible 
*  // things (cases work as binary mask).
*  CFindItemEngine* multiSearch = CFindItemEngine::NewL(strSomeText,
*                   (CFindItemEngine::TFindItemSearchCase)
*                   (CFindItemEngine::EFindItemSearchPhoneNumberBin |           
*                   CFindItemEngine::EFindItemSearchURLBin | 
*                   CFindItemEngine::EFindItemSearchMailAddressBin | 
*                   CFindItemEngine::EFindItemSearchScheme));
*
*  // Get count of found items.
*  TInt count2(multiSearch->ItemCount());
*
*  // Get currently selected item to the result2 variable.
*  multiSearch->Item(item);
*
*  // Debug print all items and their type.
*  for( TInt i=0; i<count2; i++)
*      {
*      TPtrC16 result2(strSomeText.Mid(item.iStartPos, item.iLength));
*      RDebug::Print(_L("Found type %d item:"), item.iItemType);
*      RDebug::Print(_L("%S"), &result2);
*      multiSearch->NextItem(item);
*      }
*
*  // Deallocate memory
*  delete multiSearch;
*/

class CFindItemEngine :public CBase
    {
    public:

        /**
        * Enumeration to define the search case. 
        * Multiple non-deprecated enumerations can be used as binary mask.
        * 
        * Deprecated items kept for B/SC compatibility
        */
        enum TFindItemSearchCase
            {
			EFindItemSearchPhoneNumberBin = 4,  // Searches phone numbers.
            EFindItemSearchMailAddressBin = 8,  // Searches mail addresses.
            EFindItemSearchURLBin  = 16,        // Searches fixed start URLs ("http://", "https://", "rtsp://"), "www.", "wap." and plain IP.
            EFindItemSearchScheme  = 32         // Searches for all URIs containing a scheme.
            };

        /**
        * Struct to contain an item.
        */
        struct SFoundItem
            {
            // Start position of the found item
            TInt iStartPos;
            // Length of the found item (characters)
            TInt iLength;
			// Search case of the found item
			TFindItemSearchCase iItemType;
			};

    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        *
        * @param aText          Text that will be parsed
        * @param aSearchCase    Identifies what items are we looking for:
        *                           EFindItemSearchPhoneNumberBin
        *                           EFindItemSearchMailAddressBin
        *                           EFindItemSearchURLBin
        *                           EFindItemSearchScheme
        *                       Any combination of these flags can be given
        *                       as a bit mask.
        *
        * @return Pointer to created CFindItemEngine
        */
        IMPORT_C static CFindItemEngine* NewL( const TDesC& aText, 
                                        const TFindItemSearchCase aSearchCase);
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CFindItemEngine();

    public:
        /**
        * Gets the currently 'selected' item
        *
        * @param aItem Returns currently selected item
        *
        * @return EFalse if no items were found
        */
        IMPORT_C TBool Item( SFoundItem& aItem );

        /**
        * Moves the selection to next item and gets it
        *
        * @param aItem Returns the next item
        *
        * @return EFalse if there's no next item.
        */
        IMPORT_C TBool NextItem( SFoundItem& aItem );

        /**
        * Moves the selections to previous item and gets it
        *
        * @param aItem Returns the previous item
        *
        * @return EFalse if there's no previous item.
        */
        IMPORT_C TBool PrevItem( SFoundItem& aItem );
		
        /**
        * Gets the array of found items
        *
        * @return Constant array of found items. Ownership stays with
        *   CFindItemEngine.
        */
        IMPORT_C const CArrayFixFlat<SFoundItem>* ItemArray() const;

        /**
        * Gets the current position in item array
        *
        * @return Current position.
        */
		IMPORT_C TInt Position() const;		
        /**
        * Resets the position in item array to zero (beginning of the array)
        */
        IMPORT_C void ResetPosition();

        /**
        * Gets the number of found items
        *
        * @return The number of found items
        */
		IMPORT_C TInt ItemCount() const;
		
        /**
        * Makes a new search and resets the engine
        *
        * @param aText          Text that will be parsed
        * @param aSearchCase    Identifies what items are we looking for:
        *                           EFindItemSearchPhoneNumberBin
        *                           EFindItemSearchMailAddressBin
        *                           EFindItemSearchURLBin
        *                           EFindItemSearchScheme
        *                       Any combination of these flags can be given
        *                       as a bit mask.
        *
        * @return Number of found items
        */
        IMPORT_C TInt DoNewSearchL( const TDesC& aText, const TFindItemSearchCase aSearchCase);

    private:
        
        /**
        * Adds item to search arrays. Adding is done so that arrays are always sorted.
        * If added element would overlap a previously found element, it is not added.
        *
        * @param aStartPos  Start position of the found item
        * @param aLength    Length of found item
        * @param aType      Type of the found item
        */
        void AddItemL( const TInt& aStartPos, const TInt& aLength, 
                       const TFindItemSearchCase& aType );

        /**
        * Search algorithm for searching phone numbers
        *
        * @param aText Text that will be parsed
        *
        * @return Whether any items were found
        */
        TBool SearchPhoneNumberL( const TDesC& aText);  

        /**
        * Search algorithm for searching e-mail addresses
        *
        * @param aText Text that will be parsed
        *
        * @return Whether any items were found
        */
        TBool SearchMailAddressL( const TDesC& aText);  

        /**
        * Search algorithm for searching generic URIs
        *
        * @param aText Text that will be parsed
        *
        * @return Whether any items were found
        */
        TBool SearchGenericUriL( const TDesC& aText);

        /**
        * Search fixed start URLs, i.e. URLs without schema (www., wap.).
        * Also finds plain IP addressess (*.*.*.*).
        * As a special case, supports deprecated hardcoded schematic addresses finding 
        * (http://, https://, rtsp://) to make sure deprecated search cases work 
        * as they did previously.
        *
        * @param aText Text that will be parsed
        * @param aFindFixedSchemas If true, will find old fixed schematic URLs also
        *
        * @return Whether any items were found
        */
        TBool SearchUrlL( const TDesC& aText, const TBool aFindFixedSchemas);

        /**
        * Parses URL from a token. Is used by SearchUrlL method and if a URL
        * was found it's appended to item array. Note that parsing for generic URIs 
        * is done with SearchGenericUriL -method.
        *
        * @param aType  a Type of URL to seach, i.e.
        *                   www.
        *                   wap.
        *                   IP e.g.127.0.0.1
        * @param        aTokenPtr Pointer to token that will be parsed
        * @param        aTextOffset Offset of the token (start position in the whole text)
        *
        * @return Whether any items were found
        */
        TBool ParseUrlL( const TDesC& aType, const TPtrC& aTokenPtr, const TInt aTextOffset );

        /**
        * Character information methods
        *
        * @param charac a Character to be investigated
        *
        * @return Whether the parameter was a valid for:
        */
        TBool IsValidEmailChar( const TChar& charac ) const; // Login part of the e-mail address
        TBool IsValidEmailHostChar( const TChar& charac ) const; // Host part of the e-mail address
        TBool IsValidPhoneNumberChar( const TChar& charac ) const; // Phone number
        TBool IsValidUrlChar( const TChar& charac ) const; // URL

        /**
        * C++ default constructor.
        */
        CFindItemEngine();

        /**
        * Symbian OS constructor
        *
        * @param aText          Text that will be parsed
        * @param aSearchCase    Identifies what items are we looking for:
        *                           EFindItemSearchPhoneNumberBin
        *                           EFindItemSearchMailAddressBin
        *                           EFindItemSearchURLBin
        *                           EFindItemSearchScheme
        *                       Any combination of these flags can be given
        *                       as a bit mask.
        */
        void ConstructL( const TDesC& aText, const TFindItemSearchCase aSearchCase );

		void PerformSearchL( const TDesC& aText , const TFindItemSearchCase aSearchCase );

		void ConvertArabicNumbersToWesternNumbers( HBufC* aBuf );

        // By default, prohibit copy constructor
        CFindItemEngine( const CFindItemEngine& );
        // Prohibit assigment operator
        CFindItemEngine& operator= ( const CFindItemEngine& );

    private:    // Data
        // Array of all found items.
        CArrayFixFlat<SFoundItem>* iItemArray;
		// Engine's position in the iItemArray and iItemTypeArray.
        TInt iPosition;

    };

#endif      // FINDITEMENGINE_H   
            
// End of File
