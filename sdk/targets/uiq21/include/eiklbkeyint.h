// EIKLBKEYINT.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLBKEYINT_H__)
#define __EIKLBKEYINT_H__

#include <e32std.h>
#include <coemain.h>
#include <coedef.h>
#include <eikkeyint.h>

class CEikListBox;

/**
 *
 * List box key interceptor storage object.  Allows an <code>MEikKeyInterceptor</code> to be plugged
 * into TLS by a client of CEikListBox.
 *
 * @since 6.2
 * @lib ""
 */
class CEikListBoxKeyInterceptorTls : public CCoeStatic
	{
public:
	IMPORT_C static void SetL(MEikKeyInterceptor* aListBoxKeyInterceptor);
	IMPORT_C static TKeyResponse InterceptKeyL(const TKeyEvent& aKeyEvent,TEventCode aType,CEikListBox& aListBox);
public:
	~CEikListBoxKeyInterceptorTls();
private:
	inline CEikListBoxKeyInterceptorTls();
	inline static CEikListBoxKeyInterceptorTls* Self();
private:
	MEikKeyInterceptor* iListBoxKeyInterceptor;
	};

#endif
