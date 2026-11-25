/// ImDefs.h
//
// Copyright (c) 1997-2003 UIQ Technology.  All rights reserved.
//
#ifndef __IMDEFS_H
#define __IMDEFS_H

#include <cntdef.h>
#include <e32std.h>
#include <fbs.h>

/** Enumeration that lists the dnl's that are available */
enum TImApplicationAction {
	EImActionReadNew = 100,
	EImActionComposeNew
};

/** User id length */
const TInt	KUserIdLength = 128;

/** Text length */
const TInt	KTextLength = 256;

/** Class used when dnl'ing to an IM application. The IM application should use this when interpreting parameters */
class TImDnlApplication
	{
public:
	/** The id of the action from TImApplicationAction */
	TInt		iActionId;

	/** The IM user identity the action should be performed on */
	TBuf<KUserIdLength>	iImUserId;
	};

/** Class used when dnl'ing to an IM application. The IM application should use this when interpreting parameters */
typedef TPckgBuf<TImDnlApplication> TImDnlApplicationBuf;

/** Class used to define an IM icon */
class CImIcon : public CBase
	{
	public:
	/**
	 * c'tor
	 */
	IMPORT_C CImIcon();

	/**
	 * c'tor with parameters
	 * @param	aLargeBitmap		A large bitmap
	 * @param	aLargeBItmapMask	The large bitmaps mask
	 * @param	aSmallBitmap		A small bitmap
	 * @param	aSmalBitmapMask		The small bitmaps mask
	 */
	IMPORT_C CImIcon(CFbsBitmap* aLargeBitmap, CFbsBitmap* aLargeBitmapMask, CFbsBitmap* aSmallBitmap, CFbsBitmap* aSmallBitmapMask);

	/**
	 * d'tor
	 */
	IMPORT_C ~CImIcon();

	/**
	 * LargeBitmap returns the large bitmap
	 * @return	CFbsBitmap	A pointer to the bitmap
	 */
	CFbsBitmap* LargeBitmap() {return iLargeBitmap;};

	/**
	 * SetLargeBitmap sets the large bitmap
	 * @param	aBitmap		Pointer to the bitmap
	 */
	void SetLargeBitmap(CFbsBitmap* aBitmap) {iLargeBitmap = aBitmap;};

	/**
	 * LargeBitmapMask returns the large bitmap mask
	 * @return	CFbsBitmap	A pointer to the bitmap mask
	 */
	CFbsBitmap* LargeBitmapMask() {return iLargeBitmapMask;};

	/**
	 * SetLargeBitmapMask sets the large bitmap mask
	 * @param	aBitmap		Pointer to the bitmap mask
	 */
	void SetLargeBitmapMask(CFbsBitmap* aBitmap) {iLargeBitmapMask = aBitmap;};

	/**
	 * SmallBitmap returns the small bitmap
	 * @return	CFbsBitmap	A pointer to the bitmap
	 */
	CFbsBitmap* SmallBitmap() {return iSmallBitmap;};

	/**
	 * SetSmallBitmap sets the small bitmap
	 * @param	aBitmap		Pointer to the bitmap
	 */
	void SetSmallBitmap(CFbsBitmap* aBitmap) {iSmallBitmap = aBitmap;};

	/**
	 * SmallBitmapMask returns the small bitmap mask
	 * @return	CFbsBitmap	A pointer to the bitmap mask
	 */
	CFbsBitmap* SmallBitmapMask() {return iSmallBitmapMask;};

	/**
	 * SetSmallBitmap sets the small bitmap
	 * @param	aBitmap		Pointer to the bitmap mask
	 */
	void SetSmallBitmapMask(CFbsBitmap* aBitmap) {iSmallBitmapMask = aBitmap;};

	private:
	/** A large bitmap used as an icon to indicate the new status/message */
	CFbsBitmap* 	iLargeBitmap;

	/** A mask to the large bitmap */
	CFbsBitmap* 	iLargeBitmapMask;

	/** A small bitmap used as an icon to indicate the new status/message */
	CFbsBitmap* 	iSmallBitmap;

	/** A mask to the small bitmap */
	CFbsBitmap* 	iSmallBitmapMask;
	};

/** Class that define each status the user has to choose from when changing his/her own status from owner-card/detail view. */
class CImStatusItem : public CBase
	{
	public:
	/**
	 * c'tor
	 */
	IMPORT_C CImStatusItem();

	/**
	 * c'tor with parameters
	 * @param	aStatusId		The id of the status item
	 * @param	aDescription	Text describing the status choice
	 * @param	aIcon			An icon indicating the status
	 */
	IMPORT_C CImStatusItem(TInt aStatusId, const TDesC& aDescription, CImIcon* aIcon);

	/**
	 * d'tor
	 */
	IMPORT_C ~CImStatusItem();

	/**
	 * SetStatusId sets the status's id
	 * @param	aId		The id
	 */
	void SetStatusId(const TInt& aId) {iStatusId = aId;};

	/**
	 * StatusId returns the status's id
	 * @return	TInt	The id
	 */
	TInt StatusId() {return iStatusId;};

	/**
	 * SetDescription sets the status's description
	 * @param	aDescription	The description
	 */
	void SetDescription(const TDesC& aDescription) {iDescription.Append(aDescription);};

	/**
	 * Description returns the description
	 * @return	TDesC&	The description
	 */
	TDesC& Description() {return iDescription;};

	/**
	 * SetIcon sets the status's icon
	 * @param	aIcon	The icon
	 */
	void SetIcon(CImIcon* aIcon) {iIcon = aIcon;};

	/**
	 * Icon returns the status's icon
	 * @return	CImIcon		The pointer to the icon
	 */
	CImIcon* Icon() {return iIcon;};

private:
	/** The id of this particular status choice */
	TInt			iStatusId;

	/** The description of this status shown in the detail view of Contacts */
	TBuf<KTextLength>		iDescription;

	CImIcon*		iIcon;
	};

/** An array of status items */
typedef CArrayPtrFlat<CImStatusItem> CImStatusArray;


/** Class that defines what information the user of the IM framwork can see about each plugin at a glance */
class TImServiceItem
	{
public:
	/** The ID of the service */
	TUint32			iServiceId;

	/** Its name */
	TBuf<KTextLength>		iName;

	};

/** An array of plugins */
typedef CArrayFixFlat<TImServiceItem> CImServiceArray;


/** Data passed along with both status change indications and message indications */
class TIndicationData
	{
public:
	/** Which service (IM application) the notification is sent from */
	TUint32			iServiceId;

	/** Which IM user this notification is associated with */
	TBuf<KUserIdLength>		iImUserId;

	/** Which contact id this IM user has */
	TContactItemId	iCntId;

	/** The id of this particular status */
	TInt			iStatusId;

	/** A uid that can be used to create a dnl to read the new message (this is only used in message notifications) */
	TUid			iViewUid;

	/** A description of the new status (this is only used in status change notifications) */
	TBuf<KTextLength>		iDescription;

	/** An additional description of the new status (this is only used in status change notifications) */
	TBuf<KTextLength>		iAdditionalDescription;
	};


#endif // __IMDEFS_H