//		BTUIUTILOBSERVER.H
//
//		Copyright (c) 2000 Symbian Ltd. All rights reserved.

#ifndef __BTUIUTILOBSERVER_H__
#define __BTUIUTILOBSERVER_H__

enum TBTUiUtilCommand
	{
	EBTUiUtilNameLookup,
	EBTUiUtilDeviceLookup,
	EBTUiUtilScan,
	EBTUiUtilConnect,
	EBTUiUtilIOCTL
	};

enum TBTUiUtilState
	{
	EBTUiUtilStateFoundDevice,
	EBTUiUtilStateFinishedScan,
	EBTUiUtilStateNameLookupDone,
	EBTUiUtilStateNameLookupFailed,
	EBTUiUtilStateDeviceLookupDone,
	EBTUiUtilStateDeviceLookupFailed,
	EBTUiUtilStateConnectDone,
	EBTUiUtilStateConnectFailed,
	EBTUiUtilStateIOCTLReadComplete,
	EBTUiUtilStateIOCTLWriteComplete,
	EBTUiUtilStateIOCTLReadFailed,
	EBTUiUtilStateIOCTLWriteFailed,
	};

class MBTUiUtilObserver
	{
public:
	/**
	 * Callback method our observers must implement
	 *
	 * @param aCommand What type of callback we send
	 * @param aState What state we're in (found device, finished etc)
	 * @param aParam1 different type of objects depending on aCommand
	 * @param aParam2 different type of objects depending on aCommand
	 */
	virtual void HandleBTUiEventL(TBTUiUtilCommand aCommand,TBTUiUtilState aState,TAny* aParam1, TAny* aParam2) = 0;
	};

#endif // __BTUIUTILOBSERVER_H__