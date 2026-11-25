/*
 * =========================================================================
 *  Name     : SenBaseElement.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenBaseElement.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.10 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_BASE_ELEMENT_H
#define SEN_BASE_ELEMENT_H

#include <s32mem.h>
#include <MXMLAttributes.h>

#include <SenElement.h>
#include <SenNameSpace.h>
#include <SenBaseAttribute.h>


class CSenBaseElement : public CSenElement
    {
public:
    IMPORT_C static CSenBaseElement* NewL(const TDesC& aLocalName);
    IMPORT_C static CSenBaseElement* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName
        );
    IMPORT_C static CSenBaseElement* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    /**
     *  Does not take ownership.
     */
    IMPORT_C static CSenBaseElement* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );

    IMPORT_C static CSenBaseElement* NewL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs,
        CSenElement& aParent
        );

    IMPORT_C virtual ~CSenBaseElement();

protected:
    IMPORT_C CSenBaseElement();

    IMPORT_C void BaseConstructL(const TDesC& aLocalName);
    IMPORT_C void BaseConstructL(const TDesC& aNsUri, const TDesC& aLocalName);
    IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    /**
     *  Does not take ownership.
     */
    IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        );

    IMPORT_C void BaseConstructL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs,
        CSenElement& aParent
        );

public:
    // From CSenElement
    IMPORT_C virtual const TDesC& LocalName() const;
    IMPORT_C virtual const TDesC& NsUri() const;
    IMPORT_C virtual const TDesC& NsPrefix() const;

	IMPORT_C virtual void SetPrefix(const TDesC& aPrefix);

    IMPORT_C virtual TBool HasContent() const;
    IMPORT_C virtual TPtrC Content() const;

    IMPORT_C const virtual TPtrC SetContentL(const TDesC& aContent);
    IMPORT_C virtual RWriteStream& ContentWriteStream();
    IMPORT_C virtual HBufC8* ContentUtf8L() const;

	IMPORT_C virtual void SetNameSpace(const TDesC& aNsUri);
	IMPORT_C virtual void SetNameSpace(const TDesC& aNsPrefix, const TDesC& aNsUri);
	IMPORT_C virtual const CSenNameSpace* AddNameSpaceL(CSenNameSpace& aNewNameSpace, TBool aCheckInParent);
	IMPORT_C virtual const CSenNameSpace* AddNameSpaceL(TDesC& aPrefix, TDesC& aUri);
	IMPORT_C virtual const CSenNameSpace* NameSpace();
	IMPORT_C virtual const CSenNameSpace* NameSpace(const TDesC& aNsPrefix);
	IMPORT_C virtual const CSenNameSpace* NameSpace(const TDesC& aNsPrefix, const TBool aCheckInParent);
	IMPORT_C virtual const CSenNameSpace* NameSpace(const TDesC& aNsPrefix, const TDesC& aUri);

    IMPORT_C virtual RPointerArray<CSenElement>& ElementsL();
	IMPORT_C virtual RPointerArray<CSenBaseAttribute>& AttributesL();
	IMPORT_C virtual RPointerArray<CSenNameSpace>& NameSpacesL();

    IMPORT_C virtual const TDesC* AttrValue(const TDesC& aName);
    IMPORT_C virtual void AddAttrL(const TDesC& aName, const TDesC& aValue);

    IMPORT_C virtual CSenElement* Parent();
    IMPORT_C virtual CSenElement* SetParent(CSenElement* apParent);
    IMPORT_C virtual MSenElement& Root();

    IMPORT_C virtual CSenElement* Element(const TDesC& aLocalName);
    IMPORT_C virtual CSenElement* Element(const TDesC& aNsUri, const TDesC& aLocalName);

	IMPORT_C virtual CSenElement* CreateElementL(const TDesC& aNsPrefix, const TDesC& aLocalName);
	
	IMPORT_C virtual CSenElement& InsertElementL(CSenElement& aElement, const CSenElement& aBeforeElement);

    IMPORT_C virtual CSenElement& AddElementL(CSenElement& aElement);
    IMPORT_C virtual CSenElement& AddElementL(const TDesC& aNsUri, const TDesC& aLocalName);
    IMPORT_C virtual CSenElement& AddElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        );
    IMPORT_C virtual CSenElement& AddElementL(const TDesC& aLocalName);

    IMPORT_C virtual CSenElement* RemoveElement(CSenElement& aElement);
    IMPORT_C virtual CSenElement* RemoveElement(const TDesC& aNsUri, const TDesC& aLocalName);
    IMPORT_C virtual CSenElement* RemoveElement(const TDesC& aLocalName);

    IMPORT_C virtual CSenElement* ReplaceElementL(CSenElement& aElement);

    IMPORT_C virtual HBufC8* AsXmlUtf8L();
    IMPORT_C virtual HBufC* AsXmlL();
    IMPORT_C virtual void WriteTo16L(RWriteStream& aWriteStream);
	IMPORT_C virtual void WriteNameSpacesTo16L(RWriteStream& aWriteStream);
    IMPORT_C virtual MSenElement* AsElement();
	IMPORT_C void CopyFromL(CSenElement& aSource) ;

	IMPORT_C virtual CSenElement* Detach();

