/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduledEntry.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_SCHEDULED_ENTRY_H_
#define MSV_SCHEDULED_ENTRY_H_

/////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
/////////////////////////////////////////////////////////////////////////////

#include "MsvSendErrorAction.h"
#include "MsvEntryScheduleData.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvScheduledEntry Declaration
//
/////////////////////////////////////////////////////////////////////////////

class CMsvScheduledEntry : public CBase
/** Abstract base class which stores the schedule data and recipients of a message. 

CMsvScheduledEntry does not force the Server MTM to store the message recipients 
in a certain way. However, it is recommended that the Server MTM derive its 
recipients class from CMsvRecipient, because the class already has support 
for the number of retries to send a message to a recipient. 

CMsvScheduledEntry stores the TMsvEntry to which it relates to provide quick 
access to the scheduling-related index data without needing calls to CMsvServerEntry::SetEntry(). 
However, CMsvScheduledEntry does not provide access to all the members of 
the TMsvEntry. This is to stop the user of the CMsvScheduledEntry from accessing 
the descriptor members of the TMsvEntry while the server entry is not set 
to the TMsvEntry. 
@publishedAll
@released
*/
	{
public:
	//Returns ETrue if can send to any of the recipients of iEntry
	//Otherwise returns EFalse
	//Called by CMsvScheduleSend::CanSchedule
	/** Tests if any of the recipients of this message can still be sent to.
	
	@param aErrorActions Error-actions
	@param aAction Default error-action
	@return True if at least one of the recipients has not been sent the message */
	virtual TBool CanSendToAnyRecipients(const CMsvSendErrorActions& aErrorActions, TMsvSendErrorAction& aAction) = 0;
	/** Tests if any of the recipients of this message can still be sent to.
	
	@param aAction Default error-action
	@return True if at least one of the recipients has not been sent the message */
	virtual TBool CanSendToAnyRecipients(const TMsvSendErrorAction& aAction) = 0;
	/** Sets all the recipients' retries to zero. */
	virtual void RecipientsResetRetries() = 0;
	/** Increases all the recipients' retries by one. */
	virtual void RecipientsIncreaseRetries() = 0;
	/** Sets all the recipients' flags to sending failed. */
	virtual void RecipientsSetFailed() = 0;
	/** Tests if all recipients of the message have been sent successfully. 
	
	@return True if all recipients have been sent successfully */
	virtual TBool RecipientsAllSent() const = 0;

	IMPORT_C virtual void StoreL(CMsvStore& aStore) const;
	IMPORT_C virtual void RestoreL(CMsvStore& aStore);

	/** Stores the recipients.
	
	@param aStore Store to write to */
	virtual void RecipientsStoreL(CMsvStore& aStore) const = 0;
	/** Restores the recipients.
	
	@param aStore Store to read from */
	virtual void RecipientsRestoreL(CMsvStore& aStore) = 0;

	inline const TTime& ScheduleDate() const;
	inline void SetScheduleDate(const TTime& aDate);

	inline const TBool Scheduled() const;
	inline void SetScheduled(const TBool aScheduled);

	inline const TInt SendingState() const;
	inline void SetSendingState(TInt aState);

	inline const TInt Error() const;
	inline const TMsvId Id() const;
	inline const TBool OffPeak() const;

	inline void SetFailed(const TBool aFail);
	inline const TBool Failed() const;

	inline const TUid Mtm() const;

//	inline TInt SendingState() const;
//	inline void SetSendingState(TInt aState);

	IMPORT_C void Entry(TMsvEntry& aEntry) const;

protected:

//	--- Construction ---

	IMPORT_C CMsvScheduledEntry(const TMsvEntry& aEntry);

public:

//	--- Public Members ---

	/** Message schedule data. */
	TMsvEntryScheduleData iData;

private:

//	--- Private Members ---

	TMsvEntry iEntry;
	};

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvScheduledEntries Declaration
//
/////////////////////////////////////////////////////////////////////////////

/** Dynamic array of CMsvScheduledEntry objects. 
@publishedAll
@released
*/
typedef CArrayPtrFlat<CMsvScheduledEntry> CMsvScheduledEntries;

#include "MsvScheduledEntry.inl"

#endif
