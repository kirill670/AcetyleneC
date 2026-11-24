/*
* ============================================================================
*  Name     : AlarmObserver.h
*  Part of  : EikAlert
*
*  Description:
*     I/F class for CEikAlarmControl
*
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef ALARMOBSERVER_H
#define ALARMOBSERVER_H

//  INCLUDES
#include <eiksvfty.h>


// FORWARD DECLARATIONS
class CEikAlmControlSupervisor;
class CEikServAppUiBase;


// CLASS DECLARATION

/**
*  It is I/F class for CEikAlarmControl
*/
class MAlarmObserver :public MEikServAlarm
    {
    public: // New functions
        /**
        * Two-phased constructor.
        * @param aSupervisor CEikAlmControlSupervisor class
        * @param aAppUi CEikServAppUiBase class
        */
        virtual void ConstructL(
            CEikAlmControlSupervisor* aSupervisor,
            CEikServAppUiBase* aAppUi) = 0;

    };

#endif      // ALARMOBSERVER_H

// End of File
