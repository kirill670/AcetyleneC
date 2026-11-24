/*
* ==============================================================================
*  Name        : HWRMLight.h
*  Part of     : HW Resources and Enhancements / HWResourceManager
*  Interface   : SDK
*  Description : This file contains the header of the 
*                CHWRMLight class.
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

#ifndef HWRMLIGHT_H
#define HWRMLIGHT_H

// INCLUDES

// CONSTANTS

/**
* Minimum allowed intensity setting for Light
*/
const TInt KHWRMLightMinIntensity(1);

/**
* Maximum allowed intensity setting for Light
*/
const TInt KHWRMLightMaxIntensity(100);

/**
* Indicates default intensity in various methods
*/
const TInt KHWRMDefaultIntensity(0);

/**
* Maximum allowed duration value.
*/
const TInt KHWRMLightMaxDuration( (KMaxTInt / 1000) - 1 );

/**
* Infinite duration value
*/
const TInt KHWRMInfiniteDuration(0);

/**
* Indicates device default Blink cycle time
*/
const TInt KHWRMDefaultCycleTime(0);


// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class MHWRMLightObserver;

// CLASS DECLARATIONS

/**
*  Base class of Light Client API of HWRM
*
* The HWRM Light API provides the ability to control the device display light
* as well as the keyboard illumination. 
*
* Every new call of the light API method stops all ongoing light
* control orders. Light state after duration based orders expire is the state
* specified by the last non-duration based order.
*
* The interface contains synchronous methods that will block the client application.
*
*  @lib HWRMLIGHTCLIENT.DLL
*  @since Series 60 3.0
*/
class CHWRMLight : public CBase
    {
    public: // enums
		/**
		* Possible light states that can be get for the different light targets
		*/
		enum TLightStatus
			{
			ELightStatusUnknown = 0, ///< For debugging/development and signaling an error conditions
			ELightOn,                ///< Light state switch to light on
			ELightOff,               ///< Light state switch to light off
			ELightBlink,             ///< Light state switch to light blinking
			};

        /**
        * Possible light targets. 
        * Targets can be used as bitmask. Some common masks are provided as enum.
        * 
        * Note that all targets are not supported by all devices.
        * Attempting to use unsupported target will result in
        * KErrNotSupported.
        *
        * At least one target must be defined.
        */
        enum TLightTarget
            {
            ENoTarget                    = 0,   ///< No target. Not a valid target value, used only
                                                ///< for error checking.
            
            EPrimaryDisplay              = 1,   ///< Primary display of the device.
            EPrimaryKeyboard             = 2,   ///< Primary keyboard of the device. 
            EPrimaryDisplayAndKeyboard   = 3,   ///< Both primary display and the 
                                                ///< primary keyboard of the device.  
            
            ESecondaryDisplay            = 4,   ///< Secondary display of the device.
            ESecondaryKeyboard           = 8,   ///< Secondary keyboard of the device. 
            ESecondaryDisplayAndKeyboard = 12,  ///< Both secondary display and the 
                                                ///< secondary keyboard of the device.  
                                                
            ECustomTarget1               = 16,  ///< Device specific custom target 1.
            ECustomTarget2               = 32,  ///< Device specific custom target 2.
            ECustomTarget3               = 64,  ///< Device specific custom target 3.
            ECustomTarget4               = 128, ///< Device specific custom target 4.
            };
            
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor for implementation class.
        *
        * @return New CHWRMLight implementing instance.
        * @exception KErrNotSupported Device doesn't support Light feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMLight* NewL();
        
        /**
        * Two-phased constructor for implementation class. 
        * Leaves instance to cleanup stack.
        *
        * @return New CHWRMLight implementing instance.
        * @exception KErrNotSupported Device doesn't support Light feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMLight* NewLC();

        /**
        * Two-phased constructor for implementation class.
        * Use this method for creating a Light client with callbacks.
        *
        * @param aCallback Pointer to callback instance
        * @return New CHWRMLight implementing instance.
        * @exception KErrNotSupported Device doesn't support Light feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMLight* NewL(MHWRMLightObserver* aCallback);
        
        /**
        * Two-phased constructor for implementation class. 
        * Use this method for creating a Light client with callbacks.
        * Leaves instance to cleanup stack.
        *
        * @param aCallback Pointer to callback instance
        * @return New CHWRMLight implementing instance.
        * @exception KErrNotSupported Device doesn't support Light feature.
        *            KErrNoMemory if there is a memory allocation failure. 
        */
        IMPORT_C static CHWRMLight* NewLC(MHWRMLightObserver* aCallback);

    public: // New functions

    	
    	/**
    	* Reserves light target exclusively for this client.
    	* A higher priority client may cause lower priority client reservation
    	* to be temporarily suspended. Commands can still be issued in suspended 
    	* state, but they will not be acted upon unless suspension is lifted
    	* within specified duration.
    	* The suspended client will not get any notification about suspension.
    	* If light target is already reserved by a higher or equal priority application, 
    	* reserving will still succeeds, but reservation is immediately suspended.
    	*
    	* Calling this method is equal to call ReserveLightL( aTarget, EFalse, EFalse),
    	* i.e. any previously frozen state will not be restored and CCoeEnv
    	* background/foreground status is always used to control further reservations.
    	*
		* @param aTarget Defines which light should be reserved. Multiple lights can
		*          be specified with using bitwise-or.
    	*
    	* @exception KErrNotSupported One or more of specified targets are not supported.
    	*            KErrAccessDenied if no CCoeEnv present.
    	*            KErrNotReady if trying to reserve while on background.
        *            KErrNoMemory if there is a memory allocation failure. 
		*
	 	* @see TLightTarget
    	*/
    	virtual void ReserveLightL(TInt aTarget)=0;
    	
    	/**
    	* Reserves light target exclusively for this client.
    	* A higher priority client may cause lower priority client reservation
    	* to be temporarily suspended. Commands can still be issued in suspended 
    	* state, but they will not be acted upon unless suspension is lifted
    	* within specified duration.
    	* The suspended client will not get any notification about suspension.
    	* If light target is already reserved by a higher or equal priority application, 
    	* reserving will still succeeds, but reservation is immediately suspended.
    	*
    	*
		* @param aTarget Defines which light should be reserved. Multiple lights can
		*          be specified with using bitwise-or.
    	* @param aRestoreState If ETrue, the state frozen on last release will be
    	*          restored upon successful reservation.
    	*         I.e. if light was blinking when it was released by this client the last
    	*          time, it would start blinking again upon successful reservation.
    	*         For the first reservation of each session this parameter is always
    	*          considered EFalse regardless of what is supplied, as there is no
    	*          previous frozen state to restore.
    	* @param aForceNoCCoeEnv If EFalse, then reservation requires that
    	*          this client is on the foreground at the time of reservation
    	*          and light target will be automatically released and re-reserved based on
    	*          background/foreground status of the this client. This also implies
    	*          that CCoeEnv::Static() != NULL is required.
    	*         If ETrue, the client will not require CCoeEnv to
    	*          be present nor does it automatically reserve/release light
    	*          by depending on foreground/background status of the client.
    	*         Only trusted clients are allowed to set this flag to ETrue.
    	*         Client is considered trusted if it has nonstandard priority
    	*          defined in the lights policy.
    	*
    	* @exception KErrNotSupported One or more of specified targets are not supported.
    	*            KErrAccessDenied if aForceNoCCoeEnv is ETrue and client is not
    	*             trusted.
    	*            KErrBadHandle if aForceNoCCoeEnv is EFalse and no CCoeEnv present.
    	*            KErrNotReady if trying to reserve while on background and 
    	*             aForceNoCCoeEnv is EFalse.
        *            KErrNoMemory if there is a memory allocation failure. 
		*
	 	* @see TLightTarget
    	*/
    	virtual void ReserveLightL(TInt aTarget, TBool aRestoreState, TBool aForceNoCCoeEnv)=0;

    	/**
    	* Releases light target if it was previously reserved for this client.
    	* If this client has not reserved any of the specified lights, 
    	* this method does nothing.
    	* Any reserved light targets that are released and have no other suspended
    	* clients will be reset to default state, which is either lights on or lights off, 
    	* depending on system inactivity time.
    	*
		* @param aTarget Defines which light should be released. Multiple lights can
		*          be specified with using bitwise-or.
		*
	 	* @see TLightTarget
    	*/
    	virtual void ReleaseLight(TInt aTarget)=0;


	    /** 
	    * The LightOnL method switches the specified target light on
	    * for infinite duration using default intensity. Lights will use fade-in.
	    *
		* @param aTarget Defines which light should be controlled. Multiple lights can
		*                 be specified with using bitwise-or.
		*
    	* @exception KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightOnL(TInt aTarget) = 0;

	    /** 
	    * The LightOnL method switches the specified target light on
	    * for the specified duration using default intensity. Lights will use fade-in.
	    *
		* @param aTarget   Defines which light should be controlled. Multiple lights can
		*                   be specified with using bitwise-or.
		* @param aDuration Duration of the time the light is switched on measured in milliseconds.
		*                   After the duration expires, the light state for target will be changed 
		*                    to whatever state was caused by the last infinite time duration call, or
		*                    default state determined by inactivity timer, in case there has not 
		*                    been a previous infinite time duration call in this session.
		*                   If the aDuration time is KHWRMInfiniteDuration then it
		*                    means an infinite value that has to be
		*                    stopped by calling of any of the other light control methods.
		*                   Duration can have maximum value of KHWRMLightMaxDuration.
		*
        * @exception KErrArgument aDuration is out of range.
        *            KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightOnL(TInt aTarget, 
		                      TInt aDuration) = 0;

	    /** 
	    * The LightOnL method switches the specified target light on
	    * for the specified duration using specified intensity. Fade-in can also be controlled.
	    *
		* @param aTarget    Defines which light should be controlled. Multiple lights can
		*                    be specified with using bitwise-or.
		* @param aDuration  Duration of the time the light is switched on measured in milliseconds.
		*                    After the duration expires, the light state for target will be changed 
		*                     to whatever state was caused by the last infinite time duration call, or
		*                     default state determined by inactivity timer, in case there has not 
		*                     been a previous infinite time duration call in this session.
		*                    If the aDuration time is KHWRMInfiniteDuration then it
		*                     means an infinite value that has to be
		*                     stopped by calling of any of the other light control methods.
		*                    Duration can have maximum value of KHWRMLightMaxDuration.
		* @param aIntensity Intensity of the light. If aIntensity is KHWRMDefaultIntensity, device default 
		*                     intensity will be used. 
		*                    Note: All devices might not support user defined intensity, in which case
		*                     device will behave in its default fashion.
		* @param aFadeIn    If ETrue, lights will not turn on instantly but instead smoothly fade-in.
		*                    Note: All devices will not support fade-in, in which case device will
		*                     behave in its default fashion.
		*
        * @exception KErrArgument One of the parameters is out of range.
        *            KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightOnL(TInt aTarget, 
		                      TInt aDuration, 
		                      TInt aIntensity,
		                      TBool aFadeIn) = 0;

	    /** 
	    * The LightBlinkL method blinks the target light(s) of the device for infinite duration
	    * using default intensity.
	   	*
		* @param aTarget        Defines which light should be controlled. Multiple lights can
		*                        be specified with using bitwise-or.
	   	*
        * @exception KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightBlinkL(TInt aTarget) = 0;

	    /** 
	    * The LightBlinkL method blinks the target light(s) of the device for specified duration
	    * using default intensity.
	   	*
		* @param aTarget        Defines which light should be controlled. Multiple lights can
		*                        be specified with using bitwise-or.
		* @param aDuration      Duration of the time the light is set to blink measured in milliseconds.
		*                        After the duration expires, the light state for target will be changed 
		*                         to whatever state was caused by the last infinite time duration call, or
		*                         default state determined by inactivity timer, in case there has not 
		*                         been a previous infinite time duration call in this session.
		*                        If the aTotalDuration time is KHWRMInfiniteDuration then it
		*                         means an infinite value that has to be
		*                         stopped by calling of any of the other light control methods.
		*                        Duration can have maximum value of KHWRMLightMaxDuration.
	   	*
        * @exception KErrArgument aDuration is out of range.
        *            KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightBlinkL(TInt aTarget, 
		                         TInt aDuration) = 0;

	    /** 
	    * The LightBlinkL method blinks the target light(s) of the device for specified duration
	    * using specified intensity. On- and Off-cycle times of the blinking can also be controlled.
	   	*
		* @param aTarget        Defines which light should be controlled. Multiple lights can
		*                        be specified with using bitwise-or.
		* @param aDuration      Duration of the time the light is set to blink measured in milliseconds.
		*                        After the duration expires, the light state for target will be changed 
		*                         to whatever state was caused by the last infinite time duration call, or
		*                         default state determined by inactivity timer, in case there has not 
		*                         been a previous infinite time duration call in this session.
		*                        If the aTotalDuration time is KHWRMInfiniteDuration then it
		*                         means an infinite value that has to be
		*                         stopped by calling of any of the other light control methods.
		*                        Duration can have maximum value of KHWRMLightMaxDuration.
	   	* @param aOnDuration    Duration time, measured in milliseconds, of how long the Light is
	   	*                         switched on in every Blink cycle.
		*                        Duration can have maximum value of KHWRMLightMaxDuration.
		*                        For device default cycle duration, use value KHWRMDefaultCycleTime.
		*                        If either of aOnDuration or aOffDuration is KHWRMDefaultCycleTime,
		*                         both must be KHWRMDefaultCycleTime.
		*                        Some devices might not support variable blink cycle times, in which
		*                         case default value will be substituted.
	   	* @param aOffDuration   Duration time, measured in milliseconds, of how long the Light
	   	*                         is switched off in every Blink cycle.
		*                        Duration can have maximum value of KHWRMLightMaxDuration.
        *                        For device default cycle duration, use value KHWRMDefaultCycleTime.
        *                        If either of aOnDuration or aOffDuration is KHWRMDefaultCycleTime,
		*                         both must be KHWRMDefaultCycleTime.
		*                        Some devices might not support variable blink cycle times, in which
		*                         case default value will be substituted.
		* @param aIntensity     Intensity of the light. If aIntensity is KHWRMDefaultIntensity, device default 
		*                         intensity will be used.
		*                        Note: All devices might not support user defined intensity, in which case
		*                         device will behave in its default fashion.
	   	*
        * @exception KErrArgument One of the parameters is out of range or otherwise invalid.
        *            KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightBlinkL(TInt aTarget, 
		                         TInt aDuration, 
		                         TInt aOnDuration, 
		                         TInt aOffDuration, 
		                         TInt aIntensity) = 0;

   	    /**
	    * The LightOffL method switches the device light off for the specified target for
	    * infinite duration. Lights will be switched off with fade-out.
		*
		* @param aTarget          Defines which light should be controlled. Multiple lights can
		*                          be specified with using bitwise-or.
		*
        * @exception KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightOffL(TInt aTarget) = 0;

   	    /**
	    * The LightOffL method switches the device light off for the specified target for
	    * the specified duration time. Lights will be switched off with fade-out.
		*
		* @param aTarget          Defines which light should be controlled. Multiple lights can
		*                           be specified with using bitwise-or.
		* @param aDuration        Duration of the time the light is switched off measured in milliseconds.
		*                          After the duration expires, the light state for target will be changed 
		*                           to whatever state was caused by the last infinite time duration call, or
		*                           default state determined by inactivity timer, in case there has not 
		*                           been a previous infinite time duration call in this session.
		*                          If the aDuration time is KHWRMInfiniteDuration then it 
		*                           means an infinite value that has to be
		*                           stopped by calling of any of the other light control methods.
		*                          Duration can have maximum value of KHWRMLightMaxDuration.
		*
        * @exception KErrArgument aDuration is out of range.
        *            KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightOffL(TInt aTarget, 
		                       TInt aDuration) = 0;

   	    /**
	    * The LightOffL method switches the device light off for the specified target for
	    * the specified duration time. Lights fade-out can also be controlled.
		*
		* @param aTarget          Defines which light should be controlled. Multiple lights can
		*                           be specified with using bitwise-or.
		* @param aDuration        Duration of the time the light is switched off measured in milliseconds.
		*                          After the duration expires, the light state for target will be changed 
		*                           to whatever state was caused by the last infinite time duration call, or
		*                           default state determined by inactivity timer, in case there has not 
		*                           been a previous infinite time duration call in this session.
		*                          If the aDuration time is KHWRMInfiniteDuration then it 
		*                           means an infinite value that has to be
		*                           stopped by calling of any of the other light control methods.
		*                          Duration can have maximum value of KHWRMLightMaxDuration.
		* @param aFadeOut         If ETrue, lights will not turn off instantly but instead smoothly fade-out
		*                          Note: All devices will not support fade-out, in which case device will
		*                           behave in its default fashion.
		*
        * @exception KErrArgument aDuration is out of range.
        *            KErrNotSupported One or more of specified targets are not supported.
        *            KErrBadHandle if light session has been invalidated.
        *            KErrTimedOut if timeout occurred in controlling light.
        *            KErrInUse if one or more of specified targets are not reserved for
        *             this client but are reserved for others.
        *            KErrNoMemory if there is a memory allocation failure. 
        *            KErrGeneral if there is a hardware error.
		*
	 	* @see TLightTarget
		*/
		virtual void LightOffL(TInt aTarget, 
		                       TInt aDuration, 
		                       TBool aFadeOut) = 0;
		                       
        /**
        * This method retrieves the current light status. 
        *
		* @param aTarget Defines which light status is returned. 
		*                 This method only supports single target, as different
		*                 targets might have different statuses.
        * @return TLightStatus indicating the current light status. If there is a problem or
        *         multiple targets were specified, CHWRMLight::ELightStatusUnknown is returned.
        * 
        * @see MHWRMLightObserver
	 	* @see TLightTarget
        */
        virtual TLightStatus LightStatus(TInt aTarget) const = 0;
        
        /**
        * This method retrieves the supported light targets of the device.
        * Any attempt to use or reserve unsupported targets will fail with
        * KErrNotSupported.
        *
        * @return Bitmask containing supported light targets.
        *
        * @see TLightTarget
        */
        virtual TInt SupportedTargets() const = 0;
    };
    
/**
*  An interface the developer implements for handling notification events. 
*
*  @since 3.0
*/
class MHWRMLightObserver
    {    
    public:
        
        /** 
        * Called when the device light status changes.
        * Note that if the light status for certain target changes
        * very rapidly, some state transitions might be missed.
        * It is however guaranteed that latest state is always obtained.
        *
        * @param aTarget Indicates target(s) the new status applies to.
        * @param aStatus Indicates light request status.
		*
	 	* @see CHWRMLight::TLightTarget
	 	* @see CHWRMLight::TLightStatus
		*/
        virtual void LightStatusChanged(TInt aTarget, 
                                        CHWRMLight::TLightStatus aStatus) = 0;
	};


// HWRMLIGHT_H   
#endif
            
// End of File
