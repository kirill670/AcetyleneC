// SoundDevice.h
//
// Copyright (c) 2001-3 Symbian Ltd.  All rights reserved.
//

#ifndef __SOUNDDEVICE_H__
#define __SOUNDDEVICE_H__

#include <e32base.h>
#include <f32file.h>
#include <mmfbase.h>
#include <mmfutilities.h>

#include <mmf\common\MmfController.h>


//Debugging info

/*
Notes: 
This file defines the DevSound class which acts as an interface to
the hardware and is intended to invoke VCR functionality via the plug-ins.
The DevSound also contains a product specific policy.
*/

//UIDs for buffers: According to Symbian: Not used

// Public Media Server includes

/**
 *  @publishedAll
 *
 *	Sampling rates available.
 *
 *	When queried from DevSound by calling method Capabilities(), iRate indicates
 *	the sampling rates supported by the audio device.
 *
 *	DevSound by default is configured to 8KHz sampling rate.
 *	So to configure DevSound to play/record audio at 16 KHz sampling rate:
 *
 *	The mode should not be OR'ed with each other. If they are, then highest
 *	sampling rate takes precedence and DevSound will be configured to it.
 *
 */
enum TMMFSampleRate
	{
	EMMFSampleRate8000Hz  = 0x00000001,	///< 8000 Hz Sampling Rate
	EMMFSampleRate11025Hz = 0x00000002,	///< 11025 Hz Sampling Rate
	EMMFSampleRate16000Hz = 0x00000004,	///< 16000 Hz Sampling Rate
	EMMFSampleRate22050Hz = 0x00000008,	///< 22050 Hz Sampling Rate
	EMMFSampleRate32000Hz = 0x00000010,	///< 32000 Hz Sampling Rate
	EMMFSampleRate44100Hz = 0x00000020,	///< 44100 Hz Sampling Rate
	EMMFSampleRate48000Hz = 0x00000040,	///< 48000 Hz Sampling Rate
	EMMFSampleRate88200Hz = 0x00000080,	///< 88200 Hz Sampling Rate
	EMMFSampleRate96000Hz = 0x00000100,	///< 96000 Hz Sampling Rate
	EMMFSampleRate12000Hz = 0x00000200,	///< 12000 Hz Sampling Rate
	EMMFSampleRate24000Hz = 0x00000400,	///< 24000 Hz Sampling Rate
	EMMFSampleRate64000Hz = 0x00000800  ///< 64000 Hz Sampling Rate
	};

/**
 *  @publishedAll
 *
 *	Mono Stereo playback and record modes available.
 *
 *	When queried from DevSound by calling method Capabilities(), iChannels
 *	indicates whether the underlying audio device supports playing back stereo
 *	audio samples and recording audio samples in stereo mode or not.
 *
 *	DevSound by default is configured to Mono mode.
 *	So to configure DevSound to play/record audio sample in stereo mode:
 *
 *	The mode should not be OR'ed with each other. if they are, then stereo takes
 *	precedence and DevSound will be configured to stereo mode.
 *
 */
enum TMMFMonoStereo
	{
	EMMFMono	= 0x00000001,	///< Mono mode
	EMMFStereo	= 0x00000002	///< Stereo mode
	};

/**
 *  @publishedAll
 *
 *	Encoding modes available.
 *
 *	When queried from DevSound by calling method Capabilities(), iEncoding
 *	provides information about different encoding supported by audio device.
 *
 *	DevSound by default is configured to play PCM16 Bit audio data.
 *	Setting encoding mode is not supported yet:
 *
 */
enum TMMFSoundEncoding
	{
	EMMFSoundEncoding8BitPCM		= 0x00000001,	///< Signed 8 Bit PCM
	EMMFSoundEncoding16BitPCM		= 0x00000002,	///< Signed 16 Bit PCM
	EMMFSoundEncoding8BitALaw		= 0x00000004,	///< Signed 8 Bit ALaw
	EMMFSoundEncoding8BitMuLaw		= 0x00000008,	///< Signed 8 Bit MuLaw
	};

