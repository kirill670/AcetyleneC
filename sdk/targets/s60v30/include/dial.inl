// DIAL.INL
//
// Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
//

/**
Clears the following flags:

KPhoneNumberMobile

KPhoneNumberUsePulseDial

KPhoneNumberPbxUsePulseDial

KPhoneNumberWaitForDialingTone

KPhoneNumberWaitForProceedTone

KReturnPhoneNumberWithPlusFormat

@publishedAll
@released
@deprecated 9.1
*/
inline void TDialLocation::ClearDialLocationFlags (TUint aFlags)
    {
    iFlags &= ~aFlags;
    }

/**
True if the KReturnPhoneNumberWithPlusFormat flag is set

@publishedAll
@released
@deprecated 9.1
*/
inline TBool TDialLocation::IsReturnPhoneNumberWithPlusFormat() const
    {
    return(iFlags & KReturnPhoneNumberWithPlusFormat);
    }
