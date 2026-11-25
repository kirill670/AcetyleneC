// QBTselectdlg.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef BTUISELECTDLG_H
#define BTUISELECTDLG_H

#include <e32uid.h>
#include <eikenv.h>

#include <eikappui.h>
#include <eikon.rsg>
#include <eikon.hrh>
#include <eikcfdlg.h>

#include <coeutils.h>

#include <e32base.h>

#include <Btdevice.h>
#include <btmanclient.h>
#include <BTRegistry.h>
#include <eikclb.h>
// from our utility class
#include <BTUiUtilObserver.h>

/**
* Max length of device name
*/
const TInt KMaxDeviceName = 40;

class CBtActiveNameLookup;
class CBtActiveScan;
class CEikColumnListBox;

	/**
	* This is a shared ui class. It show's a list with bluetooth devices that are found by a search.
	* There is a single and a multiple select choice.
	*/
class CQBTUISelectDialog : public CEikDialog, public MBTUiUtilObserver, public MEikListBoxObserver
	{
public:
	enum EQBTDeviceFilter
	{
	EQBTDeviceFilterAll = -1,
	EQBTDeviceFilterPC = 0x1, // EMajorDeviceComputer
	EQBTDeviceFilterHeadSet = 0x4, //EMajorDeviceAudioDevice
	EQBTDeviceFilterPhone = 0x2, //EMajorDevicePhone
	EQBTDeviceFilterPDA = 6 // EMajorDeviceComputer & EMinorDeviceComputerPalmSize
	};
	/**
	 * Constructor
	 */
	IMPORT_C CQBTUISelectDialog(TBTDevAddr& aAddress, TBTDeviceName& aName, TBTDeviceClass& aClass, EQBTDeviceFilter aFilter,TInt aServiceFilter=-1,TBool aBondedDevices = EFalse);


	/**
	*Constructor
	*/
	IMPORT_C CQBTUISelectDialog(CBTDeviceArray* aSelectedDeviceArray,EQBTDeviceFilter aFilter,TInt aServiceFilter);

	/**
	 * Destructor
	 */
	IMPORT_C ~CQBTUISelectDialog();
	/**
	 * Callback method from our utility DLL
	 *
	 * @param aCommand What type of callback we got
	 * @param aState What state we're in (found device, finished etc)
	 * @param aParam1 different type of objects depending on aCommand
	 * @param aParam2 different type of objects depending on aCommand
	 */
	IMPORT_C void HandleBTUiEventL(TBTUiUtilCommand aCommand,TBTUiUtilState aState,TAny* aParam1, TAny* aParam2);
	/**
	 * This is called when the listbox is clicked
	 *
	 * @param aListBox which listbox caused the event
	 * @param aEventType what type of even occured
	 */
	void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);

	/**
	* Launches the single select dialog choice.
	*/
	IMPORT_C TInt LaunchSingleSelectDialogLD();
	
	/**
	* Launches the multiple select dialog choice.
	*/
	IMPORT_C TInt LaunchMultipleSelectDialogLD();

	/**
	 * Used by the Help system
	 *
	 * @param aContext which area to get help on
	 */
	void GetHelpContext (TCoeHelpContext& aContext) const;

