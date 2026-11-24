// MDASOUND.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
Opens a handle to the sound driver.

The Open() method completes with KErrInUse should another client have the sound driver open. If the client
has already opened the sound driver then this method will return with KErrAlreadyExists. If the sound driver
has not already been opened either by the calling client or another client and is opened successfully then
this method returns with KErrNone.

@param  aUnit

*/
inline TInt RMdaDevSound::Open(TInt aUnit)
#ifndef __SECURE_API__
	{const TPtrC8 name = MDADEVSOUNDNAME; return DoCreate(_L("Sound"),VersionRequired(),NULL,aUnit,NULL,&name);}
#else
	{const TPtrC8 name = MDADEVSOUNDNAME; return DoCreate(_L("Sound"),VersionRequired(),aUnit,NULL,&name);}
#endif

/**
Returns the TVersion of the device.

@return The device TVersion.
*/
inline TVersion RMdaDevSound::VersionRequired() const
	{return TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber);}

/**

*/
inline TInt RMdaDevSound::IsMdaSound()
	{return DoControl(EMdaControlIsMdaSound);}

/**
Gets the capabilities of the sound driver.

Once the function returns, the supplied parameter aFormatsSupported provides the supported capabilities of
the sound driver with respect to data types supported, max buffer size, sample rate and stereo/mono capabilities.

Note:
'Format' referred to within the context of the sound driver API is different from the 'format' referred to
within MMF.

@param  aFormatsSupported
		The information detailing what sound formats are supported.
*/
inline void RMdaDevSound::PlayFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported)
	{DoControl(EMdaControlPlayFormatsSupported,(TAny*)&aFormatsSupported);}

/**
Gets the current play 'format' of the sound driver.

The play format is returned in the TCurrentSoundFormat structure.

Note:
'Format' here refers to the sound device definition of 'format' not the MMF definition.

@param  aFormat
        The current sound driver play 'format'.

@see    SetPlayFormat
@see    PlayFormatsSupported
*/
inline void RMdaDevSound::GetPlayFormat(TCurrentSoundFormatBuf& aFormat)
	{DoControl(EMdaControlGetPlayFormat,(TAny*)&aFormat);}

/**
Configures the sound driver settings for audio playback.

@param  aFormat
		The sound driver 'format' settings.

@see    GetPlayFormat
@see    PlayFormatsSupported
*/
inline TInt RMdaDevSound::SetPlayFormat(const TCurrentSoundFormatBuf& aFormat)
	{return DoSvControl(EMdaControlSetPlayFormat,(TAny*)&aFormat);}

/**
Returns the current play volume.

@return The play volume.

@see SetPlayVolume
*/
inline TInt RMdaDevSound::PlayVolume()
	{return DoControl(EMdaControlGetPlayVolume);}

/**
Sets the play volume.

Use PlayFormatSupported() to get the volume range.

The volume is not a fixed value and the client should not make assumptions about the allowable volume
range.

@param  aVolume
        The play volume to set.

@see PlayVolume
*/
inline void RMdaDevSound::SetPlayVolume(TInt aVolume)
	{DoControl(EMdaControlSetPlayVolume,(TAny*)aVolume);}

/**
Causes the sound driver to play the audio data contained in aData.

The data is buffered internally in the sound driver and the sound driver may already be playing audio 
when this method is called.  The sound driver should complete the TRequestStatus when it has finished processing
the audio data contained in aData. 

Signalled completion informs the client of RMdaDevSound that:
- It can repopulate the buffer with new audio data.
- The sound driver is ready to accept another buffer of audio data via a further call to PlayData().

The TRequestStatus should be set to KErrNone unless the request has been cancelled via CancelPlayData() in
which case the status will be set to KErrCancel.

The TRequestStatus should be completed as soon as possible and certainly before the audio has been physically played 
in order for the client to send further audio buffers before the buffers already in the sound driver are played out
(which would result in a KErrUnderflow).  In order to achieve this, the sound driver should be at least double buffer
the audio internally. Prior to calling PlayData() the client would be expected to configure the sound driver via 
SetPlayFormat() and register with the sound driver that it requires notification of error conditions via a call 
to NotifyPlayError().

@param  aStatus
        The status request parameter.
@param  aData
        The audio data to be played. The data is not owned or created by the sound driver but is owned by the client.
*/
inline void RMdaDevSound::PlayData(TRequestStatus& aStatus,const TDesC8& aData)
	{DoRequest(EMdaRequestPlayData,aStatus,(TAny*)&aData);}

