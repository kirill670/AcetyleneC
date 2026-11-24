/*
* ==============================================================================
*  Name        : DevSoundAudioOutput.h
*  Part of     : AdvancedAudioPlugin
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : 6
*
*  Copyright © 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __MMF_DEVSOUND_AUDIOOUTPUT_H__
#define __MMF_DEVSOUND_AUDIOOUTPUT_H__

// Base class from which this class is derived
#include <AdvancedAudioOutput.h>

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
#include <e32std.h>
#include <d32snd.h>
#include <e32hal.h>
#include <e32svr.h>

// MMF includes
#include <Mmfcodec.h>
#include <Mmfdatabuffer.h>
#include <mmfpaniccodes.h>

//DevSound includes
#include <SoundDevice.h>

/**
* Mixin observer class to define an object capable of handling a callback from
* DevSoundAudioOutput.
*
* @lib DevSoundAudioOutput.lib
* @since 2.1
*/
class MDevSoundAudioOutputObserver
    {
    public:
        /**
        *
        * Callback function from CDevSoundAudioInput when the given buffer needs to
        * be refilled (read to external storage)
        * @param   refillBuffer  data buffer to be filled with new data
        * @return  errCode  KErrNone (0)
        *
        */
        virtual TInt RefillBuffer(CMMFBuffer* refillBuffer) = 0;

        /**
        *
        * Callback function from CDevSoundAudioInput to indicate playback is completed
        * @param   none
        * @return  void
        *
        */
        virtual void PlaybackComplete() = 0;

        /**
        *
        * Callback function from CDevSoundAudioInput to handle specified event
        * @param   aEvent  the event to be handled
        * @return  void
        *
        */
        virtual void SendEvent(const TMMFEvent& aEvent) = 0;
    };

// Forward class declaration
class CHardwareCodec;

