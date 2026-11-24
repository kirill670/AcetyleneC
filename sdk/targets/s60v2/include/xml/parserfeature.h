// ParserFeature.h
// Copyright (c) 2003-4 Symbian Ltd.  All rights reserved.
//

#ifndef __PARSERFEATURE_H__
#define __PARSERFEATURE_H__

/** 
@file
@publishedAll
@released
*/


namespace Xml
{

enum TParserFeature 
/** Every parser has a set of optional features that it may implement */
	{
/** Convert elements and attributes to lowercase. This can be used for 
case-insensitive HTML so that a tag can be matched to a static string in the string pool.
@see RStringPool */
	EConvertTagsToLowerCase	= 0x0001,

/** Report an error when unrecognised tags are found. */
	EErrorOnUnrecognisedTags	= 0x0002,

/** Reports unrecognised tags. */
	EReportUnrecognisedTags	= 0x0004,

/** Report the namespace. */
	EReportNamespaces			= 0x0008,

/** Report the namespace prefix. */
	EReportNamespacePrefixes	= 0x0010,

/** Send all content data for an element in one chunk. */
	ESendFullContentInOneChunk	= 0x0020,

/** Report namespace mappings via the OnStartPrefixMapping & OnEndPrefixMapping methods.
@see MContentHandler */
	EReportNamespaceMapping	= 0x0040,

/** Describe the data in the specified encoding, otherwise use utf-8. */
	ERawContent                = 0x0080,

/** Should be updated to reflect any new enumerations added. */
	ELastFeature               = ERawContent,
	};

}

#endif // __PARSERFEATURE_H__
