/*
* ============================================================================
*  Name     : AknAppUi.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
#ifndef __AKNAPPUI_H__
#define __AKNAPPUI_H__

#include <eikappui.h>
#include <Eikspane.h>
#include <eikcba.h>
#include <avkon.hrh>

class CEikButtonGroupContainer;
class CAknAppShutter;
class CAknAppUiExtension;
#define iAvkonAppUi ((CAknAppUi*)CEikonEnv::Static()->EikAppUi())

class CAknAppUi : public CEikAppUi, MEikStatusPaneObserver, public MCoeViewDeactivationObserver
    {
public:
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=EStandardApp);
	IMPORT_C ~CAknAppUi();

public:
	IMPORT_C CEikStatusPane* StatusPane();
	IMPORT_C CEikButtonGroupContainer* Cba();

	IMPORT_C void ProcessCommandL(TInt aCommand);
	IMPORT_C CAknKeySoundSystem* KeySounds();
    IMPORT_C TErrorHandlerResponse HandleError (TInt aError, const SExtendedError& aExtErr, TDes& aErrorText, TDes& aContextText); 

	IMPORT_C void RunAppShutter();
	IMPORT_C TBool IsAppShutterRunning() const;

public: // MCoeViewDeactivationObserver
	IMPORT_C virtual void HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated, const TVwsViewId &aNewlyActivatedViewId);

public: // from CCoeAppUiBase
	IMPORT_C void PrepareToExit();

protected:
	// from MEikStatusPaneObserver
	IMPORT_C void HandleStatusPaneSizeChange();

	// from CCoeAppUi
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);

protected: // formerly from MTopSetMember<CEikMenuBar>, now reserved
	IMPORT_C virtual void Reserved_MtsmPosition();
	IMPORT_C virtual void Reserved_MtsmObject();
protected:
    IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);

	IMPORT_C void SetKeyBlockMode(TAknKeyBlockMode aMode);

#ifdef _DEBUG
	void DumpControl(CCoeControl* aControl, TInt aLevel, RDebug& aDebug);
#endif
    void DecideWsClientBufferSizesL();

private:
	void UpdateKeyBlockMode();
	void HandleErrorL(TInt aError);

private:
	TBool iDumpNextControl;
	CAknAppShutter* iAppShutter;	// May be set to NULL by the app shutter itself
	TAknKeyBlockMode iBlockMode;
	CAknAppUiExtension * iExtension;

public:
    /**
    * @since 2.6
    */
    IMPORT_C void HideApplicationFromFSW(TBool aHide=ETrue);
    };



#endif







