// APAMDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APAMDR_H__
#define __APAMDR_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__APADBASE_H__)
#include <apadbase.h>
#endif

// classes defined:
class TApaModelDoorFactory;
class CApaModelDoor;
class CApaModelHeader;
class MApaModelHeaderFactory;
//
// classes referenced:
class RReadStream;
class RWriteStream;
class CStreamStore;
class CStreamDictionary;
class CEmbeddedStore;
class TApaAppIdentifier;
//


/**
 *
 * A factory class for instantiating and restoring an application's door
 * using the application's model.
 * @since 5.0
 * @lib "apparc.lib"
 */
class TApaModelDoorFactory : public MPictureFactory
// Recognizes KUidPictureTypeDoor and creates CApaModelDoor pictures
	{
public:
	IMPORT_C TApaModelDoorFactory(const MApaModelHeaderFactory* aFactory);
	//
	// from MPictureFactory
	IMPORT_C void NewPictureL(TPictureHeader& aPictureHeader,const CStreamStore& aPictureStore)const; // used to create CApaDoor's during document restore only 
private:
	const MApaModelHeaderFactory* iHeaderFactory;
	};


/**
 *
 * A persistent representation of a door that also acts as a wrapper
 * around an application's model.
 *
 * The class allows embedded data to be manipulated without requiring the
 * whole associated application.
 *
 * @since 5.0
 * @lib "apparc.lib"
 */
class CApaModelDoor : public CApaDoorBase
// Provides the persistant representation of a CApaDoor while acting as a wrapper around an app's model
	{
public:
	IMPORT_C static CApaModelDoor* NewL(CApaModelHeader* aHeader);
	IMPORT_C static CApaModelDoor* NewLC(CApaModelHeader* aHeader);
	IMPORT_C static CApaModelDoor* NewL(const CStreamStore& aStore,TStreamId aHeadStreamId,const MApaModelHeaderFactory* aFactory);
	//
	
	/**
	 *
	 * Gets the application model wrapper object.
	 *
	 * @returns   "CApaModelHeader*"
	 *            A pointer to the application model wrapper object.
	 */
	inline CApaModelHeader* ModelHeader() { return iModelHeader; }
	
	/**
	 *
	 * Sets the format of the door.
	 *
	 * @param     "TFormat aFormat"
	 *            The format for the graphical representation of the
	 *            embedded document.
	 */
	inline void SetFormat(TFormat aFormat) { iFormat = aFormat; }
	//
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aHeadStreamId,const MApaModelHeaderFactory* aFactory);
	//
	IMPORT_C ~CApaModelDoor();
	//
	// from CPicture
	IMPORT_C void DetachFromStoreL(TDetach /*aDegree*/=EDetachFull);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,MGraphicsDeviceMap* aMap)const; 
	IMPORT_C void GetOriginalSizeInTwips(TSize& aSize)const;
	IMPORT_C void SetScaleFactor(TInt aScaleFactorWidth,TInt aScaleFactorHeight); 
	IMPORT_C TInt ScaleFactorWidth()const; 
	IMPORT_C TInt ScaleFactorHeight()const;
	//
private:
	CApaModelDoor();
	CApaModelDoor(CApaModelHeader* aHeader);
	//
	static CStreamDictionary* ReadStreamDictionaryLC(const CStreamStore& aSourceStore,TStreamId aStreamId);
	static void CopyStoreL(const CEmbeddedStore& aSourceStore,RWriteStream& aTargetStream);
	void InternalizeModelL(const MApaModelHeaderFactory* aFactory);
	//
	// from CApaDoorBase
	TSize GlassDoorSize()const;
private:
	CApaModelHeader* iModelHeader;
	CEmbeddedStore* iStore;
	TSize iScaleFactor;
	CBufSeg* iStoreHost; // the host for the embedded store, if the door has been detached from its originating store
	};


/**
 *
 * An interface class that acts as a wrapper for an application model.
 *
 * This is also known as an application model header.The class provides
 * the knowledge for internalizing and externalizing an application
 * model's data. An instance of the class is used by
 * <code>CApaModelDoor</code>. A concrete implementation of the class
 * must be supplied by the application model (not the application UI). An
 * instance of the class is constructed by a factory object that
 * implements the <code>MApaModelHeaderFactory</code> interface; the
 * factory object is also supplied by the application model (not the
 * application UI).
 *
 * @since 5.0
 * @lib ""
 */
class CApaModelHeader : public CBase
// Abstract wrapper for an applications model - used for file format conversion etc
	{
public:
	/**
	 *
	 * Stores the model and its components in the specified store.
	 *
	 * @param     "CStreamStore& aStore"
	 *            The store in which the model's components are to be
	 *            stored.
	 * @param     "CStreamDictionary& aDict"
	 *            The stream dictionary into which stream IDs and
	 *            associated UIDs are put.
	 */
	virtual void StoreL(CStreamStore& aStore,CStreamDictionary& aDict) const=0;
	/**
	 *
	 * Gets the identity of the application associated with the application
	 * model.
	 *
	 * @returns   "TApaAppIdentifier"
	 *            The application identity.
	 */
	virtual TApaAppIdentifier AppId()const=0;
	/**
	 *
	 * Restores the model to the specified degree.
	 *
	 * An implementation of this function should propagate this call to all
	 * components of the model.
	 *
	 * @param     "CPicture::TDetach aDegree"
	 *            The degree to which restoration is needed.
	 */
	virtual void DetachFromStoreL(CPicture::TDetach aDegree)=0;
private:
	IMPORT_C virtual void Reserved_1();
	};


/**
 *
 * An interface class that applications implement to construct an
 * application model wrapper object, also known as the application model
 * header.
 * @since 5.0
 * @lib ""
 */
class MApaModelHeaderFactory
	{
public:	
	/**
	 *
	 * Creates and returns an application model wrapper object.
	 *
	 * @param     "const CStreamStore& aStore"
	 *            The store containing model data.
	 * @param     "const CStreamDictionary& aDict"
	 *            The stream dictionary.
	 * @param     "const TApaAppIdentifier& aAppId"
	 *            The application's identity held as a stream in the
	 *            application's store
	 * @returns   "CApaModelHeader*"
	 *            A pointer to the new application model wrapper object.
	 */
	virtual CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,const TApaAppIdentifier& aAppId)const=0;
	};


#endif