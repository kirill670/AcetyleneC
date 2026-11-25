// DAMDBMS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Header file for the dbms / data application
//

#if !defined(__DADBMS_H__)
#define __DADBMS_H__

#if !defined(__BARSREAD_H__)
#include <barsread.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__S32FILE_H__)
#include <s32file.h>
#endif
#if !defined(__DADEF_H__)
#include "damdef.h"
#endif
#if !defined(__DADBDESC_H__)
#include "damdbdes.h"
#endif
#if !defined(__DAFIND_H__)
#include "damfind.h"
#endif
#if !defined (__MOBSERV_H__)
#include "damobsrv.h"

#if !defined (__DAMDELET_H__)
#include "damdelet.h"
#endif

#endif

#include <e32test.h>

class CDaSqlEvaluator;
class CDaUndoStack;

class CDaModel : public CBase
	{
// This class implements an interface to the dbms.
// 
public:
	enum TState {ETriedBeyondLast, ETriedBeforeFirst, EAtRow, ENotAtRow};
public:
	// Constructors, destructors
	IMPORT_C static CDaModel* NewL();
	IMPORT_C static CDaModel* CDaModel::NewL(CFileStore& fileStore);
	~CDaModel();
	void Attach(MDaObserver *aObserver){iObserver=aObserver;}
	// Databse opening, closing
	IMPORT_C void CloseDatabase();
	IMPORT_C void NewDatabaseL(CStreamStore& aStore);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& source);
	IMPORT_C void OpenDatabaseL(CStreamStore& aStore);
	IMPORT_C void OpenDatabaseL(RDbStoreDatabase& aDatabase, CStreamStore& aStore);
	IMPORT_C void CloseView();
	// Navigation
	IMPORT_C void FirstL();
	IMPORT_C void LastL();
	IMPORT_C void NextL();
	IMPORT_C void PreviousL();
	IMPORT_C void MoveToRowL(TInt aRow);
	// Getters
	inline TBool IsValid() const {return (HasRDbView() && View().AtRow());}
	inline const TPtrC& DefaultIndexName() const {return iDefaultIndexName;}
	inline TInt AtRow() {return (View().AtRow());}
	inline TBool HasRDbView() const {return iHasRDbView;}
	inline TBool ViewHasRows() const {return (iViewHasRows);}
	inline TBool HasOpenDatabase() const {return iDatabaseOpen;}
	inline TInt DbRecordCount() const {return iDbRecordCount;}
	inline TInt RowSetCount() const {return iRowSetCount;}
	inline CDbColSet *ColSet() const {return ipColSet;} 
	inline CDaUserDbDesc* UserDbDesc() const {return iDaUserDbDesc;}
	inline TInt CurrentRow() const {return iCurrentRow;}
	inline RDbDatabase & Database() {return iDatabase;}
	inline TStreamId DbStreamId() const {return iDbStreamId;}
	inline TState RowPosState() const {return iRowPosState;}
	inline CDaSqlParams * SqlParams() const {return iSqlParams;}
	inline CDbColSet* TableDef() const {return iTableDbColSet;}
	inline MDaObserver* RecordStatsWin() {return iRecordStatsWin;}
	inline RDbView& View() {return iRDbView1;}
	inline const RDbView& View() const {return iRDbView1;}
	inline MDaObserver* Observer() const {return iObserver;}
	inline const CDaUndoStack& UndoStack() const {return *iUndoStack;}
	inline const CDesCArray* YesNoArray() const {return iYesNoArray;}
	// Setters
	inline void SetDbColNo() {iDaUserDbDesc->SetDbColNo(*ipColSet);}
	inline void SetCurrentRow(TInt aCurrentRow) {iCurrentRow=aCurrentRow;}
	inline void RowPosState(TState aState) {iRowPosState=aState;}
	inline void SetDbRecordCountL(){iDbRecordCount=View().CountL();}
	inline void SetRowSetCountL() {iRowSetCount=View().CountL();}
	inline void SetRecordStatsWin(MDaObserver* anObserver) {iRecordStatsWin=anObserver;}
	inline void SetYesNoArray(const CDesCArray& aYesNoArray) {iYesNoArray = &aYesNoArray;}
	// DDL methods
	IMPORT_C TInt AlterTable(CDaUserColSet* aNewUserColSet);
	IMPORT_C void CreateDatabaseL( CDaUserColSet* aUserColSet);
	IMPORT_C void CreateDatabaseL(CStreamStore* aStore, CDaUserColSet* aUserColSet);
	IMPORT_C TInt CreateIndex(const TDesC& anIndexName, CDbKey* aCDbKey);
	IMPORT_C TInt HowManySteps(RDbIncremental& anAlterTable,CDaUserColSet* aNewUserColSet);
	// DML
	IMPORT_C void BuildViewL(const TDesC& aFindString);
	IMPORT_C void BuildViewL();
	IMPORT_C void BuildViewSyncL();
	IMPORT_C void BuildViewSyncL(const TDesC& aFindString);
	IMPORT_C void HandleFirstFindL();
	IMPORT_C void DeleteRowL();
	IMPORT_C void UndoDeleteRowL();
	inline void GetL() {View().GetL();}
	IMPORT_C void PutL();
	IMPORT_C void UpdateAllViewsL(MDaObserver::TNotification = MDaObserver::EDefaultNotification); //!! Only one view is active at any one time
	IMPORT_C void GoToBookmarkL(const TDbBookmark& aBookmark);
	// Utilities
	IMPORT_C static void Panic(TInt aReason);
private:
	void EvaluateL();
	CDaModel();
	void ConstructL();
	void DoBuildViewSyncL(const TDesC& aSqlStatement);
	void DoBuildViewL(const TDesC& aSqlStatement);
	void SetDbColNo(const CDbColSet& aDbColSet);
private:
	TState iRowPosState;
	CDaUserDbDesc *iDaUserDbDesc;
	TInt iCurrentRow;
	RDbStoreDatabase iDatabase;
	RDbView iRDbView1;
	CDbColSet *ipColSet;
	TBool iHasRDbView;
	TBool iDatabaseOpen;
	TBool iViewHasRows;
	MDaObserver *iObserver;
	CDaSqlParams *iSqlParams;
	TStreamId iDbStreamId;
	TUint iDbRecordCount;
	TUint iRowSetCount;
	MDaObserver* iRecordStatsWin;
	CDbColSet* iTableDbColSet;
	CDaSqlEvaluator* iSqlEvaluator;
	CDaUndoStack* iUndoStack;
	CBufFlat* iSqlStatement;
	TPtrC iDefaultIndexName;
	TPtrC iDefaultTableName;
	const CDesCArray* iYesNoArray;
public:
	MDaObserver *iDebugWin;
	};

#endif