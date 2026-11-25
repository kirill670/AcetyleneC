// FAXC.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

inline CFaxHeader& CFaxMtmClient::FaxHeader()
/** Gets the fax header for the current context: this holds recipient information.

@return The fax header for the current context */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvMessageEntry, User::Panic(_L("FAXC"), 1));
	return *iFaxHeader;
	}

inline const CFaxHeader& CFaxMtmClient::FaxHeader() const
/** Gets the (const) fax header for the current context: this holds recipient information.

@return The fax header for the current context */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvMessageEntry, User::Panic(_L("FAXC"), 1));
	return *iFaxHeader;
	}

inline TMTMFaxSettings& CFaxMtmClient::FaxSettings()
/** Gets the current fax service settings.

@return The current fax service settings */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvServiceEntry, User::Panic(_L("FAXC"), 1));
	return iFaxSettings;
	}

inline const TMTMFaxSettings& CFaxMtmClient::FaxSettings() const
/** Gets the (const) current fax service settings.

@return The current fax service settings */
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvServiceEntry, User::Panic(_L("FAXC"), 1));
	return iFaxSettings;
	}
