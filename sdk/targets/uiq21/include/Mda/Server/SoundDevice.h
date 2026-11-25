// Mda\Server\SoundDevice.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_SOUNDDEVICE_H__
#define __MDA_SERVER_SOUNDDEVICE_H__

/*
Notes: 
This file defines the interface for use by the plug-in libraries implementing
sampled sound devices. There can only be one plug-in on the system implementing the local 
and telephony devices, but there can be any number of other unique device types.
The interface for (hardware or software) tone generators is also defined here. 
*/

// Public Media Server includes
#include <Mda\Common\Audio.h>
#include <Mda\Server\Base.h>
#include <Mda\Server\Environment.h>
#include <Mda\Server\Buffer.h>
#include <Mda\Server\AudioIo.h>
#include <Mda\Server\AudioCodecs.h>
#include <Mda\Server\SoundDevicePolicy.h>

//
// Static functions for creating different kinds of sound device objects
//

// - Local sound device (there should only be one in the system)
IMPORT_C CMdaObject* NewLocalSoundDeviceL(CMdaSoundPlayerPolicy* aPlayPolicy=NULL, 
										  CMdaSoundRecorderPolicy* aRecPolicy=NULL);

// - Telephony sound device (there should only be one in the system)
//   An implementation of the state query interface is
//   required to be supplied on construction

class MMdaTelephonyStateQuery
	{
public:
	// This function should complete the supplied message with KErrNone
	// after setting the aQeury->iIsTelephonyActive member to ETrue
	// if a call is active and hence audio can currently be sent to the 
	// uplink or received from the downlink.
	// It should set it to EFalse if a call is not active.
	// Completion should be synchronous only if determining the state
	// can be performed very quickly. If the state cannot be determined quickly,
	// the message pointer should be preserved and completed asynchronously.
	// If the request cannot be completed for any reason (e.g. low memory)
	// the function should leave (if synchronous) or the message should be 
	// completed with a suitable error value (if asynchronous)
	virtual void MTSQIsTelephonyActiveL(TMdaTelephonyStateQuery* aQuery, CMdaMessage* aMessage)=0;
	};

IMPORT_C CMdaObject* NewTelephonySoundDeviceL(MMdaTelephonyStateQuery& aQuery, 
											  CMdaSoundPlayerPolicy* aPlayPolicy=NULL,
											  CMdaSoundRecorderPolicy* aRecPolicy=NULL);

// - Generic sound device (there can be many, identified by Uid)
//   An implementation of the config handler can be supplied if
//   the interface allows the client to perform extra configuration

class MMdaSoundDeviceConfigHandler
	{
public:
	// MSDCHConfigThisL() will be called by the device on creation.
	// It should perform synchronous intialisation of the config package based
	// on the supplied information.
	virtual void MSDCHConfigThisL(const TMdaPackage* aPackage, TBool aFromDest)=0;
	// MSDCHConfigOtherL() will be called by the device if the client has 
	// executed a ResourceConfig call with an unknown package
	// It should attempt to identify the supplied package, 
	// and if recognised, perform the correct action synchronous or asynchronous
	// action before completing the message with KErrNone.
	// The package can be modified and will be returned to the client on success.
	// "aFromDest" is true if this was a ResourceConfig
	// on a destination stream port (else if was a source stream port).
	// If the package is unrecognised the function 
	// should leave with "KErrNotSupported"
	virtual void MSDCHConfigOtherL(TMdaPackage* aPackage, TBool aFromDest, CMdaMessage* aMessage)=0;
	};

IMPORT_C CMdaObject* NewSoundDeviceL(TUid aUid, 
									 TMdaPackage& aConfigPackage,
									 CMdaSoundPlayerPolicy* aPlayPolicy=NULL, 
									 CMdaSoundRecorderPolicy* aRecPolicy=NULL,
									 MMdaSoundDeviceConfigHandler* aHandler=NULL);

