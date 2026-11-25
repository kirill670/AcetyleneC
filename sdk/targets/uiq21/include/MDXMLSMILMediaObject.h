// MDXMLSMILMediaObject.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILMediaObject.h
 * This file contains the declaration of a base timed media object class to be used
 * by derived classes for the specific timed media elements.
 * For non-timed media objects (text and img) the timed attributes are disabled.
 */

#ifndef __MDXMLSMILMediaObject_H__
#define __MDXMLSMILMediaObject_H__

#include <e32base.h>

// Array indices for descriptor attributes.
// These must start at zero and must be in alphabetical order of attribute name

const TInt KSMILMediaObjectAttAbstract				= 0;
const TInt KSMILMediaObjectAttAlt					= 1;
const TInt KSMILMediaObjectAttAuthor				= 2;
const TInt KSMILMediaObjectAttBegin					= 3;
const TInt KSMILMediaObjectAttClass					= 4;
const TInt KSMILMediaObjectAttClipBegin			= 5;
const TInt KSMILMediaObjectAttClipEnd				= 6;
const TInt KSMILMediaObjectAttCopyright			= 7;
const TInt KSMILMediaObjectAttCustomTest			= 8;
const TInt KSMILMediaObjectAttDur					= 9;
const TInt KSMILMediaObjectAttEnd					= 10;
const TInt KSMILMediaObjectAttId						= 11;
const TInt KSMILMediaObjectAttLongDesc				= 12;
const TInt KSMILMediaObjectAttMax					= 13;
const TInt KSMILMediaObjectAttMin					= 14;
const TInt KSMILMediaObjectAttRegion				= 15;
const TInt KSMILMediaObjectAttRepeatCount			= 16;
const TInt KSMILMediaObjectAttRepeatDur			= 17;
const TInt KSMILMediaObjectAttSrc					= 18;
const TInt KSMILMediaObjectAttSystemBitrate		= 19;
const TInt KSMILMediaObjectAttSystemCPU			= 20;
const TInt KSMILMediaObjectAttSystemComponent	= 21;
const TInt KSMILMediaObjectAttSystemLanguage		= 22;
const TInt KSMILMediaObjectAttSystemOperatingSystem	= 23;
const TInt KSMILMediaObjectAttSystemRequired		= 24;
const TInt KSMILMediaObjectAttSystemScreenDepth	= 25;
const TInt KSMILMediaObjectAttSystemScreenSize	= 26;
const TInt KSMILMediaObjectAttSystem_bitrate		= 27;
const TInt KSMILMediaObjectAttSystem_language	= 28;
const TInt KSMILMediaObjectAttSystem_required	= 29;
const TInt KSMILMediaObjectAttSystem_screen_depth	= 30;
const TInt KSMILMediaObjectAttSystem_screen_size	= 31;
const TInt KSMILMediaObjectAttTitle					= 32;
const TInt KSMILMediaObjectAttType					= 33;
const TInt KSMILMediaObjectAttXMLLang				= 34;
const TInt KSMILMediaObjectAttNameCount	= KSMILMediaObjectAttXMLLang+1;


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILMediaObject : public CMDXMLSMILBasicElt
{
public:
	IMPORT_C virtual ~CMDXMLSMILMediaObject();

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
	CMDXMLSMILMediaObject( CMDXMLDocument* aOwnerDocument );

public:
	//Access functions for element attributes

	/**
	 * @return Returns the value of the Abstract attribute
	 */
	inline TPtrC AttAbstract() const {return iDescAtts[KSMILMediaObjectAttAbstract]->Des();}

	/**
	 * @return Returns true if the Abstract attribute is specified
	 */
	inline TBool IsAttAbstractSpecified() const {return (iDescAtts[KSMILMediaObjectAttAbstract] != NULL);}

	/**
	 * Sets the value of the Abstract attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAbstractL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttAbstract, aAttVal);}

	/**
	 * Unsets the value of the Abstract attribute
	 */
	inline void RemoveAttAbstract(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttAbstract);}

	/**
	 * @return Returns the value of the Alt attribute
	 */
	inline TPtrC AttAlt() const {return iDescAtts[KSMILMediaObjectAttAlt]->Des();}

	/**
	 * @return Returns true if the Alt attribute is specified
	 */
	inline TBool IsAttAltSpecified() const {return (iDescAtts[KSMILMediaObjectAttAlt] != NULL);}

	/**
	 * Sets the value of the Alt attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAltL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttAlt, aAttVal);}

	/**
	 * Unsets the value of the Alt attribute
	 */
	inline void RemoveAttAlt(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttAlt);}

	/**
	 * @return Returns the value of the Author attribute
	 */
	inline TPtrC AttAuthor() const {return iDescAtts[KSMILMediaObjectAttAuthor]->Des();}

	/**
	 * @return Returns true if the Author attribute is specified
	 */
	inline TBool IsAttAuthorSpecified() const {return (iDescAtts[KSMILMediaObjectAttAuthor] != NULL);}

	/**
	 * Sets the value of the Author attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAuthorL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttAuthor, aAttVal);}

	/**
	 * Unsets the value of the Author attribute
	 */
	inline void RemoveAttAuthor(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttAuthor);}

	/**
	 * @return Returns the value of the Begin attribute
	 */
	inline TPtrC AttBegin() const {return iDescAtts[KSMILMediaObjectAttBegin]->Des();}

	/**
	 * @return Returns true if the Begin attribute is specified
	 */
	inline TBool IsAttBeginSpecified() const {return (iDescAtts[KSMILMediaObjectAttBegin] != NULL);}

	/**
	 * Sets the value of the Begin attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBeginL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttBegin, aAttVal);}

	/**
	 * Unsets the value of the Begin attribute
	 */
	inline void RemoveAttBegin(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttBegin);}

	/**
	 * @return Returns the value of the Class attribute
	 */
	inline TPtrC AttClass() const {return iDescAtts[KSMILMediaObjectAttClass]->Des();}

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	inline TBool IsAttClassSpecified() const {return (iDescAtts[KSMILMediaObjectAttClass] != NULL);}

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClassL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttClipEnd, aAttVal);}

	/**
	 * Unsets the value of the Class attribute
	 */
	inline void RemoveAttClass(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttClass);}

	/**
	 * @return Returns the value of the ClipBegin attribute
	 */
	inline TPtrC AttClipBegin() const {return iDescAtts[KSMILMediaObjectAttClipBegin]->Des();}

	/**
	 * @return Returns true if the ClipBegin attribute is specified
	 */
	inline TBool IsAttClipBeginSpecified() const {return (iDescAtts[KSMILMediaObjectAttClipBegin] != NULL);}

	/**
	 * Sets the value of the ClipBegin attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClipBeginL( const TDesC& aAttVal ){return (iTimedMediaObject ? SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttClass, aAttVal) : KErrNotSupported);}

	/**
	 * Unsets the value of the ClipBegin attribute
	 */
	inline void RemoveAttClipBegin(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttClipBegin);}

	/**
	 * @return Returns the value of the ClipEnd attribute
	 */
	inline TPtrC AttClipEnd() const {return iDescAtts[KSMILMediaObjectAttClipEnd]->Des();}

	/**
	 * @return Returns true if the ClipEnd attribute is specified
	 */
	inline TBool IsAttClipEndSpecified() const {return (iDescAtts[KSMILMediaObjectAttClipEnd] != NULL);}

	/**
	 * Sets the value of the ClipEnd attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClipEndL( const TDesC& aAttVal ){return (iTimedMediaObject ? SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttClipEnd, aAttVal) : KErrNotSupported);}

	/**
	 * Unsets the value of the ClipEnd attribute
	 */
	inline void RemoveAttClipEnd(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttClipEnd);}

	/**
	 * @return Returns the value of the Copyright attribute
	 */
	inline TPtrC AttCopyright() const {return iDescAtts[KSMILMediaObjectAttCopyright]->Des();}

	/**
	 * @return Returns true if the Copyright attribute is specified
	 */
	inline TBool IsAttCopyrightSpecified() const {return (iDescAtts[KSMILMediaObjectAttCopyright] != NULL);}

	/**
	 * Sets the value of the Copyright attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttCopyrightL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttCopyright, aAttVal);}

	/**
	 * Unsets the value of the Copyright attribute
	 */
	inline void RemoveAttCopyright(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttCopyright);}

	/**
	 * @return Returns the value of the CustomTest attribute
	 */
	inline TPtrC AttCustomTest() const {return iDescAtts[KSMILMediaObjectAttCustomTest]->Des();}

	/**
	 * @return Returns true if the CustomTest attribute is specified
	 */
	inline TBool IsAttCustomTestSpecified() const {return (iDescAtts[KSMILMediaObjectAttCustomTest] != NULL);}
	/**
	 * Sets the value of the CustomTest attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttCustomTestL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttCustomTest, aAttVal);}

	/**
	 * Unsets the value of the CustomTest attribute
	 */
	inline void RemoveAttCustomTest(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttCustomTest);}

	/**
	 * @return Returns the value of the Dur attribute
	 */
	inline TPtrC AttDur() const {return iDescAtts[KSMILMediaObjectAttDur]->Des();}

	/**
	 * @return Returns true if the Dur attribute is specified
	 */
	inline TBool IsAttDurSpecified() const {return (iDescAtts[KSMILMediaObjectAttDur] != NULL);}

	/**
	 * Sets the value of the Dur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttDur, aAttVal);}

	/**
	 * Unsets the value of the Dur attribute
	 */
	inline void RemoveAttDur(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttDur);}

	/**
	 * @return Returns the value of the End attribute
	 */
	inline TPtrC AttEnd() const {return iDescAtts[KSMILMediaObjectAttEnd]->Des();}

	/**
	 * @return Returns true if the End attribute is specified
	 */
	inline TBool IsAttEndSpecified() const {return (iDescAtts[KSMILMediaObjectAttEnd] != NULL);}

	/**
	 * Sets the value of the End attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttEndL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttEnd, aAttVal);}

	/**
	 * Unsets the value of the End attribute
	 */
	inline void RemoveAttEnd(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttEnd);}

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
	 * @return Returns the value of the Id attribute
	 */
	inline TPtrC AttId() const {return iDescAtts[KSMILMediaObjectAttId]->Des();}

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	inline TBool IsAttIdSpecified() const {return (iDescAtts[KSMILMediaObjectAttId] != NULL);}

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttIdL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttId, aAttVal);}

	/**
	 * Unsets the value of the Id attribute
	 */
	inline void RemoveAttId(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttId);}

	/**
	 * @return Returns the value of the LongDesc attribute
	 */
	inline TPtrC AttLongDesc() const {return iDescAtts[KSMILMediaObjectAttLongDesc]->Des();}

	/**
	 * @return Returns true if the LongDesc attribute is specified
	 */
	inline TBool IsAttLongDescSpecified() const {return (iDescAtts[KSMILMediaObjectAttLongDesc] != NULL);}

	/**
	 * Sets the value of the LongDesc attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttLongDescL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttLongDesc, aAttVal);}

	/**
	 * Unsets the value of the LongDesc attribute
	 */
	inline void RemoveAttLongDesc(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttLongDesc);}

	/**
	 * @return Returns the value of the Max attribute
	 */
	inline TPtrC AttMax() const {return iDescAtts[KSMILMediaObjectAttMax]->Des();}

	/**
	 * @return Returns true if the Max attribute is specified
	 */
	inline TBool IsAttMaxSpecified() const {return (iDescAtts[KSMILMediaObjectAttMax] != NULL);}

	/**
	 * Sets the value of the Max attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMaxL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttMax, aAttVal);}

	/**
	 * Unsets the value of the Max attribute
	 */
	inline void RemoveAttMax(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttMax);}

	/**
	 * @return Returns the value of the Min attribute
	 */
	inline TPtrC AttMin() const {return iDescAtts[KSMILMediaObjectAttMin]->Des();}

	/**
	 * @return Returns true if the Min attribute is specified
	 */
	inline TBool IsAttMinSpecified() const {return (iDescAtts[KSMILMediaObjectAttMin] != NULL);}

	/**
	 * Sets the value of the Min attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMinL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttMin, aAttVal);}

	/**
	 * Unsets the value of the Min attribute
	 */
	inline void RemoveAttMin(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttMin);}

	/**
	 * @return Returns the value of the Region attribute
	 */
	inline TPtrC AttRegion() const {return iDescAtts[KSMILMediaObjectAttRegion]->Des();}

	/**
	 * @return Returns true if the Region attribute is specified
	 */
	inline TBool IsAttRegionSpecified() const {return (iDescAtts[KSMILMediaObjectAttRegion] != NULL);}

	/**
	 * Sets the value of the Region attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRegionL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttRegion, aAttVal);}

	/**
	 * Unsets the value of the Region attribute
	 */
	inline void RemoveAttRegion(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttRegion);}

	/**
	 * @return Returns the value of the RepeatCount attribute
	 */
	inline TPtrC AttRepeatCount() const {return iDescAtts[KSMILMediaObjectAttRepeatCount]->Des();}

	/**
	 * @return Returns true if the RepeatCount attribute is specified
	 */
	inline TBool IsAttRepeatCountSpecified() const {return (iDescAtts[KSMILMediaObjectAttRepeatCount] != NULL);}

	/**
	 * Sets the value of the RepeatCount attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatCountL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttRepeatCount, aAttVal);}

	/**
	 * Unsets the value of the RepeatCount attribute
	 */
	inline void RemoveAttRepeatCount(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttRepeatCount);}

	/**
	 * @return Returns the value of the RepeatDur attribute
	 */
	inline TPtrC AttRepeatDur() const {return iDescAtts[KSMILMediaObjectAttRepeatDur]->Des();}

	/**
	 * @return Returns true if the RepeatDur attribute is specified
	 */
	inline TBool IsAttRepeatDurSpecified() const {return (iDescAtts[KSMILMediaObjectAttRepeatDur] != NULL);}

	/**
	 * Sets the value of the RepeatDur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttRepeatDur, aAttVal);}

	/**
	 * Unsets the value of the RepeatDur attribute
	 */
	inline void RemoveAttRepeatDur(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttRepeatDur);}

	/**
	 * @return Returns the value of the Src attribute
	 */
	inline TPtrC AttSrc() const {return iDescAtts[KSMILMediaObjectAttSrc]->Des();}

	/**
	 * @return Returns true if the Src attribute is specified
	 */
	inline TBool IsAttSrcSpecified() const {return (iDescAtts[KSMILMediaObjectAttSrc] != NULL);}

	/**
	 * Sets the value of the Src attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSrcL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSrc, aAttVal);}

	/**
	 * Unsets the value of the Src attribute
	 */
	inline void RemoveAttSrc(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSrc);}

	/**
	 * @return Returns the value of the SystemAudioDesc attribute
	 */
	inline TDOMAttSystemAudioDescType AttSystemAudioDesc() const {return iAttSystemAudioDesc;}

	/**
	 * @return Returns true if the SystemAudioDesc attribute is specified
	 */
	inline TBool IsAttSystemAudioDescSpecified() const {return (iAttSystemAudioDesc != EAttSystemAudioDescUndefined);}

	/**
	 * Sets the value of the SystemAudioDesc attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSystemAudioDesc( TDOMAttSystemAudioDescType aAttVal ){iAttSystemAudioDesc = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the SystemAudioDesc attribute
	 */
	inline void RemoveAttSystemAudioDesc() {iAttSystemAudioDesc = EAttSystemAudioDescUndefined;}

	/**
	 * @return Returns the value of the SystemBitrate attribute
	 */
	inline TPtrC AttSystemBitrate() const {return iDescAtts[KSMILMediaObjectAttSystemBitrate]->Des();}

	/**
	 * @return Returns true if the SystemBitrate attribute is specified
	 */
	inline TBool IsAttSystemBitrateSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemBitrate] != NULL);}

	/**
	 * Sets the value of the SystemBitrate attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemBitrateL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemBitrate, aAttVal);}

	/**
	 * Unsets the value of the SystemBitrate attribute
	 */
	inline void RemoveAttSystemBitrate(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemBitrate);}

	/**
	 * @return Returns the value of the SystemCPU attribute
	 */
	inline TPtrC AttSystemCPU() const {return iDescAtts[KSMILMediaObjectAttSystemCPU]->Des();}

	/**
	 * @return Returns true if the SystemCPU attribute is specified
	 */
	inline TBool IsAttSystemCPUSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemCPU] != NULL);}

	/**
	 * Sets the value of the SystemCPU attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemCPUL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemCPU, aAttVal);}

	/**
	 * Unsets the value of the SystemCPU attribute
	 */
	inline void RemoveAttSystemCPU(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemCPU);}

	/**
	 * @return Returns the value of the SystemCaptions attribute
	 */
	inline TDOMAttSystemCaptionsType AttSystemCaptions() const {return iAttSystemCaptions;}

	/**
	 * @return Returns true if the SystemCaptions attribute is specified
	 */
	inline TBool IsAttSystemCaptionsSpecified() const {return (iAttSystemCaptions != EAttSystemCaptionsUndefined);}

	/**
	 * Sets the value of the SystemCaptions attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSystemCaptions( TDOMAttSystemCaptionsType aAttVal ){iAttSystemCaptions = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the SystemCaptions attribute
	 */
	inline void RemoveAttSystemCaptions() {iAttSystemCaptions = EAttSystemCaptionsUndefined;}

	/**
	 * @return Returns the value of the SystemComponent attribute
	 */
	inline TPtrC AttSystemComponent() const {return iDescAtts[KSMILMediaObjectAttSystemComponent]->Des();}

	/**
	 * @return Returns true if the SystemComponent attribute is specified
	 */
	inline TBool IsAttSystemComponentSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemComponent] != NULL);}

	/**
	 * Sets the value of the SystemComponent attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemComponentL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemComponent, aAttVal);}

	/**
	 * Unsets the value of the SystemComponent attribute
	 */
	inline void RemoveAttSystemComponent(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemComponent);}

	/**
	 * @return Returns the value of the SystemLanguage attribute
	 */
	inline TPtrC AttSystemLanguage() const {return iDescAtts[KSMILMediaObjectAttSystemLanguage]->Des();}

	/**
	 * @return Returns true if the SystemLanguage attribute is specified
	 */
	inline TBool IsAttSystemLanguageSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemLanguage] != NULL);}

	/**
	 * Sets the value of the SystemLanguage attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemLanguageL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemLanguage, aAttVal);}

	/**
	 * Unsets the value of the SystemLanguage attribute
	 */
	inline void RemoveAttSystemLanguage(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemLanguage);}

	/**
	 * @return Returns the value of the SystemOperatingSystem attribute
	 */
	inline TPtrC AttSystemOperatingSystem() const {return iDescAtts[KSMILMediaObjectAttSystemOperatingSystem]->Des();}

	/**
	 * @return Returns true if the SystemOperatingSystem attribute is specified
	 */
	inline TBool IsAttSystemOperatingSystemSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemOperatingSystem] != NULL);}

	/**
	 * Sets the value of the SystemOperatingSystem attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemOperatingSystemL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemOperatingSystem, aAttVal);}

	/**
	 * Unsets the value of the SystemOperatingSystem attribute
	 */
	inline void RemoveAttSystemOperatingSystem(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemOperatingSystem);}

	/**
	 * @return Returns the value of the SystemOverdubOrSubtitle attribute
	 */
	inline TDOMAttSystemOverdubOrSubtitleType AttSystemOverdubOrSubtitle() const {return iAttSystemOverdubOrSubtitle;}

	/**
	 * @return Returns true if the SystemOverdubOrSubtitle attribute is specified
	 */
	inline TBool IsAttSystemOverdubOrSubtitleSpecified() const {return (iAttSystemOverdubOrSubtitle != EAttSystemOverdubOrSubtitleUndefined);}

	/**
	 * Sets the value of the SystemOverdubOrSubtitle attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSystemOverdubOrSubtitle( TDOMAttSystemOverdubOrSubtitleType aAttVal ){iAttSystemOverdubOrSubtitle = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the SystemOverdubOrSubtitle attribute
	 */
	inline void RemoveAttSystemOverdubOrSubtitle() {iAttSystemOverdubOrSubtitle = EAttSystemOverdubOrSubtitleUndefined;}

	/**
	 * @return Returns the value of the SystemRequired attribute
	 */
	inline TPtrC AttSystemRequired() const {return iDescAtts[KSMILMediaObjectAttSystemRequired]->Des();}

	/**
	 * @return Returns true if the SystemRequired attribute is specified
	 */
	inline TBool IsAttSystemRequiredSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemRequired] != NULL);}

	/**
	 * Sets the value of the SystemRequired attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemRequiredL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemRequired, aAttVal);}

	/**
	 * Unsets the value of the SystemRequired attribute
	 */
	inline void RemoveAttSystemRequired(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemRequired);}

	/**
	 * @return Returns the value of the SystemScreenDepth attribute
	 */
	inline TPtrC AttSystemScreenDepth() const {return iDescAtts[KSMILMediaObjectAttSystemScreenDepth]->Des();}

	/**
	 * @return Returns true if the SystemScreenDepth attribute is specified
	 */
	inline TBool IsAttSystemScreenDepthSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemScreenDepth] != NULL);}

	/**
	 * Sets the value of the SystemScreenDepth attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemScreenDepthL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemScreenDepth, aAttVal);}

	/**
	 * Unsets the value of the SystemScreenDepth attribute
	 */
	inline void RemoveAttSystemScreenDepth(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemScreenDepth);}

	/**
	 * @return Returns the value of the SystemScreenSize attribute
	 */
	inline TPtrC AttSystemScreenSize() const {return iDescAtts[KSMILMediaObjectAttSystemScreenSize]->Des();}

	/**
	 * @return Returns true if the SystemScreenSize attribute is specified
	 */
	inline TBool IsAttSystemScreenSizeSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystemScreenSize] != NULL);}

	/**
	 * Sets the value of the SystemScreenSize attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemScreenSizeL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemScreenSize, aAttVal);}

	/**
	 * Unsets the value of the SystemScreenSize attribute
	 */
	inline void RemoveAttSystemScreenSize(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystemScreenSize);}

	/**
	 * @return Returns the value of the System_bitrate attribute
	 */
	inline TPtrC AttSystem_bitrate() const {return iDescAtts[KSMILMediaObjectAttSystem_bitrate]->Des();}

	/**
	 * @return Returns true if the System_bitrate attribute is specified
	 */
	inline TBool IsAttSystem_bitrateSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystem_bitrate] != NULL);}

	/**
	 * Sets the value of the System_bitrate attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_bitrateL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_bitrate, aAttVal);}

	/**
	 * Unsets the value of the System_bitrate attribute
	 */
	inline void RemoveAttSystem_bitrate(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_bitrate);}

	/**
	 * @return Returns the value of the System_captions attribute
	 */
	inline TDOMAttSystem_captionsType AttSystem_captions() const {return iAttSystem_captions;}

	/**
	 * @return Returns true if the System_captions attribute is specified
	 */
	inline TBool IsAttSystem_captionsSpecified() const {return (iAttSystem_captions != EAttSystem_captionsUndefined);}

	/**
	 * Sets the value of the System_captions attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSystem_captions( TDOMAttSystem_captionsType aAttVal ){iAttSystem_captions = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the System_captions attribute
	 */
	inline void RemoveAttSystem_captions(){iAttSystem_captions = EAttSystem_captionsUndefined;}

	/**
	 * @return Returns the value of the System_language attribute
	 */
	inline TPtrC AttSystem_language() const {return iDescAtts[KSMILMediaObjectAttSystem_language]->Des();}

	/**
	 * @return Returns true if the System_language attribute is specified
	 */
	inline TBool IsAttSystem_languageSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystem_language] != NULL);}

	/**
	 * Sets the value of the System_language attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_languageL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_language, aAttVal);}

	/**
	 * Unsets the value of the System_language attribute
	 */
	inline void RemoveAttSystem_language(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_language);}

	/**
	 * @return Returns the value of the System_overdub_or_caption attribute
	 */
	inline TDOMAttSystem_overdub_or_captionType AttSystem_overdub_or_caption() const {return iAttSystem_overdub_or_caption;}

	/**
	 * @return Returns true if the System_overdub_or_caption attribute is specified
	 */
	inline TBool IsAttSystem_overdub_or_captionSpecified() const {return (iAttSystem_overdub_or_caption != EAttSystem_overdub_or_captionUndefined);}

	/**
	 * Sets the value of the System_overdub_or_caption attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttSystem_overdub_or_caption( TDOMAttSystem_overdub_or_captionType aAttVal ){iAttSystem_overdub_or_caption = aAttVal; return KErrNone;}

	/**
	 * Unsets the value of the System_overdub_or_caption attribute
	 */
	inline void RemoveAttSystem_overdub_or_caption() {iAttSystem_overdub_or_caption = EAttSystem_overdub_or_captionUndefined;}

	/**
	 * @return Returns the value of the System_required attribute
	 */
	inline TPtrC AttSystem_required() const {return iDescAtts[KSMILMediaObjectAttSystem_required]->Des();}

	/**
	 * @return Returns true if the System_required attribute is specified
	 */
	inline TBool IsAttSystem_requiredSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystem_required] != NULL);}

	/**
	 * Sets the value of the System_required attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_requiredL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_required, aAttVal);}

	/**
	 * Unsets the value of the System_required attribute
	 */
	inline void RemoveAttSystem_required(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_required);}

	/**
	 * @return Returns the value of the System_screen_depth attribute
	 */
	inline TPtrC AttSystem_screen_depth() const {return iDescAtts[KSMILMediaObjectAttSystem_screen_depth]->Des();}

	/**
	 * @return Returns true if the System_screen_depth attribute is specified
	 */
	inline TBool IsAttSystem_screen_depthSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystem_screen_depth] != NULL);}

	/**
	 * Sets the value of the System_screen_depth attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_screen_depthL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_screen_depth, aAttVal);}

	/**
	 * Unsets the value of the System_screen_depth attribute
	 */
	inline void RemoveAttSystem_screen_depth(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_screen_depth);}

	/**
	 * @return Returns the value of the System_screen_size attribute
	 */
	inline TPtrC AttSystem_screen_size() const {return iDescAtts[KSMILMediaObjectAttSystem_screen_size]->Des();}

	/**
	 * @return Returns true if the System_screen_size attribute is specified
	 */
	inline TBool IsAttSystem_screen_sizeSpecified() const {return (iDescAtts[KSMILMediaObjectAttSystem_screen_size] != NULL);}

	/**
	 * Sets the value of the System_screen_size attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_screen_sizeL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_screen_size, aAttVal);}

	/**
	 * Unsets the value of the System_screen_size attribute
	 */
	inline void RemoveAttSystem_screen_size(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttSystem_screen_size);}

	/**
	 * @return Returns the value of the Title attribute
	 */
	inline TPtrC AttTitle() const {return iDescAtts[KSMILMediaObjectAttTitle]->Des();}

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	inline TBool IsAttTitleSpecified() const {return (iDescAtts[KSMILMediaObjectAttTitle] != NULL);}

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTitleL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttTitle, aAttVal);}

	/**
	 * Unsets the value of the Title attribute
	 */
	inline void RemoveAttTitle(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttTitle);}

	/**
	 * @return Returns the value of the Type attribute
	 */
	inline TPtrC AttType() const {return iDescAtts[KSMILMediaObjectAttType]->Des();}

	/**
	 * @return Returns true if the Type attribute is specified
	 */
	inline TBool IsAttTypeSpecified() const {return (iDescAtts[KSMILMediaObjectAttType] != NULL);}

	/**
	 * Sets the value of the Type attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTypeL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttType, aAttVal);}

	/**
	 * Unsets the value of the Type attribute
	 */
	inline void RemoveAttType(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttType);}

		/**
	 * @return Returns the value of the XMLLang attribute
	 */
	inline TPtrC AttXMLLang() const {return iDescAtts[KSMILMediaObjectAttXMLLang]->Des();}

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	inline TBool IsAttXMLLangSpecified() const {return (iDescAtts[KSMILMediaObjectAttXMLLang] != NULL);}

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttXMLLangL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttXMLLang, aAttVal);}

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	inline void RemoveAttXMLLang(){RemoveDescAtt(iDescAtts, KSMILMediaObjectAttNameCount, KSMILMediaObjectAttXMLLang);}

