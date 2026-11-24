/*
* ==============================================================================
*  Name        : BrCtlDefs.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Enum Definition of the Browser Control API
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


#ifndef BRCTLDEFS_H
#define BRCTLDEFS_H

//  INCLUDES

// DATA TYPES

// FORWARD DECLARATIONS

// EXPORTED FUNCTION

// CLASS DECLARATION
/**
*  Definition of the enums for Browser Control API
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class TBrCtlDefs
    {
    public:  
        enum TBrCtlCommandId
            {
            ECommandIdBrowserBase = 0,
            ECommandIdSubscribeToBase = 90,
            ECommandIdPluginBase = 100,
            ECommandIdWMLBase = 300,
            ECommandIdRange = 600,
            ECommandIdBase = 15000
            };
        
        enum TBrCtlCacheMode
            {
            ECacheModeNormal = 0,
            ECacheModeHistory,
            ECacheModeNoCache,
            ECacheModeOnlyCache
            };
        
        enum TBrCtlCommands
            {
            ECommandDisconnect = 0,
            ECommandCancelFetch,
            ECommandOpen,
            ECommandReload,
            ECommandBack,
            ECommandForward,
            ECommandClearHistory,
            ECommandShowHistory,
            ECommandAccept,
            ECommandCancel,
            ECommandOpenToViewer,
            ECommandAddToPhoneBook,
            ECommandMakeCall,
            ECommandRemoveFileName,
            ECommandShowImages,
            ECommandLoadImages,
            ECommandGainFocus,
            ECommandLoseFocus,
            ECommandFindItem,
            ECommandFindItemPhoneNumber,
            ECommandFindItemEMail,
            ECommandFindItemAddress,
            ECommandFindKeyword,
      		ECommandClearFind,
			ECommandShowThumbnailView,
            ECommandShowDownloads,
			ECommandSaveLaunchParams,
			ECommandOneStepBack
            };
        
        enum TBrCtlLoadEvent
            {
            EEventNone = 0,                     // Non event = 0
            EEventNewContentStart,              // start notification, no parameters
            EEventUrlLoadingStart,              // start url notification, trid
            EEventNewUrlContentArrived,         // total size, trid
            EEventMoreUrlContentArrived,        // received size, trid
            EEventNewContentDisplayed,          // no parameters
            EEventMoreContentDisplayed,         // no parameters
            EEventUrlLoadingFinished,           // trid
            EEventLoadFinished,                 // no parameters
            EEventContentFinished,              // no parameters
            EEventTitleAvailable,               // no parameters
            EEventLoadError,                    // error code, trid
            EEventEnteringSecurePage,           // entering secure page   
            EEventExitingSecurePage,            // exiting secure page
            EEventSomeItemsNotSecure,           // unsecure item(s) on secure page
            EEventSubmittingToNonSecurePage,    // submitting to nonsecure page
            EEventRedirectConfirmation,         // redirecting confirmation
            EEventRepostConfirmation,           // repost confirmation
            EEventSecureItemInNonSecurePage,    // secure item(s) on unsecure page
            EEventAuthenticationFailed,         // canceled/failed authentication
            EEventUploadStart,                  // start file upload notification, trid TotalSize
            EEventUploadFinished,               // last chunk of data is transmitted, trid
            EEventUploadIncrement               // transmitted data length, trid, cumulative uploaded size
            };
        
        enum TBrCtlSettings
            {
            ESettingsUnknown = -1,
            ESettingsSmallScreen = 0,
            ESettingsAutoLoadImages,
            ESettingsFontSize,
            ESettingsEmbedded,
            ESettingsTextWrapEnabled,
            ESettingsCookiesEnabled,
            ESettingsCSSFetchEnabled,
            ESettingsECMAScriptEnabled,
            ESettingsIMEINotifyEnabled,
            ESettingsCharacterset,
            ESettingsSendRefererHeader,
            ESettingsSecurityWarnings,
            ESettingsApId,
            ESettingsCurrentZoomLevelIndex,
            ESettingsPageOverview,
            ESettingsNumOfDownloads,
            ESettingsLaunchAppUid,
            ESettingsLaunchViewId,
            ESettingsLaunchCustomMessageId,
            ESettingsBackList,
            ESettingsAutoRefresh,
            ESettingsBrowserUtf8Encoding,
            ESettingsMaxEnum
            };
        
        enum TBrCtlFontSizeLevel
            {
            EFontSizeLevelAllSmall = 0,
            EFontSizeLevelSmaller,
            EFontSizeLevelNormal,
            EFontSizeLevelLarger,    
            EFontSizeLevelAllLarge
            };
        
        enum TBrCtlCapabilities
            {
            ECapabilityDisplayScrollBar         = 0x0001, // Browser control display scrollbars
            ECapabilityClientResolveEmbeddedURL = 0x0002, // Embedded content loads are sent to client application. client indicates if load should go ahead
            ECapabilityClientNotifyURL          = 0x0004, // Top level URL load requests are sent to client, client indicates if load should go ahead
            ECapabilityDisableInputAndPlugins   = 0x0008, // Disable browser's ability to place itself on top of the control stack
            ECapabilityFindItem                 = 0x0010,
            ECapabilityLoadHttpFw               = 0x0020,
            ECapabilityUseDlMgr                 = 0x0040, 
            ECapabilityLaunchViewer             = 0x0080,
			ECapabilityGraphicalHistory			= 0x0100,
			ECapabilitySavedPage				= 0x0200,
			ECapabilityConfirmDownloads	        = 0x0400  // Enable confirmation of confirmation dialog in the Download Mgr
            };
        
        enum TBrCtlPageInfo
            {
            EPageInfoTitle = 0,
            EPageInfoUrl,
            EPageInfoContent,
            EPageInfoSavedPage
            };

        enum TBrCtlState
            {
            EStateImageMapView = 0,
            EStateHistoryView,
            EStateThumbnailView
            };

        enum TBrCtlElementType
            {
            EElementNone,
            EElementImageBox,
            EElementAnchor,
            EElementTelAnchor,
            EElementMailtoAnchor,
            EElementInputBox,
            EElementActivatedInputBox,
            EElementSelectBox,
            EElementButton,
            EElementTextAreaBox,
            EElementRootBox,
            EElementObjectBox,
            EElementActivatedObjectBox,
            EElementDownloadedObjectBox,
            EElementFileSelectionBoxNoContent,
            EElementFileSelectionBoxWithContent,
            EElementAreaBox,
            EElementCheckBoxChecked,
            EElementCheckBoxUnChecked,
            EElementRadioButtonSelected,
            EElementRadioButtonUnSelected
            };
        
        enum TBrCtlNavigationDirection
            {
            ENavigationBack,
            ENavigationForward
            };

        enum TBrCtlVersionInfo
	        {
	        EVersionInfoName = 0,
	        EVersionInfoVersion,
	        EVersionInfoBuild
	        };

        enum TBrCtlParams
            {
            EParamsUnknown = -1,
            EParamsSelfDownoadableTypes = 0,
            EParamsRequestHeaders,
            EParamsMax
            };
            
		enum TBrCtlFindResponse
			{
			EFindNoMatches = 0,
			EFindWrapAround,
            EFindAllMatches,     
            EFindMatch
			};

        enum TBrCtlMethod
            {
            EMethodGet,
            EMethodPost
            };

		enum TBrCtlDownloadCmd
			{
			EDownloadCmdPause,
			EDownloadCmdResume,
			EDownloadCmdCancel,
			EDownloadCmdMarkAsProgressive,
			EDownloadCmdMarkAsNotProgressive
			};

    };

#endif      // BRCTLDEFS_H
            
// End of File
