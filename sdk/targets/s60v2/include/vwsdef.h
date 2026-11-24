// VWSDEF.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __VWSDEF_H__
#define __VWSDEF_H__

#include <e32std.h>


class TVwsViewId
/** Identifies an application view using two unique identifiers (UIDs): a view 
UID and an application UID. 

The application UID is required so that the application associated with the view 
can be started if it is not already running.

@publishedAll 
@released */
	{
public:
	inline TVwsViewId();
	inline TVwsViewId(const TVwsViewId& aUid);
	inline TVwsViewId(TUid aAppUid,TUid aViewUid);
	inline TBool operator==(const TVwsViewId& aUid) const;
	inline TBool operator!=(const TVwsViewId& aUid) const;
public:
	/** A unique application ID (or application UID).
	
	Uniquely identifies the application associated with the view. */
	TUid iAppUid;
	/** A unique view ID (or view UID).
	
	Uniquely identifies the view. */
	TUid iViewUid;
	};

/** @internalTechnology */
#define KNullViewId TVwsViewId(KNullUid,KNullUid)

/** @internalTechnology */
const TInt KErrViewWrongMode=1; // !!! Wrong error code - should be -ve & unique


//
// The TVwsViewIdAndMessage class identifies a view and encapsulates a message to be read by the view when it is
// activated.
// 
class TVwsViewIdAndMessage
/**
@publishedAll 
@released 
*/
	{
public:
	inline TVwsViewIdAndMessage();
	inline TVwsViewIdAndMessage(const TVwsViewId& aId);
	inline TVwsViewIdAndMessage(const TVwsViewId& aId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
public:
	TVwsViewId iViewId;
	TUid iCustomMessageId;
	TInt iCustomMessageLength;
	TPtrC8 iCustomMessage;
	};



class TVwsViewEvent
//
// The TVwsViewEvent class encapsulates the attributes of a view server event. These are the event type, the ids of
// the two views associated with the event and the attributes of any message which can go with the event.
//
/**
@publishedPartner
@released 
*/
	{
public:
	enum TVwsViewEventType
		{
		EVwsActivateView,
		EVwsDeactivateView,
		EVwsScreenDeviceChanged,
		EVwsDeactivationNotification,
		EVwsActivationNotification
		};
public:
	inline TVwsViewEvent();
	inline TVwsViewEvent(TVwsViewEventType aEventType);
	inline TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId);
	inline TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId);
	inline TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId,TUid aCustomMessageId,TInt aCustomMessageLength);
public:
	TVwsViewEventType iEventType;
	TVwsViewId iViewOneId;
	TVwsViewId iViewTwoId;
	TUid iCustomMessageId;
	TInt iCustomMessageLength;
	};


//
// Typedefs.
//
/** @internalComponent */
typedef TPckgBuf<TVwsViewIdAndMessage> TVwsViewIdAndMessageBuf;

/** @internalComponent */
typedef TPckgBuf<TVwsViewEvent> TVwsViewEventBuf;


//
// Inlines
//

inline TVwsViewId::TVwsViewId()
/** Constructs a TVwsViewId object, and initialises both the application UID and 
the view UID to NULL. */
	: iAppUid(KNullUid), iViewUid(KNullUid) {}

inline TVwsViewId::TVwsViewId(const TVwsViewId& aUid)
/** Constructs a new TVwsViewId object from an existing one. This simply performs 
a member-wise copy, each member variable of the passed in object is individually 
copied to the corresponding member variable of the new object.

@param aUid A reference to the TVwsViewId object to be copied. */
	: iAppUid(aUid.iAppUid), iViewUid(aUid.iViewUid) {}

inline TVwsViewId::TVwsViewId(TUid aAppUid,TUid aViewUid)
/** Constructs a TVwsViewId object with the specified application UID and view UID.

@param aAppUid The application UID.
@param aViewUid The view UID. */
	: iAppUid(aAppUid), iViewUid(aViewUid) {}

inline TBool TVwsViewId::operator==(const TVwsViewId& aUid) const
/** Checks whether the TVwsViewId object being operated upon and the TVwsViewId 
object specified are the same.

Returns true if both application UIDs and both view UIDs are the same, otherwise 
returns false.

@param aUid A reference to a TVwsViewId object.
@return ETrue if objects are the same, EFalse otherwise. */
	{
	return (aUid.iAppUid==iAppUid && aUid.iViewUid==iViewUid);
	}

inline TBool TVwsViewId::operator!=(const TVwsViewId& aUid) const
/** Checks whether the TVwsViewId object being operated upon and the TVwsViewId 
object specified are different.

Returns true if either the application UIDs or view UIDs are different, otherwise 
returns false.

@param aUid A reference to a TVwsViewId object.
@return ETrue if objects are different, EFalse otherwise. */
	{
	return (aUid.iAppUid!=iAppUid || aUid.iViewUid!=iViewUid);
	}


inline TVwsViewIdAndMessage::TVwsViewIdAndMessage()
	: iViewId(TVwsViewId()), iCustomMessageLength(0)
	{
	iCustomMessageId.iUid=0;
	iCustomMessage.Set(KNullDesC8);
	}

inline TVwsViewIdAndMessage::TVwsViewIdAndMessage(const TVwsViewId& aId)
	: iViewId(aId), iCustomMessageLength(0)
	{
	iCustomMessageId.iUid=0;
	iCustomMessage.Set(KNullDesC8);
	}

inline TVwsViewIdAndMessage::TVwsViewIdAndMessage(const TVwsViewId& aId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	: iViewId(aId), iCustomMessageId(aCustomMessageId)
	{
	iCustomMessageLength=aCustomMessage.Length();
	iCustomMessage.Set(aCustomMessage);
	}


inline TVwsViewEvent::TVwsViewEvent() {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType)
	: iEventType(aEventType),iViewOneId(),iViewTwoId(),iCustomMessageId(KNullUid),iCustomMessageLength(0) {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId)
	: iEventType(aEventType),iViewOneId(aViewOneId),iViewTwoId(),iCustomMessageId(KNullUid),iCustomMessageLength(0) {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId)
	: iEventType(aEventType),iViewOneId(aViewOneId),iViewTwoId(aViewTwoId),iCustomMessageId(KNullUid),iCustomMessageLength(0) {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId,TUid aCustomMessageId,TInt aCustomMessageLength)
	: iEventType(aEventType),iViewOneId(aViewOneId),iViewTwoId(aViewTwoId),iCustomMessageId(aCustomMessageId),iCustomMessageLength(aCustomMessageLength) {}


#endif
