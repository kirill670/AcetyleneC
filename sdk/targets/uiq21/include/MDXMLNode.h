// MDXMLNode.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLNode.h
 * This file contains the declaration of the CMDXMLNode class which
 * is the base class for the Mini-DOM.
 */

#ifndef __MDXMLNODE_H__
#define __MDXMLNODE_H__

#include <e32base.h>


// forward references
class CMDXMLComposer;
class CMDXMLDocument;
class CMDXMLEntityConverter;

/**
 *	This class forms the basis for the Mini-DOM.  It is a
 *	pure abstract class and it's sole concern is the node
 *	type and name and the management of the list of child
 *	nodes.
 *
 *	The node name and type are set in the constructor and
 *	cannot be changed thereafter.
 *
 *	The list of child nodes is managed as a doubly-linked
 *	list, not an array or similar structure.  Derived
 *	classes which are not allowed children will override the
 *	operations to manipulate the child list.
 */
class CMDXMLNode : public CBase
{
public:
	/// XML DOM Node Types - The actual values are taken from the DOM definition but we only use some of them.
	enum TDOMNodeType
		{
		EElementNode=1,					///< Element
		ETextNode=3,					///< Text
		ECDATASectionNode=4,			///< CDATA Section
		EProcessingInstructionNode=7,	///< Processing Instruction
		ECommentNode=8,					///< Comment
		EDocumentNode=9					///< Document
		};

	/**
	 * When this node is deleted it will links its previous and next siblings across the gap, will
	 * delete all of its children and will correct its parents first and last child pointers if necessary.
	 */
	IMPORT_C virtual ~CMDXMLNode();

	/**
	 * @return Returns the node type of the node
	 */
	inline TDOMNodeType NodeType() {return iNodeType;}

	/**
	 * @return Returns the name of the node
	 */
	IMPORT_C TPtrC NodeName();

	/**
	 * @return Returns true if the node has any child nodes, false otherwise
	 */
	inline TBool CanHaveChildNodes() {return iCanHaveChildren;}

	/**
	 * @return Returns true if the node has any child nodes, false otherwise
	 */
	inline TBool HasChildNodes() {return (iFirstChildPtr != NULL);}

	/**
	 * @return Returns a pointer to the document which is the owner of the DOM tree
	 */
	inline CMDXMLDocument* OwnerDocument() {return (CMDXMLDocument*)iOwnerDocument;}

	/**
	 * @return Returns a pointer to the first child node if any, oherwise returns NULL
	 */
	inline CMDXMLNode* FirstChild() {return iFirstChildPtr;}

	/**
	 * @return Returns a pointer to the last child node if any, oherwise returns NULL
	 */
	inline CMDXMLNode* LastChild() {return iLastChildPtr;}

	/**
	 * @return Returns a pointer to the next sibling node if any, oherwise returns NULL
	 */
	inline CMDXMLNode* NextSibling() {return iNextSiblingPtr;}

	/**
	 * @return Returns a pointer to the previous sibling node if any, oherwise returns NULL
	 */
	inline CMDXMLNode* PreviousSibling() {return iPrevSiblingPtr;}

	/**
	 * @return Returns a pointer to the parent node if any, oherwise returns NULL (only at root of tree)
	 */
	inline CMDXMLNode* ParentNode() {return iParentPtr;}

	/**
	 * @return Returns the enumerated element type (same information as node name but faster to access)
	 */
	inline TInt ElementType() {return iElementType;}

	/**
	 * Removes a child from the list of child nodes.  The child node is not deleted - that is the responsibility of the caller
	 * @param aChildToRemove Pointer to child to remove from the list
	 * @return Returns KERRNone if sucessful or KErrNotFound if the referenced child node is not found
	 */
	IMPORT_C TInt RemoveChild(CMDXMLNode* aChildToRemove);