/**
 *  @publishedAll
 *
 *	Stereo support method.
 */
enum TMMFStereoSupport
	{
	EMMFNone						= 0x00000000,
	EMMFInterleavedOnly				= 0x00000001,
	EMMFNonInterleavedOnly			= 0x00000002,
	EMMFBothNonAndInterleaved		= 0x00000003,
	};

/**
 *  @publishedAll
 *
 *	Type class for DevSound implementation device capabilities.
 *
 *	CMMFDevSound will return Sampling Rates, Encoding and Stereo feature
 *	supported in this structure when queried for capabilities. DevSound can
 *	also be configured by setting parameters in this structure and passing the
 *	structure to it.
 *
 */

class TMMFCapabilities
	{
public:
	TUint	iRate;			///< Sampling Rates supported
	TUint	iEncoding;		///< Encodings supported
	TUint	iChannels;		///< Mono/Stereo support
	TInt	iBufferSize;	///< Buffer size supported
	};

/**
 *  @publishedAll
 *
 *	Class Name:	MDevSoundObserver
 *
 *
 *	An interface to a set of DevSound callback functions.
 *
 *
 *	This serves as the method of communication between the client and the
 *	DevSound.
 *
 *
 *	The class is a mixin and is intended to be inherited by the client class
 *	that is interested in observing the DevSound operation. The functions
 *	encapsulated by this class are called when specific events occur in the
 *	process of initializing and playing/recording an audio sample or playing
 *	tones.
 *
 */

