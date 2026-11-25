// EIKCLOCK.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCLOCK_PAN__)
#define __EIKCLOCK_PAN__

enum TEikClockPanic
	{
	EEikPanicClockTypeMustBeAllowedToChange,
	EEikPanicClockBadFormat1,
	EEikPanicClockBadFormat2,
	EEikPanicClockBadFormat3,
	EEikPanicClockBadFormat4,
	EEikPanicClockHasAlreadyBeenConstructed,
	EEikPanicClockBadChangeFormatCall,
	EEikPanicClockBadChangeUniversalTimeOffsetAndDaylightSavingZoneCall,
	EEikPanicClockNoNeedToSetFormat,
	EEikPanicClockInconsistentHorizontalTextAlignmentValues,
	EEikPanicClockInconsistentVerticalTextAlignmentValues,
	EEikPanicClockInconsistentHandTypeValues,
	EEikPanicClockBadHandFeatureType,
	EEikPanicClockClockAlreadyExists,
	EEikPanicClockNoControlContext,
	};

GLREF_C void Panic(TEikClockPanic aPanic);

#endif

