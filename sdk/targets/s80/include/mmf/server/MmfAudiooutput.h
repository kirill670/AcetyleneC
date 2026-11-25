// MMFAudioOutput.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MMF_AUDIOOUTPUT_H__
#define __MMF_AUDIOOUTPUT_H__

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
#include <e32std.h>

#include <mmfAudioIOInterfaceUIDs.hrh>

#include <mmfpaniccodes.h>

//DevSound
#include <SoundDevice.h>

/** @publishedAll */
const TUint KAudioOutputDefaultFrameSize = 0x1000;


void Panic(TInt aPanicCode);

class MMMFAudioOutput : public MDataSink
/**
@publishedAll
@released

Interface class to allow dynamic linkage to CMMFAudioOutput.
*/
	{
public:
	//factory function
	inline static MMMFAudioOutput* NewAudioOutputL(TUid aImplementationUid, const TDesC8& aInitData);
	//interface
/**
*
* SoundDevice
* @publishedAll
* @return	Returns a CMMFDevSound& objector. Accessor function exposing public CMMFDevsound methods.
*			
*/
	virtual CMMFDevSound& SoundDevice() = 0;
/**
*
* BytesPlayed
* @publishedAll
* @return	Number of bytes recorded. If 16-bit divide this number returned by 2 to get word length.
*			
*/
	virtual TInt BytesPlayed() = 0;
/**
* Get audio from hardware device abstracted MMFDevsound (not used)
* @deprecated
* @param	aBuffer
*			The data to read in from a Hardware Device
* @param	aConsumer
*			MDataSink consuming the data contained in aBuffer
*	
*/
	virtual void HWEmptyBufferL(CMMFBuffer* aBuffer, MDataSource* aSupplier)=0;//called by a EmptyBufferL if using HW codec
protected:
	//constructor
	MMMFAudioOutput() : MDataSink(KUidMmfAudioOutput) {}
	};

inline MMMFAudioOutput* MMMFAudioOutput::NewAudioOutputL( TUid aImplementationUid,  const TDesC8& aInitData )
	{
	//make sure the cast will be ok by checking the uid is what we expect
	__ASSERT_ALWAYS(aImplementationUid==KUidMmfAudioOutput, Panic(EMMFAudioOutputPanicBadUID));
	MMMFAudioOutput* retPtr = STATIC_CAST(MMMFAudioOutput*, MDataSink::NewSinkL(aImplementationUid, aInitData));
	return retPtr;
	}


class CMMFAudioOutput : public CBase, public MMMFAudioOutput, public MDevSoundObserver
/**
@publishedAll
@released

The interface into DevSound
*/
	{
public:
	static MDataSink* NewSinkL() ;
	virtual CMMFAudioOutput::~CMMFAudioOutput();
	void ConstructL();

	//MDataSink mixin implementations
	virtual TFourCC SinkDataTypeCode(TMediaId /*aMediaId*/); //used by data path MDataSource/Sink for codec matching
	virtual void EmptyBufferL(CMMFBuffer* aBuffer, MDataSource* aSupplier, TMediaId /*aMediaId*/);//called by a MDataSource to empty a buffer
	virtual void BufferFilledL(CMMFBuffer* aBuffer); //called by MDataSource to pass back full buffer to the sink
	virtual TBool CanCreateSinkBuffer();
	virtual CMMFBuffer* CreateSinkBufferL(TMediaId /*aMediaId*/, TBool &aReference);
	virtual TInt SinkThreadLogon(MAsyncEventHandler& aEventHandler);
	virtual void SinkThreadLogoff();
	virtual void SinkPrimeL();
	virtual void SinkPauseL();
	virtual void SinkPlayL();
	virtual void SinkStopL();
	virtual void SetSinkPrioritySettings(const TMMFPrioritySettings& aPrioritySettings);
	virtual void NegotiateL(MDataSource& aSource);
	// MMMFAudioOutput mixin implementations
	TInt BytesPlayed();
	void HWEmptyBufferL(CMMFBuffer* aBuffer, MDataSource* aSupplier);//called by a EmptyBufferL if using HW codec
	CMMFDevSound& SoundDevice();
	virtual TInt SetSinkDataTypeCode(TFourCC aSinkFourCC, TMediaId aMediaId);

	//The following DataType() methods should not be used.
	//They are provided to maintain BC/SC with 7.0s
	virtual void SetDataTypeL(TFourCC aAudioType);
	virtual TFourCC DataType() const;

protected:
	virtual void ConstructSinkL( const TDesC8& aInitData ) ;

private:
	inline CMMFAudioOutput() {}

	void ConfigDevSoundL();
	void LoadL();
	TFourCC FetchHWCodecIfAvailableL(TFourCC aFourCC);
	TInt State();

	//MDevSoundObserver mixin implementations	
	virtual void InitializeComplete(TInt aError);
	virtual void ToneFinished(TInt aError); 
	virtual void BufferToBeFilled(CMMFBuffer* aBuffer);
	virtual void PlayError(TInt aError); 
	virtual void BufferToBeEmptied(CMMFBuffer* aBuffer); 
	virtual void RecordError(TInt aError); 
	virtual void ConvertError(TInt aError);
	virtual void DeviceMessage(TUid aMessageType, const TDesC8& aMsg);
	virtual void SendEventToClient(const TMMFEvent& /*aEvent*/);
private:
	MAsyncEventHandler* iEventHandler;
	CMMFDevSound* iMMFDevSound;	//this is now private to stop stuff "grabbing it"
	CMMFBuffer* iAudioBuffer;

	enum TState
		{
		EIdle=0,
		EDevSoundReady,
		EPaused
		};

	enum TError
		{
		ECantCreateBuffer,
		EEmptyBuffer,
		EDevSoundNotLoaded,
		ERecordNotSupported,
		EDevSoundError,
		EUnknown
		};

	MDataSource* iSupplier;
	TState iState;

	TBool iFirstBufferSent;
	TBool iDevSoundLoaded;

	TError iError;
	TInt iMMFDevsoundError;
	TMMFPrioritySettings iPrioritySettings;

	TUint iSourceSampleRate; 
	TUint iSourceChannels;
	TFourCC iSourceFourCC;
	TFourCC iDataTypeCode;
	CMMFDataBuffer* iDevSoundBuffer;

	TMMFCapabilities iDevSoundConfig;

 	TBool iNeedsSWConversion;
	TUint iSWConvertSampleRate;
	TUint iSWConvertChannels;
 	CMMFChannelAndSampleRateConverterFactory* iChannelAndSampleRateConverterFactory;
 	CMMFChannelAndSampleRateConverter* iChannelAndSampleRateConverter;
 	CMMFDataBuffer* iConvertBuffer;
 	CMMFBuffer* iBufferToEmpty;
	};

#endif
