/** -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
  *
  * Copyright (C) 2002 Opera Software AS.  All rights reserved.
  *
  * This file is part of the Opera web browser.  It may not be distributed
  * under any circumstances.
  *
  * @file OprCntrlEnv.h
  *
  * Contains the definition of the COperaControlEnv class.
  *
  * @author Keith Hollis
  */

#include <e32base.h>

#include "epocmodel.h"

class COperaControl;

/*************************************************************************

	class MOperaControlObserver
*/

class MOperaControlObserver
    {
public:
    virtual void LoadingComplete()=0;
    };

/*************************************************************************

	class MOperaControlAdapter
*/

class MOperaControlAdapter
    {
public:
    virtual HBufC* RemapUrlLC(const TDesC& aUrl)=0;
    };

/*************************************************************************

	class MOperaControlMediator
*/

class MOperaControlMediator : public MOperaControlObserver, public MOperaControlAdapter
    {
    };

/*************************************************************************

	class COperaControlEnv
*/

class COperaControlEnv : public CBase, public MOperaModelMediator
    {
public:
    IMPORT_C static COperaControlEnv* NewL(const TDesC& aSubFolder=_L("Component"));
    IMPORT_C ~COperaControlEnv();
private: // from MOperaModelObserver
    void HeaderLoaded(const TDesC&aUrl, const TDesC8&aHeaders);
    void DocStartLoading(const TDesC&aUrl);
    void ImageLoaded(const TDesC&aUrl);
    void DocLoaded(const TDesC&aUrl);
private: // from MOperaModelAdapter
    void CompilePluginListL();
    TCookieAction GetCookieAction(const TDesC&aUrl, TInt version, const TDesC8&aCookieRequest);
    TCookieMode GetCookiesEnabled(const TDesC&aUrl,TCookieMode aCurrentMode);
    TBool GetCachePersistent(const TDesC&aUrl,TBool aCurrentFlag);
    TBool AllowNewWindow(const TDesC&aUrl,const TDesC&aName);
    TBool AddToGlobalHistory(const TDesC&aUrl);
    TBool GetShowImages(const TDesC&aUrl,TBool aCurrentFlag);
    TBool GetLoadImages(const TDesC&aUrl,TBool aCurrentFlag);
    TBool ChangeUrlName(const TDesC&aUrl,HBufC*&aNewUrl);
	// Requests from base code to EPOC UI
    void ReportErrorL(TInt aError);
	void ShowInfoDialogL(const TDesC& aTitle,const TDesC& aText);
	TBool ShowConfirmDialogL(const TDesC& aTitle,const TDesC& aText);
	void WarnCookieDomainErrorL(const TDesC& aUrl,const TDesC& aCookie);
    void AskCookieL(COperaAskCookieInfo* aInfo);
	TBool AskAuthenticationL(const TDesC& aTitle,const TDesC& aMessage,
							 const TDesC& aServer,TDes& aUsername,TDes& aPassword);
    TBool AskFileLocationL(TDes& aFileName);
    TBool AskTextL(const TDesC& aCaption,HBufC*& aText);
	void HandleUnrecognisedURLSchemeL(const TDesC& aUrl);
	TUnknownDataAction QueryUnknownDocumentL(const TDesC& aServer,const TDesC8& aMimeType,
                                             const TDesC& aName,TInt aFileSizeInBytes,
                                             const TDesC8& aHttpHeaders, TFileName& aFileName);
    void UnknownDocumentDownloadCompleteL(const TFileName& aFileName);
	void ShowTransferViewL();
    TBool ExtendUAStringL(const TDesC8& aString,HBufC8*& aExtend,TBool aUtn);
    HBufC* RemapUrlLC(const TDesC& aUrl);
	TBool AllowRefreshUrlL(const TDesC& aUrl);
    void GetHardwareSpecificRequestData(const TDesC8&aRequest,const TDesC8&aRequestBody,const TDesC8*&aContentType,HBufC8*&aBuffer);
    TBool AskToReconnectL();
public: // new
    IMPORT_C static COperaControlEnv* COperaControlEnv::Static();
    IMPORT_C void SetOperaObserver(MOperaControlObserver*aObserver);
    IMPORT_C void SetOperaAdapter(MOperaControlAdapter*aAdapter);
    IMPORT_C void SetOperaMediator(MOperaControlMediator*aMediator);
    IMPORT_C COperaModel* Model() { return iModel; }
private: // new
    COperaControlEnv();
    void ConstructL(const TDesC& aSubFolder);
private:
    COperaModel* iModel;
    MOperaControlObserver* iControlObserver;
    MOperaControlAdapter* iControlAdapter;
	TFileName iLastSaveAsFileName;
    };