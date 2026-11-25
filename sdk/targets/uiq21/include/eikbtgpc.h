// EIKBTGPC.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBTGPC_H__)
#define __EIKBTGPC_H__

#include <coecntrl.h>
#include <eikbtgrp.h>
#include <eikcmobs.h>
#include <lafpublc.h>
#include <uikon.hrh>

class MEikCommandObserver;
class CEikButtonGroupStack;
class CEikCommandButton;

/**
 *
 * Provides a wrapper around the different button arrays used in both
 * pen, and no-pen devices.  Requesting aUse as either EView or EDialog 
 * will create the default button set for the host device; the other options 
 * are included primarily for testing.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikButtonGroupContainer : public CCoeControl, public MEikCommandObserver
	{
public:
	/**
	 * Describes how the container is being used.
	 *
	 * The enumeration is used by the system to create the appropriate (DFRD
	 * specific) button group for the specified type. From 6.1 only two use
	 * types can be specified: <code>EView</code> or <code>EDialog</code>.
	 */
	enum TUse
		{
		EView				=SLafButtonGroupContainer::EView,			/** In a view. */
		EDialog				=SLafButtonGroupContainer::EDialog,			/** In a dialog. */
		EToolbar			=SLafButtonGroupContainer::EToolbar,		/** @deprecated */
		ECba				=SLafButtonGroupContainer::ECba,			/** @deprecated */
		EDialogButtons		=SLafButtonGroupContainer::EDialogButtons,	/** @deprecated */
		EDeviceCustomStart	=0x100000, 
		EDeviceCustomEnd	=0x800000
		};

	/**
	 * Describes the orientation of the container.
	 */
	enum TOrientation
		{
		EVertical	=SLafButtonGroupContainer::EVertical,	/** Buttons are laid out vertically. */
		EHorizontal =SLafButtonGroupContainer::EHorizontal	/** Buttons are laid out horizontally. */
		};

	/**
	 * Relative positions of the container and the control which uses it.
	 */
	enum TLocation
		{
		EInternal	=SLafButtonGroupContainer::EInternal,	/** E.g. dialog buttons. */
		EExternal	=SLafButtonGroupContainer::EExternal	/** E.g. toolbar or cba. */
		};

	/**
	 * Flags for the display of hotkeys.
	 */
	enum THotKeyFlags
		{
		EShowHotKey			=0x01,	/** Hotkeys for commands should be shown. */
		EPlainHotKey		=0x02	/** Hotkeys for commands should not be shown. */
		};
	enum TFlags
		{
		EAddToStack			=0x01,
		EDelayActivation	=0x02,
		EUseMaxSize			=0x04,
		};
public:
	IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
													MEikCommandObserver* aCommandObserver,TInt aResourceId,
													TUint aFlags=EAddToStack);
	IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
													MEikCommandObserver* aCommandObserver,TInt aResourceId,
													const CCoeControl& aParent,TUint aFlags=EAddToStack);
	IMPORT_C ~CEikButtonGroupContainer();
	IMPORT_C static CEikButtonGroupContainer* Current();
