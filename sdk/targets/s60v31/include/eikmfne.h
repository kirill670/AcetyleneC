// EIKMFNE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMFNE_H__)
#define __EIKMFNE_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

// For MEikCalendarObserver
#if !defined(__EIKCAL_H__)
#include <eikcal.h>	
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__BABITFLAGS_H__)
#include <babitflags.h>
#endif

// For MAknMfneCommandObserver
#if !defined(__AKNMFNECOMMANDOBSERVER)
#include <AknMfneCommandObserver.h>
//!defined(__AKNMFNECOMMANDOBSERVER)
#endif

//
// Forward Declarations
//
class CEikonEnv;
class CTimeEditor;
class CDateEditor;

// Skin-related API forward declarations
class MAknsControlContext;

// Extension object within CEikMfne
class CEikMfneExtension;

//

class CEikMfneField : public CBase
	{
public:
	enum THighlightType
		{
		EInverseVideo,
		ECursor
		};
protected:
	IMPORT_C CEikMfneField();
public:
	void Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft) const;
	TInt WidthInPixels(const CFont& aFont) const;
	TInt DistanceFromStartOfFieldToEndOfTextInPixels(const CFont& aFont) const;
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize)=0;
	virtual TCoeInputCapabilities InputCapabilities() const=0;
	IMPORT_C virtual TBool IsEditable() const;
	IMPORT_C virtual TBool IsValid() const;
	// these functions may only be called if IsEditable returns ETrue - all TBool&/TInt& parameters in these functions must be first set to EFalse/0 by the caller
	IMPORT_C virtual THighlightType HighlightType() const;
	IMPORT_C virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	IMPORT_C virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
protected:
	IMPORT_C void HandleLeftOrRightArrow(TChar aKey, TBool& aDataAltered, TInt& aHighlightIncrement);
    TInt AdditionalWidthForHighlights(const CFont& aFont) const;
private:
	virtual const TDesC& Text() const=0;
protected:
	TInt iMinimumWidthInPixels;
	};

//

NONSHARABLE_CLASS(CEikMfneSeparator) : public CEikMfneField
	{
private:
	CEikMfneSeparator(HBufC* aText);
public:
	IMPORT_C virtual ~CEikMfneSeparator();
	IMPORT_C static CEikMfneSeparator* NewL(TResourceReader& aResourceReader);
	IMPORT_C static CEikMfneSeparator* NewL(HBufC* aText); // ownership of aText is transferred when everything that can leave has successfully been done
	IMPORT_C void SetText(HBufC* aText); // allows later transfer of ownership of text - can only be called if aText was previously NULL
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual const TDesC& Text() const;
private:
	HBufC* iText;
	};

//

NONSHARABLE_CLASS(CEikMfneNumber) : public CEikMfneField
	{
public:
	enum
		{
		EFillWithLeadingZeros			=0x1,
		EPreserveOldWidthBeforeEditing	=0x2,
		ERepresentsYear					=0x4,
		EPublicallySettableFlags		=EFillWithLeadingZeros|EPreserveOldWidthBeforeEditing|ERepresentsYear
		};
private:
	enum
		{
		EIsBeingEditedWithCursor		=0x8,
		EIsUninitialised				=0x10,
		EFillWithTrailingZeros          =0x20
		};
private:
	CEikMfneNumber(TInt aMinimumValue, TInt aMaximumValue, TUint32 aFlags);
	void ConstructL();
public:
	IMPORT_C virtual ~CEikMfneNumber();
	IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TResourceReader& aResourceReader);
	IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue, const CFont& aFont); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	IMPORT_C void SetValue(TInt aValue, const CFont& aFont);
	IMPORT_C TInt Value() const;
	IMPORT_C virtual TBool IsValid() const;

	IMPORT_C void SetUninitialised(TBool aUninitialised);
	IMPORT_C TBool IsUninitialised() const;

public:
    /**
     * Sets the digit display type.
     *
     * @since S60 v3.1
     * @param aDigitType The digit display type to bet set for this number field
     * @param aFont The font of the MFNE that owns this field, usually retrieved with CEikMfne::Font()
     */
	IMPORT_C void SetDigitType(TDigitType aDigitType, const CFont& aFont);

    /**
     * Gets the digit display type.
     *
     * @since S60 v3.1
     * @return The digit display type of this number field
     */
	IMPORT_C TDigitType DigitType() const;

	/**
	 * Derive and set digit display type from locale information.
	 *
	 * @since S60 v3.1
	 * @param aFont The font of the MFNE that owns this field, usually retrieved with CEikMfne::Font()
	 */
	IMPORT_C void RefreshDigitType(const CFont& aFont);
	
	void SetTrailingZeros();

