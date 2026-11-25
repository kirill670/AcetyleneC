// EIKAUFTY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// Defines mix-in interace to break dependencey of Eikon Application UI 
// on controls

#if !defined(__EIKAUFTY_H__)
#define __EIKAUFTY_H__

#include <f32file.h>
#include <e32base.h>
#include <eikdef.h>

class CEikHotKeyTable;
class CEikMenuBar;
class CEikMenuPane;
class CEikCommandButton;
class CEikToolBar;
class CEikButtonGroupContainer;
class CEikAppUi;
class CEikonEnv;
class CEikStatusPane;

/**
 *
 * This class defines a mixin interface to break the dependency of the
 * Uikon Application User Interface on controls.
 * @since 6.0
 * @lib " eikcore.lib "
 */
class MEikAppUiFactory
	{
public:
	virtual void CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi) =0;
	virtual TRect ClientRect() = 0;
	virtual void ReadAppInfoResourceL(TInt aResourceFileOffset,CEikAppUi* aAppUi) = 0;
	virtual void LaunchPopupMenuL(
									TInt aResourceId,
									const TPoint& aTargetPos,
									TPopupTargetPosType aTargetType,
									const CEikHotKeyTable* aHotKeyTable,
									CEikAppUi* aAppUi) = 0;

	virtual void DoLaunchPopupL(TInt aResourceId,const TPoint& aTargetPos, const CEikHotKeyTable* aHotKeyTable, 
								TPopupTargetPosType aTargetType,CEikAppUi* aAppUi) = 0;

   	virtual void ClosePopup(CEikAppUi* aAppUi) = 0;
	virtual void StopDisplayingMenuBar() = 0;
	virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,
									const CEikHotKeyTable* aHotKeyTable,CEikAppUi* aAppUi) = 0;
	virtual void CreateHotKeyControlL(TInt aResourceId, CEikAppUi* aAppUi) = 0;

	/**
	 * Gets a pointer to the menu bar.
	 *
	 * @returns   " CEikMenuBar* "
	 *            Pointer to the menu bar.
	 */
	virtual CEikMenuBar* MenuBar() const = 0;

	/**
	 * Replaces or clears a menu bar, returning a pointer to the replaced
	 * menu bar.
	 *
	 * @param     " CEikMenuBar* aMenu "
	 *            The new menu bar. This can be <code>NULL</code> to
	 *            clear an existing menu bar.
	 * @returns   " CEikMenuBar* "
	 *            Pointer to the replaced menu bar.
	 */
	virtual CEikMenuBar* SwapMenuBar(CEikMenuBar* aMenu) = 0;
	virtual CEikMenuPane* Popup() const = 0;

	/**
	 * Gets a pointer to the tool bar.
	 *
	 * @returns   " CEikButtonGroupContainer* "
	 *            Pointer to the tool bar.
	 */
	virtual CEikButtonGroupContainer* ToolBar() const = 0;

	/**
	 * Replaces or clears a button group, returning a pointer to the replaced
	 * button group.
	 *
	 * @param     " CEikButtonGroupContainer* aNewGroup "
	 *            The new button group. This can be <code>NULL</code> to
	 *            clear an existing button group.
	 * @returns   " CEikButtonGroupContainer* "
	 *            Pointer to the replaced button group.
	 */
	virtual CEikButtonGroupContainer* SwapButtonGroup(CEikButtonGroupContainer* aNewGroup) = 0;

	/**
	 * Gets a pointer to the tool band.
	 *
	 * @returns   " CEikToolBar* "
	 *            Pointer to the tool band.
	 */
	virtual CEikToolBar* ToolBand() const = 0;

	/**
	 * Gets a pointer to the title band.
	 *
	 * @returns   " CEikToolBar* "
	 *            Pointer to the title band.
	 */
	virtual CEikToolBar* TitleBand() const = 0;

	/**
	 * Gets a pointer to the status pane.
	 *
	 * @returns   " CEikStatusPane* "
	 *            Pointer to the status pane
	 */
	virtual CEikStatusPane* StatusPane() const = 0;

	/**
	 * Replaces or clears a tool band, returning a pointer to the replaced
	 * tool band.
	 *
	 * @param     " CEikToolBar* aToolBand "
	 *            The new tool band. This can be <code>NULL</code> to
	 *            clear an existing tool band.
	 * @returns   " CEikToolBar* "
	 *            Pointer to the replaced tool band.
	 */
	inline CEikToolBar* SwapToolBand(CEikToolBar* aToolBand);

	/**
	 * Replaces or clears a title band, returning a pointer to the replaced
	 * title band.
	 *
	 * @param     " CEikToolBar* aTitleBand "
	 *            The new title band. This can be <code>NULL</code> to
	 *            clear an existing title band.
	 * @returns   " CEikToolBar* "
	 *            Pointer to the replaced title band.
	 */
	inline CEikToolBar* SwapTitleBand(CEikToolBar* aTitleBand);

	/**
	 * Creates a standard tab button.
	 *
	 * @returns   "CEikCommandButton*"
	 *            Pointer to the created tab button.
	 */
	virtual CEikCommandButton*  CreateStandardTabButtonL() const = 0;
	virtual void CreateEmbeddedL(CEikonEnv& aEikonEnv) = 0;
	virtual void DestroyEmbedded(CEikonEnv& aEikonEnv) = 0;
	virtual void HandleResourceChangeL(TInt aType) = 0;
protected:
	/**
	 * Defines the type of tool bar.
	 */
	enum TToolBarType
		{
		EBand,	/** Defines a band tool bar. */
		ETitle	/** Defines a title tool bar. */
		};
private:
	virtual CEikToolBar* SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType) = 0;
	};

inline CEikToolBar* MEikAppUiFactory::SwapToolBand(CEikToolBar* aToolBand)
	{return SwapToolBar(aToolBand,EBand);}
inline CEikToolBar* MEikAppUiFactory::SwapTitleBand(CEikToolBar* aTitleBand)
	{return SwapToolBar(aTitleBand,ETitle);}

#endif
