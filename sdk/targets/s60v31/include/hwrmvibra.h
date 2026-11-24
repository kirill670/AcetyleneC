/*
* ==============================================================================
*  Name        : HWRMVibra.h
*  Part of     : HW Resources and Enhancements / HWResourceManager
*  Interface   : SDK
*  Description : This file contains the header of the 
*                CHWRMVibra class.
*  Version     : 1
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
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

#ifndef HWRMVIBRA_H
#define HWRMVIBRA_H

// INCLUDES

// CONSTANTS

/**
* Minimum allowed intensity setting for vibra
*/
const TInt KHWRMVibraMinIntensity(-100);

/**
* Maximum allowed intensity setting for vibra
*/
const TInt KHWRMVibraMaxIntensity(100);

/**
* Maximum allowed duration value.
*
* Note that duration probably has device specific
* maximum duration that is much lower.
*/
const TInt KHWRMVibraMaxDuration( (KMaxTInt / 1000) - 1 );

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class MHWRMVibraObserver;

// CLASS DECLARATIONS

/**
* Base class of Vibra Client API of HWRM
*
* The HWRM Vibra API provides the ability to control the device vibra.
*
* Every new call of the Vibra API method stops all ongoing vibra 
* control orders. 
*
* The interface contains synchronous methods that will block the client application.
*
*  @lib HWRMVIBRACLIENT.DLL
*  @since Series 60 3.0
*/
class CHWRMVibra : public CBase
    {
    public: // enums
        /**
        * Vibration setting in the user profile.
        */
        enum TVibraModeState 
            {
            EVibraModeUnknown = 0, ///< Not initialized yet or there is an error condion.
            EVibraModeON,          ///< Vibration setting in the user profile is on.
            EVibraModeOFF          ///< Vibration setting in the user profile is off.
            };

        /**
        * Status of the vibration feature
        */
        enum TVibraStatus 
            {
            EVibraStatusUnknown = 0, ///< Vibra is not initialized yet or status is uncertain 
                                     ///< because of an error condition.
            EVibraStatusNotAllowed,  ///< Vibra is set off in the user profile or some
                                     ///< application is specifically blocking vibra.
            EVibraStatusStopped,     ///< Vibra is stopped.
            EVibraStatusOn           ///< Vibra is on.
            };
            
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor for implementation class.
        *
        * @return New CHWRMVibra implementing instance.
        * @exception KErrNotSupported Device doesn't support vibration feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMVibra* NewL();
        
        /**
        * Two-phased constructor for implementation class. 
        * Leaves instance to cleanup stack.
        *
        * @return New CHWRMVibra implementing instance.
        * @exception KErrNotSupported Device doesn't support vibration feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMVibra* NewLC();

        /**
        * Two-phased constructor for implementation class.
        * Use this method for creating a vibra client with callbacks.
        *
        * @param aCallback Pointer to callback instance
        * @return New CHWRMVibra implementing instance.
        * @exception KErrNotSupported Device doesn't support vibration feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMVibra* NewL(MHWRMVibraObserver* aCallback);
        
        /**
        * Two-phased constructor for implementation class. 
        * Use this method for creating a vibra client with callbacks.
        * Leaves instance to cleanup stack.
        *
        * @param aCallback Pointer to callback instance
        * @return New CHWRMVibra implementing instance.
        * @exception KErrNotSupported Device doesn't support vibration feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMVibra* NewLC(MHWRMVibraObserver* aCallback);

    public: // New functions

    	/**
    	* Reserves vibration feature exclusively for this client.
    	* A higher priority client may cause lower priority client reservation
    	* to be temporarily suspended. Commands can still be issued in suspended 
    	* state, but they will not be acted upon unless suspension is lifted
    	* within specified duration.
    	* The suspended client will not get any notification about suspension.
    	* If vibra is already reserved by a higher or equal priority application, 
    	* reserving will still succeeds, but reservation is immediately suspended.
    	*
    	* Calling this method is equal to call ReserveVibraL(EFalse, EFalse),
    	* i.e. any previously frozen state will not be restored and CCoeEnv
    	* background/foreground status is always used to control further reservations.
    	*
    	* @exception KErrAccessDenied if no CCoeEnv present.
    	*            KErrNotReady if trying to reserve while on background.
        *            KErrNoMemory if there is a memory allocation failure. 
    	*/
    	virtual void ReserveVibraL()=0;
    	
    	/**
    	* Reserves vibration feature exclusively for this client.
    	* A higher priority client may cause lower priority client reservation
    	* to be temporarily suspended. Commands can still be issued in suspended 
    	* state, but they will not be acted upon unless suspension is lifted
    	* within specified duration.
    	* The suspended client will not get any notification about suspension.
    	* If vibra is already reserved by a higher or equal priority application, 
    	* reserving will still succeeds, but reservation is immediately suspended.
    	*
    	*
    	* @param aRestoreState If ETrue, the state frozen on last release will be
    	*          restored upon successful reservation.
    	*         I.e. if vibra was on when it was released by this client the last
    	*          time, it would continue the vibrating upon successful reservation.
    	*         For the first reservation of each session this parameter is always
    	*          considered EFalse regardless of what is supplied, as there is no
    	*          previous frozen state to restore.
    	* @param aForceNoCCoeEnv If EFalse, then reservation requires that
    	*          this client has the keyboard focus at the time of reservation
    	*          and vibra will be automatically released and re-reserved based on
    	*          the keyboard focus status of the this client. This also implies
    	*          that CCoeEnv::Static() != NULL is required.
    	*         If ETrue, the client will not require CCoeEnv to
    	*          be present nor does it automatically reserve/release vibra 
    	*          by depending on foreground/background status of the client.
    	*         Only trusted clients are allowed to set this flag to ETrue.
    	*         Client is considered trusted if it has nonstandard priority
    	*          defined in the vibra policy.
    	*
    	* @exception KErrAccessDenied if aForceNoCCoeEnv is ETrue and client is not
    	*             trusted.
    	*            KErrBadHandle if aForceNoCCoeEnv is EFalse and no CCoeEnv present.
    	*            KErrNotReady if trying to reserve while on background and 
    	*             aForceNoCCoeEnv is EFalse.
        *            KErrNoMemory if there is a memory allocation failure. 
    	*/
    	virtual void ReserveVibraL(TBool aRestoreState, TBool aForceNoCCoeEnv)=0;

    	/**
    	* Releases vibration feature if it was previously reserved for this client.
    	* If this client has not reserved vibration feature, does nothing.
    	* If vibra is on when it is released and no other client has a suspended 
    	* reservation, vibra is stopped.
    	*/
    	virtual void ReleaseVibra()=0;


        /**
        * Starts the device vibration feature with the product specific default
        * intensity.
        * If StartVibraL is called again before the first vibration completes
        * then the first vibration is interrupted and the second vibrations
        * starts immediately -- i.e. The periods of vibration are not cumulative.
        *
        * The vibration can be interrupted with the method StopVibraL before
        * the specified interval has elapsed. 
        *
        * Vibra settings of the vibration feature in the user profile 
        * must be active. 
        *
        * Note: The device may have implementation defined or hardware imposed
        *       limits to the duration of the vibration feature. In such 
        *       circumstances any vibration will cut off at that limit even if
        *       the duration parameter is greater than the limit.
        *
        * @param aDuration Duration of the vibration measured in milliseconds. 
        *                  A value of 0 specifies that the vibration should
        *                  continue indefinitly and should be stopped with a 
        *                  call to StopVibraL. Duration can have maximum value
        *                  of KHWRMVibraMaxDuration.
        *
        * @exception KErrArgument if duration is invalid.
        *            KErrAccessDenied if vibration setting in the user profile
        *             is not set.
        *            KErrBadHandle if vibra session has been invalidated.
        *            KErrLocked if vibra is locked down because too much 
        *             continuous use or explicitly blocked by for example
        *             some vibration sensitive accessory.
        *            KErrTimedOut if timeout occurred in controlling vibra.
        *            KErrInUse if vibra is not reserved to this client but it is
        *             reserved to some other client.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
        * @see MHWRMVibraObserver
        */
        virtual void StartVibraL(TInt aDuration)=0;
		
        /**
        * Starts the device vibration feature. If StartVibraL is called again before
        * the first vibration completes then the first vibration is interrupted
        * and the second vibrations starts immediately -- i.e. The periods of
        * vibration are not cumulative.
        *
        * The vibration can be interrupted with the method StopVibraL before
        * the specified interval has elapsed.
        *
        * Vibra settings of the vibration feature in the user profile 
        * must be active. 
        *
        * Note: The device may have implementation defined or hardware imposed
        *       limits to the duration of the vibration feature. In such 
        *       circumstances any vibration will cut off at that limit even if
        *       the duration parameter is greater than the limit.
        *
        * @param aDuration Duration of the vibration measured in milliseconds. 
        *                  A value of 0 specifies that the vibration should
        *                  continue indefinitly and should be stopped with a 
        *                  call to StopVibraL.  Duration can have maximum value
        *                  of KHWRMVibraMaxDuration.
        * @param aIntensity Intensity of the vibra in decimal is -100 to 100,
        *                   which shows the percentage of the vibra motor full
        *                   rotation speed. When intensity is negative, 
        *                   the vibra motor rotates in the negative direction.
        *                   When intensity is positive, the vibra motor rotates
        *                   in the positive direction. Value 0 stops the vibra.
        *                   NOTE: The device might have hardware-imposed limits
        *                         on supported vibra intensity values, so actual
        *                         effect might vary between different hardware.
        * @exception KErrNotSupported if the device doesn't support user-defined 
        *             vibra intensity.
        *            KErrArgument if one of the parameters is out of range.
        *            KErrAccessDenied if vibration setting in the user profile
        *             is not set.
        *            KErrBadHandle if vibra session has been invalidated.
        *            KErrLocked if vibra is locked down because too much 
        *             continuous use or explicitly blocked by for example
        *             some vibration sensitive accessory.
        *            KErrTimedOut if timeout occurred in controlling vibra.
        *            KErrInUse if vibra is not reserved to this client but it is
        *             reserved to some other client.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
        * @see MHWRMVibraObserver
        */
	    virtual void StartVibraL(TInt aDuration, TInt aIntensity)=0;
	    
	    /**
        * Interrupts the device vibration that is started with the StartVibraL
        * method immediately.
        *
        * @exception KErrBadHandle if vibra session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling vibra.
        *            KErrInUse if vibra is not reserved to this client but it is
        *             reserved to some other client.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
        * @see MHWRMVibraObserver
        */		
        virtual void StopVibraL()=0; 
		
        /**
        * This method retrieves the current settings of the vibration feature
        * in the user profile. The developer can check the Vibra settings 
        * in the profile and if there is no Vibra active but it is needed by 
        * the game then the user can be informed.
        *
        * @return TVibraModeState indicating the current vibra mode setting.
        *
        * @see MHWRMVibraObserver
        */
        virtual TVibraModeState VibraSettings() const=0;

        /**
        * This method retrieves the current vibra status. 
        *
        * @return TVibraStatus indicating the current vibra status
        * 
        * @see MHWRMVibraObserver
        */
        virtual TVibraStatus VibraStatus() const=0;
    };
    
/**
*  An interface the developer implements for handling notification events. 
*
*  @since 3.0
*/
class MHWRMVibraObserver
    {    
    public:
        
        /** 
        * Called when the vibration setting in the user profile is changed.
        *
        * @param aStatus Indicates the new setting.
        *
        * @see CHWRMVibra::TVibraModeState
        */
        virtual void VibraModeChanged(CHWRMVibra::TVibraModeState aStatus) = 0;
        
        /** 
        * Called when the device vibration feature state changes
        *
        * @param aStatus Indicates vibra status.
        *
        * @see CHWRMVibra::TVibraStatus
		*/
        virtual void VibraStatusChanged(CHWRMVibra::TVibraStatus aStatus) = 0;
	};


// HWRMVIBRA_H   
#endif
            
// End of File
