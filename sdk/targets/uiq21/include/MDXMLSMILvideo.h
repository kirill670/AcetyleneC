// MDXMLSMILvideo.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILvideo.h
 * This file contains the declaration of the CMDXMLSMILvideo class.
 * This class represents a video element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILVIDEO_H__
#define __MDXMLSMILVIDEO_H__

#include <e32base.h>
#include "MDXMLSMILMediaObject.h"
#include "MDXMLSMILTimedMediaObject.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILvideo : public CMDXMLSMILTimedMediaObject
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILvideo
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILvideo* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILvideo
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILvideo* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new video element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILvideo* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns a video pointer if the node is of type video, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILvideo* CastToSMILvideo( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next video sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILvideo* NextvideoSibling();

	/**
	 * @return Returns a pointer to the previous video sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILvideo* PreviousvideoSibling();

	IMPORT_C virtual ~CMDXMLSMILvideo();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILvideo( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File