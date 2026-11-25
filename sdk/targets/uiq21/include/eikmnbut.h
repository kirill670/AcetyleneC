// EIKMNBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMNBUT_H__)
#define __EIKMNBUT_H__

#include <eikmobs.h>
#include <eikcmbut.h>

class CEikMenuPane;

/**
 *
 * A menu button enables a user to initiate display of a menu.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikMenuButton : public CEikCommandButton, private MEikMenuObserver
	{
public:
	IMPORT_C CEikMenuButton();
	IMPORT_C ~CEikMenuButton();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void LaunchPopupMenuL(MEikMenuObserver* aObserver);
	IMPORT_C void SetMenuPaneId(TInt aMenuPaneId);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
public: // from CEikButtonBase
	IMPORT_C void Animate();
private: // from MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommandId);
	IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
private:
	void ClosePopupMenu();
	void DoLaunchPopupMenuL();
private:
	MEikMenuObserver* iMenuObserver;
	CEikMenuPane* iMenuPopup;
	TInt iMenuPaneId;
	};


#endif
