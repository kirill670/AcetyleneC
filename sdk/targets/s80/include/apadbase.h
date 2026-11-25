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


class CApaDoorBase : public CPicture
// Base class for a wrapper for embedded CApaDocuments
/** The base class for the graphic representation of an embedded document.

An embedded document can be represented either as an icon or as a glass picture. 
Such a graphic representation is known as a door.

The class is intended for derivation.

@publishedAll 
@released
@see CApaDoor
@see CApaModelDoor */
	{
public:
	
	/** Defines the possible formats for the graphical representation of the embedded 
	document. */
	enum TFormat {
		/** The representation is an icon. */
		EIconic,
		/** The representation is a glass door. */
		EGlassDoor,
		/** The representation is a glass door but has been temporarily switched to an icon. */
		ETemporarilyIconic
		};
public:
	inline TFormat Format()const;
	inline TUid Source()const;
	inline void SetSource(TUid aSource);
protected:
	IMPORT_C void ExternalizeBaseStreamL(CStreamStore& aStore,CStreamDictionary& aStreamDict)const;
	IMPORT_C TSize InternalizeBaseStreamL(const CStreamStore& aStore,const CStreamDictionary& aStreamDict); // returns current size in twips
	/** Returns the size of the glass door, in twips.
	
	A concrete implementation of this function is provided by derived classes.
	
	@return The size of the glass door, in twips. 
	
	@publishedAll 
	@released */
	virtual TSize GlassDoorSize()const=0;
protected:
	TFormat iFormat;
	TUid iSource; // foreign representation of a translated door (eg MS Word doc)
	};

//
// inlines
//

inline CApaDoorBase::TFormat CApaDoorBase::Format()const
	/** Gets the current format of the representation of the embedded document.
	
	@return The format for the representation of the embedded document. */
	{ return iFormat; }

inline TUid CApaDoorBase::Source()const
	/** Gets the UID that identifies this door when the source originates on a non-Symbian 
	OS device.
	
	This is used by converters.
	
	@return The UID for the non-Symbian OS source. For a source that originates 
	on a Symbian OS phone, this is KNullUid. */
	{ return iSource; }

inline void CApaDoorBase::SetSource(TUid aSource)
	/** Sets the UID that identifies this door when the source originates on a non-Symbian 
	OS device.
	
	This is used by converters.
	
	@param aSource The UID for the non-Symbian OS source. For a source that originates 
	on a Symbian OS phone, this is KNullUid. */
	{ iSource=aSource; }

#endif
