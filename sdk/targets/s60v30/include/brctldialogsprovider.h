/*
* ==============================================================================
*  Name        : BrCtlDialogsProvider.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle dialogs needed for browser operation
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


#ifndef BRCTLDIALOGSPROVIDER_H
#define BRCTLDIALOGSPROVIDER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>

// DATA TYPES
enum TBrCtlSelectOptionType
    {
    ESelectTypeMultiple,  // Multiple select - Display a checkbox
    ESelectTypeSingle,    // Single select - Display a radio button
    ESelectTypeNone,      // Single select - Do not display any button
    ESelectTypeOkOnly         // Single select - Do not display any button, and no cancel button
    };

enum TBrCtlImageType
    {
    EImageTypeAny,
    EImageTypeWbmp,
    EImageTypeOta
    };


// FORWARD DECLARATIONS
class TBrCtlSelectOptionData;
class CBrCtlObjectInfo;
class TBrCtlImageCarrier;

// CLASS DECLARATION

/**
*  Provide dialogs needed for browser operation
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlDialogsProvider
    {
    public: // New functions
        
        /**
        * Notify the user of an error
        * @since 2.8
        * @param aErrCode The error that occured
        * @return void
        */
        virtual void DialogNotifyErrorL(TInt aErrCode) = 0;

        /**
        * Notify the user of an http error
        * @since 2.8
        * @param aErrCode The error that occured
        * @param aUri The uri of the request that failed
        * @return void
        */
        virtual void DialogNotifyHttpErrorL(TInt aErrCode, const TDesC& aUri) = 0;

        /**
        * File selection dialog
        * @since 2.8
        * @param aStartPath The initial displayed directory
        * @param aRootPath The top most directory that the user can go up to
        * @param aSelectedFileName The selected file name. Returned on cleanup stack. Browser control will free the buffer
        * @return TBool
        */
        virtual TBool DialogFileSelectLC(const TDesC& aStartPath,
                                         const TDesC& aRootPath,
                                         HBufC*& aSelectedFileName) = 0;

        /**
        * List selection dialog
        * @since 2.8
        * @param aTitle The title, could be empty
        * @param aBrCtlSelectOptionType The type of the list box 
        * @param aOptions A list of options to display
        * @return EFalse if the user canceled, ETrue otherwise
        */
        virtual TBool DialogSelectOptionL(const TDesC& aTitle, 
                                          TBrCtlSelectOptionType aBrCtlSelectOptionType, 
                                          CArrayFix<TBrCtlSelectOptionData>& aOptions) = 0;

        /**
        * User Authentication dialog. User name and password are returned on cleanup stack
        * @since 2.8
        * @param aUrl The url requiring authentication
        * @param aRealm The realm requiring authentication
        * @param aDefaultUserName The user name that was used before for this realm and path, if any
        * @param aReturnedUserName The user name entered by the user
        * @param aReturnedPasswd The password entered by the user
        * @param aBasicAuthentication A flag if basic authentication was used
        * @return EFalse if the user canceled, ETrue otherwise
        */
        virtual TBool DialogUserAuthenticationLC(const TDesC& aUrl, 
                                                 const TDesC& aRealm, 
                                                 const TDesC& aDefaultUserName, 
                                                 HBufC*& aReturnedUserName, 
                                                 HBufC*& aReturnedPasswd,
                                                 TBool aBasicAuthentication = EFalse) = 0;

        /**
        * Display a note to the user. No softkeys
        * @since 2.8
        * @param aMessage The message to display
        * @return void
        */
        virtual void DialogNoteL(const TDesC& aMessage) = 0; 

        /**
        * Display a note to the user with ok softkey only
        * @since 2.8
        * @param aTitle The title, could be empty
        * @param aMessage The message to display
        * @return void
        */
        virtual void DialogAlertL(const TDesC& aTitle, const TDesC& aMessage) = 0; 

        /**
        * Display confirmation message to the user
        * @since 2.8
        * @param aTitle The title, could be empty
        * @param aMessage The message to display
        * @param aYesMessage The text to display on left softkey
        * @param aNoMessage The text to display on right softkey
        * @return EFalse if the user canceled, ETrue otherwise
        */
        virtual TBool DialogConfirmL(const TDesC& aTitle,
                                     const TDesC& aMessage,
                                     const TDesC& aYesMessage,
                                     const TDesC& aNoMessage) = 0;

        /**
        * Display input dialog to the user
        * @since 2.8
        * @param aTitle The title, could be empty
        * @param aMessage The message to display
        * @param aDefaultInput The default input if available
        * @param aReturnedInput The input entered by the user. Returned on the cleanup stack
        * @return EFalse if the user canceled, ETrue otherwise
        */
        virtual TBool DialogPromptLC(const TDesC& aTitle,
                                     const TDesC& aMessage,
                                     const TDesC& aDefaultInput,
                                     HBufC*& aReturnedInput) = 0;

        /**
        * Display object info and ask confirmation before download
        * @since 2.8
        * @param aBrCtlObjectInfo The object info
        * @return EFalse if the user canceled, ETrue otherwise
        */
        virtual TBool DialogDownloadObjectL(CBrCtlObjectInfo* aBrCtlObjectInfo) = 0;

        /**
        * DIsplay the images that appear in the current page
        * @since 2.8
        * @param aPageImages The images that appear in this page
        * @return vois
        */
        virtual void DialogDisplayPageImagesL(CArrayFixFlat<TBrCtlImageCarrier>& aPageImages) = 0;

        /**
        * Cancel any dialog that is being displayed due to e.g. Browser exit or page was destroyed
        * @since 2.8
        * @return void
        */
        virtual void CancelAll() = 0;
        
        /**
        * Display search on page dialog
        * @since 3.0
        * @return void
        */
       virtual void DialogFindL() = 0; 
    };

