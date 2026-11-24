// XmlErrors.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef XMLERRORS_H
#define XMLERRORS_H

// XML-specific errors returned by the XML parser
enum TXmlParserError {
	EXmlParserError = -1000,
	EXmlSyntax = 2+EXmlParserError,		// -998
	EXmlNoElements,						// -997
	EXmlInvalidToken,					// -996
	EXmlUnclosedToken,					// ...
	EXmlPartialChar,
	EXmlTagMismatch,
	EXmlDuplicateAttribute,
	EXmlJunkAfterDocElement,
	EXmlPeRef,
	EXmlUndefinedEntity,
	EXmlRecursiveEntity,
	EXmlAsyncEntity,
	EXmlBadCharRef,
	EXmlBinaryEntityRef,
	EXmlAttributeExternalEntityRef,
	EXmlMisplacedPi,
	EXmlUnknownEncoding,
	EXmlIncorrectEncoding,
	EXmlUnclosedCdata,
	EXmlExternalEntityHandling,
	EXmlNotStandalone,
	EXmlUnexpectedState,
	EXmlEntityDeclInPe,
	EXmlDtdRequired,
	EXmlFeatureLockedWhileParsing
};

#endif  // XMLERRORS_H