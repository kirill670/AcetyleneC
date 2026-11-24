/*
* ==============================================================================
*  Name        : DevSoundAudioInput.h
*  Part of     : AdvancedAudioPlugin
*  Interface   : ?Interface_category, ?Interface_name
*  Description : This file contains the class definitions for the audio input 
*                implementation that is specific only to DevSound.
*  Version     : 5
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

#ifndef __ADVANCED_AUDIOINPUT_H__
#define __ADVANCED_AUDIOINPUT_H__

// Base class from which this class is derived
#include <AdvancedAudioInput.h>

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

// DevSound includes
#include <SoundDevice.h>

#include <mmfCodecImplementationUIDs.hrh> // KUidMmfCodecConfigure

const TUid KUidConfig = {KUidMmfCodecAudioSettings};

// CONSTANTS
// AMR Bit Rate constant
const TUint KAmrBitRate4750		= 4750;
const TUint KAmrBitRate5150		= 5150;
const TUint KAmrBitRate5900		= 5900;
const TUint KAmrBitRate6700		= 6700;
const TUint KAmrBitRate7400		= 7400;
const TUint KAmrBitRate7950		= 7950;
const TUint KAmrBitRate10200	= 10200;
const TUint KAmrBitRate12200	= 12200;

// QCELP Bit Rate constant
const TUint KQcelpFullFixedRate		= 14000;
const TUint KQcelpFullVariableRate	= 13000;
const TUint KQcelpHalfFixedRate		= 6800;
const TUint	KQcelpHalfVariableRate	= 6200;

/**
* Mixin observer class to define an object capable of handling a callback from 
* DevSoundAudioInput.
*
* @lib DevSoundAudioInput.lib
* @since 2.1
*/
class MDevSoundAudioInputObserver
    {
    public:
        /**
        *
        * Callback function from CDevSoundAudioInput when the given buffer needs to  
        * be emptied (written to external storage)
        * @param   aBuffer  data buffer to be emptied
        * @return  errCode  KErrNone (0)
        *
        */
        virtual TInt EmptySharedBufferL(CMMFBuffer* aBuffer) = 0;

        /**
        *
        * Callback function from CDevSoundAudioInput to indicate recording is completed  
        * @param   none
        * @return  void
        *
        */
        virtual void RecordComplete() = 0;

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
* Class containing audio input function implementation specific to DevSound.
* Used for recording.
*
* @lib DevSoundAudioInput.lib
* @since 2.1
*/
class CDevSoundAudioInput : public CAdvancedAudioInput, 
                            public MDevSoundObserver
    {
    public:
        /**
        *
        * Class instantiation function
        *
        * @param   aSampleRate        Required recording samling rate 
        * @param   aNumChannel        Required recording number of channels (mono/stereo)
        * @param   aFourCC            Four Character code of required format
        * @param   aCodecConfigData   structure containing codec specific configuration data
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioInput 
        *                             callbacks
        *
        * @return  pointer to the instance created
        *
        */
        IMPORT_C static CDevSoundAudioInput* NewL(TUint aSampleRate,
            TUint aNumChannel, TFourCC aFourCC, TDesC8& aCodecConfigData, 
            const TMMFPrioritySettings& aPrioritySettings,
            MDevSoundAudioInputObserver& aObserver);

        /**
        *
        * Class instantiation function (used when it's not necessary to reconfigure DevSound
        * and codec).
        *
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioInput 
        *                             callbacks
        *
        * @return  pointer to the instance created
        *
        */
        IMPORT_C static CDevSoundAudioInput* NewL(const TMMFPrioritySettings& aPrioritySettings,
            MDevSoundAudioInputObserver& aObserver);

        /**
        *
        * Destructor function
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual ~CDevSoundAudioInput();

        /**
        *
        * Prepares DevSound Audio Input for recording (sets state to ready)
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void PrimeL();

        /**
        *
        * Handles request to pause recording. Sends pause command to DevSound.
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void PauseL();

        /**
        *
        * Handles request to start recording. Configures and initializes DevSound and
        * request DevSound to start collecting audio for recording, 
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void RecordL(TAny* aBuffer);

        /**
        *
        * Handles request to stop recording. Sends stop command to DevSound.
        *
        * @param   none
        *
        * @return  none
        *
        */
        IMPORT_C virtual void StopL();

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
        * Handles request to get the maximum gain. The max gain is obtained from DevSound.
        *
        * @param   none
        *
        * @return  the maximum gain value
        *
        */
        IMPORT_C virtual TInt MaxGainL();

        /**
        *
        * Handles request to set the maximum gain. The new value is sent to DevSound.
        *
        * @param   aGain  new gain value
        *
        * @return  void
        *
        */
        IMPORT_C virtual void SetGainL(TInt aGain);

        /**
        *
        * Handles request to get the current gain. The current gain is obtained from DevSound.
        *
        * @param   void
        *
        * @return  the current gain value
        *
        */
        IMPORT_C virtual TInt GainL();

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
        * Handles request to configure DevSound with the given parameters.
        *
        * @param   aSampleRate       recording sampling rate
        * @param   aNumChannel       required number of channels (mono/stereo indication)
        * @param   aFourCC           FourCC of required recording format
        * @param   aCodecConfigData  specific codec configuration data
        *
        * @return  void
        *
        */
        IMPORT_C virtual void ConfigureL(TUint aSampleRate, TUint aNumChannel, TFourCC aFourCC, TDesC8& aCodecConfigData);

        /**
        *
        * Handles request to calculate current record position in terms to micro seconds
        *
        * @param   none
        *
        * @return  Current position in microseconds
        *
        */
        IMPORT_C virtual TInt CalculateAudioInputPositionL() const;

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

        /**
		*
		* Handles request to set bitrate to DevSound
		*
		* @param    aBitRate			bit rate
		* @param    aCodecConfigData	specific codec configuration data
		*
		* @return 	void
		*
		*/
		IMPORT_C virtual void SetBitRatesL(TUint aBitRate, RArray<TInt>& aCodecConfigData);
		
        /**
		*
		* Handles request to set sample rate to DevSound
		*
		* @param	aRate		sample rate
		*
		* @return 	void
		*
		*/
		IMPORT_C virtual void SetRatesL(TUint aSampleRate);	

        /**
		*
		* Handles request to set Channel number to DevSound
		*
		* @param	aNumChannels		number of channels
		*
		* @return 	void
		*
		*/
		IMPORT_C virtual void SetChannelsL(TUint aNumChannels);	

    private:
        /**
        *
        * Handles the request for more audio data. Sends request to DevSound for 
        * more input data to be filled in the given buffer.
        *
        * @param   aBuffer  buffer to place new audio data
        *
        * @return  void
        *
        */
        void FillBufferL(CMMFBuffer* aBuffer, TMediaId /*aMediaId*/);//called by a MDataSink to request buffer fill

        /**
        *
        * Playback function (no implementation)
        *
        * @param   aBuffer  not used
        *
        * @return  void
        *
        */
        void BufferEmptiedL(CMMFBuffer* /*aBuffer*/);

        /**
        *
        * Process the audio data in given buffer. Send data to encoder if ARM codec is selected.
        *
        * @param   aBuffer  buffer containing audio data (if hard codec, this buffer contains encoded data)
        *
        * @return  void
        *
        */
        void EmptyNextBuffer (CMMFBuffer* aBuffer);

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
        * Creates an instance of DevSound and call the initialization function.
        *
        * @param   aCodecConfigData  stucture containing codec specific configuration data
        *
        * @return  void
        *
        */
        void LoadL(const TDesC8& aCodecConfigData);

        /**
        *
        * The initialization function checks if a soft codec is required. If a soft codec is
        * required, an instance of the soft codec is created and configured with the given
        * codec configuration parameters. DevSound initialization is then called.
        *
        * @param   aCodecConfigData  stucture containing codec specific configuration data
        *
        * @return  void
        *
        */
        void InitializeL (const TDesC8& aCodecConfigData);

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
        * Get audio from hardware device (not used)
        *
        * @param   aBuffer  buffer to hold data read in from hardware device
        *
        * @return  FourCC code
        *
        */
        void HWFillBufferL(CMMFBuffer* aBuffer);

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
        * @param   aCodecConfigData   structure containing codec specific configuration data
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioInput 
        *                             callbacks
        *
        * @return  void
        *
        */
        void ConstructL(TUint aSampleRate, TUint aNumChannel,TFourCC aFourCC,
                        TDesC8& aCodecConfigData, const TMMFPrioritySettings& aPrioritySettings,
                        MDevSoundAudioInputObserver& aObserver);

        /**
        *
        * Phase 2 of two-phase constructor.
        *
        * @param   aPrioritySettings  priority settings for devSound and policy
        * @param   aObserver          observer class that will handle all DevSoundAudioInput 
        *                             callbacks
        *
        * @return  void
        *
        */
        void ConstructL(const TMMFPrioritySettings& aPrioritySettings,
                        MDevSoundAudioInputObserver& aObserver);

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

		enum TQcelpEncodingMode
			{
			EQcelpEncodingRateBlank=0,
			EQcelpEncodingRateEighth,	// non-voice (noise, silence, garbage)
			EQcelpEncodingRateQuarter,	// non-voice (noise, silence, garbage)
			EQcelpEncodingRateHalf,		// voice
			EQcelpEncodingRateFull		// voice
			};

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
            EPaused,
            EDevSoundReady,
            EBufferEmpty
            };

        // DevSoundAudioInput error code
        enum TError
            {
            ECantCreateBuffer,
            EEmptyBuffer,
            EDevSoundNotLoaded,
            EUnknown
            };

        // DevSoundAudioInput events
        enum TNextEvent
            {
            EDoNothing,
            EFlushBuffer,
            EPlayEnd
            };

        // DevSound pointer
        CMMFDevSound* iMMFDevSound;

        // current DevSoundAudioInput state
        TState iState;

        // True if this is the first audio buffer required from DevSound
        TBool iFirstBuffer;

        // True if DevSound has been loaded
        TBool iDevSoundLoaded;

        // True if DevSound has been stopped
        TBool iStopped;

        // error code
        TError iError;

        // codec selection code
        TCodec iCodecSelect;

        // priority settings for DevSound
        TMMFPrioritySettings iPrioritySettings;

        // sampling rate
        TUint iSinkSampleRate;

        // number of channels
        TUint iSinkChannels;

        // FourCC code
        TFourCC iSinkFourCC;

        // data type
        TFourCC iDataTypeCode;

        // DevSound buffer
        CMMFBuffer* iDevSoundBuf;

        // array of shared buffers
        RPointerArray<CMMFDataBuffer>* iSharedBuffers;

        // next available buffer index
	    TInt iSharedBufferIndex;

        // next available buffer pointer
        CMMFBuffer* iNextBuffer;

        // pointer to soft codec if used
        CMMFCodec* iSoftCodec;

        // pointer to DevSoundAudioInput observer for handling callback functions
        MDevSoundAudioInputObserver* iObserver;
        
	};

#endif
