// EIKCMBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCMBUT_H__)
#define __EIKCMBUT_H__

#include <eikbutb.h>
#include <coeccntx.h>
#include <gulutil.h>

class CEikLabel;
class CEikImage;
class CEikAlignedControl;
class TResourceReader;
class CEikCommandStack;

/**
 *
 * Base class for command buttons.
 *
 * A command button can be used to invoke a command in an application, or
 * to toggle one of its states. It may display a text label, an image, or
 * both.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikCommandButtonBase : public CEikButtonBase, public MCoeControlContext
	{
public:
	/**
	 * Identifies the command buttons components.
	 */
	enum TWhichComponent
		{
		EFirst,							/** First component. */
		ESecond							/** Second component. */
		};

	/**
	 *
	 * Specifies whether text, image or both are to be displayed.
	 *
	 * This enum shadows the values defined in
	 * <code>CEikCommandButtonBase::TDisplayContent</code> to provide more
	 * intuitive names for a command button.
	 */
	enum TDisplayContent
		{
		EFirstOnly	=0x0100,			/** Display only the first component. */
		ESecondOnly	=0x0200,			/** Display only the second component. */
		EBoth		=0x0300				/** Display both components. */
		};

	/**
	 *
	 * Specifies the positions of text and image on the command button.
	 *
	 * This enum shadows the values defined in
	 * <code>CEikCommandButtonBase::TLayout</code> to provide more intuitive
	 * names for a command button.
	 */
	enum TLayout
		{
		EFirstRightSecondLeft=0x0000,	/** Components are positioned horizontally with the first component to the right of the second. */
		EFirstBottomSecondTop=0x0001,	/** Components are positioned vertically with the first component below the second. */
		EFirstTopSecondBottom=0x0002,	/** Components are positioned vertically with the first component above the second. */
		EFirstLeftSecondRight=0x0003,	/** Components are positioned horizontally with the first component to the left of the second. */
		EDenseFont			 =0x0008
		};

	/**
	 * Enumerates the possible ways of allocating excess horizontal space
	 * between the two component controls of the command button.
	 */
	enum TExcess
		{
		EShare		=0x0000,			/** Excess space is shared equally. */
		EToFirst	=0x0010,			/** Excess space is allocated to the first component only. */
		EToSecond	=0x0020				/** All excess space is allocated to the second component only. */
		};
public: // new functions
	IMPORT_C ~CEikCommandButtonBase();
	IMPORT_C void SetButtonLayout(TLayout aLayout);
	IMPORT_C void SetExcessSpace(TExcess aExcess);
	IMPORT_C void SetDisplayContent(TDisplayContent aContent);
	IMPORT_C void LayoutComponents();
	IMPORT_C void StartConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructLabelFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);
	IMPORT_C void ConstructImageFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);
	IMPORT_C virtual void UpdateComponentAlignment();
	IMPORT_C void SetDefault(TBool aIsDefault);
	IMPORT_C TBool IsDefault() const;
public:	// from CCoeControl
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C TSize MinimumSize();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void ActivateL();
	IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
public: // but not exported
	CEikCommandStack* CommandStack() const;
	TInt ButFlags() const;
protected: // from CEikButtonBase
    IMPORT_C void StateChanged();
protected:
	IMPORT_C CEikCommandButtonBase();
	IMPORT_C void SetTextL(const TDesC& aText,CEikAlignedControl*& aComponent);
	IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,CEikAlignedControl*& aComponent);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask,CEikAlignedControl*& aComponent);
	inline void CheckCreateCommandStackL();
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
protected:
	void SetImageAttributes(CEikImage* aImage);
	inline TInt Behavior() const;
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
    IMPORT_C void SizeChanged();
	IMPORT_C void Reserved_2();
private: // from CEikButtonBase
	IMPORT_C void Reserved_3();
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	IMPORT_C virtual void Reserved_4();
private:
	void SetComponentExtents(const TRect& aRect);
	void SetNewComponentExtentL();
    TBool LayoutIsVertical() const;
protected:
	TMargins8 iMargins;
	CEikAlignedControl* iComponents[2];
    TInt iCmdFlags;
private:
	TInt iDrawOffset;
	CEikCommandStack* iCommandStack;
	TInt iDummy;
	TBool iDefault;
	};

/**
 *
 * Command button.
 *
 * Command buttons may contain text, an image or both. A command button
 * can be used to invoke a command in an application, or to toggle one of
 * the application's states.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikCommandButton : public CEikCommandButtonBase
	{
public:
	/**
	 *
	 * Specifies the positions of text and image on the command button.
	 *
	 * This enum shadows the values defined in
	 * <code>CEikCommandButtonBase::TLayout</code> to provide more intuitive
	 * names for a command button.
	 */
	enum TLayout
		{
		ETextRightPictureLeft=0x000,	/** Text and image are positioned horizontally with the text to the right of the image. */
		ETextBottomPictureTop=0x001,	/** Text and image are positioned vertically with the text below the image. */
		ETextTopPictureBottom=0x002,	/** Text and image are positioned vertically with the text above the image. */
		ETextLeftPictureRight=0x003		/** Text and image are positioned horizontally with the text to the left of the image. */
		};

	/**
	 *
	 * Enumerates the possible ways of sharing excess horizontal space
	 * between the command button's text and image.
	 *
	 * See also: <code>SetExcessSpace(TExcess)</code>.
	 */
	enum TExcess
		{
		EShare		=0x0000,		/** Excess space is shared equally. */
		EToText		=0x0010,		/** Excess space is allocated to the text only. */
		EToPicture	=0x0020			/** All excess space is allocated to the picture. */
		};

	/**
	 *
	 * Specifies whether text, image or both are to be displayed.
	 *
	 * This enum shadows the values defined in
	 * <code>CEikCommandButtonBase::TDisplayContent</code> to provide more
	 * intuitive names for a command button.
	 */
	enum TDisplayContent
		{
		ETextOnly		=0x0100,		/** Display text only. */
		EPictureOnly	=0x0200,		/** Display image only. */
		ETextAndPicture	=0x0300			/** Display text and image. */
		};
