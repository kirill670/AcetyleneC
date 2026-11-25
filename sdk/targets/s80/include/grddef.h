/*
* ==============================================================================
*  Name        : GrdDef.h
*  Part of     : Grid
*  Interface   : ?Interface_category, ?Interface_name
*  Description : General defines for Grid module
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


#ifndef GRDDEF_H
#define GRDDEF_H

//  INCLUDES

// CONSTANTS

// MACROS

// DATA TYPES
enum TMoveDirectionAndAmount
	{
	EMoveRowUp,					//!< Move up by one row
	EMoveRowDown,				//!< Move down by one row
	EMoveColumnLeft,			//!< Move left by one column
	EMoveColumnRight,			//!< Move right by one column
	EMovePageUp,				//!< Move up by one page
	EMovePageDown,				//!< Move down by one page
	EMovePageLeft,				//!< Move left by one page
	EMovePageRight,				//!< Move right by one page
	EMoveRowStart,				//!< Move to the start of the row
	EMoveRowEnd,				//!< Move to the end of the row
	EMoveHome,					//!< Move to the home position
	EMoveEnd,					//!< Move to the end position
	EMoveNone,					//!< Do not move the cursor
	EMoveColumnStart,			//!< Move to the start of the column
	EMoveColumnEnd				//!< Move to the end of the column
	};


// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

#endif      // GRDDEF_H   
            
// End of File
