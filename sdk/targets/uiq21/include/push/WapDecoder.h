// WapDecoder.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

/** @file WapDecoder.H
 * This file contains the Utilities for Decoding WAP Binary Data
 */

// Utilities for Decoding WAP Binary Data

#ifndef __WAPDECODER_H__
#define __WAPDECODER_H__

#include <e32std.h>
#include <e32base.h>


/** 
 * WAP Binary Codex Utility.
 * This class contains Static Function to use for decoding WAP Binary data.
 */
//##ModelId=3B659EDE01E1
class TWapBinCodex
	{
public:
	
	/** 
	 * WAP Uintvar is defined a variable length Int that is used for compaction
	 * The format is defined in "WAP WSP Section 8.1.2
	 * UInt can be up to 5 (8 bit) bytes long, with the first bit indicated a carryover.
	 * This class will hold the value of the TUintvar in the 'ivalue' field
	 * and the size (number of bytes) in the iOctetSize.
	 * This is useful for decoding and indexing through WAP Binary data
	 * 
	 */
	class TUintvar 
		{
		public:
			TUintvar() : iValue(0), iOctetSize(0) {};
			TInt	iValue;
			TInt	iOctetSize;
		};

	//##ModelId=3B659EDE01F7
	IMPORT_C static void ExtractUIntvarL(const TDesC8& aSource, TInt aStartIndex, TWapBinCodex::TUintvar& rMultiByte);
	//##ModelId=3B659EDE01EB
	IMPORT_C static void ExtractMultiOctetInteger(const TDesC8& aSource, TInt& rInt);
	};


#endif
