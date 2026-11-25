// MDXMLSMILpar.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILpar.h
 * This file contains the declaration of the CMDXMLSMILpar class.
 * This class represents a par element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILPAR_H__
#define __MDXMLSMILPAR_H__

#include <e32base.h>
#include "MDXMLSMILTimingElt.h"

// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILpar : public CMDXMLSMILTimingElt
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILpar
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILpar* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILpar
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILpar* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new par element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILpar* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns a par pointer if the node is of type par, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILpar* CastToSMILpar( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next par sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILpar* NextparSibling();

	/**
	 * @return Returns a pointer to the previous par sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILpar* PreviousparSibling();

	IMPORT_C virtual ~CMDXMLSMILpar();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILpar( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File