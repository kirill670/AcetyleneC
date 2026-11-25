// EIKSCBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSCBUT_H__)
#define __EIKSCBUT_H__

#include <eikbutb.h>
#include <lafpublc.h>

/**
 *
 * Scroll button.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikScrollButton : public CEikButtonBase
	{
public:
	/**
	 * Determines a scroll button's type.
	 */
	enum TType
		{
		ENudgeLeft=SLafScrollButton::ENudgeLeft,	/** Scroll button to move the display to the left. */
		ENudgeUp=SLafScrollButton::ENudgeUp,		/** Scroll button to move the display up. */
		ENudgeRight=SLafScrollButton::ENudgeRight,	/** Scroll button to move the display to the right. */
		ENudgeDown=SLafScrollButton::ENudgeDown,	/** Scroll button to move the display down. */
		EPageLeft=SLafScrollButton::EPageLeft,		/** Scroll button to move the display one page to the left. */
		EPageUp=SLafScrollButton::EPageUp,			/** Scroll button to move the display one page up. */
		EPageRight=SLafScrollButton::EPageRight,	/** Scroll button to move the display one page to the right. */
		EPageDown=SLafScrollButton::EPageDown,		/** Scroll button to move the display one page down. */
		EHome=SLafScrollButton::EHome,				/** Scroll button to move the display to the home position. */
		ETop=SLafScrollButton::ETop,				/** Scroll button to move the display to the top. */
		EEnd=SLafScrollButton::EEnd,				/** Scroll button to move the display to the end position. */
		EBottom=SLafScrollButton::EBottom			/** Scroll button to move the display to the bottom. */
		};

public:
	enum TTypeOfScrollBar
		{
		ENormal		=0x00,
		EArrowHead	=0x01
		};

public: // class specific functions
	IMPORT_C ~CEikScrollButton();
	IMPORT_C CEikScrollButton(TType aType);
	IMPORT_C TType Type() const;
public: // from CCoeControl
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // virtual overridden functions
	virtual void Draw(const TRect& aRect) const;
	virtual void StateChanged();
private:
	friend class CEikScrollBar;
	TType iType;
	TInt iFlag;
	};


//
// CEikArrowHeadScrollButton
//

/**
 *
 * Provides functions to create an arrow head scroll button, and to
 * handle pointer events.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikArrowHeadScrollButton : public CEikScrollButton
	{

public:
	IMPORT_C static CEikArrowHeadScrollButton* NewL(const CCoeControl* aParent, TType aType);
public: // framework
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	void HandleResourceChange(TInt aType);
private:
	CEikArrowHeadScrollButton(TType aType);
	void BaseConstructL(const CCoeControl* aParent);
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // virtual overridden functions
	virtual void Draw(const TRect& aRect) const;
private:
	TInt iFlag;
	TInt iDummy;
	TRgb iBrush;
	};



#endif
