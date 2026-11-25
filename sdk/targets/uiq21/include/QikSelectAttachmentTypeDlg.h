// QikSelectAttachmentTypeDialog.h

// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.

#ifndef __QIKSELECTATTACHMENTTYPEDLG_H__
#define __QIKSELECTATTACHMENTTYPEDLG_H__

#include <eikdialg.h>

/**
* CQikSelectAttachmentTypeDlg
*
* 
*/
class CQikSelectAttachmentTypeDlg : public CEikDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(TFileName& aFileName);
	~CQikSelectAttachmentTypeDlg();
private:
	CQikSelectAttachmentTypeDlg(TFileName& aFileName);
	//CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
private:
	CDesCArrayFlat* iCategories;
	TFileName& iFileName;
	};
#endif //CQikSelectAttachmentTypeDlg