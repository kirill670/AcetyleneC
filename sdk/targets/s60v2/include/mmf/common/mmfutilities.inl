// include\mmf\common\mmfutilities.inl
//
// Copyright (c) Symbian Software Ltd 2004.  All rights reserved.
//

/**
Unpacks the FourCC code in little-endian format into the space provided by the argument.

The argument must be a pointer to a buffer of 4 bytes or greater.

@param aDes
       A buffer to hold the unpacked FourCC code.
*/
inline void TFourCC::FourCC( TPtr8* aDes ) const
	{
	TUint8 char1 = TUint8( iFourCC ) ;
	TUint8 char2 = TUint8( iFourCC >> 8 ) ;
	TUint8 char3 = TUint8( iFourCC >> 16 ) ;
	TUint8 char4 = TUint8( iFourCC >> 24 ) ;

	aDes->Format( _L8("%1c%1c%1c%1c"), char1, char2, char3, char4 ) ;
	}

