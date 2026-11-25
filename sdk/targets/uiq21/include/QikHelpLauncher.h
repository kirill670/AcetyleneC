// QIKHELPLAUNCHER.H
//
// Copyright (c) 1997-2001 Symbian Ltd. All rights reserved.
// Created for Quartz 6.0

#ifndef __QIKHELPLAUNCHER_H__
#define __QIKHELPLAUNCHER_H__

#include <apparc.h>		// class MApaEmbeddedDocObserver
#include <coehelp.h>	// class TCoeHelpConText

class CCoeAppUi;
class CEikDocument;

/** 
 * Use this class to launch the Help viewer. To launch the Help viewer
 * from a dialog, just set the dialog's HelpContext.
 *
 * @since Quartz 6.0
 */
class CQikHelpLauncher : public CBase, public MApaEmbeddedDocObserver
	{
public:
	IMPORT_C static void LaunchLD(const CCoeAppUi* aAppUi);
	IMPORT_C static void LaunchLD(const TCoeHelpContext& aHelpContext);
private: // from MApaEmbeddedDocObserver
	void NotifyExit(TExitMode aMode); 
private:
	CQikHelpLauncher();
	~CQikHelpLauncher();
	void LaunchEmbeddedHelpL(const TCoeHelpContext& aHelpContext);
	static TInt DeleteEmbeddedDoc(TAny *aThis);
	static void LaunchHelpViewlessL(const TCoeHelpContext& aHelpContext);
private:
	CEikDocument* iEmbeddedDoc;
	CAsyncCallBack iAsyncDeleteDoc;
	};

/**
 * @internal
 */
class TQHelpPckg
	{
public:
	TCoeHelpContext iContext;
	TInt iStartMode;
	};

typedef TPckgBuf<TQHelpPckg> TQHelpPckgBuf;

#endif	// __QIKHELPLAUNCHER_H__