// CLASS DECLARATION

/**
*  List of elements to display in the list box
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class TBrCtlSelectOptionData
    {
    public:
        /**
        * Default Constructor
        * @since 2.8
        */
        inline TBrCtlSelectOptionData()
                {   
                iText.Set(NULL, 0);
                iIsSelected = EFalse;
                iIsOptGroup = EFalse;
                iHasOnPick = EFalse;
                }

        /**
        * Constructor
        * @since 2.8
        * @param aText The text to display with this element
        * @param aIsSelected If the element is selected
        * @param aIsOptGroup If a title of option group or an element
        * @param aHasOnPick If has onPick, The dialog should close when the element is selected
        */
        inline TBrCtlSelectOptionData( const TDesC& aText, 
                                        TBool aIsSelected,
                                        TBool aIsOptGroup, 
                                        TBool aHasOnPick )
                                                            {
                                                            iText.Set(aText);
                                                            iIsSelected = aIsSelected;
                                                            iIsOptGroup = aIsOptGroup;
                                                            iHasOnPick = aHasOnPick; 
                                                            }

        inline const TDesC& Text() const {return iText;}
        inline TBool IsSelected() const {return iIsSelected;}
        inline TBool IsOptGroup() const {return iIsOptGroup;}
        inline TBool HasOnPick() const {return iHasOnPick;}

        inline void SetText( TDesC& aText )             { iText.Set( aText ); }
        inline void SetIsSelected( TBool aIsSelected )  { iIsSelected = aIsSelected; }
        inline void SetIsOptGroup( TBool aIsOptGroup )  { iIsOptGroup = aIsOptGroup; }
        inline void SetHasOnPick( TBool aHasOnPick )    { iHasOnPick = aHasOnPick; }

    private:    // Data
        // The text associated with the element
        TPtrC iText;
        // Flag if the element is selected
        TBool iIsSelected;
        // Flag if an element or oprion group title
        TBool iIsOptGroup;
        // Flag if the element has onPick
        TBool iHasOnPick; 
    };

// CLASS DECLARATION

/**
*  The object info
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class CBrCtlObjectInfo : public CBase
	{
	public:
        /**
        * Default Constructor
        * @since 2.8
        */
        CBrCtlObjectInfo();
    
        /**
        * Constructor
        * @since 2.8
        * @param aAppSupported A flag if there is a viewer app for this object
        * @param aPluginSupported A flag if there is a netscape plugin for this object
        * @param aSize The size of the object
        * @param aAppName The name of the viewer app or netscape plugin that supports this object
        * @param aFileType The content type of the object
        */
		CBrCtlObjectInfo(TBool aAppSupported, TBool aPluginSupported,
                         const TDesC& aSize, const TDesC& aAppName,
                         const TDesC& aFileType);
	public:
        inline void SetAppSupported(TBool aAppSupported) {iAppSupported = aAppSupported;}
        inline void SetPluginSupported(TBool aPluginSupported) {iPluginSupported = aPluginSupported;}
        inline void SetSize(const TDesC& aSize) {iSize.Set(aSize);}
		inline void SetAppName(const TDesC& aAppName) {iAppName.Set(aAppName);}
		inline void SetFileType(const TDesC& aFileType) {iFileType.Set(aFileType);}

        inline TBool AppSupported() {return iAppSupported;}
        inline TBool PluginSupported() {return iPluginSupported;}
        inline const TDesC& Size() const {return iSize;}
		inline const TDesC& AppName() const {return iAppName;}
		inline const TDesC& FileType() const {return iFileType;}
	private:
		// A flag if there is a viewer app for this object
        TBool iAppSupported;
        // A flag if there is a Netscape plugin for this object
		TBool iPluginSupported;
        // The size of the object
		TPtrC iSize;
        // The name of the viewer app or Netscape plugin
		TPtrC iAppName;
        // The content type of the object
		TPtrC iFileType;
	};

// CLASS DECLARATION

/**
*  Image info
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class TBrCtlImageCarrier
    {
    public:
        /**
        * Constructor
        * @since 2.8
        * @param aRawData The image data
        * @param aUrl The url of the image
        * @param aAltText The alt text of the image
        * @param aImageType The type of the image
        */
        TBrCtlImageCarrier(const TDesC8& aRawData, const TDesC& aUrl,
                           const TDesC& aAltText, TBrCtlImageType aImageType);

        inline const TDesC8& RawData() const {return iRawData;}
        inline const TDesC& Url() const {return iUrl;}
        inline const TDesC& AltText() const {return iAltText;}
        inline TBrCtlImageType ImageType() const {return iImageType;}
    private:
        TPtrC8 iRawData;
        TPtrC iUrl;
        TPtrC iAltText;
        TBrCtlImageType iImageType;
    };


#endif      // BRCTLDIALOGSPROVIDER_H   
            
// End of File
