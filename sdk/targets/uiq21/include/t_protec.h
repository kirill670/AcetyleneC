// T_PROTEC.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

// Test Protection of settings in CommDB (Cameron specific)

#include <e32test.h>
#include <c32comm.h>
#include <commdb.h>
#include <protectdb.h>
#include <protectcpdb.h>
#include <cdbpreftable.h>


#define KTestNothing           0
#define KTestNormalTable       1
#define KTestConnectPrefTable  2
#define KTestBothTableTypes    (KTestNormalTable | KTestConnectPrefTable)

class CTestProtectionOfSettings : public CBase
	{
	public:
		static CTestProtectionOfSettings* NewLC();
		~CTestProtectionOfSettings();
	
	public:
		void ProtectTableL(const TDesC& aTableName);
		void ProtectConnectionPrefTableL();

		void UnprotectTableL(const TDesC& aTableName);
		void UnprotectConnectionPrefTableL();

		void ProtectRecordsL(const TDesC& aTableName);
		void ProtectConnectionPrefRecordsL();

		void UnprotectRecordsL(const TDesC& aTableName);
		void UnprotectConnectionPrefRecordsL();

		void TestProtectTableL(const TDesC& aTableName);
		void TestProtectConnectionPrefTableL();

		void TestUnprotectTableL(const TDesC& aTableName);
		void TestUnprotectConnectionPrefTableL();

		void TestProtectRecordsL(const TDesC& aTableName);
		void TestProtectConnectionPrefRecordsL();

		void TestUnprotectRecordsL(const TDesC& aTableName);
		void TestUnprotectConnectionPrefRecordsL();

		void TestAddModDeleteConnectionPrefRecordsL();

		void TestDBFailureL();

		static void TestTransactionProtectL(TAny* /* TDesC* */aOpaqueTableName);

enum TProtectTestResult{
	EProtectTestFailed,
	EProtectTestPassed,
	EProtectTestNotPerformed
	};
	
	private:
		CTestProtectionOfSettings();
		void ConstructL();
		TInt ChangeCPRankingL(CCommsDbProtectConnectPrefTableView* aTable, TUint32& Ranking);


	private:
		void    CheckTableIsProtected(CCommsDbProtectTableView* aTable);
		void    CheckTableIsNotProtected(CCommsDbProtectTableView* aTable);
		void    GoToPosition(CCommsDbProtectTableView* aTable,TInt aPos);


		void    ProtectRecordL  (CCommsDbProtectTableView* aTable,TInt aResult);
		void    UnprotectRecordL(CCommsDbProtectTableView* aTable,TInt aResult);
		void    UpdateRecordL   (CCommsDbProtectTableView* aTable,TInt aResult);
		void    DeleteRecordL   (CCommsDbProtectTableView* aTable,TInt aResult);
		void    InsertRecordL   (CCommsDbProtectTableView* aTable,TInt aResult);
		void    ModifyRecordL   (CCommsDbProtectTableView* aTable);
		void    PopulateInsertedRecordL(CCommsDbProtectTableView* aTable);

		void    CheckTableIsProtected(CCommsDbProtectConnectPrefTableView* aTable);
		void    CheckTableIsNotProtected(CCommsDbProtectConnectPrefTableView* aTable);
		void    GoToPosition(CCommsDbProtectConnectPrefTableView* aTable,TInt aPos);

        void    ProtectRecordL(CCommsDbProtectConnectPrefTableView* aTable, TInt aResult);
		void    UnprotectRecordL(CCommsDbProtectConnectPrefTableView* aTable,TInt aResult);
		void    UpdateRecordL   (CCommsDbProtectConnectPrefTableView* aTable,TInt aResult);
		void    DeleteRecordL   (CCommsDbProtectConnectPrefTableView* aTable,TInt aResult);
		void    InsertRecordL   (CCommsDbProtectConnectPrefTableView* aTable,TInt aResult);
		void    ModifyRecordL   (CCommsDbProtectConnectPrefTableView* aTable);
		void    PopulateInsertedRecordL(CCommsDbProtectConnectPrefTableView* aTable);

		void    CheckRecordAccessL(CCommsDbProtectConnectPrefTableView* aTable, TInt aExpectedAccess);

        void    OutputResult(TRefByValue<const TDesC> aName, TProtectTestResult aResult);

	private:
		CCommsDatabase*	iDb;
		TInt			iTableType;
	};