/*
* ==============================================================================
*  Name        : Chtdef.h
*  Part of     : Chart
*  Interface   : ?Interface_category, ?Interface_name
*  Description : General chart definitions
*  Version     : ?Version
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef CHTDEF_H
#define CHTDEF_H

//  INCLUDES

// CONSTANTS
const TUint KChartBaseTimeHigh=13960314u;
const TUint KChartBaseTimeLow=2328109056u;

const TInt KChartMarkerSize=6;			// must be an even number
const TInt KChartMarkerOffset=0;		// distance of markers outside a rectangular object

// MACROS


// DATA TYPES
struct SLimits
	{
	TReal iLowerLimit;
	TReal iUpperLimit;
	};

struct SChartAxesLimits
	{
	SLimits iXAxis;
	SLimits iYAxis;
	};

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION


#endif      // CHTDEF_H   
            
// End of File
