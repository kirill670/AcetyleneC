/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis, Rob Gregson
*/

#ifndef __EPOCMODEL_H
#define __EPOCMODEL_H

#include <apfctlf.h>
#include <apgctl.h>
#include <eiklbm.h>
#include <e32std.h>
#include <fbs.h>
#include <nifman.h>

#include "epocbridgeenv.h"
#include "epocabstractdocwin.h"

// #define _JAVA_LIB_UNLOAD_

class URL;
class CEpocDownload;
class MOperaDownload;
class MessageHandler;
class CDelayMessage;
class Cookie_Item_Handler;
class Window;
class CEpocLineBreaker;
class CJavaLibUnloadTimer;
class CNetworkActiveTimer;

/*********************************************************************************

	class COperaSSLCertificateInfo

*/

#if defined(_SSL_SUPPORT_) && !defined(_EXTERNAL_SSL_SUPPORT_)

class COperaSSLCertificateInfo
	{
public:
    IMPORT_C COperaSSLCertificateInfo();
    IMPORT_C ~COperaSSLCertificateInfo();
public:
    TBool iPublicKeyOnly;
    TBool iDeny;
    TBool iWarn;
    HBufC* iCurrentCertFullNameText;
    HBufC* iCurrentCertIssuerText;
    HBufC* iCurrentCertInfoText;
	};

#endif // _SSL_SUPPORT_ && !_EXTERNAL_SSL_SUPPORT_

/*********************************************************************************

  COperaHistoryItem

*/

class COperaHistoryItem : public CBase
    {
public:
    void ConstructL(const TDesC& aUrl,const TDesC& aTitle,TTime aAccessed);
    ~COperaHistoryItem();
    TPtrC Url() { return *iUrl; }
    TPtrC Title() { return *iTitle; }
    TTime Accessed() { return iAccessed; }
private:
    HBufC* iUrl;
    HBufC* iTitle;
    TTime iAccessed;
    };

/*********************************************************************************

  COperaAskCookieInfo

*/

class COperaAskCookieInfo : public CBase
    {
public:
    COperaAskCookieInfo(Cookie_Item_Handler*aHandler);
    void ConstructL();
    ~COperaAskCookieInfo();
public: // new
	Cookie_Item_Handler* Handler() const { return iHandler; }
	CArrayFixFlat<TAskCookieAction>* Actions() const { return iActions; }
	TPtrC Url() const { return *iUrl; }
	TPtrC Name() const { return *iName; }
	TPtrC Value() const { return *iValue; }
	TPtrC Domain() const { return *iDomain; }
	TPtrC Path() const { return *iPath; }
	TBool DontAskAgain() const { return iDontAskAgain; }
    TBool Accepted() const { return iAccepted; }
    TBool IllegalPath() const { return iIllegalPath; }
	TAskCookieAction SelectedAction() const { return iSelectedAction; }
	void SetAction(TAskCookieAction aAction) { iSelectedAction=aAction; }
	void SetDontAskAgain(TBool aSet) { iDontAskAgain=aSet; }
    void SetAccepted(TBool aSet=ETrue) { iAccepted=aSet; }
private:
    Cookie_Item_Handler* iHandler;
    CArrayFixFlat<TAskCookieAction>* iActions;
	HBufC* iUrl;
	HBufC* iName;
	HBufC* iValue;
	HBufC* iDomain;
	HBufC* iPath;
    TBool iIllegalPath;
    TAskCookieAction iSelectedAction;
    TBool iDontAskAgain;
    TBool iAccepted;
    };

/*********************************************************************************

	class MOperaModelObserver

*/

class MOperaModelObserver
	{
public:
    virtual void HeaderLoaded(const TDesC& aUrl, const TDesC8& aHeaders)=0;
    virtual void DocStartLoading(const TDesC& aUrl)=0;
    virtual void ImageLoaded(const TDesC& aUrl)=0;
    virtual void DocLoaded(const TDesC& aUrl)=0;
    };

/*********************************************************************************

	class MOperaModelAdapter

*/

