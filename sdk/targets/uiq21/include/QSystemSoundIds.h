// QSystemSoundIds.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __QSYSTEMSOUNDIDS_H__
#define __QSYSTEMSOUNDIDS_H__

#include <QSystemSoundIds.hrh>	// System sound UIDs
#include <bassnd.h>

// This file define UIQ specific system sound IDs. 
// See QSystemSoundIds.hrh for UID definitions.
// See end of file for complete TBaSystemSoundType definitions!

// Event sound
const TBaSystemSoundUid KQSystemSoundMajorUidEvent = {EQSystemSoundMajorUidEvent};
const TBaSystemSoundUid KQSystemSoundMinorUidEventScreenTap = {EQSystemSoundMinorUidEventScreenTap};
const TBaSystemSoundUid KQSystemSoundMinorUidEventHwButtonPressed = {EQSystemSoundMinorUidEventHwButtonPressed};

// Error sound
const TBaSystemSoundUid KQSystemSoundMajorUidError = {EQSystemSoundMajorUidError};

// Ring
const TBaSystemSoundUid KQSystemSoundMajorUidRing = {EQSystemSoundMajorUidRing};

// Alarm
const TBaSystemSoundUid KQSystemSoundMajorUidAlarm = {EQSystemSoundMajorUidAlarm};

// Message
const TBaSystemSoundUid KQSystemSoundMajorUidMessage = {EQSystemSoundMajorUidMessage};
const TBaSystemSoundUid KQSystemSoundMinorUidMessageNewSms = {EQSystemSoundMinorUidMessageNewSms};
const TBaSystemSoundUid KQSystemSoundMinorUidMessageNewMms = {EQSystemSoundMinorUidMessageNewMms};
const TBaSystemSoundUid KQSystemSoundMinorUidMessageNewEmail = {EQSystemSoundMinorUidMessageNewEmail};
const TBaSystemSoundUid KQSystemSoundMinorUidMessageNewVoiceMessage = {EQSystemSoundMinorUidMessageNewVoiceMessage};
const TBaSystemSoundUid KQSystemSoundMinorUidMessageNewBeamedObject = {EQSystemSoundMinorUidMessageNewBeamedObject};
const TBaSystemSoundUid KQSystemSoundMinorUidMessageNewFax = {EQSystemSoundMinorUidMessageNewFax};

//
// UIQ-specific system sound types
//
#define KQSystemSoundEvent TBaSystemSoundType(KQSystemSoundMajorUidMessage)
#define KQSystemSoundEventScreenTap TBaSystemSoundType(KQSystemSoundMajorUidEvent, KQSystemSoundMinorUidEventScreenTap)
#define KQSystemSoundEventHwButtonPressed TBaSystemSoundType(KQSystemSoundMajorUidEvent, KQSystemSoundMinorUidEventHwButtonPressed)
#define KQSystemSoundError TBaSystemSoundType(KQSystemSoundMajorUidError)
#define KQSystemSoundDefaultRingSignal TBaSystemSoundType(KQSystemSoundMajorUidRing)
#define KQSystemSoundDefaultAlarm TBaSystemSoundType(KQSystemSoundMajorUidAlarm)
#define KQSystemSoundMessageGeneralNew TBaSystemSoundType(KQSystemSoundMajorUidMessage)
#define KQSystemSoundMessageNewSms TBaSystemSoundType(KQSystemSoundMajorUidMessage, KQSystemSoundMinorUidMessageNewSms)
#define KQSystemSoundMessageNewMms TBaSystemSoundType(KQSystemSoundMajorUidMessage, KQSystemSoundMinorUidMessageNewMms)
#define KQSystemSoundMessageNewEmail TBaSystemSoundType(KQSystemSoundMajorUidMessage, KQSystemSoundMinorUidMessageNewEmail)
#define KQSystemSoundMessageNewVoiceMessage TBaSystemSoundType(KQSystemSoundMajorUidMessage, KQSystemSoundMinorUidMessageNewVoiceMessage)
#define KQSystemSoundMessageNewBeamedObject TBaSystemSoundType(KQSystemSoundMajorUidMessage, KQSystemSoundMinorUidMessageNewBeamedObject)
#define KQSystemSoundMessageNewFax TBaSystemSoundType(KQSystemSoundMajorUidMessage, KQSystemSoundMinorUidMessageNewFax)


#endif // __QSYSTEMSOUNDIDS_H__