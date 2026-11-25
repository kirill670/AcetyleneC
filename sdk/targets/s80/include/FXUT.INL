// FXUT.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////////
//
// class TFaxSessionProgress
//

inline TInt16 CFaxRecipient::SendingPage() const
/** Gets the number of the page being currently sent.

@return Number of the page being currently sent */
	{
	return iSendingPage;
	}

inline void CFaxRecipient::SetSendingPage(TInt16 aPage)
/** Sets the number of the page being currently sent.

@param aPage Number of the page being currently sent */
	{
	iSendingPage = aPage;
	}

//////////////////////////////////////////////////////////////////////////////////
//
// class TMsvFaxEntry
//

inline TInt16 TMsvFaxEntry::SendingPage() const
/** Gets the number of the page being currently sent.

If the fax is not being sent, the function panics.

@return Number of the page being currently sent */
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Return msig word
	return (TInt16)((iMtmData1 & 0xffff<<16) >> 16);
	}

inline void TMsvFaxEntry::SetSendingPage(TInt16 aPage)
/** Sets the number of the page being currently sent.

@param aPage Number of the page being currently sent */
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Set msig word
	iMtmData1 = (iMtmData1 & 0xffff) | (aPage << 16);
	}

inline TInt16 TMsvFaxEntry::TotalPages() const
/** Gets the total number of the pages being sent.

@return Total number of the pages being sent */
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Return lsig word
	return (TInt16)(iMtmData1 & 0xffff);
	}

inline void TMsvFaxEntry::SetTotalPages(TInt16 aTotal)
/** Sets the total number of the pages being sent.

@param aTotal Total number of the pages being sent */
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Set lsig word only
	iMtmData1 = (iMtmData1 & 0xffff<<16) | aTotal;
	}

inline TInt16 TMsvFaxEntry::SendingRecipient() const
/** Gets which recipient is being sent to.

Recipients are numbered from 0: i.e. 0 is the first recipient.

@return Number of the recipient being sent to */
	{
	// Return msig word
	return (TInt16)((iMtmData3 & 0xffff<<16) >> 16);
	}

inline void TMsvFaxEntry::SetSendingRecipient(TInt16 aRecipient)
/** Sets which recipient is being sent to.

Recipients are numbered from 0: i.e. 0 is the first recipient.

@param aRecipient Number of the recipient being sent to */
	{
	// Set msig word
	iMtmData3 = (iMtmData3 & 0xffff) | (aRecipient << 16);
	}

inline TInt16 TMsvFaxEntry::TotalRecipients() const
/** Gets the total number of recipients being sent to.

@return Total number of recipients being sent to */
	{
	// Return lsig word
	return (TInt16)(iMtmData3 & 0xffff);
	}

inline void TMsvFaxEntry::SetTotalRecipients(TInt16 aTotal)
/** Sets the total number of recipients being sent to.

@param aTotal Total number of recipients being sent to */
	{
	// Set lsig word only
	iMtmData3 = (iMtmData3 & 0xffff<<16) | aTotal;
	}

inline TFaxResolution TMsvFaxEntry::Resolution() const
/** Gets the fax resolution.

@return Fax resolution */
	{
	// Bit 0 indicates fine resolution if set
	return iMtmData2 & EMsvFineResolution ? EFaxFine : EFaxNormal;
	}

inline void TMsvFaxEntry::SetResolution(TFaxResolution aResolution)
	{
	// Bit 0 indicates fine resolution if set, normal if not
	if (aResolution == EFaxNormal)
		iMtmData2 &= ~EMsvFineResolution;
	else
		iMtmData2 |= EMsvFineResolution;
	}

inline TInt8 TMsvFaxEntry::RenderingComplete() const
/** Gets the percentage of the fax so far rendered.

The function panics if the fax is not being prepared to be sent.

@return Percentage of the fax so far rendered */
	{
	__ASSERT_DEBUG(SendingState() == EFaxSendingStatePreparing, User::Invariant()); // Only call this when fax is being prepared
	return (TInt8)iMtmData1;
	}

inline void TMsvFaxEntry::SetRenderingComplete(TInt8 aComplete)
/** Sets the percentage of the fax so far rendered.

The function panics if the fax is not being prepared to be sent.

@param aComplete Percentage of the fax so far rendered */
	{
	__ASSERT_DEBUG(SendingState() == EFaxSendingStatePreparing, User::Invariant()); // Only call this when fax is being prepared
	__ASSERT_DEBUG(aComplete <= 100, User::Invariant()); // This should be a percentage
	iMtmData1 = aComplete;
	}

//////////////////////////////////////////////////////////////////////////////////
//
// class TMTMFaxSettings
//

inline TBool TMTMFaxSettings::ProgressInEntry() const
/** Tests if the entry for a fax message being sent is regularly updated to identify 
how many pages of the fax have been transmitted.

If this flag is set, the RenderingComplete() and SendingPage() settings in 
the TMsvFaxEntry are updated while the fax is sent.

Fax transmissions will be slower when this settings is switched on.

This is true by default.

@return True if updates occur */
	{
	return (iFlags & EFaxNoProgressInEntry) != EFaxNoProgressInEntry;
	}

