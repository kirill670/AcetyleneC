// RHTTPRequest.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file RHTTPRequest.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __RHTTPREQUEST_H__
#define __RHTTPREQUEST_H__ 

// System includes
#include <uri8.h>
#include <stringpool.h>
#include <http/rhttpmessage.h>


//##ModelId=3C4C186E0191
class RHTTPRequest : public RHTTPMessage
/** 
An HTTP Request.  This class extends the abstract HTTP Message to add an HTTP
method to be invoked on the resource at the remote HTTP server, and the URL that
identifies that resource.
@publishedAll
@released
*/
	{
 public:
	/** @name Get Methods
		Methods for reading information from the response.
	*/
	//@{
	/// Gets the method name
	//##ModelId=3C4C186E01B3
	IMPORT_C RStringF Method() const;
	/// Gets the URI
	//##ModelId=3C4C186E01B2
	IMPORT_C const TUriC8& URI() const;
	//@}
	/** @name Set Methods
		
		Methods for setting information. These methods will not be of
		use to the client; they are intended for the use of advanced
		filters
	*/
	//@{
	/// Sets the method name
	//##ModelId=3C4C186E01B0
	IMPORT_C void  SetMethod(RStringF aMethod);
	/// Sets the URI
	//##ModelId=3C4C186E01A6
	IMPORT_C void SetURIL(const TUriC8& aURI);
	//@}

	friend class CRequest;
	};


#endif //	__RHTTPREQUEST_H__  
