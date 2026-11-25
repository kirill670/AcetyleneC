/*
 * =========================================================================
 *  Name     : SenElement.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenElement.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.7 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_ELEMENT_H
#define SEN_ELEMENT_H

#include <e32base.h>
#include <s32strm.h>

#include <MXMLAttributes.h>

#include <MSenElement.h>

class CSenElement : public CBase, public MSenElement
    {
public:
    /**
     *  @return KNullDesC if not set (argumentless constructor).
     */
    virtual const TDesC& LocalName() const = 0;

    /**
     *  @return KNullDesC if not set.
     */
    virtual const TDesC& NsUri() const = 0;

	virtual void SetNameSpace(const TDesC& aNsUri) = 0;

	virtual void SetNameSpace(const TDesC& aNsPrefix, const TDesC& aNsUri) = 0;

	virtual const CSenNameSpace* AddNameSpaceL(TDesC& aPrefix, TDesC& aUri) = 0;

	virtual const CSenNameSpace* NameSpace() = 0;

	/**
	 * Return the Namespace that is declared for the given prefix
	 * within the scope of this Element. If no such prefix is
	 * declared return null. 
	 * 
	 * @param prefix
	 * @return the found Namespace
	 */
	virtual const CSenNameSpace* NameSpace(const TDesC& aNsPrefix) = 0;

	virtual const CSenNameSpace* NameSpace(const TDesC& aNsPrefix, const TDesC& aUri) = 0;

	virtual const CSenNameSpace* NameSpace(const TDesC& aNsPrefix, const TBool aCheckInParent) = 0;
    
	/**
     *  @return KNullDesC if not set.
     */
    virtual const TDesC& NsPrefix() const = 0;

public:
    virtual TBool HasContent() const = 0;

    /**
     *  @return KNullDesC if empty.
     */
    virtual TPtrC Content() const = 0;

    /**
     *  @return NULL if empty.
     */
    virtual HBufC8* ContentUtf8L() const = 0;

    /**
     *  @return KNullDesC if empty.
     */
    virtual const TPtrC SetContentL(const TDesC& aContent) = 0;

    /**
     *  Writing 16-bit string to the returned stream will be appended
     *  to the content.
     */
    virtual RWriteStream& ContentWriteStream() = 0;

public:
    /**
     *  @return an array of child elements. This is an empty array if there
     *          are no children. Any modifications made on the returned array
     *          modify the element object.
     */
    virtual RPointerArray<CSenElement>& ElementsL() = 0;

public:
	/**
	 * Add a namespace declaration. 
	 * If this element (or its parent if "checkWithParent" is true) already has a 
	 * Namespace with the same prefix and URI the given
	 * Namespace is not added.
	 * 
	 * @param ns
	 * @param checkWithParent
	 * @return the added Namespace, or the equivalent pre-exisiting one.
	 */
	virtual const CSenNameSpace* AddNameSpaceL(CSenNameSpace& aNewNameSpace, TBool aCheckInParent) = 0;

    /**
     *  @return the value of the attribute, or NULL if not found.
     */
    virtual const TDesC* AttrValue(const TDesC& aName) = 0;

    /**
     *  Add (if new) or replace (if exists) the value for the attribute.
     */
    virtual void AddAttrL(const TDesC& aName, const TDesC& aValue) = 0;

	virtual RPointerArray<CSenBaseAttribute>& AttributesL() = 0;
	virtual RPointerArray<CSenNameSpace>& NameSpacesL() = 0;
	
public:
    /**
     *  @return NULL if no parent.
     */
    virtual CSenElement* Parent() = 0;

    /**
     *  Accepts NULL.
     */
    virtual CSenElement* SetParent(CSenElement* apParent) = 0;

	/**
	 * Detach the element from its parent. 
	 * If the element, or one of its children, is dependent
	 * on a namespace declared in the scope of the parent
	 * copy those namespace declarations to this element.
	 * 
	 * @return this Element
	 */
	virtual CSenElement* Detach() = 0;

    /**
     *  @return the root of the tree.
     */
    virtual MSenElement& Root() = 0;

public:
    /**
     *  Assumes that namespace is the same as ours.
     *  @return NULL if child is not found.
     */
    virtual CSenElement* Element(const TDesC& aLocalName) = 0;

    /**
     *  @return NULL if child is not found.
     */
    virtual CSenElement* Element(const TDesC& aNsUri, const TDesC& aLocalName) = 0;

public:
	/**
	 * Create a new element ready for adding or insertion.
	 * If the given namespace prefix is not declared yet
	 * the element will not be created and null will be returned.
	 *
	 * @param prefix
	 * @param localName
	 * @return the new Element
	 */
	virtual CSenElement* CreateElementL(const TDesC& aNsPrefix, const TDesC& aLocalName) = 0;
	
	/**
	 * Insert an Element into the list of children elements
	 * such that the inserted Element is placed right before
	 * the beforeElement 
	 * 
	 * @param insertedElement
	 * @param beforeElement
	 * @return the inserted Element
	 */
	virtual CSenElement& InsertElementL(CSenElement& aInsertedElement, const CSenElement& aBeforeElement) = 0;

    virtual CSenElement& AddElementL(CSenElement& aElement) = 0;
    virtual CSenElement& AddElementL(const TDesC& aNsUri, const TDesC& aLocalName) = 0;
    virtual CSenElement& AddElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        ) = 0;
    virtual CSenElement& AddElementL(const TDesC& aLocalName) = 0;

    /**
     *  Remove the element.
     *  @return if NULL, nothing has been removed. If non-NULL, it has been
     *          removed, and the caller takes ownership.
     */
    virtual CSenElement* RemoveElement(CSenElement& aElement) = 0;

    /**
     *  Remove the element.
     *  @return if NULL, nothing has been removed. If non-NULL, it has been
     *          removed, and the caller takes ownership.
     */
    virtual CSenElement* RemoveElement(const TDesC& aNsUri, const TDesC& aLocalName) = 0;

    /**
     *  Remove the element.
     *  @return if NULL, nothing has been removed. If non-NULL, it has been
     *          removed, and the caller takes ownership.
     */
    virtual CSenElement* RemoveElement(const TDesC& aLocalName) = 0;

    /**
     *  Replace an element.
     *  @return the old element, if any; NULL otherwise. 
	 *  Caller takes ownership of the returned object.
     */
    virtual CSenElement* ReplaceElementL(CSenElement& aElement) = 0;

public:
    virtual HBufC8* AsXmlUtf8L() = 0;
    virtual HBufC* AsXmlL() = 0;
    virtual void WriteTo16L(RWriteStream& aWriteStream) = 0;

public:
    /**
     *  @return the current object as element.
     *          Retains ownership.
     */
    virtual MSenElement* AsElement() = 0;
	
	virtual void CopyFromL(CSenElement& aSource) = 0;

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
	virtual void Set(const TDesC& aNamespaceURI, const TDesC& aLocalName, const TDesC& aQName) = 0;

	virtual void AddAttributesL(MXMLAttributes* apAttrs) = 0;
    };

#endif //SEN_ELEMENT_H
