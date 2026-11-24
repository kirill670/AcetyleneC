/*
* ==============================================================================
*  Name        : BrCtlInterface.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Definition of the Browser Control API
*  Version     : %Version%
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


#ifndef BRCTLINTERFACE_H
#define BRCTLINTERFACE_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <eikmenup.h>
#include <ssl.h>

#include <BrCtlDialogsProvider.h>
#include <BrCtlLayoutObserver.h>
#include <BrCtlLinkResolver.h>
#include <BrCtlSoftkeysObserver.h>
#include <BrCtlSpecialLoadObserver.h>
#include <BrCtlDefs.h>

// DATA TYPES

// FORWARD DECLARATIONS
class MBrCtlDataLoadSupplier;
class MBrCtlDataLoadConsumer;
class MBrCtlLoadEventObserver;
class MBrCtlDialogsProvider;
class TBrCtlWmlServiceOption;
class MBrCtlStateChangeObserver;

class CBrCtlInterface;
class CPluginInfo;

// EXPORTED FUNCTION
/**
* Create Browser Control.
  MSoftkeysObserver       // Default: browser does not update softkeys
  MLinkResolver           // Must be provided if ECapabilityClientResolveEmbeddedURL or ECapabilityClientNotifyURL is set
  MSpecialLoadObserver    // Default: DocumentHandler and SchemeDispatcher are not called by browser and connection created by Proxy Filter
  MLayoutObserver         // Default: Browser does not update scroll location
  MDialogsProvider        // Default: Use Browser's own dialogs
*/
IMPORT_C CBrCtlInterface* CreateBrowserControlL(CCoeControl* aParent, TRect aRect,
    TUint aBrCtlCapabilities, TUint aCommandIdBase = TBrCtlDefs::ECommandIdBase,
    MBrCtlSoftkeysObserver* aBrCtlSoftkeysObserver = NULL,
    MBrCtlLinkResolver* aBrCtlLinkResolver = NULL,
    MBrCtlSpecialLoadObserver* aBrCtlSpecialLoadObserver = NULL,
    MBrCtlLayoutObserver* aBrCtlLayoutObserver = NULL,
    MBrCtlDialogsProvider* aBrCtlDialogsProvider = NULL);