inline void TMTMFaxSettings::SetProgressInEntry(TBool aProgress)
/** Sets if the entry for a fax message being sent should be regularly updated 
to identify how many pages of the fax have been transmitted.

If this flag is set, the RenderingComplete() and SendingPage() settings in 
the TMsvFaxEntry are updated while the fax is sent.

@param aProgress True if updates should occur, false if not */
	{
	iFlags = (iFlags & ~EFaxNoProgressInEntry) | (aProgress ? KFaxSettingsClearFlag : EFaxNoProgressInEntry);
	}

inline TBool TMTMFaxSettings::PartialResend() const
/** Tests if partial resending is enabled.

Partial resending means that if an error occurs when sending a fax, the last 
successfully sent page is recorded with the recipient details. If the fax 
is then resent, only those pages that were not sent previously will be retransmitted.

This is true by default.

@return ETrue if partial resending is used, EFalse if not. */
	{
	return (iFlags & EFaxNoPartialResend) != EFaxNoPartialResend;
	}

inline void TMTMFaxSettings::SetPartialResend(TBool aResend)
/** Sets a flag that indicates whether partial resending should be used. 

Partial resending means that if an error occurs when sending a fax, the last 
successfully sent page is recorded with the recipient details. If the fax 
is then resent, only those pages that were not sent previously will be retransmitted. 


If the Partial Resend flag is not set, partial resending is disabled and all 
the pages of a failed fax are resent, whether they were previously sent successfully 
or not. 

@param aResend ETrue if partial resending should be used, otherwise EFalse. */
	{
	iFlags = (iFlags & ~EFaxNoPartialResend) | (aResend ? KFaxSettingsClearFlag : EFaxNoPartialResend);
	}

inline TBool TMTMFaxSettings::UnRenderOnSend() const
/** Tests if faxes are unrendered when they have been successfully sent to all 
recipients. 

Rendered fax images can consume a lot of space in the file system, so better 
use can be made of limited space if faxes are unrendered when the image is 
no longer needed. 

This returns true by default.

@return ETrue if faxes should be unrendered when they have been successfully 
sent to all recipients, EFalse if not. */
	{
	return (iFlags & EFaxNoUnRenderOnSend) != EFaxNoUnRenderOnSend;
	}

inline void TMTMFaxSettings::SetUnRenderOnSend(TBool aUnRender)
/** Sets a flag that indicates whether faxes should be unrendered when they have 
been successfully sent to all recipients. 

Rendered fax images can consume a lot of space in the file system, so better 
use can be made of limited space if faxes are unrendered when the image is 
no longer needed.

@param aUnRender ETrue if faxes should be unrendered when they have been successfully 
sent to all recipients. otherwise EFalse. */
	{
	iFlags = (iFlags & ~EFaxNoUnRenderOnSend) | (aUnRender ? KFaxSettingsClearFlag : EFaxNoUnRenderOnSend);
	}

inline TBool TMTMFaxSettings::WatcherEnabled() const
/** Tests if the fax watcher is enabled.

The fax watcher is a separate background thread. It listens to the telephony 
interfaces to identify incoming fax calls, and, when a call is detected, loads 
the fax server MTM and receives the fax, placing it in the inbox.

@return ETrue if the fax watcher should answer incoming fax calls, EFalse 
if not. */
	{
	return (iFlags & EFaxWatcherDisabled) != EFaxWatcherDisabled;
	}

inline void TMTMFaxSettings::SetWatcherEnabled(TBool aEnabled)
/** Enables or disables the fax watcher. 

@param aEnabled ETrue if the fax watcher should answer incoming fax calls, 
EFalse if not. */
	{
	iFlags = (iFlags & ~EFaxWatcherDisabled) | (aEnabled ? KFaxSettingsClearFlag : EFaxWatcherDisabled);
	}

inline TBool TMTMFaxSettings::SentFaxesReadOnly() const
/** Tests if fax entries are marked as read-only after they have been successfully 
sent.

@return ETrue if fax entries should be marked as read-only after they have 
been successfully sent, EFalse if not. */
	{
	return (iFlags & EFaxSentFaxesNotReadOnly) != EFaxSentFaxesNotReadOnly;
	}

inline void TMTMFaxSettings::SetSentFaxesReadOnly(TBool aReadOnly)
/** Sets if fax entries should be marked as read-only after they have been successfully 
sent. 

By default this flag is set to true.

@param aReadOnly ETrue if fax entries should be marked as read-only after 
they have been successfully sent, EFalse if not. */
	{
	iFlags = (iFlags & ~EFaxSentFaxesNotReadOnly) | (aReadOnly ? KFaxSettingsClearFlag : EFaxSentFaxesNotReadOnly);
	}
