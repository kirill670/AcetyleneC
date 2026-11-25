// CONTACUILISTDIALOG.H
//
// Copyright (c) 1997-2001 Symbian AB.  All rights reserved.
//

#ifndef __CONTACUILISTDIALOG__
#define __CONTACUILISTDIALOG__

#include <eikdialg.h>					// CEikDialog
#include <ContactsAppModel.h>			// CContactsAppModel
#include <eiklbo.h>						// MEikListBoxObserver
#include <cmcobs.h>						// MContactsControlObserver
#include <cmmobs.h>						// MContactsAppModelObserver
#include <cntview.h>					// MContactViewObserver
#include <eikchlst.h>					// CEikChoiceList


class CContactsAppListWin;
class CContactsSelector;
class CContacuiListTabGroup;
class CContacuiReturnData;
class CContactLocalView;


const TInt KContactUiCategoryAreaSize = 1000;		// The size of the category event mapping, i.e how many categories do we allow
/**The category types*/
enum TCategoryType 
		{
		EContactUiDefaultCategory = KContactUiCategoryAreaSize,
		EContactUiEngineCategory = EContactUiDefaultCategory+KContactUiCategoryAreaSize
		};

/**
* CContactUiListDialog class. This dialog is used to display all contactitems. 
* When the user taps a contact in the list, the data defined in the method 
* SetReturnType(TUid) is stored in a ContacUiReturndata object which the array 
* that is passed on to this dialog in the constructor holds pointers to.
*
* The creator of the dialog defines the type of data that should be sent back. 
* The sortorder and columnstate could also be changed but they also have a 
* default state.
*
* The listbox in  this dialog is the same listbox that is used in the listview
* in Contacts application (ContactsAppListWin in Cmlstbx.h). But here it is a 
* multiple select list.
*
* @see ContacUiReturnData, ContacUiListAltDialog, Cmlstbx
*/
class CContactUiListDialog : public CEikDialog,
							 public MContactsControlObserver,
							 public MEikListBoxObserver,
							 public MContactsAppModelObserver
	{
public:
	IMPORT_C static TBool RunDlgLD(CArrayPtr<CContacuiReturnData>& aResultArray, 
		TBool aShowPhoneNumber = EFalse, 
		CContactDatabase::TContactViewFilter aFilter = CContactDatabase::EUnfiltered);

	/**
	* Sets the vCardMappings if narrower search should be done. This is optional and is used 
	* only to get for example only _home_ phone numbers instead of _all_ phone numbers.
	* @param CArrayFixFlat<TUid>* aMapArray : Array of vCard mapping items.
	*/
	IMPORT_C static TBool RunDlgLD(CArrayPtr<CContacuiReturnData>& aResultArray, CArrayFix<TUid>* aMapArray,
		TBool aShowPhoneNumber = EFalse, 
		CContactDatabase::TContactViewFilter aFilter = CContactDatabase::EUnfiltered);

private:
	/**
	* Constructor. 
	* @param aResultArray
	* @param aFilter
	*/
	CContactUiListDialog(CArrayPtr<CContacuiReturnData>& aResultArray, CArrayFix<TUid>* aMapArray,
		TBool aShowPhoneNumber, CContactDatabase::TContactViewFilter aFilter);


private:
	

private:
	~CContactUiListDialog();
	
	
	/**
	* From CEikForm
	* @param TInt aControlType.
	* @return A SEikControlInfo.
	*/
	SEikControlInfo CreateCustomControlL(TInt aControlType); 
	
	/**
	* From CEikDialog
	*/
	void PreLayoutDynInitL();

	/**
	* From CEikDialog
	*/
	void PostLayoutDynInitL();

	/**
	* From CEikDialog
	* @param TInt aButtonId:
	* @return A TBool that always returns ETrue.
	*/
	TBool OkToExitL(TInt aButtonId);
	
	/**
	* Method that delete object with contactitemID aItem Id from the returnarray
	* @param The contact ID that should be deleted.
	*/
	void DeleteFromReturnArray(TContactItemId aItemId);

	/**
	* Method that searches for an item with contactitemID aItem Id from the returnarray
	* @param The contact ID that should be searched for.
	* @return The pos where the item was found (KErrNotFound if not found)
	*/
	TInt FindInReturnArray(TContactItemId aItemId);
	
	/**
	* Retrive the Default categories
	*/
	CDesCArrayFlat* RetrieveDefaultCategoriesL();
	
	/**
	* Retrive the engine categories 
	*/
	CDesCArrayFlat* RetrieveEngineCategoriesL();
	
	/**
	* Map the choice list content to the corresponding group
	*/
	void MapArraysL(const CDesCArrayFlat* aEngineCategories, CDesCArrayFlat* aChoiceListContent);
	
	
	/**
	* Gets a category type from a choosen index
	*/
	TCategoryType CategoryType(  TInt aChoosenItem );
	
	/**
	* Start filtering synchronized, in order to finish correctly
	*/
	static TInt StaticStartFilterL(TAny* aContactListDialog);
	void StartFilterL();

	
	



private: // from MContactsControlObserver
	/**
	* Deal with Contacts specific events.
	* @param CCoeControl* aControl: The control that triggered the event.
	* @param TContactsEvent aEventType: The type of event that was triggered.
	*/
	void HandleContactsEventL( CCoeControl* aControl, TContactsEvent aEventType ); 

	/**	
	* A method for setting the fieldtype and mapping corresponding to the filter. 
	* @see ContactsAppModel
	*/
	void SetFieldTypeL();

private: // from MContactsAppModelObserver & CContactManViewBase 
	/**
	* Reacts to a change in the model. Currently in this version no updates in list dialog if model is updated.
	* Empty implementation.
	*/
	void HandleContactsAppModelChangeL(TInt aFlags, TInt aItemHighlightIndex);

	/**
	* From MEikListBoxObserver 
	*/
	void HandleListBoxEventL(CEikListBox* aListBox, MEikListBoxObserver::TListBoxEvent aEventType);
		
	/**
	* Checks the number of possible alternatives of fielddata according to chosen TUid. 
	* If there are more than one alternative, a new dialog is opened (ContacuiListAltDialog).
	* If there are exactly one alternative, that one is stored. If there are no data of that kind
	* a infomessage is displayed.
	* @param TContactItemId* aItemID: The ID of the item that was tapped in the list.
	*/
	TBool LaunchDialogL(TContactItemId aItemID);

	/**
	* Method that checks how many alternatives there are for the specified TUid for the chosen contact.
	* Returns an array of pointers to the found fields.
	* @param TContactItemId* aItemID: The ID from which field data is taken.
	* @param CDesCArray& aExtraArray: An array to catch the suffix (w) and (h)
	* @return CDesCArray*: An array of pointer to the extracted data.
	*/
	CDesCArray* ArrayOfAlternativesLC(CContactItemFieldSet& aFieldSet, CDesCArray& aExtraArray);
	
	/**
	* From MContactsAppModelObserver, empty implementation.
	* @param TInt aError
	*/
	void UnrecoverableError(TInt aError); 



private:
	/**
	* Compound control for the selection of contacts.
	*/
	CContactsSelector* iSelector;

	/**
	* ContactsAppModel, contacts model 'interface' towards contacts engine.
	*/
	CContactsAppModel* iModel;
	


	
	/**
	* The reference array that was passed on to this dialog from the caller.
	* Contains an array of pointers to CContacuiReturnData objects.
	*/
	CArrayPtr<CContacuiReturnData>& iResultArray; 
	/**
	*Array for vCard Mappings to be able to narrow the 'search'.
	*/
	CArrayFix<TUid>* iMapArray;

	CArrayFixFlat<TUid>* iFieldTypeArray;
	
	
	/**
	* Settings from caller. One or two-column state.
	*/
	TColumnState iColumnState;
	
	CContactDatabase::TContactViewFilter iFilter;
	
	/**
	* Callback to start the category filter 
	*/
	CAsyncCallBack	iStartFilterCallBack;

	/**
	* Settings from caller. Type of data that the caller wants to be returned.
	*/
	TUid iFieldType;



	TInt iResourceId;

	
	CContactsAppListWin* iListBox;

	
	//Flag for : EMailable = 0x1,	ELastWasSIM = 0x2,	ECategoryChanged = 0x4,	EPhoneBookInitialized = 0x8,	EDialogFirstDraw = 0x10
	TInt iFlag;
	
	/**
	* Remember wich category was last choosen
	*/
	TInt  iLastCategory;

	/**
	* Engine categories
	*/ 
	CContactIdArray* iEngineIdArray;
	
	/**
	* Default categories (SIM, Unfiled, All)
	*/
	CArrayFixFlat<TInt>* iDefaultCategories;
	
	/**
	* Mapping array that maps default categories and engine categories to the choice list 
	*/
	CArrayFixFlat<TInt>* iMappingArray;


protected: 
	/**
	* react to event in iCategoryChoiceList
	*/
	void HandleControlStateChangeL(TInt aControlId);

	
};


