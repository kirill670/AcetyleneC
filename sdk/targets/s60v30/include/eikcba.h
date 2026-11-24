// EIKCBA.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCBA_H__)
#define __EIKCBA_H__

#if !defined(__EIKCTGRP_H__)
#include <eikctgrp.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__EIKBRGRP_H__)
#include <eikbtgrp.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__EIKSBFRM_H__)
#include <eiksbfrm.h>
#endif

#include <eikimage.h>
#include <akncontrol.h>

class CEikLabel;
class CEikCbaButton;
class CCoeBrushAndPenContext;
class MEikCommandObserver;
class TCoeColorUse;

class CAknScrollBar;
class TEikScrollBarModel;

class CEikCbaExtension;
class CEikEnhancedCbaButton;
class TAknsItemID;

class CEikCommandTable;

const TInt KMaxCbaLabelLength = 32;
const TInt KMaxButtonsInCommandTable = 4;

/**
 * Defines a Control Button Array control, used in Avkon to define the softkeys in the
 * control pane.
 *
 */
 NONSHARABLE_CLASS(CEikCba) : public CEikControlGroup, public MEikEnhancedButtonGroup, public MEikScrollBarObserver
// NONSHARABLE_CLASS(CEikCba) : public CEikControlGroup, public MEikButtonGroup, public MEikScrollBarObserver
	{
public:	
	DECLARE_TYPE_ID(0x101F4105)

	// Construction/Destruction
	static CEikCba* NewL(const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	static CEikCba* NewL(TInt aResourceId,const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	static CEikCba* NewLC(const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	static CEikCba* NewLC(TInt aResourceId,const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	~CEikCba();

public:		// new methods
	TInt MaxCommands() const;
	void UpdateCbaLabels(TBool aScrollerOn);

	// Scrollbar handling methods
	void SetSBFrameObserver(MEikScrollBarObserver* aObserver);
	void SetScrollBarModelL(TEikScrollBarModel* aModel);
	const CEikCbaScrollBarFrame* ScrollBarFrame() const;
	CAknScrollBar* VScrollBarAsControl();
	void CreateArrowHeadScrollBarL(); // @since 3.0

public:		// from CEikControlGroup
	void InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex);	// Overridden to prevent setting container window

public:		// from MEikButtonGroup
	void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void SetCommandL(TInt aPosition,TInt aResourceId);
	void SetCommandSetL(TInt aResourceId);
	void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void AddCommandToStackL(TInt aPosition,TInt aResourceId);
	void AddCommandSetToStackL(TInt aResourceId);
	void SetDefaultCommand(TInt aCommandId);
	TSize CalcMinimumSizeL(TInt aResourceId);
	void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
	TInt CommandPos(TInt aCommandId) const;
	void DimCommand(TInt aCommandId,TBool aDimmed);
	TBool IsCommandDimmed(TInt aCommandId) const;
	void MakeCommandVisible(TInt aCommandId,TBool aVisible);
	TBool IsCommandVisible(TInt aCommandId) const;
	void AnimateCommand(TInt aCommandId);
	CCoeControl* AsControl();
	const CCoeControl* AsControl() const;
	void SetBoundingRect(const TRect& aBoundingRect);
	void ReduceRect(TRect& aBoundingRect) const;
	CCoeControl* GroupControlById(TInt aCommandId);
	CCoeControl* GroupControlById(TInt aCommandId) const;
	TInt CommandId(TInt aCommandPos) const;
	TInt ButtonCount() const;
	void RemovePreviousCommand(TInt aPosition);

	// Added during integration for Rel18 by Tim.
	CEikCommandButton* GroupControlAsButton(TInt aCommandId) const ;
	TUint ButtonGroupFlags() const ;
	IMPORT_C void SetButtonGroupFlags(TInt aFlags);

    /**
    * Sets the skin background for this control button array.
    * The new background is used for all the subsequent drawing operations.
    * This method does not itself cause a repaint.
    *
    * @param aIID Skin item ID of the new background. This is one of the constants
    *   defined in AknsConstants.h, and the usual values are
    *   KAknsIIDQsnBgAreaControl, KAknsIIDQsnBgAreaControlPopup, and
    *   KAknsIIDQsnBgAreaControlIdle.
    *
    * @since 2.0
    */
    IMPORT_C void SetSkinBackgroundId(const TAknsItemID& aIID);

public:		// formerly from MTopSetMember<CEikCba>, now reserved
	virtual void Reserved_MtsmPosition();
	virtual void Reserved_MtsmObject();

public:		// from CCoeControl
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TSize MinimumSize();
	void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	void HandleResourceChange(TInt aType);
 
    /**
    * From CCoeControl. Handles pointer events.
    *
    * @param aPointerEvent The pointer event
    */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

public: 		//from MEikEnhancedButtonGroup
	IMPORT_C void OfferCommandListL(const RArray<TInt>& aCommandList);
	IMPORT_C void OfferCommandListL(const TInt aResourceId);
	IMPORT_C TBool IsCommandInGroup(const TInt aCommandId) const;
	IMPORT_C void ReplaceCommand(const TInt aCommandId, const TInt aResourceId);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );


protected:	// from MEikScrollBarObserver
	virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);

protected:  // from CCoeControl
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    void Draw(const TRect& aRect) const;

private:	// new methods
	CEikCba(const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	void BaseConstructL();
	void ConstructL(TInt aResourceId);
	void ConstructFromResourceL(TResourceReader& aReader);
	CEikCbaButton* ButtonById(TInt aCommandId) const;
	void CreateScrollBarFrameL();
	void InsertScrollBarL();
	TEikGroupControl VScrollBarAsGroupControl();
    void CheckSkinAndUpdateContext();
    
    TInt AknLayoutFlags() const;
	void SizeChangedInControlPane();
	void SizeChangedInStaconPane();
	void UpdateFonts();
    

private:	// from CCoeControl
	void SizeChanged();

private:
	TUint					iCbaFlags;
	const CEikCba*			iLink;	// used to maintain the original settings if a client needs to temporarily change its cba 
	CCoeBrushAndPenContext* iBrushAndPenContext;
	MEikCommandObserver*	iCommandObserver;
	CEikCbaScrollBarFrame*	iSBFrame;
    CEikCbaExtension*       iExtension;
	RWindowGroup*			iParentWg;
	
	// new member variable that stores commands in correct order 
	CEikCommandTable* 	iCommandTable;
	};


class CEikCbaButton : public CAknControl
	{
public:
	struct SButtonOptions
		{
		TInt iCommandId;
		TBool iDimmed;
		};
public:
	~CEikCbaButton();
	void ConstructL(TGulAlignmentValue aAlignment);
public:
	void AddCommandL(const TDesC& aText);
	void PushCommandL(TInt aCommandId,const TDesC& aText);
	TInt PopCommand();
	void RemoveCommand(TInt aCommandId);
	void RemovePreviousCommand();
	// AKNLAF start
	void SwitchToShortTextL(TBool aShortText);
	void SetLabelFont(const CFont* aLabelFont);
	void TruncateLabelText();
	// AKNLAF end
public: // from CCoeControl
	void SetContainerWindowL(const CCoeControl& aContainer);
	void ConstructFromResourceL(TResourceReader& aReader, TGulAlignmentValue anAlignment);
	TSize MinimumSize();
	void SetDimmed(TBool aDimmed);
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
public:
    void SetImage(CEikImage &aImage);
    void ReplaceImageByLabel();
    inline TBool IsImageOn() const {return iDoImage;};
    //private:
protected:
//	void UpdateLabelReserveLengthL(const TDesC& aText);
	TInt IndexFromCommandId(TInt aCommandId);
	void UpdateLabelText(TPtrC aLabelText);
private: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
protected:
	TBuf<KMaxCbaLabelLength> iFullLabelText;
	TPtrC iLongLabelText;
	TPtrC iShortLabelText;
	CEikLabel* iLabel;
	CDesCArray* iText;
	CArrayFix<SButtonOptions>* iButtonOptions;
    CEikImage* iImage;
    TBool iDoImage;
	TInt iSpare;
	};

/**
 * Specialization of CEikCbaButton for the new Enhanced CBA button
 * @since 4.0 
 */
class CEikEnhancedCbaButton : public CEikCbaButton
	{
public:
	/**
	 * default constructor
	 */
	CEikEnhancedCbaButton();

	/**
	 * default destructor
	 */
	~CEikEnhancedCbaButton();
	
	/**
	 * returns command's type for current button
	 * @return TInt command's type 
	 */
	TInt CommandType() const;
	
	/**
	 * Sets command type for current button
	 * @param aCommandType Command type to be set
	 */
	void SetCommandType(const TInt aCommandType);
	
	/**
	 * returns command id for current button
	 * @return TInt command's id
	 */
	TInt CommandId() const;	
	
	/**
	 * constructs button based on resource definition
	 * @param aReader created resource reader for reading information from resource file
	 */
	void ConstructFromResourceL(TResourceReader& aReader);
	
	/**
	 * Constructs empty button with id EAknSoftkeyEmpty
	 */
	void ConstructEmptyButtonL();
	
	/**
	 * Used to get the label text for the button
	 * @return TPtrC pointer to the label text
	 */
	TPtrC* LabelText();


private: // member variables
	TInt iCommandType; 
	TInt iCommandId;
	};

/**
 * Holds (enhanced)	CBA commands and handles command ordering
 * due to placement rules
 * @internal
 * @since 4.0 
 */
 
NONSHARABLE_CLASS(CEikCommandTable) : public CBase
	{
public:
 	/**
 	 * construction and destruction
 	 */
	static CEikCommandTable* NewL();
	static CEikCommandTable* NewLC();
	~CEikCommandTable();	
		
	/**
	 * Used to add a command to CommandTable
	 * @param aButton button to be added
	 * @return TInt return KErrNone if addition was successful
	 */
	TInt AddCommandL(CEikEnhancedCbaButton* aButton);
	
	/**
	 * Used to check if command table has a button with a certain id
	 * @param aCommandId id to be checked
	 * @return TBool ETrue if command is placed in the command table
	 */
	TBool IsCommandPlaced(const TInt aCommandId) const;
	
	/**
	 * Used to replace command with a new command
	 * @param aCommandId Id for command that should be replaced 
	 * @param aResourceId Id for new ENHANCED_CBA_BUTTON resource to be placed in the CommandTable
	 */
	void ReplaceCommandL(const TInt aCommandId, const TInt aResourceId);
	
	/**
	 * Used to get CEikEnhancedCbaButton for current control button (1-4)
	 * @param aCommandIndex Index for requested button, use enum TCommandTableCbaPositions
	 * @return CEikCbaButton for current position, NULL if no button placed in that position
	 */
	CEikEnhancedCbaButton* Command(const TInt aCommandIndex);
	
	/**
	 * Reset CommandTable
	 */
	void Reset();
	
private: // member functions
	/**
	 * Constructor
	 */
	CEikCommandTable();
	
	/**
	 * constructs command table with device button priorities
	 */
	void ConstructL();
	
private: // member variables
	TFixedArray<CEikEnhancedCbaButton*, KMaxButtonsInCommandTable> iCommandButtons; // displayed commands
	
	// priority order for each button
	RArray< RArray<TInt> > iPriorities;	
	};

#endif
