/*
* ==============================================================================
*  Name        : eiksrvc.h
*  Part of     : UIKON
*  Interface   : Application server API
*  Description : Session for the application server.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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

#ifndef EIKSRVC_H
#define EIKSRVC_H

// INCLUDES
#include <eiksrvs.h>
#include <eiksrv.h>

// CONSTANTS
const TInt KNumConnectRetries=5;

// TYPES
/** 
@internalComponent
*/
typedef TThreadFunction* (*EikSrvEntrypoint)();

class REikAppUiSession : public RSessionBase
/**
@publishedPartner 
@released
*/
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C REikAppUiSession();

		/**
		 * Connect to the server attempting to start it if required
		 *
		 * @internal
		 */
		IMPORT_C TInt Connect();

		/**
		 * Close server session.
		 */
		IMPORT_C void Close();

		/**
		* Get the version of the REikAppUiSession.
		* @return The version.
		* <BR><B>Type of return value:</B> TVersion
		*/
		IMPORT_C TVersion Version() const;

		/**
		* Wakes the alarm server up to let it know a key has been pressed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void NotifyAlarmServerOfTaskChange() const;

		/**
		* Not supported.
		*/
		IMPORT_C void LaunchTaskList() const;

		/**
		* Cycles through all current tasks, i.e. sets the next task to be the foreground task.
		* @param aDirection Either CEikServAppUiBase::EForwards or CEikServAppUiBase::EBackwards to cycle forwards or backwards through the tasks.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void CycleTasks(CEikServAppUiBase::TTaskCycleDirection aDirection) const;

		/**
		* Not implemented.
		*/
		IMPORT_C CEikonEnv* GetCoeEnv() const;

		/**
		* Sets the flags of the status pane.
		* @param aFlags A bitwise OR of visual flags. See KEikStatusPaneBaseFadedBit KEikStatusPaneBaseVisibleBit and KEikStatusPaneBaseDimmedBit.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C TInt SetStatusPaneFlags(TInt aFlags) const;

		/**
		* Sets the layout of the status pane.
		* @param aLayoutResId Resources to define the new status pane layout.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C TInt SetStatusPaneLayout(TInt aLayoutResId) const;

		/**
		* Creates a blank screen window to cover the screen.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C TInt BlankScreen() const;

		/**
		* Deletes the blank screen window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C TInt UnblankScreen() const;

		/**
		* Get the text for an error message.
		* @param aText On return, contains the error message.
		* @param aError The error code ID.
		* @param aAppUid The application which caused the error.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ResolveError(TDes& aText,TInt aError,TUid aAppUid) const;

		/**
		* Not supported.
		*/
		IMPORT_C void Extension(TUid aExtensionUid,const TDesC8& aBuffer,TRequestStatus& aRequestStatus) const;
		IMPORT_C TInt UpdateStatusPaneLayout(TInt aCurrentResId, TInt wgId);
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

/**
function to panic the server
@internalComponent
*/
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);

#endif	// EIKSRVC_H

// End of File