/**
* Class containing audio output function implementation specific to DevSound.
* Used for playback.
*
* @lib DevSoundAudioOutput.lib
* @since 2.1
*/
class CDevSoundAudioOutput : public CAdvancedAudioOutput,
                             public MDevSoundObserver
    {
    public:
        /**
        *
        * Class instantiation function
        *
        * @param   aSampleRate        Required playback samling rate
        * @param   aNumChannel        Required playback number of channels (mono/stereo)
        * @param   aFourCC            Four Character code of required format
        * @param   aCodecConfigData   structure containing codec specific configuration data
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioOutput
        *                             callbacks
        *
        * @return  pointer to the instance created
        *
        */
        IMPORT_C static CDevSoundAudioOutput* NewL(TUint aSampleRate,
            TUint aNumChannel, TFourCC aFourCC, TUid aConfigType, TDesC8& aCodecConfigData,
            const TMMFPrioritySettings& aPrioritySettings,
            MDevSoundAudioOutputObserver& aObserver);

        /**
        *
        * Class instantiation function (used when it's not necessary to reconfigure DevSound
        * and codec).
        *
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioOutput
        *                             callbacks
        *
        * @return  pointer to the instance created
        *
        */
        IMPORT_C static CDevSoundAudioOutput* NewL(const TMMFPrioritySettings& aPrioritySettings,
                                                   MDevSoundAudioOutputObserver& aObserver);

        /**
        *
        * Destructor function
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual ~CDevSoundAudioOutput();

        /**
        *
        * Prepares DevSound Audio Input for playback (sets state to ready)
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void PrimeL();

        /**
        *
        * Handles request to pause playback. Sends pause command to DevSound.
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void PauseL();

        /**
        *
        * Handles request to start playback. Configures and initializes DevSound and
        * sends first buffer of audio data to DevSound,
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void PlayL(TAny* aBuffer);

        /**
        *
        * Handles request to stop playback. Sends stop command to DevSound.
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void StopL();

        /**
        *
        * Handles request to get the maximum volume. The max volume is obtained from DevSound.
        *
        * @param   none
        *
        * @return  the maximum gain value
        *
        */
        IMPORT_C virtual TInt MaxVolumeL();

        /**
        *
        * Handles request to set the maximum volume. The new value is sent to DevSound.
        *
        * @param   aVolume  new volume value
        *
        * @return  void
        *
        */
        IMPORT_C virtual void SetVolumeL(TInt aVolume);

        /**
        *
        * Handles request to get the current volume. The current volume is obtained from DevSound.
        *
        * @param   void
        *
        * @return  the current volume value
        *
        */
        IMPORT_C virtual TInt VolumeL();

        /**
        *
        * Handles request to set priority. The given priority settings are sent to DevSound.
        *
        * @param   aPrioritySettings  new priority settings
        *
        * @return  none
        *
        */
		IMPORT_C virtual void SetPrioritySettingsL(const TMMFPrioritySettings& aPrioritySettings);

        /**
        *
        * Handles request to calculate current playback position in terms to micro seconds
        *
        * @param   none
        *
        * @return  Current position in microseconds
        *
        */
        IMPORT_C virtual TInt CalculateAudioOutputPositionL() const;

        /**
        *
        * Handles request to get all configured sampling rates from DevSound.
        * This is a request for all sampling rates that DevSound is currently
        * configured with.
        *
        * @param   aRates  array to hold the retrieved sampling rates
        *
        * @return  void
        *
        */
        IMPORT_C virtual void ConfigRatesL(RArray<TUint>& aRates);

        /**
        *
        * Handles request to get all configured channels from DevSound.
        * This is a request for all channels that DevSound is currently
        * configured with.
        *
        * @param   aChannels  array to hold the retrieved channels
        *
        * @return  void
        *
        */
        IMPORT_C virtual void ConfigChannelsL(RArray<TUint>& aChannels);

        /**
        *
        * Handles request to get all configured data types (FourCC) from DevSound.
        * This is a request for all data types that DevSound is currently
        * configured with.
        *
        * @param   aDataTypes  array to hold the retrieved data types
        *
        * @return  void
        *
        */
        IMPORT_C virtual void ConfigDataTypesL(RArray<TFourCC>& aDataTypes);

        /**
        *
        * Handles request to get all capablities sampling rates from DevSound.
        * This contains all sampling rates DevSound is capable of supporting
        *
        * @param   aRates  array to hold the retrieved sampling rates
        *
        * @return  void
        *
        */
        IMPORT_C virtual void CapabilitiesRatesL(RArray<TUint>& aRates);

        /**
        *
        * Handles request to get all capabilities channels from DevSound.
        * This is a request for all channels that DevSound is capable of
        * supporting.
        *
        * @param   aChannels  array to hold the retrieved channels
        *
        * @return  void
        *
        */
        IMPORT_C virtual void CapabilitiesChannelsL(RArray<TUint>& aChannels);

        /**
        *
        * Handles request to get all capabilities data types (FourCC) from DevSound.
        * This is a request for all data types that DevSound is capable of
        * supporting.
        *
        * @param   aDataTypes  array to hold the retrieved channels
        *
        * @return  void
        *
        */
        IMPORT_C virtual void CapabilitiesDataTypesL(RArray<TFourCC>& aDataTypes);

        /**
        *
        * Handles request to set volume ramp to given duration.
        *
        * @param   aRampDuration  ramp duration in microseconds
        *
        * @return  void
        *
        */
        IMPORT_C virtual void SetVolumeRampL(const TTimeIntervalMicroSeconds& aRampDuration);

        /**
        *
        * Handles request to set play balance in DevSound.
        *
        * @param   aLeftPercentage   percentage for left channel
        * @param   aRightPercentage  percentage for right channel
        *
        * @return  void
        *
        */
        IMPORT_C virtual void SetPlayBalanceL(TInt aLeftPercentage, TInt aRightPercentage);

        /**
        *
        * Handles request to get play balance from DevSound.
        *
        * @param   aLeftPercentage   percentage retrieved for left channel
        * @param   aRightPercentage  percentage retrieved for right channel
        *
        * @return  void
        *
        */
        IMPORT_C virtual void GetPlayBalanceL(TInt& aLeftPercentage, TInt& aRightPercentage);

        /**
        *
        * Handles request to configure DevSound with the given parameters.
        *
        * @param   aSampleRate       recording sampling rate
        * @param   aNumChannel       required number of channels (mono/stereo indication)
        * @param   aFourCC           FourCC of required recording format
        * @param   aConfigType       UID for use in the codec ConfigureL function (this UID
        *                            is used to identify the command to the ConfigureL function
        * @param   aCodecConfigData  specific codec configuration data
        *
        * @return  void
        *
        */
        IMPORT_C virtual void ConfigureL(TUint aSampleRate, TUint aNumChannel, TFourCC aFourCC,
                                         TUid aConfigType, const TDesC8& aCodecConfigData);

        /**
        *
        * Handles request to configure DevSound with the given parameters.
        *
        * @param   aConfigType       UID for use in the codec ConfigureL function (this UID
        *                            is used to identify the command to the ConfigureL function
        * @param   aCodecConfigData  specific codec configuration data
        *
        * @return  void
        *
        */
        IMPORT_C virtual void ConfigureL(TUid aConfigType, const TDesC8& aConfigData);

// MDevSoundObserver mixin implementations
        /**
        *
        * Callback function from DevSound to indicate initialization has completed
        *
        * @param   aError  error code returned by DevSound (KErrNone if no error)
        *
        * @return  void
        *
        */
        virtual void InitializeComplete(TInt aError);

        /**
        *
        * Callback function from DevSound to indicate tone playback has completed
        *
        * @param   aError  error code returned by DevSound (KErrNone if no error)
        *
        * @return  void
        *
        */
        virtual void ToneFinished(TInt aError);

        /**
        *
        * Callback function from DevSound for more playback data (for playback only)
        *
        * @param   aBuffer  buffer to place playback PCM data
        *
        * @return  void
        *
        */
        virtual void BufferToBeFilled(CMMFBuffer* aBuffer);

        /**
        *
        * Callback function from DevSound to indicate error has occurred during playback
        * (for playback only)
        *
        * @param   aError  error code returned by DevSound (KErrNone if no error)
        *
        * @return  void
        *
        */
        virtual void PlayError(TInt aError);

        /**
        *
        * Callback function from DevSound to indicate input buffer needs to be emptied
        * (for record only)
        *
        * @param   aBuffer  buffer with recorded data that needs to be emptied
        *
        * @return  void
        *
        */
        virtual void BufferToBeEmptied(CMMFBuffer* aBuffer);

        /**
        *
        * Callback function from DevSound to indicate error has occurred during recording
        * (for record only)
        *
        * @param   aError  error code returned by DevSound (KErrNone if no error)
        *
        * @return  void
        *
        */
        virtual void RecordError(TInt aError);

        /**
        *
        * Callback function from DevSound to indicate error has occurred during conversion
        * (during conversion only)
        *
        * @param   aError  error code returned by DevSound (KErrNone if no error)
        *
        * @return  void
        *
        */
        virtual void ConvertError(TInt aError);

        /**
        *
        * Callback function from hardware device passed through via DevSound
        *
        * @param   aMessageType  type of message
        * @param   aMsg          message contents
        *
        * @return  void
        *
        */
        virtual void DeviceMessage(TUid aMessageType, const TDesC8& aMsg);

        /**
        *
        * Callback function from DevSound to request given event be sent to client
        *
        * @param   aEvent  event to send
        *
        * @return  void
        *
        */
        virtual void SendEventToClient(const TMMFEvent& /*aEvent*/);

    private:
        /**
        *
        * Request DevSound to empty given buffer, i.e play audio in buffer
        *
        * @param   aBuffer  buffer containing audio data. If soft codec, this buffer
        *                   contains PCM data; if hard codec, this buffer contains
        *                   encoded data.
        *
        * @return  void
        *
        */
        virtual void EmptyBufferL(CMMFBuffer* aBuffer, TMediaId /*aMediaId*/);//called by a MDataSource to empty a buffer

        /**
        *
        * Request from MDataSource to pass back full buffer to the sink
        * (not applicable to playback)
        *
        * @param   aBuffer  buffer containing audio data.
        *
        * @return  void
        *
        */
        virtual void BufferFilledL(CMMFBuffer* aBuffer); //called by MDataSource to pass back full buffer to the sink

        /**
        *
        * Fill next buffer with audio data. This function will call either the FillNextBufferArmL() or
        * FillNextBufferHwL()
        *
        * @param   aBuffer  buffer containing audio data.
        *
        * @return  void
        *
        */
        void FillNextBufferL(CMMFBuffer* aBuffer);

        /**
        *
        * Soft codec implementation to fill next buffer with audio data. The data is first decoded
        * before placing in the buffer.
        *
        * @param   aBuffer        buffer to hold the decoded audio data.
        * @param   aRefillBuffer  address of source buffer returned to caller if all data in the buffer
        *                         has been consumed and so needs to be refilled
        *
        * @return  void
        *
        */
        void FillNextBufferArmL(CMMFBuffer* aBuffer, CMMFBuffer*& aRefillBuffer, TInt& aNextEvent);

        /**
        *
        * Hard codec implementation to fill next buffer with audio data. The data is merely copied
        * from the source buffer to the specified DevSound buffer
        *
        * @param   aBuffer        buffer to hold the encoded data.
        * @param   aRefillBuffer  address of source buffer returned to caller if all data in the buffer
        *                         has been consumed and so needs to be refilled
        *
        * @return  void
        *
        */
        void FillNextBufferHwL(CMMFBuffer* aBuffer, CMMFBuffer*& aRefillBuffer, TInt& aNextEvent);

        /**
        *
        * Creates an instance of DevSound and call the initialization function.
        *
        * @param   aConfigType       UID for use in the codec ConfigureL function (this UID
        *                            is used to identify the command to the ConfigureL function
        * @param   aCodecConfigData  stucture containing codec specific configuration data
        *
        * @return  void
        *
        */
        void LoadL(TUid aConfigType, const TDesC8& aCodecConfigData);

        /**
        *
        * The initialization function checks if a soft codec is required. If a soft codec is
        * required, an instance of the soft codec is created and configured with the given
        * codec configuration parameters. DevSound initialization is then called.
        *
        * @param   aConfigType       UID for use in the codec ConfigureL function (this UID
        *                            is used to identify the command to the ConfigureL function
        * @param   aCodecConfigData  stucture containing codec specific configuration data
        *
        * @return  void
        *
        */
        void InitializeL (TUid aConfigType, const TDesC8& aCodecConfigData);

        /**
        *
        * Determine sampling rate to use. Hardware accelerated codecs perform the
        * sampling rate conversion, so coded sampling rate can be used. For soft codec,
        * DevSound capabilities must first be obtained to determine what samples rates
        *  are supported by DevSound. If coded sampling rate is not supported, DevSound
        * must be configured with the next lowest sampling rate (downsampled)
        *
        * @param   none
        *
        * @return  void
        *
        */
        void NegotiateL();

        /**
        *
        * Gets the next available shared buffer from the pool of shared buffers.
        *
        * @param   none
        *
        * @return  void
        *
        */
		void NextSharedBufferL();

        /**
        *
        * This function does a match on ECOM Registry to look for hardware codec.
        * If there is a hardware codec, set Sink 4CC to match, otherwise use PCM16 as the
        * default.
        *
        * @param   none
        *
        * @return  FourCC code
        *
        */
        TFourCC FetchHWCodecIfAvailable();

        /**
        *
        * Request hardware device to empty given buffer (not used)
        *
        * @param   aBuffer  buffer with audio data to playback
        *
        * @return  void
        *
        */
        void HWEmptyBufferL(CMMFBuffer* /*aBuffer*/);

        /**
        *
        * Function to get DevSound capabilities and configure DevSound appropriately.
        *
        * @param   none
        *
        * @return  void
        *
        */
        void ConfigDevSoundL();

        /**
        *
        * Phase 2 of two-phase constructor
        *
        * @param   aSampleRate        Required recording samling rate
        * @param   aNumChannel        Required recording number of channels (mono/stereo)
        * @param   aFourCC            Four Character code of required format
        * @param   aConfigType        UID for use in the codec ConfigureL function (this UID
        *                             is used to identify the command to the ConfigureL function
        * @param   aCodecConfigData   structure containing codec specific configuration data
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioInput
        *                             callbacks
        *
        * @return  void
        *
        */
        void ConstructL(TUint aSampleRate,
            TUint aNumChannel, TFourCC aFourCC, TUid aConfigType, TDesC8& aCodecConfigData,
            const TMMFPrioritySettings& aPrioritySettings,
            MDevSoundAudioOutputObserver& aObserver);

        /**
        *
        * Phase 2 of two-phase constructor.
        *
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioOuput
        *                             callbacks
        *
        * @return  void
        *
        */
        void ConstructL(const TMMFPrioritySettings& aPrioritySettings, MDevSoundAudioOutputObserver& aObserver);

        /**
        *
        * Converts DevSound bit representation of sampling rates to integer values.
        *
        * @param   aDevSoundCaps  DevSound capabilities structure
        * @param   aSampleRates   array to hold the retrieved sampling rates
        *
        * @return  void
        *
        */
		void ConvertFromDevSoundCapsToSampleRatesL(const TMMFCapabilities& aDevSoundCaps, RArray<TUint>& aSampleRates);

        /**
        *
        * Converts DevSound representation of data types to FourCC values.
        *
        * @param   aDevSoundCaps  DevSound capabilities structure
        * @param   aDataTypes     array to hold the retrieved data types
        *
        * @return  void
        *
        */
		void ConvertFromDevSoundCapsToDataTypesL(const TMMFCapabilities& aDevSoundCaps, RArray<TFourCC>& aDataTypes);

        /**
        *
        * Converts DevSound representation of channels to integer values.
        *
        * @param   aDevSoundCaps  DevSound capabilities structure
        * @param   aNumChannels   array to hold the retrieved number of channels
        *
        * @return  void
        *
        */
		void ConvertFromDevSoundCapsToNumChannelsL(const TMMFCapabilities& aDevSoundCaps, RArray<TUint>& aNumChannels);

        /**
        *
        * Issues a user panic with the given panic code
        *
        * @param   aPanicCode  panic code
        *
        * @return  void
        *
        */
		void Panic(TInt aPanicCode) const;

    private:
        // Codec options
        enum TCodec
            {
            EUseARMCodec=0,
            EUseHWCodec
            };

        // DevSoundAudioInput states
        enum TState
            {
            EIdle=0,
            EDevSoundReady,
            EMMFDevSoundFirstBufferSent,
            EPlaying,
            EPaused,
            EBufferEmpty,
			EPreIdle
            };

        // DevSoundAudioInput error code
        enum TError
            {
            ECantCreateBuffer,
            EEmptyBuffer,
            EDevSoundNotLoaded,
            ERecordNotSupported,
            EDevSoundError,
            EUnknown
            };

    private:
        // True if sampling rate conversion is required
        TBool iNeedsSWConversion;

        // Sample rate to convert to
        TUint iSWConvertSampleRate;

        // Number of channels to convert to
        TUint iSWConvertChannels;

        // sample rate converter factory pointer
        CMMFChannelAndSampleRateConverterFactory* iChannelAndSampleRateConverterFactory;

        // sample rate converter pointer
        CMMFChannelAndSampleRateConverter* iChannelAndSampleRateConverter;

        // converter buffer pointer
        CMMFDataBuffer* iConvertBuffer;

        // DevSound pointer
        CMMFDevSound* iMMFDevSound;

        // asynchronous event handler
        MAsyncEventHandler* iEventHandler;

        // True if first buffer has been sent to DevSound
        TBool iFirstBufferSent;

        // DevSoundAudioOutput internal state
        TState iState;

        // Hardware accelerated codec pointer if hardware codec is used
        CHardwareCodec* iHWCodec;

        // True if DevSound has been loaded
        TBool iDevSoundLoaded;

        // codec selection option (soft/hard codec)
        TCodec iCodecSelect;

        // soft codec pointer if soft codec is used
		CMMFCodec* iSoftCodec;

        // priority settings for DevSound
        TMMFPrioritySettings iPrioritySettings;

        // Structure for DevSound configuration parameters
        TMMFCapabilities iDevSoundConfig;

        // sampling rate from the source audio data
        TUint iSourceSampleRate;

        // number of channel from the source audio data
        TUint iSourceChannels;

        // FourCC from the source audio data
        TFourCC iSourceFourCC;

        // profile - only used for AAC
        TInt iSourceProfile;

        // saved data type (FourCC)
        TFourCC iDataTypeCode;

        // codec type
        TAdvancedAudioOutputCodecType iCodecType;

        // array of shared buffers
        RPointerArray<CMMFDataBuffer>* iSharedBuffers;

        // next available buffer index
	    TInt iSharedBufferIndex;

        // audio buffer to empty pointer
        CMMFBuffer* iBufferToEmpty;

        // next available buffer pointer
        CMMFBuffer* iNextBuffer;

        // saved buffer pointer during pause
        CMMFBuffer* iPausedBuffer;

        // pointer to DevSoundAudioInput observer for handling callback functions
        MDevSoundAudioOutputObserver* iObserver;

	};

#endif
