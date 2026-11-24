//	ScheduleBaseServerMtm.H
//
//	Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved.
//


#ifndef SCHEDULE_BASE_SERVER_MTM_H_
#define SCHEDULE_BASE_SERVER_MTM_H_

/////////////////////////////////////////////////////////////////////////////
//
//	CScheduleBaseServerMtm Declaration
//
/////////////////////////////////////////////////////////////////////////////

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__

#include <mtsr.h>
#include <barsc.h>

#ifndef __MESSAGING_API_V2__
#include <saclient.h>
#endif // endif __MESSAGING_API_V2__

class CMsvScheduleSend;
class CMsvSysAgentActions;
class TMsvSendErrorAction;
class TMsvSchedulePackage;
#ifdef __MESSAGING_API_V2__
class CRepository;
#endif

class CScheduleBaseServerMtm : public CBaseServerMtm
/**
Base class for Server MTMs that support scheduling.

It contains pure virtual functions which must be implemented by the Server 
MTM. These functions are not required for interoperability with any other 
classes, however they are essential functionality that must be implemented 
by a Server MTM that support scheduling.

CScheduleBaseServerMtm uses a class derived from CMsvScheduleSend to
interface with the task scheduler.

@see CMsvScheduleSend
@publishedAll
@released
*/
	{
protected:

//	--- Construction ---

	IMPORT_C CScheduleBaseServerMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aServerEntry);

//	--- Send the Scheduled Messages ---

	IMPORT_C virtual void SendScheduledL(CMsvEntrySelection& aSelection, const TBool aMove, const TDesC8& aParameter, TRequestStatus& aStatus);
	IMPORT_C virtual void ScheduleL(CMsvEntrySelection& aSelection, const TBool aMove, const TDesC8& aParameter, TRequestStatus& aStatus);
	IMPORT_C virtual void ConstructL();
#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C virtual void RestoreScheduleSettingsL(TBool aRestoreErrorsFromResource = EFalse, TInt aErrorsResourceId = 0);
#endif
	IMPORT_C void LoadResourceFileL(const TDesC& aResFileName);

// Other Schedule Commands

	IMPORT_C virtual void CheckScheduleL(const CMsvEntrySelection& aSelection, const TDesC8& aParameter, TRequestStatus& aStatus);
	IMPORT_C virtual void DeleteScheduleL(const CMsvEntrySelection& aSelection, const TDesC8& aParameter, TRequestStatus& aStatus);

//	--- Pure virtual functions that must be implemented in a derived class ---

	/**
	Populates a TMsvSchedulePackage object with scheduling information.
	
	@param aParameter Parameter information for the package
	@param aMove Flag that signals whether a move or copy is required
	@param aPackage On return, a populated object
	*/
	virtual void PopulateSchedulePackage(const TDesC8& aParameter, const TBool aMove, TMsvSchedulePackage& aPackage) const = 0;
	
	/**
	Loads the resource file (if any) for the MTM.
	*/
	virtual void LoadResourceFileL() = 0;


	IMPORT_C void Queue(TRequestStatus& aStatus);

#ifdef __MESSAGING_API_V2__	
	IMPORT_C void LoadScheduleSettingsL(CRepository& aRepository, TBool aRestoreErrorsFromResource = EFalse, TInt aErrorsResourceId = 0);
#endif	

protected:

	IMPORT_C ~CScheduleBaseServerMtm();

private:

	void RequestComplete(TRequestStatus* aStatus, TInt aError);

protected:

//	--- Data Member ---

	/** Message scheduler. */
	CMsvScheduleSend* iScheduleSend; //Should be constructed and deleted by the derived class

	/** MTM resource file. */
	RResourceFile iResourceFile;
	/** File server handle. */
	RFs iFs;
	/** Asynchronous status word. */
	TRequestStatus* iReport;
	};

#endif
