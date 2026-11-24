// XmlErrors.h
// Copyright (c) 2003-2006 Symbian Software Ltd.  All rights reserved.
//

#ifndef XMLERRORS_H
#define XMLERRORS_H

// XML-specific errors returned by the XML parser
enum TXmlParserError {
	EXmlParserError = -1000,
	EXmlSyntax = 2+EXmlParserError,		// -998
	EXmlNoElements,						// -997
	EXmlInvalidToken,					// -996
	EXmlUnclosedToken,					// -995
	EXmlPartialChar,					// -994
	EXmlTagMismatch,					// -993
	EXmlDuplicateAttribute,				// -992
	EXmlJunkAfterDocElement,			// -991
	EXmlPeRef,							// -990
	EXmlUndefinedEntity,				// -989
	EXmlRecursiveEntity,				// -988
	EXmlAsyncEntity,					// -987
	EXmlBadCharRef,						// -986
	EXmlBinaryEntityRef,				// -985
	EXmlAttributeExternalEntityRef,		// -984
	EXmlMisplacedPi,					// -983
	EXmlUnknownEncoding,				// -982
	EXmlIncorrectEncoding,				// -981
	EXmlUnclosedCdata,					// -980
	EXmlExternalEntityHandling,			// -979
	EXmlNotStandalone,					// -978
	EXmlUnexpectedState,				// -977
	EXmlEntityDeclInPe,					// -976
	EXmlDtdRequired,					// -975
	EXmlFeatureLockedWhileParsing		// -974
};

// XMLERRORS_H
#endif
