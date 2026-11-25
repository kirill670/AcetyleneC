// MTURUTILS.H
//
// Copyright (C) Symbian Ltd 2000
//

#ifndef __MTURUTILS_H__
#define __MTURUTILS_H__

#include <msvstd.h>

class MturUtils
/**
@publishedAll
@released
*/
{
public:
	IMPORT_C static void LaunchEditorL(TMsvId aId);
	IMPORT_C static void LaunchEditorAndWaitL(TMsvId aId);
};

#endif
