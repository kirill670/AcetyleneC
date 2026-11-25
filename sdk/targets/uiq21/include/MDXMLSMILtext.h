// MDXMLSMILtext.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILtext.h
 * This file contains the declaration of the CMDXMLSMILtext class.
 * This class represents a text element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILTEXT_H__
#define __MDXMLSMILTEXT_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILtext : public CMDXMLSMILMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILtext
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILtext* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILtext
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILtext* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new text element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILtext* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns a text pointer if the node is of type text, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILtext* CastToSMILtext( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next text sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtext* NexttextSibling();

	/**
	 * @return Returns a pointer to the previous text sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtext* PrevioustextSibling();

	IMPORT_C ~CMDXMLSMILtext();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILtext( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File