class MOperaModelAdapter
	{
public:
    // Control calls to change Opera's default operation
    virtual void CompilePluginListL()=0;
    virtual TCookieAction GetCookieAction(const TDesC& aUrl, TInt version, const TDesC8& aCookieRequest)=0;
    virtual TCookieMode GetCookiesEnabled(const TDesC& aUrl,TCookieMode aCurrentMode)=0;
    virtual TBool GetCachePersistent(const TDesC& aUrl,TBool aCurrentFlag)=0;
    virtual TBool AllowNewWindow(const TDesC& aUrl,const TDesC& aName)=0;
    virtual TBool AddToGlobalHistory(const TDesC& aUrl)=0;
    virtual TBool GetShowImages(const TDesC& aUrl,TBool aCurrentFlag)=0;
    virtual TBool GetLoadImages(const TDesC& aUrl,TBool aCurrentFlag)=0;
    virtual TBool ChangeUrlName(const TDesC& aUrl,HBufC*& aNewUrl)=0;

	// Requests from base code to EPOC UI
    virtual void ReportErrorL(TInt aError)=0;
	virtual void ShowInfoDialogL(const TDesC& aTitle,const TDesC& aText)=0;
	virtual TBool ShowConfirmDialogL(const TDesC& aTitle,const TDesC& aText)=0;
	virtual void WarnCookieDomainErrorL(const TDesC& aUrl,const TDesC& aCookie)=0;
	virtual void AskCookieL(COperaAskCookieInfo* aInfo)=0;
	virtual TBool AskAuthenticationL(const TDesC& aTitle,const TDesC& aMessage,
									 const TDesC& aServer,TDes& aUsername,TDes& aPassword)=0;
	virtual TBool AskFileLocationL(TDes& aFileName)=0;
	virtual TBool AskTextL(const TDesC& aCaption,HBufC*& aText)=0;

	/**
	  * Handles the recognition of an unknown URL
	  * 
	  * @param aUrl The unrecogniserd url.
	  *
	  * Leaves on error.
	  */
	virtual void HandleUnrecognisedURLSchemeL(const TDesC& aUrl)=0;

	/**
	  * Returns an action defined by user in response to information about unknown data
	  * 
	  * @param aServer - the server's url
	  * @param aMimeType - the mime type of the unknown document (KNullDesC if unknown)
	  * @param aName - the suggested name of the download file
	  * @param aFileSizeInBytes - size (or -1 if unknown)
	  * @param aHttpHeaders - The HTTP headers received in the server response
	  * @param aFileName - user selected filename
	  *
	  * @return TUnknownDataAction - the action chosen by the user
	  *
	  * Leaves on error.
	  */
	virtual TUnknownDataAction QueryUnknownDocumentL(const TDesC& aServer,const TDesC8& aMimeType,
                                                     const TDesC& aName,TInt aFileSizeInBytes,
                                                     const TDesC8& aHttpHeaders, TFileName& aFileName)=0;
    virtual void UnknownDocumentDownloadCompleteL(const TFileName& aFileName)=0;
   
    virtual void ShowTransferViewL()=0;
    virtual TBool ExtendUAStringL(const TDesC8& /*aString*/,HBufC8*& /*aExtend*/,TBool /*aUtn*/) { return EFalse; }
	virtual HBufC* RemapUrlLC(const TDesC& aUrl)=0;
	virtual TBool AllowRefreshUrlL(const TDesC& aUrl)=0;

	// Core extensions
	virtual void GetHardwareSpecificRequestData(const TDesC8& aRequest,const TDesC8& aRequestBody,
												const TDesC8*& aContentType,HBufC8*& aBuffer)=0;

    virtual TBool AskToReconnectL()=0;
	};

/*********************************************************************************

	class MOperaModelMediator

*/

class MOperaModelMediator : public MOperaModelObserver, public MOperaModelAdapter
	{};

/*********************************************************************************

	class COperaModel

*/

class MOperaTransferFactory;
class SSL_Options;
class CISPNotifier;

