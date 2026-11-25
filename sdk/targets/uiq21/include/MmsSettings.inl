// $Workfile: MmsSettings.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 5 $
// $Date: 15/11/01 17:27 $
//


/** @file
 * This file contains inline function definitions for the CMmsSettings class.
 */


#ifndef __MMSSETTINGS_INL__
#define __MMSSETTINGS_INL__


inline TInt CMmsSettings::MaxIncomingMessageSize() const
    {
    return iMaxIncomingMessageSize;
    }
inline void CMmsSettings::SetMaxIncomingMessageSize(TInt aMaxSizeBytes)
    {
    iMaxIncomingMessageSize = aMaxSizeBytes;
    }

inline TBool CMmsSettings::AutomaticFetch() const
    {
	return iAutomaticFetch;
    }
inline void CMmsSettings::SetAutomaticFetch(TBool aEnable)
    {
    iAutomaticFetch = aEnable;
    }

inline TMmsPriority CMmsSettings::DefaultPriority()
    {
    return iDefaultPriority;
    }
inline void CMmsSettings::SetDefaultPriority(TMmsPriority aPriority)
    {
    iDefaultPriority = aPriority;
    }

inline TInt CMmsSettings::DefaultExpiryInterval()
    {
    return iDefaultExpiryInterval;
    }
inline void CMmsSettings::SetDefaultExpiryInterval(TInt aSeconds)
    {
    iDefaultExpiryInterval = aSeconds;
    }

inline TInt CMmsSettings::DefaultDeliveryTimeInterval()
    {
    return iDefaultDeliveryTimeInterval;
    }
inline void CMmsSettings::SetDefaultDeliveryTimeInterval(TInt aSeconds)
    {
    iDefaultDeliveryTimeInterval = aSeconds;
    }

inline TMmsSenderVisibility CMmsSettings::DefaultSenderVisibility()
    {
    return iDefaultSenderVisibility;
    }
inline void CMmsSettings::SetDefaultSenderVisibility(TMmsSenderVisibility aVisibility)
    {
    iDefaultSenderVisibility = aVisibility;
    }

inline TMmsYesNo CMmsSettings::DefaultReadReply()
    {
    return iDefaultReadReply;
    }
inline void CMmsSettings::SetDefaultReadReply(TMmsYesNo aReadReply)
    {
    iDefaultReadReply = aReadReply;
    }

inline TMmsYesNo CMmsSettings::DefaultDeliveryReport()
    {
    return iDefaultDeliveryReport;
    }
inline void CMmsSettings::SetDefaultDeliveryReport(TMmsYesNo aDeliveryReport)
    {
    iDefaultDeliveryReport = aDeliveryReport;
    }


#endif // __MMSSETTINGS_INL__