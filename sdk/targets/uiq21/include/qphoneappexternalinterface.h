// QPHONEAPPEXTERNALINTERFACE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __QPHONEAPPEXTERNALINTERFACE_H__
#define __QPHONEAPPEXTERNALINTERFACE_H__

#include <E32Std.h>
#include <cntdef.h>

const TInt KPhoneNumMaxLength = 127;

const TUid KUidPhoneApp={0x100051f1}; // the phone app must use this UID
const TUid KUidPhoneAppView={0x100051f2}; // the DNL view in a phone app must use this UID

/**
 * DNL to phone app with a contact as parameter
 */
const TUid KUidCntDnlPhone={0x100051f3};

class TCntDnlPhone
	{
public:
	TContactItemId iContactId; // id of the contact to be dialled
	TInt iFieldId; // id of field to be dialled, in the contact context
	TBufC<KPhoneNumMaxLength> iNumber; // descriptor containing the phone number to be dialled
	};

typedef TPckgBuf<TCntDnlPhone> TCntDnlPhoneBuf;

/**
 * DNL to phone app with only a phone number as parameter
 */
const TUid KUidNumDnlPhone={0x10005FE6};

class TNumDnlPhone
	{
public:
	TBufC<KPhoneNumMaxLength> iNumber; // descriptor containing the phone number to be dialled
	};

typedef TPckgBuf<TNumDnlPhone> TNumDnlPhoneBuf;

#endif // __QPHONEAPPEXTERNALINTERFACE_H__
