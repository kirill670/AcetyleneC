// MDXMLSMILTimingElt.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILTimingElt.h
 * This file contains the declaration of a base timing object class to be used
 * by derived classes for the specific timing elements
 */

#ifndef __MDXMLSMILTIMINGELT_H__
#define __MDXMLSMILTIMINGELT_H__

#include <e32base.h>


// Array indices for descriptor attributes.
// These must start at zero and must be in alphabetical order of attribute
// name

const TInt KSMILtimingeltAttAbstract				= 0;
const TInt KSMILtimingeltAttAuthor					= 1;
const TInt KSMILtimingeltAttBegin					= 2;
const TInt KSMILtimingeltAttClass					= 3;
const TInt KSMILtimingeltAttCopyright				= 4;
const TInt KSMILtimingeltAttCustomTest				= 5;
const TInt KSMILtimingeltAttDur						= 6;
const TInt KSMILtimingeltAttEnd						= 7;
const TInt KSMILtimingeltAttEndsync					= 8;
const TInt KSMILtimingeltAttId						= 9;
const TInt KSMILtimingeltAttMax						= 10;
const TInt KSMILtimingeltAttMin						= 11;
const TInt KSMILtimingeltAttRepeatCount				= 12;
const TInt KSMILtimingeltAttRepeatDur				= 13;
const TInt KSMILtimingeltAttSystemBitrate			= 14;
const TInt KSMILtimingeltAttSystemCPU				= 15;
const TInt KSMILtimingeltAttSystemComponent			= 16;
const TInt KSMILtimingeltAttSystemLanguage			= 17;
const TInt KSMILtimingeltAttSystemOperatingSystem	= 18;
const TInt KSMILtimingeltAttSystemRequired			= 19;
const TInt KSMILtimingeltAttSystemScreenDepth		= 20;
const TInt KSMILtimingeltAttSystemScreenSize		= 21;
const TInt KSMILtimingeltAttSystem_bitrate			= 22;
const TInt KSMILtimingeltAttSystem_language			= 23;
const TInt KSMILtimingeltAttSystem_required			= 24;
const TInt KSMILtimingeltAttSystem_screen_depth		= 25;
const TInt KSMILtimingeltAttSystem_screen_size		= 26;
const TInt KSMILtimingeltAttTitle					= 27;
const TInt KSMILtimingeltAttXMLLang					= 28;
const TInt KSMILtimingeltAttNameCount	= KSMILtimingeltAttXMLLang+1;


// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;

class CMDXMLSMILTimingElt : public CMDXMLSMILBasicElt
{
public:
	IMPORT_C virtual ~CMDXMLSMILTimingElt();

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
	CMDXMLSMILTimingElt( CMDXMLDocument* aOwnerDocument );

public:

	//Access functions for element attributes
	/**
	 * @return Returns the value of the Abstract attribute
	 */
	inline TPtrC AttAbstract() const {return iDescAtts[KSMILtimingeltAttAbstract]->Des();}

	/**
	 * @return Returns true if the Abstract attribute is specified
	 */
	inline TBool IsAttAbstractSpecified() const {return (iDescAtts[KSMILtimingeltAttAbstract] != NULL);}