class MDevSoundObserver
	{
public:
/**
 *
 *	Handles initialization completion event.
 *	
 *	A derived class must provide an implementation to handle the initialization
 *	request.
 *
 *	CMMFDevSound object calls this method when its InitializeL() function
 *	completes.
 *
 *	@param	"TInt aError"
 *			Error code. KErrNone if successful. Other values are possible
 *			indicating a problem initializing CMMFDevSound object.
 *
 */
	virtual void InitializeComplete(TInt aError)=0;

/**
 *
 *	Handles tone play completion event.
 *	
 *	A derived class must provide an implementation to handle the tone play 
 *	completion request.
 *
 *	CMMFDevSound object calls this method when an attempt to play tone has
 *	completed, successfully or otherwise.
 *
 *	The following are the play tone methods; PlayToneL(), PlayDMTFStringL(),
 *	PlayToneSequenceL(), and PlayFixedSequenceL().
 *
 *	@param	"TInt aError"
 *			Error code. The status of tone playback. KErrUnderflow playing of
 *			the tone is complete. KErrDied or KErrAccessDenied the sound device is in use by
 *			another higher priority client. KErrDied or KErrCancel playing of the audio
 *			sample is stopped by DevSound client another higher priority client.
 *
 */
	virtual void ToneFinished(TInt aError)=0; 

/**
 *
 *	Handles CMMFDevSound object's data request event.
 *	
 *	A derived class must provide an implementation to supply CMMFDevSound
 *	object the data that it needs to play or convert.
 *
 *	CMMFDevSound object calls this method when and where it needs data for
 *	playing or converting. The observer should notify CMMFDevSound object as
 *	quickly as possible after the data is read into buffer, aBuffer by calling
 *	PlayData(), otherwise the implementation might callback method PlayError()
 *	on derived class object with error code KErrUnderflow.
 *
 *	@param	"CMMFBuffer* aBuffer"
 *			Buffer into which data should be read. The amount of data that is
 *			needed is specified in CMMFBuffer::RequestSize().
 *
 */
	virtual void BufferToBeFilled(CMMFBuffer* aBuffer)=0;

/**
 *
 *	Handles play completion or cancel event.
 *	
 *	A derived class must provide an implementation to handle the play
 *	completion or cancel request.
 *
 *	CMMFDevSound object calls this method when an attempt to play audio sample
 *	has completed, successfully or otherwise.
 *
 *	@param	"TInt aError"
 *			Error code. The status of playback. KErrUnderflow playing of the
 *			audio sample is complete. KErrDied or KErrAccessDenied the sound device is in
 *			use by another higher priority client. KErrDied or KErrCancel playing of the
 *			audio sample is stopped by DevSound client another higher priority
 *			client.
 *
 */
	virtual void PlayError(TInt aError)=0; 

/**
 *
 *	Handles CMMFDevSound object's data request event.
 *	
 *	A derived class must provide an implementation to process the data
 *	supplied by CMMFDevSound object while recording or converting.
 *
 *	CMMFDevSound object calls this method when the buffer, aBuffer gets filled
 *	while recording or converting. The observer should notify CMMFDevSound
 *	object as quickly as possible after data in the buffer is processed by
 *	calling RecordData(), otherwise the implementation might callback
 *	method RecordError() on derived class object with error code KErrOverflow.
 *
 *	@param	"CMMFBuffer* aBuffer"
 *			Buffer containing processed (recorded or converted) data. The amount
 *			of data that is available is specified in CMMFBuffer::RequestSize().
 *
 */
	virtual void BufferToBeEmptied(CMMFBuffer* aBuffer)=0; 

/**
 *
 *	Handles record completion or cancel event.
 *	
 *	A derived class must provide an implementation to handle the record 
 *	completion or cancel request.
 *
 *	CMMFDevSound object calls this method when an attempt to record audio sample
 *	has completed, successfully or otherwise.
 *
 *	@param	"TInt aError"
 *			Error code. The status of recording. KErrOverflow audio devices
 *			runs out of internal buffer. KErrDied or KErrAccessDenied the sound device is
 *			in use by another higher priority client. KErrDied or KErrCancel recording of
 *			the audio sample is stopped by DevSound client another higher
 *			priority client.
 *
 */
	virtual void RecordError(TInt aError)=0; 

/**
 *
 *	Handles conversion completion or cancel event.
 *	
 *	A derived class must provide an implementation to handle the conversion
 *	completion or cancel request.
 *
 *	CMMFDevSound object calls this method when an attempt to convert data from
 *	source format to destination format has completed, successfully or otherwise.
 *
 *	@param	"TInt aError"
 *			Error code. KErrCancel conversion operation is cancelled. KErrNone
 *			conversion is complete. Other values are possible indicating a
 *			problem converting data.
 *
 */
	virtual void ConvertError(TInt aError)=0;

/**
 *
 *	Handles device event.
 *	
 *	A derived class must provide an implementtion to handle the messages from
 *	audio hardware device.
 *
 *	CMMFDevSound object calls this method when a message is received from the
 *	audio hardware device.
 *
 *	@param	"aMessageType"	Defines the type of message. Used to determine how to 
							interpret the contents of aMsg.
 *	@param	"aMsg"			Message that is packed in the Descriptor format.
 *
 */
	virtual void DeviceMessage(TUid aMessageType, const TDesC8& aMsg)=0;

/**
 *	Handles policy request completion event.
 *	
 *	A derived class must provide an implementation to handle the policy request
 *	completion event.
 *
 *	CMMFDevSound object calls this method when an attempt to acquire sound
 *	device is rejected by audio policy server.
 *
 *	@param	"const TMMFEvent& aEvent"
 *
 */
	virtual void SendEventToClient(const TMMFEvent& /*aEvent*/) {};

	};


/**
 *  @publishedAll
 *
 *	Class Name:	CMMFDevSound
 *
 *	This is the interface from SymbianOS to the raw audio functions on the
 *	device hardware.
 *
 *	DevSound is currently loaded as a DLL, and implements the VCR-type
 *	functions to be expected for such an interface.
 *
 *	@lib	"MMFServerBaseClasses.lib", "MMFAudioPolicyProxy.lib", "ECom.lib"
 *
 */

