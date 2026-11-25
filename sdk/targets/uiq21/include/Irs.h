//	IrS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__IRS_H__)
#define __IRS_H__


#if !defined(__MTSR_H__)
#include "mtsr.h"
#endif







class CIrSrvMtm : public CBaseServerMtm
	{
public:
	enum TIrMtmOperations
		{
		EIrMtmUiNullOp,
		EIrMtmUiIrSend
		};

public:
	IMPORT_C static CIrSrvMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry*  aEntry);
	~CIrSrvMtm();

	void CopyToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void CopyFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void DeleteL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void DeleteAllL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void CreateL(TMsvEntry aNewEntry, TRequestStatus& aStatus);
	void ChangeL(TMsvEntry aNewEntry, TRequestStatus& aStatus);
	//
	void StartCommandL(CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter, TRequestStatus& aStatus);
	//
	TBool CommandExpected();
	//
	const TDesC8& Progress();
	//
	void SetInitialEntry(CMsvServerEntry* aEntry);

protected:
	void DoCancel();
	void DoRunL();
	void DoComplete(TInt aError);

private:
	CIrSrvMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aEntry);
	void ConstructL();

private:

	CMsvServerEntry*	iEntry;	
	TRequestStatus*		iReport;

	TPckgBuf<TIrMtmOperations>  iSendProgress;
	};

#endif  // __IRS_H__