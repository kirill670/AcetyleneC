// DIAL.INL
// Written by Michael Phan, October 1997
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
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
*/
inline  void TDialLocation::ClearDialLocationFlags (TUint aFlags)
    {
    iFlags &= ~aFlags;
    }

/**
True if the KReturnPhoneNumberWithPlusFormat flag is set

@publishedAll
@released
*/
inline   TBool TDialLocation::IsReturnPhoneNumberWithPlusFormat() const
    {
    return(iFlags & KReturnPhoneNumberWithPlusFormat);
    }