public:
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void SetCommandL(TInt aPosition,TInt aResourceId);
	inline void SetCommandL(TInt aCommandId,const TDesC& aText);
	inline void SetCommandL(TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void SetCommandL(TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	IMPORT_C void SetCommandSetL(TInt aResourceId);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandToStackL(TInt aPosition,TInt aResourceId);
	IMPORT_C void AddCommandSetToStackL(TInt aResourceId);
	IMPORT_C void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
	IMPORT_C void SetDefaultCommand(TInt aCommandId); 
	IMPORT_C TSize CalcMinimumSizeL(TInt aResourceId) const;
	IMPORT_C void CleanupCommandPushL(TInt aPosition);
	inline void CleanupCommandPop();
	IMPORT_C void CleanupCommandPop(TInt aCount);
	inline void CleanupCommandPopAndDestroy();
	inline void CleanupCommandPopAndDestroy(TInt aCount);
	IMPORT_C TInt MaxCommands() const;
	IMPORT_C TInt ButtonCount() const;
	IMPORT_C void DimCommand(TInt aCommandId,TBool aDimmed);
	IMPORT_C TBool IsCommandDimmed(TInt aCommandId) const;
	IMPORT_C void MakeCommandVisible(TInt aCommandId,TBool aVisible);
	IMPORT_C TBool IsCommandVisible(TInt aCommandId) const;
	IMPORT_C void AnimateCommand(TInt aCommandId);
	IMPORT_C TLocation Location() const;
	IMPORT_C CEikCommandButton* CommandButtonOrNull(TInt aCommandId) const;
	// For use by EExternal button groups only.
	IMPORT_C void SetBoundingRect(const TRect& aRect);
	IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
	//
	IMPORT_C CCoeControl* ControlOrNull(TInt aCommandId) const;
	IMPORT_C CEikCommandButton* ButtonById(TInt aCommandId) const;
	IMPORT_C TInt PositionById(TInt aCommandId) const;
	IMPORT_C void UpdateHotKey(TInt aCommandId,THotKeyFlags aFlags,TInt aKeyId);
	IMPORT_C void UpdateCommandObserverL(TInt aPos,MEikCommandObserver& aCommandObserver);
	IMPORT_C void RemoveCommandObserver(TInt aPos);
	IMPORT_C TBool DelayActivation() const;
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void MakeVisible(TBool aVisible);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	enum TCommandOp {ESet, EAdd, EPush};
private:
	class TCmdPos
		{
	public:
		inline TCmdPos();
		inline TCmdPos(TInt aPos,TInt aCmd);
	public:
		TInt iPos;
		TInt iCmd;
		};
	class TCmdObserver
		{
	public:
		inline TCmdObserver(TInt aPos,MEikCommandObserver& aObserver);
	public:
		TInt iPos;
		MEikCommandObserver& iObserver;
		};
	class CCmdObserverArray : public CArrayFixFlat<TCmdObserver>
		{
	public:
		inline CCmdObserverArray();
		TInt FindIndex(TInt aPos);
		};
private:
	CEikButtonGroupContainer(TUse aUse);
	void ConstructL(TOrientation aOrientation,MEikCommandObserver* aCommandObserver,TInt aResourceId,TUint aFlags);
	IMPORT_C void DoSetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aCommandId,const TDesC* aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aPosition,TInt aResourceId,TCommandOp aOp);
	inline CCoeControl* ButtonGroupAsControl() const;
	void UpdateRect();
	static void CleanupCommandDestroy(TAny* aPtr);
	TCmdPos DoCleanupCommandPop();
	void DoCleanupCommandPopAndDestroy();
private: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();
private: // from MEikCommandObserver
	void ProcessCommandL(TInt aCommandId);
	CCoeControl* CreateCustomCommandControlL(TInt aControlType);
private:
	MEikButtonGroup* iButtonGroup;
	TUse iUse;
	CArrayFix<TCmdPos>* iCommandsCleanup;
	MEikCommandObserver* iCommandObserver;
	CCmdObserverArray* iObserverArray;
	TDblQueLink iBtLink;
private:
	friend class CCmdObserverArray;
	friend class CEikButtonGroupStack;
	};


/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            Position within the button group.
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aText"
 *            Text for the button.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            Position within the button group.
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            Position within the button group.
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aText"
 *            Text for the button.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            Position within the button group.
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aFile"
 *            EPOC multi-bitmap file containing mask and bitmap
 *            images.
 * @param     "TInt aBitmapId"
 *            Index within <code>aFile</code> of the image bitmap.
 * @param     "TInt aMaskId"
 *            Index within <code>aFile</code> of a single-plane
 *            bitmap to use as the mask.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            Position within the button group.
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aText"
 *            Text for the button.
 * @param     "const TDesC& aFile"
 *            EPOC multi-bitmap file containing mask and bitmap
 *            images.
 * @param     "TInt aBitmapId"
 *            Index within <code>aFile</code> of the image bitmap.
 * @param     "TInt aMaskId"
 *            Index within <code>aFile</code> of a single-plane
 *            bitmap to use as the mask.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            Position within the button group.
 * @param     "TInt aResourceId"
 *            ID of a resource specifying the text, bitmaps and
 *            command ID.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aResourceId)
	{DoSetCommandL(aPosition,aResourceId,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aText"
 *            Text for the button.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aCommandId,&aText,NULL,NULL,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aCommandId,NULL,&aBitmap,&aMask,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aCommandId,&aText,&aBitmap,&aMask,ESet);}