	/**
	 * Sets the value of the Abstract attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAbstractL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttAbstract, aAttVal);}

	/**
	 * Unsets the value of the Abstract attribute
	 */
	inline void RemoveAttAbstract(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttAbstract);}

	/**
	 * @return Returns the value of the Author attribute
	 */
	inline TPtrC AttAuthor() const {return iDescAtts[KSMILtimingeltAttAuthor]->Des();}

	/**
	 * @return Returns true if the Author attribute is specified
	 */
	inline TBool IsAttAuthorSpecified() const {return (iDescAtts[KSMILtimingeltAttAuthor] != NULL);}

	/**
	 * Sets the value of the Author attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttAuthorL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttAuthor, aAttVal);}

	/**
	 * Unsets the value of the Author attribute
	 */
	inline void RemoveAttAuthor(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttAuthor);}

	/**
	 * @return Returns the value of the Begin attribute
	 */
	inline TPtrC AttBegin() const {return iDescAtts[KSMILtimingeltAttBegin]->Des();}

	/**
	 * @return Returns true if the Begin attribute is specified
	 */
	inline TBool IsAttBeginSpecified() const {return (iDescAtts[KSMILtimingeltAttBegin] != NULL);}

	/**
	 * Sets the value of the Begin attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttBeginL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttBegin, aAttVal);}

	/**
	 * Unsets the value of the Begin attribute
	 */
	inline void RemoveAttBegin(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttBegin);}

	/**
	 * @return Returns the value of the Class attribute
	 */
	inline TPtrC AttClass() const {return iDescAtts[KSMILtimingeltAttClass]->Des();}

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	inline TBool IsAttClassSpecified() const {return (iDescAtts[KSMILtimingeltAttClass] != NULL);}

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttClassL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttClass, aAttVal);}

	/**
	 * Unsets the value of the Class attribute
	 */
	inline void RemoveAttClass(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttClass);}

	/**
	 * @return Returns the value of the Copyright attribute
	 */
	inline TPtrC AttCopyright() const {return iDescAtts[KSMILtimingeltAttCopyright]->Des();}

	/**
	 * @return Returns true if the Copyright attribute is specified
	 */
	inline TBool IsAttCopyrightSpecified() const {return (iDescAtts[KSMILtimingeltAttCopyright] != NULL);}

	/**
	 * Sets the value of the Copyright attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttCopyrightL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttCopyright, aAttVal);}

	/**
	 * Unsets the value of the Copyright attribute
	 */
	inline void RemoveAttCopyright(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttCopyright);}

	/**
	 * @return Returns the value of the CustomTest attribute
	 */
	inline TPtrC AttCustomTest() const {return iDescAtts[KSMILtimingeltAttCustomTest]->Des();}

	/**
	 * @return Returns true if the CustomTest attribute is specified
	 */
	inline TBool IsAttCustomTestSpecified() const {return (iDescAtts[KSMILtimingeltAttCustomTest] != NULL);}

	/**
	 * Sets the value of the CustomTest attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttCustomTestL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttCustomTest, aAttVal);}

	/**
	 * Unsets the value of the CustomTest attribute
	 */
	inline void RemoveAttCustomTest(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttCustomTest);}

	/**
	 * @return Returns the value of the Dur attribute
	 */
	inline TPtrC AttDur() const {return iDescAtts[KSMILtimingeltAttDur]->Des();}

	/**
	 * @return Returns true if the Dur attribute is specified
	 */
	inline TBool IsAttDurSpecified() const {return (iDescAtts[KSMILtimingeltAttDur] != NULL);}

	/**
	 * Sets the value of the Dur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttDur, aAttVal);}

	/**
	 * Unsets the value of the Dur attribute
	 */
	inline void RemoveAttDur(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttDur);}

	/**
	 * @return Returns the value of the End attribute
	 */
	inline TPtrC AttEnd() const {return iDescAtts[KSMILtimingeltAttEnd]->Des();}

	/**
	 * @return Returns true if the End attribute is specified
	 */
	inline TBool IsAttEndSpecified() const {return (iDescAtts[KSMILtimingeltAttEnd] != NULL);}

	/**
	 * Sets the value of the End attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttEndL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttEnd, aAttVal);}

	/**
	 * Unsets the value of the End attribute
	 */
	inline void RemoveAttEnd(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttEnd);}

	/**
	 * @return Returns the value of the Endsync attribute
	 */
	inline TPtrC AttEndsync() const {return iDescAtts[KSMILtimingeltAttEndsync]->Des();}

	/**
	 * @return Returns true if the Endsync attribute is specified
	 */
	inline TBool IsAttEndsyncSpecified() const {return (iDescAtts[KSMILtimingeltAttEndsync] != NULL);}

	/**
	 * Sets the value of the Endsync attribute
	 * @param aAttVal value to set
	 * @return Returns KErrNone if successful
	 */
	inline TInt SetAttEndsyncL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttEndsync, aAttVal);}

	/**
	 * Unsets the value of the Endsync attribute
	 */
	inline void RemoveAttEndsync(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttEndsync);}

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
	inline TPtrC AttId() const {return iDescAtts[KSMILtimingeltAttId]->Des();}

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	inline TBool IsAttIdSpecified() const {return (iDescAtts[KSMILtimingeltAttId] != NULL);}

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttIdL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttId, aAttVal);}

	/**
	 * Unsets the value of the Id attribute
	 */
	inline void RemoveAttId(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttId);}

	/**
	 * @return Returns the value of the Max attribute
	 */
	inline TPtrC AttMax() const {return iDescAtts[KSMILtimingeltAttMax]->Des();}

	/**
	 * @return Returns true if the Max attribute is specified
	 */
	inline TBool IsAttMaxSpecified() const {return (iDescAtts[KSMILtimingeltAttMax] != NULL);}

	/**
	 * Sets the value of the Max attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMaxL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttMax, aAttVal);}

	/**
	 * Unsets the value of the Max attribute
	 */
	inline void RemoveAttMax(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttMax);}

	/**
	 * @return Returns the value of the Min attribute
	 */
	inline TPtrC AttMin() const {return iDescAtts[KSMILtimingeltAttMin]->Des();}

	/**
	 * @return Returns true if the Min attribute is specified
	 */
	inline TBool IsAttMinSpecified() const {return (iDescAtts[KSMILtimingeltAttMin] != NULL);}

	/**
	 * Sets the value of the Min attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttMinL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttMin, aAttVal);}

	/**
	 * Unsets the value of the Min attribute
	 */
	inline void RemoveAttMin(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttMin);}

	/**
	 * @return Returns the value of the RepeatCount attribute
	 */
	inline TPtrC AttRepeatCount() const {return iDescAtts[KSMILtimingeltAttRepeatCount]->Des();}

	/**
	 * @return Returns true if the RepeatCount attribute is specified
	 */
	inline TBool IsAttRepeatCountSpecified() const {return (iDescAtts[KSMILtimingeltAttRepeatCount] != NULL);}

	/**
	 * Sets the value of the RepeatCount attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatCountL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttRepeatCount, aAttVal);}

	/**
	 * Unsets the value of the RepeatCount attribute
	 */
	inline void RemoveAttRepeatCount(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttRepeatCount);}

	/**
	 * @return Returns the value of the RepeatDur attribute
	 */
	inline TPtrC AttRepeatDur() const {return iDescAtts[KSMILtimingeltAttRepeatDur]->Des();}

	/**
	 * @return Returns true if the RepeatDur attribute is specified
	 */
	inline TBool IsAttRepeatDurSpecified() const {return (iDescAtts[KSMILtimingeltAttRepeatDur] != NULL);}

	/**
	 * Sets the value of the RepeatDur attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttRepeatDurL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttRepeatDur, aAttVal);}

	/**
	 * Unsets the value of the RepeatDur attribute
	 */
	inline void RemoveAttRepeatDur(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttRepeatDur);}

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
	inline TPtrC AttSystemBitrate() const {return iDescAtts[KSMILtimingeltAttSystemBitrate]->Des();}

	/**
	 * @return Returns true if the SystemBitrate attribute is specified
	 */
	inline TBool IsAttSystemBitrateSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemBitrate] != NULL);}

	/**
	 * Sets the value of the SystemBitrate attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemBitrateL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemBitrate, aAttVal);}

	/**
	 * Unsets the value of the SystemBitrate attribute
	 */
	inline void RemoveAttSystemBitrate(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemBitrate);}

	/**
	 * @return Returns the value of the SystemCPU attribute
	 */
	inline TPtrC AttSystemCPU() const {return iDescAtts[KSMILtimingeltAttSystemCPU]->Des();}

	/**
	 * @return Returns true if the SystemCPU attribute is specified
	 */
	inline TBool IsAttSystemCPUSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemCPU] != NULL);}

	/**
	 * Sets the value of the SystemCPU attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemCPUL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemCPU, aAttVal);}

	/**
	 * Unsets the value of the SystemCPU attribute
	 */
	inline void RemoveAttSystemCPU(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemCPU);}

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
	inline TPtrC AttSystemComponent() const {return iDescAtts[KSMILtimingeltAttSystemComponent]->Des();}

	/**
	 * @return Returns true if the SystemComponent attribute is specified
	 */
	inline TBool IsAttSystemComponentSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemComponent] != NULL);}

	/**
	 * Sets the value of the SystemComponent attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemComponentL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemComponent, aAttVal);}

	/**
	 * Unsets the value of the SystemComponent attribute
	 */
	inline void RemoveAttSystemComponent(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemComponent);}

	/**
	 * @return Returns the value of the SystemLanguage attribute
	 */
	inline TPtrC AttSystemLanguage() const {return iDescAtts[KSMILtimingeltAttSystemLanguage]->Des();}

	/**
	 * @return Returns true if the SystemLanguage attribute is specified
	 */
	inline TBool IsAttSystemLanguageSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemLanguage] != NULL);}

	/**
	 * Sets the value of the SystemLanguage attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemLanguageL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemLanguage, aAttVal);}

	/**
	 * Unsets the value of the SystemLanguage attribute
	 */
	inline void RemoveAttSystemLanguage(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemLanguage);}

	/**
	 * @return Returns the value of the SystemOperatingSystem attribute
	 */
	inline TPtrC AttSystemOperatingSystem() const {return iDescAtts[KSMILtimingeltAttSystemOperatingSystem]->Des();}

	/**
	 * @return Returns true if the SystemOperatingSystem attribute is specified
	 */
	inline TBool IsAttSystemOperatingSystemSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemOperatingSystem] != NULL);}

	/**
	 * Sets the value of the SystemOperatingSystem attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemOperatingSystemL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemOperatingSystem, aAttVal);}

	/**
	 * Unsets the value of the SystemOperatingSystem attribute
	 */
	inline void RemoveAttSystemOperatingSystem(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemOperatingSystem);}

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
	inline TPtrC AttSystemRequired() const {return iDescAtts[KSMILtimingeltAttSystemRequired]->Des();}

	/**
	 * @return Returns true if the SystemRequired attribute is specified
	 */
	inline TBool IsAttSystemRequiredSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemRequired] != NULL);}

	/**
	 * Sets the value of the SystemRequired attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemRequiredL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemRequired, aAttVal);}

	/**
	 * Unsets the value of the SystemRequired attribute
	 */
	inline void RemoveAttSystemRequired(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemRequired);}

	/**
	 * @return Returns the value of the SystemScreenDepth attribute
	 */
	inline TPtrC AttSystemScreenDepth() const {return iDescAtts[KSMILtimingeltAttSystemScreenDepth]->Des();}

	/**
	 * @return Returns true if the SystemScreenDepth attribute is specified
	 */
	inline TBool IsAttSystemScreenDepthSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemScreenDepth] != NULL);}

	/**
	 * Sets the value of the SystemScreenDepth attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemScreenDepthL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemScreenDepth, aAttVal);}

	/**
	 * Unsets the value of the SystemScreenDepth attribute
	 */
	inline void RemoveAttSystemScreenDepth(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemScreenDepth);}

	/**
	 * @return Returns the value of the SystemScreenSize attribute
	 */
	inline TPtrC AttSystemScreenSize() const {return iDescAtts[KSMILtimingeltAttSystemScreenSize]->Des();}

	/**
	 * @return Returns true if the SystemScreenSize attribute is specified
	 */
	inline TBool IsAttSystemScreenSizeSpecified() const {return (iDescAtts[KSMILtimingeltAttSystemScreenSize] != NULL);}

	/**
	 * Sets the value of the SystemScreenSize attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystemScreenSizeL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemScreenSize, aAttVal);}

	/**
	 * Unsets the value of the SystemScreenSize attribute
	 */
	inline void RemoveAttSystemScreenSize(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystemScreenSize);}

	/**
	 * @return Returns the value of the System_bitrate attribute
	 */
	inline TPtrC AttSystem_bitrate() const {return iDescAtts[KSMILtimingeltAttSystem_bitrate]->Des();}

	/**
	 * @return Returns true if the System_bitrate attribute is specified
	 */
	inline TBool IsAttSystem_bitrateSpecified() const {return (iDescAtts[KSMILtimingeltAttSystem_bitrate] != NULL);}

	/**
	 * Sets the value of the System_bitrate attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_bitrateL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_bitrate, aAttVal);}

	/**
	 * Unsets the value of the System_bitrate attribute
	 */
	inline void RemoveAttSystem_bitrate(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_bitrate);}

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
	inline void RemoveAttSystem_captions() {iAttSystem_captions = EAttSystem_captionsUndefined;}

	/**
	 * @return Returns the value of the System_language attribute
	 */
	inline TPtrC AttSystem_language() const {return iDescAtts[KSMILtimingeltAttSystem_language]->Des();}

	/**
	 * @return Returns true if the System_language attribute is specified
	 */
	inline TBool IsAttSystem_languageSpecified() const {return (iDescAtts[KSMILtimingeltAttSystem_language] != NULL);}

	/**
	 * Sets the value of the System_language attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_languageL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_language, aAttVal);}

	/**
	 * Unsets the value of the System_language attribute
	 */
	inline void RemoveAttSystem_language(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_language);}

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
	inline TPtrC AttSystem_required() const {return iDescAtts[KSMILtimingeltAttSystem_required]->Des();}

	/**
	 * @return Returns true if the System_required attribute is specified
	 */
	inline TBool IsAttSystem_requiredSpecified() const {return (iDescAtts[KSMILtimingeltAttSystem_required] != NULL);}

	/**
	 * Sets the value of the System_required attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_requiredL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_required, aAttVal);}

	/**
	 * Unsets the value of the System_required attribute
	 */
	inline void RemoveAttSystem_required(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_required);}

	/**
	 * @return Returns the value of the System_screen_depth attribute
	 */
	inline TPtrC AttSystem_screen_depth() const {return iDescAtts[KSMILtimingeltAttSystem_screen_depth]->Des();}

	/**
	 * @return Returns true if the System_screen_depth attribute is specified
	 */
	inline TBool IsAttSystem_screen_depthSpecified() const {return (iDescAtts[KSMILtimingeltAttSystem_screen_depth] != NULL);}

	/**
	 * Sets the value of the System_screen_depth attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_screen_depthL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_screen_depth, aAttVal);}

	/**
	 * Unsets the value of the System_screen_depth attribute
	 */
	inline void RemoveAttSystem_screen_depth(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_screen_depth);}

	/**
	 * @return Returns the value of the System_screen_size attribute
	 */
	inline TPtrC AttSystem_screen_size() const {return iDescAtts[KSMILtimingeltAttSystem_screen_size]->Des();}

	/**
	 * @return Returns true if the System_screen_size attribute is specified
	 */
	inline TBool IsAttSystem_screen_sizeSpecified() const {return (iDescAtts[KSMILtimingeltAttSystem_screen_size] != NULL);}

	/**
	 * Sets the value of the System_screen_size attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttSystem_screen_sizeL( const TDesC& aAttVal ){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_screen_size, aAttVal);}

	/**
	 * Unsets the value of the System_screen_size attribute
	 */
	inline void RemoveAttSystem_screen_size(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttSystem_screen_size);}

	/**
	 * @return Returns the value of the Title attribute
	 */
	inline TPtrC AttTitle() const {return iDescAtts[KSMILtimingeltAttTitle]->Des();}

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	inline TBool IsAttTitleSpecified() const {return (iDescAtts[KSMILtimingeltAttTitle] != NULL);}

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttTitleL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttTitle, aAttVal);}

	/**
	 * Unsets the value of the Title attribute
	 */
	inline void RemoveAttTitle(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttTitle);}

	/**
	 * @return Returns the value of the XMLLang attribute
	 */
	inline TPtrC AttXMLLang() const {return iDescAtts[KSMILtimingeltAttXMLLang]->Des();}

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	inline TBool IsAttXMLLangSpecified() const {return (iDescAtts[KSMILtimingeltAttXMLLang] != NULL);}

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	inline TInt SetAttXMLLangL(const TDesC& aAttVal){return SetDescAttL(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttXMLLang, aAttVal);}

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	inline void RemoveAttXMLLang(){RemoveDescAtt(iDescAtts, KSMILtimingeltAttNameCount, KSMILtimingeltAttXMLLang);}