class CMMFDevSound : public CBase
	{
public:
/**
 *	Constructs, and returns a pointer to, a new CMMFDevSound object.
 *
 *	Leaves on failure.
 */
	IMPORT_C static CMMFDevSound* NewL();

/**
 *	Destructor.
 *
 *	Deletes all objects and releases all resource owned by this
 *	instance.
 */
	IMPORT_C ~CMMFDevSound();

/**
 *	Initializes CMMFDevSound object to play and record PCM16 raw audio data
 *	with sampling rate of 8 KHz.
 *
 *	On completion of Initialization, calls InitializeComplete() on
 *	aDevSoundObserver.
 *
 *	Leaves on failure.
 *
 *	@param	"aDevSoundObserver"
 *			A reference to DevSound Observer instance.
 */
 	IMPORT_C void InitializeL(MDevSoundObserver& aDevSoundObserver, TMMFState aMode);

/**
 *	Initializes DevSound object for the mode aMode for processing audio data
 *	with hardware device aHWDev.
 *
 *	On completion of Initialization, the observer will be notified via call back
 *	InitializeComplete().
 *
 *	Leaves on failure.
 *
 *	@param	"aDevSoundObserver"
 *			A reference to DevSound Observer instance.
 *
 *	@param	"aHWDev"
 *			CMMFHwDevice implementation identifier.
 *
 *	@param	"aMode"
 *			Mode for which this object will be used.
 */
	IMPORT_C void InitializeL(MDevSoundObserver& aDevSoundObserver, TUid aHWDev, TMMFState aMode);

/**
 *	Initializes DevSound object for the mode aMode for processing audio data
 *	using an array of Hardware devices identified by aHWDevArray identifier
 *	array. The hardware devices are chained together with data flow starting
 *	with first array element.
 *
 *	On completion of Initialization, the observer will be notified via call back
 *	InitializeComplete().
 *
 *	Leaves on failure.
 *
 *	@param	"aDevSoundObserver"
 *			A reference to DevSound Observer instance.
 *
 *	@param	"aHWDevArray"
 *			Array of CMMFHwDevice implementation identifiers.
 *
 *	@param	"aMode"
 *			Mode for which this object will be used.
 */	
	IMPORT_C void InitializeL(MDevSoundObserver& aDevSoundObserver, CArrayPtr<TUid> aHWDevArray, TMMFState aMode);

/**
 *	Initializes DevSound object for the mode aMode for processing audio data
 *	with hardware device supporting FourCC aDesiredFourCC.
 *
 *	On completion of Initialization, the observer will be notified via call back
 *	InitializeComplete().
 *
 *	Leaves on failure.
 *
 *	@param	"aDevSoundObserver"
 *			A reference to DevSound Observer instance.
 *
 *	@param	"aDesiredFourCC"
 *			CMMFHwDevice implementation FourCC.
 *
 *	@param	"aMode"
 *			Mode for which this object will be used.
 */
	IMPORT_C void InitializeL(MDevSoundObserver& aDevSoundObserver, TFourCC aDesiredFourCC, TMMFState aMode); 

/**
 *	Returns the supported Audio settings.
 *
 *	@return	"TMMFCapabilities"
 *			Device settings.
 */
	IMPORT_C TMMFCapabilities Capabilities();

/**
 *	Returns the current device configuration.
 *
 *	@return	"TMMFCapabilities"
 *			Device settings.
 */
	IMPORT_C TMMFCapabilities Config() const;

/**
 *	Configure CMMFDevSound object with the settings in aConfig.
 *
 *	Use this to set sampling rate, Encoding and Mono/Stereo.
 *
 *	@param	"aConfig"
 *			Attribute values to which CMMFDevSound object will be configured to.
 */
	IMPORT_C void SetConfigL(const TMMFCapabilities& aCaps);

/**
 *	Returns an integer representing the maximum volume device supports.
 *
 *	This is the maximum value which can be passed to CMMFDevSound::SetVolume.
 *
 *	@return	"TInt"
 *			The maximum volume. This value is platform dependent but is always
 *			greater than or equal to one.
 */
	IMPORT_C TInt MaxVolume();

/**
 *	Returns an integer representing the current volume.
 *
 *	@return	"TInt"
 *			The current volume level.
 */
	IMPORT_C TInt Volume();

/**
 *	Changes the current playback volume to a specified value.
 *
 *	The volume can be changed before or during playback and is effective
 *	immediately.
 *
 *	@param	"aVolume"
 *			The volume setting. This can be any value from zero to the value
 *			returned by a call to CMdaAudioPlayerUtility::MaxVolume(). If the
 *			volume is not within this range, the volume is automatically set to
 *			minimum or maximum value based on the value that is being passed.
 *			Setting a zero value mutes the sound. Setting the maximum value
 *			results in the loudest possible sound.
 */
	IMPORT_C void SetVolume(TInt aVolume);

/**
 *	Returns an integer representing the maximum gain device supports.
 *
 *	This is the maximum value which can be passed to CMMFDevSound::SetGain.
 *
 *	@return	"TInt"
 *			The maximum gain. This value is platform dependent but is always
 *			greater than or equal to one.
 */
	IMPORT_C TInt MaxGain();

/**
 *	Returns an integer representing the current gain.
 *
 *	@return	"TInt"
 *			The current gain level.
 */
	IMPORT_C TInt Gain();

/**
 *	Changes the current recording gain to a specified value.
 *
 *	The gain can be changed before or during recording and is effective
 *	immediately.
 *
 *	@param	"aGain"
 *			The volume setting. This can be any value from zero to the value
 *			returned by a call to CMdaAudioPlayerUtility::MaxVolume(). If the
 *			volume is not within this range, the gain is automatically set to
 *			minimum or maximum value based on the value that is being passed.
 *			Setting a zero value mutes the sound. Setting the maximum value
 *			results in the loudest possible sound.
 */
	IMPORT_C void SetGain(TInt aGain);

/**
 *	Returns the speaker balance set for playing.
 *
 *	Leaves on failure.
 *
 *	@param	"aLeftPrecentage"
 *			On return contains the left speaker volume percentage.
 *
 *	@param	"aRightPercentage"
 *			On return contains the right speaker volume percentage.
 */
	IMPORT_C void GetPlayBalanceL(TInt& aLeftPercentage, TInt& aRightPercentage);

/**
 *	Sets the speaker balance for playing.
 *
 *	The speaker balance can be changed before or during playback and is
 *	effective immediately.
 *
 *	@param	"aLeftPercentage"
 *			On return contains left speaker volume perecentage. This can be any
 *			value from zero to 100. Setting a zero value mutes the sound on left
 *			speaker.
 *
 *	@param	"aRightPercentage"
 *			On return contains right speaker volume perecentage. This can be any
 *			value from zero to 100. Setting a zero value mutes the sound on
 *			right speaker.
 */
	IMPORT_C void SetPlayBalanceL(TInt aLeftPercentage, TInt aRightPercentage);

/**
 *	Returns the microphone gain balance set for recording.
 *
 *	Leaves on failure.
 *
 *	@param	"aLeftPercentage"
 *			On return contains the left microphone gain percentage.
 *
 *	@param	"aRightPercentage"
 *			On return contains the right microphone gain percentage.
 */
	IMPORT_C void GetRecordBalanceL(TInt& aLeftPercentage, TInt& aRightPercentage);

/**
 *	Sets the microphone gain balance for recording.
 *
 *	The microphone gain balance can be changed before or during recording and
 *	is effective immediately.
 *
 *	@param	"aLeftPercentage"
 *			Left microphone gain precentage. This can be any value from zero to
 *			100. Setting a zero value mutes the gain on left microphone.
 *
 *	@param	"aRightPercentage"
 *			Right microphone gain precentage. This can be any value from zero to
 *			100. Setting a zero value mutes the gain on right microphone.
 */
	IMPORT_C void SetRecordBalanceL(TInt aLeftPercentage, TInt aRightPercentage);

/**
 *	Initializes audio device and start play process. This method queries and
 *	acquires the audio policy before initializing audio device. If there was an
 *	error during policy initialization, PlayError() method will be called on
 *	the observer with error code KErrAccessDenied, otherwise BufferToBeFilled()
 *	method will be called with a buffer reference. After reading data into the
 *	buffer reference passed, the client should call PlayData() to play data.
 *
 *	The amount of data that can be played is specified in
 *	CMMFBuffer::RequestSize(). Any data that is read into buffer beyond this
 *	size will be ignored.
 *
 *	Leaves on failure.
 */
	IMPORT_C void PlayInitL();

/**
 *	Initializes audio device and starts record process. This method queries and
 *	acquires the audio policy before initializing audio device. If there was an
 *	error during policy initialization, RecordError() method will be called on
 *	the observer with error code KErrAccessDenied, otherwise BufferToBeEmptied()
 *	method will be called with a buffer reference. This buffer contains recorded
 *	or encoded data. After processing data in the buffer reference passed, the
 *	client should call RecordData() to continue recording process.
 *
 *	The amount of data that is available is specified in
 *	CMMFBuffer::RequestSize().
 *
 *	Leaves on failure.
 */
	IMPORT_C void RecordInitL();

/**
 *	Plays data in the buffer at the current volume. The client should fill
 *	the buffer with audio data before calling this method. The Observer gets
 *	reference to buffer along with callback BufferToBeFilled(). When playing of
 *	the audio sample is complete, successfully or otherwise, the method
 *	PlayError() on observer is called.
 */
	IMPORT_C void PlayData();

/**
 *	Contine the process of recording. Once the buffer is filled with recorded
 *	data, the Observer gets reference to buffer along with callback
 *	BufferToBeEmptied(). After processing the buffer (copying over to a
 *	different buffer or writing to file) the client should call this
 *	method to continue recording process.
 */
	IMPORT_C void RecordData();

/**
 *	Stops the ongoing operation (Play, Record, TonePlay, Convert)
 */
	IMPORT_C void Stop();

/**
 *	Temporarily Stops the ongoing operation (Play, Record, TonePlay, Convert)
 */
	IMPORT_C void Pause();

/**
 *	Returns the sample recorded so far.
 *
 *	@return "TInt"
 *			Returns the samples recorded.
 */
	IMPORT_C TInt SamplesRecorded();

/**
 *	Returns the sample played so far.
 *
 *	@return "TInt"
 *			Returns the samples recorded.
 */
	IMPORT_C TInt SamplesPlayed();

/**
 *	Initializes audio device and start playing tone. Tone is played with
 *	frequency and for duration specified.
 *
 *	Leaves on failure.
 *
 *	@param	"aFrequency"
 *			Frequency at with the tone will be played.
 *
 *	@param	"aDuration"
 *			The period over which the tone will be played. A zero value causes
 *			the no tone to be played (Verify this with test app).
 */
	IMPORT_C void PlayToneL(TInt aFrequency, const TTimeIntervalMicroSeconds& aDuration);

/**
 *	Initializes audio device and start playing a dual tone. 
 *  The generated tone consists of two sine waves of different frequencies 
 *  summed together.
 *  Dual Tone is played with specified frequencies and for specified duration.
 *
 *	Leaves on failure.
 *
 *
 *	@param	"aFrequencyOne"
 *			First frequency of dual tone
 *
 *	@param	"aFrequencyTwo"
 *			Second frequency of dual tone
 *
 *	@param	"aDuration"
 *			The period over which the tone will be played. A zero value causes
 *			the no tone to be played (Verify this with test app).
 */
	IMPORT_C void PlayDualToneL(TInt aFrequencyOne, TInt aFrequencyTwo, const TTimeIntervalMicroSeconds& aDuration);

/**
 *	Initializes audio device and start playing DTMF string aDTMFString.
 *
 *	Leaves on failure.
 *
 *	@param	"aDTMFString"
 *			DTMF sequence in a descriptor.
 */
	IMPORT_C void PlayDTMFStringL(const TDesC& aDTMFString);

/**
 *	Initializes audio device and start playing tone sequence.
 *
 *	Leaves on failure.
 *
 *	@param	"aData"
 *			Tone sequence in a descriptor.
 */
	IMPORT_C void PlayToneSequenceL(const TDesC8& aData);

/**
 *	Initializes audio device and start playing the specified pre-defined tone
 *	sequence.
 *
 *	Leaves on failure.
 *
 *	@param	"aSequenceNumber"
 *			The index identifying the specific pre-defined tone sequence. Index
 *			values are relative to zero.
 *			This can be any value from zero to the value returned by a call to
 *			CMdaAudioPlayerUtility::FixedSequenceCount() - 1.
 *			The function raises a panic if sequence number is not within this
 *			range.
 */
	IMPORT_C void PlayFixedSequenceL(TInt aSequenceNumber);

/**
 *	Defines the number of times the audio is to be repeated during the tone
 *	playback operation.
 *
 *	A period of silence can follow each playing of tone. The tone playing can
 *	be repeated indefinitely.
 *
 *	@param	"aRepeatCount"
 *			The number of times the tone, together with the trailing silence,
 *			is to be repeated. If this is set to KMdaRepeatForever, then the
 *			tone, together with the trailing silence, is repeated indefinitely
 *			or until Stop() is called. If this is set to zero, then the tone is
 *			not repeated.
 * @param	"aRepeatTrailingSilence"
 *			An interval of silence which will be played after each tone.
 *			Supported only during tone playing.
 */
	IMPORT_C void SetToneRepeats(TInt aRepeatCount,
					const TTimeIntervalMicroSeconds& aRepeatTrailingSilence);

/**
 *	Defines the duration of tone on, tone off and tone pause to be used during the
 *	DTMF tone playback operation.
 *
 *	Supported only during tone playing.
 *
 *	@param	"aToneOnLength"
 *			The period over which the tone will be played. If this is set to
 *			zero, then the tone is not played.
 *
 *	@param	"aToneOffLength"
 *			The period over which the no tone will be played.
 *
 *	@param	"aPauseLength"
 *			The period over which the tone playing will be paused.
 */
	IMPORT_C void SetDTMFLengths(TTimeIntervalMicroSeconds32& aToneOnLength,
									TTimeIntervalMicroSeconds32& aToneOffLength,
									TTimeIntervalMicroSeconds32& aPauseLength);

/**
 *	Defines the period over which the volume level is to rise smoothly from
 *	nothing to the normal volume level.
 *
 *	@param	"aRampDuration"
 *			The period over which the volume is to rise. A zero value causes 
 *			the tone sample to be played at the normal level for the full
 *			duration of the playback. A value, which is longer than the duration
 *			of the tone sample, that the sample never reaches its normal
 *			volume level.
 */
	IMPORT_C void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration);

