// SAFILTC.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.


#ifndef __SAFILTC_H__
#define __SAFILTC_H__


enum TSyncAidFilterHow
	{
	ESyncAidFilterAppts			= 0x1, 
	ESyncAidFilterAnnivs		= 0x2,
	ESyncAidFilterEvents		= 0x4,
	ESyncAidFilterTodo			= 0x8,
	ESyncAidFilterDeleted		= 0x10, // note that deleted and dereferenced searches are assumed to be
	ESyncAidFilterDereferenced	= 0x20  // mutually exclusive i.e. you can't filter for both at once
	};

#endif
