// supplieroutputfile.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.

#ifndef __SUPPLIEROUTPUTFILE_H__
#define __SUPPLIEROUTPUTFILE_H__

#include <e32base.h>
#include <caf/caf.h>

namespace ContentAccess
	{
	class CAttribute;

	/** 
	* Holds the details of an output file produced by CAF. 
	*
	* For instance:
	* @li filename
	* @li type of file (receipt or content)
	* @li MIME type (from Apparc)
	* @li can create a CAttribute for the output file.
	*
	* @publishedPartner
	* @prototype
	*/
	class CSupplierOutputFile : public CBase
		{
	public:
		IMPORT_C static CSupplierOutputFile* NewL(const TDesC& aFileName, const TOutputType aOutputType);

		~CSupplierOutputFile();

		/** Finds out the name of the file.
		*
		* @return	The name (with full path) of the output file produced.
		*/
		IMPORT_C TPtrC FileName() const;

		/** The type of the file, e.g., Content or a Receipt.
		* 
		* @return	The type of output file.
		*/
		IMPORT_C TOutputType OutputType() const;

		/** Uses Apparc to find out the MIME type of the output file.
		*
		* @return the MIME type. 
		*/
		IMPORT_C TPtrC8 MimeTypeL();

		/** 
		* Gets the attributes of the output file produced. 
		*
		* If the client does not wish to build a specific queryset, the aPreloaded parameter can be used
		* to update all the values in the Attributes response set before it is returned to the caller.
		*
		* Here is an example of how to retrieve attributes from a file that has been imported.
		*
		* @code
		*	
		* // how to test the attributes without needing to create a Queryset etc
		* CImportFile *import;
		* ....
		* CAttributes myAttributes = import->OutputFileL(x).AttributesL(ETrue);
  	    *
		* // test if file is protected
		* if(myAttributes.ResponseSet().IsSet(EProtected))
		*	{
		*	...
		*	}
		*
		* @endcode
		*
		* @param aPreloaded	Whether to query and update all attribute fields before returning the attribute.
		* @return			The output file's CAttributes.
		*/
		IMPORT_C CAttribute& AttributesL(TBool aPreloaded);

	private:
		CSupplierOutputFile(const TOutputType aOutputType);
		void ConstructL(const TDesC& aFileName);

		HBufC *iFileName;
		HBufC8 *iMimeType;
		TOutputType iOutputType;
		CAttribute *iAttr;
		};
	}
#endif