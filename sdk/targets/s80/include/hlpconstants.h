/*
* ==============================================================================
*  Name        : HlpConstants.h
*  Part of     : Help model
*  Interface   :
*  Description : Help database support
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __HLPCONSTANTS_H__
#define __HLPCONSTANTS_H__

// System includes
#include <e32std.h>

// Constants
const TUid KUidHlpApp		=	{ 0x0100052b3 };	// UID 3
const TUid KUidHlpFile		=	{ 0x0100052b4 };	// UID 2
const TUid KUidHlpDbStream	=	{ 0x0100052b5 };	// Database stream in the help file
const TUid KUidHlpUidStream	=	{ 0x0100052b6 };	// UID stream in the help file
//
const TInt KTitleColumn	= 1;
const TInt KIdColumn = 2;
const TInt KMaxTitleColumn = 120;
const TInt KHlpSQLMaxLength = 512;
const TInt KHlpMaxTextColLength = 200;
const TInt KHlpMaxContextColLength = 32;




#endif