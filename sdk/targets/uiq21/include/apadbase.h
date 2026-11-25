// APADBASE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APADBASE_H__
#define __APADBASE_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__S32STD_H__)
#include <s32std.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif


/**
 *
 * The base class for the graphic representation of an embedded document.
 *
 * An embedded document can be represented either as an icon or as a
 * glass picture. Such a graphic representation is known as a door.The
 * class is intended for derivation.
 *
 * @since 5.0
 * @lib "apparc.lib"
 */
class CApaDoorBase : public CPicture
// Baseclass for a wrapper for embedded CApaDocuments
// Doors in general can display either as an icon or as a glass picture
	{
public:
	
	/**
	 *
	 * Defines the possible formats for the graphical representation of the
	 * embedded document.
	 * @since 
	 */
	enum TFormat {
		/** The representation is an icon.
		 */
		EIconic,
		/** The representation is a glass door.
		 */
		EGlassDoor,
		/** The representation is a glass door but has been temporarily switched
		to an icon.
		 */
		ETemporarilyIconic
		};
public:
	inline TFormat Format()const;
	inline TUid Source()const;
	inline void SetSource(TUid aSource);
protected:
	IMPORT_C void ExternalizeBaseStreamL(CStreamStore& aStore,CStreamDictionary& aStreamDict)const;
	IMPORT_C TSize InternalizeBaseStreamL(const CStreamStore& aStore,const CStreamDictionary& aStreamDict); // returns current size in twips
	/**
	 *
	 * Returns the size of the glass door, in twips.
	 *
	 * A concrete implementation of this function is provided by derived
	 * classes.
	 *
	 * @returns   "TSize"
	 *            The size of the glass door, in twips.
	 */
	virtual TSize GlassDoorSize()const=0;
protected:
	TFormat iFormat;
	TUid iSource; // foreign representation of a translated door (eg MS Word doc)
	};

//
// inlines
//

/**
 *
 * Gets the current format of the representation of the embedded
 * document.
 *
 * @returns   "TFormat"
 *            The format for the representation of the embedded
 *            document.
 */
inline CApaDoorBase::TFormat CApaDoorBase::Format()const
	{ return iFormat; }

/**
 *
 * Gets the UID that identifies this door when the source originates on a
 * non-Symbian platform.
 *
 * This is used by converters.
 *
 * @returns   "TUid"
 *            The UID for the non-Symbian source. For source that
 *            originates on a Symbian platform, this is
 *            <code>KNullUid</code>.
 */
inline TUid CApaDoorBase::Source()const
	{ return iSource; }

/**
 *
 * Sets the UID that identifies this door when the source originates on a
 * non-Symbian platform.
 *
 * This is used by converters.
 *
 * @param     "TUid aSource"
 *            The UID for the non-Symbian source. For source that
 *            originates on a Symbian platform, this is
 *            <code>KNullUid</code>.
 */
inline void CApaDoorBase::SetSource(TUid aSource)
	{ iSource=aSource; }

#endif
