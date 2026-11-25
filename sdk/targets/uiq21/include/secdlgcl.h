// SECDLGCL.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// Security Dialog Server Client

#ifndef __SECDLGCL_H__
#define __SECDLGCL_H__

#ifndef __EIKENV_H__
#include <eikenv.h>
#endif

#ifndef __EIKDIALG_H__
#include <eikdialg.h>
#endif

#ifndef __SECDLG_H__
#include "secdlg.h"
#endif


class CX509Certificate;
class RSecurityDialogServer : public RSessionBase
	{
public:
	IMPORT_C RSecurityDialogServer();
	IMPORT_C ~RSecurityDialogServer();
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt Connect();
	IMPORT_C void DisplayCertNotTrustedDlg(TBool& aBool,const CX509Certificate& aCert,TRequestStatus& aStatus);
	IMPORT_C void DisplayAlertDialog(TSecurityAlertEnum aAlert,TRequestStatus& aStatus);
	IMPORT_C TInt Cancel();
private:
// must be the same size as a TPtr8
// this could be avoided if RSecurityDialogServer derived from or contained an RNotifier
	RNotifier* iNotifier;
	TPtr8* iProceed;
	TPckgBuf<TSecurityDlgData> *iTempData;
	};

IMPORT_C TInt StartDialogThread();

#endif
