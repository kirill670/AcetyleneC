/*
* ==============================================================================
*  Name        : SenXmlConstants.h
*  Part of     : Web Services Xml
*  Interface   : 
*  Description : This header lists all constants of XML Extensions library
*  Version     : 
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef SEN_XML_CONSTANTS_H
#define SEN_XML_CONSTANTS_H

//  INCLUDES
#include <e32base.h>

// CONSTANTS
// Leave codes
const TInt KErrSenInvalidCharacters		=	-30300;
const TInt KErrSenZeroLengthDescriptor		=	-30301;
const TInt KErrSenXmlReaderNotSet		=	-30302;
const TInt KErrSenXmlContentHandlerNotSet	=	-30303;

// Panics
_LIT(KPanic, "SenXml");
// XML String constants
_LIT8(KLessThan, "<");
_LIT8(KGreaterThan, ">");
_LIT8(KColon, ":");
_LIT8(KSpace, " ");
_LIT8(KDblQuot, "\"");
_LIT8(KEqualsDblQuot, "=\"");
_LIT8(KSlashGreaterThan, "/>");
_LIT8(KLessThanSlash, "</");
_LIT8(KSpaceXmlns, " xmlns");
_LIT8(KXmlns, "xmlns");

_LIT8(KQuotedApos, "&apos;");
_LIT8(KQuotedDblQuot, "&quot;");
_LIT8(KQuotedGt, "&gt;");
_LIT8(KQuotedLt, "&lt;");
_LIT8(KQuotedAmp, "&amp;");

// DATA TYPES
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

#endif // SEN_XML_CONSTANTS_H

// End of File

