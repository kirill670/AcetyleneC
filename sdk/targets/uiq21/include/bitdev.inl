// BITDEV.INL
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

/**
 *
 * Creates a <code>CGraphicsContext</code> graphics context for the device.
 *
 * It is the responsibility of the caller to delete the graphics context
 * when it is no longer needed.
 *
 * @param     " CGraphicsContext*& aGc "
 *            On return, contains a pointer to the created
 *            graphics context (actually a <code>CFbsBitGc</code>).
 * @returns   " TInt "
 *            <code>KErrNone</code>, if successful, otherwise,
 *            another one of the system-wide error codes.
 */
TInt CFbsDevice::CreateContext(CGraphicsContext*& aGc)
	{return(CreateContext((CFbsBitGc*&)aGc));} // relies on CFbsDevice deriving _only_ from CBitmapDevice

/**
 *
 * Gets the nearest FBSERV font to that in the specified font
 * specification.
 *
 * The FBSERV returns a pointer to the nearest matching FBSERV font from
 * those available.
 *
 * @param     " CFbsFont*& aFont "
 *            On return, the pointer is set to point to the device
 *            font which most closely approximates the font
 *            specification.
 * @param     " const TFontSpec& aFontSpec "
 *            An absolute font specification.
 * @returns   " TInt "
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another one of the system-wide error codes.
 */
TInt CFbsDevice::GetNearestFontInTwips(CFbsFont*& aFont,const TFontSpec& aFontSpec)
	{return(GetNearestFontInTwips((CFont*&)aFont,aFontSpec));} // relies on CFbsFont deriving _only_ from CFont

/**
 *
 * Gets the nearest FBSERV font to that in the specified font
 * specification.
 *
 * The FBSERV returns a pointer to the nearest matching FBSERV font from
 * those available.
 *
 * @param     " CFbsFont*& aFont "
 *            On return, the pointer is set to point to the device
 *            font which most closely approximates the font
 *            specification.
 * @param     " const TFontSpec& aFontSpec "
 *            An absolute font specification.
 * @returns   " TInt "
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
TInt CFbsDevice::GetNearestFontInPixels(CFbsFont*& aFont,const TFontSpec& aFontSpec)
	{return(GetNearestFontInPixels((CFont*&)aFont,aFontSpec));} // relies on CFbsFont deriving _only_ from CFont

/**
 *
 * Gets the font identified by UID in the fontstore.
 *
 * @param     " CFbsFont*& aFont "
 *            On return, the pointer is set to point to the device
 *            font.
 * @param     " TUid aFileId "
 *            The UID identifying the font.
 * @param     " const TAlgStyle& aStyle "
 *            Algorithmic style for the font.
 * @returns   " TInt "
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
TInt CFbsDevice::GetFontById(CFbsFont*& aFont,TUid aFileId,const TAlgStyle& aStyle)
	{return(GetFontById((CFont*&)aFont,aFileId,aStyle));} // relies on CFbsFont deriving _only_ from CFont

/**
 *
 * Gets a pointer to the current graphics accelerator.
 *
 * @since     6.2
 * @returns   "CGraphicsAccelerator*"
 *            A pointer to the current graphics accelerator,
 *            if present, <code>NULL</code> otherwise.
 */
CGraphicsAccelerator* CFbsDevice::GraphicsAccelerator() const
	{return(iGraphicsAccelerator);}

/**
 *
 * Gets the current orientation.
 *
 * @since     6.2
 * @returns   "CFbsBitGc::TGraphicsOrientation"
 *            The current orientation setting of the device.
 */
CFbsBitGc::TGraphicsOrientation CFbsDevice::Orientation() const
	{return(iOrientation);}

