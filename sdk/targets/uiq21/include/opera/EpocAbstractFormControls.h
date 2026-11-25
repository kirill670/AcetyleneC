/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Rob Gregson, Keith Hollis
*/

#ifndef __EPOCABSTRACTFORMCONTROLS_H
#define __EPOCABSTRACTFORMCONTROLS_H

#include <e32std.h>
#include <w32std.h>
#include <coedef.h>
#include <bamdesca.h>

/*************************************************************************

	class MOperaFormControlObserver

	This class is implemented in Opera base code - not for porting
*/

class MOperaFormControlObserver
	{
public:
	virtual void SizeChanged(TSize aSize)=0;
	virtual void ControlStateChanged()=0;
	virtual void FocusGained()=0;
	virtual void FocusLost()=0;
	virtual void HandleKeyEvent(const TKeyEvent& aKeyEvent,TEventCode aType)=0;
	virtual void HandlePointerEvent(const TPointerEvent& aPointerEvent)=0;
	};

/*************************************************************************

	class MOperaFormControl

  	This class and all derived classes are templates for porting
*/

class MOperaFrame;
class OpFormsListener;

class MOperaFormControl
	{
public:
	enum TType 
		{ 
		ENotAFormControl,
		ETextInputField,
		ECheckBox,
		ERadioButton,
		EPushButton,
		ESecretEditor,
		EDropDownChoiceList,
		EListBox,
		ETextInputArea,
		EFileChooser
		};
	virtual ~MOperaFormControl() {}
	virtual TType GetType() const=0;
	virtual void FormReset()=0;
	virtual void FormSetSize(TSize aSize)=0;
	virtual TSize FormGetSize() const=0;
	virtual void FormSetPosition(TPoint aPoint)=0;
	virtual TPoint FormGetPosition() const=0;
	virtual void FormSetVisible(TBool aVisible)=0;
	virtual TBool FormIsVisible() const=0;
	virtual void FormSetDimmed(TBool aDimmed)=0;
	virtual TBool FormIsDimmed() const=0;
public: // new
	// Temporary 'hook' for Core/Bridge/UI interaction due to inconsistent architecture.
	OpFormsListener* iListener;
	};

/*********************************************************************************

	class MOperaStateControl	-  check box
*/

class MOperaStateControl : public MOperaFormControl
	{
public:
	enum TState
		{
		EClear,
		ESet,
		EIndeterminate 
		};
	virtual void FormSetState(TState aState)=0;
	virtual TState FormGetState() const=0;
	};

class MOperaCheckBox : public MOperaStateControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aZoomPercent)=0;
	};

/*************************************************************************
 
	class MOperaTextControl		- text input field, file chooser
*/

class MOperaTextControl : public MOperaFormControl
	{
public:
	enum TClipboardFunc
		{
		ENoClipboard,
		ECut,
		ECopy,
		EPaste
		};
	virtual void SelectAllTextL()=0;
	virtual void FormSetTextL(const TDesC* aText)=0;
	virtual TPtrC GetText()=0;
	virtual void FormClipboardL(TClipboardFunc aClipboardFunc)=0;
	};

/*************************************************************************

	class MOperaSelectionControl
*/

const TInt KNotSpecified=-1;

class MOperaSelectionControl : public MOperaFormControl
	{
public:
	virtual void FormAddItemL(const TDesC& aItemText,TInt aInsertAt=KNotSpecified)=0;
    virtual void FormAddItemsL(MDesCArray* aItemTextArray,TInt aInsertAt=KNotSpecified)=0;
	virtual void RemoveItem(TInt aItemIndex)=0;
	};

/*************************************************************************

	class MOperaTextInputField	
*/

class MOperaTextInputField : public MOperaTextControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aWidthInChars,
							TInt aMaxLength,TInt aZoomPercent,CFont* aFont,
							TBool aReadOnly)=0;
	};

/*********************************************************************************

	class MOperaButton 
*/

class MOperaButton : public MOperaStateControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,const TDesC& aLabel,TInt aZoomPercent,CFont* aFont)=0;
	virtual const TDesC* FormGetLabel()=0;
	virtual void FormSetLabelL(const TDesC& aLabel)=0;
	};

/*************************************************************************

	class MOperaRadioButton
*/

class MOperaRadioButton : public MOperaStateControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aZoomPercent)=0;
	};

/*************************************************************************

	class MOperaSecretEditor
*/

class MOperaSecretEditor : public MOperaTextControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aWidthInChars,
							TInt aMaxLength,TInt aZoomPercent,CFont* aFont,
							TBool aReadOnly)=0;
	};

/*************************************************************************

	class MOperaChoiceList - only displays one line
*/

class MOperaChoiceList : public MOperaSelectionControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aZoomPercent,CFont* aFont)=0;
	virtual void SetChoice(const TInt aItemIndex)=0;
	virtual const TInt GetChoice() const=0;
	};

/*************************************************************************

	class MOperaListBox - displays mutliple lines
*/

class MOperaListBox : public MOperaSelectionControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aNumDisplayLines,
							TBool aAllowMultipleSelection,TInt aZoomPercent,CFont* aFont)=0;
	virtual void SetSelectionsL(CArrayFix<TInt>* aSelections)=0;
	virtual void AddSelectionL(TInt aSelection)=0;
	virtual const CArrayFix<TInt>* GetSelections() const=0;
	};

/*************************************************************************

	class MOperaTextArea
*/

class MOperaTextArea : public MOperaTextControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aRows,
							TInt aCols,TInt aZoomPercent,CFont* aFont,
							TBool aReadOnly)=0;
	};

/*************************************************************************

	class MOperaFileChooser
*/

class MOperaFileChooser : public MOperaTextControl
	{
public:
	virtual void ConstructL(MOperaFrame* aParentFrame,TInt aWidthChars,
							TInt aZoomPercent,const TDesC* aButtonText,CFont* aFont)=0;
	virtual void SetDirectoryL(TDesC& aDirectory)=0;
	};

#endif