protected:
	/**
	 * Check the immediate children of this element - i.e. the first level of children only
	 * The default implementation returns true - derived classes can override with
	 * DTD-specific checks.
	 * @returns True if immediate children are valid
	 */
	virtual TBool CheckImmediateChildren();

	/**
	 * Indicate that this object is or isn't a timed media object - should only be set
	 * in the constructor of a derived object.
	 */
	void SetTimedMediaObject( TBool aIsTimed );

private:
	// All descriptor-based attributes are stored in an array.
	// The array is fixed-size for the class and is indexed based on 
	// alphabetical order of attribute name
	HBufC *iDescAtts[KSMILMediaObjectAttNameCount];				///< Array of descriptor attributes

	//Member variables for element attributes
	// These are the Enum-based attributes which are handled in a hard-wired way
	TDOMAttFillType iAttFill;		///< Member variable for the Fill attribute
	TDOMAttSystemAudioDescType iAttSystemAudioDesc;		///< Member variable for the SystemAudioDesc attribute
	TDOMAttSystemCaptionsType iAttSystemCaptions;		///< Member variable for the SystemCaptions attribute
	TDOMAttSystemOverdubOrSubtitleType iAttSystemOverdubOrSubtitle;		///< Member variable for the SystemOverdubOrSubtitle attribute
	TDOMAttSystem_captionsType iAttSystem_captions;		///< Member variable for the System_captions attribute
	TDOMAttSystem_overdub_or_captionType iAttSystem_overdub_or_caption;		///< Member variable for the System_overdub_or_caption attribute

	// The CMDXMLSMILmediaObject class is used to represent both timed and un-timed
	// Media objects.  For un-timed objects, the ClipBegin and ClipEnd attributes 
	// cannot be set or accessed.  The following flag tells us which type of media
	// object we are.
	TBool iTimedMediaObject;
	};

#endif

// End of File