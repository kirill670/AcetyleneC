/////////////////////////////////////////////////////////////////////////////
//
//	MsvSchedulePackage.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_SCHEDULE_PACKAGE_H_
#define MSV_SCHEDULE_PACKAGE_H_

/////////////////////////////////////////////////////////////////////////////
//
//	TMsvSchedulePackage Declaration
//
/////////////////////////////////////////////////////////////////////////////

const TInt KMaxParameterLength = 256;

class TTaskInfo;


class TMsvSchedulePackage
/** Packaged message scheduling information. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TMsvSchedulePackage();
	
	IMPORT_C void PackLC(TTaskInfo& aTask, HBufC*& aDes) const;
	IMPORT_C void UnpackL(const TTaskInfo& aTask, const TDesC& aDes);

private:

	HBufC* PackLC() const;
	void UnpackL(const TDesC& aDes);

	void ExternalizeL(RWriteStream&) const;
	void InternalizeL(RReadStream&);

	TPtrC Convert(const TDesC8& aDes) const;
	TPtrC8 Convert(const TDesC16& aDes) const;

public:

	/** Message ID. */
	TMsvId iId;
	/** Command ID to be passed to CMsvSession::TransferCommandL() when it is time 
	to send the messages. */
	TInt iCommandId;
	/** Intervals at which the scheduler should check the sending operation's progress. */
	TTimeIntervalMicroSeconds32 iPollProgress;
	/** Server MTM specific binary data to be passed to CMsvSession::TransferCommandL() 
	when it is time to send the messages. */
	TBuf8<KMaxParameterLength> iParameter;
	};

#endif
