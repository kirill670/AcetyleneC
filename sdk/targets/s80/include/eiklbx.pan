// EIKLBX.PAN
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLBX_PAN__)
#define __EIKLBX_PAN__

enum TEikListBoxPanic
    {
    /** no match text array */
    EEikPanicListBoxNoMatchTextArray,
    /** no match buffer present */
    EEikPanicListBoxNoMatchBuffer,
    /** no model for the Listbox */
    EEikPanicListBoxNoModel,
    /** no view */
    EEikPanicListBoxNoView,
    /** invalid top item index specified */
    EEikPanicListBoxInvalidTopItemIndexSpecified,
    /** invalid current item index specified */
    EEikPanicListBoxInvalidCurrentItemIndexSpecified,
    /** invalid item index specified */
    EEikPanicListBoxInvalidItemIndexSpecified,
    /** invalid model specified */
    EEikPanicListBoxInvalidModelSpecified,
    /** invalid item drawer specified */
    EEikPanicListBoxInvalidItemDrawerSpecified,
    /** invalid flags specified */
    EEikPanicListBoxInvalidFlagsSpecified,
    /** invalid item height specified */
    EEikPanicListBoxInvalidItemHeightSpecified, 
    /** invalid item font specified */
    EEikPanicListBoxInvalidItemFontSpecified,   
    /** the called method is not valid for a single selection listbox */
    EEikPanicListBoxCalledFuncNotValidForSingleSelectionLBX,
    /** no selected index array */
    EEikPanicListBoxNoSelIndexArray,
    /** invalid selected index array specified */
    EEikPanicListBoxInvalidSelIndexArraySpecified,
    /** invalid row index specified */
    EEikPanicListBoxInvalidRowIndexSpecified,
    /** invalid column index specified */
    EEikPanicListBoxInvalidColIndexSpecified,
    /** invalid column width specified */
    EEikPanicListBoxInvalidColumnWidthSpecified,
    /** invalid graphics context specified */
    EEikPanicListBoxInvalidGcSpecified,
    /** invalid font specified */
    EEikPanicListBoxInvalidFontSpecified,
    /** no graphics context */
    EEikPanicListBoxNoGc,
    /** no font specified */
    EEikPanicListBoxNoFont,
    /** no hierarchical array present */
    EEikPanicListBoxNoHierArray,
    /** item is null */
    EEikPanicListBoxItemIsNull,
    /** invalid item index 1 */
    EEikPanicListBoxInvalidItemIndex1,
    /** invalid item index 2 */
    EEikPanicListBoxInvalidItemIndex2,
    /** invalid item index 3 */
    EEikPanicListBoxInvalidItemIndex3,
    /** invalid item height */
    EEikPanicListBoxInvalidItemHeight,
    /** does not support variable height items 1 */
    EEikPanicListBoxDoesNotSupportVariableHeightItems1,
    /** does not support variable height items 2 */
    EEikPanicListBoxDoesNotSupportVariableHeightItems2,
    /** does not support variable height items 3 */
    EEikPanicListBoxDoesNotSupportVariableHeightItems3,
    /** does not support variable height items 4 */
    EEikPanicListBoxDoesNotSupportVariableHeightItems4,
    /** does not support variable height items 5 */
    EEikPanicListBoxDoesNotSupportVariableHeightItems5,
    /** index overshoot 1 */
    EEikPanicListBoxIndexOvershoot1,
    /** index overshoot 2 */
    EEikPanicListBoxIndexOvershoot2,
    /** index overshoot 3 */
    EEikPanicListBoxIndexOvershoot3,
    /** bad number of pixels above top item 1 */
    EEikPanicListBoxBadNumberOfPixelsAboveTopItem1,
    /** bad number of pixels above top item 2 */
    EEikPanicListBoxBadNumberOfPixelsAboveTopItem2,
    /** bad number of pixels above top item 3 */
    EEikPanicListBoxBadNumberOfPixelsAboveTopItem3,
    /** bad number of pixels above top item 4 */
    EEikPanicListBoxBadNumberOfPixelsAboveTopItem4,
    /** bad number of pixels above top item 5 */
    EEikPanicListBoxBadNumberOfPixelsAboveTopItem5,
    /** negative item index */
    EEikPanicListBoxNegativeItemIndex,
    /** bad top item index 1 */
    EEikPanicListBoxBadTopItemIndex1,
    /** bad top item index 2 */
    EEikPanicListBoxBadTopItemIndex2,
    /** bad top item index 3 */
    EEikPanicListBoxBadTopItemIndex3,
    /** bad top item index 4 */
    EEikPanicListBoxBadTopItemIndex4,
    /** bad top item index 5 */
    EEikPanicListBoxBadTopItemIndex5,
    /** bad scrollbar thumb position 1 */
    EEikPanicListBoxBadScrollBarThumbPosition1,
    /** bad scrollbar thumb position 2 */
    EEikPanicListBoxBadScrollBarThumbPosition2,
    /** bad scrollbar thumb position 3 */
    EEikPanicListBoxBadScrollBarThumbPosition3,
    /** inconsistent item indices */
    EEikPanicListBoxInconsistentItemIndices,
    /** variable item heights not stored in order */
    EEikPanicListBoxVariableItemHeightsNotStoredInOrder,
    /** arithmetic error 1 */
    EEikPanicListBoxArithmeticError1,
    /** arithmetic error 2 */
    EEikPanicListBoxArithmeticError2,
    /** bad item index 1 */
    EEikPanicListBoxBadItemIndex1,
    /** bad item index 2 */
    EEikPanicListBoxBadItemIndex2,
    /** bad smooth scrolling */
    EEikPanicListBoxBadSmoothScrolling,
    /** bad number of spare vertical pixels 1 */
    EEikPanicListBoxBadNumberOfSpareVerticalPixels1,
    /** bad number of spare vertical pixels 2 */
    EEikPanicListBoxBadNumberOfSpareVerticalPixels2,
    /** negative minimum number of spare vertical pixels */
    EEikPanicListBoxNegativeMinimumNumberOfSpareVerticalPixels,
    /** inconsistent client rectangle 1 */
    EEikPanicListBoxInconsistentClientRect1,
    /** inconsistent client rectangle 2 */
    EEikPanicListBoxInconsistentClientRect2,
    /** inconsistent client rectangle 3 */
    EEikPanicListBoxInconsistentClientRect3,
    /** inconsistent number of vertical pixels 1 */
    EEikPanicListBoxInconsistentNumberOfVerticalPixels1,
    /** inconsistent number of vertical pixels 2 */
    EEikPanicListBoxInconsistentNumberOfVerticalPixels2,
    /** no preceding call to create extension L1 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL1,
    /** no preceding call to create extension L2 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL2,
    /** no preceding call to create extension L3 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL3,
    /** no preceding call to create extension L4 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL4,
    /** no preceding call to create extension L5 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL5,
    /** no preceding call to create extension L6 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL6,
    /** no preceding call to create extension L7 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL7,
    /** no preceding call to create extension L8 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL8,
    /** no preceding call to create extension L9 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL9,
    /** no preceding call to create extension L10 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL10,
    /** no preceding call to create extension L11 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL11,
    /** no preceding call to create extension L12 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL12,
    /** no preceding call to create extension L13 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL13,
    /** no preceding call to create extension L14 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL14,
    /** no preceding call to create extension L15 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL15,
    /** no preceding call to create extension L16 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL16,
    /** no preceding call to create extension L17 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL17,
    /** no preceding call to create extension L18 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL18,
    /** no preceding call to create extension L19 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL19,
    /** no preceding call to create extension L20 */
    EEikPanicListBoxNoPrecedingCallToCreateExtensionL20,
    /** not holding new number of pixels above top item */
    EEikPanicListBoxNotHoldingNewNumberOfPixelsAboveTopItem,
    /** not holding new top item index */
    EEikPanicListBoxNotHoldingNewTopItemIndex,
    /** not holding new view rect */
    EEikPanicListBoxNotHoldingNewViewRect,
    /** not holding number of vertical pixels */
    EEikPanicListBoxNotHoldingNumberOfVerticalPixels,
    /** not holding Listbox */
    EEikPanicListBoxNotHoldingListBox,
    /** horizontal dimensions of view rectangle has changed */
    EEikPanicListBoxHorizontalDimensionsOfViewRectChanged,
    /** inconsistent state */
    EEikPanicListBoxInconsistentState,
    /** both top and bottom item indices set */
    EEikPanicListBoxBothTopAndBottomItemIndicesSet,
    /** neither top nor bottom item indices set */
    EEikPanicListBoxNeitherTopNorBottomItemIndicesSet,
    /** bad function call preparation 1 */
    EEikPanicListBoxBadFunctionCallPreparation1,
    /** bad function call preparation 2 */
    EEikPanicListBoxBadFunctionCallPreparation2,
    /** bad scrollbar side */
    EEikPanicListBoxBadScrollBarSide,
    /** bad number of items */
    EEikPanicListBoxBadNumberOfItems,
    /** non-supported feature 1 */
    EEikPanicListBoxNonSupportedFeature1,
    /** non-supported feature 2 */
    EEikPanicListBoxNonSupportedFeature2,
    /** non-supported feature 3 */
    EEikPanicListBoxNonSupportedFeature3,
    /** bad view rectangle height adjustment */
    EEikPanicListBoxBadViewRectHeightAdjustment,
    /** component control index */
    EEikPanicListBoxComponentControlIndex,
    /** unknown selection array modification operation */
    EEikPanicListBoxUnknownSelectionArrayModificationOperation,
    /** supports variable height items */
    EEikPanicListBoxSupportsVariableHeightItems
    };

GLREF_C void Panic(TEikListBoxPanic aPanic);

#endif
