
// D32USBC.INL
//
// Copyright (c) 1995-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __D32USBC_INL__
#define __D32USBC_INL__


inline TInt TUsbcEndpointCaps::MaxPacketSize() const
	{
	return (iSizes & KUsbEpSize1023) ? 1023 :
		((iSizes & KUsbEpSize512) ? 512 :
		 ((iSizes & KUsbEpSize256) ? 256 :
		  ((iSizes & KUsbEpSize128) ? 128 :
		   ((iSizes & KUsbEpSize64) ? 64 :
			((iSizes & KUsbEpSize32) ? 32 :
			 ((iSizes & KUsbEpSize16) ? 16 :
			  ((iSizes & KUsbEpSize8) ? 8 : 0)))))));
	}

inline TInt TUsbcEndpointCaps::MinPacketSize() const
	{
	return (iSizes & KUsbEpSize8) ? 8 :
		((iSizes & KUsbEpSize16) ? 16 :
		 ((iSizes & KUsbEpSize32) ? 32 :
		  ((iSizes & KUsbEpSize64) ? 64 :
		   ((iSizes & KUsbEpSize128) ? 128 :
			((iSizes & KUsbEpSize256) ? 256 :
			 ((iSizes & KUsbEpSize512) ? 512 :
			  ((iSizes & KUsbEpSize1023) ? 1023 : 0)))))));
	}

static inline TUint PacketSize2Mask(TInt aSize)
	{
	return (aSize == 8) ? KUsbEpSize8 :
		((aSize == 16) ? KUsbEpSize16 :
		 ((aSize == 32) ? KUsbEpSize32 :
		  ((aSize == 64) ? KUsbEpSize64 :
		   ((aSize == 128) ? KUsbEpSize128 :
			((aSize == 256) ? KUsbEpSize256 :
			 ((aSize == 512) ? KUsbEpSize512 :
			  ((aSize == 1023) ? KUsbEpSize1023 : 0)))))));
	}

static inline TUint EpTypeMask2Value(TInt aType)
	{
	return (aType & KUsbEpTypeControl) ? KUsbEpAttr_Control :
		((aType & KUsbEpTypeIsochronous) ? KUsbEpAttr_Isochronous :
		 ((aType & KUsbEpTypeBulk) ? KUsbEpAttr_Bulk :
		  ((aType & KUsbEpTypeInterrupt) ? KUsbEpAttr_Interrupt : -1)));
	}

inline TUsbcEndpointInfo::TUsbcEndpointInfo(TUint aType, TUint aDir,TInt aSize, TInt aInterval, TInt aExtra)
	: iType(aType), iDir(aDir), iSize(aSize), iInterval(aInterval), iExtra(aExtra)
	{}

inline TUsbcClassInfo::TUsbcClassInfo(TInt aClass,TInt aSubClass,TInt aProtocol)
	: iClassNum(aClass), iSubClassNum(aSubClass), iProtocolNum(aProtocol)
	{}

inline TUsbcInterfaceInfo::TUsbcInterfaceInfo(TInt aClass,TInt aSubClass,TInt aProtocol,
											  TDesC16* aString,TUint aTotalEndpoints)
	: iClass(aClass,aSubClass,aProtocol),iString(aString),iTotalEndpointsUsed(aTotalEndpoints)
	{}

inline TInt RDevUsbcClient::Open(TInt aUnit)
	{
	_LIT(KUsbDevName, "Usbc");
	return (DoCreate(KUsbDevName, VersionRequired(), NULL, aUnit, NULL, NULL, EOwnerThread));
	}

inline TVersion RDevUsbcClient::VersionRequired() const
	{return (TVersion(EMajorVersionNumber, EMinorVersionNumber, EBuildVersionNumber));}

// DoControl

inline TInt RDevUsbcClient::EndpointZeroRequestError()
	{return DoControl(EControlEndpointZeroRequestError);}
inline TInt RDevUsbcClient::EndpointCaps(TDes8& aCapsBuf)
	{return DoControl(EControlEndpointCaps,&aCapsBuf);}
inline TInt RDevUsbcClient::DeviceCaps(TDes8& aCapsBuf)
	{return DoControl(EControlDeviceCaps,&aCapsBuf);}

inline TInt RDevUsbcClient::GetAlternateSetting(TInt &aInterfaceNumber)
	{return DoControl(EControlGetAlternateSetting,&aInterfaceNumber);}
inline TInt RDevUsbcClient::DeviceStatus(TUsbcDeviceState &aDeviceStatus)
	{return DoControl(EControlDeviceStatus, &aDeviceStatus);}
