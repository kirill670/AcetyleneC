// W32CLICK.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

// Definition of class that needs to be provided by a Key Click plugin
//

#ifndef __W32CLICK_H__
#define __W32CLICK_H__

#ifndef __E32STD_H__
#include <e32std.h>
#endif
#ifndef __E32BASE_H__
#include <e32base.h>
#endif
#ifndef __W32STD_H__
#include <w32std.h>
#endif

/**
 * A pointer to a TClickMakerData object is passed to CClickMaker's OtherEvent function for
 * EEventScreenDeviceChanged events.
 */
struct TClickMakerData
	{
	TInt screenDeviceMode;
	};

class CClickMaker: public CBase
	{
public:
	virtual void KeyEvent(TEventCode aType,const TKeyEvent& aEvent)=0;
	virtual void PointerEvent(const TPointerEvent& aEvent)=0;
	virtual void OtherEvent(TInt aType,TAny* aParam=NULL)=0;
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs)=0;
	};

#endif
