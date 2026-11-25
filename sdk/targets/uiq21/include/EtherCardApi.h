// EtherCardApi.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
// Produced for Symbian by CLF Consulting Ltd.
//
// This header defines the user side interface to EtherCard.LDD, 
//

#if !defined(__ETHERAPI_H__)
#define __ETHERAPI_H__

#include <c32comm.h>
#include "EtherCardIoc.h"

class TCapsPcmNetCd
	{
public:
	TVersion	version ;
	};

class RPcmNetCardIf : public RBusLogicalChannel
//
// User side Ethernet adapter API class
	{
public:
	enum TVer {EMajorVersionNumber=1, EMinorVersionNumber=0,
			   EBuildVersionNumber=KE32BuildVersionNumber};
	enum TRequest
		{
		ERequestRead = 0,
		ERequestControl = 1,
		ERequestWrite = 2,
		ERequestEvent = 3,
		}; // The aysnchronous call types
	enum TControl
		{
		EControlGetConfig,
		EControlGetCaps,
		ESvControlPowerUp,
		EControlReadCancel,
		EControlWriteCancel,
		EControlControlCancel,
		EControlEventCancel,
		ESvControlReset,
		ESvControlPowerDown,
		ESvSetMACAddress,
		}; // The synchronous call types
public:
	inline TInt Open(const TVersion& aVer, TInt aUnit, const TDesC * aDriver) ;
	inline TVersion	VersionRequired() const  ;
	inline void Read(TRequestStatus &aStatus,TDes8 &aDes) ;
	inline void Read(TRequestStatus &aStatus,TDes8 &aDes,TInt aLength) ;
	inline void ReadCancel() ;
	inline void Write(TRequestStatus &aStatus,const TDesC8 &aDes) ;
	inline void WriteCancel() ;
	inline TInt GetConfig(TDes8 &aConfig) ;
	inline TInt IOControl(TRequestStatus &aStatus, TDes8 &aConfig);
	inline void IOControlCancel() ;
	inline void GetEvent(TRequestStatus &aStatus, const TDesC8 &aConfig);
	inline void GetEventCancel();
	inline TInt GetCaps(TDes8 &aCaps) ;
	};

#include "EtherCardApi.inl"

#endif
