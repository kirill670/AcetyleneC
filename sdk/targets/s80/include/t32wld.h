/*
* ==============================================================================
*  Name        : t32wld.h
*  Part of     : WorldServer
*  Interface   : WorldServer API
*  Description : World server access class.
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


#ifndef T32WLD_H
#define T32WLD_H

// INCLUDES
#include <e32base.h>

// DATA TYPES
_LIT(KWorldServerName, "WorldServer");
_LIT(KWorldServerImageName, "WorldServer");
//
/**
 * @internal Component
 * @released
 */
const TUid KWorldServerUid = { 0x101F5025 };

/**
 * @internal Component
 * @released
 */
const TInt KWorldServerMajorVN=1;

/**
 * @internal Component
 * @released
 */
const TInt KWorldServerMinorVN=0;

/**
 * @internal Component
 * @released
 */
const TInt KWorldServerBuildVN=105;
//
/**
 * @internal Component
 * @released
 */
const TInt KMaxZoneName=3;

/** Maximum length for TCityName. 
 * @internal Component
 * @released
 */
const TInt KMaxCityName=25;  

/** Maximum length for TCountryName. 
 * @internal Component
 * @released
 */
const TInt KMaxCountryName=25;

/** Maximum length for TAreaCode. 
 * @internal Component
 * @released
 */
const TInt KMaxAreaCode=10;

/** Maximum length for TDialString. 
 * @internal Component
 * @released
 */
const TInt KMaxDialString=50;

/** Maximum length for TNatCode. 
 * @internal Component
 * @released
 */
const TInt KMaxNatCode=10;

/** Maximum length for TNatPrefCode.
 * @internal Component
 * @released
 */
const TInt KMaxNatPrefCode=10;

/** Maximum length for TIntlPrefCode. 
 * @internal Component
 * @released
 */
const TInt KMaxIntlPrefCode=10;

/**
 * @internal Component
 * @released
 */
const TInt KMaxWorldRomTitle=32;

/**
 * @internal Component
 * @released
 */
const TInt KMaxWorldLatitudeMinutes=90*60;

/**
 * @internal Component
 * @released
 */
const TInt KMaxWorldLongitudeMinutes=180*60;

/**
 * @internal Component
 * @released
 */
const TInt KMaxWorldUniversalTimeOffsetMinutes=17*60;

/**
 * @internal Component
 * @released
 */
const TInt KISOCountryCodeLength=2;

/** A buffer for a city name. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxCityName> TCityName;

/** A buffer for a country name. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxCountryName> TCountryName;

/** A buffer to contain a telephone number to dial. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxDialString> TDialString;

/** A buffer for a telephony area code. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxAreaCode> TAreaCode;

/** A buffer for a telephony national code. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxNatCode> TNatCode;

/** A buffer for a telephony national prefix code. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxNatPrefCode> TNatPrefCode;

/** A buffer for a telephony international prefix code. 
 * @publishedAll
 * @released
 */
typedef TBuf<KMaxIntlPrefCode> TIntlPrefCode;

/**
 * @publishedAll
 * @released
 */
typedef TBuf<KISOCountryCodeLength> TISOCountryCode;

/** Defines the distance units which can be used by the world server. 
 * @publishedAll
 * @released
 */
enum TWldDistanceUnits 
    {
    /** miles */
    EWldMiles,
    /** kilometres */
    EWldKilometers,
    /** nautical miles */
    EWldNauticalMiles
    };

/** City search mode flags. These define whether a search for a city involves 
 * the whole of the world database, or just a single country. For example, the 
 * <code>RWorldServer::NextCity()</code> function returns either the next city 
 * in the country, or the next city in the world, depending on which of these 
 * two values is set in the <code>TWorldId</code>. 
 * @publishedAll
 * @released
 */
enum TWldSelect 
    {
    /** the search is within the whole world database */
    EWithinWorld,
    /** the search is within the current country only */
    EWithinCountry
    };

/** Flags which indicate the reasons why the server cannot delete a city or 
 * country. Bitmasks of these flags are returned by the 
 * <code>RWorldServer</code> methods <code>IsCityDeletable()</code> and 
 * <code>IsCountryDeletable()</code>. 
 * @publishedAll
 * @released
 */
enum TWldDeleteDeniedFlags
    {
    /** the specified <code>TWorldId</code> is not found */
    EWldDelNotFound=0x01,
    /** the specified <code>TWorldId</code> is in a read-only file */
    EWldDelDerivedFromRom=0x02,
    /** the specified <code>TWorldId</code> is the home city or country */
    EWldDelHomeCityCountry=0x04,
    /** the specified <code>TWorldId</code> is a capital city */
    EWldDelCapitalCity=0x08,
    /** the specified <code>TWorldId</code> is the default country */
    EWldDelDefaultCountry=0x10,
    /** mask for all of the above reasons */
    EWldDelAll=0xff
    };

