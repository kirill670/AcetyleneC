// cdsb.h
//
// Copyright (c) 1996-2002 Symbian Ltd. All rights reserved.
//

#ifndef __CDSB_H__
#define __CDSB_H__

#include <e32base.h>
#include <bitdev.h>

class CDirectScreenBitmap : public CBase
/** Direct Screen Bitmap.
 *	API to allow provide synchronisation of the display of images with the
 *	displays refresh to prevent tearing.
 *
 *	This is an abstract base class, so must be derived from on a per-variant basis.
 *	
 *	@since 7.0s
 *	@library scdv.lib
 */
	{
public:
	enum TSettingsFlags
		{
		ENone = 0,
		EDoubleBuffer = 1,
		EIncrementalUpdate = 2
		};

public:
	/**
	 * Constructs a CDirectScreenBitmap derived object.
	 *
	 * @since 7.0s
	 */
	IMPORT_C static CDirectScreenBitmap* NewL();	

	/**
	 * Creates a CDirectScreenBitmap object which can be used for drawing to
	 * a region of the screen indicated by aScreenRect.  This region must have
	 * previously been 'claimed' via the Window Servers Direct Screen Access API.
	 *
	 * @param "const TRect& aScreenRect" The region to be displayed
	 * @param "TSettingsFlags aSettingsFlags" The mode of operation
	 *
	 * @return Standard error code
	 *
	 * @since 7.0s
	 */
	virtual TInt Create(const TRect& aScreenRect, TSettingsFlags aSettingsFlags) =0;

	/**
	 * Returns a TAcceleratedBitmapInfo referring to a bitmap which the
	 * applicationcan render to.
	 *
	 * @param "TAcceleratedBitmapInfo& aBitmapInfo" The Bitmap
	 *
	 * @return Standard error code
	 *
	 * @since 7.0s
	 */
	virtual TInt BeginUpdate(TAcceleratedBitmapInfo& aBitmapInfo) =0;

	/**
	 * Indicates to the Video Driver that the bitmap corresponding to the
	 * previous update has been fully rendered.  The video driver will perform
	 * the actions required to copy this to the frame buffer.
	 *
	 * The request status aComplete will be signalled when the copying has completed.
	 *
	 * @param "TRequestStatus& aComplete" Asynchronous completion status
	 *
	 * @return Standard error code
	 *
	 * @since 7.0s
	 */
	virtual void EndUpdate(TRequestStatus& aComplete) =0;

	/**
	 * Indicates to the Video Driver that the area indicated in aScreenRect has
	 * been fully rendered.  The video driver will perform the actions required 
	 * to copy this to the frame buffer.
	 *
	 * The request status aComplete will be signalled when the copying has completed.
	 *
	 * @param "const TRect& aScreenRect" The Sub-Region to update
	 * @param "TRequestStatus& aComplete" Asynchronous completion status
	 *
	 * @since 7.0s
	 */
	virtual void EndUpdate(const TRect& aScreenRect, TRequestStatus& aComplete) =0;

	/**
	 * Deletes all resources associated with the CDirectScreenBitmap object.
	 *
	 * @param "TRequestStatus& aComplete" Asynchronous Request Status
	 *
	 * @since 7.0s
	 */
	virtual void Close() =0;
	};

#endif
