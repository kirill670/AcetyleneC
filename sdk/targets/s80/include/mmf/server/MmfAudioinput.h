// MMFAudioInput.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MMF_AUDIOINPUT_H__
#define __MMF_AUDIOINPUT_H__

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
#include <e32std.h>

// Public Media Server includes
#include <mmfAudioIOInterfaceUIDs.hrh>
#include <mmfpaniccodes.h>


// DevSound
#include <SoundDevice.h>

/** @publishedAll */
const TUint KAudioInputDefaultFrameSize = 0x1000;  //4K
//#define KAudioInputCanResample		//uncomment this to allow Audio Input to sample rate convert 


void Panic(TInt aPanicCode);

class MMMFAudioInput : public MDataSource
/**
@publishedAll
@released

Interface class to allow dynamic linkage to CMMFAudioInput.
*/
	{
public:
	//factory function
	inline static MMMFAudioInput* NewAudioInputL(TUid aImplementationUid, const TDesC8& aInitData);
	//interface

/**
*
* SoundDevice
* @return	Returns a CMMFDevSound& objector. Accessor function exposing public CMMFDevsound methods.
*			
*/
	virtual CMMFDevSound& SoundDevice() = 0;

/**
*
* BytesPlayed
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
	virtual void HWFillBufferL(CMMFBuffer* aBuffer, MDataSink* aConsumer) = 0;
protected:
	//constructor
	inline MMMFAudioInput() : MDataSource(KUidMmfAudioInput) {};
	};

inline MMMFAudioInput* MMMFAudioInput::NewAudioInputL( TUid aImplementationUid,  const TDesC8& aInitData ) 
	{
	//make sure the cast will be ok by checking the uid is what we expect
	__ASSERT_ALWAYS(aImplementationUid==KUidMmfAudioInput, Panic(EMMFAudioInputPanicBadUID));
	MMMFAudioInput* retPtr = STATIC_CAST(MMMFAudioInput*, MDataSource::NewSourceL(aImplementationUid, aInitData));
	return retPtr;
	}


class CMMFAudioInput : public CBase, public MMMFAudioInput, public MDevSoundObserver
/**
@publishedAll
@released

The interface into DevSound
*/
	{
public:

	static MDataSource* NewSourceL();
	virtual ~CMMFAudioInput();
	void ConstructL();

	//MDataSource mixin implementations
	virtual TFourCC SourceDataTypeCode(TMediaId /*aMediaId*/);
	virtual void FillBufferL(CMMFBuffer* aBuffer, MDataSink* aConsumer,TMediaId /*aMediaId*/);//called by a MDataSink to request buffer fill
	virtual void BufferEmptiedL(CMMFBuffer* aBuffer); //called by MDataSink to pass back emptied buffer to the source
	virtual TBool CanCreateSourceBuffer();
	virtual CMMFBuffer* CreateSourceBufferL(TMediaId /*aMediaId*/);

/**
*
* CreateSourceBufferL
* Intended for synchronous usage (returns buffer specific to a Media Type)
*
* @param	aMediaId
* @param	&aSinkBuffer
*		
* @return CMMFBuffer*
*/

	virtual CMMFBuffer* CreateSourceBufferL(TMediaId aMediaId, CMMFBuffer& /*aSinkBuffer*/) 
		{return CreateSourceBufferL(aMediaId);};
	virtual CMMFBuffer* CreateSourceBufferL(TMediaId /*aMediaId*/, TBool &aReference);

/**
*
* CreateSourceBufferL
* Intended for asynchronous usage (returns buffer specific to a Media Type)
*
* @param	aMediaId
* @param	&aSinkBuffer
* @param	&aaReference
*		
* @return CMMFBuffer*
*/
	virtual CMMFBuffer* CreateSourceBufferL(TMediaId aMediaId, CMMFBuffer& /*aSinkBuffer*/, TBool &aReference) 
		{return CreateSourceBufferL(aMediaId, aReference);};
	virtual TInt SourceThreadLogon(MAsyncEventHandler& aEventHandler);
	virtual void SourceThreadLogoff();
	virtual void SourcePrimeL();
	virtual void SourceStopL();
	virtual void SourcePlayL();
	virtual void SourcePauseL();
	virtual void SetSourcePrioritySettings(const TMMFPrioritySettings& aPrioritySettings);

	virtual void NegotiateSourceL(MDataSink& aSink);

	// MMMFAudioInput mixin implementations
	TInt BytesPlayed();
	void HWFillBufferL(CMMFBuffer* aBuffer, MDataSink* aConsumer); //called by a FillBufferL if using HW codec
	CMMFDevSound& SoundDevice();
	virtual TInt SetSourceDataTypeCode(TFourCC aSourceFourCC, TMediaId aMediaId);

	void LoadL();

	//The following DataType() methods and iBufferStatus should not be used.
	//They are provided to maintain BC/SC with 7.0s
	virtual void SetDataTypeL(TFourCC aAudioType);
	virtual TFourCC DataType() const;
	TRequestStatus iBufferStatus;

protected:
	virtual void ConstructSourceL( const TDesC8& aInitData ) ;

private:
	inline CMMFAudioInput() {}

	MAsyncEventHandler* iEventHandler;
	CMMFDevSound* iMMFDevSound;	//this is now private to stop stuff "grabbing it"
	
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

	void ConfigDevSoundL();
	
private:
	
	enum TCodec
		{
		EUseARMCodec=0,
		EUseHWCodec
		};

	enum TState
		{
		EIdle=0,
		EPaused,
		EDevSoundReady,
		EBufferEmpty
		};

	enum TError
		{
		ECantCreateBuffer,
		EEmptyBuffer,
		EDevSoundNotLoaded,
		EUnknown
		}; 
	

	MDataSink* iConsumer;
	TState iState;

	TBool iFirstBufferRead;

	TBool iDevSoundLoaded;
	TBool iStopped;

	TError iError;
	TInt iMMFDevsoundError;
	TMMFPrioritySettings iPrioritySettings;

	TUint iSinkSampleRate;
	TUint iSinkChannels;
	TFourCC iSinkFourCC;
	TFourCC iDataTypeCode;
	CMMFBuffer* iDevSoundBuf;
	};

#endif
