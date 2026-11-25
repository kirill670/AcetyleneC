// CKNPRTDG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__CKNPRTDG_H__)
#define __CKNPRTDG_H__

#include <eikdialg.h>
#include <eikprtdg.h>
#include <prnprev.h>
#include <eikmobs.h>
#include <eikmobs.h>
#include <eikpprob.h>
#include <FRMPRINT.H>
/**
 * The TCknPrintParameters class define parameters for printing
 *@internal
 */
class TCknPrintParameters
	{
public:
	enum TExtraPrintParameters
		{
		ECknPrintWholeDocument=0,
		ECknPrintCurrentPage,
		ECknPrintSelection,
		ECknPrintUserDefinedPage
		};
	TCknPrintParameters():iFlags(ECknPrintWholeDocument) {}
public:
	TPrintParameters iParams;
	TInt iFlags;
	};

class CCknPrintOptionsDialogExtension;
/**
 * The CCknPrintOptionsDialog class implements a print options dialog for Ckon. 
  * It can change print settings such as number of copies, print range,
 * connection type and printer.
 *
 * @since Ckon1.0 
 */
class CCknPrintOptionsDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(
                                TCknPrintParameters&	aPrintParameters,
                                CPrintSetup&			aPrintSetup,
                                TUid&					aUid,
								TInt&					aPrinterPort);
	//from CCoeControl
	void GetHelpContext(TCoeHelpContext& aContext) const;
private: 
    CCknPrintOptionsDialog(TCknPrintParameters& aPrintParameters,CPrintSetup& aPrintSetup,TUid& aUid,TInt& aPrinterPort);
    ~CCknPrintOptionsDialog();
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void GetPrinterNamesL(CPrinterModelList* aModelNameList);
	void GetPrinterPortsL(CDesCArray& aPrinterPortArray);
	void RunFileDialogL();
private:
    TCknPrintParameters* iPrintParameters;
    SEikRange iPageRange;
    CPrintSetup* iPrintSetup;
    TUid& iUid;
	TInt& iPrinterPort;
    CDesCArray* iPrinterNameArray;
    CCknPrintOptionsDialogExtension* iExtension;
	CArrayFixFlat<TUid>* iUidArray;
	};
/**
* The MPrintDialogObserver class implements an interface class for a print dialog observer.
*/

class MPrintDialogObserver
	{
public:
	virtual TBool RunPaginationDialogL(CPrintSetup& aPrintSetup,TCknPrintParameters& aPrintParameters)=0;
	virtual TBool RunPrintPreviewDialogL(CPrintSetup& aPrintSetup,MPageRegionPrinter& aPrinter)=0;
	};

class MPrintPreviewDialogObserver;
class CCknPrintDialogExtension;

/**
 * The CCknPrintDialog class implements the Ckon print dialog. Displays print options and allows to change them with 
 * CCknPrintOptionsDialog class. Provides also access to print preview.
 *
 * @since Ckon1.0 
 */
class CCknPrintDialog : public CEikDialog
    {
public:
    IMPORT_C static void InitPrintOptions(TInt aListResourceId,TInt& aSelectedListIndex);
	IMPORT_C static TBool RunDlgLD(MPageRegionPrinter&			aPrinter,
								MPrintDialogObserver*			aPrintObserver,
								TCknPrintParameters&			aPrintParameters,
								CPrintSetup&					aPrintSetup,
								TUid&							aUid);
    IMPORT_C static TBool RunDlgLD(
								CEikGlobalTextEditor&			aGlobalEditor,
								CTextPageRegionPrinter&			aLayDoc,
								CArrayFix<TInt>&				aPageList,
								TCknPrintParameters&			aPrintParameters,
								CPrintSetup&					aPrintSetup,
								TUid&							aUid,
								MPrintPreviewDialogObserver&	aPreviewObs);
    IMPORT_C static TBool RunDlgLD(
								CTextPaginator&					aPaginator,
								CTextPageRegionPrinter&			aLayDoc,
								CArrayFix<TInt>&				aPageList,
								TCknPrintParameters&			aPrintParameters,
								CPrintSetup&					aPrintSetup,
								TUid&							aUid,
								MPrintPreviewDialogObserver&	aPreviewObs);
	//3 new static functions that allow prewiew to be turned off
	IMPORT_C static TBool RunDlgLD(MPageRegionPrinter&			aPrinter,
								MPrintDialogObserver*			aPrintObserver,
								TCknPrintParameters&			aPrintParameters,
								CPrintSetup&					aPrintSetup,
								TUid&							aUid,
								TBool							aAllowPreview);
    IMPORT_C static TBool RunDlgLD(
								CEikGlobalTextEditor&			aGlobalEditor,
								CTextPageRegionPrinter&			aLayDoc,
								CArrayFix<TInt>&				aPageList,
								TCknPrintParameters&			aPrintParameters,
								CPrintSetup&					aPrintSetup,
								TUid&							aUid,
								MPrintPreviewDialogObserver&	aPreviewObs,
								TBool							aAllowPreview);
    IMPORT_C static TBool RunDlgLD(
								CTextPaginator&					aPaginator,
								CTextPageRegionPrinter&			aLayDoc,
								CArrayFix<TInt>&				aPageList,
								TCknPrintParameters&			aPrintParameters,
								CPrintSetup&					aPrintSetup,
								TUid&							aUid,
								MPrintPreviewDialogObserver&	aPreviewObs,
								TBool							aAllowPreview);
	//from CCoeControl
	void GetHelpContext(TCoeHelpContext& aContext) const;
private: 
    CCknPrintDialog(CEikGlobalTextEditor& aGlobalEditor,CTextPageRegionPrinter& aPrinter,
		CArrayFix<TInt>& aPageList,TCknPrintParameters& aPrintParameters,
		CPrintSetup& aPrintSetup,TUid& aUid,MPrintPreviewDialogObserver& aPreviewObs,TBool	aAllowPreview);
    CCknPrintDialog(CTextPaginator& aPaginator,CTextPageRegionPrinter& aPrinter,
		CArrayFix<TInt>& aPageList,TCknPrintParameters& aPrintParameters,
		CPrintSetup& aPrintSetup,TUid& aUid,MPrintPreviewDialogObserver& aPreviewObs,TBool	aAllowPreview);
	CCknPrintDialog(MPageRegionPrinter&	aPrinter,MPrintDialogObserver* aPrintObserver,
		TCknPrintParameters& aPrintParameters,CPrintSetup& aPrintSetup,TUid& aUid,TBool	aAllowPreview);
    ~CCknPrintDialog();
	void SetPrinterNameL();
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
	void GetPrinterPortsL(CDesCArray& aPrinterPortArray);
	void GetPrinterNamesL(CPrinterModelList* aModelNameList);
	TBool OkToExitL(TInt aButtonId);
	TBool RunPaginationDialogL();
private:
	TBool iPaginationDone;
	TCknPrintParameters* iPrintParameters;
	SEikRange iPageRange;
	CPrintSetup* iPrintSetup;
	TUid& iUid;
	CCknPrintDialogExtension* iExtension;
	CDesCArray* iPrinterNameArray;

    CTextPageRegionPrinter* iPrinter;
    CArrayFix<TInt>* iPageList;
	CEikGlobalTextEditor* iGlobalEditor;
	CTextPaginator* iPaginator;
	const CFont* iFont;
	MPrintPreviewDialogObserver* iPreviewObs;
//
	MPrintDialogObserver* iPrintObserver;
	MPageRegionPrinter* iNonTextPrinter;
	TBool iAllowPreview;
    };
#endif // __CKNPRTDG_H__
