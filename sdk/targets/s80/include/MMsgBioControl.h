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
 *           Bio Control API
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
 * $Archive: /Erin messaging/Implementation/MSGEDITORUTILS/Inc/MMsgBioControl.h $
 * 
 * $Revision: 1 $
 * 
 * 
 * Copyright (c) 1998. Nokia Mobile Phones
 * 
 * 
 * Change History:
 * 
 * History: MMsgBioControl.h $
 * 
 *
 *---------------------------------------------------------------------------
 */


/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Defines an interface for Bio controls.

-----------------------------------------------------------------------------
*/

#if !defined(__MMSGBIOCONTROL_H__)
#define __MMSGBIOCONTROL_H__


#include <e32std.h>
#include <e32base.h>
#include <msgeditor.hrh>                // for typedefs

// FORWARD DECLARATIONS

class CEikButtonGroupContainer;
class CGulIcon;
class CGlobalText;
class CRichText;

// CLASS DEFINITIONS

class MMsgBioControl
    {
    public:
        enum TMsgEvent
            {
            EMsgEventClose,
            EMsgEventSave,
            EMsgEventDelete,
            EMsgEventSend
            };

    public:
        virtual void SetAndGetSizeL(TSize& aSize) = 0;
        virtual void SetToolBarCommandSetL(CEikButtonGroupContainer& aToolBar) = 0;
        virtual void HandleCommandL(TInt aCommand) = 0;
        virtual TRect CurrentLineRect() const = 0;
        virtual void SetReadOnly(TBool aReadOnly) = 0;
        virtual void ClipboardL(TMsgClipboardFunc aFunc) = 0;
        virtual void EditL(TMsgEditFunc aFunc) = 0;
        virtual TBool IsFocusChangePossible(TMsgFocusDirection aDirection) const = 0;
        virtual TBool IsClipboardFuncPossible(TMsgClipboardFunc aFunc) const = 0;
        virtual TBool IsEditFuncPossible(TMsgEditFunc aFunc) const = 0;
        virtual TBool IsCursorLocation(TMsgCursorLocation aLocation) const = 0;
        virtual HBufC* GetHeaderIconAndTextL(CGulIcon& aIcon)  const = 0;
        virtual TInt PrepareForEventL(TMsgEvent aEvent) = 0;
    };


#endif // __MMSGBIOCONTROL_H__

