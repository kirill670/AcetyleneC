// T_CREATEDBDLL.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

/**	Create a CommDb from other units test code. The contents of the database is
	specified in an `*.ini` file. The format of which is described in
	`t_createini.h`
*/

/** Bitmask for return error codes from `SetUserSettingsL()` */
enum TUserSettings
	{
	ECmdLnNoArgs	=	0x01,
	ECmdLnNtras		=	0x02,
	ECmdLnDefault	=	0x04,
	ECmdLnAutoDial	=	0x08,
	ECmdLnPortNum0	=	0x10,
	ECmdLnPortNum1	=	ECmdLnPortNum0 << 1,	// 0x0020
	ECmdLnPortNum2	=	ECmdLnPortNum0 << 2,	// 0x0040
	ECmdLnPortNum3	=	ECmdLnPortNum0 << 3,	// 0x0080
	ECmdLnPortNum4	=	ECmdLnPortNum0 << 4,	// 0x0100
	ECmdLnPortNum5	=	ECmdLnPortNum0 << 5,	// 0x0200
	ECmdLnPortNum6	=	ECmdLnPortNum0 << 6,	// 0x0400
	ECmdLnPortNum7	=	ECmdLnPortNum0 << 7,	// 0x0800
	ECmdLnPortNum8	=	ECmdLnPortNum0 << 8,	// 0x1000
	ECmdLnPortNum9	=	ECmdLnPortNum0 << 9		// 0x2000
	};

/** return codes for `UseIniSettings()` */
enum TIniSettings
	{
	EIniFileNoErr		=	KErrNone,
	EIniFileParseErr	=	0x01,
	EIniFileFileOpenErr	=	0x02
	};

/** See `t_createdb.h` */
class CUserSettings;

/**	Stores creation settings entered from `*.ini` files. Creates a comms
	database.
*/
class CCreateDB : public CBase
	{
	public:
		IMPORT_C static CCreateDB* NewLC();
		IMPORT_C ~CCreateDB();

		/** Remove the current database file */
		IMPORT_C TInt DeleteExistingCommDB();

		/** Initialise settings depending on the following arguments:
			`aArg1` contains "-ntras" :- connection via NT RAS,
			`aArg1` contains "-default" :- do not create the following tables:
				DIAL_OUT_ISP, DIAL_IN_ISP, GPRS_SERVICE, CDMA2000_SERVICE,
				PROXYS, CHARGECARD, LOCATION, MODEM, IAP, WAP, SECURE_SOCKETS,
				DEFAULT_GPRS
			`aArg1` contains "-autodial" :- set the connection preference to
											not prompt
			`aArg2` specifies port for NT RAS e.g. "0" */
		IMPORT_C TUserSettings SetUserSettingsL(TDesC& aArg1,TDesC& aArg2);

		/** Configure from default ini file. See KIniFileName in
			`t_createini.h`. */
		IMPORT_C TInt UseIniSettings();
		/** Configure from ini file specified. */
		IMPORT_C TInt UseIniSettings(TDesC& aIniFile);

		/** Make the new empty database file. */
		IMPORT_C TInt CreateCommDBL();

		/** Pass the UserSettings */
		//IMPORT_C TInt CreateCommDBL(CUserSettings* aUserSettings);

		

	private:
		/** @private */
		void ConstructL();
		//dummy function to wrap CCreateDB::NewLC();
		CCreateDB* doLCUseIniSettingsL();
	private:
		CUserSettings* iUserSettings;
	};