inline TInt RDevUsbcClient::EndpointStatus(TEndpointNumber aEndpoint,TEndpointState &aEndpointStatus)
	{return DoControl(EControlEndpointStatus,(TAny*) aEndpoint,&aEndpointStatus);}
inline TInt RDevUsbcClient::QueryReceiveBuffer(TEndpointNumber aEndpoint,TInt& aNumberOfBytes)
	{return DoControl(EControlQueryReceiveBuffer, (TAny*) aEndpoint, &aNumberOfBytes);}
inline TInt RDevUsbcClient::SendEp0StatusPacket()
	{return DoControl(EControlSendEp0StatusPacket);}
inline TInt RDevUsbcClient::HaltEndpoint(TEndpointNumber aEndpoint)
	{return DoControl(EControlHaltEndpoint, (TAny*) aEndpoint);}
inline TInt RDevUsbcClient::ClearHaltEndpoint(TEndpointNumber aEndpoint)
	{return DoControl(EControlClearHaltEndpoint, (TAny*) aEndpoint);}
//
inline TUint RDevUsbcClient::EndpointZeroMaxPacketSizes()
	{return DoControl(EControlEndpointZeroMaxPacketSizes);}
inline TInt RDevUsbcClient::SetEndpointZeroMaxPacketSize(TInt aMaxPacketSize)
	{return DoControl(EControlSetEndpointZeroMaxPacketSize,(TAny*) aMaxPacketSize);}

inline TInt RDevUsbcClient::GetDeviceDescriptor(TDes8& aDeviceDescriptor)
	{return DoControl(EControlGetDeviceDescriptor, &aDeviceDescriptor);}
inline TInt RDevUsbcClient::SetDeviceDescriptor(const TDesC8& aDeviceDescriptor)
	{return DoControl(EControlSetDeviceDescriptor, const_cast<TDesC8*>(&aDeviceDescriptor));}
inline void RDevUsbcClient::GetDeviceDescriptorSize(TInt& aSize)
	{
	TPckgBuf<TInt> p;
	DoControl(EControlGetDeviceDescriptorSize, &p);
	aSize = p();
	}
inline TInt RDevUsbcClient::GetConfigurationDescriptor(TDes8& aConfigurationDescriptor)
	{return DoControl(EControlGetConfigurationDescriptor, &aConfigurationDescriptor);}
inline TInt RDevUsbcClient::SetConfigurationDescriptor(const TDesC8& aConfigurationDescriptor)
	{return DoControl(EControlSetConfigurationDescriptor, const_cast<TDesC8*>(&aConfigurationDescriptor));}
inline void RDevUsbcClient::GetConfigurationDescriptorSize(TInt& aSize)
	{
	TPckgBuf<TInt> p;
	DoControl(EControlGetConfigurationDescriptorSize, &p);
	aSize = p();
	}
inline TInt RDevUsbcClient::GetInterfaceDescriptor(TInt aSettingNumber, TDes8& aInterfaceDescriptor)
	{return DoControl(EControlGetInterfaceDescriptor,(TAny*) aSettingNumber, &aInterfaceDescriptor);}
inline TInt RDevUsbcClient::SetInterfaceDescriptor(TInt aSettingNumber, const TDesC8& aInterfaceDescriptor)
	{return DoControl(EControlSetInterfaceDescriptor,(TAny*) aSettingNumber,
					  const_cast<TDesC8*>(&aInterfaceDescriptor));}
inline TInt RDevUsbcClient::GetInterfaceDescriptorSize(TInt aSettingNumber, TInt& aSize)
	{
	TPckgBuf<TInt> p;
	TInt r = DoControl(EControlGetInterfaceDescriptorSize,(TAny*) aSettingNumber, &p);
	if (r == KErrNone)
		aSize = p();
	return r;
	}
inline TInt RDevUsbcClient::GetEndpointDescriptor(TInt aSettingNumber, TInt aEndpointNumber,
												  TDes8& aEndpointDescriptor)
	{TEndpointDescriptorInfo info={aSettingNumber, aEndpointNumber, &aEndpointDescriptor};
	return DoControl(EControlGetEndpointDescriptor,&info,NULL);}
inline TInt RDevUsbcClient::SetEndpointDescriptor(TInt aSettingNumber, TInt aEndpointNumber,
												  const TDesC8& aEndpointDescriptor)
	{TEndpointDescriptorInfo info={aSettingNumber, aEndpointNumber, const_cast<TDesC8*>(&aEndpointDescriptor)};
	return DoControl(EControlSetEndpointDescriptor,&info,NULL);}
