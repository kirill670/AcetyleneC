// MDXMLDocumentElement.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLDocumentElement.h
 * This file contains the declaration of the CMDXMLDocumentElement class.
 * This class represents a dummy XML element for use as the top level 
 * element by the document - this is required to cater for instances of 
 * badly formed XML documents that may be parsed.
 */

#ifndef __MDXMLDOCUMENTELEMENT_H__
#define __MDXMLDOCUMENTELEMENT_H__

#include <e32base.h>
#include "MDXMLElement.h"



class CMDXMLDocumentElement : public CMDXMLElement
{
public:
	/**
	 * Two phase constructor
  	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLDocumentElement
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLDocumentElement* NewLC( CMDXMLDocument* aOwnerDocument);

	/**
	 * Two phase constructor
  	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLDocumentElement
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLDocumentElement* NewL( CMDXMLDocument* aOwnerDocument);

	IMPORT_C virtual ~CMDXMLDocumentElement();

	/**
	 * Suppresses the outputs of a start tag for the element
	 * @param aComposer The composer to use - necessary to override the parent class
	 * @return Returns KErrNone
	 */
	virtual TInt ComposeStartTagL(CMDXMLComposer& aComposer);

	/**
	 * Suppresses the outputs of an end tag for the element.
	 * @param aComposer object - necessary to override the parent class
	 * @return Returns KErrNone
	 */
	virtual TInt ComposeEndTagL(CMDXMLComposer& aComposer);

protected: //construction
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree - if NULL then assume this is the root
	 */
	CMDXMLDocumentElement( CMDXMLDocument* aOwnerDocument );
};


#endif
