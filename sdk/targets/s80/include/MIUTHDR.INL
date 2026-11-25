// MIUTHDR.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

inline void TImHeaderEncodingInfo::SetField(const TFieldList aField)
/** Sets the field type.

@param aField Field type */
	{
	iField = aField;
	}

inline TImHeaderEncodingInfo::TFieldList TImHeaderEncodingInfo::Field() const
/** Gets the field type.

@return Field type */
	{
	return iField;
	}

inline void TImHeaderEncodingInfo::SetOffset(const TInt aOffset)
/** Sets the field offset.

@param aOffset Field offset */
	{
	iOffset = (TUint16)aOffset;
	}

inline TInt TImHeaderEncodingInfo::Offset() const
/** Gets the field offset.

@return Field offset */
	{
	return iOffset;
	}

inline void TImHeaderEncodingInfo::SetLength(const TInt aLength)
/** Sets the field length.

@param aLength Field length */
	{
	iLength = (TUint16)aLength;
	}


inline TInt TImHeaderEncodingInfo::Length()  const
/** Gets the field length.

@return Field length */
	{
	return iLength;
	}


void TImHeaderEncodingInfo::SetCharsetUid(const TUint aUid)
/** Sets the character set UID.

@param aUid Character set UID */
	{
	iCharsetUid = aUid;
	}


TUint TImHeaderEncodingInfo::CharsetUid() const
/** Gets the character set UID.

@return Character set UID */
	{
	return iCharsetUid;
	}


inline void TImHeaderEncodingInfo::SetEncodingType(const TDesC8& aChar)
/** Sets the encoding type (string).

@param aChar Encoding type */
	{
	// If invalid, defaults to QPEncoding
	if (aChar[0] == 'b' || aChar[0] == 'B')
		iType = TImHeaderEncodingInfo::EBase64;
	else if (aChar[0] == 'q' || aChar[0] == 'Q')
		iType = TImHeaderEncodingInfo::EQP;
	else
		iType = TImHeaderEncodingInfo::ENoEncoding;
	}

inline void TImHeaderEncodingInfo::SetEncodingType(const TEncodingType aType)
/** Sets the encoding type (enumeration).

@param aType Encoding type */
	{
	iType = aType;
	}


inline TImHeaderEncodingInfo::TEncodingType TImHeaderEncodingInfo::EncodingType()  const
/** Gets the encoding type (enumeration).

@return Encoding type */
	{
	return iType;
	}

inline void TImHeaderEncodingInfo::SetArrayValue(const TInt aValue)
/** Sets the array value.

@param aValue Array value */
	{
	iArrayValue = (TUint16)aValue;
	}


inline TInt TImHeaderEncodingInfo::ArrayValue()  const
/** Gets the array value.

@return Array value */
	{
	return iArrayValue;
	}


inline void TImHeaderEncodingInfo::SetAddSpace(const TBool atrueFalse)
/** Sets if a space character needs adding between two adjoining encoded-words.

@param atrueFalse True to add a space character */
	{
	iAddSpace = atrueFalse;
	}


inline  TBool TImHeaderEncodingInfo::AddSpace() const
/** Tests if the add space character flag is set.

@return True for added space characters */
	{
	return iAddSpace;
	}

inline void TImHeaderEncodingInfo::SetEncodedLength(const TInt aLength)
/** Sets the encoded length.

@param aLength Encoded length */
	{
	iEncodedLength = (TInt8) aLength;
	}

inline TInt TImHeaderEncodingInfo::EncodedLength() const
/** Gets the encoded length.

@return Encoded length */
	{
	return iEncodedLength + (AddSpace() ? 1 : 0);
	}

//----------------------------------------------------------------------------------------

inline CDesCArray& CImHeader::ToRecipients ()
/** Gets a list of "To" recipients.

@return Recipient list */
	{
	return *iTo;
	}

inline CDesCArray& CImHeader::CcRecipients ()
/** Gets a list of "Cc" recipients.

@return Recipient list */
	{
	return *iCc;
	}
	
inline CDesCArray& CImHeader::BccRecipients()
/** Gets a list of "Bcc" recipients.

@return Recipient list */
	{
	return *iBcc;
	}

inline const CDesCArray& CImHeader::ToRecipients () const 
/** Gets a const list of "To" recipients.

@return Recipient list */
	{
	return *iTo;
	}

inline const CDesCArray& CImHeader::CcRecipients () const
/** Gets a const list of "Cc" recipients.

@return Recipient list */
	{
	return *iCc;
	}
	
inline const CDesCArray& CImHeader::BccRecipients() const
/** Gets a const list of "Bcc" recipients.

@return Recipient list */
	{
	return *iBcc;
	}

//-------------------------------------------------------------------------------------
//---------------------------- Used for forwarding an email ---------------------------

