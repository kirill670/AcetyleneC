// SHGCOORD.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGCOORD_H__)
#define __SHGCOORD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__BACELL_H__)
#include <bacell.h>
#endif

#if !defined(__SHGAPI_H__)
#include <shgapi.h>
#endif

#if !defined(__SHGPANIC_H__)
#include "shgpanic.h"
#endif

class CShgFormulaViewer;

class TShgCellRef
/** A cell reference, specifying a cell's row and column, in either absolute or 
relative terms. 
@publishedAll
@released
*/
	{
public:
	/** Constant definition. */
	enum 
		{
		/** Character to use in string references to indicate an absolute reference. */
		EAbsoluteIndicator='$'
		};
private:
	enum {EExternalizedSize=6};
	friend class CShgFormulaViewer;
public:
	inline TShgCellRef();
	inline TShgCellRef(TInt aRow,TInt aCol,TInt aWorkSheetNo);
	inline TShgCellRef(const TShgCellRef& aCell);
	TBool operator==(const TShgCellRef& aCell) const;

	inline void SetRow(TInt aRow);
	inline TInt Row() const;
	inline void SetCol(TInt aCol);
	inline TInt Col() const;
	inline void SetRowCol(TInt aRow,TInt aCol);
	inline void SetWorkSheetNo(TInt aWorkSheetNo);
	inline TInt WorkSheetNo() const;

	inline TCellRef AsCellRef() const;
	TCellRef AsCellRef(const TCellRef& aCell) const;
	void MakeAbsolute(const TCellRef& aCell);
	TInt MakeAbsoluteReturningError(const TCellRef& aCell);
	inline TBool IsAbs() const;
	inline TBool IsRowAbs() const;
	inline TBool IsColAbs() const;
	inline void SetRowRel();
	inline void SetRowAbs();
	inline void SetColRel();
	inline void SetColAbs();
	inline void SetWorkSheetExplicit();
	inline void SetWorkSheetNotExplicit();
	inline TBool IsWorkSheetExplicit() const;

	void AppendTextValue(TDes& aCellRefBuf,const TCellRef& aCell) const;
	IMPORT_C void Externalize(CBufBase* aBuf) const; // previously was exported for test code
	IMPORT_C void Externalize(TDes8& aDes) const;
	IMPORT_C TInt Internalize(const TUint8* aPtr);
	static void StoreL(CBufBase* aBuf,const TDesC8& aDes);
	static void StoreL(CBufBase* aBuf,const TDesC16& aDes);
	static const TPtrC8 LexDes8(const TUint8*& aPtr);
	static const TPtrC LexDes(const TUint8*& aPtr);
	static const TUint8* LexPastDes(const TUint8* aPtr);
private:
	enum {EAbsFlag=0x4000,ESignBit=0x8000};
	enum {EWorkSheetExplicit=0x80000000};
	enum {EWorkSheetExplicitExternalize=0x80};
private:
	TInt iRow;
	TInt iCol;
private:
	TUint iWorkSheetNo;
	};

class TShgRangeRef
/** A cell range reference, specifying a continuous range of cells. 
@publishedAll
@released
*/
	{
public:
	/** Constant definition. */
	enum 
		{
		/** Character to use as a separator in range strings. */
		ERangeSeparator=':'
		};
	/** Constant definition. */
	enum 
		{
		/** Character to use as a worksheet separator in range strings. */
		EWorkSheetSeparator='!'
		};
	/** Constant definition. */
	enum 
		{
		/** Character to use to mark the start and end of a worksheet 
		specification in range strings. */
		EWorkSheetNameStartAndEndIndicator='\''
		};
private:
	enum {EExternalizedSize=12};
	friend class CShgFormulaViewer;
public:
	inline TShgRangeRef();
	inline TShgRangeRef(const TShgCellRef& aFrom,const TShgCellRef& aTo);
	inline TShgRangeRef(const TShgRangeRef& aRangeRef);
	TBool IsAbs() const;
	void MakeAbsolute(const TCellRef& aCell);
	TInt MakeAbsoluteReturningError(const TCellRef& aCell);
	TBool Contains(const TCellRef& aCell) const;
	TRangeRef AsRangeRef() const;
	TRangeRef AsRangeRef(const TCellRef& aCell) const;
	void AppendTextValue(TDes& aRangeRefBuf,const TCellRef& aCell) const;
	TInt NoRows() const;
	TInt NoCols() const;
	void Externalize(CBufBase* aBuf) const;
	void Externalize(TDes8& aLex) const;
	TInt Internalize(const TUint8* aPtr);
public:
	/** Start of the range. */
	TShgCellRef iFrom;
	/** End of the range. */
	TShgCellRef iTo;
	};

inline TShgCellRef::TShgCellRef()
/** Default constructor. */
	{}
inline TShgCellRef::TShgCellRef(TInt aRow,TInt aCol,TInt aWorkSheetNo)
/** Constructor, specifying absolute cell position.

@param aRow Cell row
@param aCol Cell column
@param aWorkSheetNo Cell worksheet */
	: iRow(aRow),iCol(aCol),iWorkSheetNo(aWorkSheetNo) {if (iRow<0) iRow = ((-iRow)|ESignBit); if (iCol<0) iCol = ((-iCol)|ESignBit);}
