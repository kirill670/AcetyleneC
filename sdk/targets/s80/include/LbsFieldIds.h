/*
* ==============================================================================
*  Name        : LbsFieldIds.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsFieldIDs.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSFIELDIDS_H__
#define __LBSFIELDIDS_H__

#include <e32std.h>

enum _TPositionFieldId
	{
	EPositionFieldNone,		//Used to signify a blank field.
	EPositionFieldComment,

	EPositionFieldSpeedCapabilitiesBegin		= 100,	// Speed Capabilities
	EPositionFieldHorizontalSpeed,
	EPositionFieldHorizontalSpeedError,
	EPositionFieldVerticalSpeed,
	EPositionFieldVerticalSpeedError,

	EPositionFieldDirectionCapabilitiesBegin	= 200,	// Direction Capabilities
	EPositionFieldHeading, 
	EPositionFieldHeadingError,

	EPositionFieldCompassCapabilitiesBegin		= 300,	// Compass Capabilities
	EPositionFieldTrueCourse,
	EPositionFieldTrueCourseError,
	EPositionFieldMagneticCourse,
	EPositionFieldMagneticVariation,
	EPositionFieldOrientation,
	EPositionFieldOrientationError,

	EPositionFieldAddressCapabilitiesBegin		= 400,	// Address Capabilities
	EPositionFieldCountry,
	EPositionFieldCountryCode,
	EPositionFieldState,
	EPositionFieldCity,
	EPositionFieldDistrict,
	EPositionFieldStreet,
	EPositionFieldStreetExtension,
	EPositionFieldLocationName,
	EPositionFieldPostalCode,
	EPositionFieldLocality,
	EPositionFieldCrossing1,
	EPositionFieldCrossing2,
	EPositionFieldCounty,

	EPositionFieldBuildingCapabilitiesBegin		= 500,	// Building Capabilities
	EPositionFieldBuildingName,
	EPositionFieldBuildingFloor,
	EPositionFieldBuildingRoom,
	EPositionFieldBuildingZone,
	EPositionFieldBuildingTelephone,

	EPositionFieldNMEACapabilitiesBegin			= 600,	// NMEA Capabilities
	EPositionFieldNMEASentences,
	EPositionFieldNMEASentencesStart,

	EPositionFieldSatelliteCapabilitiesBegin	= 700,	// Satellite Capabilities
	EPositionFieldSatelliteNumInView,
	EPositionFieldSatelliteNumUsed,
	EPositionFieldSatelliteTime,
	EPositionFieldSatelliteHorizontalDoP,
	EPositionFieldSatelliteVerticalDoP,
	EPositionFieldSatelliteTimeDoP,
	EPositionFieldSatellitePositionDoP,
	EPositionFieldSatelliteSeaLevelAltitude,
	EPositionFieldSatelliteGeoidalSeparation,

	EPositionFieldMediaCapabilitiesBegin		= 800,	// Media Capabilities
	EPositionFieldMediaLinks					= EPositionFieldMediaCapabilitiesBegin,
	EPositionFieldMediaLinksStart,

	//EPositionFieldURL is a deprecated field Id and shouldn't be used.
	//EPositionFieldMediaLinksStart should be used instead.
	EPositionFieldURL							= EPositionFieldMediaLinksStart,

	EPositionFieldProprietaryFieldsBegin		= 0x8000,

	EPositionFieldIdLast = KMaxTUint16
	};

#endif	//__LBSFIELDIDS_H__
