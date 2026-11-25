// D32DBMS.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TDbCol
inline TDbCol::TDbCol(const TDesC &aName)
	: iName(aName)
	{}
inline TBool TDbCol::IsLong(TDbColType aType)
/** Tests if a column is of the Long column type, i.e. one of the EDbColLongXxxx 
types.

@param aType The column type to test.
@return ETrue if the aType is a Long column type, EFalse otherwise. */
	{return aType>=EDbColLongText8;}

// Class CDbColSet
inline TInt CDbColSet::Count() const
/** Returns the number of column definitions in the set.

Note that using a TDbColSetIter is another way to iterate through the contents 
of a CDbColSet.

@return The number of columns in the columns set. */
	{return iColumns.Count();}
inline void CDbColSet::Clear()
/** Removes all of the columns from the column set. */
	{iColumns.Reset();}
inline const TDbCol& CDbColSet::operator[](TDbColNo aCol) const
/** Returns a column definition by its ordinal number in the set.

Note that using a TDbColSetIter is another way to iterate through the contents 
of a CDbColSet.

@param aCol The ordinal number of the column in the set. Columns in a column 
set are numbered from 1 to Count(), unlike Symbian OS array classes. Ordinal 
0 is reserved to represent the invalid column number KDbNullColNo.
@return The column definition requested. */
	{return iColumns[aCol-1];}		// 1-based column ids 
// Class TDbColSetIter
inline TDbColSetIter::operator TAny* () const
	{return CONST_CAST(TDbCol*,iColumn);}
inline const TDbCol& TDbColSetIter::operator*() const
/** Dereferences the iterator on the current column definition.

@return A const reference to the current column definition. */
	{__ASSERT_DEBUG(iIndex<iArray->Count(),User::Invariant());return *iColumn;}
inline const TDbCol* TDbColSetIter::operator->() const
/** Gets a member of the currently referenced column definition. This enables the 
use of the following constructs:

if (iter->iType==EDbColText && iter->iMaxLength<50) 

@return A const pointer to the current column definition. */
	{__ASSERT_DEBUG(iIndex<iArray->Count(),User::Invariant());return iColumn;}
inline TDbColNo TDbColSetIter::Col() const
/** Returns a column ordinal in the set for the currently referenced column definition.

@return The column ordinal of the current column definition. */
	{__ASSERT_DEBUG(iIndex<iArray->Count(),User::Invariant());return iIndex+1;}
inline TDbColSetIter TDbColSetIter::operator++(TInt)
/** Moves the iterator to the next column in the set pre increment operator.

@return A reference to this iterator, after the increment operation has been 
performed. */
/** Moves the iterator to the next column in the set post increment operator.

Note that this is implemented in terms of the pre-increment operator, and 
is less efficient.

@param Unused: required for the C++ compiler to resolve the ambiguity with 
the pre-increment operator.
@return A copy of this iterator, referring to the column definition before 
the increment operation is performed. */
	{TDbColSetIter tmp(*this);++(*this);return tmp;}

// Class CDbKey
inline TInt CDbKey::Count() const
	{return iKeys.Count();}
inline const TDbKeyCol& CDbKey::operator[](TInt aCol) const
/** Returns a key column by its position in the key.

@param aCol The position of the column in the key. These are numbered from 
0 to Count()-1.
@return The key column requested. */
	{return iKeys[aCol];}
inline void CDbKey::MakeUnique()
/** Makes the key unique. This ensures that every key value in the index is distinct 
from every other. */
	{iAttributes|=EUnique;}
inline TBool CDbKey::IsUnique() const
/** Tests whether the key is unique.

@return ETrue, if the key is unique; EFalse, otherwise. */
	{return iAttributes&EUnique;}
inline TBool CDbKey::IsPrimary() const
/** Tests whether the key is the primary key.

@return ETrue, if the key is unique; EFalse, otherwise. */
	{return iAttributes&EPrimary;}
inline void CDbKey::SetComparison(TDbTextComparison aComparison)
/** Sets the way in which Text columns are compared for the key. All Text columns 
in the key are compared in the same way.

@param aComparison The comparison type to use. */
	{iComparison=aComparison;}
inline TDbTextComparison CDbKey::Comparison() const
/** Returns the method used to compare Text columns in this key.

@return The comparison type used for the key. */
	{return iComparison;}
inline void CDbKey::MakePrimary()
	{iAttributes|=EPrimary;}

// Class TDbQuery
inline TDbQuery::TDbQuery(const TDesC& aQuery,TDbTextComparison aComparison)
	: iQuery(aQuery), iComparison(aComparison)
/** Constructs a query object from an SQL string and a text comparison mode.

Note that no copy is made of the descriptor passed; it is stored by reference 
in the query object.

@param aQuery The SQL string as a descriptor.
@param aComparison The type of text comparison to use in evaluation of the 
SQL. If not supplied, normal comparison is used. */
	{}