private:
	/**
	 * CEikDialog method that is called when the user press cancel or selects a device
	 *
	 * @see CEikDialog::OkToExitL(TINt aButtonId)
	 */
	TBool OkToExitL(TInt aButtonId);
	/**
	 * CEikDialog method that is called when the dialog is started
	 *
	 * @see CEikDialog::PreLayoutDynInitL()
	 */
	void PreLayoutDynInitL();
	/**
	 * CEikDialog method that is called when the dialog is started
	 *
	 * @see CEikDialog::PostLayoutDynInitL()
	 */
	void PostLayoutDynInitL();

	/**
	 * Called from higher levels (virtual) when a custom control should be created
	 *
	 * @see CEikDialog::CreateCustomControlL(TInt aControlType)
	 */
	SEikControlInfo		CreateCustomControlL(TInt aControlType);

	/**
	 * @see CEikDialog::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
	 */
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	/**
	 * Refreshes the listbox
	 */
	void RefreshDeviceListboxL();
	/**
	 * Starts an active name lookup with a device containing the TBTAddr to search for
	 *
	 * @param aDevice CBTDevice object containing the address of the object we want the name for
	 */
	void StartActiveLookupL(CBTDevice& aDevice);
	/*
	 * Returns right icon for the device sent in.
	 * @params aDevice The device to find the right icon for.
	 */
	TInt FindRightIcon( CBTDevice& aDevice );

	/*
	 * Insert aDevice on correct place in iDeviceArray, sorted on DeviceClass
	 * @params aDevice The device to insert.
	 */
	void InsertDeviceInListL( CBTDevice& aDevice );

	/**
	* Returns the Default name for a device.
	* @paramas aDevice The device to find the name on
	*/
	TBuf<KMaxDeviceName> GetDefaultDeviceName(CBTDevice& aDevice);
	
	/**
	* Returns the name for a device.
	* @paramas aDevice The device to find the name on
	*/
	TBuf<KMaxDeviceName> GetDeviceName(CBTDevice& aDevice);

	/**
	* Overrided method from CEikDialog. 
	* Fix's so no item is preselected.
	*/
	void SetInitialCurrentLine();

	/**
	* Filter the devices useing iFilter as base
	* @retrun Will retrun ETrue if the device should be listed.
	* @paramas aDevice The device
	*/
	TBool FilterDevice(CBTDevice& aDevice);

	/**
	*Callback used to call TryToExit, after HandleListBoxEvent has finished.
    */
	static TInt CallbackTryExitL(TAny* aBtSelectDialog);

private:
	enum TFilterSelection
		{
		EAll = 0,
		EPC,
		EHeadset,
		EPhone,
		EPDA
		};
	
	CBtActiveScan*	iActiveScan;
	CBtActiveNameLookup* iActiveLookup;
	/**
	 * This is the array that holds the context of the listbox
	 */
	CDesCArrayFlat* iTextArray;
	/**
	 * A array for holding complete device objects
	 */
	CBTDeviceArray* iDeviceArray;
	/*
	 * A list of found devices
	 */
	CBTDeviceArray*	iFoundDevices;
	/**
	* A list of selected devices
	*/
	CBTDeviceArray* iSelectedDeviceArray;

	/**
	* A list of Bonded devices
	*/
	CBTDeviceArray* iBondedDeviceArray;

	/**
	* 
	*/
	CBTDeviceArray* iTemporaryDeviceArray;
	/**
	 * Holds the resource file id after the resources has been added to the dialog - used by delete at exit
	 */
	TInt iResourceFileId;
	/**
	 * Array index when updating names of devices returned by inquiry
	 */
	TInt iIndex;

	/** Registry functions to get data from COMMDB */
	CBTRegistry* iBTReg;
	
	/**
	* The choosen device address
	*/
	TBTDevAddr*	iAddress;

	/**
	* The choosen device name
	*/
	TBTDeviceName* iName;

	/**
	* The choosen device class
	*/
	TBTDeviceClass* iClass;

	/**
	 * Keeps track of what filter to use for presenting found devices
	 */
	TInt iFilter;

	/**
	 * Index list to map the index the user select in the list to the correct device
	 */
	CArrayFixFlat<TInt>* iIndexList;

	/**
	*Keeps track of what filter to use for presenting found devices
	*/
	TInt iServiceFilter;

	/*
	*Flag for multipleselection
	*/
	TBool iMultipleSelection;

	/* 
	* Flag for showing boned devices in the select dialog
	*/
	TBool iBondedDevices;

	/**
	* The number of listed bonded devices
	*/
	TInt iNumberOfListedBondedDevices;

	/**
	* Asyc callback so TryToExit isn't called before HandleListBoxEventL is done.
	*/
	CAsyncCallBack* iTryExitCallback;

	/**
	* Array of device that are listed in the listbox
	*/
	CBTDeviceArray* iVisibleDevices;

	/**
	* Reserved variable for future use
	*/
	TAny* iReserved3;

	/**
	* Reserved variable for future use
	*/
	TAny* iReserved4;
	};

#endif //BTUISELECTDLG_H
