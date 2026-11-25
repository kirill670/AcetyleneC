// $Workfile: MmsRecipient.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 3 $
// $Date: 11/12/01 16:49 $
//

/** @file
 * This file contains inline function definitions for the CMmsRecipient class.
 */


#ifndef __MMSRECIPIENT_INL__
#define __MMSRECIPIENT_INL__


inline void CMmsRecipient::SetDeliveryReportReceived()
    {
    iDeliveryReportReceived = ETrue;
    }

inline TBool CMmsRecipient::DeliveryReportReceived() const
    {
    return iDeliveryReportReceived;
    }

inline TPtrC CMmsRecipient::Address() const
    {
    return TPtrC(*iAddress);
    }

inline MmsAddressParser::TMmsAddressType CMmsRecipient::AddressType() const
    {
    return iAddressType;
    }


#endif // __MMSRECIPIENT_INL__