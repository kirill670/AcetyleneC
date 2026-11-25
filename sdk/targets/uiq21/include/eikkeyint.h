// EIKKEYINT.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKKEYINT_H__)
#define __EIKKEYINT_H__

#include <e32std.h>
#include <coemain.h>
#include <coedef.h>

class CCoeControl;

/**
 * Key interceptor interface for controls.
 * Controls wishing to allow key event interception should allow for a pluggable key interceptor.  Then clients
 * wishing to intercept the key events should override the necessary functions in this interface and plug it into
 * the particular framework as appropriate.
 *
 * @since 6.2
 * @lib ""
 */
class MEikKeyInterceptor
	{
public:
	virtual TKeyResponse InterceptKeyL(const TKeyEvent& aKeyEvent,TEventCode aType,CCoeControl& aControl)=0;
	IMPORT_C virtual void Release();
private:
	IMPORT_C virtual void Reserved_1();
	};

#endif
