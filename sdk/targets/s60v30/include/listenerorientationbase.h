/*
* ==============================================================================
*  Name        : ListenerOrientationBase.h
*  Part of     : Effects Framework
*  Description : This is the definition of the listener location effect class.
*
*  Version     : 2
*
*  Copyright © 2004 Nokia Corporation.
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

#ifndef CLISTENERORIENTATION_H
#define CLISTENERORIENTATION_H

// INCLUDES

#include <e32base.h>
#include <OrientationBase.h>
#include <MCustomInterface.h>

const TUid KUidListenerOrientationEffect = {0x1020382E};

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

// CLASS DECLARATION

/**
*  This is the listener location effect class for managing audio location settings.
*
*  @lib ListenerOrientationEffect.lib
*  @since 3.0
*/

class CListenerOrientation : public COrientation
	{

	public:		// Constructors and Destructor

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to a convert utility
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMdaAudioConvertUtility& aUtility );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to an audio input stream utility
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMdaAudioInputStream& aUtility );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to an audio output stream utility
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMdaAudioOutputStream& aUtility );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to an audio player utility
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMdaAudioPlayerUtility& aUtility );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to an audio record utility
        * @param aRecordStream ETrue if the effect is to be applied to the recording,
        *                      EFalse if the effect is to be applied only to the playback
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMdaAudioRecorderUtility& aUtility, TBool aRecordStream );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to an audio tone utility
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMdaAudioToneUtility& aUtility );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aDevSound A reference to a DevSound instance
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CMMFDevSound& aDevSound );

	    /**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aUtility A reference to a custom command utility
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( CCustomCommandUtility* aUtility );

		/**
        * Factory function for creating the listener location object.
        * @since 3.0
        * @param aCustomInterface A reference to a custom interface
        * @return pointer to CListenerOrientation object
        */
		IMPORT_C static CListenerOrientation* NewL( MCustomInterface& aCustomInterface );

		/**
        *
        * Destructor
        */
		IMPORT_C virtual ~CListenerOrientation();

	public: // functions from base class

		/*
		* From CAudioEffect
        * Get the unique identifier of the audio effect
        * @since 3.0
        * @return Unique identifier
        */
		IMPORT_C TUid Uid() const;

	protected:

		/**
		* Private C++ constructor for this class.
        * @since	3.0
        * @param	aEffectObserver	reference to event observer object
        * @return	-
        */
		IMPORT_C CListenerOrientation();

    protected:    // Friend classes

		friend class CListenerOrientationMessageHandler;

	};

#endif	// of CLISTENERORIENTATION_H

// End of File
