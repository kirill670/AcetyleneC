// PSDPROG.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// PSD Connection progress enums

#ifndef __PSDPROG_H__
#define __PSDPROG_H__


enum TPsdProgress
	{
	EStartingConfiguration = 50,
	EFinishedConfiguration,
	EStartingActivation,
	EFinishedActivation,
	EAnsweringIncoming,
	ESuspended,
	EStartingDeactivation,
	EFinishedDeactivation
	};

#endif

