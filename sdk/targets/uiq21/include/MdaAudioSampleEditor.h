// MdaAudioSampleEditor.h 
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOSAMPLEEDITOR_H__
#define __MDAAUDIOSAMPLEEDITOR_H__

/*
Notes:
 This file defines an audio editing utility API. 

Classes:
 CMdaAudioClipUtility
 Abstract utility base class providing play, record, crop, and positioning functions

 CMdaAudioRecorderUtility
 Concrete class for playing and recording to audio data using an audio device

 CMdaAudioConvertUtility
 Concrete class for converting audio data between different formats

*/

#include <e32base.h>

#include <Mda\Client\Resource.h>
#include <Mda\Client\Utility.h>
#include <Mda\Common\Audio.h>

const TInt KMdaAudioClipUtilityRepeatForever = -1;


/**
 *
 * A class which encapsulates the format, the codec and the audio
 * settings which characterize an audio sample.
 *
 * These three items are further encapsulated within other classes and
 * instances of these classes are constructed on the heap. These
 * instances are destroyed when this object is destroyed.
 *
 * @since 5.0
 * @lib " MediaClientAudio.lib "
 */
class CMdaAudioType : public CBase
	{
public:	
	IMPORT_C virtual ~CMdaAudioType();
public:
	TMdaClipFormat* iFormat;
	TMdaPackage* iCodec;
	TMdaAudioDataSettings* iSettings;
	// Registry entries
	TMdaRegistryEntryData* iFormatInfo;
	TMdaRegistryEntryData* iCodecInfo;
	TBool iIsPlayOnly;
	};

enum TMdaAudioClipUtilityPanic
	{ // Panic category will be reported as "MdaAudioSampleEditor"
	EMdaAudioClipUtilityPanicNotReady = 1,
	EMdaAudioClipUtilityPanicPlayCalledWhileStillRecording = 2,
	EMdaAudioClipUtilityPanicRecordCalledWhileStillPlaying = 3,
	EMdaAudioClipUtilityPanicAlreadyPlaying = 4,
	EMdaAudioClipUtilityPanicAlreadyRecording= 5,
	EMdaAudioClipUtilityPanicAlreadyOpen = 6
	};

class CMdaClipUtilityImplData;

/**
 *
 * A utility class which implements behaviour which is common to both the
 * audio recorder and the audio converter.
 * @since 5.0
 * @lib "MediaClientAudio.lib"
 */
class CMdaAudioClipUtility : public CBase
	{
public:

/**
 *
 * Defines the possible state of the audio data sample.
 *
 */
	enum TState
		{
/** The audio clip recorder or audio converter has been constructed but no
file or descriptor has been opened
 */
		ENotReady = 0,
/** Files or descriptors are open but no playing or recording operation is
in progress.
 */
		EOpen,
/** Audio sample data is playing
 */
		EPlaying,
		ERecording
		};
public:
	virtual TState State();
	virtual void Close();
	virtual void PlayL();
	virtual void RecordL();
	virtual void Stop();
	virtual void CropL();
	virtual void SetPosition(const TTimeIntervalMicroSeconds& aPosition);
	virtual const TTimeIntervalMicroSeconds& Position();
	virtual const TTimeIntervalMicroSeconds& RecordTimeAvailable();
	virtual const TTimeIntervalMicroSeconds& Duration();
	virtual void SetPlayWindow(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd);
	virtual void ClearPlayWindow();
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);
	virtual CMdaAudioType* TypeL();
	virtual void SetMaxWriteLength(TInt aMaxWriteLength = KMdaClipLocationMaxWriteLengthNone);
public:
	// Reserved functions - do not call
	virtual void ClipUtil_Reserved2();
	virtual void ClipUtil_Reserved3();
	virtual void ClipUtil_Reserved4();
protected:
	CMdaClipUtilityImplData* iData;
	};

/**
 *
 * Plays back, records and edits audio sample data.
 *
 * The class offers an interface to play, record and edit audio sample
 * data samples. This data can be supplied either in a file or as a
 * descriptor.While this class is abstract, the static function
 * constructs, initialises and returns a pointer to an instance of a
 * concrete class derived from this abstract class. This concrete class
 * is part of the Media Server implementation and is private.If a client
 * only needs to play back existing audio sample data, it may be better
 * to use the simpler Audio Sample Player API.
 *
 * @since 5.0
 * @lib "MediaClientAudio.lib"
 */
