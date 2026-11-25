// EIKSECED.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKSECED_H__
#define __EIKSECED_H__

#include <eikdef.h>
#include <eikbctrl.h>

class TResourceReader;
class CPeriodic;

class CEikSecretEditor : public CEikBorderedControl
	{
public:
	enum { EMaxSecEdLength=255 };
public:
	IMPORT_C CEikSecretEditor();
	IMPORT_C ~CEikSecretEditor();
public:	// from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C void PrepareForFocusLossL();
public:	// specific
	IMPORT_C void GetText(TDes& aText) const;
	IMPORT_C void Reset();
	IMPORT_C void SetMaxLength(TInt aMaxLength);
public:	// Quartz specific
	IMPORT_C void SetText(const TDesC& aText);
protected:	// from CCoeControl
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // specific
	TInt DrawText() const;
	void DrawTextNow() const;
	void DisplayCursor(TInt aCursorPosX) const;
	static TInt MaskTextCallback(TAny* aSelf);
	void MaskText();
	void StartTimerL();
private:
	typedef TBuf<EMaxSecEdLength> TSecEdBuf;
private:
	TInt iMaxLen;
	TInt iCharWidth;
	TInt iAscent;
	TInt iCharsVisible;
	CPeriodic* iTextMaskingTimer;
	TSecEdBuf iSecCharArr;
	TBool iTextSelected;
	};

#endif	// __EIKSECED_H__