/**[what]*/
enum TMonthOccurence
    {
    /**[what]*/
    EMthOccNoOccurenceInMonth = 0,

    EMthOccLastWeekdayInMonth,
    EMthOccNthWeekdayInMonth,
    EMthOccNthWeekdayAfterDate,
    EMthOccFixedOccurence,
    EMthOccTotal
    };

// CLASS DECLARATION
/**
 * This class stores the location coordinates (latitude and longitude) of a 
 * city. 
 *
 * @lib worldclient.lib
 * @since 6.0
 */
class TLatLong
    {
    public:     // Methods

        /**
        * Gets the minutes of the location's latitude.
        * @return the latitude in minutes
        * @remarks A positive return value indicates the Northern hemisphere, 
        * negative Southern
        */
        inline TInt MinutesLat() const;

        /**
        * Gets the minutes of tthe location's latitude.
        * @return the longitude in minutes
        * @remarks A positive return value indicates the Western hemisphere, 
        * negative Eastern
        */
        inline TInt MinutesLong() const;

        /**
        * Sets the latitude and longitude of the location.
        * @param aLat The latitude in minutes - North is 
        *             positive, South is negative
        * @param aLong The longitude in minutes - West is positive, East is 
        *              negative
        */
        IMPORT_C void SetMinutesL(TInt aLat,TInt aLong); // 

        /**
        * Sets the latitude and longitude of the location. If any of the 
        * values are out of range, they are set to the maximum/minimum values.
        * @since Series90 1.0
        * @param aLat The latitude in minutes - North is positive, South is 
        *             negative
        * @param aLong The longitude in minutes - West is positive, East is 
        *              negative
        */
        IMPORT_C void SetMinutesCorrectingErrors(TInt aLat,TInt aLong); // North and West are +ve, South and East are -ve
    private:     // Data
        TInt16 iLat;
        TInt16 iLong;
    };

// CLASS DECLARATION
/**
 * This class stores Daylight Saving Time (DST) information for a city.  
 *
 * @lib worldclient.lib
 * @since Series90 1.0
 */
class TDSTData
    {
    public:  // Methods

        /**
        * Is DST used in this city? 
        * @since Series90 1.0
        * @return <code>ETrue</code> if this daylight saving is used by this 
        *         city, <code>EFalse</code> if it is not
        */
        IMPORT_C TBool HasDSTData() const;

        /**
        * Retrieves the first date in a given year on which daylight saving 
        * changes. Note that in the Northern hemisphere, this is the date 
        * daylight saving starts; in the Southern hemisphere, this will be the 
        * date that daylight saving ends.
        * @since Series90 1.0
        * @param aYear The year for which to get the date
        * @return the first date on which daylight saving changes
        */
        IMPORT_C TTime GetDSTStartDate(TInt aYear) const;

        /**
        * Retrieves the second date in a given year on which daylight 
        * saving changes. Note that in the Northern hemisphere, this will be 
        * the date daylight saving ends; in the Southern hemisphere, this will 
        * be the date that daylight saving starts.
        * @since Series90 1.0
        * @param aYear The year for which to get the date
        * @return the second date on which daylight saving changes
        */
        IMPORT_C TTime GetDSTEndDate(TInt aYear) const;
    
    private:  // Methods
    // private functions used to calculate DST date
        TInt TDayToDOW(TInt aDay) const;
        TInt DayOfWeek(TInt aYear, TMonth aMonth, TInt aDay) const;
        TInt NthDayInMonth(TInt aYear, TMonth aMonth, TInt aNth, TDay aDayOfWeek) const;
        TInt LastDayInMonth(TInt aYear, TMonth aMonth, TDay aDayOfWeek) const;
        TInt DayOnOrAfterInMonth(TInt aYear, TMonth aMonth, TInt aDay, TDay aDayOfWeek) const;

    public:     // Data
        /** [what] */
        TMonthOccurence iStartOccurence;
        /** [what] */
        TDay            iStartDay;
         /** [what] */
		TMonth          iStartMonth;        TInt            iStartNum;
         /** [what] */
		TMonthOccurence iEndOccurence;
         /** [what] */
		TDay            iEndDay;
         /** [what] */
		TMonth          iEndMonth;
         /** [what] */
        TInt            iEndNum;
    };

// CLASS DECLARATION
/**
* This class is required for backward compatibility of the 
* <code>TCityData</code> class.
* <code>TCityDataV1</code> doesn't have a <code>TDSTData</code>.
*
*  @lib worldclient.lib
*  @since Series90 1.0
*/
class TCityDataV1
    {
    public:     // Data
        /** [what] */
		TCityName iCity;
        /** [what] */
        TCountryName iCountry;
        /** [what] */
		TPoint iMapPos;
        /** [what] */
		TLatLong iLatLong;
        /** [what] */
		TAreaCode iAreaCode;
        /** [what] */
		TInt iUniversalTimeOffset; // in minutes
        /** [what] */
		TDaylightSavingZone iDaylightSavingZone;
    };