public:
	TBool IsTextNull() const;
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual TBool IsEditable() const;
	virtual THighlightType HighlightType() const;
	virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	virtual const TDesC& Text() const;
private:
	TInt MaximumNumberOfDigits() const;
	TInt NumberOfDigits() const;
	void SetTextToValue(TInt aValue, const CFont& aFont);
	TInt ValueFromText() const;
	TBool ConvertsIntoValidValue(TInt& aValue) const;

private: // International digit support
	TChar NormalizeDigit(TChar aChar);
	TText ZeroCharacter() const;
	TText NegativeCharacter() const;

private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iMaxDigits;
	TUint32 iFlags;
	HBufC* iText;
	TChar iNudgeCharMinus;
	TChar iNudgeCharPlus;
	TInt iMaxDigitsMinimumValue;
    TInt iMaxDigitsMaximumValue;
	TDigitType	iDigitType;
	};

//

NONSHARABLE_CLASS(CEikMfneSymbol) : public CEikMfneField
	{
public:
	NONSHARABLE_CLASS(CItem) : public CBase
		{
	private:
		CItem(TInt aId, TChar aKeyToMatch, HBufC* aText);
	public:
		IMPORT_C virtual ~CItem();
		IMPORT_C static CItem* NewL(TResourceReader& aResourceReader);
		IMPORT_C static CItem* NewL(TInt aId, TChar aKeyToMatch, HBufC* aText); // ownership of aText is transferred when everything that can leave has successfully been done
		IMPORT_C void SetText(HBufC* aText); // allows later transfer of ownership of text - can only be called if aText was previously NULL
	private:
		friend class CEikMfneSymbol;
	private:
		TInt iId;
		TCharF iKeyToMatch;
		HBufC* iText;
		};
private:
	CEikMfneSymbol(TInt aNumSymbolicItems);
public:
	IMPORT_C virtual ~CEikMfneSymbol();
	IMPORT_C static CEikMfneSymbol* NewL(TResourceReader& aResourceReader);
	IMPORT_C static CEikMfneSymbol* NewL(TInt aNumSymbolicItems);
	IMPORT_C void AddSymbolicItem(CItem* aSymbolicItem, TBool aMakeCurrent); // to be called by container only if not constructed from resource - ownership of aSymbolicItem is transferred to "this"
	IMPORT_C void SetCurrentSymbolicItemToId(TInt aId);
	IMPORT_C TInt IdOfCurrentSymbolicItem() const;
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	IMPORT_C TBool IsUninitialised() const;
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual TBool IsEditable() const;
	virtual THighlightType HighlightType() const;
	virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	virtual const TDesC& Text() const;
private:
	TInt CurrentSymbolicItem() const;
	void SetCurrentSymbolicItem(TInt aCurrentSymbolicItem);
private:
	TInt iNumSymbolicItems;
	TInt iCurrentSymbolicItem;
	CItem** iSymbolicItems;
	};

//

