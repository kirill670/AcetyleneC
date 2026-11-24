/*
* ==============================================================================
*  Name        : CLmkEditorDlg.h
*  Part of     : Landmarks UI / LmkCommonUI.dll
*  Interface   : Public
*  Description : This class provides functionality for viewing and editing 
*                landmark data.
*  Version     : 
*
*  Copyright (c) 2004 Nokia Corporation.
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

#ifndef CLMKEDITORDLG_H
#define CLMKEDITORDLG_H

//  INCLUDES
#include "EPos_CPosLandmark.h"
#include <EPos_Landmarks.h> // Lm typedefs, constants etc.
#include <e32base.h>        // CBase

// FORWARD DECLARATIONS
class CPosLandmarkDatabase;
class CPosLandmark;
class CLmkEditorImpl;
class MObjectProvider;
class TCoeHelpContext;
class CLmkSender;

// TYPE DEFINITIONS
typedef TUint32 TLmkEditorAttributes;
typedef TInt TLmkEditorMode;

// CLASS DECLARATION
/**
*  Landmark editor dialog.
*  This class provides functionality for viewing and editing landmark data.
*  It is also possible to disallow editing and use the dialog as a viewer only.
*
*@enum _TLmkEditorAttributes 
*@enum _TLmkEditorMode 
*/
class CLmkEditorDlg : public CBase
    {
    public: // Types
                
        enum _TLmkEditorAttributes
            {
            ELmkOnlyName            = 0x0000,   // name field is always shown
            ELmkCategory            = 0x0001,
            ELmkStreet              = 0x0002,
            ELmkCity                = 0x0004,
            ELmkStateProvince       = 0x0008,
            ELmkCountry             = 0x0010,
            ELmkPostalZIP           = 0x0020,
            ELmkLatitude            = 0x0040,
            ELmkLongitude           = 0x0080,
            ELmkPositionAccuracy    = 0x0100,
            ELmkAltitude            = 0x0200,
            ELmkAltitudeAccuracy    = 0x0400,
            ELmkAll                 = 0xFFFF,    // all fields are shown
            ELmkDescription         = 0x0800,
            ELmkPhoneNumber         = 0x1000,
            ELmkWebAddress          = 0x2000         
            };
        
	    enum _TLmkEditorMode
		    {
            ELmkEditor, // editing allowed
		    ELmkViewer  // only viewing allowed
            };

        /**
        * Editor parameters class.
        */
        class TLmkEditorParams
            {
            public:  // Constructors and destructor
                /**
                * C++ Constructor.
                * @return newly instantiated object
                */
                IMPORT_C TLmkEditorParams();

                // Compiler-generated destructor is ok for this class;

            private:  // Unimplemented functions
                // Unimplemented copy constructor
                TLmkEditorParams( const TLmkEditorParams& );

                // Unimplemented assignment operator
                TLmkEditorParams& operator = ( const TLmkEditorParams& );

            public:  // Input parameters

                /**
                * Defines which landmark attributes are shown in editor/viewer
                * Default attributes used if not specified.
                */
                TLmkEditorAttributes iAttributes;

                /**
                * Editor mode options. By default editing is allowed.
                */
                TLmkEditorMode iEditorMode;
            };

    public:  // Constructors and destructor
        /**
        * Creates a landmark editor for editing a landmark which already
        * exists in aDb.
        * @param aDb landmark database, does not need to be initialized
        * @param aLandmark landmark id,which exists in Landmarks database.
        * @param aParams attributes whether to launch landmark in viewer mode
        *        or editor mode.
        * @leave Leaves with KErrNotFound,If the landmark does not exist in the database
        *        Leaves with KErrNotSupported if framework
        * functionality is not available.
        * @return new instance of this class
        */
        IMPORT_C static CLmkEditorDlg* NewL( CPosLandmarkDatabase& aDb,
                                             TPosLmItemId aLandmarkId,
                                             TLmkEditorParams& aParams );

        /**
        * Creates a landmark editor for editing a landmark which does not yet
        * exist in aDb. aLandmark may contain filled-in data.Client can get
        * id of the newly created landmark by using Landmarks Selector API.
        * @param aDb landmark database, does not need to be initialized
        * @param aLandmark pre-filled landmarks object.
        * @param aParams aParams attributes whether to launch landmark in viewer mode
        *        or editor mode.
        * @leave Leaves with KErrNotFound,If the landmark does not exist in the database
        *        Leaves with KErrNotSupported if framework
        * @return new instance of this class
        */
        IMPORT_C static CLmkEditorDlg* NewL( CPosLandmarkDatabase& aDb,
                                             CPosLandmark& aLandmark,
                                             TLmkEditorParams& aParams );

        /**
        * Destructor. Can be also used to cancel this dialog.
        */
        IMPORT_C ~CLmkEditorDlg();

    public: // New functions
        /**
        * Object provider mechanism.
        * @param aParent parent object
        */
        IMPORT_C void SetMopParent( MObjectProvider* aParent );

        /**
        * Sets help context. There are many applications using landmark editor
        * and they may have an own help topic to be shown, when editor's help
        * is launched. With this command it's possible to define the used
        * help content. Landmark's own help context used as default.
        * @param aContext help context to use
        */
        IMPORT_C void SetHelpContext( TCoeHelpContext aContext );

        /**
        * Runs the dialog. This object is destroyed when this function
        * returns or leaves.
        * Editor mode: 
        * Saving Landmarks without entering Landmark name is not allowed
        * Saving can fail due to less memory and an info note is displayed.
        * If any of the landmark fields are filled and landmark name is not provided,
        * an info note is displayed while closing the dialog else the dialog gets closed without
        * landmark being saved.
        * In Editor mode,  the user can edit the landmark fields(some or all) and can save the 
        *                  Landmarks 
        * In Viewer mode, the user can view the Landmark contents by accepting the dialog
        *                      Canelling the dialog will close the dialog 
        * @return Returns non-zero if accepted,else zero
        */
        IMPORT_C TInt ExecuteLD();
        /**
        * This function when invoked, disables the Map and Navigation related Menu Options 
        * This needs to be invoked before ExecuteLD().By default, the Map and Navigation
        * menu options are enabled and are shown.
        *
        */
        IMPORT_C void DisableMapAndNavigationMenuOptions();

    private:
        /**
        * C++ default constructor.
        * @return newly instantiated object
        */
        CLmkEditorDlg();
        
        /**
        * By default Symbian 2nd phase constructor is private.
        * @param aDb
        * @param aParams
        * @param aLandmarkId
        * @param aLandmark
        */
        void ConstructL( CPosLandmarkDatabase& aDb,
                         TLmkEditorParams& aParams,           
                         TPosLmItemId aLandmarkId,
                         CPosLandmark* aLandmark );

    private:    // Data
        /// Own: Search implementor object
        CLmkEditorImpl* iEditorImpl;

        /// Own: A pointer to TBool
        TBool* iDestroyedPtr;

        /// Own: Landmark sender object
        CLmkSender* iSender;
    };

// CLMKEDITORDLG_H
#endif

// End of File
