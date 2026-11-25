// CNTUIFINDDLG.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTUIFINDDLG_H__
#define __CNTUIFINDDLG_H__

#include <eikdialg.h>			// CEikDialog
#include <cmmobs.h>				// MContactsAppModelObserver
#include <cmcobs.h>				// MContactsControlObserver
#include <cntdef.h>				// TContactItemId

class ContacUiFindHistory;
class CEikComboBox;
class CContactsAppModel;

/**
* This find dialog has two options; search in all and search in names. Search in all
* searches in all text in all contacts beginning/middle/or end of words. Search in 
* names seaches in First, Last and Company name and finds only words that starts with 
* the search criteria.
* 
* @see Cntuifind
*/
class CContactUiFindDialog : public CEikDialog, public MContactsAppModelObserver, public MContactsControlObserver
	{
public:
	IMPORT_C static TBool RunDlgLD(TContactItemId& aItemId);

private:
	/**
	*Exported method which creates the object and takes a reference to an ContactItemId.
	*@param TContactItemId& aItemId : The items itemid that was found is stored in this parameter.
	*@see cntdef.h
	*/
	CContactUiFindDialog(TContactItemId& aItemId);
	~CContactUiFindDialog();

private: // from CCoeControl
	/**
	* From CCoeControl
	* Launches context sensitive help for this dialog
	*/
	void GetHelpContext(TCoeHelpContext& aContext) const;

private: // from CEikDialog
	/**
	* From CEikDialog. Does nothing for the moment
	*/
	void PreLayoutDynInitL();
	
	/**
	* From CEikDialog. Loads the combobox in the dialog
	*/
	void PostLayoutDynInitL();
	
	/**
	* From CEikDialog takes care of the entered data in the finddialog and passes it to StoreL in class cntuifind.
	* @param TInt aButtonId: The id of the button.
	* @return A TBool : Always returning ETrue.
	*/
	TBool OkToExitL(TInt aButtonId);

private: // from MContactsAppModelObserver
	/**
	* Reacts to a change in the model. Currently in this version no updates in list dialog if model is updated.
	* Empty implementation.
	*/
	void HandleContactsAppModelChangeL(TInt aFlags, TInt aItemHighlightIndex);

	/**
	* From MContactsAppModelObserver, empty implementation.
	* @param TInt aError
	*/
	void UnrecoverableError(TInt aError); 

private: // from MContactsControlObserver
	/**
	* Deal with Contacts specific events.
	* @param CCoeControl* aControl: The control that triggered the event.
	* @param TContactsEvent aEventType: The type of event that was triggered.
	*/
	void HandleContactsEventL( CCoeControl* aControl, TContactsEvent aEventType ); 

private:
	/**
	* Pointer to Cntuifind object
	*/
	ContacUiFindHistory* iFindHistory;

	/**
	* Passed over to founddialog. The chosen contacts id is stored in 
	* this variable and could be accessed when dialog closes.
	*/
	TContactItemId& iContactItemId;

	/**
	* Reference to ContactsAppModel
	*/
	CContactsAppModel* iModel;
	};

#endif // __CNTUIFINDDLG_H__