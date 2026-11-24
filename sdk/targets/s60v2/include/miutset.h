// MIUTSET.H
//
// Copyright (c) 1998-2004 Symbian Software Ltd.  All rights reserved. 
//

#if !defined (__MIUTSET_H__)
#define __MIUTSET_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__

#include <MSVUIDS.H>
#include "miuthdr.h"
#ifndef __HIDE_MESSAGING_API_V1__	
#include <msvstore.h>

class CMsvStore;
class RMsvWriteStream;
class RMsvReadStream;
#endif

const TInt KMaxSettingStringLength = 1024;

/** UID of an SMTP message type. */
const TUid KUidMsgTypeSMTP			= {0x10001028};	// 268439592
/** UID of a POP3 message type. */
const TUid KUidMsgTypePOP3			= {0x10001029};	// 268439593
/** UID of an IMAP4 message type. */
const TUid KUidMsgTypeIMAP4			= {0x1000102A};	// 268439594

/**
@deprecated
*/
const TUid KUidMsgTypeSMTPServer	= {0x10003923};	// 268450083


class CImBaseEmailSettings : public CBase
/**
Parent class for CImPop3Settings, CImImap4Settings, CImSmtpSettings.

This class should not be instantiated directly. It implements common email
settings such as the hostname or IP address of the server, port number,
and whether or not to use SSL.

@see CImPop3Settings
@see CImImap4Settings
@see CImSmtpSettings

@publishedAll
@released
*/
	{
public:
	IMPORT_C CImBaseEmailSettings();
	IMPORT_C virtual ~CImBaseEmailSettings();
	IMPORT_C void Reset();
#ifndef __HIDE_MESSAGING_API_V1__	
	IMPORT_C void InternalizeL(RMsvReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aWriteStream) const;
	IMPORT_C virtual void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C virtual void StoreL(CMsvStore& aMsvStore) const;
#endif	
	IMPORT_C const TPtrC ServerAddress() const;
	IMPORT_C void SetServerAddressL(const TDesC& aServerAddress);
#ifndef __HIDE_MESSAGING_API_V1__		
	IMPORT_C const TPtrC UserAddress() const;
	IMPORT_C void SetUserAddressL(const TDesC& aUserAddress);
#endif	
	IMPORT_C TUint Port() const;
	IMPORT_C void SetPort(const TUint aPortNumber);
#ifndef __HIDE_MESSAGING_API_V1__			
	IMPORT_C TUint16 Version() const;
#endif	
	IMPORT_C TBool SecureSockets() const;
	IMPORT_C void SetSecureSockets(TBool aFlag);
	IMPORT_C TBool SSLWrapper() const;
	IMPORT_C void SetSSLWrapper(TBool aFlag);
	IMPORT_C CImBaseEmailSettings& CopyL(const CImBaseEmailSettings& aCImBaseEmailSettings);
	IMPORT_C TBool operator==(const CImBaseEmailSettings& aCImBaseEmailSettings) const;

#ifdef __MESSAGING_API_V2__
	TUint32 SettingsFlags() const;
	void SetSettingsFlags(TUint32 aSetFlags);
#endif	

protected:
	enum TImBaseEmailSettings
		{
		EBaseEmailSettingsClearFlag			= 0x00000000,
		EBaseEmailSettingsSecureSockets		= 0x00000001,
		EBaseEmailSettingsSSLWrappedSockets	= EBaseEmailSettingsSecureSockets << 1,  //0x00000002,
		EBaseEmailSettingsLastUsedFlag		= EBaseEmailSettingsSSLWrappedSockets  //0x00000002
		};
#ifndef __REMOVE_MESSAGING_API_V1__		
	TUint16 iVersion;		// Version number for stream persisted in store
#endif	// __REMOVE_MESSAGING_API_V1__
	TUint32 iPortNumber;	// the port the TCP/IP connection be made on

	TUint32 iFlags;			// space for flags info (now and for future)

#ifndef __REMOVE_MESSAGING_API_V1__		
	TUint32 iData;			// space for flags info (for future)
#endif	// __REMOVE_MESSAGING_API_V1__
private:
	HBufC* iServerAddress;	// remote server's IP address
#ifndef __REMOVE_MESSAGING_API_V1__		
	HBufC* iUserAddress;	// my IP address
#endif	// __REMOVE_MESSAGING_API_V1__
	};

#endif