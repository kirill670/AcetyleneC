// MDXMLSMILref.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILref.h
 * This file contains the declaration of the CMDXMLSMILref class.
 * This class represents a ref element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILREF_H__
#define __MDXMLSMILREF_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"
#include "MDXMLSMILTimedMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILref : public CMDXMLSMILTimedMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILref
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILref* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILref
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILref* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new ref element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILref* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns a ref pointer if the node is of type ref, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILref* CastToSMILref( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next ref sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILref* NextrefSibling();

	/**
	 * @return Returns a pointer to the previous ref sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILref* PreviousrefSibling();

	IMPORT_C virtual ~CMDXMLSMILref();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILref( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File