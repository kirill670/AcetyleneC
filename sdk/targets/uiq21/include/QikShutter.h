// QikShutter.h
//
// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKSHUTTER_H__
#define __QIKSHUTTER_H__

#include <EikEnv.h>

/**
 * This class defines an interface used by the CQikShutter to target the control
 * that should be closed. Any control implementing this interface will automatically 
 * be targeted by the shutter, and will consequently be closed down (through the 
 * ShutL() method) when a view switch between two applications occurs, or if 
 * the application is closed down by e.g. the backup or memory manager.
 *
 * @since Quartz 6.1
 */
class MQikShutterTarget
	{
public:
	IMPORT_C MQikShutterTarget();
	IMPORT_C virtual ~MQikShutterTarget();
	/**
	 * When called, the ShutL() method shall close down the control and return ETrue. To refuse the 
	 * shut, EFalse must be returned. Doing this will stop the shutter from continuing.
	 */
	virtual TBool ShutL() = 0;
	virtual const CCoeControl& AsControl() const = 0;
	};


/**
 * Do not use! 
 * This class is for Symbian use only. 
 * The API might change at any time.
 *
 * @internal
 */
class CQikShutter : private CActive
	{
public:
	enum TAppExitOption
		{
		EAlwaysExitApp, 
		ENeverExitApp,
		EExitIfAutoExitFlagSet
		};
public:
	IMPORT_C static CQikShutter* DeferredExecuteL(CEikonEnv& aEikEnv, TAppExitOption aExitApp, CQikShutter** aObserver = NULL, TInt aPriority = EActivePriorityWsEvents+1);
	static void DeferredExecuteL(CEikonEnv& aEikEnv, TUid aMessageUid, const TDesC8& aMessageParameters, TAppExitOption aExitApp);
	~CQikShutter();
private: // virtual from CActive
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);
private:
	CQikShutter(CEikonEnv& aEikEnv, TUid aMessageUid, HBufC8* aMessageParameters, TAppExitOption aExitApp, CQikShutter** aObserver, TInt aPriority);
	void Queue();
	void Terminate();
	static TInt StartLevel();
private:
	enum TFlags
		{ETriedDismissMenu=0x01,
		 ETryingToTerminateApp=0x02};
private:
	CEikonEnv& iEikEnv;
	TUid iMessageUid;
	HBufC8* iMessageParameters;
	TInt iFlags;
	TInt iCount;
	TInt iStartLevel;
	TInt iTargetCounter;
	CQikShutter** iObserver;
	TAppExitOption iExitAppOption;
	TInt iTopOrdinalPositionOfShutterTarget;
	};


/**
 * @internal
 */
class CQikShutterList : public CCoeStatic
	{
public:
	IMPORT_C static void NewLD();
	IMPORT_C static TBool AutoExitApp();
	IMPORT_C static CArrayPtrFlat<MQikShutterTarget>* List();
	~CQikShutterList();
private:
	CQikShutterList(TUid aUid, TScope = EThread);
private:
	CArrayPtrFlat<MQikShutterTarget> iList;
	};


#endif // __QIKSHUTTER_H__