//e32/include/e32msgqueue.inl
//
// Copyright (c) 2002 Symbian Ltd. All rights reserved.
//


template <typename T>
inline TInt RMsgQueue<T>::CreateLocal(TInt aSize, TOwnerType aOwner)
	/** Create a private message queue

		Create a message queue which is private to the current process.

		@param "TInt aSize" The number of message 'slots' in the queue
		@param "TOwnerType aType" The type of handle to be created

		@panic "EMsgQueueInvalidLength" CreateLocal will panic if sizeof type T is not a multiple of 4 bytes, 
				 is less than 4 or is greater than KMaxLength.
		@panic "EMsgQueueInvalidSlots" CreateLocal will panic if aSize is less than or equal to zero.

		@return KErrNone if queue created sucessfully.
	*/
	{return RMsgQueueBase::CreateLocal(aSize, sizeof(T), aOwner);}

template <typename T>
inline TInt RMsgQueue<T>::CreateGlobal(const TDesC& aName, TInt aSize, TOwnerType aOwner)
	/** Create a global message queue

		Create a message queue which is visible to all processes.

		@param "const TDesC& aName" The name of the message queue
		@param "TInt aSize" The number of message 'slots' in the queue
		@param "TOwnerType aType" The type of handle to be created

		@panic "EMsgQueueInvalidLength" CreateGlobal will panic if sizeof type T is not a multiple of 4 bytes, 
				 is less than 4 or is greater than KMaxLength.
		@panic "EMsgQueueInvalidSlots" CreateGlobal will panic if aSize is less than or equal to zero.

		@return KErrNone if queue created sucessfully.
	*/
	{return RMsgQueueBase::CreateGlobal(aName, aSize, sizeof(T), aOwner);}

template <typename T>
inline TInt RMsgQueue<T>::Send(const T& aMessage)
	/** Send a message

		Send a message through the queue. 
		If the queue is full, this returns KErrOverflow and will not block.

		@param "const T& aMsg" The message data to send

		@see RMsgQueueBase::Send
	*/
	{return RMsgQueueBase::Send(&aMessage, sizeof(T));}

template <typename T>
inline void RMsgQueue<T>::SendBlocking(const T& aMessage)
	/** Send a message

		Send a message through the queue. 
		If the queue is full, this will wait until space is available. Note that this uses
		NotifySpaceAvailable() to provide the blocking operation.

		@param "const T& aMsg" The message data to send

		@see RMsgQueueBase::SendBlocking
	*/
	{RMsgQueueBase::SendBlocking(&aMessage, sizeof(T));}

template <typename T>
inline TInt RMsgQueue<T>::Receive(T& aMessage)
	/** Receive a message

		Retrieve the first message in the queue.
		If the queue is empty, this returns KErrUnderflow and will not block.

		@param "T& aMsg" The object into which the message is retrieved

		@see RMsgQueueBase::Receive
	*/
	{return RMsgQueueBase::Receive(&aMessage, sizeof(T));}

template <typename T>
inline void RMsgQueue<T>::ReceiveBlocking(T& aMessage)
	/** Receive a message

		Retrieve the first, message in the queue.
		If the queue is empty, this will wait until a message is available. Note that this uses
		NotifyDataAvailable() to provide the blocking operation.

		@param "T& aMsg" The object into which the message is retrieved
	
		@see RMsgQueueBase::ReceiveBlocking
	*/
	{RMsgQueueBase::ReceiveBlocking(&aMessage, sizeof(T));}