inline CDesCArray& CImHeader::ResentToRecipients ()
	{
	return *iResentTo;
	}

inline CDesCArray& CImHeader::ResentCcRecipients ()
	{
	return *iResentCc;
	}
	
inline CDesCArray& CImHeader::ResentBccRecipients()
	{
	return *iResentBcc;
	}

inline const CDesCArray& CImHeader::ResentToRecipients () const 
	{
	return *iResentTo;
	}

inline const CDesCArray& CImHeader::ResentCcRecipients () const
	{
	return *iResentCc;
	}
	
inline const CDesCArray& CImHeader::ResentBccRecipients() const
	{
	return *iResentBcc;
	}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

inline const TUint CImHeader::RemoteSize() const
	{
	return iRemoteSize;
	}

inline void CImHeader::SetRemoteSize( TUint aRemoteSize )
	{
	iRemoteSize = aRemoteSize;
	}


inline const TUint16 CImHeader::Version() const
	{
	return iVersion;
	}

inline void CImHeader::SetVersion( TUint16 aVersion )
	{
	iVersion = aVersion;
	}

inline CArrayFix<TImHeaderEncodingInfo>& CImHeader::EncodingInfo()
/** Gets information relating to the encoding of header fields in received email. 

This includes the charset. This information can be used when forwarding the 
email, to re-encode the header fields.

@return Encoding information */
	{
	return *iEncodingInfo;
	}

inline const CArrayFix<TImHeaderEncodingInfo>& CImHeader::EncodingInfo() const
/** Gets const information relating to the encoding of header fields in received 
email. 

This includes the charset. This information can be used when forwarding the 
email, to re-encode the header fields.

@return Encoding information */
	{
	return *iEncodingInfo;
	}

//////////////////////////////////////////////////////////////
//															//
//////////////////////////////////////////////////////////////


inline TBool TMsvEmailEntry::Encrypted() const
/** Tests whether encryption is used.

Not currently used.

@return True if encryption is used */
	{
	return iMtmData1&KMsvEmailEntryEncryptedFlag;
	}

inline void TMsvEmailEntry::SetEncrypted(TBool aFlag)
/** Sets whether encryption is used.

Not currently used.

@param aFlag True if encryption is used */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryEncryptedFlag) | (aFlag?KMsvEmailEntryEncryptedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Signed() const
/** Tests whether signing is used.

Not currently used.

@return True if signing is used */
	{
	return iMtmData1&KMsvEmailEntrySignedFlag;
	}

inline void TMsvEmailEntry::SetSigned(TBool aFlag)
/** Sets whether signing is used.

Not currently used.

@param aFlag True if signing is used */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntrySignedFlag) | (aFlag?KMsvEmailEntrySignedFlag:KMsvEmailEntryClearFlag);
	}

///
inline TBool TMsvEmailEntry::MHTMLEmail() const
/** Returns the flag indicating if the message has an HTML body part.

Note: the flag is for HTML and not only MHTML.

Use CImEmailMessage to retrieve the HTML body part.

@return True if the message has an HTML body part
@see CImEmailMessage
*/
	{
	return iMtmData1&KMsvEmailEntryMHTMLFlag;
	}

inline void TMsvEmailEntry::SetMHTMLEmail(TBool aFlag)
/** Sets the flag indicating if the message has an HTML body part.

Note: the flag is for HTML and not only MHTML.

Use CImEmailMessage to retrieve the HTML body part.

@param aFlag True if the message has an HTML body part
@see CImEmailMessage
*/
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryMHTMLFlag) | (aFlag?KMsvEmailEntryMHTMLFlag:KMsvEmailEntryClearFlag);
	}

///
inline TBool TMsvEmailEntry::BodyTextComplete() const
/** Tests if body text is complete.

@return True if body text is complete. */
	{
	return iMtmData1 & KMsvEmailEntryBodyTextCompleteFlag;
	}

inline void TMsvEmailEntry::SetBodyTextComplete(TBool aFlag)
/** Sets if body text is complete.

@param aFlag True if body text is complete. */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryBodyTextCompleteFlag) | (aFlag?KMsvEmailEntryBodyTextCompleteFlag:KMsvEmailEntryClearFlag);
	}

///
inline TBool TMsvEmailEntry::VCard() const
/** Tests if the message contains a VCard attachment.

@return True if the message contains a VCard attachment */
	{
	return iMtmData1&KMsvEmailEntryVCardFlag;
	}

inline void TMsvEmailEntry::SetVCard(TBool aFlag)
/** Sets a flag that the message contains a VCard attachment.

@param aFlag True if the message contains a VCard attachment */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryVCardFlag) | (aFlag?KMsvEmailEntryVCardFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::VCalendar() const
/** Tests if the message contains a VCal attachment.

@return True if the message contains a VCal attachment */
	{
	return iMtmData1&KMsvEmailEntryVCalendarFlag;
	}

inline void TMsvEmailEntry::SetVCalendar(TBool aFlag)
/** Sets a flag that the message contains a VCal attachment.

@param aFlag True if the message contains a VCal attachment */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryVCalendarFlag) | (aFlag?KMsvEmailEntryVCalendarFlag:KMsvEmailEntryClearFlag);
	}

