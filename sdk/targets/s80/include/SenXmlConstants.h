/*
 * =========================================================================
 *  Name     : SenXmlConstants.h
 *  Part of  : SenXml
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenXmlConstants.h,v $
 *   $Date: 2004/07/31 05:29:22 $
 *   $Revision: 1.1 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_XML_CONSTANTS_H
#define SEN_XML_CONSTANTS_H

#include <e32base.h>

// Panics

_LIT(KPanic, "SenXml");

enum TPanic
    {
    EBadNamespace = 1,
    EBadNamespacePrefix,
    EBufNot16Bit,
    EFragmentElementNotInitialized,
    EDelegatedFragmentAlreadySet,
    EInconsistentTokens,
    EBadInternalState
    };

// XML String constants

_LIT(KLessThan, "<");
_LIT(KGreaterThan, ">");
_LIT(KColon, ":");
_LIT(KSpace, " ");
_LIT(KDblQuot, "\"");
_LIT(KEqualsDblQuot, "=\"");
_LIT(KSlashGreaterThan, "/>");
_LIT(KLessThanSlash, "</");
_LIT(KSpaceXmlns, " xmlns");
_LIT(KXmlns, "xmlns");

_LIT(KQuotedApos, "&apos;");
_LIT(KQuotedDblQuot, "&quot;");
_LIT(KQuotedGt, "&gt;");
_LIT(KQuotedLt, "&lt;");
_LIT(KQuotedAmp, "&amp;");

#endif // SEN_XML_CONSTANTS_H
