/*
* ==============================================================================
*  Name        : aknborders.h
*  Part of     : 
*  Description : 
*  Version     : 
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef __AKNBORDERS_H__
#define __AKNBORDERS_H__

#include <e32std.h>

class AknBorderId
	{
public:
	enum TAknBorderId
		{
		EAknBorderNotePopup = 0x800110,		// also valid for query, find?
		EAknBorderMenuPopup,
		EAknBorderMenuSubmenuPopup,
		EAknBorderNotificationPopup,
		EAknBorderGroupedNotificationsPopup,
		EAknBorderCharacterSelectionPopup,
		EAknBorderPopups, // for list queries (looks like the menu things DOES NOT work for dialogs, I dunno why...)
		EAknBorderPopupsWithHeading,
		EAknBorderMax			// End marker for avkon borders. Not a real border type.
		};
	};


#endif //__AKNBORDERS_H__
