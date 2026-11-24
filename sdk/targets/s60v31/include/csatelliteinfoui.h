/*
* ============================================================================
*  Name     : CSatelliteInfoUI.h
*  Part of  : SatInfo.dll
*  Interface: Public
*  Description: Implements interface for SatelliteInfoUI.
*  Version:
*
*  Copyright (c) 2005 Nokia Corporation.
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

#ifndef __SATELLITE_INFO_UI_H__
#define __SATELLITE_INFO_UI_H__

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATION
class CSatellite;

// CLASS DECLARATION
/**
 *  Implements entry point class to Satellite Info UI
 */
class CSatelliteInfoUI : public CBase
    {
    public:
        /**
         * Two-phased constructor.
         *
         * @return CSatelliteInfoUI.h object.
         */
        IMPORT_C static CSatelliteInfoUI* NewL();

        /**
         * Destructor.
         */
        IMPORT_C virtual ~CSatelliteInfoUI();

    private:
        /**
         * By default Symbian 2nd phase constructor is private.
         */
        void ConstructL();

        /**
         * C++ default constructor.
         */
        CSatelliteInfoUI();

    public: // new functions
        /**
         * Display satellite's information
         * @param aNameOfRule is requestor data for Location FW
         * @return TInt variable
         */
        IMPORT_C TInt ExecuteLD( const TDesC& aNameOfRule );

        /**
         * Dialog switched to foreground or background
         * @param aForeground ETrue to switch to the foreground. 
         * EFalse to switch to background.
         */
        IMPORT_C void HandleForegroundEventL(TBool aForeground);

    private: //Data

        /// Own: A pointer to CSatellite. Contains the engine and
        /// the dialog implementation.
        CSatellite* iSatellite;

        /// Own: A pointer to TBool
        TBool* iDestroyedPtr;

    };

// __SATELLITE_INFO_UI_H__
#endif

// End of File
