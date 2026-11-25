// MMSCHARCONV.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved. 
//

/** @file MMSCHARCONV.H
 * This file contains a wrapper class around the CHARCONV
 */

#ifndef __MMSCHARCONV_H__
#define __MMSCHARCONV_H__

#include <e32base.h>
#include <charconv.h>
#include <utf.h>

_LIT8(KMiutUndisplayableChar, "?");

/**
 * Wrapper class around the CHARCONV character set conversion utility.
 */
class CMmsCharconv : public CBase
	{
public:	
	/**
	 * NewL		Construct a parameter name/value pair.
	 *
	 */
	static CMmsCharconv* NewL(RFs& anFs);
	~CMmsCharconv();

	/**
	 * PrepareConverterL
	 * @param aUid	MIBE representation of character set.
	 * @return EFalse if aUid==0 or if the charset converter for aUid is not present.
	 *		   ETrue otherwisw
	 */
	TBool PrepareConverterL(const TUint aUid);


	/**
	 * ConvertToUnicodeL Converts input buffer from UNICODE to chosen character set.
	 * @param  aBufIn	 Input buffer to be converted.
	 * @param  rBufOut	 Output, converted, buffer.
	 * @precon			 The charset converted from is set by calling PrepareConverter.
	 * @return If there  is a problem with the input returns KErrCorrupt, else KErrNone.
	 */
	TInt ConvertToUnicodeL( const TDesC8& aBufIn, TDes& rBufOut);

	
	/**
	 * ConvertFromUnicodeL Converts input buffer from particular character set to UNICODE.
	 * @param  aBufIn	 Input UNICODE buffer to be converted.
	 * @param  rBufOut	 Output, converted, buffer.
	 * @precon			 The charset converted TO is set by calling PrepareConverter.
	 * @return If there  is a problem with the input returns KErrCorrupt, else KErrNone.
	 */
	TInt ConvertFromUnicodeL(const TDesC& aBufIn, TDes8& rBufOut);

private:
	void ConstructL();

	/**
	 * CMmsCharconv		Constructor
	 * @param  anFs		Files Session
	 */
	CMmsCharconv(RFs& anFs);

private:
	CCnvCharacterSetConverter* iConverter; ///< Pointer to charconv converter object.
	RFs& iFs;							   ///< File Session, not owned.
	};

#endif // __MMSCHARCONV_H__
