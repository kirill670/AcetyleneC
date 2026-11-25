// EIKBTGPS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBTGPS_H__)
#define __EIKBTGPS_H__

#include <coemain.h>
#include <eikbtgpc.h>

/**
 *
 * A list of all button groups currently available within a thread.
 *
 * Only button groups that are expected to be available to other controls
 * will register here.
 *
 * @since 1.2
 * @lib "eikcoctl.lib"
 */
class CEikButtonGroupStack : public CCoeStatic
	{
public:
	IMPORT_C static TSize MinimumSize();
public:
	static CEikButtonGroupContainer* Current();
	static void AddL(CEikButtonGroupContainer& aGroup);
	static void Remove(CEikButtonGroupContainer& aGroup);
private:
	inline CEikButtonGroupStack();
	inline static CEikButtonGroupStack* Self();
private:
	TDblQue<CEikButtonGroupContainer> iBtStack;
	};

#endif
