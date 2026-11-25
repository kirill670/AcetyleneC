// DAMDELET.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __DAMDELET_H__
#define __DAMDELET_H__

#include <d32dbms.h>

class CDaUndoStack : public CBase
	{
//
// Note we operate totally in the dbms view of the database.
// We can safely ignore the user view.
//
	public:
		CDaUndoStack(TInt aGranularity, TInt aMaxSavedRecords);
		IMPORT_C void DeleteL(RDbView& aView, const CDbColSet& aColSet);
		IMPORT_C void UndoL(RDbView& aView, const CDbColSet& aColSet);
		inline TInt Count() const {return iColDataArray.Count();}
		inline void Reset() {iColDataArray.Reset();}
	private:
		enum {EMaxSavedRecords=3};
		void SaveDeleteDataL(RDbView& aView, const CDbColSet& aColSet);
		void DoUndoL(RDbView& aView);
	private:
		CArrayVarSeg<TAny> iColDataArray;
		TInt iMaxSavedRecords;
		TInt iViewColCount;
		TInt iArrayItemsCount;
	};

#endif