/**
 *	Defines the priority settings that should be used for this instance.
 *
 *	@param	"aPrioritySettings"
 *			An class type representing the client's priority, priority 
 *			preference and state.
 */
	IMPORT_C void SetPrioritySettings(const TMMFPrioritySettings& aPrioritySettings);

/**
 *	Initializes and starts conversion process. Once the process is initiated,
 *	observer's call back method BufferToBeFilled() is called with reference to
 *	the buffer into which source format data is to be read.
 *
 *	The maximum size of data (in bytes) that can be converted is specified in
 *	CMMFBuffer::RequestSize(). Any data that is read into buffer beyond this
 *	size will be ignored.
 *
 *	Leaves on failure.
 */
	IMPORT_C void ConvertInitL();

/**
 *	Converts the data in the buffer from source format to destination format.
 *	After the data is converted to destination format, a reference to the buffer
 *	containing data in destination format is passed in the observer call back
 *	method BufferToBeEmptied().
 *
 *	The amount of data contained in buffer is specified in
 *	CMMFBuffer::RequestSize().
 */
	IMPORT_C void ConvertData();

/**
	Retrieves a custom interface to the device.
	@param  "aInterface"	"Interface UID, defined with the custom interface."
	@return "Pointer to the interface implementation, or NULL if the device does not 
			implement the interface requested. The return value must be cast to the 
			correct type by the user."
*/
	IMPORT_C TAny* CustomInterface(TUid aInterfaceId);