//

inline TBool TMsvEmailEntry::Receipt() const
/** Tests if the email message requests a receipt.

@return True if the email message requests a receipt */
	{
	return iMtmData1&KMsvEmailEntryReceiptFlag;
	}

inline void TMsvEmailEntry::SetReceipt(TBool aFlag)
/** Sets a flag that the email message requests a receipt.

@param aFlag True if the email message requests a receipt */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryReceiptFlag) | (aFlag?KMsvEmailEntryReceiptFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::UnreadIMAP4Flag() const
/** Gets the state of the "Unread" IMAP4 flag.

@return "Unread" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4UnreadFlag;
	}

inline void TMsvEmailEntry::SetUnreadIMAP4Flag(TBool aFlag)
/** Sets the state of the "Unread" IMAP4 flag.

@param aFlag "Unread" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4UnreadFlag) | (aFlag?KMsvEmailEntryIMAP4UnreadFlag:KMsvEmailEntryClearFlag);
	}

inline TBool TMsvEmailEntry::SeenIMAP4Flag() const
/** Gets the state of the "Seen" IMAP4 flag.

@return "Seen" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4SeenFlag;
	}

inline void TMsvEmailEntry::SetSeenIMAP4Flag(TBool aFlag)
/** Sets the state of the "Seen" IMAP4 flag.

@param aFlag "Seen" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4SeenFlag) | (aFlag?KMsvEmailEntryIMAP4SeenFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::AnsweredIMAP4Flag() const
/** Gets the state of the "Answered" IMAP4 flag.

@return "Answered" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4AnsweredFlag;
	}

inline void TMsvEmailEntry::SetAnsweredIMAP4Flag(TBool aFlag)
/** Sets the state of the "Answered" IMAP4 flag.

@param aFlag "Answered" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4AnsweredFlag) | (aFlag?KMsvEmailEntryIMAP4AnsweredFlag:KMsvEmailEntryClearFlag);
	}



inline TBool TMsvEmailEntry::FlaggedIMAP4Flag() const
/** Gets the state of the "Flagged" IMAP4 flag.

@return "Flagged" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4FlaggedFlag;
	}

inline void TMsvEmailEntry::SetFlaggedIMAP4Flag(TBool aFlag)
/** Sets the state of the "Flagged" IMAP4 flag.

@param aFlag "Flagged" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4FlaggedFlag) | (aFlag?KMsvEmailEntryIMAP4FlaggedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::DeletedIMAP4Flag() const
/** Gets the state of the "Deleted" IMAP4 flag.

@return "Deleted" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4DeletedFlag;
	}

inline void TMsvEmailEntry::SetDeletedIMAP4Flag(TBool aFlag)
/** Sets the state of the "Deleted" IMAP4 flag.

@param aFlag "Deleted" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4DeletedFlag) | (aFlag?KMsvEmailEntryIMAP4DeletedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::DraftIMAP4Flag() const
/** Gets the state of the "Draft" IMAP4 flag.

@return "Draft" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4DraftFlag;
	}

inline void TMsvEmailEntry::SetDraftIMAP4Flag(TBool aFlag)
/** Sets the state of the "Draft" IMAP4 flag.

@param aFlag "Draft" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4DraftFlag) | (aFlag?KMsvEmailEntryIMAP4DraftFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::RecentIMAP4Flag() const
/** Gets the state of the "Recent" IMAP4 flag.

@return "Recent" IMAP4 flag */
	{
	return iMtmData1&KMsvEmailEntryIMAP4RecentFlag;
	}

inline void TMsvEmailEntry::SetRecentIMAP4Flag(TBool aFlag)
/** Sets the state of the "Recent" IMAP4 flag.

@param aFlag "Recent" IMAP4 flag */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4RecentFlag) | (aFlag?KMsvEmailEntryIMAP4RecentFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Mailbox() const
/** Tests if the specified folder is the IMAP4 Mailbox.

@return True if the specified folder is the Mailbox */
	{
	return iMtmData1&KMsvEmailEntryIMAP4MailboxFlag;
	}

inline void TMsvEmailEntry::SetMailbox(TBool aFlag)
/** Sets if the specified folder is the IMAP4 Mailbox.

@param aFlag True if the specified folder is the Mailbox */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4MailboxFlag) | (aFlag?KMsvEmailEntryIMAP4MailboxFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Orphan() const
/** Gets the IMAP4 orphaned state for the specified message/folder.

@return True if the specified entry is orphaned */
	{
	return iMtmData1&KMsvEmailEntryOrphanFlag;
	}

inline void TMsvEmailEntry::SetOrphan(TBool aFlag)
/** Sets the IMAP4 orphaned state for the specified message/folder.

@param aFlag True if the specified entry is orphaned */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryOrphanFlag) | (aFlag?KMsvEmailEntryOrphanFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::ValidUID() const
/** Gets the IMAP4 UID (unique identifier) validity for the specified folder.

@return True if IMAP4 UID validity is set */
	{
	return iMtmData1&KMsvEmailEntryIMAP4ValidUIDFlag;
	}

inline void TMsvEmailEntry::SetValidUID(TBool aFlag)
/** Sets the IMAP4 UID (unique identifier) validity for the specified folder.

@param aFlag True if IMAP4 UID validity is set */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4ValidUIDFlag) | (aFlag?KMsvEmailEntryIMAP4ValidUIDFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Subscribed() const
/** Gets the IMAP4 subscription state for the specified folder.

@return IMAP4 subscription state */
	{
	return iMtmData1&KMsvEmailEntryIMAP4SubscribedFlag;
	}

inline void TMsvEmailEntry::SetSubscribed(TBool aFlag)
/** Sets the IMAP4 subscription state for the specified folder.

@param aFlag IMAP4 subscription state */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4SubscribedFlag) | (aFlag?KMsvEmailEntryIMAP4SubscribedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::LocalSubscription() const
/** Gets the IMAP4 local subscription state for the specified folder.

@return IMAP4 local subscription state */
	{
	return iMtmData1&KMsvEmailEntryIMAP4LocalSubFlag;
	}

inline void TMsvEmailEntry::SetLocalSubscription(TBool aFlag)
/** Sets the IMAP4 local subscription state for the specified folder.

@param aFlag IMAP4 local subscription state */
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4LocalSubFlag) | (aFlag?KMsvEmailEntryIMAP4LocalSubFlag:KMsvEmailEntryClearFlag);
	}


