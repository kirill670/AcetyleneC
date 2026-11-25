// GRDPRINT.INL
//
// Copyright (c) Nokia Corporation 2001-2004. All rights reserved.
//

/**
* Supplies the object that deals with the mapping between twips and 
* device-specific units for a specific printer
*
* @param  "const MGraphicsDeviceMap* aGraphicsDeviceMap"
*			The interface object for mapping between twips and device-specific units
*/
inline void CGridPrinter::SetRealPrintingDeviceMap(const MGraphicsDeviceMap* aGraphicsDeviceMap)
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

/**
* Gets the grid layout used by this printing object.
* 
* Note that this is not the same object passed to CGridPrinter::NewL(). 
* Internally, the class creates its own CGridLay object from the information 
* supplied in the CGridLay object passed to CGridPrinter::NewL().
* 
*
* @returns	"CGridLay&"
*			The grid layout object
*/
inline CGridLay& CGridPrinter::GridLay()
	{
	return *iGridLay;
	}