/**
Cancels the current request for PlayData() if currently active.

The currently active PlayData() should complete the request status immediately with KErrCancel.
*/
inline void RMdaDevSound::CancelPlayData()
	{DoCancel(1 << EMdaRequestPlayData);}

/**
Requests notification of an error that occurs during playback.

The TRequestStatus passed in the NotifyPlayError() method is separate to the TRequestStatus passed
into the PlayData() method, and hence the client would typically have a separate active object for
both the PlayData() and NotifyPlayError() TRequestStatuses.  The NotifyPlayError() method is required
because if an error occurs during playback, the PlayData() TRequestStatus may not be active.

Note:
A call to CancelPlayData() should complete the PlayData() request status with KErrCancel and should not
complete the NotifyPlayError() TRequestStatus.

@param  aStatus
        The status request parameter.
*/
inline void RMdaDevSound::NotifyPlayError(TRequestStatus& aStatus)
	{DoRequest(EMdaRequestPlayErrorNotification,aStatus);}

/**
Cancels the NotifyPlayError() TRequestStatus if currently active.

The TRequestStatus should complete immediately with KErrCancel.
*/
inline void RMdaDevSound::CancelNotifyPlayError()
	{DoCancel(1 << EMdaRequestPlayErrorNotification);}

/**
Gets the recording capabilities of the sound driver.

The sound driver recording capabilites relate to data types supported, max buffer size, sample rate and
stereo/mono capabilities.

@param  aFormatsSupported
        A structure detailing the capabilities of the recording sound driver.
*/
inline void RMdaDevSound::RecordFormatsSupported(TSoundFormatsSupportedBuf& aFormatsSupported)
	{DoControl(EMdaControlRecordFormatsSupported,(TAny*)&aFormatsSupported);}

/**
Returns the current record 'format' of the sound driver.

As with RecordFormatsSupported(), 'format' here refers to the sound device definition of 'format' not the MMF definition.

@param  aFormat
        The format buffer containing the current sound driver record settings.

@see SetRecordFormat
@see RecordFormatsSupported
*/
inline void RMdaDevSound::GetRecordFormat(TCurrentSoundFormatBuf& aFormat)
	{DoControl(EMdaControlGetRecordFormat,(TAny*)&aFormat);}

/**
Configures the sound driver settings for audio recording.

Settings used should not be outside the ranges by GetRecordFormat

@param  aFormat
        The format buffer containing the sound driver record settings.

@see GetRecordFormat
@see RecordFormatsSupported
*/
inline TInt RMdaDevSound::SetRecordFormat(const TCurrentSoundFormatBuf& aFormat)
	{return DoSvControl(EMdaControlSetRecordFormat,(TAny*)&aFormat);}

/**
Returns the current gain setting.

@return The current gain setting.
*/
inline TInt RMdaDevSound::RecordLevel()
	{return DoControl(EMdaControlGetRecordLevel);}

/**
Sets the record gain to the specified level.

The client needs to call RecordFormatsSupported() to get the gain range. This is not a fixed value and
the client should not make assumptions about the allowable volume range.

@param  aLevel
        The level at which to set the record gain.
*/
inline void RMdaDevSound::SetRecordLevel(TInt aLevel)
	{DoControl(EMdaControlSetRecordLevel,(TAny*)aLevel);}

/**
Causes the sound driver to record audio data into the aData buffer.

The sound driver completes the TRequestStatus when it has recorded a complete buffer of audio data into
aData, ie aData is filled to its max length.  The sound driver should continue recording, buffering the audio
data internally after the TRequestStatus has been completed. i.e. the sound driver should be at least double
buffered internally.

The TRequestStatus is set to KErrNone unless the request has been cancelled via CancelRecordData() in which case
the status will be set to KErrCancel.

On completion of the TRequestStatus the client can assume that the aData buffer contains valid recorded audio
data and that once the client has handled the data it can reuse the same buffer to request further recorded data
from the sound driver via subsequent calls to RecordData().

Prior to calling RecordData() the client would be expected to configure the sound driver via SetRecordFormat() and
register with the sound driver that it requires notification of error conditions via a call to NotifyRecordError().

@param  aStatus
        The status request parameter.
@param  aData
        The buffer to be used for audio recording.
*/
inline void RMdaDevSound::RecordData(TRequestStatus& aStatus,TDes8& aData)
	{DoRequest(EMdaRequestRecordData,aStatus,(TAny*)&aData);}