class COperaModel : public CBase, public MEpocBridgeAdapter
	{
public:
	static IMPORT_C COperaModel* NewL(RFs& aFs);
	IMPORT_C ~COperaModel();
private:
	void ConstructL(RFs& aFs);
public: // from MEpocBridgeAdapter
    void ReportErrorL(TInt aError);
public: // new
    IMPORT_C void InitialiseL(RFs& aFs,const TDesC& aWriteDrive,const TDesC& aSubFolder=TPtrC());
	IMPORT_C void PrepareForExit();
	IMPORT_C void SetDocWindowFactory(MOperaDocWindowFactory* aDocWindowFactory);
	MOperaDocWindowFactory* DocWindowFactory() const;
	IMPORT_C void SetMediator(MOperaModelMediator* aMediator);
	MOperaModelObserver* Observer() const;
	MOperaModelAdapter* Adapter() const;
    RLibrary& JavaLibrary();
    IMPORT_C void SetTransferFactory(MOperaTransferFactory* aTransferFactory);
    MOperaTransferFactory* TransferFactory();
    IMPORT_C CArrayPtr<COperaHistoryItem>* CompileArrayOfHistoryItemsLC();
    IMPORT_C void DeleteAllHistoryItems();
#ifdef USE_OP_EPOC_CHARCONV
	TBool CanBreakBetweenChars(TText c1, TText c2);
#endif // USE_OP_EPOC_CHARCONV
    TBool NetworkActive();
public: // Signals from the UI code
    IMPORT_C void InsertPluginL(const TFileName& aDllFile);
    IMPORT_C void OpenUrlL(const TDesC& aUrl=TPtrC(),TBool aNewWindow=EFalse);
    IMPORT_C void ReloadAll();
    IMPORT_C void CloseAllConnections();
public: // Signals from dialog interfaces
    IMPORT_C void Commit(); // Commits all changed preferences to disk.
    // Commits all file information to disk (cookies, cache, global history, visited links).
    IMPORT_C void CommitFilesL();
    IMPORT_C TBool OfflineModeIsOn() const;
    IMPORT_C void SetOfflineMode(TBool aOffline=ETrue);
	IMPORT_C const TDesC* HomeUrl();
	IMPORT_C void SetHomeUrlL(const TDesC* aHomeUrl);
    // Dialog: Connections/General preferences
	IMPORT_C TOperaAlternateBrowserType GetIdentifyAs() const;				
	IMPORT_C void SetIdentifyAs(TOperaAlternateBrowserType aBrowserType);	
	IMPORT_C TBool UseAbsoluteFTPPathIsOn() const;
	IMPORT_C void SetUseAbsoluteFTPPath(TBool aState);
	IMPORT_C TInt GetHttpErrorStrategy() const;
	IMPORT_C void SetHttpErrorStrategy(TBool aState);
    // Dialog: Connections/Performance preferences
    IMPORT_C TBool SyncDNSLookupIsOn() const;
	IMPORT_C void SetSyncDNSLookup(TBool aState);
	IMPORT_C TInt GetMaxConnectionsServer() const;
	IMPORT_C void SetMaxConnectionsServer(TInt16 aConnections);
	IMPORT_C TInt GetMaxConnectionsTotal() const;
	IMPORT_C void SetMaxConnectionsTotal(TInt16 aConnections);
    // Dialog: Privacy/General+Cookies preferences
    IMPORT_C TBool ReferrerEnabled() const;
	IMPORT_C TCookieMode CookieMode() const;
	IMPORT_C TBool ConfirmCookies() const;
	IMPORT_C TBool CookiesSessionOnly() const;
	IMPORT_C void SetLogging(TBool aRefState,TCookieMode aCookieMode,TBool aConfirm,TBool aSessionOnly);
    IMPORT_C TBool EnableClientPull() const;
    IMPORT_C void SetEnableClientPull(TBool aSet);
    IMPORT_C TBool TagUrls() const;
    IMPORT_C void SetTagUrls(TBool aSet);
    IMPORT_C TBool CookiesShowDomainErr() const;
    IMPORT_C void SetCookiesShowDomainErr(TBool aSet);
    IMPORT_C TBool CookiesShowPathErr() const;
    IMPORT_C void SetCookiesShowPathErr(TBool aSet);
    // Dialog: Name completion
	IMPORT_C TBool CheckLocalIsOn() const;
	IMPORT_C TBool NameCompletionIsOn() const;
	IMPORT_C const TDesC* Prefices() const;
	IMPORT_C const TDesC* Suffices() const;
	IMPORT_C void SetNameCompletionSettingsL(TBool aCheckLocal,TBool aNameCompletion,
										     const TDesC& aPrefixBuf,const TDesC& aSuffixBuf);
    // Dialog: Appearance/General preferences
    IMPORT_C TInt DefaultZoomFactor() const;
    IMPORT_C void SetDefaultZoomFactor(TInt aZoomFactor);
	IMPORT_C TBool GetEnableFrames() const;
	IMPORT_C void SetEnableFrames(TBool aState);
	IMPORT_C TBool GetEnableInlineFrames() const;
	IMPORT_C void SetEnableInlineFrames(TBool aState);
	IMPORT_C TBool GetActiveFrameBorder() const;
	IMPORT_C void SetActiveFrameBorder(TBool aState);
	IMPORT_C TBool GetDocumentModeAsDefault() const;
	IMPORT_C void SetDocumentModeAsDefault(TBool aDocModeIsDefault);
    // Dialog: Appearance/User CSS file preferences
	IMPORT_C TDesC* GetUserCSSFile() const;
	IMPORT_C void SetUserCSSFileL(const TDesC* aCSSFile);
    // Dialog: Appearance/Document/User mode preferences
	IMPORT_C TBool GetEnableDocumentCSS(TCSSDisplayMode aMode) const;
	IMPORT_C void SetEnableDocumentCSS(TCSSDisplayMode aMode,TBool aState);
	IMPORT_C TBool GetEnableDocumentFontAndColors(TCSSDisplayMode aMode) const;
	IMPORT_C void SetEnableDocumentFontAndColors(TCSSDisplayMode aMode,TBool aState);
	IMPORT_C TBool GetEnableUserCSS(TCSSDisplayMode aMode) const;
	IMPORT_C void SetEnableUserCSS(TCSSDisplayMode aMode,TBool aState);
	IMPORT_C TBool GetEnableUserFontAndColors(TCSSDisplayMode aMode) const;
	IMPORT_C void SetEnableUserFontAndColors(TCSSDisplayMode aMode,TBool aState);
	IMPORT_C TBool GetEnableUserLinks(TCSSDisplayMode aMode) const;
	IMPORT_C void SetEnableUserLinks(TCSSDisplayMode aMode,TBool aState);
	IMPORT_C TBool GetEnableTables(TCSSDisplayMode aMode) const;
	IMPORT_C void SetEnableTables(TCSSDisplayMode aMode,TBool aState);
    // Dialog: Proxy preferences
	IMPORT_C void GetProxyServerUsage(TBool& aHttp, TBool& aHttps, TBool& aFtp, TBool& aGopher, TBool& aWais) const;
	IMPORT_C void SetProxyServerUsage(TBool aHttp, TBool aHttps, TBool aFtp, TBool aGopher, TBool aWais);
	IMPORT_C void GetHTTPProxyServerAndPort(TDes& aServer, TDes& aPort) const;
	IMPORT_C void GetHTTPSProxyServerAndPort(TDes& aServer, TDes& aPort) const;
	IMPORT_C void GetFTPProxyServerAndPort(TDes& aServer, TDes& aPort) const;
	IMPORT_C void GetGopherProxyServerAndPort(TDes& aServer, TDes& aPort) const;
	IMPORT_C void GetWAISProxyServerAndPort(TDes& aServer, TDes& aPort) const;
	IMPORT_C void SetProxyServersL(const TDesC& aHttpServer, const TDesC& aHttpsServer,
								   const TDesC& aFtpServer, const TDesC& aGopherServer,
								   const TDesC& aWaisServer);
    // Dialog: Proxy exceptions
    IMPORT_C HBufC* GetProxyExceptionsL(TBool& aUse) const;
    IMPORT_C void SetProxyExceptionsL(const TDesC& aExpections,TBool aUse);
    // Dialog: Multimedia preferences
	IMPORT_C TImageDisplayMode GetImageDisplayMode() const;
	IMPORT_C void SetImageDisplayMode(TImageDisplayMode aDisplayMode);
    IMPORT_C TBool AnimationOn() const;
	IMPORT_C void SetAnimationOnL(TBool aOn=ETrue);
    // Dialog: JPEG preferences
	IMPORT_C TJpegDCTMethod GetJpegDctMethod() const;
	IMPORT_C TBool GetJpegSmoothing() const;
	IMPORT_C TJpegDithering GetJpegDithering() const;
	IMPORT_C TJpegPasses GetJpegPasses() const;
	IMPORT_C TBool GetJpegProgrDownload() const;
    IMPORT_C void SetJpegSettings(TJpegDCTMethod aDctMethod,TBool aSmoothing,TJpegDithering aDitheringMethod,TJpegPasses aPasses,TBool aProgressive);
    // Dialog: Plugins preferences
    IMPORT_C TBool PluginsOn() const;
    IMPORT_C void SetPluginsOn(TBool aPlugins);
    IMPORT_C TBool ECMAScriptOn() const;
    IMPORT_C void SetECMAScriptOn(TBool aECMAScript);
    IMPORT_C TBool ECMAScriptErrorsOn() const;
    IMPORT_C void SetECMAScriptErrorsOn(TBool aECMAScriptErrors);
    IMPORT_C TBool JavaOn() const;
    IMPORT_C void SetJavaOn(TBool aJava);
    // Dialog: Cache preferences
	IMPORT_C TInt GetDiskCacheSize() const;
	IMPORT_C void SetDiskCacheSize(TInt aCacheSize);
	IMPORT_C TBool GetDiskCacheDocsOn() const;
	IMPORT_C TBool GetDiskCacheImagesOn() const;
	IMPORT_C TBool GetDiskCacheOtherOn() const;
	IMPORT_C void SetDiskCacheSettings(TBool aCacheDocs, TBool aCacheImages,TBool aCacheOther);
	IMPORT_C TBool GetEmptyCacheOnExitOn() const;
	IMPORT_C void SetEmptyCacheOnExit(TBool aEmptyCache);
    IMPORT_C TBool GetAutomaticRamCacheOn() const;
    IMPORT_C void SetAutomaticRamCache(TBool aSet);
	IMPORT_C TBool GetRamCacheDocsOn() const;
	IMPORT_C TBool GetRamCacheImagesOn() const;
	IMPORT_C void SetRamCacheSettings(TBool aDocCache, TInt aImagesCache);
	IMPORT_C TInt GetRamCacheDocumentsSize() const;
	IMPORT_C TInt GetRamCacheFiguresSize() const;
	IMPORT_C void SetRamCacheSize(TInt aDocCacheSize, TInt aImagesCacheSize);
	IMPORT_C TBool GetTurboModeOn() const;
	IMPORT_C void SetTurboMode(TBool aTurboModeOn);
	IMPORT_C TBool GetCacheCheckModifiedDocsOn() const;
	IMPORT_C TBool GetCacheCheckModifiedImagesOn() const;
	IMPORT_C TBool GetCacheCheckModifiedOtherOn() const;
	IMPORT_C void SetCacheCheckModifiedModes(TBool aCheckModifiedDocsOn,TBool aCheckModifiedImagesOn,TBool aCheckModifiedOtherOn);
	IMPORT_C TBool GetCacheCheckRedirectDocsOn() const;
	IMPORT_C void SetCacheCheckRedirectDocsMode(TBool aCheckRedirectDocsOn);
	IMPORT_C TBool GetCacheCheckRedirectImagesOn() const;
	IMPORT_C void SetCacheCheckRedirectImagesMode(TBool aCheckRedirectImagesOn);	
    IMPORT_C void EmptyDiskCache();
    // Dialog: Security preferences
#if defined(_SSL_SUPPORT_) && !defined(_EXTERNAL_SSL_SUPPORT_)
	IMPORT_C void CreateSecurityManager();
	IMPORT_C void DestroySecurityManager();
	IMPORT_C TBool GetSSL2On() const;
	IMPORT_C void SetSSL2On(TBool aSSL2State);
	IMPORT_C TBool GetSSL3On() const;
	IMPORT_C void SetSSL3On(TBool aSSL3State);
	IMPORT_C TBool GetTLS1On() const;
	IMPORT_C void SetTLS1On(TBool aTLS1State);
	IMPORT_C TInt GetPasswordRequestFrequency() const;
	IMPORT_C void SetPasswordRequestFrequency(TInt aFrequency);
#endif // _SSL_SUPPORT_ && !_EXTERNAL_SSL_SUPPORT_
	IMPORT_C TBool GetInsecurePostAlertOn() const;
	IMPORT_C void SetInsecurePostAlertOn(TBool aPostAlertState);
    // Dialog: Personal/Authority certificates
#if defined(_SSL_SUPPORT_) && !defined(_EXTERNAL_SSL_SUPPORT_)
    IMPORT_C TInt CertificateCount(TBool aPersonal) const;
	IMPORT_C const TDesC* GetCertTitle(TBool aPersonal,TInt aIndex) const;
	IMPORT_C void GetCertificateInfo(TBool aPersonal,TInt aIndex,COperaSSLCertificateInfo&aInfo) const;
	IMPORT_C void SetCertificateInfo(TBool aPersonal,TInt aIndex,TBool aWarn,TBool aDeny);
	IMPORT_C void DeleteCertificate(TBool aPersonal,TInt aIndex);
	IMPORT_C void InstallCertChain(TBool aWarn, TBool aDeny);
#endif // _SSL_SUPPORT_ && !_EXTERNAL_SSL_SUPPORT_
    // Dialog: Startup and exit
	IMPORT_C TOnStartupShow GetOnStartupShow() const;
	IMPORT_C void SetOnStartupShow(TOnStartupShow aStartupShow);
	IMPORT_C TBool GetConfirmExit() const;
	IMPORT_C void SetConfirmExit(TBool aConfirm);
	IMPORT_C TBool GetCloseConnectionOnExit() const;
	IMPORT_C void SetCloseConnectionOnExit(TBool aClose);
	IMPORT_C TBool GetSaveWindowsOnExit() const;
	IMPORT_C void SetSaveWindowsOnExit(TBool aSave);

    IMPORT_C TPtrC8 GetDefaultEncoding() const;
    IMPORT_C void SetDefaultEncodingL(const TDesC8& aCharset);

    IMPORT_C TPtrC GetPreferenceString(const TDesC& aKey,const TDesC& aDefault=TPtrC()) const;
    IMPORT_C void SetPreferenceString(const TDesC& aKey,const TDesC& aValue);
    IMPORT_C TInt GetPreferenceInt(const TDesC& aKey,TInt aDefault=0) const;
    IMPORT_C void SetPreferenceInt(const TDesC& aKey,TInt aValue);

    IMPORT_C void CompleteAskCookieRequestL(COperaAskCookieInfo* aInfo);
    IMPORT_C void ReclaimMemory(TBool aAgressive=EFalse);
    IMPORT_C void DeleteTemporaryCookies();
    IMPORT_C void DeleteAllCookies();
    IMPORT_C TBool ServerNameIsTrustedL(const TDesC8& aName) const;

#ifdef _JAVA_LIB_UNLOAD_
   	/**
	  * Reference Incrementor for Java Library unloading
	  */
    IMPORT_C void JavaLibRefCountInc();
   	/**
	  * Reference Decrementor for Java Library unloading
      * Starts a timer to unload the JVM after a time period
	  */
    IMPORT_C void JavaLibRefCountDec();
    void JavaLibUnload();
#endif // _JAVA_LIB_UNLOAD_

public:
	enum TZoomDirection
		{
		EZoomIn=0,
		EZoomOut
		};

public: // new
    void AddTransferItemL(URL&aUrl,const TDesC& aFileName,Window *aWindow);
	CEpocDownload* HasDownloadItem(URL& aUrl);
public: // for deferred message handling
    void AppendDeferredMessage(CDelayMessage* aMessage);
    void RemoveDeferredMessages(MessageHandler* aMessageHandler);
    void ProcessDeferredMessages();
    void SetNetworkActiveShutout(TBool aShutout) { iNetworkActiveShutout=aShutout; }
public: // for deferred message handling
    TInt iDisableMessages;
    CArrayFixFlat<CDelayMessage*> *iDeferredMessageList;

private:
    TInt iStringsResource; // Handle for strings.rsc resource file.

    CEpocBridgeEnv* iBridgeEnv;

    MOperaDocWindowFactory* iDocWinFactory;
	MOperaModelObserver* iModelObserver;
	MOperaModelAdapter* iModelAdapter;
	MOperaTransferFactory* iTransferFactory;
	mutable HBufC* iTempHBuf;					// text output buffer

    RLibrary iJavaLibrary;
#ifdef _JAVA_LIB_UNLOAD_
    TInt iJavaLibRefCount;
    CJavaLibUnloadTimer *iJavaLibUnloadTimer;
#endif // _JAVA_LIB_UNLOAD_
#ifdef USE_OP_EPOC_CHARCONV
	CEpocLineBreaker* iLineBreaker;
#endif // USE_OP_EPOC_CHARCONV

	CArrayFixFlat<CEpocDownload*>* iDownloads;
    CPeriodic* iDownloadTimer;

	// Is this right??
	SSL_Options* iOperaSecurityManager;

    CPeriodic* iBlinkTimer;
	CISPNotifier *iISPNotifier;

    TBool iNetworkActiveShutout;
    CNetworkActiveTimer* iNetworkActiveTimer;
    TBool iNetworkActiveValue;
	};

#endif // __EPOCMODEL_H
