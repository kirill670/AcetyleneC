/*
* ==============================================================================
*  Name        : cknfepcontrolobserver.h
*  Part of     : CKON
*  Interface   : FEP API
*  Description : FEP observer classes to watch for cursor moving and dialog activation.
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

#ifndef CKNFEPCONTROLOBSERVER_H
#define CKNFEPCONTROLOBSERVER_H


/**
 * The <code>MCknFepControlObserver</code> class is a mixin class, which allows 
 * FEPs to observe events from controls, such as when a dialog is opened and 
 * when the cursor moves in editor controls.
 * To become an observer first the FEP must register itself using 
 * <code>CEikonEnv::SetFepControlObserver()</code>
 *
 * @lib cknctl.lib 
 * @since Series 90 1.0
 */
class MCknFepControlObserver
	{
	public:

		/**
		* A callback method that can be used to watch a cursor position change 
        *  in a <code>CEikonEnv</code>.
        *
		* @remarks
        * @see
		*/
		virtual void HandleChangeInCursorPosition() = 0;

		/**
		* A callback method that is called when a dialog is about to be 
        * displayed so that a FEP can gain access to the dialog window in 
        * order to set the position of the dialog.
        *
		* @remarks
        * @see
		*/
		virtual void HandleDialogActivated() = 0;

		/**
		* A callback method that can be used to watch pen-down events in a 
        * <code>CEikonEnv</code>.
		* 
        * @remarks
        * @see
		*/
		IMPORT_C virtual void HandlePenDownEvent();

		/**
		* A callback method that can be used to watch pen-up events in a 
        * <code>CEikonEnv</code>.
		* 
        * @remarks
        * @see
		*/
		IMPORT_C virtual void HandlePenUpEvent();
	private:
		IMPORT_C virtual void MCknFepControlObserver_Reserved_1();
		IMPORT_C virtual void MCknFepControlObserver_Reserved_2();
	};
	
#endif	// CKNFEPCONTROLOBSERVER_H

// End of File