class CMdaAudioRecorderUtility : public CMdaAudioClipUtility
	{
public:

/**
 *
 * Audio device mode.
 *
 */
	enum TDeviceMode
		{
/** The default behaviour.When recording:if a telephony call is in
progress, an attempt is made to connect to the telephony downlink plus
the device microphone.if there is no telephony call in progress or a
connection to the telephony downlink fails, an attempt is made to
connect to the device microphone only.When playing:if a telephony call
is in progress, an attempt is made to connect to the telephony
uplink.if there is no telephony call in progress or a connection to
the telephony uplink fails, an attempt is made to connect to the
device speaker.
 */
		EDefault=0,
/** See <code>EDefault</code>
 */
		ETelephonyOrLocal=EDefault,
/** When recording:if a telephony call is in progress the audio source is
the telephony downlink mixed with the device microphone.if there is no
telephony call in progress or a connection to the telephony downlink
fails, no attempt is made to connect to the microphone.When playing:if
a telephony call is in progress the audio sample data is played to the
telephony uplink and the device speaker.if there is no telephony call
in progress or a connection to the telephony uplink fails, no attempt
is made to connect to the device speaker.
 */
		ETelephonyMixed=1,
/** When recording, the audio source is the telephony downlink and is not
mixed with the device microphone.When playing, the audio sample data
is played to the telephony uplink and is not mixed with the device
speaker.
 */
		ETelephonyNonMixed=2,
/** When recording, the audio source is the device microphone.When
playing, the audio sample data is played to the device speaker.
 */
		ELocal=3
		};
public:
	IMPORT_C static CMdaAudioRecorderUtility* NewL(
						MMdaObjectStateChangeObserver& aObserver, 
						CMdaServer* aServer=NULL, 
						TInt aPriority=EMdaPriorityNormal, 
						TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality);

/**
 *
 * Opens an existing file to play back existing audio sample data.
 *
 * @param     "const TDesC& aFilename"
 *            The full path name of the file which can be a source
 *            of existing audio sample data or a target for new
 *            audio sample data.
 */
	virtual void OpenFileL(const TDesC& aFilename)=0;

/**
 *
 * Opens an existing descriptor to play back existing audio sample data.
 *
 * @param     "const TDesC8& aData"
 *            The descriptor which can be a source of existing audio
 *            sample data or a target for new audio sample data.
 *            This descriptor must remain in existence for the
 *            lifetime of this audio clip recorder object.
 */
	virtual void OpenDesL(const TDesC8& aData)=0;

/**
 *
 * Opens a generic audio object to play back existing audio sample data
 * or to record new audio sample data.
 *
 * @param     "TMdaClipLocation* aLocation"
 *            The location of a source of existing audio sample data
 *            or a target for new audio sample data. The identity of
 *            the source is generic but is normally a file name (a
 *            <code>TMdaFileClipLocation</code>) or a descriptor (a
 *            <code>TMdaDesClipLocation</code>).
 * @param     "TMdaClipFormat* aFormat"
 *            The data format
 * @param     "TMdaPackage* aArg1"
 *            The codec to use
 * @param     "TMdaPackage* aArg2"
 *            Audio settings
 */
	virtual void OpenL(TMdaClipLocation* aLocation,	// Normally file or descriptor
						TMdaClipFormat* aFormat,		// Data format
						TMdaPackage* aArg1 = NULL,		// Normally codec to use
						TMdaPackage* aArg2 = NULL)=0;		// Normally audio settings

/**
 *
 * Sets the mode of the audio device to be used.
 *
 * This determines how the API handles the configuration of the device
 * hardware.
 *
 * @param     "TDeviceMode aMode"
 *            The audio device mode
 */
	virtual void SetAudioDeviceMode(TDeviceMode aMode)=0;

/**
 *
 * Gets an integer representing the maximum volume for the audio device.
 *
 * This is the maximum value which can be passed to
 * <code>CMdaAudioRecorderUtility::SetVolume()</code>.
 *
 * @returns   "TInt"
 *            The maximum volume. This value is platform dependent
 *            but is always greater than or equal to one.
 */
	virtual TInt MaxVolume()=0;

/**
 *
 * Gets an integer representing the maximum gain setting for the audio
 * device.
 *
 * This is the maximum value which can be passed
 * to<code>CMdaAudioRecorderUtility::SetGain()</code>.
 *
 * @returns   "TInt"
 *            The maximum gain. For devices where automatic gain
 *            control is used, this value may be zero.
 */
	virtual TInt MaxGain()=0;

/**
 *
 * Sets the playback volume for the audio device to a specified value.
 *
 * @param     "TInt aVolume"
 *            The volume setting. This can be any value from zero to
 *            the value returned by a call to
 *            <code>CMdaAudioRecorderUtility::MaxVolume()</code>. A
 *            value which is less than zero is set to zero. A value
 *            which is greater than
 *            <code>CMdaAudioRecorderUtility::MaxVolume()</code> is
 *            set to
 *            <code>CMdaAudioRecorderUtility::MaxVolume()</code>.
 *            Setting a zero value mutes the sound. Setting the
 *            maximum value results in the loudest possible sound.
 */
	virtual void SetVolume(TInt aVolume)=0;

/**
 *
 * Sets the gain for the audio device to a specified value.
 *
 * @param     "TInt aGain"
 *            The gain setting. This can be any value from zero to
 *            the value returned by a call to
 *            <code>CMdaAudioRecorderUtility::MaxGain()</code>. A
 *            value which is less than zero is set to zero. A value
 *            which is greater
 *            than<code>CMdaAudioRecorderUtility::MaxGain()</code>
 *            is set
 *            to<code>CMdaAudioRecorderUtility::MaxGain()</code>.
 */
	virtual void SetGain(TInt aGain)=0;

/**
 *
 * Sets the volume increase gradient.
 *
 * This defines the period over which the volume level of a played audio
 * sample is to rise smoothly from nothing to the normal volume level.
 *
 * @param     "const TTimeIntervalMicroSeconds& aRampDuration"
 *            The period over which the volume is to rise. A zero
 *            value causes the audio sample to be played at the
 *            normal level for the full duration of the playback. A
 *            value which is longer than the duration of the audio
 *            sample means that the sample never reaches its normal
 *            volume level.
 */
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;
	};

