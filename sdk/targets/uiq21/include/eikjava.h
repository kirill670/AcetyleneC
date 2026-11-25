// EikJava.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKJAVA_H__
#define __EIKJAVA_H__

#include <e32base.h>
#include <coecntrl.h>

class CJavaAppletGroup;
class CEikAwtServer;
class MAppletObserver;
class CEikJava : public CBase
	{
public:
	IMPORT_C static CEikJava* NewL(); // possibly taking a server priority
	IMPORT_C void InitializeJava(TRequestStatus& aStatus);
	IMPORT_C CJavaAppletGroup* NewAppletGroupL(RWindow& aWindow,MAppletObserver* aObserver=NULL); // (const CCoeControl& aParent,MAppletObserver* aObserver=NULL) instead?? 
	IMPORT_C void ReStartServerIfNeeded();
	~CEikJava();
private:
	CEikJava();
	void ConstructL(TInt aPriority);
	static TInt LaunchJavaVM(TAny* );
	CEikAwtServer* iServer;
	RThread iJvmThread;
	};


class CJavaApplet;
struct Hjava_lang_Object;
class CJavaAppletGroup : public CBase
	{
public:
	IMPORT_C CJavaApplet* NewAppletL();
	IMPORT_C void Close(TRequestStatus& aStatus);
	IMPORT_C void Construct(TRequestStatus& aStatus);
	~CJavaAppletGroup();
	CJavaAppletGroup(CEikAwtServer* aServer,RWindow& aWindow,MAppletObserver* aObserver=NULL);
	void CompleteRequest(TInt aError);
private:
	RThread iUiThread; // used in CompleteRequest
	CEikAwtServer* iServer;
	MAppletObserver* iAppletObserver; // NB can be NULL
	RWindow iWindow;
	Hjava_lang_Object* iEmbeddedFrame;
	TRequestStatus* iStatusPtr;
	friend class CJavaApplet;
	friend class CEmbeddedFrameCreateCallback;
	friend class CEmbeddedFrameCloseCallback;
	friend class CAppletCreateCallback;
	friend class CAwtMessageHandler;
	};

  //class CDesCArray; // can't do this because it's a #define
#include <badesca.h>
class CJavaApplet : public CCoeControl
	{
public:
	IMPORT_C void AddParameterL(const TDesC& aNames,const TDesC& aValues);
	IMPORT_C void Construct(TRequestStatus& aStatus);
	IMPORT_C void AppletLoadL();
	IMPORT_C void AppletStopLoadL();
	IMPORT_C void AppletInitL();
	IMPORT_C void AppletStartL();
	IMPORT_C void AppletStopL();
	IMPORT_C void AppletDestroyL();
	IMPORT_C void AppletDisposeL();
	IMPORT_C void AppletQuit(TRequestStatus& aStatus);
	IMPORT_C TInt GetParameter(const TDesC& aName, TPtrC& aValue);
	~CJavaApplet();
private:
	CJavaApplet(CJavaAppletGroup* aGroup);
	void SetContainerWindowL(const CCoeControl& aContainer);
	void PositionChanged();
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void FocusChanged(TDrawNow aDrawNow);
	void SizeChanged();
	void CompleteRequest(TInt aError);
	void SendAppletMessageL(TInt aMessageNo);
	CDesCArray* iNames;
	CDesCArray* iValues;
	CJavaAppletGroup* iGroup;
	CCoeControl* iPanel;
	Hjava_lang_Object* iAppletPanel;
	RThread iUiThread; // used in CompleteRequest
	TRequestStatus* iStatusPtr;
	friend class CJavaAppletGroup;
	friend class CAppletCreateCallback;
	friend class CAppletQuitMessageCallback;
	TBool iFocus;
	};

class MAppletObserver
	{
public:
	enum TFocusTarget
		{
		ENext,
		EThis,
		EPrevious
		};
	// these are all optional
	IMPORT_C virtual void ShowStatus(const TDesC& aStatusMessage);
	IMPORT_C virtual void ResizeRequest(CJavaApplet* aApplet,const TSize& aNewSize);
	IMPORT_C virtual void MoveFocus(CJavaApplet* aApplet,TFocusTarget aTarget);
	IMPORT_C virtual void OpenUrl(const TDesC& aUrl);
	IMPORT_C virtual void OpenUrl(const TDesC& aUrl,const TDesC& aNewWindowName);
	};

#endif // __EIKJAVA_H__