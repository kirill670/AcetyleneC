/** @file

    Each constant definition in this file, for example,
    <code>const TUid KUidSkinScrollbarBitmaps = {...}</code> is assigned a
    value, for example, <code>KUidSkinScrollbarBitmapsValue</code>, defined in
    file skinmbmuid.h. The value represents the hexadecimal ID of
    an .mbm file in the <code>bitmap_section</code> of the skin configuration
    file. Developers should use constants such as
    <code>KUidSkinScrollbarBitmaps</code>, defined in skinuid.h rather than
    accessing those defined in the skin configuration file.
 */

/*
* ==============================================================================
*  Name        : skinuid.h
*  Part of     : SKINLOADER
*  Interface   : Skin API
*  Description : Skin UIDs for bitmaps and icons, and skin constant IDs.
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


#ifndef SKINUID_H
#define SKINUID_H

/** */


// INCLUDES
#include <SkinMbmUid.h>
#include <SkinColorUid.h>

// CONSTANTS
/** The enumeration <code>TSkinIconId</code> provides skin icon constants. */
enum TSkinIconId
    {
    /** folder collapsed */
    ESkinIconFolderCollapsed,
    /** folder expanded */
    ESkinIconFolderExpanded,
    /** folder open */
    ESkinIconFolderOpen,
    /** folder closed */
    ESkinIconFolderClosed,
    /** communicator collapsed */
    ESkinIconCommunicatorCollapsed,
    /** communicator expanded */
    ESkinIconCommunicatorExpanded,
    /** communicator closed */
    ESkinIconCommunicatorClosed,
    /** MMC collapsed */
    ESkinIconMmcCollapsed,
    /** MMC expanded */
    ESkinIconMmcExpanded,
    /** MMC closed */
    ESkinIconMmcClosed,
    /** information */
    ESkinIconInformation,
    /** confirmation */
    ESkinIconConfirmation,
    /** search */
    ESkinIconSearch,
    /** input */
    ESkinIconInput,
    /** URL */
    ESkinIconUrl,
    /** date-editor */
    ESkinIconDateEditor,
    /** date-editor disabled */
    ESkinIconDateEditorDisabled,
    /** date-editor pressed */
    ESkinIconDateEditorPressed,
    /** time-editor */
    ESkinIconTimeEditor,
    /** time-editor disabled */
    ESkinIconTimeEditorDisabled,
    /** time-editor pressed */
    ESkinIconTimeEditorPressed,
    /** terminator */
    ESkinIconTerminator
    };

/** The enumeration <code>TSkinConstId</code> provides skin constant IDs.
    Each  element defined corresponds to a definition in the
    <code>constant_section</code>
    of the skin configuration file. Developers should use the element definition
    in this enumeration to access the constants defined in the skin configuration
    file.*/
