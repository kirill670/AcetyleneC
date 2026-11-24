/*
* ============================================================================
*  Name     : aknconsts.h
*  Part of  : AVKON
*
*  Description:
*     The file contains some avkon constants (mainly for internal use).
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*/

#ifndef AKNCONSTS_H
#define AKNCONSTS_H

#include <avkon.hrh>

// Status pane constants

const TInt KStatusPaneBackgroundGraphicsColorIdle = 215;
const TInt KStatusPaneBackgroundGraphicsColorUsual = 237;

const TInt KStatusPaneBackgroundColor = 0;

const TInt Kqpn_height_status_pane_idle = 56;
const TInt Kqpn_height_status_pane_usual = 44;

struct SLafIconLayout
    {
    TInt left;
    TInt top;
    TInt right;
    TInt bottom;
    TInt width;
    TInt height;
    };

struct SLafTextCharasteristics
    {
    TInt color;
    TInt left;
    TInt right;
    TInt baseline;
    TInt width;
    TInt justification;
    };

// Navi pane constants
const TInt KNoValue = -1000;
const TInt KUseOtherValue = -1001;
const TInt KUseBaseValue = 0;


const struct SLafIconLayout KStatusPaneBackgroundGraphics =
    {1,29,KNoValue,KNoValue,174,15};

const struct SLafIconLayout KStatusPaneNaviPaneWipeGraphics =
    {0, 1, KNoValue, KNoValue, 174, 15};

const struct SLafIconLayout KStatusPaneNaviPaneWipeBitmapOffset =
    {55, 0, KNoValue, KNoValue, 174, 15};

const struct SLafIconLayout KNaviQgnNaviArrowLeft =
    {0,0,KNoValue,KNoValue,4,16};

const struct SLafIconLayout KNaviQgnNaviArrowRight[2] =
    {
        {KNoValue,0,5,KNoValue,4,16},
        {KNoValue,0,1,KNoValue,4,16}
    };


const struct SLafIconLayout KNaviQgnNaviTabBitmap =
    {4,0,KNoValue,KNoValue,107,16};

const struct SLafIconLayout KNaviQgnNaviTabIcon2[2] =
    {
        {17,3,KNoValue,KNoValue,35,11},
        {63,3,KNoValue,KNoValue,35,11}
    };

const struct SLafIconLayout KNaviQgnNaviTabIconLong2[2] =
    {
        {17,3,KNoValue,KNoValue,74,11},
        {24,3,KNoValue,KNoValue,74,11}
    };

const struct SLafIconLayout KNaviQgnNaviTabIcon3[3] =
    {
        {16,3,KNoValue,KNoValue,22,11},
        {47,3,KNoValue,KNoValue,22,11},
        {78,3,KNoValue,KNoValue,22,11}
    };


const struct SLafIconLayout KNaviQgnNaviTabIcon4[4] =
    {
        {14,3,KNoValue,KNoValue,18,11},
        {37,3,KNoValue,KNoValue,18,11},
        {60,3,KNoValue,KNoValue,18,11},
        {83,3,KNoValue,KNoValue,18,11}
    };

const struct SLafIconLayout KNaviQgnNaviTabIconLong3[3] =
    {
        {17,3,KNoValue,KNoValue,67,11},
        {24,3,KNoValue,KNoValue,67,11},
        {31,3,KNoValue,KNoValue,67,11}
    };

const struct SLafTextCharasteristics KNaviQgnNaviTabText2[2] =
    {
        {215,17,66,12,36,ECenter},
        {215,63,20,12,36,ECenter}
    };

const struct SLafTextCharasteristics KNaviQgnNaviTabTextLong2[2] =
    {
        {215,17,29,12,74,ECenter},
        {215,24,22,12,74,ECenter}
    };

const struct SLafTextCharasteristics KNaviQgnNaviTabText3[3] =
    {
        {215,17,81,12,21,ECenter},
        {215,48,50,12,21,ECenter},
        {215,79,19,12,21,ECenter}
    };
const struct SLafTextCharasteristics KNaviQgnNaviTabText4[4] =
    {
        {215,17,89,12,13,ECenter},
        {215,40,66,12,13,ECenter},
        {215,63,43,12,13,ECenter},
        {215,86,20,12,13,ECenter}
    };
