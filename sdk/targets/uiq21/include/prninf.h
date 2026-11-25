// PRNINF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PRNINF_H__
#define __PRNINF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__FLDBASE_H__)
#include <fldbase.h>
#endif

// Classes defined
//class TPageNumbers;
class CHeaderFooter;
class TPrintParameters;		
class TPageMargins;
class MPrintProcessObserver;	

// classes referenced
class RReadStream;
class RWriteStream;
class CRichText;
class CParaFormatLayer;
class CCharFormatLayer;
class MFieldFileNameInfo;
class MFieldPageNumInfo;
class MFieldNumPagesInfo;
//////////////////

/**
 *
 * Print parameters.
 *
 * These parameters include the number of copies and the number of the
 * first and last page to be printed in a print job. This data is
 * separate from the print setup information contained in class
 * <code>CPrintSetup</code>, because it is associated with a particular
 * print request, not with a document. Print parameters are not therefore
 * stored with the persistent form of a document.Objects of this class
 * are required by <code>CPrintSetup::StartPrintL()</code> and by
 * <code>CPrintSetup::StartPreviewPrintL()</code> and must be provided
 * when the standard GUI print range and print progress dialogs are
 * constructed.
 *
 * @since 5.0
 * @lib "print.lib"
 */
class TPrintParameters
	{
public:
	IMPORT_C TPrintParameters(); // sets to 1,0,0
public:
	TInt iNumCopies;									
	TInt iFirstPage;	// First page to print			
	TInt iLastPage;		// ... and last page to print
	};

/**
 *
 * Encapsulates the page margins located at the top, bottom, left and
 * right hand sides of the page.
 *
 * Page margins are accessed via the public
 * <code>iPageMarginsInTwips</code> member of class
 * <code>CPrintSetup</code>. They are a component of print setup
 * information because they are associated with a document and may be
 * stored as part of the persistent state of that document. A single set
 * of margin settings apply throughout a document, so that gutter margins
 * are not supported.If set, the header and footer are located within the
 * top and bottom margins respectively. The <code>TPageMargins</code>
 * class stores the header and footer offsets, which determine the
 * position of the header and footer within the top and bottom margins.
 *
 * @since 5.0
 * @lib "print.lib"
 */
class TPageMargins
	{
public:
	IMPORT_C void InternalizeL(RReadStream& aStream); 	
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
public:
	TInt iHeaderOffset; // from top of page
	TInt iFooterOffset; // from bottom margin
	TMargins iMargins;
	};


/**
 *
 * Creates, stores, formats and inserts text and fields into a header and
 * footer.
 *
 * The header is located within the top page margin and the footer is
 * located within the bottom page margin. Only a single header or footer
 * may exist throughout a document. The header and footer can
 * independently be suppressed on the first pages of a
 * document.<code>CHeaderFooter</code> derives from the
 * <code>MTextFieldFactory</code> mixin class. This enables the insertion
 * of the following fields: — page number, total number of pages,
 * current date or time and filename.Headers and footers contain rich
 * text. The wide range of text manipulation and formatting functions
 * provided by class <code>CRichText</code> are easily accessed by means
 * of the rich text object which is owned by a header or footer.
 * Additionally, each header or footer owns the character and paragraph
 * format layers which are referenced by the rich text object. The
 * formatting of the header or footer is based upon these layers. The
 * header and footer are part of print setup information, encapsulated by
 * class <code>CPrintSetup</code>. They are accessed using the
 * <code>Header()</code> and <code>Footer()</code> member functions of
 * that class and they may be stored and restored together with the rest
 * of the print setup information.This class is not intended for user
 * derivation.
 *
 * @since 5.0
 * @lib "print.lib"
 */
class CHeaderFooter : public CBase, private MTextFieldFactory
	{
public:
	IMPORT_C static CHeaderFooter* NewL();
	IMPORT_C virtual ~CHeaderFooter();
	//
	IMPORT_C void CreateTextL();
	IMPORT_C void SetFirstPageToPrintTo(TInt aPageNum); // allows the first few pages of a doc not to have a header on them
	inline TInt FirstPageToPrintTo()const; // relative to the first page being numbered 0
	//
	// persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId,MPictureFactory* aFactory);
	IMPORT_C void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap)const;
	IMPORT_C void RestoreComponentsL(const CStreamStore& aStore,MPictureFactory* aFactory);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	//
	// text bits
	IMPORT_C CRichText* Text()const;
	IMPORT_C CParaFormatLayer* ParaFormat()const;
	IMPORT_C CCharFormatLayer* CharFormat()const;
	IMPORT_C void SetText(CRichText* aText); // takes ownership
	IMPORT_C void SetParaFormat(CParaFormatLayer* aParaFormat); // takes ownership
	IMPORT_C void SetCharFormat(CCharFormatLayer* aCharFormat); // takes ownership
	//
	// field bits
	IMPORT_C void SetFileNameInfo(const MFieldFileNameInfo& aFileNameInfo); // call if you want headers/footers to support filename fields
	IMPORT_C void SetNumPagesInfo(const MFieldNumPagesInfo& aNumPagesInfo); // call if you want headers/footers to support "total number of pages" fields
	inline MFieldFileNameInfo* FileNameFieldInfo()const;
	inline MFieldNumPagesInfo* NumPagesFieldInfo()const;
	//
	void SetPageNumInfo(const MFieldPageNumInfo& aPageNumInfo); // called by CPrintSetup