// CLASS DECLARATION
/**
*  Definition of the Browser Control API
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class CBrCtlInterface : public CCoeControl
    {
    public:  // Constructors and destructor

        /**
        * Destructor.
        */
      inline virtual ~CBrCtlInterface() {}

    public: // New functions
        
        /**
        * Pass a command to the Browser Control
        * @since 2.8
        * @param aCommand The command that the Browser Control should process
        * @return void
        */
        IMPORT_C virtual void HandleCommandL(TInt aCommand) = 0;
        
        /**
        * Return the display size that would be needed to see all the content
        * @since 2.8
        * @return The display size that would be needed to see all the content
        */
        IMPORT_C virtual TSize ContentSize() = 0;
        
        /**
        * Update a Browser Control setting
        * @since 2.8
        * @param aSetting The setting to update
        * @param aValue The new value of the setting
        * @return void
        */
        IMPORT_C virtual void SetBrowserSettingL(TUint aSetting, TUint aValue) = 0;
        
        /**
        * Get a setting from the Browser Control
        * @since 2.8
        * @param aSetting The setting to get
        * @return The value of the setting
        */
        IMPORT_C virtual TUint BrowserSettingL(TUint aSetting) = 0;
        
        /**
        * Request the Browser Control to display the content of a buffer
        * @since 2.8
        * @param aUrl A url that refers to the data. If a url scheme is used, it must be "data:"
        * @param aData The content to display. Browser Control does not take ownership
        * @param aDataType The data type of the data
        * @param aCharsetUid The UID of the character converter of the content's charset 0 assumed Latin-1
        * @return void
        */
        IMPORT_C virtual void LoadDataL(const TDesC& aUrl,
                                const TDesC8& aData,
                                const TDataType& aDataType,
                                TUid aCharsetUid) = 0;
        
        /**
        * Request the Browser Control to display content incrementaly
        * @since 2.8
        * @param aUrl A url that refers to the data. If a url scheme is used, it must be "data:"
        * @param aDataType The data type of the data
        * @param aCharsetUid The UID of the character converter of the content's charset 0 assumed Latin-1
        * @param aContentLength The length of the content.
        * @param aBrCtlDataLoadSupplier A callback interface to stop passing data if an error occured in the Browser Control
        * @param aBrCtlDataLoadConsumer A callback interface returned by the browser. Data should be passed to that interface
        * @return void
        */
        // The url scheme must be "data:" The url is needed as reference to this load request
        IMPORT_C virtual void InitLoadDataL(const TDesC& aUrl,
                                    const TDataType& aDataType,
                                    TUid aCharsetUid,
                                    TUint aContentLength,
                                    MBrCtlDataLoadSupplier* aBrCtlDataLoadSupplier,
                                    MBrCtlDataLoadConsumer** aBrCtlDataLoadConsumer) = 0;
        
        /**
        * Request the Browser Control to load a url
        * @since 2.8
        * @param aUrl The url to load
        * @param aApId The Access Point Id to use
        * @param aCacheMode The cache mode to use
        * @return void
        */
        IMPORT_C virtual void LoadUrlL( const TDesC& aUrl,
                                        TInt aApId = -1,
                                        TBrCtlDefs::TBrCtlCacheMode aBrCtlCacheMode = TBrCtlDefs::ECacheModeNormal) = 0;
        
        /**
        * Request the Browser Control to load and display a file from the file system
        * @since 2.8
        * @param aFileName The name of the file
        * @return void
        */
        IMPORT_C virtual void LoadFileL(const TDesC& aFileName) = 0;

        /**
        * Request the Browser Control to load and display a file from the file system
        * @since 2.8
        * @param aFileHandle The handle of the file
        * @return void
        */
        IMPORT_C virtual void LoadFileL(RFile& aFileHandle) = 0;

        /**
        * Return the WML Options for the current page
        * @since 2.8
        * @param 
        * @return The WML Options for the current page
        */
        IMPORT_C virtual RPointerArray<TBrCtlWmlServiceOption>* WMLOptionMenuItemsL()  = 0;
        
        /**
        * Request the Browser Control to add its own options to the option menu
        * @since 2.8
        * @param aMenuPane Handle of the menu that will contain the options
        * @param aResourceId The resource ID of the menu
        * @param aAfter WML options should be added after that index
        * @return void
        */
        IMPORT_C virtual void AddOptionMenuItemsL(CEikMenuPane& aMenuPane, TInt aResourceId, TInt aAfter=-1 ) = 0;

        /**
        * Request the Browser Control to clear the cache
        * @since 2.8
        * @return The number of bytes that were freed from cache
        */
        IMPORT_C virtual TUint ClearCache() = 0;

        /**
        * Ask the Browser Control if a URL is in cache
        * @since 2.8
        * @param aUrl The Url
        * @return ETrue, if a specific Url is in cache
        */
        IMPORT_C virtual TBool IsUrlInCache(TDesC& aUrl) = 0;

        /**
        * Ask the Browser Control to clear a URL from the cache
        * @since 2.8
        * @param aUrl The Url
        * @return KErrNone, or an error
        */
        IMPORT_C virtual TInt ClearItemInCache(TDesC& aUrl) = 0;

        /**
        * Request the Browser Control to return info about the page. The info is returned on the Cleanup Stack.
        * @since 2.8
        * @param aBrCtlPageInfo The type of requested info
        * @return A descriptor containing the requested page info
        */
        IMPORT_C virtual HBufC* PageInfoLC(TBrCtlDefs::TBrCtlPageInfo aBrCtlPageInfo ) = 0;
        
        /**
        * From CBrCtlInterface Query the Browser Control 
        * if there is a previous or next (depending on aDirection) element in history stack
        * @since 2.8
        * @return ETrue if can go aDirection, EFalse otherwise
        */
        IMPORT_C virtual TBool NavigationAvailable( TBrCtlDefs::TBrCtlNavigationDirection aDirection ) = 0;

        /**
        * Request the Browser Control to save the current content to a file
        * @since 2.8
        * @param aFileName The name of the file to use for saving the content
        * @return The number of bytes in the saved file
        */
        IMPORT_C virtual TUint16 SaveToFileL(const TDesC& aFileName) = 0;

        /**
        * Request the Browser Control to pass the server's certificate info for the current page 
        * @since 2.8
        * @return Certificate info of the server of the current page
        */
        IMPORT_C virtual const TCertInfo* CertInfo() = 0;
        
        /**
        * Request the Browser Control to register for load events
        * @since 2.8
        * @param aBrCtlLoadEventObserver A load events observer to add
        * @return void
        */
        IMPORT_C virtual void AddLoadEventObserverL(MBrCtlLoadEventObserver* aBrCtlLoadEventObserver) = 0;
        
        /**
        * Request the Browser Control to unregister for load events
        * @since 2.8
        * @param aBrCtlLoadEventObserver A load events observer to remove
        * @return void
        */
        IMPORT_C virtual void RemoveLoadEventObserver(MBrCtlLoadEventObserver* aBrCtlLoadEventObserver) = 0;

        /**
        * Return the number of images in the current page
        * @since 2.8
        * @param 
        * @return The number of images in the current page
        */
        IMPORT_C virtual TInt ImageCountL() = 0;

        /**
        * Returns the focused element
        * @since 2.8
        * @return The type of the focused element
        */
        IMPORT_C virtual TBrCtlDefs::TBrCtlElementType FocusedElementType() = 0;

        /**
        * Register an observer for state changes
        * @since 2.8
        * @param The observer to register
        * @return void
        */
        IMPORT_C virtual void AddStateChangeObserverL(MBrCtlStateChangeObserver* aBrCtlStateChangeObserver) = 0;

        /**
        * Unregister an observer for state changes
        * @since 2.8
        * @param The observer to unregister
        * @return void
        */
        IMPORT_C virtual void RemoveStateChangeObserver(MBrCtlStateChangeObserver* aBrCtlStateChangeObserver) = 0;

        /**
        * Request the Browser Control to return info about the Browser Control version. The info is returned on the Cleanup Stack.
        * @since 2.8
        * @param aVersionInfo The type of requested info
        * @return A descriptor containing the requested page info
        */
        IMPORT_C virtual HBufC* VersionInfoLC(TBrCtlDefs::TBrCtlVersionInfo aVersionInfo) = 0;

        /**
        * Pass a list of content types to the Browser Control.
        * These content types will not be using the download manager.
        * The list must be separated by ';' e.g. "text/html;text/wml"
        * @since 2.8
        * @param aContentTypes The content types that should not use Download Manager
        * @return void
        */
        IMPORT_C virtual void SetSelfDownloadContentTypesL(TDesC& aContentTypes) = 0;
        
        /**
        * Update a Browser Control parameter. consequent calls with the
        * same aParam will replace the value, and not append to it.
        * @since 2.8
        * @param aParam The parameter to update
        * @param aValue The new value of the parameter
        *        EParamsSelfDownoadableTypes: Pass a list of content types to the 
        *        Browser Control. These content types will not be using the 
        *        download manager. The list must be separated by ';' e.g. 
        *        "text/html;text/wml"
        *
        *        EParamsRequestHeaders: Pass a list of headers that the
        *        Browser Control. These headers will be added to each request.
        *        The list must be separated by '\r'. The header name and value must be 
        *        separated by ':'  e.g. 
        *        "x-myheader: myvalue\rx-myotherheader: myothervalue"
        * @return void
        */
        IMPORT_C virtual void SetParamL(TBrCtlDefs::TBrCtlParams aParam, const TDesC& aValue) = 0;

    public: // Functions from base classes
        
        // Functions from CCoeControl

        /**
        * From CCoeControl Return the minimum size the Browser Control can use
        * @since 2.8
        * @return The minimum size that the Browser Control can use
        */
        IMPORT_C virtual TSize MinimumSize() = 0;

        /**
        * From CCoeControl Pass key events to the Browser Control
        * @since 2.8
        * @param aKeyEvent The key event
        * @param aType The key code
        * @return If the Browser Control consumed the key event or not
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType) = 0;

        /**
        * From CCoeControl Sets that the Browser Control has keyboard focus.
        * @since 2.8
        * @param aFocus If the Browser Control gets or loses focus
        * @param ENoDrawNow If the Browser Control should redraw itself as result of focus change
        * @return void
        */
        IMPORT_C virtual void SetFocus(TBool aFocus, TDrawNow aDrawNow = ENoDrawNow) = 0;
    };