enum TSkinConstId
    {
    /** menu bar text top space */
    ESkinConstMenuBarTextTopSpace=0x0000,
    /** menu bar text bottom space */
    ESkinConstMenuBarTextBottomSpace=0x0001,
    /** menu item text right space */
    ESkinConstMenuItemTextRightSpace=0x0002,
    /** space between menu border and highlight */
    ESkinConstSpaceBetweenMenuBorderAndHighlight=0x0003,
    /** border margin pop-out window left */
    ESkinConstBorderMarginPopoutWindowLeft=0x0004,
    /** border margin pop-out window right */
    ESkinConstBorderMarginPopoutWindowRight=0x0005,
    /** border margin pop-out window top */
    ESkinConstBorderMarginPopoutWindowTop=0x0006,
    /** border margin pop-out window bottom */
    ESkinConstBorderMarginPopoutWindowBottom=0x0007,
    /** choicelist text maximum width */
    ESkinConstChoicelistTextMaxWidth=0x0008,
    /** dialog title baseline */
    ESkinConstDialogTitleBaseline=0x0009,
    /** status pane application sub name text vertical offset */
    ESkinConstStatusPaneAppSubNameTextVertOffset=0x000a,
    /** status pane application name icon vertical offset */
    ESkinConstStatusPaneAppNameIconVertOffset=0x000b,
    /** status pane application name text vertical offset */
    ESkinConstStatusPaneAppNameTextVertOffset=0x000c,
    /** link model tick column width */
    ESkinConstLinkModelTickColumnWidth=0x000d,
    /** dialog title height */
    ESkinConstDialogTitleHeight=0x000e,
    /** time-picker arrow width */
    ESkinConstTimePickerArrowWidth=0x000f,
    /** time-picker arrow height */
    ESkinConstTimePickerArrowHeight=0x0010,
    /** choicelist dropdown arrow width */
    ESkinConstChoicelistDropdownArrowWidth=0x0011,
    /** command bar minimum width */
    ESkinConstCommandBarMinWidth=0x0012,
    /** command bar maximum width */
    ESkinConstCommandBarMaxWidth=0x0013,
    /** infoprint icon width */
    ESkinConstInfoPrintIconWidth=0x0014,
    /** infoprint icon height */
    ESkinConstInfoPrintIconHeight=0x0015,
    /** enable scrollbar nudge buttons */
    ESkinConstEnableScrollBarNudgeButtons=0x0016,
    /** link model scroll box width */
    ESkinConstLinkModelScrollBoxWidth=0x0017,
    /** link model check column index */
    ESkinConstLinkModelCheckColumnIndex=0x0018,
    /** horizontal gap between dialog buttons */
    ESkinConstHorizGapBetweenDialogButtons=0x0019,
    /** vertical gap between dialog buttons */
    ESkinConstVertGapBetweenDialogButtons=0x001a,
    /** dialog button minimum width */
    ESkinConstDialogButtonMinWidth=0x001b,
    /** combobox dropdown arrow width */
    ESkinConstComboboxDropdownArrowWidth=0x001c,
    /** combobox dropdown arrow height */
    ESkinConstComboboxDropdownArrowHeight=0x001d,
    /** dialog page container space from top */
    ESkinConstDialogPageContainerSpaceFromTop=0x001e,
    /** dialog page container space from bottom */
    ESkinConstDialogPageContainerSpaceFromBottom=0x001f,
    /** dialog button 1 margin left */
    ESkinConstDialogButton1MarginLeft=0x0020,
    /** dialog button 1 margin right */
    ESkinConstDialogButton1MarginRight=0x0021,
    /** dialog button 2 margin left */
    ESkinConstDialogButton2MarginLeft=0x0022,
    /** dialog button 2 margin right */
    ESkinConstDialogButton2MarginRight=0x0023,
    /** dialog button 3 margin left */
    ESkinConstDialogButton3MarginLeft=0x0024,
    /** dialog button 3 margin right */
    ESkinConstDialogButton3MarginRight=0x0025,
    /** dialog button margin top */
    ESkinConstDialogButtonMarginTop=0x0026,
    /** dialog button margin bottom */
    ESkinConstDialogButtonMarginBottom=0x0027,
    /** margin application view 1 left */
    ESkinConstMarginAppView1Left=0x0028,
    /** margin application view 1 right */
    ESkinConstMarginAppView1Right=0x0029,
    /** margin application view 1 top */
    ESkinConstMarginAppView1Top=0x002a,
    /** margin application view 1 bottom */
    ESkinConstMarginAppView1Bottom=0x002b,
    /** button pressed offset */
    ESkinConstButtonPressedOffset=0x002c,
    /** menu shadow height */
    ESkinConstMenuShadowHeight=0x002d,
    /** pop-out corner type */
    ESkinConstPopoutCornerType=0x002e, // REMOVE when apps stop using this
    /** status pane vertical offset large icon DEPRECATED */
    //ESkinConstStatusPaneVertOffsetLargeIcon=0x002f,
    /** status pane vertical offset small icon DEPRECATED */
    //ESkinConstStatusPaneVertOffsetSmallIcon=0x0030,
    /** menu item text left space */
    ESkinConstMenuItemTextLeftSpace=0x0031,
    /** space between menu right border and title */
    ESkinConstSpaceBetweenMenuRightBorderAndTitle=0x0032,
    /** menu cascade overlap */
    ESkinConstMenuCascadeOverlap=0x0033,
    /** dialog button 4 margin left */
    ESkinConstDialogButton4MarginLeft=0x0034,
    /** dialog button 4 margin right */
    ESkinConstDialogButton4MarginRight=0x0035,
    /** status pane separator vertical position */
    ESkinConstStatusPaneSeparatorVerticalPos=0x0036,
    /** dialog buttons same size */
    ESkinConstDialogButtonsSameSize=0x0037,
    /** dialog margin left */
    ESkinConstDialogMarginLeft=0x0038,
    /** dialog margin right */
    ESkinConstDialogMarginRight=0x0039,
    /** dialog margin top */
    ESkinConstDialogMarginTop=0x003a,
    /** dialog margin bottom */
    ESkinConstDialogMarginBottom=0x003b,
    /** multi-page dialog margin left */
    ESkinConstMultiPageDialogMarginLeft=0x003c,
    /** multi-page dialog margin right */
    ESkinConstMultiPageDialogMarginRight=0x003d,
    /** multi-page dialog margin top */
    ESkinConstMultiPageDialogMarginTop=0x003e,
    /** multi-page dialog margin bottom */
    ESkinConstMultiPageDialogMarginBottom=0x003f,
    /** dialog maximum height */
    ESkinConstDialogMaxHeight=0x0040,
    /** multi-page dialog maximum height */
    ESkinConstMultiPageDialogMaxHeight=0x0041,
    /** margin application view 2 left */
    ESkinConstMarginAppView2Left=0x0042,
    /** margin application view 2 right */
    ESkinConstMarginAppView2Right=0x0043,
    /** margin application view 2 top */
    ESkinConstMarginAppView2Top=0x0044,
    /** margin application view 2 bottom */
    ESkinConstMarginAppView2Bottom=0x0045,
    /** margin application view 3 left */
    ESkinConstMarginAppView3Left=0x0046,
    /** margin application view 3 right */
    ESkinConstMarginAppView3Right=0x0047,
    /** margin application view 3 top */
    ESkinConstMarginAppView3Top=0x0048,
    /** margin application view 3 bottom */
    ESkinConstMarginAppView3Bottom=0x0049,
    /** margin application view 4 left */
    ESkinConstMarginAppView4Left=0x004a,
    /** margin application view 4 right */
    ESkinConstMarginAppView4Right=0x004b,
    /** margin application view 4 top */
    ESkinConstMarginAppView4Top=0x004c,
    /** margin application view 4 bottom */
    ESkinConstMarginAppView4Bottom=0x004d,
    /** select enter key interaction */
    ESkinConstSelectEnterKeyInteraction=0x004e,
    /**
     * calendar version: <code>0</code> = <code>CEikCalendar</code>;
     * <code>1</code> = <code>CCknCalendar</code>
     */
    ESkinConstCalendarVersion=0x004f,   //
    /** mandatory field icon height */
    ESkinConstMandatoryFieldIconHeight=0x0050,
    /** mandatory field icon width */
    ESkinConstMandatoryFieldIconWidth=0x0051,
    /** dialog border margin left */
    ESkinConstDialogBorderMarginLeft=0x0052,
    /** dialog border margin right */
    ESkinConstDialogBorderMarginRight=0x0053,
    /** dialog border margin top */
    ESkinConstDialogBorderMarginTop=0x0054,
    /** dialog border margin bottom */
    ESkinConstDialogBorderMarginBottom=0x0055,
    /** status pane height */
    ESkinConstStatusPaneHeight=0x0056,
    /** focus rect margin left */
    ESkinConstFocusRectMarginLeft=0x0057,
    /** focus rect margin right */
    ESkinConstFocusRectMarginRight=0x0058,
    /** command bar button total */
    ESkinConstCommandBarButtonTotal=0x0059,
    /** border margin menu bar left */
    ESkinConstBorderMarginMenuBarLeft=0x005a,
    /** border margin menu bar right */
    ESkinConstBorderMarginMenuBarRight=0x005b,
    /** border margin menu bar top */
    ESkinConstBorderMarginMenuBarTop=0x005c,
    /** border margin menu bar bottom */
    ESkinConstBorderMarginMenuBarBottom=0x005d,
    /** border margin menu pane left */
    ESkinConstBorderMarginMenuPaneLeft=0x005e,
    /** border margin menu pane right */
    ESkinConstBorderMarginMenuPaneRight=0x005f,
    /** border margin menu pane top */
    ESkinConstBorderMarginMenuPaneTop=0x0060,
    /** border margin menu pane bottom */
    ESkinConstBorderMarginMenuPaneBottom=0x0061,
    /** link model group name column index */
    ESkinConstLinkModelGroupNameColumnIndex=0x0062,
    /** menu pane vertical offset */
    ESkinConstMenuPaneVerticalOffset=0x0063,
    /** cap control gap between mandatory icon and component */
    ESkinConstCapControlGapBetweenMandatoryIconAndComponent=0x0064,
    /** listbox maximum height in num of items */
    ESkinConstListBoxMaxHeightInNumOfItems=0x0065,
    /** listbox margin top */
    ESkinConstListBoxMarginTop=0x0066,
    /** listbox margin bottom */
    ESkinConstListBoxMarginBottom=0x0067,
    /** listbox margin left */
    ESkinConstListBoxMarginLeft=0x0068,
    /** listbox margin right */
    ESkinConstListBoxMarginRight=0x0069,
    /** margin application view toolband left */
    ESkinConstMarginAppViewToolbandLeft=0x006a,
    /** margin application view toolband top */
    ESkinConstMarginAppViewToolbandTop=0x006b,
    /** toolband width with CBA */
    ESkinConstToolbandWidthWithCba=0x006c,
    /** toolband width no CBA */
    ESkinConstToolbandWidthNoCba=0x006d,
    /** toolband height */
    ESkinConstToolbandHeight=0x006e,
    /** command bar button height */
    ESkinConstCommandBarButtonHeight=0x006f,
    /** command bar button margin left */
    ESkinConstCommandBarButtonMarginLeft=0x0070,
    /** command bar button margin right */
    ESkinConstCommandBarButtonMarginRight=0x0071,
    /** command bar margin left */
    ESkinConstCommandBarMarginLeft=0x0072,
    /** thumb minimum length */
    ESkinConstThumbMinLength=0x0073,
    /** seek bar left margin */
    ESkinConstSeekBarLeftMargin=0x0074,
    /** seek bar right margin */
    ESkinConstSeekBarRightMargin=0x0075,
    /** seek bar time box vertical offset */
    ESkinConstSeekBarTimeBoxVerticalOffset=0x0076,
    /** seek bar time box left and right border */
    ESkinConstSeekBarTimeBoxLeftAndRightBorder=0x0077,
    /** seek bar time box top and bottom border */
    ESkinConstSeekBarTimeBoxTopAndBottomBorder=0x0078,
    /** seek bar start position from left */
    ESkinConstSeekBarStartPositionFromLeft=0x0079,
    /** seek bar end position from right */
    ESkinConstSeekBarEndPositionFromRight=0x007a,
    /** seek bar thumb over hang */
    ESkinConstSeekBarThumbOverHang=0x007b,
    /** status pane title area horizontal offset */
    ESkinConstStatusPaneTitleAreaHorizOffset=0x007c,
    /** region red */
    ESkinConstRegionRed=0x007d,
    /** region green */
    ESkinConstRegionGreen=0x007e,
    /** region blue */
    ESkinConstRegionBlue=0x007f,
    /** default background fading black map */
    ESkinConstDefaultBackroundFadingBlackMap=0x0080,
    /** default background fading white map */
    ESkinConstDefaultBackroundFadingWhiteMap=0x0081,
    /** combo popup distance to edge */
    ESkinConstComboPopupDistanceToEdge=0x0082,
    /** status pane icon enable */
    ESkinConstStatusPaneIconEnable=0x0083,
    /** view button 1 margin left */
    ESkinConstViewButton1MarginLeft=0x0084,
    /** view button 1 margin right */
    ESkinConstViewButton1MarginRight=0x0085,
    /** view button 2 margin left */
    ESkinConstViewButton2MarginLeft=0x0086,
    /** view button 2 margin right */
    ESkinConstViewButton2MarginRight=0x0087,
    /** view button 3 margin left */
    ESkinConstViewButton3MarginLeft=0x0088,
    /** view button 3 margin right */
    ESkinConstViewButton3MarginRight=0x0089,
    /** view button 4 margin left */
    ESkinConstViewButton4MarginLeft=0x008a,
    /** view button 4 margin right */
    ESkinConstViewButton4MarginRight=0x008b,
    /** view button margin top */
    ESkinConstViewButtonMarginTop=0x008c,
    /** view button margin bottom */
    ESkinConstViewButtonMarginBottom=0x008d,
    /** dialog help margin top */
    ESkinConstDialogHelpMarginTop=0x008e,
    /** dialog help margin right */
    ESkinConstDialogHelpMarginRight=0x008f,
    /** captioned control horizontal margin. Only used in Series 80. */
    ESkinConstCaptionedControlHorizMargin=0x0090,
    /** status pane title area width */
    ESkinConstStatusPaneTitleAreaWidth=0x0091,
    /** choicelist popup horizontal offset */
    ESkinConstChoicelistPopupHorizOffset=0x0092,
    /** search field margin left */
    ESkinConstSearchFieldMarginLeft=0x0093,
    /** search field margin right */
    ESkinConstSearchFieldMarginRight=0x0094,
    /** search field margin top */
    ESkinConstSearchFieldMarginTop=0x0095,
    /** search field margin bottom */
    ESkinConstSearchFieldMarginBottom=0x0096,
    /** time-picker margin left */
    ESkinConstTimePickerMarginLeft=0x0097,
    /** time-picker margin right */
    ESkinConstTimePickerMarginRight=0x0098,
    /** time-picker margin top */
    ESkinConstTimePickerMarginTop=0x0099,
    /** time-picker margin bottom */
    ESkinConstTimePickerMarginBottom=0x009a,
    /** cap control gap between caption and separator */
    ESkinConstCapControlGapBetweenCaptionAndSeparator=0x009b,
    /** cap control prompt margin left */
    ESkinConstCapControlPromptMarginLeft=0x009c,
    /** cap control prompt margin right */
    ESkinConstCapControlPromptMarginRight=0x009d,
    /** MFNE height */
    ESkinConstMfneHeight=0x009e,
    /** MFNE baseline */
    ESkinConstMfneBaseline=0x009f,
    /** focus rect margin top */
    ESkinConstFocusRectMarginTop=0x00a0,
    /** focus rect margin bottom */
    ESkinConstFocusRectMarginBottom=0x00a1,
    /** cap control gap between ear and component */
    ESkinConstCapControlGapBetweenEarAndComponent=0x00a2,
    /** infoprint margin left */
    ESkinConstInfoPrintMarginLeft=0x00a3,
    /** infoprint margin right */
    ESkinConstInfoPrintMarginRight=0x00a4,
    /** infoprint margin top */
    ESkinConstInfoPrintMarginTop=0x00a5,
    /** infoprint margin bottom */
    ESkinConstInfoPrintMarginBottom=0x00a6,
    /** status pane large indicators x */
    ESkinConstStatusPaneLargeIndicatorsX=0x00a7,
    /** status pane large indicator width DEPRECATED */
    //ESkinConstStatusPaneLargeIndicatorWidth=0x00a8,
    /** status pane small indicators x */
    ESkinConstStatusPaneSmallIndicatorsX=0x00aa,
    /** status pane small indicator width DEPRECATED */
    //ESkinConstStatusPaneSmallIndicatorWidth=0x00ab,
    /** command bar button label width */
    ESkinConstCommandBarButtonLabelWidth=0x00ac,
    /** command bar button label height */
    ESkinConstCommandBarButtonLabelHeight=0x00ad,
    /** status pane placeholder total */
    ESkinConstStatusPanePlaceholderTotal=0x00ae,
    /** digit flipper width */
    ESkinConstDigitFlipperWidth=0x00af,
    /** digit flipper height */
    ESkinConstDigitFlipperHeight=0x00b0,
    /** listbox gap between mark and text */
    ESkinConstListboxGapBetweenMarkAndText=0x00b1,
    /** time-picker digit baseline offset */
    ESkinConstTimePickerDigitBaselineOffset=0x00b2,
    /** time-picker am pm width */
    ESkinConstTimePickerAmPmWidth=0x00b3,
    /** time-picker am pm height */
    ESkinConstTimePickerAmPmHeight=0x00b4,
    /** color selector width */
    ESkinConstColourSelectorWidth=0x00b5,
    /** color selector height */
    ESkinConstColourSelectorHeight=0x00b6,
    /** status pane priority call */
    ESkinConstStatusPanePriorityCall=0x00b7,                    // MX priority 01; STA-ICO002,003,004,005,006,034;
    /** if set, the location of an agenda item is shown in the alarm notifier */
    KSkinConstAlarmShowLocation=0x00b8,
    /** status pane priority selected line */
    ESkinConstStatusPanePrioritySelectedLine=0x00b9,            // MX priority 05; STA-ICO012,013;
    /** status pane priority call forwarding */
    ESkinConstStatusPanePriorityCallForwarding=0x00ba,          // MX priority 06; STA-ICO014,015,016,017,018;
    /** status pane priority Bluetooth */
    ESkinConstStatusPanePriorityBluetooth=0x00bb,               // MX priority 10; STA-ICO026;
    /** status pane priority USB */
    ESkinConstStatusPanePriorityUsb=0x00bc,                     // MX priority 11; STA-ICO027;
    /** ITU9 delete width */
    ESkinConstItu9DeleteWidth=0x00bd,
    /** allows the pop-out arrow to be displayed or not */
    ESkinConstSeries80ChoicelistBehaviour=0x00be,
    /** ITU9 delete height */
    ESkinConstItu9DeleteHeight=0x00bf,
    /** status pane priority voice mail */
    ESkinConstStatusPanePriorityVoiceMail=0x00c0,               // MX priority 09; STA-ICO021,022,024,025;
    /** dialog title width maximum */
    ESkinConstDialogTitleWidthMax=0x00c1,
    /** mask red */
    ESkinConstMaskRed=0x00c2,
    /** mask green */
    ESkinConstMaskGreen=0x00c3,
    /** mask blue */
    ESkinConstMaskBlue=0x00c4,
    /** scrollbar default breadth */
    ESkinConstScrollBarDefaultBreadth=0x00c5,
    /** scrollbar button breadth */
    ESkinConstScrollBarButtonBreadth=0x00c6,
    /** scrollbar arrow head button breadth */
    ESkinConstScrollBarArrowHeadButtonBreadth=0x00c7,
    /** cap control ear height */
    ESkinConstCapControlEarHeight=0x00c8,
    /** infoprint text block x offset */
    ESkinConstInfoPrintTextBlockXOffset=0x00c9,
    /** infoprint text block y offset */
    ESkinConstInfoPrintTextBlockYOffset=0x00ca,
    /** control bar top and bottom border thickness */
    ESkinConstControlBarTopAndBottomBorderThickness=0x00cb,
    /** menu show hotkeys */
    ESkinConstMenuShowHotkeys=0x00cc,
    /** dialog tab margin left */
    ESkinConstDialogTabMarginLeft=0x00cd,
    /** dialog tab margin top */
    ESkinConstDialogTabMarginTop=0x00ce,
    /** dialog tab margin right */
    ESkinConstDialogTabMarginRight=0x00cf,
    /** dialog tab margin bottom */
    ESkinConstDialogTabMarginBottom=0x00d0,
    /** dialog page margin left */
    ESkinConstDialogPageMarginLeft=0x00d1,
    /** dialog page margin right */
    ESkinConstDialogPageMarginRight=0x00d2,
    /** dialog page margin bottom */
    ESkinConstDialogPageMarginBottom=0x00d3,
    /** status pane small indicator gap DEPRECATED */
    //ESkinConstStatusPaneSmallIndicatorGap=0x00d4,
    /** status pane large indicator height DEPRECATED */
    //ESkinConstStatusPaneLargeIndicatorHeight=0x00d5,
    /** status pane priority silent profile */
    ESkinConstStatusPanePrioritySilentProfile=0x00d6,           // MX priority 03; STA-ICO009
    /** status pane large indicator gap DEPRECATED */
    //ESkinConstStatusPaneLargeIndicatorGap=0x00d7,
    /** status pane small indicator height DEPRECATED */
    //ESkinConstStatusPaneSmallIndicatorHeight=0x00d8,
    /** cap control ear width */
    ESkinConstCapControlEarWidth=0x00d9,
    /** dialog gap between columns */
    ESkinConstDialogGapBetweenColumns=0x00da,
    /**
     * <code>0</code> means the tab key is consumed by stock control.
     * <code>1</code> means the tab key is consumed by the dialog or form
     */
    ESkinConstTabKeyMovesFocus=0x00db,
    /** dialog maximum width */
    ESkinConstDialogMaxWidth=0x00dc,
    /** columned text alignment margin */
    ESkinConstColumnedTextTextAlignmentMargin=0x00dd,
    /** columned text inter text gap */
    ESkinConstColumnedTextInterTextGap=0x00de,
    /** columned text control margin top */
    ESkinConstColumnedTextControlMarginTop=0x00df,
    /** columned text control margin bottom */
    ESkinConstColumnedTextControlMarginBottom=0x00e0,
    /** columned text control margin left */
    ESkinConstColumnedTextControlMarginLeft=0x00e1,
    /** columned text control margin right */
    ESkinConstColumnedTextControlMarginRight=0x00e2,
    /** infoprint line height */
    ESkinConstInfoPrintLineHeight=0x00e3,
    /** checkbox width */
    ESkinConstCheckboxWidth=0x00e4,
    /** checkbox height */
    ESkinConstCheckboxHeight=0x00e5,
    /** priority of the zone indicator, STA-ICO007 */
    ESkinConstStatusPanePriorityZone=0x00e6,
    /** priority of the fax modem indicator, STA-ICO028 */
    ESkinConstStatusPanePriorityFaxModem=0x00e7,
    /** status pane priority streamer */
    ESkinConstStatusPanePriorityStreamer=0x00e8,                // MX priority 16; STA-ICO033
    /** checkbox margin left */
    ESkinConstCheckboxMarginLeft=0x00e9,
    /** checkbox margin right */
    ESkinConstCheckboxMarginRight=0x00ea,
    /** status pane priority accessory */
    ESkinConstStatusPanePriorityAccessory=0x00eb,               // MX priority 15; STA-ICO031,032
    /** listbox gap between columns */
    ESkinConstListboxGapBetweenColumns=0x00ec,
    /** status pane priority keypad lock */
    ESkinConstStatusPanePriorityKeypadLock=0x00ed,              // MX priority 13; STA-ICO029
    /**
     * status pane priority alarm. If set to 0, there is no indicator for the
     * alarm
     */
    ESkinConstStatusPanePriorityAlarm=0x00ee,                   // MX priority 14; STA-ICO030,
    /** status pane priority volume handling */
    ESkinConstStatusPanePriorityVolumeHandling=0x00ef,          // MX priority 04; STA-ICO010,011
    /** volume bar horizontal start position from left */
    ESkinConstVolumeBarHorizStartPositionFromLeft=0x00f0,
    /** volume bar horizontal end position from right */
    ESkinConstVolumeBarHorizEndPositionFromRight=0x00f1,
    /** volume bar horizontal left margin */
    ESkinConstVolumeBarHorizLeftMargin=0x00f2,
    /** volume bar horizontal right margin */
    ESkinConstVolumeBarHorizRightMargin=0x00f3,
    /** volume bar horizontal gap from mute to left arrow */
    ESkinConstVolumeBarHorizGapFromMuteToLeftArrow=0x00f4,
    /** volume bar vertical start position from top */
    ESkinConstVolumeBarVertStartPositionFromTop=0x00f5,
    /** volume bar vertical end position from bottom */
    ESkinConstVolumeBarVertEndPositionFromBottom=0x00f6,
    /** volume bar vertical top margin */
    ESkinConstVolumeBarVertTopMargin=0x00f7,
    /** volume bar vertical bottom margin */
    ESkinConstVolumeBarVertBottomMargin=0x00f8,
    /** volume bar vertical gap from mute to up arrow */
    ESkinConstVolumeBarVertGapFromMuteToUpArrow=0x00f9,
    /** icon with text horizontal gap to bitmap */
    ESkinConstIconWithTextHorizontalGapToBitmap=0x00fa,
    /** icon with text horizontal text alignment gap */
    ESkinConstIconWithTextHorizontalTextAlignmentGap=0x00fb,
    /** icon with text height */
    ESkinConstIconWithTextHeight=0x00fc,
    /** icon with text baseline */
    ESkinConstIconWithTextBaseline=0x00fd,
    /** horizontal scrollbar margin */
    ESkinConstHorizScrollBarMargin=0x00fe,
    /** vertical scrollbar margin */
    ESkinConstVertScrollBarMargin=0x00ff,
    /** note contents margin left */
    ESkinConstNoteContentsMarginLeft=0x0100,
    /** note contents margin right */
    ESkinConstNoteContentsMarginRight=0x0101,
    /** note contents margin top */
    ESkinConstNoteContentsMarginTop=0x0102,
    /** note contents margin bottom */
    ESkinConstNoteContentsMarginBottom=0x0103,
    /** note contents text margin left */
    ESkinConstNoteContentsTextMarginLeft=0x0104,
    /** note contents text margin right */
    ESkinConstNoteContentsTextMarginRight=0x0105,
    /** note contents text margin top */
    ESkinConstNoteContentsTextMarginTop=0x0106,
    /** note contents text margin bottom */
    ESkinConstNoteContentsTextMarginBottom=0x0107,
    /** note contents icon margin left */
    ESkinConstNoteContentsIconMarginLeft=0x0108,
    /** note contents icon margin right */
    ESkinConstNoteContentsIconMarginRight=0x0109,
    /** note contents icon margin top */
    ESkinConstNoteContentsIconMarginTop=0x010a,
    /** note contents icon margin bottom */
    ESkinConstNoteContentsIconMarginBottom=0x010b,
    /** note contents text line spacing */
    ESkinConstNoteContentsTextLineSpacing=0x010c,
    /** note contents minimum width */
    ESkinConstNoteContentsMinimumWidth=0x010d,
    /** note contents minimum height */
    ESkinConstNoteContentsMinimumHeight=0x010e,
    /** height zoom level 1 */
    ESkinConstHeightZoomLevel1=0x010f,
    /** height zoom level 2 */
    ESkinConstHeightZoomLevel2=0x0110,
    /** height zoom level 3 */
    ESkinConstHeightZoomLevel3=0x0111,
    /** baseline zoom level 1 */
    ESkinConstBaselineZoomLevel1=0x0112,
    /** baseline zoom level 2 */
    ESkinConstBaselineZoomLevel2=0x0113,
    /** baseline zoom level 3 */
    ESkinConstBaselineZoomLevel3=0x0114,
    /** choicelist height */
    ESkinConstChoicelistHeight=0x115,
    /** choicelist baseline */
    ESkinConstChoicelistBaseline=0x116,
    /** secret editor height */
    ESkinConstSecretEditorHeight=0x117,
    /** secret editor baseline */
    ESkinConstSecretEditorBaseline=0x118,
    /** dialog help button width */
    ESkinConstDialogHelpButtonWidth=0x119,
    /** dialog help button height */
    ESkinConstDialogHelpButtonHeight=0x11a,
    /** dialog clipboard button width */
    ESkinConstDialogClipboardButtonWidth=0x11b,
    /** dialog clipboard button height */
    ESkinConstDialogClipboardButtonHeight=0x11c,
    /** dialog clipboard margin top */
    ESkinConstDialogClipboardMarginTop=0x11d,
    /** dialog clipboard margin left */
    ESkinConstDialogClipboardMarginLeft=0x11e,
    /** label height */
    ESkinConstLabelHeight=0x11f,
    /** label baseline */
    ESkinConstLabelBaseline=0x120,
    /** call header button 1 margin left */
    ESkinConstCallHeaderButton1MarginLeft=0x121,
    /** call header button 1 margin right */
    ESkinConstCallHeaderButton1MarginRight=0x122,
    /** call header button 2 margin left */
    ESkinConstCallHeaderButton2MarginLeft=0x123,
    /** call header button 2 margin right */
    ESkinConstCallHeaderButton2MarginRight=0x124,
    /** call header button 3 margin left */
    ESkinConstCallHeaderButton3MarginLeft=0x125,
    /** call header button 3 margin right */
    ESkinConstCallHeaderButton3MarginRight=0x126,
    /** call header button 4 margin left */
    ESkinConstCallHeaderButton4MarginLeft=0x127,
    /** call header button 4 margin right */
    ESkinConstCallHeaderButton4MarginRight=0x128,
    /** call header button margin top */
    ESkinConstCallHeaderButtonMarginTop=0x129,
    /** call header button margin bottom */
    ESkinConstCallHeaderButtonMarginBottom=0x12a,
    /**
     * if set to <code>0</code>, the C drive, MMC drive, and ROM drive use a
     * different tab; if set to <code>1</code>, no tabs are used and the drives
     * appear on one tab
     */
    ESkinConstDrivesOnOneTab=0x12b,
    /** status pane title alignment */
    ESkinConstStatusPaneTitleAlignment=0x12c,
    /** status pane priority inbox */
    ESkinConstStatusPanePriorityInbox=0x012d,               // MX priority 07; STA-ICO019
    /** status pane priority outbox */
    ESkinConstStatusPanePriorityOutbox=0x012e,              // MX priority 08; STA-ICO020
    /** status pane supports wide pane mode */
    ESkinConstStatusPaneSupportsWidePaneMode=0x12F,
    /** status pane wide mode large indicator width DEPRECATED */
    //ESkinConstStatusPaneWideModeLargeIndicatorWidth=0x130,
    /** status pane wide mode large indicator height DEPRECATED */
    //ESkinConstStatusPaneWideModeLargeIndicatorHeight=0x131,
    /** status pane wide mode vertical offset large icon DEPRECATED */
    //ESkinConstStatusPaneWideModeVertOffsetLargeIcon=0x132,
    /** status pane wide mode large indicators x DEPRECATED */
    //ESkinConstStatusPaneWideModeLargeIndicatorsX=0x133,
    /** status pane wide mode large indicator gap DEPRECATED */
    //ESkinConstStatusPaneWideModeLargeIndicatorGap=0x134,
    /** status pane wide mode small indicator width DEPRECATED */
    //ESkinConstStatusPaneWideModeSmallIndicatorWidth=0x135,
    /** status pane wide mode small indicator height DEPRECATED */
    //ESkinConstStatusPaneWideModeSmallIndicatorHeight=0x136,
    /** status pane wide mode vertical offset small icon DEPRECATED */
    //ESkinConstStatusPaneWideModeVertOffsetSmallIcon=0x137,
    /** status pane wide mode small indicators x DEPRECATED */
    //ESkinConstStatusPaneWideModeSmallIndicatorsX=0x138,
    /** status pane wide mode small indicator gap. S80V2 only - deprecated in convergence. */
    ESkinConstStatusPaneWideModeSmallIndicatorGap=0x139,
    /** screen preferred width */
    ESkinConstScreenPreferedWidth=0x13A,
    /** screen preferred height */
    ESkinConstScreenPreferedHeight=0x13B,
    /** dialogs have no help button */
    ESkinConstDialogsHaveNoHelpButton=0x013C,
    /** search field icon left aligned */
    ESkinConstSearchFieldIconLeftAligned=0x13D,
    /** shrink client rect for tool band */
    ESkinConstShrinkClientRectForToolBand=0x13E,
    /** mover left margin */
    ESkinConstMoverLeftMargin=0x13f,
    /** dialog buttons on CBA */
    ESkinConstDialogButtonsOnCBA=0x140,
    /** status pane allow fading */
    ESkinConstStatusPaneAllowFading=0x141,
    /** status pane priority synchronization */
    ESkinConstStatusPanePrioritySyncronization=0x142,
    /** LAF labeled button label alignment */
    ESkinConstLafLabeledButtonLabelAlignment=0x143,
    /** clock on CBA */
    ESkinConstClockOnCBA=0x144,
    /** CBA has default command */
    ESkinConstCbaHasDefaultCommand=0x145,
    /** button panel use background */
    ESkinConstButtonPanelUseBackground=0x146,
    /** button panel vertical buttons at bottom */
    ESkinConstButtonPanelVerticalButtonsAtBottom=0x147,
    /** command button transparent */
    ESkinConstCommandButtonTransparent=0x148,
    /** <code>CEikCommandButton</code> base fixed height */
    ESkinConstCEikCommandButtonBaseFixedHeight=0x149,
    /** control group transparent */
    ESkinConstControlGroupTransparent=0x14a,
    /** label transparent */
    ESkinConstLabelTransparent=0x14b,
    /** labeled button transparent */
    ESkinConstLabeledButtonTransparent=0x14c,
    /** dialog button transparent */
    ESkinConstDialogButtonTransparent=0x14d,
    /** background button panel location */
    ESkinConstBgButtonPanelLocation=0x14e,
    /** status pane vertical */
    ESkinConstStatusPaneVertical=0x14f,
    /** default application view */
    ESkinConstDefaultAppView=0x150,
    /** menu bar horizontal */
    ESkinConstMenuBarHorizontal=0x151,
    /** command bar separate */
    ESkinConstCommandBarSeparate=0x152,
    /** command bar faded */
    ESkinConstCommandBarFaded=0x153,
    /** menu bar highlight */
    ESkinConstMenuBarHighlight=0x154,
    /** menu pane has CBA */
    ESkinConstMenuPaneHasCba=0x155,
    /** controls can have CBA */
    ESkinConstWidgetsCanHaveCba=0x156,
    /** tasks list in menu */
    ESkinTasksListInMenu=0x157,
    /** Ckon application title */
    ESkinConstCkonAppTitle=0x158,
    /** offset between menu pane and menu pane title */
    ESkinConstOffsetBetweenMenuPaneAndMenuPaneTitle=0x159,
    /** parse scan delay */
    ESkinConstParseScanDelay=0x15a,
    /** status pane priority profile name */
    ESkinConstStatusPanePriorityProfileName=0x15b,
    /** menu key wrap around */
    ESkinConstMenuKeyWrapAround=0x15c,
    /** find dim unusable buttons */
    ESkinConstFindDimUnusableButtons=0x15d,
    /** cancel dialog button position */
    ESkinConstCancelDialogButtonPos=0x15e,
    /** status pane use four bar indicators */
    ESkinConstStatusPaneUseFourBarIndicators=0x15f,
    /** un-used */
/*    ESkinConstStatusPane...=0x160,*/
    /** dialog clipboard menu offset */
    ESkinConstDialogClipboardMenuOffset=0x161,
    /** multi-page selector bottom margin to buttons */
    ESkinConstMultiPageSelectorBottomMarginToButtons=0x162,
    /** multi-page selector bottom margin */
    ESkinConstMultiPageSelectorBottomMargin=0x163,
    /** multi-page selector right margin to buttons */
    ESkinConstMultiPageSelectorRightMarginToButtons=0x164,
    /** single page selector bottom margin to buttons */
    ESkinConstSinglePageSelectorBottomMarginToButtons=0x165,
    /** single page selector bottom margin */
    ESkinConstSinglePageSelectorBottomMargin=0x166,
    /** single page selector right margin to buttons */
    ESkinConstSinglePageSelectorRightMarginToButtons=0x167,
    /** edwin margin top */
    ESkinConstEdwinMarginTop=0x168,
    /** edwin margin bottom */
    ESkinConstEdwinMarginBottom=0x169,
    /** control border margin left */
    ESkinConstControlBorderMarginLeft=0x16a,
    /** control border margin right */
    ESkinConstControlBorderMarginRight=0x16b,
    /** control border margin top */
    ESkinConstControlBorderMarginTop=0x16c,
    /** control border margin bottom */
    ESkinConstControlBorderMarginBottom=0x16d,
    /** button line height */
    ESkinConstButtonLineHeight=0x16e,
    /** button baseline */
    ESkinConstButtonBaseline=0x16f,
    /** infoprint wrapping width */
    ESkinConstInfoPrintWrappingWidth=0x0170,
    /** pop-out top scroll arrow gap to pop-out edge */
    ESkinConstPopoutTopScrollArrowGapToPopoutEdge=0x0171,
    /** pop-out top scroll arrow gap to first item */
    ESkinConstPopoutTopScrollArrowGapToFirstItem=0x0172,
    /** pop-out bottom scroll arrow gap to pop-out edge */
    ESkinConstPopoutBottomScrollArrowGapToPopoutEdge=0x0173,
    /** pop-out bottom scroll arrow gap to last item */
    ESkinConstPopoutBottomScrollArrowGapToLastItem=0x0174,
    /** note contents wrapping width */
    ESkinConstNoteContentsWrappingWidth=0x0175,
    /** line spacing in pixels */
    ESkinConstLineSpacingInPixels=0x0176,
    /** time-picker gap between hours and minutes */
    ESkinConstTimePickerGapBetweenHoursAndMinutes=0x0177,
    /** menu cascade width */
    ESkinConstMenuCascadeWidth=0x0178,
    /** time-picker gap between flipper and top arrow */
    ESkinConstTimePickerGapBetweenFlipperAndTopArrow=0x0179,
    /** time-picker gap between flipper and bottom arrow */
    ESkinConstTimePickerGapBetweenFlipperAndBottomArrow=0x017a,
    /** digit flipper tens arrow margin left */
    ESkinConstDigitFlipperTensArrowMarginLeft=0x017b,
    /** digit flipper inter arrow gap */
    ESkinConstDigitFlipperInterArrowGap=0x017c,
    /** digit flipper single arrow margin left */
    ESkinConstDigitFlipperSingleArrowMarginLeft=0x017d,
    /** time-picker gap between flipper and close button */
    ESkinConstTimePickerGapBetweenFlipperAndCloseButton=0x017e,
    /** time-picker am/pm vertical offset */
    ESkinConstTimePickerAmPmVerticalOffset=0x017f,
    /** time-picker space between time and am pm */
    ESkinConstTimePickerSpaceBetweenTimeAndAmPm=0x0180,
    /** menu left adornment width */
    ESkinConstMenuLeftAdornmentWidth=0x181,
    /** calendar month name baseline */
    ESkinConstCalendarMonthNameBaseline=0x182,
    /** menu pane maximum width of text in pixels */
    ESkinConstMenuPaneMaxWidthOfTextInPixels=0x183,
    /** menu pane vertical offset in pixels */
    ESkinConstMenuPaneVerticalOffsetInPixels=0x184,
    /**
     * edwin auto scroll on focus change. Defines default behavior;
     * <code>0</code> = not enabled, <code>1</code>=enabled
     */
    ESkinConstEdwinAutoScrollOnFocusChange=0x185,
    /** fade behind menu */
    ESkinConstFadeBehindMenu=0x186,
    /** fade behind dialog */
    ESkinConstFadeBehindDialog=0x187,
    /** fade application when in background */
    ESkinConstFadeAppWhenInBackground=0x188,
    /** status pane alarm indicator on clock */
    ESkinConstStatusPaneAlarmIndicatorOnClock=0x189,
    /** status pane priority PDA */
    ESkinConstStatusPanePriorityPda = 0x018a,
    /** status pane priority computer */
    ESkinConstStatusPanePriorityComputer = 0x018b,
    /** status pane priority IP pass through */
    ESkinConstStatusPanePriorityIPPassThrough = 0x018c,
    /** status pane priority no CS calls */
    ESkinConstStatusPanePriorityNoCSCalls = 0x018d,
    /** status pane priority mute */
    ESkinConstStatusPanePriorityMute = 0x018e,
    /**
     * disable dialog button hotkey indicator: <code>0</code> = allow dialog
     * buttons to indicate hotkey; <code>1</code> = do not allow
     */
    ESkinConstDisableDialogButtonHotkeyIndicator=0x018f,
    /** text baseline for the weekday picker */
    ESkinConstDayPickerCellTextBaseline=0x0190,
    /** calendar highlight horizontal margin */
    ESkinConstCalendarHighlightHorizontalMargin=0x191,
    /** calendar highlight vertical margin */
    ESkinConstCalendarHighlightVerticalMargin=0x192,
    /** calendar round rect corner */
    ESkinConstCalendarRoundRectCorner=0x193,
    /** calendar week separator line width */
    ESkinConstCalendarWeekSepLineWidth=0x194,
    /** calendar week separator line margin */
    ESkinConstCalendarWeekSepLineMargin=0x195,
    /** calendar buttons on dialog */
    ESkinConstCalendarButtonsOnDialog=0x196,
    /** calendar shadow title */
    ESkinConstCalendarShadowTitle=0x197,
    /** calendar draw dimmed days */
    ESkinConstCalendarDrawDimmedDays=0x198,
    /** calendar vertical space above year */
    ESkinConstCalendarVerticalSpaceAboveYear=0x199,
    /** calendar vertical space between year and top row of months */
    ESkinConstCalendarVerticalSpaceBetweenYearAndTopRowOfMonths=0x19a,
    /** calendar vertical space beneath bottom row of months */
    ESkinConstCalendarVerticalSpaceBeneathBottomRowOfMonths=0x19b,
    /** calendar horizontal space on each side of month matrix */
    ESkinConstCalendarHorizontalSpaceOnEachSideOfMonthMatrix=0x19c,
    /** calendar vertical space between day name initials and top row of days */
    ESkinConstCalendarVerticalSpaceBetweenDayNameInitialsAndTopRowOfDays=0x19d,
    /** calendar vertical space between each row of days */
    ESkinConstCalendarVerticalSpaceBetweenEachRowOfDays=0x19e,
    /** calendar horizontal space between each column of days */
    ESkinConstCalendarHorizontalSpaceBetweenEachColumnOfDays=0x19f,
    /** calendar number of cells in day matrix */
    ESkinConstCalendarNumberOfCellsInDayMatrix=0x1a0,
    /** calendar number of rows of days */
    ESkinConstCalendarNumberOfRowsOfDays=0x1a1,
    /** calendar week separator gap */
    ESkinConstCalendarWeekSepGap=0x1a2,
    /** calendar button side margin */
    ESkinConstCalendarButtonSideMargin=0x1a3,
    /** calendar between button space */
    ESkinConstCalendarBetweenButtonSpace=0x1a4,
    /** calendar left button width */
    ESkinConstCalendarLeftButtonWidth=0x1a5,
    /** calendar right button width */
    ESkinConstCalendarRightButtonWidth=0x1a6,
    /** calendar gap between buttons */
    ESkinConstCalendarIntraButtonGap=0x1a7,
    /** calendar day cell width */
    ESkinConstCalendarDayCellWidth=0x1a8,
    /** calendar day cell height */
    ESkinConstCalendarDayCellHeight=0x1a9,
    /** calendar title alignment */
    ESkinConstCalendarTitleAlignment=0x1aa,
    /** calendar horizontal space before year */
    ESkinConstCalendarHorizontalSpaceBeforeYear=0x1ab,
    /** calendar month name height */
    ESkinConstCalendarMonthNameHeight=0x1ac,
    /** parsers trigger CBA */
    ESkinConstParsersTriggerCba=0x1ad,
    /** skin bitmap hue shift */
    ESkinConstSkinBitmapHueShift=0x1ae,
    /** skin color hue shift */
    ESkinConstSkinColorHueShift=0x1af,
    /** ideal pixels above found string */
    ESkinConstIdealPixelsAboveFoundString=0x01b0,
    /** seek bar small left margin */
    ESkinConstSeekBarSmallLeftMargin=0x01b1,
    /** seek bar small right margin */
    ESkinConstSeekBarSmallRightMargin=0x01b2,
    /** seek bar small time box horizontal offset */
    ESkinConstSeekBarSmallTimeBoxHorizontalOffset=0x01b3,
    /** seek bar small time box left and right border */
    ESkinConstSeekBarSmallTimeBoxLeftAndRightBorder=0x01b4,
    /** seek bar small time box top and bottom border */
    ESkinConstSeekBarSmallTimeBoxTopAndBottomBorder=0x01b5,
    /** seek bar small start position from left */
    ESkinConstSeekBarSmallStartPositionFromLeft=0x01b6,
    /** seek bar small end position from right */
    ESkinConstSeekBarSmallEndPositionFromRight=0x01b7,
    /** secret editor hide character delay */
    ESkinConstSecretEditorHideCharacterDelay=0x01b8,
    /**
     * secret editor hide character mode: <code>0</code> = always hide the
     * character immediately; <code>1</code> = hide the character immediately, if FEP is not
     * handwriting recognition window; <code>2</code> = display the character
     * and then hide it
     */
    ESkinConstSecretEditorHideCharacterMode=0x01b9,
    /** seek bar small border left */
    ESkinConstSeekBarSmallBorderLeft=0x01ba,
    /** seek bar small border right */
    ESkinConstSeekBarSmallBorderRight=0x01bb,
    /** volume bar horizontal small start position from left */
    ESkinConstVolumeBarHorizSmallStartPositionFromLeft=0x01bc,
    /** volume bar horizontal small end position from right */
    ESkinConstVolumeBarHorizSmallEndPositionFromRight=0x01bd,
    /** volume bar horizontal small left margin */
    ESkinConstVolumeBarHorizSmallLeftMargin=0x01be,
    /** volume bar horizontal small right margin */
    ESkinConstVolumeBarHorizSmallRightMargin=0x01bf,
    /** volume bar horizontal small gap from mute to left arrow */
    ESkinConstVolumeBarHorizSmallGapFromMuteToLeftArrow=0x01c0,
    /** volume bar small border left */
    ESkinConstVolumeBarSmallBorderLeft=0x01c1,
    /** volume bar small border right */
    ESkinConstVolumeBarSmallBorderRight=0x01c2,
    /** edwin has visible baseline */
    ESkinConstEdwinHasVisibleBaseline=0x01c3,
    /** expand Save as dialog */
    ESkinConstExpandSaveAsDialog=0x01c4,
    /**
     * whether the listbox has yes/no: <code>0</code> = checkboxes should be
     * used; <code>1</code> = Yes/No should be used (9210 style)
     */
    ESkinConstListBoxHasYesNo=0x01c5,
    /**
     * listbox selection mark location: <code>0</code> = mark is left of the
     * text; <code>1</code> = mark is right of the text
     */
    ESkinConstListBoxSelectionMarkLocation=0x01c6,
    /**
     * listbox default mark column width: <code>0</code> = the value of
     * <code>ESkinConstCheckboxWidth</code> is used
     */
    ESkinConstListBoxDefaultMarkColumnWidth=0x01c7,
    /**
     * listbox text mark separator: <code>0</code> = no separator; <code>1</code>
     * = use bitmap provided by the skin
     */
    ESkinConstListBoxTextMarkSeparator=0x01c8,
    /** cap control gap between separator and control */
    ESkinConstCapControlGapBetweenSeparatorAndControl=0x01c9,
    /** cap control use separator bitmap */
    ESkinConstCapControlUseSeparatorBitmap=0x01ca,
    /** cap control separator width */
    ESkinConstCapControlSeparatorWidth=0x01cb,
    /** cap control separator height */
    ESkinConstCapControlSeparatorHeight=0x01cc,
    /** menu pane maximum items */
    ESkinConstMenuPaneMaxItems=0x01cd,
    /** menu pane left aligned scroller */
    ESkinConstMenuPaneLeftAlignedScroller=0x01ce,
    /**
     * listbox pop-out has scrollbar: <code>0</code> = <code>EPopout</code>
     * style uses up and down arrows; <code>1</code> = <code>EPopout</code>
     * style uses scrollbar
     */
    ESkinConstListBoxPopoutHasScrollBar=0x01cf,
    /** dialog clipboard required */
    ESkinConstDialogClipboardRequired=0x01d0,
    /** dialog cyclic navigation */
    ESkinConstDialogCyclicNavigation=0x01d1,
    /** is dialog title 3D text */
    ESkinConstIsDialogTitle3DText=0x01d2,
    /** support double height application title: <code>)</code> or <code>1</code> */
    ESkinConstSupportDoubleHeightAppTitle=0x01d3,
    /**
     * is MFNE icon left aligned: <code>0</code> = false, or <code>1</code> =
     * true
     */
    ESkinConstIsMfneIconLeftAligned=0x01d4,
    /**
     * long menu key press: <code>0</code> if not enabled; otherwise time in
     * seconds
     */
    ESkinConstLongMenuKeypress=0x01d5,
    /**
     * MFNE time editor do not allow pop-out: <code>0</code> if pop-out allowed;
     * <code>1</code> if not allowed
     */
    ESkinConstMfneTimeEditorDontAllowPopout=0x01d6,
    /** touch screen support: <code>0</code> or <code>1</code> */
    ESkinConstTouchScreenSupport=0x01d7,
    /** title shadow text: <code>0</code> or <code>1</code> */
    ESkinConstTitleShadowText=0x01d8,
    /** volume bar vertical gap from slider limit to slider fill */
    ESkinConstVolumeBarVertGapFromSliderLimitToSliderFill=0x01d9,
    /** volume bar vertical gap from background edge to slider fill */
    ESkinConstVolumeBarVertGapFromBackgroundEdgeToSliderFill=0x01da,
    /** volume bar horizontal gap from slider limit to slider fill */
    ESkinConstVolumeBarHorizGapFromSliderLimitToSliderFill=0x01db,
    /** volume bar horizontal gap from background edge to slider fill */
    ESkinConstVolumeBarHorizGapFromBackgroundEdgeToSliderFill=0x01dc,
    /** volume bar horizontal small gap from slider limit to slider fill */
    ESkinConstVolumeBarHorizSmallGapFromSliderLimitToSliderFill=0x01de,
    /** volume bar horizontal small gap from background edge to slider fill */
    ESkinConstVolumeBarHorizSmallGapFromBackgroundEdgeToSliderFill=0x01df,
    /** seek bar slider length */
    ESkinConstSeekBarSliderLength=0x01e0,
    /** seek bar slider length small */
    ESkinConstSeekBarSliderLengthSmall=0x01e1,
    /** seek bar gap from slider limit to slider fill */
    ESkinConstSeekBarGapFromSliderLimitToSliderFill=0x01e2,
    /** seek bar gap from background edge to slider fill */
    ESkinConstSeekBarGapFromBackgroundEdgeToSliderFill=0x01e3,
    /** seek bar small gap from slider limit to slider fill */
    ESkinConstSeekBarSmallGapFromSliderLimitToSliderFill=0x01e4,
    /** seek bar small gap from background edge to slider fill */
    ESkinConstSeekBarSmallGapFromBackgroundEdgeToSliderFill=0x01e5,
    /** skin bitmap saturation shift */
    ESkinConstSkinBitmapSaturationShift=0x1e6,
    /** skin color saturation shift */
    ESkinConstSkinColorSaturationShift=0x1e7,
    /** skin bitmap luminosity shift */
    ESkinConstSkinBitmapLuminosityShift=0x1e8,
    /** skin color luminosity shift */
    ESkinConstSkinColorLuminosityShift=0x1e9,
    /** default iconic door width */
    ESkinConstDefaultIconicDoorWidth=0x1ea,
    /** default iconic door height */
    ESkinConstDefaultIconicDoorHeight=0x1eb,
    /** progress bar horizontal offset from the right border */
    ESkinConstProgressBarHorizontalOffset=0x1ec,
    /** progress bar vertical offset from the top border */
    ESkinConstProgressBarVerticalOffset=0x1ed,
    /** listbox Series 80 key events */
    ESkinConstListBoxSeries80KeyEvents=0x1ee,
    /** status pane priority WLAN available */
    ESkinConstStatusPanePriorityWLanAvailable=0x1ef,
    /** status pane priority WLAN active */
    ESkinConstStatusPanePriorityWLanActive=0x1f0,
    /** status pane priority WLAN secure */
    ESkinConstStatusPanePriorityWLanSecure=0x1f1,
    /** status pane priority IR connecting */
    ESkinConstStatusPanePriorityIrConnecting=0x1f2,
    /** status pane priority IR connection ok */
    ESkinConstStatusPanePriorityIrConnectionOk=0x1f3,
    /** status pane priority IR blocked */
    ESkinConstStatusPanePriorityIrBlocked=0x1f4,
    /** status pane priority GPRS attached */
    ESkinConstStatusPanePriorityGprsAttached=0x1f5,
    /** status pane priority GPRS act */
    ESkinConstStatusPanePriorityGprsAct=0x1f6,
    /** status pane priority GPRS suspended */
    ESkinConstStatusPanePriorityGprsSuspended=0x1f7,
    /** dialog tabs overlap */
    ESkinConstDialogTabsOverlap=0x1f8,
    /**
     * dialog default label alignment. The value is defined by the resource
     * struct: <code>0</code> = left, <code>1</code> = center, <code>2</code> =
     * right
     */
    ESkinConstDialogDefaultLabelAlignment=0x1f9,
    /**
     * map linda fonts: <code>1</code> = no 9210 fonts in *.skn / *.bsk;
     * <code>0</code> = load old 9210 fonts from *.skn / *.bsk
     */
    ESkinConstMapLindaFonts=0x1fa,
    /** status pane priority instant messaging */
    ESkinConstStatusPanePriorityInstantMessaging = 0x01fb,
    /** status pane priority presence of service */
    ESkinConstStatusPanePriorityPresenceOfService = 0x01fc,
    /** status pane sort indicators */
    ESkinConstStatusPaneSortIndicators = 0x01fd,
    /**
     * information banner next to CBA. If this flag is set, the information
     * banners appear in front of the CBA instead of in the top right corner
     */
    ESkinConstInformationBannerNextToCBA = 0x01fe,
    /** listbox pop-out maximum text width, in pixels */
    ESkinConstListBoxPopoutMaxTextWidthInPixels = 0x01ff,
    /** input frame margin left */
    ESkinConstInputFrameMarginLeft=0x0200,
    /** input frame margin right */
    ESkinConstInputFrameMarginRight=0x0201,
    /** input frame margin top */
    ESkinConstInputFrameMarginTop=0x0202,
    /** input frame margin bottom */
    ESkinConstInputFrameMarginBottom=0x0203,
    /** input frame use inner rect for central rect drawing */
    ESkinConstInputFrameUseInnerRectForCentralRectDrawing=0x0204,
    /** add to desk requires at least one selection */
    ESkinConstAddToDeskRequiresAtLeastOneSelection=0x0205,
    /** dialog does not send <code>EEikBidOk</code> */
    ESkinConstDialogDoesntSendEEikBidOk=0x0206,
    /** link model uses yes/no */
    ESkinConstLinkModelUsesYesNo=0x0207,
    /** desk background color */
    ESkinConstDeskBackgroundColour=0x0208,
    /**
     * rich text editor uses images: <code>0</code> = Sketch application is used;
     * <code>1</code> = Images application is used
     */
    ESkinConstRichTextEditorUsesImages=0x0209,
    /**
     * alarm notifier has calendar icons: <code>0</code> = there is only one
     * icon for all calendar alarms; <code>1</code> = there is an icon for each
     * type of calendar entry
     */
    ESkinConstAlarmNotifierHasCalendarIcons=0x020a,
    /** link model uses italic font */
    ESkinConstLinkModelUsesItalicFont=0x020b,
    /** status pane priority alternative keyboard */
    ESkinConstStatusPanePriorityAlternativeKbd=0x020c,
    /**
     * menu task switching. If set, pressing chr-tab switches between
     * currently open tasks
     */
    ESkinConstMenuTaskSwitching=0x020d,
    /**
     * dialog line minimum height. The minimum size of a line in a dialog.
     * This is used to avoid lines being too close to each other
     */
    ESkinConstDialogLineMinimumHeight=0x020e,
    /**
     * link model Series 80 behavior. Used for various purposes in
     * <code>LinkModel</code> that behave differently in Series 80
     */
    ESkinConstLinkModelSeries80Behaviour=0x20f,
    /** changes the behavior of <code>EikFileUtils::AbbreviatePath</code> */
    ESkinConstSeries80Abbreviation=0x210,
    /** status pane priority blackberry indicator */
    ESkinConstStatusPanePriorityBlackBerry = 0x0211,
    /** the space between the border and the text in a text listbox */
    ESkinConstListBoxInnerGutter=0x212,
    /** dialog line separator width */
    ESkinConstDialogLineSeparatorWidth=0x213,
    /** dialog line separator spacing above and below line */
    ESkinConstDialogLineSeparatorSpacing=0x214,
    /** seek bar text baseline offset */
    ESkinConstSeekBarBaseline=0x215,
    /**
     * enable PDA Mode: <code>0</code> = device requires SIM to function;
     * <code>1</code> = device operates normally without SIM
     */
    ESkinConstEnablePDAMode=0x216,
    /** Fep input method selection */
    ESkinConstStatusPanePriorityFepInputSelection=0x217,
    /** New folder dialogs */
    ESkinConstNewDialogs=0x218,
	ESkinConstSeries80HierarchicalListBox=0x0219,
	/** The gap between items in a listbox */
	ESkinConstListBoxInterItemVGap=0x21A,
    /** status pane app name enable */
    ESkinConstStatusPaneAppNameEnable=0x21b,
    /** status pane icon horizontal offset */
    ESkinConstStatusPaneIconHorizontalOffset=0x21c,
    
    /** underline editable fields */
    ESkinConstUnderlineEditableFields=0x21d,

    /** Express Menu X position */
    //ESkinConstExpressMenuXPos=0x21e,
    /** Express Menu Y position */
    //ESkinConstExpressMenuYPos=0x21f,
    /** Express Title Tl.X position */
    //ESkinConstExpressMenuTLXPos=0x220,
    /** Express Title Tl.Y position */
    //ESkinConstExpressMenuTLYPos=0x221,
    /** Express Title width */
    //ESkinConstExpressMenuWidth=0x222,
    /** Express Title height */
    //ESkinConstExpressMenuHeight=0x223,
    /** App Title Tl.X position */
    //ESkinConstAppTitleTLXPos=0x224,
    /** App Title Tl.Y position */
    //ESkinConstAppTitleTLYPos=0x225,
    /** App Title Width */
    //ESkinConstAppTitleWidth=0x226,
    /** App Title Height */
    //ESkinConstAppTitleHeight=0x227,

    /** App icon width small */
    //ESkinConstAppIconWidthSmall=0x228,
    /** App icon height small */
    //ESkinConstAppIconHeightSmall=0x229,
    /** App icon width large */
    //ESkinConstAppIconWidthLarge=0x22A,
    /** App icon height large */
    //ESkinConstAppIconHeightLarge=0x22B,
    // !!
    // do not change this value (try to use the spare slots above);
    // do not add constants below this constant
    // !!
    /** terminator */
    ESkinConstTerminator=0x0220
    };

