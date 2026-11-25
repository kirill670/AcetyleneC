// QikZoomDlg.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0

#ifndef __QIKZOOMDLG_H__
#define __QIKZOOMDLG_H__

#include <eikdialg.h>

/**
 * Dialog that lets the user change zoom level.
 * 
 * @since Quartz 6.0
 */
class CQikZoomDialog : public CEikDialog
	{
public:	
	IMPORT_C static TBool RunDlgLD( TInt aOriginalZoomLevel );
protected:  	
	CQikZoomDialog( TInt aOriginalZoomLevel );
	~CQikZoomDialog();
protected:  //From CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	TInt iOriginalZoomLevel;
	};

#endif // __QIKZOOMDLG_H__
