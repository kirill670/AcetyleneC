/*
* ============================================================================
*  Name        : AknClearer.h
*  Part of     : S60 UI Framework / EikCoCtl
*  Description : Screen Clearer API, support for screen blanking.
*  Version     :
*
*  Copyright © 2002-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef AKNCLEARER_H
#define AKNCLEARER_H

#include <AknControl.h>

#include <eikenv.h>

class CAknScreenClearerBaseExtension;

class CAknScreenClearerBase : public CAknControl
	{
public:
	IMPORT_C void HandleStatusPaneSizeChangeL();
    // from CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
protected:
	IMPORT_C virtual ~CAknScreenClearerBase();
	IMPORT_C void ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane);
private:	// from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
protected:
	void SetShapeL();
	void SetSkinShapeL();
private:
    CAknScreenClearerBaseExtension* iExtension;
	TBitFlags iFlags;
	};


// CLASS DECLARATION

/**
*  This class is for use inside applications for screen blanking.
*
*  @since Series 60 0.9
*/
class CAknLocalScreenClearer : public CAknScreenClearerBase
	{
public:

    /**
    * Two-phased constructor.
    */
	IMPORT_C static CAknLocalScreenClearer* NewLC();

    /**
    * Two-phased constructor.
    * @param aBlankAppStatusPane @c ETrue if application status pane is blank, 
    *                            @c EFalse if not.
    */
	IMPORT_C static CAknLocalScreenClearer* NewLC(TBool aBlankAppStatusPane);

    /**
    * Two-phased constructor.
    * @param aBlankAppStatusPane @c ETrue if application status pane is blank, 
    *                            @c EFalse if not.
    */
	IMPORT_C static CAknLocalScreenClearer* NewL(TBool aBlankAppStatusPane);

    /**
    * From CCoeControl
    */
	IMPORT_C void HandleResourceChange(TInt aType);

	};

// AKNCLEARER_H
#endif
