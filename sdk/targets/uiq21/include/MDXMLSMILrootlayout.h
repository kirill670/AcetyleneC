// MDXMLSMILroot_layout.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILroot_layout.h
 * This file contains the declaration of the CMDXMLSMILroot_layout class.
 * This class represents a root-layout element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILROOTLAYOUT_H__
#define __MDXMLSMILROOTLAYOUT_H__

#include <e32base.h>


// Array indices for descriptor attributes.
// These must start at zero and must be in alphabetical order of attribute
// name
const TInt KSMILrootlayoutAttBackgroundColor	= 0;
const TInt KSMILrootlayoutAttBackground_color	= 1;
const TInt KSMILrootlayoutAttClass			= 2;
const TInt KSMILrootlayoutAttHeight			= 3;
const TInt KSMILrootlayoutAttId				= 4;
const TInt KSMILrootlayoutAttTitle			= 5;
const TInt KSMILrootlayoutAttWidth			= 6;
const TInt KSMILrootlayoutAttXMLLang			= 7;
const TInt KSMILrootlayoutAttNameCount	= KSMILrootlayoutAttXMLLang+1;


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILroot_layout : public CMDXMLSMILBasicElt
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILroot_layout
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILroot_layout* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILroot_layout
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILroot_layout* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLSMILroot_layout();

	/**
	 * This factory function creates a new root-layout element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILroot_layout* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an root_layout pointer if the node is of type root_layout, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILroot_layout* CastToSMILroot_layout( CMDXMLNode* aNode );

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


protected:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILroot_layout( CMDXMLDocument* aOwnerDocument );

public:
	//Access functions for element attributes
	/**
	 * @return Returns the value of the BackgroundColor attribute
	 */
	inline TPtrC AttBackgroundColor() const {return iDescAtts[KSMILrootlayoutAttBackgroundColor]->Des();}

	/**
	 * @return Returns true if the BackgroundColor attribute is specified
	 */
	inline TBool IsAttBackgroundColorSpecified() const {return (iDescAtts[KSMILrootlayoutAttBackgroundColor] != NULL);}

	/**
	 * Sets the value of the BackgroundColor attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBackgroundColorL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttBackgroundColor, aAttVal);}

	/**
	 * Unsets the value of the BackgroundColor attribute
	 */
	inline void RemoveAttBackgroundColor(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttBackgroundColor);}

	/**
	 * @return Returns the value of the Background_color attribute
	 */
	inline TPtrC AttBackground_color() const {return iDescAtts[KSMILrootlayoutAttBackground_color]->Des();}

	/**
	 * @return Returns true if the Background_color attribute is specified
	 */
	inline TBool IsAttBackground_colorSpecified() const {return (iDescAtts[KSMILrootlayoutAttBackground_color] != NULL);}

	/**
	 * Sets the value of the Background_color attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBackground_colorL( const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttBackground_color, aAttVal);}

	/**
	 * Unsets the value of the Background_color attribute
	 */
	inline void RemoveAttBackground_color(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttBackground_color);}

	/**
	 * @return Returns the value of the Class attribute
	 */
	inline TPtrC AttClass() const {return iDescAtts[KSMILrootlayoutAttClass]->Des();}

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	inline TBool IsAttClassSpecified() const {return (iDescAtts[KSMILrootlayoutAttClass] != NULL);}

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClassL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttClass, aAttVal);}

	/**
	 * Unsets the value of the Class attribute
	 */
	inline void RemoveAttClass(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttClass);}

	/**
	 * @return Returns the value of the Close attribute
	 */
	inline TDOMAttCloseType AttClose() const {return iAttClose;}

	/**
	 * @return Returns true if the Close attribute is specified
	 */
	inline TBool IsAttCloseSpecified() const {return (iAttClose != EAttCloseUndefined);}

	/**
	 * Sets the value of the Close attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttClose( TDOMAttCloseType aAttVal ){iAttClose = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the Close attribute
	 */
	inline void RemoveAttClose() {iAttClose = EAttCloseUndefined;}

	/**
	 * @return Returns the value of the Height attribute
	 */
	inline TPtrC AttHeight() const {return iDescAtts[KSMILrootlayoutAttHeight]->Des();}

	/**
	 * @return Returns true if the Height attribute is specified
	 */
	inline TBool IsAttHeightSpecified() const {return (iDescAtts[KSMILrootlayoutAttHeight] != NULL);}

	/**
	 * Sets the value of the Height attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttHeightL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttHeight, aAttVal);}

	/**
	 * Unsets the value of the Height attribute
	 */
	inline void RemoveAttHeight(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttHeight);}

	/**
	 * @return Returns the value of the Id attribute
	 */
	inline TPtrC AttId() const {return iDescAtts[KSMILrootlayoutAttId]->Des();}

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	inline TBool IsAttIdSpecified() const {return (iDescAtts[KSMILrootlayoutAttId] != NULL);}

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttIdL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttId, aAttVal);}

	/**
	 * Unsets the value of the Id attribute
	 */
	inline void RemoveAttId(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttId);}

	/**
	 * @return Returns the value of the Open attribute
	 */
	inline TDOMAttOpenType AttOpen() const {return iAttOpen;}

	/**
	 * @return Returns true if the Open attribute is specified
	 */
	inline TBool IsAttOpenSpecified() const {return (iAttOpen != EAttOpenUndefined);}

	/**
	 * Sets the value of the Open attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttOpen( TDOMAttOpenType aAttVal ) {iAttOpen = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the Open attribute
	 */
	inline void RemoveAttOpen() {iAttOpen = EAttOpenUndefined;}

	/**
	 * @return Returns the value of the Title attribute
	 */
	inline TPtrC AttTitle() const {return iDescAtts[KSMILrootlayoutAttTitle]->Des();}

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	inline TBool IsAttTitleSpecified() const {return (iDescAtts[KSMILrootlayoutAttTitle] != NULL);}

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTitleL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttTitle, aAttVal);}

	/**
	 * Unsets the value of the Title attribute
	 */
	inline void RemoveAttTitle(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttTitle);}

	/**
	 * @return Returns the value of the SkipContent attribute
	 */
	inline TDOMAttSkipContentType AttSkipContent() const {return iAttSkipContent;}

	/**
	 * @return Returns true if the SkipContent attribute is specified
	 */
	inline TBool IsAttSkipContentSpecified() const {return (iAttSkipContent != EAttSkipContentUndefined);}

	/**
	 * Sets the value of the SkipContent attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSkipContent( TDOMAttSkipContentType aAttVal ) {iAttSkipContent = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the SkipContent attribute
	 */
	inline void RemoveAttSkipContent() {iAttSkipContent = EAttSkipContentUndefined;}

	/**
	 * @return Returns the value of the Width attribute
	 */
	inline TPtrC AttWidth() const {return iDescAtts[KSMILrootlayoutAttWidth]->Des();}

	/**
	 * @return Returns true if the Width attribute is specified
	 */
	inline TBool IsAttWidthSpecified() const {return (iDescAtts[KSMILrootlayoutAttWidth] != NULL);}

	/**
	 * Sets the value of the Width attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttWidthL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttWidth, aAttVal);}

	/**
	 * Unsets the value of the Width attribute
	 */
	inline void RemoveAttWidth(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttWidth);}

	/**
	 * @return Returns the value of the XMLLang attribute
	 */
	inline TPtrC AttXMLLang() const {return iDescAtts[KSMILrootlayoutAttXMLLang]->Des();}

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	inline TBool IsAttXMLLangSpecified() const {return (iDescAtts[KSMILrootlayoutAttXMLLang] != NULL);}

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttXMLLangL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttXMLLang, aAttVal);}

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	inline void RemoveAttXMLLang(){RemoveDescAtt(iDescAtts, KSMILrootlayoutAttNameCount, KSMILrootlayoutAttXMLLang);}

protected:
	// All descriptor-based attributes are stored in an array.
	// The array is fixed-size for the class and is indexed based on 
	// alphabetical order of attribute name
	HBufC *iDescAtts[KSMILrootlayoutAttNameCount];				///< Array of descriptor attributes

	//Member variables for element attributes
	// These are the Enum-based attributes which are handled in a hard-wired way
	TDOMAttCloseType iAttClose;				///< Member variable for the Close attribute
	TDOMAttOpenType iAttOpen;				///< Member variable for the Open attribute
	TDOMAttSkipContentType iAttSkipContent;	///< Member variable for the SkipContent attribute
	};

#endif

// End of File