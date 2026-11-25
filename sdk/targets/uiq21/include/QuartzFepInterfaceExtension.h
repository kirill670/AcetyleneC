// QUARTZFEPINTERFACEEXTENSION.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __QUARTZFEPINTERFACEEXTENSION_H__
#define __QUARTZFEPINTERFACEEXTENSION_H__

const TUid KFepInterfaceExtensionsUid = {0x101F60C9};

/**
 * Definition of <code>TCoeInputCapabilities::MCoeFepSpecificExtensions</code>
 * to allow several FepExtensions installed on the same device, 
 * and thereby allowing several FEPs with their own extension.
 */
class TCoeInputCapabilities::MCoeFepSpecificExtensions
	{
public:
	virtual TAny* Extensions(TUid aExtensionSpecificUid) = 0;
	};

#endif	// __QUARTZFEPINTERFACEEXTENSION_H__