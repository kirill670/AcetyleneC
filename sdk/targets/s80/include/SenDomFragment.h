/*
 * =========================================================================
 *  Name     : SenDomFragment.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenDomFragment.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.12 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_DOM_FRAGMENT_H
#define SEN_DOM_FRAGMENT_H

#include <SenBaseFragment.h>

// class declaration
class CSenDomFragment : 
	public CSenBaseFragment
    {
public:
	/*************************************************************************
	* Use this only for parsing new fragments etc. Constructing DomFragments *
	* for other use should be done with at least Localname parameter         *
	*************************************************************************/
	IMPORT_C static CSenDomFragment* NewL();
    IMPORT_C static CSenDomFragment* NewL(const TDesC& aLocalName);
    IMPORT_C static CSenDomFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName
        );
    IMPORT_C static CSenDomFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    IMPORT_C static CSenDomFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs
        );

    IMPORT_C static CSenDomFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs,
		CSenElement& aParent
        );

    IMPORT_C virtual ~CSenDomFragment();

protected:
    IMPORT_C CSenDomFragment();

    IMPORT_C void BaseConstructL(const TDesC& aLocalName);
    IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName
        );
    IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs
        );

	IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs,
		CSenElement& aParent
        );

    IMPORT_C void BaseConstructL(RXMLReader aReader);

public:
    // From CSenFragment

	IMPORT_C void ResumeParsingFromL( // IOP
		const TDesC& aNsUri,
		const TDesC& aLocalName,
		const TDesC& aQName);

		/**
     *  This method will panic if element has not been initialized for any
     *  reason.
     */
    IMPORT_C virtual void ParseWithL(RXMLReader aReader);

	/**
     *  Default implementation does nothing. Subclasses can override.
     *  Does not take ownership.
     */
    IMPORT_C virtual void SetAttributesL(MXMLAttributes* aAttrs);

    IMPORT_C virtual void CharactersL(const TDesC& aChars,
									  TInt aStart,
									  TInt aLength);

public: // Deprecated methods, just for BC:
	IMPORT_C virtual void ExpandL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        MXMLAttributes* apAttrs
        );

public:
	IMPORT_C virtual void ExpandL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
		const TDesC& aQName,
        MXMLAttributes* apAttrs
        );



protected:
    // These methods are invoked and TRAP-ped by their non-leaving variant.
    IMPORT_C virtual void StartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );

protected:	
	// override content writing from CSenBaseFragment to do _nothing_
	// in DOM fragment..
	IMPORT_C void WriteStartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );
	// override content writing from CSenBaseFragment to do _nothing_
	// in DOM fragment..
    IMPORT_C void WriteEndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );


protected: // data
	CSenDomFragment* ipDomDelegate;

	}; // end of class declaration

#endif //SEN_DOM_FRAGMENT_H

// end of file