// MDXMLComposer.h
//
/** @file MDXMLComposer.h
 * This file contains the declaration of the generic CMDXMLComposer class 
 * which is responsible for creating an XML file
 * from a given DOM structure.
 */


#ifndef __MDXMLCOMPOSER_H
#define __MDXMLCOMPOSER_H

#include <e32base.h>
#include <f32file.h>
#include "MDXMLConstants.h"
#include <Charconv.h>

//forward reference
class CMDXMLDocument;
class CMDXMLEntityConverter;


class MMDXMLComposerObserver
	{
public:
	/**
	 * Call back function used to inform client of Composer when RunL function completes
	 */
	virtual void ComposeFileCompleteL() = 0;
	};


class CMDXMLComposer: public CActive
	{
public:
	/**
	 * Destructor
	 */
	IMPORT_C ~CMDXMLComposer();

public:
	/**
	 * Starts file composition.
	 * @param aRFS File system to use
	 * @param aFileToCompose Name of file to create
	 * @param aDocument The document object to compose to the file
	 * @returns KERRNone if successful
	 */
	IMPORT_C TInt ComposeFile(RFs aRFs, TDesC& aFileToCompose, CMDXMLDocument* aDocument, TXMLFileType aFileType);

	/**
	 * @returns error code held within internal member variable
	 */
	inline const TInt Error() const {return iError;}

public: // public functions used by other classes within the .dll, not for Export.
	/**
	 * @returns the entity converter used by the composer.
	 */
	inline CMDXMLEntityConverter* EntityConverter() {return iEntityConverter;}
	
	/**
	 * Output a comment
	 * @param aComment the comment text to output
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputCommentL(const TDesC& aComment);
	
	/**
	 * Output a processing instruction
	 * @param aInstruction the processing instruction text to output
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputProcessingInstructionL(const TDesC& aInstruction);

	/**
	 * Output raw data
	 * @param the data to be output
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputDataL(const TDesC& aData);

	/**
	 * Output a start of element tag
	 * @param aElementName the name of the tag to output
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputStartOfElementTagL(const TDesC& aElementName);

	/**
	 * Output an end of element start tag
	 * @param aHasChildren true if the element has children
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputEndOfElementTagL(const TBool aHasChildren);

	/**
	 * Output an end of element tag
	 * @param aElementName the name of the tag to output
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputEndTagL(const TDesC& aElementName);

	/**
	 * Output an attribute - name and value.
	 * @param aAttributeName the name of the attribute to output
	 * @param aAttributeValue the text of the attribute value to output
	 * @returns KERRNone if successful, otherwise a file writing error.
	 */
	TInt OutputAttributeL(const TDesC& aAttributeName, const TDesC& aAttributeValue);

protected:
	/**
	 * BaseConstructL function to be called by dervived classes during their construction
	 */
	void BaseConstructL();

	/**
	 * RunError function inherited from CActive base class - intercepts any Leave from
	 * the RunL() function, sets an appropriate errorcode and calls ComposeFileCompleteL
	 */
	TInt RunError(TInt aError);

	 /**
	 * DoCancel function inherited from CActive base class
	 */
	virtual void DoCancel();

	/**
	 * RunL function inherited from CActive base class - does the actual composition
	 * @exception can Leave due to OOM
	 */
	virtual void RunL();
	
	/**
	 * Function to write string to required file format - handles format conversion
	 * @param aStringToWrite the string to output
	 * @return returns KERRNone if successful or a file write error.
	 */
	virtual TInt WriteFileL(const TDesC& aStringToWrite);

	/**
	 * Function to flush output string to required file format - handles format conversion
	 * @return returns KERRNone if successful or a file write error.
	 */
	virtual TInt FlushOutputBufferL();

protected:
	/**
	 * Constructor
	 */
	CMDXMLComposer(MMDXMLComposerObserver* aComposerObserver);

protected:
	/**
	 * Sets the entity converter to be used
	 * @param aEntityConverter The entity converter to be used
	 */
	inline void SetEntityConverter(CMDXMLEntityConverter* aEntityConverter) {iEntityConverter = aEntityConverter;}

	/**
	 * Sets iError to new errorcode if more serious than any error so far encountered
	 */
	void SetError(const TInt aErrorCode, const TXMLErrorCodeSeverity aSeverity);

protected:
	MMDXMLComposerObserver* iComposerObserver;
	CMDXMLEntityConverter* iEntityConverter;	///< Entity converter to use
	CMDXMLDocument* iXMLDoc;					///< XML document being composed
	RFile iXMLFile;								///< File being composed
	TXMLFileType iFileType;						///< Type of file being composed
	TInt iError;								///< Current error
	TXMLErrorCodeSeverity iSeverity;			///< ErrorCode severity
	CCnvCharacterSetConverter* iCharconv;
	TBuf<KWriteBufferLen> iOutputBuffer;
	RFs iRFs;									///< File system to use
	
#ifdef _DEBUG
	TInt iIndentationLevel;
#endif
	};

#endif