/**
 *
 * Converts audio sample data from one format to another.
 *
 * The audio sample data can be supplied either in a file or as a
 * descriptor.While this class is abstract, the static functions
 * construct, initialise and return a pointer to an instance of a
 * concrete class derived from this abstract class. This concrete class
 * is part of the Media Server implementation and is private.
 *
 * @since 5.0
 * @lib " MediaClientAudio.lib "
 */
class CMdaAudioConvertUtility : public CMdaAudioClipUtility
	{
public:
	IMPORT_C static CMdaAudioConvertUtility* NewL(
						MMdaObjectStateChangeObserver& aObserver, 
						CMdaServer* aServer=NULL, 
						TInt aPriority = EMdaPriorityNormal, 
						TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

/**
 *
 * Opens existing files so that audio sample data can be extracted from
 * the source file, converted and appended onto the target file.
 *
 * @param     "const TDesC& aPrimaryFile"
 *            The full path name of a file containing audio sample
 *            data to be converted.
 * @param     "const TDesC& aSecondaryFile"
 *            The full path name of a file to which converted data
 *            is appended.
 */
	virtual void OpenL(const TDesC& aPrimaryFile, const TDesC& aSecondaryFile)=0;

/**
 *
 * More generic way of opening a source file and a destination "location" that
 * may or may not already exist.
 *
 * @param     "const TDesC& aPrimaryFile"
 *            The full path name of a file containing audio sample
 *            data to be converted.
 * @param     "TMdaClipLocation* aLocation"
 *            The clip location object representing the destination.
 * @param     "TMdaClipFormat* aFormat"
 *            The clip format to use.
 * @param     "TMdaPackage* aArg1 = NULL"
 *            Optionally, the codec to use if there is a choice.
 * @param     "TMdaPackage* aArg2 = NULL"
 *            Optionally, additional audio settings that may be required.
 */
	virtual void OpenL(const TDesC& aPrimaryFile,
						TMdaClipLocation* aLocation,	// Normally file or descriptor
						TMdaClipFormat* aFormat,		// Data format
						TMdaPackage* aArg1 = NULL,		// Normally codec to use
						TMdaPackage* aArg2 = NULL)=0;	// Normally audio settings

/**
 *
 * Completely generic way of opening source and destination "locations" -
 * destination may or may not already exist.
 *
 * @param     "TMdaClipLocation* aPriLocation"
 *            The clip location object representing the source.
 * @param     "TMdaClipLocation* aSecLocation"
 *            The clip location object representing the destination.
 * @param     "TMdaClipFormat* aPriFormat"
 *            The clip format to use to read the source.
 * @param     "TMdaClipFormat* aSecFormat"
 *            The clip format to use to write to the destination.
 * @param     "TMdaPackage* aPriArg1 = NULL"
 *            Optionally, the codec to use to read the source.
 * @param     "TMdaPackage* aPriArg2 = NULL"
 *            Optionally, additional audio settings that may be required
 *            to read the source.
 * @param     "TMdaPackage* aSecArg1 = NULL"
 *            Optionally, the codec to use to write to the destination.
 * @param     "TMdaPackage* aSecArg2 = NULL"
 *            Optionally, additional audio settings that may be required
 *            to write to the destination.
 */
	virtual void OpenL(TMdaClipLocation* aPriLocation, 
						TMdaClipLocation* aSecLocation, 
						TMdaClipFormat* aPriFormat, 
						TMdaClipFormat* aSecFormat, 
						TMdaPackage* aPriArg1 = NULL, 
						TMdaPackage* aPriArg2 = NULL, 
						TMdaPackage* aSecArg1 = NULL, 
						TMdaPackage* aSecArg2 = NULL)=0;
	};

#endif

