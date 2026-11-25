//		BtOnOff.h
//
//		Copyright (c) 2000 Symbian Ltd. All rights reserved.


#ifndef BTONOFF_H
#define BTONOFF_H

// This file defines the interface of the Bluetooth Radio ON/OFF interface. Default implementation
// just streams the on/off value to c:\system\data\BluetoothOnOff.ini - while licensees themselves
// have to supply another implementation that actually switches the BT RF interface on and off.

class CBTOnOff : public CBase
	{
public:
	/**
	 * enum containing on and off values
	 */
	enum TBTRadio
		{
		EBTRadioOn,
		EBTRadioOff
		};
	/**
	 * Switch on/off Bluetooth RF
	 *
	 * @param aStatus TBTRadio enum containing on or off value
	 * @returns TInt containing error message
	 */
	IMPORT_C static TInt SetBluetoothRadio(TBTRadio aStatus);
	/**
	 * Returns the current status of BT RF
	 *
	 * @returns TBTRadio enum containing on or off value
	 */
	IMPORT_C static TBTRadio BluetoothRadio();
	};

#endif // BTONOFF_H