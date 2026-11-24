/*
* ============================================================================
*  Name     : Eikslb.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

// EIKSLB.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKSLB_H__)
#define __EIKSLB_H__

#include <eikfrlb.h>

class MTextListBoxModel;
class CFont;
class CSettingsListBoxData;
class CSettingsListBoxView;

class CSettingsListBoxItemDrawer : public CFormattedCellListBoxItemDrawer
	{
public:
	IMPORT_C CSettingsListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel,
					    const CFont* aFont,
					    CSettingsListBoxData* aSettingsData);

	IMPORT_C ~CSettingsListBoxItemDrawer();
	IMPORT_C CSettingsListBoxData* SettingsData() const;
public: // from CTextListItemDrawer
	IMPORT_C void DrawItemText(TInt aItemIndex,
				   const TRect& aItemTextRect,
				   TBool aItemIsCurrent,
				   TBool aViewIsEmphasized,
				   TBool aItemIsSelected) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();

	};



/**
* List box base class. Creates listbox view and item drawer classes. This class
* is used throughout @c AknListBoxLinesTemplate< T > class. 
* The @c CEikSettingsListBox uses @c CSettingsListBoxView as a list box view 
* class and a @c CSettingsListBoxItemDrawer as an item drawer. 
*/
class CEikSettingsListBox : public CEikFormattedCellListBox
	{
public:

    /**
     * C++ default constructor.
     */
    IMPORT_C CEikSettingsListBox();

public:

    /**
     * Gets an item drawer of @c CEikSettingListBox which handles drawing of 
     * single list box items and manages their properties.
     * 
     * @return Pointer to the item drawer instance.
     */
	IMPORT_C CSettingsListBoxItemDrawer* ItemDrawer() const;

protected:

    /**
     * Creates an item drawer for @c CEikSettingsListBox.
     */
	IMPORT_C void CreateItemDrawerL();

public: // from CEikListBox

    /**
     * From @c CEikListBox. 
     *
     * Creates the list box view. The function is called 
     * by @c ConstructL() to create an instance of the appropriate list box 
     * view class for this list box. The returned instance is owned by this 
     * object, and does not have to have its second-phase constructor run. 
     * This function is called by @c CreateViewL().
     *
     * @return Pointer to a newly constructed list box view for this object.
     */
	IMPORT_C CListBoxView* MakeViewClassInstanceL();

public: // from CCoeControl

    /**
     * From @c CCoeControl. 
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected:

    /**
     * Gets a list box view class as @c CSettingsListBoxView.
     *
     * @return Pointer to the list box view class object.
     */
	CSettingsListBoxView* View() { return (CSettingsListBoxView*)iView; }

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // listbox use only
	IMPORT_C virtual void CEikListBox_Reserved();
    
	};

class CSettingsListBoxView : public CFormattedCellListBoxView
	{
public: // from CListBoxView
	CSettingsListBoxView() {}
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C void DrawItem(TInt aItemIndex) const;
	inline CSettingsListBoxItemDrawer *ItemDrawer() const;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
	};


inline CSettingsListBoxItemDrawer* CSettingsListBoxView::ItemDrawer() const
	{ return (CSettingsListBoxItemDrawer*)iItemDrawer; }


// __EIKSLB_H__
#endif