/**
Cancels the current request for RecordData() if currently active.

The currently active RecordData() should complete the request status immediately with KErrCancel.
*/
inline void RMdaDevSound::CancelRecordData()
	{DoCancel(1 << EMdaRequestRecordData);}

/**
Requests notification of an error that occurs during recording.

Since the TRequestStatus is not the same TRequestStatus as that passed in the RecordData() method, the client
would typically have a separate active object to handle each of the TRequestStatuses.

NotifyRecordError() is required as a record error can occur even if no RecordData() TRequestStatus is active.

Note:
A call to CancelRecordData() should complete the RecordData() TRequestStatus with KErrCancel and not the
NotifyRecordError() TRequestStatus.

An example of an error occurring during recording would be if the client does not call RecordData() sufficiently
fast enough such that the sound drivers internal audio buffer becomes full and cannot be filled with further
recorded data. This would cause the NotifyRecordError() TRequestStatus to complete with KErrOverflow.

@param  aStatus
		The status request parameter.
*/
inline void RMdaDevSound::NotifyRecordError(TRequestStatus& aStatus)
	{DoRequest(EMdaRequestRecordErrorNotification,aStatus);}

/**
Cancels the NotifyRecordError() TRequestStatus if currently active.

The TRequestStatus should complete immediately with KErrCancel.
*/
inline void RMdaDevSound::CancelNotifyRecordError()
	{DoCancel(1 << EMdaRequestRecordErrorNotification);}

/**
Flushes all internally buffered audio.

This method should not complete any pending TRequestStatuses.
*/
inline void RMdaDevSound::FlushPlayBuffer()
	{DoControl(EMdaControlFlushPlayBuffer);}

/**
Stops further audio recording.

Since recorded audio data may be buffered internally in the sound driver, this function does not immediately
delete the internally buffered audio data. Instead, it allows the client to continue to call RecordData() and
acknowledge the RecordData() TRequestStatus.

The buffer filled on completion of the RecordData() TRequestStatus will contain the internally buffered audio
that was recorded prior to calling FlushRecordBuffer().

The client can know when all the internally buffered recorded data has been flushed when the RecordData() TRequestStatus
has been completed and the buffer that was passed into RecordData() has less than the MaxLength() bytes of data.  In 
most drivers, the length would be 0 as the sound driver deals in complete buffers, but the client should assume 
less than MaxLength as a clever driver could stop recording immediately when FlushRecordBuffer() is called i.e. in 
mid buffer.  

The sound driver does not record any new audio data after a call to FlushRecordBuffer().
*/
inline void RMdaDevSound::FlushRecordBuffer()
	{DoControl(EMdaControlFlushRecordBuffer);}

/**
Returns the total number of bytes played by the sound driver.

It is generally updated after each buffer has been played ie if BytesPlayed() is called mid buffer then 
the value returned will not be exact but will be to the nearest buffer.

Note:
If the buffer is paused via PausePlayBuffer() then the bytes played may be rounded up to the buffer that was
currently being played when the pause occurred. The BytesPlayed are not reset to 0 on an error condition. They
must be explicitly reset via a call to ResetBytesPlayed().

@return The number of bytes played.
*/
inline TInt RMdaDevSound::BytesPlayed()
	{return DoControl(EMdaControlBytesPlayed);}

/**
Resets the number of bytes played to 0.
*/
inline void RMdaDevSound::ResetBytesPlayed()
	{DoControl(EMdaControlResetBytesPlayed);}

/**
Immediately halts the playing of the audio in mid buffer.

If the TRequestStatus from the previous PlayData() is outstanding then PausePlayBuffer() does not complete
the TRequestStatus.  The TRequestStatus will only be completed after ResumePlaying() is called.
*/
inline void RMdaDevSound::PausePlayBuffer()
	{DoControl(EMdaControlPausePlayBuffer);}

/**
Resumes playing from the exact point where playing was halted from the previous call to PausePlayBuffer().

The next TRequestStatus (if active) to be completed, is the request status from the previous PlayData() prior
to calling PausePlayBuffer(). If PausePlayBuffer() has not been called prior to ResumePlaying(), then this method
does nothing.  If ResumePlaying() is called and the buffer underflows because no further calls to PlayData() occur 
and no PlayData() TRequestStatus is pending then the NotifyPlayError() TRequestStatus should complete with KErrUnderflow 
if enabled.
*/
inline void RMdaDevSound::ResumePlaying()
	{DoControl(EMdaControlResumePlaying);}
