// MDXMLSMILa.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILa.h
 * This file contains the declaration of the CMDXMLSMILa class.
 * This class represents an a element and is specific to the SMIl 2.0 Basic DTD.
 * Element attributes are represented as member variables, each with their own
 * access functions.  No generic attributes are stored.
 */

#ifndef __MDXMLSMILA_H__
#define __MDXMLSMILA_H__

#include <e32base.h>


// Array indices for descriptor attributes.
// These must start at zero and must be in alphabetical order of attribute
// name
const TInt KSMILaAttAccessKey			= 0;	///< Index for the AccessKey attribute
const TInt KSMILaAttBegin				= 1;	///< Index for the Begin attribute
const TInt KSMILaAttClass				= 2;	///< Index for the class attribute
const TInt KSMILaAttDestinationLevel	= 3;	///< Index for the DestinationLevel attribute
const TInt KSMILaAttDur					= 4;	///< Index for the Dur attribute
const TInt KSMILaAttEnd					= 5;	///< Index for the End attribute
const TInt KSMILaAttHRef				= 6;	///< Index for the HRef attribute
const TInt KSMILaAttId					= 7;	///< Index for the id attribute
const TInt KSMILaAttMax					= 8;	///< Index for the Max attribute
const TInt KSMILaAttMin					= 9;	///< Index for the Min attribute
const TInt KSMILaAttRepeatCount			= 10;	///< Index for the RepeatCount attribute
const TInt KSMILaAttRepeatDur			= 11;	///< Index for the RepeatDur attribute
const TInt KSMILaAttSourceLevel			= 12;	///< Index for the SourceLevel attribute
const TInt KSMILaAttTabIndex			= 13;	///< Index for the TabIndex attribute
const TInt KSMILaAttTarget				= 14;	///< Index for the Target attribute
const TInt KSMILaAttTitle				= 15;	///< Index for the title attribute
const TInt KSMILaAttXMLLang				= 16;	///< Index for the xml_lang attribute
const TInt KSMILaAttNameCount = KSMILaAttXMLLang+1;


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILa : public CMDXMLSMILBasicElt
{
public:
	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILa
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILa* NewLC( CMDXMLDocument* aOwnerDocument );

	/**
	 * Two phase constructor
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @returns Created CMDXMLSMILa
	 * @exception can Leave due to OOM
	 */
	IMPORT_C static CMDXMLSMILa* NewL( CMDXMLDocument* aOwnerDocument );

	IMPORT_C virtual ~CMDXMLSMILa();

	/**
	 * This factory function creates a new img element object 
	 * using the tag text passed in.
	 * It parses attribute definitions and stores them.
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 * @param aTagToParse Text of the tag to parse
	 * @param aEntityConverter Entity converter to normalise attribute text
 	 * @param aErrorCode Parsing error code
	 * @return Returns a pointer to the newly created element
	 * @exception can Leave due to OOM
	 */
	static CMDXMLSMILa* ParseStartTagL(CMDXMLDocument* aOwnerDocument, TDes& aTagToParse, CMDXMLEntityConverter* aEntityConverter, TInt& aErrorCode);

	/**
	 * @param aNode pointer to cast from
	 * @return Returns an a pointer if the node is of type a, otherwise returns NULL
	 */
	IMPORT_C static CMDXMLSMILa* CastToSMILa( CMDXMLNode* aNode );

public:
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
	CMDXMLSMILa( CMDXMLDocument* aOwnerDocument );

public:
	//Access functions for element attributes
	/**
	 * @return Returns the value of the AccessKey attribute
	 */
	inline TPtrC AttAccessKey() const {return iDescAtts[KSMILaAttAccessKey]->Des();}

	/**
	 * @return Returns true if the AccessKey attribute is specified
	 */
	inline TBool IsAttAccessKeySpecified() const {return (iDescAtts[KSMILaAttAccessKey] != NULL);}

	/**
	 * Sets the value of the AccessKey attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAccessKeyL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttAccessKey, aAttVal); }

	/**
	 * Unsets the value of the AccessKey attribute
	 */
	inline void RemoveAttAccessKey(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttAccessKey);}

	/**
	 * @return Returns the value of the Actuate attribute
	 */
	inline TDOMAttActuateType AttActuate() const {return iAttActuate;}

	/**
	 * @return Returns true if the Actuate attribute is specified
	 */
	inline TBool IsAttActuateSpecified() const {return (iAttActuate != EAttActuateUndefined);}

	/**
	 * Sets the value of the Actuate attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttActuate( TDOMAttActuateType aAttVal ){iAttActuate = aAttVal;return KErrNone;}

	/**
	 * Unsets the value of the Actuate attribute
	 */
	inline void RemoveAttActuate() {iAttActuate = EAttActuateUndefined;}

	/**
	 * @return Returns the value of the Begin attribute
	 */
	inline TPtrC AttBegin() const {return iDescAtts[KSMILaAttBegin]->Des();}

	/**
	 * @return Returns true if the Begin attribute is specified
	 */
	inline TBool IsAttBeginSpecified() const {return (iDescAtts[KSMILaAttBegin] != NULL);}

	/**
	 * Sets the value of the Begin attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBeginL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttBegin, aAttVal);}

	/**
	 * Unsets the value of the Begin attribute
	 */
	inline void RemoveAttBegin(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttBegin);}

	/**
	 * @return Returns the value of the Class attribute
	 */
	inline TPtrC AttClass() const {return iDescAtts[KSMILaAttClass]->Des();}

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	inline TBool IsAttClassSpecified() const {return (iDescAtts[KSMILaAttClass] != NULL);}

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClassL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttClass, aAttVal);}

	/**
	 * Unsets the value of the Class attribute
	 */
	inline void RemoveAttClass(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttClass);}

	/**
	 * @return Returns the value of the DestinationLevel attribute
	 */
	inline TPtrC AttDestinationLevel() const {return iDescAtts[KSMILaAttDestinationLevel]->Des();}

	/**
	 * @return Returns true if the DestinationLevel attribute is specified
	 */
	inline TBool IsAttDestinationLevelSpecified() const {return (iDescAtts[KSMILaAttDestinationLevel] != NULL);}

	/**
	 * Sets the value of the DestinationLevel attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttDestinationLevelL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttDestinationLevel, aAttVal);}

	/**
	 * Unsets the value of the DestinationLevel attribute
	 */
	inline void RemoveAttDestinationLevel(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttDestinationLevel);}

	/**
	 * @return Returns the value of the DestinationPlaystate attribute
	 */
	inline TDOMAttDestinationPlaystateType AttDestinationPlaystate() const {return iAttDestinationPlaystate;}

	/**
	 * @return Returns true if the DestinationPlaystate attribute is specified
	 */
	inline TBool IsAttDestinationPlaystateSpecified() const {return (iAttDestinationPlaystate != EAttDestinationPlaystateUndefined);}

	/**
	 * Sets the value of the DestinationPlaystate attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttDestinationPlaystate( TDOMAttDestinationPlaystateType aAttVal ){iAttDestinationPlaystate = aAttVal;return KErrNone;}

	/**
	 * Unsets the value of the DestinationPlaystate attribute
	 */
	inline void RemoveAttDestinationPlaystate() {iAttDestinationPlaystate = EAttDestinationPlaystateUndefined;}

	/**
	 * @return Returns the value of the Dur attribute
	 */
	inline TPtrC AttDur() const {return iDescAtts[KSMILaAttDur]->Des();}

	/**
	 * @return Returns true if the Dur attribute is specified
	 */
	inline TBool IsAttDurSpecified() const {return (iDescAtts[KSMILaAttDur] != NULL);}

	/**
	 * Sets the value of the Dur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttDur, aAttVal);}

	/**
	 * Unsets the value of the Dur attribute
	 */
	inline void RemoveAttDur(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttDur);}

	/**
	 * @return Returns the value of the End attribute
	 */
	inline TPtrC AttEnd() const {return iDescAtts[KSMILaAttEnd]->Des();}

	/**
	 * @return Returns true if the End attribute is specified
	 */
	inline TBool IsAttEndSpecified() const {return (iDescAtts[KSMILaAttEnd] != NULL);}

	/**
	 * Sets the value of the End attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttEndL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttEnd, aAttVal);}

	/**
	 * Unsets the value of the End attribute
	 */
	inline void RemoveAttEnd(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttEnd);}

	/**
	 * @return Returns the value of the External attribute
	 */
	inline TDOMAttExternalType AttExternal() const {return iAttExternal;}

	/**
	 * @return Returns true if the External attribute is specified
	 */
	inline TBool IsAttExternalSpecified() const {return (iAttExternal != EAttExternalUndefined);}

	/**
	 * Sets the value of the External attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttExternal( TDOMAttExternalType aAttVal ){iAttExternal = aAttVal;	return KErrNone;}

	/**
	 * Unsets the value of the External attribute
	 */
	inline void RemoveAttExternal() {iAttExternal = EAttExternalUndefined;}

	/**
	 * @return Returns the value of the Fill attribute
	 */
	inline TDOMAttFillType AttFill() const {return iAttFill;}

	/**
	 * @return Returns true if the Fill attribute is specified
	 */
	inline TBool IsAttFillSpecified() const {return (iAttFill != EAttFillUndefined);}

	/**
	 * Sets the value of the Fill attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttFill( TDOMAttFillType aAttVal ){iAttFill = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the Fill attribute
	 */
	inline void RemoveAttFill() {iAttFill = EAttFillUndefined;}

	/**
	 * @return Returns the value of the HRef attribute
	 */
	inline TPtrC AttHRef() const {return iDescAtts[KSMILaAttHRef]->Des();}

	/**
	 * @return Returns true if the HRef attribute is specified
	 */
	inline TBool IsAttHRefSpecified() const {return (iDescAtts[KSMILaAttHRef] != NULL);}

	/**
	 * Sets the value of the HRef attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttHRefL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttHRef, aAttVal);}

	/**
	 * Unsets the value of the HRef attribute
	 */
	inline void RemoveAttHRef(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttHRef);}

	/**
	 * @return Returns the value of the Id attribute
	 */
	inline TPtrC AttId() const {return iDescAtts[KSMILaAttId]->Des();}

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	inline TBool IsAttIdSpecified() const {return (iDescAtts[KSMILaAttId] != NULL);}

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttIdL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttId, aAttVal);}

	/**
	 * Unsets the value of the Id attribute
	 */
	inline void RemoveAttId(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttId);}

	/**
	 * @return Returns the value of the Max attribute
	 */
	inline TPtrC AttMax() const {return iDescAtts[KSMILaAttMax]->Des();}

	/**
	 * @return Returns true if the Max attribute is specified
	 */
	inline TBool IsAttMaxSpecified() const {return (iDescAtts[KSMILaAttMax] != NULL);}

	/**
	 * Sets the value of the Max attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMaxL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttMax, aAttVal);}

	/**
	 * Unsets the value of the Max attribute
	 */
	inline void RemoveAttMax(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttMax);}

	/**
	 * @return Returns the value of the Min attribute
	 */
	inline TPtrC AttMin() const {return iDescAtts[KSMILaAttMin]->Des();}

	/**
	 * @return Returns true if the Min attribute is specified
	 */
	inline TBool IsAttMinSpecified() const {return (iDescAtts[KSMILaAttMin] != NULL);}

	/**
	 * Sets the value of the Min attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMinL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttMin, aAttVal);}

	/**
	 * Unsets the value of the Min attribute
	 */
	inline void RemoveAttMin(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttMin);}

	/**
	 * @return Returns the value of the RepeatCount attribute
	 */
	inline TPtrC AttRepeatCount() const {return iDescAtts[KSMILaAttRepeatCount]->Des();}

	/**
	 * @return Returns true if the RepeatCount attribute is specified
	 */
	inline TBool IsAttRepeatCountSpecified() const {return (iDescAtts[KSMILaAttRepeatCount] != NULL);}

	/**
	 * Sets the value of the RepeatCount attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatCountL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttRepeatCount, aAttVal);}

	/**
	 * Unsets the value of the RepeatCount attribute
	 */
	inline void RemoveAttRepeatCount(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttRepeatCount);}

	/**
	 * @return Returns the value of the RepeatDur attribute
	 */
	inline TPtrC AttRepeatDur() const {return iDescAtts[KSMILaAttRepeatDur]->Des();}

	/**
	 * @return Returns true if the RepeatDur attribute is specified
	 */
	inline TBool IsAttRepeatDurSpecified() const {return (iDescAtts[KSMILaAttRepeatDur] != NULL);}

	/**
	 * Sets the value of the RepeatDur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttRepeatDur, aAttVal);}

	/**
	 * Unsets the value of the RepeatDur attribute
	 */
	inline void RemoveAttRepeatDur(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttRepeatDur);}

	/**
	 * @return Returns the value of the Show attribute
	 */
	inline TDOMAttShowType AttShow() const {return iAttShow;}

	/**
	 * @return Returns true if the Show attribute is specified
	 */
	inline TBool IsAttShowSpecified() const {return (iAttShow != EAttShowUndefined);}

	/**
	 * Sets the value of the Show attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttShow( TDOMAttShowType aAttVal ){iAttShow = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the Show attribute
	 */
	inline void RemoveAttShow() {iAttShow = EAttShowUndefined;}

	/**
	 * @return Returns the value of the SourceLevel attribute
	 */
	inline TPtrC AttSourceLevel() const {return iDescAtts[KSMILaAttSourceLevel]->Des();}

	/**
	 * @return Returns true if the SourceLevel attribute is specified
	 */
	inline TBool IsAttSourceLevelSpecified() const {return (iDescAtts[KSMILaAttSourceLevel] != NULL);}

	/**
	 * Sets the value of the SourceLevel attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSourceLevelL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttSourceLevel, aAttVal);}

	/**
	 * Unsets the value of the SourceLevel attribute
	 */
	inline void RemoveAttSourceLevel(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttSourceLevel);}

	/**
	 * @return Returns the value of the SourcePlaystate attribute
	 */
	inline TDOMAttSourcePlaystateType AttSourcePlaystate() const {return iAttSourcePlaystate;}

	/**
	 * @return Returns true if the SourcePlaystate attribute is specified
	 */
	inline TBool IsAttSourcePlaystateSpecified() const {return (iAttSourcePlaystate != EAttSourcePlaystateUndefined);}

	/**
	 * Sets the value of the SourcePlaystate attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSourcePlaystate( TDOMAttSourcePlaystateType aAttVal ){iAttSourcePlaystate = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the SourcePlaystate attribute
	 */
	inline void RemoveAttSourcePlaystate() {iAttSourcePlaystate = EAttSourcePlaystateUndefined;}

	/**
	 * @return Returns the value of the TabIndex attribute
	 */
	inline TPtrC AttTabIndex() const {return iDescAtts[KSMILaAttTabIndex]->Des();}

	/**
	 * @return Returns true if the TabIndex attribute is specified
	 */
	inline TBool IsAttTabIndexSpecified() const {return (iDescAtts[KSMILaAttTabIndex] != NULL);}

	/**
	 * Sets the value of the TabIndex attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTabIndexL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttTabIndex, aAttVal);}

	/**
	 * Unsets the value of the TabIndex attribute
	 */
	inline void RemoveAttTabIndex(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttTabIndex);}

	/**
	 * @return Returns the value of the Target attribute
	 */
	inline TPtrC AttTarget() const {return iDescAtts[KSMILaAttTarget]->Des();}

	/**
	 * @return Returns true if the Target attribute is specified
	 */
	inline TBool IsAttTargetSpecified() const {return (iDescAtts[KSMILaAttTarget] != NULL);}

	/**
	 * Sets the value of the Target attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTargetL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttTarget, aAttVal);}

	/**
	 * Unsets the value of the Target attribute
	 */
	inline void RemoveAttTarget(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttTarget);}

	/**
	 * @return Returns the value of the Title attribute
	 */
	inline TPtrC AttTitle() const {return iDescAtts[KSMILaAttTitle]->Des();}

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	inline TBool IsAttTitleSpecified() const {return (iDescAtts[KSMILaAttTitle] != NULL);}

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTitleL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttTitle, aAttVal);}

	/**
	 * Unsets the value of the Title attribute
	 */
	inline void RemoveAttTitle(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttTitle);}

	/**
	 * @return Returns the value of the XMLLang attribute
	 */
	inline TPtrC AttXMLLang() const {return iDescAtts[KSMILaAttXMLLang]->Des();}

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	inline TBool IsAttXMLLangSpecified() const {return (iDescAtts[KSMILaAttXMLLang] != NULL);}

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttXMLLangL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILaAttNameCount, KSMILaAttXMLLang, aAttVal);}

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	inline void RemoveAttXMLLang(){RemoveDescAtt(iDescAtts, KSMILaAttNameCount, KSMILaAttXMLLang);}

protected:
	/**
	 * Check the immediate children of this element - i.e. the first level of children only
	 * The default implementation returns true - derived classes can override with
	 * DTD-specific checks.
	 * @returns True if immediate children are valid
	 */
	virtual TBool CheckImmediateChildren();

protected:
	// All descriptor-based attributes are stored in an array.
	// The array is fixed-size for the class and is indexed based on 
	// alphabetical order of attribute name
	HBufC *iDescAtts[KSMILaAttNameCount];				///< Array of descriptor attributes

	// These are the Enum-based attributes which are handled in a hard-wired way
	TDOMAttActuateType iAttActuate;		///< Member variable for the Actuate attribute
	TDOMAttDestinationPlaystateType iAttDestinationPlaystate;		///< Member variable for the DestinationPlaystate attribute
	TDOMAttExternalType iAttExternal;	///< Member variable for the External attribute
	TDOMAttFillType iAttFill;			///< Member variable for the Fill attribute
	TDOMAttShowType iAttShow;			///< Member variable for the Show attribute
	TDOMAttSourcePlaystateType iAttSourcePlaystate;	///< Member variable for the SourcePlaystate attribute

};

#endif

// End of File
