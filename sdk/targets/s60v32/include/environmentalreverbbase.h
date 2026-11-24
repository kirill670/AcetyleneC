/*
* ==============================================================================
*  Name        : EnvironmentalReverbBase.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Environmental Reverb effect class.
*  Version     : %version: 5 %
*
*  Copyright © 2006 Nokia. All rights reserved.
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

#ifndef CENVIRONMENTALREVERB_H
#define CENVIRONMENTALREVERB_H

// INCLUDES

#include <e32base.h>
#include <AudioEffectBase.h>
#include <EnvironmentalReverbData.h>
#include <MCustomInterface.h>

const TUid KUidEnvironmentalReverbEffect = {0x10203837};

// FORWARD DELCARATION
class CMdaAudioConvertUtility;
class CMdaAudioPlayerUtility;
class CMdaAudioRecorderUtility;
class CMdaAudioInputStream;
class CMdaAudioOutputStream;
class CMdaAudioToneUtility;
class CCustomCommandUtility;
class CCustomInterfaceUtility;
class CMMFDevSound;
class CMidiClientUtility;
class CDrmPlayerUtility;
class CVideoPlayerUtility;

// CLASS DECLARATION

/**
*  This is the Environmental Reverb effect class for managing reverb settings.
*
*  
*  
*/

