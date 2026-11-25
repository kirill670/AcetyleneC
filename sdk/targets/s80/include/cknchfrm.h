// CKNCHFRM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
/*
* ============================================================================
*  Name     : MCknConversionUi
*  Part of  : CKON

* ============================================================================
*/
#ifndef CKNCHFRM_H
#define CKNCHFRM_H


// INCLUDES
#include <e32base.h>
#include <ConArc.h>


// DATA TYPES


// FORWARD DECLARATIONS
class CEikDocument;
class CConverterBase;


// CLASS DECLARATIONS

/**
 * The MCknConversionUi class implements an interface to convert a document.
 *
 * used by the SaveAs dialog for change format functionality
 *
 * any application which doesn't implement standard application documents should provide
 * one of these when using the SaveAs dialog (if they require change format functionality)
 *
 * ConvertL should save the document to a temporary file, and then convert using aConverter to aFileName
 *
 * SaveL should just save the file directly to aFileName in native format
 *
 *  Link against CKNDLG.LIB
 */
class MCknConversionUi
	{
	public:
	// New methods
        
		/**
		* ConvertL saves the document to a temporary file, and then converts it using aConverter to aFileName.
		* @param aDocument Document to be saved and converted
		* @param aConverter Converter that converts a temporary file to aFileName
		* @param aFileName File name
		* <BR><B>Type of return value:</B> void
		*/
		virtual void ConvertL(CEikDocument& aDocument,CConverterBase& aConverter,const TDesC& aFileName)=0;
		/**
		* Saves the file directly to aFileName in native format.
		* @param aDocument Document to be saved
		* @param aFileName Saved file name
		* <BR><B>Type of return value:</B> void
		*/
		virtual void SaveL(CEikDocument& aDocument,const TDesC& aFileName)=0;
	};

/**
 * The CCknConversionUi class implements the
 *
 * default change format implementation used by the 'Save as' dialog. Saves the application
 * document to a temporary file, and then uses ConArc to change the format
 *  Link against CKNDLG.LIB
 */
class CCknConversionUi : public CBase, public MCknConversionUi/*, public MConverterUiObserver*/
	{
public:
	// Constructors and destructor
		/**
		* Static constructor.
		*/
		IMPORT_C static CCknConversionUi* NewL();
		/**
		* Saves a normal application to a temporary file and then converts it and renames it to aFileName
		* This function is a utility function so that applications can save in a different format once they
		* have a TDataType, which will have been returned by the SaveAsDialog
		* @param aDocument Document to be converted
		* @param aMimeType Converter
		* @param aFileName 'Saved' file name
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void ConvertL(CEikDocument& aDocument,const TDataType& aMimeType,const TDesC& aFileName);
		/**
		* Saves a normal application to a temporary file and then converts it and renames it to aFileName
		* @param aDocument Document to be saved and converted
		* @param aConverter Converter
		* @param aFileName 'Saved' file name
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConvertL(CEikDocument& aDocument,CConverterBase& aConverter,const TDesC& aFileName);
		/**
		* Saves a normal application to a temporary file and then renames it to aFileName
		* @param aDocument Document to be saved
		* @param aFileName 'Saved' file name
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SaveL(CEikDocument& aDocument,const TDesC& aFileName);
    private: //Methods
		void ConstructL();

		void DoConvertCallBackL();

		void MaxSteps(TInt aMax, TInt aObject);

		TInt Result(TInt aResult, TInt aObject); // Passes in a TResult, returns a TAction

		CConverterBase* EmbeddedObject(TDataType& aType);

		static TInt ConvertCallBackL(TAny* aObj);

		static void DoConvertL(CEikDocument& aDocument,CConverterBase& aConverter,const TDesC& aFileName);
	};
#endif      // CKNCHFRM_H   
            
// End of File