	/**
	 * Inserts a new child node at a specific point in the child list.
	 * @param aInsertBeforeChild Pointer to the element before which the new child should be inserted (NULL to insert at the start of the list)
	 * @param aChildToInsert Pointer to the new child node to insert.
	 * @return Returns KErrNone if successful, KErrXMLInvalidChild if the node cannot have children or KErrNotFound if it cannot fnd the child before which to insert
	 */
	IMPORT_C TInt InsertBefore(CMDXMLNode* aInsertBeforeChild, CMDXMLNode* aChildToInsert);

	/**
	 * Appends a new child at the end of the child list.
	 * @param aChildToInsert Pointer to the new child node to append.
	 * @return Returns KErrNone if successful or KErrXMLInvalidChild if the node cannot have children
	 */
	IMPORT_C TInt AppendChild(CMDXMLNode* aChildToInsert);

	/**
	 * Inserts a new child node while removing an existing one.  The old child is not deleted.
	 * @param aChildToInsert Pointer to the new child node to insert.
	 * @param aChildToReplace Pointer to the child node to be replaced.
	 * @return Returns KErrNone if successful, KErrXMLInvalidChild if the node cannot have children or KErrNotFound if it cannot fnd the child to replace.
	 */
	IMPORT_C TInt ReplaceChild(CMDXMLNode* aChildToInsert, CMDXMLNode* aChildToReplace);

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
	 * Outputs an end tag for the node.
	 * @param aComposer The composer to use - provides access to output and entity conversion
 	 * @return Returns KerrNone if successful or a file write error
	 */
	virtual TInt ComposeEndTagL(CMDXMLComposer& aComposer);

	/**
	 * Function to output the contents of the node as XML to some output stream.
	 * @param aComposer The composer to use - provides access to output and entity conversion
	 * @return Returns KerrNone if successful or a file write error
	 * @exception Can Leave due to OOM.
	 */
	virtual TInt ComposeL(CMDXMLComposer& aComposer );

	/**
	 * Check the children of this node for legality - must be defined based on DTD.
	 * @return True if the node has legitimate children
	 */
	IMPORT_C virtual TBool CheckChildren()=0;

protected:
	/**
	 * The node type will normally be hard-wired in any derived class constructor.
	 * The node name and HaveChildren flag will normally be hard-wired in a derived class constructor unless it
     * covers a generic element.
	 * @param aNodeType The tpe of node to be created
	 * @param aCanHaveChildren Flag to indicate if the node represents a node which is allowed children
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree - if NULL then assume this is the root
	 */
	CMDXMLNode( TDOMNodeType aNodeType, TBool aCanHaveChildren, CMDXMLDocument* aOwnerDocument );

	/**
	 * @return Returns a pointer to the previous sibling node of the same type if any,
	 * oherwise returns NULL
	 */
	CMDXMLNode* PreviousSameTypeSibling();

	/**
	 * @return Returns a pointer to the next sibling node of the same type if any,
	 * oherwise returns NULL
	 */
	CMDXMLNode* NextSameTypeSibling();

	/**
	 * Set the node name - normally on creation
	 * @param aNodeName The node name - commonly an element tag name - _not_ any unique identifier
	 * @exception Can Leave due to OOM
	 */
	void SetNodeNameL(const TDesC& aNodeName);
	
	/**
	 * Sets the enumerated element type (same information as node name but faster to access)
	 */
	inline void SetElementType( TInt aElementType ) {iElementType = aElementType;}

private:
	TInt iElementType;				///< Enumerated element type
	TDOMNodeType iNodeType;			///< Node type
	HBufC* iNodeName;				///< Name of the node, e.g. element tag name - not unique id
	CMDXMLNode* iParentPtr;			///< Pointer to parent node if any
	CMDXMLNode* iFirstChildPtr;		///< Pointer to first child node if any
	CMDXMLNode* iLastChildPtr;		///< Pointer to last child node if any
	CMDXMLNode* iNextSiblingPtr;	///< Pointer to next sibling if any
	CMDXMLNode* iPrevSiblingPtr;	///< Pointer to previous sibling if any
	CMDXMLDocument* iOwnerDocument;	///< Pointer to owning document
	TBool iCanHaveChildren;			///< true if this node is allowed to have children
};

#endif
// End Of File