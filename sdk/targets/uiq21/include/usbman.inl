/** @file usbman/Inc/UsbMan.inl
 *
 * RUsb Client side header
 * Implements the Symbian OS USB Management API RUsb
 *
 * Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
 */


#ifndef __USBMAN_INL__
#define __USBMAN_INL__

#include <usbman.h>

//
// TSignal inline functions
//

inline UsbMan::TSignal::TSignal(TRequestStatus& aStatus)
	:iStatus(&aStatus),iId(RThread().Id())
	{
	aStatus=KRequestPending;
	}

inline TPtrC UsbMan::TSignal::Command() const
	{
	return TPtrC((const TText*)this,sizeof(*this)/sizeof(TText));
	}

inline TInt UsbMan::TSignal::Set(const TDesC& aCommand)
	{
	if (aCommand.Size()!=sizeof(*this))
		return KErrGeneral;
	
	return (Mem::Copy(this,aCommand.Ptr(),sizeof(*this)),KErrNone);
	}

#endif
