// MDXMLSMILarea.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILarea.h
 * This file contains the declaration of the CMDXMLSMILarea class.
 * This class represents an area element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILAREA_H__
#define __MDXMLSMILAREA_H__

#include <e32base.h>


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILarea : public CMDXMLSMILAnchorBase
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILarea
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILarea* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILarea
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILarea* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new area element object 
	 * using the tag area passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute area
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILarea* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);
	
	/**
	 * @param aNode pointer to cast from
	 * @return Returns an area pointer if the node is of type area, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILarea* CastToSMILarea( CMDXMLNode* aNode );

	IMPORT_C virtual ~CMDXMLSMILarea();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILarea( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File