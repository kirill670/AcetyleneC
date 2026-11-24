// MDASOUND.H
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __MDASOUND_H__
#define __MDASOUND_H__

#ifndef __E32VER_H__
#include <e32ver.h>
#endif

#define MDADEVSOUNDNAME _L8("RMdaDevSound")

/**
@publishedPartner
@released

User side API to the reference Symbian sound driver as used on WINS and the reference
hardware platform.
Note that this API is used internally within the Symbian reference CMMFDevSound/CMMFHwDevices.
As such, within Devsound, Licensees are free to access their own audio hardware as they see fit, ie there is no
need for a Licensee DevSound implementation to have to use this API.  

*/
class RMdaDevSound : public RBusLogicalChannel
	{
public:
	/** 
	Sound driver version number
	*/
	enum TVer
		{
		/** Major Version Number
		*/
		EMajorVersionNumber=1,
		/** Minor Version Number
		*/
		EMinorVersionNumber=0,
		/** Major Version Number
		*/
		EBuildVersionNumber=KE32BuildVersionNumber
		};
	/**
	Request command enumeration referenced by Sound LDD
	*/
	enum TMdaRequest
		{
		/** PlayData
		*/
		EMdaRequestPlayData,
		/** NotifyPlayError
		*/
		EMdaRequestPlayErrorNotification,
		/** RecordData
		*/
		EMdaRequestRecordData,
		/** NotifyRecordError
		*/
		EMdaRequestRecordErrorNotification
		};
		
	/**
	Control command enumeration referenced by Sound LDD
	*/
	enum TMdaControl
		{
		/** PlayFormatsSupported
		*/
		EMdaControlPlayFormatsSupported,
		/** GetPlayFormat
		*/
		EMdaControlGetPlayFormat,
		/** SetPlayFormat
		*/
		EMdaControlSetPlayFormat,
		/** GetPlayVolume
		*/
		EMdaControlGetPlayVolume,
		/** SetPlayVolume
		*/
		EMdaControlSetPlayVolume,
		/** RecordFormatsSupported
		*/
		EMdaControlRecordFormatsSupported,
		/** GetRecordFormat
		*/
		EMdaControlGetRecordFormat,
		/** SetRecordFormat
		*/
		EMdaControlSetRecordFormat,
		/** GetRecordLevel
		*/
		EMdaControlGetRecordLevel,
		/** SetRecordLevel
		*/
		EMdaControlSetRecordLevel,
		/** FlushPlayBuffer
		*/
		EMdaControlFlushPlayBuffer,
		/** FlushRecordBuffer
		*/
		EMdaControlFlushRecordBuffer,
		/** BytesPlayed
		*/
		EMdaControlBytesPlayed,
		/** ResetBytesPlayed
		*/
		EMdaControlResetBytesPlayed,
		/** IsMdaSound
		*/
		EMdaControlIsMdaSound,
		/** PausePlayBuffer
		*/
		EMdaControlPausePlayBuffer,
		/** ResumePlaying
		*/
		EMdaControlResumePlaying
		};

	/**
	The data types of the audio data that the sound driver can accept. Normally signed 16 bit PCM data would be sent to
	the sound driver, however the driver can also accept 8 bit PCM, ALaw and MuLaw data types.
	*/
	enum TMdaSoundEncoding
		{
		/** 8 bit PCM audio data.
		*/
		EMdaSoundEncoding8BitPCM		= 0x00000001,
		/** 16 bit PCM audio data.
		*/
		EMdaSoundEncoding16BitPCM		= 0x00000002,
		/** 8 bit ALaw audio data.
		*/
		EMdaSoundEncoding8BitALaw		= 0x00000004,
		/** 8 bit MuLaw audio data.
		*/
		EMdaSoundEncoding8BitMuLaw		= 0x00000008,
		};

	/**
	@publishedPartner
	@released

	Used to report the capabilities of the sound driver.

	@see PlayFormatsSupported
	@see RecordFormatsSupported
	*/
	class TSoundFormatsSupported
		{
	public:

		/** The minimum sample rate supported.
		*/
		TInt iMinRate;

		/** The maximum sample rate supported.
		*/
		TInt iMaxRate;

		/** The types of audio data the sounds driver can handle.
		*/
		TUint32 iEncodings;

		/** The maximum number of channels supported (1=mono, 2=stereo).
		*/
		TInt iChannels;

		/** The mimimum buffer size that can be played/recorded by the sound driver using PlayData() and
		RecordData() respectively.
		*/
		TInt iMinBufferSize;

		/** The maximum buffer size that can be played/recorded by the sound driver using PlayData() and
		RecordData() respectively.
		*/
		TInt iMaxBufferSize;

		/** The minimum volume/gain supported by the sound driver. SetPlayVolume() and SetRecordLevel() should not
		set values less than this.
		*/
		TInt iMinVolume;

		/** The maximum volume/gain supported by the sound driver. SetPlayVolume() and SetRecordLevel() should not set
		values greater than this.
		*/
		TInt iMaxVolume;
		};

	/** Packaged TSoundFormatsSupported buffer.

	@see TSoundFormatsSupported
	@see PlayFormatsSupported
	@see RecordFormatsSupported
	*/
	typedef TPckgBuf<TSoundFormatsSupported> TSoundFormatsSupportedBuf;

	/**
	@publishedPartner
	@released

	Used to report the current play/record 'format' of the sound driver.

	Note:
	'Format' here refers to the sound device definition of 'format' not the MMF definition.

	@see GetPlayFormat
	@see SetPlayFormat
	@see GetRecordFormat
	@see SetRecordFormat
	*/
	class TCurrentSoundFormat
		{
	public:

		/** The current sample rate.
		*/
		TInt iRate;

		/** The audio data type the sound driver is currently configured to accept.
		Note that TMdaSoundEncoding is the 'data type' the sound driver is currently configured to accept.
		Only pcm16 data will be sent to the sound driver.
		The WINS EKA1 sound driver can accept other data types such as 8 bit pcm8 aLaw and MuLaw
		but these are not required.  There is no need to implement pcm8, aLaw and uLaw support.
		*/
		TMdaSoundEncoding iEncoding;

		/** The current number of channels (1=mono, 2=stereo).
		*/
		TInt iChannels;

		/** The current buffer size.
		*/
		TInt iBufferSize;
		};

	/** Packaged TCurrentSoundFormat buffer.

	@see TCurrentSoundFormat
	@see GetPlayFormat
	@see SetPlayFormat
	@see GetRecordFormat
	@see SetRecordFormat
	*/
	typedef TPckgBuf<TCurrentSoundFormat> TCurrentSoundFormatBuf;
public:
	/**
	Method to open a handle to the sound driver.
	On the reference hardware only one client can have the sound driver open at any one time.
	Since the record and play APIs are on the same sound driver API it also implies that if
	one client wishes to play audio, then another client cannot simultaneously record audio. 

	@param aUnit  This function should not take any parameters.  
	The KNullUnit being used to set the RBusLogicalChannels DoCreate() unit of the device.
		
	@return	Symbian standard error code.  The Open() method completes with KErrInUse should an 
	instance of the sound driver be already open.  
	If the sound driver has not already been opened either by the calling client or another client and is
	opened successfully then this method returns with KErrNone .
	*/	
	inline TInt Open(TInt aUnit=KNullUnit);
	
	/**
	Returns the TVersion of the device.
	
	@return TVersion of the device
	*/
	inline TVersion VersionRequired() const;
	
	/** 
	This sound driver is not a MdaSound driver so this method will return false
	
	@return false ie 0
	*/
	inline TInt IsMdaSound();

	/**
	This function provides the capabilities of the sound driver.
	Note the function name is somewhat misleading since 'format' has a specific meaning within the MMF.
	'Format' within the context of the sound driver API refers to the capabilities of the sound driver
	with respect to data types supported , max buffer size, sample rate and stereo/mono capabilities.
	
	@param aFormatsSupported TSoundFormatsSupported structure has written into it the supported capabilities
	*/
	inline void PlayFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported);
	
	/**
	This method returns the current play 'format' of the sound driver.
	As with PlayFormatsSupported() 'format' here refers to the sound device definition of 'format'
	not the MMF definition.
	
	@param aFormat The play format is returned in the TCurrentSoundFormatBuf.
	*/
	inline void GetPlayFormat(TCurrentSoundFormatBuf& aFormat);
	
	/**
	This method configures the sound driver settings for audio playback.
	The configuration data is set in the TCurrentSoundFormatBuf the structure of which is as defined in GetPlayFormat().
	
	@param aFormat The play format to be set
	*/
	inline TInt SetPlayFormat(const TCurrentSoundFormatBuf& aFormat);
	
	/**
	Gets the current volume.
	
	@return The current volume
	*/
	inline TInt PlayVolume();
	
	/**
	Sets the play volume.  The client should call PlayFormatsSupported()  to get volume range.
	This is not a fixed value and the client should not make assumptions about the allowable volume range.
	For EAK1 reference sound drivers the maximum volume is 65535 but the software using this API should not
	assume that is the case.
	
	@param aVolume The volume to be set
	*/
	inline void SetPlayVolume(TInt aVolume);
	
	/**
	This function causes the sound driver to play the audio data contained in aData.
	The data is buffered internally in the sound driver and the sound driver may already be playing audio
	when this method is called.
	The sound driver completes the TRequestStatus when it has finished with the audio data contained in aData.  
	By 'finished' this does not mean finished as in physically finished playing the audio,
	but to inform the client of RMdaDevSound that:
	a)	it can repopulate the buffer with new audio data.
	b)	 the sound driver is ready to accept another buffer of audio data via a further call to PlayData()
	(ie the sound driver is not expected to accept multiple buffers in succession prior to completing their
	TRequestStatus as this would not provide the client with any indication of whether the
	sound drivers internal buffers are full).

	@param aStatus  The TRequestStatus completed when the sound driver has finished with the audio data contained in aData.
	The TRequestStatus is set to KErrNone unless the request has been cancelled via CancelPlayData()
	in which case the status will be set to KErrCancel. 
	The TRequestStatus is completed as soon as possible and before the audio has been physically played
	in order for the client to send further audio buffers before the buffers already in the sound driver
	are played out (which would result in a KErrUnderflow). 
	Prior to calling PlayData() the client would be expected to configure the sound driver via SetPlayFormat()
	and register with the sound driver that it requires notification of error conditions via a call to NotifyPlayError().
	
	@param aData  Buffer containing the audio data to be played.  
	aData, is not owned or created by the sound driver but is owned by the client.  
	If the EKA2 sound driver were to be modified at a later stage to use shared IO buffers
	then the buffer ownership would belong with the sound driver which would necessitate an API change.
	*/
	inline void PlayData(TRequestStatus& aStatus,const TDesC8& aData);
	
	/**
	Cancels the current request for PlayData() if currently active.
	The currently active PlayData() should complete the request status immediately with KErrCancel.
	*/
	inline void CancelPlayData();
	
	/**
	This function is used when the client is requesting notification of an error that occurs during playback.
	The TRequestStatus passed in the NotifyPlayError() method is separate to the TRequestStatus passed into the PlayData() method,
	and hence the client would typically have a separate active object for both the PlayData()
	and NotifyPlayError() TRequestStatuses.
	The NotifyPlayError() method is required because if an error occurs during playback,
	the PlayData() TRequestStatus may not be active.
	If a PlayData() request status is active then the error is reported back via the PlayData()
	TRequestStatus and not via the NotifyPlayError() TRequestStatus.
	If no PlayData() TRequestStatus is active then the error is reported back by completing the NotifyPlayError()
	TRequestStatus with the appropriate error code.
	Note that a call to CancelPlayData() should complete the PlayData() request status with KErrCancel
	and should not complete the NotifyPlayError() TRequestStatus.
	
	aParam aStatus TRequestStatus completed when a play error occurs.
	*/
	inline void NotifyPlayError(TRequestStatus& aStatus);
	
	/**
	Cancels the NotifyPlayError() TRequestStatus if currently active.
	The TRequestStatus completes immediately with KErrCancel.
	*/
	inline void CancelNotifyPlayError();

	/**
	This method provides the capabilities of the sound driver when recording.
	The method name is somewhat misleading since 'format' has a specific meaning within the MMF.
	'Format' within the context of the sound driver API  does not refer to a 'format' as used in the MMF
	but refers to the capabilities of the sound driver with respect to
	data types supported , max buffer size, sample rate and stereo/mono capabilities.
	
	@param aFormatsSupported TSoundFormatsSupported structure has written into it the supported capabilities
	*/
	inline void RecordFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported);
	
	/**
	This method returns the current record 'format' of the sound driver.
	As with RecordFormatsSupported() 'format' here refers to the sound device definition of 'format'
	not the MMF definition.
	
	@param aFormat The record format is returned in the TCurrentSoundFormatBuf.
	*/
	inline void GetRecordFormat(TCurrentSoundFormatBuf& aFormat);
	
	/**
	This method configures the sound driver settings for audio record.
	The configuration data is set in the TCurrentSoundFormatBuf the structure of which is as defined in GetRecordFormat().
	
	@param aFormat The record format to be set
	*/
	inline TInt SetRecordFormat(const TCurrentSoundFormatBuf& aFormat);
	
	/**
	Returns the current gain setting.
	
	@return The current gain setting
	*/
	inline TInt RecordLevel();
	
	/**
	Sets the record gain.
	The client needs to call RecordFormatsSupported()  to get the gain range. 
	This is not a fixed value and the client should not make assumptions about the allowable volume range.
	For EKA1 reference sound drivers the maximum gain is 255.
	
	@param aLevel The required gain
	*/
	inline void SetRecordLevel(TInt aLevel);
	
	/**
	This function causes the sound driver to record audio data into the aData buffer. 
	The sound driver completes the TRequestStatus when it has recorded a complete buffer of audio data into aData,
	ie aData is filled to its max length.
	The sound driver continues recording, buffering the audio data internally after the TRequestStatus
	has been completed.
	Prior to calling RecordData() the client would be expected to configure the sound driver via SetRecordFormat()
	and register with the sound driver that it requires notification of error conditions via a call to 
	NotifyRecordError().
	
	@param aStatus The TRequestStatus, set to KErrNone unless the request has been cancelled via CancelRecordData()
	in which case the status will be set to KErrCancel. 
	On completion of the TRequestStatus the client can assume that the aData buffer contains valid recorded audio data
	and that once the client has handled the data it can reuse the same buffer
	to request further recorded data from the sound driver via subsequent calls to RecordData().

	@param aData Descriptor containing the recorded data
	*/
	inline void RecordData(TRequestStatus& aStatus,TDes8& aData);
	
	/**
	Cancels the current request for RecordData() if currently active.
	The currently active RecordData() should complete the request status immediately with KErrCancel.
	*/
	inline void CancelRecordData();
	
	/**
	This function is used when the client is requesting notification of an error that occurs during recording.
	Since the TRequestStatus is not the same TRequestStatus as that passed in the RecordData() method,
	the client would typically have a separate active object to handle each of the TRequestStatuses.
	NotifyRecordError() is required as a record error can occur even if no RecordData() TRequestStatus is active.
	When an error occurs during recording the NotifyRecordError() TRequestStatus should complete
	with the error when RecordData() TRequestStatus is inactive.
	If a RecordData TRequestStatus is also active then the error should be reported via the RecordData()
	TRequestStatus and not the NotifyRecordError() TRequestStatus.
	A call to CancelRecordData() should complete the RecordData() TRequestStatus with KErrCancel and not
	the NotifyRecordError() TRequestStatus.

	An example of an error occurring during recording would be if the client does not call RecordData()
 	sufficiently fast enough such that the sound drivers internal audio buffer becomes full and cannot be
 	filled with further recorded data.  This would cause the NotifyRecordError() TRequestStatus to complete
 	with KErrOverflow.
 	
 	@param aStatus TRequestStatus completed when a record error occurs.
	*/
	inline void NotifyRecordError(TRequestStatus& aStatus);
	
	/**
	Cancels the NotifyRecordError() TRequestStatus if currently active.
	The TRequestStatus completes immediately with KErrCancel.
	*/
	inline void CancelNotifyRecordError();

	/**
	Used to clear all internally buffered audio.  This method does not complete any pending TRequestStatuses.  
	*/
	inline void FlushPlayBuffer();
	
	
	inline void FlushRecordBuffer();
	
	/**
	Returns the total number of bytes played by the sound driver.
	It is generally updated after each buffer has been played ie if BytesPlayed()
	is called mid buffer then the value returned will not be exact but will be to the nearest buffer.
	Note that if the buffer is paused via PausePlayBuffer() then this method returns the number of bytes
	played at the Pause() ie in mid buffer.
 	The BytesPlayed are not reset to 0 on an error condition.
 	They must be explicitly reset via a call to ResetBytesPlayed().
 	
 	@param The number of bytes played
 	*/
	inline TInt BytesPlayed();
	
	/**
	Resets bytes played to 0.
	*/
	inline void ResetBytesPlayed();
	
	/**
	This halts the playing of the audio in mid buffer.
	The bytes played reflects the bytes of audio played even if in mid buffer.
	If the TRequestStatus from the previous PlayData() is outstanding then PausePlayBuffer()
	does not complete the TRequestStatus.
	The TRequestStatus will only be completed after ResumePlaying() is called.
	*/
	inline void PausePlayBuffer();
	
	/**
	This resumes playing from the exact point where playing was halted from the previous call to PausePlayBuffer().
	The next TRequestStatus (if active) to be completed, is the request status from the previous PlayData()
	prior to calling PausePlayBuffer().
	If PausePlayBuffer() has not been called prior to ResumePlaying(),
	then this method does nothing.
	If ResumePlaying() is called and the buffer underflows because no further calls to PlayData() occur
	and no PlayData() TRequestStatus is pending then the NotifyPlayError() TRequestStatus should complete
	with KErrUnderflow if enabled.
	*/
	inline void ResumePlaying();
	};

#include "mdasound.inl"

#endif

