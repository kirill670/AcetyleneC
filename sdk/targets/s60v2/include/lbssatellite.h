/*
* ==============================================================================
*  Name        : LbsSatellite.h
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
// LbsSatellite.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSSATELLITE_H__
#define __LBSSATELLITE_H__

#include <LbsPosition.h>
#include <LbsPositionInfo.h>

const TUint KPositionMaxSatellitesInView = 20;


/**
 * This class is used to transfer data about a satellite
 */
class TSatelliteData
	{
public:
    /**
     * Default constructor for a TSatelliteData.
     * Note the azimuth and elevation are both initially NaN.
     */
	IMPORT_C TSatelliteData();

    /**
     * @return The Satellite ID
     */
	IMPORT_C TInt SatelliteId() const;

    /**
     * @param aSatelliteId The satellite ID to be set
     */
	IMPORT_C void SetSatelliteId(TInt aSatelliteId);

    /**
     * @return The satellite azimuth
     */
	IMPORT_C TReal32 Azimuth() const;

    /**
     * @param aAzimuth The satellite azimuth to be set
     */
	IMPORT_C void SetAzimuth(TReal32 aAzimuth);

    /**
     * @return The satellite elevation
     */
	IMPORT_C TReal32 Elevation() const;

    /**
     * @param aElevation The satellite elevation to be set
     */
	IMPORT_C void SetElevation(TReal32 aElevation);

    /**
     * @return Whether this satellite is used
     */
	IMPORT_C TBool IsUsed() const;

    /**
     * @param aIsUsed Whether this satellite will be used
     */
	IMPORT_C void SetIsUsed(TBool aIsUsed);

    /**
     * @return The signal strength
     */
	IMPORT_C TInt SignalStrength() const;

    /**
     * @param aSignalStrength The signal strength to set
     */
	IMPORT_C void SetSignalStrength(TInt aSignalStrength);

protected:
	/** The ID (in GPS, the PRN) */
	TInt    iSatelliteId;
	/** The azimuth, in degrees */
	TReal32 iAzimuth;
	/** The elevation, in degrees */
	TReal32 iElevation;
	/** Whether the satellite is used */
	TBool   iIsUsed;
	/** The signal strength, in decibels */
	TInt    iSignalStrength;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};

/**
 * This class is used to store information about positions obtained by satellites.
 */
class TPositionSatelliteInfo : public TPositionCourseInfo
	{
public:
    /**
     * TPositionSatelliteInfo constructor.
     * Note the the horizontal and vertical dilution of precision values are initially NaN.
     */
	IMPORT_C TPositionSatelliteInfo();

    /**
     * @param aIndex The index of the satellite whose data is requested
     * @param aSatelliteData The TSatelliteData structure where the data will be placed
     * @return KErrNone if successful, KErrNotFound otherwise
     */
	IMPORT_C TInt GetSatelliteData(TUint aIndex, TSatelliteData& aSatelliteData) const;

    /**
     * @param aSatelliteData The data to append
     * @return KErrNone if successful, KErrOverflow otherwise
     */
	IMPORT_C TInt AppendSatelliteData(const TSatelliteData& aSatelliteData);

    /**
     * @return The number of satellites in view
     */
	IMPORT_C TInt NumSatellitesInView() const;

    /**
     * Reset the number of satellites in view
     */
	IMPORT_C void ClearSatellitesInView();

    /**
     * @return The number of satellites used in the calculation
     */
	IMPORT_C TInt NumSatellitesUsed() const;

    /**
     * @return The time according to the satellite
     */
	IMPORT_C TTime SatelliteTime() const;

    /**
     * @param aTime The satellite time to be set
     */
	IMPORT_C void SetSatelliteTime(TTime aTime);

    /**
     * @return The horizontal dilution of precision
     */
	IMPORT_C TReal32 HorizontalDoP() const;

    /**
     * @return The vertical dilution of precision
     */
	IMPORT_C TReal32 VerticalDoP() const;

    /**
     * @return The time dilution of precision
     */
	IMPORT_C TReal32 TimeDoP() const;

    /**
     * @param aDoPValue The horizontal dilution of precision to be set
     */
	IMPORT_C void SetHorizontalDoP(TReal32 aDoPValue);

    /**
     * @param aDoPValue The vertical dilution of precision to be set
     */
	IMPORT_C void SetVerticalDoP(TReal32 aDoPValue);

    /**
     * @param aDoPValue The time dilution of precision to be set
     */
	IMPORT_C void SetTimeDoP(TReal32 aDoPValue);

protected:
	/** The number of satellites in view */
	TUint iNumSatellitesInView;
	/** The number of satellites used */
	TUint iNumSatellitesUsed;
	/** The time according to the satellite */
	TTime iSatelliteTime;
	/** The horizontal dilution of precision */
	TReal32 iHorizontalDoPValue;
	/** The vertical dilution of precision */
	TReal32 iVerticalDoPValue;
	/** The time dilution of precision */
	TReal32 iTimeDoPValue;
	/** The satellites in view */
	TFixedArray<TSatelliteData, KPositionMaxSatellitesInView> iSatellitesInView;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[24];
	};

#endif //__LBSSATELLITE_H__
