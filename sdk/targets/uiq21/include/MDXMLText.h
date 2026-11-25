// MDXMLText.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLText.h
 * This class represents a text section of an XML file -
 * basically it is a chunk of text which has a place in the
 * object tree but has no children.
 */

#if !defined(__MDXMLTEXT_H__)
#define __MDXMLTEXT_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMDXMLText : public CMDXMLCharacterData
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLText
	 * @exception can Leave due to OOM
	 */
	IMPORT_C CMDXMLText* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLText
	 * @exception can Leave due to OOM
	 */
	IMPORT_C CMDXMLText* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLText();

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
	CMDXMLText( CMDXMLDocument* aOwnerDocument );
};


#endif
