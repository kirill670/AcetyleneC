// THTTPFilterRegistration.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file THTTPFilterRegistration.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __THTTPFILTERREGISTRATION_H__
#define __THTTPFILTERREGISTRATION_H__ 

// System includes
#include <e32std.h>
#include <stringpool.h>
#include <http/thttpevent.h>

// Forward declarations
class MHTTPFilter;

/** 
	@public
	@class			THTTPFilterRegistration
	@since			7.0
	A registration of a filter in the filter queue
 */

//##ModelId=3C4C187D0188
class THTTPFilterRegistration
	{
 public:
	/// Default constructor
	//##ModelId=3C4C187D020B
	THTTPFilterRegistration();
	/// Constructor
	//##ModelId=3C4C187D0214
	THTTPFilterRegistration(MHTTPFilter& aFilter, THTTPEvent aEvent,
						RStringTokenF aHeader, TInt aStatusCode, 
						TInt aPosition, RStringTokenF aName, TInt aHandle);
	/// Equality operator
	//##ModelId=3C4C187D0201
	TBool operator==(THTTPFilterRegistration& aThat);
	/// Inequality operator
	//##ModelId=3C4C187D01F9
	TBool operator!=(THTTPFilterRegistration& aThat);

 public:
	/// The position
	//##ModelId=3C4C187D01F6
	TInt				iPosition; // This MUST be first!
	/// The filter
	//##ModelId=3C4C187D01E4
	MHTTPFilter*		iFilter;
	/// The event it's interested in (or any)
	//##ModelId=3C4C187D01D8
	THTTPEvent			iEvent;
	/// The header it's interested in (or any)
	//##ModelId=3C4C187D01C6
	RStringTokenF	iHeader;
	/// The status it's interested in (or any)
	//##ModelId=3C4C187D01BC
	TInt				iStatus;
	/// The name of the filter
	//##ModelId=3C4C187D01B2
	RStringTokenF    iName;
	/// The handle of the filter
	//##ModelId=3C4C187D01A8
	TInt                iHandle;
	};

inline THTTPFilterRegistration::THTTPFilterRegistration()
		: iEvent(THTTPEvent::EAll)
	{
	}

inline THTTPFilterRegistration::THTTPFilterRegistration(MHTTPFilter& aFilter, 
														THTTPEvent aEvent,
														RStringTokenF aHeader,
														TInt aStatusCode, 
														TInt aPosition,
														RStringTokenF aName,
														TInt aHandle)
		:iPosition(aPosition), iFilter(&aFilter), iEvent(aEvent),
	iHeader(aHeader), iStatus(aStatusCode) , iName(aName), iHandle(aHandle)
	{
	}



#endif // __THTTPFILTERREGISTRATION_H__
