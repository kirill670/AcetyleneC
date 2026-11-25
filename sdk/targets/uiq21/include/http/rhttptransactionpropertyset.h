// RHTTPTransactionPropertySet.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file RHTTPTransactionPropertySet.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __RHTTPTRANSACTIONPROPERTYSET_H__
#define __RHTTPTRANSACTIONPROPERTYSET_H__ 

// System includes
#include <http/rhttppropertyset.h>

/** 
	@public
	@class			RHTTPTransactionPropertySet
	@since			7.0
	The set of properties of a transaction. This is used by filters to
    store per-transaction information, and is also used by the client
    to specify transaction properties (such as no caching, reload and
    so on) 
 */

//##ModelId=3B1E670402C2
class RHTTPTransactionPropertySet : public RHTTPPropertySet
	{
	};

#endif //	__RHTTPTRANSACTIONPROPERTYSET_H__ 
