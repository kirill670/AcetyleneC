// AGMMODEL.INL
//
// Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
//

// -------------------------------- CAgnEntryModel -----------------------------------

inline CAgnEntryModel::CAgnEntryModel(MAgnModelStateCallBack* aStateCallBack)
	: iStateCallBack(aStateCallBack), 
	iTodoListMapKey (_FOFF(TTodoListMapItem,iOldId),ECmpNormal8,sizeof(TAgnTodoListId))
	{
	}

inline CAgnEntryModelExData& CAgnEntryModel::AgnEntryModelExData() const
	{ return *iAgnEntryModelExData; }

inline CAgnServFile& CAgnEntryModelExData::AgnServerFile() const
	{
	return *iAgnServerFile;
	}	

inline void CAgnEntryModelExData::SetFileredEntry(CArrayFixSeg<TAgnEntryId>* aEntries)
	{
	iFilteredEntries = aEntries;
	}

inline void CAgnEntryModelExData::SetFileredEntryToNull()
	{
	iFilteredEntries=NULL;
	}

inline CArrayFixSeg<TAgnEntryId>* CAgnEntryModelExData::FilteredEntries() const
	{
	return iFilteredEntries;
	}

inline void CAgnProgressReporter::SetReport(TInt aValue)
 {iValue = aValue;}

inline CAgnObsController* CAgnEntryModel::ObserverController() const
/** Gets a pointer to the model's observer controller.

@return A pointer to the model's observer controller. */
	{ return (iObserverController); }

inline CStreamStore& CAgnEntryModel::StreamStore() const
/** Gets a reference to the stream store in which the model's data is stored.

Note: this function is deprecated when the model is in client mode, 
because data should not be accessed directly.

@return A reference to the stream store in which the model's data is stored. 
@deprecated
*/
	{ return (*iStreamStore); }

inline CAgnModelStreamIdSet* CAgnEntryModel::ModelStreamIdSet() const
	{ return (iModelStreamIdSet); }

// this is public
inline const CAgnTodoListList* CAgnEntryModel::PeekAtTodoListList() const
/** Gets a pointer to the model's list of to-do lists. 

This can be used to retrieve the model's to-do lists and their order.

@return Constant pointer to the model's list of to-do lists. */
	{ return (iTodoListList);}

// but these two are protected
inline CAgnTodoListList* CAgnEntryModel::TodoListList() 
	{ return (iTodoListList); }

inline const CAgnTodoListList* CAgnEntryModel::TodoListList() const
	{ return (iTodoListList); }

inline const CAgnDeletedTodoListList* CAgnEntryModel::PeekAtDeletedTodoListList() const
/** Gets a pointer to the list of deleted to-do lists. 

This is provided for synchronisation.

Note: to get an array of the todo list IDs for all the to-do lists held by the model, 
whether deleted or not, use the function TodoListIdsL().

@return Pointer to the model's list of deleted to-do lists. */
	{ return (iDeletedTodoListList); }

inline CAgnDeletedTodoListList* CAgnEntryModel::DeletedTodoListList() 
	{ return (iDeletedTodoListList); }

inline const CAgnEntryStore* CAgnEntryModel::EntryStore() const
	{ return (iEntryStore); }

inline CAgnEntryStore* CAgnEntryModel::EntryStore() 
	{ return (iEntryStore); }

inline const TAgnTodoListStore& CAgnEntryModel::TodoListStore() const
	{ return (iTodoListStore); }

inline TAgnTodoListStore& CAgnEntryModel::TodoListStore() 
	{ return (iTodoListStore); }

inline void CAgnEntryModel::SetDefaultEventDisplayTime(TTimeIntervalMinutes aDefaultEventDisplayTime)
/** Sets the default display time for events.

@param aDefaultEventDisplayTime The new default display time for events, as 
a number of minutes from midnight. */
	{ iDefaultEventDisplayTime=aDefaultEventDisplayTime; }

inline void CAgnEntryModel::SetDefaultAnnivDisplayTime(TTimeIntervalMinutes aDefaultAnnivDisplayTime)
/** Sets the default display time for anniversaries.

@param aDefaultAnnivDisplayTime The new default display time for anniversary 
entries, as a number of minutes from midnight. */
	{ iDefaultAnnivDisplayTime=aDefaultAnnivDisplayTime; }

inline void CAgnEntryModel::SetDefaultDayNoteDisplayTime(TTimeIntervalMinutes aDefaultDayNoteDisplayTime)
/** Sets the default display time for day notes.

@param aDefaultDayNoteDisplayTime The new default display time for day notes, 
as a number of minutes from midnight. */
	{ iDefaultDayNoteDisplayTime=aDefaultDayNoteDisplayTime; }

