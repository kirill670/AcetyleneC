 /*
* ==============================================================================
*  Name        : nsmlsynchronizer.h
*  Part of     : Nokia SyncML / Synchronizer
*  Interface   : RNSmlSynchronizer
*  Description : Synchronizer client base class.
*  Version     : $Revision: 17 $ $Modtime: 4.02.04 12:01 $
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __NSMLSYNCHRONIZER_H__
#define __NSMLSYNCHRONIZER_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>
#include "nsmlsynchronizerconstants.h"

// ------------------------------------------------------------------------------------------------
// Constants
// ------------------------------------------------------------------------------------------------

const TInt KNSmlDefaultProfileId = -1;
const TInt KNSmlDefaultIAPId = -1;

// ------------------------------------------------------------------------------------------------
// class RNSmlSynchronizer
// ------------------------------------------------------------------------------------------------
class RNSmlSynchronizer : public RSessionBase
	{
public:
	enum TResult
		{
		EErrNone,
		EErrAppNotFound,
		EErrAppLaunchFailed,
		EErrAppBusy,
		EErrProfileNotFound,
		EErrUndefined,
		EErrNotConsumed
		};

	IMPORT_C RNSmlSynchronizer();
	IMPORT_C virtual ~RNSmlSynchronizer();
	
	virtual TResult ConnectL() = 0; // pure virtual
	IMPORT_C void Close();

	IMPORT_C void SynchronizeL( TInt aProfileId, TRequestStatus& aStatus );
	IMPORT_C void SynchronizeL( TInt aProfileId, TRequestStatus& aStatus, TNSmlProfileMediumType aMediumType, TInt aIAPid = KNSmlDefaultIAPId );
	IMPORT_C TResult SynchronizeL( TInt aProfileId, const TDesC8& aPackage0 );
	IMPORT_C TResult CancelSynchronize();

protected:
	IMPORT_C TResult DoConnectL( const TDesC& aServerName, const TUid& aAppUid );

	enum TState
		{
		ENotConnected,
		EConnecting,
		EConnected
		};

private:
	void WaitForReadySignal();
	TInt LaunchAppL( const TUid& aAppUid );
	void CloseApp() const;
	TResult MapError( TInt aSystemError ) const;

private:
	TBool iAppWasLaunched;
	TBool iCloseAppAllowed;
	TThreadId iId;
	TState iState;
	RSemaphore iSignal;
	};

#endif // __NSMLSYNCHRONIZER_H__
