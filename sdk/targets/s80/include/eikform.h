/**
* ==============================================================================
*  Name        : eikform.h
*  Part of     : CKON / EIKDLG
*  Interface   : Form API
*  Description : Handling of controls on a form
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef EIKFORM_H
#define EIKFORM_H

// INCLUDES
#include <eikbctrl.h>
#include <eikbutb.h>
#include <eikon.hrh>
#include <bamdesca.h>
#include <eikteled.h>

// FORWARD DECLARATIONS
class CEikCapCArray;
class CEikCaptionedControl;
class CEikLabel;
class CGlobalText;
class CEikGlobalTextEditor;

/** [what] */
struct SEikRange;
/** [what] */
struct SEikDegreesMinutesDirection;
/** [what] */
struct SEikControlInfo;

/**
 * This class handles the form class, including the controls that are placed on
 * it. A form is a container control that contains a number of lines, and on 
 * each line is a control. Any of the supported controls can be added to a
 * form.
 *
 * @lib eikdlg.lib
 * @since Series90 1.0
 */
class CEikForm : public CEikBorderedControl, public MCoeControlObserver
    {
    public:

        /**
        * C++ default constructor.
        */
        IMPORT_C CEikForm();

        /**
        * Destructor.
        */
        IMPORT_C ~CEikForm();

        /**
        * Creates a new line (as a captioned control) in the form.
        *
        * @param aCaption The caption for the captioned control line
        * @param aControlId The control ID for the line
        * @param aControlType The type of control
        * @param aReturnValue The return value for the captioned control line
        * @return a pointer to the newly created control
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue);

        /**
        * Sets the caption for the specified control by descriptor.
        *
        * @param aControlId The captioned control ID to be changed
        * @param aText A reference to a descriptor containing the new caption
        *              text
        * @remarks
        * @see
        */
        IMPORT_C void SetControlCaptionL(TInt aControlId,const TDesC& aText);

        /**
        * Sets the caption for the specified control by resource ID.
        *
        * @param aControlId The captioned control ID to be changed
        * @param aResourceId The resource ID for the new caption
        * @remarks
        * @see
        */
        IMPORT_C void SetControlCaptionL(TInt aControlId,TInt aResourceId);

        /**
        * Returns the caption of the control specified by the control ID.
        * Asserts if the control is not found and returns <code>NULL</code>.
        *
        * @param aControlId The control ID of the required control
        * @return a pointer to a <code>CEikLabel</code> containing the caption
        * @remarks
        * @see
        */
        IMPORT_C CEikLabel* ControlCaption(TInt aControlId) const;

        /**
        * Returns a pointer to a control specified by the control ID.
        * Asserts if the control is not found and returns <code>NULL</code>.
        *
        * @param aControlId The control ID of the required control
        * @return a <code>CCoeControl</code> pointer to the control
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* Control(TInt aControlId) const;

        /**
        * Returns a control if <code>aControlId</code> is a valid control, or 
        * else returns <code>NULL</code>.
        *
        * @param aControlId The potential control ID of a valid control
        * @return a <code>CCoeControl</code> pointer or <code>NULL</code>
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* ControlOrNull(TInt aControlId) const;

        /**
        * Adds a text editor to the form. For parameters, see 
        * <code>CEikEdwin</code>.
        * 
        * @param aPrompt [what]
        * @param aId [what]
        * @param aFlags [what]
        * @param aWidthInChars [what]
        * @param aNoOfLines [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TDes* aReturn);

        /**
        * Adds a global text editor to the form. For parameters, see 
        * <code>CEikGlobalTextEditor</code>.
        * 
        * @param aPrompt [what]
        * @param aId [what]
        * @param aFlags [what]
        * @param aWidthInChars [what]
        * @param aNoOfLines [what]
        * @param aTextLimit [what]
        * @param aReturn [what]
        * @param aFontControlFlags [what]
        * @param aFontNameFlags [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoGlobalTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);

        /**
        * Adds a rich text editor to the form. For parameters, see 
        * <code>CEikRichTextEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aFlags [what]
        * @param aWidthInChars [what]
        * @param aNoOfLines [what]
        * @param aTextLimit [what]
        * @param aReturn [what]
        * @param aFontControlFlags [what]
        * @param aFontNameFlags [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoRichTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);

        /**
        * Adds a choice list to the form. For parameters, see 
        * <code>EikChoiceList</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aFlags [what]
        * @param aMaxChar [what]
        * @param aArray [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoChoiceListL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aMaxChar,MDesCArray* aArray,TInt* aReturn);

        /**
        * Adds a number editor to the form. For parameters, see 
        * <code>CEikNumberEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoNumberEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn);

        /**
        * Adds a range editor to the form. For parameters, see 
        * <code>CEikRangeEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aSeparatorText [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoRangeEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,HBufC* aSeparatorText,SEikRange* aReturn);

        /**
        * Adds a time editor to the form. For parameters, see 
        * <code>CEikTimeEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aNoSeconds [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoTimeEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TTime* aReturn);

        /**
        * Adds a time editor to the form. For parameters, see 
        * <code>CEikDateEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aNoPopout [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax, TBool aNoPopout,TTime* aReturn);

        /**
        * Adds a time and date editor to the form. For parameters, see 
        * <code>CEikTimeAndDateEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aNoSeconds [what]
        * @param aNoPopout [what]
        * @param aInterveningText [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoTimeAndDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TBool aNoPopout,HBufC* aInterveningText,TTime* aReturn);

        /**
        * Adds a duration editor to the form. For parameters, see 
        * <code>CEikDurationEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aNoSeconds [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoDurationEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);

        /**
        * Adds a time offset editor to the form. For parameters, see 
        * <code>CEikTimeOffsetEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aNoSeconds [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoTimeOffsetEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);

        /**
        * Adds a latitude editor to the form. For parameters, see 
        * <code>CEikLatitudeEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aDegreeSign [what]
        * @param aMinuteSign [what]
        * @param aSecondSign [what]
        * @param aTextForNorth [what]
        * @param aKeyToMatchForNorth [what]
        * @param aTextForSouth [what]
        * @param aKeyToMatchForSouth [what]
        * @param aReturn [what]
        * @param aFlags [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoLatitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForNorth,TChar aKeyToMatchForNorth,HBufC* aTextForSouth,TChar aKeyToMatchForSouth,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);

        /**
        * Adds a longitute editor to the form. For parameters, see 
        * <code>CEikLongitudeEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aDegreeSign [what]
        * @param aMinuteSign [what]
        * @param aSecondSign [what]
        * @param aTextForEast [what]
        * @param aKeyToMatchForEast [what]
        * @param aTextForWest [what]
        * @param aKeyToMatchForWest [what]
        * @param aReturn [what]
        * @param aFlags [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoLongitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForEast,TChar aKeyToMatchForEast,HBufC* aTextForWest,TChar aKeyToMatchForWest,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);

        /**
        * Adds a floating point editor to the form. For parameters, see 
        * <code>CEikFloatingPointEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoFloatEditorL(const TDesC& aPrompt,TInt aId,const TReal& aMin,const TReal& aMax,TReal* aReturn);

        /**
        * Adds a twips editor to the form. For parameters, see 
        * <code>CEikTwipsEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoTwipsEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn);

        /**
        * Adds a fixed point editor to the form. For parameters, see 
        * <code>CEikFixedPointEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMin [what]
        * @param aMax [what]
        * @param aRetValue [what]
        * @param aDecimalPlaces [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoFixedPointEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aRetValue,TInt aDecimalPlaces);

        /**
        * Adds a check box to the form. For parameters, see 
        * <code>CEikCheckBox</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoCheckBoxL(const TDesC& aPrompt,TInt aId,CEikButtonBase::TState* aReturn);

        /**
        * Adds a secret editor to the form. For parameters, see 
        * <code>CEikSecretEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoSecretEditorL(const TDesC& aPrompt,TInt aId,TDes* aReturn);

        /**
        * Adds a telephone number editor to the form. For parameters, see 
        * <code>CEikTelephoneNumberEditor</code>.
        *
        * @param aPrompt [what]
        * @param aId [what]
        * @param aMode [what]
        * @param aFlags [what]
        * @param aPromptArray [what]
        * @param aWidth [what]
        * @param aReturn [what]
        * @remarks
        * @see
        */
        IMPORT_C void AddAutoTelephoneNumberEditorL(const TDesC& aPrompt,TInt aId,CEikTelephoneNumberEditor::TTelephoneEditorMode aMode, TInt aFlags, TPtrC* aPromptArray, TInt aWidth,TDes* aReturn);

        /**
        * Sets the gap between the lines in the form.
        *
        * @param aValue The size of the gap between the lines
        * @remarks
        * @see
        */
        IMPORT_C void SetGapBetweenLines(TInt aValue);  
    public: // from CCoeControl

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    protected:  // Set state functions  

        /**
        * Sets a label for an item in the form by descriptor
        * @param aControlId The control id of the item in the form
        * @param aDes A reference to a descriptor containing the label text
        * @return void
        */
        IMPORT_C void SetLabelL(TInt aControlId, const TDesC& aDes);

        /**
        * Sets a label for an item in the form by descriptor
        * @param aControlId The control id of the item in the form
        * @param aResourceId The resource id of the new label text
        * @return void
        */
        IMPORT_C void SetLabelL(TInt aControlId, TInt aResourceId);

        /**
        * Sets the reserve length of a label control
        * @param aControlId The control id of the label control
        * @param aLength The new reserve length
        * @return void
        */
        IMPORT_C void SetLabelReserveLengthL(TInt aControlId, TInt aLength);

        /**
        * Sets the text for an edwin control
        * @param aControlId The control id of the edwin control
        * @param aDes The new text
        * @return void
        */
        IMPORT_C void SetEdwinTextL(TInt aControlId, const TDesC* aDes);

        /**
        * Sets the text for a text editor control
        * @param aControlId The control id of the text editor control
        * @param aGlobalText The new text
        * @return void
        */
        IMPORT_C void SetTextEditorTextL(TInt aControlId,const CGlobalText* aGlobalText);

        /**
        * Clears a secret editor control
        * @param aControlId The control id of the secret editor control
        * @return void
        */
        IMPORT_C void ResetSecretEditor(TInt aControlId);

        /**
        * Sets the state of a checkbox control
        * @param aControlId The control id of the checkbox control
        * @param aState The new state
        * @return void
        */
        IMPORT_C void SetCheckBoxState(TInt aControlId, CEikButtonBase::TState aState);

        /**
        * Sets the current (highlighted) item in a choice list control
        * @param aControlId The control id of the choice list control
        * @param aItem The new item to be highlighted
        * @return void
        */
        IMPORT_C void SetChoiceListCurrentItem(TInt aControlId, TInt aItem);

        /**
        * Sets the value of a floating point editor control
        * @param aControlId The control id of the floating point editor control
        * @param aValue The new value
        * @return void
        */
        IMPORT_C void SetFloatingPointEditorValueL(TInt aControlId, const TReal* aValue);

        /**
        * Sets the value of a fixed point editor control
        * @param aControlId The control id of the fixed point editor control
        * @param aValue The new value
        * @return void
        */
        IMPORT_C void SetFixedPointEditorValueL(TInt aControlId,TInt aValue);

        /**
        * Sets the amount of decimals for a fixed point editor control
        * @param aControlId The control id of the fixed point editor control
        * @param aDecimal The new number of decimal places
        * @return void
        */
        IMPORT_C void SetFixedPointEditorDecimal(TInt aControlId, TInt aDecimal);

        /**
        * Sets the value of a twips editor control
        * @param aControlId The control id of the twips editor control
        * @param aValue The new value for the twips editor control
        * @return void
        */
        IMPORT_C void SetTwipsEditorValueL(TInt aControlId, TInt* aValue);

        /**
        * Sets the minimum and maximum values for a number editor control
        * @param aControlId The control id for the number editor control
        * @param aMinimumValue The new minimum value
        * @param aMaximumValue The new maximum value
        * @return void
        */
        IMPORT_C void SetNumberEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted

        /**
        * Sets the value of a number editor control
        * @param aControlId The control id for the number editor control
        * @param aNumber The new value
        * @return void
        */
        IMPORT_C void SetNumberEditorValue(TInt aControlId, TInt aNumber);

        /**
        * Sets the minimum and maximum values of a float editor control
        * @param aControlId The control id for the float editor control
        * @param aMin The new minimum value
        * @param aMax The new maximum value
        * @return void
        */
        IMPORT_C void SetFloatEditorMinAndMax(TInt aControlId,TInt aMin,TInt aMax);

        /**
        * Sets the value of a float editor control
        * @param aControlId The control id for the float editor control
        * @param aFloat The new value
        * @return void
        */
        IMPORT_C void SetFloatEditorValueL(TInt aControlId,TReal aFloat);

        /**
        * Sets the minimum and maximum values of a range editor control
        * @param aControlId The control id of the range editor control
        * @param aMinimumValue The new minimum value
        * @param aMaximumValue The new maximum value
        * @return void
        */
        IMPORT_C void SetRangeEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted

        /**
        * Sets the value for a range editor control
        * @param aControlId The control id of the range editor control
        * @param aRange The new range
        * @return void
        */
        IMPORT_C void SetRangeEditorValue(TInt aControlId, const SEikRange& aRange);

        /**
        * Sets the minimum and maximum values of a time editor control
        * @param aControlId The control id of the time editor control
        * @param aMinimumTime The new minimum time
        * @param aMaximumTime The new maximum time
        * @return void
        */
        IMPORT_C void SetTTimeEditorMinAndMax(TInt aControlId, const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial min and max are permitted

        /**
        * Sets the value of a time editor control
        * @param aControlId The control id of the time editor control
        * @param aTime The new time
        * @return void
        */
        IMPORT_C void SetTTimeEditorValue(TInt aControlId, const TTime& aTime);

        /**
        * Sets the minimum and maximum value of a duration editor control
        * @param aControlId The control id of the duration editor control
        * @param aMinimumDuration The new minimum duration
        * @param aMaximumDuration The new maximum duration
        * @return void
        */
        IMPORT_C void SetDurationEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial min and max are permi

        /**
        * Sets the value of a duration editor control
        * @param aControlId The control id of the duration editor control
        * @param aDuration The new duration
        * @return void
        */
        IMPORT_C void SetDurationEditorValue(TInt aControlId, const TTimeIntervalSeconds& aDuration);

        /**
        * Sets the minimum and maximum values of a time offset editor control
        * @param aControlId The control id of the time offset editor control
        * @param aMinimumTimeOffset The new minimum time offset
        * @param aMaximumTimeOffset The new maximum time offset
        * @return void
        */
        IMPORT_C void SetTimeOffsetEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial min and max are

        /**
        * Sets the value of a time offset editor control
        * @param aControlId The control id of the time offset editor control
        * @param aTimeOffset The new time offset
        * @return void
        */
        IMPORT_C void SetTimeOffsetEditorValue(TInt aControlId, const TTimeIntervalSeconds& aTimeOffset);

        /**
        * Sets the value of the latitude editor control
        * @param aControlId The control id of the latitude editor control
        * @param aLatitude The new latitude
        * @return void
        */
        IMPORT_C void SetLatitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLatitude);

        /**
        * Sets the value of the longitude editor control
        * @param aControlId The control id of the longitude editor control
        * @param aLongitude The new latitude
        * @return void
        */
        IMPORT_C void SetLongitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLongitude);

        /**
        * Sets the state of an option button control
        * @param aControlId The control id of the option button control
        * @param aState The new state
        * @return vpod
        */
        IMPORT_C void SetOptionButtonState(TInt aControlId, CEikButtonBase::TState aState);

        /**
        * Sets the current set of a CEikHorOptionButtonList control
        * @param aControlId The control id of the CEikHorOptionButtonList control
        * @param aSetButId The new button set
        * @return void
        */
        IMPORT_C void SetHorOptionButListCurrentSet(TInt aControlId,TInt aSetButId);
    // not available before Release 005

        /**
        * Sets the mode of a telephone editor control
        * @param aControlId The control id of the telephone editor control
        * @param aMode The new mode
        * @return void
        */
        IMPORT_C void SetTelephoneEditorMode(TInt aControlId,CEikTelephoneNumberEditor::TTelephoneEditorMode aMode);

        /**
        * Sets the simple value of a telephone editor control
        * @param aControlId The control id of a telephone editor control
        * @param aNumber The new value
        * @return void
        */
        IMPORT_C void SetTelephoneEditorNumberL(TInt aControlId,const TDesC& aNumber);

        /**
        * Sets the detailed value of a telephone editor control
        * @param aControlId The control id of the telephone editor control
        * @param aCountry The new country value
        * @param aArea The new area value
        * @param aNumber The new number value
        * @return void
        */
        IMPORT_C void SetTelephoneEditorNumberL(TInt aControlId,const TDesC& aCountry,const TDesC& aArea,const TDesC& aNumber);
    //
    protected:  // Get state functions

        /**
        * Returns the text of a label control
        * @param aDes Will contain the label text upon completion
        * @param aControlId The control id of the label control
        * @return void
        */
        IMPORT_C void GetLabelText(TDes&, TInt aControlId) const;

        /**
        * Returns the text of an edwin control
        * @param aDes Will contain the edwin text upon completion
        * @param aControlId The control id of the edwin control
        * @return void
        */
        IMPORT_C void GetEdwinText(TDes& aDes,TInt aControlId) const;

        /**
        * Returns the text of a text editor control
        * @param aGlobalText Will contain the text editor text upon completion
        * @param aControlId The control id of the text editor control
        * @return void
        */
        IMPORT_C void GetTextEditorText(CGlobalText*& aGlobalText,TInt aControlId);

        /**
        * Returns the text of a secret editor control
        * @param aDes Will contain the secret editor text upon completion
        * @param aControlId The control id of the secret editor control
        * @return void
        */
        IMPORT_C void GetSecretEditorText(TDes& aDes,TInt aControlId) const;

        /**
        * Returns the state of a check box control
        * @param aControlId The control id of the check box control
        * @return The state of the check box control
        */
        IMPORT_C CEikButtonBase::TState CheckBoxState(TInt aControlId) const;

        /**
        * Returns the current (highlighted) index in a choice list control
        * @param aControlId The control id of a choice list control
        * @return The current (highlighed) index
        */
        IMPORT_C TInt ChoiceListCurrentItem(TInt aControlId) const;

        /**
        * Returns the floating point value from a floating point editor control
        * @param aControlId The control id of a floating point editor control
        * @return The current value of the floating point editor control
        */
        IMPORT_C TReal FloatingPointEditorValue(TInt aControlId) const;

        /**
        * Returns the fixed point value from a fixed point editor control
        * @param aControlId The control id of a fixed point editor control
        * @return The current value of the fixed point editor control
        */
        IMPORT_C TInt FixedPointEditorValue(TInt aControlId) const;

        /**
        * Returns the number of decimal places from a fixed point editor control
        * @param aControlId The control id of a fixed point editor control
        * @return The number of decimal places of the fixed point editor control
        */
        IMPORT_C TInt FixedPointEditorDecimal(TInt aControlId) const;

        /**
        * Returns the value of a twips editor control
        * @param aControlId The control id of the twips editor control
        * @return The value of the twips editor control
        */
        IMPORT_C TInt TwipsEditorValue(TInt aControlId) const;

        /**
        * Returns the value of a float editor control
        * @param aControlId The control id of the float editor control
        * @return The value of the float editor control
        */
        IMPORT_C TReal FloatEditorValue(TInt aControlId) const;

        /**
        * Returns the value of a number editor control
        * @param aControlId The control id of the number editor control
        * @return The value of the float control
        */
        IMPORT_C TInt NumberEditorValue(TInt aControlId) const;

        /**
        * Returns the range of a range editor control
        * @param aControlId The control id of the range control
        * @return The range of the range control
        */
        IMPORT_C SEikRange RangeEditorValue(TInt aControlId) const;

        /**
        * Returns the time value of a time editor control
        * @param aControlId The control id of the time editor control
        * @return The time value of the time editor control
        */
        IMPORT_C TTime TTimeEditorValue(TInt aControlId) const;

        /**
        * Returns the value of a duration editor control
        * @param aControlId The control id of the duration editor control
        * @return The value of the duration editor control
        */
        IMPORT_C TTimeIntervalSeconds DurationEditorValue(TInt aControlId) const;

        /**
        * Returns the value of a time offset editor control
        * @param aControlId The control id of the time offset editor control
        * @return The value of the time offset editor control
        */
        IMPORT_C TTimeIntervalSeconds TimeOffsetEditorValue(TInt aControlId) const;

        /**
        * Returns the value of a latitude editor control
        * @param aControlId The control id of the latitude editor control
        * @return The value of the latitude editor control
        */
        IMPORT_C SEikDegreesMinutesDirection LatitudeEditorValue(TInt aControlId) const;

        /**
        * Returns the value of a longitude editor control
        * @param aControlId The control id of the longitude editor control
        * @return The value of the longitude editor control
        */
        IMPORT_C SEikDegreesMinutesDirection LongitudeEditorValue(TInt aControlId) const;

        /**
        * Returns all the auto values from a page
        * @param aLines Will be filled with the auto values on the page upon completion
        * @return void
        */
        IMPORT_C void GetAutoValuesFromPage(CEikCapCArray* aLines);

        /**
        * Returns the state of an option button control
        * @param aControlId The control id of an option button control
        * @return The current state of the option button control
        */
        IMPORT_C CEikButtonBase::TState OptionButtonState(TInt aControlId) const;

        /**
        * Returns the current set of a CEikHorOptionButtonList control
        * @param aControlId The control id of the CEikHorOptionButtonList control
        * @return The current set
        */
        IMPORT_C TInt HorOptionButListCurrentSet(TInt aControlId) const;

        /**
        * Returns the current number in a telephone editor control
        * @param aControlId The control id of the telephone editor control
        * @param aNumber Will contain the telephone number upon completion
        * @return void
        */
        IMPORT_C void GetTelephoneEditorNumber(TInt aControlId,TDes& aNumber) const; // not available before Release 005
    private:
