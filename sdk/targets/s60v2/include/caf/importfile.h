// importfile.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.

#ifndef __IMPORTFILE_H__
#define __IMPORTFILE_H__

#include <e32base.h>

namespace ContentAccess
	{
	class CAgentInfo;
	class CSupplierOutputFile;
	class CCafMimeHeader;
	class CAgentSupplier;
	class CSupplier;

	/**
	* Created by the CSupplier to import a file. 
	*
	* The MIME type of the file must be one of the CAF supplier MIME types. 
	* Applications should check using CSupplier::IsImportSupported().
	*
	* This class creates a CAgentSupplier and uses it to import the file into the 
	* content access agent who supports the given MIME type.
	*
	* This class is single use only, and cannot be used to import multiple files. The 
	* import process may produce one or more output files.
	*
	* @publishedPartner
	* @prototype
	*
	*/
	class CImportFile: public CBase
		{
	public:
		virtual ~CImportFile();

		/** Passes a block of data to the agent.
		*
		* @param aData	Block of data from the message.
		* @return		KErrNone if the data was written successfully, 
		*				otherwise one of the standard error codes.
		*/
		IMPORT_C TInt WriteData(const TDesC8& aData);

		/** 
		* Passes a block of data to the CA agent. 
		*
		* The agent will use aStatus to notify the caller when it is ready for the next block.
		*
		* @param aData		Block of data from the message.
		* @param aStatus	Used to notify the caller that the CA agent is ready for the next block of data.
		*/
		IMPORT_C void WriteData(const TDesC8& aData, TRequestStatus& aStatus);

		/** 
		* Tells the CA agent that no more calls to WriteData() are required. 
		*
		* The entire file has now been transferred to the agent.
		*
		* @return	KErrNone if the data was written successfully, otherwise one of the standard
		* 			error codes.
		*/
		IMPORT_C TInt WriteDataComplete();

		/** 
		* Tells the CA agent that no more calls to WriteData() are required; 
		* the entire file has now been transferred to the agent.
		*
		* @param aStatus	Used to notify the caller when processing of the file is complete.
		*
		*/
		IMPORT_C void WriteDataComplete(TRequestStatus& aStatus);


		/** Gets the number of usable output files produced so far. 
		*
		* These files may only be partially complete but it allows a consumer process 
		* to begin reading the content at soon as it is available.
		*
		* @return The number of output files.
		*/
		IMPORT_C TInt OutputFileCountL() const;
		
		/** Gets details of the output file produced. 
		* 
		* The file may not be complete but it will
		* be in a state usable by the consumer framework.
		*
		* @return	Details of the output file.
		*/
		IMPORT_C CSupplierOutputFile& OutputFileL(TInt aIndex) const;


		
	private:
		friend class CSupplier;

		CImportFile();

		static CImportFile* NewL(CAgentInfo& aAgent, CCafMimeHeader& aMimeHeader, const TDesC& aOutputDirectory, const TDesC& aSuggestedFileName);

		void ConstructL(CAgentInfo& aAgent, CCafMimeHeader& aMimeHeader, const TDesC& aOutputDirectory, const TDesC& aSuggestedFileName);

		// Agent within CAF used to import the file
		CAgentSupplier *iAgentSupplier;

		// Need to increment the reference count of a CAgentInfo 
		// otherwise ECOM will unload the agent when we least expect it
		CAgentInfo *iAgent;

		};
	}
#endif