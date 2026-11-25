/*
 * NOKIA MOBILE PHONES
 * DIGITAL CONVERGENCE
 * LINDA SW
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *           BIO Control
 *           -------------------------
 * 
 *           SW Include Document - C++
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Module name:    MsgEditorUtils
 * 
 * $Archive: /Erin messaging/Implementation/MSGEDITORUTILS/Inc/MsgBioControl.h $
 * 
 * $Revision: 1 $
 * 
 * 
 * Copyright (c) 1998. Nokia Mobile Phones
 * 
 * 
 * Change History:
 * 
 * History: MsgBioControl.h $
 * 
 *
 *---------------------------------------------------------------------------
 */



/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Defines a base bio control.

-----------------------------------------------------------------------------
*/

#if !defined(__MSGBIOCONTROL_H__)
#define __MSGBIOCONTROL_H__


// INCLUDES 

#include <coecntrl.h>           // for CCoeControl
#include <mmsgbiocontrol.h>     // for MMsgBioControl
#include <MSVSTD.H>             // for TMsvId                   


// FORWARD DECLARATIONS

class TZoomFactor; 
class MMsgBioControlObserver;
class CMsvSession;

// CLASS DEFINITIONS

class CMsgBioControl : public CCoeControl, public MMsgBioControl
	{
    public:
        IMPORT_C ~CMsgBioControl();
        IMPORT_C CMsgBioControl(MMsgBioControlObserver& aObserver, TZoomFactor& aZoomFactor, CMsvSession& aSession, TMsvId aId);
        IMPORT_C virtual void MMsgBioControl_Reserved1();

    private: // not available
        CMsgBioControl();
        CMsgBioControl(const CMsgBioControl& aSource);
        const CMsgBioControl& operator=(const CMsgBioControl& aSource);

    protected:
        MMsgBioControlObserver&         iBioControlObserver;
        TZoomFactor&                    iZoomFactor;
        CMsvSession&                    iSession;
        TMsvId                          iId;
	    };

#endif // __MSGBIOCONTROL_H__

// End of File