class CEikMfne : public CEikBorderedControl, public MAknMfneCommandObserver
	{
public:
	// miscellaneous functions
	IMPORT_C CEikMfne();
	IMPORT_C virtual ~CEikMfne();
	IMPORT_C void CreateFieldArrayL(TInt aNumFields); // to be called by container only if not constructed from resource
	IMPORT_C void AddField(CEikMfneField* aField); // to be called by container only if not constructed from resource - ownership of aField is transferred to "this"
	IMPORT_C TMargins BorderMargins() const;
	IMPORT_C void DrawNowAndLeaveWithTimeDateFormatInfoMsgL(TInt aResourceId, const TTime& aTimeDate) const;
	IMPORT_C CEikMfneField* Field(TInt aField) const;
public:
	// some utility functions which other classes may find useful
	IMPORT_C static TTime ReadTime(TResourceReader& aResourceReader);
	IMPORT_C static TTime ReadDate(TResourceReader& aResourceReader);
	IMPORT_C static TTime ReadTimeAndDate(TResourceReader& aResourceReader);
	IMPORT_C static TTimeIntervalSeconds ReadDuration(TResourceReader& aResourceReader);
	IMPORT_C static TTimeIntervalSeconds ReadTimeOffset(TResourceReader& aResourceReader);
	IMPORT_C static TTimeIntervalSeconds Convert(const TTime& aTime);
	IMPORT_C static TTime Convert(const TTimeIntervalSeconds& aTimeIntervalSeconds);
    //
    inline TInt CurrentField() const;
    inline TInt NumFields() const;

public: // AVKON addition
    IMPORT_C void SetMfneAlignment(TInt aAlignment);
    IMPORT_C void SetUpAndDownKeysConsumed(TBool aConsume);
    /**
    * Used for suppressing all editor's background drawing. This is
    * intended for internal use.
    *
    * Note that when this is set, the background is not drawn with skin
    * nor cleared, so the background MUST be drawn by the parent control
    * every time the editor changes.
    *
    * @param aSuppress If ETrue, suppress background drawing
    */
    IMPORT_C void SetSuppressBackgroundDrawing( TBool aSuppress );

    // Highlights a field
    void HighlightField(  TInt aFieldPosition );

	IMPORT_C const CFont* Font() const;
	IMPORT_C void SetFont(const CFont* aFont);

    /**
    * Sets within in the editor an externally owned Skins background control context.
    * This background control context will then be used by the editor to draw background.
    *
    * If this API is not called, then the editor IS skin enabled, (that is CEikMfnes are skin
    * enabled by default) but it will try to find a control context with which to perform background 
    * drawing from the Control Environment, via the Object Provider.
    *
    * Setting this control context to NULL will have the effect of turning off background 
    * skinning. 
    *
    * @param aBackgroundControlContext   Control context to store. Not owned. Can be NULL
    */
    IMPORT_C void SetSkinBackgroundControlContextL( MAknsControlContext* aControlContext );
    
    
    /**
    * From MAknMfneCommandObserver. Allows owning controls to give commands to 
    * MFNE editors. This is interface was added to enable modifying the current field
    * value with touch buttons.
    *
    * @param aCommand Command ID defined in MAknMfneCommandObserver::TMfneCommand
    */
    IMPORT_C void HandleMfneCommandL(TInt aCommand);


public:	// from CCoeControl
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C virtual void PrepareForFocusLossL();
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

public: // new 
    /**
    * @since 3.0
    * Please note that bgcolor overrides skinned draw if set
    **/
    IMPORT_C void SetSkinTextColorL(TInt aAknSkinIDForTextColor, TInt aAknSkinIDForBgColor=KErrNotFound);

protected:
	// framework
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	// miscellaneous functions
	IMPORT_C void HandleInteraction(TBool aHandleDeHighlight, TInt aNewCurrentField, TInt aOldWidthInPixelsOfOldCurrentField,
								CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, TBool& aDataAltered, TBool& aError);
	IMPORT_C virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields); // first occurrence of this virtual function - does nothing by default
	IMPORT_C TSize MfneSize() const;
	IMPORT_C TSize MfneSize(TBool aShrinkToMinimumSize);

public:
	static void InvalidFieldAlert();
	static void LeaveWithAlert(TInt aResourceId);

private:
	// framework
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	// new virtual functions
	IMPORT_C virtual void CreatePopoutIfRequiredL();
	// miscellaneous functions
	void DrawRange(CWindowGc& aGc, TInt aFirstField, TInt aLastField) const;
	CWindowGc& PreparedGc() const;
	void SetGcToNormalVideo(CWindowGc& aGc) const;
	void SetGcToInverseVideo(CWindowGc& aGc) const;
	void SetGcToDimmedVideo(CWindowGc& aGc) const;
	void DrawCursor();
	void HideCursor();
	IMPORT_C void Reserved_2();
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
	enum {ENullIndex=KMaxTInt};

	/**
	* Access to state of whether up/down keys are eaten and used to increment/decrement.  If
	* these keys are not consumed, then the events are passed on.
	* 
	* @return EFalse iff Up and Down keys are not consumed (and acted upon)
	*/
	TBool ConsumesUpAndDownKeys() const;

	/**
	* This state of enabling means that skinning will actually be drawn
	* It is a combination of 
	* - application is skin enabled
	* - current skin has a background or frame bitmap
	* It is set during construction and does not change its value after except if the Skin is 
	* changed, whereupon the control context is re-accessed and checked for bitmaps present
	*
	* @return EFalse iff background skin will not be drawn.
	*/
	TBool SkinningBackground() const;

	/** 
	* Checks if app is skin enabled and that the current control context has bitmap. 
	* If so, then state is set true.
	* This should be called at constuction and when HandleResourceChange is called
	*
	*/ 
	void EvaluateSkinningBackground(); 

    /**
    * Access to Skins background control context that is potentially being used by the Editor.
    *
    * This API will first check to see if an control context has been set by API, and if so, 
    * return that.  If the background control context has been set to NULL by API, then it will
    * return NULL. If the background control context has never been set by API, then this returns
    * the control context (if one exists) that the object obtains from Object Provider.
    * 
    * @return Pointer to control context potentially in use, or NULL.
    */
    MAknsControlContext* SkinBackgroundControlContext() const;

    /**
    * Check for the extistence of the extension and create if required
    */
    void CreateExtensionIfRequiredL();

