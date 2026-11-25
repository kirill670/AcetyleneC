// EIKDIALG.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKDIALG_H__
#define __EIKDIALG_H__

#include <coecobs.h>
#include <coeccntx.h>
#include <eikbctrl.h>
#include <eikdpobs.h>
#include <gulftflg.hrh>
#include <qikshutter.h>

//
// Header files needed by deprecated interfaces.
//

#include <eikbutb.h>
#include <eikbgfty.h>

//
// Forward declarations.
//

class CEikMover;
class CEikCaptionedControl;
class CEikDialogPageSelector;
class CEikButtonGroupContainer;
class CEikDialogButtonCommandObserver;
class MEikCommandObserver;
class CEikLabel;
class CDialogMenuPaneObserver;
class TQikDlgWrappingContext;

struct SEikControlInfo;


/**
 * The CEikDialog class provides an instantiable base class for dialogs. Controls can be added directly
 * to this class but it is normal to create a subclass to handle the controls appearing on the dialog
 * dynamically.
 */
class CEikDialog : public CEikBorderedControl,public MCoeControlObserver,public MEikDialogPageObserver,public MCoeControlContext, public MQikShutterTarget
	{ 
public:
	IMPORT_C CEikDialog(); 
	IMPORT_C ~CEikDialog(); 
	IMPORT_C TInt ExecuteLD(TInt aResourceId);
	IMPORT_C void PrepareLC(TInt aResourceId);
	IMPORT_C TInt RunLD();
	IMPORT_C void SetTitleL(const TDesC& aText);
	IMPORT_C void SetTitleL(TInt aResourceId);
	IMPORT_C void SetPageDimmedNow(TInt aPageId,TBool aDimmed);
	IMPORT_C void SetLineNonFocusing(TInt aControlId);
	IMPORT_C void SetLineDimmedNow(TInt aControlId,TBool aDimmed);
	IMPORT_C void MakeLineVisible(TInt aControlId,TBool aVisible);
	IMPORT_C void MakeWholeLineVisible(TInt aControlId,TBool aVisible);
	IMPORT_C void DeleteLine(TInt aControlId);
	IMPORT_C void InsertLineL(TInt aIndex,TInt aResourceId,TInt aPageId=0);
	IMPORT_C void MakePanelButtonVisible(TInt aButtonId,TBool aVisible);
	IMPORT_C void TryChangeFocusToL(TInt aControlId);
	IMPORT_C void SwitchLineLatency(TInt aBecomesLatent,TInt aNoLongerLatent);
	IMPORT_C void SetPageDensePacking(TInt aPageId,TBool aDensePacking);
	IMPORT_C void Layout();
	IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue);
	IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aControlId,TInt aControlType,TAny* aReturnValue);
	IMPORT_C void SetControlCaptionL(TInt aControlId,const TDesC& aText);
	IMPORT_C void SetControlCaptionL(TInt aControlId,TInt aResourceId);
	IMPORT_C CEikLabel* ControlCaption(TInt aControlId) const;
	IMPORT_C CCoeControl* Control(TInt aControlId) const;
	IMPORT_C CCoeControl* ControlOrNull(TInt aControlId) const;
	IMPORT_C CEikButtonGroupContainer& ButtonGroupContainer() const;
	IMPORT_C CEikButtonGroupContainer& PageButtonGroupContainer(TInt aPageId) const;
	IMPORT_C CEikMover& Title() const;
	IMPORT_C TInt ActivePageId() const;
	IMPORT_C void ActivateFirstPageL() const;
	IMPORT_C TInt SetHelpContext(const TCoeHelpContext& aContext);		// Quartz specific
	IMPORT_C TSize PreferredSize(const TSize& aMaxSize) const;	// deprecated
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual void GetHelpContext(TCoeHelpContext& aContext) const;
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
private: // from MEikDialogPageObserver
	IMPORT_C void ProcessPageButtonCommandL(TInt aCommandId);
