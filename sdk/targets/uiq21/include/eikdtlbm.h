// EIKDTLBM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDTLBM_H__)
#define __EIKDTLBM_H__

#include <f32file.h>
#include <eikhlbm.h>


class CDirectoryTreeListBoxModel : public CHierarchicalListBoxModel
	{
public:
	enum TContent
		{
		EShowSystem	=0x01,
		EShowHidden	=0x02
		};
public:
	IMPORT_C CDirectoryTreeListBoxModel(RFs& aFsSession,TInt aFlags);
	IMPORT_C ~CDirectoryTreeListBoxModel();
	IMPORT_C void CreateListForSpecifiedDriveL(TDriveNumber* aDrive);
	IMPORT_C void ExpandItemL(TInt aNodeToBeExpanded);
	IMPORT_C TFileName FullPath(TInt aIndex) const;
	IMPORT_C void UpdateL();
	IMPORT_C void SetContent(TInt aContentFlags);
private: // from MListBoxModel
	IMPORT_C TAny* Reserved_1();
private:
	void CreateDriveListL();
	TInt PathExists(const TDesC& aPath) const;
private:
	RFs& iFsSession;
	TInt iFlags;
	};

#endif
