#ifndef MPLUGINADAPTER_H
#define MPLUGINADAPTER_H

#include "coecntrl.h"
#include "coecobs.h"
#include "npupp.h"

class MPluginNotifier;


class MPluginAdapter {
public:
	virtual TUint16 GetVersion()=0;
    virtual void PluginConstructedL(CCoeControl* aPluginControl)=0;
    virtual void PluginFinishedL()=0;
    virtual void OpenUrlL(const TDesC& aUrl)=0;
    virtual void OpenUrlInTargetWindowL(const TDesC& aUrl, const TDesC& aNewTargetWindowName)=0;
    virtual TBool HasNavigationHistoryPrevious() const=0;
    virtual void LoadNavigationHistoryPreviousL()=0;
    virtual TBool HasNavigationHistoryNext() const=0;
    virtual void LoadNavigationHistoryNextL()=0;
    virtual CCoeControl* GetParentControl()=0;
    virtual MCoeControlObserver* GetParentControlObserver()=0;
    virtual void SetPluginNotifier(MPluginNotifier *aNotifier)=0;
};

 


class MPluginNotifier

{

public:

enum TNotificationType {
EEditCut,
EEditCopy, 
EEditPaste, 
EEditDelete, 
EApplicationFocusChanged, 
ESystemNotification 

};

virtual TInt NotifyL (TNotificationType aCallType, TAny *aParam)=0;
};

 

#endif //MPLUGINADAPTER_H
