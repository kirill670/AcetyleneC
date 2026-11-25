// QikTaskMenu.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef QIKTASKMENU_H
#define QIKTASKMENU_H

#include <coecntrl.h>
#include <eikappui.h>
#include <eikmobs.h>


class MQikTaskMenuObserver
	{
public:
	/**
	 * Lets an observing class handle a menu command.
	 *
	 * @param aCommandId the command id of the tapped menu option.
	 */
	virtual void ProcessTaskMenuCommandL(TInt aCommandId) = 0;
	};


class CRichText;
class CQikTaskEntry;
class CQikTaskMenu: public CBase,
							private MEikMenuObserver
	{
public:
	// Use directly
	IMPORT_C static void LaunchLD(TInt aMenuPaneId, TInt aTaskArrayId, const TDesC& aTaskBuf);

	// Construct before use
	IMPORT_C static CQikTaskMenu* NewL(TInt aMenuPaneId, TInt aTaskArrayId);
	IMPORT_C void LaunchTaskL(const TDesC& aTaskBuf=KNullDesC);
	IMPORT_C ~CQikTaskMenu();

	// Modify menu
	IMPORT_C TInt AddMenuItemL(TInt aResourceId);
	IMPORT_C void SetMenuObserver(MQikTaskMenuObserver *aMenuObserver);
private: // from MEikCommandObserver
	void ProcessCommandL(TInt aCommandId);
	void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
private:
	CQikTaskMenu(TInt aMenuPaneResId);
	CQikTaskMenu();
	
	void ConstructL(TInt aResource);
	void DoLaunchTaskL(TInt aMenuOption);
	void ConstructMenuPaneL(TInt aResource);
	void ShowMenuL();
	void DestroyMenu();
	void SetDestroyWhenFinished(TBool aDestroyWhenFinished);
private:	
	TBool iDestroyWhenFinished;					/** If ETrue, this object will be destroyed after ProcessCommand */
	CEikMenuPane* iMenu;						/** This choice list is used to let the user choose what to do when clicking on a phone number.	*/
	CArrayPtrFlat<CQikTaskEntry>* iTaskArray;	/** Holds the Dnl entries. */
	MQikTaskMenuObserver* iMenuObserver;		/** A menu observer */
	HBufC *iParseBuf;							/** Used when sending a DNL to any app. */
	TInt iMenuPaneResId;						/** Used to store the menu pane resource id. This is needed everytime the ShowMenuL() is called. */
	
	CEikonEnv *iEikEnv;
	};


#endif // QIKTaskMenu_H