inline const TDesC& TDbQuery::Query() const
/** Returns the SQL string in the query object.

@return A descriptor containing the SQL string. */
	{return iQuery;}
inline TDbTextComparison TDbQuery::Comparison() const
/** Returns the text comparison mode for the query object.

@return The text comparison mode. */
	{return iComparison;}

// Class RDbHandleBase
inline RDbHandleBase::RDbHandleBase()
	:iObject(0)
	{}

// Class RDbRowSet
inline void RDbRowSet::BeginningL()
/** Positions the cursor at the beginning of the rowset. */
	{GotoL(EBeginning);}
inline void RDbRowSet::EndL()
/** Positions the cursor at the end of the rowset. */
	{GotoL(EEnd);}
inline TBool RDbRowSet::FirstL()
/** Positions the cursor on the first row in the rowset. If there are no rows, 
the cursor is positioned at the end.

@return ETrue if the cursor is now at a row, EFalse if it is at the end. */
	{return GotoL(EFirst);}
inline TBool RDbRowSet::LastL()
/** Positions the cursor on the last row in the rowset. If there are no rows, the 
cursor is positioned at the beginning.

@return ETrue if the cursor is now at a row, EFalse if it is at the beginning. */
	{return GotoL(ELast);}
inline TBool RDbRowSet::NextL()
/** Moves the cursor to the next row in the rowset. If there are no more rows, 
the cursor is positioned to the end.

If the cursor is at the beginning prior to the function, it is equivalent 
to FirstL().

@return */
	{return GotoL(ENext);}
inline TBool RDbRowSet::PreviousL()
/** Moves the cursor to the previous row in the rowset. If there are no more rows, 
the cursor is positioned to the beginning.

If the cursor is at the end prior to the function, it is equivalent to LastL().

@return ETrue if the cursor is now at a row, EFalse if it is at the beginning. */
	{return GotoL(EPrevious);}
inline TBool RDbRowSet::IsColNull(TDbColNo aCol) const
/** Tests whether a column has the NULL value.

Columns which have the NULL value can still be extracted with the correct 
accessor function, in which case numerical columns will return a 0 (or equivalent) 
value, and text and binary columns will have a zero length.

@param aCol The column ordinal for the column to test.
@return ETrue if column aCol is NULL, otherwise EFalse. */
	{return ColSize(aCol)==0;}
inline TInt RDbRowSet::ColInt(TDbColNo aCol) const
/** Extracts a signed integer column value. The type should fit within a TInt.

@param aCol The column ordinal of the column to extract.
@return The value of column aCol. */
	{return ColInt32(aCol);}
inline TUint RDbRowSet::ColUint(TDbColNo aCol) const
/** Extracts an unsigned integer column value.

@param aCol The column ordinal of the column to extract.
@return The value of column aCol. */
	{return ColUint32(aCol);}
inline TReal RDbRowSet::ColReal(TDbColNo aCol) const
/** Extracts a TReal64 column value.

@param aCol The column ordinal of the column to extract.
@return The value of column aCol. */
	{return ColReal64(aCol);}
inline void RDbRowSet::SetColL(TDbColNo aCol,TInt aValue)
/** Sets a signed integer column value. The type should fit into a TInt.

@param aCol The column ordinal of the column to set.
@param aValue The new column value. */

	{SetColL(aCol,TInt32(aValue));}
inline void RDbRowSet::SetColL(TDbColNo aCol,TUint aValue)
/** Sets a signed integer column value. The type should fit into a TInt.

@param aCol The column ordinal of the column to set.
@param aValue The new column value. */

	{SetColL(aCol,TUint32(aValue));}

// Class TDbWindow
inline TDbWindow::TDbWindow()
	: iSize(ENone)
/** Constructs this object with a size of ENone. This can be used to request a 
view with no pre-evaluation window. */
	{}
inline TDbWindow::TDbWindow(TUnlimited)
	: iSize(EUnlimited)
/** Constructs this object with a size of EUnlimited. This is used to request a 
completely pre-evaluated view. The constant KDbUnlimitedWindow is an instance 
of such a TDbWindow.

@param The argument is only used to direct the compiler to construct an unlimited 
window. */
	{}
inline TInt TDbWindow::Size() const
/** Returns the number of rows stored by the view.

@return The number of rows stored by the window. This could be one of the 
special values ENone or EUnlimited. */
	{return iSize;}
inline TInt TDbWindow::PreferredPos() const
/** Returns the preferred position in the window of the current row marker. i.e. 
the position with the forward and backward slots as requested.

@return The preferred position in the window. It is undefined if this is not 
a limited window. */
	{return iPreferredPos;}

// Class TUnion
template <class T>
inline TUnion<T>::operator const T&() const
	{return *(const T*)&iRep[0];}
template <class T>
inline const T& TUnion<T>::operator()() const
	{return *(const T*)&iRep[0];}