// CLASS DECLARATION
/**
 * This class stores data about a city, i.e. name, location, 
 * phone code and DST information. 
 * 
 * @lib worldclient.lib
 * @since 6.0
 */
class TCityData : public TCityDataV1
    {
    public:

        /**
        * C++ constructor. This copy constructor is provided for BC purposes.
        * @param aOldCityData city data framed using the deprecated class
        */
        IMPORT_C TCityData(TCityDataV1 aOldCityData);

        /**
        * C++ default constructor.
        */
        IMPORT_C TCityData();
    public:
        TDSTData iDSTData;
    };

// CLASS DECLARATION
/**
* This class is required for backward compatibility of the 
* <code>TCountryData</code> class.
* <code>TCountryDataV1</code> does not have any ISO data.
*
* @lib worldclient.lib
* @since 6.0
*/
class TCountryDataV1  
    {
    public:
        /** [what] */
        TCountryName iCountry;
        /** [what] */
        TNatCode iNatCode;
        /** [what] */
        TCityName iCapital;
        /** [what] */
        TNatPrefCode iNatPref;
        /** [what] */
        TIntlPrefCode iIntlPref;
    };

// CLASS DECLARATION
/**
* This class has no methods. It stores data about a country, i.e. name,
* capital city, phone codes. 
* 
* @lib worldclient.lib
* @since Series90 1.0
*/
class TCountryData : public TCountryDataV1
    {
    public:
        /**
        * C++ constructor. This copy constructor is provided for BC purposes.
        * @param aOldCountryData country data framed using the deprecated class
        */
        IMPORT_C TCountryData(TCountryDataV1 aOldCountryData);

        /**
        * C++ default constructor.
        */
        IMPORT_C TCountryData();

    public:
        /** [what] */
        TISOCountryCode iISOCode;
    };

// CLASS DECLARATION
/**
* This class acts as an index for all the cities in the world database. 
* 
* @lib worldclient.lib
* @since 6.0
*/
class TWorldId
    {
    public:

        /**
        * Constructs a city ID object, and initializes it with the search 
        * locale <code>EWithinWorld</code>. 
        */
        IMPORT_C TWorldId();

        /**
        * Gets the city name in the current <code>TWorldId</code>.
        * @return a reference to the city name
        */
        inline const TCityName& City() const;

        /**
        * Gets the country name in the current <code>TWorldId</code>.
        * @return a reference to the country name
        */
        inline const TCountryName& Country() const;

        /**
        * Gets the current city search mode. Clients can search 
        * for cities by country, or over the whole world database.
        * @return the current city search mode
        */
        inline TWldSelect Select() const;

        /**
        * Sets the city search mode. Clients can search for cities by 
        * country, or over the whole world database.
        * @param aSelector The city search mode
        */
        inline void SetSelect(TWldSelect aSelector);
    private:
        TCityName iCity;
        TWldSelect iSelect;
        TCountryName iCountry;

    friend class RWorldServer;
    };

// CLASS DECLARATION
/**
 * Main class for connecting to world server. This class provides all the main 
 * methods required for accessing the world server database. There are methods 
 * for finding, adding, editing and deleting cities and countries, as well as 
 * some data manipulation functions such as calculating distances and 
 * sunset/sunrise times. 
 *
 * @lib worldclient.lib
 * @since 6.0
 */
