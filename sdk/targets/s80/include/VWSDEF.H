// VWSDEF.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __VWSDEF_H__
#define __VWSDEF_H__

#include <e32std.h>

/**
 *
 * Identifies an application view using two unique identifiers (UIDs): a
 * view UID and an application UID.
 *
 * The application UID is required so that the application associated
 * with the view can be started if it is not already running.
 *
 * @since 1.0
 * @lib "N/A"
 */
class TVwsViewId
	{
public:
	inline TVwsViewId();
	inline TVwsViewId(const TVwsViewId& aUid);
	inline TVwsViewId(TUid aAppUid,TUid aViewUid);
	inline TBool operator==(const TVwsViewId& aUid) const;
	inline TBool operator!=(const TVwsViewId& aUid) const;
public:
	TUid iAppUid;
	TUid iViewUid;
	};

#define KNullViewId TVwsViewId(KNullUid,KNullUid)
const TInt KErrViewWrongMode=1; // !!! Wrong error code - should be -ve & unique


/**
 * The TVwsViewIdAndMessage class identifies a view and encapsulates a message to be read by the view when it is
 * activated.
 *
 * @internal
 * Internal to Symbian
 */
class TVwsViewIdAndMessage
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


/**
 * The TVwsViewEvent class encapsulates the attributes of a view server event. These are the event type, the ids of
 * the two views associated with the event and the attributes of any message which can go with the event.
 *
 * @internal
 * Internal to Symbian
 */
class TVwsViewEvent
	{
public:
	enum TVwsViewEventType
		{
		EVwsActivateView,
		EVwsDeactivateView,
		EVwsScreenDeviceChanged,
		EVwsDeactivationNotification,
		EVwsActivationNotification,
		EVwsActivateViewAsync	//Only used in Series 80
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

typedef TPckgBuf<TVwsViewIdAndMessage> TVwsViewIdAndMessageBuf;
typedef TPckgBuf<TVwsViewEvent> TVwsViewEventBuf;


//
// Inlines
//

/**
 *
 * Constructs a <code>TVwsViewId</code> object with the specified
 * application UID and view UID.
 *
 * @param     "TUid aAppUid"
 *            The application UID.
 * @param     "TUid aViewUid"
 *            The view UID.
 */
inline TVwsViewId::TVwsViewId()
	: iAppUid(KNullUid), iViewUid(KNullUid) {}

inline TVwsViewId::TVwsViewId(const TVwsViewId& aUid)
	: iAppUid(aUid.iAppUid), iViewUid(aUid.iViewUid) {}

inline TVwsViewId::TVwsViewId(TUid aAppUid,TUid aViewUid)
	: iAppUid(aAppUid), iViewUid(aViewUid) {}

/**
 *
 * Checks whether the <code>TVwsViewId</code> object being operated upon
 * and the <code>TVwsViewId</code> object specified are the same.
 *
 * Returns true if both application UIDs and both view UIDs are the same,
 * otherwise returns false.
 *
 * @param     "const TVwsViewId& aUid"
 *            A reference to a <code>TVwsViewId</code> object.
 * @returns   "TBool"
 *            <code>ETrue</code> if objects are the same,
 *            <code>EFalse</code> otherwise.
 */
inline TBool TVwsViewId::operator==(const TVwsViewId& aUid) const
	{
	return (aUid.iAppUid==iAppUid && aUid.iViewUid==iViewUid);
	}

/**
 *
 * Checks whether the <code>TVwsViewId</code> object being operated upon
 * and the <code>TVwsViewId</code> object specified are different.
 *
 * Returns true if either the application UIDs or view UIDs are
 * different, otherwise returns false.
 *
 * @param     "const TVwsViewId& aUid"
 *            A reference to a <code>TVwsViewId</code> object.
 * @returns   "TBool"
 *            <code>ETrue</code> if objects are different,
 *            <code>EFalse</code> otherwise.
 */
inline TBool TVwsViewId::operator!=(const TVwsViewId& aUid) const
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
