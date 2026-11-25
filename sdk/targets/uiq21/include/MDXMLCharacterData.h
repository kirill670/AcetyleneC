// MDXMLCharacterData.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLCharacterData.h
 * This class represents a section of an XML file -
 * basically it is a chunk of text which has a place in the
 * object tree but has no children.
 * Objects such as CDATA sections, Comments and Processing Instructions
 * derive from it.
 */

#if !defined(__MDXMLCHARACTERDATA_H__)
#define __MDXMLCHARACTERDATA_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMDXMLCharacterData : public CMDXMLNode
{
public:
	IMPORT_C virtual ~CMDXMLCharacterData();

	/**
	 * @return Returns the text of the section
	 */
	IMPORT_C virtual TDesC& Data();

	/** 
	 * Sets the whole of the section text
	 * @param aData Text to set.
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C virtual void SetDataL( TDesC& aData );

	/**
	 * @return Returns the length of the text
	 */
	IMPORT_C virtual TInt Length();

	/**
	 * Appends text to the section
	 * @param aData Text to append
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C virtual void AppendL( TDesC& aData );

	/**
	 * Inserts text at a point in the section
	 * @param aInsertPos The position to insert the text (0 means insert at the start)
	 * @param aData Text to insert
	 * @exception Can Leave due to OOM
	 * @return Returns KErrNone if successful or KErrNotFound if the insert position is out of range
	 */
	IMPORT_C virtual TInt InsertL( TInt aInsertPos, TDesC& aData );

	/**
	 * Replaces a block of text in the section
	 * @param aInsertPos The position to insert the text (0 means insert at the start)
	 * @param aLength The number of characters to replace
	 * @param aData Text to insert
	 * @exception Can Leave due to OOM
	 * @return Returns KErrNone if successful or KErrNotFound if the replace block is out of range
	 */
	IMPORT_C virtual TInt ReplaceL( TInt aInsertPos, TInt aLength, TDesC& aData );

	/**
	 * Outputs a start tagfor the node which includes the
	 * tag name and all attribute name value pairs currently
	 * specified.  If the node is an empty node then it
	 * makes the tag an empty node tag, otherwise it creates
	 * a start tag.
	 * @param aComposer Composer to use to output the tag.
	 * @return Returns KerrNone if successful or a file write error
	 */
	virtual TInt ComposeStartTagL(CMDXMLComposer& aComposer) = 0;

	/**
	 * Check the children of this node for legality - must be defined based on DTD.
	 * For a character data section there can be no children so this always returns true.
	 * @return True if the node has legitimate children
	 */
	IMPORT_C virtual TBool CheckChildren();

protected:
	/**
	 * Constructor
	 * @param aNodeType The node type of the derived object
	 * @param aOwnerDocument The Document at the root of the DOM tree.
	 */
	CMDXMLCharacterData( TDOMNodeType aNodeType, CMDXMLDocument* aOwnerDocument );

private:
	HBufC* iData;	//< Buffer to hold the actual text of the CDATA section
};


#endif
