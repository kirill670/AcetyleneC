
/*
* ==============================================================================
*  Name        : eikcmds.h
*  Part of     : UIKON
*  Interface   : System event API
*  Description : Extends AppArc with low memory shutdown notifier
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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

#if !defined(__EIKCMDS_H__)
#define __EIKCMDS_H__
/** Extra system event enum
 */
enum TExtraApaSystemEvent
	{
	/** The task is being closed by memory watcher
	 */
	EApaSystemEventLowMemoryShutdown=1000,
	/** The Notifier server is showing/hiding a notifier
	 */
	EApaSystemEventNotifierServer
	};

#endif // __EIKCMDS_H__
