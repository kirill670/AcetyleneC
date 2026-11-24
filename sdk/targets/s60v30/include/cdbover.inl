/**
@file CDBOVER.INL

CCommDbOverrideSettings inline functions

Written by Ann, July 1998
Copyright (C) Symbian Ltd 2003
*/

#if !defined(__CDBOVER_INL__)
#define __CDBOVER_INL__

#include <cdbover.h>
#include <commdb.h>

inline CCommDbOverrideSettings::TParamList CCommDbOverrideSettings::PartialFull() const
/**
Returns the value set in the constructor.

@return An enumeration which determines whether this set of override values is full or partial. 
*/
	{
	return iPartialFull;
	}

#endif

