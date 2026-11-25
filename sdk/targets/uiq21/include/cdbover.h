// CDBOVER.H
//
// Copyright (c) 1997-1999, 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CDBOVER_H__
#define __CDBOVER_H__

#include <e32base.h>
#include <commdb.h>
#include <cdbpreftable.h>

class CCommDbOverride;
class CCommDbLongDesOverride;
class TCommDbIapConnectionPrefOverride;

/** Holds all information about CommDb overrides.
	Allows the client to store, retrieve and test the existance of overrides.
*/
class CCommDbOverrideSettings : public CBase
	{
public:
	/** @deprecated 7.0 "The only use of TParamList is during the comparison of
		two override sets" */
	enum TParamList
		{
		EParamListPartial,
		EParamListFull
		};

	/** The value types that may be stored in as overrides
		@internal "Could just use TDbColType" */
	enum TValueType
		{
		EIntValue,
		EBoolValue,
		EDes8Value,
		EDes16Value,
		ELongDesValue,
		EUnknownType
		};

public:
	/** Create a new override set. The `aParamList` argument is not used except
		when comparing two sets. */
	IMPORT_C static CCommDbOverrideSettings* NewL(TParamList aParamList);
	IMPORT_C virtual ~CCommDbOverrideSettings();

	/** Add an override to the override set. */
	IMPORT_C TInt SetIntOverride(const TDesC& aTableName, const TDesC& aColumnName, TUint32 aValue);
	IMPORT_C TInt SetBoolOverride(const TDesC& aTableName, const TDesC& aColumnName, TBool aValue);
	IMPORT_C TInt SetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, const TDesC8& aValue);
	IMPORT_C TInt SetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, const TDesC16& aValue);
	IMPORT_C TInt SetLongDesOverride(const TDesC& aTableName, const TDesC& aColumnName, const TDesC& aValue);

	/** Get an override from the override set. Returns `KErrNotFound` if the
		column has not been overriden. */
	IMPORT_C TInt GetIntOverride(const TDesC& aTableName, const TDesC& aColumnName, TUint32& aValue);
	IMPORT_C TInt GetBoolOverride(const TDesC& aTableName, const TDesC& aColumnName, TBool& aValue);
	IMPORT_C TInt GetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, TDes8& aValue);
	IMPORT_C TInt GetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, TDes16& aValue);
	IMPORT_C TInt GetLongDesOverride(const TDesC& aTableName, const TDesC& aColumnName, TDes& aValue);
	IMPORT_C TInt GetLongDesOverrideLength(const TDesC& aTableName, const TDesC& aColumnName, TInt& aLength);

	/** Add a connection preferences override to the override set. */
	IMPORT_C TInt SetConnectionPreferenceOverride(const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& aPref);
	/** Get a connection preferences override filtered by the contents of
		`aPref`. Any field in `aPref` may be ignored in the filter by
		initialising with the following values:
			aPref.iRanking == 0,
			aPref.iDirection == ECommDbConnectionDirectionUnknown,
			aPref.iDialogPref == ECommDbDialogPrefUnknown,
			aPref.iBearer.iBearerSet == 0,
			aPref.iBearer.iIapId == 0 */
	IMPORT_C TInt GetConnectionPreferenceOverride(CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& aPref);

	/** True if `aOverrides` has the same overrides as this. */
	IMPORT_C TBool Compare(CCommDbOverrideSettings* aOverrides) const;
	/** True if an override has been set for `aColumnName` */ 
	IMPORT_C TBool IsOverridden(const TDesC& aTableName, const TDesC& aColumnName, TValueType aType);
	/** Retrieve the value set as `aParamList` in `NewL()` */
	inline TParamList PartialFull() const;

protected:
	CCommDbOverrideSettings(TParamList aParamList);
	virtual void ConstructL();
	TInt FindOverride(const TDesC& aTableName, const TDesC& aColumnName, TValueType aType) const;
	TBool IllegalOverride(const TDesC& aTableName,  const TDesC& aColumnName) const;
	void CheckL(const TDesC& aTableName, const TDesC& aColumnName, TValueType aType) const;
	static TBool MatchIapOverride(const TCommDbIapConnectionPrefOverride& aFirst,
								  const TCommDbIapConnectionPrefOverride& aSecond);
protected:
	TParamList iPartialFull;
	RPointerArray<CCommDbOverride> iOverrides;
	RArray<TCommDbIapConnectionPrefOverride> iIapOverrides;
	CCommsDatabase* iDb;
	};

#include <cdbover.inl>

#endif