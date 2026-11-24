/*
* ==============================================================================
*  Name        : EnvironmentalReverbUTILITY.h
*  Part of     : Audio Effects Framework
*  Description : This is the definition of the audio EnvironmentalReverb utility class.
*  Version     : %version: 5 %
*
*  Copyright © 2006 Nokia. All rights reserved.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia. All rights are reserved. Copying, including
*  reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef CENVIRONMENTALREVERBUTILITY_H
#define CENVIRONMENTALREVERBUTILITY_H

//  INCLUDES
#include <e32base.h>
#include <e32svr.h>
#include <EnvironmentalReverbBase.h>
#include <centralrepository.h>
#include "EnvironmentalReverbUtilityData.h"

// FORWARD DECLARATIONS
class TEfEnvironmentalReverbUtilityPreset;
class CEnvironmentalReverb;
class CMdaAudioConvertUtility;
class CMdaAudioPlayerUtility;
class CMdaAudioRecorderUtility;
class CMdaAudioInputStream;
class CMdaAudioOutputStream;
class CMdaAudioToneUtility;
class CCustomCommandUtility;
class CCustomInterfaceUtility;
class CMMFDevSound;
class CRepository;
class CMidiClientUtility;
class CDrmPlayerUtility;
class CVideoPlayerUtility;

// CLASS DECLARATION

/**
*  This is the EnvironmentalReverb Utility class for managing audio EnvironmentalReverb presets.
*
*  
*  
*/