// End of functions defined in EIKFRMUT.CPP
    protected: // new functions

        /**
        * Constructs a control by the type specified
        * @param aControlType The type of control (see relevant hrh file)
        * @param aLine The captioned control line associated with the new control
        * @param aContainer The CCoeControl container for the new control
        * @return void
        */
        IMPORT_C void ConstructByTypeL(TInt aControlType,CEikCaptionedControl* aLine,CCoeControl* aContainer);

        /**
        * Returns the control id of the currently focused control
        * @return The control id of the currently focused control
        */
        IMPORT_C TInt IdOfFocusControl() const;

        /**
        * Returns the line index of the specified control
        * @param aControl The control
        * @return The line index
        */
        IMPORT_C TInt FindLineIndex(CCoeControl* aControl) const;

        /**
        * Returns a captioned control specified by the control id
        * @param aControlId The control id of the required captioned control
        * @return The captioned control
        */
        IMPORT_C CEikCaptionedControl* Line(TInt aControlId) const;

        /**
        * Switches the focus on the current line on or off
        * @param aFocus ETrue if the focus should be shown, otherwise eFalse
        * @return void
        */
        IMPORT_C virtual void ShowFocus(TBool aFocus);

        /**
        * Changes the focus of the current line
        * @param aCurrentLine The index of the line which requires the focus
        * @return void
        */
        IMPORT_C virtual void ChangeFocusTo(TInt aCurrentLine);

        /**
        * Moves the focus position past a specified number of positions
        * @param aDelta The number of positions to shift the focus
        * @return ETrue if the focus shift succeeded, otherwise eFalse
        */
        IMPORT_C TBool RotateFocusByL(TInt aDelta);

        /**
        * The current focused line is informed it is about to lose focus
        * @return void
        */
        IMPORT_C virtual void PrepareForFocusTransitionL();

        /**
        * Returns the line index of a control specified by ID
        * @param aControlId The control id of the required control
        * @param aArray The array of lines
        * @return The line index
        */
        IMPORT_C virtual TInt LineIndexFromId(TInt aControlId,CEikCapCArray*& aArray) const;
    
        /**
        * Modifies the captioned control so that checkboxes
        * respond to pointer clicks on the caption label
        * @param    aType   The control type
        * @param    aLine   The captioned control
        * @return void
        */
        IMPORT_C void ModifyControlL(TInt aType, CEikCaptionedControl* aLine);
    private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
    private: // new functions
        IMPORT_C virtual SEikControlInfo CreateCustomControlL(TInt aControlType);
        IMPORT_C virtual void GetCustomAutoValue(TAny* aReturnValue,TInt aControlType,const CCoeControl* aControl);
        IMPORT_C virtual void Reserved_3();
    protected: // from CCoeControl

        /**
        * Returns the number of component controls on the form - See CCoeControl
        * @return Number of component controls
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * Returns the component control with the specified index - See CCoeControl
        * @param aIndex The index of the required component control
        * @return A pointer to the component control
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * Informs the form the size has been changed - See CCoeControl
        * @return void
        */
        IMPORT_C void SizeChanged();

        /**
        * Returns the minimum size of the form - See CCoeControl
        * @return The minimum size
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Informs the form the focus has been changed - See CCoeControl
        * @param aDrawNow See TDrawNow - whether or not to redraw the line 
        * @return void
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    protected: // from MCoeControlObserver

        /**
        * Handle a form event of type TCoeEvent - See MCoeControlObserver
        * @param aControl The control responsible for the event
        * @param aEventType The event type
        * @return void
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    protected:
        CEikCapCArray* iLines;
        TInt iCurrentLine;
    };


#endif  // EIKFORM_H

// End of File
