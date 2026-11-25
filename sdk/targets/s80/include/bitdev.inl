// BITDEV.INL
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//


TInt CFbsDevice::CreateContext(CGraphicsContext*& aGc)
/** Creates a font and bitmap server graphics context for the device and activates 
it.

It is the responsibility of the caller to delete the graphics context when 
it is no longer needed.

@param aGc On return, contains a pointer to the graphics context. 
@return KErrNone if successful, otherwise, another one of the system-wide error 
codes. */
	{return(CreateContext((CFbsBitGc*&)aGc));} // relies on CFbsDevice deriving _only_ from CBitmapDevice


TInt CFbsDevice::GetNearestFontInTwips(CFbsFont*& aFont,const TFontSpec& aFontSpec)
/** Creates a client-side FBSERV font from those available in the device's typeface store 
that most closely matches a font specification. 

When the font is no longer needed, call ReleaseFont().

@param aFont On return, points to the font which most closely matches the 
specified font.
@param aFontSpec An absolute font specification. Its iHeight member is interpreted 
as being in twips.
@return KErrNone if successful; otherwise, another one of the system-wide error 
codes. */
	{return(GetNearestFontInTwips((CFont*&)aFont,aFontSpec));} // relies on CFbsFont deriving _only_ from CFont


TInt CFbsDevice::GetNearestFontInPixels(CFbsFont*& aFont,const TFontSpec& aFontSpec)
/** Creates a client-side FBSERV font from those available in the device's typeface store 
that most closely matches a font specification.

When the font is no longer needed, call ReleaseFont().

@param aFont On return, points to the font which most closely matches the 
specified font.
@param aFontSpec An absolute font specification. Its iHeight member is interpreted 
as being in pixels.
@return KErrNone if successful; otherwise, another of the system-wide error 
codes. */
	{return(GetNearestFontInPixels((CFont*&)aFont,aFontSpec));} // relies on CFbsFont deriving _only_ from CFont


TInt CFbsDevice::GetFontById(CFbsFont*& aFont,TUid aFileId,const TAlgStyle& aStyle)
/** Gets a specific font, identified by its UID, from the device's typeface store.

When the font is no longer needed, call ReleaseFont().

@param aFont On return, set to point to the font.
@param aFileId The UID identifying the font.
@param aStyle Algorithmic style for the font.
@return KErrNone if successful; otherwise, another of the system-wide error 
codes. */
	{return(GetFontById((CFont*&)aFont,aFileId,aStyle));} // relies on CFbsFont deriving _only_ from CFont


CGraphicsAccelerator* CFbsDevice::GraphicsAccelerator() const
/** Gets a pointer to the 2D graphics accelerator owned by the device. If one is 
available, it is used to accelerate various CFbsBitGc graphics operations.

@return Pointer to the graphics accelerator or NULL if not supported.
@see CFbsBitmapDevice::NewL() */
	{return(iGraphicsAccelerator);}


CFbsBitGc::TGraphicsOrientation CFbsDevice::Orientation() const
/** Gets the device's orientation. The orientation can be set using CFbsBitGc::SetOrientation().

@return The device's orientation. */
	{return(iOrientation);}

