// EIKWBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKWBUT_H__
#define __EIKWBUT_H__

#define KEikWButDefaultButtonPos -1

#include <coecntrl.h>
#include <eikwbut.hrh>
class CEikCommandButton;
class CEikControlGroup;

/**
 * The MEikWindowButtonGroupObserver class defines an interface to be implemented by a client that wishes to observe events from the window buttons.
 *
 * @since ER5U
 */
class MEikWindowButtonGroupObserver
	{
public:
	IMPORT_C virtual void HandleWindowButtonControlEventL(TInt aId, MCoeControlObserver::TCoeEvent aEventType)=0;
	};

/**
 * The CEikWindowButtonGroup class implements a control which is a horizontal group of buttons
 * for use on the titlebar of a window or 'frame'.
 * Various 'built in styles' of button, or custom buttons may be used.
 * Each button must have a unique integer id.
 *
 * @since ER5U
 */
class CEikWindowButtonGroup : public CCoeControl, public MCoeControlObserver
	{
public:// C'tor, D'tor
	IMPORT_C ~CEikWindowButtonGroup();
	IMPORT_C static CEikWindowButtonGroup* NewL();
private:
	CEikWindowButtonGroup();
	void ConstructL();
public:// Framework from CCoeControl
	IMPORT_C TSize MinimumSize() const;
	IMPORT_C void SetContainerWindowL(const CCoeControl& aWindowOwner);
protected:
	IMPORT_C void SizeChanged();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
public://From MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public:// Accessors
	IMPORT_C void SetButtonObserver(MEikWindowButtonGroupObserver& aObserver);
	IMPORT_C void SetContainerWindowL(TInt aId, CCoeControl& aWindowOwner);
	IMPORT_C void SetButtonDimmed(TBool aDimmed, TInt aId);
	IMPORT_C TBool IsDimmed(TInt aId);
	IMPORT_C CCoeControl* Button(TInt aId) const;
	IMPORT_C void AddButtonL(TInt aId, CCoeControl* aButton, TInt aPos=KEikWButDefaultButtonPos);
	IMPORT_C void RemoveButton(TInt aId);
	IMPORT_C void AddCloseButtonL(TInt aPos=KEikWButDefaultButtonPos);
	IMPORT_C void AddMinimizeButtonL(TInt aPos=KEikWButDefaultButtonPos);
	IMPORT_C void AddMaximizeButtonL(TInt aPos=KEikWButDefaultButtonPos);
	IMPORT_C void AddStandardSizeButtonL(TInt aPos=KEikWButDefaultButtonPos);
	IMPORT_C void AddResizeButtonL(TInt aPos=KEikWButDefaultButtonPos);
	IMPORT_C CEikControlGroup& ButtonGroup() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void AddStandardButtonL(TInt aId, TInt aResourceId, TInt aPos);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	MEikWindowButtonGroupObserver*		iObserver;
	CEikControlGroup*					iButtonGroup;
	};

#endif
