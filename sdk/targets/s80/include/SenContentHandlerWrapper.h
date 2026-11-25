/*
 * =========================================================================
 *  Name     : SenContentHandlerWrapper.h
 *  Part of  : SenXmlInterface
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/XmlInterface/inc/SenContentHandlerWrapper.h,v $
 *   $Date: 2004/10/21 22:00:12 $
 *   $Revision: 1.2 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */



#ifndef SEN_CONTENTHANDLER_WRAPPER_H
#define SEN_CONTENTHANDLER_WRAPPER_H

#include <e32base.h>
#include <badesca.h>

#include "MXMLContentHandler.h"


/**
 *  A doc handler wrapper that fixes some wrinkles of the current
 *  implementation of the XMLInterface library:
 *  - XML default namespace ('xmlns=') is handled correctly
 *  - XML namespace attributes are passed correctly for ending elements
 *  - some quoted characters are properly parsed (like '&amp;' -> '&')
 */
class CSenContentHandlerWrapper :
    public CBase,
    public MXMLContentHandler
    {
public:
    static CSenContentHandlerWrapper* NewL();
    virtual ~CSenContentHandlerWrapper();

public:
    /**
     *  @return KErrNone if there was no error during parsing, the error
     *      code otherwise.
     */
    TInt ErrorState();

    /**
     *  Reset to default state;
     */
    void Reset();

public:
    void SetContentHandler(MXMLContentHandler* apContentHandler);
    MXMLContentHandler* ContentHandler();

private:
    // from MXMLContentHandler
    virtual TInt StartDocument();
    virtual TInt EndDocument();
    virtual TInt StartElement(
        TDesC& aNsUri,
        TDesC& aLocalName,
        TDesC& aQName,
        MXMLAttributes* apAttrs
        );
    virtual TInt EndElement(TDesC& aNsUri, TDesC& aLocalName, TDesC& aQName);
    virtual TInt Charecters(TDesC& aBuf, TInt aStart, TInt aLength);

private:
    void StartElementL(
        TDesC& aNsUri,
        TDesC& aLocalName,
        TDesC& aQName,
        MXMLAttributes* apAttrs
        );
    void EndElementL(
        TDesC& aNsUri,
        TDesC& aLocalName,
        TDesC& aQName
        );
    void CharactersL(TDesC& aBuf, TInt aStart, TInt aLength);

private:
    CSenContentHandlerWrapper();
    void ConstructL();

private:
    static TBool StartsWith(const TDesC& aDesC, const TDesC& aPrefix);

private:
    MXMLContentHandler* ipEmbeddedHandler; // Not owned

    CDesCArray* ipElementNsUris; // Owned
    CDesCArray* ipDefaultNsUris; // Owned

    TInt iErrorState;
    };

#endif // SEN_CONTENTHANDLER_WRAPPER_H
