// MDXMLParser.h
//
/** @file MDXMLParser.h
 * This file contains the declaration of the generic CMDXMLParser class 
 * which is responsible for creating a DOM structure 
 * from a given XML file.
 */


#ifndef __MDXMLPARSER_H
#define __MDXMLPARSER_H

#include <e32std.h>
#include <eikenv.h>
#include "MDXMLConstants.h"

//forward reference
class CMDXMLDocument;
class CMDXMLEntityConverter;
class CMDXMLElement;


class MMDXMLParserObserver
	{
public:
	/**
	 * Call back function used to inform client of Parser when RunL function completes
	 */
	virtual void ParseFileCompleteL() = 0;
	};

class CMDXMLParser: public CActive
	{
public:
	/**
	 * Destructor
	 */
	IMPORT_C ~CMDXMLParser();

public:
	/**
	 * @returns error code held within internal member variable
	 */
	inline const TInt Error() const {return iError;}

	/**
	 * @returns CMDXMLDocument* the created DOM, should be called after the 
	 * conclusion of the parser process.  Note that internal variable pointing to 
	 * the document is set to NULL so this function can only be called once per file
	 * parse.  Client application must take ownership of document for cleanup purposes.
	 */
	IMPORT_C CMDXMLDocument* DetachXMLDoc();

	/**
	 * ParseFile opens a file ready for parsing
	 * @param aRFs a resource file session used for file I/O
	 * @param aFileToParse the file name to parse
	 * @returns KErrNone if all OK or file read error code
	 */
	IMPORT_C TInt ParseFile(RFs aRFs, TDesC& aFileToParse);

public: // public functions used by other classes within the .dll, not for Export.
	/**
	 * @returns the CMDXMLEntityConverter for use in converting built in entity 
	 * and character entities back to their original format
	 */
	CMDXMLEntityConverter* EntityConverter();

protected:
	/**
	 * DoCancel function inherited from CActive base class
	 */
	virtual void DoCancel();

	/**
	 * RunL function inherited from CActive base class - carries out the actual parsing.
	 * @exception can Leave due to OOM
	 */
	virtual void RunL();

	/**
	 * RunError function inherited from CActive base class - intercepts any Leave from
	 * the RunL() function, sets an appropriate errorcode and calls ParseFileCompleteL
	 */
	TInt RunError(TInt aError);

protected:
	/**
	 * Constructor
	 */
	CMDXMLParser(MMDXMLParserObserver* aParserObserver);

protected:

	/**
	 * Called when a character is read in and found to bo outside of an element tag
	 */
	virtual void HandleText(TDes& aChar);

	/**
	 * Fetch one character from the input file
	 * @param aChar the returned character.
	 * @return returns true if a character returned or false if the file is finished
	 */
	TBool GetChar(TDes& aChar);

	/**
	 * @return Returns true if the current tag is a doctype tag and sets the
	 * Document DocType member accordingly on the first pass of this function.
	 */
	TBool DocTypeL();

	/**
	 * creates a new processing instruction if necessary and adds to document
	 * @return Returns true if the current tag is a processing instruction
	 */
	TBool ProcessingInstructionL(CMDXMLElement* aParentElement);

	/**
	 * @return returns true if the current tag is a version id tag and sets the
	 * Document Version member accordingly on the first pass of this function.
	 */
	TBool VersionIDL();

	/**
	 * creates a new comment if necessary and adds to document
	 * @return returns true if the current tag is a comment tag
	 */
	TBool CommentL(CMDXMLElement* aParentElement);

	/*
	 * Sets the entity converter to be used for parsing.
	 * @param aEntityConverter the entity converter to be used.
	 */
	inline void SetEntityConverter(CMDXMLEntityConverter* aEntityConverter) {iEntityConverter = aEntityConverter;}

	/**
	 * Parse a start of element tag and create an element with attributes set.
	 * @return Returns a pointer to the created element
	 * @exception can Leave due to OOM
	 */
	virtual CMDXMLElement* ParseStartTagL();

	/**
	 * Detects the type of a file - can be Unicode or ASCII
	 */
	void DetectFileType();

	/**
	 * Creates a generic or DTD-specific document object
	 * @exception can Leave due to OOM
	 */
	virtual void CreateDocumentL();

	/**
	 * Sets iError to new errorcode if more serious than any error so far encountered
	 */
	void SetError(const TInt aErrorCode, const TXMLErrorCodeSeverity aSeverity);

protected:
	MMDXMLParserObserver* iParserObserver;
	TInt iError;								///< Current error
	TXMLErrorCodeSeverity iSeverity;			///< ErrorCode severity
	CMDXMLDocument* iXMLDoc;					///< Document created by the parser
	CMDXMLEntityConverter* iEntityConverter;	///< Entity converter used by the parser
	RFile iXMLFile;								///< XML file to be parsed
	HBufC* iElementTag;							///< Currently processed element tag
	TBool iDocTypeSet;
	TBool iVersionSet;
	TInt iBytesPerChar;
	TBuf8<KReadBufferLen> iInputBuffer;
	TPtr iInputBufferPtr;
	TInt iCurrentInputBufferLen;
	TInt iNextChar;
	};

#endif
