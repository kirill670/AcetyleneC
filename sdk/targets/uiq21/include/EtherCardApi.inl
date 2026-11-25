// EtherCardApi.inl
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
// Produced for Symbian by CLF Consulting Ltd.
//
// This provides the inline implementation of the user side interface to Ethernet LDD, 
// which provides a set of interface functions for a PCMCIA Ethernet Card
// via a suitable PDD & EPBUS.DLL
//
//
inline TInt RPcmNetCardIf::Open(const TVersion& aVer, TInt aUnit, const TDesC * aDriver)
// Open a channel
	{
	return(DoCreate(_L("EtherCard"), aVer, NULL, aUnit, aDriver, NULL));
	}

inline TVersion RPcmNetCardIf::VersionRequired() const
// Return version numbering information.
		{return(TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber));}

inline void RPcmNetCardIf::Read(TRequestStatus &aStatus,TDes8 &aDes)
// Request Ethernet frame read, limited in length to the maximum user descriptor size.
		{TInt len=aDes.MaxLength();DoRequest(ERequestRead,aStatus,&aDes,&len);}

inline void RPcmNetCardIf::Read(TRequestStatus &aStatus,TDes8 &aDes,TInt aLength)
// Request Ethernet frame read, limited in length to the specified size.
		{ DoRequest(ERequestRead,aStatus,&aDes,&aLength);}

inline void RPcmNetCardIf::ReadCancel()
// Cancel read request.
		{ DoControl(EControlReadCancel,NULL);}

inline void RPcmNetCardIf::Write(TRequestStatus &aStatus,const TDesC8 &aDes)
// Request Ethernet frame write.
		{TInt len=aDes.Length();DoRequest(ERequestWrite,aStatus,(TAny *)&aDes,&len);}

inline void RPcmNetCardIf::WriteCancel()
// Cancel write request.
		{ DoControl(EControlWriteCancel,NULL);}

inline TInt RPcmNetCardIf::GetConfig(TDes8 &aConfig)
// Retrieve configuration information.
		{return(DoControl(EControlGetConfig,&aConfig));}

inline TInt RPcmNetCardIf::IOControl(TRequestStatus &aStatus, TDes8 &aConfig)
// Request control operation - synchronous or asynchronous
		{
		TInt len=aConfig.Length();
		switch(*((TUint8 *)aConfig.Ptr()))
			{
			case KIoControlPowerUpCard:
				{
				return(DoSvControl(ESvControlPowerUp, (TAny *)&aConfig, (TAny *)&aStatus));
				}
			case KIoControlPowerDownCard:
				{
				return(DoSvControl(ESvControlPowerDown, (TAny *)&aConfig, (TAny *)&aStatus));
				}
			case KIoControlResetCard:
				{
				return(DoSvControl(ESvControlReset, (TAny *)&aConfig, (TAny *)&aStatus));
				}
			case KIoControlSetMACAddress:
				{
				return(DoSvControl(ESvSetMACAddress, (TAny *)&aConfig, (TAny *)&aStatus));
				}
			default:
				{
				DoRequest(ERequestControl, aStatus, (TAny *)&aConfig, &len);
				return(KErrNone);
				}
			}
		}

inline void RPcmNetCardIf::IOControlCancel()
// Cancel control operation request
		{ DoControl(EControlControlCancel,NULL);}

inline void RPcmNetCardIf::GetEvent(TRequestStatus &aStatus, const TDesC8 &aConfig)
// Request event monitor.
		{TInt len=aConfig.Length(); DoRequest(ERequestEvent, aStatus, (TAny *)&aConfig, &len);}

inline void RPcmNetCardIf::GetEventCancel()
// Cancel event monitor.
		{
		DoControl(EControlEventCancel,NULL);
		}

inline TInt RPcmNetCardIf::GetCaps(TDes8 &aCaps)
// Retrieve device capabilities information.
		{return(DoControl(EControlGetCaps,&aCaps));}