const struct SLafTextCharasteristics KNaviQgnNaviTabTextLong3[3] =
    {
        {215,17,36,12,67,ECenter},
        {215,24,29,12,67,ECenter},
        {215,31,22,12,67,ECenter}
    };

const struct SLafIconLayout KNaviQgnNaviTabIcon1 =
    {20,3,KNoValue,KNoValue,35,11};

const struct SLafTextCharasteristics KNaviQgnNaviTabText1 =
    {0,62,25,13,33,ECenter};


const struct SLafTextCharasteristics KNaviQgnNaviInformation[2] =
    {
        {0, 8, 12, 12, 100, ECenter},
        {0, 8, 8, 12, 85, ECenter}
    };

const struct SLafTextCharasteristics KNaviQgnAdditionalInformation =
    {0, 6, 3, 12, 92, ELeft};

const struct SLafTextCharasteristics KNaviQgnHelpHints =
    {0, 6, 4, 12, 110, ELeft};

const struct SLafIconLayout KNaviQgnNaviIcon =
    {20, 3, KNoValue, KNoValue, 35, 11};

const struct SLafTextCharasteristics KNaviQgnNaviIconText =
    {0, 62, 25, 13, 33, ECenter};

const struct SLafIconLayout KNaviQgnNaviEditingStatusIcon =
    {75, 4, KNoValue, KNoValue, 110, 9};


const TInt KTabWidthWithTwoTabs = EAknTabWidthWithTwoTabs;
const TInt KTabWidthWithTwoLongTabs = EAknTabWidthWithTwoLongTabs;
const TInt KTabWidthWithThreeTabs = EAknTabWidthWithThreeTabs;
const TInt KTabWidthWithThreeLongTabs = EAknTabWidthWithThreeLongTabs;
const TInt KTabWidthWithFourTabs = EAknTabWidthWithFourTabs;
const TInt KTabWidthWithOneTab = EAknTabWidthWithOneTab;

const TInt KNaviTabMargins=0;
const TInt KNaviTabActiveTextColor = 215;
const TInt KNaviTabInactiveTextColor = 129;
const TInt KNaviTabOneTabTextColor = 0;


const TInt KTabNumberOfTabBitmaps = 14;
const TInt KTabIndexOfFirstTabBitmapInTwoTabsSet = 0;
const TInt KTabIndexOfLastTabBitmapInTwoTabsSet = 1;
const TInt KTabIndexOfFirstTabBitmapInTwoLongTabsSet = 2;
const TInt KTabIndexOfLastTabBitmapInTwoLongTabsSet = 3;
const TInt KTabIndexOfFirstTabBitmapInThreeTabsSet = 7;
const TInt KTabIndexOfLastTabBitmapInThreeTabsSet = 9;
const TInt KTabIndexOfFirstTabBitmapInThreeLongTabsSet = 4;
const TInt KTabIndexOfLastTabBitmapInThreeLongTabsSet = 6;
const TInt KTabIndexOfFirstTabBitmapInFourTabsSet = 10;
const TInt KTabIndexOfLastTabBitmapInFourTabsSet = 13;

// Title pane constants

const struct SLafTextCharasteristics KTitleQgnOneLineLabel[2] =
    {
        { 215, 1, 3, 22, 104, ELeft},
        { KUseOtherValue, KUseOtherValue, KUseOtherValue, KUseOtherValue, 97, KUseOtherValue}
    };

const struct SLafTextCharasteristics KTitleQgnTwoLineLabel[2] =
    {
        { 215, 1, 3, 11, 104, ELeft},
        { KUseOtherValue, KUseOtherValue, KUseOtherValue, 25, 97, KUseOtherValue}
    };

const struct SLafIconLayout KTitleQgnLogoImage = { 2, 2, 2, 1, 97, 25};

_LIT(KTitlePaneDefaultText, " ");
#ifndef __GMXMLCONSTANTS_H__
// KNewLine is deprecated here. Do not use this any more. 
// Notice that GMXMLConstants.h contains same constant with different value. 
_LIT(KNewLine, "\n");
#endif


// Context pane constants

const struct SLafIconLayout KContextQgnBitmap =
    { 0, 0, KNoValue, KNoValue, 44, 44};

// Battery pane
const TInt KBatteryLevelMin = 0;
const TInt KBatteryLevelMax = 7;

