// FEPBASE.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__FEPBASE_H__)
#define __FEPBASE_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

#if !defined(__F32FILE_H__)
#include <F32FILE.H>
#endif

#if !defined(__W32STD_H__)
#include <W32STD.H>
#endif

#if !defined(__COEDEF_H__)
#include <COEDEF.H>
#endif

#if !defined(__COEMAIN_H__)
#include <COEMAIN.H>
#endif

// macros to be called by keyboard-based FEPs in their CCoeControl::OfferKeyEventL-overriding function

#define FEP_START_KEY_EVENT_HANDLER_L(aFep, aKeyEvent, aEventCode)\
	{\
	if ((aFep).IsSimulatingKeyEvent())\
		{\
		return EKeyWasNotConsumed;\
		}\
	(aFep).OnStartingHandlingKeyEvent_WithDownUpFilterLC();\
	if (((aEventCode)!=EEventKey) || (aFep).IsTurnedOnByL(aKeyEvent) || (aFep).IsTurnedOffByL(aKeyEvent))\
		{\
		return (aFep).OnFinishingHandlingKeyEvent_WithDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasConsumed);\
		}\
	if (!(aFep).IsOn())\
		{\
		return (aFep).OnFinishingHandlingKeyEvent_WithDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasNotConsumed);\
		}\
	}

#define FEP_END_KEY_EVENT_HANDLER_L(aFep, aKeyEvent, aKeyResponse)\
	{\
	return (aFep).OnFinishingHandlingKeyEvent_WithDownUpFilterL(EEventKey, (aKeyEvent), (aKeyResponse));\
	}

#define FEP_START_KEY_EVENT_HANDLER_NO_DOWN_UP_FILTER_L(aFep, aKeyEvent, aEventCode)\
	{\
	if ((aFep).IsSimulatingKeyEvent())\
		{\
		return EKeyWasNotConsumed;\
		}\
	(aFep).OnStartingHandlingKeyEvent_NoDownUpFilterLC();\
	if ((aEventCode)==EEventKey)\
		{\
		if ((aFep).IsTurnedOnByL(aKeyEvent) || (aFep).IsTurnedOffByL(aKeyEvent))\
			{\
			return (aFep).OnFinishingHandlingKeyEvent_NoDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasConsumed);\
			}\
		if (!(aFep).IsOn())\
			{\
			return (aFep).OnFinishingHandlingKeyEvent_NoDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasNotConsumed);\
			}\
		}\
	}

#define FEP_END_KEY_EVENT_HANDLER_NO_DOWN_UP_FILTER_L(aFep, aKeyEvent, aEventCode, aKeyResponse)\
	{\
	return (aFep).OnFinishingHandlingKeyEvent_NoDownUpFilterL((aEventCode), (aKeyEvent), (aKeyResponse));\
	}

/**
 *
 * On or off key data for FEPs.
 *
 * The <code>CCoeFep</code> class uses instances of this class to specify
 * the key combination which is used to turn the FEP on and off. These
 * values are initialised during construction of the FEP (see
 * <code>CCoeFep::BaseConstructL()</code>).The class consists of three
 * <code>TUint</code>s. They represent: the character code of the key
 * combinationa modifier mask which indicates which modifiers are
 * relevant to the key combinationthe modifier values which indicate
 * which of the modifiers specified in the modifier mask must be on and
 * which must be offFor example, if the key combination to turn the FEP
 * off is Fn+Enter, where the Shift modifier must not be down (and the
 * state of all other modifiers is irrelevant), the
 * <code>TFepOnOrOffKeyData</code> object would be constructed as
 * follows:Note that modifiers should not be set in the values if they
 * are not also set in the mask.
 *
 * @since 6.0
 * @lib "fepbase.lib"
 */
class TFepOnOrOffKeyData
	{
public:
	/**
	 *
	 * The C++ constructor is used to construct the key data object with the
	 * character code, the modifier mask and the modifier values.
	 *
	 * @param     "TUint aCharacterCodeForFoldedMatch"
	 *            The character code.
	 * @param     "TUint aModifierMask"
	 *            The modifier mask.
	 * @param     "TUint aModifierValues"
	 *            The modifier values.
	 */
	inline TFepOnOrOffKeyData(TUint aCharacterCodeForFoldedMatch, TUint aModifierMask, TUint aModifierValues) :iCharacterCodeForFoldedMatch(aCharacterCodeForFoldedMatch), iModifierMask(aModifierMask), iModifierValues(aModifierValues) {}
	/**
	 *
	 * Gets the character code.
	 *
	 * @returns   "TUint"
	 *            The character code.
	 */
	inline TUint CharacterCodeForFoldedMatch() const {return iCharacterCodeForFoldedMatch;}
	/**
	 *
	 * Gets the modifier mask.
	 *
	 * @returns   "TUint"
	 *            The modifier mask.
	 */
	inline TUint ModifierMask() const {return iModifierMask;}
	/**
	 *
	 * Gets the modifier values.
	 *
	 * @returns   "TUint"
	 *            The modifier values.
	 */
	inline TUint ModifierValues() const {return iModifierValues;}
private:
	TUint iCharacterCodeForFoldedMatch;
	TUint iModifierMask;
	TUint iModifierValues;
	};

class CDictionaryStore;
class RWriteStream;
class RReadStream;

/**
 *
 * Reads and writes generic FEP settings.
 *
 * Used by the <code>CCoeFep</code> class. The generic FEP settings are
 * whether the FEP is on or off and what key combinations should turn the
 * FEP on or off. Also used to synchronise these settings across all
 * running instances of the FEP. These settings are generic, unlike FEP
 * attributes which are FEP-specific. FEP attributes are stored, restored
 * and synchronised using class <code>MFepAttributeStorer</code>. Generic
 * FEP settings are changed locally using the <code>Set...()</code>
 * member functions. Then, to store these as the system settings and to
 * apply them globally, call
 * <code>StoreChangesAndBroadcastL()</code>.Class <code>CCoeFep</code>
 * initialises its generic FEP settings from the global system settings
 * during construction. Its generic FEP settings are updated when the
 * settings are changed by a call to
 * <code>StoreChangesAndBroadcastL()</code> by another running instance
 * of the FEP.
 *
 * @since 6.0
 * @lib "fepbase.lib"
 */
