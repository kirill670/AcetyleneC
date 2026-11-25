// SimTsy.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file SimTsy.h
 *
 * External header file for the Simulator TSY.
 */

#ifndef __SIMTSY_H__
#define __SIMTSY_H__

// Uids used for The Simulator TSY System Agent.
// 20 Uids has been allocated for this purpose. Some of these are unused at present.
// 
#define KUidSASimTsyValue		(0x101F4126)	/// < First Uid allocated for the Sim TSY
#define KUidSASimTsyEndValue	(0x101F4139)	/// < Last Uid allocated for the Sim TSY

const TUid KUidSASimTsy = {KUidSASimTsyValue};			/// < First UID reserved for Simulator TSY SA
const TUid KUidSASimTsyEnd = {KUidSASimTsyEndValue};	/// < Last UID reserved for Simulator TSY SA

#define KUidSASimTsyIncomingVoiceCallValue (KUidSASimTsyValue)						/// < UID value for simulating an incoming Voice Call
const TUid KUidSASimTsyIncomingVoiceCall = {KUidSASimTsyIncomingVoiceCallValue};	/// < UID for simulating an incoming Voice Call via the System Agent

#define KUidSASimTsyTestNumberValue (KUidSASimTsyValue+1)			/// < UID value for test number.
const TUid KUidSASimTsyTestNumber= {KUidSASimTsyTestNumberValue};	/// < UID for test number.

#define KUidSASimTsyIncomingDataCallValue {KUidSASimTsyValue+2}					/// < UID value for simulating an incoming Data Call
const TUid KUidSASimTsyIncomingDataCall = {KUidSASimTsyIncomingDataCallValue};	/// < UID for simulating an incoming Data Call

_LIT(KConfigFilename,"config.txt");			/// < Configuration filename.
_LIT(KPhoneName,"SimulatorPhone");			///< The name of the phone supported by the Simulator TSY.
_LIT(KVoiceLineName,"Voice");		///< The name of the voice line supported by the Simulator TSY.
_LIT(KDataLineName,"Data");			///< The name of the data line supported by the Simulator TSY.

#endif