const TInt KBatteryBitmapOffsets[KBatteryLevelMax] =
    {25,21,17,13,9,5,1}; // Levels 1,2,3,4,5,6,7

const struct SLafIconLayout KBatteryQgnIndiBatteryStrength =
    {KNoValue,0,0,KNoValue,12,29};

const struct SLafIconLayout KBatteryQgnIndiBatteryIcon =
    {KNoValue,29,0,KNoValue,12,15};


// Signal pane

const TInt KSignalLevelMin = 0;
const TInt KSignalLevelMax = 7;

const TInt KSignalBitmapOffsets[KSignalLevelMax] =
    {25,21,17,13,9,5,1}; // Levels 1,2,3,4,5,6,7

const struct SLafIconLayout KSignalQgnIndiSignalStrength =
    {0,0,KNoValue,KNoValue,12,29};

const struct SLafIconLayout KSignalQgnIndiSignalIcon =
    {0,29,KNoValue,KNoValue,12,15};


// Common

_LIT(KCommonDialogsBitmapFile,  "z:\\system\\data\\commondialogs.mbm");
_LIT(KCallStatusBitmapFile,     "z:\\system\\data\\callstatus.mbm");
_LIT(KMemoryCardUiBitmapFile,   "z:\\system\\data\\aknmemorycardui.mbm");
_LIT(KAvkonBitmapFile,          "z:\\system\\data\\avkon.mbm");
_LIT(KAvkonVariatedBitmapsFile, "z:\\system\\data\\variatedbitmaps.mbm");

const TInt KAknSoftkeyPaneHeight = 20;

const TInt KAknDefaultWsBufferSize = 7000;
const TInt KAknMaxWsBufferSize = 16000;


// Small status pane
const TInt KMinSpaceBetweenIconsInPixels = 3;

const struct SLafIconLayout KSmallStatusPaneIndicator =
    {0,3,KNoValue,KNoValue,171,15};
const struct SLafIconLayout KSmallStatusPaneTextIndicator =
    {2,2,KNoValue,KNoValue,171,11};
const struct SLafIconLayout KSmallStatusPaneSecureStateIndicator =
    {0,4,KNoValue,KNoValue,10,9};
const struct SLafIconLayout KSmallStatusPaneWmlWaitGlobeIndicator =
    {82,1,80,KNoValue,13,13};
const struct SLafIconLayout KSmallStatusPaneWaitBarIndicator =
    {3,3,KNoValue,KNoValue,77,9};
const struct SLafIconLayout KSmallStatusPaneProgressBarIndicator =
    {3,3,KNoValue,KNoValue,77,9};
const struct SLafIconLayout KSmallStatusPaneGprsIndicator =
    {KNoValue,KNoValue,KNoValue,KNoValue,12,15};

// Mirrored statuspane for A&H
const struct SLafIconLayout KMirroredStatusPaneNaviPaneWipeBitmapOffset =
    {0, 0, 55, KNoValue, 174, 15};

const struct SLafIconLayout KMirroredNaviQgnNaviArrowLeft[2] =
    {
        {5,0,KNoValue,KNoValue,4,16},
        {1,0,KNoValue,KNoValue,4,16}
    };

const struct SLafIconLayout KMirroredNaviQgnNaviArrowRight =
    {0,0,KNoValue,KNoValue,4,16};

const struct SLafIconLayout KMirroredNaviQgnNaviTabBitmap =
    {9,0,KNoValue,KNoValue,107,16};


// Naviwipe related constants
struct SNaviWipePart
    {
    TInt start;
    TInt end;
    };

// Note that values are for skin navi wipes (176x15). Not for
// default avkon LAF navi wipes (174x15).
const struct SNaviWipePart KNaviWipeSignalPanePart =
    {0,12};
const struct SNaviWipePart KNaviWipeContextPanePart =
    {12,56};
const struct SNaviWipePart KNaviWipeNaviPanePart =
    {56,176};

const struct SNaviWipePart KNaviWipeSignalPanePartMirrored =
    {164,176};
const struct SNaviWipePart KNaviWipeContextPanePartMirrored =
    {120,164};
const struct SNaviWipePart KNaviWipeNaviPanePartMirrored =
    {0,120};


#endif // AKNCONSTS_H

