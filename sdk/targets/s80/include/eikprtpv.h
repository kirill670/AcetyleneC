// EIKPRTPV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKPRTPV_H__)
#define __EIKPRTPV_H__

#include <eikbctrl.h>
#include <coecobs.h>
#include <eikdialg.h>
#include <eikmobs.h>
#include <prnprev.h>

//
// Class CEikPrintPreview
//

class TResourceReader;
class CPrintSetup;
class MPageRegionPrinter;
class CEikScrollButton;
class MPrintPreviewDialogObserver;

class CEikPrintPreview : public CEikBorderedControl, public MCoeControlObserver, public MEikScrollBarObserver
	{
public:
	IMPORT_C CEikPrintPreview();
	IMPORT_C ~CEikPrintPreview();
	IMPORT_C void ConstructL(const CCoeControl* aParent);
    IMPORT_C void InitializeFormat(CPrintSetup& aPrintSetup,MPageRegionPrinter& aBodyPrinter,TPrintPreviewFormat& aFormat,TInt& aNumPagesInDoc,TInt& aFirstPageToDisplay,TInt aNumPagesToView,CPrintPreviewImage::TMarginState& aMarginState);
	IMPORT_C void SetFormatAndDrawL(TInt& aFirstPageToDisplay,TInt& aNumPagesToView);
	IMPORT_C void SetMarginAndDrawL(CPrintPreviewImage::TMarginState aMarginState);
	IMPORT_C void SetPreviewImageObserver(MPrintProcessObserver* aObserver);
	IMPORT_C void SetNumBands(TInt aNumBands);
	IMPORT_C void SetNumPagesInDoc(TInt aNumPagesInDoc,TInt aFirstPageToDisplay,TInt aNumPagesToView);
	IMPORT_C void SetInPrintBand(TBool aBool);
	IMPORT_C TBool InPrintBand();
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void Draw(const TRect& /*aRect*/) const;
	IMPORT_C void SetDrawFlag(TBool aDraw);
	IMPORT_C TBool DrawFlag();
	IMPORT_C void ActivateL();
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
protected: // from MEikScrollBarObserver
	IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
protected: // from CCoeControl
    IMPORT_C TInt CountComponentControls() const;
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();

private: // from CCoeControl
	IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);
private: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
private:
	void DrawPreview(const TRect& aRect);
	void SwitchFirstPageToDisplayL(TInt& aNewFirstPageToDisplay);
	void DrawButtons() const;
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();	
private:
	CPrintPreviewImage* iPreview;
	CPrintSetup* iPrintSetup;
	MPageRegionPrinter* iBodyPrinter;
	TPrintPreviewFormat* iPrintPreviewFormat;
	TInt* iFirstPageToDisplay;
	TInt iNumPagesInDoc;
	TInt iNumPagesToView;
	TInt iNumBands;
	CPrintPreviewImage::TMarginState iMarginState;
	TRect iDisplayRect;
	TBool iPreviewDraw;
	TBool iInPrintBand;
	CEikScrollBar* iScrollBar;
	TEikScrollBarModel iScrollBarModel;
	};	

class CEikPrintPreviewDialog : public CEikDialog, private MEikMenuObserver, private MPrintProcessObserver
    {
public:
    IMPORT_C static TBool RunDlgLD(
									CPrintSetup&					aPrintSetup,
									MPageRegionPrinter&				aBodyPrinter,
									TInt&							aNumPagesInDoc,
									MPrintPreviewDialogObserver*	aObserver,
									TInt							aNumBands);

    IMPORT_C ~CEikPrintPreviewDialog();
	//from CCoeControl
	void GetHelpContext(TCoeHelpContext& aContext) const;
private: 
    CEikPrintPreviewDialog(CPrintSetup& aPrintSetup,MPageRegionPrinter& aBodyPrinter,TInt& aNumPagesInDoc,MPrintPreviewDialogObserver* aObserver,TInt aNumBands);
	// from CEikDialog
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	void Draw(const TRect& aRect) const;
	//from menuobserver
	void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
private: // from MEikCommandObserver
	void ProcessCommandL(TInt aCommand);
private:  // from MPrintProcessObserver 
	void NotifyPrintStarted(TPrintParameters aPrintParams);
	void NotifyPrintEnded(TInt anErrorCode);
	void NotifyBandPrinted(TInt aPercentageOfPagePrinted, TInt aCurrentPageNum, TInt aCurrentCopyNum);
private:
	void SetNumPagesInDoc();
private:
	CPrintSetup* iPrintSetup;
	MPageRegionPrinter* iBodyPrinter;
	TPrintParameters iParameters;
	TPrintPreviewFormat iPrintPreviewFormat;
	TInt iNumPagesInDoc;
	TInt iFirstPageToDisplay;
	TInt iNumPagesToView;
	TInt iNumBands;
	CPrintPreviewImage::TMarginState iMarginState;
    MPrintPreviewDialogObserver* iObserver;
	};


class CEikPreviewSetupDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(
								TInt&								aNumber,
								TInt								aMax,
								CPrintPreviewImage::TMarginState&	aMarginState);
    };


class CEikPreviewGotoDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(TInt& aNumber, TInt aMax);

    };


#endif

