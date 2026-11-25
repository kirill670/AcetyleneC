// AGMMODEL.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// -------------------------------- CAgnEntryModel -----------------------------------
inline CAgnEntryModel::CAgnEntryModel(MAgnModelStateCallBack* aStateCallBack)
	: iStateCallBack(aStateCallBack), 
	iTodoListMapKey (_FOFF(TTodoListMapItem,iOldId),ECmpNormal8,sizeof(TAgnTodoListId))
	{
	}

/**
 * Returns a pointer to the model's observer controller.
 *
 * @returns   "CAgnObsController*"
 *            A pointer to the model's observer controller.
 */
inline CAgnObsController* CAgnEntryModel::ObserverController() const
	{ return (iObserverController); }

/**
 * Returns a reference to the stream store in which the model's data is
 * stored.
 *
 * NoteThis function is deprecated when the model is using the agenda
 * server. This is because the model data should not be accessed directly
 * if the file has multiple clients.
 *
 * @returns   "CStreamStore&"
 *            A reference to the stream store in which the model's
 *            data is stored.
 */
inline CStreamStore& CAgnEntryModel::StreamStore() const
	{ return (*iStreamStore); }

inline CAgnModelStreamIdSet* CAgnEntryModel::ModelStreamIdSet() const
	{ return (iModelStreamIdSet); }

// this is public
/**
 * Returns a pointer to the model's list of to-do lists.
 *
 * This pointer can be used to retrieve the model's to-do lists and their
 * order.
 *
 * @returns   "CAgnTodoListList*"
 *            Constant pointer to the model's list of to-do lists.
 */
inline const CAgnTodoListList* CAgnEntryModel::PeekAtTodoListList() const
	{ return (iTodoListList);}

// but these two are protected
inline CAgnTodoListList* CAgnEntryModel::TodoListList() 
	{ return (iTodoListList); }

inline const CAgnTodoListList* CAgnEntryModel::TodoListList() const
	{ return (iTodoListList); }

inline const CAgnDeletedTodoListList* CAgnEntryModel::PeekAtDeletedTodoListList() const
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

/**
 * Sets the default display time for events.
 *
 * @param     "TTimeIntervalMinutes aDefaultEventDisplayTime"
 *            The new default display time for events, as a number
 *            of minutes from midnight.
 */
inline void CAgnEntryModel::SetDefaultEventDisplayTime(TTimeIntervalMinutes aDefaultEventDisplayTime)
	{ iDefaultEventDisplayTime=aDefaultEventDisplayTime; }

/**
 * Sets the default display time for anniversary entries.
 *
 * @param     "TTimeIntervalMinutes aDefaultAnnivDisplayTime"
 *            The new default display time for anniversary entries,
 *            as a number of minutes from midnight.
 */
inline void CAgnEntryModel::SetDefaultAnnivDisplayTime(TTimeIntervalMinutes aDefaultAnnivDisplayTime)
	{ iDefaultAnnivDisplayTime=aDefaultAnnivDisplayTime; }

/**
 * Sets the default display time for day notes.
 *
 * @param     "TTimeIntervalMinutes aDefaultDayNoteDisplayTime"
 *            The new default display time for day notes, as a
 *            number of minutes from midnight.
 */
inline void CAgnEntryModel::SetDefaultDayNoteDisplayTime(TTimeIntervalMinutes aDefaultDayNoteDisplayTime)
	{ iDefaultDayNoteDisplayTime=aDefaultDayNoteDisplayTime; }

/**
 * Retrieves the default display time for events.
 *
 * This value is initialised when the model is opened. It may be changed
 * by calling <code>SetDefaultEventDisplayTime()</code>.
 *
 * @returns   "TTimeIntervalMinutes"
 *            The default display time for events, as a number of
 *            minutes from midnight.
 */
inline TTimeIntervalMinutes CAgnEntryModel::DefaultEventDisplayTime() const
	{ return (iDefaultEventDisplayTime); }

/**
 * Retrieves the default display time for anniversary entries.
 *
 * This value is initialised when the model is opened. It may be changed
 * by calling <code>SetDefaultAnnivDisplayTime()</code>.
 *
 * @returns   "TTimeIntervalMinutes"
 *            The default display time for anniversary entries, as a
 *            number of minutes from midnight.
 */
inline TTimeIntervalMinutes CAgnEntryModel::DefaultAnnivDisplayTime() const
	{ return (iDefaultAnnivDisplayTime); }

