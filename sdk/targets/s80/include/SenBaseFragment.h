/*
 * =========================================================================
 *  Name     : SenBaseFragment.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenBaseFragment.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.14 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_BASE_FRAGMENT_H
#define SEN_BASE_FRAGMENT_H

#include <s32mem.h>

#include <MXMLContentHandler.h>

//#include <SenContentSaver.h>
#include <SenElement.h>
#include <SenFragment.h>


const TInt KStateNotSet = -1;
const TInt KStateIgnore =  0;
const TInt KStateSave	=  1;
const TInt KStateResume =  2;

class CSenBaseFragment :
	public CSenFragment,
    public MXMLContentHandler
    {
public:
    IMPORT_C static CSenBaseFragment* NewL(const TDesC& aLocalName);
    IMPORT_C static CSenBaseFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName
        );
    IMPORT_C static CSenBaseFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    IMPORT_C static CSenBaseFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs
        );

	IMPORT_C static CSenBaseFragment* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* aAttrs,
		CSenElement& aParent
        );

    IMPORT_C virtual ~CSenBaseFragment();

protected:
    IMPORT_C CSenBaseFragment();

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

    /**
     *  This method will panic if element has not been initialized for any
     *  reason. Ownership is not transferred.
     */
    IMPORT_C virtual CSenElement& AsElement();
    
    /************************************************************************
    * Ownership is transferred to the caller                               *
    ************************************************************************/
    IMPORT_C virtual CSenElement* ExtractElement();

    IMPORT_C virtual RXMLReader Reader();
    IMPORT_C virtual void SetReader(RXMLReader aReader);

    IMPORT_C virtual void ParseL(const TDesC8& aBuf);
    IMPORT_C virtual TInt BuildFrom(const TDesC& aBuf);

    IMPORT_C virtual void DelegateParsingL(MSenFragment& aDelegate);
    IMPORT_C virtual void DelegateParsingL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
		const TDesC& aQName,
        MXMLAttributes* aAttrs
        );
    IMPORT_C virtual void ParseWithL(RXMLReader aReader);

	// depracated: only to ensure bc
    IMPORT_C virtual void RegisterNamespaceL(const TDesC& aNsUri, const TDesC& aNsPrefix);

    IMPORT_C virtual void SetOwner(MSenFragment& aFragment);
    IMPORT_C virtual void ResumeParsingFromL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );

	IMPORT_C virtual CSenNameSpace* NameSpace(const TDesC& aPrefix);
	IMPORT_C virtual void EnsureNameSpace(const TDesC& aPrefix);
	IMPORT_C virtual CSenBaseFragment* Detach();
	IMPORT_C virtual void SaveNameSpacesL(MXMLAttributes* aAttrs, TBool aEnsure);

    /**
     *  Default implementation does nothing. Subclasses can override.
     *  Does not take ownership.
     */
    IMPORT_C virtual void SetAttributesL(MXMLAttributes* aAttrs);

public:
    // Convenience methods work on element
    IMPORT_C virtual void ResetContent();

    /**
     *  @return AsElement()->Content()
     */
    IMPORT_C virtual TPtrC Content();

    /**
     *  @return AsElement()->AsXmlL()
     */
    IMPORT_C virtual HBufC* AsXmlL();

    /**
     *  @return AsElement()->AsXmlLUtf8L()
     */
	IMPORT_C virtual HBufC8* AsXmlUtf8L();

    /**
     *  Invoke AsElement()->WriteTo16L(aWs);
     */
    IMPORT_C virtual void WriteTo16L(RWriteStream& aWs);

public: // from MSenFragment and CSenFragment
    IMPORT_C void WriteStartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );
    IMPORT_C void WriteEndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );

protected:
    // These methods are invoked and TRAP-ped by their non-leaving variant.
    IMPORT_C virtual void StartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );
    IMPORT_C virtual void EndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    IMPORT_C virtual void CharactersL(
        const TDesC& aChars,
        TInt aStart,
        TInt aLength
        );

	IMPORT_C MSenElement& SetContentOfL(const TDesC& aLocalName, const TDesC &aContent);
	IMPORT_C const TPtrC ContentOf(const TDesC& aLocalName);

private:
    // From MXMLContentHandler, cannot be overridden
    IMPORT_C virtual TInt StartDocument();
    IMPORT_C virtual TInt EndDocument();
    IMPORT_C virtual TInt StartElement(
        TDesC& aNsUri,
        TDesC& aLocalName,
        TDesC& aQName,
        MXMLAttributes* apAttrs
        );
    IMPORT_C virtual TInt EndElement(
        TDesC& aNsUri,
        TDesC& aLocalName,
        TDesC& aQName
        );
    IMPORT_C virtual TInt Charecters(
        TDesC& aChars,
        TInt aStart,
        TInt aLength
        );

protected:
    IMPORT_C virtual void AllocContentSaverL();

protected:
    TInt iState;

protected:
    CSenElement* ipElement;                 // Owned
    //CSenContentSaver* ipContentSaver;       // Owned

	// test
    RXMLReader iXmlReader;                  // Not owned (no CreateL/Destroy)

    MSenFragment* ipOwner;                  // Not owned

private:
    CSenFragment* ipDelegate;               // Owned

	// to hold namespaces that are referred to from within the content
	// but were not declared within this BaseFragment.
	RPointerArray<CSenNameSpace> iNameSpaces;	// Not owned
	
	// to hold prefixes that have been declared within the scope of the BaseFragment
	RPointerArray<HBufC> iPrefixes;				// owned

	CBufFlat* ipContentWithNamespaces;

	TBool hasContentWriteStream;
	RWriteStream iWs;

	TBool iElementOwned; // indicates whether or not ipElement member is an owned object
    };

#endif //SEN_BASE_FRAGMENT_H
