// Quartz.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QUARTZ_H__
#define __QUARTZ_H__

#include <qikcolor.hrh>

_LIT(KQuartzBitmapStore,"z:\\System\\Data\\quartz.mbm");


//Define Channel Uid:s for different notifier channels.

//Dialogs
const TUid KQuartzScreenOutputChannel = {0x10009D48};

//Leds & Audio
const TUid KQuartzLedOutputChannel = {0x10009D46}; // Deprecated
const TUid KQuartzAudioOutputChannel = {0x10009D47}; // Deprecated

#endif
