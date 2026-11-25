// EIKPRTDG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKPRTDG_H__)
#define __EIKPRTDG_H__

#include <eikdialg.h>
#include <gdi.h>
#include <prninf.h>
#include <frmpage.h>
#include <eikmfne.h>
#include <pdrport.h>
#include <eikenv.h>
#include <cknmcanc.h>
#include <es_sock.h> // THostName
#include <btsdp.h>		// SDP

class CPrintSetup;
class CPrinterDriverUI;
class CEikGlobalTextEditor;

class CEikPageSetupDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(CPrintSetup* aPrintSetup);
	//from CCoeControl
	void GetHelpContext(TCoeHelpContext& aContext) const;
private:
    CEikPageSetupDialog(CPrintSetup* aPrintSetup);
	// inherited and overridden
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);
	void PageChangedL(TInt aPageId);
private: // internal use
	TInt FindPageSizeNameIndex(const TSize aSize);
	TSize FindPageSizeInPortraitFormat(TInt aPageSizeNameIndex);
	void ValidateFocusControlL();
private:
    CPrintSetup* iPrintSetup;
	TPageSpec iPageSpecInTwips;
	TMargins iPageMarginsInTwips;
	TPrintParameters iPrintParams;
	TBool iSizeChanged;
    };

class CEikPrinterSetupDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(CPrintSetup* aPrintSetup,TUid& aUid);
    IMPORT_C ~CEikPrinterSetupDialog();
	IMPORT_C static CPrintSetup* NewDefaultPrintSetupL();
private:
    CEikPrinterSetupDialog(CPrintSetup* aPrintSetup,TUid& aUid);
	// inherited and overridden
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);
private:
	void RunFileDialogL();
	void RunSerialPortDialogL();
	void UpdatePortControlL();
	void DisplayDevicePropertiesButtonL();
private:
	CDesCArray* iArray;
	CPrintSetup* iPrintSetup;
	CPrintSetup* iTempPrintSetup;
	CPrinterDriverUI* iPrinterDriverUi;
	TUid& iUid;
    };

class CEikPrintProgressDialogExtension;

class CEikPrintProgressDialog : public CCoeControl, private MPrintProcessObserver, public MCknCancellableOperation
    {
public:
    IMPORT_C static TBool RunDlgLD(
								CPrintSetup*			aPrintSetup,
								MPageRegionPrinter*		aPageRegionPrinter,
								const TPrintParameters& aPrintParameters);
	IMPORT_C ~CEikPrintProgressDialog();

	IMPORT_C void AttributeRequestComplete(TSdpServRecordHandle aHandle, TInt aError);
	IMPORT_C void AttributeRequestResult(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue* aAttrValue);
	IMPORT_C void NextRecordRequestComplete(TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount);
private:
    CEikPrintProgressDialog(CPrintSetup* aPrintSetup, MPageRegionPrinter* aPageRegionPrinter,const TPrintParameters& aPrintParameters);
	void DisplayErrorMessage(TInt aErrCode,TDes& aDes);
	void ConstructL();

public: // inherited from MPrintProcessObserver
	void NotifyPrintStarted(TPrintParameters aPrintParams);
	void NotifyPrintEnded(TInt anErrorCode);
	void NotifyBandPrinted(TInt aPercentageOfPagePrinted, TInt aCurrentPageNum, TInt aCurrentCopyNum);
	// inherited from MCknCancellableOperation
	void CancelOperation();

	TInt RunFileDialogL(CPrinterPort*& aPort);
	TInt LPRPrintL(CPrinterPort*& aPort);
	TInt SocketPrintL(CPrinterPort*& aPort);
	TInt BTPrintL(CPrinterPort*& aPort);
private:
	CPrintSetup* iPrintSetup;
	MPageRegionPrinter* iPageRegionPrinter;
	TPrintParameters iPrintParameters;
	TEikPortFlag iPortFlag;
	MCknCancelDialog* iCancelNote;
	TBool iActiveSchedulerStarted;
	TBool iPrintJobCancelled;
	TBool iPrintSuccess;
	CEikPrintProgressDialogExtension* iExt;
	};

class CEikPaginateDialog : public CEikDialog, public MPaginateObserver
    {
public:
	IMPORT_C static TBool RunDlgLD(	CEikGlobalTextEditor*	aEditor,
									CPrintSetup*			aPrintSetup,
									CArrayFix<TInt>*		aCharsPerPage);
	IMPORT_C static TBool RunDlgLD(CTextPaginator* aPaginator);
private:
	CEikPaginateDialog(CTextPaginator* aPaginator);
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
private: //from MPaginateObserver
	void NotifyCompletion();
	void NotifyError(TInt anErrorCode);
	void NotifyPageCompletion(TInt aCurrentPageNum);
private:
	CTextPaginator* iPaginator;
    };

class CEikSerialPortDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD();
    };

class CEikPrintRangeDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(
								TPrintParameters&	iPrintParameters,
								CPrintSetup*		aPrintSetup,
								TUid&				aUid,
								TBool				aPrintButton=EFalse);
public:
    IMPORT_C CEikPrintRangeDialog(TPrintParameters& iPrintParameters,CPrintSetup* aPrintSetup,TUid& aUid,TBool aPrintButton=EFalse);
	IMPORT_C void SetTextForOkButtonL();
	IMPORT_C void SetPrinterNameL();
private:
	IMPORT_C void PreLayoutDynInitL();
    IMPORT_C TBool OkToExitL(TInt aButtonId);
	IMPORT_C void HandleControlStateChangeL(TInt aControlId);
public: // dialogs which derive from this dialog can have access to the data members
		//+ SURELY THIS SHOULD BE 'protected' - NOT 'public'? BUT LEAVE AS IS FOR SOURCE COMPATIBILITY
	TPrintParameters* iPrintParameters;
	SEikRange iPageRange;
	CPrintSetup* iPrintSetup;
    TBool iPrintButton;
	TUid& iUid;
private:
	TInt iSpare;
	};

class CEikJetDirectSetupDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(THostName& aIpOrName, TUint& aPort);
private:
    CEikJetDirectSetupDialog(THostName& aIpOrName, TUint& aPort);
	// inherited and overridden
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);
private: // internal use

private:
	THostName&	iIpOrName;
	TUint&		iPort;
    };

//#define CBTPRINTERPORT_DEFINED
#ifndef CBTPRINTERPORT_DEFINED
const TInt KLprMaxHostnameLen = 32;
const TUint KLprMaxUserNameLen = 32;
const TUint KLprMaxQueueLen = 256;
typedef TBuf<KLprMaxQueueLen> TLprQueueName;
typedef TBuf<KLprMaxUserNameLen> TLprUserName;
#endif

class CEikLPRSetupDialog : public CEikDialog
    {
public:
    IMPORT_C static TBool RunDlgLD(THostName& aNetworkName, TLprQueueName& aQueueName, TLprUserName& aUserName);
private:
    CEikLPRSetupDialog(THostName& aNetworkName, TLprQueueName& aQueueName, TLprUserName& aUserName);
	// inherited and overridden
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
	void HandleControlStateChangeL(TInt aControlId);
private: // internal use

private:
	THostName&		iNetworkName;
	TLprQueueName&	iQueueName;
	TLprUserName&	iUserName;
    };

#endif