/**
 *	Returns the number of available pre-defined tone sequences.
 *
 *	This is the number of fixed sequence supported by DevSound by default.
 *
 *	@return	"TInt"
 *			The fixed sequence count. This value is implementation dependent
 *			but is always greater than or equal to zero.
 */
	IMPORT_C TInt FixedSequenceCount();

/**
 *	Returns the name assigned to a specific pre-defined tone sequence.
 *
 *	This is the number of fixed sequence supported by DevSound by default.
 *
 *	The function raises a panic if sequence number specified invalid.
 *
 *	@return	"TDesC&"
 *			A reference to a Descriptor containing the fixed sequence
 *			name indexed by aSequenceNumber.
 *
 *	@param	"aSequenceNumber"
 *			The index identifying the specific pre-defined tone sequence. Index
 *			values are relative to zero.
 *			This can be any value from zero to the value returned by a call to
 *			CMdaAudioPlayerUtility::FixedSequenceCount() - 1.
 *			The function raises a panic if sequence number is not within this
 *			range.
 */
	IMPORT_C const TDesC& FixedSequenceName(TInt aSequenceNumber);

/**
 *	Returns a list of the supported input datatypes that can be sent to DevSound for
 *  playing audio.  The datatypes returned are those that the DevSound
 *  supports given the priority settings passed in aPrioritySettings
 *
 *	@param  "aSupportedDataTypes"
 *			The array of supported data types that will be filled in by this method. 
 *			The supported datatypes of the DevSound are in the form of an array 
 *			of TFourCC codes.
 *			Any existing entries in the array will be overwritten on calling this method.
 *			If no supported datatypes are found given the priority settings, then
 *			the aSupportedDatatypes array will have zero entries.
 *
 *	@param	"aPrioritySettings"
 *			The priority settings used to determine the supported datatypes.  Note this
 *			does not set the priority settings.  For input datatypes the iState member
 *			of the priority settings would expected to be either 
 *			EMMFStatePlaying or EMMFStatePlayingRecording.  The priority settings may
 *			effect the supported datatypes depending on the audio routing
 *
 *	@leave  Leave on failure with standard Symbian OS error code.  Note that if no supported
 *			data types are found this does not constitute failure, the method will return
 *			normally with no entries in aSupportedDataTypes
 *			
 */
	IMPORT_C void GetSupportedInputDataTypesL(RArray<TFourCC>& aSupportedDataTypes, const TMMFPrioritySettings& aPrioritySettings) const;


