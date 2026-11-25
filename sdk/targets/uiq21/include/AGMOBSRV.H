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


/**
 * The abstract base class for agenda model observers.
 *
 * All types of agenda model observer must inherit from this class and
 * implement the pure virtual functions it specifies.When an entry or
 * to-do list is added, deleted or updated, each agenda model observer
 * receives notification of the change via the model's observer
 * controller.For example, after an entry has been added to the model,
 * <code>CAgnEntryModel::AddEntryL()</code> calls:<code>ObserverControll-
 * er()->Send(CAgnObserver::ENotifyAddEntry,aEntry);</code>This in turn
 * calls the <code>Send()</code> function of every observer which has
 * been registered with the controller, passing it the same arguments
 * (the type of operation and the to-do list or entry affected)
 * <code>Send()</code> is overloaded to take a <code>CAgnEntry</code> and
 * a <code>CAgnTodoList</code>. The observer's <code>Send()</code>
 * function implementation might carry out some processing on the entry
 * or to-do list, depending on the type of operation.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnObserver : public CBase
  	{
public:
	enum TFunction /** Function Type.*/
			{
			ENotifyAddEntry=1, /** An entry was added.*/
			ENotifyDeleteEntry=2, /** An entry was deleted.*/
			ENotifyUpdateEntry=3, /** An entry was updated.*/
			ENotifyFetchEntry=4, /** An entry was fetched.*/
			ENotifyAddTodoList=5, /** A to-do list was added.*/
			ENotifyDeleteTodoList=6, /** A to-do list was deleted.*/
			ENotifyUpdateTodoList=7, /** A to-do list was updated.*/
			ENotifyFetchTodoList=8 /** A to-do list was fetched.*/
			};  

	enum {EEooByte1 = 0x55, EEooByte2 = 0xCC,EEooByte3 = 0xAA,EEooByte4 = 0x33};	// Eoo == end Of Observer

	// interface functions

	/**
	  * Starts observing changes.
	  *
	  * Called during <code>CAgnEntryModel::RegisterObserverL()</code>, after
	  * the controller has installed the observer.
	  */
	virtual void StartObserving()=0; 
	/**
	  *
	  * Stops observing changes.
	  *
	  * Called during <code>CAgnEntryModel::UnregisterObserverL()</code>, just
	  * before it is removed from the observer controller.
	  */
	virtual void StopObserving()=0;
	/**
	  *
	  * Implementations should create and return a copy of the observer.
	  *
	  * Called by the observer controller during installation of the observer.
	  *
	  * @returns   "CAgnObserver*"
	  *            Pointer to the observer clone.
	  */
	virtual CAgnObserver* CloneL()=0; 
	/**
	  *
	  * This overloaded function is called when an entry or to-do list is
	  * added, deleted or updated by the agenda model.
	  *
	  * It is called by the observer controller with which this observer is
	  * registered. The overload allows for changes to both agenda entries and
	  * to-do lists to be observed.
	  *
	  * @param     "TInt aFunction"
	  *            Indicates which function caused the change
	  *            notification. For possible values, see the
	  *            <code>TFunction</code> enumeration.
	  * @param     "CAgnEntry* aEntry"
	  *            Pointer to the entry affected.
	  * @param     "CAgnTodoList* aTodoList"
	  *            Pointer to the to-do list affected.
	  */
	virtual void Send(TInt aFunction,CAgnEntry* aEntry)=0;
	virtual void Send(TInt aFunction,CAgnTodoList* aTodoList)=0;
	/**
	  *
	  * Externalises the observer data to a write stream.
	  *
	  * The presence of this function means that the standard templated
	  * <code>operator<<()</code> is available to externalise objects of this
	  * class. The last item written to the write stream by this function
	  * should be the end of observer marker
	  * (<code>CAgnObserver::WriteEndMarkerL()</code>).
	  *
	  * @param     "RWriteStream& aStream"
	  * Stream to which the data should be externalised.
	  */
	virtual void ExternalizeL(RWriteStream& aStream) const=0;
	/**
	  *
	  * Internalises the observer data from a read stream.
	  *
	  * The presence of this function means that the standard templated
	  * <code>operator>>()</code> is available to internalise objects of this
	  * class. The last item read from the read stream by this function should
	  * be the end of observer marker
	  * (<code>CAgnObserver::ReadEndMarkerL()</code>).
	  *
	  * @param     "RReadStream& aStream"
	  *            Stream from which the data should be internalised.
	  */
	virtual void InternalizeL(RReadStream& aStream)=0;
	/**
	  *
	  * Writes the end of observer marker to the write stream.
	  *
	  * Call this function within <code>ExternalizeL()</code>.Note that
	  * derived classes should ensure that the combination of byte values in
	  * the end of observer marker (<code>EEooByte1</code>,
	  * <code>EEooByte2</code> etc.) is not present in the data being
	  * externalised.
	  *
	  * @param     "RWriteStream& aStream"
	  *            The stream to write to.
	  */
	IMPORT_C void WriteEndMarkerL(RWriteStream& aStream) const; // MUST be written as the LAST thing in Externalize	
	/**
	  *
	  * Reads the end of observer marker from the read stream.
	  *
	  * This must be the last item read by the <code>InternalizeL()</code>
	  * function.
	  *
	  * @param     "RReadStream& aStream"
	  *            The stream to read from.
	  */
	IMPORT_C void ReadEndMarkerL(RReadStream& aStream) const;
	};


#endif
