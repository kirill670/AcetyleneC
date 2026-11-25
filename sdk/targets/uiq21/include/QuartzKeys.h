// QuartzKeys.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

/**
 * This file defines logical names for the standard keys supported by the Quartz DFRD. 
 * These logical names (EQuartzKeyConfirm etc) should be used in source in preference to EStdKeyDevice8 etc.
 * Further keys may be added to this list in subsequent releases of the DRFD
 */

#ifndef __QUARTZKEYS_H__
#define __QUARTZKEYS_H__

#include <e32keys.h>

// For the emulator these keys are mapped to the PC keyboard and facia bitmap in epoc.ini 
// For real hardware they require matching support in the keyboard driver 

	//////////////////////////////////
	// KeyCode
	//////////////////////////////////

	// Two way controller (supports up, down and confirm)
	#define EQuartzKeyTwoWayUp EKeyDevice1 			
	#define EQuartzKeyTwoWayDown EKeyDevice2 		
	
	// Four way controller (supports up, down, left, right and confirm)
	#define EQuartzKeyFourWayUp EKeyDevice4
	#define EQuartzKeyFourWayDown EKeyDevice5
	#define EQuartzKeyFourWayLeft EKeyDevice6
	#define EQuartzKeyFourWayRight EKeyDevice7

	#define EQuartzKeyConfirm EKeyDevice8 			


	/////////////////////////////////
	// ScanCode
	/////////////////////////////////

	// Two way controller (supports up, down and confirm)
	#define EStdQuartzKeyTwoWayUp EStdKeyDevice1 			
	#define EStdQuartzKeyTwoWayDown EStdKeyDevice2 		
	
	// Four way controller (supports up, down, left, right and confirm)
	#define EStdQuartzKeyFourWayUp EStdKeyDevice4
	#define EStdQuartzKeyFourWayDown EStdKeyDevice5
	#define EStdQuartzKeyFourWayLeft EStdKeyDevice6
	#define EStdQuartzKeyFourWayRight EStdKeyDevice7

	#define EStdQuartzKeyConfirm EStdKeyDevice8 			


/* 
// Mapping used on the brutus board to generate Quartz-specific keys //

EQuartzKeyTwoWayUp			EStdKeyDevice1				[ (left square bracket)			
EQuartzKeyTwoWayDown		EStdKeyDevice2				; (semi-colon)		
EQuartzKeyFourWayUp			EStdKeyDevice4				(up arrow)
EQuartzKeyFourWayDown		EStdKeyDevice5				(down arrow)
EQuartzKeyFourWayLeft		EStdKeyDevice6				(left arrow)
EQuartzKeyFourWayRight		EStdKeyDevice7				(right arrow)
EQuartzKeyConfirm			EStdKeyDevice8				' (single quote)
							EStdKeyYes					= (equal)
							EStdKeyNo					- (minus)
							EStdKeyDictaphoneRecord		prog
*/


// The following define is for moving from one control to the next/previous.
#define EQuartzKeySwitchToNextControl		0xF6DC
#define EQuartzKeySwitchToPreviousControl	0xF6DD

#endif