/** scrollbar bitmaps */
const TUid KUidSkinScrollbarBitmaps =   { KUidSkinScrollbarBitmapsValue };
/** progress bitmaps */
const TUid KUidSkinProgressBitmaps =    { KUidSkinProgressBitmapsValue };
/** general bitmaps */
const TUid KUidSkinGeneralBitmaps =     { KUidSkinGeneralBitmapsValue };
/** file system bitmaps */
const TUid KUidSkinFileSystemBitmaps =  { KUidSkinFileSystemBitmapsValue };
/** controls bitmaps */
const TUid KUidSkinWidgetsBitmaps =     { KUidSkinWidgetsBitmapsValue };
/** status panel bitmaps */
const TUid KUidSkinStatuspaneBitmaps =  { KUidSkinStatuspaneBitmapsValue };
/** borders bitmaps */
const TUid KUidSkinBordersBitmaps =     { KUidSkinBordersBitmapsValue };
/** menu bitmaps */
const TUid KUidSkinMenuBitmaps =        { KUidSkinMenuBitmapsValue };
/** dialog button bitmaps */
const TUid KUidSkinDialogButtonBitmaps ={ KUidSkinDialogButtonBitmapsValue };
/** AppView bitmaps */
const TUid KUidSkinAppViewBitmaps =     { KUidSkinAppViewBitmapsValue };
/** command bar bitmaps */
const TUid KUidSkinCommandBarBitmaps =  { KUidSkinCommandBarBitmapsValue };
/** dialog frame bitmaps */
const TUid KUidSkinDialogFrameBitmaps = { KUidSkinDialogFrameBitmapsValue };
/** view button bitmaps */
const TUid KUidSkinViewButtonBitmaps =  { KUidSkinViewButtonBitmapsValue };
/** seek bar bitmaps */
const TUid KUidSkinSeekBarBitmaps =     { KUidSkinSeekBarBitmapsValue };
/** volume bar bitmaps */
const TUid KUidSkinVolumeBarBitmaps =   { KUidSkinVolumeBarBitmapsValue };
/** control bar bitmaps */
const TUid KUidSkinControlBarBitmaps =  { KUidSkinControlBarBitmapsValue };
/** call header button bitmaps */
const TUid KUidSkinCallHeaderButtonBitmaps = { KUidSkinCallHeaderButtonBitmapsValue };
/** day picker bitmaps */
const TUid KUidSkinDaypickerBitmaps =   { KUidSkinDaypickerBitmapsValue };
/** seek bar small bitmaps */
const TUid KUidSkinSeekBarSmallBitmaps = { KUidSkinSeekBarSmallBitmapsValue };
/** volume bar small bitmaps */
const TUid KUidSkinVolumeBarSmallBitmaps = { KUidSkinVolumeBarSmallBitmapsValue };
/** volume bar vertical bitmaps */
const TUid KUidSkinVolumeBarVerticalBitmaps = { KUidSkinVolumeBarVerticalBitmapsValue };
/** AppTitle bitmaps */
const TUid KUidSkinAppTitleBitmaps =    { KUidSkinAppTitleBitmapsValue };
/** status pane wide bitmaps */
const TUid KUidSkinStatusPaneWideBitmaps =  { KUidSkinStatusPaneWideBitmapsValue };
/** borders dialog bitmaps */
const TUid KUidSkinBordersDialogBitmaps = { KUidSkinBordersDialogValue };
/** App icon bitmaps */
const TUid KUidSkinAppIconBitmaps =     { KUidSkinAppIconBitmapsValue };


#endif  // SKINUID_H

// End of File