private:
	TInt iNumFields;
	TInt iCurrentField;
	CEikMfneField** iFields;
	CEikMfneExtension* iExtension;
	const CFont* iFont;
    TInt iAlignment;
    TBitFlags iFlags;
	};

inline TInt CEikMfne::CurrentField() const
    {
    return(iCurrentField);
    }

inline TInt CEikMfne::NumFields() const
    {
    return(iNumFields);
    }

//

class CEikNumberEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikNumberEditor();
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue); // to be called by container only if not constructed from resource
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	IMPORT_C void SetNumber(TInt aNumber);
	IMPORT_C TInt Number() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	IMPORT_C virtual void CEikMfne_Reserved();
private:
	void RefreshFromLocale();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	// none of these pointers owns anything
	CEikMfneNumber* iNumber;
	TInt iSpare;
	};


//

struct SEikRange
	{
	TInt iLowerLimit;
	TInt iUpperLimit;
	};

//

class CEikRangeEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikRangeEditor();
	// ConstructL to be called by container only if not constructed from resource, also ownership of aSeparatorText is transferred when everything that can leave has successfully been done
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, const SEikRange& aInitialRange, HBufC* aSeparatorText);
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	IMPORT_C void SetRange(const SEikRange& aRange);
	IMPORT_C SEikRange Range() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
	virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields);
	IMPORT_C virtual void CEikMfne_Reserved();
	void RefreshFromLocale();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	// none of these pointers owns anything
	CEikMfneNumber* iLowerLimit;
	CEikMfneNumber* iUpperLimit;
	TInt iSpare;
	};


//

class CEikTTimeEditor : public CEikMfne
	{
public:
	virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime)=0;
	virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximum) const=0;
	virtual void SetTTime(const TTime& aTime)=0;
	virtual TTime GetTTime() const=0; // can only be called if PrepareForFocusLossL() succeeded
	};


class CEikTimeEditor : public CEikTTimeEditor
	{
public:
	// miscellaneous functions
	IMPORT_C CEikTimeEditor();
	IMPORT_C virtual ~CEikTimeEditor();
	IMPORT_C void ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags); // to be called by container only if not constructed from resource
	IMPORT_C void SetTime(const TTime& aTime);
	IMPORT_C TTime Time() const;
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	IMPORT_C TBool IsUninitialised() const;
	// from CEikTTimeEditor
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial minimum and maximum are permitted
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximumTime) const;
	// from CCoeControl
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C virtual void PrepareForFocusLossL();
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aTime);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	TTime iMinimumTime;
	TTime iMaximumTime;
	TInt iSpare;
	};


//

// note: TDateTime uses zero based day numbers, so -1 on the day field
#define KAknMinimumDate (TTime(TDateTime(0001, EJanuary, 1-1, 0, 0, 0, 0)))
#define KAknMaximumDate (TTime(TDateTime(9999, EDecember, 31-1, 23, 59, 59, 999999)))

/**
 * Date editor.
 *
 * A date editor has five fields: day, month and year, and two separator 
 * characters. The order of the fields varies depending on the locale's 
 * date format setting. Locale information, which is set and retrieved using 
 * class @c TLocale, is used to determine field order and the characters used 
 * to separate the date components. The upper and lower field bounds are set, 
 * and dates outside these bounds are invalid.
 *
 * The editor can be configured to launch a pop-out calendar dialog, 
 * @c CEikCalendar. This may be used to directly set the day, month and year 
 * values. 
 *
 * The editor has an associated resource struct @c DATE_EDITOR and control 
 * factory identifier @c EEikCtDateEditor.
 *
 */
