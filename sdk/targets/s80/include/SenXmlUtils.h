/*
 * =========================================================================
 *  Name     : SenXmlUtils.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenXmlUtils.h,v $
 *   $Date: 2004/08/06 13:54:18 $
 *   $Revision: 1.2 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_XML_UTILS_H
#define SEN_XML_UTILS_H

#include <e32base.h>


class SenXmlUtils
    {
public:
    IMPORT_C static HBufC8* ToUtf8LC(const TDesC16& aUnicodeString);
    IMPORT_C static HBufC16* ToUnicodeLC(const TDesC8& aUtf8String);

public:
    IMPORT_C static TBool StartsWith(const TDesC& aDes, const TDesC& aPrefix);
    IMPORT_C static TBool EndsWith(const TDesC& aDes, const TDesC& aPrefix);

public:
    /**
     *  @return the namespace prefix for the element, e.g. 'soap' for
     *      'soap:Body'. The returned ptr is empty if there is no prefix.
     */
    IMPORT_C static TPtrC NsPrefix(const TDesC& aQName);

    /**
     *  @return the local name for the element, e.g. 'Body' for
     *      'soap:Body'.
     */
    IMPORT_C static TPtrC LocalName(const TDesC& aQName);

private:
    SenXmlUtils() { }
    };

#endif // SEN_XML_UTILS_H
