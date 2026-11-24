/*
* ==============================================================================
*  Name        : AknIconSrvClient.h
*  Part of     : AknIconSrv
*  Interface   : N/A
*  Description : 
*
*  Version     : 1
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


#ifndef AKN_ICON_SRV_CLIENT_H
#define AKN_ICON_SRV_CLIENT_H

// INCLUDES
#include <e32base.h>
#include <AknIconUtils.h>

// CONSTANTS

// FORWARD DECLARATIONS
struct TAknIconParams;
struct TAknIconInitData;
class CAknBitmap;
class CAknIconManager;

// CLASS DECLARATION

class RAknIconSrvClient : public RSessionBase
    {
    public: // New functions


        /**
        * Constructor.
        */      
        RAknIconSrvClient();


        /**
        * Connects AknIconSrv session. It is stored in TLS.
        * Application framework calls this in application startup.
        *
        * @return Symbian OS standard error code
        */      
        IMPORT_C static TInt Connect();

        /**
        * Disconnects the session.
        */
        IMPORT_C static void Disconnect();


        /**
        * Returns the connected server client from TLS.
        * Panics if Connect() has not been called successfully earlier.
        */
        static RAknIconSrvClient* GetSession();

    public: // But not exported.

        /**
        * Initializes the given bitmap and mask according to the member data stored in them
        * and the given pixel size.
        */
        void InitializeIconL( 
            CAknBitmap& aBitmap,
            CAknBitmap& aMask,
            const TAknIconParams& aInfo ) const;

        /**
        * Frees the shared bitmap.
        */
        void FreeBitmap( CAknBitmap& aBitmap ) const;

        /**
        * Gets content dimensions of the icon.
        */
        TInt GetContentDimensions( 
            CAknBitmap& aBitmap, TSize& aContentDimensions ) const;

        /**
        * Preserves icon data (e.g. SVG-T DOM tree) in memory.
        */
        TInt PreserveIconData( CAknIconManager& aBitmap ) const;

        /**
        * Removes icon data (e.g. SVG-T DOM tree) from the memory.
        */
        void DestroyIconData( CAknIconManager& aBitmap ) const;

        /**
        * Retrieves initialisation data from server side.
        */
        void GetInitData( TAknIconInitData& aData ) const;

        /*
        * Support for OOM testing the server side.
        */
        void __SERVER_HEAP_MARK() const;
        void __SERVER_HEAP_MARKEND() const;
        void __SERVER_HEAP_FAILNEXT( TInt aCount ) const;
        void __SERVER_HEAP_FAILNEXT_INCREASING( TInt aCount ) const;
        void __SERVER_HEAP_RESET() const;
        void __SERVER_RESET_DYNAMICALLY_CHANGING_ALLOCATIONS() const;
        TInt __SERVER_HEAP_USED() const;

        TInt ConnectToServer();

    private: // Data
        TInt iConnections;

    };

#endif // AKN_ICON_SRV_CLIENT_H

// End of File