/**
* CContacuiReturnData class. Contains ID and Data in an array that is defined to be sent back to the 
* caller. It is used by the listdialog to store the data that the user has choosed in the ContacUiListDialog 
* and ContacUiListAltDialog.
* @see ContacUiListDialog, ContacUiListAltDialog
*/
class CContacuiReturnData : public CBase
	{
public:
	IMPORT_C static CContacuiReturnData* NewL();
	IMPORT_C ~CContacuiReturnData();

	/**
	* Method that returns the ID of a contact.
	* @return A ContactID of the type TContactItemId.
	*/
	IMPORT_C TContactItemId Id();

	/**
	* Method that returns array of data (TUid aFieldType) specified in method SetOptions in Contacuilistdialog.
	* @return CDesCArray* of TUid's
	* @see Contacuilistdialog: SetReturnType(TUid aFieldType).
	*/
	IMPORT_C CDesCArray* ReturnedData();

public:
	/**
	* Method that stores the contact ID in the object.
	* @param A TContactItemId defined in CntDef.h.
	*/
	void SetId(TContactItemId aId);

	/**
	* Method that stores the fieldtype data for the object.
	* @param A CDesCArray& that holds TUid fieldtype data per Contacuireturndata object.
	*/
	void SetArrayL(CDesCArray& aCurrentIdArray);

private:
	CContacuiReturnData();
	void ConstructL();

	/**
	* Array that holds the fieldtype data.
	*/
	CDesCArray* iReturnArray; 

	/**
	* Variable that holds the contact ID.
	*/
	TContactItemId iCurrentContactId;
	};


#endif
