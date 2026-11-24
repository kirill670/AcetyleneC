// ContentSource.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//
// Plugin interface


#ifndef __CONTENTSOURCE_H__
#define __CONTENTSOURCE_H__

namespace Xml
{

class MContentHandler;

class MContentSource
/** This interface must be implemented by xml framework plugins wishing
to pass data as part of a chain of plugins.

@publishedPartner
@released
*/
	{
public:
/** This method tells us what's the next content handler in the chain. */
	virtual void SetContentSink (MContentHandler& aContentHandler) = 0;
	};

}

//__CONTENTSOURCE_H__
#endif
