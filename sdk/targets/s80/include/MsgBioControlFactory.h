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
 *           BioControl Factory
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
 * $Archive: /Erin messaging/Implementation/MSGEDITORUTILS/Inc/MsgBioControlFactory.h $
 * 
 * $Revision: 1 $
 * 
 * 
 * Copyright (c) 1998. Nokia Mobile Phones
 * 
 * 
 * Change History:
 * 
 * History: MsgBioControlFactory.h $
 * 
 *
 *---------------------------------------------------------------------------
 */



/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Defines a bio control factory.

-----------------------------------------------------------------------------
*/

#if !defined(__MSGBIOCONTROLFACTORY_H__)
#define __MSGBIOCONTROLFACTORY_H__


// INCLUDES 

#include <e32std.h>
#include <e32base.h>                        // for CBase
#include <MSVSTD.H>                         // for TMsvId

// FORWARD DECLARATIONS

class CMsgBioControl;
class MMsgBioControlObserver;
class CBIODatabase;
class RFs;
class TZoomFactor;
class CMsvSession;

// CLASS DEFINITIONS

class CMsgBioControlFactory : public CBase
	{
    public:
        ~CMsgBioControlFactory();
        static CMsgBioControlFactory* NewL();
        CMsgBioControl* CreateControlL(MMsgBioControlObserver& aBioControlObserver, 
            const TUid& aBioMsgType, 
            RFs& aFs, TZoomFactor& aZoomFactor, 
            CMsvSession& aSession, TMsvId aId);

    private:
        CMsgBioControlFactory();
        void ConstructL();
        void LoadLibraryL(RFs& aFs, const TUidType& aUidType);
        TInt FindFullName(RFs& aFs, const TUidType& aUidType, TDes& aFullName);

    private: // not available
        CMsgBioControlFactory(const CMsgBioControlFactory& aSource);
        const CMsgBioControlFactory& operator=(const CMsgBioControlFactory& aSource);

    private:
	    RLibrary                iControlDllLibrary;
	    };

#endif // __MSGBIOCONTROLFACTORY_H__

// End of File