class CEnvironmentalReverbUtility : public CBase
    {
    public:  // Constructors and destructor


        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a Devsound Instance
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMMFDevSound& aDevSound);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a convert utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMdaAudioConvertUtility& aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a audio input stream utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMdaAudioInputStream& aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a audio output stream utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMdaAudioOutputStream& aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a audio player utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMdaAudioPlayerUtility& aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a audio recorder utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMdaAudioRecorderUtility& aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to a audio tone utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMdaAudioToneUtility& aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to custom command utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CCustomCommandUtility* aUtility);

        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to custom interface utility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(MCustomInterface& aCustomInterface);


        /**
        * Factory function for creating the audio EnvironmentalReverb utility object.
        * 
        * @param aUtility A reference to CMidiClientUtility
        * @return pointer to CEnvironmentalReverbUtility object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CMidiClientUtility& aUtility);


        /**
        * Factory function for creating the audio equalizer object.
        * 
        * @param CDrmPlayerUtility A reference to a CDrmPlayerUtility object
        * @return pointer to CAudioEqualizer object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CDrmPlayerUtility& aUtility);

        /**
        * Factory function for creating the audio equalizer object.
        * 
        * @param CVideoPlayerUtility A reference to a CVideoPlayerUtility object
        * @return pointer to CAudioEqualizer object
        */
        IMPORT_C static CEnvironmentalReverbUtility* NewL(CVideoPlayerUtility& aUtility);

         /**
        * Destructor.
        */
        virtual ~CEnvironmentalReverbUtility();

        /**
        * Apply the Preset Index value
        * 
        * @param aPreset Preset Value
        */
        IMPORT_C void ApplyPresetL(TInt aPreset);

        /**
        * Disable the EnvironmentalReverb
        * 
        */
        IMPORT_C void DisableEnvironmentalReverbL();

        /**
        * Create a Preset with the given Name and EnvironmentalReverb Settings
        * 
        * @param aName Name of the Preset
        * @param aEnvironmentalReverb EnvironmentalReverb Settings for the Preset
        */
        IMPORT_C void CreatePresetL(TDesC& aName, CEnvironmentalReverb& aEnvironmentalReverbUI);

        /**
        * Delete a Preset with the given index in the Central Repository
        * 
        * @param aPresetIndex Index of the Preset in the Array
        */
        IMPORT_C void DeletePresetL(TInt aPresetIndex);

        /**
        * Retrieves a Preset with the given index from the Central Repository
        * 
        * @param aPresetIndex Index of the Preset in the Array
        */
        IMPORT_C  const TDesC& GetPresetL(TInt aPresetIndex);

        /**
        * Get the reference to the EnvironmentalReverb Object
        * 
        * @return Reference to the EnvironmentalReverb Object.
        */
        IMPORT_C CEnvironmentalReverb& EnvironmentalReverb();

        /**
        * Modify a Preset with the given Name and EnvironmentalReverb Settings
        * 
        * @param aPresetIndex Array Index of the Preset
        * @param aName Name of the Preset
        * @param aEnvironmentalReverb EnvironmentalReverb Settings for the Preset
        */
        IMPORT_C void ModifyPresetL(TInt aPresetIndex, TDesC& aName, CEnvironmentalReverb& aEnvironmentalReverbUI);

        /**
        * Get the number of Pre Defined Presets
        * 
        * @return Number of Pre Defined Presets
        */
        IMPORT_C TUint32 NumberOfPreDefinedPresets() const;

        /**
        * Get all the Presets defined in the Central Repository
        * 
        * @return Array of all Presets.
        */
        IMPORT_C TArray<TEfEnvironmentalReverbUtilityPreset> Presets();

        /**
         * Reset a System Defined Preset with the given index in the Array returned from Presets()
         * 
         * @param aPresetIndex Index of the Preset in the Array
         */
        IMPORT_C void ResetPresetL(TInt aPresetIndex);

    private:

        /**
        * C++ default constructor.
        */
        CEnvironmentalReverbUtility();

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        /**
        * Second Phase Costructor for DevSound Instance
        * 
        * @param aDevSound DevSound Referece
        */
        void ConstructL(CMMFDevSound& aDevSound);

        /**
        * Second Phase Costructor for Audio Convert Utility
        * 
        * @param aUtility CMdaAudioConvertUtility Referece
        */
        void ConstructL(CMdaAudioConvertUtility& aUtility);

        /**
        * Second Phase Costructor for CMdaAudioInputStream
        * 
        * @param aUtility CMdaAudioInputStream Referece
        */
        void ConstructL(CMdaAudioInputStream& aUtility);

        /**
        * Second Phase Costructor for CMdaAudioOutputStream
        * 
        * @param aUtilityCMdaAudioOutputStream Referece
        */
        void ConstructL(CMdaAudioOutputStream& aUtility);

        /**
        * Second Phase Costructor for CMdaAudioPlayerUtility
        * 
        * @param aUtility CMdaAudioPlayerUtility Referece
        */
        void ConstructL(CMdaAudioPlayerUtility& aUtility);

        /**
        * Second Phase Costructor for CMdaAudioRecordUtility
        * 
        * @param aUtility CMdaAudioRecordUtility Referece
        */
        void ConstructL(CMdaAudioRecorderUtility& aUtility);

        /**
        * Second Phase Costructor for CMdaAudioToneUtility
        * 
        * @param aUtility CMdaAudioToneUtility Referece
        */
        void ConstructL(CMdaAudioToneUtility& aUtility);

        /**
        * Second Phase Costructor for MCustomCommand
        * 
        * @param aUtility MCustomCommand Referece
        */
        void ConstructL(CCustomCommandUtility* aUtility);

        /**
        * Second Phase Costructor for MCustomInterface
        * 
        * @param aUtility MCustomInterface Referece
        */
        void ConstructL(MCustomInterface& aCustomInterface);

        /**
        * Second Phase Costructor for CMidiClientUtility
        * 
        * @param aUtility CMidiClientUtility Referece
        */
        void ConstructL(CMidiClientUtility& aUtility);
        
        /**
        * Second Phase Costructor for CDrmPlayerUtility
        * 
        * @param aUtility CDrmPlayerUtility Referece
        */
        void ConstructL(CDrmPlayerUtility& aUtility);                

		/**
		* Second Phase Costructor for CVideoPlayerUtility
		* 
		* @param aUtility CVideoPlayerUtility Referece
		*/
		void ConstructL(CVideoPlayerUtility& aUtility);		

        /**
        * Function for Updating the Array from the Central Repository
        * 
        * @param aUtility MCustomInterface Referece
        */
        void UpdateFullPresetArrayFromCenRep(RArray<TEfEnvironmentalReverbUtilityPreset> &aFullPresetArray);

        /**
        * Function of Updating the Preset Array for the User
        * 
        * @param aUtility MCustomInterface Referece
        */
        void UpdatePresetArray(RArray<TEfEnvironmentalReverbUtilityPreset>& aPresetArray,const RArray<TEfEnvironmentalReverbUtilityPreset> &aFullPresetArray);


    private: // Data

        // Array for Storing the Current State of the Repository
        // which has been compacted after the transaction
        // with the Central Repository
        RArray<TEfEnvironmentalReverbUtilityPreset> iPresetArray;

        // Array Which contains the full information from the
        // Central Repository except the Description Values
        RArray<TEfEnvironmentalReverbUtilityPreset> iFullPresetArray;

        // Pointer to the EnvironmentalReverb Object
        CEnvironmentalReverb* iEnvironmentalReverb;

        // Pointer to the EnvironmentalReverb Object
        // which is returned to the UI for Manipulation
        CEnvironmentalReverb* iTransEnvironmentalReverb;

        // Pointer to the Preset Repository
        CRepository* iPresetRepository;
   };

// CENVIRONMENTALREVERBUTILITY_H
#endif

// End of File
