// CDBPREFTABLE.H
//
// Copyright (c) 2000, 2001 Symbian Ltd.  All rights reserved.
//

// Comms Database Connection Preference Table header

#ifndef __CDBPREFTABLE_H__
#define	__CDBPREFTABLE_H__

#include <d32dbms.h>
#include <cdbcols.h>
#include <cdblen.h>

/** @private */
class CCommsDatabase;
class TCommDbCommonBearerInfo;

/** @public
	Implements actions on records of the Connection Preferences table. Uses a
	CCommsDatabase and has an RDbView for access to the	database. Created via
	`CCommsDatabase::OpenConnectionPrefTable*LC()` or `NewLC()`.
*/

class 	CCommDbTableExtension; 
class CCommsDbConnectionPrefTableView : public CBase
	{
public:
	/** Used in calls to `UpdateBearerL()` and as a public member of
		`TCommDbIapConnectionPref`. */
	class TCommDbIapBearer
		{
	public:
		IMPORT_C TCommDbIapBearer();
	public:
		TUint32 iBearerSet;
		TUint32 iIapId;
		};

	/** A complete connection preference - containing rank, direction, dialogue
		option, bearers for the dialogue and the prefered IAP. */
	class TCommDbIapConnectionPref
		{
	public:
		IMPORT_C TCommDbIapConnectionPref();
		IMPORT_C TBool operator==(const TCommDbIapConnectionPref& aPref) const;
	public:
		TUint32 iRanking;
		TCommDbConnectionDirection iDirection;
		TCommDbDialogPref iDialogPref;
		TCommDbIapBearer iBearer;
		};

public:
	/** From CBase */
	IMPORT_C virtual ~CCommsDbConnectionPrefTableView();

	/** Create a view. Usually, however, views are created by calling one of
		the `CCommsDatabase::OpenConnectionPrefTable*LC()` functions. */
	static CCommsDbConnectionPrefTableView* NewLC(CCommsDatabase& aDb, const TDbQuery& aQuery);

	/** Insert a new connection preference into the connetion preference table.
		The supplied `aPref` is checked to ensure that the rank and direction
		do not conflict with existing records. The dialog option, bearer set
		and IAP are checked for consistancy. */
	IMPORT_C void InsertConnectionPreferenceL(const TCommDbIapConnectionPref& aPref, TBool aReadOnly = EFalse);

	/** Read the currently selected connection preference. */
	IMPORT_C void ReadConnectionPreferenceL(TCommDbIapConnectionPref& aPref);

	/** Update the bearer set and iap for the currently selected connection
		preference. The dialog option, bearer set and IAP are checked for
		consistancy. */
	IMPORT_C void UpdateBearerL(const TCommDbIapBearer& aUpdate, TBool aReadOnly = EFalse);

	/** Update the dialogue option for the currently selected connection
		preference. */
	IMPORT_C void UpdateDialogPrefL(const TCommDbDialogPref& aUpdate);

	/** Update the rank for the currently selected connection preference. An
		existing connection preference with a rank of `aNewRank` will have its
		rank set to zero. */
	IMPORT_C void ChangeConnectionPreferenceRankL(TUint32 aNewRank);

	/** Delete the currently selected connection preference. */
	IMPORT_C void DeleteConnectionPreferenceL();

	/** Swap the bearer set and IAP of the two connection preferences selected
		by rank. Note that the dialogue option is not altered. */
	IMPORT_C void SwapConnectionPreferencesL(TCommDbConnectionDirection aDirection, TUint32 aFirstRank, TUint32 aSecondRank);

	/** Select the first connection preference record in this view */
	IMPORT_C TInt GotoFirstRecord();
	/** Select the next connection preference record in this view */
	IMPORT_C TInt GotoNextRecord();
	/** Select the previous connection preference record in this view */
	IMPORT_C TInt GotoPreviousRecord();

	/** @protected */
protected:
	CCommsDbConnectionPrefTableView(CCommsDatabase& aDb);
	void ConstructL(const TDbQuery& aQuery);
	void Close();
	void  OpenL(const TDbQuery& aQuery);
	RDbRowSet::TAccess GetL();
	inline TDbColNo ColNum(const TDesC& aColumn) const;
	void GetUint32L(const TDesC& aColumnName, TUint32& aValue);

	/** @private */
private:
	void RefreshL(TBool aMustBeWriteable);
	void SetRankL(TUint32 aNewRank, TBool aNotify = ETrue);
	void FindConnectionFromDirectionAndRankL(TCommDbConnectionDirection aDirection, TUint32 aRank, TDbBookmark& aBookmark);
	void DoReadBearerInfoL(TCommDbCommonBearerInfo& aInfo);
	void DoWriteBearerInfoL(const TCommDbCommonBearerInfo& aInfo);
	void DoSwapConnectionPreferencesL(TCommDbConnectionDirection aDirection, TUint32 aFirstRank, TUint32 aSecondRank);
	void CheckRankDoesNotExistL(TUint32 aRank, TCommDbConnectionDirection aDirection);
	void GetUint32OrNull(const TDesC& aColumnName, TUint32& aValue, TBool& aExists);
	void ValidateIapL(TUint32 aIapId, TCommDbConnectionDirection aDirection, TUint32 aBearerSet, TCommDbDialogPref aDlgPref);
	void ValidateBearerAndDirectionL(const TDesC& aServiceType, TCommDbConnectionDirection aDirection, TUint32 aBearerSet, TCommDbDialogPref aDlgPref);
	void ValidateRankL(TUint32 aRank);
	void DoGotoRecordL(RDbView::TPosition aPos);

protected:
	/** DBMS view */
	RDbView iTableView;
//	CCommDbConnectPrefTableExtension* iThis;
	CCommDbTableExtension* iThis;

private:
	/** Comms data base that is being viewed */
	CCommsDatabase& iDb;
	};

#endif

