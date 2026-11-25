// DAMFIND.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Header file for the find, filter and sort classes
//
#ifndef __DAFIND_H__
#define __DAFIND_H__

class TDaSort
	{
// This class defines the parameters required for sorting on a field:
public:
	IMPORT_C TDaSort(TInt aUId, TDbKeyCol::TOrder=TDbKeyCol::EAsc);
public:
	TInt iUId;
	TDbKeyCol::TOrder iOrder;
	};

class TDaFilter
	{
// This class defines the parameters required for filtering on a field
public:
	IMPORT_C TDaFilter();
	IMPORT_C TDaFilter(TInt aUId);
public:
	TInt iUId;
	};

typedef CArrayFixFlat<TDaSort> CDaSortArray;
typedef CArrayFixFlat<TDaFilter> CDaFilterArray;

class CDaModel;
class CDaUserDbDesc;
class TDaUserCol;

class CDaSqlParams : public CBase
	{
public:
	static CDaSqlParams *NewL(CDaModel& aModel);
	~CDaSqlParams();
	void ExternalizeL(RWriteStream& aStream);
	void InternalizeL(RReadStream& aStream);
// Setters
	IMPORT_C void CopyFilterArrayL(const CDaFilterArray& aFilterArray);
	IMPORT_C void CopySortArrayL(const CDaSortArray& aSortArray);
	inline void ResetSortArray() {iSortArray->Reset();}
	IMPORT_C void FindString(const TDesC& aFindString);
	inline void SortEnabled(TBool aSortEnabled){iSortEnabled=aSortEnabled;}
	IMPORT_C TInt SetAllFiltersL();
	void SynchronizeL();
// Getters
	inline const TFindString & FindString() const {return iFindString;}
	inline const CDaSortArray& SortArray() const {return *iSortArray;}
	inline const CDaFilterArray& FilterArray() const {return *iFilterArray;}
	inline TBool SortEnabled() const {return iSortEnabled;}
	void BuildSqlStatementL(CBufFlat* aSqlStatement);
	IMPORT_C CDaSortArray* CloneSortArrayL() const;
	IMPORT_C CDaFilterArray* CloneFilterArrayL() const;
private:
	void Prolog(CBufFlat* sqlStatement, TInt aUId, TBool& aIsFirstColumn) const;
	CDaSqlParams(CDaModel& aModel);
	void ConstructL();
private:
	TFindString iFindString;
	TFindString iAdjustedFindString;
	CDaSortArray *iSortArray;
	TBool iSortEnabled;
	CDaFilterArray *iFilterArray;
	CDaModel& iModel;
	};


#endif
