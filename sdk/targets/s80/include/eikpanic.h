/*
* ==============================================================================
*  Name        : eikpanic.h
*  Part of     : UIKON
*  Interface   : Application API
*  Description : Panic reasons
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


#ifndef EIKPANIC_H
#define EIKPANIC_H

/**
@publishedPartner
@released
*/
enum TEikPanic
    {
    /** invalid preview page number */
    EEikPanicInvalidPreviewPageNumber,
    /** the startup heap is too small */
    EEikPanicStartupHeapTooSmall,
    /** there is no library on the command line */
    EEikPanicNoLibraryOnCommandLine,
    /** there is no document on the command line */
    EEikPanicNoDocumentOnCommandLine,
    /** the alert text is too long */
    EEikPanicAlertTextTooLong,
    /** the cursor control is not focused */
    EEikPanicCursorControlNotFocused,
    /** the control does not own the cursor */
    EEikPanicControlNotCursorOwner,
    /** there is no hotkey to remove */
    EEikPanicNoHotKeyToRemove,
    /** there is no such menu item */
    EEikPanicNoSuchMenuItem,
    /** invalid menu pane */
    EEikPanicInvalidMenuPane,
    /** the menu bar title update is not supported */
    EEikPanicMenuBarTitleUpdateNotSupported,
    /** invalid bounds */
    EEikPanicInvalidBounds,
    /** unknown playback command */
    EEikPanicUnknownPlaybackCommand,
    /** the secret editor is too long */
    EEikPanicSecretEditorTooLong,
    /** invalid clock size */
    EEikPanicInvalidClockSize,
    /** invalid clock type */
    EEikPanicInvalidClockType,
    /** invalid clock settings */
    EEikPanicInvalidClockSettings,
    /** the scrollbar does not exist */
    EEikPanicScrollBarDoesNotExist,
    /** the scrollbar manager does not exist */
    EEikPanicScrollBarManagerDoesNotExist,
    /** the button array is higher than the screen */
    EEikPanicButtonArrayHigherThanScreen,
    /** the button array is wider than the screen */
    EEikPanicButtonArrayWiderThanScreen,
    /** the length for the button array is exceeded */
    EEikPanicBArrayLengthExceeded,
    /** the world manager */
    EEikPanicWorldManager,
    /** the world selector */
    EEikPanicWorldSelector,
    /** the world controller duplicated selector */
    EEikPanicWorldControllerDuplicateSelector,
    /** out of range */
    EEikPanicOutOfRange,
    /** null pointer */
    EEikPanicNullPointer,
    /** the wrong display mode */
    EEikPanicWrongDisplayMode,
    /** invalid resource value for the calendar*/
    EEikPanicCalendarInvalidResourceValue,
    /** invalid resource value for the print preview */
    EEikPanicPrintPreviewInvalidResourceValue,
    /** the field does not exist */
    EEikPanicFieldDoesNotExist,
    /** the edit combo is of insufficient size */
    EEikPanicEditComboInsufficientSize,
    /** invalid number of rows or columns */
    EEikPanicInvalidNumberOfRowsOrColumns,
    /** the button has no component */
    EEikPanicButtonHasNoComponent,
    /** no such folder for the selected file */
    EEikPanicFSelNoSuchFolder,
    /** the toolbar has no observer */
    EEikPanicToolBarHasNoObserver,
    /** the toolbar has null control */
    EEikPanicToolBarNullControl,
    /** there is no such dialog page */
    EEikPanicNoSuchDialogPage,
    /** the Eikon server message is too long */
    EEikPanicOverlongEikonServerMessage,
    /** invalid dimension for the control group */
    EEikPanicCtGroupInvalidDimension,
    /** invalid number of lines for the control group */
    EEikPanicCtGroupInvalidNumberOfLines,
    /** insufficient initialization for the control group */
    EEikPanicCtGroupInsufficientInitialisation,
    /** column list invalid bitmap index */
    EEikPanicColumnListInvalidBitmapIndex,
    /** header footer null filename */
    EEikPanicHeaderFooterNullFileName,
    /** process no store */
    EEikPanicProcessNoStore,
    /** process wrong store type */
    EEikPanicProcessWrongStoreType,
    /** the dialog toolbar has no observer */
    EEikPanicDialogToolBarNoObserver,
    /** the labeled button has an invalid hotkey */
    EEikPanicLabeledButtonInvalidHotKey,
    /** the labeled button has an invalid button type */
    EEikPanicLabeledButtonInvalidButtonType,
    /** illegal crop */
    EEikPanicIllegalCrop,
    /** time no data for dialog */
    EEikPanicTimeNoDataForDialog,
    /** the DTMF player is active */
    EEikPanicDtmfPlayerActive,
    /** nothing to dial */
    EEikPanicNothingToDial,
    /** logical color not found */
    EEikPanicLogicalColorNotFound,
    /** the logical color already exists */
    EEikPanicLogicalColorAlreadyExists,
    /** invalid color range */
    EEikPanicInvalidColorRange,
    /** the App color array is not found */
    EEikPanicAppColorArrayNotFound,
    /** the label has null text */
    EEikPanicLabelNullText,
    /** no library entry point */
    EEikPanicNoLibraryEntryPoint,
    /** the resource file was not removed */
    EEikPanicResourceFileNotRemoved,
    /** the control factory was not removed */
    EEikPanicControlFactoryNotRemoved,
    /** button group duplicate cleanup position */
    EEikPanicButtonGroupDuplicateCleanupPos,
    /** button group cleanup corrupt */
    EEikPanicButtonGroupCleanupCorrupt,
    /** the button group has a duplicate observer */
    EEikPanicButtonGroupDuplicateObserver,
    /** bad inline editing state 1 */
    EEikPanicBadInlineEditingState1,
    /** bad inline editing state 2 */
    EEikPanicBadInlineEditingState2,
    /** bad inline editing state 3 */
    EEikPanicBadInlineEditingState3,
    /** bad inline editing state 4 */
    EEikPanicBadInlineEditingState4,
    /** bad inline editing state 5 */
    EEikPanicBadInlineEditingState5,
    /** bad inline editing state 6 */
    EEikPanicBadInlineEditingState6,
    /** bad inline editing state 7 */
    EEikPanicBadInlineEditingState7,
    /** bad inline editing state 8 */
    EEikPanicBadInlineEditingState8,
    /** bad inline editing state 9 */
    EEikPanicBadInlineEditingState9,
    /** bad inline editing state 10 */
    EEikPanicBadInlineEditingState10,
    /** bad inline editing state 11 */
    EEikPanicBadInlineEditingState11,
    /** bad inline editing state 12 */
    EEikPanicBadInlineEditingState12,
    /** no such menu title */
    EEikPanicNoSuchMenuTitle,
    /** library not loaded */
    EEikPanicLibraryNotLoaded,
    /** the scrollbar frame has null scrollbar */
    EEikPanicScrollBarFrameNullScrollBar,
    /** AppUI not constructed */
    EEikPanicAppUiNotConstructed,
    /** virtual cursor leave not expected */
    EEikPanicVirtualCursorLeaveNotExpected,
    /** the command stack is null */
    EEikPanicCommandStackIsNull,
    /** the virtual cursor has an undefined error */
    EEikPanicVirtualCursorUndefinedError,
    /** the CBA button has an invalid ID */
    EEikPanicCbaButtonInvalidId,
    /** no button group factory */
    EEikPanicNoButtonGroupFactory,
    /** the button group was not found in the factory */
    EEikPanicButtonGroupNotFoundInFactory,
    /** the list item drawer graphics context is null */
    EEikPanicListItemDrawerGraphicsContextIsNull,
    /** invalid number of lines */
    EEikPanicInvalidNumberOfLines,
    /** the array length has been exceeded */
    EEikPanicArrayLengthExceeded,
    /** invalid index */
    EEikPanicInvalidIndex,
    /** invalid length */
    EEikPanicInvalidLength,
    /** no observers are left in position for the button group */
    EEikPanicButtonGroupNoObserversLeftInPosition
    };

/**
 * Calls <code>User::Panic</code> to terminate the current thread, specifying 
 * a category name and panic number.
 *
 * @param aPanic The panic code
 * @remarks
 * @see
 */
GLREF_C void Panic(TEikPanic aPanic);


#endif  // EIKPANIC_H

// End of File
