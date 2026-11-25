// AGMOBSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMOBSRV_H__
#define __AGMOBSRV_H__

#include <s32file.h>
#include <txtrich.h>
#include "agmentry.h"
#include "agmtodos.h"


#define KUidAgnObserver 0x10000135


class CAgnObserver : public CBase
/** The abstract base class for agenda model observers. 

All types of agenda model observer must implement this interface.

When an entry or to-do list is added, deleted or updated, each agenda model 
observer receives notification of the change via the model's observer controller.

For example, after an entry has been added to the model, CAgnEntryModel::AddEntryL() 
calls:

ObserverController()->Send(CAgnObserver::ENotifyAddEntry,aEntry);

This in turn calls the Send() function of every observer which has been registered 
with the controller, passing it the same arguments (the type of operation 
and the to-do list or entry affected) - Send() is overloaded to take a 
CAgnEntry and a CAgnTodoList. The observer's implementation of Send() 
might carry out some processing on the entry or to-do list, depending on the 
type of operation. 
@publishedAll
@released
*/
  	{
public:
	/** Identifies the type of change that caused the notification. */
	enum TFunction
			{
			/** An entry was added. */
			ENotifyAddEntry=1, 
			/** An entry was deleted. */
			ENotifyDeleteEntry=2,
			/** An entry was updated. */
			ENotifyUpdateEntry=3, 
			/** An entry was fetched.*/
			ENotifyFetchEntry=4, 
			/** A to-do list was added. */
			ENotifyAddTodoList=5,
			/** A to-do list was deleted. */
			ENotifyDeleteTodoList=6,
			/** A to-do list was updated. */
			ENotifyUpdateTodoList=7, 
			/** A to-do list was fetched.*/
			ENotifyFetchTodoList=8 
			};  

	enum {EEooByte1 = 0x55, EEooByte2 = 0xCC,EEooByte3 = 0xAA,EEooByte4 = 0x33};	// Eoo == end Of Observer

	// interface functions

	/** Starts observing changes. 
	
	Called by CAgnEntryModel::RegisterObserverL(), after the controller has 
	installed the observer. */
	virtual void StartObserving()=0; 
	/** Stops observing changes. 
	
	Called by CAgnEntryModel::UnregisterObserverL(), just before the observer 
	is removed from the observer controller. */
	virtual void StopObserving()=0;
	/** Creates and returns a copy of the observer. 
	
	Called by the observer controller during installation of the observer.
	
	@return Pointer to the observer clone. */
	virtual CAgnObserver* CloneL()=0; 
	/** This is called when an entry is added, deleted or updated by the 
	agenda model. 
	
	It is called by the observer controller with which this observer is registered. 

	@param aFunction Indicates which function caused the change notification. 
	For possible values, see the TFunction enumeration.
	@param aEntry Pointer to the entry affected. */
	virtual void Send(TInt aFunction,CAgnEntry* aEntry)=0;
	/** This is called when a to-do list is added, deleted or updated by the 
	agenda model. 
	
	It is called by the observer controller with which this observer is registered. 

	@param aFunction Indicates which function caused the change notification. 
	For possible values, see the TFunction enumeration.
	@param aTodoList Pointer to the to-do list affected. */
	virtual void Send(TInt aFunction,CAgnTodoList* aTodoList)=0;
	/** Externalises the observer data to a write stream. 
	
	The presence of this function means that the standard templated operator<<() 
	is available to externalise objects of this class. The last item written to 
	the write stream by this function should be the end of observer marker 
	(CAgnObserver::WriteEndMarkerL()).
	
	@param aStream Stream to which the data should be externalised. */
	virtual void ExternalizeL(RWriteStream& aStream) const=0;
	/** Internalises the observer data from a read stream. 
	
	The presence of this function means that the standard templated operator>>() is 
	available to internalise objects of this class. The last item read from the read 
	stream by this function should be the end of observer marker 
	(CAgnObserver::ReadEndMarkerL()).
	
	@param aStream Stream from which the data should be internalised. */
	virtual void InternalizeL(RReadStream& aStream)=0;
	IMPORT_C void WriteEndMarkerL(RWriteStream& aStream) const;
	IMPORT_C void ReadEndMarkerL(RReadStream& aStream) const;
	};


#endif
