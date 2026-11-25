// MDXMLProcessing Instruction.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLProcessingInstruction.h
 * This class represents a Processing Instruction section of an XML file -
 * basically it is a chunk of text which has a place in the
 * object tree but has no children.
 */

#ifndef __MDXMLPROCINSTR_H__
#define __MDXMLPROCINSTR_H__

#include <e32base.h>
#include "MDXMLCharacterData.h"


class CMDXMLProcessingInstruction : public CMDXMLCharacterData
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMProcessingInstruction
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLProcessingInstruction* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLElement
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLProcessingInstruction* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLProcessingInstruction();

	/**
	 * Outputs a start tagfor the node which includes the
	 * tag name and all attribute name value pairs currently
	 * specified.  If the node is an empty node then it
	 * makes the tag an empty node tag, otherwise it creates
	 * a start tag.
	 * @param aComposer Composer to use to output the tag.
	 * @return Returns KerrNone if successful or a file write error
	 */
	virtual TInt ComposeStartTagL(CMDXMLComposer& aComposer);

protected:
	/**
	 * Constructor
	 * @param aOwnerDocument The document at the root of the DOM tree
	 */
	CMDXMLProcessingInstruction( CMDXMLDocument* aOwnerDocument );
};


#endif
