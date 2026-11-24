// ImageTransformPluginExt.h
//
// Copyright (c) 2004 Symbian Software Ltd. All rights reserved
//
// This is the extension to the plugin API for the Image Transform framework
//
#ifndef __IMAGETRANSFORMPLUGINEXT_H__
#define __IMAGETRANSFORMPLUGINEXT_H__

#include <e32base.h>

/**
This class should be derived by a plugin writer wishing to extend the client 
API defined in CImageTransform

@publishedAll
@released
*/
class CImageTransformPluginExtension : public CBase
	{
public:
	
	/**
	Get a Uid by which a plugin extension can be identified.

	@return A Uid unique to the specific plugin extension
	*/
	IMPORT_C virtual const TUid Uid() const = 0;
	};

#endif // __IMAGETRANSFORMPLUGINEXT_H__