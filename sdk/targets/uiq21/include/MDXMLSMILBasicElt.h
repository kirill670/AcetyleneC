// MDXMLSMILhead.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file MDXMLSMILBasicElt.h
 * This file contains the declaration of a base class with attributes common to all
 * SMIL elements.
 */

#ifndef __MDXMLSMILBASICELT_H__
#define __MDXMLSMILBASICELT_H__

#include <e32base.h>

// forward references
class CMDXMLEntityConverter;
class CMDXMLComposer;
class CMDXMLSMILregion;
class CMDXMLSMILpar;
class CMDXMLSMILseq;
class CMDXMLSMILref;
class CMDXMLSMILaudio;
class CMDXMLSMILimg;
class CMDXMLSMILtext;
class CMDXMLSMILvideo;
class CMDXMLSMILtextstream;
class CMDXMLSMILanimation;

class CMDXMLSMILBasicElt : public CMDXMLElement
{
public:
	IMPORT_C virtual ~CMDXMLSMILBasicElt();

protected:
	/**
	 * Constructor
	 * @param aCanHaveChildren Can the element have child elements
	 * @param aOwnerDocument Pointer to the document at the root of the DOM tree
	 */
	CMDXMLSMILBasicElt( TBool aCanHaveChildren, CMDXMLDocument* aOwnerDocument );

public:
	//Access functions for element attributes

	/**
	 * @return Returns a pointer to the first region child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILregion* FirstregionChild();

	/**
	 * @return Returns a pointer to the last region child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILregion* LastregionChild();

	/**
	 * @return Returns a pointer to the first par child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILpar* FirstparChild();

	/**
	 * @return Returns a pointer to the last par child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILpar* LastparChild();

	/**
	 * @return Returns a pointer to the first seq child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILseq* FirstseqChild();

	/**
	 * @return Returns a pointer to the last seq child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILseq* LastseqChild();

	/**
	 * @return Returns a pointer to the first ref child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILref* FirstrefChild();

	/**
	 * @return Returns a pointer to the last ref child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILref* LastrefChild();

	/**
	 * @return Returns a pointer to the first audio child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILaudio* FirstaudioChild();

	/**
	 * @return Returns a pointer to the last audio child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILaudio* LastaudioChild();

	/**
	 * @return Returns a pointer to the first img child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILimg* FirstimgChild();

	/**
	 * @return Returns a pointer to the last img child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILimg* LastimgChild();

	/**
	 * @return Returns a pointer to the first text child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtext* FirsttextChild();

	/**
	 * @return Returns a pointer to the last text child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtext* LasttextChild();

	/**
	 * @return Returns a pointer to the first video child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILvideo* FirstvideoChild();

	/**
	 * @return Returns a pointer to the last video child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILvideo* LastvideoChild();

	/**
	 * @return Returns a pointer to the first textstream child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtextstream* FirsttextstreamChild();

	/**
	 * @return Returns a pointer to the last textstream child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILtextstream* LasttextstreamChild();

	/**
	 * @return Returns a pointer to the first animation child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILanimation* FirstanimationChild();

	/**
	 * @return Returns a pointer to the last animation child if any, otherwise returns NULL
	 */
	IMPORT_C CMDXMLSMILanimation* LastanimationChild();

	// The following routines are presented for SC - Ideally they should not be used
	// As the versions supplied by more derived classes are more efficient.
	/**
	 * @return Returns the value of the Class attribute
	 */
	IMPORT_C TPtrC AttClass() const;

	/**
	 * @return Returns true if the Class attribute is specified
	 */
	IMPORT_C TBool IsAttClassSpecified() const;

	/**
	 * Sets the value of the Class attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C TInt SetAttClassL(const TDesC& aAttVal);

	/**
	 * Unsets the value of the Class attribute
	 */
	IMPORT_C void RemoveAttClass();

	/**
	 * @return Returns the value of the Id attribute
	 */
	IMPORT_C TPtrC AttId() const;

	/**
	 * @return Returns true if the Id attribute is specified
	 */
	IMPORT_C TBool IsAttIdSpecified() const;

	/**
	 * Sets the value of the Id attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C TInt SetAttIdL(const TDesC& aAttVal);

	/**
	 * Unsets the value of the Id attribute
	 */
	IMPORT_C void RemoveAttId();

	/**
	 * @return Returns the value of the Title attribute
	 */
	IMPORT_C TPtrC AttTitle() const;

	/**
	 * @return Returns true if the Title attribute is specified
	 */
	IMPORT_C TBool IsAttTitleSpecified() const;

	/**
	 * Sets the value of the Title attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C TInt SetAttTitleL(const TDesC& aAttVal);

	/**
	 * Unsets the value of the Title attribute
	 */
	IMPORT_C void RemoveAttTitle();

	/**
	 * @return Returns the value of the XMLLang attribute
	 */
	IMPORT_C TPtrC AttXMLLang() const;

	/**
	 * @return Returns true if the XMLLang attribute is specified
	 */
	IMPORT_C TBool IsAttXMLLangSpecified() const;

	/**
	 * Sets the value of the XMLLang attribute
	 * @param aAttVal value to set
	 * @exception Can Leave due to OOM
	 */
	IMPORT_C TInt SetAttXMLLangL(const TDesC& aAttVal);

	/**
	 * Unsets the value of the XMLLang attribute
	 */
	IMPORT_C void RemoveAttXMLLang();

protected:
};

#endif
