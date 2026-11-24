/*
* ============================================================================
*  Name     : AknKeyLock.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
// AKNKEYLOCK.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Avkon KeyLock Client


#if !defined(__AKNKEYLOCK_H__)
#define __AKNKEYLOCK_H__

#include <e32base.h>

#include <aknnotifystd.h>

class RAknKeyLock : public RNotifier
	{
public:
	IMPORT_C void EnableKeyLock();
	IMPORT_C void DisableKeyLock();
	IMPORT_C TBool IsKeyLockEnabled();
	IMPORT_C void EnableSoftNotifications(TBool aEnable);
	IMPORT_C void OfferKeyLock();
	IMPORT_C void CancelAllNotifications();
	/**
	* @since 2.0
	*/
	IMPORT_C void EnableAutoLockEmulation();
	/**
	* @since 2.0
	*/
	IMPORT_C void DisableWithoutNote();
	/**
	* @since 2.1
	*/
	IMPORT_C void EnableWithoutNote();
private:
	void SendMessage(TKeyLockNotifierReason aMessage);
	};

#endif
