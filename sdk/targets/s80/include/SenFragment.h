/*
 * =========================================================================
 *  Name     : SenFragment.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenFragment.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.4 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_FRAGMENT_H
#define SEN_FRAGMENT_H

#include <e32base.h>
#include <s32strm.h>

#include <MXMLAttributes.h>
#include <RXMLReader.h>

#include <SenElement.h>
#include <MSenFragment.h>

class CSenFragment : public CBase, public MSenFragment
    {
public:
    /**
     *  @return the current object as element.
     *          Retains ownership.
     */
    virtual CSenElement& AsElement() = 0;

    /**
     *  @return the current object as element. May return NULL.
     *          Caller takes ownership.
	 * 
	 * Note(!): the return value (CSenElement) STRONGLY suggests that
	 * subclasses INHERIT CSenFragment in order properly comply the
	 * requirement of the ExtractElement() implementation.
     */
    virtual CSenElement* ExtractElement() = 0;

public:
    virtual void SetReader(RXMLReader aReader) = 0;
    virtual RXMLReader Reader() = 0;

    /**
     *  SetReader() must be called before this method can be used.
     */
    virtual void ParseL(const TDesC8& aBuf) = 0;

    /**
     *  Same as ParseL() except that it takes 16-bit input and does silently
     *  fail in case of all errors.
     *  SetReader() must be called before this method can be used.
     *
     *  @return error code, if any.
     */
    virtual TInt BuildFrom(const TDesC& aBuf) = 0;

public:
    /**
     *  Let the delegate MSenFragment handle with SAX events.
     *  "this" MSenFragment is made the owner of the delegate and
     *  the delegate is expected to make this MSenFragment the receiver
     *  of SAX events once it has seen the end element for itself.
     */
    virtual void DelegateParsingL(MSenFragment& aDelegate) = 0;

    /**
     *  Let a new MSenFragment for a new CSenBaseElement with the given
     *  namespace and name handle SAX events. The new MSenElement is made
     *  a child of the MSenElement of this MSenFragment.
     */
    virtual void DelegateParsingL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
		const TDesC& aQName,
        MXMLAttributes* aAttrs
        ) = 0;

    virtual void ParseWithL(RXMLReader aReader) = 0;

    /**
     *  May be invoked before ParseWithL() to indicate that a namespace is
     *  already declared. In this case, the saved content will not declare
     *  it again.
     */
    virtual void RegisterNamespaceL(const TDesC& aNsUri, const TDesC& aNsPrefix) = 0;

public:
    virtual void SetOwner(MSenFragment& aFragment) = 0;
    virtual void ResumeParsingFromL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        ) = 0;

public:
    virtual void SetAttributesL(MXMLAttributes* aAttrs) = 0;


public:
    virtual void WriteStartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName,
        MXMLAttributes* apAttrs
        ) = 0;
    virtual void WriteEndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aQName
        ) = 0;

    };

#endif // SEN_FRAGMENT_H
