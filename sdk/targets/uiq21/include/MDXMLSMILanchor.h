// MDXMLSMILanchor.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILanchor.h
 * This file contains the declaration of the CMDXMLSMILanchor class.
 * This class represents an anchor element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILANCHOR_H__
#define __MDXMLSMILANCHOR_H__

#include <e32base.h>


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILanchor : public CMDXMLSMILAnchorBase
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILanchor
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILanchor* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILanchor
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILanchor* NewL( CMDXMLDocument* aOwnerDocument );

	/**
	 * This factory function creates a new anchor element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILanchor* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);
	
	/**
	 * @param aNode pointer to cast from
	 * @return Returns an anchor pointer if the node is of type anchor, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILanchor* CastToSMILanchor( CMDXMLNode* aNode );

	IMPORT_C virtual ~CMDXMLSMILanchor();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILanchor( CMDXMLDocument* aOwnerDocument );

	};

#endif

// End of File