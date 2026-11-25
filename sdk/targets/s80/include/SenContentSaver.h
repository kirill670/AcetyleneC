/*
 * =========================================================================
 *  Name     : SenContentSaver.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenContentSaver.h,v $
 *   $Date: 2004/10/14 12:29:03 $
 *   $Revision: 1.4 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_CONTENT_SAVER_H
#define SEN_CONTENT_SAVER_H

#include <e32base.h>

#include <badesca.h>
#include <s32mem.h>
#include <MXMLAttributes.h>


/**
 *  Helper class to write sub-elements of an XML document into a separate
 *  buffer. This class manages namespaces on its own. It may not work
 *  properly in the following circumstances:
 *  - if the same namespace prefix (e.g. "soap:") is used for multiple
 *    URIs in the same XML document
 *  - if the default namespace means multiple URIs in the same document.
 */

// deprecated, only for bc
class CSenContentSaver :
    public CBase
    {
public:
	// deprecated, only for bc
    IMPORT_C static CSenContentSaver* NewL(RWriteStream& aWs);
	// deprecated, only for bc
    IMPORT_C static CSenContentSaver* NewLC(RWriteStream& aWs);
 	// deprecated, only for bc
    IMPORT_C virtual ~CSenContentSaver();

public:
    /**
     *  Register the given namespace with the given prefix. If this namespace
     *  will be encountered during WriteXXX methods, it will not declare this
     *  namespace again.
     *  @param aNsPrefix may be KNullDesC (= default namespace)
     */
	// deprecated, only for bc
    IMPORT_C void RegisterNamespaceL(
        const TDesC& aNsUri,
        const TDesC& aNsPrefix
        );

public:
	// deprecated, only for bc
    IMPORT_C void WriteStartElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aName,
        MXMLAttributes* apAttrs
        );
	// deprecated, only for bc
    IMPORT_C void WriteEndElementL(
        const TDesC& aNsUri,
        const TDesC& aLocalName,
        const TDesC& aName
        );
	// deprecated, only for bc
    IMPORT_C void WriteCharactersL(const TDesC& aChars);

private:

	// deprecated, only for bc
    TBool NotifyStartElementL(
        TPtrC& aNsPrefix,
        const TDesC& aNsUri,
        const TDesC& aQName
        );
	// deprecated, only for bc
    void NotifyEndElementL();

private:
	// deprecated, only for bc
    CSenContentSaver(RWriteStream &aWs);
	// deprecated, only for bc
    void ConstructL();

private:
//    RWriteStream& iWs;              // Not owned (Close)
//    TBool iStartTagUnfinished;

    };

#endif // SEN_CONTENT_SAVER_H
