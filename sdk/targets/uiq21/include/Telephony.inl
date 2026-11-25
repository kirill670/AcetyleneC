// Telephony.inl
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

// Inline code, logically part of Etel3rdParty.h

// inline-functions are not embedded in Telephony.DLL.
// So, they don't get EXPORTed, and they don't
// have any associated ordinal at link-time.

/** @file Telephony.inl */

inline TVersion CTelephony::Version() const
/**
 * Get current CTelephony version
 *
 * This function returns major, minor, and build version-numbers.
 *
 * @return	TVersion object, see E32STD.H
 */
	{
	return(TVersion(KTelephonyMajorVersionNumber,
					KTelephonyMinorVersionNumber,
					KTelephonyBuildVersionNumber));
	}