public:
	IMPORT_C CEikCommandButton();
	IMPORT_C ~CEikCommandButton();
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);
	IMPORT_C CEikLabel* Label() const;
	IMPORT_C CEikImage* Picture() const;
	IMPORT_C void SetButtonLayout(TLayout aLayout);
	IMPORT_C void SetExcessSpace(TExcess aExcess);
	IMPORT_C void SetDisplayContent(TDisplayContent aContent);
	IMPORT_C void SetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	IMPORT_C void AddCommandToStackL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	IMPORT_C TBool RemoveCommandFromStack(TInt aCommandId);
	IMPORT_C TInt PopCommandFromStack();
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
public: // from CEikCommandButtonBase
	IMPORT_C void UpdateComponentAlignment();
private:
	void UpdateLabelReserveLengthL(const TDesC* aText);
private:
	TInt iDummy;
	};

/**
 *
 * This class provides a command button which can hold two pictures in
 * addition to label text. If a second picture is set for the button it 
 * is shown when the button is pressed.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikTwoPictureCommandButton : public CEikCommandButtonBase
	{
public:
	/**
	 * Determines how the buttons label and pictures are layed out.
	 */
	enum TLayout
		{
		/** The label is placed on the right and the picture on the left of the
		button.	 */
		ETextRightPictureLeft=0x000,

		/** The label is placed at the bottom and the picture on the top of the
		button. */
		ETextBottomPictureTop=0x001,

		/** The label is placed at the top and the picture on the bottom of the
		button.
		 */
		ETextTopPictureBottom=0x002,

		/** The label is placed on the left and the picture on the right of the
		button.	 */
		ETextLeftPictureRight=0x003
		};

	/**
	 * Determines how excess space is allocated between the buttons label and
	 * pictures.
	 */
	enum TExcess
		{
		EShare		=0x0000,		/** Excess space is shared equally between the buttons label and pictures. */
		EToText		=0x0010,		/** Excess space is allocated to the buttons label. */
		EToPicture	=0x0020			/** Excess space is allocated to the buttons pictures. */
		};

	/**
	 * Determines which of the buttons label and pictures are displayed.
	 */
	enum TDisplayContent
		{
		ETextOnly		=0x0100,		/** Only the buttons label is displayed. */
		EPictureOnly	=0x0200,		/** Only the buttons picture is displayed. */
		ETextAndPicture	=0x0300			/** The buttons label and picture are displayed. */
		};
private:
	enum TPictureButtonType
		{
		EPictureButWithBorders		=0x0000,
		EPictureButWithoutBorders	=0x1000
		};
	enum TExternalPicture
		{
		EPictureNotOwnedExternally	=0x00,
		EPictureOwnedExternally		=0x01
		};
public:
	IMPORT_C CEikTwoPictureCommandButton();
	IMPORT_C ~CEikTwoPictureCommandButton();
	IMPORT_C TBool IsSecondPictureOwnedExternally();
	IMPORT_C CEikImage* Picture() const;
	IMPORT_C void ConstructImagesFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetTwoPicturesL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL,const CFbsBitmap* aSecondMain=NULL, const CFbsBitmap* aSecondMask=NULL);
	IMPORT_C void SetSecondPicture(const CFbsBitmap* aSecondMain, const CFbsBitmap* aSecondMask=NULL);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);
	IMPORT_C void SetSecondPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);
	IMPORT_C void SetSecondPictureOwnedExternally(TBool aOwnership);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ActivateL();
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& /*aRect*/) const;
    IMPORT_C void StateChanged();
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	void SwapPictures(CEikImage* aImage);
private:
	const CFbsBitmap* iSecondBitmap;
	const CFbsBitmap* iSecondMaskBitmap;
	TInt iPictureFlags;
	TInt iDummy;
	};

/**
 * The CEikInverterCommandButton class is a command button which swaps the foreground and background
 * colors used to draw the button contents when the button is pressed.
 *
 * @since ER5U
 */
class CEikInverterCommandButton : public CEikCommandButton
	{
public:
	IMPORT_C CEikInverterCommandButton();
	IMPORT_C ~CEikInverterCommandButton();
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	TInt iFlag;
	TInt iDummy;
	};

//
// CEikTextButton
//

/**
 *
 * This class provides member functions to enable you to create a text
 * button with a label.
 *
 * A text button has no image associated with it, it displays a label
 * only.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikTextButton : public CEikCommandButtonBase
	{
public:
	IMPORT_C CEikTextButton();
	IMPORT_C ~CEikTextButton();
	IMPORT_C void SetTextL(const TDesC& aText,TWhichComponent aWhich=EFirst);
	IMPORT_C CEikLabel* Label(TWhichComponent aWhich=EFirst) const;
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
private:
	TInt iDummy;
	};

/**
 *
 * This class provides member functions to enable you to create a command
 * button with a bitmap image.
 *
 * A bitmap button has no text associated with it: it displays a picture
 * only.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikBitmapButton : public CEikCommandButtonBase
	{
public:
	IMPORT_C CEikBitmapButton();
	IMPORT_C ~CEikBitmapButton();
	IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL,TWhichComponent aWhich=EFirst);
	IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1,TWhichComponent aWhich=EFirst);
	IMPORT_C CEikImage* Picture(TWhichComponent aWhich=EFirst) const;
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
private:
	TInt iDummy;
	};

#endif
