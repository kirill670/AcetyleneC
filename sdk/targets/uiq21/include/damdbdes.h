// DAMDBDES.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __DADBDESC_H__
#define __DADBDESC_H__

#if !defined (__D32DBMS_H__)	//TUId
#include <d32dbms.h>
#endif
#include "damdef.h"


class TDaUserCol
	{
public:
	enum {EDialable=0x02};
	IMPORT_C TDaUserCol(const TDesC& aName,TDbColType aType,TInt aUId, 
		TInt aMaxLength=KDbUndefinedLength, TInt aMaxLinesDE=KMaxLinesDE);
	IMPORT_C TDaUserCol();
	IMPORT_C void MapToCDbColSetL(CDbColSet& aCDbColSet) const;
	IMPORT_C void ExternalizeL(RWriteStream& aSink) const;
	IMPORT_C void InternalizeL(RReadStream& aSource);
	IMPORT_C void SetDialable(TBool aDialable); 
	inline TBool IsDialable() const {return iDaAttributes&EDialable;}
public:
	TBuf<KDbMaxColName> iName;
	TDbColType iType;
	TInt iMaxLength;
	TUint iAttributes;
	TInt iUId;
	TUint iDaAttributes;
	TInt iMinKeyLength;
	TInt iMaxLinesDE;
	TInt iPrecision;
	TInt iMinValue;
	TInt iMaxValue;
	TUint iDbColNo1;
	TUint iDbColNo2;
	};

class CDaUserColSet : public CBase
	{
public:
	enum TPanics
		{
		EDaInvalidColumn
		};
	// Constructors, destructors
	IMPORT_C static CDaUserColSet* New();
	IMPORT_C static CDaUserColSet* NewL();
	IMPORT_C ~CDaUserColSet();
	IMPORT_C CDaUserColSet* CloneL() const; 
	// Getters
	inline const TDaUserCol& operator[](TDbColNo aCol) const;	 
	inline TDaUserCol& operator[](TDbColNo aCol);	 
	IMPORT_C const TDaUserCol* Col(const TDesC& aColName) const;
	IMPORT_C TDbColNo ColNo(const TDesC& aColName) const;	  
	inline TDbColNo IncColNo() {return ++iMaxColNo;}
	inline TDbColNo MaxColNo() const {return iMaxColNo;} 
	inline TInt Count() const;
	IMPORT_C TInt ColNoFromUId(TInt aUId) const;
	// Setters
	void SetDbColNo(const CDbColSet& aDbColSet);
	inline void Clear();
	IMPORT_C void Remove(const TDesC& aColName);
	IMPORT_C CDaUserColSet& AddL(const TDaUserCol& aCol);
	IMPORT_C CDbColSet* MapToCDbColSetL() const;
	inline void ResizeL(TInt aCount) {iColumns.ResizeL(aCount);}
	inline void SetReserveL(TInt aCount) {iColumns.SetReserveL(aCount);}
private:
	IMPORT_C CDaUserColSet();
	inline void SetMaxColNo(TDbColNo aColNo) {iMaxColNo=aColNo;}
private:
	TDbColNo iMaxColNo;
	CArrayFixFlat<TDaUserCol> iColumns;
	friend class CDaUserDbDesc;
	};

// Class CDaUserColSet
inline TInt CDaUserColSet::Count() const
	{return iColumns.Count();}
inline void CDaUserColSet::Clear()
	{iColumns.Reset();}
inline const TDaUserCol& CDaUserColSet::operator[](TDbColNo aCol) const
	{return iColumns[aCol-1];}		// 1-based column ids 
inline TDaUserCol& CDaUserColSet::operator[](TDbColNo aCol)
	{return iColumns[aCol-1];}		// 1-based column ids 

typedef CArrayFixFlat<TDbColName> CDaColNameArray;

class CDaModel;

class CDaUserDbDesc : public CBase
	{
// This class describes the database in a manner understandable to the Data App.
//
public:
	// Constructors, destructors
	IMPORT_C static CDaUserDbDesc* NewL(CDaModel* aModel);
	IMPORT_C static CDaUserDbDesc* NewL(const TFileName &aTableName, CDaUserColSet *aColSet,CDaModel* aModel);
	~CDaUserDbDesc();
	IMPORT_C void ExternalizeL(RWriteStream& aSink) const;
	IMPORT_C void InternalizeL(RReadStream& aSource);
	// Setters
	IMPORT_C void CopyColSetL(const CDaUserColSet& aColSet);
	inline void SetDbColNo(const CDbColSet& aColSet) {iColSet->SetDbColNo(aColSet);}
	inline void TableName(const TFileName& aTableName) {iTableName=aTableName;}
	inline void SetReserveL(TInt aCount) {iColSet->SetReserveL(aCount);}
	// Getters
	inline TInt ColumnCount() const {return iColSet->Count();}

	inline const TDaUserCol& Col(TDbColNo aColNo) const {return (*iColSet)[aColNo];}
	IMPORT_C const TDaUserCol& Col(const TDbColName& aUserColName) const;

	IMPORT_C TDbColNo ColNoFromUId(TInt aUId) const;
	IMPORT_C TDbColNo UserColNo(const TDbColName& aUserColName) const;
	IMPORT_C TDbColNo DbColNo(TDbColNo aUserColNo, const CDbColSet* aDbColSet) const;

	inline const TDbColName ColName(TDbColNo aUserColNo) const {return (Col(aUserColNo).iName);}

	IMPORT_C TDbColName DbColName(const TDbColName& aUserColName) const;
	IMPORT_C TDbColName DbColNameFromUId(TInt aUid) const;
		
	inline const TFileName& TableName() const {return iTableName;}

	inline const CDaUserColSet& ColSet() const {return *iColSet;}

	IMPORT_C TInt UId (TDbColNo aUserColNo) const ;
	IMPORT_C TInt UId (const TDesC& aColName) const;
private:
	void ConstructL(const TFileName &aTableName, CDaUserColSet *aColSet);
	CDaUserDbDesc();
private:
	CDaUserColSet *iColSet;
	CDaModel* iModel;
	TFileName iDatabaseName;
	TFileName iTableName;
	};
#endif