template <class T>
inline T& TUnion<T>::operator()()
	{return *(T*)&iRep[0];}
template <class T>
inline void TUnion<T>::Set(const T& aT)
	{new(&iRep[0]) T(aT);}

// Class TDbLookupKey
inline TDbLookupKey::TDbLookupKey()
	: iCount(0)
	{}
inline TInt TDbLookupKey::Count() const
	{return iCount;}
inline const TDbLookupKey::SColumn* TDbLookupKey::First() const
	{return &iKey[0];}
// Class TDbSeekKey
inline TDbSeekKey::TDbSeekKey()
	: iMaxKeys(1)
/** Constructs an empty key value. 

Add() should be called before the key value is used for lookup. */
	{}
inline TDbSeekKey::TDbSeekKey(TInt aKey)
	: iMaxKeys(1)
/** Constructs a key value for an TInt8, TInt16 or TInt32 column.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TUint aKey)
	: iMaxKeys(1)
/** Constructs a key value for a Bit, TUint8, TUint16 or TUint32 column.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TInt64 aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TReal32 aKey)
	: iMaxKeys(1)
/** Constructs a key value for a TReal32 column.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TReal64 aKey)
	: iMaxKeys(1)
/** Construct a key value for a TReal64 column.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TTime aKey)
	: iMaxKeys(1)
/** Constructs a key value for a TDateTime column.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(const TDesC8& aKey)
	: iMaxKeys(1)
/** Constructs a key value for a non-Unicode text column.

Note that the seek key does not copy the text data contained by the descriptor. 
This needs to be retained until the seek key is no longer required.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(const TDesC16& aKey)
	: iMaxKeys(1)
/** Constructs a key value for a Unicode text column.

Note that the seek key does not copy the text data contained by the descriptor. 
This needs to be retained until the seek key is no longer required.

@param aKey The key value to lookup. */
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TInt aKeys,TInt)
	: iMaxKeys(aKeys)
	{}
// Class TDbSeekMultiKey
template <TInt S>
inline TDbSeekMultiKey<S>::TDbSeekMultiKey()
	: TDbSeekKey(S,0)
/** Constructs an empty multi-column key value. */
	{}

// Class RDbTable
inline TInt RDbTable::SetIndex(const TDesC& anIndex)
/** Sets the specified index as the active index for this table. The rows will 
be presented in index order, and this index key will be used for lookup by 
the SeekL() function.

If successful, the rowset is reset to the beginning.

@param anIndex The name of the index to activate.
@return KErrNone, if successful, otherwise one of the system-wide error codes. 
Specifically:KErrWrite if the table was created with insert-only access.KErrNotFound 
if the index does not exist on the table. This can also be one of the DBMS 
database error codes. */
	{return SetIndex(&anIndex);}
inline TInt RDbTable::SetNoIndex()
/** Sets the ordering to be the underlying ordering of the rows — this will 
usually provide faster navigation of the rowset.

@return KErrNone, if successful, otherwise one of the system-wide error codes. 
Specifically:KErrWrite if the table was created with insert-only access. This 
can also be one of the DBMS database error codes. */
	{return SetIndex(0);}

inline RDbColWriteStream::RDbColWriteStream(const MExternalizer<TStreamRef> &anExternalizer)
	: RWriteStream(anExternalizer)
/** Constructs this object by invoking the matching constructor for RWriteStream.

@param anExternalizer Specifies an externaliser */
	{}

// Class CDbNames
inline TInt CDbNames::Count() const
	{return iList.Count();}
inline const TDesC& CDbNames::operator[](TInt anIndex) const
	{return iList[anIndex];}

// Class RDbDatabase
inline TInt RDbDatabase::CreateTable(const TDesC& aName,const CDbColSet& aColSet)
	{return CreateTable(aName,aColSet,NULL);}
inline TInt RDbDatabase::CreateTable(const TDesC& aName,const CDbColSet& aColSet,const CDbKey& aPrimaryKey)
	{return CreateTable(aName,aColSet,&aPrimaryKey);}

// Class RDbIncremental
inline TInt RDbIncremental::Execute(RDbDatabase& aDatabase,const TDesC& aSql,TInt& aStep)
/** Initiates the execution of a DDL (SQL schema update) statement on the database.

This is the incremental form of RDbDatabase::Execute().

Note that to begin executing a DML (SQL data update) statement incrementally, 
use the RDbUpdate class.

@param aDatabase The database on which the DDL (SQL schema update) statement 
is to execute.
@param aSql The DDL SQL statement to be executed on the database.
@param aStep On return, contains the initial step count for the incremental 
operation. This value should be passed in to subsequent calls to Next() to 
continue the operation.
@return KErrNone if successful, otherwise another of the system-wide error 
codes.
@see RDbDatabase::Execute()
@see RDbUpdate */
	{return Execute(aDatabase,aSql,EDbCompareNormal,aStep);}
