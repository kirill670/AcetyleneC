// PRNSETUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PRNSETUP_H__
#define __PRNSETUP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__FLDBLTIN_H__)
#include <fldbltin.h>
#endif
#if !defined(__PRNINF_H__)
#include <prninf.h>
#endif


// Classes defined //
class CPrintSetup;
//

// Forward Reference
class CPreviewProcess;
class CPrintProcess;
class CPdrModelList;
class CPdrDevice;
class CHeaderFooter;
class TPageSpec;
class RReadStream;
class RWriteStream;
class MPageRegionPrinter;
class RFs;
class CPrinterDriver;
class CPrinterDriverUI;
//


/**
 *
 * Sets, retrieves, stores and restores print setup information and
 * starts and terminates a print job.
 *
 * Print setup information includes the printer device to print to, page
 * margins and the contents of the header and footer. It may also be used
 * to retrieve the current target printer device, through which the page
 * specification, consisting of page orientation and dimensions, can be
 * set.Print setup information is associated with a particular document
 * and may be stored as part of the persistent form of the document.
 * Print parameters are not included as print setup information because
 * they are associated with a particular print request, not with the
 * document itself. They are not stored with the document.This class is
 * not intended for user derivation.The printer model list:On
 * construction, a print setup object's print settings are not
 * initialised. This means that a target printer device must be selected
 * and other settings, including the page specification, should be set
 * before printing can begin.To set the target printer device, a printer
 * model list must first have been created and initialised.
 * <code>CPrintSetup</code> initialises the printer model list by
 * searching through the list of printer driver search paths which it
 * owns, for the models supported by all .pdr files found. You must have
 * added at least one path to this search path list (using
 * <code>AddPrinterDriverDirL()</code>) before the model list can be
 * initialised. This is demonstrated in the
 * <code>CPrintExampleControl::SetupPrintingL()</code> function in the
 * PRINT example code (see file epoc32ex\print\prexamp.cpp). Any paths
 * which do not include a drive letter will be scanned on all non-remote
 * drives.Header and footer:A <code>CPrintSetup</code> object owns the
 * header and footer into which rich text, fields and objects may be
 * inserted. The inherited <code>MFieldPageNumInfo</code> protocol allows
 * page numbering to be easily inserted into the header or footer.
 *
 * @since 5.0
 * @lib "print.lib"
 */
class CPrintSetup : public CBase, private MFieldPageNumInfo
	{
public:
	IMPORT_C static CPrintSetup* NewL();
	IMPORT_C virtual ~CPrintSetup();
	//
	// printer model selection/control functions
	IMPORT_C void AddPrinterDriverDirL(const TDesC& aDriverDir);
	IMPORT_C CPrinterModelList* ModelNameListL(RFs& aFs);
	IMPORT_C void FreeModelList();
	IMPORT_C void CreatePrinterDeviceL(TInt aModelIndex); // requires ModelList to exist
	IMPORT_C void CreatePrinterDeviceL(TUid aModelUid,RFs& aFs);
	IMPORT_C CPrinterDevice* PrinterDevice()const;
	IMPORT_C CPrinterDriverUI* CreatePrinterDriverUIL(); // ownership is transfered to the caller
	//
	// print functions
	IMPORT_C void EndPrint();
	IMPORT_C TInt StartPrintL(const TPrintParameters& aPrintParams,MPageRegionPrinter& aBodyPrinter,
				CPrinterPort* aPort,MPrintProcessObserver* anObserver);
	IMPORT_C TInt StartPreviewPrintL(const TPrintParameters& aPrintParams,MPageRegionPrinter& aBodyPrinter,
				MPrintProcessObserver* anObserver,CGraphicsDevice& aPreviewDev,const TRect& aHeaderRectInPixels,
				const TRect& aFooterRectInPixels,TInt aNumBands);
	//
	// accessors
	inline CHeaderFooter* Header()const;
	inline CHeaderFooter* Footer()const;
	//
	// persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId,const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,MPictureFactory* aFactory=NULL);
	IMPORT_C void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap)const;
	IMPORT_C void RestoreComponentsL(const CStreamStore& aStore,const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,MPictureFactory* aFactory=NULL);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	//
private:
	CPrintSetup();
	void ConstructL();
	void DoStartPrintL(const TPrintParameters& aPrintParams,MPageRegionPrinter& aBodyPrinter,MPrintProcessObserver* aObserver,CPrinterPort* aPort);
	void InitializePrintingL(CGraphicsDevice* aPrinterDev,const TPrintParameters& aPrintParams,MPrintProcessObserver* aObserver);
	void InitializePrintingL(const TPrintParameters& aPrintParams,MPrintProcessObserver* aObserver,
									 const TRect& aHeaderRectInPixels,const TRect& aFooterRectInPixels);
	// from MFieldPageNumInfo
	TInt UpdateFieldPageNum()const;
public:
	// Info regarding print setup etc.
	TPageMargins iPageMarginsInTwips;
	TInt iNumOfFirstPage; // value to start page numbering at
private:
	enum {
		ENumberFirstPage = 0x0001,
		};
private:
	CHeaderFooter* iHeader;
	CHeaderFooter* iFooter;
	CPrinterDriver* iPrinterDriver; // the target printer driver
	CPreviewProcess* iPrintProcess;
	CPdrModelList* iModelList;
	MPrintProcessObserver* iPrintObserver;
	TPrintParameters iPrintParams; // not persisted
	CArrayFixSeg<TFileName>* iDriverDirList;
	};


//
// inlines
//

/**
 *
 * Gets the print setup object's header.
 *
 * @returns   "CHeaderFooter*"
 *            The header
 */
inline CHeaderFooter* CPrintSetup::Header()const
	{ return iHeader; }

/**
 *
 * Gets the print setup object's footer.
 *
 * @returns   "CHeaderFooter*"
 *            The footer
 */
inline CHeaderFooter* CPrintSetup::Footer()const
	{ return iFooter; }




#endif
