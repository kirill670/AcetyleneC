// EIKBTGRP.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBTGRP_H__)
#define __EIKBTGRP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class CCoeControl;
class CEikCommandButton;
class CFbsBitmap;

/**
 * @internal
 */
class MEikButtonGroup
	{
public:
	void Release();
	virtual void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;
	virtual void SetCommandL(TInt aPosition,TInt aResourceId)=0;
	virtual void SetCommandSetL(TInt aResourceId)=0;
	virtual void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;
	virtual void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;
	virtual void AddCommandToStackL(TInt aPosition,TInt aResourceId)=0;
	virtual void AddCommandSetToStackL(TInt aResourceId)=0;
	virtual void SetDefaultCommand(TInt aCommandId)=0;
	virtual TSize CalcMinimumSizeL(TInt aResourceId)=0;
	virtual void RemoveCommandFromStack(TInt aPosition,TInt aCommandId)=0;
	virtual TInt CommandPos(TInt aCommandId) const=0;
	virtual void DimCommand(TInt aCommandId,TBool aDimmed)=0;
	virtual TBool IsCommandDimmed(TInt aCommandId) const=0;
	virtual void MakeCommandVisible(TInt aCommandId,TBool aVisible)=0;
	virtual TBool IsCommandVisible(TInt aCommandId) const=0;
	IMPORT_C virtual void AnimateCommand(TInt aCommandId);
	virtual CCoeControl* AsControl()=0;
	virtual const CCoeControl* AsControl() const=0;
	// The following methods are only needed for external button groups.
	virtual void SetBoundingRect(const TRect& aBoundingRect)=0;
	virtual void ReduceRect(TRect& aBoundingRect) const=0;
	//
	virtual CCoeControl* GroupControlById(TInt aCommandId) const=0;
	virtual CEikCommandButton* GroupControlAsButton(TInt aCommandId) const=0;
	virtual TInt CommandId(TInt aCommandPos) const=0;
	virtual TInt ButtonCount() const=0;
	virtual TUint ButtonGroupFlags() const=0;
private:
	IMPORT_C void Reserved_1();
	};
	

/**
 * extends needed functions for enhanced cba
 * @internal 
 * @since 4.0
 */
class MEikEnhancedButtonGroup : public MEikButtonGroup
	{
public:
	/**
	 * Used to offer list of commands for softkeys
	 * @param aCommandList a list of command ids to be offered for softkeys
	 * @since 4.0
 	 */
	IMPORT_C virtual void OfferCommandListL(const RArray<TInt>& aCommandList)=0;

	/**
	 * Used to offer list of commands for softkeys
	 * @param aResourceId id for CBA resource that defines enhanced cba buttons
	 * @since 4.0
 	 */
	IMPORT_C virtual void OfferCommandListL(const TInt aResourceId)=0;
	
	/**
	 * Used to check if a certain command have been approved to the current command set
	 * @param aCommandId the id for command which existence should be checked
	 * @return TBool returns ETrue is command is in control group, otherwise EFalse
	 * @since 4.0
 	 */	
	IMPORT_C virtual TBool IsCommandInGroup(const TInt aCommandId) const=0;
	
	/**
	 * Replace existing command with a new command
	 * @param aCommandId Id for command that should be replaced
	 * @param aResourceId resource id for new enhanced cba button
	 * @since 4.0
 	 */	
	IMPORT_C virtual void ReplaceCommand(const TInt aCommandId, const TInt aResourceId)=0;	
	};

#endif