inline TTimeIntervalMinutes CAgnEntryModel::DefaultEventDisplayTime() const
/** Gets the default display time for events. 

This value is initialised when the model is opened. It may be 
changed by calling SetDefaultEventDisplayTime().

@return The default display time for events, as a number of minutes from midnight. */
	{ return (iDefaultEventDisplayTime); }

inline TTimeIntervalMinutes CAgnEntryModel::DefaultAnnivDisplayTime() const
/** Gets the default display time for anniversaries. 

This value is initialised when the model is opened. It may be changed by 
calling SetDefaultAnnivDisplayTime().

@return The default display time for anniversary entries, as a number of minutes 
from midnight. */
	{ return (iDefaultAnnivDisplayTime); }

inline TTimeIntervalMinutes CAgnEntryModel::DefaultDayNoteDisplayTime() const
/** Gets the default display time for day notes. 

This value is initialised when the model is opened. It may be changed by 
calling SetDefaultDayNoteDisplayTime().

@return The default display time for day notes, as a number of minutes from 
midnight. */
	{ return (iDefaultDayNoteDisplayTime); }

inline CAgnEntryModel::TState CAgnEntryModel::State() const
/** Gets the state of the agenda model.

@return The state of the agenda model. */
	{ return (iState); }

inline void CAgnEntryModel::SetState(CAgnEntryModel::TState aState)
	{ iState = aState; }

inline void CAgnEntryModel::RegisterIndex(CAgnSortEntryTable* aIndex)
	{ iRegisteredIndex = aIndex; }

inline CAgnSortEntryTable* CAgnEntryModel::RegisteredIndex() const
/** Gets a pointer to the model's entry index. 

This index can be used to find entries which are the same apart from 
their entry IDs.

@return The model's entry index. */
	{ return (iRegisteredIndex); }

inline void CAgnEntryModel::RegisterAlarm(CAgnAlarm* aAlarm)
/** Sets the model's registered alarm.

@param aAlarm Pointer to the alarm to set as the model's registered alarm. */
	{ iRegisteredAlarm = aAlarm; }

inline CAgnAlarm* CAgnEntryModel::RegisteredAlarm() const
/** Gets a pointer to the model's registered alarm.

@return Pointer to the model's registered alarm. NULL if no registered alarm 
has been set. */
	{ return (iRegisteredAlarm); }

inline const CParaFormatLayer* CAgnEntryModel::ParaFormatLayer() const
/** Gets a pointer to the paragraph format layer used by the model's entries.

@return A pointer to the model's paragraph format layer. */
	{ return (iParaFormatLayer); }

inline const CCharFormatLayer* CAgnEntryModel::CharFormatLayer() const
/** Gets a pointer to the character format layer used by the model's entries.

@return A pointer to the model's character format layer. */
	{ return (iCharFormatLayer); }

inline MPictureFactory* CAgnEntryModel::PictureFactory() const
/** Gets a pointer to the model's picture factory.

@return Pointer to the agenda model's picture header factory. */
	{ return (iPictureFactory); }

inline void CAgnEntryModel::SetPictureFactory(MPictureFactory* aPictureFactory)
/** Sets the model's picture factory.

@param aPictureFactory Pointer to the model's picture header factory. */
	{ iPictureFactory = aPictureFactory; }

inline TAgnVersion CAgnEntryModel::FileVersion() const
/** Gets the version of the agenda model that was used to create the current 
file.

@return The version of the agenda model that was used to create the current 
agenda file. */
	{ return (ModelStreamIdSet()->Version()); }

inline CAgnGlobalIdIndex* CAgnEntryModel::GlobalIdIndex() const
	{ return iGlobalIdIndex; }

inline CAgnUniqueIdIndex* CAgnEntryModel::UniqueIdIndex() const
	{ return iUniqueIdIndex; }

inline CAgnTodoListIdIndex* CAgnEntryModel::TodoListIdIndex() const
	{ return iTodoListIdIndex; }

inline CAgnDeletedIndex* CAgnEntryModel::DeletedIndex() const
	{ return iDeletedIndex; }


// -------------------------------- CAgnIndexedModel ----------------------------------

