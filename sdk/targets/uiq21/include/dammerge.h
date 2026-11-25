// DAMMERGE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include <damdbms.h>
#include <damdbdes.h>
#include <damainc.h>

#ifndef __DAMMERGE_H_

#define __DAMMERGE_H_

class TDaColMap
	{
public:
	TDaColMap(TDbColNo aTarget, TDbColNo aSource) :iTarget(aTarget), iSource(aSource) {}
	TDbColNo iTarget;
	TDbColNo iSource;
	};

typedef CArrayFixFlat<TDaColMap> CDaColMap;

class TDaColMapFactory
	{
public:
	IMPORT_C static CDaColMap* MakeColMapL(const CDaUserDbDesc& aTarget, const CDaUserDbDesc& aSource);
	IMPORT_C static CDaColMap* MakeUserColMapL(const CDaUserDbDesc& aTargetDbDesc, const CDaUserDbDesc& aSourceDbDesc);
	};

class CDaModel;

class CDaMerger : public CDaIncremental
	{
	public:
		enum
			{
			EMerged,
			ENoRecords,
			ENotCompatible
			};
	public:
		CDaMerger(CDaModel& aTarget, CDaModel& aSource) :iTarget(aTarget), iSource(aSource) {}
		IMPORT_C static CDaMerger* NewLC(CDaModel& aTarget, CDaModel& aSource);
		IMPORT_C ~CDaMerger();

		IMPORT_C TInt InitializeL();
	
	// From MDaIncremental:
		IMPORT_C TInt Next(TInt& aRemainingSteps);
		IMPORT_C void Open();
		IMPORT_C void CloseL();
		IMPORT_C void HandleLeave(TInt aError);
		IMPORT_C void HandleCancel();

	private:
		CDaColMap* CreateColMapL();
		TInt DoStepL();
	private:
		CDaModel& iTarget;
		CDaModel& iSource;
		RDbView* iTargetView;
		RDbView* iSourceView;
		CDaColMap *iColumnMap;
	};

#endif