/**
@file CDBTEMP.H

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.

CommDb Template Record View
*/

#ifndef __CDBTEMP_H__
#define __CDBTEMP_H__

#include <d32dbms.h>

// @private 
class CCommsDatabaseBase;
class CCommsDbTableView;

// Template view class. Uses a supplied `CCommsDatabase` and a
// `CCommsDbTableView` to read and write template records. Created from
// `CCommsDbTableView::ConstructL()` the recursion	is stopped because the
//	template view NewL is called with aUseTemplate set to false.
//	@internal "This class is poorly named it should be something like:
//	CCommDbTemplateView"
class CCommsDbTemplateRecord : public CBase
/** The view on a template record of a specific table. 

The view contains only the template record and therefore, unlike the more 
general CCommsDbTableView class, does not contain any navigation functions.

This class does, however, contain the necessary member functions for reading 
and writing to columns.
@publishedAll
@released */
	{
public:
	/** Creates a new template view on the database and table specified. */
	IMPORT_C static CCommsDbTemplateRecord* NewL(CCommsDatabaseBase* aDb,const TDesC& aTableName);
	IMPORT_C ~CCommsDbTemplateRecord();

	/** Modifies the existing template record if there is no template create one.
		StoreModifications() is called to complete the transaction. */
	IMPORT_C TInt Modify();
	/** Removes the template from the table. */
	IMPORT_C TInt Delete();
	/** Stores an new or updated template back to the database. */
	IMPORT_C TInt StoreModifications();
	/** Cancels pending changes since `Modify()`. */
	IMPORT_C void CancelModifications();

	// Access data from the template 
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes8& aValue);
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes16& aValue);
	IMPORT_C HBufC* ReadLongTextLC(const TDesC& aColumn);
	IMPORT_C void ReadUintL(const TDesC& aColumn, TUint32& aValue);
	IMPORT_C void ReadBoolL(const TDesC& aColumn, TBool& aValue);
	IMPORT_C void ReadTypeAttribL(const TDesC& aColumn, TDbColType& aColType, TUint32& aAttrib);
	IMPORT_C void ReadColumnLengthL(const TDesC& aColumn, TInt& aLength);

	// Modify a new or modified template. Must call `StoreModifications()`
	// to store the changes. 
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC8& aValue);
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC16& aValue);
	IMPORT_C void WriteLongTextL(const TDesC& aColumn, const TDesC& aValue);
	IMPORT_C void WriteUintL(const TDesC& aColumn, const TUint32& aValue);
	IMPORT_C void WriteBoolL(const TDesC& aColumn, const TBool& aValue);

	/** The name of the table that this template belongs to. */
	IMPORT_C void GetTableName(TDes& aTableName) const;

	/** True if a template exists. */
	IMPORT_C TBool TemplateRecordExists();
	
	// Create a new record based on the contents of the template record 
	IMPORT_C TInt InsertCopy(TUint32& aId);
private:
	CCommsDbTemplateRecord();
	void ConstructL(CCommsDatabaseBase* aDb, const TDesC& aTableName);
	void RepositionL();
private:
	CCommsDbTableView* iView;
	TBool iRecordExists;
	};

#endif
