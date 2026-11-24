/**
@file CDBSTORE.INL

CStoreableOverrideSettings class inline functions

Written by Ann, August 1998
Copyright (C) 2003 Symbian Ltd
*/

#ifndef __CDBSTORE_INL__
#define __CDBSTORE_INL__

#include <cdbstore.h>

inline CBufStore* CStoreableOverrideSettings::GetStore() const
/** 
Accesses the buffer store.
@deprecated 7.0 There is no need for this store - none of the above functions use this
store. If a client needs a store it should create its own.
@return The pointer to the memory store object.
*/
	{
	return iStore;
	}

#endif