protected:
	/**
	 * Check the immediate children of this element - i.e. the first level of children only
	 * The default implementation returns true - derived classes can override with
	 * DTD-specific checks.
	 * @returns True if immediate children are valid
	 */
	virtual TBool CheckImmediateChildren();

private:
	// All descriptor-based attributes are stored in an array.
	// The array is fixed-size for the class and is indexed based on 
	// alphabetical order of attribute name
	HBufC *iDescAtts[KSMILtimingeltAttNameCount];				///< Array of descriptor attributes

	//Member variables for element attributes
	// These are the Enum-based attributes which are handled in a hard-wired way
	TDOMAttFillType iAttFill;						///< Member variable for the Fill attribute
	TDOMAttSystemAudioDescType iAttSystemAudioDesc;	///< Member variable for the SystemAudioDesc attribute
	TDOMAttSystemCaptionsType iAttSystemCaptions;	///< Member variable for the SystemCaptions attribute
	TDOMAttSystemOverdubOrSubtitleType iAttSystemOverdubOrSubtitle;	///< Member variable for the SystemOverdubOrSubtitle attribute
	TDOMAttSystem_captionsType iAttSystem_captions;	///< Member variable for the System_captions attribute
	TDOMAttSystem_overdub_or_captionType iAttSystem_overdub_or_caption;	///< Member variable for the System_overdub_or_caption attribute
	};

#endif

// End of File