inline TInt RDevUsbcClient::GetEndpointDescriptorSize(TInt aSettingNumber, TInt aEndpointNumber, TInt& aSize)
	{
	TPckgBuf<TInt> p;
	TEndpointDescriptorInfo info = {aSettingNumber, aEndpointNumber, &p};
	TInt r = DoControl(EControlGetEndpointDescriptorSize, &info, NULL);
	if (r == KErrNone)
		aSize = p();
	return r;
	}
inline TInt RDevUsbcClient::GetCSInterfaceDescriptorBlock(TInt aSettingNumber, TDes8& aInterfaceDescriptor)
	{return DoControl(EControlGetCSInterfaceDescriptor,(TAny*) aSettingNumber, &aInterfaceDescriptor);}
inline TInt RDevUsbcClient::GetCSInterfaceDescriptorBlockSize(TInt aSettingNumber, TInt& aSize)
	{
	TPckgBuf<TInt> p;
	TInt r = DoControl(EControlGetCSInterfaceDescriptorSize,(TAny*) aSettingNumber, &p);
	if (r == KErrNone)
		aSize = p();
	return r;
	}
inline TInt RDevUsbcClient::GetCSEndpointDescriptorBlock(TInt aSettingNumber, TInt aEndpointNumber,
													TDes8& aEndpointDescriptor)
	{TEndpointDescriptorInfo info={aSettingNumber, aEndpointNumber, &aEndpointDescriptor};
	return DoControl(EControlGetCSEndpointDescriptor,&info,NULL);}
inline TInt RDevUsbcClient::GetCSEndpointDescriptorBlockSize(TInt aSettingNumber, TInt aEndpointNumber,
															 TInt& aSize)
	{
	TPckgBuf<TInt> p;
	TEndpointDescriptorInfo info = {aSettingNumber, aEndpointNumber, &p};
	TInt r = DoControl(EControlGetCSEndpointDescriptorSize, &info, NULL);
	if (r == KErrNone)
		aSize = p();
	return r;
	}
inline TInt RDevUsbcClient::SignalRemoteWakeup()
	{return DoControl(EControlSignalRemoteWakeup);}
inline void RDevUsbcClient::DumpRegisters()
	{DoControl(EControlDumpRegisters);}

inline TInt RDevUsbcClient::DeviceDisconnectFromHost()
	{return DoControl(EControlDeviceDisconnectFromHost);}
inline TInt RDevUsbcClient::DeviceConnectToHost()
	{return DoControl(EControlDeviceConnectToHost);}
inline TInt RDevUsbcClient::PowerUpUdc()
	{return DoControl(EControlDevicePowerUpUdc);}


// DoSvControl
inline TInt RDevUsbcClient::SetInterface(TInt aInterfaceNumber,  TUsbcInterfaceInfoBuf& aInterfaceData)
	{return DoSvControl(EControlSetInterface, &aInterfaceNumber, &aInterfaceData);}
inline TInt RDevUsbcClient::ReleaseInterface(TInt aInterfaceNumber)
	{return DoSvControl(EControlReleaseInterface, &aInterfaceNumber);}
inline TInt RDevUsbcClient::SetCSInterfaceDescriptorBlock(TInt aSettingNumber, const TDesC8& aInterfaceDescriptor)
	{
	TCSDescriptorInfo info = {aSettingNumber, 0, const_cast<TDesC8*>(&aInterfaceDescriptor),
							  aInterfaceDescriptor.Size()};
	return DoSvControl(EControlSetCSInterfaceDescriptor, &info, NULL);
	}
inline TInt RDevUsbcClient::SetCSEndpointDescriptorBlock(TInt aSettingNumber, TInt aEndpointNumber,
														 const TDesC8& aEndpointDescriptor)
	{
	TCSDescriptorInfo info = {aSettingNumber, aEndpointNumber, const_cast<TDesC8*>(&aEndpointDescriptor),
							  aEndpointDescriptor.Size()};
	return DoSvControl(EControlSetCSEndpointDescriptor, &info, NULL);
	}

inline TInt RDevUsbcClient::SetDeviceControl()
	{return DoSvControl(EControlSetDeviceControl);}
inline TInt RDevUsbcClient::ReleaseDeviceControl()
	{return DoSvControl(EControlReleaseDeviceControl);}

inline TInt RDevUsbcClient::GetManufacturerStringDescriptor(TDes16& aString)
	{return DoSvControl(EControlGetManufacturerStringDescriptor, &aString);}
