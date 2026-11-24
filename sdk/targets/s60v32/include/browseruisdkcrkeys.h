#ifndef BROWSERUISDKCRKEYS_H
#define BROWSERUISDKCRKEYS_H

const TUid KCRUidBrowserUiLV = {0x101F861B};
const TUid KCRUidBrowser   = {0x10008D39};

// Users should be able to select the volume for plugins
// Valid Values: (mute)0,2,5,8,10(maximum)
const TUint32 KBrowserMediaVolumeControl =  0x0000001C;

// The setting for CSS fetching.
// Valid values: 0 = disabled, 1 = enabled
const TUint32 KBrowserCSSFetch =            0x00000003;

// Boolean value which determines if text inside <nowrap>
// tags on a wml page should be wrapped.
// Valid values: 0 = On, 1 = Off
const TUint32 KBrowserTextWrapEnabled =     0x00000004;

// Browser Security Dialog suppression setting.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserSecurityUI =          0x00000008;

// Variant specific Browser encoding setting.
// Valid values: any positive 32-bit integer value
const TUint32 KBrowserDefaultCharset =      0x00000009;

// Default access point, UID of the AP record.
// Valid values:any positive 32-bit integer value
const TUint32 KBrowserDefaultAccessPoint =  0x0000000E;

// Indicates whether the user has to confirm DTFM sending or not.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserConfirmDTMFSending =  0x00000017;

// Browser IMEI notification setting. UAProf filter uses
// this key to decide whether to send phone's IMEI code
// within User-Agent header. IMEI notification feature is
// only ON if the operator requests it.#
// Valid values: 0 = disable 1 = enable
const TUint32 KBrowserIMEINotification =    0x00000018;

// Integer value to turn on or off the send referrer
// header option.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserSendReferrerHeader =  0x00000019;

// Flags for variating Browser engine
// Any Integer value
const TUint32 KBrowserEngineFlags =         0x00000001;

// These content types will be handled specially like descriptor contents
// Any String value
const TUint32 KBrowserSelfDownloadContentTypes = 0x0000001D;

// Defines the access point selection mode (User defined, Always ask, Destination)
// Valid values: 0 = User Defined, 1 = Always Ask, 2 = Destination
// User defined is also what so called Connection Method after SNAP introduction
const TUint32 KBrowserAccessPointSelectionMode = 0x0000001E;

// Setting for DownloadManager to indicate the available drives on harware.
// Valid values: constant string with maximum length of 52bytes,
const TUint32 KBrowserDrivePrefListForDownloadedContent = 0x00000021;

// The flag that's set if Browser build is to be used in United States (USA)
// Valid values: 0 = not set (non-US build)  1 = set (US build)
const TUint32 KBrowserUsBuild =             0x00000023;

// Indicates whether the user has confirmed DTFM once or not.
// Valid values: 0 = no 1 = yes
const TUint32 KBrowserConfirmedDTMFOnce =  0x00000024;

/**
*
* OSS Browser Keys
*
*/

// Load Content 
// Valid values: 
// If flash plugin is present: 0 = Text only, 1 = Images,No flash, 2 = All
// If flash plugin is not present 0 = Text only, 1 = All
const TUint32 KBrowserNGImagesEnabled =       	0x00000025;

// Browser font size.
// Valid values:any positive 32-bit integer value
const TUint32 KBrowserNGFontSize =            	0x00000026;

// Browser encoding setting.
// Valid values: any positive 32-bit integer value
const TUint32 KBrowserNGEncoding =            	0x00000027;

// Browser uses cookies.
// Valid values: 0 = reject 1 = allow
const TUint32 KBrowserNGCookiesEnabled =      	0x0000002B;

// Boolean value which determines whether ECMA Script
// setting is enabled or disabled in Browser.
// Valid values: 0 = disabled 1 = enabled
const TUint32 KBrowserNGECMAScriptSupport =   	0x0000002C;

// Show HTTP security warnings.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserNGShowSecurityWarnings= 	0x0000002D;

// Show Page Overview.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserNGPageOverview = 		  	0x0000002E;

// Mime types for HTTP accept header.
// Any String value
const TUint32 KBrowserNGMimeTypes = 		  	0x00000032;

// Show History view on back softkey press.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserNGBackList = 		  		0x00000033;

// Auto refresh.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserNGAutoRefresh = 		  	0x00000034;

// The setting for encoding a URL with UTF-8 or the original encoding.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserNGUtf8Encoding = 	  		0x00000036;

// With this setting automatic updating of
// Wen Feeds can be set on (with anupdate interval) or off.
// Valid values:
// 0 = Every week
// 1 = Every day
// 2 = Every 4 hours
// 3 = Every hour
// 4 = Every 15 minutes
// 5 = Off
const TUint32 KBrowserNGAutomaticUpdating = 	0x00000037;

// Short cut keys for function: Navigates to home page
// Any String value
const TUint32 KBrowserNGShortCutFuncHomePg =    0x0000003A;

// Short cut keys for function: Go to bookmark 
// Any String value
const TUint32 KBrowserNGShortCutFuncBkMark =    0x0000003B;

// Short cut keys for function: Find keyword
// Any String value
const TUint32 KBrowserNGShortCutFuncFindKeyWord  =    0x0000003C;

// Short cut keys for function: Go to the previous page
// Any String value
const TUint32 KBrowserNGShortCutFuncPrePage =    0x0000003D;

// Short cut keys for function: Switch window
// Any String value
const TUint32 KBrowserNGShortCutFuncSwitchWin =    0x0000003E;

// Short cut keys for function: Toggles miniature image on/off
// Any String value
const TUint32 KBrowserNGShortCutFuncMiniImage =    0x0000003F;

// Short cut keys for function: Go to address
// Any String value
const TUint32 KBrowserNGShortCutFuncGoAddr =    0x00000040;

// Short cut keys for function: Zoom in
// Any String value
const TUint32 KBrowserNGShortCutFuncZoomIn =    0x00000041;

// Short cut keys for function: Zoom out
// Any String value
const TUint32 KBrowserNGShortCutFuncZoomOut =    0x00000042;

// Smart Link.
// Valid values: 0 = off 1 = on
const TUint32 KBrowserNGSmartLink = 		  	0x00000046;    

// The access point used when Web Feeds was updated automatically
const TUint32 KBrowserNGAutomaticUpdatingAccessPoint =     0x00000043;

// Setting to enable "Rotate display" menu item
const TUint32 KBrowserNGRotateDisplay =          0x00000044;

// Setting to enable "Open download" menu item
// Valid value 0 = no, 1 = yes 
const TUint32 KBrowserNGOpenDownloads =          0x00000045;


const TUint32 KBrowserNGAutomaticUpdatingWhileRoaming = 0x00000047;

// Setting to enable the Http Optimisations (HttpFilterOptB)
// Valid values: 0 = disabled, 1 = enabled
const TUint32 KBrowserNGHttpOptBEnabled	=        0x00000050;

//The FileManager UID
const TUint32 KFileManagerUid =               0x00000052;

//the key used to get the default snap id
const TUint32 KBrowserNGDefaultSnapId =    0x00000053;

// Int value which determines if and how
// script console is enabled in Browser.
// Valid values: 0 = disabled 1 = log to file 1 = log to UI console
const TUint32 KBrowserNGScriptLog =   	0x00000054;

// BROWSERUISDKCRKEYS_H
#endif
