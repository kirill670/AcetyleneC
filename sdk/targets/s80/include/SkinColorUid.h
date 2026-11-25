/** @file 
   Some of the definitions in this file are also found in the 
   <code>extended_color_section</code> in the skin configuration file. 
   Developers should use these definitions instead of accessing those in
   the configuration file.
*/

/*
* ==============================================================================
*  Name        : skincoloruid.h
*  Part of     : SKINLOADER
*  Interface   : Skin API
*  Description : Skin colour constants.
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


#ifndef SKINCOLORUID_H
#define SKINCOLORUID_H

// CONSTANTS

/** this color is used in Contacts to draw the "my card" text */
#define KUidSkinColorMyName                             0x101F8090
/** skin color calendar highlight text */
#define KUidSkinColorCalendarHighlightText              0x101F8091
/** skin color calendar heading text */
#define KUidSkinColorCalendarHeadingText                0x101F8092
/** skin color calendar normal text */
#define KUidSkinColorCalendarNormalText                 0x101F8099
/** skin color calendar line */
#define KUidSkinColorCalendarLine                       0x101F8093
/** skin color calendar today text */
#define KUidSkinColorCalendarTodayText                  0x101F8098
/** skin color calendar outside month text */
#define KUidSkinColorCalendarOutsideMonthText           0x101F8097

/** skin color search field */
#define KUidSkinColorSearchField                        0x101F8094
/** skin colour for search icon background */
#define KUidSkinColorSearchFieldBackground              0x101FAC6A
/** skin color view background alternative */
#define KUidSkinColorViewBackgroundAlternative          0x101F809a
/** skin color overdue text */
#define KUidSkinColorOverdueText                        0x101F8095
/** skin color view header background */
#define KUidSkinColorViewHeaderBackground               0x101F8096

/** skin color control bar block */
#define KUidSkinColorControlBarBlock                    0x101F809c
/** skin color control bar background */
#define KUidSkinColorControlBarBackground               0x101F809d
/** skin color control bar outline shadow */
#define KUidSkinColorControlBarOutlineShadow            0x101F809e
/** skin color control bar outline highlight */
#define KUidSkinColorControlBarOutlineHighlight         0x101F8929

/**
 * this color is used by Web to show URLs. It is also used
 * by rich text editors, for example, the rich text editor
 * in the Word application, to show phone numbers, email addresses, and URLs
 */
#define KUidSkinColorLink                               0x101F892a
/**
 * this color is used by Web only to show URLs that the
 * user has already visited. This color is not used by
 * rich text editors
 */
#define KUidSkinColorLinkVisited                        0x101F892b

/** skin color editor highlight background */
#define KUidSkinColorEditorHighlightBackground          0x101F892c

/** skin color editor highlight text */
#define KUidSkinColorEditorHighlightText                0x101F8974

/** skin color annotation text */
#define KUidSkinColorAnnotationText                     0x101F892f

/**
 * this color is used by MIDP. This color is referred in
 * MIDP as, <code>Display.COLOR_BORDER</code>
 */
#define KUidSkinColorBorder                             0x101F8930
/**
 * this color is used by MIDP. This color is referred in
 * MIDP as: <code>Display.COLOR_HIGHLIGHTED_BORDER</code>
 */
#define KUidSkinColorBorderHighlighted                  0x101F8931

/** skin color progress bar */
#define KUidSkinColorProgressBar                        0x101F8975
/** skin color progress bar background */
#define KUidSkinColorProgressBarBackground              0x101F8976

/** colors for the weekday picker */
/** skin color day cell center */
#define KUidSkinColorDayCellCenter                      0x101F87B4
/** skin color day cell center dimmed */
#define KUidSkinColorDayCellCenterDimmed                0x101F87B5
/** skin color day cell center focused */
#define KUidSkinColorDayCellCenterFocused               0x101F87B6
/** skin color day cell center pressed */
#define KUidSkinColorDayCellCenterPressed               0x101F87B7
/** skin color day cell center pressed dimmed */
#define KUidSkinColorDayCellCenterPressedDimmed         0x101F87B8
/** skin color day cell center pressed focused */
#define KUidSkinColorDayCellCenterPressedFocused        0x101F87B9
/** skin color day cell center text */
#define KUidSkinColorDayCellCenterText                  0x101FAC5C
/** skin color day cell center dimmed text */
#define KUidSkinColorDayCellCenterDimmedText            0x101FAC5D
/** skin color day cell center focused text */
#define KUidSkinColorDayCellCenterFocusedText           0x101FAC5E
/** skin color day cell center pressed text */
#define KUidSkinColorDayCellCenterPressedText           0x101FAC5F
/** skin color day cell center pressed dimmed text */
#define KUidSkinColorDayCellCenterPressedDimmedText     0x101FAC60
/** skin color day cell center pressed focused text */
#define KUidSkinColorDayCellCenterPressedFocusedText    0x101FAC61


/** skin color active focus rect */
#define KUidSkinColorActiveFocusRect                    0x101F809b

/** colors for the view button center rectangle */
/** skin color view button center */
#define KUidSkinColorViewButtonCenter                   0x101FAC35
/** skin color view button center down */
#define KUidSkinColorViewButtonCenterDown               0x101FAC36
/** skin color view button center disabled */
#define KUidSkinColorViewButtonCenterDisabled           0x101FAC37
/** skin color view button center highlight */
#define KUidSkinColorViewButtonCenterHighlight          0x101FAC38
/** skin color view button center highlight down */
#define KUidSkinColorViewButtonCenterHiglightDown       0x101FAC39
/** skin color view button normal text */
#define KUidSkinColorViewButtonNormalText               0x101FAC62
/** skin color view button highlight text */
#define KUidSkinColorViewButtonHighlightText            0x101FAC63
/** skin color view button dimmed text */
#define KUidSkinColorViewButtonDimmedText				0x101FAC67

/** skin color desk background */
#define KUidSkinColorDeskBackground                     0x101F87E2

/** skin color clock text */
#define KUidSkinColorClockText                          0x101F87FD
/** skin color clock background */
#define KUidSkinColorClockBackground                    0x101F87FE

/** skin color for the background of the selected listbox */
#define KUidSkinColorListBoxNonFocussedSelectedBackground   0x101F87FF
/** skin color for the border of the selected listbox */
#define KUidSkinColorListBoxNonFocussedSelectedBorder       0x101F8800

/** skin color for text in the selected dialog tab */
#define KUidSkinColorDialogTabSelectedText              0x101FAC68
/** skin color for normal text in a dialog tab */
#define KUidSkinColorDialogTabNormalText                0x101FAC69
/** skin color for dimmed text in a dialog tab */
#define KUidSkinColorDialogTabDimmedText                0x101FAC70

/** skin colors displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette1                       0x101F8801
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette2                       0x101F8802
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette3                       0x101F8803
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette4                       0x101F8804
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette5                       0x101F8805
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette6                       0x101F8806
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette7                       0x101F8807
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette8                       0x101F8808
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette9                       0x101F8809
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette10                      0x101F880A
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette11                      0x101F880B
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette12                      0x101F880C
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette13                      0x101F880D
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette14                      0x101F880E
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette15                      0x101F880F
/** skin color displayed in <code>CEikGrayPalette</code> */
#define KUidSkinColorGrayPalette16                      0x101F8810

/** skin color used to draw underlines on editable fields */
#define KUidSkinColorUnderline                          0x101F8F05


#endif  // SKINCOLORUID_H

// End of File
