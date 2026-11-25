// SMILParser.h
//
/** @file SMILParser.h
 * This file contains the declaration of the DTD-specific CMDXMLSMILParser class 
 * which is responsible for creating a DOM structure 
 * from a given XML file.
 */

#ifndef __SMILPARSER_H
#define __SMILPARSER_H

#include <e32std.h>
#include <eikenv.h>
#include "MDXMLParser.h"

//forward reference
class CMDXMLDocument;
class CMDXMLEntityConverter;
class CMDXMLElement;

class CMDXMLSMILParser: public CMDXMLParser
	{
public:
	/**
	 * Two phase static factory function constructor
	 * @returns Created CMDXMLSMILParser
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILParser* NewL(MMDXMLParserObserver* aParserObserver);

	/**
	 * Two phase static factory function constructor
	 * @returns Created CMDXMLSMILParser
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILParser* NewLC(MMDXMLParserObserver* aParserObserver);

	IMPORT_C ~CMDXMLSMILParser();
protected:
	/**
	 * Parse a start of element tag and create an element with attributes set.
	 * @return Returns a pointer to the created element
	 * @exception can Leave due to OOM
	 */
	virtual CMDXMLElement* ParseStartTagL();

	/*
	 * Creates a generic or DTD-specific document object
	 * @exception can Leave due to OOM
	 */
	virtual void CreateDocumentL();

	/**
	 * Called when a character is read in and found to bo outside of an element tag
	 */
	virtual void HandleText(TDes& aChar);

private:
	/**
	 * First stage constructor
	 */
	CMDXMLSMILParser(MMDXMLParserObserver* aParserObserver);

	/**
	 * Second stage constructor
	 */
	void ConstructL();
	};

#endif
