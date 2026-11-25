// EIKSRVC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSRVC_H__)
#define __EIKSRVC_H__

#include <eiksrvs.h>
#include <eiksrv.h>

const TInt KNumConnectRetries=5;

/**
 * @internal
 * Do not use
 */
class REikAppUiSession : public RSessionBase
	{
public:
	IMPORT_C REikAppUiSession();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C TVersion Version() const;
	IMPORT_C void NotifyAlarmServerOfTaskChange() const;
	IMPORT_C void LaunchTaskList() const;
	IMPORT_C void CycleTasks(CEikServAppUiBase::TTaskCycleDirection aDirection) const;
	IMPORT_C TInt SetStatusPaneFlags(TInt aFlags) const;
	IMPORT_C TInt SetStatusPaneLayout(TInt aLayoutResId) const;
	IMPORT_C TInt BlankScreen() const;
	IMPORT_C TInt UnblankScreen() const;
	IMPORT_C void ResolveError(TDes& aText,TInt aError,TUid aAppUid) const;
	IMPORT_C void Extension(TUid aExtensionUid,const TDesC8& aBuffer,TRequestStatus& aRequestStatus) const;
private:		
	void StartServerL();
#if defined(__WINS__)
private:
	RLibrary iNotUsed; // kept for the moment to preserve sizeof(REikAppUiSession)
#endif
	};

//**********************************
//global functions
//**********************************

// function to panic the server
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);


#endif

