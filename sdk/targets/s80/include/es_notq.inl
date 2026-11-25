/**
@file es_notq.inl

@internalComponent

Copyright (c) 2002 Symbian Ltd.  All rights reserved.
*/

template<class TInfo, TInt QueueSize> TNotificationQueue<TInfo, QueueSize>::TNotificationQueue()
/**
Constructor
*/
	: iQueueLength(0), iQueueStart(0)
	{
	}

template<class TInfo, TInt QueueSize> void TNotificationQueue<TInfo, QueueSize>::Reset()
/**
Reset notification queue, throwing away any stored notifications
*/
	{
	iQueueLength = 0;
	iQueueStart = 0;
	}

template<class TInfo, TInt QueueSize> void TNotificationQueue<TInfo, QueueSize>::Enque(const TInfo& aInfo)
/**
Place a InterfaceChange notification on the queue
@param aInfo notification information
*/
	{
	TUint index;

	if (IsEmpty())
		{
		index = iQueueStart;
		iQueueLength++;
		}
	else
		{
		index = (iQueueStart + iQueueLength) % QueueSize;

		// Have we reached capacity?
		if (index == iQueueStart)	// Yes, so overwrite
			iQueueStart = (iQueueStart + 1) % QueueSize;
		else
			iQueueLength++;

		}

	iQueue[index] = aInfo;		// default assignment operator used
	}

template<class TInfo, TInt QueueSize> TBool TNotificationQueue<TInfo, QueueSize>::Deque(TInfo& aInfo)
/**
De-queue the next InterfaceChange notification and return it

@param aInfo returned notification info
@return ETrue if a notification info was returned, EFalse otherwise (ie: queue was empty).
*/
	{
	if (!IsEmpty())
		{
		aInfo = iQueue[iQueueStart];	// default assignment operator used
		iQueueLength--;
		iQueueStart = (iQueueStart + 1) % QueueSize;
		return ETrue;
		}
	else
		return EFalse;
	}
