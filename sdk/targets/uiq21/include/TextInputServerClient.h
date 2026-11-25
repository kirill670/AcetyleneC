// TextInputServerClient.H
//
// Copyright (c) 2001 Symbian Ltd. All rights reserved
//

// This file defines the Client for the TextInputServer.

#ifndef __TEXTINPUTSERVERCLIENT_H__
#define __TEXTINPUTSERVERCLIENT_H__

// global include files
#include <e32base.h>
#include <e32std.h>
#include <gulalign.h>

// forward declaration
class CTextInputServerNotifier;
class CTextInputServerObserver;
class MTextInputObserver;

/**
 * Client class for the TextInputServer. The TextInputServer is an anchorpoint for the write-anywhere AnimationDLL, and handles
 * switching between the write-anywhere FEP and the InABox (e.g. virtual keyboard) FEP
 * 
 * @short Client class for the TextInputServer
 * @since Quartz 6.0
 */
class RTextInputServerClient : public RSessionBase
	{
	friend class CTextInputServerObserver;
public:
	IMPORT_C RTextInputServerClient();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C TVersion Version() const;
public:	// Typically used by applications
	inline TInt SetInABoxTiAllowed(TBool aAllowed) const;
	inline TInt SetWriteAnywhereTiAllowed(TBool aAllowed) const;
public:	// Typically used by applications or status bar etc
	IMPORT_C TInt StatusOfInABoxTi(TBool& aStatusActive) const;
	inline TInt OpenTextInputBox() const;
	inline TInt CloseTextInputBox() const;
public:	// Typically used by the status bar
	IMPORT_C void SetTextInputObserver(MTextInputObserver* aTextInputObserver);
	IMPORT_C TInt StartNotificationL();
	IMPORT_C void StopNotification();
public:	// Typically used by the control panel
	IMPORT_C TInt SetWriteAnywhereModule(const TDesC& aFepModuleName) const;
	IMPORT_C TInt GetWriteAnywhereModule(TFileName& aFepModuleName) const;
	IMPORT_C TInt SetInABoxModule(const TDesC& aFepModuleName) const;
	IMPORT_C TInt GetInABoxModule(TFileName& aFepModuleName) const;
	inline TInt SetFactorySettingsForWriteAnywhereTi() const;
	inline TInt SetFactorySettingsForInABoxTi() const;
public:	// Typically used by FEP developers
	IMPORT_C TInt LoadNewAnimDll(const TDesC& aHandAnimDllPath, TBool aDrawingWithMask = ETrue) const;
	IMPORT_C TInt AddSlaveSpriteAnim(TGulAlignment aCorner, TSize aSize) const;
	inline TInt UnloadActiveAnimDll() const;
	
	IMPORT_C TInt StatusOfWriteAnywhereTi(TBool& aStatusActive) const;
	inline TInt ActivateWriteAnywhereTi() const;
	inline TInt DeactivateWriteAnywhereTi() const;
	IMPORT_C TInt PassOnWriteAnywhereParameters(TInt anOpCode, TAny* aParameters) const;
	IMPORT_C TInt PassOnWriteAnywhereParametersReply(TInt anOpCode, TAny* aParameters, TInt& aResponse) const;
	inline TInt RestoreApplicationStatus() const;
public:	// functions for debugging only
	inline TInt DbgTisStopActiveScheduler() const;
	inline TInt DbgTisPanicServer() const;
	inline TInt DbgTisPanicClient() const;
private:
	IMPORT_C TInt GlobalSendFunction(TInt aSendFunction) const;
	enum
		{
		EUnloadAnimDll = 0,
		EDeactivateWriteAnywhere,
		EActivateWriteAnywhere,
		EAppProhibitsWriteAnywhere,
		EAppAllowsWriteAnywhere,
		ERestoreAppStatus,
		EOpenTextInputBox,
		ECloseTextInputBox,
		EAppAllowsInputBox,
		EAppProhibitsInputBox,
		EFactoryWriteAnywhere,
		EFactoryInputBox,
		EDbgStopScheduler,
		EDbgPanicServer,
		EDbgPanicClient
		};
private:
	CTextInputServerNotifier* iTisNotifier;
	CTextInputServerObserver* iServerObserver;
	MTextInputObserver* iTextInputObserver;
	};

/**
 * Mixin class for classes that want to get notified about changes in the TextInputServer
 *
 * @since Quartz v6.0
 */
class MTextInputObserver
	{
public:
	// notification reasons, that a client can get if it reqisters itself in the server
	enum TNotificationReasons
		{
		ETisNotifyTextInputBoxOpened,
		ETisNotifyTextInputBoxClosed,
		ETisNotifyWriteAnywhereTiActivated,
		ETisNotifyWriteAnywhereTiDeactivated,

		ETisNotifyRestoreApplicationStatus,
		
		ETisNotifyNewAnimDLL,
		ETisNotifyUnloadAnimDLL,
		ETisNotifyWriteAnywhereTiNotAllowed,
		ETisNotifyWriteAnywhereTiAllowed,
		ETisNotifyPassOnWriteAnywhereParameters,
		ETisNotifyPassOnWriteAnywhereParametersReply,
						
		ETisNotifyInABoxTiAllowed,
		ETisNotifyInABoxTiNotAllowed
		};
public:
	/**
	 * This function should get implemented by classes, that want to get notified by changes
	 * in the TextInputServer. This is the simplified interface of te MTextInputServerOBserver
	 * that is used internaly by the RTextInputServerClient
	 *
	 * @param aReason	The reason, why the client got notified, thus information,
	 *					about what changed inside the server.
	 *
	 * @see MTextInputServerObserver
	 * @see RTextInputServerClient
	 */
	virtual void HandleTextInputNotification(TNotificationReasons aReason) = 0;
	};


#include <TextInputServerClient.inl>

#endif	// __TEXTINPUTSERVERCLIENT_H__