public:
    /**
     *  Get the value of the attribute or return KNullDesC if not found.
     */
    IMPORT_C static TPtrC AttrValue(MXMLAttributes* apAttrs, const TDesC& aAttrName);

    /**
     *  Get a newly allocated copy of the attribute or return NULL if not found.
     */
    IMPORT_C static HBufC* AllocAttrValueL(MXMLAttributes* apAttrs, const TDesC& aAttrName);

    /**
     *  Does not take ownership.
     */
    IMPORT_C virtual void SetAttributesL(MXMLAttributes* apAttrs);

	/**
	 * (Re-) Set the name and namespace of this Element. The element will be given 
	 * the localName in the the given namespace. A prefix will will be computed from the
	 * qaulified name.
	 * 
	 * This method should be used with care and is mainly intended for 
	 * protected use in implementations.
	 * 
	 * @param namespaceURI
	 * @param localName
	 * @param qName
	 */
	IMPORT_C virtual void Set(const TDesC& aNsUri, const TDesC& aLocalName, const TDesC& aQName);

	IMPORT_C virtual void AddAttributesL(MXMLAttributes* apAttrs);



protected:

    /**
     *  @return the 1st attr with the name, or NULL. Owner retains ownership.
     */
    IMPORT_C virtual CSenBaseAttribute* FindAttr(const TDesC& aName);
    IMPORT_C virtual TInt IndexOfElement(const TDesC& aNsUri, const TDesC& aLocalName) const;

    IMPORT_C virtual void WriteAttrsTo16L(RWriteStream& aWriteStream);
    IMPORT_C virtual void WriteAttrTo16L(RWriteStream& aWriteStream, const TDesC& aName, const TDesC& aValue);
    IMPORT_C virtual void WriteElementsTo16L(RWriteStream& aWriteStream);
    IMPORT_C virtual void WriteContentTo16L(RWriteStream& aWriteStream);

	// @return value of the attribute as string (TDesC&)
	IMPORT_C virtual const TDesC& AddAttributeL(const TDesC& aQName, 
												const TDesC& aLocalName, 
												const TDesC& aValue);

	// @return value of the attribute as string (TDesC&)
	IMPORT_C virtual const TDesC& AddAttributeL(const TDesC& aAttrName, 
												const TDesC& aValue);


	// takes the ownership of the given attribute
	// @return value of the attribute as string (TDesC&)
	IMPORT_C const TDesC& AddAttributeL(CSenBaseAttribute* apAttribute);



    IMPORT_C virtual void AllocContentBufL();

    IMPORT_C virtual TPtrC WriteToBuf16L(CBufBase& aBuf);

private:
	void AddNameSpaceMissingFrom(RPointerArray<CSenNameSpace>& aNamespaces);

private:
    HBufC* ipLocalName; // Owned
    HBufC* ipNsUri;     // Owned  TODO: RString?
    //HBufC* ipNsPrefix;  // Owned

    CBufFlat* ipContentBuf; // Owned
    RBufWriteStream iContentWriteStream;

    RPointerArray<CSenBaseAttribute> iAttrs;    // Elements owned
    RPointerArray<CSenElement> iElements;  // Elements owned
	RPointerArray<CSenNameSpace> iNameSpaces; // Elements owned
    CSenElement*	ipParent; // Not owned
	CSenNameSpace*	ipNameSpace;	// owned
    };

#endif // SEN_BASE_ELEMENT_H
