/*
* ==============================================================================
*  Name        : AdvancedAudioInput.h
*  Part of     : AdvancedAudioController
*  Interface   : ?Interface_category, ?Interface_name
*  Description : This file contains the base class from which specific audio
*                input classes are derived. This class encapsulates common
*                behavior for all audio inputs. An audio input class serves as
*                the interface between the controller and the lower-level sound
*                gathering interface.
*  Version     : 8
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


#ifndef __CADVANCEDAUDIOINPUT_H__
#define __CADVANCEDAUDIOINPUT_H__

//  INCLUDES
#include <E32Base.h>
#include <e32std.h>
#include <mmfcontrollerframeworkbase.h>
#include <mmfcontrollerframework.h>
#include <Mmfbase.h>
#include <mmfpaniccodes.h>

// CONSTANTS
// Opcodes used in message passing between client and server
enum TAdvancedAudioInputCodecType
	{
	EAAICodecSoftware = 1,
	EAAICodecHardwareAccelerator
	};

// CLASS DECLARATION

/**
*  This is the base class for all audio input classes used for recording.
*  It contains common behaviour for all audio Inputs. The audio Input class
*  provides the interface between the Controller and the sound device.
*
*  @lib AdvancedAudioController.lib
*  @since 2.1
*/
class CAdvancedAudioInput : public CBase
    {
    public: // New functions

        /**
        * Prepares the resources for recording.
        * @since 2.1
        * @param none
        * @return void
        */
        IMPORT_C virtual void PrimeL() = 0;

        /**
        * Pauses the recording.
        * @since 2.1
        * @param none
        * @return void
        */
        IMPORT_C virtual void PauseL() = 0;

        /**
        * Initiates recording.
        * @since 2.1
        * @param aBuffer buffer to record into
        * @return void
        */
        IMPORT_C virtual void RecordL( TAny* aBuffer ) = 0;

        /**
        * Stops recording.
        * @since 2.1
        * @param none
        * @return void
        */
        IMPORT_C virtual void StopL() = 0;

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
        * Returns the max gain.
        * @since 2.1
        * @param none
        * @return max gain
        */
		IMPORT_C virtual TInt MaxGainL() = 0;

        /**
        * Sets the gain.
        * @since 2.1
        * @param aGain gain to be set
        * @return void
        */
        IMPORT_C virtual void SetGainL(TInt /*aGain*/) = 0;

		/**
		* Set the bit rate.
		* @since 2.7
		* @param aBitRate			bit rate to be set
		* @param aCodecConfigData	specific codec configuration data
		* @return 	void
		*/
		IMPORT_C virtual void SetBitRatesL(TUint aBitRate, RArray<TInt>& aCodecConfigData ) = 0;
		
        /**
		* Set sample rate.
		* @since 2.7
		* @param aRate	sample rate to be set
		* @return 	void
		*/
		IMPORT_C virtual void SetRatesL(TUint aSampleRate) = 0;	

        /**
		* Set Channel number
		* @since 2.7
		* @param aNumChannels	number of channels
		* @return 	void
		*/
		IMPORT_C virtual void SetChannelsL(TUint aNumChannels) = 0;	

        /**
        * Returns the current gain.
        * @since 2.1
        * @param none
        * @return current gain
        */
        IMPORT_C virtual TInt GainL() = 0;

        /**
        * Returns the audio input position in microseconds.
        * @since 2.1
        * @param none
        * @return input position
        */
        IMPORT_C virtual TInt CalculateAudioInputPositionL() const = 0;

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
        * Sets the configuration parameters for recording.
        * @since 2.1
        * @param aSampleRate sample rate
        * @param aNumChannel number of channels
        * @param aFourCC data type
        * @param aCodecConfigData codec configuration data
        * @return void
        */
        IMPORT_C virtual void ConfigureL( TUint aSampleRate, TUint aNumChannel,
        	TFourCC aFourCC, TDesC8& aCodecConfigData ) = 0;

        /**
        * Sends an event to the client.
        * @since 2.1
		* @param aEvent event to send
        * @return void
        */
		void SendEventToClient( const TMMFEvent& aEvent);
	};

#endif		// __CADVANCEDAUDIOINPUT_H__