/**
 *	Returns a list of the supported output datatypes that can be received from DevSound for
 *  recording audio.  The datatypes returned are those that the DevSound
 *  supports given the priority settings passed in aPrioritySettings
 *
 *	@param  "aSupportedDataTypes"
 *			The array of supported data types that will be filled in by this method. 
 *			The supported datatypes of the DevSound are in the form of an array 
 *			of TFourCC codes.
 *			Any existing entries in the array will be overwritten on calling this method.
 *			If no supported datatypes are found given the priority settings, then
 *			the aSupportedDatatypes array will have zero entries.
 *
 *	@param	"aPrioritySettings"
 *			The priority settings used to determine the supported datatypes.  Note this
 *			does not set the priority settings.  For output datatypes the iState member
 *			of the priority settings would expected to be either 
 *			EMMFStateRecording or EMMFStatePlayingRecording.  The priority settings may
 *			effect the supported datatypes depending on the audio routing
 *
 *	@leave  Leave on failure with standard Symbian OS error code.  Note that if no supported
 *			data types are found this does not constitute failure, the method will return
 *			normally with no entries in aSupportedDataTypes
 *			
 */
	IMPORT_C void GetSupportedOutputDataTypesL(RArray<TFourCC>& aSupportedDataTypes, const TMMFPrioritySettings& aPrioritySettings) const;
protected:
/**
 *	Default Constructor.
 *  So that nobody can extend derive from CMMFDevSound
 */
	CMMFDevSound();
/**
 *	Second phase constructor.
 */
	void ConstructL();

// body
	class CBody;
	CBody* iBody;
};

#endif // __SOUNDDEVICE_H__