class CFepGenericGlobalSettings : public CBase
	{
public:
	IMPORT_C static CFepGenericGlobalSettings* NewL(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	IMPORT_C static CFepGenericGlobalSettings* NewLC(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	IMPORT_C TFepOnOrOffKeyData OnKeyData() const;
	IMPORT_C void SetOnKeyData(const TFepOnOrOffKeyData& aOnKeyData);
	IMPORT_C TFepOnOrOffKeyData OffKeyData() const;
	IMPORT_C void SetOffKeyData(const TFepOnOrOffKeyData& aOffKeyData);
	IMPORT_C TBool IsOn() const;
	IMPORT_C void SetIsOn(TBool aIsOn);
	IMPORT_C void StoreChangesAndBroadcastL();
	IMPORT_C void RefreshL();
	static void ReadOnAndOffKeyDataFromStreamL(TFepOnOrOffKeyData& aOnKeyData, TFepOnOrOffKeyData& aOffKeyData, RReadStream& aStream);
	static void ReadIsOnFromStreamL(TUint& aFlags, TUint aFlagIsOn, RReadStream& aStream);
	static void StoreIsOnAndBroadcastL(CCoeEnv& aConeEnvironment, TBool aIsOn);
private:
	CFepGenericGlobalSettings(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	void ConstructL();
	static void ReadOnOrOffKeyDataFromStreamL(TFepOnOrOffKeyData& aOnOrOffKeyData, RReadStream& aStream);
	static void WriteOnOrOffKeyDataToStreamL(const TFepOnOrOffKeyData& aOnOrOffKeyData, RWriteStream& aStream);
	static void WriteOnAndOffKeyDataAndBroadcastL(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aOnKeyData, const TFepOnOrOffKeyData& aOffKeyData, CDictionaryStore& dictionaryStore);
	static void WriteIsOnDataAndBroadcastL(CCoeEnv& aConeEnvironment, TBool aIsOn, CDictionaryStore& aDictionaryStore);
private:
	enum
		{
		EFlagDefaultIsOn	=0x00000001,
		EFlagIsOn			=0x00000002
		};
private:
	CCoeEnv& iConeEnvironment;
	TUint iFlags;
	TFepOnOrOffKeyData iDefaultOnKeyData;
	TFepOnOrOffKeyData iDefaultOffKeyData;
	TFepOnOrOffKeyData iOnKeyData;
	TFepOnOrOffKeyData iOffKeyData;
	};

/**
 *
 * Specifies the mixin protocol for observing a FEP transaction.
 *
 * Applications which need to implement this protocol should derive from
 * this class. The functions are not pure virtual because most
 * applications will only need to override one of them.
 *
 * @since 6.0
 * @lib ""
 */
class MCoeFepObserver
	{
public:
	// both of these functions do nothing by default - the reason that they are not pure virtual is that most applications will only want to override one of them
	IMPORT_C virtual void HandleStartOfTransactionL(); // the responsibility of FEPs to call
	IMPORT_C virtual void HandleCompletionOfTransactionL(); // the responsibility of FEPBASE to call - not to be called if the transaction is canceled
private:
	IMPORT_C virtual void MCoeFepObserver_Reserved_1();
	IMPORT_C virtual void MCoeFepObserver_Reserved_2();
	};

IMPORT_C void FepObserverHandleStartOfTransactionL(MCoeFepObserver& aFepObserver);

class CCoeFepParameters : public CBase
	{
public: // Internal to Symbian
	IMPORT_C static CCoeFepParameters* NewL(const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	IMPORT_C static CCoeFepParameters* NewLC(const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	TFepOnOrOffKeyData DefaultOnKeyData() const;
	TFepOnOrOffKeyData DefaultOffKeyData() const;
	TBool DefaultIsOn() const;
private:
	CCoeFepParameters(const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
private:
	TFepOnOrOffKeyData iDefaultOnKeyData;
	TFepOnOrOffKeyData iDefaultOffKeyData;
	TBool iDefaultIsOn;
	};

/**
 *
 * Protocol for storing, restoring and synchronising FEP attributes.
 *
 * An abstract base class for <code>CCoeFep</code>, so FEPs must
 * implement the pure virtual functions declared in this class.Rather
 * than using a single device-wide instance of a FEP, each application
 * has its own instance of the FEP. <code>MFepAttributeStorer</code>
 * provides a framework for synchronising FEP attributes across each
 * running instance of the same FEP. For this to happen, the FEP must
 * implement
 * <code>MFepAttributeStorer::WriteAttributeDataToStreamL()</code> and
 * <code>MFepAttributeStorer::ReadAttributeDataFromStreamL()</code>.
 * Attributes are FEP-specific, and are identified by a UID which can be
 * accessed using <code>AttributeAtIndex()</code>. An example of a FEP
 * attribute might be whether inline editing is enabled or disabled.
 *
 * @since 6.0
 * @lib "fepbase.lib"
 */
class MFepAttributeStorer
	{
public:
	IMPORT_C void ReadAllAttributesL(CCoeEnv& aConeEnvironment);
	IMPORT_C void WriteAttributeDataAndBroadcastL(CCoeEnv& aConeEnvironment, TUid aAttributeUid);
	IMPORT_C void WriteAttributeDataAndBroadcastL(CCoeEnv& aConeEnvironment, const TArray<TUid>& aAttributeUids);
	/**
	 *
	 * Returns the total number of FEP attributes.
	 *
	 * @returns   "TInt"
	 *            The number of FEP attributes.
	 */
	virtual TInt NumberOfAttributes() const=0;
	/**
	 *
	 * Returns the UID of the FEP attribute at the index specified.
	 *
	 * @param     "TInt aIndex"
	 *            An array index.
	 * @returns   "TUid"
	 *            The UID of the FEP attribute at <code>aIndex</code>.
	 */
	virtual TUid AttributeAtIndex(TInt aIndex) const=0;
	/**
	 *
	 * Writes the value of the attribute specified to the specified write
	 * stream.
	 *
	 * Called by
	 * <code>MFepAttributeStorer::WriteAttributeDataAndBroadcastL()</code>
	 * for each attribute passed to it.
	 *
	 * @param     "TUid aAttributeUid"
	 *            UID of the attribute to write to the stream.
	 * @param     "RWriteStream& aStream"
	 *            The stream to which to write the attribute.
	 */
	virtual void WriteAttributeDataToStreamL(TUid aAttributeUid, RWriteStream& aStream) const=0;
	/**
	 *
	 * Reads the value of the attribute identified by the UID specified in
	 * <code>aAttributeUid</code> from the specified read stream.
	 *
	 * You should take appropriate action if the attribute has changed e.g.
	 * if inline editing has been disabled, you might cancel the current
	 * transaction.This function is called by
	 * <code>MFepAttributeStorer::ReadAllAttributesL()</code> for all
	 * attributes. It is also called when the FEP receives a message that an
	 * attribute has been changed by another running instance of the FEP
	 * (using <code>WriteAttributeDataAndBroadcastL()</code>).
	 *
	 * @param     "TUid aAttributeUid"
	 *            Identifies the attribute whose value should be read.
	 * @param     "RReadStream& aStream"
	 *            Read stream from which to read the attribute's value.
	 */
	virtual void ReadAttributeDataFromStreamL(TUid aAttributeUid, RReadStream& aStream)=0;
private:
	IMPORT_C virtual void MFepAttributeStorer_Reserved_1();
	IMPORT_C virtual void MFepAttributeStorer_Reserved_2();
	TInt NumberOfOccurrencesOfAttributeUid(TUid aAttributeUid) const;
	};

class CCoeControl;

/**
 *
 * Abstract base class for all FEPs.
 *
 * FEP authors must derive a class from <code>CCoeFep</code>. The
 * <code>CCoeFep</code>-derived class should implement all of its pure
 * virtual functions including the ones which <code>CCoeFep</code>
 * inherits from its base classes. For information on these functions,
 * see the documentation of the base classes. The global
 * <code>NewFepL()</code> function is used to create a fully initialised
 * object of the derived class. FEPs should own a
 * <code>CCoeControl</code>-derived object — this object is referred to
 * as the FEP control. The FEP control can be placed on the control stack
 * so that it receives key events from the window server. It should run
 * at high priority, so that it receives first refusal of key events.FEPs
 * do not take focus — focus is retained by the underlying application.
 * This has the advantage that the user can see where the output produced
 * by the FEP will be inserted (e.g. the cursor will still be displayed).
 * When focus is switched between controls, the FEP must be notified in
 * case the input capability of the newly focussed control is different.
 * For instance, the FEP needs to avoid the situation where the user
 * composes a large amount of text only for it to be passed to a newly
 * focussed control that cannot accept text input. <code>CCoeFep</code>
 * derives from <code>MCoeFocusObserver</code>, which enables FEPs to
 * receive notification when the focus for the underlying control
 * changes. The implementation of <code>MCoeFocusObserver</code>'s
 * functions can call the enquiry functions of class
 * <code>TCoeInputCapabilities</code> to find out what input capabilities
 * are supported by the new target control (you need to get the
 * <code>TCoeInputCapabilities</code> object from the application UI
 * first: see <code>CCoeAppUi::InputCapabilities()</code>).Note that
 * there can be more than one underlying target control at a time. For
 * instance in an application displaying a dialog, the dialog itself is a
 * focussed control, as is the captioned control, the edit window and
 * other intermediary controls. If a FEP enquires about the input
 * capabilities of such an application (i.e. the merged input
 * capabilities of all its focused controls), it would be returned a
 * <code>TCoeInputCapabilities</code> object whose
 * <code>FepAwareTextEditor()</code> and
 * <code>CaptionRetrieverForFep()</code> member functions return
 * non-NULL, even though these interfaces are implemented by 2 different
 * focused controls.
 *
 * @since 6.0
 * @lib "fepbase.lib"
 */
class CCoeFep : public CBase, protected MFepAttributeStorer, public MCoeForegroundObserver, public MCoeFocusObserver, private MCoeMessageObserver
	{
public:
	/**
	 *
	 * Response to key or pointer event.
	 * @since 
	 */
	enum TEventResponse
		{
		/** Indicates that the FEP did not process the event.
		 */
		EEventWasNotConsumed,
		/** Indicates that the FEP did process the event.
		 */
		EEventWasConsumed
		};
	/**
	 *
	 * Enables FEPs to have some code called but not in the context of the
	 * current call stack hence the name "deferred".
	 *
	 * For an explanation of the intended use of this class, see the
	 * documentation of <code>CCoeFep::MakeDeferredFunctionCall()</code>.
	 *
	 * @since 6.0
	 * @lib "fepbase.lib"
	 */
	class MDeferredFunctionCall
		{
	public:
		/**
		 *
		 * This function is called from within a high-priority active object's
		 * <code>RunL()</code> shortly after the active object has been queued by
		 * calling <code>CCoeFep::MakeDeferredFunctionCall()</code>.
		 *
		 */
		virtual void ExecuteFunctionL()=0;
	private:
		IMPORT_C virtual void MDeferredFunctionCall_Reserved_1();
		IMPORT_C virtual void MDeferredFunctionCall_Reserved_2();
		};
	class MKeyEventQueue // Internal to Symbian
		{
	public:
		virtual void AppendKeyEventL(const TKeyEvent& aKeyEvent)=0;
	private:
		IMPORT_C virtual void MKeyEventQueue_Reserved_1();
		IMPORT_C virtual void MKeyEventQueue_Reserved_2();
		};
	/**
	 *
	 * FEPs send character codes to the application underneath them using
	 * <code>SimulateKeyEventsL()</code>.
	 *
	 * Occasionally a FEP may wish to also specify the modifiers (e.g. Fn,
	 * ctrl, shift) to be sent with that character code. In this case, they
	 * should use the overload of <code>CCoeFep::SimulateKeyEventsL()</code>
	 * which takes an array of <code>MModifiedCharacter</code>s.
	 *
	 * @since 6.0
	 * @lib "fepbase.lib"
	 */
	class MModifiedCharacter
		{
	public:
		/**
		 *
		 * Returns the character code of the key combination.
		 *
		 * @returns   "TUint"
		 *            The character code of the key combination.
		 */
		virtual TUint CharacterCode() const=0;
		virtual TUint ModifierMask() const=0;
		virtual TUint ModifierValues() const=0;
	private:
		IMPORT_C virtual void MModifiedCharacter_Reserved_1();
		IMPORT_C virtual void MModifiedCharacter_Reserved_2();
		};
public:
	IMPORT_C virtual ~CCoeFep();
	IMPORT_C TBool IsSimulatingKeyEvent() const;
	IMPORT_C TBool IsTurnedOnByL(const TKeyEvent& aKeyEvent) const;
	IMPORT_C TBool IsTurnedOffByL(const TKeyEvent& aKeyEvent) const;
	// new public virtual functions
	/**
	 *
	 * Cancels the FEP transaction.
	 *
	 * Pure virtual function.A FEP transaction begins when an event is first
	 * intercepted by the FEP and ends either when the processed text is
	 * committed to the application underneath, or if it is cancelled.
	 *
	 */
	virtual void CancelTransaction()=0;
public: // Internal to Symbian
	// the following functions (and also those of MCoeForegroundObserver) are to be called by applications that do not always have an active-scheduler running, (e.g. OPLR)
	IMPORT_C TEventResponse OfferKeyEvent(TInt& aError, MKeyEventQueue& aKeyEventQueue, const TKeyEvent& aKeyEvent, TEventCode aEventCode);
	IMPORT_C TEventResponse OfferPointerEvent(TInt& aError, MKeyEventQueue& aKeyEventQueue, const TPointerEvent& aPointerEvent, const CCoeControl* aWindowOwningControl);
	IMPORT_C TEventResponse OfferPointerBufferReadyEvent(TInt& aError, MKeyEventQueue& aKeyEventQueue, const CCoeControl* aWindowOwningControl);
	IMPORT_C static TEventResponse OfferEventToActiveScheduler(CCoeFep* aFep, TInt& aError, MKeyEventQueue& aKeyEventQueue, TInt aMinimumPriority); // aFep may be NULL
public: // *** Do not use! API liable to change ***
	IMPORT_C void OnStartingHandlingKeyEvent_WithDownUpFilterLC();
	IMPORT_C void OnStartingHandlingKeyEvent_NoDownUpFilterLC();
	IMPORT_C TKeyResponse OnFinishingHandlingKeyEvent_WithDownUpFilterL(TEventCode aEventCode, const TKeyEvent& aKeyEvent, TKeyResponse aKeyResponse);
	IMPORT_C TKeyResponse OnFinishingHandlingKeyEvent_NoDownUpFilterL(TEventCode aEventCode, const TKeyEvent& aKeyEvent, TKeyResponse aKeyResponse);
protected:
	IMPORT_C CCoeFep(CCoeEnv& aConeEnvironment);
	IMPORT_C void BaseConstructL(const CCoeFepParameters& aFepParameters);
	IMPORT_C void ReadAllAttributesL();
	IMPORT_C void MakeDeferredFunctionCall(MDeferredFunctionCall& aDeferredFunctionCall);
	IMPORT_C void SimulateKeyEventsL(const TArray<TUint>& aArrayOfCharacters);
	IMPORT_C void SimulateKeyEventsL(const TArray<MModifiedCharacter>& aArrayOfModifiedCharacters);
	IMPORT_C void WriteAttributeDataAndBroadcastL(TUid aAttributeUid);
	IMPORT_C void WriteAttributeDataAndBroadcastL(const TArray<TUid>& aAttributeUids);
	IMPORT_C TBool IsOn() const;
private:
	enum {EUndefinedEventResponse=100};
	enum
		{
		EFlagDefaultIsOn		=0x00000001,
		EFlagIsOn				=0x00000002,
		EFlagIsHandlingKeyEvent	=0x00000004,
		EFlagNoDownUpFilter		=0x00000008
		};
	struct SKeyEvent
		{
		TEventCode iEventCode;
		TKeyEvent iKeyEvent;
		TKeyResponse iKeyResponse;
		};
	class CHighPriorityActive;
	class CLowPriorityActive;
private:
	void DoOnStartingHandlingKeyEventLC(TUint aFlagNoDownUpFilter);
	TKeyResponse DoOnFinishingHandlingKeyEventL(TEventCode aEventCode, const TKeyEvent& aKeyEvent, TKeyResponse aKeyResponse);
	static TBool KeyEventMatchesOnOrOffKeyData(const TKeyEvent& aKeyEvent, const TFepOnOrOffKeyData& aOnOrOffKeyData);
	static void TurnOffKeyEventHandlingFlags(TAny* aFlags);
	void DoHandleMessageL(TMessageResponse& aMessageResponse, RReadStream& aStream, TUid aMessageUid);
	// from MFepAttributeStorer
	IMPORT_C virtual void MFepAttributeStorer_Reserved_1();
	IMPORT_C virtual void MFepAttributeStorer_Reserved_2();
	// from MCoeForegroundObserver
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
	// from MCoeFocusObserver
	IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
	IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
	// from MCoeMessageObserver
	IMPORT_C virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
	IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
	// new private virtual functions
	/**
	 *
	 * Called to notify the FEP that it has either just been turned on or
	 * just been turned off (it can find out which by calling
	 * <code>CCoeFep::IsOn()</code>).
	 *
	 * If FEPs want to change their visual appearance when they are off (e.g.
	 * make themselves invisible), then they should implement this function
	 * accordingly.
	 *
	 */
	virtual void IsOnHasChangedState()=0;
	/**
	 *
	 * This function is provided to support FEPs in OPL.
	 *
	 * It is called when a FEP running over an OPL application receives key
	 * events. This function is completely independent from
	 * <code>CCoeControl</code>s virtual function of the same name but should
	 * be implemented in exactly the same way.A number of things should be
	 * done in the implementation of this function:If the type of key event
	 * received is a key up or key down, (<code>EEventKeyUp</code> or
	 * <code>EEventKeyDown</code>), then <code>aEventResponse</code> should
	 * return the same value as it does for the corresponding
	 * <code>EEventKey</code> event.return <code>EEventWasNotConsumed</code>
	 * if the <code>CCoeFep</code> member function
	 * <code>IsSimulatingKeyEvent()</code> returns truereturn
	 * <code>EEventWasNotConsumed</code> if the <code>CCoeFep</code> member
	 * function <code>IsOn()</code> returns falsereturn
	 * <code>EEventWasConsumed</code> to indicate that it did process the key
	 * event if either of <code>CCoeFep</code>s member functions
	 * <code>IsTurnedOnByL()</code> or <code>IsTurnedOffByL()</code> return
	 * trueAfter this has been done, the FEP can do its own processing of the
	 * key event. In general, it is recommended that the implementation of
	 * <code>OfferKeyEventL()</code> should be generous in what gets passed
	 * on to the application when not inside a FEP transaction, and should
	 * block all key events from getting through to the application when it
	 * is inside a FEP transaction.
	 *
	 * @param     "TEventResponse& aEventResponse"
	 *            On return, should be set by the function overriding
	 *            <code>CCoeFep::OfferKeyEventL()</code> to indicate
	 *            whether the key event was consumed or not. Must be set
	 *            to either <code>EEventWasNotConsumed</code> or
	 *            <code>EEventWasConsumed</code> and this must be done
	 *            before any function that can leave is called.
	 *            <code>EEventWasNotConsumed</code> allows the event to
	 *            be passed on to the application and returning
	 *            <code>EEventWasConsumed</code> prevents the event from
	 *            being passed on to the application.
	 * @param     "const TKeyEvent& aKeyEvent"
	 *            The key event.
	 * @param     "TEventCode aEventCode"
	 *            The type of the event: <code>EEventKey</code>,
	 *            <code>EEventKeyUp</code>, or
	 *            <code>EEventKeyDown</code>.
	 */
	virtual void OfferKeyEventL(TEventResponse& aEventResponse, const TKeyEvent& aKeyEvent, TEventCode aEventCode)=0;
	virtual void OfferPointerEventL(TEventResponse& aEventResponse, const TPointerEvent& aPointerEvent, const CCoeControl* aWindowOwningControl)=0;
	virtual void OfferPointerBufferReadyEventL(TEventResponse& aEventResponse, const CCoeControl* aWindowOwningControl)=0;
	IMPORT_C virtual void CCoeFep_Reserved_1();
	IMPORT_C virtual void CCoeFep_Reserved_2();
private:
	CCoeEnv& iConeEnvironment;
	TUint iFlags;
	TFepOnOrOffKeyData iDefaultOnKeyData;
	TFepOnOrOffKeyData iDefaultOffKeyData;
	TFepOnOrOffKeyData iOnKeyData;
	TFepOnOrOffKeyData iOffKeyData;
	CHighPriorityActive* iHighPriorityActive;
	CLowPriorityActive* iLowPriorityActive;
	MKeyEventQueue* iKeyEventQueue; // this pointer does not own anything
	SKeyEvent* iLastKeyEvent;
	};

class CFepFastFileAccessor : public CBase, private MCoeMessageObserver // Internal to Symbian
	{
public: // *** Do not use! API liable to change ***
	class MFileObserver
		{
	public:
		virtual void FileHasChangedL(const TDesC& aFullFileName, const TUint8* aData, TInt aDataLength, TBool aIsRom)=0;
	private:
		IMPORT_C virtual void MFileObserver_Reserved_1();
		IMPORT_C virtual void MFileObserver_Reserved_2();
		};
public: // Internal to Symbian
	inline static CFepFastFileAccessor* NewL(CCoeEnv& aConeEnvironment) {return NewL(aConeEnvironment, NULL);}
	inline static CFepFastFileAccessor* NewL(CCoeEnv& aConeEnvironment, MFileObserver& aFileObserver) {return NewL(aConeEnvironment, &aFileObserver);}
	inline static CFepFastFileAccessor* NewLC(CCoeEnv& aConeEnvironment) {return NewLC(aConeEnvironment, NULL);}
	inline static CFepFastFileAccessor* NewLC(CCoeEnv& aConeEnvironment, MFileObserver& aFileObserver) {return NewLC(aConeEnvironment, &aFileObserver);}
	IMPORT_C virtual ~CFepFastFileAccessor();
	IMPORT_C void AddFileL(const TDesC& aFullFileName);
	IMPORT_C void RemoveFile(const TDesC& aFullFileName);
	inline void GetData(const TDesC& aFullFileName, const TUint8*& aData, TInt& aDataLength) const {GetData(aFullFileName, aData, aDataLength, NULL);}
	inline void GetData(const TDesC& aFullFileName, const TUint8*& aData, TInt& aDataLength, TBool& aIsRom) const {GetData(aFullFileName, aData, aDataLength, &aIsRom);}
	IMPORT_C void FileHasChangedL(const TDesC& aFullFileName);
private:
	enum {EGranularity=5};
	enum {EBroadcastUid=0x1000162a};
	struct SFile
		{
		HBufC* iFullName;
		TBool iIsRom;
		TUint8* iData;
		TInt iDataLength;
		};
private:
	IMPORT_C static CFepFastFileAccessor* NewL(CCoeEnv& aConeEnvironment, MFileObserver* aFileObserver);
	IMPORT_C static CFepFastFileAccessor* NewLC(CCoeEnv& aConeEnvironment, MFileObserver* aFileObserver);
	CFepFastFileAccessor(CCoeEnv& aConeEnvironment, MFileObserver* aFileObserver);
	void ConstructL();
	IMPORT_C void GetData(const TDesC& aFullFileName, const TUint8*& aData, TInt& aDataLength, TBool* aIsRom) const; // exported as it is used by public inline functions
	void LoadNonRomFileL(SFile& aFile);
	void CloseArrayIfEmpty();
	static void CloseFile(SFile& aFile);
	static TBool IsFullFileName(const TDesC& aFileName);
	// from MCoeMessageObserver
	virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
private:
	CCoeEnv& iConeEnvironment;
	TInt iArrayLength;
	SFile* iArrayOfFiles;
	MFileObserver* iFileObserver;
	};

class CFepGlobalDynamicFrequencyTable : public CBase // Internal to Symbian
	{
public: // Internal to Symbian
	typedef TInt (*TCharacterCompareFunction)(TUint aCharacter1, TUint aCharacter2); // returns a negative number if aCharacter1 "comes before" aCharacter2, a positive number if aCharacter2 "comes before" aCharacter1 or zero if they are equivalent
	enum TSortType
		{
		ESortByFrequencyThenByUserDefinedCompareFunction,
		ESortByUserDefinedCompareFunctionThenByFrequency
		};
	class MCharacterArray
		{
	public:
		virtual TInt NumberOfCharacters() const=0;
		virtual TUint CharacterAtIndex(TInt aIndex) const=0;
		virtual void SetCharacterAtIndex(TInt aIndex, TUint aCharacter)=0;
	private:
		IMPORT_C virtual void MCharacterArray_Reserved_1();
		IMPORT_C virtual void MCharacterArray_Reserved_2();
		};
public: // Internal to Symbian
	IMPORT_C static CFepGlobalDynamicFrequencyTable* NewL(TInt aMaximumNumberOfCharacters);
	IMPORT_C static CFepGlobalDynamicFrequencyTable* NewLC(TInt aMaximumNumberOfCharacters);
	IMPORT_C virtual ~CFepGlobalDynamicFrequencyTable();
	IMPORT_C void IncrementFrequencyOfCharacter(TUint aCharacter);
	IMPORT_C void SortL(MCharacterArray& aCharacterArray, TCharacterCompareFunction aUserDefinedCharacterCompareFunction, TSortType aSortType);
	IMPORT_C void Reset();
private:
	struct SFrequencyCountedCharacter
		{
		TUint iCharacter;
		TInt iFrequencyCount;
		};
	struct SGlobalData
		{
		struct SArrayOfCharactersOrderedByAge
			{
			TInt iMaximumCount;
			TInt iCount;
			TInt iIndexOfOldest;
			TInt iOffsetToArray; // offset from the address of the SGlobalData object
			};
		struct SArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding
			{
			TInt iCount;
			TInt iOffsetToArray; // offset from the address of the SGlobalData object
			};
		SArrayOfCharactersOrderedByAge iArrayOfCharactersOrderedByAge;
		SArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding iArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding;
		};
	struct SSortItem
		{
		SFrequencyCountedCharacter iFrequencyCountedCharacter;
		TInt iOriginalIndex;
		};
	typedef TBool (*TFirstParameterComesBeforeSecondFunction)(const SSortItem& aSortItem1, const SSortItem& aSortItem2, TCharacterCompareFunction aUserDefinedCharacterCompareFunction); // returns a non-zero if aSortItem1 "comes before" aSortItem2
private:
	CFepGlobalDynamicFrequencyTable();
	void ConstructL(TInt aMaximumNumberOfCharacters);
	void HeapSort(TInt aNumberOfSortItems, SSortItem* aArrayOfSortItems, TFirstParameterComesBeforeSecondFunction aFirstParameterComesBeforeSecondFunction, TCharacterCompareFunction aUserDefinedCharacterCompareFunction);
	TInt IndexInArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding(TUint aCharacter, TBool& aExists);
	static TBool FirstParameterComesBeforeSecondWhenSortedByFrequencyThenByUserDefinedCompareFunction(const SSortItem& aSortItem1, const SSortItem& aSortItem2, TCharacterCompareFunction aUserDefinedCharacterCompareFunction);
	static TBool FirstParameterComesBeforeSecondWhenSortedByUserDefinedCompareFunctionThenByFrequency(const SSortItem& aSortItem1, const SSortItem& aSortItem2, TCharacterCompareFunction aUserDefinedCharacterCompareFunction);
private:
	RMutex iMutex;
	RChunk iChunk;
	SGlobalData* iGlobalData; // this pointer does not own anything
	TAny* iSpareForFutureUse;
	};

/**
 *
 * Specifies the mixin protocol for handling pointer events in inline
 * text.
 *
 * This class should be overridden by front end processors which support
 * inline editing.An instance of a class which implements this protocol
 * should be passed to
 * <code>MCoeFepAwareTextEditor::StartFepInlineEditL()</code>.
 *
 * @since 6.0
 * @lib ""
 */
class MFepPointerEventHandlerDuringInlineEdit // to be overridden by inline-editing front-end processors
	{
public:
	/**
	 *
	 * This function is called when a pointer event is received within the
	 * inline text.
	 *
	 * It may need to update the cursor position within the inline text and
	 * do text selection in response to drag events.
	 *
	 * @param     "TPointerEvent::TType aType"
	 *            Pointer event types.
	 * @param     "TUint aModifiers"
	 *            Modifier keys (SHIFT, CTRL, FN etc.).
	 * @param     "TInt aPositionInInlineText"
	 *            The position at which the pointer event occurred, as
	 *            an offset from the start of the inline text string.
	 */
	virtual void HandlePointerEventInInlineTextL(TPointerEvent::TType aType, TUint aModifiers, TInt aPositionInInlineText)=0;
private:
	IMPORT_C virtual void MFepPointerEventHandlerDuringInlineEdit_Reserved_1();
	IMPORT_C virtual void MFepPointerEventHandlerDuringInlineEdit_Reserved_2();
	};

class TCharFormat;
class TCursorSelection;
class MFormCustomDraw;
class MFepInlineTextFormatRetriever;
class MCoeFepAwareTextEditor_Extension1;

/**
 *
 * Specifies a protocol for FEP-aware text editors.
 *
 * An implementation of this class is provided by UIKONs
 * <code>CEikEdwin</code> class which is used in text
 * editors.<code>TCoeInputCapabilities::FepAwareTextEditor()</code>
 * returns a pointer to an object of this class. A NULL return value
 * indicates that the interface is not supported by any of the currently
 * focused controls.Inline editing: Inline editing means composing text
 * directly in the target text editorcontrol rather than in the FEP's
 * edit window first. The target text editor must implement the
 * <code>MCoeFepAwareTextEditor</code> interface in order to support
 * inline text. The inline text may be differentiated from the
 * surrounding text by the use of different formatting. These differences
 * are removed when the inline text transaction is committed (causing the
 * inline text to become a real part of the document). Cancelling the
 * inline text transaction deletes the inline text and restores any
 * previously selected text. A benefit of inline editing is that the user
 * only has to concentrate on one area of the screen rather than two. An
 * inline editing transaction consists of the following sequence of
 * function calls:a call to <code>StartFepInlineEditL()</code>zero, one
 * or more calls to <code>UpdateFepInlineTextL()</code>a call to either
 * <code>CommitFepInlineEditL()</code> or
 * <code>CancelFepInlineEdit()</code>
 *
 * @since 6.0
 * @lib "fepbase.lib"
 */
class MCoeFepAwareTextEditor // to be overridden by text-editors
	{
public:
	/**
	 *
	 * Starts a FEP inline editing transaction.
	 *
	 * Inserts a descriptor containing the initial inline text into the text
	 * editor. The inline text should normally replace any selected text.
	 *
	 * @param     "const TDesC& aInitialInlineText"
	 *            The inline text to insert into the text editor.
	 * @param     "TInt aPositionOfInsertionPointInInlineText"
	 *            An insertion position within the inline text. This is
	 *            an offset from the start of the inline text.
	 * @param     "TBool aCursorVisibility"
	 *            <code>ETrue</code> for visible text cursor,
	 *            <code>EFalse</code> for invisible text cursor in the
	 *            text editor.
	 * @param     "const MFormCustomDraw* aCustomDraw"
	 *            Pointer to a custom drawing object. May be used to do
	 *            advanced formatting of the inline text. This parameter
	 *            is optional — a <code>NULL</code> pointer may be
	 *            specified.
	 * @param     "MFepInlineTextFormatRetriever&
					aInlineTextFormatRetriever"
	 *            Defines a single member function,
	 *            <code>GetFormatOfFepInlineText()</code> which is used
	 *            by the text editor to find out the formatting to apply
	 *            to the inline text. It is also possible to apply
	 *            different formatting to different parts of the inline
	 *            text.
	 * @param     "MFepPointerEventHandlerDuringInlineEdit&
					aPointerEventHandlerDuringInlineEdit"
	 *            Defines a single function,
	 *            <code>HandlePointerEventInInlineTextL</code>() which
	 *            is called when a pointer event is received within the
	 *            inline text. This function might update the cursor
	 *            position within the inline text and do text selection.
	 */
	virtual void StartFepInlineEditL(const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit)=0;
	/**
	 *
	 * Updates the inline text.
	 *
	 * Called when a character is added to or deleted from the inline text.
	 *
	 * @param     "const TDesC& aNewInlineText"
	 *            Descriptor which holds the entire new inline text
	 *            string.
	 * @param     "TInt aPositionOfInsertionPointInInlineText"
	 *            The position of the insertion point (i.e. the cursor)
	 *            within the inline text string
	 *            <code>aNewInlineText</code>. This is an offset from
	 *            the start of the string.
	 */
	virtual void UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt aPositionOfInsertionPointInInlineText)=0;
	/**
	 *
	 * Sets the visibility of the text cursor in the text editor.
	 *
	 * @param     "TBool aCursorVisibility"
	 *            <code>ETrue</code> for visible text cursor,
	 *            <code>EFalse</code> for invisible text cursor.
	 */
	virtual void SetInlineEditingCursorVisibilityL(TBool aCursorVisibility)=0;
	/**
	 *
	 * Commits the inline text to the document.
	 *
	 * This function's implementation calls the text editor's implementation
	 * of <code>DoCommitFepInlineEditL()</code> then calls
	 * <code>HandleCompletionOfTransactionL()</code> for each FEP observer
	 * which has been added to the cone environment's FEP observer list (see
	 * <code>CCoeEnv::AddFepObserverL()</code>).
	 *
	 * @param     "CCoeEnv& aConeEnvironment"
	 *            The control's environment.
	 */
	IMPORT_C void CommitFepInlineEditL(CCoeEnv& aConeEnvironment);
	/**
	 *
	 * Cancels the inline editing transaction.
	 *
	 * The edit window should be rolled back to the state it was in before
	 * the FEP transaction started, i.e. any inline text in the document
	 * which has not yet been committed should be removed. If the inline text
	 * has replaced existing text, (e.g. a selection) the replaced text
	 * should be reinstated.
	 *
	 */
	virtual void CancelFepInlineEdit()=0;
	// with regard to the behaviour of the following functions (except GetScreenCoordinatesForFepL), note that when inline editing, the contents of the editor will be such that the text constituting the selection immediately prior to inline editing will be replaced by the inline text (CancelFepInlineEdit reinstates the previous selection)
	/**
	 *
	 * Returns the total number of characters in the text editor.
	 *
	 * @returns   "TInt"
	 *            The total number of characters in the text editor.
	 */
	virtual TInt DocumentLengthForFep() const=0;
	/**
	 *
	 * Returns the upper limit (if any) on the length of text that the text
	 * editor can hold.
	 *
	 * @returns   "TInt"
	 *            The maximum number of characters that the text editor
	 *            can hold.
	 */
	virtual TInt DocumentMaximumLengthForFep() const=0;
	/**
	 *
	 * Sets the range of characters in the text editor which should be
	 * selected.
	 *
	 * @param     "const TCursorSelection& aCursorSelection"
	 *            Contains the cursor and anchor positions for the
	 *            selection.
	 */
	virtual void SetCursorSelectionForFepL(const TCursorSelection& aCursorSelection)=0;
	/**
	 *
	 * Gets the range of characters in the text editor which are selected.
	 *
	 * @param     "TCursorSelection& aCursorSelection"
	 *            On return, contains the cursor and anchor positions of
	 *            the selection.
	 */
	virtual void GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const=0;
	/**
	 *
	 * Copies a portion of the text editor's text content into a descriptor.
	 *
	 * @param     "TDes& aEditorContent"
	 *            A descriptor; on return contains a copy of a portion
	 *            of the text.
	 * @param     "TInt aDocumentPosition"
	 *            The document position in the text editor from which to
	 *            copy.
	 * @param     "TInt aLengthToRetrieve"
	 *            The number of characters to copy.
	 */
	virtual void GetEditorContentForFep(TDes& aEditorContent, TInt aDocumentPosition, TInt aLengthToRetrieve) const=0;
	/**
	 *
	 * Gets the character formatting which applies to the document position
	 * specified.
	 *
	 * This function allows FEPs to find out the ambient formatting so that
	 * the FEP can choose a format for the inline text that will clearly
	 * differentiate it from the surrounding text.
	 *
	 * @param     "TCharFormat& aFormat"
	 *            On return, contains the character formatting which
	 *            applies to the character at
	 *            <code>aDocumentPosition</code>.
	 * @param     "TInt aDocumentPosition"
	 *            The document position of interest.
	 */
	virtual void GetFormatForFep(TCharFormat& aFormat, TInt aDocumentPosition) const=0;
	/**
	 *
	 * Gets the x,y screen coordinates for the left hand side of the baseline
	 * of the character located at a specified document position.
	 *
	 * Also gets the height (ascent + descent) and ascent of the font of the
	 * character. This function could be used to position the FEP window as
	 * close as possible to the insertion point in the text editor.
	 *
	 * @param     "TPoint& aLeftSideOfBaseLine"
	 *            On return, contains the x,y coordinates of the left
	 *            side of the baseline of the character located at
	 *            <code>aDocumentPosition</code>.
	 * @param     "TInt& aHeight"
	 *            On return, contains the height (ascent + descent) of
	 *            the font of the character at
	 *            <code>aDocumentPosition</code>.
	 * @param     "TInt& aAscent"
	 *            On return, contains the ascent of the font of the
	 *            character at <code>aDocumentPosition</code>.
	 * @param     "TInt aDocumentPosition"
	 *            The document position of interest.
	 */
	virtual void GetScreenCoordinatesForFepL(TPoint& aLeftSideOfBaseLine, TInt& aHeight, TInt& aAscent, TInt aDocumentPosition) const=0;
	/**
	 *
	 * Returns a pointer to an instance of the interface class
	 * <code>MCoeFepAwareTextEditor_Extension1</code>, or NULL, if the
	 * interface is not supported.
	 *
	 * Calls the private virtual function of the same name.
	 *
	 * @since     6.1
	 * @returns   "MCoeFepAwareTextEditor_Extension1*"
	 *            A pointer to an instance of the interface class
	 *            <code>MCoeFepAwareTextEditor_Extension1</code>, or
	 *            NULL, if the interface is not supported.
	 */
	IMPORT_C MCoeFepAwareTextEditor_Extension1* Extension1();
private:
	/**
	 *
	 * Private function called by <code>CommitFepInlineEditL()</code>.
	 *
	 * Implementations should commit the inline text to the document. This
	 * ends the inline editing transaction and causes the inline text to
	 * become a "real" part of the document.
	 *
	 */
	virtual void DoCommitFepInlineEditL()=0;
	IMPORT_C virtual MCoeFepAwareTextEditor_Extension1* Extension1(TBool& aSetToTrue);
	IMPORT_C virtual void MCoeFepAwareTextEditor_Reserved_2();
	};

/**
 *
 * An interface class which may be derived from by text editors to enable
 * FEPs to store state information inside the editor.
 *
 * The <code>CState</code> class, defined within the scope of
 * <code>MCoeFepAwareTextEditor_Extension1</code> represents the state
 * information. This is information specific to the control which is only
 * of interest to the FEP.A class which implements this interface must
 * implement the pure virtual functions <code>State()</code> and
 * <code>SetStateTransferingOwnershipL()</code>, to get and set the
 * state. The class should also implement the
 * <code>MCoeFepAwareTextEditor</code> interface. It must override the
 * private virtual <code>MCoeFepAwareTextEditor::Extension1()</code> to
 * return a pointer to itself (the default implementation returns NULL).
 * The private virtual <code>MCoeFepAwareTextEditor::Extension1()</code>
 * function is called by the public, non-virtual
 * <code>MCoeFepAwareTextEditor::Extension1()</code> function.For
 * example, if a FEP wants to set some state information in a text editor
 * which is about to lose focus, the FEP should first call the editor's
 * <code>Extension1()</code> function. If this returns non-NULL, the FEP
 * should call the editor's implementation of
 * <code>SetStateTransferingOwnershipL()</code>, passing in an object of
 * a class derived from <code>CState</code>, which holds the state
 * information. It should also pass in a UID which uniquely identifies
 * the FEP. Later, when focus returns to the editor, the FEP can call
 * <code>State()</code> to retrieve the state information it previously
 * set. Note that <code>CState</code> has several reserved functions, to
 * enable it to be extended in future, while retaining backwards
 * compatibility.
 *
 * @since 6.1
 * @lib "fepbase.lib"
 */
class MCoeFepAwareTextEditor_Extension1 // to be overridden by text-editors
	{
public:
	/**
	 *
	 * State information for a text editor control.
	 *
	 * This is information specific to the control which is only of interest
	 * to the FEP which sets it.
	 *
	 * @lib "fepbase.lib"
	 */
	class CState : public CBase
		{
	protected:
		IMPORT_C CState();
		IMPORT_C void BaseConstructL();
	public:
		IMPORT_C virtual ~CState();
	private:
		IMPORT_C virtual void CState_Reserved_1();
		IMPORT_C virtual void CState_Reserved_2();
		IMPORT_C virtual void CState_Reserved_3();
		IMPORT_C virtual void CState_Reserved_4();
	private:
		TAny* iSpareForFutureUse;
		};
public:
	/**
	 *
	 * Sets state information in the text editor.
	 *
	 * This function must only transfer ownership of the state object after
	 * it has successfully done everything that can leave.
	 *
	 * @param     "CState* aState"
	 *            Pointer to the state information object.
	 * @param     "TUid aTypeSafetyUid"
	 *            A UID which uniquely identifies the FEP which is
	 *            calling this function. The text editor should store
	 *            this value for use by the <code>State()</code>
	 *            function.
	 */
	virtual void SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid)=0; // this function must only transfer ownership after it has successfully done everything that can leave
	/**
	 *
	 * Gets the state information previously set using
	 * <code>SetStateTransferingOwnershipL()</code>.
	 *
	 * This function does not transfer ownership. The function should first
	 * check that <code>aTypeSafetyUid</code> matches the UID value
	 * previously specified by <code>SetStateTransferingOwnershipL()</code>.
	 * If it doesn't match, the function should return NULL.
	 *
	 * @param     "TUid aTypeSafetyUid"
	 *            A UID which uniquely identifies the FEP which is
	 *            calling this function. The purpose of this is to
	 *            enable the FEP to safely downcast the
	 *            <code>CState</code> pointer returned by this function
	 *            to a pointer to a derived class known about by the
	 *            FEP.
	 * @returns   "CState*"
	 *            Pointer to the state information object.
	 */
	virtual CState* State(TUid aTypeSafetyUid)=0; // this function does *not* transfer ownership
public:
	/**
	 *
	 * Starts a FEP inline editing transaction.
	 *
	 * Before starting the transaction, sets the range of characters in the
	 * text editor which should be selected using <code>aCursorSelection</code>,
	 * without visually highlighting the selected characters.
	 *
	 * This method can be used to avoid flicker when selecting a range of characters
	 * followed by starting a FEP inline editing transaction.
	 *
	 * Inserts a descriptor containing the initial inline text into the text
	 * editor. The inline text should normally replace any selected text.
	 *
	 * @param     "TBool& aSetToTrue"
	 *            The implementor of this method must set
	 *            <code>aSetToTrue</code> to <code>ETrue</code>
	 * @param     "const TCursorSelection& aCursorSelection"
	 *            Contains the cursor and anchor positions for the
	 *            selection.
	 * @param     "const TDesC& aInitialInlineText"
	 *            The inline text to insert into the text editor.
	 * @param     "TInt aPositionOfInsertionPointInInlineText"
	 *            An insertion position within the inline text. This is
	 *            an offset from the start of the inline text.
	 * @param     "TBool aCursorVisibility"
	 *            <code>ETrue</code> for visible text cursor,
	 *            <code>EFalse</code> for invisible text cursor in the
	 *            text editor.
	 * @param     "const MFormCustomDraw* aCustomDraw"
	 *            Pointer to a custom drawing object. May be used to do
	 *            advanced formatting of the inline text. This parameter
	 *            is optional — a <code>NULL</code> pointer may be
	 *            specified.
	 * @param     "MFepInlineTextFormatRetriever&
					aInlineTextFormatRetriever"
	 *            Defines a single member function,
	 *            <code>GetFormatOfFepInlineText()</code> which is used
	 *            by the text editor to find out the formatting to apply
	 *            to the inline text. It is also possible to apply
	 *            different formatting to different parts of the inline
	 *            text.
	 * @param     "MFepPointerEventHandlerDuringInlineEdit&
					aPointerEventHandlerDuringInlineEdit"
	 *            Defines a single function,
	 *            <code>HandlePointerEventInInlineTextL</code>() which
	 *            is called when a pointer event is received within the
	 *            inline text. This function might update the cursor
	 *            position within the inline text and do text selection.
	 */
	IMPORT_C virtual void StartFepInlineEditL(TBool& aSetToTrue, const TCursorSelection& aCursorSelection, const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
	IMPORT_C virtual void SetCursorType(TBool& aSetToTrue, const TTextCursor& aTextCursor);
private:
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();
	};

/**
 *
 * Retrieves a control's caption for use by a FEP.
 *
 * An example of a caption is the non-editable text description displayed
 * alongside each item in a
 * dialog.<code>TCoeInputCapabilities::CaptionRetrieverForFep()</code>
 * returns a pointer to an object of this class. A NULL return value
 * indicates that the interface is not supported by any of the currently
 * focused controls. If not NULL, call <code>GetCaptionForFep()</code>,
 * which fills the supplied buffer with the control's caption, truncating
 * it if the supplied buffer is too small for the whole caption.
 *
 * @since 6.0
 * @lib "fepbase.lib"
 */
class MCoeCaptionRetrieverForFep // to be overridden by captioned-controls
	{
public:
	/**
	 *
	 * An implementation of this function should fill <code>aCaption</code>
	 * with the target control's caption (or as much of the caption as will
	 * fit).
	 *
	 * ExampleCode similar to the following might be used (assuming that your
	 * caption is stored internally in <code>iCaption</code>):
	 *
	 * @param     "TDes& aCaption"
	 *            On return, this should be set to the caption of the
	 *            target control.
	 */
	virtual void GetCaptionForFep(TDes& aCaption) const=0; // gets as much as will fit in aCaption
private:
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_1();
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_2();
	};

#endif