private:
	CHeaderFooter();
	void CreateFormatLayersL();
	// from MTextFieldFactory
	CTextField* NewFieldL(TUid aFieldType);
private:
	TInt iFirstPageToPrintTo; // relative to the first page being numbered 0
	MFieldFileNameInfo* iFileNameInfo;
	MFieldPageNumInfo* iPageNumInfo;
	MFieldNumPagesInfo* iNumPagesInfo;
	CRichText* iText; // RichText Doc Handle
	CParaFormatLayer* iParaLayer;
	CCharFormatLayer* iCharLayer;
private:
	enum { ETextExists = 0x0001 };
	};

/**
 *
 * Print progress and status notification interface class.
 *
 * The three notification functions are called before, during and after
 * the completion of a print or print preview operation, to provide
 * notification of the operation's progress. These functions should be
 * implemented by classes which derive from this mixin.In a typical
 * application, the print process observer will be the standard GUI print
 * progress or print preview dialog. If so, the application programmer
 * need not be concerned with implementing a class deriving from this
 * mixin.Otherwise, after implementing a class deriving from
 * <code>MPrintProcessObserver</code>, an object of this class should be
 * passed as a parameter to <code>CPrintSetup::StartPrintL()</code>, or
 * to <code>CPrintSetup::StartPreviewPrintL()</code>. Its notification
 * functions are automatically called during the course of the print
 * process. If no notification is required, the observer may in both
 * cases be NULL.Writing derived classes:A class which derives from this
 * mixin should provide an implementation of the three print notification
 * functions, any of which may be empty.
 *
 * @since 5.0
 * @lib "N/A"
 */
class MPrintProcessObserver
	{
public:
	/**
	 *
	 * Notifies that a print or print preview operation is about to begin.
	 *
	 * It may also be used to display information about the document to be
	 * printed. It is called once, immediately before printing or print
	 * previewing begins.When subclassing, add variables to store
	 * initialisation information as required
	 *
	 * @param     "TPrintParameters aPrintParams"
	 *            The parameters for the current print job
	 */
	virtual void NotifyPrintStarted(TPrintParameters aPrintParams)=0;
	/**
	 *
	 * Notifies that a band is about to be printed.
	 *
	 * It may be used to display information about the progress of the print
	 * operation, including the number of the page being printed. This
	 * function is called immediately before each band is printed. It will
	 * typically be used to implement a print progress indication control.
	 *
	 * @param     "TInt aPercentageOfPagePrinted"
	 *            Percentage of page which has been printed
	 * @param     "TInt aCurrentPageNum"
	 *            Number of page currently being printed
	 * @param     "TInt aCurrentCopyNum"
	 *            Number of copy currently being printed
	 */
	virtual void NotifyBandPrinted(TInt aPercentageOfPagePrinted, TInt aCurrentPageNum, TInt aCurrentCopyNum)=0;
	/**
	 *
	 * Notifies that the print or print preview operation has completed.
	 *
	 * It may be used to display information about how the print operation
	 * completed. For example if the print operation failed, this function
	 * may be used to report the error which caused the failure. It is called
	 * once, immediately after the print job terminates.
	 *
	 * @param     "TInt anErrorCode"
	 *            <code>KErrNone</code> if the print job completed
	 *            successfully, otherwise another of the system-wide
	 *            error codes.
	 */
	virtual void NotifyPrintEnded(TInt anErrorCode)=0;
	//
	};


//
// inlines
//

/**
 *
 * Gets the first page on which the header or footer is to be printed.
 *
 * Note:The first page is numbered zero.
 *
 * @returns   "TInt"
 *            The number of the first page on which the header or
 *            footer is to be printed, offset from zero.
 */ 
inline TInt CHeaderFooter::FirstPageToPrintTo()const
	{ return iFirstPageToPrintTo; }

/**
 *
 * Gets the object which provides this <code>CHeaderFooter</code> with
 * filename update information.
 *
 * @returns   "MFieldFileNameInfo*"
 *            Object which implements
 *            <code>UpdateFieldFileName()</code> function.
 */
inline MFieldFileNameInfo* CHeaderFooter::FileNameFieldInfo()const
	{ return iFileNameInfo; }

/**
 *
 * Gets the object which provides this <code>CHeaderFooter</code> with
 * total number of pages update information.
 *
 * @returns   "MFieldNumPagesInfo*"
 *            Object which implements
 *            <code>UpdateFieldNumPages()</code> function.
 */
inline MFieldNumPagesInfo* CHeaderFooter::NumPagesFieldInfo()const
	{ return iNumPagesInfo; }

#endif
