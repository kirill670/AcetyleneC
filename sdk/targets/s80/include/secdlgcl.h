// SECDLGCL.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

/**
 * @file secdlgcl.h 
 * Security Dialog Server Client Header
 *
 * @internalComponent
 */

#ifndef __SECDLGCL_H__
#define __SECDLGCL_H__

#include <e32std.h>

/** SSL security alerts. 
* 
* @since v6.0 */
enum TSecurityAlertEnum 
	{ 
	/** General alert. */
	EGeneralAlert, 
	/** Unsupported algorithm. */
	EUnsupportedAlg, 
	/** Unsupported version. */
	EUnsupportedVersion 
	};

class CX509Certificate;
class RSecurityDialogServer : public RSessionBase
/** Security dialog server. 
* 
* @since v6.0 */
	{
public:
	IMPORT_C RSecurityDialogServer();
	IMPORT_C ~RSecurityDialogServer();
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt Connect();
	//pg 16/02/2000 Port to new certman api
	IMPORT_C void DisplayCertNotTrustedDlg(TBool& aBool,const CX509Certificate& aCert,TRequestStatus& aStatus);
//	IMPORT_C void DisplayCertNotTrustedDlg(TBool& aBool,TCertInfo& aCert,TRequestStatus& aStatus);
	// Used to post SSL alerts/warnings
	IMPORT_C void DisplayAlertDialog(TSecurityAlertEnum aAlert,TRequestStatus& aStatus);
	IMPORT_C TInt Cancel();
private:
//// @todo	RNotifier* iNotifier;
	TPtr8 iProceed;
	};

/** Attempts to find the comm server thread and, if found, starts a thread for the 
* SSL dialog.
* 
* @return	KErrNone if successful; otherwise, a system-wide error code. */
IMPORT_C TInt StartDialogThread();

#endif // __SECDLGCL_H__

