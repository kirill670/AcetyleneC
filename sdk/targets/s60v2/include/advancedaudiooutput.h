/*
* ==============================================================================
*  Name        : AdvancedAudioOutput.h
*  Part of     : AdvancedAudioController
*  Interface   : ?Interface_category, ?Interface_name
*  Description : This file contains the base class from which specific audio
*                output classes are derived. This class encapsulates common
*                behavior for all audio outputs. An audio output class serves as
*                the interface between the controller and the lower-level sound
*                producing interface.
*  Version     : 10
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


#ifndef CADVANCEDAUDIOOUTPUT_H
#define CADVANCEDAUDIOOUTPUT_H

//  INCLUDES
#include <E32Base.h>
#include <e32std.h>
#include <mmfcontrollerframeworkbase.h>
#include <mmfcontrollerframework.h>
#include <Mmfbase.h>
#include <mmfpaniccodes.h>

// CONSTANTS
// Opcodes used in message passing between client and server
enum TAdvancedAudioOutputCodecType
	{
	EAAOCodecSoftware = 1,
	EAAOCodecHardwareAccelerator
	};

// CLASS DECLARATION

/**
*  This is the base class for all audio output classes, used for playback.
*  It contains common behaviour for all audio outputs. The audio output class
*  provides the interface between the Controller and the sound device.
*
*  @lib AdvancedAudioController.lib
*  @since 2.1
*/
class CAdvancedAudioOutput : public CBase
    {
    public: // New functions

        /**
        * Prepares the resources for playback.
        * @since 2.1
        * @param none
        * @return void
        */
        IMPORT_C virtual void PrimeL() = 0;

        /**
        * Pauses the playback.
        * @since 2.1
        * @param none
        * @return void
        */
        IMPORT_C virtual void PauseL() = 0;

        /**
        * Initiates playback.
        * @since 2.1
        * @param aBuffer buffer to be played
        * @return void
        */
        IMPORT_C virtual void PlayL( TAny* aBuffer ) = 0;

        /**
        * Stops recording.
        * @since 2.1
        * @param none
        * @return void
        */
        IMPORT_C virtual void StopL() = 0;

        /**
        * Returns the max volume.
        * @since 2.1
        * @param none
        * @return max volume
        */
		IMPORT_C virtual TInt MaxVolumeL() = 0;

        /**
        * Sets the volume.
        * @since 2.1
        * @param aVolume volume to be set
        * @return void
        */
        IMPORT_C virtual void SetVolumeL( TInt /*aVolume*/ ) = 0;

        /**
        * Returns the current volume.
        * @since 2.1
        * @param none
        * @return current volume
        */
        IMPORT_C virtual TInt VolumeL() = 0;

        /**
		* Sets the source priority settings if a priority mechanism is required
		* to arbitrate between multiple clients trying to access the same resource.
		* Sets the priority for the source and the sink (provided they are defined).
		* @since 2.1
        * @param aPrioritySettings priority settings
        * @return void
        */
        IMPORT_C virtual void SetPrioritySettingsL( const TMMFPrioritySettings& /*aPrioritySettings*/ ) = 0;

        /**
        * Returns the audio output position in microseconds.
        * @since 2.1
        * @param none
        * @return input output
        */
        IMPORT_C virtual TInt CalculateAudioOutputPositionL() const = 0;

        /**
        * Returns the currently configured rates.
        * @since 2.1
        * @param aRates on return, configured rates
        * @return void
        */
        IMPORT_C virtual void ConfigRatesL( RArray<TUint>& aRates ) = 0;

        /**
        * Returns the currently configured channels.
        * @since 2.1
        * @param aChannels on return, configured channels
        * @return void
        */
        IMPORT_C virtual void ConfigChannelsL( RArray<TUint>& aChannels ) = 0;

        /**
        * Returns the currently configured data types.
        * @since 2.1
        * @param aDataTypes on return, configured data types
        * @return void
        */
        IMPORT_C virtual void ConfigDataTypesL( RArray<TFourCC>& aDataTypes ) = 0;

        /**
        * Returns the supported rates.
        * @since 2.1
        * @param aRates on return, supported rates
        * @return void
        */
        IMPORT_C virtual void CapabilitiesRatesL( RArray<TUint>& aRates ) = 0;

        /**
        * Returns the supported channels.
        * @since 2.1
        * @param aChannels on return, supported channels
        * @return void
        */
        IMPORT_C virtual void CapabilitiesChannelsL( RArray<TUint>& aChannels ) = 0;

        /**
        * Returns the supported data types.
        * @since 2.1
        * @param aDataTypes on return, supported data types
        * @return void
        */
        IMPORT_C virtual void CapabilitiesDataTypesL( RArray<TFourCC>& aDataTypes ) = 0;

        /**
        * Sets the volume ramp.
        * @since 2.1
        * @param aRampDuration duration over which the volume is to be increased in microseconds
        * @return void
        */
        IMPORT_C virtual void SetVolumeRampL( const TTimeIntervalMicroSeconds& aRampDuration ) = 0;

        /**
        * Sets the balance.
        * @since 2.1
        * @param aLeftPercentage percentage of balance to be played on left
        * @param aRightPercentage percentage of balance to be played on right
        * @return void
        */
        IMPORT_C virtual void SetPlayBalanceL( TInt aLeftPercentage, TInt aRightPercentage ) = 0;

        /**
        * Returns the current balance percentages.
        * @since 2.1
        * @param aLeftPercentage on return, percentage of balance to be played on left
        * @param aRightPercentage on return, percentage of balance to be played on right
        * @return void
        */
        IMPORT_C virtual void GetPlayBalanceL( TInt& aLeftPercentage, TInt& aRightPercentage ) = 0;

        /**
        * Sets the configuration parameters for recording.
        * @since 2.1
        * @param aSampleRate sample rate
        * @param aNumChannel number of channels
        * @param aFourCC data type
        * @param aConfigType configuration type
        * @param aCodecConfigData codec configuration data
        * @return void
        */
        IMPORT_C virtual void ConfigureL( TUint aSampleRate, TUint aNumChannel, TFourCC aFourCC,
                                          TUid aConfigType, const TDesC8& aCodecConfigData ) = 0;

        /**
        * Sets the configuration parameters for recording.
        * @since 2.1
        * @param aConfigType configuration type
        * @param aCodecConfigData codec configuration data
        * @return void
        */
        IMPORT_C virtual void ConfigureL( TUid aConfigType, const TDesC8& aConfigData ) = 0;
	};

#endif		// CADVANCEDAUDIOOUTPUT_H
