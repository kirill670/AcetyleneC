// EIKMOVER.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKMOVER_H__
#define __EIKMOVER_H__

#include <coecntrl.h>
#include <coecobs.h>
#include <coeccntx.h>
#include <eikmenub.h>

//
// Forward declarations
//

class TResourceReader;
class CEikImage;
class CEikTwoPictureCommandButton;

/**
 * The CEikMover class implements a draggable bar that can be used as
 * the title bar of a dialog window.
 */
class CEikMover : public CCoeControl, public MCoeControlObserver, public MCoeControlContext
	{
public: // class specific
	IMPORT_C ~CEikMover();
	IMPORT_C CEikMover();
	IMPORT_C void SetText(HBufC* aText);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetActive(TBool aActive);
	IMPORT_C TBool Active() const;
	IMPORT_C void SetFont(const CFont* aFont);
	IMPORT_C void SetTitleLeftMargin(TInt aLeftMargin);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize(); 
	IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
	//
	IMPORT_C void Reserved_2();
protected:
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
public:
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;	// Set the background color of the CEikImage
	IMPORT_C void SetExpectNoPointerEvents(TBool aExpectNoPointerEvent);
	void ShowInfoButtonL(TBool aShowButton);
	void SetMenuPaneAvailable(TBool aAvailable);
	void DrawTitle(TDesC& aText, TInt aOffset, CWindowGc& aGc, TRect aTitleRect) const;
	void SetMenuPaneObserver(MEikMenuObserver* aObserver);
private:
	void DoHandleResourceChangeL(TInt aType);
	void ShowMenuL(TPoint aPoint);
	void SetupMenuL();
	void DestroyMenuPane();
private:
	HBufC* iText;
	const CFont* iFont;
	TPoint iPointerDownPos;
	TInt iMoverFlags;
	TInt iMenuTitleLeftMargin;
	CCoeControl* iParentControl;
	
	CEikTwoPictureCommandButton* iInfoButton;
	CEikImage* iLeftImage;
	TPoint iOriginalPosition;

	CEikMenuBarTitle* iMenuTitle;
	CEikMenuPane* iMenuPane;
	MEikMenuObserver* iMenuPaneObserver;
	TInt iMoverSpare;
	};

#endif	// __EIKMOVER_H__
