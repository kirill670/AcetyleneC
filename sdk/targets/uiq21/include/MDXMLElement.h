// MDXMLElement.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
/** @file MDXMLElement.h
 * This file contains the declaration of the CMDXMLElement class.
 * This class represents a generic XML element with attributes 
 * stored as name-value pairs.  DTD-specific element classes
 * will store their attributes as member variables.
 */

#ifndef __MDXMLELEMENT_H__
#define __MDXMLELEMENT_H__

#include <e32base.h>
#include "MDXMLNode.h"


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;


// Structures and definitions for child element checking.
// The child element checks are managed by a state machine and this type defines
// allowed transitions.
struct TXMLChildStateType
	{
	TInt         FromState;	// Starting state - 0 = initial state
	TInt         ToState;	// Next state - -1 = terminating state
	const TText *TagName;	// Name of tag causing the transition, empty string = finished
	TInt         TagLength;	// Length of tag string (helps to make the descriptor)
	};
#define MAKESTATETYPE( from, to, str ) { from, to, _S(str), (sizeof(str)-1) }

struct TXMLDescAttType
	{
	const TText *AttName;	// Name of attribute
	TInt         AttLength;	// Length of name string (helps to make the descriptor)
	};
#define MAKEATTTYPE( str ) { _S(str), (sizeof(str)-1) }

// Constants for the initial and terminal states
const TInt KXMLStartState = 0;
const TInt KXMLEndState = -1;
const TInt KXMLMinJump = 5; // Don't do binary chop below this size.  Not a critical value.


class CMDXMLElement : public CMDXMLNode
{
public:
	/**
	 * Two phase constructor
  	 * @param aCanHaveChildren Flag to indicate if the node represents a node 
  	 * @which is allowed children
  	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagName Name of the tag used to create the element
	 * @returns Created CMDXMLElement
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLElement* NewLC( TBool aCanHaveChildren, CMDXMLDocument* aOwnerDocument, TPtrC aTagName );

	/**
	 * Two phase constructor
  	 * @param aCanHaveChildren Flag to indicate if the node represents a node 
  	 * @which is allowed children
  	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagName Name of the tag used to create the element
	 * @returns Created CMDXMLElement
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLElement* NewL( TBool aCanHaveChildren, CMDXMLDocument* aOwnerDocument, TPtrC aTagName );

	IMPORT_C virtual ~CMDXMLElement();

	// Attribute handling routines.

	/**
	 * Returns the attribute value if it is set.
	 * @param aAttributeName Name of attribute to return
	 * @param aAttributeValue Value of attribute returned
	 * @return Returns KErrNone if successful, KErrNotFound if the named attribute 
	 * is not set or KErrNotSupported if the named attribute doesn't exist.
	 */
	IMPORT_C virtual TInt GetAttribute(const TDesC& aAttributeName, TPtrC& aAttributeValue ) const;

	/**
	 * Sets the attribute value.
	 * @param aAttributeName Name of attribute to set
	 * @param aAttributeValue Value of attribute
	 * @return Returns KErrNone if successful, KErrNotSupported if an invalid attribute name
	 * or attribute value.
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C virtual TInt SetAttributeL(const TDesC& aAttributeName, const TDesC& aAttributeValue);


	/**
	 * Removes the named attribute if present.
	 * @param aAttributeName Name of attribute to set
	 * @return Returns KErrNone if successful, KErrNotFound if the named attribute is not set.
	 */
	IMPORT_C virtual TInt RemoveAttribute(const TDesC& aAttributeName);

	/**
	 * Finds out whether or not the named attribute is set
	 * @param aAttributeName Name of attribute that is subject of the enquiry.
	 * @return true of the named attribute has a value set, false if not
	 */
	IMPORT_C virtual TBool IsAttributeSpecified(const TDesC& aAttributeName) const;


	/**
	 * This factory function creates a new element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLElement* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * Parses an end tag.  In fact, at this point the end tag must match
	 * the tag name of the start tag.  This is a member function unlike
	 * the ParseStartTagL factory function.
	 * @param aTagToParse Text of the end tag.
	 * @return Returns KErrNone if the end tag matches the start tag or KErrNotFound if there is a mismatch.
	 */
	virtual TInt ParseEndTag(const TDesC& aTagToParse);

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

	/**
	 * Check the children of this node for legality - must be defined based on DTD.
	 * This function checks that the list of child elements
	 * conforms to those allowed by the DTD.  In the generic
	 * CMDXMLElement class this always returns true as it has
	 * no basis for a meaningful check.
	 * As well as checking the list of direct children, it
	 * calls CheckChildren for each child element which is an
	 * element (it does not call this for child nodes which are
	 * not elements as they cannot have children).
	 * @return True if the node has legitimate children
	 */
	IMPORT_C virtual TBool CheckChildren();

protected: //construction
	/**
	 * Constructor
	 * @param aCanHaveChildren Flag to indicate if the node represents a node which is allowed children
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree - if NULL then assume this is the root
	 */
	CMDXMLElement( TBool aCanHaveChildren, CMDXMLDocument* aOwnerDocument );

protected:
	/**
	 * This function is used by derived class parse routines.  Once the derived class
	 * has made a basic element, this routine parses the attributes.
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
	 * @return Returns KErrNone if successful
	 * @exception can Leave due to OOM
	 */
	TInt ParseAttributesL( TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter);

	/**
	 * Check the immediate children of this element - i.e. the first level of children only
	 * The default implementation returns true - derived classes can override with
	 * DTD-specific checks.
	 * @returns True if immediate children are valid
	 */
	virtual TBool CheckImmediateChildren();

	/**
	 * Checks child element ownership based on a Finite State Machine
	 * @param aFirstChild - pointer to first child element
	 * @param aStateTrans - Array of state transition elements.
	 *        The elements must be ordered by tag name first and then starting state
	 *        as this routine uses the ordering to drive an efficient search.
	 * @param aStateCount - the number of state transitions in the array
	 * @returns true if the list of children matches the defined state machine
	 */
	static TBool CheckChildStates( CMDXMLNode* aFirstChild, const TXMLChildStateType aStateTrans[], TInt aStateCount );

public: // static functions used for finding, setting and deleting elements in the Attributes array held by child classes
	/**
	 * Find a string in an array and return the index
	 * @param aAttNameArray the array containing the descriptor
	 * @param aArrayCount the number of elements of the array - for overflow checking
	 * @param aAttName the string to search for
	 * @return returns the index of the string if found or KErrNotFound
	 */
	static TInt FindIndex(const TXMLDescAttType aAttNameArray[], const TInt aArrayCount, const TDesC& aAttName);

	/**
	 * Replaces an element in a descriptor array
	 * @param aAttributes the array containing the descriptor
	 * @param aAttCount the number of elements of the array - for overflow checking
	 * @param aAttIndex the array index to set
	 * @param aAttVal value to set
	 * @return returns KErrNone if successfully set or KErrArgument if aAttIndex is out of bounds
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C static TInt SetDescAttL(HBufC* aAttributes[], const TInt aAttCount, const TInt aAttIndex, const TDesC& aAttVal);
	
	/**
	 * Removes an element in a descriptor array
	 * @param aAttributes the array containing the descriptor
	 * @param aAttCount the number of elements of the array - for overflow checking
	 * @param aAttIndex the array index of the element to remove
	 */
	IMPORT_C static void RemoveDescAtt(HBufC* aAttributes[], const TInt aAttCount, const TInt aAttIndex);
};


#endif