protected: // from MEikDialogPageObserver
	IMPORT_C virtual void PrepareForFocusTransitionL();
	IMPORT_C virtual void PageChangedL(TInt aPageId);
	IMPORT_C virtual void LineChangedL(TInt aControlId);
public: // from MEikDialogPageObserver
	IMPORT_C virtual SEikControlInfo CreateCustomControlL(TInt aControlType);
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void Reserved_2();
protected: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
protected: // new functions
	IMPORT_C void TryExitL(TInt aButtonId);
	IMPORT_C void AdjustAllIdsOnPage(TInt aPageId,TInt aControlIdDelta);
	IMPORT_C void ConstructSleepingDialogL(TInt aResourceId);
	IMPORT_C void ConstructSleepingAlertDialogL(TInt aResourceId);
	IMPORT_C TInt RouseSleepingDialog();
	IMPORT_C void ExitSleepingDialog();
	IMPORT_C TInt IdOfFocusControl() const;
	IMPORT_C TInt FindLineIndex(const CCoeControl& aControl) const;
	IMPORT_C CEikCaptionedControl* Line(TInt aControlId) const;
	IMPORT_C CEikCaptionedControl* CurrentLine() const;
	IMPORT_C TBool RotateFocusByL(TInt aDelta);
	IMPORT_C TInt ActivePageIndex() const;
	IMPORT_C void ResetLineMinimumSizes();
	IMPORT_C CEikButtonGroupContainer* SwapButtonGroupContainer(CEikButtonGroupContainer* aContainer);
	IMPORT_C MEikCommandObserver* ButtonCommandObserver() const;
protected: // new functions
	IMPORT_C virtual TBool OkToExitL(TInt aButtonId);
	IMPORT_C virtual TInt PrepareForcedExitL();
	IMPORT_C virtual void PreLayoutDynInitL();
	IMPORT_C virtual void PostLayoutDynInitL();
	IMPORT_C virtual void SetInitialCurrentLine();
	IMPORT_C virtual void HandleControlStateChangeL(TInt aControlId);
	IMPORT_C virtual void HandleInteractionRefused(TInt aControlId);
	IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);
private: // from MQikShutterTaget
	IMPORT_C TBool ShutL();
	IMPORT_C const CCoeControl& AsControl() const;
protected:// new functions
	IMPORT_C virtual void CreateButtonGroupContainerL(TInt aResourceId);
private:
	IMPORT_C virtual void Reserved_4();
private: // internal functions
	void BaseConstructL();
	void StaticConstructL(TInt aResourceId);
	void DynamicConstructL();
	void CreateTitleBarL();
	void CreatePageSelectorL();
	void CreatePageSelectorL(TInt aResourceId,TQikDlgWrappingContext& aWrapCntx);
	TInt WaitAsRequired();
	TKeyResponse TryAnimateButtonAndExitL(TInt aKeycode);
	void CommonConstructSleepingDialogL(TInt aResourceId);
	TRect ConfiningRect() const;
	TSize doLayoutL(TSize aMaxSize);
	static MEikButtonGroup* CreateQikButtonPanelL(TInt aType, EikButtonGroupFactory::TCreationData& aCreationData, TBool& aAddToButtonGroupStack);
public:
	void HandleMenuDimmingL();
	void ProcessCommandL(TInt aCommandId);
private:
	CDialogMenuPaneObserver* iMenuPaneObserver;
	CEikMover* iTitleBar;
	CEikDialogPageSelector* iPageSelector;
	CEikButtonGroupContainer* iButtonGroupContainer;
	CEikDialogButtonCommandObserver* iButtonCommandObserver;
	TInt iDialogFlags;
	TInt* iExitConfirmed;
	TCoeHelpContext* iHelpContext; // Quartz specific
private:	// Quartz specific
	TInt iQSpare[3];
private:
	friend class CEikDialogButtonCommandObserver;
	};

 
#endif	// __EIKDIALG_H__
