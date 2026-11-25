// MDXMLSMILtextstream.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILtextstream.h
 * This file contains the declaration of the CMDXMLSMILtextstream class.
 * This class represents a textstream element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILTEXTSTREAM_H__
#define __MDXMLSMILTEXTSTREAM_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"
#include "MDXMLSMILTimedMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILtextstream : public CMDXMLSMILTimedMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILtextstream
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILtextstream* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILtextstream
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILtextstream* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new textstream element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILtextstream* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an textstream pointer if the node is of type textstream, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILtextstream* CastToSMILtextstream( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next textstream sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtextstream* NexttextstreamSibling();

	/**
	 * @return Returns a pointer to the previous textstream sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtextstream* PrevioustextstreamSibling();

	IMPORT_C virtual ~CMDXMLSMILtextstream();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILtextstream( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File