#ifdef SYMBIAN_SUPPORT_COREAPPS_API_V1
/** Deletes, copies or moves a subset of the model's entries.

The entries affected are those which occur within the date/time range starting 
at aStartDate and ending at aEndDate.

If either of the operations ECopy or ECopyAndDelete is specified in aDirective then 
the function will either create or open a stream framework within the supplied store 
(aStoreToTidyTo) to which the tidied entries will be copied. 

After each step in the operation, the percentage completed is reported via the 
callback aProgressCallBack at a frequency of ETidyByDateCallBackMedium. 
aProgressCallBack also reports how the operation completed.

If the model has a state callback, the function calls its StateCallBack() function 
to notify users when the model is about to enter the blocked state, and when it 
has left the blocked state.

Note: if the directive is either ECopy or ECopyAndDelete, then a store to copy to must 
be specified. If the directive is EDelete you can use the six parameter variant 
of this function instead.

@capability WriteUserData
@capability ReadUserData
@param aFilter Identifies which entry types should be included in the operation.
@param aTodaysDate Today's date. Identifies which to-do entries should be included in the operation.
@param aStartDate The start date for the operation.
@param aEndDate The end date for the operation.
@param aProgressCallBack Pointer to a callback object which reports the progress of the operation.
@param aDirective The type of operation: delete, copy or move. If ECopy or ECopyAndDelete is specified, 
a store must be specified in aStoreToTidyTo.
@param aStoreToTidyTo If aDirective is either ECopy or ECopyAndDelete, the stream store of the model to tidy 
to. Not relevant if the directive is EDelete.
@return ETrue if there were entries which matched the criteria and were tidied, EFalse if not. 
*/
//OpCodes: ECommit, ESetModelTextFormatting, EFetchTodoList, ERefreshTodoListList, ENextAlarm
//OpCodes: ESetLastSynchronizedDate, ECreateDateIterator, ESetBufferedStoring, EGetNumEntriesToTidy
//OpCodes: ESetBufferedDeleting
inline TBool CAgnIndexedModel::TidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,const TTime& aStartDate,
						const TTime& aEndDate,MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,CStreamStore* aStoreToTidyTo)
	{
	TStreamId id=KNullStreamId;
	return TidyByDateL(aFilter,aTodaysDate,aStartDate,aEndDate,aProgressCallBack,aDirective,aStoreToTidyTo,id);
	}
#endif


#ifdef SYMBIAN_SUPPORT_COREAPPS_API_V1
//#ifndef __SECURE_DATA__ 
/** Deletes, copies or moves the entries contained in a list of to-do lists. 

The operation may affect all the entries in the lists, just crossed out entries, 
or all entries except the crossed out ones.

After each step in the operation, the percentage completed is reported via the 
callback aProgressCallBack at a frequency of ETidyByTodoListCallBackMedium. 
aProgressCallBack also reports how the operation completed.

If the model has a state callback, its StateCallBack() function is called to 
notify users when the model is about to enter the blocked state, and when it 
has left the blocked state.

If either of the operations ECopy or ECopyAndDelete is specified in aDirective 
then the function will either create or open a stream framework within the 
supplied store (aStoreToTidyTo) to which the tidied entries will be copied. 
In this case, a store to copy to must be specified.

If the directive is EDelete then you can use the four parameter overload instead.

@capability WriteUserData
@capability ReadUserData
@param aList Pointer to a list of IDs which identify the to-do lists to be tidied.
@param aProgressCallBack Pointer to a callback object which reports the progress of 
the operation.
@param aDirective The type of operation: delete, copy or move. If ECopy or ECopyAndDelete 
is specified, a store must be specified in aStoreToTidyTo.
@param aTidyHow Specifies which to-do entries are to be tidied.
@param aStoreToTidyTo If aDirective is either ECopy or ECopyAndDelete, the stream 
store of the model to tidy to. Not relevant if the directive is EDelete.
@return Always ETrue. 
*/
//OpCodes: ESetModelTextFormatting, EFetchTodoList, ERefreshTodoListList
//OpCodes: ESetLastSynchronizedDate, ESetBufferedStoring, ESetBufferedDeleting
inline TBool CAgnIndexedModel::TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,CStreamStore* aStoreToTidyTo)
	{
	TStreamId id=KNullStreamId;
	return TidyByTodoListL(aList,aProgressCallBack,aDirective,aTidyHow,aStoreToTidyTo,id);
	}
#endif
	
inline CAgnIndexedModel::CAgnIndexedModel(MAgnModelStateCallBack* aStateCallBack)
	: CAgnEntryModel(aStateCallBack)
	{
	}

inline CAgnSortEntryTable* CAgnIndexedModel::Indexes() const  
/** Gets a pointer to the model's indexes.

@return Pointer to the model's indexes. */
	{ return iIndexes; }

// -------------------------------- CAgnModel ----------------------------------
inline CAgnModel::CAgnModel(MAgnModelStateCallBack* aStateCallBack)
	: CAgnIndexedModel(aStateCallBack)
	{
	}
