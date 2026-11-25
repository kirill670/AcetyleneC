/**
@file CSDPROG.H
@internalComponent

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.

*/

#ifndef __CSDPROG_H__
#define __CSDPROG_H__

#include <nifvar.h>

/**
Stages in establishing a circuit switched data connection
*/
enum TCsdProgress
	{
	ECsdStartingDialling			= KCsdStartingDialling,
	ECsdFinishedDialling			= KCsdFinishedDialling,
	ECsdScanningScript				= KCsdScanningScript,
	ECsdScannedScript				= KCsdScannedScript,
	ECsdGettingLoginInfo			= KCsdGettingLoginInfo,
	ECsdGotLoginInfo				= KCsdGotLoginInfo,
	ECsdStartingConnect				= KCsdStartingConnect,
	ECsdFinishedConnect				= KCsdFinishedConnect,
	ECsdStartingLogIn				= KCsdStartingLogIn,
	ECsdFinishedLogIn				= KCsdFinishedLogIn,
	ECsdStartingAnswer				= KCsdStartingAnswer,
	ECsdAnswered					= KCsdAnswered,
	ECsdConnectionOpen              = KCsdConnectionOpen,
	ECsdStartingHangUp				= KCsdStartingHangUp,
	ECsdFinishedHangUp              = KCsdFinishedHangUp
	};

#endif