/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aFile"
 *            EPOC multi-bitmap file containing mask and bitmap
 *            images.
 * @param     "TInt aBitmapId"
 *            Index within <code>aFile</code> of the image bitmap.
 * @param     "TInt aMaskId"
 *            Index within <code>aFile</code> of a single-plane
 *            bitmap to use as the mask.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aCommandId,NULL,aFile,aBitmapId,aMaskId,ESet);}
/**
 *
 * Sets a command button's content, overwriting any previous contents at
 * that position.
 *
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aCommandId"
 *            Command ID the new button will send.
 * @param     "const TDesC& aText"
 *            Text for the button.
 * @param     "const TDesC& aFile"
 *            EPOC multi-bitmap file containing mask and bitmap
 *            images.
 * @param     "TInt aBitmapId"
 *            Index within <code>aFile</code> of the image bitmap.
 * @param     "TInt aMaskId"
 *            Index within <code>aFile</code> of a single-plane
 *            bitmap to use as the mask.
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aCommandId,&aText,aFile,aBitmapId,aMaskId,ESet);}
/**
 *
 * Adds a command button at the specified position in the container.
 *
 * The button may have an optional text string or a bitmap image; bitmaps
 * may optionally have a mask.
 *
 * @param     "TInt aPosition"
 *            Position for the new button.
 * @param     "TInt aCommandId"
 *            Command ID for the new button.
 * @param     "const TDesC& aText"
 *            Text for the button.
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,EAdd);}
/**
 *
 * Adds a command button at the specified position in the container.
 *
 * The button may have an optional text string or a bitmap image; bitmaps
 * may optionally have a mask.
 *
 * @param     "TInt aPosition"
 *            Position for the new button.
 * @param     "TInt aCommandId"
 *            Command ID for the new button.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,EAdd);}
/**
 *
 * Adds a command button at the specified position in the container.
 *
 * The button may have an optional text string or a bitmap image; bitmaps
 * may optionally have a mask.
 *
 * @param     "TInt aPosition"
 *            Position for the new button.
 * @param     "TInt aCommandId"
 *            Command ID for the new button.
 * @param     "const TDesC& aText"
 *            Text for the button.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,EAdd);}
/**
 * Adds a button containing the bitmaps specified at aPosition.
 * Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,EAdd);}
/**
 *
 * Adds a command button at the specified position in the container.
 *
 * The button may have an optional text string or a bitmap image; bitmaps
 * may optionally have a mask.
 *
 * @param     "TInt aPosition"
 *            Position for the new button.
 * @param     "TInt aCommandId"
 *            Command ID for the new button.
 * @param     "const TDesC& aText"
 *            Text for the button.
 * @param     "const TDesC& aFile"
 *            File containing the bitmap and any mask for the
 *            button.
 * @param     "TInt aBitmapId"
 *            ID of the bitmap, within <code>aFile</code>, for the
 *            button.
 * @param     "TInt aMaskId"
 *            ID of the mask, within <code>aFile</code>, for the
 *            button.
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,EAdd);}
/**
 *
 * Pushes a command button onto a position's button stack.
 *
 * As with <code>SetCommandL()</code> but allows the previous command to
 * be retrieved at any time by calling <code>RemoveCommand()</code>.
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            The button's position in the group.
 * @param     "TInt aCommandId"
 *            The button's command ID.
 * @param     " const TDesC& aText"
 *            Text for the button.
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,EPush);}
/**
 *
 * Pushes a command button onto a position's button stack.
 *
 * As with <code>SetCommandL()</code> but allows the previous command to
 * be retrieved at any time by calling <code>RemoveCommand()</code>.
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            The button's position in the group.
 * @param     "TInt aCommandId"
 *            The button's command ID.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,EPush);}
/**
 *
 * Pushes a command button onto a position's button stack.
 *
 * As with <code>SetCommandL()</code> but allows the previous command to
 * be retrieved at any time by calling <code>RemoveCommand()</code>.
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            The button's position in the group.
 * @param     "TInt aCommandId"
 *            The button's command ID.
 * @param     " const TDesC& aText"
 *            Text for the button.
 * @param     "const CFbsBitmap& aBitmap"
 *            Bitmap for the button.
 * @param     "const CFbsBitmap& aMask"
 *            Mask bitmap for <code>aBitmap</code>.
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,EPush);}
/**
 *
 * Pushes a command button onto a position's button stack.
 *
 * As with <code>SetCommandL()</code> but allows the previous command to
 * be retrieved at any time by calling <code>RemoveCommand()</code>.
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            The button's position in the group.
 * @param     "TInt aCommandId"
 *            The button's command ID.
 * @param     "const TDesC& aFile"
 *            EPOC multi-bitmap file containing mask and bitmap
 *            images.
 * @param     "TInt aBitmapId"
 *            Index within <code>aFile</code> of the image bitmap.
 * @param     "TInt aMaskId"
 *            Index within <code>aFile</code> of a single-plane
 *            bitmap to use as the mask.
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,EPush);}
/**
 *
 * Pushes a command button onto a position's button stack.
 *
 * As with <code>SetCommandL()</code> but allows the previous command to
 * be retrieved at any time by calling <code>RemoveCommand()</code>.
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            The button's position in the group.
 * @param     "TInt aCommandId"
 *            The button's command ID.
 * @param     " const TDesC& aText"
 *            Text for the button.
 * @param     "const TDesC& aFile"
 *            EPOC multi-bitmap file containing mask and bitmap
 *            images.
 * @param     "TInt aBitmapId"
 *            Index within <code>aFile</code> of the image bitmap.
 * @param     "TInt aMaskId"
 *            Index within <code>aFile</code> of a single-plane
 *            bitmap to use as the mask.
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,EPush);}
/**
 *
 * Pushes a command button onto a position's button stack.
 *
 * As with <code>SetCommandL()</code> but allows the previous command to
 * be retrieved at any time by calling <code>RemoveCommand()</code>.
 * There are several overloads of this function which allow the command
 * button's image and text to be optionally set. All these functions will
 * raise a panic if the supplied position is out of range.If an image is
 * set, a mask must also be specified to guarantee compliance with
 * different colour schemes. Ownership of bitmap arguments is transferred
 * at the end of the function.If a button position is not supplied,
 * <code>CEikButtonGroupContainer</code> attempts to identify which
 * button to overwrite by command ID. If two buttons have the same ID,
 * which will be altered is not defined. The behaviour is also undefined
 * if <code>aCommandId</code> can't be matched to any button.
 *
 * @param     "TInt aPosition"
 *            The button's position in the group.
 * @param     "TInt aResourceId"
 *            ID of a resource specifying the text, bitmaps and
 *            command ID.
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aResourceId)
	{DoSetCommandL(aPosition,aResourceId,EPush);}
/**
 * Removes a command from the cleanup stack without destroying it.
 */
inline void CEikButtonGroupContainer::CleanupCommandPop()
	{CleanupCommandPop(1);}
/**
 *
 * Removes a command which was pushed onto the cleanup stack.
 *
 * It does this by calling <code>CleanupCommandPushL()</code>, rolling
 * back to the previous details. The command buttons popped are
 * destroyed.
 */
inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy()
	{CleanupStack::PopAndDestroy();}
/**
 *
 * Removes one or more commands which were pushed onto the cleanup stack.
 *
 * It does this by calling <code>CleanupCommandPushL()</code>, rolling
 * back to the previous details. The command buttons popped are
 * destroyed.
 *
 * @param     "TInt aCount"
 *            Number of commands to pop and destroy.
 */
inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy(TInt aCount)
	{CleanupStack::PopAndDestroy(aCount);}

#endif