class CEikDateEditor : public CEikTTimeEditor, private MEikCalendarObserver
	{

public:

    // miscellaneous functions
    /**
     * C++ default constructor.
     */
    IMPORT_C CEikDateEditor();

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CEikDateEditor();

    // to be called by container only if not constructed from resource
    /**
     * Handles 2nd phase construction.
     *
     * This function completes the construction of a newly-allocated date 
     * editor. This function should be used instead of 
     * @c ConstructFromResourceL() when not initialising from a resource file.
     * The editor's minimum, maximum and initial date values are set and the 
     * date format and date separator characters specified in class @c TLocale
     * are honoured.
     * 
     * @param aMinimumDate The minimum allowable date.
     * @param aMaximumDate The maximum allowable date.
     * @param aInitialDate The initial value.
     * @param aWithoutPopoutCalendar If @c ETrue the editor will not have a 
     *        pop-out calendar dialog / icon. If @c EFalse the editor will have
     *        a pop-out calendar dialog / icon.
     */
    IMPORT_C void ConstructL(const TTime& aMinimumDate, 
                             const TTime& aMaximumDate, 
                             const TTime& aInitialDate, 
                             TBool aWithoutPopoutCalendar); 
    
    /**
     * Sets the date editor's value.
     * 
     * @param aDate The editor's value. Time components are ignored.
     */
    IMPORT_C void SetDate(const TTime& aDate);

    /**
     * Gets the date editor's value.
     *
     * @return The editor's date value.
     */
	IMPORT_C TTime Date() const;

    /**
     * Sets date editor to initialised or uninitialised.
     * 
     * @param aUninitialised If @c ETrue then the date editor is set 
     *        to be uninitialised.
     */
	IMPORT_C void SetUninitialised(TBool aUninitialised);

    /**
     * Tests whether the editor is uninitialised.
     * 
     * @return @c ETrue if uninitialised.
     */
	IMPORT_C TBool IsUninitialised() const;

	// from CEikTTimeEditor
	// only values inside the initial minimum and maximum are permitted
    /**
     * From @c CEikTTimeEditor.
     * 
     * Sets the minimum and maximum allowable dates.
     *
     * If the current date is outside the new bounds it is changed to be within
     * them.
     *
     * @param aMinimumDate The minimum allowable value.
     * @param aMaximumDate The maximum allowable value.
     */
    IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumDate, 
                                               const TTime& aMaximumDate); 
    	
    /**
     * From @c CEikTTimeEditor.
     *
     * Gets the date editor's minimum and maximum values.
     *
     * @param aMinimumDate On return, the minimum allowable value.
     * @param aMaximumDate On return, the maximum allowable value.
     */
    IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumDate, 
                                               TTime& aMaximumDate) const;
	
    // from CCoeControl
    /**
     * From @c CCoeControl.
     *
     * Handles key events.
     *
     * @param aKeyEvent The key event.
     * @param aType The type of key event.
     * @return @c EKeyConsumed if the key has beend handled. 
     */
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, 
                                                 TEventCode aType);
	
    /**
     * From @c CCoeControl.
     * 
     * Second-phase construction from a resource file.
     *
     * The function reads the maximum and minimum date values and whether 
     * or not the editor should support a pop-out calendar and/or date icon 
     * from a @c DATE_EDITOR resource. It sets the initial date to be the same 
     * as the maximum date and honours the locale's date format and separators.
     * 
     * @param aResourceReader A resource file reader.
     */
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& 
                                                 aResourceReader);
	
    /**
     * From @c CCoeControl.
     * 
     * Editor validation.
     *
     * This function should be called before an attempt is made to remove focus
     * from a date editor. If the control value is not within the bounds 
     * specified by the minimum and maximum date values, it is reset to the 
     * nearest allowable value, the function then leaves and displays an 
     * appropriate message.
     */
    IMPORT_C virtual void PrepareForFocusLossL();
    
    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:

    // from CEikMfne
    virtual void CreatePopoutIfRequiredL();
    // from CEikTTimeEditor
    virtual void SetTTime(const TTime& aDate);
    virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded

private:

    // from MEikCalendarDialogObserver
    virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, 
                                                                 TTime& aMaximumDate, 
                                                                 TTime& aInitialDate) const;
    virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
    // miscellaneous functions
    void DoSetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate);
    IMPORT_C virtual void CEikMfne_Reserved();

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:

	CDateEditor* iDateEditor;
	TTime iMinimumDate;
	TTime iMaximumDate;
	TInt iSpare;
	};


//

class CEikTimeAndDateEditor : public CEikTTimeEditor, private MEikCalendarObserver
	{
public:
	// miscellaneous functions
	IMPORT_C CEikTimeAndDateEditor();
	IMPORT_C virtual ~CEikTimeAndDateEditor();
	// ConstructL to be called by container only if not constructed from resource, also ownership of aInterveningText is transferred when everything that can leave has successfully been done
	IMPORT_C void ConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate, const TTime& aInitialTimeAndDate, TUint32 aFlags, HBufC* aInterveningText=NULL);
	IMPORT_C void SetTimeAndDate(const TTime& aTimeAndDate);
	IMPORT_C TTime TimeAndDate() const;
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	IMPORT_C TBool IsUninitialised() const;
	// from CEikTTimeEditor
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate); // only values inside the initial minimum and maximum are permitted
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTimeAndDate, TTime& aMaximumTimeAndDate) const;
	// from CCoeControl
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C virtual void PrepareForFocusLossL();
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	// from CEikMfne
	virtual void CreatePopoutIfRequiredL();	
	IMPORT_C virtual void CEikMfne_Reserved();
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aTimeAndDate);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// from MEikCalendarDialogObserver
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	CDateEditor* iDateEditor;
	TTime iMinimumTimeAndDate;
	TTime iMaximumTimeAndDate;
	TInt iSpare;
	};


//

class CEikDurationEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikDurationEditor();
	IMPORT_C virtual ~CEikDurationEditor();
	IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration, const TTimeIntervalSeconds& aInitialDuration, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumDuration, TTimeIntervalSeconds& aMaximumDuration) const;
	IMPORT_C void SetDuration(const TTimeIntervalSeconds& aDuration);
	IMPORT_C TTimeIntervalSeconds Duration() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C void PrepareForFocusLossL();
    // From CCoeControl    
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	TTimeIntervalSeconds iMinimumDuration;
	TTimeIntervalSeconds iMaximumDuration;
	TInt iSpare;
	};


class CEikTimeOffsetEditor : public CEikMfne
	{
public:
	// miscellaneous functions
	IMPORT_C CEikTimeOffsetEditor();
	IMPORT_C virtual ~CEikTimeOffsetEditor();
	IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset, const TTimeIntervalSeconds& aInitialTimeOffset, TUint32 aFlags);
	IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial minimum and maximum are permitted
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumTimeOffset, TTimeIntervalSeconds& aMaximumTimeOffset) const;
	IMPORT_C void SetTimeOffset(const TTimeIntervalSeconds& aTimeOffset);
	IMPORT_C TTimeIntervalSeconds TimeOffset() const; // can only be called if PrepareForFocusLossL() succeeded
	// framework
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C void PrepareForFocusLossL();
    // From CCoeControl    
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	TTimeIntervalSeconds iMinimumTimeOffset;
	TTimeIntervalSeconds iMaximumTimeOffset;
	// none of these pointers owns anything
	CEikMfneSymbol* iSign;
	TInt iSpare;
	};




//
// Longitude and Latitude editors removed 2.4.2002:

enum
	{
	EEikOrientationNorthSouth   =0x1000,
	EEikOrientationWestEast     =0x2000,
	EEikOrientationMask=EEikOrientationNorthSouth|EEikOrientationWestEast
	};


enum
	{
	EEikDirectionNegative,
	EEikDirectionPositive,
	EEikDirectionMask=EEikDirectionNegative|EEikDirectionPositive
	};


enum TEikCompass
	{
	EEikCompassNorth=EEikOrientationNorthSouth|EEikDirectionNegative,
	EEikCompassSouth=EEikOrientationNorthSouth|EEikDirectionPositive,
	EEikCompassEast=EEikOrientationWestEast|EEikDirectionNegative,
	EEikCompassWest=EEikOrientationWestEast|EEikDirectionPositive
	};


struct SEikDegreesMinutesDirection
	{
	TInt iDegrees;
	TInt iMinutes;
	TInt iSeconds;
	TEikCompass iDirection;
	};

// __EIKMFNE_H__
#endif
// End of file