inline TShgCellRef::TShgCellRef(const TShgCellRef& aCell)
/** Constructor, copying another cell reference.

@param aCell Cell reference to copy */
	: iRow(aCell.iRow),iCol(aCell.iCol),iWorkSheetNo(aCell.iWorkSheetNo) {}
inline void TShgCellRef::SetRow(TInt aRow)
/** Sets the cell row.

@param aRow Cell row */
	{if (aRow<0) aRow = ((-aRow)|ESignBit); __ASSERT_DEBUG((aRow&~ESignBit)>=0 && (aRow&~ESignBit)<ESheetMaxRows && !(aRow&EAbsFlag),Panic(EShgPanicBug)); iRow = (iRow&EAbsFlag)|aRow;}
inline TInt TShgCellRef::Row() const
/** Gets the cell row.

@return Cell row */
	{TInt row = iRow&~EAbsFlag; __ASSERT_DEBUG((row&~ESignBit)>=0 && (row&~ESignBit)<ESheetMaxRows,Panic(EShgPanicBug)); if (row&ESignBit) row = -(row&~ESignBit); return row;}
inline void TShgCellRef::SetCol(TInt aCol)
/** Sets the cell column.

@param aCol Cell column */
	{if (aCol<0) aCol = ((-aCol)|ESignBit); __ASSERT_DEBUG((aCol&~ESignBit)>=0 && (aCol&~ESignBit)<ESheetMaxColumns && !(aCol&EAbsFlag),Panic(EShgPanicBug)); iCol = (iCol&EAbsFlag)|aCol;}
inline TInt TShgCellRef::Col() const
/** Gets the cell column.

@return Cell column */
	{TInt col = iCol&~EAbsFlag; __ASSERT_DEBUG((col&~ESignBit)>=0 && (col&~ESignBit)<ESheetMaxColumns,Panic(EShgPanicBug)); if (col&ESignBit) col = -(col&~ESignBit); return col;}
inline void TShgCellRef::SetRowCol(TInt aRow,TInt aCol)
/** Sets the cell row and column.

@param aRow Cell row
@param aCol Cell column */
	{SetRow(aRow); SetCol(aCol);}
inline void TShgCellRef::SetRowRel()
/** Sets the row setting to be relative. */
	{iRow &= ~EAbsFlag;}
inline void TShgCellRef::SetColRel()
/** Sets the column setting to be relative. */
	{iCol &= ~EAbsFlag;}
inline void TShgCellRef::SetRowAbs()
/** Sets the row setting to be absolute. */
	{iRow |= EAbsFlag;}
inline void TShgCellRef::SetColAbs()
/** Sets the column setting to be absolute. */
	{iCol |= EAbsFlag;}
inline TBool TShgCellRef::IsAbs() const
/** Tests if the reference is absolute.

@return True if the reference is absolute */
	{return IsRowAbs() && IsColAbs();}
inline TBool TShgCellRef::IsRowAbs() const
/** Tests if the row setting is absolute.

@return True if the row setting is absolute */
	{return iRow&EAbsFlag;}
inline TBool TShgCellRef::IsColAbs() const
/** Tests if the column setting is absolute.

@return True if the column setting is absolute */
	{return iCol&EAbsFlag;}
inline TCellRef TShgCellRef::AsCellRef() const
/** Gets the cell reference converted to a Grid API cell reference.

@return Grid API cell reference */
	{return TCellRef(Row(),Col());}
inline void TShgCellRef::SetWorkSheetNo(TInt aWorkSheetNo)
/** Sets the cell worksheet.

@param aWorkSheetNo Cell worksheet */
	{iWorkSheetNo = (iWorkSheetNo&EWorkSheetExplicit)|aWorkSheetNo;}
inline TInt TShgCellRef::WorkSheetNo() const
/** Gets the cell worksheet.

@return Cell worksheet */
	{return iWorkSheetNo&~EWorkSheetExplicit;}
inline void TShgCellRef::SetWorkSheetExplicit()
/** Sets a flag indicating that a worksheet has been set for the cell. */
	{iWorkSheetNo |= EWorkSheetExplicit;}
inline void TShgCellRef::SetWorkSheetNotExplicit()
/** Sets a flag indicating that a worksheet has not been set for the cell. */
	{iWorkSheetNo &= ~EWorkSheetExplicit;}
inline TBool TShgCellRef::IsWorkSheetExplicit() const
/** Tests if a worksheet has been set for the cell.

@return True if a worksheet has been set for the cell */
	{return iWorkSheetNo&EWorkSheetExplicit;}
inline TShgRangeRef::TShgRangeRef()
/** Default constructor. */
	{}
inline TShgRangeRef::TShgRangeRef(const TShgCellRef& aFrom,const TShgCellRef& aTo)
	: iFrom(aFrom),iTo(aTo) 	
/** Constructor specifying two cell references.

@param aFrom Cell reference specifying the start of the range
@param aTo Cell reference specifying the end of the range */
	{}
inline TShgRangeRef::TShgRangeRef(const TShgRangeRef& aRangeRef)
	: iFrom(aRangeRef.iFrom),iTo(aRangeRef.iTo) 
/** Copy constructor. */
	{}
#endif
