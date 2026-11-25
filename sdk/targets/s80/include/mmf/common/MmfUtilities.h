// include\mmf\common\mmfutilities.h
//
// Copyright  2002 Symbian Ltd. All rights reserved.
//
#ifndef __MMF_COMMON_UTILITIES_H__
#define __MMF_COMMON_UTILITIES_H__

#include <E32Base.h>
#include <mmf\server\mmfdatabuffer.h>
#include <mmf\common\MmfFourCC.h>


/** 
 * @publishedAll
 * @released
 *
 * class to identify the media type of a particular stream
 */
class TMediaId
	{
public:
	TMediaId(TUid aMediaType, TUint aStreamId) : iMediaType(aMediaType), iStreamId(aStreamId) {};
	TMediaId(TUid aMediaType) : iMediaType(aMediaType), iStreamId(0) {};
	TMediaId() : iMediaType(KNullUid), iStreamId(0) {};
public:
	/**
	 * Media type. KUidMediaTypeAudio, KUidMediaTypeVideo, etc.
	 */
	TUid iMediaType; 

	/**
	 * identifies a particular media stream used in case where multiple streams 
	 * of same media type are present on same MDataSource
	 */
	TUint iStreamId; 
	};

/**
 * @publishedAll
 */
const TInt KFourCCNULL = KMMFFourCCCodeNULL;

/**
 * @publishedAll
 * @released
 *
 * identifies a multimedia data type using a four character code
 */
class TFourCC
{
public:
	TFourCC() {iFourCC = KMMFFourCCCodeNULL;} //'NULL'
	TFourCC(TUint8 aChar1, TUint8 aChar2, TUint8 aChar3, TUint8 aChar4) {iFourCC =(aChar4<<24)+(aChar3<<16)+(aChar2<<8)+aChar1;}
	TFourCC(TInt32 aFourCC) {iFourCC = aFourCC;}
	TUint32 FourCC() {return iFourCC;}
	inline void FourCC( TPtr8* aDes ) const ;
	void Set(TFourCC aFourCC) {iFourCC = aFourCC.iFourCC;}
	void Set(TUint32 aFourCC) {iFourCC = aFourCC;}
	TBool operator==(const TFourCC& aA) const {return (iFourCC == aA.iFourCC);}
	TBool operator==(const TUint32& aUint) const {return (iFourCC == aUint);}
	TBool operator!=(const TFourCC& aA) const {return (iFourCC != aA.iFourCC);}
	TBool operator!=(const TUint32& aUint) const {return (iFourCC != aUint);}
	
private:
	TUint32 iFourCC;
};


inline void TFourCC::FourCC( TPtr8* aDes ) const 
	{
	TUint8 char1 = TUint8( iFourCC ) ;
	TUint8 char2 = TUint8( iFourCC >> 8 ) ;
	TUint8 char3 = TUint8( iFourCC >> 16 ) ;
	TUint8 char4 = TUint8( iFourCC >> 24 ) ;

	aDes->Format( _L8("%1c%1c%1c%1c"), char1, char2, char3, char4 ) ;
	}

/**
 * @internalAll
 *
 * Base utility class to change the sample rate of audio data in a buffer
 *
 */
class CMMFChannelAndSampleRateConverter : public CBase
	{
public:
	/**
	 * 
	 * Reads the audio data from the source buffer, 
	 * converts the number of channels and the sample rate
	 * and copies the result to the destination buffer
	 *
	 * @param "aSrcBuffer"
	 *         Pointer to a source buffer containing the audio data to convert
	 * @param "aDstBuffer"
	 *         Pointer to a destination buffer
	 * @return length of destination buffer
	 *
	 */
	virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer) =0;
	virtual void Reset() {};

	/*
	 * indicates what buffer size is required to hold the converted data
	 */
	virtual TUint MaxConvertBufferSize(TUint aSrcBufferSize) {return aSrcBufferSize;}

	void SetRates(TInt aSrcRate,TInt aSrcChannels,TInt aDstRate,TInt aDstChannels);
public:
	/*
	 * The sample rate of the data in the source buffer
	 */
	TInt iFromRate;
	/*
	 * The sample rate of the data in the destination buffer
	 */
	TInt iToRate;
	/*
	 * The number of channels of data in the source buffer
	 */
	TInt iFromChannels;
	/*
	 * The number of channels of data in the destination buffer
	 */
	TInt iToChannels;
protected:
	TReal iRatio;
	TInt iFraction;
	TInt iIndex;
	};

/**
 * @internalAll
 */
class CMMFStereoToMonoRateConverter : public CMMFChannelAndSampleRateConverter
	{
	public:
		virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer);
		virtual TUint MaxConvertBufferSize(TUint aSrcBufferSize);

	};

/**
 * @internalAll
 */
class CMMFStereoToMonoConverter : public CMMFChannelAndSampleRateConverter
	{
	public:
		virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer);
		virtual TUint MaxConvertBufferSize(TUint aSrcBufferSize);
	};

/**
 * @internalAll
 */
class CMMFStereoToStereoRateConverter : public CMMFChannelAndSampleRateConverter
	{
	public:
		virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer);
	};

/**
 * @internalAll
 */
class CMMFMonoToMonoRateConverter : public CMMFChannelAndSampleRateConverter
	{
	public:
		virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer);
	};

/**
 * @internalAll
 */
class CMMFMonoToStereoConverter : public CMMFChannelAndSampleRateConverter
	{
	public:
		virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer);
		virtual TUint MaxConvertBufferSize(TUint aSrcBufferSize);
	};

/**
 * @internalAll
 */
class CMMFMonoToStereoRateConverter : public CMMFChannelAndSampleRateConverter
	{
	public:
		virtual TInt Convert(const CMMFDataBuffer& aSrcBuffer, CMMFDataBuffer& aDstBuffer);
		virtual TUint MaxConvertBufferSize(TUint aSrcBufferSize);
	};

/**
 * @internalAll
 *
 * Factory class to create the appropriate CMMFChannelAndSampleRateConverter-derived
 * class depending on the supplied number of channels and bit rate
 *
 */
class CMMFChannelAndSampleRateConverterFactory : public CBase
	{
public:
	IMPORT_C CMMFChannelAndSampleRateConverter* CreateConverterL(TInt aFromRate,TInt aFromChannels,
												 TInt aToRate,TInt aToChannels);
	IMPORT_C CMMFChannelAndSampleRateConverter* CreateConverterL();
	CMMFChannelAndSampleRateConverter* Converter() {return iConverter;}
	IMPORT_C ~CMMFChannelAndSampleRateConverterFactory();
	TInt Rate() {return iToRate;}
	TInt Channels() {return iToChannels;}
public:
	/**
	 * The sample rate of the data in the source buffer
	 */
	TInt iFromRate;
	/**
	 * The sample rate of the data in the destination buffer
	 */
	TInt iToRate;
	/**
	 * The number of channels of data in the source buffer
	 */
	TInt iFromChannels;
	/**
	 * The number of channels of data in the destination buffer
	 */
	TInt iToChannels;
private:
	CMMFChannelAndSampleRateConverter* iConverter;
	};



#endif

