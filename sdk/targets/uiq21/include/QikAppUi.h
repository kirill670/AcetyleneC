// QikAppUi.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0


#ifndef __QIKAPPUI_H__
#define __QIKAPPUI_H__

#include <eikappui.h>
#include <Qikon.hrh>
#include <eikbgfty.h>

class CQikCategoryModel;
class CQikToolbar;

/**
 * @short Extra AppUi layer adding Category support etc to Quartz applications.
 */
class CQikAppUi : public CEikAppUi
	{
public:
	IMPORT_C CQikAppUi();
	IMPORT_C ~CQikAppUi();
public:	// from CEikAppUi
	IMPORT_C void ConstructL();
	IMPORT_C void HandleResourceChangeL(TInt aType);
	IMPORT_C void ProcessMessageL(TUid aUid,const TDesC8& aParams);
	IMPORT_C TErrorHandlerResponse HandleError(TInt aError,const SExtendedError& aExtErr,TDes& aErrorText,TDes& aContextText);
public:	// new functions
	IMPORT_C CQikCategoryModel* CategoryModel() const;
	IMPORT_C void SetCategoryModel(CQikCategoryModel* aCategoryModel);
	IMPORT_C void SetToolbarL(TUint aToolbarResId, TDrawNow aDrawNow = EDrawNow);
	IMPORT_C void RemoveToolbarL();
	IMPORT_C static TInt ZoomFactorL(TInt aZoomLevel, const CEikonEnv& aEikonEnv);
	IMPORT_C TBool AutoExitOnAppSwitch() const;
public: // from CCoeAppUiBase
	IMPORT_C void PrepareToExit();
protected:	// new functions
	IMPORT_C virtual void HandleCategoryChangeL(TInt aCategoryHandle);
	IMPORT_C void DynInitCategoryMenuPaneL(CEikMenuPane *aMenuPane);
	IMPORT_C void DynInitCategoryMenuPaneL(CEikMenuPane *aMenuPane, const TArray<TInt> aExcludeHandles);
	IMPORT_C void SetAutoExitOnAppSwitch(TBool aAutoExit);
	IMPORT_C void IgnorePointerEventsWhenInBackground(TBool aIgnore);
	IMPORT_C TBool AboutToOpenOrCreateFile() const;
protected: // from CEikAppUi
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=0);
protected:	// from CCoeAppUi
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
	IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
protected: // from MCoeMessageObserver
	IMPORT_C MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
protected:	// from MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommand);
private:	// from CCoeAppUiBase
	IMPORT_C void HandleSwitchOnEventL(CCoeControl* aDestination);
	IMPORT_C void SetAndDrawFocus(TBool aFocus);
	IMPORT_C void HandleScreenDeviceChangedL();
	IMPORT_C void Reserved_2();
private:	// from CEikAppUi
	IMPORT_C void Reserved_3();
	IMPORT_C void Reserved_4();
private:	// new functions
	void PositionToolbarL(CEikButtonGroupContainer* aToolbar) const;
	static MEikButtonGroup* CreateQikToolbarL(TInt aType, EikButtonGroupFactory::TCreationData& aCreationData, TBool& aAddToButtonGroupStack);
	IMPORT_C virtual void CQikAppUi_reserved1();
	IMPORT_C virtual void CQikAppUi_reserved2();
	IMPORT_C virtual void CQikAppUi_reserved3();
protected:
	CQikCategoryModel* iCategoryModel;
private:
	CArrayFixFlat<TInt>* iCategoryMenuIdTranslationTable;
private:
	TInt iQikAppUiSpare1;
	};

#endif // __QIKAPPUI_H__
