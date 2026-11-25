// QikIpEditor.h
//
// Copyright (C) Symbian Ltd 2001. All rights reserved.
//

#ifndef __QIKIPEDITOR_H__
#define __QIKIPEDITOR_H__

#include <EIKBCTRL.H>	// CEikBorderedControl

class CSegmentEditor;
class CIpEditorFepSupport;

const TInt KMaxUiIpAddressNumbers = 8;	// Max numbers visible in ui for an IP address

/**
 * The type of an ip address
 */
enum TIpType { EIpv4Address, EIpv6Address, EIpv4CompatibleAddress, EIpv4MappedAddress, EIpUnknownAddress };

/**
 * @short This class provides a control to edit IP addresses
 *		It handles IPv4 and IPv6 addresses
 *		The IP mode is determined by the address passed to the editor or by setting it explicitly
 *		Input format:
 *			IPv4 addresses: n.n.n.n	where n is decimal 0-255
 *			IPv6 addresses: n:n:n:n:n:n:n:n where n is hexadecimal 0-ffff
 *			IPv4 compatible adresses: 0:0:0:0:0:0:n.n.n.n where n is decimal 0-255
 *			IPv4 mapped addresses: 0:0:0:0:0:ffff:n.n.n.n where n is decimal 0-255
 *			All types of short versions for ipv6 addresses are also supported
 *			See RFC2373 for more information on address formats
 *		Output format:
 *			The output is always given in normal form, i.e. not short form for IPv6 addresses
 *		Associated resource: QIK_IP_EDITOR
 */
class CQikIpEditor : public CEikBorderedControl
	{
public:	// Public API
	IMPORT_C CQikIpEditor();
	virtual ~CQikIpEditor();
	IMPORT_C void ConstructL();
	IMPORT_C void SetMode(TIpType aIPMode);
	IMPORT_C TIpType Mode() const;
	IMPORT_C TInt SetIpAddress(const TDesC& aIpAddress);
	IMPORT_C void IpAddress(TDes& aIpAddress) const;
	void SetSelectedSegmentAndDrawNow(const TInt aIndex);
	TUint NumberInSegment(const TInt aSegmentIndex) const;

private:	// From CCoeControl
	void ConstructFromResourceL(TResourceReader& aReader);
	void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	void HandleResourceChange(TInt aType);
	TSize MinimumSize();
	void Draw(const TRect& aRect) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TCoeInputCapabilities InputCapabilities() const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void FocusChanged(TDrawNow aDrawNow);
	void PrepareForFocusLossL();
	void SizeChanged();
	void WriteInternalStateL(RWriteStream& aWriteStream) const;
	IMPORT_C void Reserved_2();

private:	// Internal methods
	void PrepareGc(CWindowGc& aGc) const;
	void DrawDigits(CWindowGc& aGc) const;
	void DrawSeparators(CWindowGc& aGc) const;
	void DrawHighlight(CWindowGc& aGc) const;
	void DrawHighlightNow() const;

private:
	/**
	 * Storage for ip addresses
	 */
	TFixedArray<TFixedArray<TUint, KMaxUiIpAddressNumbers>, EIpUnknownAddress> iIpAddress;

	/**
	 * The current mode of the ip editor
	 */
	TIpType iIpMode;

	/**
	 * One rect for each part of the address
	 * Ex: An IPv4 address has 4 number rects in which this may be written:
	 * "000" "000" "000" "000"
	 */
	CArrayFixFlat<TRect>* iNumberRects;

	/**
	 * One rect for each part of the address
	 * Ex: An IPv4 address has 3 separator rects in which this may be written:
	 * "." "."  "."
	 */
	CArrayFixFlat<TRect>* iSeparatorRects;

	/**
	 * Segment currently being edited, -1 if none
	 */
	TInt8 iEditedSegmentIndex;

	/**
	 * Max rows of numbers in editor, 4 for ipv4 & 8 for ipv6
	 */
	TInt8 iMaxRows;

	/**
	 * Y pos for the middle separator in IPv6 editor
	 */
	TInt iPixIPv6MiddleSeparatorYPos;

	/**
	 * Used each time a single number within the IpEditor is edited
	 */
	CSegmentEditor* iEditor;

	/**
	 * The  MCoeFepAwareTextEditor support class
	 */
	CIpEditorFepSupport* iFepSupport;
};

#endif	// __QIKIPEDITOR_H__