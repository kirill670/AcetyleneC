// EIKWBTB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKWBTB_H__
#define __EIKWBTB_H__

#include <coecntrl.h>
class CEikWindowButtonGroup;
class CEikMover;
class MEikWindowButtonGroupObserver;

/**
 * The CEikWindowButtonTitleBar class provides a titlebar which comprises of a CEikMover
 * and a CEikWindowButtonGroup, and is intended for use as a window/frame titlebar.
 *
 * @since ER5U
 */
class CEikWindowButtonTitleBar : public CCoeControl
	{
public://C'tor ,D'tor
	IMPORT_C static CEikWindowButtonTitleBar* NewL();
	IMPORT_C ~CEikWindowButtonTitleBar();
public://framework from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void SizeChanged();
	IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
public:// accessors
	IMPORT_C void SetButtonObserver(MEikWindowButtonGroupObserver& aObserver);
	IMPORT_C CEikWindowButtonGroup& Buttons() const;
	IMPORT_C CEikMover& Mover() const;
	IMPORT_C void SetText(HBufC* aText);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetTextFromResourceL(TResourceReader& aReader);
	IMPORT_C void SetActive(TBool aActive);
	IMPORT_C TBool IsActive() const;
protected: //framework from CCoeControl
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	CEikWindowButtonTitleBar();
	void ConstructL();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	CEikWindowButtonGroup*	iWindowButtons;
	CEikMover*				iMover;
	};

#endif