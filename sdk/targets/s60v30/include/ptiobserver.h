/*
* ============================================================================
*  Name       : PtiObserver.h
*  Part of    : PtiEngine
*  Description: MPtiObserver class definition.  
*  Version:
*
*  Copyright © 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef _PTI_OBSERVER_H
#define _PTI_OBSERVER_H

class MPtiObserver
	{
	public:
		virtual void KeyTimerExpired() = 0;
		virtual void LastWordInSelectionList() = 0;
		virtual void FirstWordInSelectionList() = 0;
	};


#endif // _PTI_OBSERVER_H

// End of file
