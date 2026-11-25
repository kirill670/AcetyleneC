// MDXMLSMILmeta.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILmeta.h
 * This file contains the declaration of the CMDXMLSMILmeta class.
 * This class represents a meta element and is specific to the SMIl 2.0 (not Basic) DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILMETA_H__
#define __MDXMLSMILMETA_H__

#include <e32base.h>


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILmeta : public CMDXMLElement
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILmeta
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILmeta* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILmeta
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILmeta* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLSMILmeta();

	/**
	 * This factory function creates a new meta element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILmeta* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an meta pointer if the node is of type meta, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILmeta* CastToSMILmeta( CMDXMLNode* aNode );

	// Generic attribute handling routines derived from the CMDXMLElement class.

	/**
	 * Returns the attribute value if it is set.
	 * @param aAttributeName Name of attribute to return
	 * @param aAttributeValue Value of attribute returned
	 * @return Returns KErrNone if successful, KErrNotFound if the named attribute 
	 * is not set or KErrNotSupported if the named attribute doesn't exist.
	 */
	IMPORT_C virtual TInt GetAttribute( const TDesC& aAttributeName, TPtrC& aAttributeValue ) const;

	/**
	 * Sets the attribute value.
	 * @param aAttributeName Name of attribute to set
	 * @param aAttributeValue Value of attribute
	 * @return Returns KErrNone if the attribute can be set or KErrNotSupported if not
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C virtual TInt SetAttributeL( const TDesC& aAttributeName, const TDesC& aAttributeValue );

	/**
	 * Removes the named attribute if present.
	 * @param aAttributeName Name of attribute to set
	 * @return Returns KErrNone if successful or KErrNotSupported if not
	 */
	IMPORT_C virtual TInt RemoveAttribute( const TDesC& aAttributeName );

	/**
	 * Finds out whether or not the named attribute is set
	 * @param aAttributeName Name of attribute that is subject of the enquiry.
	 * @return true if the attribute is set, false if not
	 */
	IMPORT_C virtual TBool IsAttributeSpecified( const TDesC& aAttributeName ) const;

	/**
	 * Outputs a start tag for the element which includes the
	 * tag name and all attribute values. 
	 * @param aComposer object to which the tag text is output.
	 * @return Returns KErrNone if successful or a file write error
	 * @exception can Leave due to OOM
	 */
	virtual TInt ComposeStartTagL(CMDXMLComposer& aComposer);

public:
	//Access functions for element attributes

	/**
	 * @return Returns the value of the Content attribute
	 */
	inline TPtrC AttContent() const {return iAttContent->Des();}

	/**
	 * @return Returns true if the Content attribute is specified
	 */
	inline TBool IsAttContentSpecified() const {return (iAttContent != NULL);}

	/**
	 * Sets the value of the Content attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C TInt SetAttContentL( const TDesC& aAttVal );

	/**
	 * Unsets the value of the Content attribute
	 */
	IMPORT_C void RemoveAttContent();

	/**
	 * @return Returns the value of the Name attribute
	 */
	inline TPtrC AttName() const {return iAttName->Des();}

	/**
	 * @return Returns true if the Name attribute is specified
	 */
	inline TBool IsAttNameSpecified() const {return (iAttName != NULL);}

	/**
	 * Sets the value of the Name attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C TInt SetAttNameL( const TDesC& aAttVal );

	/**
	 * Unsets the value of the Name attribute
	 */
	IMPORT_C void RemoveAttName();

private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILmeta( CMDXMLDocument* aOwnerDocument );

	private:
	//Member variables for element attributes
	HBufC* iAttContent;	///< Member variable for the Content attribute
	HBufC* iAttName;	///< Member variable for the Name attribute
	};

#endif

// End of File