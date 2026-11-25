/*
* ==============================================================================
*  Name        : AdvancedAudioPlayController.h
*  Part of     : AdvancedAudioPlayController
*  Interface   : ?Interface_category, ?Interface_name
*  Description : This file contains the base class from which specific audio
*                play controllers are derived. This class encapsulates common
*                behavior for all audio play controllers.
*  Version     : 13
*
*  Copyright (c) 2003 Nokia Corporation.
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


#ifndef CADVANCEDAUDIOPLAYCONTROLLER_H
#define CADVANCEDAUDIOPLAYCONTROLLER_H

// INCLUDES
#include <AdvancedAudioController.h>

// FORWARD DECLARATIONS
class CAdvancedAudioOutput;

// CLASS DECLARATION

/**
*  This is the base class CAdvancedAudioPlayController.
*  All specific audio play controllers derive from this class.
*
*  @lib AdvancedAudioController.lib
*  @since 2.1
*/
class CAdvancedAudioPlayController : public CAdvancedAudioController,
                                     public MMMFAudioPlayDeviceCustomCommandImplementor,
                                     public MMMFAudioPlayControllerCustomCommandImplementor
    {
    public:	// Constructors and destructor

		/**
		* Destructor
		*/
		IMPORT_C virtual ~CAdvancedAudioPlayController();

        /**
        * C++ default constructor.
        */
        IMPORT_C CAdvancedAudioPlayController();

    protected:	// Functions from base classes

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the sample rate of the data source in samples/second.
		* @param aRate source sample rate, in samples/second
		* @return void
		*/
		IMPORT_C virtual void MacGetSourceSampleRateL( TUint& aRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the bit rate of the data source in bits/second.
		* @param aRate source bit rate, in samples/second
		* @return void
		*/
		IMPORT_C virtual void MacGetSourceBitRateL( TUint& aRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the number of channels in the data source.
		* @param aNumChannels number of channels
		* @return void
		*/
		IMPORT_C virtual void MacGetSourceNumChannelsL( TUint& aNumChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the fourCC code of the source.
		* @param aDataType fourCC code
		* @return void
		*/
		IMPORT_C virtual void MacGetSourceDataTypeL( TFourCC& aDataType );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the sample rate of the data sink in samples/second.
		* @param aRate sample rate, in samples/second
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkSampleRateL( TUint& aRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the bit rate of the data sink in bits/second.
		* @param aRate bit rate, in bits/second.
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkBitRateL( TUint& aRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the number of channels in the data sink.
		* @param aNumChannels number of channels.
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkNumChannelsL( TUint& aNumChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the fourCC code of the sink.
		* @param aDataType fourCC code.
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkDataTypeL( TFourCC& aDataType );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of sample rates supported by the data source.
		* @param aSupportedRates supported rates.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceSampleRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of bit rates supported by the data source.
		* @param aSupportedRates supported rates.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceBitRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of channels supported by the data source L(ie mono, stereo etc).
		* @param aSupportedChannels supported channels.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceNumChannelsL( RArray<TUint>& aSupportedChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of fourCC codes supported by the data source.
		* @param aSupportedDataTypes supported data types.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceDataTypesL( RArray<TFourCC>& aSupportedDataTypes );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of sample rates supported by the data sink.
		* @param aSupportedRates supported rates.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkSampleRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of bit rates supported by the data sink.
		* @param aSupportedRates supported rates.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkBitRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of channels supported by the data sink L(ie mono, stereo etc).
		* @param aSupportedChannels supported channels.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkNumChannelsL( RArray<TUint>& aSupportedChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of fourCC codes supported by the data sink.
		* @param aSupportedDataTypes supported data types.
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkDataTypesL( RArray<TFourCC>& aSupportedDataTypes );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the number of meta data entries in the clip.
		* @param aNumberOfEntries the number of meta data entries
		* @return void
		*/
		IMPORT_C virtual void GetNumberOfMetaDataEntriesL( TInt& aNumberOfEntries );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the specified meta data entry.
		* @param aIndex zero based meta data entry index to retrieve.
		* @return pointer to the meta data entry.
		*/
		IMPORT_C virtual CMMFMetaDataEntry* GetMetaDataEntryL( TInt aIndex );

		/**
		* From MMMFAudioPlayDeviceCustomCommandImplementor
		* Sets the volume of the sound device.
		* @param aVolume new volume
		* @return void
		*/
		IMPORT_C virtual void MapdSetVolumeL( TInt aVolume );

		/**
		* From MMMFAudioPlayDeviceCustomCommandImplementor
		* Gets the max volume of the sound device
		* @param aMaxVolume contains the max volume on return
		* @return void
		*/
		IMPORT_C virtual void MapdGetMaxVolumeL( TInt& aMaxVolume );

		/**
		* From MMMFAudioPlayDeviceCustomCommandImplementor
		* Gets the current playback volume
		* @param aVolume contains the current volume on return
		* @return void
		*/
		IMPORT_C virtual void MapdGetVolumeL( TInt& aVolume );

		/**
		* From MMMFAudioPlayDeviceCustomCommandImplementor
		* Sets a volume ramp.
		* This will cause the sound device to start playing with zero volume,
		* increasing the volume over aRampDuration microseconds.
		* The volume ramp can be removed by setting the ramp duration to zero.
		* @param aRampDuration duration over which the volume is to be increased,
		*					in microseconds
		* @return void
		*/
		IMPORT_C virtual void MapdSetVolumeRampL( const TTimeIntervalMicroSeconds& aRampDuration );

		/**
		* From MMMFAudioPlayDeviceCustomCommandImplementor
		* Sets the balance between the left and right stereo audio channels.
		* @param aBalance Use a value between KMMFBalanceMaxLeft and KMMFBalanceMaxRight.
		*                 Center balance can be restored by using KMMFBalanceCenter.
		* @return void
		*/
		IMPORT_C virtual void MapdSetBalanceL( TInt aBalance );

		/**
		* From MMMFAudioPlayDeviceCustomCommandImplementor
		* Retrieves the balance between the left and right stereo audio channels.
		*
		* @param aBalande The current balance, filled in by the controller.
		* @return void
		*/
		IMPORT_C virtual void MapdGetBalanceL( TInt& aBalance );

		/**
		* From MMMFAudioPlayControllerCustomCommandImplementor
		* Sets a playback window. The controller will start playing from the start of the window,
		* and finish playing at the end of the window.
		* @param aStart start of the window, in microseconds
		* @param aEnd end of the window, in microseconds
		* @return void
		*/
		IMPORT_C virtual void MapcSetPlaybackWindowL( const TTimeIntervalMicroSeconds& aStart,
			const TTimeIntervalMicroSeconds& aEnd );

		/**
		* From MMMFAudioPlayControllerCustomCommandImplementor
		* Removes a previously defined playback window.
		* @param none
		* @return void
		*/
		IMPORT_C virtual void MapcDeletePlaybackWindowL();

		/**
		* From MMMFAudioPlayControllerCustomCommandImplementor
		* Gets the completion status of loading/rebuffering the current audio clip
		* @param aPercentageComplete status of loading as a percentage completed
		* @return void
		*/
		IMPORT_C virtual void MapcGetLoadingProgressL( TInt& /*aPercentageComplete*/ );

	protected: // Data

		// Indication whether metadata is supported or not
		TBool iMetaDataSupport;
		// Metadata entries, if supported
		RPointerArray<CMMFMetaDataEntry> iMetaDataEntries;

		// Pointer to audio output
		CAdvancedAudioOutput* iAudioOutput;
		// Play window - start position in microseconds
		TTimeIntervalMicroSeconds iPlayWindowStartPosition;
		// Play window - end position in microseconds
		TTimeIntervalMicroSeconds iPlayWindowEndPosition;
		// Play window - end position in byte position
		TUint iPlayWindowEndBytePosition;
    };

#endif 		// CADVANCEDAUDIOPLAYCONTROLLER_H

// End of File