// CLASS DECLARATION
/**
*  A callback interface the Browser Control can use to cancel the load operation
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlDataLoadSupplier
    {
    public: // New functions
        /**
        * Cancel the load operation
        * @since 2.8
        * @return void
        */
    virtual void CancelLoad() = 0;
    };

// CLASS DECLARATION
/**
*  A callback interface in the Browser Control to incrementaly pass the content
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlDataLoadConsumer
    {
    public: // New functions
        /**
        * Pass the next data chunk
        * @since 2.8
        * @param aData The data chunk to process
        * @return void
        */
        virtual void HandleNextDataChunk(const TDesC8& aData) = 0;

        /**
        * Inform the Browser Control about completion of data load
        * @since 2.8
        * @return void
        */
        virtual void HandleLoadComplete() = 0;

        /**
        * Inform the Browser Control that an error occured
        * if HandleError() is called, then LoadComplete() is infered.
        * @since 2.8
        * @param aError The error code
        * @return void
        */
        virtual void HandleError(TInt aError) = 0;
    };

// CLASS DECLARATION
/**
*  This observer registers for load events
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlLoadEventObserver
    {
    public: // New functions
        /**
        * A load events notification
        * @since 2.8
        * @param aLoadEvent The load event   
        * @param aSize Size depends on the event
        * @param aTransactionId The transaction id of the transaction that had this event
        * @return void
        */
        virtual void HandleBrowserLoadEventL(TBrCtlDefs::TBrCtlLoadEvent aLoadEvent, TUint aSize, TUint16 aTransactionId) = 0;
    };

// CLASS DECLARATION
/**
*  Information of WML DO elements
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class TBrCtlWmlServiceOption
    {
    public:
        /**
        * Constructor
        * @since 2.8
        * @param aText The text to display in the WML service options
        * @param aElemID The element Id to use when the user selects this command
        */
        TBrCtlWmlServiceOption(HBufC* aText, TUint aElemID, TUint aActualElemID);

        inline const TDesC& Text() {return *iText;}
        inline TUint ElemID(){return iElemID;}
        inline TUint ActualElemID(){return iActualElemID;}

        /**
        * Destructor.
        */
        ~TBrCtlWmlServiceOption();

    private:    // Data
        /**
        * Default constructor
        * @since 2.8
        */
        TBrCtlWmlServiceOption() {};

        // The text to display in the WML service options
        HBufC* iText;
        // The element Id to use when the user selects this command
        TUint iElemID;
        // The actual element Id 
        TUint iActualElemID;
    };

// CLASS DECLARATION
/**
*  Observer for 
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlStateChangeObserver
    {
    public:
        virtual void StateChanged(TBrCtlDefs::TBrCtlState aState, TInt aValue) = 0;
    };

#endif      // BRCTLINTERFACE_H
            
// End of File
