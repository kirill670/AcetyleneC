/**
@file
@publishedAll
@released
*/

// include\mmf\common\mmffourcc.h
//
// Copyright  2002 Symbian Ltd. All rights reserved.
//
#ifndef __MMF_COMMON_FOURCC_H__
#define __MMF_COMMON_FOURCC_H__


//Standard FourCC codes

/** 8-bit PCM
*/
const TUint32 KMMFFourCCCodePCM8 = 0x38502020;		//( ' ', ' ', 'P', '8' )

/** 8-bit unsigned PCM
*/
const TUint32 KMMFFourCCCodePCMU8 = 0x38555020;		//(' ', 'P', 'U', '8') 

/** 16-bit PCM
*/
const TUint32 KMMFFourCCCodePCM16 = 0x36315020;		//(' ', 'P', '1', '6')

/** 16-bit unsigned PCM
*/
const TUint32 KMMFFourCCCodePCMU16 = 0x36315550;	//('P', 'U', '1', '6')

/** Most-Significant-Byte-first (big endian) 16-bit PCM
*/
const TUint32 KMMFFourCCCodePCM16B = 0x42363150;	//( 'P', '1', '6', 'B' )

/** Most-Significant-Byte-first  (big endian)16-bit unsigned PCM
*/
const TUint32 KMMFFourCCCodePCMU16B = 0x42365550;	//( 'P', 'U', '6', 'B' )

/** IMA ADPCM
*/
const TUint32 KMMFFourCCCodeIMAD = 0x44414d49;		//('I', 'M', 'A', 'D')

/** IMA stereo ADPCM
*/
const TUint32 KMMFFourCCCodeIMAS = 0x53414d49;		//('I', 'M', 'A', 'S')

/** ALAW
*/
const TUint32 KMMFFourCCCodeALAW = 0x57414c41;		//('A', 'L', 'A', 'W')

/** MuLAW
*/
const TUint32 KMMFFourCCCodeMuLAW = 0x57414c75;		//('u', 'L', 'A', 'W')

/** GSM 610
*/
const TUint32 KMMFFourCCCodeGSM610 = 0x364d5347;	//('G', 'S', 'M', '6')

/** FourCC used if the actual fourCC is not known or not applicable
*/
const TUint32 KMMFFourCCCodeNULL = 0x4c4c554e;		//('N','U','L','L')

/** AMR
*/
const TUint32 KMMFFourCCCodeAMR = 0x524d4120;		//(' ','A','M','R')

/** Advanced Audio Codec (MPEG4, Audio layer 3)
*/
const TUint32 KMMFFourCCCodeAAC = 0x43414120;		//(' ','A','A','C')

/** Wideband AMR
*/
const TUint32 KMMFFourCCCodeAWB = 0x42574120;		//(' ','A','W','B')

/** MPEG, Audio layer 3
*/
const TUint32 KMMFFourCCCodeMP3 = 0x33504d20;		//(' ','M','P','3')

/** SBC
*/
const TUint32 KMMFFourCCCodeSBC = 0x43425320;		//(' ','S','B','C')

#include <mmf\common\mmfutilities.h>


#endif
