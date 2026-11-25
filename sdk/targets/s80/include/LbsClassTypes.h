/*
* ==============================================================================
*  Name        : LbsClassTypes.h
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
// LbsClassTypes.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//


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
 *
 * @publishedAll
 */
enum _TPositionQualityClassType
	{
	EPositionQualityUnknownClass		= 0,
	EPositionQualityClass				= 0x01,
	EPositionQualityFirstCustomClass	= 0x01000000
	};

/**
 * Position module information class types
 *
 * @publishedAll
 */
enum _TPositionModuleInfoClassType
	{
	EPositionModuleInfoUnknownClass		= 0,
	EPositionModuleInfoClass			= 0x01,
	EPositionModuleInfoFirstCustomClass	= 0x01000000
	};

/**
 * Position module status class types
 *
 * @publishedAll
 */
enum _TPositionModuleStatusClassType
	{
	EPositionModuleStatusUnknownClass		= 0,
	EPositionModuleStatusClass				= 0x01,
	EPositionModuleStatusFirstCustomClass	= 0x01000000
	};

/**
 * Position module status event class types
 *
 * @publishedAll
 */
enum _TPositionModuleStatusEventClassType
	{
	EPositionModuleStatusEventUnknownClass		= 0,
	EPositionModuleStatusEventClass				= 0x01,
	EPositionModuleStatusEventFirstCustomClass	= 0x01000000
	};

/**
 * Position update options class types
 *
 * @publishedAll
 */
enum _TPositionUpdateOptionsClassType
	{
	EPositionUpdateOptionsUnknownClass		= 0,
	EPositionUpdateOptionsClass				= 0x01,
	EPositionUpdateOptionsFirstCustomClass	= 0x01000000
	};

/**
 * TPositionInfoBase derived classes class types
 *
 * @publishedAll
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
 *
 * @publishedAll
 */
enum _TPositionCriteriaClassType
	{
	EPositionCriteriaUnknownClass		= 0,
	EPositionCriteriaClass				= 0x01,
	EPositionCriteriaFirstCustomClass	= 0x01000000
	};

typedef TUint32 TPositionInfoClassType;


#endif //__LBSCLASSTYPES_H__
