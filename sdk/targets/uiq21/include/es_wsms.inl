// WS_ADDR.INL
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

/**
 *  @file   was_addr.inl
 *
 *  Publich access to the WapPorts and the WapAddresses - this file is exported
 */

inline TWapPortNumber TWapAddr::WapPort() const
/**
 *  Return wap port number
 */
    {
    return TWapPortNumber(Port());
    }

inline void TWapAddr::SetWapPort(TWapPortNumber aPort)
/**
 * Set wap port number
 */
    {
    SetPort(TUint(aPort));
    }

inline void TWapAddr::SetWapAddress(const TDesC8& aTel)
/**
 * Set the wap address
 */
    {
    Mem::Copy(UserPtr(),aTel.Ptr(),aTel.Length()<EMaxWapAddressLength ? aTel.Length() : EMaxWapAddressLength);
    SetUserLen(aTel.Length());
    }


inline TPtrC8 TWapAddr::WapAddress() const
/**
 * Return the wap address
 */
    {
    return TPtrC8(UserPtr(),CONST_CAST(TWapAddr*,this)->GetUserLen());
    }

inline TBool TWapAddr::operator==(const TWapAddr& anAddr) const
/**
 * Comparison operator
 */
    {
    if (WapPort()==anAddr.WapPort())
        return ETrue;
    return EFalse;
    }
