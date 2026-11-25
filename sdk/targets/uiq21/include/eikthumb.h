// EIKTHUMB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKTHUMB_H__)
#define __EIKTHUMB_H__

#include <eikbctrl.h>
#include <lafpublc.h>

/**
 *
 * A scroll thumb.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikScrollThumb : public CEikBorderedControl
	{
public:
	/**
	 * Specifes a scroll thumb's orientation.
	 */
	enum TOrientation 
		{
		EVertical	=SLafScrollThumb::EVertical,	/** Sets orientation to vertical. */
		EHorizontal	=SLafScrollThumb::EHorizontal	/** Sets orientation to horizontal. */
		};
public:
	CEikScrollThumb(TOrientation aOrientation);
	void SetDragState(TBool aState);
	TBool DragState();
	void DrawDragStateNow() const;
public:	// from CCoeControl
	void Draw(const TRect& aRect) const;
	void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: //from CCoeControl
	void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void DrawDragState(CWindowGc& aGc) const;
private:
	TBool iDragState;
	TOrientation iOrientation;
	};


#endif
