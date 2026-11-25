// MDXMLSMILComposer.h
//
/** @file MDXMLSMILComposer.h
 * This file contains the declaration of the DTD-specific CMDXMLSMILComposer class 
 * which is responsible for creating an XML file
 * from a given DOM structure.
 */


#ifndef __MDXMLSMILCOMPOSER_H
#define __MDXMLSMILCOMPOSER_H

#include "MDXMLComposer.h"

//forward reference
class CMDXMLDocument;
class CMDXMLEntityConverter;


class CMDXMLSMILComposer: public CMDXMLComposer
	{
public:
	/**
	 * Two phase static factory function constructor
	 * @returns Created CMDXMLSMILComposer
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILComposer* NewL(MMDXMLComposerObserver* aComposerObserver);

	/**
	 * Two phase static factory function constructor
	 * @returns Created CMDXMLSMILComposer
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILComposer* NewLC(MMDXMLComposerObserver* aComposerObserver);

	IMPORT_C virtual ~CMDXMLSMILComposer();
protected:
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

private:
	/**
	 * First stage constructor
	 */
	CMDXMLSMILComposer(MMDXMLComposerObserver* aComposerObserver);

	/**
	 * Second stage constructor
	 */
	void ConstructL();
	};


#endif
