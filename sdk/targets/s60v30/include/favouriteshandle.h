/*
* ============================================================================
*  Name     : FavouritesHandle.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class RFavouritesHandle.
*      
*  Version:
*
*  Copyright (C) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef FAVOURITES_HANDLE_H
#define FAVOURITES_HANDLE_H

//  INCLUDES

#include <e32base.h>
#include <FavouritesSession.h>

// CLASS DECLARATION

/**
* Favourites object handle.
*/
class RFavouritesHandle
    {

    public:     // Construct / destruct
        
        /**
        * Constructor.
        */
        inline RFavouritesHandle();

        /**
        * Close the object.
        */
        IMPORT_C void Close();

    public:     // New methods

        /**
        * Get handle number.
        * @return Handle number.
        */
        inline TInt Handle() const;

    protected:  // New methods

        /**
        * Open the object.
        * @param aSess Session to be used.
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @return Error code.
        */
        TInt Open
            (
            RFavouritesSession& aSess,
            TInt aFunction,
            const TIpcArgs& aArgs
            );

        /**
        * Open this object using other object.
        * @param aHandle Handle used to open this object.
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @return Error code.
        */
        TInt Open
            (
            RFavouritesHandle& aHandle,
            TInt aFunction,
            const TIpcArgs& aArgs
            );

        /**
        * Message passing routine.
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @param aStatus Request status.
        */
        void SendReceive
            (
            TInt aFunction,
            const TIpcArgs& aArgs,
            TRequestStatus& aStatus
            ) const;

        /**
        * Message passing routine.
        * @param aFunction Function.
        * @param aArgs Arguments.
        * @return Error code.
        */
        TInt SendReceive( TInt aFunction, const TIpcArgs& aArgs ) const;

        /**
        * Message passing routine.
        * @param aFunction Function.
        * @return Error code.
        */
        TInt SendReceive( TInt aFunction ) const;

    protected:  // Data

        RFavouritesSession iSess;   ///< Session handle.
        TInt iHandle;               ///< Handle number.

    };

#include <FavouritesHandle.inl>

#endif
            
// End of File
