/*
* ============================================================================
*  Name     : AknBitmapAnimation.h
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
// AKNBITMAPANIMATION.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNBITMAPANIMATION_H__)
#define __AKNBITMAPANIMATION_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#include <bmpancli.h>
#include <AknControl.h>
#include <AknIconUtils.h>


class RAknBitmapAnim : public RBitmapAnim
	{
public:
	/**
	 * Constructor
	 */
	RAknBitmapAnim(RAnimDll& aAnimDll);

	/**
	 * Starts the animation, and displays the last frame when finished.
	 */
	void StartAndKeepLastFrameL();

	/**
	 * Stops the animation.
	 */
	TInt Stop();
	};

// FORWARD DECLARATIONS
class TResourceReader;
class TAknsItemID;

NONSHARABLE_CLASS(CAknBitmapAnimation) : public CAknControl
	{
public:
	/**
	 * 2 phase construction.
	 */
	IMPORT_C static CAknBitmapAnimation* NewL();

	/**
	 * Destructor.
	 */
	IMPORT_C virtual ~CAknBitmapAnimation();
public:
	/**
	 * gives access to RBitmapAnimation.
	 */
	IMPORT_C RBitmapAnim& Animation();

	/**
	 * gives access to CBitmapAnimClientData.
	 */
	IMPORT_C CBitmapAnimClientData* BitmapAnimData() const;

	/**
	 * Cancels the animation.
	 */
	IMPORT_C TInt CancelAnimation();

	/**
	 * Sets the frame index.
	 */
	IMPORT_C void SetFrameIndexL(TInt aIndex);

	/**
	 * Sets the frame interval in milliSeconds.
	 */
	IMPORT_C void SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds);

	/**
	 * Starts the animation.
	 */
	IMPORT_C void StartAnimationL();

    /**
    * Sets the scale mode for the animation frames that is used when the
    * animation frames are scaled to the size of the control.
    * Default scale mode is EAspectRatioPreserved.
    *
    * @since 3.1
    * @param aMode scale mode
    */
    IMPORT_C void SetScaleModeForAnimationFrames(TScaleMode aMode);
    
    /**
    * Sets the scale mode for the animation background frame that is used when the
    * animation background frame is scaled to the size of the control.
    * Default scale mode is EAspectRatioPreserved.
    *
    * @since 3.1
    * @param aMode scale mode
    */
    IMPORT_C void SetScaleModeForAnimationBackgroundFrame(TScaleMode aMode);
    
    /**
    * Excludes the animation frames from the icon cache.    
    * Note that this method should be called before setting the size of the control
    * to be in effect. If the animation frames are created outside of the scope of this 
    * class method AknIconUtils::ExcludeFromCache should be called for animation frames
    * to get the same effect.
    * 
    * By default scalable animation frames are being put to icon cache after they are
    * no longer used. 
    * This makes it possible to retrieve recently used animation frames fast
    * without the need to render them again.
    * Excluding infrequently used animation frames from icon cache could improve performance
    * and memory usage of the system.
    * 
    * @since 3.1    
    */
    IMPORT_C void ExcludeAnimationFramesFromCache();
    
public: 
	/**
	 * Set if the animation has started
	 */
	TInt AnimationHasStarted(TBool aHasStarted);
	
	


public:

    /**
    * Construct the animation from skin.
    *
    * Usually this method should be called before ConstructFromResourceL,
    * and if EFalse is returned the caller should try to construct the
    * same animation with ConstructFromResourceL. The ownership of the
    * constructed animation and its frames is vested in this class.
    * Furthermore, the animation is not automatically updated during
    * a skin change.
    *
    * @since 2.0
    *
    * @param aItemID Item ID of the animation.
    *
    * @return ETrue if the animation was found and succesfully constructed.
    *   EFalse if the animation (or at least one of its frames) was not
    *   found.
    */
    IMPORT_C TBool ConstructFromSkinL( const TAknsItemID& aItemID );

public: // from CCoeControl
	/**
	 * Construct animation from resource.
	 */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

	/**
	 * Minimum size.
	 */
	IMPORT_C virtual TSize MinimumSize();
private: // from CCoeControl
	virtual void SizeChanged();
	virtual void PositionChanged();
	virtual void Draw(const TRect& aRect) const;

private:
	CAknBitmapAnimation();
	void ConstructL();
	void CompleteAnimationInitialisationL();
	TBool IsInitialisationCompleted();
	CBitmapFrameData* CreateFrameDataFromResourceL(TResourceReader& aFramesReader, const TDesC& aFileName);
	void SetAnimationWindowL();
private: // timer
	static TInt AnimationStartedCallback(TAny* aPtr);

private:
	CBitmapAnimClientData* iBitmapAnimData;
	RAnimDll iAnimDll;
	RAknBitmapAnim iAnimation;
	TInt iFlags;
	CPeriodic* iTimer;
    TScaleMode iScaleModeFrames;
    TScaleMode iScaleModeBackgroundFrame;
	};

#endif
