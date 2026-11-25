// T_CREATEINI.H
//
// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __T_CREATEDBINI_H__
#define __T_CREATEDBINI_H__


/** The name of the ini file:  C:\System\Data\t_createdb.ini */
_LIT(KIniFileName,"C:\\System\\Data\\t_createdb.ini");

/** The ini file uses the following layout: 
[section]
variable= value

The spacing between the equals sign and the value are important.
If the space is missed the ini file will not be parsed correctly.
Also, any value containing spaces will be truncated.
@internal "This is due to defects in CESockIniData"

Furthermore, the parser is case-sensitive. This means that the
variables and their values must be used with exactly the same
case as they appear here.
*/

/** The first entry in the ini-file is config= <database config> */
_LIT(KConfigField, "config");

/** Where <database config> is one of the following three:
	NTRAS - database configured for NTRAS
	ISP - database configured for a number of ISPs
	DEFAULT - default or "empty" database which contains no ISPs, but all
		protocol bindings and tcpip / ppp settings. */
_LIT(KConfigNtRas, "NTRAS");
_LIT(KConfigIsp, "ISP");
_LIT(KConfigDefault, "DEFAULT");

/** ISP Variables - stored in the `[ISP]` section
	`Modem`, `CommPort` and `Location` are the default settings for data
	connections.
	`ModemSMS`, `CommPortSMS` and `LocationSMS` are for the telephony modem
	(SMS). For example:
[ISP]
Modem= USR
Location= Office
CommPort= 0
ModemSMS= GsmSerial
LocationSMS= Mobile
CommPortSMS= 1
*/
_LIT(KDataModem, "Modem");
_LIT(KDataCommPort, "CommPort");
_LIT(KDataLocation, "Location");
_LIT(KSmsModem, "ModemSMS");
_LIT(KSmsCommPort, "CommPortSMS");
_LIT(KSmsLocation, "LocationSMS");
/** Values for the `Modem` and `ModemSMS` variables */
_LIT(KModemNull, "NullModem");
_LIT(KModemUSR, "USR");
_LIT(KModemDacom, "Dacom");
_LIT(KModemGsmIr, "GsmIr");
_LIT(KModemGsmSerial, "GsmSerial");
_LIT(KModem520Ir, "520Ir");
_LIT(KModem520Serial, "520Serial");
_LIT(KModemMotorolaSerial, "MotorolaSerial");
/** Values for the `Location` and `LocationSMS` variables */
_LIT(KLocationOffice, "Office");
_LIT(KLocationOfficeDirect, "OfficeDirect");
_LIT(KLocationMobile, "Mobile");
_LIT(KLocationHome, "Home");

/** Dial out service variables - stored in section `[ISP`n`]`
	Where n is a squential number from 1. For example:
[ISP1]
name= NameOfIspWithNoSpaces
number= +4408451234567
username= UsernameCaseSensitive
password= PasswordCaseSensitive

[ISP2]
name= NameOfSecondIspWithNoSpaces
number= +4408457654321
username= UsernameForSecondISP
password= PasswordForSecondISP
*/
_LIT(KIspName, "name");
_LIT(KIspNumber, "number");
_LIT(KIspUsername, "username");
_LIT(KIspPassword, "password");

/** NTRAS variables - stored in section `[NTRAS]`
`_LIT(KSmsCommPort, "CommPort");` */

#endif
