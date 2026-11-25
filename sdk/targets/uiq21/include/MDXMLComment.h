// MDXMLComment.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLComment.h
 * This class represents a Comment section of an XML file -
 * basically it is a chunk of text which has a place in the
 * object tree but has no children.
 */

#if !defined(__MDXMLCOMMENT_H__)
#define __MDXMLCOMMENT_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMDXMLComment : public CMDXMLCharacterData
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMComment
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLComment* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLElement
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLComment* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLComment();

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
	CMDXMLComment( CMDXMLDocument* aOwnerDocument );
};


#endif
