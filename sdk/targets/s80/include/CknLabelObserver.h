/*
* ==============================================================================
*  Name        : cknlabelobserver.h
*  Part of     : CKON
*  Interface   : LABEL API
*  Description : Label observer class to watch for pointer events in labels
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

#ifndef CKNLABELOBSERVER_H
#define CKNLABELOBSERVER_H


/**
 * class MCknLabelObserver
 * 
 * This mixin class allows controls to watch for 
 * pointer events in labels
 * @since Series 90 1.0
 */
class MCknLabelObserver
	{
	public:

		/**
		* Called when a pointer event occurs on a label
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleLabelPointerL(const TPointerEvent& aPointerEvent) = 0;

	private:
		IMPORT_C virtual void MCknLabelObserver_Reserved_1();
		IMPORT_C virtual void MCknLabelObserver_Reserved_2();
	};
	
#endif	// CKNLABELOBSERVER_H

// End of File