/**
 * Retrieves the default display time for day notes.
 *
 * This value is initialised when the model is opened. It may be changed
 * by calling <code>SetDefaultDayNoteDisplayTime()</code>.
 *
 * @returns   "TTimeIntervalMinutes"
 *            The default display time for day notes, as a number of
 *            minutes from midnight.
 */
inline TTimeIntervalMinutes CAgnEntryModel::DefaultDayNoteDisplayTime() const
	{ return (iDefaultDayNoteDisplayTime); }

/**
 * Returns the state of the agenda model.
 *
 * @returns   "TState"
 *            The state of the agenda model.
 */
inline CAgnEntryModel::TState CAgnEntryModel::State() const
	{ return (iState); }

inline void CAgnEntryModel::SetState(CAgnEntryModel::TState aState)
	{ iState = aState; }

inline void CAgnEntryModel::RegisterIndex(CAgnSortEntryTable* aIndex)
	{ iRegisteredIndex = aIndex; }

/**
 * Returns a pointer to the model's entry index.
 *
 * This index can be used to find entries which are the same apart from
 * their entry IDs.
 *
 * @returns   "CAgnSortEntryTable*"
 *            The model's entry index.
 */
inline CAgnSortEntryTable* CAgnEntryModel::RegisteredIndex() const
	{ return (iRegisteredIndex); }

/**
 * Sets the model's registered alarm.
 *
 * @param     "CAgnAlarm* aAlarm"
 *            Pointer to the alarm to set as the model's registered
 *            alarm.
 */
inline void CAgnEntryModel::RegisterAlarm(CAgnAlarm* aAlarm)
	{ iRegisteredAlarm = aAlarm; }

/**
 * Returns a pointer to the model's registered alarm.
 *
 * @returns   "CAgnAlarm*"
 *            Pointer to the model's registered alarm. NULL if no
 *            registered alarm has been set.
 */
inline CAgnAlarm* CAgnEntryModel::RegisteredAlarm() const
	{ return (iRegisteredAlarm); }

/**
 * Returns a pointer to the paragraph format layer used by the model's
 * entries.
 *
 * @returns   "CParaFormatLayer*"
 *            A pointer to the model's paragraph format layer.
 */
inline const CParaFormatLayer* CAgnEntryModel::ParaFormatLayer() const
	{ return (iParaFormatLayer); }

/**
 * Returns a pointer to the character format layer used by the model's
 * entries.
 *
 * @returns   "CCharFormatLayer*"
 *            A pointer to the model's character format layer.
 */
inline const CCharFormatLayer* CAgnEntryModel::CharFormatLayer() const
	{ return (iCharFormatLayer); }

/**
 * Returns a pointer to the model's picture factory.
 *
 * @returns   "MPictureFactory*"
 *            Pointer to the agenda model's picture header factory.
 */
inline MPictureFactory* CAgnEntryModel::PictureFactory() const
	{ return (iPictureFactory); }

/**
 * Sets the model's picture factory.
 *
 * @param     "MPictureFactory* aPictureFactory"
 *            Pointer to the model's picture header factory.
 */
inline void CAgnEntryModel::SetPictureFactory(MPictureFactory* aPictureFactory)
	{ iPictureFactory = aPictureFactory; }

/**
 * Returns the version of the agenda model that was used to create the
 * currently loaded file.
 *
 * @returns   "TAgnVersion"
 *            The version of the agenda model that was used to
 *            create the currently loaded agenda file.
 */
