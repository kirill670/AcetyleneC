// MDXMLSMILanimation.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILanimation.h
 * This file contains the declaration of the CMDXMLSMILanimation class.
 * This class represents an animation element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILANIMATION_H__
#define __MDXMLSMILANIMATION_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"
#include "MDXMLSMILTimedMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILanimation : public CMDXMLSMILTimedMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILanimation
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILanimation* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILanimation
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILanimation* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new animation element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILanimation* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an animation pointer if the node is of type animation, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILanimation* CastToSMILanimation( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next animation sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILanimation* NextanimationSibling();

	/**
	 * @return Returns a pointer to the previous animation sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILanimation* PreviousanimationSibling();

	IMPORT_C virtual ~CMDXMLSMILanimation();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILanimation( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File