/**
@file
@deprecated Obselete

Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
*/

#ifndef __PLPVAR_H__
#define __PLPVAR_H__

#include <e32std.h>

/** Machine identifier length
@internalAll */
const TInt KMaxPlpVariantMachineIdLength = 0x80;

/** Drive identifier length
@internalAll */
const TInt KMaxPlpVariantDriveIdLength = 0x80;

/** Drive alias length
@internalAll */
const TInt KMaxPlpVariantDriveAliasLength = 0x80;

/** Machine identifier buffer
@internalAll */
typedef TBuf<KMaxPlpVariantMachineIdLength> TPlpVariantMachineId;
	
/** Drive identifier buffer
@internalAll */
typedef TBuf<KMaxPlpVariantDriveIdLength> TPlpVariantDriveId;

/** Drive alias buffer
@internalAll */
typedef TBuf<KMaxPlpVariantDriveAliasLength> TPlpVariantDriveAlias;	

#endif __PLPVAR_H__