inline TUint32 TMsvEmailEntry::UID() const
/** Gets the IMAP4 UID (unique identifier) for the specified message/folder.

@return IMAP4 UID */
	{
	return (TUint32)iMtmData2;	// hide the casting away from the caller
	}

inline void TMsvEmailEntry::SetUID(TUint32 aUID)
/** Sets the IMAP4 UID (unique identifier) for the specified message/folder.

@param aUID IMAP4 UID */
	{
	iMtmData2 = (TInt32) aUID;	// hide the casting away from the user
	}

inline TInt TMsvEmailEntry::RemoteFolderEntries() const
/** Gets the number of messages stored in the remote folder.

@return Number of messages */
	{
	return iMtmData3&KMsvRemoteFolderEntriesMask;
	}

inline void TMsvEmailEntry::SetRemoteFolderEntries(TInt aEntries)
/** Sets the number of messages stored in the remote folder.

@param aEntries Number of messages */
	{
	iMtmData3 = (TInt32) ((iMtmData3 & ~KMsvRemoteFolderEntriesMask) | (aEntries & KMsvRemoteFolderEntriesMask));
	}


//////////////////////////////////////////////////////////////
//				CImMimeHeader inlines						//
//////////////////////////////////////////////////////////////


inline const CDesC8Array& CImMimeHeader::ContentTypeParams() const 
/** Gets the const Content-Type parameters and their associated values.

@return Parameters and associated values */
	{
	return *iContentTypeParams;
	}


inline const CDesC8Array& CImMimeHeader::ContentDispositionParams() const
/** Gets the const Content-Disposition parameters and their associated values.

@return Parameters and associated values */
	{
	return *iContentDispositionParams;
	}


inline const CDesC8Array& CImMimeHeader::XTypeParams() const
/** Gets the const MIME header parameters and their associated values.

This can be used by any MIME header fields.

@return Parameters and associated values */
	{
	return *iXTypeParams;
	}



inline CDesC8Array& CImMimeHeader::ContentTypeParams()
/** Gets the Content-Type parameters and their associated values.

@return Parameters and associated values */	{
	return *iContentTypeParams;
	}


inline CDesC8Array& CImMimeHeader::ContentDispositionParams()
/** Gets the Content-Disposition parameters and their associated values.

@return Parameters and associated values */
	{
	return *iContentDispositionParams;
	}


inline CDesC8Array& CImMimeHeader::XTypeParams()
/** Gets the MIME header parameters and their associated values.

This can be used by any MIME header fields.

@return Parameters and associated values */
	{
	return *iXTypeParams;
	}


inline const TUint16 CImMimeHeader::Version() const
	{
	return iVersion;
	}

inline void CImMimeHeader::SetVersion( TUint16 aVersion )
	{
	iVersion = aVersion;
	}
