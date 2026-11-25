// MDXMLSMILAnchorBase.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILAnchorBase.h
 * This file contains the declaration of a base anchor class to be used
 * by derived classes for the specific anchor elements
 */

#ifndef __MDXMLSMILANCHORBASE_H__
#define __MDXMLSMILANCHORBASE_H__

#include <e32base.h>


// Array indices for descriptor attributes.
// These must start at zero and must be in alphabetical order of attribute
// name
const TInt KSMILanchorbaseAttAccessKey			= 0;
const TInt KSMILanchorbaseAttAlt				= 1;
const TInt KSMILanchorbaseAttBegin				= 2;
const TInt KSMILanchorbaseAttClass				= 3;
const TInt KSMILanchorbaseAttCoords				= 4;
const TInt KSMILanchorbaseAttDestinationLevel	= 5;
const TInt KSMILanchorbaseAttDur				= 6;
const TInt KSMILanchorbaseAttEnd				= 7;
const TInt KSMILanchorbaseAttHRef				= 8;
const TInt KSMILanchorbaseAttId					= 9;
const TInt KSMILanchorbaseAttMax				= 10;
const TInt KSMILanchorbaseAttMin				= 11;
const TInt KSMILanchorbaseAttRepeatCount		= 12;
const TInt KSMILanchorbaseAttRepeatDur			= 13;
const TInt KSMILanchorbaseAttSourceLevel		= 14;
const TInt KSMILanchorbaseAttTabIndex			= 15;
const TInt KSMILanchorbaseAttTarget				= 16;
const TInt KSMILanchorbaseAttTitle				= 17;
const TInt KSMILanchorbaseAttXMLLang			= 18;
const TInt KSMILanchorbaseAttNameCount = KSMILanchorbaseAttXMLLang+1;


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILAnchorBase : public CMDXMLSMILBasicElt
{
public:
	IMPORT_C virtual ~CMDXMLSMILAnchorBase();

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
	CMDXMLSMILAnchorBase( CMDXMLDocument* aOwnerDocument );

public:	//Access functions for element attributes
	/**
	 * @return Returns the value of the AccessKey attribute
	 */
	inline TPtrC AttAccessKey() const {return iDescAtts[KSMILanchorbaseAttAccessKey]->Des();}

	/**
	 * @return Returns true if the AccessKey attribute is specified
	 */
	inline TBool IsAttAccessKeySpecified() const {return (iDescAtts[KSMILanchorbaseAttAccessKey] != NULL);}

	/**
	 * Sets the value of the AccessKey attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAccessKeyL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttAccessKey, aAttVal); }

	/**
	 * Unsets the value of the AccessKey attribute
	 */
	inline void RemoveAttAccessKey(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttAccessKey);}

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
	 * @return Returns the value of the Alt attribute
	 */
	inline TPtrC AttAlt() const {return iDescAtts[KSMILanchorbaseAttAlt]->Des();}

	/**
	 * @return Returns true if the Alt attribute is specified
	 */
	inline TBool IsAttAltSpecified() const {return (iDescAtts[KSMILanchorbaseAttAlt] != NULL);}

	/**
	 * Sets the value of the Alt attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAltL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttAlt, aAttVal);}

	/**
	 * Unsets the value of the Alt attribute
	 */
	inline void RemoveAttAlt(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttAlt);}

	/**
	 * @return Returns the value of the Begin attribute
	 */
	inline TPtrC AttBegin() const {return iDescAtts[KSMILanchorbaseAttBegin]->Des();}

	/**
	 * @return Returns true if the Begin attribute is specified
	 */
	inline TBool IsAttBeginSpecified() const {return (iDescAtts[KSMILanchorbaseAttBegin] != NULL);}

	/**
	 * Sets the value of the Begin attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBeginL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttBegin, aAttVal);}

	/**
	 * Unsets the value of the Begin attribute
	 */
	inline void RemoveAttBegin(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttBegin);}

	/**
	 * @return Returns the value of the Class attribute
	 */
	inline TPtrC AttClass() const {return iDescAtts[KSMILanchorbaseAttClass]->Des();}

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	inline TBool IsAttClassSpecified() const {return (iDescAtts[KSMILanchorbaseAttClass] != NULL);}

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClassL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttClass, aAttVal);}

	/**
	 * Unsets the value of the Class attribute
	 */
	inline void RemoveAttClass(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttClass);}

	/**
	 * @return Returns the value of the Coords attribute
	 */
	inline TPtrC AttCoords() const {return iDescAtts[KSMILanchorbaseAttCoords]->Des();}

	/**
	 * @return Returns true if the Coords attribute is specified
	 */
	inline TBool IsAttCoordsSpecified() const {return (iDescAtts[KSMILanchorbaseAttCoords] != NULL);}

	/**
	 * Sets the value of the Coords attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttCoordsL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttCoords, aAttVal);}

	/**
	 * Unsets the value of the Coords attribute
	 */
	inline void RemoveAttCoords(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttCoords);}

	/**
	 * @return Returns the value of the DestinationLevel attribute
	 */
	inline TPtrC AttDestinationLevel() const {return iDescAtts[KSMILanchorbaseAttDestinationLevel]->Des();}

	/**
	 * @return Returns true if the DestinationLevel attribute is specified
	 */
	inline TBool IsAttDestinationLevelSpecified() const {return (iDescAtts[KSMILanchorbaseAttDestinationLevel] != NULL);}

	/**
	 * Sets the value of the DestinationLevel attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttDestinationLevelL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttDestinationLevel, aAttVal);}

	/**
	 * Unsets the value of the DestinationLevel attribute
	 */
	inline void RemoveAttDestinationLevel(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttDestinationLevel);}

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
	inline TPtrC AttDur() const {return iDescAtts[KSMILanchorbaseAttDur]->Des();}

	/**
	 * @return Returns true if the Dur attribute is specified
	 */
	inline TBool IsAttDurSpecified() const {return (iDescAtts[KSMILanchorbaseAttDur] != NULL);}

	/**
	 * Sets the value of the Dur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttDur, aAttVal);}

	/**
	 * Unsets the value of the Dur attribute
	 */
	inline void RemoveAttDur(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttDur);}

	/**
	 * @return Returns the value of the End attribute
	 */
	inline TPtrC AttEnd() const {return iDescAtts[KSMILanchorbaseAttEnd]->Des();}

	/**
	 * @return Returns true if the End attribute is specified
	 */
	inline TBool IsAttEndSpecified() const {return (iDescAtts[KSMILanchorbaseAttEnd] != NULL);}

	/**
	 * Sets the value of the End attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttEndL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttEnd, aAttVal);}

	/**
	 * Unsets the value of the End attribute
	 */
	inline void RemoveAttEnd(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttEnd);}

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
	inline TPtrC AttHRef() const {return iDescAtts[KSMILanchorbaseAttHRef]->Des();}

	/**
	 * @return Returns true if the HRef attribute is specified
	 */
	inline TBool IsAttHRefSpecified() const {return (iDescAtts[KSMILanchorbaseAttHRef] != NULL);}

	/**
	 * Sets the value of the HRef attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttHRefL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttHRef, aAttVal);}

	/**
	 * Unsets the value of the HRef attribute
	 */
	inline void RemoveAttHRef(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttHRef);}

	/**
	 * @return Returns the value of the Id attribute
	 */
	inline TPtrC AttId() const {return iDescAtts[KSMILanchorbaseAttId]->Des();}

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	inline TBool IsAttIdSpecified() const {return (iDescAtts[KSMILanchorbaseAttId] != NULL);}

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttIdL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttId, aAttVal);}

	/**
	 * Unsets the value of the Id attribute
	 */
	inline void RemoveAttId(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttId);}

	/**
	 * @return Returns the value of the Max attribute
	 */
	inline TPtrC AttMax() const {return iDescAtts[KSMILanchorbaseAttMax]->Des();}

	/**
	 * @return Returns true if the Max attribute is specified
	 */
	inline TBool IsAttMaxSpecified() const {return (iDescAtts[KSMILanchorbaseAttMax] != NULL);}

	/**
	 * Sets the value of the Max attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMaxL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttMax, aAttVal);}

	/**
	 * Unsets the value of the Max attribute
	 */
	inline void RemoveAttMax(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttMax);}

	/**
	 * @return Returns the value of the Min attribute
	 */
	inline TPtrC AttMin() const {return iDescAtts[KSMILanchorbaseAttMin]->Des();}

	/**
	 * @return Returns true if the Min attribute is specified
	 */
	inline TBool IsAttMinSpecified() const {return (iDescAtts[KSMILanchorbaseAttMin] != NULL);}

	/**
	 * Sets the value of the Min attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMinL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttMin, aAttVal);}

	/**
	 * Unsets the value of the Min attribute
	 */
	inline void RemoveAttMin(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttMin);}
	/**
	 * @return Returns the value of the NoHRef attribute
	 */
	inline TDOMAttNoHRefType AttNoHRef() const {return iAttNoHRef;}

	/**
	 * @return Returns true if the NoHRef attribute is specified
	 */
	inline TBool IsAttNoHRefSpecified() const {return (iAttNoHRef != EAttNoHRefUndefined);}

	/**
	 * Sets the value of the NoHRef attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttNoHRef( TDOMAttNoHRefType aAttVal ){iAttNoHRef = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the NoHRef attribute
	 */
	inline void RemoveAttNoHRef(){iAttNoHRef = EAttNoHRefUndefined;}

	/**
	 * @return Returns the value of the RepeatCount attribute
	 */
	inline TPtrC AttRepeatCount() const {return iDescAtts[KSMILanchorbaseAttRepeatCount]->Des();}

	/**
	 * @return Returns true if the RepeatCount attribute is specified
	 */
	inline TBool IsAttRepeatCountSpecified() const {return (iDescAtts[KSMILanchorbaseAttRepeatCount] != NULL);}

	/**
	 * Sets the value of the RepeatCount attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatCountL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttRepeatCount, aAttVal);}

	/**
	 * Unsets the value of the RepeatCount attribute
	 */
	inline void RemoveAttRepeatCount(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttRepeatCount);}

	/**
	 * @return Returns the value of the RepeatDur attribute
	 */
	inline TPtrC AttRepeatDur() const {return iDescAtts[KSMILanchorbaseAttRepeatDur]->Des();}

	/**
	 * @return Returns true if the RepeatDur attribute is specified
	 */
	inline TBool IsAttRepeatDurSpecified() const {return (iDescAtts[KSMILanchorbaseAttRepeatDur] != NULL);}

	/**
	 * Sets the value of the RepeatDur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttRepeatDur, aAttVal);}

	/**
	 * Unsets the value of the RepeatDur attribute
	 */
	inline void RemoveAttRepeatDur(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttRepeatDur);}

	/**
	 * @return Returns the value of the Shape attribute
	 */
	inline TDOMAttShapeType AttShape() const {return iAttShape;}

	/**
	 * @return Returns true if the Shape attribute is specified
	 */
	inline TBool IsAttShapeSpecified() const {return (iAttShape != EAttShapeUndefined);}

	/**
	 * Sets the value of the Shape attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttShape( TDOMAttShapeType aAttVal ) {iAttShape = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the Shape attribute
	 */
	inline void RemoveAttShape() {iAttShape = EAttShapeUndefined;}

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
	inline TInt SetAttSkipContent( TDOMAttSkipContentType aAttVal ){iAttSkipContent = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the SkipContent attribute
	 */
	inline void RemoveAttSkipContent(){iAttSkipContent = EAttSkipContentUndefined;}

	/**
	 * @return Returns the value of the SourceLevel attribute
	 */
	inline TPtrC AttSourceLevel() const {return iDescAtts[KSMILanchorbaseAttSourceLevel]->Des();}

	/**
	 * @return Returns true if the SourceLevel attribute is specified
	 */
	inline TBool IsAttSourceLevelSpecified() const {return (iDescAtts[KSMILanchorbaseAttSourceLevel] != NULL);}

	/**
	 * Sets the value of the SourceLevel attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSourceLevelL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttSourceLevel, aAttVal);}

	/**
	 * Unsets the value of the SourceLevel attribute
	 */
	inline void RemoveAttSourceLevel(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttSourceLevel);}

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
	inline TPtrC AttTabIndex() const {return iDescAtts[KSMILanchorbaseAttTabIndex]->Des();}

	/**
	 * @return Returns true if the TabIndex attribute is specified
	 */
	inline TBool IsAttTabIndexSpecified() const {return (iDescAtts[KSMILanchorbaseAttTabIndex] != NULL);}

	/**
	 * Sets the value of the TabIndex attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTabIndexL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttTabIndex, aAttVal);}

	/**
	 * Unsets the value of the TabIndex attribute
	 */
	inline void RemoveAttTabIndex(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttTabIndex);}

	/**
	 * @return Returns the value of the Target attribute
	 */
	inline TPtrC AttTarget() const {return iDescAtts[KSMILanchorbaseAttTarget]->Des();}

	/**
	 * @return Returns true if the Target attribute is specified
	 */
	inline TBool IsAttTargetSpecified() const {return (iDescAtts[KSMILanchorbaseAttTarget] != NULL);}

	/**
	 * Sets the value of the Target attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTargetL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttTarget, aAttVal);}

	/**
	 * Unsets the value of the Target attribute
	 */
	inline void RemoveAttTarget(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttTarget);}

	/**
	 * @return Returns the value of the Title attribute
	 */
	inline TPtrC AttTitle() const {return iDescAtts[KSMILanchorbaseAttTitle]->Des();}

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	inline TBool IsAttTitleSpecified() const {return (iDescAtts[KSMILanchorbaseAttTitle] != NULL);}

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTitleL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttTitle, aAttVal);}

	/**
	 * Unsets the value of the Title attribute
	 */
	inline void RemoveAttTitle(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttTitle);}

	/**
	 * @return Returns the value of the XMLLang attribute
	 */
	inline TPtrC AttXMLLang() const {return iDescAtts[KSMILanchorbaseAttXMLLang]->Des();}

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	inline TBool IsAttXMLLangSpecified() const {return (iDescAtts[KSMILanchorbaseAttXMLLang] != NULL);}

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttXMLLangL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttXMLLang, aAttVal);}

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	inline void RemoveAttXMLLang(){RemoveDescAtt(iDescAtts, KSMILanchorbaseAttNameCount, KSMILanchorbaseAttXMLLang);}

private:
	// All descriptor-based attributes are stored in an array.
	// The array is fixed-size for the class and is indexed based on 
	// alphabetical order of attribute name
	HBufC *iDescAtts[KSMILanchorbaseAttNameCount];				///< Array of descriptor attributes

	//Member variables for element attributes
	// These are the Enum-based attributes which are handled in a hard-wired way
	TDOMAttActuateType iAttActuate;		///< Member variable for the Actuate attribute
	TDOMAttDestinationPlaystateType iAttDestinationPlaystate;	///< Member variable for the DestinationPlaystate attribute
	TDOMAttExternalType iAttExternal;	///< Member variable for the External attribute
	TDOMAttFillType iAttFill;			///< Member variable for the Fill attribute
	TDOMAttNoHRefType iAttNoHRef;		///< Member variable for the NoHRef attribute
	TDOMAttShapeType iAttShape;			///< Member variable for the Shape attribute
	TDOMAttShowType iAttShow;			///< Member variable for the Show attribute
	TDOMAttSkipContentType iAttSkipContent;	///< Member variable for the SkipContent attribute
	TDOMAttSourcePlaystateType iAttSourcePlaystate;	///< Member variable for the SourcePlaystate attribute

	};

#endif

// End of File