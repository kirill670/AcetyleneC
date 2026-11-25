/*
* ==============================================================================
*  Name        : wldtools.h
*  Part of     : WLDTOOLS
*  Interface   : WORLDSERVER TOOLS API
*  Description : Contains definitions used in both the World Server and the World Server database generating tool.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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


#ifndef WLDTOOLS_H
#define WLDTOOLS_H

// INCLUDES
#include <e32std.h>

// CONSTANTS
/**
 * @internal 
 */
const TInt KWldToolsMajorVersionNumber=1;
/**
 * @internal 
 */
const TInt KWldToolsMinorVersionNumber=1;
/**
 * @internal 
 */
const TInt KWldToolsBuildVersionNumber=26;
/**
 * @internal 
 */
const TInt KUidDataFile=268435920; // 0x100001D0
/**
 * @internal 
 */
const TInt KUidWorldRomData=268435884; // 0x100001AC
/**
 * @internal 
 */
const TInt KUidWorldRomDataCompression1=268435885; // 0x100001AD
/**
 * @internal 
 */
const TInt KUidWorldRomDataFormat2=0x1000AF57;
/**
 * @internal 
 */
const TInt KWldToolsExtraHeaderInfo=40;
/**
 * @internal 
 */
const TInt KWldToolsSizeID=1;
/**
 * @internal 
 */
const TInt KWldToolsSizeOffset=2;
/**
 * @internal 
 */
const TInt KWldToolsSizeUids=16;
/**
 * @internal 
 */
const TInt KWldToolsSizeHeader=20+KWldToolsExtraHeaderInfo;
/**
 * @internal 
 */
const TInt KWldToolsSizeNameLen=1;
/**
 * @internal 
 */
const TInt KWldToolsSizeIndexChar=2;
/**
 * @internal 
 */
const TInt KWldToolsSizeNibDialLen=1;
/**
 * @internal 
 */
const TInt KWldToolsSizeDescription=32;
/**
 * @internal 
 */
const TInt KWldToolsSizeBitCity=12; // sizeof(TBitPackableCityData)
/**
 * @internal 
 */
const TInt KWldToolsSizeOfFixedWidthCityEntry_Format2=(2*KWldToolsSizeOffset)+KWldToolsSizeBitCity; // data structure is: offset-to-variable-width-city-entry, offset-to-fixed-width-country-entry, TBitPackableCityData-data-structure
/**
 * @internal 
 */
const TInt KWldToolsSizeOfFixedWidthCountryEntry_Format2=3*KWldToolsSizeOffset; // data structure is: offset-to-variable-width-country-entry, offset-to-fixed-width-city-entry-of-capital, ISO-code
/**
 * @internal 
 */
const TInt KWldToolsOffsetToCities_Format2=8; // this replaces KWldToolsOffCityIndex - the data structure is: number-of-cities (2-bytes), all-the-fixed-width-city-entries-in-order
/**
 * @internal 
 */
const TInt KWldToolsOffsetToCountries_Format2=10; // this replaces KWldToolsOffCountryIndex - the data structure is: number-of-countries (2-bytes), all-the-fixed-width-country-entries-in-order
/**
 * @internal 
 */
const TInt KWldToolsOffHeader=KWldToolsSizeUids;
/**
 * @internal 
 */
const TInt KWldToolsOffDescrip=KWldToolsOffHeader+KWldToolsSizeHeader;
/**
 * @internal 
 */
const TInt KWldToolsOffReleaseId=0;
/**
 * @internal 
 */
const TInt KWldToolsOffDaysOffset=2;
/**
 * @internal 
 */
const TInt KWldToolsOffSpare1=4; // set to 1
/**
 * @internal 
 */
const TInt KWldToolsOffReleaseVersion=5;
/**
 * @internal 
 */
const TInt KWldToolsOffDescription=6;
/**
 * @internal 
 */
const TInt KWldToolsOffCityIndex=8; // superseded in format 2 by KWldToolsOffsetToCities_Format2
/**
 * @internal 
 */
const TInt KWldToolsOffCountryIndex=10; // superseded in format 2 by KWldToolsOffsetToCountries_Format2
/**
 * @internal 
 */
const TInt KWldToolsOffSpare2=12; // set to 0
/**
 * @internal 
 */
const TInt KWldToolsOffLanguageId=13;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCity=14;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCountry=16;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultAltCity=18;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultTimeFormat=36;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultAmPmSpaceBetween=37;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultAmPmSymbolPosition=38;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultTimeSeparator=39;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultDateFormat=47;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultDateSeparator=48;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultStartOfWeek=56;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultWorkDays=57;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultDecimalSeparator=58;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCurrencyTriadsAllowed=60;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultThousandsSeparator=61;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultUnitsFormat=63;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCurrencyDecimalPlaces=64;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCurrencySymbolPosition=65;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCurrencySpaceBetween=66;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultNegativeCurrencyFormat=67;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultExtraNegativeCurrencyFormat=68;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultNitzOn=69;
/**
 * @internal 
 */
const TInt KWldToolsOffDefaultCurrencySymbol=70;
/**
 * @internal 
 */
const TInt KWldToolsDialSpacer=10;
/**
 * @internal 
 */
const TInt KWldToolsDialPause=11;
/**
 * @internal 
 */
const TInt KWldToolsDialSeparator=12;
/**
 * @internal 
 */
const TInt KWldToolsDialUnknown=13;
/**
 * @internal 
 */
const TInt KWldToolsCharLastIndex=0xffff;
/**
 * @internal 
 */
const TInt KWldToolsMaxLat=90*60;
/**
 * @internal 
 */
const TInt KWldToolsMaxLong=180*60;
/**
 * @internal 
 */
const TInt KWldToolsMaxGmt=780;
/**
 * @internal 
 */
const TInt KWldToolsMaxMapX=640;
/**
 * @internal 
 */
const TInt KWldToolsMaxMapY=240;
/**
 * @internal 
 */
const TInt KWldToolsMaxDstNum=31;
/**
 * @internal 
 */
enum TWldToolsDstZoneIndex
    {
    EWldToolsDstIndexNone,
    EWldToolsDstIndexEurope,
    EWldToolsDstIndexNorth,
    EWldToolsDstIndexSouth,
    EWldToolsDstIndexLast
    };
/**
 * @internal 
 */
enum TCityDataBitsSize 
    {
    ECityDataBitsLat=14,        // signed
    ECityDataBitsX=10,          // unsigned
    ECityDataBitsY=8,           // unsigned
    ECityDataBitsLong=15,       // signed
    ECityDataBitsGmt=11,        // signed
    ECityDataBitsDstZone=3,         // unsigned
    ECityDataBitsDstStartOccurence=3,   // unsigned
    ECityDataBitsDstStartDay=3,     // unsigned
    ECityDataBitsDstStartMonth=4,       // unsigned
    ECityDataBitsDstStartNum=5,     // unsigned
    ECityDataBitsDstEndOccurence=3, // unsigned
    ECityDataBitsDstEndDay=3,       // unsigned
    ECityDataBitsDstEndMonth=4,     // unsigned
    ECityDataBitsDstEndNum=5,       // unsigned
    ECityDataBitsSpare=5,       
    ECityDataBitsTotal=96 // Must be a multiple of 8
    };
/**
 * @internal 
 */
#endif  // WLDTOOLS_H

// End of File
