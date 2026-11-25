// MDXMLSMILregion.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILregion.h
 * This file contains the declaration of the CMDXMLSMILregion class.
 * This class represents a region element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILREGION_H__
#define __MDXMLSMILREGION_H__

#include <e32base.h>
#include "MDXMLSMILrootlayout.h"


// Array indices for descriptor attributes.
// These must start at zero and must be in alphabetical order of attribute
// name
const TInt KSMILregionAttBackgroundColor	= 0;
const TInt KSMILregionAttBackground_color	= 1;
const TInt KSMILregionAttBottom				= 2;
const TInt KSMILregionAttClass				= 3;
const TInt KSMILregionAttHeight				= 4;
const TInt KSMILregionAttId					= 5;
const TInt KSMILregionAttLeft				= 6;
const TInt KSMILregionAttRight				= 7;
const TInt KSMILregionAttTitle				= 8;
const TInt KSMILregionAttTop				= 9;
const TInt KSMILregionAttWidth				= 10;
const TInt KSMILregionAttXMLLang			= 11;
const TInt KSMILregionAttZIndex				= 12;
const TInt KSMILregionAttNameCount	= KSMILregionAttZIndex+1;


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILregion : public CMDXMLSMILBasicElt
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILregion
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILregion* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILregion
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILregion* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLSMILregion();

	/**
	 * This factory function creates a new region element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILregion* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns a region pointer if the node is of type region, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILregion* CastToSMILregion( CMDXMLNode* aNode );

	/**
	 * @return Returns a pointer to the next region sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILregion* NextregionSibling();

	/**
	 * @return Returns a pointer to the previous region sibling if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILregion* PreviousregionSibling();

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


private:
	/**
	 * Constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILregion( CMDXMLDocument* aOwnerDocument );

public:
	//Access functions for element attributes
	/**
	 * @return Returns the value of the BackgroundColor attribute
	 */
	inline TPtrC AttBackgroundColor() const {return iDescAtts[KSMILregionAttBackgroundColor]->Des();}

	/**
	 * @return Returns true if the BackgroundColor attribute is specified
	 */
	inline TBool IsAttBackgroundColorSpecified() const {return (iDescAtts[KSMILregionAttBackgroundColor] != NULL);}

	/**
	 * Sets the value of the BackgroundColor attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBackgroundColorL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttBackgroundColor, aAttVal);}

	/**
	 * Unsets the value of the BackgroundColor attribute
	 */
	inline void RemoveAttBackgroundColor(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttBackgroundColor);}

	/**
	 * @return Returns the value of the Background_color attribute
	 */
	inline TPtrC AttBackground_color() const {return iDescAtts[KSMILregionAttBackground_color]->Des();}

	/**
	 * @return Returns true if the Background_color attribute is specified
	 */
	inline TBool IsAttBackground_colorSpecified() const {return (iDescAtts[KSMILregionAttBackground_color] != NULL);}

	/**
	 * Sets the value of the Background_color attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBackground_colorL( const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttBackground_color, aAttVal);}

	/**
	 * Unsets the value of the Background_color attribute
	 */
	inline void RemoveAttBackground_color(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttBackground_color);}

	/**
	 * @return Returns the value of the Class attribute
	 */
	inline TPtrC AttClass() const {return iDescAtts[KSMILregionAttClass]->Des();}

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	inline TBool IsAttClassSpecified() const {return (iDescAtts[KSMILregionAttClass] != NULL);}

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClassL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttClass, aAttVal);}

	/**
	 * Unsets the value of the Class attribute
	 */
	inline void RemoveAttClass(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttClass);}

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
	inline TPtrC AttHeight() const {return iDescAtts[KSMILregionAttHeight]->Des();}

	/**
	 * @return Returns true if the Height attribute is specified
	 */
	inline TBool IsAttHeightSpecified() const {return (iDescAtts[KSMILregionAttHeight] != NULL);}

	/**
	 * Sets the value of the Height attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttHeightL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttHeight, aAttVal);}

	/**
	 * Unsets the value of the Height attribute
	 */
	inline void RemoveAttHeight(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttHeight);}

	/**
	 * @return Returns the value of the Id attribute
	 */
	inline TPtrC AttId() const {return iDescAtts[KSMILregionAttId]->Des();}

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	inline TBool IsAttIdSpecified() const {return (iDescAtts[KSMILregionAttId] != NULL);}

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttIdL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttId, aAttVal);}

	/**
	 * Unsets the value of the Id attribute
	 */
	inline void RemoveAttId(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttId);}

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
	inline TPtrC AttTitle() const {return iDescAtts[KSMILregionAttTitle]->Des();}

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	inline TBool IsAttTitleSpecified() const {return (iDescAtts[KSMILregionAttTitle] != NULL);}

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTitleL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttTitle, aAttVal);}

	/**
	 * Unsets the value of the Title attribute
	 */
	inline void RemoveAttTitle(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttTitle);}

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
	inline TPtrC AttWidth() const {return iDescAtts[KSMILregionAttWidth]->Des();}

	/**
	 * @return Returns true if the Width attribute is specified
	 */
	inline TBool IsAttWidthSpecified() const {return (iDescAtts[KSMILregionAttWidth] != NULL);}

	/**
	 * Sets the value of the Width attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttWidthL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttWidth, aAttVal);}

	/**
	 * Unsets the value of the Width attribute
	 */
	inline void RemoveAttWidth(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttWidth);}

	/**
	 * @return Returns the value of the XMLLang attribute
	 */
	inline TPtrC AttXMLLang() const {return iDescAtts[KSMILregionAttXMLLang]->Des();}

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	inline TBool IsAttXMLLangSpecified() const {return (iDescAtts[KSMILregionAttXMLLang] != NULL);}

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttXMLLangL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttXMLLang, aAttVal);}

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	inline void RemoveAttXMLLang(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttXMLLang);}

	/**
	 * @return Returns the value of the Bottom attribute
	 */
	inline TPtrC AttBottom() const {return iDescAtts[KSMILregionAttBottom]->Des();}

	/**
	 * @return Returns true if the Bottom attribute is specified
	 */
	inline TBool IsAttBottomSpecified() const {return (iDescAtts[KSMILregionAttBottom] != NULL);}

	/**
	 * Sets the value of the Bottom attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBottomL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttBottom, aAttVal);}

	/**
	 * Unsets the value of the Bottom attribute
	 */
	inline void RemoveAttBottom(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttBottom);}

	/**
	 * @return Returns the value of the Fit attribute
	 */
	inline TDOMAttFitType AttFit() const {return iAttFit;}

	/**
	 * @return Returns true if the Fit attribute is specified
	 */
	inline TBool IsAttFitSpecified() const {return (iAttFit != EAttFitUndefined);}

	/**
	 * Sets the value of the Fit attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttFit( TDOMAttFitType aAttVal ){iAttFit = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the Fit attribute
	 */
	inline void RemoveAttFit() {iAttFit = EAttFitUndefined;}

	/**
	 * @return Returns the value of the Left attribute
	 */
	inline TPtrC AttLeft() const {return iDescAtts[KSMILregionAttLeft]->Des();}

	/**
	 * @return Returns true if the Left attribute is specified
	 */
	inline TBool IsAttLeftSpecified() const {return (iDescAtts[KSMILregionAttLeft] != NULL);}

	/**
	 * Sets the value of the Left attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttLeftL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttLeft, aAttVal);}

	/**
	 * Unsets the value of the Left attribute
	 */
	inline void RemoveAttLeft(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttLeft);}

	/**
	 * @return Returns the value of the Right attribute
	 */
	inline TPtrC AttRight() const {return iDescAtts[KSMILregionAttRight]->Des();}

	/**
	 * @return Returns true if the Right attribute is specified
	 */
	inline TBool IsAttRightSpecified() const {return (iDescAtts[KSMILregionAttRight] != NULL);}

	/**
	 * Sets the value of the Right attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRightL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttRight, aAttVal);}

	/**
	 * Unsets the value of the Right attribute
	 */
	inline void RemoveAttRight(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttRight);}

	/**
	 * @return Returns the value of the ShowBackground attribute
	 */
	inline TDOMAttShowBackgroundType AttShowBackground() const {return iAttShowBackground;}

	/**
	 * @return Returns true if the ShowBackground attribute is specified
	 */
	inline TBool IsAttShowBackgroundSpecified() const {return (iAttShowBackground != EAttShowBackgroundUndefined);}

	/**
	 * Sets the value of the ShowBackground attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttShowBackground( TDOMAttShowBackgroundType aAttVal ){iAttShowBackground = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the ShowBackground attribute
	 */
	inline void RemoveAttShowBackground() {iAttShowBackground = EAttShowBackgroundUndefined;}

	/**
	 * @return Returns the value of the Top attribute
	 */
	inline TPtrC AttTop() const {return iDescAtts[KSMILregionAttTop]->Des();}

	/**
	 * @return Returns true if the Top attribute is specified
	 */
	inline TBool IsAttTopSpecified() const {return (iDescAtts[KSMILregionAttTop] != NULL);}

	/**
	 * Sets the value of the Top attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTopL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttTop, aAttVal);}

	/**
	 * Unsets the value of the Top attribute
	 */
	inline void RemoveAttTop(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttTop);}

	/**
	 * @return Returns the value of the ZIindex attribute
	 */
	inline TPtrC AttZIndex() const {return iDescAtts[KSMILregionAttZIndex]->Des();}

	/**
	 * @return Returns true if the ZIindex attribute is specified
	 */
	inline TBool IsAttZIndexSpecified() const {return (iDescAtts[KSMILregionAttZIndex] != NULL);}

	/**
	 * Sets the value of the ZIindex attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttZIndexL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILregionAttNameCount, KSMILregionAttZIndex, aAttVal);}

	/**
	 * Unsets the value of the ZIindex attribute
	 */
	inline void RemoveAttZIndex(){RemoveDescAtt(iDescAtts, KSMILregionAttNameCount, KSMILregionAttZIndex);}

private:
	// All descriptor-based attributes are stored in an array.
	// The array is fixed-size for the class and is indexed based on 
	// alphabetical order of attribute name
	HBufC *iDescAtts[KSMILregionAttNameCount];				///< Array of descriptor attributes

	//Member variables for element attributes
	// These are the Enum-based attributes which are handled in a hard-wired way
	TDOMAttCloseType iAttClose;				///< Member variable for the Close attribute
	TDOMAttFitType iAttFit;							///< Member variable for the Fit attribute
	TDOMAttOpenType iAttOpen;				///< Member variable for the Open attribute
	TDOMAttShowBackgroundType iAttShowBackground;	///< Member variable for the ShowBackground attribute
	TDOMAttSkipContentType iAttSkipContent;	///< Member variable for the SkipContent attribute
	};

#endif

// End of File