// TextInputServerClient.inl
//
// Copyright (c) 1997-2001 Symbian Ltd. All rights reserved
//

/**
 * This function allows to unload the active AnimDll. For replacing the AnimDll with another one, also the LoadNewAnimDll
 * function can be called. The FEP should NOT call this function on exit. by that the AnimDLL only needs to be deactivated,
 * and does not have to be loaded each time the user switches between the virtual keyboard and the write-anywhere Handwriting
 * Recognition (HWR)
 * 
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::UnloadActiveAnimDll() const
	{
	return GlobalSendFunction(EUnloadAnimDll);
	}
/**
 * This function sends a Deactivate signal to the AnimDll, that should deactivate itself until it gets again an Acivate signal.
 * This function can be called several times, but all cunsecutive calls will be ignored.
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::DeactivateWriteAnywhereTi() const
	{
	return GlobalSendFunction(EDeactivateWriteAnywhere);
	}

/**
 * This function sends an Activate signal to the AnimDll, that will activate the AnimDll (after a Deactivate signal)
 * This function can be called several times, but all cunsecutive calls will be ignored.
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::ActivateWriteAnywhereTi() const
	{
	return GlobalSendFunction(EActivateWriteAnywhere);
	}

/**
 * If for some reason the standard behaviour of the TextInputServer is not the one an application wants to have (in a certain
 * circumstance), the application has the possiblity to prohibit the write-anywhere TextInput (Ti). The Ti will not get active
 * until the application makes a call to the ApplicationAllowsWriteAnywhereTi. The Ti is only deactivated for that specific
 * application not for any other application.
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::SetWriteAnywhereTiAllowed(TBool aAllowed) const
	{
	if( aAllowed )
		return GlobalSendFunction(EAppAllowsWriteAnywhere);
	else
		return GlobalSendFunction(EAppProhibitsWriteAnywhere);
	}

/**
 * This function should get called whenever the application gains the forground.
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::RestoreApplicationStatus() const
	{
	return GlobalSendFunction(ERestoreAppStatus);
	}

/**
 * This function will show the secondTi method (virtual keyboard), if it is not already visible
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::OpenTextInputBox() const
	{
	return GlobalSendFunction(EOpenTextInputBox);
	}

/**
 * This function will hide the second Ti method (virtual keyboard) and show the primary, if it is not already hidden. The primary is
 * active, but that doesn't mean, that write-anywhere HWR is active, since that is up to the HWR-Fep to decide.
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::CloseTextInputBox() const
	{
	return GlobalSendFunction(ECloseTextInputBox);
	}

/**
 * An application has the possibility to disallow the second Ti method by calling the SecondTiNotAllowed function.
 * This should only be used in special cases. The application has to enable it in order to get the vk by calling 
 * this function.
 *
 * @return An Errorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::SetInABoxTiAllowed(TBool aAllowed) const
	{
	if( aAllowed )
		return GlobalSendFunction(EAppAllowsInputBox);
	else
		return GlobalSendFunction(EAppProhibitsInputBox);
	}
/**
 * This function resets the primary Ti method to whatever is defined in the resource file of the TextInputServer
 *
 * @return AnErrorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::SetFactorySettingsForWriteAnywhereTi() const
	{
	return GlobalSendFunction(EFactoryWriteAnywhere);
	}

/**
 * This function resets the secondary Ti method to whatever is defined in the resource file of the TextInputServer
 *
 * @return AnErrorcode. KErrNone if successful
 */
inline TInt RTextInputServerClient::SetFactorySettingsForInABoxTi() const
	{
	return GlobalSendFunction(EFactoryInputBox);
	}

// debug functions
/**
 * This function is for test purposes only, and therefore the client will be paniced, if they
 * are in a nondebug environment.
 */
inline TInt RTextInputServerClient::DbgTisStopActiveScheduler() const
	{
	return GlobalSendFunction(EDbgStopScheduler);
	}

/**
 * This function is for test purposes only, and therefore the client will be paniced, if they
 * are in a nondebug environment.
 */
inline TInt RTextInputServerClient::DbgTisPanicServer() const
	{
	return GlobalSendFunction(EDbgPanicServer);
	}
/**
 * This function is for test purposes only, and therefore the client will be paniced, if they
 * are in a nondebug environment.
 */
inline TInt RTextInputServerClient::DbgTisPanicClient() const
	{
	return GlobalSendFunction(EDbgPanicClient);
	}

