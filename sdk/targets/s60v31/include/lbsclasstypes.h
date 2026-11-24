/*
* ==============================================================================
*  Name        : LbsClassTypes.h
*  Part of     : Mobile Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Position data class' types
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

#ifndef __LBSCLASSTYPES_H__
#define __LBSCLASSTYPES_H__

enum TPositionClassFamily
	{
	EPositionInfoFamily,
	EPositionModuleInfoFamily,
	EPositionModuleStatusFamily,
	EPositionModuleStatusEventFamily,
	EPositionModuleQualityFamily,
	EPositionPositionCriteriaFamily,
	EPositionUpdateOptionsFamily,

	EPositionLastFamily = 20
	};

/**
 * Position quality class types
 */
enum _TPositionQualityClassType
	{
	EPositionQualityUnknownClass		= 0,
	EPositionQualityClass				= 0x01,
	EPositionQualityFirstCustomClass	= 0x01000000
	};

/**
 * Position module information class types
 */
enum _TPositionModuleInfoClassType
	{
	EPositionModuleInfoUnknownClass		= 0,
	EPositionModuleInfoClass			= 0x01,
	EPositionModuleInfoFirstCustomClass	= 0x01000000
	};

/**
 * Position module status class types
 */
enum _TPositionModuleStatusClassType
	{
	EPositionModuleStatusUnknownClass		= 0,
	EPositionModuleStatusClass				= 0x01,
	EPositionModuleStatusFirstCustomClass	= 0x01000000
	};

/**
 * Position module status event class types
 */
enum _TPositionModuleStatusEventClassType
	{
	EPositionModuleStatusEventUnknownClass		= 0,
	EPositionModuleStatusEventClass				= 0x01,
	EPositionModuleStatusEventFirstCustomClass	= 0x01000000
	};

/**
 * Position update options class types
 */
enum _TPositionUpdateOptionsClassType
	{
	EPositionUpdateOptionsUnknownClass		= 0,
	EPositionUpdateOptionsClass				= 0x01,
	EPositionUpdateOptionsFirstCustomClass	= 0x01000000
	};

/**
 * TPositionInfoBase derived classes class types
 */
enum _TPositionInfoClassType
	{
	EPositionInfoUnknownClass		= 0,
	EPositionInfoClass				= 0x01,
	EPositionGenericInfoClass		= 0x02,
	EPositionCourseInfoClass		= 0x04,
	EPositionSatelliteInfoClass		= 0x08,
	EPositionInfoFirstCustomClass	= 0x01000000
	};

/**
 * TPositionCriteriaBase derived classes class types
 */
enum _TPositionCriteriaClassType
	{
	EPositionCriteriaUnknownClass		= 0,
	EPositionCriteriaClass				= 0x01,
	EPositionCriteriaFirstCustomClass	= 0x01000000
	};

typedef TUint32 TPositionInfoClassType;


//__LBSCLASSTYPES_H__
#endif