class RWorldServer : public RSessionBase
    {
    public:

        /**
        * Connects the client process to the world server.
        *
        * @return <code>KErrNone</code> if successful, otherwise another of 
        *         the system-wide error codes
        * @remarks As with any server, a connection should be closed after use.
        *          <code>RHandleBase</code> provides the necessary 
        *          <code>Close()</code> function, which should be called when 
        *          the server session is no longer required
        */
        IMPORT_C TInt Connect();

        /**
        * Gets the version number of the world server. 
        * @return the version number
        * @see e32std.h
        */
        IMPORT_C TVersion Version() const;

        /**
        * Gets the title of the currently-loaded world database, which is 
        * defined in the read-only file.
        * @param aText On return, contains the title of the world database
        */
        IMPORT_C void RomTitle(TDes& aText) const;

        /**
        * Gets the number of cities in the world database.
        * @return on return, contains the number of cities in the database
        */
        IMPORT_C TInt NumberCities() const;

        /**
        * Gets the number of countries in the world database.
        * @return on return, contains the number of countries in the database
        */
        IMPORT_C TInt NumberCountries() const;
    //

        /**
        * Provides notification of changes to the home city, default country, 
        * system time and database files. The user must add their own active 
        * object using the same <code>TRequestStatus</code> and examine it 
        * when the object's <code>RunL</code> is called.
        *
        * @param aStatus A variable that indicates the completion 
        *                status of the request
        */
        IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);

        /**
        * Cancels an outstanding request for notification of changes to the 
        * home city, default country, system time and database files.
        */
        IMPORT_C void NotifyOnChangeCancel();
    //

        /**
        * Resets the database to the state it had when first opened, and 
        * notifies the clients. Note that when the database is first opened it 
        * contains only the information in the read-only file. This file may 
        * have originated either from ROM or RAM.
        * @return <code>KErrNone</code> if successful, otherwise another of 
        *         the system-wide error codes
        */
        IMPORT_C TInt ResetAllData();

        /**
        * Saves the world database data added by the user to the current data 
        * file.
        * 
        * @return <code>KErrNone</code> if successful, otherwise another of 
        *         the system-wide error codes
        * @remarks This function exports a world server data file. 
        *          To save the file to another location, 
        *          <code>useDataFileSaveAs()</code>. 
        *          <BR><B>Type of return value:</B> <code>TInt</code>
        */
        IMPORT_C TInt DataFileSave();

        /**
        * Resets the world database to its state when the data file was last 
        * saved, discarding unsaved data. 
        * @return <code>KErrNone</code> if successful, otherwise another of 
        *         the system-wide error codes
        */
        IMPORT_C TInt DataFileRevertToSaved();

        /**
        * Allows clients to import a specified world database data file.
        * @param aDataFile The location of the data file to be imported, 
        *                  including drive, path and filename
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt DataFileOpen(const TDesC& aDataFile);

        /**
        * Gets the location of the most recently imported user data file.
        * @param aDataFile On return, contains the name and path of the 
        *                  most recently imported data file 
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt DataFileLocation(TFileName& aDataFile) const;

        /**
        * Saves the world database data added by the user to a specified data 
        * file.
        * @param aDataFile The name, including path, of the data file in which 
        *                  the user added data is to be saved
        * @param aReplace  Specifies whether or not the function will allow 
        *                  an existing data file to be over-written. By 
        *                  default the method does not over-write data files 
        * @return          <code>KErrNone</code> if successful, otherwise one  
        *                  of the system-wide error codes. 
        *                  <code>KErrAlreadyExists</code> is returned if the 
        *                  data file exists and <code>aReplace</code> is set 
        *                  to disallow overwriting
        */
        IMPORT_C TInt DataFileSaveAs(const TDesC& aDataFile,TBool aReplace=EFalse);
    //

        /**
        * Gets the ID of the default country.
        * @param aCountry On return, contains the ID of the default country
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt DefaultCountry(TWorldId& aCountry) const;

        /**
        * Sets the default country.
        * @param aId The ID of the country which is to become the default 
        *            country
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt SetDefaultCountry(const TWorldId& aId);

        /**
        * Gets the ID of the home city.
        * @param aHome On return, contains the ID of the home city
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt Home(TWorldId& aHome) const;

        /**
        * Sets the home city.
        * @param aId The ID of the city which is to become the home city
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt SetHome(const TWorldId& aId);
    //

        /**
        * Retrieves daylight saving dates for the specified city in a given 
        * year. This gets the two dates on which daylight saving changes.
        * @since Series90 1.0
        * @param aId The city to get DST data for
        * @param aYear The year to get dates for
        * @param aDSTStart On return, this contains the first date in the 
        *                  year on which daylight saving changes. Note that 
        *                  for cities in the Northern hemisphere, this is 
        *                  the date on which daylight saving starts. In the 
        *                  Southern hemisphere it is the date on which 
        *                  daylight saving ends
        * @param aDSTEnd On return, this contains the second date in the year 
        *                on which daylight saving changes. Note that for 
        *                cities in the Northern hemisphere, this is the date 
        *                on which daylight saving ends. In the Southern 
        *                hemisphere it is the date on which daylight saving 
        *                starts
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt GetDSTInfo(const TWorldId& aId, const TInt &aYear, TTime& aDSTStart, TTime& aDSTEnd);
    //

        /**
        * Adds a new city to the world database. Cities must be in a valid 
        * country, and have a valid DST zone. Required for backward 
        * compatibility.
        * @param aCity The new city information
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes. <code>KErrArgument</code> is 
        *         returned if the city already exists, or if the city data 
        *         does not specify a city name. It is also returned if the 
        *         named country does not exist, or if the country name is not 
        *         specified
        * @remarks Cities must be in a valid country, and have a valid DST 
        *          zone. City names must be unique within a country though the 
        *          same city name may be used for cities in different 
        *          countries
        */
        IMPORT_C TInt AddCity(const TCityDataV1& aCity);

        /**
        * Adds a new city to the world database.
        * @since Series90 1.0
        * @param aCity The new city information
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes. <code>KErrArgument</code> is 
        *         returned if the city already exists, or if the city data 
        *         does not specify a city name. It is also returned if the 
        *         named country does not exist, or if the country name is not 
        *         specified
        * @remarks Cities must be in a valid country, and have a valid DST 
        *          zone. City names must be unique within a country though the 
        *          same city name may be used for cities in different countries
        */
        IMPORT_C TInt AddCity(const TCityData& aCity);

        /**
        * Adds a new country and its capital city to the world database. 
        * Required for backward compatibility.
        * @param aCountry The country to be added to the database
        * @param aCapital The country's capital
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrArgument</code> if the name of the new country is 
        *         not specified or if the capital city information indicates 
        *         that it is not in the country, otherwise another of the 
        *         system-wide error codes
        * @remarks Country names must be unique
        */
        IMPORT_C TInt AddCountry(const TCountryDataV1& aCountry,const TCityDataV1& aCapital);

        /**
        * Adds a new country, with its capital city, to the world database. 
        * @param aCountry The country to be added to the database
        * @param aCapital The country's capital
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrArgument</code> if the name of the new country is 
        *         not specified or if the capital city information indicates 
        *         that it is not in the country, otherwise another of the 
        *         system-wide error codes
        * @remarks Country names must be unique
        */
        IMPORT_C TInt AddCountry(const TCountryData& aCountry,const TCityData& aCapital);

        /**
        * Gets the city data associated with the specified ID. Required for 
        * backward compatibility.
        * @param aCity On return, contains the city data
        * @param aId The ID of the city
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt CityData(TCityDataV1& aCity,const TWorldId& aId) const;

        /**
        * Gets the city data associated with the specified ID.
        * @since Series90 1.0
        * @param aCity On return, contains the city data
        * @param aId The ID of the city
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt CityData(TCityData& aCity,const TWorldId& aId) const;

        /**
        * Gets the country data associated with the specified ID. Required for 
        * backward compatibility.
        * @param aCountry On return, contains the country data
        * @param aId The ID of the country
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt CountryData(TCountryDataV1& aCountry,const TWorldId& aId) const;

        /**
        * Gets the country data associated with the specified ID.
        * @since Series90 1.0
        * @param aCountry On return, contains the country data
        * @param aId The ID of the country
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt CountryData(TCountryData& aCountry,const TWorldId& aId) const;
        /**
        * Calculates the distance between two cities using the currently 
        * selected distance units.
        * @param aDistance On return, contains the distance between the two 
        *                  cities
        * @param aLeft The ID of the first city
        * @param aRight The ID of the second city
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt CalculateDistance(TInt& aDistance,const TWorldId& aLeft,const TWorldId& aRight) const;

        /**
        * Gets a city’s sunset and sunrise time on a specified date.
        * @param aSunrise On return, contains the sunrise time
        * @param aSunset On return, contains the sunset time
        * @param aId The ID of the city for which the sunset and sunrise times 
        *            are to be calculated
        * @param aDate The date for which the sunrise/sunset times are to be 
        *              calculated
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt CalculateSunlight(TTime& aSunrise,TTime& aSunset,const TWorldId& aId,const TTime& aDate=Time::NullTTime()) const;

        /**
        * Deletes a city from the world database. Capital cities, the home 
        * city, and all cities from the read-only file cannot be deleted.
        * An error will occur if an attempt is made to delete a city which 
        * cannot be, or already has been, deleted
        * @param aId The ID of the city which is to be deleted
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt DeleteCity(TWorldId& aId);

        /**
        * Deletes a country from the world database. The home country, default 
        * country, and all countries from the read-only file cannot be 
        * deleted. An error will occur if an attempt is made to delete a 
        * country which has already been deleted. If a country is deleted, its 
        * cities are added to the null country.
        * @param aId The ID of the country to be deleted
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt DeleteCountry(TWorldId& aId);

        /**
        * Gets the distance units used by the session.
        * @param aDistanceUnit On return, contains the session's distance units
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt DistanceUnits(TWldDistanceUnits& aDistanceUnit) const;

        /**
        * Sets the distance units used by the session.
        * @param aUnit The new distance units
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt SetDistanceUnits(TWldDistanceUnits aUnit);

        /**
        * Finds the ID of the city which precisely matches the specified city 
        * and country names.
        * @param aId On return, contains the ID of the specified city
        * @param aCity The city name
        * @param aCountry The country name
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> if there is no match between the 
        *         city and country names and those of a city in the world 
        *         database, otherwise another of the system-wide error codes
        */
        IMPORT_C TInt Find(TWorldId& aId,const TDesC& aCity,const TDesC& aCountry) const;

        /**
        * Locates the ID of the first city that has a name which starts with 
        * the search string. 
        * @param aCity Specifies the locale within which the city is to be 
        *              found over the whole database, or in the current 
        *              country. On return, contains the ID of the first city 
        *              matching the partial name within the specified locale
        * @param aPartialCity A descriptor containing the search string for 
        *                     the city
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> if no city matches the search 
        *         string, otherwise another of the system-wide error codes
        * @remarks The search string can contain a partial name or the full 
        *          name. The search is not case-sensitive. If several cities 
        *          have names matching the search string, then the city 
        *          first in the alphabetic order is returned. The method 
        *          cannot locate strings in the middle of city names
        */
        IMPORT_C TInt FindCity(TWorldId& aCity,const TDesC& aPartialCity) const;

        /**
        * Locates the ID of the first country which starts with the search 
        * string.
        * @param aCountry On return, contains the ID of the country
        * @param aPartialCountry A descriptor containing the search string,
        *                        or partial country name
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> if no country matches the search 
        *         string, otherwise another of the system-wide error codes
        * @remarks The search string can contain a partial name or the full
        *          name. The string may be capitalised, uncapitalised, or a
        *          combination of the two. If several countries have names 
        *          matching the search string, then the country first 
        *          in alphabetic order is returned. The method cannot locate 
        *          strings in the middle of country names
        */
        IMPORT_C TInt FindCountry(TWorldId& aCountry,const TDesC& aPartialCountry) const;

        /**
        * Locates the ID of the specified country.
        * @param aCountry On return, contains the ID of the country
        * @param aExactCountry A descriptor containing the search string
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> if no country matches the search 
        *         string, otherwise another of the system-wide error codes
        * @remarks The search string must contain the full name. The string 
        *          is not case-sensitive
        */
        IMPORT_C TInt FindExactCountry(TWorldId& aCountry,const TDesC& aExactCountry) const;

        /**
        * Gets the ID of the first city in the selected locale. 
        * @remarks The locale can be either the current country or the 
        *          whole world database, and is defined by the select mode
        *          of the <code>TWorldId</code>. The first city is the one 
        *          earliest in alphabetic order. A search in the country 
        *          locale returns the first city in the country; a search in 
        *          the world locale returns the first city in the whole 
        *          database
        * @param aId Specifies the locale for which the search is to be 
        *            carried out. On return, contains the ID of the first city 
        *            within the specified locale
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt FirstCity(TWorldId& aId) const;

        /**
        * Gets the ID of the first country in the world database.
        * @param aId On return, contains the ID of the first country
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks The first country is the one earliest in alphabetic order. 
        *          Country searches are not locale specific. Searches span 
        *          the whole world database. This method ignores the search 
        *          mode select state defined in the <code>TWorldId</code>
        */
        IMPORT_C TInt FirstCountry(TWorldId& aId) const;

        /**
        * Tests whether a given city can be deleted. 
        * @param aDeleteDeniedFlags Bitmask of the 
        *                           <code>TWldDeleteDeniedFlags</code> flags. 
        *                           Gives the reasons why the specified 
        *                           <code>TWorldID</code> cannot be deleted. 
        *                           The value on return is 0 if the city can 
        *                           be deleted
        * @param aId The ID of the city which is being queried
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks Capital cities, the home city, and cities from the 
        *          read-only file cannot be deleted
        */
        IMPORT_C TInt IsCityDeletable(TInt& aDeleteDeniedFlags,const TWorldId& aId) const;

        /**
        * Determines whether a given country can be deleted. 
        * @param aDeleteDeniedFlags Bitmask of the 
        *                           <code>TWldDeleteDeniedFlags</code> flags. 
        *                           Gives the reasons why the specified 
        *                           <code>TWorldID</code> cannot be deleted. 
        *                           The value on return is 0 if the country 
        *                           can be deleted
        * @param aId The ID of the country which is being queried
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks The home country, default country, and any 
        *          countries from the read-only file cannot be deleted
        */
        IMPORT_C TInt IsCountryDeletable(TInt& aDeleteDeniedFlags,const TWorldId& aId) const;

        /**
        * Gets the ID of the last city in the selected locale.
        * @param aId Specifies the locale within which the last city is to be 
        *            found, over the whole database, or in the current country. 
        *            On return, contains the ID of the last city in the 
        *            specified locale
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks The locale can be either the current country or the whole 
        *          world database, and is defined by the select mode of the 
        *          <code>TWorldId</code>. A search in the country locale will 
        *          display the last city in the country. A search in the world 
        *          locale gets the last city in the whole database. The last 
        *          city is the one last in alphabetic order
        */
        IMPORT_C TInt LastCity(TWorldId& aId) const;

        /**
        * Gets the ID of the last country in the world database. 
        * @param aId On return, contains the ID of the last country
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks The last country in the database is the one last in 
        *          alphabetic order. Country searches are not locale specific 
        *          searches, that is they span the whole world database. This 
        *          method ignores the search mode select state defined in the 
        *          <code>TWorldId</code>
        */
        IMPORT_C TInt LastCountry(TWorldId& aId) const;

        /**
        * Initializes the parameters for a next city search. 
        * @param aMapCoord The map co-ordinate, in pixels, for which the 
        *                  nearest city is to be found
        * @param aCityToBeat The ID of the reference city. The search spans a 
        *                    specified number of cites, starting from this ID
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks To start the search, use the <code>NextNearestCity()</code> 
        *          method
        */
        IMPORT_C TInt NearestCity(const TPoint& aMapCoord,const TWorldId* aCityToBeat=NULL);

        /**
        * Gets the results of a search for the city nearest to a map 
        * co-ordinate.
        * @remarks The co-ordinate is specified using the 
        *          <code>NearestCity()</code> method. The search compares 
        *          the distance between each city and the map co-ordinate. It 
        *          starts at the reference city and continues the comparison 
        *          until it reaches a specified number of cities. By default, 
        *          the search spans <code>KMaxTInt</code> cities, which is 
        *          effectively the entire database
        * @param aId On return, contains the ID of the nearest city
        * @param aMaxNumberToCompare The number of cities to compare
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt NextNearestCity(TWorldId& aId,TInt aMaxNumberToCompare=KMaxTInt);

        /**
        * Gets the ID of the next city in the selected locale. 
        * @param aId Specifies the locale within which the next city is to be 
        *            found, either over the whole database or in the current 
        *            country. On return, contains the ID of the next city in 
        *            the specified locale
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes. <code>KErrNotFound</code> is 
        *         returned if this function is called when the current city is 
        *         the last city
        * @remarks The locale can be either the current country or the whole 
        *          world database, and is defined by the select mode of the 
        *          <code>TWorldId</code> parameter. The next city is the next 
        *          within the selected locale, where the cities are ordered 
        *          alphabetically. A search in the country locale will display 
        *          the next city in the country; a search in the world locale 
        *          gets the next city in the whole database
        */
        IMPORT_C TInt NextCity(TWorldId& aId) const;

        /**
        * Gets the ID of the next country in the world database. 
        * @param aId On return, contains the ID of the next country
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> when the current country is the 
        *         last country, otherwise another of the system-wide error 
        *         codes
        * @remarks The next country is the country after the current country, 
        *          where the database is ordered alphabetically. Country 
        *          searches are not locale specific, and span the whole world 
        *          database. This method ignores the search mode select state 
        *          defined in the <code>TWorldId</code>
        */
        IMPORT_C TInt NextCountry(TWorldId& aId) const;

        /**
        * Gets the ID of the previous city in the selected locale. 
        * @remarks The locale can either be the current country or the whole 
        *          world database, and is defined by the select mode of the 
        *          <code>TWorldId</code>. 
        *          The previous city is the city before the current city 
        *          within the selected locale, where the cities are ordered 
        *          alphabetically. A search in the country locale will display 
        *          the previous city within the country. A search in the world 
        *          locale gets the previous city for the whole database
        * @param aId Specifies the locale within which the previous city is to 
        *            be found; either over the whole database, or in the 
        *            current country. On return, contains the ID of the 
        *            previous city within the specified locale
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> when the current city is the first 
        *         city, otherwise another of the system-wide error codes
        */
        IMPORT_C TInt PrevCity(TWorldId& aId) const;

        /**
        * Gets the ID of the previous country in the world database. 
        * @remarks The previous country is the country preceding the current 
        *          country, where the database is ordered alphabetically. 
        *          Country searches are not locale specific - searches span 
        *          the whole world database. This method ignores the search 
        *          mode select state defined in the <code>TWorldId</code>
        * @param aId On return, contains the ID of the previous country
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrNotFound</code> when the current country is the 
        *         first country, otherwise another of the system-wide error 
        *         codes
        */
        IMPORT_C TInt PrevCountry(TWorldId& aId) const;

        /**
        * Updates the information for a city. This method is required for 
        * backwards compatibility.
        * @since Series90 1.0
        * @param aId The ID of the city to be updated
        * @param aCity The new city information
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrArgument</code> if the updated city name 
        *         overwrites an existing city, or if it is not specified. 
        *         <code>KErrArgument</code> is also returned if the updated 
        *         country name does not exist, or if the country name is not 
        *         specified. Otherwise returns another of the system-wide 
        *         error codes
        * @remarks The new information must be valid. A city must be in a 
        *          valid country, and have a valid DST zone. The city names 
        *          must be unique within a country, though the same city name 
        *          may be used for cities in different countries
        */
        IMPORT_C TInt UpdateCity(TWorldId& aId,const TCityDataV1& aCity);

        /**
        * Updates the information for a city.
        * @since Series90 1.0
        * @param aId The ID of the city to be updated
        * @param aCity The new city information
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrArgument</code> if the updated city name 
        *         overwrites an existing city, or if it isn’t specified. 
        *         <code>KErrArgument</code> is also returned if the updated 
        *         country name does not exist, or if the country name is not 
        *         specified. Otherwise returns another of the system-wide 
        *         error codes
        * @remarks The new information must be valid. A city must be in a 
        *          valid country and have a valid DST zone. The city names 
        *          must be unique within a country though the same city name 
        *          may be used for cities in different countries
        */
        IMPORT_C TInt UpdateCity(TWorldId& aId,const TCityData& aCity);

        /**
        * Updates the data for an existing country. 
        * @param aId The ID of the country to be updated
        * @param aCountry The new country data
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrArgument</code> if the updated country name is not 
        *         specified or if it is not unique, otherwise another of the 
        *         system-wide error codes
        * @remarks The updated country names must be unique. This method is 
        *          required for backward compatibility
        */
        IMPORT_C TInt UpdateCountry(TWorldId& aId,const TCountryDataV1& aCountry);

        /**
        * Updates the data of an existing country. Updated country names must 
        * be unique.
        * @since Series90 1.0
        * @param aId The ID of the country to be updated
        * @param aCountry The new country data
        * @return <code>KErrNone</code> if successful, 
        *         <code>KErrArgument</code> is returned if the updated country 
        *         name is not specified or if it is not unique, otherwise 
        *         another of the system-wide error codes
        */
        IMPORT_C TInt UpdateCountry(TWorldId& aId,const TCountryData& aCountry);

        /**
        * Gets the country name for the given ISO country code.
        * @param aCode The ISO country code
        * @param aCountry On return, contains the name of the country
        * @return <code>KErrNone</code> if successful or 
        *         <code>KErrNotFound</code> if there is an attempt to get a 
        *         country name with an undefined country code. Otherwise 
        *         returns another of the system-wide error codes
        * @remarks Not all country names returned by this method represent 
        *          countries in the world database. ISO country codes are 
        *          defined in ISO3166-1, and are most commonly used as country 
        *          extensions in e-mail addresses, for example uk, au
        */
        IMPORT_C TInt GetCountryNameByISOCode(const TDesC& aCode, TDes& aCountry) const;

        /**
        * Sets the collation level passed into all calls to 
        * <code>TInt CompareC(const TDesC16& aDes, TInt aMaxLevel, 
        * const TCollationMethod* aCollationMethod)</code> when searching for 
        * city and country names.
        * @since Series90 1.0
        * @param aCollationLevel The collation level
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        */
        IMPORT_C TInt SetCollationLevelForFind(TInt aCollationLevel); // this is a per-client setting

        /**
        * Sets the world server to give locale updates or not when the home 
        * city etc. is changed.
        * @since Series90 1.0
        * @param aEnabled <code>ETrue</code> if locale updates are to be 
        *                 enabled, <code>EFalse</code> to disable them
        * @return <code>KErrNone</code> if successful, otherwise one of the 
        *         system-wide error codes
        * @remarks By default, these are always initially enabled 
        */
        IMPORT_C TInt EnableLocaleUpdates(TBool aEnabled); 

    public: // *** Do not use! API liable to change ***//FIX

        /**
        * For test code only.
        */
        IMPORT_C void __DbgFailAlloc(TInt aCount);

        /**
        * For test code only.
        */
        IMPORT_C void __DbgMarkEnd(); 

        /**
        * For test code only.
        */
        IMPORT_C void __DbgMarkHeap();

        /**
        * For test code only.
        */
        IMPORT_C TInt SetRomDatabaseToUse(const TDesC& aRomDatabaseToUse); 

        /**
        * For test code only.
        */
        IMPORT_C TBool ReadOnlyDataIsInRAM() const;
    };

// INLINE FUNCTIONS

inline TWldSelect TWorldId::Select() const
    {
        return(iSelect);
    }

inline const TCityName& TWorldId::City() const
    {
        return(iCity);
    }

inline const TCountryName& TWorldId::Country() const
    {
        return(iCountry);
    }

inline void TWorldId::SetSelect(TWldSelect aSelector)
    {
    iSelect=aSelector;
    }

inline TInt TLatLong::MinutesLat() const
    {
        return(iLat);
    }

inline TInt TLatLong::MinutesLong() const
    {
        return(iLong);
    }


#endif  // T32WLD_H

// End of File
