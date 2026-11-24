/*
* ============================================================================
*  Name     : PAlbFetch.h
*  Part of  : PhotoAlbum
*
*  Description:
*   Implements fetch popup for picture fetch and image fetch.
*  Version  :
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

#ifndef __PALBFETCH_H
#define __PALBFETCH_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <PAlbUtil.h>

// FORWARD DECLARATIONS
class CPAlbImageData;

// CLASS DECLARATION

// ============================================================================
// CPAlbImageFetchPopupList
// ============================================================================

/**
 *  @deprecated
 *  @see MGFetch
 *
 *   Fetching an image name, path from PhotoAlbum. It uses internally a
 *   modified AknPopUpList class.
 *
 *   To launch this popup just call:
 *
 *   CPAlbImageData* data = CPAlbImageData::NewL();
 *   CleanupStack::PushL( data );
 *   TBool result( CPAlbImageFetchPopupList::RunL( data ) );
 *   ...
 *   CleanupStack::PopAndDestroy(); // data
 *
 * Returns ETrue if the user selected a picture.
 * The name and path of the selected picture are stored in the CPAlbImageData object.
 */
class CPAlbImageFetchPopupList : public CBase, public MPAlbSubscriber
    {
    public:
        /**
         * Runs first the memory selection dialog and and if user selects OK
         * launches the popup and fills the data if image is selected.
         * @param aData image data to fill, fetch result is here
         * @return ETrue is image is selected, otherwise EFalse
         */
        IMPORT_C static TBool RunL( CPAlbImageData* aData );

    public: // Functions from base classes
        /**
         * Empty implementation.
         *
         * @param aModel publisher of the event
         * @param aEvent event to be handled
         */
        void Update( const CPAlbPublisher* aModel, TInt aEvent );

    private: // Constructors and destructor
        /**
         * Default constructor
         */
        CPAlbImageFetchPopupList();

        /**
         * destructor.
         */
        virtual ~CPAlbImageFetchPopupList();

    };

// ============================================================================
// CPAlbPictureFetchPopupList
// ============================================================================
/**
 * @deprecated
 * @see MGFetch
 *
 * Fetching a picture name, path from PhotoAlbum. It uses internally a
 * modified AknPopUpList class.
 *
 * To launch this popup just call:
 *
 * CPAlbImageData* data = CPAlbImageData::NewL();
 * CleanupStack::PushL( data );
 * TBool result( CPAlbPictureFetchPopupList::RunL( data ) );
 * ...
 * CleanupStack::PopAndDestroy(); // data
 *
 * Returns ETrue if the user selected a picture.
 * The name and path of the selected picture are stored in the CPAlbImageData object.
 */
class CPAlbPictureFetchPopupList : public CBase
    {
    public:
        /**
         * Runs the popup and fills the data if picture is selected.
         * @param aData image data to fill
         * @return ETrue if picture is selected, otherwise EFalse
         */
        IMPORT_C static TBool RunL( CPAlbImageData* aData );

        /**
         * Runs the popup with custom title text and fills the aData
         * if picture is selected.
         * @param aData image data to fill, fetch result is here
         * @param aTitle custom title text for the popup
         * @return ETrue if picture is selected, otherwise EFalse
         */
        IMPORT_C static TBool RunL( CPAlbImageData* aData, const TDesC& aTitle );

    private: // Constructors and destructor

        /**
         * default constructor
         */
        CPAlbPictureFetchPopupList();

        /**
         * destructor.
         */
        virtual ~CPAlbPictureFetchPopupList();

    private:    // Data
    };

#endif      // __PALBFETCH_H

// End of File