// - Tone generator device (there should only be one in the system)
//	 Factory function requires a reference to an implementation of 
//	 MMdaToneGeneratorDevice which handles that actual generation of tones when required.	 
//	 A new device is created for each client so any sharing policy is entirely up to
//   the particular implementation (unlike the sampled sound devices).
//	 Note that unrecognised sequence formats might be redirected to other
//	 plug-in software synthesisers/generators within the system.

class HMdaToneFixedSequenceNames : public TMdaToneFixedSequenceNames
	{
public:
	IMPORT_C HMdaToneFixedSequenceNames();
	IMPORT_C HMdaToneFixedSequenceNames* AddNameL(const TDesC& aName);
	};

class MMdaToneGeneratorDevice
	{
public:
	// Configuration functions
	// -----------------------
	// Note: Cannot be called during playback
	// apart from MtgdSetVolume(...)

	// Allocate all resource required to use the interface. Should return immediately
	// and call CMdaToneGeneratorDevice::DeviceInitFinished(...) when finished.
	// Can fail by leaving (in which case no callback required) or passing error
	// value to callback function
	virtual void InitL()=0;
	// Cancel asynchronous InitL
	virtual void CancelInit()=0;
	// Release all resources associated with this interface
	virtual void Release()=0;
	// Return the maximum volume value (must be >= 1)
	virtual TInt MtgdGetMaxVolume()=0;
	// Return the current volume settings
	virtual TInt MtgdGetVolume()=0;
	// Set the volume (should work during playback)
	virtual void MtgdSetVolume(TInt aVolume)=0;
	// Set the priority of play requests
	virtual void MtgdSetPriority(TInt aPriority, TMdaPriorityPreference aPref)=0;
	// Set the DTMF tone lengths. Note: If iToneOnLength < 0, only the first
	// character of DTMF string should be played, and then held 
	// until MtgdStopPlayback is called
	virtual void MtgdSetDTMFLengths(TTimeIntervalMicroSeconds32 aToneOnLength,
									TTimeIntervalMicroSeconds32 aToneOffLength,
									TTimeIntervalMicroSeconds32 aPauseLength)=0;
	// Set the number of times to repeat the sound, and any silence between repeats
	// If repeat count is KMdaRepeatForever then repeat indefinately
	virtual void MtgdSetRepeats(TInt aRepeatCount, const TTimeIntervalMicroSeconds& aRepeatTrailingSilence)=0;
	// Set a volume ramp-up of the specified duration when playback begins
	virtual void MtgdSetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;
	// Create a package containing human-readable names for the fixed
	// sequences supported by this generator
	virtual TMdaToneFixedSequenceNames* MtgdCreateSequenceNameListL()=0;
	// Try to identify data as a sequence - return true if recognised
	virtual TBool MtgdRecogniseSequenceData(const TDesC8& aData)=0;

	// Playback functions
	// ------------------
	// All play functions should return immediately, and call the 
	// CMdaToneGeneratorDevice::TonePlaybackFinished(...) when playback has completed
	// If MtgdStopPlayback() is called, playback should terminate immediately and
	// no callback should be made on the device.

	// Play a simple tone at the specified frequency for the specified duration
	virtual void MtgdPlayToneL(TInt aFrequency, const TTimeIntervalMicroSeconds& aDuration)=0;
	// Play supplied DTMF string or character
	virtual void MtgdPlayDTMFL(const TDesC& aDTMFString)=0;
	// Play supplied sequence (will be recognisable data)
	virtual void MtgdPlaySequenceDataL(const TDesC8& aData)=0;
	// Play fixed sequence
	virtual void MtgdPlayFixedSequenceL(TInt aSequenceNumber)=0;
	// Stop current playback
	virtual void MtgdStopPlayback()=0;
	};

class CMdaToneGeneratorDevice : public CMdaObject
	{
public:
	IMPORT_C static CMdaToneGeneratorDevice* NewL(MMdaToneGeneratorDevice& aToneDevice);
	virtual void DeviceInitFinished(TInt aError)=0; // aError == KErrNone means success
	virtual void TonePlaybackFinished(TInt aError)=0; // aError == KErrNone means success
	};

#endif