inline TAgnVersion CAgnEntryModel::FileVersion() const
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
/**
 * Deletes, copies or moves a subset of the model's entries —
 * overloaded function.
 *
 * The entries affected are those which occur within the date/time range
 * starting at <code>aStartDate</code> and ending at
 * <code>aEndDate</code>. <code>aTodaysDate</code> identifies which to-do
 * entries fall within the specified range. <code>aFilter</code>
 * identifies which entry types are affected by the operation.If either
 * of the operations <code>ECopy</code> or <code>ECopyAndDelete</code> is
 * specified in <code>aDirective</code> then the function will either
 * create or open a stream freamwork within the supplied store
 * (<code>aStoreToTidyTo</code>) to which the tidied entries will be
 * copied. If <code>aStoreStreamId</code> is <code>KNullStreamId</code>
 * or is not specified, then a stream freamwork is created in
 * <code>aStoreToTidyTo</code>, and on return,
 * <code>aStoreStreamId</code> is set to the root stream ID of the store.
 * If <code>aStoreStreamId</code> is not <code>KNullStreamId</code> then
 * it is assumed that it is the root ID of an existing model and the
 * function opens and uses that to tidy to. Any previous contents will
 * remain untouched.The return value is <code>ETrue</code> or
 * <code>EFalse</code> depending on whether or not there were any entries
 * which matched the criteria and were tidied.After each step in the
 * operation, the percentage completed is reported via the callback
 * <code>aProgressCallBack</code> at a frequency which may be specified
 * in <code>aCallBackFrequency</code>. If <code>aCallBackFrequency</code>
 * is not specified, the callback frequency is the default value of
 * <code>ETidyByDateCallBackMedium</code>. <code>aProgressCallBack</code>
 * also reports how the operation completed.If the model has a state
 * callback, the function calls its <code>StateCallBack()</code> function
 * to notify users when the model is about to enter the blocked state,
 * and when it has left the blocked state.NoteIf the directive is either
 * <code>ECopy</code> or <code>ECopyAndDelete</code>, then a store to
 * copy to must be specified. If the directive is <code>EDelete</code>,
 * then you can specify NULL and <code>KNullStreamId</code> for the store
 * and stream ID, (or use the six parameter variant of the function).
 *
 * @param     "const TAgnFilter& aFilter"
 *            Identifies which entry types should be included in the
 *            operation.
 * @param     "const TTime& aTodaysDate"
 *            Today's date. Identifies which to-do entries should be
 *            included in the operation.
 * @param     "const TTime& aStartDate"
 *            The start date for the operation.
 * @param     "const TTime& aEndDate"
 *            The end date for the operation.
 * @param     "MAgnProgressCallBack* aProgressCallBack"
 *            Pointer to a callback object which reports the
 *            progress of the operation.
 * @param     "TTidyDirective aDirective"
 *            The type of operation — delete, copy or move. If
 *            <code>ECopy</code> or <code>ECopyAndDelete</code> is
 *            specified, a store must be specified in
 *            <code>aStoreToTidyTo</code>.
 * @param     "CStreamStore* aStoreToTidyTo"
 *            If <code>aDirective</code> is either
 *            <code>ECopy</code> or <code>ECopyAndDelete</code>, the
 *            stream store of the model to tidy to. Not relevant if
 *            the directive is <code>EDelete</code>.
 * @param     "TStreamId& aStoreStreamId"
 *            If specified, the root stream ID of the store to which
 *            the entries are copied. Only relevant if
 *            <code>aDirective</code> is either <code>ECopy</code>
 *            or <code>ECopyAndDelete</code>. If a null value is
 *            specified, on return, this is set to the root stream
 *            ID of <code>aStoreToTidyTo</code>.
 * @param     "TTidyByDateCallBackFrequency aCallBackFrequency = ETidyByDateCallBackMedium"
 *            If specified, the frequency at which
 *            <code>aProgressCallBack</code> should notify the
 *            progress of the operation. It should not normally be
 *            necessary to change this from the default value.
 * @returns   "TBool"
 *            <code>ETrue</code> if there were entries to tidy,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnIndexedModel::TidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,const TTime& aStartDate,
						const TTime& aEndDate,MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective)
	{
	CStreamStore* store=NULL;
	TStreamId id=KNullStreamId;
	return TidyByDateL(aFilter,aTodaysDate,aStartDate,aEndDate,aProgressCallBack,aDirective,store,id);
	}


inline TBool CAgnIndexedModel::TidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,const TTime& aStartDate,
						const TTime& aEndDate,MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,CStreamStore* aStoreToTidyTo)
	{
	TStreamId id=KNullStreamId;
	return TidyByDateL(aFilter,aTodaysDate,aStartDate,aEndDate,aProgressCallBack,aDirective,aStoreToTidyTo,id);
	}

/**
 * Tidy to-do listsDeletes, copies or moves the entries contained in a
 * list of to-do lists — overloaded function.
 *
 * The operation may affect all the entries in the lists, just crossed
 * out entries, or all entries except the crossed out ones.After each
 * step in the operation, the percentage completed is reported via the
 * callback <code>aProgressCallBack</code> at a frequency which may be
 * specified in <code>aCallBackFrequency</code>. If
 * <code>aCallBackFrequency</code> is not specified, the callback
 * frequency is the default value of
 * <code>ETidyByTodoListCallBackMedium</code>.
 * <code>aProgressCallBack</code> also reports how the operation
 * completed.If the model has a state callback, its
 * <code>StateCallBack()</code> function is called to notify users when
 * the model is about to enter the blocked state, and when it has left
 * the blocked state.If either of the operations <code>ECopy</code> or
 * <code>ECopyAndDelete</code> is specified in <code>aDirective</code>
 * then the function will either create or open a stream freamwork within
 * the supplied store (<code>aStoreToTidyTo</code>) to which the tidied
 * entries will be copied. If <code>aStoreStreamId</code> is
 * <code>KNullStreamId</code> or is not specified, then a stream
 * freamwork is created in <code>aStoreToTidyTo</code>, and on return,
 * <code>aStoreStreamId</code> is set to the root stream ID of the store.
 * If <code>aStoreStreamId</code> is not <code>KNullStreamId</code> then
 * it is assumed that it is the root ID of an existing model and the
 * function opens and uses that to tidy to. Any previous contents will
 * remain unaffected.NoteIf the directive is either <code>ECopy</code> or
 * <code>ECopyAndDelete</code>, then a store to copy to must be
 * specified. If the directive is <code>EDelete</code>, then you can
 * specify NULL and <code>KNullStreamId</code> for the store and stream
 * ID, (or use the four parameter variant of the function).
 *
 * @param     "const CArrayFixFlat<TAgnTodoListId>* aList"
 *            Pointer to a list of to-do list IDs which identify the
 *            to-do lists to be tidied.
 * @param     "MAgnProgressCallBack* aProgressCallBack"
 *            Pointer to a callback object which reports the
 *            progress of the operation.
 * @param     "TTidyDirective aDirective"
 *            The type of operation — delete, copy or move. If
 *            <code>ECopy</code> or <code>ECopyAndDelete</code> is
 *            specified, a store must be specified in
 *            <code>aStoreToTidyTo</code>.
 * @param     "TTidyTodoListHow aTidyHow"
 *            Specifies which to-do entries are to be tidied.
 * @param     "CStreamStore* aStoreToTidyTo"
 *            If <code>aDirective</code> is either
 *            <code>ECopy</code> or <code>ECopyAndDelete</code>, the
 *            stream store of the model to tidy to. Not relevant if
 *            the directive is <code>EDelete</code>.
 * @param     "TStreamId& aStoreStreamId"
 *            If specified, the root stream ID of the store to which
 *            the entries are copied. Only relevant if
 *            <code>aDirective</code> is either <code>ECopy</code>
 *            or <code>ECopyAndDelete</code>. If a null value is
 *            specified, on return, this is set to the root stream
 *            ID of <code>aStoreToTidyTo</code>.
 * @param     "TTidyByTodoListCallBackFrequency aCallBackFrequency = ETidyByTodoListCallBackMedium"
 *            If specified, the frequency at which
 *            <code>aProgressCallBack</code> should notify the
 *            progress of the operation. It should not normally be
 *            necessary to change this from the default value.
 * @returns   "TBool"
 *            Always <code>ETrue</code>.
 */
inline TBool CAgnIndexedModel::TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective,TTidyTodoListHow aTidyHow)
	{
	CStreamStore* store=NULL;
	TStreamId id=KNullStreamId;
	return TidyByTodoListL(aList,aProgressCallBack,aDirective,aTidyHow,store,id);
	}

inline TBool CAgnIndexedModel::TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,CStreamStore* aStoreToTidyTo)
	{
	TStreamId id=KNullStreamId;
	return TidyByTodoListL(aList,aProgressCallBack,aDirective,aTidyHow,aStoreToTidyTo,id);
	}
	
inline CAgnIndexedModel::CAgnIndexedModel(MAgnModelStateCallBack* aStateCallBack)
	: CAgnEntryModel(aStateCallBack)
	{
	}

/**
 * Gets a pointer to the model's indexes.
 *
 * @returns   "CAgnSortEntryTable*"
 *            Pointer to the model's indexes.
 */
inline CAgnSortEntryTable* CAgnIndexedModel::Indexes() const  
	{ return iIndexes; }

// -------------------------------- CAgnModel ----------------------------------
inline CAgnModel::CAgnModel(MAgnModelStateCallBack* aStateCallBack)
	: CAgnIndexedModel(aStateCallBack)
	{
	}

