
#ifndef MEIKDIALOGCANCELINTERFACE_H
#define MEIKDIALOGCANCELINTERFACE_H

/**
 *  A Mixin Interface class for closing an open dialog from another
 *  class/App that does not own the dialog.
 *
 *  A derived class can instantiate a MEikDialogCancelInterface and use 
 *  the CancelDialog() function to call for the closing of the dialog. We 
 *  use this to dismiss previously open dialogs upon entry/exit of an app 
 *  that has been tasked away from, with dialogs left open.  It prevents
 *  the user coming back to the screen from another View/control and finding 
 *	an unrelated dialog open.
 *
 *  The CancelDialog() function simply calls TryExitL(EEikBidCancel) we 
 *  do not allow the Ok action.
 *
 *  @since Series90 1.0
 */

class MEikDialogCancelInterface
	{
	public:

		/**
		* Virtual Accessor function to cancel an Active Dialog
		* <BR><B>Type of return value:</B> void
		*/
		virtual void CancelDialog()=0;
	};


#endif MEIKDIALOGCANCELINTERFACE_H