// DevSoundStandardCustomInterfaces.h 
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __DEVSOUNDSTANDARDCUSTOMINTERFACES_H__
#define __DEVSOUNDSTANDARDCUSTOMINTERFACES_H__

#include <e32std.h>

/**
UID associated with the custom interface MMMFDevSoundCustomInterfaceBitRate.
@publishedAll
*/
const TUid KUidCustomInterfaceDevSoundBitRate = {0x101F7DD5};

/**
Custom interface class to allow DevSound and hwdevices to support setting and getting
audio bit rates.
@publishedAll
@released
*/
class MMMFDevSoundCustomInterfaceBitRate
	{
	/**
	Retrieves the bit rates that are supported by DevSound in its current configuration.
	@param	"aSupportedBitRates"	"The supported bit rates, in bits per second, shall be appended
									to this array.  Note that the array shall be reset by this method."
	@leave  "This method may leave with one of the system-wide error codes."
	*/
	void GetSupportedBitRatesL(RArray<TInt>& aSupportedBitRates) = 0;

	/**
	Returns the current bit rate.
	@return "The current bit rate, in bits per second."
	@leave  "This method may leave with one of the system-wide error codes."
	*/
	TInt BitRateL() = 0;

	/**
	Sets the bit rate to a new value.
	@param	"aBitRate"	"The new bit rate, in bits per second."
	@leave  "This method may leave with one of the system-wide error codes."
	*/
	void SetBitRateL(TInt aBitRate) = 0;
	};


#endif