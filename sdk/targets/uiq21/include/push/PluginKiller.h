// PluginKiller.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//


#ifndef __PLUGINKILLER_H__
#define __PLUGINKILLER_H__

#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

///Forward Declarations
class CPushHandlerBase;

/**
 * Utility Class Used by a Plugin to Delete itself.
 */
//##ModelId=3B659EEA0198
class CPluginKiller: public CActive 
	{
public:
	//##ModelId=3B659EEA01D6
	virtual ~CPluginKiller();

	//##ModelId=3B659DB701AC
	CPluginKiller(CPushHandlerBase* aPushPlugin);
	//##ModelId=3B659DB701AB
	IMPORT_C void KillPushPlugin();

protected:
	//From CActive
	//##ModelId=3B659EEA01CB
	virtual void DoCancel();
	//##ModelId=3B659EEA01CA
	virtual void RunL();

private:
	//##ModelId=3B659DB70199
	CPushHandlerBase*		iPushPlugin;
	//##ModelId=3B659DB70190
	TBool					iDeletePushPlugin;
	};

#endif //_PLUGINKILLER_H
