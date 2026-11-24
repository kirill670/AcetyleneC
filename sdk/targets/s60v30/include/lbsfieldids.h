/*
* ==============================================================================
*  Name        : LbsFieldIds.h
*  Part of     : Mobile Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Position data Fields
*  Version     :
*
*  Copyright (c) 2002-2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __LBSFIELDIDS_H__
#define __LBSFIELDIDS_H__

#include <e32std.h>

/**
 * Standard position field identifiers
 */
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
	EPositionFieldTrueCourse,
	EPositionFieldTrueCourseError,
	EPositionFieldMagneticCourse,
	EPositionFieldMagneticCourseError,

	EPositionFieldCompassCapabilitiesBegin		= 300,	// Compass Capabilities
	EPositionFieldHeading, 
	EPositionFieldHeadingError,
	EPositionFieldMagneticHeading, 
	EPositionFieldMagneticHeadingError,

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
	EPositionFieldMediaLinks,
	EPositionFieldMediaLinksStart,
	EPositionFieldMedaiLinksEnd					= 899,


	EPositionFieldProprietaryFieldsBegin		= 0x8000,

	EPositionFieldIdLast = KMaxTUint16
	};

#endif	//__LBSFIELDIDS_H__
