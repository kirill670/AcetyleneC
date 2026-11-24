// GsmAudio.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __GSMAUDIO_H__
#define __GSMAUDIO_H__


//*******************************************************************
//* INCLUDE FILES:
//*******************************************************************

// Standard EPOC32 includes
#include <e32base.h>
// Public Media Server includes
#include <Mda\Common\Base.h>
#include <Mda\Common\Resource.h>
#include <Mda\Common\Controller.h>
#include <Mda\Common\Audio.hrh>
#include <Mda\Common\GsmAudio.hrh>


//*******************************************************************
//* CONSTANTS:
//*******************************************************************

// Wav Codec Uids
/**
@publishedAll
@released
Uid value for GSM610 codec
*/
const TUint KUidMdaGsmWavCodecValue = KUidMdaGsmWavCodecDefine;
/**
@publishedAll
@released
Uid for GSM610 codec
*/
const TUid  KUidMdaGsmWavCodec      = { KUidMdaGsmWavCodecValue };


//*******************************************************************
//* TMdaGsmWavCodec Class:
//*******************************************************************


class TMdaGsmWavCodec : public TMdaWavCodec
/** 
 * @internalTechnology
 */
	{
public:
	inline TMdaGsmWavCodec();
	};


//*******************************************************************
//* INLINE FUNCTIONS:
//*******************************************************************

inline TMdaGsmWavCodec::TMdaGsmWavCodec() :
	TMdaWavCodec (KUidMdaGsmWavCodec, sizeof(TMdaGsmWavCodec) )
	{
	}


#endif	// __GSMAUDIO_H__
