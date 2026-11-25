// CKNFLASH.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CKNFLASH_H__)
#define __CKNFLASH_H__

#include <gulicon.h>
#include <eikdialg.h>
#include <e32base.h>
#include <e32std.h>

class CFlashingDialogVisibilityTimer;
class CFlashingDialogMinimumVisibilityTimer;

/**
 * The CCknFlashingDialog class implements a flashing note dialog.
 * @since Ckon1.0 
 */
class CCknFlashingDialog : public CEikDialog
	{
public:
    enum TFlashTime
		{
		ENormal,
		EShort
		};
public:
    ~CCknFlashingDialog();
    static IMPORT_C TBool RunDlgLD(const TDesC& aTitle,
                                   const TDesC& aMsg,
                                   CGulIcon* aIcon=NULL,
                                   TFlashTime aFlashTime=ENormal,
								   RWindowGroup* aParent=NULL);
    void CloseDialogL();   // This should be called from the timer as it launches
protected: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private:
	CCknFlashingDialog(const TDesC& aTitle,
                       const TDesC& aMsg,
                       CGulIcon* aIcon,
                       TFlashTime aFlashTime,
					   RWindowGroup* aParent=NULL);
private:
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
	void PreLayoutDynInitL();
    void PostLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
private:
	const TDesC* iTitle;
	const TDesC* iMessage;
    const CGulIcon* iIcon;
    TFlashTime iFlashTime;
    TBool iMinimumTimeExceeded;
    CFlashingDialogMinimumVisibilityTimer* iMinimumVisibilityTimer;
    CFlashingDialogVisibilityTimer* iVisibilityTimer;
	RWindowGroup* iParent;
	};

/**
 * The FlashingDialogVisibilityTimer class implements a timer for flashing dialogs.
 *@internal
 */
class CFlashingDialogVisibilityTimer : public CTimer
    {
public:
    static CFlashingDialogVisibilityTimer* NewL(CCknFlashingDialog& aFlashingDialog);
protected:
    void RunL();
private:
    CFlashingDialogVisibilityTimer();
    void SetFlashingDialog(CCknFlashingDialog& aFlashingDialog);
private:
    CCknFlashingDialog* iFlashingDialog;
    };

/**
 * The FlashingDialogMinimumVisibilityTimer class implements a timer for flashing dialogs.
 *@internal
 */
class CFlashingDialogMinimumVisibilityTimer : public CTimer
    {
public:
    static CFlashingDialogMinimumVisibilityTimer* NewL(TBool& aFlag);
protected:
    void RunL();
private:
    CFlashingDialogMinimumVisibilityTimer();
    void SetFlag(TBool& aFlag);
private:
    TBool* iFlag;
    };


#endif
