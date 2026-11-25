// MDXMLCDATASection.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLCDataSection.h
 * This class represents a CDATA section of an XML file -
 * basically it is a chunk of text which has a place in the
 * object tree but has no children.
 */

#if !defined(__MDXMLCDATA_H__)
#define __MDXMLCDATA_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMDXMLCDATASection : public CMDXMLCharacterData
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMCDATASection
	 * @exception can Leave due to OOM
	 */
	IMPORT_C CMDXMLCDATASection* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLCDATASection
	 * @exception can Leave due to OOM
	 */
	IMPORT_C CMDXMLCDATASection* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLCDATASection();

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
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLCDATASection( CMDXMLDocument* aOwnerDocument );
};


#endif
