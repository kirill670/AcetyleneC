// include\mmf\common\mmfpaniccodes.h
//
// Copyright  2002 Symbian Ltd. All rights reserved.
//
#ifndef __MMF_COMMON_PANICCODES_H__
#define __MMF_COMMON_PANICCODES_H__

//Multimedia Framework Panic Codes

/** 
 * @publishedAll
 *
 * Panic codes for CMMFAudioInput
 */
enum TMMFAudioInputPanicCode
	{
	/**
	 * panic in MMMFAudioInput::NewAudioInputL() if ImplementationUid!=KUidMmfAudioInput
	 */	
	EMMFAudioInputPanicBadUID = 1,
	/**
	 * MDevSoundObserver::ToneFinished() was called but not implemented
	 */
	EMMFAudioInputPanicToneFinishedNotSupported,
	/**
	 * MDevSoundObserver::BufferToBeFilled() was called but not implemented
	 */
	EMMFAudioInputPanicPlayerDataUsedNotSupported,
	/**
	 * MDevSoundObserver::PlayError() was called but not implemented
	 */
	EMMFAudioInputPanicPlayErrorNotSupported,
	/**
	 * panic if CMMFAudioInput::DevSound not loaded
	 */
	EMMFAudioInputDevSoundNotLoaded
	};

/** 
 * @publishedAll
 *
 * Panic codes for CMMFAudioOutput
 */
enum TMMFAudioOutputPanicCode 
	{
	/**
	 * panic in MMMFAudioOutput::NewAudioInputL() if ImplementationUid!=KUidMmfAudioInput
	 */
	EMMFAudioOutputPanicBadUID = 1,
	/**
	 * MMMFAudioOutput::BufferFilledL() was called but not implemented
	 */
	EMMFAudioOutputPanicBufferFilledLNotSupported,
	/**
	 * MMMFAudioOutput::ToneFinished() was called but not implemented
	 */
	EMMFAudioOutputPanicToneFinishedNotSupported,

	EMMFAudioOutputPanicRecordDataFilledNotSupported,
	/**
	 * MMMFAudioOutput::RecordError() was called but not implemented
	 */
	EMMFAudioOutputPanicRecordErrorNotSupported,
	/**
	 * panic if CMMFAudioOutput::iMMFDevSound is NULL
	 */
	EMMFAudioOutputDevSoundNotLoaded
	};

/**
 * @publishedAll
 *
 * Panic codes for CMMFDescriptor
 */
enum TMMFDescriptorPanicCode
	{
	/**
	 * MDataSource::BufferEmptiedL() was called but not implemented
	 */
	EMMFDescriptorPanicBufferEmptiedLNotSupported = 1,
	/**
	 * MDataSink::BufferFilledL() was called but not implemented
	 */
	EMMFDescriptorPanicBufferFilledLNotSupported
	};

/**
 * @publishedAll
 *
 * Panic codes for CMMFFile
 */
enum TMMFFilePanicCode
	{
	/**
	 * MDataSource::BufferEmptiedL() called but not implemented
	 */
	EMMFFilePanicBufferEmptiedLNotSupported = 1,
	/**
	 * MDataSink::BufferFilledL() called but not implemented
	 */
	EMMFFilePanicBufferFilledLNotSupported,

	EMMFFileAlreadyOpen
	};

/** 
 * @publishedAll
 * @deprecated
 *
 * Panic codes for CMMFDataPath
 */
enum TMMFDataPathPanicCode
	{
	/**
	 * iState is not the expected value (normally EPlaying)
	 */
	EMMFDataPathPanicBadState = 1000000,

	/**
	 * Code has detected a condition that cannot occur - must be programming error
	 */
	EMMFDataPathPanicProgrammingError = 2000000,
	/**
	 * panic in CMMFDataPath::EmptySinkBufferL() if sink status 
	 * is not EFull or EBeingFilled
	 */
	EMMFDataPathPanicSinkError = 3000000
	};

/**
 * @publishedAll
 *
 * Panic codes for RMMFSubThread
 */
enum TMMFSubThreadPanicCode
	{
	/**
	 * RMMFSubThreadBase::Shutdown(): an attempt to close the subthread timed out
	 */
	EMMFSubThreadPanicTimedOut = 1
	};

/**
 * @publishedAll
 *
 * Panic codes for MMFCodecBaseDefinitions
 */
enum TMMFCodecBaseDefinitionsPanicCode
	{
	/**
	 * ConvertFast() not supported for this codec
	 */
	EMMFCodecBaseDefinitionsPanicConvertFastNotSupported = 1	
	};

/**
 * @publishedAll
 *
 * Panic codes for CMMFAudioController
 */
enum TMMFAudioControllerPanicCode
	{
	/**
	 * reserved
	 */
	EMMFAudioControllerPanicBadUID = 1,

	/**
	 * AddDataSourceL() failed to add a data source
	 */
	EMMFAudioControllerPanicDataSourceDoesNotExist,
	/**
	 * AddDataSinkL() failed to add a sink
	 */
	EMMFAudioControllerPanicDataSinkDoesNotExist
	};

/**
 * @publishedAll
 * @deprecated
 *
 * Panic codes for MMFDisplay
 */
enum TMMFDisplayPanicCode
	{
	EMMFDisplayPanicWrongThread = 1,
	EMMFDisplayPanicNotReady,
	EMMFDisplayPanicCreateSinkBufferLNotSupported,
	EMMFDisplayPanicBufferFilledLNotSupported,
	EMMFDisplayPanicCallingSupplierDoesNotExist,
	EMMFDisplayPanicRequestStatusError
	};

/**
 * @publishedAll
 * @deprecated
 *
 * Panic codes for MMFToneController
 */
enum TMMFToneControllerPanicCode 
	{
	EMMFToneControllerPanicBadUID = 1,
	EMMFToneControllerPanicUnexpectedMixinApiCall,
	EMMFToneControllerPanicBadCancelCustomCommand
	};


/**
 * @publishedAll
 *
 * Panic codes for the audio media client
 */
enum TMMFMediaClientPanicCode 
	{
	EMMFMediaClientPanicSetAudioDeviceModeNotSupported = 1,

	/**
	 * an error occurred communicating with the audio device
	 */
	EMMFMediaClientPanicServerCommunicationProblem,

	/**
	 * CMMFMdaAudioConvertUtility::OpenL() or CMMFMdaAudioRecorderUtility::DoPlay()
	 * detected an invalid internal state 
	 */
	EMMFMediaClientBadState,
	
	EMMFMediaClientBadArgument,
	
	/**
	 * Reserved function should not be called
	 */
	EMMFReservedCall
	};

/**
 * @internalTechnology 
 *
 * Panic codes for the sw codec wrapper
 */
enum TMMFSwCodecWrapperPanicCode
	{	
	/**
	 * codec wrapper did not create an internal datapath
	 */
	EMMFSwCodecWrapperNoDataPath,

	/**
	 * codec wrapper does not have a device handle
	 */
	 EMMFSwCodecWrapperNoDevice,

	/**
	 * codec wrapper codec returns non existant process result
	 */
	 EMMFSwCodecWrapperBadCodec,

	/**
	 * sound driver returns unexpected buffer
	 */
	 EMMFSwCodecWrapperBadBuffer
	};


#endif