class CEnvironmentalReverb : public CAudioEffect
    {

    public:     //New Functions

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL();

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to a convert utility
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMdaAudioConvertUtility& aUtility );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to an audio input stream utility
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMdaAudioInputStream& aUtility );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to an audio output stream utility
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMdaAudioOutputStream& aUtility );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to an audio player utility
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMdaAudioPlayerUtility& aUtility );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to an audio record utility
        * @param aRecordStream ETrue if the effect is to be applied to the recording,
        *                      EFalse if the effect is to be applied only to the playback
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMdaAudioRecorderUtility& aUtility, TBool aRecordStream );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to an audio tone utility
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMdaAudioToneUtility& aUtility );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aDevSound A reference to a DevSound instance
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMMFDevSound& aDevSound );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to a custom command utility
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CCustomCommandUtility* aUtility );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aCustomInterface A reference to a custom interface
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( MCustomInterface& aCustomInterface );

        /**
        * Factory function for creating the audio reverb object.
        * 
        * @param aUtility A reference to a CMidiClientUtility object
        * @return pointer to CEnvironmentalReverb object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CMidiClientUtility& aUtility );

        /**
        * Factory function for creating the audio equalizer object.
        * 
        * @param CDrmPlayerUtility A reference to a CDrmPlayerUtility object
        * @return pointer to CAudioEqualizer object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CDrmPlayerUtility& aUtility );

        /**
        * Factory function for creating the audio equalizer object.
        * 
        * @param CVideoPlayerUtility A reference to a CVideoPlayerUtility object
        * @return pointer to CAudioEqualizer object
        */
        IMPORT_C static CEnvironmentalReverb* NewL( CVideoPlayerUtility& aUtility );

        /**
        *
        * Destructor
        */
        IMPORT_C virtual ~CEnvironmentalReverb();

        /**
        * Gets the decay HF Ratio in hundredths
        * 
        * @return decay HF Ratio
        */
        IMPORT_C TUint32 DecayHFRatio() const;

        /**
        * Gets the reverb decay HF Ratio minimum and maximum in hundredths.
        * 
        * @param aMin Minimum decay HF Ratio
        * @param aMax Maximum decay HF Ratio
        */
        IMPORT_C void DecayHFRatioRange(TUint32& aMin, TUint32& aMax);

        /**
        * Gets the decay time in milliseconds
        * 
        * @return decay time
        */
        IMPORT_C TUint32 DecayTime() const;

        /**
        * Gets the allowable reverb decay time range in milliseconds.
        * 
        * @param aMin Minimum decay time in milliseconds
        * @param aMax Maximum decay time in milliseconds
        */
        IMPORT_C void DecayTimeRange(TUint32& aMin, TUint32& aMax);

        /**
        * Gets the density current value as a percentage in hundredths
        * 
        * @return density value
        */
        IMPORT_C TUint32 Density() const;

        /**
        * Gets the diffusion current value as a percentage in hundredths.
        * 
        * @return diffusion value
        */
        IMPORT_C TUint32 Diffusion() const;

        /**
        * Gets the reverb reflections delay in ms.
        * 
        * @return reverb reflections delay
        */
        IMPORT_C TUint32 ReflectionsDelay() const;

        /**
        * Gets the reverb reflections delay maximum in milliseconds.
        * 
        * @return reverb reflections delay maximum
        */
        IMPORT_C TUint32 ReflectionsDelayMax() const;

        /**
        * Gets the reverb reflections level in mB
        * 
        * @return Reverb reflections level
        */
        IMPORT_C TInt32 ReflectionsLevel() const;

        /**
        * Gets the reverb reflections level maximum and minimum in mB
        * 
        * @param aMin Minimum reflections level
        * @param aMax Maximum reflections level
        */
        IMPORT_C void ReflectionLevelRange( TInt32& aMin, TInt32& aMax );

        /**
        * Gets the reverb delay in milliseconds
        * 
        * @return reverb delay
        */
        IMPORT_C TUint32 ReverbDelay() const;

        /**
        * Gets the reverb delay maximum in milliseconds
        * 
        * @return reverb delay maximum
        */
        IMPORT_C TUint32 ReverbDelayMax() const;

        /**
        * Gets the reverb current level in mB
        * 
        * @return reverb current level
        */
        IMPORT_C TInt32 ReverbLevel() const;

        /**
        * Gets the reverb current level maximum and minimum in mB
        * 
        * @param aMin Minimum current level
        * @param aMax Maximum current level
        * @return -
        */
        IMPORT_C void ReverbLevelRange( TInt32& aMin, TInt32& aMax );

        /**
        * Gets the room HF level current ratio
        * 
        * @return room HF level ratio
        */
        IMPORT_C TInt32 RoomHFLevel() const;

        /**
        * Gets the room HF level maximum and minimum ratios
        * 
        * @param aMin Minimum current room HF level
        * @param aMax Maximum current room HF level
        * @return -
        */
        IMPORT_C void RoomHFLevelRange( TInt32& aMin, TInt32& aMax );

        /**
        * Gets the room level current value in mB
        * 
        * @return room level value
        */
        IMPORT_C TInt32 RoomLevel() const;

        /**
        * Gets the room level maximum and minimum in mB
        * 
        * @param aMin Minimum current room level
        * @param aMax Maximum current room level
        * @return -
        */
        IMPORT_C void RoomLevelRange( TInt32& aMin, TInt32& aMax );

        /**
        * Sets the decay HF Ratio in hundredths
        * 
        * @param aDecayHFRatio The decay high frequence ratio in hundredths
        * @return -
        */
        IMPORT_C void SetDecayHFRatioL( TUint32 aDecayHFRatio );

        /**
        * Sets the decay time in millisecond
        * 
        * @param aDecayTime Decay time in ms
        */
        IMPORT_C void SetDecayTimeL( TUint32 aDecayTime );

        /**
        * Sets the density value as percentage in hundredths
        * 
        * @param aDensity The density.
        */
        IMPORT_C void SetDensityL( TUint32 aDensity );

        /**
        * Sets the diffusion value as a percentage in hundredths
        * 
        * @param aDiffusion The diffusion.
        */
        IMPORT_C void SetDiffusionL( TUint32 aDiffusion );

        /**
        * Sets the reverb reflections delay
        * 
        * @param aRefectionsDelay The reflection delay in ms.
        */
        IMPORT_C void SetReflectionsDelayL( TUint32 aReflectionsDelay );

        /**
        * Sets the reverb reflections level in milli-dB
        * 
        * @param aRefectionsLevel The reflection level in mB
        */
        IMPORT_C void SetReflectionsLevelL( TInt32 aReflectionsLevel );

        /**
        * Sets the reverb delay
        * 
        * @param aReverbDelay The reverb delay in ms
        */
        IMPORT_C void SetReverbDelayL( TUint32 aReverbDelay );

        /**
        * Sets the reverb level
        * 
        * @param aReverbLevel The reverb level in mB
        */
        IMPORT_C void SetReverbLevelL( TInt32 aReverbLevel );

        /**
        * Sets the room HF level ratio
        * 
        * @param aRoomHFLevel The room high frequency ratio
        */
        IMPORT_C void SetRoomHFLevelL( TInt32 aRoomHFLevel );

        /**
        * Sets the room level value in milli-dB
        * 
        * @param aRoomLevel The room level
        */
        IMPORT_C void SetRoomLevelL( TInt32 aRoomLevel );

        /**
        * Gets the total delay maximum in milliseconds
        * 
        * @return reverb delay maximum
        */
        IMPORT_C TUint32 DelayMax() const;

    public: // functions from base class

        /*
        * From CAudioEffect
        * Get the unique identifier of the audio effect
        * 
        * @return Unique identifier
        */
        IMPORT_C TUid Uid() const;

    protected:  // Functions from base classes

        /**
        * From CAudioEffect
        * Create a package of the effect data
        * 
        * @return A descriptor containing the effect data.
        */
        IMPORT_C const TDesC8& DoEffectData();

        /**
        * From CAudioEffect
        * Internal function to unpack effect data
        * 
        * @param aEffectDataBuffer Descriptor containing packed effect data
        * @return -
        */
        IMPORT_C void SetEffectData( const TDesC8& aEffectDataBuffer );

    protected:

        /**
        * Private C++ constructor for this class.
        * 
        * @return   -
        */
        IMPORT_C CEnvironmentalReverb();

    protected:

        // Reverb data structure
        TEfEnvironmentalReverb iReverbData;
        // Data package sent to server
        TEfEnvReverbDataPckg iDataPckgTo;
        // Data package received from server
        TEfEnvReverbDataPckg iDataPckgFrom;

    protected:    // Friend classes

        friend class CEnvironmentalReverbMessageHandler;
        friend class CEnvironmentalReverbUtility;

    };

// of CENVIRONMENTALREVERB_H
#endif

// End of File
