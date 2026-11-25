// EIKMFNE.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMFNE_PAN__)
#define __EIKMFNE_PAN__

/** 
 * The enumeration <code>TEikMfnePanic</code> provides panic codes for the 
 * MFNE controls. 
 */
enum TEikMfnePanic
    {
    /** field is not editable 1 */
    EEikPanicMfneFieldIsNotEditable1,
    /** field is not editable 2 */
    EEikPanicMfneFieldIsNotEditable2,
    /** field is not editable 3 */
    EEikPanicMfneFieldIsNotEditable3,
    /** arrow key expected */
    EEikPanicMfneArrowKeyExpected,
    /** separator text has already been set */
    EEikPanicMfneSeparatorTextHasAlreadyBeenSet,
    /** bad number flags */
    EEikPanicMfneBadNumberFlags,
    /** inconsistent number flags */
    EEikPanicMfneInconsistentNumberFlags,
    /** bad number minimum and maximum 1 */
    EEikPanicMfneBadNumberMinimumAndMaximum1,
    /** bad number minimum and maximum 2 */
    EEikPanicMfneBadNumberMinimumAndMaximum2,
    /** bad number minimum and maximum 3 */
    EEikPanicMfneBadNumberMinimumAndMaximum3,
    /** unexpected minus sign */
    EEikPanicMfneUnexpectedMinusSign,
    /** number outside permitted range */
    EEikPanicMfneNumberOutsidePermittedRange,
    /** number text in bad state */
    EEikPanicMfneNumberTextInBadState,
    /** number has no digits */
    EEikPanicMfneNumberHasNoDigits,
    /** digit expected */
    EEikPanicMfneDigitExpected,
    /** too few symbolic items */
    EEikPanicMfneTooFewSymbolicItems,
    /** symbolic item array not created */
    EEikPanicMfneSymbolicItemArrayNotCreated,
    /** too many symbolic items added */
    EEikPanicMfneTooManySymbolicItemsAdded,
    /** ID of symbolic item not found */
    EEikPanicMfneIdOfSymbolicItemNotFound,
    /** symbolic item text has already been set */
    EEikPanicMfneSymbolicItemTextHasAlreadyBeenSet,
    /** field array already created */
    EEikPanicMfneFieldArrayAlreadyCreated,
    /** too few fields */
    EEikPanicMfneTooFewFields,
    /** field array not created */
    EEikPanicMfneFieldArrayNotCreated,
    /** too many fields added */
    EEikPanicMfneTooManyFieldsAdded,
    /** inverse video highlight type expected */
    EEikPanicMfneInverseVideoHighlightTypeExpected,
    /** bad cursor state 1 */
    EEikPanicMfneBadCursorState1,
    /** bad cursor state 2 */
    EEikPanicMfneBadCursorState2,
    /** bad cursor state 3 */
    EEikPanicMfneBadCursorState3,
    /** negative duration */
    EEikPanicMfneNegativeDuration,
    /** bad size */
    EEikPanicMfneBadSize,
    /** no control context */
    EEikPanicMfneNoControlContext,
    /** bad range to draw */
    EEikPanicMfneBadRangeToDraw,
    /** Range-editor: inconsistent minimum and maximum */
    EEikPanicRangeEditorInconsistentMinimumAndMaximum,
    /** Date-editor: bad time format */
    EEikPanicDateEditorBadTimeFormat,
    /** Date-editor: bad tab button height */
    EEikPanicDateEditorBadTabButtonHeight,
    /** Date-editor: bad date format */
    EEikPanicDateEditorBadDateFormat,
    /** Date-editor: bad date element position */
    EEikPanicDateEditorBadDateElementPosition,
    /** Date-editor: no more date elements */
    EEikPanicDateEditorNoMoreDateElements,
    /** Time-editor: bad minimum and maximum 1 */
    EEikPanicTimeEditorBadMinimumAndMaximum1,
    /** Time-editor: bad minimum and maximum 2 */
    EEikPanicTimeEditorBadMinimumAndMaximum2,
    /** Date-editor: bad minimum and maximum 1 */
    EEikPanicDateEditorBadMinimumAndMaximum1,
    /** Date-editor: bad minimum and maximum 2 */
    EEikPanicDateEditorBadMinimumAndMaximum2,
    /** Date-editor: bad component control index */
    EEikPanicDateEditorBadComponentControlIndex,
    /** Time-and-date-editor: bad minimum and maximum 1 */
    EEikPanicTimeAndDateEditorBadMinimumAndMaximum1,
    /** Time-and-date-editor: bad minimum and maximum 2 */
    EEikPanicTimeAndDateEditorBadMinimumAndMaximum2,
    /** Time-and-date-editor */
    EEikPanicTimeAndDateEditor,
    /** Time-and-date-editor: bad component control index */
    EEikPanicTimeAndDateEditorBadComponentControlIndex,
    /** Duration-editor: bad minimum and maximum 1 */
    EEikPanicDurationEditorBadMinimumAndMaximum1,
    /** Duration-editor: bad minimum and maximum 2 */
    EEikPanicDurationEditorBadMinimumAndMaximum2,
    /** Time-offset-editor: bad minimum and maximum 1 */
    EEikPanicTimeOffsetEditorBadMinimumAndMaximum1,
    /** Time-offset-editor: bad minimum and maximum 2 */
    EEikPanicTimeOffsetEditorBadMinimumAndMaximum2,
    /** <code>LatitudeLongitudeEditorBase</code>: bad values 1 */
    EEikPanicLatitudeLongitudeEditorBaseBadValues1,
    /** <code>LatitudeLongitudeEditorBase</code>: bad values 2 */
    EEikPanicLatitudeLongitudeEditorBaseBadValues2,
    /** Latitude-editor: bad direction */
    EEikPanicLatitudeEditorBadDirection,
    /** Longitude-editor: bad direction */
    EEikPanicLongitudeEditorBadDirection,
    /** direction already added */
    EEikPanicDirectionAlreadyAdded,
    /** has no checkbox field */
    EEikPanicMfneHasNoCheckBoxField,
    /** Duration-editor: bad absolute time */
    EEikPanicDurationEditorBadAbsoluteTime,
    /** Duration-editor: bad <code>WithDays</code> type */
    EEikPanicDurationBadDurationEditorWithDaysType
    };

GLREF_C void Panic(TEikMfnePanic aPanic);

#endif

