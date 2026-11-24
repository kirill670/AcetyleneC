// f32agentui.h
// Copyright (C) Symbian Software Ltd 2004-2005.  All rights reserved.

/** 
@file

This defines an interface used by the F32 Agent to display information on
the screen. The default implementation does nothing. Licensees wishing to allow the F32
agent to display information on the screen should replace this DLL with
a DLL that does display information on screen.

@publishedPartner
@released
*/

#ifndef __F32AGENTUI_H__
#define __F32AGENTUI_H__

#include <e32base.h>

class RFile;

namespace ContentAccess
	{
	/** Interface that must be implemented in order for the F32 agent to display
	information on the screen
	*/
	class CF32AgentUi : public CBase
		{
	public:
		/** Display a dialog asking the user to confirm deleting a file
	
		The function should only return once the dialog has completed

		@param aFileName The name of the file that is about to be deleted
		@return Whether to delete the file
		@return ETrue If F32 should attempt to delete the file
		@return EFalse If the F32 Agent should not delete the file
		*/
		virtual TBool ConfirmDeleteL(const TDesC& aFileName) = 0;	

	
		/** Display information describing the supplied file
	
		The file will already be open before calling this function.
		The function should only return once the dialog has completed
	
		@param aInfo The information to display, from ContentAccess::TDisplayInfo
		@param aFile The file to display
		@return KErrNone or one of the system wide error codes
		*/
		virtual void DisplayInfoL(TInt aInfo, RFile& aFile) = 0;	
	
		/** Set a property. 
	
		@param aProperty The property to set, from ContentAccess::TAgentProperty
		@param aValue The value of the property
		@return Whether the property was set
		@return KErrNone if the property was set correctly
		@return KErrCANotSupported if the property is not supported
		*/
		virtual TInt SetProperty(TInt aProperty, TInt aValue) = 0;
		};

	/** Factory function that creates the F32 Agent UI 
	@return a CF32AgentUi object 
	*/
	class TF32AgentUiFactory
		{
	public:
		IMPORT_C static CF32AgentUi* CreateF32AgentUiL();
		};
	}



#endif // __F32AGENTUI_H__
