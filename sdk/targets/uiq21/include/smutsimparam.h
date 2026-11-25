//////////////////////////////////////////////////////////////////////////
//
//	SmutSimParam.h
//
//	Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#include <msvapi.h>

#include "smcmmain.h"	// panics

typedef TPckgBuf<TInt> TIntBuf;
const TUid KUidMsvSimSmsParams = {0x100081BC};

class CMobilePhoneSmspList;
class TSmsProgress;

class CSmsSimParamOperation : public CMsvOperation
	{
public:

	static CSmsSimParamOperation* ReadSimParamsL(TUid aMtm, TMsvId aService, CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);
	static CSmsSimParamOperation* WriteSimParamsL(const CMobilePhoneSmspList& aList, TUid aMtm, TMsvId aService, CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);

	~CSmsSimParamOperation();

	inline const CMobilePhoneSmspList& SmspList() const;

	IMPORT_C CMobilePhoneSmspList* ServiceCentersLC() const;

	IMPORT_C const TDesC8& ProgressL();

	IMPORT_C static void RestoreSimParamsL(CMsvStore& aStore, CMobilePhoneSmspList& aList);
	IMPORT_C static void StoreSimParamsL(CMsvStore& aStore, const CMobilePhoneSmspList& aList);

private:

	CSmsSimParamOperation(TUid aMtm, TMsvId aService, CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);

	void RunL();
	void DoCancel();

	TInt RunError(TInt aError);

	void DoReadSimParamsL();
	void DoRunReadSimParamsL(/*TSmsProgress aProgress*/);
	void DoWriteSimParamsL(const CMobilePhoneSmspList& aList);

	void TransferCommandL(TInt aCommandId);
	void Complete();

private:

	/// Enum defining the state.
	enum TReadSimParamsState
		{
		EStateWaiting,				///< Specifies waiting state
		EStateReadingSimParams,		///< Specifies reading state
		EStateWritingSimParams		///< Specifies writing state
		} iState;

	CMobilePhoneSmspList* iSimParams;	///< A list containing the SMS parameters
	TInt iError;
	TIntBuf iProgressBuf;
	CMsvOperation* iOperation;
	};

const CMobilePhoneSmspList& CSmsSimParamOperation::SmspList() const
	{
/**
	Returns the SMS parameter list read from the SIM 
	
	@since			7.0
	@exception		ESmscPanicUnexpectedCommand
	@return			CMobilePhoneSmspList	SMS parameters read from the SIM 
 */
	__ASSERT_DEBUG(iState == EStateReadingSimParams, Panic(ESmscPanicUnexpectedCommand));
	return *iSimParams;
	}