inline TInt RDevUsbcClient::SetManufacturerStringDescriptor(const TDesC16& aString)
	{return DoSvControl(EControlSetManufacturerStringDescriptor, const_cast<TDesC16*>(&aString));}

inline TInt RDevUsbcClient::GetProductStringDescriptor(TDes16& aString)
	{return DoSvControl(EControlGetProductStringDescriptor, &aString);}
inline TInt RDevUsbcClient::SetProductStringDescriptor(const TDesC16& aString)
	{return DoSvControl(EControlSetProductStringDescriptor, const_cast<TDesC16*>(&aString));}

inline TInt RDevUsbcClient::GetSerialNumberStringDescriptor(TDes16& aString)
	{return DoSvControl(EControlGetSerialNumberStringDescriptor, &aString);}
inline TInt RDevUsbcClient::SetSerialNumberStringDescriptor(const TDesC16& aString)
	{return DoSvControl(EControlSetSerialNumberStringDescriptor, const_cast<TDesC16*>(&aString));}

inline TInt RDevUsbcClient::GetConfigurationStringDescriptor(TDes16& aString)
	{return DoSvControl(EControlGetConfigurationStringDescriptor, &aString);}
inline TInt RDevUsbcClient::SetConfigurationStringDescriptor(const TDesC16& aString)
	{return DoSvControl(EControlSetConfigurationStringDescriptor, const_cast<TDesC16*>(&aString));}


// DoRequest
inline void RDevUsbcClient::ReadOneOrMore(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadOneOrMore, aDes.MaxLength()};
	 DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::ReadOneOrMore(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes, TInt aLen)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadOneOrMore, aLen};
	DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::ReadUntilShort(TRequestStatus &aStatus, TEndpointNumber aEndpoint, TDes8 &aDes)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadUntilShort, aDes.MaxLength()};
	 DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::ReadUntilShort(TRequestStatus &aStatus, TEndpointNumber aEndpoint, TDes8 &aDes, TInt aLen)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadUntilShort, aLen};
	DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::Read(TRequestStatus &aStatus, TEndpointNumber aEndpoint, TDes8 &aDes)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadData, aDes.MaxLength()};
	 DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::Read(TRequestStatus &aStatus, TEndpointNumber aEndpoint, TDes8 &aDes, TInt aLen)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadData, aLen};
	DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::ReadPacket(TRequestStatus &aStatus, TEndpointNumber aEndpoint, TDes8 &aDes,
									   TInt aMaxLen)
	{TEndpointTransferInfo info = {&aDes, ETransferTypeReadPacket, aMaxLen};
	DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::Write(TRequestStatus &aStatus, TEndpointNumber aEndpoint, const TDesC8& aDes,
								  TInt aLen, TBool aZlpRequired)
	{TEndpointTransferInfo info = {const_cast<TDesC8*>(&aDes), ETransferTypeWrite, aLen, aZlpRequired};
	DoRequest(aEndpoint,aStatus,&info,NULL);}

inline void RDevUsbcClient::AlternateDeviceStatusNotify(TRequestStatus& aStatus, TUint& aValue)
	{DoControl(EControlReqAlternateDeviceStatusNotify,&aStatus,&aValue);}

inline void RDevUsbcClient::ReEnumerate(TRequestStatus& aStatus)
	{DoControl(EControlReqReEnumerate,&aStatus);}

inline void RDevUsbcClient::AlternateDeviceStatusNotifyCancel()
	{DoControl(EControlReqAlternateDeviceStatusNotifyCancel);}

inline void RDevUsbcClient::ReEnumerateCancel()
	{DoControl(EControlReqReEnumerateCancel);}

inline void RDevUsbcClient::EndpointStatusNotify(TRequestStatus& aStatus, TUint& aEndpointMask)
	{DoControl(EControlNotifyEndpointStatus,&aStatus, &aEndpointMask);}

inline void RDevUsbcClient::EndpointStatusNotifyCancel()
	{DoControl(EControlCancelNotifyEndpointStatus);}


// DoCancel
inline void RDevUsbcClient::ReadCancel(TEndpointNumber aEndpoint)
	{DoCancel(1<<aEndpoint);}
inline void RDevUsbcClient::WriteCancel(TEndpointNumber aEndpoint)
	{DoCancel(1<<aEndpoint);}
inline void RDevUsbcClient::EndpointTransferCancel(TUint aTransferMask)
	{DoCancel(aTransferMask);}


#endif // __D32Usbc_INL__
