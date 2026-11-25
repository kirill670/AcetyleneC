/*
* ==============================================================================
*  Name        : AdvancedAudioRecordController.h
*  Part of     : AdvancedAudioRecordController
*  Interface   : ?Interface_category, ?Interface_name
*  Description : This file contains the base class from which specific audio
*                record controllers are derived. This class encapsulates common
*                behavior for all audio record controllers.
*  Version     : 8
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


#ifndef ADVANCEDAUDIORECORDCONTROLLER_H
#define ADVANCEDAUDIORECORDCONTROLLER_H

// INCLUDES
#include <AdvancedAudioController.h>

// FORWARD DECLARATIONS
class CAdvancedAudioInput;

// CLASS DECLARATION

/**
*  This is the base class CAdvancedAudioRecordController
*  All specific audio record controllers derive from this class.
*
*  @lib AdvancedAudioController.lib
*  @since 2.1
*/
class CAdvancedAudioRecordController : public CAdvancedAudioController,
									   public MMMFAudioRecordDeviceCustomCommandImplementor,
                                       public MMMFAudioRecordControllerCustomCommandImplementor
    {
    public:	// Constructors and destructor

		/**
		* Destructor
		*/
		IMPORT_C virtual ~CAdvancedAudioRecordController();

        /**
        * C++ default constructor.
        */
        IMPORT_C CAdvancedAudioRecordController();

    protected: // Functions from base classes

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the sample rate of the data source in samples/second.
		* @param aRate sample rate, in samples/second
		* @return void
		*/
		IMPORT_C virtual void MacGetSourceSampleRateL( TUint& aRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the bit rate of the data source in bits/second.
		* @param aRate sample rate, in bits/second
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
		* @param aRate bit rate, in bits/second
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkBitRateL( TUint& aRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the number of channels in the data sink.
		* @param aNumChannels number of channels
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkNumChannelsL( TUint& aNumChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the fourCC code of the sink.
		* @param aDataType fourCC code
		* @return void
		*/
		IMPORT_C virtual void MacGetSinkDataTypeL( TFourCC& aDataType );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of sample rates supported by the data source.
		* @param aSupportedRates supported rates
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceSampleRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of bit rates supported by the data source.
		* @param aSupportedRates supported rates
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceBitRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of channels supported by the data source (ie mono, stereo etc).
		* @param aSupportedChannels supported channels
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceNumChannelsL( RArray<TUint>& aSupportedChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of fourCC codes supported by the data source.
		* @param aSupportedDataTypes supported data types
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSourceDataTypesL( RArray<TFourCC>& aSupportedDataTypes );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of sample rates supported by the data sink.
		* @param aSupportedRates supported rates
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkSampleRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of bit rates supported by the data sink.
		* @param aSupportedRates supported rates
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkBitRatesL( RArray<TUint>& aSupportedRates );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of channels supported by the data sink (ie mono, stereo etc).
		* @param aSupportedChannels supported channels
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkNumChannelsL( RArray<TUint>& aSupportedChannels );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Gets the list of fourCC codes supported by the data sink.
		* @param aSupportedDataTypes supported data types
		*        Warning: Existing objects in this array will be removed by this method.
		* @return void
		*/
		IMPORT_C virtual void MacGetSupportedSinkDataTypesL( RArray<TFourCC>& aSupportedDataTypes );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Sets the bit rate of the data sink in bits/second.
		* @param aRate bit rate, in bits/second.
		* @return void
		*/
		IMPORT_C virtual void MacSetSinkBitRateL( TUint aBitRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Sets the sample rate of the data sink in samples/second.
		* @param aSampleRate The sample rate, in samples/second.
		* @return void
		*/
		IMPORT_C virtual void MacSetSinkSampleRateL( TUint aSampleRate );

		/**
		* From MMMFAudioControllerCustomCommandImplementor
		* Sets the number of channels in the data sink.
		* For example, one channel for mono, two channels for stereo, etc.
		* @param aNumChannels number of channels
		* @return void
		*/
		IMPORT_C virtual void MacSetSinkNumChannelsL( TUint aNumChannels );

		/**
		* From MMMFAudioRecordDeviceCustomCommandImplementor
		* Sets the gain of the sound device.
		* @param aGain new gain
		* @return void
		*/
		IMPORT_C virtual void MardSetGainL( TInt aGain );

		/**
		* From MMMFAudioRecordDeviceCustomCommandImplementor
		* Gets the maximum gain supported by the sound device.
		* @param aMaxGain maximum gain filled in by the controller
		* @return void
		*/
		IMPORT_C virtual void MardGetMaxGainL( TInt& aMaxGain );

		/**
		* From MMMFAudioRecordDeviceCustomCommandImplementor
		* Gets the current recording gain.
		* @param aGain current gain filled in by the controller
		* @return void
		*/
		IMPORT_C virtual void MardGetGainL( TInt& aGain );

		/**
		* From MMMFAudioRecordDeviceCustomCommandImplementor
		* Sets the balance between the left and right stereo microphone channels.
		* @param aBalance Use a value between KMMFBalanceMaxLeft and KMMFBalanceMaxRight
		*                 Centre balance can be restored by using KMMFBalanceCenter.
		* @return void
		*/
		IMPORT_C virtual void MardSetBalanceL( TInt aBalance );

		/**
		* From MMMFAudioRecordDeviceCustomCommandImplementor
		* Retrieve the balance between the left and right stereo microphone channels.
		* @param aBalance current balance, filled in by the controller
		* @return void
		*/
		IMPORT_C virtual void MardGetBalanceL( TInt& aBalance );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Gets the (possibly estimated) record time left in the clip.
		*
		* @param aTime The record time available, in microseconds
		* @return void
		*/
		IMPORT_C virtual void MarcGetRecordTimeAvailableL( TTimeIntervalMicroSeconds& aTime );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Sets the maximum duration of the recorded clip, in microseconds.
		* Not currently supported. Leaves with KErrNotSupported.
		* @param aMaxDuration maximum duration of the recorded clip, in microseconds
		* @return void
		*/
		IMPORT_C virtual void MarcSetMaxDurationL( const TTimeIntervalMicroSeconds& aMaxDuration );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Sets the maximum size of the recorded clip, in bytes.
		* Not currently supported. Leaves with KErrNotSupported.
		* @param aFileSize maximum size of the recorded clip, in bytes
		* @return void
		*/
		IMPORT_C virtual void MarcSetMaxFileSizeL( TInt aFileSize );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Remove a portion from the clip, either from the current position to the beginning
		* or the current position to the end.
		* @param aToEnd crop to the end if ETrue, otherwise crop to the beginning
		* @return void
		*/
		IMPORT_C virtual void MarcCropL( TBool aToEnd );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Add meta data to the clip.
		* Not currently supported. Leaves with KErrNotSupported.
		* @param aNewEntry details of the new entry to be added
		* @return void
		*/
		IMPORT_C virtual void MarcAddMetaDataEntryL( const CMMFMetaDataEntry& aNewEntry );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Remove meta data from the clip.
		* Not currently supported. Leaves with KErrNotSupported.
		*
		* @param aIndex The id of the meta data entry to delete.
		* @return void
		*/
		IMPORT_C virtual void MarcRemoveMetaDataEntryL( TInt aIndex );

		/**
		* From MMMFAudioRecordControllerCustomCommandImplementor
		* Replace a meta data in the clip.
		* Not currently supported. Leaves with KErrNotSupported.
		*
		* @param aIndex The id of the meta data entry to replace.
		* @param aNewEntry The details of the new entry to be added.
		* @return void
		*/
		IMPORT_C virtual void MarcReplaceMetaDataEntryL( TInt aIndex, const CMMFMetaDataEntry& aNewEntry );

	protected: // Data

		// Pointer to audio input
		CAdvancedAudioInput* iAudioInput;
		// max file size
		TInt iMaxFileSize;
    };

#endif		// ADVANCEDAUDIORECORDCONTROLLER_H

// End of File
