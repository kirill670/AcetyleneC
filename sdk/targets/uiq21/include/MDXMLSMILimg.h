// MDXMLSMILimg.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILimg.h
 * This file contains the declaration of the CMDXMLSMILimg class.
 * This class represents a img element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILIMG_H__
#define __MDXMLSMILIMG_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILimg : public CMDXMLSMILMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILimg
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILimg* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILimg
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILimg* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new img element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILimg* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an img pointer if the node is of type img, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILimg* CastToSMILimg( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next img sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILimg* NextimgSibling();

	/**
	 * @return Returns a pointer to the previous img sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILimg* PreviousimgSibling();

	IMPORT_C virtual ~CMDXMLSMILimg();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILimg( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File