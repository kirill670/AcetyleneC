// MDXMLConstants.h
//
/** @file MDXMLConstants.h
 * This file contains generic XML constants
 */

#ifndef __MDXMLCONSTANTS_H__
#define __MDXMLCONSTANTS_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

enum TXMLFileType
	{
	EAscii = 1,
	EUnicode = 2
	};

const TInt KReadBufferLen = 1024;
const TInt KWriteBufferLen = 1024;

// Error codes
const TInt KErrXMLBase = -9000;
const TInt KErrXMLBadAttributeValue =			KErrXMLBase - 1;
const TInt KErrXMLBadAttributeName = 			KErrXMLBase - 2;
const TInt KErrXMLInvalidChild = 				KErrXMLBase - 3;
const TInt KErrXMLBadNesting = 					KErrXMLBase - 4;
const TInt KErrXMLIncomplete = 					KErrXMLBase - 5;
const TInt KErrXMLBadElementName = 				KErrXMLBase - 6;
const TInt KErrXMLDuplicateDocTypeTags = 		KErrXMLBase - 7;
const TInt KErrXMLDuplicateVersionTags = 		KErrXMLBase - 8;
const TInt KErrXMLDuplicateRootElements =		KErrXMLBase - 9;
const TInt KErrXMLMissingDocTypeTag = 			KErrXMLBase - 10;
const TInt KErrXMLMissingVersionTag = 			KErrXMLBase - 11;
const TInt KErrXMLDuplicateAttributeName =	KErrXMLBase - 12;
const TInt KErrXMLMultipleRootElements = 		KErrXMLBase - 13;
const TInt KErrXMLCorruptFile = 					KErrXMLBase - 14;
const TInt KErrXMLIllegalCharacter = 			KErrXMLBase - 15;


enum TXMLErrorCodeSeverity
	{
	EXMLFatal,
	EXMLIndeterminate,
	EXMLWorkable,
	EXMLNone
	};


_LIT(KNewLine, "\r\n");

#ifdef _DEBUG
	_LIT(KTab, "   ");
#endif

_LIT(KXMLSemiColon, ";");
_LIT(KXMLDecimalId, "&#");
_LIT(KXMLHexidecimalId, "&#x");
_LIT(KXMLEndTag, ">");
_LIT(KXMLStartComment, "<!--");
_LIT(KXMLEndComment, "-->");
_LIT(KXMLStartEndTag, "</");
_LIT(KXMLStartTag, "<");
_LIT(KXMLEndStartTag, "/>");
_LIT(KXMLStartProcessingInstruction, "<?");
_LIT(KXMLEndProcessingInstruction, "?>");
_LIT(KXMLVersion, "<?XML");
_LIT(KXMLDocumentTypes, "<!DOCTYPE");

_LIT(KXMLCDATASectionNodeName, "#cdata-section");
_LIT(KXMLDocumentElementNodeName, "documentelement");
_LIT(KXMLCommentNodeName, "comment");
_LIT(KXMLProcessingInstructionNodeName, "processing_instruction");
_LIT(KXMLTextNodeName, "#text");

_LIT(KBackSlash, "\\");
_LIT(KDash, "-");
_LIT(KExclamation, "!");
_LIT(KForwardSlash, "/");
_LIT(KEqualSign, "=");
_LIT(KLeftArrow, "<");
_LIT(KRightArrow, ">");
_LIT(KAmpersand, "&");
_LIT(KApostrophe, "\'");
_LIT(KQuotation, "\"");
_LIT(KSingleSpace, " ");

//Built in entities
_LIT(KLeftArrowText, "&lt;");
_LIT(KRightArrowText, "&gt;");
_LIT(KAmpersandText, "&amp;");
_LIT(KApostropheText, "&apos;");
_LIT(KQuotationText, "&quot;");

const TInt KNominalTagLength = 256;
const TInt KStartPosition = -1;
const TInt KXMLUndefinedElement = -1; // ELement whose enumerated type has not been set.

#endif
