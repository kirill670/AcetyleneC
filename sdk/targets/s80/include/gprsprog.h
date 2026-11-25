/**
@file GPRSPROG.H

Copyright (c) 2003 Symbian Ltd.  All rights reserved.

GPRS Connection progress enums
*/



#ifndef __GPRSCONNECTPROG_H__
#define __GPRSCONNECTPROG_H__

#include <e32def.h>

/**
New software should use the PSD progress values defined in psdprog.h

@publishedAll
@deprecated 7.0s - maintained for compatibility with 6.1
*/
enum TGprsProgress
	{
	EStartingConfiguration = 50, 	///< Starting Configuration
	EFinishedConfiguration,			///< Finished Configuration
	EStartingActivation,			///< Starting Activation
	EFinishedActivation,			///< Finished Activation
	EAnsweringIncoming,				///< Answering Incoming
	ESuspended,						///< Suspended
	EStartingDeactivation,			///< Starting Deactivation
	EFinishedDeactivation			///< Finished Deactivation
	};

#endif

