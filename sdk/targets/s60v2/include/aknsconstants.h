/*
* ==============================================================================
*  Name        : AknsConstants.h
*  Part of     : Avkon Skins / Skin Library
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Defines constant values for Avkon Skins.
*  Version     : ?Version
*
*  Copyright (C) 2002-2004 Nokia Corporation.
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

#ifndef AKNSCONSTANTS_H
#define AKNSCONSTANTS_H

/**
* @file AknsConstants.h
*
* Defines constants common for Avkon Skins.
*
* @since 2.0
*/

//  INCLUDES
#include <e32std.h>
#include <AknsItemID.h>
#include <AknsConstants.hrh>

// CONSTANTS

// SCCMARKER_BEGIN

// ============================================================================
// Common IIDs
// ============================================================================

// ----------------------------------------------------------------------------
// None and default values
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDNone =
    { EAknsMajorNone, EAknsMinorNone };

static const TAknsItemID KAknsIIDDefault =
    { EAknsMajorDefault, EAknsMinorDefault };

// ----------------------------------------------------------------------------
// EAknsMajorSkin item IDs
// ----------------------------------------------------------------------------

// Screen, status and control areas

static const TAknsItemID KAknsIIDQsnBgScreen =
    { EAknsMajorSkin, EAknsMinorQsnBgScreen };

static const TAknsItemID KAknsIIDQsnBgScreenIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgScreenIdle };

static const TAknsItemID KAknsIIDQsnBgAreaStatus =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStatus };

static const TAknsItemID KAknsIIDQsnBgAreaStatusIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStatusIdle };

static const TAknsItemID KAknsIIDQsnBgAreaControl =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaControl };

static const TAknsItemID KAknsIIDQsnBgAreaControlPopup =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaControlPopup };

static const TAknsItemID KAknsIIDQsnBgAreaControlIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaControlIdle };

// Stacon

static const TAknsItemID KAknsIIDQsnBgAreaStaconRt =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconRt };

static const TAknsItemID KAknsIIDQsnBgAreaStaconLt =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconLt };

static const TAknsItemID KAknsIIDQsnBgAreaStaconRb =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconRb };

static const TAknsItemID KAknsIIDQsnBgAreaStaconLb =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconLb };

static const TAknsItemID KAknsIIDQsnBgAreaStaconRtIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconRtIdle };

static const TAknsItemID KAknsIIDQsnBgAreaStaconLtIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconLtIdle };

static const TAknsItemID KAknsIIDQsnBgAreaStaconRbIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconRbIdle };

static const TAknsItemID KAknsIIDQsnBgAreaStaconLbIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaStaconLbIdle };

// Main areas

static const TAknsItemID KAknsIIDQsnBgAreaMain =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMain };

static const TAknsItemID KAknsIIDQsnBgAreaMainListGene =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainListGene };

static const TAknsItemID KAknsIIDQsnBgAreaMainListSet =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainListSet };

static const TAknsItemID KAknsIIDQsnBgAreaMainAppsGrid =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainAppsGrid };

static const TAknsItemID KAknsIIDQsnBgAreaMainMessage =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainMessage };

static const TAknsItemID KAknsIIDQsnBgAreaMainIdle =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainIdle };

static const TAknsItemID KAknsIIDQsnBgAreaMainPinb =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainPinb };

static const TAknsItemID KAknsIIDQsnBgAreaMainCalc =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainCalc };

static const TAknsItemID KAknsIIDQsnBgAreaMainQdial =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainQdial };

static const TAknsItemID KAknsIIDQsnBgAreaMainIdleDimmed =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainIdleDimmed };

static const TAknsItemID KAknsIIDQsnBgAreaMainHigh =
    { EAknsMajorSkin, EAknsMinorQsnBgAreaMainHigh };

// Slice elements

static const TAknsItemID KAknsIIDQsnBgSlicePopup =
    { EAknsMajorSkin, EAknsMinorQsnBgSlicePopup};

static const TAknsItemID KAknsIIDQsnBgSlicePinb =
    { EAknsMajorSkin, EAknsMinorQsnBgSlicePinb };

static const TAknsItemID KAknsIIDQsnBgSliceFswap =
    { EAknsMajorSkin, EAknsMinorQsnBgSliceFswap };

// Wallpaper

static const TAknsItemID KAknsIIDWallpaper =
    { EAknsMajorSkin, EAknsMinorWallpaper };

static const TAknsItemID KAknsIIDQgnGrafIdleFade =
    { EAknsMajorSkin, EAknsMinorQgnGrafIdleFade };

// Volume levels

static const TAknsItemID KAknsIIDQsnCpVolumeOn =
    { EAknsMajorSkin, EAknsMinorQsnCpVolumeOn };

static const TAknsItemID KAknsIIDQsnCpVolumeOff =
    { EAknsMajorSkin, EAknsMinorQsnCpVolumeOff };

// List column background

static const TAknsItemID KAknsIIDQsnBgColumn0 =
    { EAknsMajorSkin, EAknsMinorQsnBgColumn0 };

static const TAknsItemID KAknsIIDQsnBgColumnA =
    { EAknsMajorSkin, EAknsMinorQsnBgColumnA };

static const TAknsItemID KAknsIIDQsnBgColumnAB =
    { EAknsMajorSkin, EAknsMinorQsnBgColumnAB };

static const TAknsItemID KAknsIIDQsnBgColumnC0 =
    { EAknsMajorSkin, EAknsMinorQsnBgColumnC0 };

static const TAknsItemID KAknsIIDQsnBgColumnCA =
    { EAknsMajorSkin, EAknsMinorQsnBgColumnCA };

static const TAknsItemID KAknsIIDQsnBgColumnCAB =
    { EAknsMajorSkin, EAknsMinorQsnBgColumnCAB };

// List bottom elements

static const TAknsItemID KAknsIIDQsnBgSliceList0 =
    { EAknsMajorSkin, EAknsMinorQsnBgSliceList0 };

static const TAknsItemID KAknsIIDQsnBgSliceListA =
    { EAknsMajorSkin, EAknsMinorQsnBgSliceListA };

static const TAknsItemID KAknsIIDQsnBgSliceListAB =
    { EAknsMajorSkin, EAknsMinorQsnBgSliceListAB };

// Setting item list - option item frame

static const TAknsItemID KAknsIIDQsnFrSetOpt =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOpt };

static const TAknsItemID KAknsIIDQsnFrSetOptCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptCornerTl };

static const TAknsItemID KAknsIIDQsnFrSetOptCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptCornerTr };

static const TAknsItemID KAknsIIDQsnFrSetOptCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptCornerBl };

static const TAknsItemID KAknsIIDQsnFrSetOptCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptCornerBr };

static const TAknsItemID KAknsIIDQsnFrSetOptSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptSideT };

static const TAknsItemID KAknsIIDQsnFrSetOptSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptSideB };

static const TAknsItemID KAknsIIDQsnFrSetOptSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptSideL };

static const TAknsItemID KAknsIIDQsnFrSetOptSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptSideR };

static const TAknsItemID KAknsIIDQsnFrSetOptCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptCenter };

// Setting item list - focused option item frame

static const TAknsItemID KAknsIIDQsnFrSetOptFoc =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFoc };

static const TAknsItemID KAknsIIDQsnFrSetOptFocCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocCornerTl };

static const TAknsItemID KAknsIIDQsnFrSetOptFocCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocCornerTr };

static const TAknsItemID KAknsIIDQsnFrSetOptFocCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocCornerBl };

static const TAknsItemID KAknsIIDQsnFrSetOptFocCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocCornerBr };

static const TAknsItemID KAknsIIDQsnFrSetOptFocSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocSideT };

static const TAknsItemID KAknsIIDQsnFrSetOptFocSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocSideB };

static const TAknsItemID KAknsIIDQsnFrSetOptFocSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocSideL };

static const TAknsItemID KAknsIIDQsnFrSetOptFocSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocSideR };

static const TAknsItemID KAknsIIDQsnFrSetOptFocCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrSetOptFocCenter };

// Setting list volume graphics

static const TAknsItemID KAknsIIDQsnCpSetListVolumeOn =
    { EAknsMajorSkin, EAknsMinorQsnCpSetListVolumeOn };

static const TAknsItemID KAknsIIDQsnCpSetListVolumeOff =
    { EAknsMajorSkin, EAknsMinorQsnCpSetListVolumeOff };

// Setting list slider graphics

static const TAknsItemID KAknsIIDQgnIndiSliderSet =
    { EAknsMajorSkin, EAknsMinorQgnIndiSliderSet };

// General list highlight frame

static const TAknsItemID KAknsIIDQsnFrList =
    { EAknsMajorSkin, EAknsMinorQsnFrList };

static const TAknsItemID KAknsIIDQsnFrListCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrListCornerTl };

static const TAknsItemID KAknsIIDQsnFrListCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrListCornerTr };

static const TAknsItemID KAknsIIDQsnFrListCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrListCornerBl };

static const TAknsItemID KAknsIIDQsnFrListCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrListCornerBr };

static const TAknsItemID KAknsIIDQsnFrListSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrListSideT };

static const TAknsItemID KAknsIIDQsnFrListSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrListSideB };

static const TAknsItemID KAknsIIDQsnFrListSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrListSideL };

static const TAknsItemID KAknsIIDQsnFrListSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrListSideR };

static const TAknsItemID KAknsIIDQsnFrListCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrListCenter };

// General grid highlight frame

static const TAknsItemID KAknsIIDQsnFrGrid =
    { EAknsMajorSkin, EAknsMinorQsnFrGrid };

static const TAknsItemID KAknsIIDQsnFrGridCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrGridCornerTl };

static const TAknsItemID KAknsIIDQsnFrGridCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrGridCornerTr };

static const TAknsItemID KAknsIIDQsnFrGridCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrGridCornerBl };

static const TAknsItemID KAknsIIDQsnFrGridCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrGridCornerBr };

static const TAknsItemID KAknsIIDQsnFrGridSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrGridSideT };

static const TAknsItemID KAknsIIDQsnFrGridSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrGridSideB };

static const TAknsItemID KAknsIIDQsnFrGridSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrGridSideL };

static const TAknsItemID KAknsIIDQsnFrGridSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrGridSideR };

static const TAknsItemID KAknsIIDQsnFrGridCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrGridCenter };

// General input field border frame

static const TAknsItemID KAknsIIDQsnFrInput =
    { EAknsMajorSkin, EAknsMinorQsnFrInput };

static const TAknsItemID KAknsIIDQsnFrInputCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrInputCornerTl };

static const TAknsItemID KAknsIIDQsnFrInputCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrInputCornerTr };

static const TAknsItemID KAknsIIDQsnFrInputCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrInputCornerBl };

static const TAknsItemID KAknsIIDQsnFrInputCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrInputCornerBr };

static const TAknsItemID KAknsIIDQsnFrInputSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrInputSideT };

static const TAknsItemID KAknsIIDQsnFrInputSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrInputSideB };

static const TAknsItemID KAknsIIDQsnFrInputSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrInputSideL };

static const TAknsItemID KAknsIIDQsnFrInputSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrInputSideR };

static const TAknsItemID KAknsIIDQsnFrInputCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrInputCenter };

// Settings volume graphics

static const TAknsItemID KAknsIIDQsnCpSetVolumeOn =
    { EAknsMajorSkin, EAknsMinorQsnCpSetVolumeOn };

static const TAknsItemID KAknsIIDQsnCpSetVolumeOff =
    { EAknsMajorSkin, EAknsMinorQsnCpSetVolumeOff };

// Slider editing graphics

static const TAknsItemID KAknsIIDQgnIndiSliderEdit =
    { EAknsMajorSkin, EAknsMinorQgnIndiSliderEdit };

// Scrollbars

static const TAknsItemID KAknsIIDQsnCpScrollBgTop =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollBgTop };

static const TAknsItemID KAknsIIDQsnCpScrollBgMiddle =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollBgMiddle };

static const TAknsItemID KAknsIIDQsnCpScrollBgBottom =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollBgBottom };

static const TAknsItemID KAknsIIDQsnCpScrollHandleBgTop =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollHandleBgTop };

static const TAknsItemID KAknsIIDQsnCpScrollHandleBgMiddle =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollHandleBgMiddle };

static const TAknsItemID KAknsIIDQsnCpScrollHandleBgBottom =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollHandleBgBottom };

static const TAknsItemID KAknsIIDQsnCpScrollHandleTop =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollHandleTop };

static const TAknsItemID KAknsIIDQsnCpScrollHandleMiddle =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollHandleMiddle };

static const TAknsItemID KAknsIIDQsnCpScrollHandleBottom =
    { EAknsMajorSkin, EAknsMinorQsnCpScrollHandleBottom };

// Popup generics

static const TAknsItemID KAknsIIDQsnBgScreenDimming =
    { EAknsMajorSkin, EAknsMinorQsnBgScreenDimming };

static const TAknsItemID KAknsIIDQsnBgPopupBackground =
    { EAknsMajorSkin, EAknsMinorQsnBgPopupBackground };

// General popup frame

static const TAknsItemID KAknsIIDQsnFrPopup =
    { EAknsMajorSkin, EAknsMinorQsnFrPopup };

static const TAknsItemID KAknsIIDQsnFrPopupCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCornerTl };

static const TAknsItemID KAknsIIDQsnFrPopupCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCornerTr };

static const TAknsItemID KAknsIIDQsnFrPopupCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCornerBl };

static const TAknsItemID KAknsIIDQsnFrPopupCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCornerBr };

static const TAknsItemID KAknsIIDQsnFrPopupSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSideT };

static const TAknsItemID KAknsIIDQsnFrPopupSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSideB };

static const TAknsItemID KAknsIIDQsnFrPopupSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSideL };

static const TAknsItemID KAknsIIDQsnFrPopupSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSideR };

static const TAknsItemID KAknsIIDQsnFrPopupCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenter };

// Specific popup centers

static const TAknsItemID KAknsIIDQsnFrPopupCenterMenu =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterMenu };

static const TAknsItemID KAknsIIDQsnFrPopupCenterSubmenu =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterSubmenu };

static const TAknsItemID KAknsIIDQsnFrPopupCenterNote =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterNote };

static const TAknsItemID KAknsIIDQsnFrPopupCenterQuery =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterQuery };

static const TAknsItemID KAknsIIDQsnFrPopupCenterFind =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterFind };

static const TAknsItemID KAknsIIDQsnFrPopupCenterSnote =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterSnote };

static const TAknsItemID KAknsIIDQsnFrPopupCenterFswap =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupCenterFswap };

// Submenu frame

static const TAknsItemID KAknsIIDQsnFrPopupSub =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSub };

static const TAknsItemID KAknsIIDQsnFrPopupSubCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubCornerTl };

static const TAknsItemID KAknsIIDQsnFrPopupSubCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubCornerTr };

static const TAknsItemID KAknsIIDQsnFrPopupSubCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubCornerBl };

static const TAknsItemID KAknsIIDQsnFrPopupSubCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubCornerBr };

static const TAknsItemID KAknsIIDQsnFrPopupSubSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubSideT };

static const TAknsItemID KAknsIIDQsnFrPopupSubSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubSideB };

static const TAknsItemID KAknsIIDQsnFrPopupSubSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubSideL };

static const TAknsItemID KAknsIIDQsnFrPopupSubSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupSubSideR };

// Popup heading frame

static const TAknsItemID KAknsIIDQsnFrPopupHeading =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeading };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingCornerTl };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingCornerTr };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingCornerBl };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingCornerBr };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingSideT };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingSideB };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingSideL };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingSideR };

static const TAknsItemID KAknsIIDQsnFrPopupHeadingCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrPopupHeadingCenter };

// Fast application swapping

static const TAknsItemID KAknsIIDQsnBgFswapEnd =
    { EAknsMajorSkin, EAknsMinorQsnBgFswapEnd };

// Colours

/**
* Component color group.
*
* @since 2.0
*
* @deprecated Since release 2.8, use specific color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColors =
    { EAknsMajorSkin, EAknsMinorQsnComponentColors };

/**
* Enumeration for values in QsnComponentColors color table.
*
* @since 2.0
*
* @deprecated Since release 2.8, use specific color groups instead.
*/
enum TAknsQsnComponentColorsIndex
    {
    EAknsCIQsnComponentColorsCG1    = 0,
    EAknsCIQsnComponentColorsCG2    = 1,
    EAknsCIQsnComponentColorsCG3    = 2,
    EAknsCIQsnComponentColorsCG4    = 3,
    EAknsCIQsnComponentColorsCG5    = 4,
    EAknsCIQsnComponentColorsCG6a   = 5,
    EAknsCIQsnComponentColorsCG6b   = 6,
    EAknsCIQsnComponentColorsCG7    = 7,
    EAknsCIQsnComponentColorsCG8    = 8,
    EAknsCIQsnComponentColorsCG9    = 9,
    EAknsCIQsnComponentColorsCG10   = 10,
    EAknsCIQsnComponentColorsCG11   = 11,
    EAknsCIQsnComponentColorsCG12   = 12,
    EAknsCIQsnComponentColorsCG13   = 13,
    EAknsCIQsnComponentColorsCG14   = 14,
    EAknsCIQsnComponentColorsCG15   = 15,
    EAknsCIQsnComponentColorsCG16   = 16,
    EAknsCIQsnComponentColorsCG17   = 17,
    EAknsCIQsnComponentColorsCG18   = 18,
    EAknsCIQsnComponentColorsCG19   = 19,
    EAknsCIQsnComponentColorsCG20   = 20,
    EAknsCIQsnComponentColorsCG21   = 21,
    EAknsCIQsnComponentColorsCG22   = 22,
    EAknsCIQsnComponentColorsCG23   = 23,
    EAknsCIQsnComponentColorsCG24   = 24
    };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG1 =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG1 };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG2 =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG2 };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG3 =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG3 };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG4 =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG4 };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG5 =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG5 };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG6a =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG6a };

/**
* @deprecated Since release 2.8, use color groups instead.
*/
static const TAknsItemID KAknsIIDQsnComponentColorBmpCG6b =
    { EAknsMajorSkin, EAknsMinorQsnComponentColorBmpCG6b };

/**
* Scroll indicator color group.
* 
* @since 2.0
*/
static const TAknsItemID KAknsIIDQsnScrollColors =
    { EAknsMajorSkin, EAknsMinorQsnScrollColors };

/**
* Icon color group.
*
* @since 2.8
*/
static const TAknsItemID KAknsIIDQsnIconColors =
    { EAknsMajorSkin, EAknsMinorQsnIconColors };

/**
* Enumeration for values in QsnIconColors color table.
*
* @since 2.8
*/
enum TAknsQsnIconColorsIndex
    {
    // icon #1	main area; idle	status indicators	#215 
    EAknsCIQsnIconColorsCG1    = 0,
    // icon #2	status area	universal indicator pane icons	#215
    EAknsCIQsnIconColorsCG2    = 1,
    // icon #3	status area	reception off icon	#215
    EAknsCIQsnIconColorsCG3    = 2,
    // icon #4	navi pane	editing state icons	#0
    EAknsCIQsnIconColorsCG4    = 3,
    // icon #5	navi pane	signal iconpacket data indications	#0
    EAknsCIQsnIconColorsCG5    = 4,
    // icon #6	navi pane	battery icon	#0
    EAknsCIQsnIconColorsCG6    = 5,
    // icon #7	navi pane	other navi pane icons (e.g. tab 1 icons)	#0
    EAknsCIQsnIconColorsCG7    = 6,
    // icon #8	active tab	active tab icon colour	#215
    EAknsCIQsnIconColorsCG8    = 7,
    // icon #9	passive tab	passive tab icon colour	#243
    EAknsCIQsnIconColorsCG9    = 8,
    // icon #10	popup window	query editing state icons	#210
    EAknsCIQsnIconColorsCG10   = 9,
    // icon #11	call graphics	call status icons	#215
    EAknsCIQsnIconColorsCG11   = 10,
    // icon #12			
    EAknsCIQsnIconColorsCG12   = 11,
    // icon #13	main area	additional list icons	#215
    EAknsCIQsnIconColorsCG13   = 12,
    // icon #14	settings popup list	checkbox, radio button	#215
    EAknsCIQsnIconColorsCG14   = 13,
    // icon #15	form popup list	checkbox, radio button	#215
    EAknsCIQsnIconColorsCG15   = 14,
    // icon #16	list highlight	additional list iconsform checkbox, radio button	#215
    EAknsCIQsnIconColorsCG16   = 15,
    // icon #17	grid highlight	additional list iconsgms images (?)	#215
    EAknsCIQsnIconColorsCG17   = 16,
    // icon #18	setting list highlight	checkbox, radio button	#0
    EAknsCIQsnIconColorsCG18   = 17,
    // icon #19	calendar views	additional list icons	#215
    EAknsCIQsnIconColorsCG19   = 18,
    // icon #20	stacon area	universal indicator pane icons	#0
    EAknsCIQsnIconColorsCG20   = 19,
    // icon #21	stacon area	reception off icon	#0
    EAknsCIQsnIconColorsCG21   = 20,
    // icon #22	stacon navi pane	editing state icons	#0
    EAknsCIQsnIconColorsCG22   = 21,
    // icon #23	stacon navi pane	signal iconpacket data indications	#0
    EAknsCIQsnIconColorsCG23   = 22,
    // icon #24	stacon navi pane	battery icon	#0
    EAknsCIQsnIconColorsCG24   = 23,
    // icon #25	stacon navi pane	other navi pane icons (e.g. tab 1 icons)	#0
    EAknsCIQsnIconColorsCG25   = 24
    };

/**
* Text color group.
*
* @since 2.8
*/
static const TAknsItemID KAknsIIDQsnTextColors =
    { EAknsMajorSkin, EAknsMinorQsnTextColors };

/**
* Enumeration for values in QsnTextColors color table.
*
* @since 2.8
*/
enum TAknsQsnTextColorsIndex
    {
    // text #1	status area	title text	#215
    EAknsCIQsnTextColorsCG1    = 0,
    // text #2	navi pane	navi pane texts	#0
    EAknsCIQsnTextColorsCG2    = 1,
    // text #3	active tab	active tab text	#215
    EAknsCIQsnTextColorsCG3    = 2,
    // text #4	passive tab	passive tab text	#243
    EAknsCIQsnTextColorsCG4    = 3,
    // text #5	power save state	time/date power save text	#0
    EAknsCIQsnTextColorsCG5    = 4,
    // text #6	main area	main area texts	#215
    EAknsCIQsnTextColorsCG6    = 5,
    // text #7	settings popup list	settings list item text	#215
    EAknsCIQsnTextColorsCG7    = 6,
    // text #8	form popup listform input field	form list item textform data entry text	#215
    EAknsCIQsnTextColorsCG8    = 7,
    // text #9	application grid	unfocused application title texts 	#215
    EAknsCIQsnTextColorsCG9    = 8,
    // text #10	list highlight	list texts	#215
    EAknsCIQsnTextColorsCG10   = 9,
    // text #11	grid highlight	grid text 	#215
    EAknsCIQsnTextColorsCG11   = 10,
    // text #12	settings popup list highlight;settings list item value box	settings value item text	#0
    EAknsCIQsnTextColorsCG12   = 11,
    // text #13	control pane general	left softkey text	#215
    EAknsCIQsnTextColorsCG13   = 12,
    // text #14	control pane general	right softkey text	#215
    EAknsCIQsnTextColorsCG14   = 13,
    // text #15	control pane idle	left softkey text	#215
    EAknsCIQsnTextColorsCG15   = 14,
    // text #16 control pane idle	right softkey text	#215
    EAknsCIQsnTextColorsCG16   = 15,
    // text #17	control pane popup windows	left softkey text	#215
    EAknsCIQsnTextColorsCG17   = 16,
    // text #18	control pane popup windows	right softkey text	#215
    EAknsCIQsnTextColorsCG18   = 17,
    // text #19	popup windows	popup windows text	#215
    EAknsCIQsnTextColorsCG19   = 18,
    // text #20	submenu popup windows	submenu texts	#215
    EAknsCIQsnTextColorsCG20   = 19,
    // text #21	calendar month view	passive month day numbers	#221
    EAknsCIQsnTextColorsCG21   = 20,
    // text #22	calendar month viewcalendar day view	active month day numbersday view list items	#215
    EAknsCIQsnTextColorsCG22   = 21,
    // text #23	calendar month viewcalendar week view	day abbreviationshoursweek numbers	#215
    EAknsCIQsnTextColorsCG23   = 22,
    // text #24	cut/copy/paste highlight	copied text	#0
    EAknsCIQsnTextColorsCG24   = 23,
    // text #25	find pane	search string text	#215
    EAknsCIQsnTextColorsCG25   = 24,
    // text #26	settings input field	setting text entry	#215
    EAknsCIQsnTextColorsCG26   = 25,
    // text #27	query input field	query text entry	#215
    EAknsCIQsnTextColorsCG27   = 26,
    // text #28	power save mode	time/date shadow text	#215
    EAknsCIQsnTextColorsCG28   = 27,
    // text #29	calculator paper 	operator/operand	#215
    EAknsCIQsnTextColorsCG29   = 28,
    // text #30	calculator display	result	#210
    EAknsCIQsnTextColorsCG30   = 29,
    // text #31 calculator display	result shadow	#219
    EAknsCIQsnTextColorsCG31   = 30,
    // text #32	pinboard input field	item title/find string	#215
    EAknsCIQsnTextColorsCG32   = 31,
    // text #33	pinboard/list view	item title	#215
    EAknsCIQsnTextColorsCG33   = 32,
    // text #34	notepad	note text	#215
    EAknsCIQsnTextColorsCG34   = 33,
    // text #35 active idle text    #215
    EAknsCIQsnTextColorsCG35   = 34,
    // text #36 status area title text in idle #215
    EAknsCIQsnTextColorsCG36   = 35,
    // text #37 stacon area title text  #0
    EAknsCIQsnTextColorsCG37   = 36,
    // text #38 stacon area title text in idle #0
    EAknsCIQsnTextColorsCG38   = 37,
    // text #39 stacon area top softkey text    #0
    EAknsCIQsnTextColorsCG39   = 38,
    // text #40 stacon area bottom softkey text    #0
    EAknsCIQsnTextColorsCG40   = 39,
    // text #41 stacon area top softkey text in idle #0
    EAknsCIQsnTextColorsCG41   = 40,
    // text #42 stacon area bottom softkey text in idle #0
    EAknsCIQsnTextColorsCG42   = 41,
    // text #43 stacon navi pane text   #0
    EAknsCIQsnTextColorsCG43   = 42
    };

/**
* Line color group.
*
* @since 2.8
*/
static const TAknsItemID KAknsIIDQsnLineColors =
    { EAknsMajorSkin, EAknsMinorQsnLineColors };

/**
* Enumeration for values in QsnLineColors color table.
*
* @since 2.8
*/
enum TAknsQsnLineColorsIndex
    {
    // line #1	calendar day/week/month view	lines 	#215
    EAknsCIQsnLineColorsCG1    = 0,
    // line #2	calendar day/week/month view	lines 	#221
    EAknsCIQsnLineColorsCG2    = 1,
    // line #3	heading pane	heading pane separator line	#215
    EAknsCIQsnLineColorsCG3    = 2,
    // line #4	main pane	grid cell separator lines	#221
    EAknsCIQsnLineColorsCG4    = 3,
    // line #5	popup windows	grid cell separator lines	#221
    EAknsCIQsnLineColorsCG5    = 4,
    // line #6	lists	column separator lines	#215
    EAknsCIQsnLineColorsCG6    = 5,
    // line #7	setting list	column separator lines	#215
    EAknsCIQsnLineColorsCG7    = 6,
    // line #8	form	slider line 	#215
    EAknsCIQsnLineColorsCG8    = 7,
    // line #9	settings list	value item slider line	#215
    EAknsCIQsnLineColorsCG9    = 8,
    // line #10	opened settings list	value item slider line	#215
    EAknsCIQsnLineColorsCG10   = 9,
    // line #11	popup 	separator line in options menu	#221
    EAknsCIQsnLineColorsCG11   = 10
    };

/**
* Miscellaneous color group.
*
* @since 2.8
*/
static const TAknsItemID KAknsIIDQsnOtherColors =
    { EAknsMajorSkin, EAknsMinorQsnOtherColors };

/**
* Enumeration for values in QsnOtherColors color table.
*
* @since 2.8
*/
enum TAknsQsnOtherColorsIndex
    {
    // other #1	calendar week view	public event	#35
    EAknsCIQsnOtherColorsCG1    = 0,
    // other #2	calendar week view	private event	#210
    EAknsCIQsnOtherColorsCG2    = 1,
    // other #3	calendar week view	not synchronized event	#35 dimmed
    EAknsCIQsnOtherColorsCG3    = 2,
    // other #4	calendar week view	2 or more events overlapping	#215
    EAknsCIQsnOtherColorsCG4    = 3,
    // other #5	calendar month view	event indication on focused month	#215
    EAknsCIQsnOtherColorsCG5    = 4,
    // other #6	calendar month view	event indication on unfocused month	#221
    EAknsCIQsnOtherColorsCG6    = 5
    };

/**
* Highlight color group.
*
* @since 2.8
*/
static const TAknsItemID KAknsIIDQsnHighlightColors =
    { EAknsMajorSkin, EAknsMinorQsnHighlightColors };

/**
* Enumeration for values in QsnHighlightColors color table.
*
* @since 2.8
*/
enum TAknsQsnHighlightColorsIndex
    {
    // highlight #1	link highlight 	browser link highlight colour; japanese fep predictive candidate indication;automatic find item indcation	#244
    EAknsCIQsnHighlightColorsCG1    = 0,
    // highlight #2	cut/copy/paste 	cut/copy/paste highlight	#210
    EAknsCIQsnHighlightColorsCG2    = 1,
    // highlight #3	link indication	link text and underline indication	#210
    EAknsCIQsnHighlightColorsCG3    = 2
    };

static const TAknsItemID KAknsIIDQsnParentColors =
    { EAknsMajorSkin, EAknsMinorQsnParentColors };

/**
* Enumeration for values in QsnParentColors color table.
*
* @par Notes:
* No client code should use these groups, they are reserved for 
* the framework and skin package preparation tools.
*
* @since 2.8
*/
enum TAknsQsnParentColorsIndex
    {
    EAknsCIQsnParentColorsCG1    = 0,
    EAknsCIQsnParentColorsCG2    = 1,
    EAknsCIQsnParentColorsCG3    = 2,
    EAknsCIQsnParentColorsCG4    = 3,
    EAknsCIQsnParentColorsCG5    = 4,
    EAknsCIQsnParentColorsCG6    = 5,
    EAknsCIQsnParentColorsCG7    = 6,
    EAknsCIQsnParentColorsCG8    = 7,
    EAknsCIQsnParentColorsCG9    = 8,
    EAknsCIQsnParentColorsCG10   = 9,
    EAknsCIQsnParentColorsCG11   = 10,
    EAknsCIQsnParentColorsCG12   = 11,
    EAknsCIQsnParentColorsCG13   = 12,
    EAknsCIQsnParentColorsCG14   = 13,
    EAknsCIQsnParentColorsCG15   = 14,
    EAknsCIQsnParentColorsCG16   = 15,
    EAknsCIQsnParentColorsCG17   = 16,
    EAknsCIQsnParentColorsCG18   = 17
    };

// Analogue clock

static const TAknsItemID KAknsIIDQsnCpClockAnalogueFace1 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnalogueFace1 };
static const TAknsItemID KAknsIIDQsnCpClockAnalogueFace1MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnalogueFace1MaskSoft };

static const TAknsItemID KAknsIIDQsnCpClockAnalogueBorderNum =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnalogueBorderNum };

static const TAknsItemID KAknsIIDQsnCpClockAnalogueFace2 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnalogueFace2 };
static const TAknsItemID KAknsIIDQsnCpClockAnalogueFace2MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnalogueFace2MaskSoft };

static const TAknsItemID KAknsIIDQsnCpClockAnaloguePointerHour =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnaloguePointerHour };
static const TAknsItemID KAknsIIDQsnCpClockAnaloguePointerMinute =
    { EAknsMajorSkin, EAknsMinorQsnCpClockAnaloguePointerMinute };

// Digital clock

static const TAknsItemID KAknsIIDQsnCpClockDigitalZero =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalZero };
static const TAknsItemID KAknsIIDQsnCpClockDigitalOne =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalOne };
static const TAknsItemID KAknsIIDQsnCpClockDigitalTwo =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalTwo };
static const TAknsItemID KAknsIIDQsnCpClockDigitalThree =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalThree };
static const TAknsItemID KAknsIIDQsnCpClockDigitalFour =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalFour };
static const TAknsItemID KAknsIIDQsnCpClockDigitalFive =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalFive };
static const TAknsItemID KAknsIIDQsnCpClockDigitalSix =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalSix };
static const TAknsItemID KAknsIIDQsnCpClockDigitalSeven =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalSeven };
static const TAknsItemID KAknsIIDQsnCpClockDigitalEight =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalEight };
static const TAknsItemID KAknsIIDQsnCpClockDigitalNine =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalNine };
static const TAknsItemID KAknsIIDQsnCpClockDigitalStop =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalStop };
static const TAknsItemID KAknsIIDQsnCpClockDigitalColon =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalColon };
static const TAknsItemID KAknsIIDQsnCpClockDigitalZeroMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalZeroMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalOneMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalOneMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalTwoMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalTwoMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalThreeMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalThreeMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalFourMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalFourMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalFiveMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalFiveMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalSixMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalSixMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalSevenMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalSevenMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalEightMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalEightMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalNineMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalNineMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalStopMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalStopMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalColonMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalColonMaskSoft };

// Arabic-Indic digital clock

static const TAknsItemID KAknsIIDQsnCpClockDigitalAhZero =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhZero };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhOne =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhOne };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhTwo =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhTwo };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhThree =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhThree };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhFour =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhFour };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhFive =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhFive };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhSix =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhSix };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhSeven =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhSeven };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhEight =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhEight };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhNine =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhNine };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhStop =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhStop };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhColon =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhColon };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhZeroMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhZeroMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhOneMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhOneMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhTwoMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhTwoMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhThreeMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhThreeMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhFourMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhFourMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhFiveMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhFiveMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhSixMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhSixMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhSevenMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhSevenMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhEightMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhEightMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhNineMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhNineMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhStopMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhStopMaskSoft };
static const TAknsItemID KAknsIIDQsnCpClockDigitalAhColonMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalAhColonMaskSoft };

// Notepad frame

static const TAknsItemID KAknsIIDQsnFrNotepad =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepad };

static const TAknsItemID KAknsIIDQsnFrNotepadCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadCornerTl };

static const TAknsItemID KAknsIIDQsnFrNotepadCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadCornerTr };

static const TAknsItemID KAknsIIDQsnFrNotepadCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadCornerBl };

static const TAknsItemID KAknsIIDQsnFrNotepadCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadCornerBr };

static const TAknsItemID KAknsIIDQsnFrNotepadSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadSideT };

static const TAknsItemID KAknsIIDQsnFrNotepadSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadSideB };

static const TAknsItemID KAknsIIDQsnFrNotepadSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadSideL };

static const TAknsItemID KAknsIIDQsnFrNotepadSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadSideR };

static const TAknsItemID KAknsIIDQsnFrNotepadCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadCenter };

// Notepad "cont" frame

static const TAknsItemID KAknsIIDQsnFrNotepadCont =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadCont };

static const TAknsItemID KAknsIIDQsnFrNotepadContCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContCornerTl };

static const TAknsItemID KAknsIIDQsnFrNotepadContCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContCornerTr };

static const TAknsItemID KAknsIIDQsnFrNotepadContCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContCornerBl };

static const TAknsItemID KAknsIIDQsnFrNotepadContCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContCornerBr };

static const TAknsItemID KAknsIIDQsnFrNotepadContSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContSideT };

static const TAknsItemID KAknsIIDQsnFrNotepadContSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContSideB };

static const TAknsItemID KAknsIIDQsnFrNotepadContSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContSideL };

static const TAknsItemID KAknsIIDQsnFrNotepadContSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContSideR };

static const TAknsItemID KAknsIIDQsnFrNotepadContCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrNotepadContCenter };

// Calculator paper frame

static const TAknsItemID KAknsIIDQsnFrCalcPaper =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaper };

static const TAknsItemID KAknsIIDQsnFrCalcPaperCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperCornerTl };

static const TAknsItemID KAknsIIDQsnFrCalcPaperCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperCornerTr };

static const TAknsItemID KAknsIIDQsnFrCalcPaperCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperCornerBl };

static const TAknsItemID KAknsIIDQsnFrCalcPaperCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperCornerBr };

static const TAknsItemID KAknsIIDQsnFrCalcPaperSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperSideT };

static const TAknsItemID KAknsIIDQsnFrCalcPaperSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperSideB };

static const TAknsItemID KAknsIIDQsnFrCalcPaperSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperSideL };

static const TAknsItemID KAknsIIDQsnFrCalcPaperSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperSideR };

static const TAknsItemID KAknsIIDQsnFrCalcPaperCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcPaperCenter };

// Calculator display parts

static const TAknsItemID KAknsIIDQsnFrCalcDisplaySideL =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcDisplaySideL };

static const TAknsItemID KAknsIIDQsnFrCalcDisplaySideR =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcDisplaySideR };

static const TAknsItemID KAknsIIDQsnFrCalcDisplayCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrCalcDisplayCenter };

// Button frame

static const TAknsItemID KAknsIIDQsnFrSelButton =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButton };

static const TAknsItemID KAknsIIDQsnFrSelButtonCornerTl =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonCornerTl };

static const TAknsItemID KAknsIIDQsnFrSelButtonCornerTr =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonCornerTr };

static const TAknsItemID KAknsIIDQsnFrSelButtonCornerBl =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonCornerBl };

static const TAknsItemID KAknsIIDQsnFrSelButtonCornerBr =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonCornerBr };

static const TAknsItemID KAknsIIDQsnFrSelButtonSideT =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonSideT };

static const TAknsItemID KAknsIIDQsnFrSelButtonSideB =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonSideB };

static const TAknsItemID KAknsIIDQsnFrSelButtonSideL =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonSideL };

static const TAknsItemID KAknsIIDQsnFrSelButtonSideR =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonSideR };

static const TAknsItemID KAknsIIDQsnFrSelButtonCenter =
    { EAknsMajorSkin, EAknsMinorQsnFrSelButtonCenter };

// ----------------------------------------------------------------------------
// EAknsMajorAvkon item IDs
// ----------------------------------------------------------------------------

// Icon group "gene"

static const TAknsItemID KAknsIIDQgnIndiScrollUpMask =
    { EAknsMajorAvkon, EAknsMinorQgnIndiScrollUpMask };

static const TAknsItemID KAknsIIDQgnIndiScrollDownMask =
    { EAknsMajorAvkon, EAknsMinorQgnIndiScrollDownMask };

static const TAknsItemID KAknsIIDQgnIndiSignalStrength =
    { EAknsMajorAvkon, EAknsMinorQgnIndiSignalStrength };

static const TAknsItemID KAknsIIDQgnIndiBatteryStrength =
    { EAknsMajorAvkon, EAknsMinorQgnIndiBatteryStrength };

static const TAknsItemID KAknsIIDQgnIndiNoSignal =
    { EAknsMajorAvkon, EAknsMinorQgnIndiNoSignal };

static const TAknsItemID KAknsIIDQgnIndiFindGlass =
    { EAknsMajorAvkon, EAknsMinorQgnIndiFindGlass };

static const TAknsItemID KAknsIIDQgnPropCheckboxOff =
    { EAknsMajorAvkon, EAknsMinorQgnPropCheckboxOff };

static const TAknsItemID KAknsIIDQgnPropCheckboxOn =
    { EAknsMajorAvkon, EAknsMinorQgnPropCheckboxOn };

static const TAknsItemID KAknsIIDQgnPropFolderSmall =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSmall };

static const TAknsItemID KAknsIIDQgnPropGroupSmall =
    { EAknsMajorAvkon, EAknsMinorQgnPropGroupSmall };

static const TAknsItemID KAknsIIDQgnPropRadiobuttOff =
    { EAknsMajorAvkon, EAknsMinorQgnPropRadiobuttOff };

static const TAknsItemID KAknsIIDQgnPropRadiobuttOn =
    { EAknsMajorAvkon, EAknsMinorQgnPropRadiobuttOn };

static const TAknsItemID KAknsIIDQgnPropFolderLarge =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderLarge };

static const TAknsItemID KAknsIIDQgnPropFolderMedium =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderMedium };

static const TAknsItemID KAknsIIDQgnPropGroupLarge =
    { EAknsMajorAvkon, EAknsMinorQgnPropGroupLarge };

static const TAknsItemID KAknsIIDQgnPropGroupMedium =
    { EAknsMajorAvkon, EAknsMinorQgnPropGroupMedium };

static const TAknsItemID KAknsIIDQgnPropUnsupportedFile =
    { EAknsMajorAvkon, EAknsMinorQgnPropUnsupportedFile };

static const TAknsItemID KAknsIIDQgnPropFolderGms =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderGms };

static const TAknsItemID KAknsIIDQgnPropFmgrFileGame =
    { EAknsMajorAvkon, EAknsMinorQgnPropFmgrFileGame};

static const TAknsItemID KAknsIIDQgnPropFmgrFileOther =
    { EAknsMajorAvkon, EAknsMinorQgnPropFmgrFileOther};

static const TAknsItemID KAknsIIDQgnPropFolderCurrent =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderCurrent };

static const TAknsItemID KAknsIIDQgnPropFolderSubSmall =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubSmall };

static const TAknsItemID KAknsIIDQgnPropFolderAppsMedium =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderAppsMedium };

static const TAknsItemID KAknsIIDQgnMenuFolderApps =
    { EAknsMajorAvkon, EAknsMinorQgnMenuFolderApps };

static const TAknsItemID KAknsIIDQgnPropFolderSubMedium =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubMedium };

static const TAknsItemID KAknsIIDQgnPropFolderImages =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderImages };

static const TAknsItemID KAknsIIDQgnPropFolderMmsTemp =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderMmsTemp };

static const TAknsItemID KAknsIIDQgnPropFolderSounds =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSounds };

static const TAknsItemID KAknsIIDQgnPropFolderSubLarge =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubLarge };

static const TAknsItemID KAknsIIDQgnPropFolderVideo =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderVideo };

static const TAknsItemID KAknsIIDQgnPropImFrom =
    { EAknsMajorAvkon, EAknsMinorQgnPropImFrom };

static const TAknsItemID KAknsIIDQgnPropImTome =
    { EAknsMajorAvkon, EAknsMinorQgnPropImTome };

static const TAknsItemID KAknsIIDQgnPropNrtypAddress =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypAddress };

static const TAknsItemID KAknsIIDQgnPropNrtypCompAddress =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypCompAddress };

static const TAknsItemID KAknsIIDQgnPropNrtypHomeAddress =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypHomeAddress };

static const TAknsItemID KAknsIIDQgnPropNrtypDate =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypDate };

static const TAknsItemID KAknsIIDQgnPropNrtypEmail =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypEmail };

static const TAknsItemID KAknsIIDQgnPropNrtypFax =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypFax };

static const TAknsItemID KAknsIIDQgnPropNrtypMobile =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypMobile };

static const TAknsItemID KAknsIIDQgnPropNrtypNote =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypNote };

static const TAknsItemID KAknsIIDQgnPropNrtypPager =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypPager };

static const TAknsItemID KAknsIIDQgnPropNrtypPhone =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypPhone };

static const TAknsItemID KAknsIIDQgnPropNrtypTone =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypTone };

static const TAknsItemID KAknsIIDQgnPropNrtypUrl =
    { EAknsMajorAvkon, EAknsMinorQgnPropNrtypUrl };

static const TAknsItemID KAknsIIDQgnIndiSubmenu =
    { EAknsMajorAvkon, EAknsMinorQgnIndiSubmenu };

static const TAknsItemID KAknsIIDQgnIndiOnimageAudio =
    { EAknsMajorAvkon, EAknsMinorQgnIndiOnimageAudio };

static const TAknsItemID KAknsIIDQgnPropFolderDigital =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderDigital };

static const TAknsItemID KAknsIIDQgnPropFolderSimple =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSimple };

static const TAknsItemID KAknsIIDQgnPropFolderPres =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderPres };

static const TAknsItemID KAknsIIDQgnPropFileVideo =
    { EAknsMajorAvkon, EAknsMinorQgnPropFileVideo };

static const TAknsItemID KAknsIIDQgnPropFileAudio =
    { EAknsMajorAvkon, EAknsMinorQgnPropFileAudio };

static const TAknsItemID KAknsIIDQgnPropFileRam =
    { EAknsMajorAvkon, EAknsMinorQgnPropFileRam };

static const TAknsItemID KAknsIIDQgnPropFilePlaylist =
    { EAknsMajorAvkon, EAknsMinorQgnPropFilePlaylist };

static const TAknsItemID KAknsIIDQgnPropWmlFolderLinkSeamless =
    { EAknsMajorAvkon, EAknsMinorQgnPropWmlFolderLinkSeamless };

static const TAknsItemID KAknsIIDQgnIndiFindGoto =
    { EAknsMajorAvkon, EAknsMinorQgnIndiFindGoto };

// Icon group "tab"

static const TAknsItemID KAknsIIDQgnGrafTab21 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab21 };

static const TAknsItemID KAknsIIDQgnGrafTab22 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab22 };

static const TAknsItemID KAknsIIDQgnGrafTab31 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab31 };

static const TAknsItemID KAknsIIDQgnGrafTab32 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab32 };

static const TAknsItemID KAknsIIDQgnGrafTab33 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab33 };

static const TAknsItemID KAknsIIDQgnGrafTab41 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab41 };

static const TAknsItemID KAknsIIDQgnGrafTab42 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab42 };

static const TAknsItemID KAknsIIDQgnGrafTab43 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab43 };

static const TAknsItemID KAknsIIDQgnGrafTab44 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTab44 };

static const TAknsItemID KAknsIIDQgnGrafTabLong21 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTabLong21 };

static const TAknsItemID KAknsIIDQgnGrafTabLong22 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTabLong22 };

static const TAknsItemID KAknsIIDQgnGrafTabLong31 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTabLong31 };

static const TAknsItemID KAknsIIDQgnGrafTabLong32 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTabLong32 };

static const TAknsItemID KAknsIIDQgnGrafTabLong33 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafTabLong33 };

// Tab icons for A&H

static const TAknsItemID KAknsIIDQgnPropFolderTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderTab1 };

static const TAknsItemID KAknsIIDQgnPropFolderHelpTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderHelpTab1 };

static const TAknsItemID KAknsIIDQgnPropHelpOpenTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropHelpOpenTab1 };

static const TAknsItemID KAknsIIDQgnPropFolderImageTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderImageTab1 };

static const TAknsItemID KAknsIIDQgnPropFolderMessageTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderMessageTab1 };

static const TAknsItemID KAknsIIDQgnPropFolderMessageAttachTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderMessageAttachTab1 };

static const TAknsItemID KAknsIIDQgnPropFolderMessageAudioTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderMessageAudioTab1 };

static const TAknsItemID KAknsIIDQgnPropFolderMessageObjectTab1 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderMessageObjectTab1 };

static const TAknsItemID KAknsIIDQgnPropNoteListAlphaTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropNoteListAlphaTab2 };

static const TAknsItemID KAknsIIDQgnPropListKeywordTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropListKeywordTab2 };

static const TAknsItemID KAknsIIDQgnPropNoteListTimeTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropNoteListTimeTab2 };

static const TAknsItemID KAknsIIDQgnPropMceDocTab4 =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDocTab4 };

static const TAknsItemID KAknsIIDQgnPropFolderTab =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderTab };

static const TAknsItemID KAknsIIDQgnPropListKeywordArabicTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropListKeywordArabicTab2 };

static const TAknsItemID KAknsIIDQgnPropListKeywordHebrewTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropListKeywordHebrewTab2 };

static const TAknsItemID KAknsIIDQgnPropNoteListAlphaArabicTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropNoteListAlphaArabicTab2 };

static const TAknsItemID KAknsIIDQgnPropNoteListAlphaHebrewTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropNoteListAlphaHebrewTab2 };

// Icon group "bt"

static const TAknsItemID KAknsIIDQgnPropBtAudio =
    { EAknsMajorAvkon, EAknsMinorQgnPropBtAudio };

static const TAknsItemID KAknsIIDQgnPropBtUnknown =
    { EAknsMajorAvkon, EAknsMinorQgnPropBtUnknown };

// Icon group "mce"

static const TAknsItemID KAknsIIDQgnPropFolderSmallNew =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSmallNew };

static const TAknsItemID KAknsIIDQgnPropFolderTemp =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderTemp };

static const TAknsItemID KAknsIIDQgnPropMceUnknownRead =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceUnknownRead };

static const TAknsItemID KAknsIIDQgnPropMceUnknownUnread =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceUnknownUnread };

static const TAknsItemID KAknsIIDQgnPropMceBtUnread =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceBtUnread };

static const TAknsItemID KAknsIIDQgnPropMceDocSmall =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDocSmall };

static const TAknsItemID KAknsIIDQgnPropMceDocumentsNewSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDocumentsNewSub };

static const TAknsItemID KAknsIIDQgnPropMceDocumentsSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDocumentsSub };

static const TAknsItemID KAknsIIDQgnPropFolderSubs =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubs };

static const TAknsItemID KAknsIIDQgnPropFolderSubsNew =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubsNew };

static const TAknsItemID KAknsIIDQgnPropFolderSubSubs =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubSubs };

static const TAknsItemID KAknsIIDQgnPropFolderSubSubsNew =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubSubsNew };

static const TAknsItemID KAknsIIDQgnPropFolderSubUnsubsNew =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderSubUnsubsNew };

static const TAknsItemID KAknsIIDQgnPropFolderUnsubsNew =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderUnsubsNew };
    
static const TAknsItemID KAknsIIDQgnPropMceWriteSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceWriteSub };
    
static const TAknsItemID KAknsIIDQgnPropMceInboxSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceInboxSub };
    
static const TAknsItemID KAknsIIDQgnPropMceInboxNewSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceInboxNewSub };
    
static const TAknsItemID KAknsIIDQgnPropMceRemoteSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceRemoteSub };
    
static const TAknsItemID KAknsIIDQgnPropMceRemoteNewSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceRemoteNewSub };
    
static const TAknsItemID KAknsIIDQgnPropMceSentSub = 
    { EAknsMajorAvkon, EAknsMinorQgnPropMceSentSub };
    
static const TAknsItemID KAknsIIDQgnPropMceOutboxSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceOutboxSub };
    
static const TAknsItemID KAknsIIDQgnPropMceDrSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDrSub };
    
// Icon group "logs"

static const TAknsItemID KAknsIIDQgnPropLogCallsSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogCallsSub };
    
static const TAknsItemID KAknsIIDQgnPropLogMissedSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogMissedSub };
    
static const TAknsItemID KAknsIIDQgnPropLogInSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogInSub };
    
static const TAknsItemID KAknsIIDQgnPropLogOutSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogOutSub };
    
static const TAknsItemID KAknsIIDQgnPropLogTimersSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogTimersSub };
    
static const TAknsItemID KAknsIIDQgnPropLogTimerCallLast =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogTimerCallLast };
    
static const TAknsItemID KAknsIIDQgnPropLogTimerCallOut =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogTimerCallOut };
    
static const TAknsItemID KAknsIIDQgnPropLogTimerCallIn =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogTimerCallIn };
    
static const TAknsItemID KAknsIIDQgnPropLogTimerCallAll =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogTimerCallAll };
    
static const TAknsItemID KAknsIIDQgnPropLogGprsSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogGprsSub };
    
static const TAknsItemID KAknsIIDQgnPropLogGprsSent =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogGprsSent };
    
static const TAknsItemID KAknsIIDQgnPropLogGprsReceived =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogGprsReceived };
    
// Icon group "Camera settings"

static const TAknsItemID KAknsIIDQgnPropSetCamsImageSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetCamsImageSub };
    
static const TAknsItemID KAknsIIDQgnPropSetCamsVideoSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetCamsVideoSub };

// Icon group "Realplayer settings"

static const TAknsItemID KAknsIIDQgnPropSetMpVideoSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetMpVideoSub };
    
static const TAknsItemID KAknsIIDQgnPropSetMpAudioSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetMpAudioSub };
    
static const TAknsItemID KAknsIIDQgnPropSetMpStreamSub = 
    { EAknsMajorAvkon, EAknsMinorQgnPropSetMpStreamSub };

// Icon group "chat"

static const TAknsItemID KAknsIIDQgnPropImIbox =
    { EAknsMajorAvkon, EAknsMinorQgnPropImIbox };
    
static const TAknsItemID KAknsIIDQgnPropImFriends =
    { EAknsMajorAvkon, EAknsMinorQgnPropImFriends };
    
static const TAknsItemID KAknsIIDQgnPropImList =
    { EAknsMajorAvkon, EAknsMinorQgnPropImList };

// Icon group "dyc"

static const TAknsItemID KAknsIIDQgnPropDycPublicSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycPublicSub };
    
static const TAknsItemID KAknsIIDQgnPropDycPrivateSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycPrivateSub };
    
static const TAknsItemID KAknsIIDQgnPropDycBlockedSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycBlockedSub };
    
static const TAknsItemID KAknsIIDQgnPropDycAvailBig =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycAvailBig };
    
static const TAknsItemID KAknsIIDQgnPropDycDiscreetBig =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycDiscreetBig };
    
static const TAknsItemID KAknsIIDQgnPropDycNotAvailBig =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycNotAvailBig };
    
static const TAknsItemID KAknsIIDQgnPropDycNotPublishBig =
    { EAknsMajorAvkon, EAknsMinorQgnPropDycNotPublishBig };

// Icon group "Settings"

static const TAknsItemID KAknsIIDQgnPropSetDeviceSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetDeviceSub };
    
static const TAknsItemID KAknsIIDQgnPropSetCallSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetCallSub };
    
static const TAknsItemID KAknsIIDQgnPropSetConnecSub =    
    { EAknsMajorAvkon, EAknsMinorQgnPropSetConnecSub };
    
static const TAknsItemID KAknsIIDQgnPropSetDatimSub = 
    { EAknsMajorAvkon, EAknsMinorQgnPropSetDatimSub };
    
static const TAknsItemID KAknsIIDQgnPropSetSecSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropSetSecSub };
    
static const TAknsItemID KAknsIIDQgnPropSetDivSub =  
    { EAknsMajorAvkon, EAknsMinorQgnPropSetDivSub };
    
static const TAknsItemID KAknsIIDQgnPropSetBarrSub =   
    { EAknsMajorAvkon, EAknsMinorQgnPropSetBarrSub };
    
static const TAknsItemID KAknsIIDQgnPropSetNetworkSub =    
    { EAknsMajorAvkon, EAknsMinorQgnPropSetNetworkSub };
    
static const TAknsItemID KAknsIIDQgnPropSetAccessorySub =    
    { EAknsMajorAvkon, EAknsMinorQgnPropSetAccessorySub };

// Icon group "location"

static const TAknsItemID KAknsIIDQgnPropLocSetSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropLocSetSub };
    
static const TAknsItemID KAknsIIDQgnPropLocRequestsSub =    
    { EAknsMajorAvkon, EAknsMinorQgnPropLocRequestsSub };

// Icon group "Wallet"

static const TAknsItemID KAknsIIDQgnPropWalletServiceSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropWalletServiceSub };
    
static const TAknsItemID KAknsIIDQgnPropWalletTicketsSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropWalletTicketsSub };
    
static const TAknsItemID KAknsIIDQgnPropWalletCardsSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropWalletCardsSub };
    
static const TAknsItemID KAknsIIDQgnPropWalletPnotesSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropWalletPnotesSub };

// Icon group "Sync"

static const TAknsItemID KAknsIIDQgnPropSmlBt = 
    { EAknsMajorAvkon, EAknsMinorQgnPropSmlBt };

// Icon group "note"

static const TAknsItemID KAknsIIDQgnNoteQuery =
    { EAknsMajorAvkon, EAknsMinorQgnNoteQuery };

static const TAknsItemID KAknsIIDQgnNoteAlarmClock =
    { EAknsMajorAvkon, EAknsMinorQgnNoteAlarmClock };

static const TAknsItemID KAknsIIDQgnNoteBattCharging =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattCharging };

static const TAknsItemID KAknsIIDQgnNoteBattFull =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattFull };

static const TAknsItemID KAknsIIDQgnNoteBattLow =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattLow };

static const TAknsItemID KAknsIIDQgnNoteBattNotCharging =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattNotCharging };

static const TAknsItemID KAknsIIDQgnNoteBattRecharge =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattRecharge };

static const TAknsItemID KAknsIIDQgnNoteErased =
    { EAknsMajorAvkon, EAknsMinorQgnNoteErased };

static const TAknsItemID KAknsIIDQgnNoteError =
    { EAknsMajorAvkon, EAknsMinorQgnNoteError };

static const TAknsItemID KAknsIIDQgnNoteFaxpc =
    { EAknsMajorAvkon, EAknsMinorQgnNoteFaxpc };

static const TAknsItemID KAknsIIDQgnNoteGrps =
    { EAknsMajorAvkon, EAknsMinorQgnNoteGrps };

static const TAknsItemID KAknsIIDQgnNoteInfo =
    { EAknsMajorAvkon, EAknsMinorQgnNoteInfo };

static const TAknsItemID KAknsIIDQgnNoteKeyguard =
    { EAknsMajorAvkon, EAknsMinorQgnNoteKeyguard };

static const TAknsItemID KAknsIIDQgnNoteOk =
    { EAknsMajorAvkon, EAknsMinorQgnNoteOk };

static const TAknsItemID KAknsIIDQgnNoteProgress =
    { EAknsMajorAvkon, EAknsMinorQgnNoteProgress };

static const TAknsItemID KAknsIIDQgnNoteWarning =
    { EAknsMajorAvkon, EAknsMinorQgnNoteWarning };

// Icon group "phota"

static const TAknsItemID KAknsIIDQgnPropImageNotcreated =
    { EAknsMajorAvkon, EAknsMinorQgnPropImageNotcreated };

static const TAknsItemID KAknsIIDQgnPropImageCorrupted =
    { EAknsMajorAvkon, EAknsMinorQgnPropImageCorrupted };

// Icon group "memc"

static const TAknsItemID KAknsIIDQgnPropFileSmall =
    { EAknsMajorAvkon, EAknsMinorQgnPropFileSmall };

static const TAknsItemID KAknsIIDQgnPropPhoneMemc =
    { EAknsMajorAvkon, EAknsMinorQgnPropPhoneMemc };

static const TAknsItemID KAknsIIDQgnPropMmcMemc =
    { EAknsMajorAvkon, EAknsMinorQgnPropMmcMemc };

static const TAknsItemID KAknsIIDQgnPropMmcLocked =
    { EAknsMajorAvkon, EAknsMinorQgnPropMmcLocked };

static const TAknsItemID KAknsIIDQgnPropMmcNon =
    { EAknsMajorAvkon, EAknsMinorQgnPropMmcNon };

static const TAknsItemID KAknsIIDQgnPropPhoneMemcLarge =
    { EAknsMajorAvkon, EAknsMinorQgnPropPhoneMemcLarge };

static const TAknsItemID KAknsIIDQgnPropMmcMemcLarge =
    { EAknsMajorAvkon, EAknsMinorQgnPropMmcMemcLarge };

// Other icons

static const TAknsItemID KAknsIIDQgnIndiNaviArrowLeft =
    { EAknsMajorAvkon, EAknsMinorQgnIndiNaviArrowLeft };

static const TAknsItemID KAknsIIDQgnIndiNaviArrowRight =
    { EAknsMajorAvkon, EAknsMinorQgnIndiNaviArrowRight };

static const TAknsItemID KAknsIIDQgnGrafProgressBar =
    { EAknsMajorAvkon, EAknsMinorQgnGrafProgressBar };

static const TAknsItemID KAknsIIDQgnGrafVorecProgressBar =
    { EAknsMajorAvkon, EAknsMinorQgnGrafVorecProgressBar };

static const TAknsItemID KAknsIIDQgnGrafVorecBarBackground =
    { EAknsMajorAvkon, EAknsMinorQgnGrafVorecBarBackground };

static const TAknsItemID KAknsIIDQgnGrafWaitBarBackground =
    { EAknsMajorAvkon, EAknsMinorQgnGrafWaitBarBackground };

static const TAknsItemID KAknsIIDQgnGrafWaitBar1 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafWaitBar1 };

static const TAknsItemID KAknsIIDQgnGrafSimpdStatusBackg =
    { EAknsMajorAvkon, EAknsMinorQgnGrafSimpdStatusBackg };

static const TAknsItemID KAknsIIDQgnGrafPbStatusBackg =
    { EAknsMajorAvkon, EAknsMinorQgnGrafPbStatusBackg };

static const TAknsItemID KAknsIIDQgnGrafSnoteAdd1 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafSnoteAdd1 };

static const TAknsItemID KAknsIIDQgnGrafSnoteAdd2 =
    { EAknsMajorAvkon, EAknsMinorQgnGrafSnoteAdd2 };

// Other icons for A&H

static const TAknsItemID KAknsIIDQgnIndiCamsPhoneMemc =
    { EAknsMajorAvkon, EAknsMinorQgnIndiCamsPhoneMemc };

static const TAknsItemID KAknsIIDQgnIndiDycDtOtherAdd =
    { EAknsMajorAvkon, EAknsMinorQgnIndiDycDtOtherAdd };

static const TAknsItemID KAknsIIDQgnPropFolderDyc =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderDyc };

static const TAknsItemID KAknsIIDQgnPropFolderTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropFolderTab2 };

static const TAknsItemID KAknsIIDQgnPropLogLogsTab2 =
    { EAknsMajorAvkon, EAknsMinorQgnPropLogLogsTab2 };

static const TAknsItemID KAknsIIDQgnPropMceDraftsNewSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDraftsNewSub };

static const TAknsItemID KAknsIIDQgnPropMceDraftsSub =
    { EAknsMajorAvkon, EAknsMinorQgnPropMceDraftsSub };

static const TAknsItemID KAknsIIDQgnPropWmlFolderAdap =
    { EAknsMajorAvkon, EAknsMinorQgnPropWmlFolderAdap };

// Navi area components

static const TAknsItemID KAknsIIDQsnBgNavipaneSolid =
    { EAknsMajorAvkon, EAknsMinorQsnBgNavipaneSolid };

static const TAknsItemID KAknsIIDQsnBgNavipaneWipe =
    { EAknsMajorAvkon, EAknsMinorQsnBgNavipaneWipe };

static const TAknsItemID KAknsIIDQsnBgNavipaneSolidIdle =
    { EAknsMajorAvkon, EAknsMinorQsnBgNavipaneSolidIdle };

static const TAknsItemID KAknsIIDQsnBgNavipaneWipeIdle =
    { EAknsMajorAvkon, EAknsMinorQsnBgNavipaneWipeIdle };

static const TAknsItemID KAknsIIDQgnNoteQuery2 =
    { EAknsMajorAvkon, EAknsMinorQgnNoteQuery2 };

static const TAknsItemID KAknsIIDQgnNoteQuery3 =
    { EAknsMajorAvkon, EAknsMinorQgnNoteQuery3 };

static const TAknsItemID KAknsIIDQgnNoteQuery4 =
    { EAknsMajorAvkon, EAknsMinorQgnNoteQuery4 };

static const TAknsItemID KAknsIIDQgnNoteQuery5 =
    { EAknsMajorAvkon, EAknsMinorQgnNoteQuery5 };

// Animations

static const TAknsItemID KAknsIIDQgnNoteQueryAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteQueryAnim };

static const TAknsItemID KAknsIIDQgnNoteBattChargingAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattChargingAnim };

static const TAknsItemID KAknsIIDQgnNoteBattFullAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattFullAnim };

static const TAknsItemID KAknsIIDQgnNoteBattLowAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattLowAnim };

static const TAknsItemID KAknsIIDQgnNoteBattNotChargingAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattNotChargingAnim };

static const TAknsItemID KAknsIIDQgnNoteBattRechargeAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBattRechargeAnim };

static const TAknsItemID KAknsIIDQgnNoteErasedAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteErasedAnim };

static const TAknsItemID KAknsIIDQgnNoteErrorAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteErrorAnim };

static const TAknsItemID KAknsIIDQgnNoteInfoAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteInfoAnim };

static const TAknsItemID KAknsIIDQgnNoteKeyguardLockedAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteKeyguardLockedAnim };

static const TAknsItemID KAknsIIDQgnNoteKeyguardOpenAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteKeyguardOpenAnim };

static const TAknsItemID KAknsIIDQgnNoteOkAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteOkAnim };

static const TAknsItemID KAknsIIDQgnNoteWarningAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteWarningAnim };

static const TAknsItemID KAknsIIDQgnNoteBtAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteBtAnim };

static const TAknsItemID KAknsIIDQgnNoteFaxpcAnim =
    { EAknsMajorAvkon, EAknsMinorQgnNoteFaxpcAnim };

static const TAknsItemID KAknsIIDQgnGrafBarWaitAnim =
    { EAknsMajorAvkon, EAknsMinorQgnGrafBarWaitAnim };

// Browser animations

static const TAknsItemID KAknsIIDQgnMenuWmlAnim =
    { EAknsMajorAvkon, EAknsMinorQgnMenuWmlAnim };

static const TAknsItemID KAknsIIDQgnIndiWaitWmlCsdAnim =
    { EAknsMajorAvkon, EAknsMinorQgnIndiWaitWmlCsdAnim };

static const TAknsItemID KAknsIIDQgnIndiWaitWmlGprsAnim =
    { EAknsMajorAvkon, EAknsMinorQgnIndiWaitWmlGprsAnim };

static const TAknsItemID KAknsIIDQgnIndiWaitWmlHscsdAnim =
    { EAknsMajorAvkon, EAknsMinorQgnIndiWaitWmlHscsdAnim };

// CLS animations

static const TAknsItemID KAknsIIDQgnMenuClsCxtAnim =
    { EAknsMajorAvkon, EAknsMinorQgnMenuClsCxtAnim };

// ----------------------------------------------------------------------------
// EAknsMajorAppIconBmpLst item IDs
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDQgnMenuBtLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuBtLst };

static const TAknsItemID KAknsIIDQgnMenuCalcLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuCalcLst };

static const TAknsItemID KAknsIIDQgnMenuCaleLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuCaleLst };

static const TAknsItemID KAknsIIDQgnMenuCamcorderLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuCamcorderLst };

static const TAknsItemID KAknsIIDQgnMenuCamLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuCamLst };

static const TAknsItemID KAknsIIDQgnMenuDivertLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuDivertLst };

static const TAknsItemID KAknsIIDQgnMenuGamesLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuGamesLst };

static const TAknsItemID KAknsIIDQgnMenuHelpLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuHelpLst };

static const TAknsItemID KAknsIIDQgnMenuIdleLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuIdleLst };

static const TAknsItemID KAknsIIDQgnMenuImLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuImLst };

static const TAknsItemID KAknsIIDQgnMenuIrLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuIrLst };

static const TAknsItemID KAknsIIDQgnMenuLogLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuLogLst };

static const TAknsItemID KAknsIIDQgnMenuMceLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuMceLst };

static const TAknsItemID KAknsIIDQgnMenuMceCardLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuMceCardLst };

static const TAknsItemID KAknsIIDQgnMenuMemoryLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuMemoryLst };

static const TAknsItemID KAknsIIDQgnMenuMidletLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuMidletLst };

static const TAknsItemID KAknsIIDQgnMenuMidletSuiteLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuMidletSuiteLst };

static const TAknsItemID KAknsIIDQgnMenuModeLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuModeLst };

static const TAknsItemID KAknsIIDQgnMenuNoteLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuNoteLst };

static const TAknsItemID KAknsIIDQgnMenuPhobLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuPhobLst };

static const TAknsItemID KAknsIIDQgnMenuPhotaLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuPhotaLst };

static const TAknsItemID KAknsIIDQgnMenuPinbLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuPinbLst };

static const TAknsItemID KAknsIIDQgnMenuQdialLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuQdialLst };

static const TAknsItemID KAknsIIDQgnMenuSetLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuSetLst };

static const TAknsItemID KAknsIIDQgnMenuSimpdLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuSimpdLst };

static const TAknsItemID KAknsIIDQgnMenuSmsvoLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuSmsvoLst };

static const TAknsItemID KAknsIIDQgnMenuTodoLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuTodoLst };

static const TAknsItemID KAknsIIDQgnMenuUnknownLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuUnknownLst };

static const TAknsItemID KAknsIIDQgnMenuVideoLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuVideoLst };

static const TAknsItemID KAknsIIDQgnMenuVoirecLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuVoirecLst };

static const TAknsItemID KAknsIIDQgnMenuWclkLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuWclkLst };

static const TAknsItemID KAknsIIDQgnMenuWmlLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuWmlLst };

static const TAknsItemID KAknsIIDQgnMenuLocLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuLocLst };

static const TAknsItemID KAknsIIDQgnMenuBlidLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuBlidLst };

static const TAknsItemID KAknsIIDQgnMenuDycLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuDycLst };

static const TAknsItemID KAknsIIDQgnMenuDmLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuDmLst };

static const TAknsItemID KAknsIIDQgnMenuLmLst =
    { EAknsMajorAppIconBmpLst, EAknsMinorQgnMenuLmLst };

// ----------------------------------------------------------------------------
// EAknsMajorAppIconBmpCxt item IDs
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDQgnMenuAppsgridCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuAppsgridCxt };

static const TAknsItemID KAknsIIDQgnMenuBtCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuBtCxt };

static const TAknsItemID KAknsIIDQgnMenuCaleCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuCaleCxt };

static const TAknsItemID KAknsIIDQgnMenuCamcorderCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuCamcorderCxt };

static const TAknsItemID KAknsIIDQgnMenuCamCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuCamCxt };

static const TAknsItemID KAknsIIDQgnMenuCnvCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuCnvCxt };

static const TAknsItemID KAknsIIDQgnMenuConCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuConCxt };

static const TAknsItemID KAknsIIDQgnMenuDivertCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuDivertCxt };

static const TAknsItemID KAknsIIDQgnMenuGamesCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuGamesCxt };

static const TAknsItemID KAknsIIDQgnMenuHelpCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuHelpCxt };

static const TAknsItemID KAknsIIDQgnMenuImCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuImCxt };

static const TAknsItemID KAknsIIDQgnMenuImOffCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuImOffCxt };

static const TAknsItemID KAknsIIDQgnMenuIrCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuIrCxt };

static const TAknsItemID KAknsIIDQgnMenuJavaCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuJavaCxt };

static const TAknsItemID KAknsIIDQgnMenuLogCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuLogCxt };

static const TAknsItemID KAknsIIDQgnMenuMceCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuMceCxt };

static const TAknsItemID KAknsIIDQgnMenuMceCardCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuMceCardCxt };

static const TAknsItemID KAknsIIDQgnMenuMceMmcCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuMceMmcCxt };

static const TAknsItemID KAknsIIDQgnMenuMemoryCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuMemoryCxt };

static const TAknsItemID KAknsIIDQgnMenuMidletSuiteCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuMidletSuiteCxt };

static const TAknsItemID KAknsIIDQgnMenuModeCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuModeCxt };

static const TAknsItemID KAknsIIDQgnMenuNoteCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuNoteCxt };

static const TAknsItemID KAknsIIDQgnMenuPhobCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuPhobCxt };

static const TAknsItemID KAknsIIDQgnMenuPhotaCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuPhotaCxt };

static const TAknsItemID KAknsIIDQgnMenuSetCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuSetCxt };

static const TAknsItemID KAknsIIDQgnMenuSimpdCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuSimpdCxt };

static const TAknsItemID KAknsIIDQgnMenuSmsvoCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuSmsvoCxt };

static const TAknsItemID KAknsIIDQgnMenuTodoCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuTodoCxt };

static const TAknsItemID KAknsIIDQgnMenuUnknownCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuUnknownCxt };

static const TAknsItemID KAknsIIDQgnMenuVideoCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuVideoCxt };

static const TAknsItemID KAknsIIDQgnMenuVoirecCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuVoirecCxt };

static const TAknsItemID KAknsIIDQgnMenuWclkCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuWclkCxt };

static const TAknsItemID KAknsIIDQgnMenuWmlCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuWmlCxt };

static const TAknsItemID KAknsIIDQgnMenuLocCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuLocCxt };

static const TAknsItemID KAknsIIDQgnMenuBlidCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuBlidCxt };

static const TAknsItemID KAknsIIDQgnMenuBlidOffCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuBlidOffCxt };

static const TAknsItemID KAknsIIDQgnMenuDycCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuDycCxt };

static const TAknsItemID KAknsIIDQgnMenuDycOffCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuDycOffCxt };

static const TAknsItemID KAknsIIDQgnMenuDmCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuDmCxt };

static const TAknsItemID KAknsIIDQgnMenuDmDisabledCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuDmDisabledCxt };

static const TAknsItemID KAknsIIDQgnMenuLmCxt =
    { EAknsMajorAppIconBmpCxt, EAknsMinorQgnMenuLmCxt };

// ----------------------------------------------------------------------------
// EAknsMajorScreensaver item IDs
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDQsnBgPowersave =
    { EAknsMajorScreensaver, EAknsMinorQsnBgPowersave };

static const TAknsItemID KAknsIIDQsnBgScreenSaver =
    { EAknsMajorScreensaver, EAknsMinorQsnBgScreenSaver};

// ----------------------------------------------------------------------------
// EAknsMajorCallstatus item IDs
// ----------------------------------------------------------------------------

// Icon group "call" - call status icons

static const TAknsItemID KAknsIIDQgnIndiCallActive =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallActive };

static const TAknsItemID KAknsIIDQgnIndiCallActiveCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallActiveCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallDisconn };

static const TAknsItemID KAknsIIDQgnIndiCallDisconnCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallDisconnCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallHeld };

static const TAknsItemID KAknsIIDQgnIndiCallHeldCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallHeldCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallMutedCallsta =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallMutedCallsta };

static const TAknsItemID KAknsIIDQgnIndiCallActive2 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallActive2 };

static const TAknsItemID KAknsIIDQgnIndiCallActiveCyphOff2 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallActiveCyphOff2 };

static const TAknsItemID KAknsIIDQgnIndiCallActiveConf =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallActiveConf };

static const TAknsItemID KAknsIIDQgnIndiCallActiveConfCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallActiveConfCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallDisconnConf =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallDisconnConf };

static const TAknsItemID KAknsIIDQgnIndiCallDisconnConfCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallDisconnConfCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallHeldConf =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallHeldConf };

static const TAknsItemID KAknsIIDQgnIndiCallHeldConfCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallHeldConfCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallMuted =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallMuted };

static const TAknsItemID KAknsIIDQgnIndiCallWaiting =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaiting };

static const TAknsItemID KAknsIIDQgnIndiCallWaiting2 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaiting2 };

static const TAknsItemID KAknsIIDQgnIndiCallWaitingCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaitingCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallWaitingCyphOff2 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaitingCyphOff2 };

static const TAknsItemID KAknsIIDQgnIndiCallWaitingDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaitingDisconn };

static const TAknsItemID KAknsIIDQgnIndiCallWaitingDisconnCyphOff =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaitingDisconnCyphOff };

static const TAknsItemID KAknsIIDQgnIndiCallWaiting1 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallWaiting1 };

// Icon group "call" - call handling graphics icons

static const TAknsItemID KAknsIIDQgnGrafBubbleIncall =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafBubbleIncall };

static const TAknsItemID KAknsIIDQgnGrafBubbleIncallDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafBubbleIncallDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallConfFive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallConfFive };

static const TAknsItemID KAknsIIDQgnGrafCallConfFour =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallConfFour };

static const TAknsItemID KAknsIIDQgnGrafCallConfThree =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallConfThree };

static const TAknsItemID KAknsIIDQgnGrafCallConfTwo =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallConfTwo };

static const TAknsItemID KAknsIIDQgnGrafCallFirstHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstHeld };

static const TAknsItemID KAknsIIDQgnGrafCallFirstOneActive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstOneActive };

static const TAknsItemID KAknsIIDQgnGrafCallFirstOneDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstOneDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallFirstOneHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstOneHeld };

static const TAknsItemID KAknsIIDQgnGrafCallFirstThreeActive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstThreeActive };

static const TAknsItemID KAknsIIDQgnGrafCallFirstThreeDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstThreeDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallFirstThreeHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstThreeHeld };

static const TAknsItemID KAknsIIDQgnGrafCallFirstTwoActive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstTwoActive };

static const TAknsItemID KAknsIIDQgnGrafCallFirstTwoDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstTwoDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallFirstTwoHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstTwoHeld };

static const TAknsItemID KAknsIIDQgnGrafCallFirstWaitActive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstWaitActive };

static const TAknsItemID KAknsIIDQgnGrafCallFirstWaitDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallFirstWaitDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallHiddenHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallHiddenHeld };

static const TAknsItemID KAknsIIDQgnGrafCallRecBig =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBig };

static const TAknsItemID KAknsIIDQgnGrafCallRecBigDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBigDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallRecBigLeft =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBigLeft };

static const TAknsItemID KAknsIIDQgnGrafCallRecBigLeftDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBigLeftDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallRecBigRight =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBigRight };

static const TAknsItemID KAknsIIDQgnGrafCallRecBigger =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBigger };

static const TAknsItemID KAknsIIDQgnGrafCallRecBigRightDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecBigRightDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallRecSmallLeft =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecSmallLeft };

static const TAknsItemID KAknsIIDQgnGrafCallRecSmallRight =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecSmallRight };

static const TAknsItemID KAknsIIDQgnGrafCallRecSmallRightDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallRecSmallRightDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallSecondThreeActive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallSecondThreeActive };

static const TAknsItemID KAknsIIDQgnGrafCallSecondThreeDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallSecondThreeDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallSecondThreeHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallSecondThreeHeld };

static const TAknsItemID KAknsIIDQgnGrafCallSecondTwoActive =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallSecondTwoActive };

static const TAknsItemID KAknsIIDQgnGrafCallSecondTwoDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallSecondTwoDisconn };

static const TAknsItemID KAknsIIDQgnGrafCallSecondTwoHeld =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafCallSecondTwoHeld };

// Video call

static const TAknsItemID KAknsIIDQgnIndiCallVideo1 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideo1 };

static const TAknsItemID KAknsIIDQgnIndiCallVideo2 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideo2 };

static const TAknsItemID KAknsIIDQgnIndiCallVideoBlindIn =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoBlindIn };

static const TAknsItemID KAknsIIDQgnIndiCallVideoBlindOut =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoBlindOut };

static const TAknsItemID KAknsIIDQgnIndiCallVideoCallsta1 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoCallsta1 };

static const TAknsItemID KAknsIIDQgnIndiCallVideoCallsta2 =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoCallsta2 };

static const TAknsItemID KAknsIIDQgnIndiCallVideoCallstaDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoCallstaDisconn };

static const TAknsItemID KAknsIIDQgnIndiCallVideoDisconn =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoDisconn };

static const TAknsItemID KAknsIIDQgnIndiCallVideoLst =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiCallVideoLst };

// Zoom indications

static const TAknsItemID KAknsIIDQgnGrafZoomArea =
    { EAknsMajorCallstatus, EAknsMinorQgnGrafZoomArea };

static const TAknsItemID KAknsIIDQgnIndiZoomMin =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiZoomMin };

static const TAknsItemID KAknsIIDQgnIndiZoomMax =
    { EAknsMajorCallstatus, EAknsMinorQgnIndiZoomMax };

// ----------------------------------------------------------------------------
// EAknsMajorCalendar item IDs
// ----------------------------------------------------------------------------

// General calendar frame

static const TAknsItemID KAknsIIDQsnFrCale =
    { EAknsMajorCalendar, EAknsMinorQsnFrCale };

static const TAknsItemID KAknsIIDQsnFrCaleCornerTl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleCornerTl };

static const TAknsItemID KAknsIIDQsnFrCaleCornerTr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleCornerTr };

static const TAknsItemID KAknsIIDQsnFrCaleCornerBl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleCornerBl };

static const TAknsItemID KAknsIIDQsnFrCaleCornerBr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleCornerBr };

static const TAknsItemID KAknsIIDQsnFrCaleSideT =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideT };

static const TAknsItemID KAknsIIDQsnFrCaleSideB =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideB };

static const TAknsItemID KAknsIIDQsnFrCaleSideL =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideL };

static const TAknsItemID KAknsIIDQsnFrCaleSideR =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideR };

static const TAknsItemID KAknsIIDQsnFrCaleCenter =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleCenter };

// Calendar frame for holiday event

static const TAknsItemID KAknsIIDQsnFrCaleHoli =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoli };

static const TAknsItemID KAknsIIDQsnFrCaleHoliCornerTl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliCornerTl };

static const TAknsItemID KAknsIIDQsnFrCaleHoliCornerTr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliCornerTr };

static const TAknsItemID KAknsIIDQsnFrCaleHoliCornerBl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliCornerBl };

static const TAknsItemID KAknsIIDQsnFrCaleHoliCornerBr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliCornerBr };

static const TAknsItemID KAknsIIDQsnFrCaleHoliSideT =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliSideT };

static const TAknsItemID KAknsIIDQsnFrCaleHoliSideB =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliSideB };

static const TAknsItemID KAknsIIDQsnFrCaleHoliSideL =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliSideL };

static const TAknsItemID KAknsIIDQsnFrCaleHoliSideR =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliSideR };

static const TAknsItemID KAknsIIDQsnFrCaleHoliCenter =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHoliCenter };

// Calendar icons

static const TAknsItemID KAknsIIDQgnIndiCdrBirthday =
    { EAknsMajorCalendar, EAknsMinorQgnIndiCdrBirthday };

static const TAknsItemID KAknsIIDQgnIndiCdrMeeting =
    { EAknsMajorCalendar, EAknsMinorQgnIndiCdrMeeting };

static const TAknsItemID KAknsIIDQgnIndiCdrReminder =
    { EAknsMajorCalendar, EAknsMinorQgnIndiCdrReminder };

// Calendar heading frame

static const TAknsItemID KAknsIIDQsnFrCaleHeading =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeading };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingCornerTl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingCornerTl };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingCornerTr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingCornerTr };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingCornerBl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingCornerBl };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingCornerBr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingCornerBr };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingSideT =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingSideT };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingSideB =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingSideB };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingSideL =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingSideL };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingSideR =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingSideR };

static const TAknsItemID KAknsIIDQsnFrCaleHeadingCenter =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleHeadingCenter };

// Calendar side frame

static const TAknsItemID KAknsIIDQsnFrCaleSide =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSide };

static const TAknsItemID KAknsIIDQsnFrCaleSideCornerTl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideCornerTl };

static const TAknsItemID KAknsIIDQsnFrCaleSideCornerTr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideCornerTr };

static const TAknsItemID KAknsIIDQsnFrCaleSideCornerBl =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideCornerBl };

static const TAknsItemID KAknsIIDQsnFrCaleSideCornerBr =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideCornerBr };

static const TAknsItemID KAknsIIDQsnFrCaleSideSideT =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideSideT };

static const TAknsItemID KAknsIIDQsnFrCaleSideSideB =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideSideB };

static const TAknsItemID KAknsIIDQsnFrCaleSideSideL =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideSideL };

static const TAknsItemID KAknsIIDQsnFrCaleSideSideR =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideSideR };

static const TAknsItemID KAknsIIDQsnFrCaleSideCenter =
    { EAknsMajorCalendar, EAknsMinorQsnFrCaleSideCenter };

// ----------------------------------------------------------------------------
// EAknsMajorPinboard item IDs
// ----------------------------------------------------------------------------

// Pinboard frame

static const TAknsItemID KAknsIIDQsnFrPinb =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinb };

static const TAknsItemID KAknsIIDQsnFrPinbCornerTl =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbCornerTl };

static const TAknsItemID KAknsIIDQsnFrPinbCornerTr =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbCornerTr };

static const TAknsItemID KAknsIIDQsnFrPinbCornerBl =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbCornerBl };

static const TAknsItemID KAknsIIDQsnFrPinbCornerBr =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbCornerBr };

static const TAknsItemID KAknsIIDQsnFrPinbSideT =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbSideT };

static const TAknsItemID KAknsIIDQsnFrPinbSideB =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbSideB };

static const TAknsItemID KAknsIIDQsnFrPinbSideL =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbSideL };

static const TAknsItemID KAknsIIDQsnFrPinbSideR =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbSideR };

// Pinboard wallpaper

static const TAknsItemID KAknsIIDQsnFrPinbCenterWp =
    { EAknsMajorPinboard, EAknsMinorQsnFrPinbCenterWp };

// Icon group "pinb"

static const TAknsItemID KAknsIIDQgnPropPinbLinkUnknownId =
    { EAknsMajorPinboard, EAknsMinorQgnPropPinbLinkUnknownId };

static const TAknsItemID KAknsIIDQgnIndiFindTitle =
    { EAknsMajorPinboard, EAknsMinorQgnIndiFindTitle };

static const TAknsItemID KAknsIIDQgnPropPinbHelp =
    { EAknsMajorPinboard, EAknsMinorQgnPropPinbHelp };

// ----------------------------------------------------------------------------
// EAknsMajorCbsuiApp item IDs
// ----------------------------------------------------------------------------

// List icons

static const TAknsItemID KAknsIIDQgnPropCbMsg =
    { EAknsMajorCbsuiApp, EAknsMinorQgnPropCbMsg };

static const TAknsItemID KAknsIIDQgnPropCbMsgUnread =
    { EAknsMajorCbsuiApp, EAknsMinorQgnPropCbMsgUnread };

static const TAknsItemID KAknsIIDQgnPropCbSubs =
    { EAknsMajorCbsuiApp, EAknsMinorQgnPropCbSubs };

static const TAknsItemID KAknsIIDQgnPropCbSubsUnread =
    { EAknsMajorCbsuiApp, EAknsMinorQgnPropCbSubsUnread };

static const TAknsItemID KAknsIIDQgnPropCbUnsubs =
    { EAknsMajorCbsuiApp, EAknsMinorQgnPropCbUnsubs };

static const TAknsItemID KAknsIIDQgnPropCbUnsubsUnread =
    { EAknsMajorCbsuiApp, EAknsMinorQgnPropCbUnsubsUnread };

// ----------------------------------------------------------------------------
// EAknsMajorSound item IDs
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDSoundRingingTone =
    { EAknsMajorSound, EAknsMinorSoundRingingTone };

static const TAknsItemID KAknsIIDSoundMessageAlert =
    { EAknsMajorSound, EAknsMinorSoundMessageAlert };

// ----------------------------------------------------------------------------
// EAknsMajorProperty item IDs
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDPropertyListSeparatorLines =
    { EAknsMajorProperty, EAknsMinorPropertyListSeparatorLines };

static const TAknsItemID KAknsIIDPropertyMessageHeaderLines =
    { EAknsMajorProperty, EAknsMinorPropertyMessageHeaderLines };

static const TAknsItemID KAknsIIDPropertyAnalogueClockDate =
    { EAknsMajorProperty, EAknsMinorPropertyAnalogueClockDate };

// ----------------------------------------------------------------------------
// EAknsMajorGeneric item IDs
// ----------------------------------------------------------------------------

static const TAknsItemID KAknsIIDQgnBtConnectOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnBtConnectOn };

static const TAknsItemID KAknsIIDQgnGrafBarFrame =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarFrame };

static const TAknsItemID KAknsIIDQgnGrafBarFrameLong =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarFrameLong };

static const TAknsItemID KAknsIIDQgnGrafBarFrameShort =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarFrameShort };

static const TAknsItemID KAknsIIDQgnGrafBarFrameVorec =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarFrameVorec };

static const TAknsItemID KAknsIIDQgnGrafBarProgress =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarProgress };

static const TAknsItemID KAknsIIDQgnGrafBarWait1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait1 };

static const TAknsItemID KAknsIIDQgnGrafBarWait2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait2 };

static const TAknsItemID KAknsIIDQgnGrafBarWait3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait3 };

static const TAknsItemID KAknsIIDQgnGrafBarWait4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait4 };

static const TAknsItemID KAknsIIDQgnGrafBarWait5 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait5 };

static const TAknsItemID KAknsIIDQgnGrafBarWait6 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait6 };

static const TAknsItemID KAknsIIDQgnGrafBarWait7 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBarWait7 };

static const TAknsItemID KAknsIIDQgnGrafBlidCompass =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBlidCompass };

static const TAknsItemID KAknsIIDQgnGrafCalcDisplay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafCalcDisplay };

static const TAknsItemID KAknsIIDQgnGrafCalcPaper =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafCalcPaper };

static const TAknsItemID KAknsIIDQgnGrafCallFirstOneActiveEmergency =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafCallFirstOneActiveEmergency };

static const TAknsItemID KAknsIIDQgnGrafCallTwoActiveEmergency =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafCallTwoActiveEmergency };

static const TAknsItemID KAknsIIDQgnGrafCallVideoOutBg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafCallVideoOutBg };

static const TAknsItemID KAknsIIDQgnGrafMmsAudioInserted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsAudioInserted };

static const TAknsItemID KAknsIIDQgnGrafMmsAudioPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsAudioPlay };

static const TAknsItemID KAknsIIDQgnGrafMmsEdit =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsEdit };

static const TAknsItemID KAknsIIDQgnGrafMmsInsertedVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsInsertedVideo };

static const TAknsItemID KAknsIIDQgnGrafMmsInsertedVideoEdit =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsInsertedVideoEdit };

static const TAknsItemID KAknsIIDQgnGrafMmsInsertedVideoView =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsInsertedVideoView };

static const TAknsItemID KAknsIIDQgnGrafMmsInsertImage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsInsertImage };

static const TAknsItemID KAknsIIDQgnGrafMmsInsertVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsInsertVideo };

static const TAknsItemID KAknsIIDQgnGrafMmsObjectCorrupt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsObjectCorrupt };

static const TAknsItemID KAknsIIDQgnGrafMmsPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsPlay };

static const TAknsItemID KAknsIIDQgnGrafMmsTransBar =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransBar };

static const TAknsItemID KAknsIIDQgnGrafMmsTransClock =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransClock };

static const TAknsItemID KAknsIIDQgnGrafMmsTransEye =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransEye };

static const TAknsItemID KAknsIIDQgnGrafMmsTransFade =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransFade };

static const TAknsItemID KAknsIIDQgnGrafMmsTransHeart =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransHeart };

static const TAknsItemID KAknsIIDQgnGrafMmsTransIris =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransIris };

static const TAknsItemID KAknsIIDQgnGrafMmsTransNone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransNone };

static const TAknsItemID KAknsIIDQgnGrafMmsTransPush =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransPush };

static const TAknsItemID KAknsIIDQgnGrafMmsTransSlide =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransSlide };

static const TAknsItemID KAknsIIDQgnGrafMmsTransSnake =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransSnake };

static const TAknsItemID KAknsIIDQgnGrafMmsTransStar =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTransStar };

static const TAknsItemID KAknsIIDQgnGrafMmsUnedit =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsUnedit };

static const TAknsItemID KAknsIIDQgnGrafMpSplash =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMpSplash };

static const TAknsItemID KAknsIIDQgnGrafNoteCont =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafNoteCont };

static const TAknsItemID KAknsIIDQgnGrafNoteStart =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafNoteStart };

static const TAknsItemID KAknsIIDQgnGrafPhoneLocked =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafPhoneLocked };

static const TAknsItemID KAknsIIDQgnGrafPopup =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafPopup };

static const TAknsItemID KAknsIIDQgnGrafQuickEight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickEight };

static const TAknsItemID KAknsIIDQgnGrafQuickFive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickFive };

static const TAknsItemID KAknsIIDQgnGrafQuickFour =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickFour };

static const TAknsItemID KAknsIIDQgnGrafQuickNine =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickNine };

static const TAknsItemID KAknsIIDQgnGrafQuickOne =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickOne };

static const TAknsItemID KAknsIIDQgnGrafQuickSeven =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickSeven };

static const TAknsItemID KAknsIIDQgnGrafQuickSix =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickSix };

static const TAknsItemID KAknsIIDQgnGrafQuickThree =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickThree };

static const TAknsItemID KAknsIIDQgnGrafQuickTwo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafQuickTwo };

static const TAknsItemID KAknsIIDQgnGrafStatusSmallProg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafStatusSmallProg };

static const TAknsItemID KAknsIIDQgnGrafWmlSplash =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafWmlSplash };

static const TAknsItemID KAknsIIDQgnImstatEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnImstatEmpty };

static const TAknsItemID KAknsIIDQgnIndiAccuracyOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAccuracyOff };

static const TAknsItemID KAknsIIDQgnIndiAccuracyOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAccuracyOn };

static const TAknsItemID KAknsIIDQgnIndiAlarmAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAlarmAdd };

static const TAknsItemID KAknsIIDQgnIndiAlsLine2Add =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAlsLine2Add };

static const TAknsItemID KAknsIIDQgnIndiAmInstMmcAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAmInstMmcAdd };

static const TAknsItemID KAknsIIDQgnIndiAmNotInstAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAmNotInstAdd };

static const TAknsItemID KAknsIIDQgnIndiAttachementAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachementAdd };

static const TAknsItemID KAknsIIDQgnIndiAttachAudio =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachAudio };

static const TAknsItemID KAknsIIDQgnIndiAttachGene =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachGene };

static const TAknsItemID KAknsIIDQgnIndiAttachImage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachImage };

static const TAknsItemID KAknsIIDQgnIndiAttachUnsupportAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachUnsupportAdd };

static const TAknsItemID KAknsIIDQgnIndiBtAudioConnectedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBtAudioConnectedAdd };

static const TAknsItemID KAknsIIDQgnIndiBtAudioSelectedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBtAudioSelectedAdd };

static const TAknsItemID KAknsIIDQgnIndiBtPairedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBtPairedAdd };

static const TAknsItemID KAknsIIDQgnIndiBtTrustedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBtTrustedAdd };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonDivide =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonDivide };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonDividePressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonDividePressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonDown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonDown };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonDownInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonDownInactive };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonDownPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonDownPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonEquals =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonEquals };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonEqualsPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonEqualsPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMinus =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMinus };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMinusPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMinusPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMr =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMr };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMrPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMrPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMs =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMs };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMsPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMsPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMultiply =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMultiply };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonMultiplyPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonMultiplyPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonPercent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonPercent };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonPercentInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonPercentInactive };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonPercentPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonPercentPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonPlus =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonPlus };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonPlusPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonPlusPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonSign =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonSign };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonSignInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonSignInactive };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonSignPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonSignPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonSquareroot =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonSquareroot };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonSquarerootInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonSquarerootInactive };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonSquarerootPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonSquarerootPressed };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonUp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonUp };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonUpInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonUpInactive };

static const TAknsItemID KAknsIIDQgnIndiCalcButtonUpPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCalcButtonUpPressed };

static const TAknsItemID KAknsIIDQgnIndiCallActiveEmergency =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallActiveEmergency };

static const TAknsItemID KAknsIIDQgnIndiCallCypheringOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallCypheringOff };

static const TAknsItemID KAknsIIDQgnIndiCallData =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallData };

static const TAknsItemID KAknsIIDQgnIndiCallDataDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallDataDiv };

static const TAknsItemID KAknsIIDQgnIndiCallDataHscsd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallDataHscsd };

static const TAknsItemID KAknsIIDQgnIndiCallDataHscsdDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallDataHscsdDiv };

static const TAknsItemID KAknsIIDQgnIndiCallDataHscsdWaiting =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallDataHscsdWaiting };

static const TAknsItemID KAknsIIDQgnIndiCallDataWaiting =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallDataWaiting };

static const TAknsItemID KAknsIIDQgnIndiCallDiverted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallDiverted };

static const TAknsItemID KAknsIIDQgnIndiCallFax =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallFax };

static const TAknsItemID KAknsIIDQgnIndiCallFaxDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallFaxDiv };

static const TAknsItemID KAknsIIDQgnIndiCallFaxWaiting =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallFaxWaiting };

static const TAknsItemID KAknsIIDQgnIndiCallLine2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallLine2 };

static const TAknsItemID KAknsIIDQgnIndiCallVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVideo };

static const TAknsItemID KAknsIIDQgnIndiCallVideoAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVideoAdd };

static const TAknsItemID KAknsIIDQgnIndiCallVideoCallsta =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVideoCallsta };

static const TAknsItemID KAknsIIDQgnIndiCallWaitingCyphOff1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallWaitingCyphOff1 };

static const TAknsItemID KAknsIIDQgnIndiCamsExpo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsExpo };

static const TAknsItemID KAknsIIDQgnIndiCamsFlashOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsFlashOff };

static const TAknsItemID KAknsIIDQgnIndiCamsFlashOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsFlashOn };

static const TAknsItemID KAknsIIDQgnIndiCamsMicOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsMicOff };

static const TAknsItemID KAknsIIDQgnIndiCamsMmc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsMmc };

static const TAknsItemID KAknsIIDQgnIndiCamsNight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsNight };

static const TAknsItemID KAknsIIDQgnIndiCamsPaused =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsPaused };

static const TAknsItemID KAknsIIDQgnIndiCamsRec =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsRec };

static const TAknsItemID KAknsIIDQgnIndiCamsTimer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsTimer };

static const TAknsItemID KAknsIIDQgnIndiCamsZoomBg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsZoomBg };

static const TAknsItemID KAknsIIDQgnIndiCamsZoomElevator =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsZoomElevator };

static const TAknsItemID KAknsIIDQgnIndiCamZoom2Video =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamZoom2Video };

static const TAknsItemID KAknsIIDQgnIndiCbHotAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCbHotAdd };

static const TAknsItemID KAknsIIDQgnIndiCbKeptAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCbKeptAdd };

static const TAknsItemID KAknsIIDQgnIndiCdrDummy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrDummy };

static const TAknsItemID KAknsIIDQgnIndiCdrEventDummy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrEventDummy };

static const TAknsItemID KAknsIIDQgnIndiCdrEventGrayed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrEventGrayed };

static const TAknsItemID KAknsIIDQgnIndiCdrEventMixed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrEventMixed };

static const TAknsItemID KAknsIIDQgnIndiCdrEventPrivate =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrEventPrivate };

static const TAknsItemID KAknsIIDQgnIndiCdrEventPrivateDimm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrEventPrivateDimm };

static const TAknsItemID KAknsIIDQgnIndiCdrEventPublic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrEventPublic };

static const TAknsItemID KAknsIIDQgnIndiCheckboxOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCheckboxOff };

static const TAknsItemID KAknsIIDQgnIndiCheckboxOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCheckboxOn };

static const TAknsItemID KAknsIIDQgnIndiChiFindNumeric =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindNumeric };

static const TAknsItemID KAknsIIDQgnIndiChiFindPinyin =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindPinyin };

static const TAknsItemID KAknsIIDQgnIndiChiFindSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindSmall };

static const TAknsItemID KAknsIIDQgnIndiChiFindStrokeSimple =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindStrokeSimple };

static const TAknsItemID KAknsIIDQgnIndiChiFindStrokeSymbol =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindStrokeSymbol };

static const TAknsItemID KAknsIIDQgnIndiChiFindStrokeTrad =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindStrokeTrad };

static const TAknsItemID KAknsIIDQgnIndiChiFindZhuyin =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindZhuyin };

static const TAknsItemID KAknsIIDQgnIndiChiFindZhuyinSymbol =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindZhuyinSymbol };

static const TAknsItemID KAknsIIDQgnIndiConnectionAlwaysAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiConnectionAlwaysAdd };

static const TAknsItemID KAknsIIDQgnIndiConnectionInactiveAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiConnectionInactiveAdd };

static const TAknsItemID KAknsIIDQgnIndiConnectionOnAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiConnectionOnAdd };

static const TAknsItemID KAknsIIDQgnIndiDrmRightsExpAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDrmRightsExpAdd };

static const TAknsItemID KAknsIIDQgnIndiDstAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDstAdd };

static const TAknsItemID KAknsIIDQgnIndiDycAvailAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycAvailAdd };

static const TAknsItemID KAknsIIDQgnIndiDycDiscreetAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycDiscreetAdd };

static const TAknsItemID KAknsIIDQgnIndiDycDtMobileAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycDtMobileAdd };

static const TAknsItemID KAknsIIDQgnIndiDycDtPcAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycDtPcAdd };

static const TAknsItemID KAknsIIDQgnIndiDycNotAvailAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycNotAvailAdd };

static const TAknsItemID KAknsIIDQgnIndiDycNotPublishAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycNotPublishAdd };

static const TAknsItemID KAknsIIDQgnIndiEarpiece =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiEarpiece };

static const TAknsItemID KAknsIIDQgnIndiEarpieceActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiEarpieceActive };

static const TAknsItemID KAknsIIDQgnIndiEarpieceMuted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiEarpieceMuted };

static const TAknsItemID KAknsIIDQgnIndiEarpiecePassive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiEarpiecePassive };

static const TAknsItemID KAknsIIDQgnIndiFepArrowDown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFepArrowDown };

static const TAknsItemID KAknsIIDQgnIndiFepArrowLeft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFepArrowLeft };

static const TAknsItemID KAknsIIDQgnIndiFepArrowRight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFepArrowRight };

static const TAknsItemID KAknsIIDQgnIndiFepArrowUp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFepArrowUp };

static const TAknsItemID KAknsIIDQgnIndiFindGlassPinb =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFindGlassPinb };

static const TAknsItemID KAknsIIDQgnIndiImFriendOffAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiImFriendOffAdd };

static const TAknsItemID KAknsIIDQgnIndiImFriendOnAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiImFriendOnAdd };

static const TAknsItemID KAknsIIDQgnIndiImImsgAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiImImsgAdd };

static const TAknsItemID KAknsIIDQgnIndiImWatchAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiImWatchAdd };

static const TAknsItemID KAknsIIDQgnIndiItemNotShown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiItemNotShown };

static const TAknsItemID KAknsIIDQgnIndiLevelBack =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiLevelBack };

static const TAknsItemID KAknsIIDQgnIndiMarkedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMarkedAdd };

static const TAknsItemID KAknsIIDQgnIndiMarkedGridAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMarkedGridAdd };

static const TAknsItemID KAknsIIDQgnIndiMic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMic };

static const TAknsItemID KAknsIIDQgnIndiMissedCallOne =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMissedCallOne };

static const TAknsItemID KAknsIIDQgnIndiMissedCallTwo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMissedCallTwo };

static const TAknsItemID KAknsIIDQgnIndiMissedMessOne =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMissedMessOne };

static const TAknsItemID KAknsIIDQgnIndiMissedMessTwo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMissedMessTwo };

static const TAknsItemID KAknsIIDQgnIndiMmcAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmcAdd };

static const TAknsItemID KAknsIIDQgnIndiMmcMarkedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmcMarkedAdd };

static const TAknsItemID KAknsIIDQgnIndiMmsArrowLeft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsArrowLeft };

static const TAknsItemID KAknsIIDQgnIndiMmsArrowRight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsArrowRight };

static const TAknsItemID KAknsIIDQgnIndiMmsPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsPause };

static const TAknsItemID KAknsIIDQgnIndiMmsSpeakerActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsSpeakerActive };

static const TAknsItemID KAknsIIDQgnIndiMmsTemplateImageCorrupt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsTemplateImageCorrupt };

static const TAknsItemID KAknsIIDQgnIndiMpButtonForw =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonForw };

static const TAknsItemID KAknsIIDQgnIndiMpButtonForwInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonForwInact };

static const TAknsItemID KAknsIIDQgnIndiMpButtonNext =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonNext };

static const TAknsItemID KAknsIIDQgnIndiMpButtonNextInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonNextInact };

static const TAknsItemID KAknsIIDQgnIndiMpButtonPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonPause };

static const TAknsItemID KAknsIIDQgnIndiMpButtonPauseInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonPauseInact };

static const TAknsItemID KAknsIIDQgnIndiMpButtonPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonPlay };

static const TAknsItemID KAknsIIDQgnIndiMpButtonPlayInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonPlayInact };

static const TAknsItemID KAknsIIDQgnIndiMpButtonPrev =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonPrev };

static const TAknsItemID KAknsIIDQgnIndiMpButtonPrevInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonPrevInact };

static const TAknsItemID KAknsIIDQgnIndiMpButtonRew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonRew };

static const TAknsItemID KAknsIIDQgnIndiMpButtonRewInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonRewInact };

static const TAknsItemID KAknsIIDQgnIndiMpButtonStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonStop };

static const TAknsItemID KAknsIIDQgnIndiMpButtonStopInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpButtonStopInact };

static const TAknsItemID KAknsIIDQgnIndiMpCorruptedFileAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpCorruptedFileAdd };

static const TAknsItemID KAknsIIDQgnIndiMpPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpPause };

static const TAknsItemID KAknsIIDQgnIndiMpPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpPlay };

static const TAknsItemID KAknsIIDQgnIndiMpPlaylistArrowAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpPlaylistArrowAdd };

static const TAknsItemID KAknsIIDQgnIndiMpRandom =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpRandom };

static const TAknsItemID KAknsIIDQgnIndiMpRandomRepeat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpRandomRepeat };

static const TAknsItemID KAknsIIDQgnIndiMpRepeat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpRepeat };

static const TAknsItemID KAknsIIDQgnIndiMpStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMpStop };

static const TAknsItemID KAknsIIDQgnIndiObjectGene =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiObjectGene };

static const TAknsItemID KAknsIIDQgnIndiPaused =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiPaused };

static const TAknsItemID KAknsIIDQgnIndiPinSpace =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiPinSpace };

static const TAknsItemID KAknsIIDQgnIndiQdialAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiQdialAdd };

static const TAknsItemID KAknsIIDQgnIndiRadiobuttOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadiobuttOff };

static const TAknsItemID KAknsIIDQgnIndiRadiobuttOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadiobuttOn };

static const TAknsItemID KAknsIIDQgnIndiRepeatAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRepeatAdd };

static const TAknsItemID KAknsIIDQgnIndiSettProtectedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSettProtectedAdd };

static const TAknsItemID KAknsIIDQgnIndiSignalActiveCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalActiveCdma };

static const TAknsItemID KAknsIIDQgnIndiSignalDormantCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalDormantCdma };

static const TAknsItemID KAknsIIDQgnIndiSignalGprsAttach =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalGprsAttach };

static const TAknsItemID KAknsIIDQgnIndiSignalGprsContext =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalGprsContext };

static const TAknsItemID KAknsIIDQgnIndiSignalGprsMultipdp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalGprsMultipdp };

static const TAknsItemID KAknsIIDQgnIndiSignalGprsSuspended =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalGprsSuspended };

static const TAknsItemID KAknsIIDQgnIndiSignalPdAttach =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalPdAttach };

static const TAknsItemID KAknsIIDQgnIndiSignalPdContext =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalPdContext };

static const TAknsItemID KAknsIIDQgnIndiSignalPdMultipdp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalPdMultipdp };

static const TAknsItemID KAknsIIDQgnIndiSignalPdSuspended =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalPdSuspended };

static const TAknsItemID KAknsIIDQgnIndiSignalWcdmaAttach =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalWcdmaAttach };

static const TAknsItemID KAknsIIDQgnIndiSignalWcdmaContext =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalWcdmaContext };

static const TAknsItemID KAknsIIDQgnIndiSignalWcdmaIcon =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalWcdmaIcon };

static const TAknsItemID KAknsIIDQgnIndiSignalWcdmaMultidp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalWcdmaMultidp };

static const TAknsItemID KAknsIIDQgnIndiSignalWcdmaMultipdp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalWcdmaMultipdp };

static const TAknsItemID KAknsIIDQgnIndiSliderNavi =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSliderNavi };

static const TAknsItemID KAknsIIDQgnIndiSpeaker =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSpeaker };

static const TAknsItemID KAknsIIDQgnIndiSpeakerActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSpeakerActive };

static const TAknsItemID KAknsIIDQgnIndiSpeakerMuted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSpeakerMuted };

static const TAknsItemID KAknsIIDQgnIndiSpeakerPassive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSpeakerPassive };

static const TAknsItemID KAknsIIDQgnIndiThaiFindSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiThaiFindSmall };

static const TAknsItemID KAknsIIDQgnIndiTodoHighAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiTodoHighAdd };

static const TAknsItemID KAknsIIDQgnIndiTodoLowAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiTodoLowAdd };

static const TAknsItemID KAknsIIDQgnIndiVoiceAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVoiceAdd };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonForw =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonForw };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonForwInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonForwInactive };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonForwPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonForwPressed };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonPause };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonPauseInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonPauseInactive };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonPausePressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonPausePressed };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonPlay };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonPlayInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonPlayInactive };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonPlayPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonPlayPressed };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonRec =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonRec };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonRecInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonRecInactive };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonRecPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonRecPressed };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonRew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonRew };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonRewInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonRewInactive };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonRewPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonRewPressed };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonStop };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonStopInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonStopInactive };

static const TAknsItemID KAknsIIDQgnIndiVorecButtonStopPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiVorecButtonStopPressed };

static const TAknsItemID KAknsIIDQgnIndiWmlCsdAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlCsdAdd };

static const TAknsItemID KAknsIIDQgnIndiWmlGprsAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlGprsAdd };

static const TAknsItemID KAknsIIDQgnIndiWmlHscsdAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlHscsdAdd };

static const TAknsItemID KAknsIIDQgnIndiWmlObject =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlObject };

static const TAknsItemID KAknsIIDQgnIndiXhtmlMmc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiXhtmlMmc };

static const TAknsItemID KAknsIIDQgnIndiZoomDir =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiZoomDir };

static const TAknsItemID KAknsIIDQgnLogoEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnLogoEmpty };

static const TAknsItemID KAknsIIDQgnNoteAlarmAlert =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteAlarmAlert };

static const TAknsItemID KAknsIIDQgnNoteAlarmCalendar =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteAlarmCalendar };

static const TAknsItemID KAknsIIDQgnNoteAlarmMisc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteAlarmMisc };

static const TAknsItemID KAknsIIDQgnNoteBt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteBt };

static const TAknsItemID KAknsIIDQgnNoteBtPopup =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteBtPopup };

static const TAknsItemID KAknsIIDQgnNoteCall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteCall };

static const TAknsItemID KAknsIIDQgnNoteCopy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteCopy };

static const TAknsItemID KAknsIIDQgnNoteCsd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteCsd };

static const TAknsItemID KAknsIIDQgnNoteDycStatusChanged =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteDycStatusChanged };

static const TAknsItemID KAknsIIDQgnNoteEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteEmpty };

static const TAknsItemID KAknsIIDQgnNoteGprs =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteGprs };

static const TAknsItemID KAknsIIDQgnNoteImMessage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteImMessage };

static const TAknsItemID KAknsIIDQgnNoteMail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteMail };

static const TAknsItemID KAknsIIDQgnNoteMemory =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteMemory };

static const TAknsItemID KAknsIIDQgnNoteMessage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteMessage };

static const TAknsItemID KAknsIIDQgnNoteMms =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteMms };

static const TAknsItemID KAknsIIDQgnNoteMove =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteMove };

static const TAknsItemID KAknsIIDQgnNoteRemoteMailbox =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteRemoteMailbox };

static const TAknsItemID KAknsIIDQgnNoteSim =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteSim };

static const TAknsItemID KAknsIIDQgnNoteSml =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteSml };

static const TAknsItemID KAknsIIDQgnNoteSmlServer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteSmlServer };

static const TAknsItemID KAknsIIDQgnNoteUrgentMessage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteUrgentMessage };

static const TAknsItemID KAknsIIDQgnNoteVoice =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteVoice };

static const TAknsItemID KAknsIIDQgnNoteVoiceFound =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteVoiceFound };

static const TAknsItemID KAknsIIDQgnNoteWarr =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteWarr };

static const TAknsItemID KAknsIIDQgnNoteWml =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteWml };

static const TAknsItemID KAknsIIDQgnPropAlbumMusic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumMusic };

static const TAknsItemID KAknsIIDQgnPropAlbumPhoto =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumPhoto };

static const TAknsItemID KAknsIIDQgnPropAlbumVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumVideo };

static const TAknsItemID KAknsIIDQgnPropAmsGetNewSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAmsGetNewSub };

static const TAknsItemID KAknsIIDQgnPropAmMidlet =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAmMidlet };

static const TAknsItemID KAknsIIDQgnPropAmSis =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAmSis };

static const TAknsItemID KAknsIIDQgnPropBatteryIcon =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBatteryIcon };

static const TAknsItemID KAknsIIDQgnPropBlidCompassSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidCompassSub };

static const TAknsItemID KAknsIIDQgnPropBlidCompassTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidCompassTab3 };

static const TAknsItemID KAknsIIDQgnPropBlidLocationSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidLocationSub };

static const TAknsItemID KAknsIIDQgnPropBlidLocationTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidLocationTab3 };

static const TAknsItemID KAknsIIDQgnPropBlidNavigationSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidNavigationSub };

static const TAknsItemID KAknsIIDQgnPropBlidNavigationTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidNavigationTab3 };

static const TAknsItemID KAknsIIDQgnPropBrowserSelectfile =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBrowserSelectfile };

static const TAknsItemID KAknsIIDQgnPropBtCarkit =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtCarkit };

static const TAknsItemID KAknsIIDQgnPropBtComputer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtComputer };

static const TAknsItemID KAknsIIDQgnPropBtDeviceTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtDeviceTab2 };

static const TAknsItemID KAknsIIDQgnPropBtHeadset =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtHeadset };

static const TAknsItemID KAknsIIDQgnPropBtMisc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtMisc };

static const TAknsItemID KAknsIIDQgnPropBtPhone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtPhone };

static const TAknsItemID KAknsIIDQgnPropBtSetTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtSetTab2 };

static const TAknsItemID KAknsIIDQgnPropCamsBright =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCamsBright };

static const TAknsItemID KAknsIIDQgnPropCamsBurst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCamsBurst };

static const TAknsItemID KAknsIIDQgnPropCamsContrast =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCamsContrast };

static const TAknsItemID KAknsIIDQgnPropCamsSetImageTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCamsSetImageTab2 };

static const TAknsItemID KAknsIIDQgnPropCamsSetVideoTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCamsSetVideoTab2 };

static const TAknsItemID KAknsIIDQgnPropCheckboxOffSel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCheckboxOffSel };

static const TAknsItemID KAknsIIDQgnPropClkAlarmTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropClkAlarmTab2 };

static const TAknsItemID KAknsIIDQgnPropClkDualTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropClkDualTab2 };

static const TAknsItemID KAknsIIDQgnPropCmonGprsSuspended =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCmonGprsSuspended };

static const TAknsItemID KAknsIIDQgnPropDrmExpForbid =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmExpForbid };

static const TAknsItemID KAknsIIDQgnPropDrmExpForbidLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmExpForbidLarge };

static const TAknsItemID KAknsIIDQgnPropDrmRightsExp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsExp };

static const TAknsItemID KAknsIIDQgnPropDrmRightsExpLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsExpLarge };

static const TAknsItemID KAknsIIDQgnPropDrmExpLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmExpLarge }; // Intentionally duplicate numeric IID

static const TAknsItemID KAknsIIDQgnPropDrmRightsHold =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsHold };

static const TAknsItemID KAknsIIDQgnPropDrmRightsMultiple =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsMultiple };

static const TAknsItemID KAknsIIDQgnPropDrmRightsValid =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsValid };

static const TAknsItemID KAknsIIDQgnPropDrmSendForbid =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmSendForbid };

static const TAknsItemID KAknsIIDQgnPropDscontentTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDscontentTab2 };

static const TAknsItemID KAknsIIDQgnPropDsprofileTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDsprofileTab2 };

static const TAknsItemID KAknsIIDQgnPropDycActWatch =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycActWatch };

static const TAknsItemID KAknsIIDQgnPropDycAvail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycAvail };

static const TAknsItemID KAknsIIDQgnPropDycBlockedTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycBlockedTab3 };

static const TAknsItemID KAknsIIDQgnPropDycDiscreet =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycDiscreet };

static const TAknsItemID KAknsIIDQgnPropDycNotAvail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycNotAvail };

static const TAknsItemID KAknsIIDQgnPropDycNotPublish =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycNotPublish };

static const TAknsItemID KAknsIIDQgnPropDycPrivateTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycPrivateTab3 };

static const TAknsItemID KAknsIIDQgnPropDycPublicTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycPublicTab3 };

static const TAknsItemID KAknsIIDQgnPropDycStatusTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDycStatusTab1 };

static const TAknsItemID KAknsIIDQgnPropEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropEmpty };

static const TAknsItemID KAknsIIDQgnPropFileAllSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileAllSub };

static const TAknsItemID KAknsIIDQgnPropFileAllTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileAllTab4 };

static const TAknsItemID KAknsIIDQgnPropFileDownload =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileDownload };

static const TAknsItemID KAknsIIDQgnPropFileImagesSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileImagesSub };

static const TAknsItemID KAknsIIDQgnPropFileImagesTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileImagesTab4 };

static const TAknsItemID KAknsIIDQgnPropFileLinksSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileLinksSub };

static const TAknsItemID KAknsIIDQgnPropFileLinksTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileLinksTab4 };

static const TAknsItemID KAknsIIDQgnPropFileMusicSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileMusicSub };

static const TAknsItemID KAknsIIDQgnPropFileMusicTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileMusicTab4 };

static const TAknsItemID KAknsIIDQgnPropFileSounds =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileSounds };

static const TAknsItemID KAknsIIDQgnPropFileSoundsSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileSoundsSub };

static const TAknsItemID KAknsIIDQgnPropFileSoundsTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileSoundsTab4 };

static const TAknsItemID KAknsIIDQgnPropFileVideoSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileVideoSub };

static const TAknsItemID KAknsIIDQgnPropFileVideoTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileVideoTab4 };

static const TAknsItemID KAknsIIDQgnPropFmgrDycLogos =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrDycLogos };

static const TAknsItemID KAknsIIDQgnPropFmgrFileApps =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileApps };

static const TAknsItemID KAknsIIDQgnPropFmgrFileCompo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileCompo };

static const TAknsItemID KAknsIIDQgnPropFmgrFileGms =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileGms };

static const TAknsItemID KAknsIIDQgnPropFmgrFileImage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileImage };

static const TAknsItemID KAknsIIDQgnPropFmgrFileLink =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileLink };

static const TAknsItemID KAknsIIDQgnPropFmgrFilePlaylist =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFilePlaylist };

static const TAknsItemID KAknsIIDQgnPropFmgrFileSound =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileSound };

static const TAknsItemID KAknsIIDQgnPropFmgrFileVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileVideo };

static const TAknsItemID KAknsIIDQgnPropFmgrFileVoicerec =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFmgrFileVoicerec };

static const TAknsItemID KAknsIIDQgnPropFolder =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolder };

static const TAknsItemID KAknsIIDQgnPropFolderSmsTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolderSmsTab1 };

static const TAknsItemID KAknsIIDQgnPropGroupOpenTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropGroupOpenTab1 };

static const TAknsItemID KAknsIIDQgnPropGroupTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropGroupTab2 };

static const TAknsItemID KAknsIIDQgnPropGroupTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropGroupTab3 };

static const TAknsItemID KAknsIIDQgnPropImageOpenTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImageOpenTab1 };

static const TAknsItemID KAknsIIDQgnPropImFriendOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImFriendOff };

static const TAknsItemID KAknsIIDQgnPropImFriendOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImFriendOn };

static const TAknsItemID KAknsIIDQgnPropImFriendTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImFriendTab4 };

static const TAknsItemID KAknsIIDQgnPropImIboxNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImIboxNew };

static const TAknsItemID KAknsIIDQgnPropImIboxTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImIboxTab4 };

static const TAknsItemID KAknsIIDQgnPropImImsg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImImsg };

static const TAknsItemID KAknsIIDQgnPropImJoinedNotSaved =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImJoinedNotSaved };

static const TAknsItemID KAknsIIDQgnPropImListTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImListTab4 };

static const TAknsItemID KAknsIIDQgnPropImMany =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImMany };

static const TAknsItemID KAknsIIDQgnPropImNewInvit =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImNewInvit };

static const TAknsItemID KAknsIIDQgnPropImNonuserCreatedSavedActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImNonuserCreatedSavedActive };

static const TAknsItemID KAknsIIDQgnPropImNonuserCreatedSavedInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImNonuserCreatedSavedInactive };

static const TAknsItemID KAknsIIDQgnPropImSaved =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSaved };

static const TAknsItemID KAknsIIDQgnPropImSavedChat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSavedChat };

static const TAknsItemID KAknsIIDQgnPropImSavedChatTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSavedChatTab4 };

static const TAknsItemID KAknsIIDQgnPropImSavedConv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSavedConv };

static const TAknsItemID KAknsIIDQgnPropImSmileysAngry =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysAngry };

static const TAknsItemID KAknsIIDQgnPropImSmileysBored =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysBored };

static const TAknsItemID KAknsIIDQgnPropImSmileysCrying =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysCrying };

static const TAknsItemID KAknsIIDQgnPropImSmileysGlasses =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysGlasses };

static const TAknsItemID KAknsIIDQgnPropImSmileysHappy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysHappy };

static const TAknsItemID KAknsIIDQgnPropImSmileysIndif =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysIndif };

static const TAknsItemID KAknsIIDQgnPropImSmileysKiss =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysKiss };

static const TAknsItemID KAknsIIDQgnPropImSmileysLaugh =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysLaugh };

static const TAknsItemID KAknsIIDQgnPropImSmileysRobot =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysRobot };

static const TAknsItemID KAknsIIDQgnPropImSmileysSad =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysSad };

static const TAknsItemID KAknsIIDQgnPropImSmileysShock =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysShock };

static const TAknsItemID KAknsIIDQgnPropImSmileysSkeptical =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysSkeptical };

static const TAknsItemID KAknsIIDQgnPropImSmileysSleepy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysSleepy };

static const TAknsItemID KAknsIIDQgnPropImSmileysSunglasses =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysSunglasses };

static const TAknsItemID KAknsIIDQgnPropImSmileysSurprise =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysSurprise };

static const TAknsItemID KAknsIIDQgnPropImSmileysTired =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysTired };

static const TAknsItemID KAknsIIDQgnPropImSmileysVeryhappy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysVeryhappy };

static const TAknsItemID KAknsIIDQgnPropImSmileysVerysad =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysVerysad };

static const TAknsItemID KAknsIIDQgnPropImSmileysWickedsmile =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysWickedsmile };

static const TAknsItemID KAknsIIDQgnPropImSmileysWink =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSmileysWink };

static const TAknsItemID KAknsIIDQgnPropImToMany =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImToMany };

static const TAknsItemID KAknsIIDQgnPropImUserBlocked =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImUserBlocked };

static const TAknsItemID KAknsIIDQgnPropImUserCreatedActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImUserCreatedActive };

static const TAknsItemID KAknsIIDQgnPropImUserCreatedInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImUserCreatedInactive };

static const TAknsItemID KAknsIIDQgnPropKeywordFindTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropKeywordFindTab1 };

static const TAknsItemID KAknsIIDQgnPropListAlphaTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropListAlphaTab2 };

static const TAknsItemID KAknsIIDQgnPropListTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropListTab3 };

static const TAknsItemID KAknsIIDQgnPropLocAccepted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocAccepted };

static const TAknsItemID KAknsIIDQgnPropLocExpired =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocExpired };

static const TAknsItemID KAknsIIDQgnPropLocPolicyAccept =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocPolicyAccept };

static const TAknsItemID KAknsIIDQgnPropLocPolicyAsk =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocPolicyAsk };

static const TAknsItemID KAknsIIDQgnPropLocPolicyReject =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocPolicyReject };

static const TAknsItemID KAknsIIDQgnPropLocPrivacySub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocPrivacySub };

static const TAknsItemID KAknsIIDQgnPropLocPrivacyTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocPrivacyTab3 };

static const TAknsItemID KAknsIIDQgnPropLocRejected =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocRejected };

static const TAknsItemID KAknsIIDQgnPropLocRequestsTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocRequestsTab2 };

static const TAknsItemID KAknsIIDQgnPropLocRequestsTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocRequestsTab3 };

static const TAknsItemID KAknsIIDQgnPropLocSetTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocSetTab2 };

static const TAknsItemID KAknsIIDQgnPropLocSetTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLocSetTab3 };

static const TAknsItemID KAknsIIDQgnPropLogCallsInTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallsInTab3 };

static const TAknsItemID KAknsIIDQgnPropLogCallsMissedTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallsMissedTab3 };

static const TAknsItemID KAknsIIDQgnPropLogCallsOutTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallsOutTab3 };

static const TAknsItemID KAknsIIDQgnPropLogCallsTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallsTab4 };

static const TAknsItemID KAknsIIDQgnPropLogCallAll =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallAll };

static const TAknsItemID KAknsIIDQgnPropLogCallLast =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallLast };

static const TAknsItemID KAknsIIDQgnPropLogCostsSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCostsSub };

static const TAknsItemID KAknsIIDQgnPropLogCostsTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCostsTab4 };

static const TAknsItemID KAknsIIDQgnPropLogCountersTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCountersTab2 };

static const TAknsItemID KAknsIIDQgnPropLogGprsTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogGprsTab4 };

static const TAknsItemID KAknsIIDQgnPropLogIn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogIn };

static const TAknsItemID KAknsIIDQgnPropLogMissed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogMissed };

static const TAknsItemID KAknsIIDQgnPropLogOut =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogOut };

static const TAknsItemID KAknsIIDQgnPropLogTimersTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogTimersTab4 };

static const TAknsItemID KAknsIIDQgnPropLogTimerCallActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogTimerCallActive };

static const TAknsItemID KAknsIIDQgnPropMailText =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMailText };

static const TAknsItemID KAknsIIDQgnPropMailUnsupported =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMailUnsupported };

static const TAknsItemID KAknsIIDQgnPropMceBtRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceBtRead };

static const TAknsItemID KAknsIIDQgnPropMceDraftsTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceDraftsTab4 };

static const TAknsItemID KAknsIIDQgnPropMceDrTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceDrTab4 };

static const TAknsItemID KAknsIIDQgnPropMceInboxSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceInboxSmall };

static const TAknsItemID KAknsIIDQgnPropMceInboxTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceInboxTab4 };

static const TAknsItemID KAknsIIDQgnPropMceIrRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceIrRead };

static const TAknsItemID KAknsIIDQgnPropMceIrUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceIrUnread };

static const TAknsItemID KAknsIIDQgnPropMceMailFetRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMailFetRead };

static const TAknsItemID KAknsIIDQgnPropMceMailFetReaDel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMailFetReaDel };

static const TAknsItemID KAknsIIDQgnPropMceMailFetUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMailFetUnread };

static const TAknsItemID KAknsIIDQgnPropMceMailUnfetRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMailUnfetRead };

static const TAknsItemID KAknsIIDQgnPropMceMailUnfetUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMailUnfetUnread };

static const TAknsItemID KAknsIIDQgnPropMceMmsInfo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMmsInfo };

static const TAknsItemID KAknsIIDQgnPropMceMmsRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMmsRead };

static const TAknsItemID KAknsIIDQgnPropMceMmsUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMmsUnread };

static const TAknsItemID KAknsIIDQgnPropMceNotifRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceNotifRead };

static const TAknsItemID KAknsIIDQgnPropMceNotifUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceNotifUnread };

static const TAknsItemID KAknsIIDQgnPropMceOutboxTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceOutboxTab4 };

static const TAknsItemID KAknsIIDQgnPropMcePushRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMcePushRead };

static const TAknsItemID KAknsIIDQgnPropMcePushUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMcePushUnread };

static const TAknsItemID KAknsIIDQgnPropMceRemoteOnTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceRemoteOnTab4 };

static const TAknsItemID KAknsIIDQgnPropMceRemoteTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceRemoteTab4 };

static const TAknsItemID KAknsIIDQgnPropMceSentTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSentTab4 };

static const TAknsItemID KAknsIIDQgnPropMceSmartRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmartRead };

static const TAknsItemID KAknsIIDQgnPropMceSmartUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmartUnread };

static const TAknsItemID KAknsIIDQgnPropMceSmsInfo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmsInfo };

static const TAknsItemID KAknsIIDQgnPropMceSmsRead =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmsRead };

static const TAknsItemID KAknsIIDQgnPropMceSmsReadUrgent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmsReadUrgent };

static const TAknsItemID KAknsIIDQgnPropMceSmsUnread =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmsUnread };

static const TAknsItemID KAknsIIDQgnPropMceSmsUnreadUrgent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmsUnreadUrgent };

static const TAknsItemID KAknsIIDQgnPropMceTemplate =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceTemplate };

static const TAknsItemID KAknsIIDQgnPropMemcMmcTab =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMemcMmcTab };

static const TAknsItemID KAknsIIDQgnPropMemcMmcTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMemcMmcTab2 };

static const TAknsItemID KAknsIIDQgnPropMemcPhoneTab =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMemcPhoneTab };

static const TAknsItemID KAknsIIDQgnPropMemcPhoneTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMemcPhoneTab2 };

static const TAknsItemID KAknsIIDQgnPropMmsEmptyPageSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsEmptyPageSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateTitleSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateTitleSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateVideoSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateVideoSub };

static const TAknsItemID KAknsIIDQgnPropNetwork2g =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNetwork2g };

static const TAknsItemID KAknsIIDQgnPropNetwork3g =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNetwork3g };

static const TAknsItemID KAknsIIDQgnPropNrtypHome =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypHome };

static const TAknsItemID KAknsIIDQgnPropNrtypHomeDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypHomeDiv };

static const TAknsItemID KAknsIIDQgnPropNrtypMobileDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypMobileDiv };

static const TAknsItemID KAknsIIDQgnPropNrtypPhoneCnap =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypPhoneCnap };

static const TAknsItemID KAknsIIDQgnPropNrtypPhoneDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypPhoneDiv };

static const TAknsItemID KAknsIIDQgnPropNrtypSdn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypSdn };

static const TAknsItemID KAknsIIDQgnPropNrtypVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypVideo };

static const TAknsItemID KAknsIIDQgnPropNrtypWork =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypWork };

static const TAknsItemID KAknsIIDQgnPropNrtypWorkDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypWorkDiv };

static const TAknsItemID KAknsIIDQgnPropNrtypWvid =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypWvid };

static const TAknsItemID KAknsIIDQgnPropNtypVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNtypVideo };

static const TAknsItemID KAknsIIDQgnPropOtaTone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropOtaTone };

static const TAknsItemID KAknsIIDQgnPropPbContactsTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPbContactsTab3 };

static const TAknsItemID KAknsIIDQgnPropPbPersonalTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPbPersonalTab4 };

static const TAknsItemID KAknsIIDQgnPropPbPhotoTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPbPhotoTab3 };

static const TAknsItemID KAknsIIDQgnPropPbSubsTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPbSubsTab3 };

static const TAknsItemID KAknsIIDQgnPropPinbAnchorId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbAnchorId };

static const TAknsItemID KAknsIIDQgnPropPinbBagId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbBagId };

static const TAknsItemID KAknsIIDQgnPropPinbBeerId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbBeerId };

static const TAknsItemID KAknsIIDQgnPropPinbBookId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbBookId };

static const TAknsItemID KAknsIIDQgnPropPinbCrownId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbCrownId };

static const TAknsItemID KAknsIIDQgnPropPinbCupId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbCupId };

static const TAknsItemID KAknsIIDQgnPropPinbDocument =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbDocument };

static const TAknsItemID KAknsIIDQgnPropPinbDuckId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbDuckId };

static const TAknsItemID KAknsIIDQgnPropPinbEightId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbEightId };

static const TAknsItemID KAknsIIDQgnPropPinbExclamtionId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbExclamtionId };

static const TAknsItemID KAknsIIDQgnPropPinbFiveId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbFiveId };

static const TAknsItemID KAknsIIDQgnPropPinbFourId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbFourId };

static const TAknsItemID KAknsIIDQgnPropPinbHeartId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbHeartId };

static const TAknsItemID KAknsIIDQgnPropPinbInbox =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbInbox };

static const TAknsItemID KAknsIIDQgnPropPinbLinkBmId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkBmId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkImageId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkImageId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkMessageId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkMessageId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkNoteId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkNoteId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkPageId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkPageId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkToneId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkToneId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkVideoId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkVideoId };

static const TAknsItemID KAknsIIDQgnPropPinbLinkVorecId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkVorecId };

static const TAknsItemID KAknsIIDQgnPropPinbLockId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLockId };

static const TAknsItemID KAknsIIDQgnPropPinbLorryId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLorryId };

static const TAknsItemID KAknsIIDQgnPropPinbMoneyId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbMoneyId };

static const TAknsItemID KAknsIIDQgnPropPinbMovieId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbMovieId };

static const TAknsItemID KAknsIIDQgnPropPinbNineId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbNineId };

static const TAknsItemID KAknsIIDQgnPropPinbNotepad =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbNotepad };

static const TAknsItemID KAknsIIDQgnPropPinbOneId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbOneId };

static const TAknsItemID KAknsIIDQgnPropPinbPhoneId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbPhoneId };

static const TAknsItemID KAknsIIDQgnPropPinbSevenId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbSevenId };

static const TAknsItemID KAknsIIDQgnPropPinbSixId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbSixId };

static const TAknsItemID KAknsIIDQgnPropPinbSmiley1Id =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbSmiley1Id };

static const TAknsItemID KAknsIIDQgnPropPinbSmiley2Id =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbSmiley2Id };

static const TAknsItemID KAknsIIDQgnPropPinbSoccerId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbSoccerId };

static const TAknsItemID KAknsIIDQgnPropPinbStarId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbStarId };

static const TAknsItemID KAknsIIDQgnPropPinbSuitcaseId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbSuitcaseId };

static const TAknsItemID KAknsIIDQgnPropPinbTeddyId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbTeddyId };

static const TAknsItemID KAknsIIDQgnPropPinbThreeId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbThreeId };

static const TAknsItemID KAknsIIDQgnPropPinbToday =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbToday };

static const TAknsItemID KAknsIIDQgnPropPinbTwoId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbTwoId };

static const TAknsItemID KAknsIIDQgnPropPinbWml =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbWml };

static const TAknsItemID KAknsIIDQgnPropPinbZeroId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbZeroId };

static const TAknsItemID KAknsIIDQgnPropPslnActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPslnActive };

static const TAknsItemID KAknsIIDQgnPropPushDefault =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPushDefault };

static const TAknsItemID KAknsIIDQgnPropSetAccessoryTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetAccessoryTab4 };

static const TAknsItemID KAknsIIDQgnPropSetBarrTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetBarrTab4 };

static const TAknsItemID KAknsIIDQgnPropSetCallTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetCallTab4 };

static const TAknsItemID KAknsIIDQgnPropSetConnecTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetConnecTab4 };

static const TAknsItemID KAknsIIDQgnPropSetDatimTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetDatimTab4 };

static const TAknsItemID KAknsIIDQgnPropSetDeviceTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetDeviceTab4 };

static const TAknsItemID KAknsIIDQgnPropSetDivTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetDivTab4 };

static const TAknsItemID KAknsIIDQgnPropSetMpAudioTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetMpAudioTab3 };

static const TAknsItemID KAknsIIDQgnPropSetMpStreamTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetMpStreamTab3 };

static const TAknsItemID KAknsIIDQgnPropSetMpVideoTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetMpVideoTab3 };

static const TAknsItemID KAknsIIDQgnPropSetNetworkTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetNetworkTab4 };

static const TAknsItemID KAknsIIDQgnPropSetSecTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetSecTab4 };

static const TAknsItemID KAknsIIDQgnPropSetTonesSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetTonesSub };

static const TAknsItemID KAknsIIDQgnPropSetTonesTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetTonesTab4 };

static const TAknsItemID KAknsIIDQgnPropSignalIcon =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSignalIcon };

static const TAknsItemID KAknsIIDQgnPropSmlBtOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlBtOff };

static const TAknsItemID KAknsIIDQgnPropSmlHttp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlHttp };

static const TAknsItemID KAknsIIDQgnPropSmlHttpOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlHttpOff };

static const TAknsItemID KAknsIIDQgnPropSmlIr =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlIr };

static const TAknsItemID KAknsIIDQgnPropSmlIrOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlIrOff };

static const TAknsItemID KAknsIIDQgnPropSmlRemoteNewSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlRemoteNewSub };

static const TAknsItemID KAknsIIDQgnPropSmlRemoteSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlRemoteSub };

static const TAknsItemID KAknsIIDQgnPropSmlUsb =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlUsb };

static const TAknsItemID KAknsIIDQgnPropSmlUsbOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlUsbOff };

static const TAknsItemID KAknsIIDQgnPropSmsDeliveredCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsDeliveredCdma };

static const TAknsItemID KAknsIIDQgnPropSmsDeliveredUrgentCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsDeliveredUrgentCdma };

static const TAknsItemID KAknsIIDQgnPropSmsFailedCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsFailedCdma };

static const TAknsItemID KAknsIIDQgnPropSmsFailedUrgentCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsFailedUrgentCdma };

static const TAknsItemID KAknsIIDQgnPropSmsPendingCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsPendingCdma };

static const TAknsItemID KAknsIIDQgnPropSmsPendingUrgentCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsPendingUrgentCdma };

static const TAknsItemID KAknsIIDQgnPropSmsSentCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsSentCdma };

static const TAknsItemID KAknsIIDQgnPropSmsSentUrgentCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsSentUrgentCdma };

static const TAknsItemID KAknsIIDQgnPropSmsWaitingCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsWaitingCdma };

static const TAknsItemID KAknsIIDQgnPropSmsWaitingUrgentCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmsWaitingUrgentCdma };

static const TAknsItemID KAknsIIDQgnPropTodoDone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropTodoDone };

static const TAknsItemID KAknsIIDQgnPropTodoUndone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropTodoUndone };

static const TAknsItemID KAknsIIDQgnPropVoice =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVoice };

static const TAknsItemID KAknsIIDQgnPropVpnLogError =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVpnLogError };

static const TAknsItemID KAknsIIDQgnPropVpnLogInfo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVpnLogInfo };

static const TAknsItemID KAknsIIDQgnPropVpnLogWarn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVpnLogWarn };

static const TAknsItemID KAknsIIDQgnPropWalletCards =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletCards };

static const TAknsItemID KAknsIIDQgnPropWalletCardsLib =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletCardsLib };

static const TAknsItemID KAknsIIDQgnPropWalletCardsLibDef =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletCardsLibDef };

static const TAknsItemID KAknsIIDQgnPropWalletCardsLibOta =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletCardsLibOta };

static const TAknsItemID KAknsIIDQgnPropWalletCardsOta =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletCardsOta };

static const TAknsItemID KAknsIIDQgnPropWalletPnotes =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletPnotes };

static const TAknsItemID KAknsIIDQgnPropWalletService =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletService };

static const TAknsItemID KAknsIIDQgnPropWalletTickets =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWalletTickets };

static const TAknsItemID KAknsIIDQgnPropWmlBm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlBm };

static const TAknsItemID KAknsIIDQgnPropWmlBmAdap =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlBmAdap };

static const TAknsItemID KAknsIIDQgnPropWmlBmLast =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlBmLast };

static const TAknsItemID KAknsIIDQgnPropWmlBmTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlBmTab2 };

static const TAknsItemID KAknsIIDQgnPropWmlCheckboxOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlCheckboxOff };

static const TAknsItemID KAknsIIDQgnPropWmlCheckboxOffSel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlCheckboxOffSel };

static const TAknsItemID KAknsIIDQgnPropWmlCheckboxOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlCheckboxOn };

static const TAknsItemID KAknsIIDQgnPropWmlCheckboxOnSel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlCheckboxOnSel };

static const TAknsItemID KAknsIIDQgnPropWmlCircle =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlCircle };

static const TAknsItemID KAknsIIDQgnPropWmlCsd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlCsd };

static const TAknsItemID KAknsIIDQgnPropWmlDisc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlDisc };

static const TAknsItemID KAknsIIDQgnPropWmlGprs =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlGprs };

static const TAknsItemID KAknsIIDQgnPropWmlHome =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlHome };

static const TAknsItemID KAknsIIDQgnPropWmlHscsd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlHscsd };

static const TAknsItemID KAknsIIDQgnPropWmlImageMap =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlImageMap };

static const TAknsItemID KAknsIIDQgnPropWmlImageNotShown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlImageNotShown };

static const TAknsItemID KAknsIIDQgnPropWmlObject =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlObject };

static const TAknsItemID KAknsIIDQgnPropWmlPage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlPage };

static const TAknsItemID KAknsIIDQgnPropWmlPagesTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlPagesTab2 };

static const TAknsItemID KAknsIIDQgnPropWmlRadiobuttOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlRadiobuttOff };

static const TAknsItemID KAknsIIDQgnPropWmlRadiobuttOffSel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlRadiobuttOffSel };

static const TAknsItemID KAknsIIDQgnPropWmlRadiobuttOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlRadiobuttOn };

static const TAknsItemID KAknsIIDQgnPropWmlRadiobuttOnSel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlRadiobuttOnSel };

static const TAknsItemID KAknsIIDQgnPropWmlSelectarrow =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlSelectarrow };

static const TAknsItemID KAknsIIDQgnPropWmlSelectfile =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlSelectfile };

static const TAknsItemID KAknsIIDQgnPropWmlSms =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlSms };

static const TAknsItemID KAknsIIDQgnPropWmlSquare =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlSquare };

static const TAknsItemID KAknsIIDQgnStatAlarm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatAlarm };

static const TAknsItemID KAknsIIDQgnStatBt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatBt };

static const TAknsItemID KAknsIIDQgnStatBtBlank =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatBtBlank };

static const TAknsItemID KAknsIIDQgnStatBtUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatBtUni };

static const TAknsItemID KAknsIIDQgnStatBtUniBlank =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatBtUniBlank };

static const TAknsItemID KAknsIIDQgnStatCaseArabic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseArabic };

static const TAknsItemID KAknsIIDQgnStatCaseArabicNumeric =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseArabicNumeric };

static const TAknsItemID KAknsIIDQgnStatCaseArabicNumericQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseArabicNumericQuery };

static const TAknsItemID KAknsIIDQgnStatCaseArabicQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseArabicQuery };

static const TAknsItemID KAknsIIDQgnStatCaseCapital =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseCapital };

static const TAknsItemID KAknsIIDQgnStatCaseCapitalFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseCapitalFull };

static const TAknsItemID KAknsIIDQgnStatCaseCapitalQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseCapitalQuery };

static const TAknsItemID KAknsIIDQgnStatCaseHebrew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseHebrew };

static const TAknsItemID KAknsIIDQgnStatCaseHebrewQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseHebrewQuery };

static const TAknsItemID KAknsIIDQgnStatCaseNumeric =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseNumeric };

static const TAknsItemID KAknsIIDQgnStatCaseNumericFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseNumericFull };

static const TAknsItemID KAknsIIDQgnStatCaseNumericQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseNumericQuery };

static const TAknsItemID KAknsIIDQgnStatCaseSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseSmall };

static const TAknsItemID KAknsIIDQgnStatCaseSmallFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseSmallFull };

static const TAknsItemID KAknsIIDQgnStatCaseSmallQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseSmallQuery };

static const TAknsItemID KAknsIIDQgnStatCaseText =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseText };

static const TAknsItemID KAknsIIDQgnStatCaseTextFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseTextFull };

static const TAknsItemID KAknsIIDQgnStatCaseTextQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseTextQuery };

static const TAknsItemID KAknsIIDQgnStatCaseThai =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseThai };

static const TAknsItemID KAknsIIDQgnStatCaseTitle =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseTitle };

static const TAknsItemID KAknsIIDQgnStatCaseTitleQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseTitleQuery };

static const TAknsItemID KAknsIIDQgnStatCdmaRoaming =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCdmaRoaming };

static const TAknsItemID KAknsIIDQgnStatCdmaRoamingUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCdmaRoamingUni };

static const TAknsItemID KAknsIIDQgnStatChiPinyin =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiPinyin };

static const TAknsItemID KAknsIIDQgnStatChiPinyinQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiPinyinQuery };

static const TAknsItemID KAknsIIDQgnStatChiStroke =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiStroke };

static const TAknsItemID KAknsIIDQgnStatChiStrokeFind =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiStrokeFind };

static const TAknsItemID KAknsIIDQgnStatChiStrokeFindQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiStrokeFindQuery };

static const TAknsItemID KAknsIIDQgnStatChiStrokeQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiStrokeQuery };

static const TAknsItemID KAknsIIDQgnStatChiStrokeTrad =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiStrokeTrad };

static const TAknsItemID KAknsIIDQgnStatChiStrokeTradQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiStrokeTradQuery };

static const TAknsItemID KAknsIIDQgnStatChiZhuyin =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiZhuyin };

static const TAknsItemID KAknsIIDQgnStatChiZhuyinFind =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiZhuyinFind };

static const TAknsItemID KAknsIIDQgnStatChiZhuyinFindQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiZhuyinFindQuery };

static const TAknsItemID KAknsIIDQgnStatChiZhuyinQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiZhuyinQuery };

static const TAknsItemID KAknsIIDQgnStatCypheringOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCypheringOn };

static const TAknsItemID KAknsIIDQgnStatCypheringOnUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCypheringOnUni };

static const TAknsItemID KAknsIIDQgnStatDivert0 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatDivert0 };

static const TAknsItemID KAknsIIDQgnStatDivert1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatDivert1 };

static const TAknsItemID KAknsIIDQgnStatDivert12 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatDivert12 };

static const TAknsItemID KAknsIIDQgnStatDivert2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatDivert2 };

static const TAknsItemID KAknsIIDQgnStatDivertVm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatDivertVm };

static const TAknsItemID KAknsIIDQgnStatHeadset =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatHeadset };

static const TAknsItemID KAknsIIDQgnStatHeadsetUnavailable =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatHeadsetUnavailable };

static const TAknsItemID KAknsIIDQgnStatIhf =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatIhf };

static const TAknsItemID KAknsIIDQgnStatIhfUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatIhfUni };

static const TAknsItemID KAknsIIDQgnStatImUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatImUni };

static const TAknsItemID KAknsIIDQgnStatIr =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatIr };

static const TAknsItemID KAknsIIDQgnStatIrBlank =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatIrBlank };

static const TAknsItemID KAknsIIDQgnStatIrUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatIrUni };

static const TAknsItemID KAknsIIDQgnStatIrUniBlank =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatIrUniBlank };

static const TAknsItemID KAknsIIDQgnStatJapinHiragana =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatJapinHiragana };

static const TAknsItemID KAknsIIDQgnStatJapinHiraganaOnly =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatJapinHiraganaOnly };

static const TAknsItemID KAknsIIDQgnStatJapinKatakanaFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatJapinKatakanaFull };

static const TAknsItemID KAknsIIDQgnStatJapinKatakanaHalf =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatJapinKatakanaHalf };

static const TAknsItemID KAknsIIDQgnStatKeyguard =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatKeyguard };

static const TAknsItemID KAknsIIDQgnStatLine2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatLine2 };

static const TAknsItemID KAknsIIDQgnStatLoc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatLoc };

static const TAknsItemID KAknsIIDQgnStatLocOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatLocOff };

static const TAknsItemID KAknsIIDQgnStatLocOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatLocOn };

static const TAknsItemID KAknsIIDQgnStatLoopset =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatLoopset };

static const TAknsItemID KAknsIIDQgnStatMessage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessage };

static const TAknsItemID KAknsIIDQgnStatMessageBlank =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageBlank };

static const TAknsItemID KAknsIIDQgnStatMessageData =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageData };

static const TAknsItemID KAknsIIDQgnStatMessageDataUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageDataUni };

static const TAknsItemID KAknsIIDQgnStatMessageFax =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageFax };

static const TAknsItemID KAknsIIDQgnStatMessageFaxUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageFaxUni };

static const TAknsItemID KAknsIIDQgnStatMessageMail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageMail };

static const TAknsItemID KAknsIIDQgnStatMessageMailUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageMailUni };

static const TAknsItemID KAknsIIDQgnStatMessageOther =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageOther };

static const TAknsItemID KAknsIIDQgnStatMessageOtherUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageOtherUni };

static const TAknsItemID KAknsIIDQgnStatMessagePs =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessagePs };

static const TAknsItemID KAknsIIDQgnStatMessageRemote =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageRemote };

static const TAknsItemID KAknsIIDQgnStatMessageRemoteUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageRemoteUni };

static const TAknsItemID KAknsIIDQgnStatMessageUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageUni };

static const TAknsItemID KAknsIIDQgnStatMessageUniBlank =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMessageUniBlank };

static const TAknsItemID KAknsIIDQgnStatMissedCallsUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMissedCallsUni };

static const TAknsItemID KAknsIIDQgnStatMissedCallPs =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMissedCallPs };

static const TAknsItemID KAknsIIDQgnStatModBt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatModBt };

static const TAknsItemID KAknsIIDQgnStatOutbox =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatOutbox };

static const TAknsItemID KAknsIIDQgnStatOutboxUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatOutboxUni };

static const TAknsItemID KAknsIIDQgnStatQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatQuery };

static const TAknsItemID KAknsIIDQgnStatQueryQuery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatQueryQuery };

static const TAknsItemID KAknsIIDQgnStatT9 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatT9 };

static const TAknsItemID KAknsIIDQgnStatT9Query =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatT9Query };

static const TAknsItemID KAknsIIDQgnStatTty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatTty };

static const TAknsItemID KAknsIIDQgnStatUsb =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatUsb };

static const TAknsItemID KAknsIIDQgnStatUsbUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatUsbUni };

static const TAknsItemID KAknsIIDQgnStatVm0 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm0 };

static const TAknsItemID KAknsIIDQgnStatVm0Uni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm0Uni };

static const TAknsItemID KAknsIIDQgnStatVm1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm1 };

static const TAknsItemID KAknsIIDQgnStatVm12 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm12 };

static const TAknsItemID KAknsIIDQgnStatVm12Uni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm12Uni };

static const TAknsItemID KAknsIIDQgnStatVm1Uni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm1Uni };

static const TAknsItemID KAknsIIDQgnStatVm2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm2 };

static const TAknsItemID KAknsIIDQgnStatVm2Uni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVm2Uni };

static const TAknsItemID KAknsIIDQgnStatZoneHome =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatZoneHome };

static const TAknsItemID KAknsIIDQgnStatZoneViag =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatZoneViag };

static const TAknsItemID KAknsIIDQgnIndiJapFindCaseNumericFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindCaseNumericFull };

static const TAknsItemID KAknsIIDQgnIndiJapFindCaseSmallFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindCaseSmallFull };

static const TAknsItemID KAknsIIDQgnIndiJapFindHiragana =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindHiragana };

static const TAknsItemID KAknsIIDQgnIndiJapFindHiraganaOnly =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindHiraganaOnly };

static const TAknsItemID KAknsIIDQgnIndiJapFindKatakanaFull =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindKatakanaFull };

static const TAknsItemID KAknsIIDQgnIndiJapFindKatakanaHalf =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindKatakanaHalf };

static const TAknsItemID KAknsIIDQgnIndiJapFindPredictive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiJapFindPredictive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonBack =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonBack };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonBackInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonBackInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonBackPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonBackPressed };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonDown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonDown };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonDownInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonDownInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonDownPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonDownPressed };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonForward =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonForward };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonForwardInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonForwardInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonForwardPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonForwardPressed };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonPause };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonPauseInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonPauseInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonPausePressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonPausePressed };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonRecord =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonRecord };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonRecordInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonRecordInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonRecordPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonRecordPressed };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonStop };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonStopInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonStopInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonStopPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonStopPressed };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonUp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonUp };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonUpInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonUpInactive };

static const TAknsItemID KAknsIIDQgnIndiRadioButtonUpPressed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiRadioButtonUpPressed };

static const TAknsItemID KAknsIIDQgnPropAlbumMain =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumMain };

static const TAknsItemID KAknsIIDQgnPropAlbumPhotoSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumPhotoSmall };

static const TAknsItemID KAknsIIDQgnPropAlbumVideoSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumVideoSmall };

static const TAknsItemID KAknsIIDQgnPropLogGprsReceivedSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogGprsReceivedSub };

static const TAknsItemID KAknsIIDQgnPropLogGprsSentSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogGprsSentSub };

static const TAknsItemID KAknsIIDQgnPropLogGprsTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogGprsTab3 };

static const TAknsItemID KAknsIIDQgnPropPinbLinkStreamId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbLinkStreamId };

static const TAknsItemID KAknsIIDQgnStatCaseShift =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCaseShift };

static const TAknsItemID KAknsIIDQgnIndiCamsBw =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsBw };

static const TAknsItemID KAknsIIDQgnIndiCamsCloudy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsCloudy };

static const TAknsItemID KAknsIIDQgnIndiCamsFluorescent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsFluorescent };

static const TAknsItemID KAknsIIDQgnIndiCamsNegative =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsNegative };

static const TAknsItemID KAknsIIDQgnIndiCamsSepia =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsSepia };

static const TAknsItemID KAknsIIDQgnIndiCamsSunny =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsSunny };

static const TAknsItemID KAknsIIDQgnIndiCamsTungsten =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsTungsten };

static const TAknsItemID KAknsIIDQgnIndiPhoneAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiPhoneAdd };

static const TAknsItemID KAknsIIDQgnPropLinkEmbdLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLinkEmbdLarge };

static const TAknsItemID KAknsIIDQgnPropLinkEmbdMedium =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLinkEmbdMedium };

static const TAknsItemID KAknsIIDQgnPropLinkEmbdSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLinkEmbdSmall };

static const TAknsItemID KAknsIIDQgnPropMceDraft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceDraft };

static const TAknsItemID KAknsIIDQgnPropMceDraftNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceDraftNew };

static const TAknsItemID KAknsIIDQgnPropMceInboxSmallNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceInboxSmallNew };

static const TAknsItemID KAknsIIDQgnPropMceOutboxSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceOutboxSmall };

static const TAknsItemID KAknsIIDQgnPropMceOutboxSmallNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceOutboxSmallNew };

static const TAknsItemID KAknsIIDQgnPropMceSent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSent };

static const TAknsItemID KAknsIIDQgnPropMceSentNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSentNew };

static const TAknsItemID KAknsIIDQgnPropSmlRemoteTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlRemoteTab4 };

static const TAknsItemID KAknsIIDQgnIndiAiSat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiSat };

static const TAknsItemID KAknsIIDQgnMenuCb2Cxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuCb2Cxt };

static const TAknsItemID KAknsIIDQgnMenuSimfdnCxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuSimfdnCxt };

static const TAknsItemID KAknsIIDQgnMenuSiminCxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuSiminCxt };

static const TAknsItemID KAknsIIDQgnPropDrmRightsExpForbidLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsExpForbidLarge };

static const TAknsItemID KAknsIIDQgnMenuCbCxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuCbCxt };

static const TAknsItemID KAknsIIDQgnGrafMmsTemplatePrevImage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTemplatePrevImage };

static const TAknsItemID KAknsIIDQgnGrafMmsTemplatePrevText =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTemplatePrevText };

static const TAknsItemID KAknsIIDQgnGrafMmsTemplatePrevVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsTemplatePrevVideo };

static const TAknsItemID KAknsIIDQgnIndiSignalNotAvailCdma =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalNotAvailCdma };

static const TAknsItemID KAknsIIDQgnIndiSignalNoService =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalNoService };

static const TAknsItemID KAknsIIDQgnMenuDycRoamingCxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuDycRoamingCxt };

static const TAknsItemID KAknsIIDQgnMenuImRoamingCxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuImRoamingCxt };

static const TAknsItemID KAknsIIDQgnMenuMyAccountLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuMyAccountLst };

static const TAknsItemID KAknsIIDQgnPropAmsGetNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAmsGetNew };

static const TAknsItemID KAknsIIDQgnPropFileOtherSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileOtherSub };

static const TAknsItemID KAknsIIDQgnPropFileOtherTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileOtherTab4 };

static const TAknsItemID KAknsIIDQgnPropMyAccount =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMyAccount };

static const TAknsItemID KAknsIIDQgnIndiAiCale =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiCale };

static const TAknsItemID KAknsIIDQgnIndiAiTodo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiTodo };

static const TAknsItemID KAknsIIDQgnIndiMmsLinksEmail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsLinksEmail };

static const TAknsItemID KAknsIIDQgnIndiMmsLinksPhone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsLinksPhone };

static const TAknsItemID KAknsIIDQgnIndiMmsLinksWml =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsLinksWml };

static const TAknsItemID KAknsIIDQgnIndiMmsSpeakerMuted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsSpeakerMuted };

static const TAknsItemID KAknsIIDQgnPropAiShortcut =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAiShortcut };

static const TAknsItemID KAknsIIDQgnPropImFriendAway =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImFriendAway };

static const TAknsItemID KAknsIIDQgnPropImServer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImServer };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageBotSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageBotSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageMidSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageMidSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmBotSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmBotSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmLdiaSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmLdiaSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmManySub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmManySub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmRdiaSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmRdiaSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmTlSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmTlSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateImageSmTrSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateImageSmTrSub };

static const TAknsItemID KAknsIIDQgnPropMmsTemplateTextSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsTemplateTextSub };

static const TAknsItemID KAknsIIDQgnPropWmlPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlPlay };

static const TAknsItemID KAknsIIDQgnIndiOnlineAlbumImageAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiOnlineAlbumImageAdd };

static const TAknsItemID KAknsIIDQgnIndiOnlineAlbumVideoAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiOnlineAlbumVideoAdd };

static const TAknsItemID KAknsIIDQgnPropClsInactiveChannel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropClsInactiveChannel };

static const TAknsItemID KAknsIIDQgnPropClsTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropClsTab1 };

static const TAknsItemID KAknsIIDQgnPropOnlineAlbumEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropOnlineAlbumEmpty };

static const TAknsItemID KAknsIIDQgnPropNetwSharedConn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNetwSharedConn };

static const TAknsItemID KAknsIIDQgnPropFolderDynamic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolderDynamic };

static const TAknsItemID KAknsIIDQgnPropFolderDynamicLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolderDynamicLarge };

static const TAknsItemID KAknsIIDQgnPropFolderMmc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolderMmc };

static const TAknsItemID KAknsIIDQgnPropFolderProfiles =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolderProfiles };

static const TAknsItemID KAknsIIDQgnPropLmArea =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmArea };

static const TAknsItemID KAknsIIDQgnPropLmBusiness =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmBusiness };

static const TAknsItemID KAknsIIDQgnPropLmCategoriesTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmCategoriesTab2 };

static const TAknsItemID KAknsIIDQgnPropLmChurch =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmChurch };

static const TAknsItemID KAknsIIDQgnPropLmCommunication =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmCommunication };

static const TAknsItemID KAknsIIDQgnPropLmCxt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmCxt };

static const TAknsItemID KAknsIIDQgnPropLmEducation =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmEducation };

static const TAknsItemID KAknsIIDQgnPropLmFun =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmFun };

static const TAknsItemID KAknsIIDQgnPropLmGene =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmGene };

static const TAknsItemID KAknsIIDQgnPropLmHotel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmHotel };

static const TAknsItemID KAknsIIDQgnPropLmLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmLst };

static const TAknsItemID KAknsIIDQgnPropLmNamesTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmNamesTab2 };

static const TAknsItemID KAknsIIDQgnPropLmOutdoor =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmOutdoor };

static const TAknsItemID KAknsIIDQgnPropLmPeople =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmPeople };

static const TAknsItemID KAknsIIDQgnPropLmPublic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmPublic };

static const TAknsItemID KAknsIIDQgnPropLmRestaurant =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmRestaurant };

static const TAknsItemID KAknsIIDQgnPropLmShopping =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmShopping };

static const TAknsItemID KAknsIIDQgnPropLmSightseeing =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmSightseeing };

static const TAknsItemID KAknsIIDQgnPropLmSport =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmSport };

static const TAknsItemID KAknsIIDQgnPropLmTransport =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLmTransport };

static const TAknsItemID KAknsIIDQgnPropPmAttachAlbum =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPmAttachAlbum };

static const TAknsItemID KAknsIIDQgnPropProfiles =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropProfiles };

static const TAknsItemID KAknsIIDQgnPropProfilesSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropProfilesSmall };

static const TAknsItemID KAknsIIDQgnPropSmlSyncFromServer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlSyncFromServer };

static const TAknsItemID KAknsIIDQgnPropSmlSyncOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlSyncOff };

static const TAknsItemID KAknsIIDQgnPropSmlSyncServer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlSyncServer };

static const TAknsItemID KAknsIIDQgnPropSmlSyncToServer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSmlSyncToServer };

static const TAknsItemID KAknsIIDQgnPropAlbumPermanentPhoto =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumPermanentPhoto };

static const TAknsItemID KAknsIIDQgnPropAlbumPermanentPhotoSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumPermanentPhotoSmall };

static const TAknsItemID KAknsIIDQgnPropAlbumPermanentVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumPermanentVideo };

static const TAknsItemID KAknsIIDQgnPropAlbumPermanentVideoSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumPermanentVideoSmall };

static const TAknsItemID KAknsIIDQgnPropAlbumSounds =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumSounds };

static const TAknsItemID KAknsIIDQgnPropAlbumSoundsSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropAlbumSoundsSmall };

static const TAknsItemID KAknsIIDQgnPropFolderPermanent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFolderPermanent };

static const TAknsItemID KAknsIIDQgnPropOnlineAlbumSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropOnlineAlbumSub };

static const TAknsItemID KAknsIIDQgnGrafDimWipeLsc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafDimWipeLsc };

static const TAknsItemID KAknsIIDQgnGrafDimWipePrt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafDimWipePrt };

static const TAknsItemID KAknsIIDQgnGrafLinePrimaryHorizontal =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafLinePrimaryHorizontal };

static const TAknsItemID KAknsIIDQgnGrafLinePrimaryHorizontalDashed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafLinePrimaryHorizontalDashed };

static const TAknsItemID KAknsIIDQgnGrafLinePrimaryVertical =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafLinePrimaryVertical };

static const TAknsItemID KAknsIIDQgnGrafLinePrimaryVerticalDashed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafLinePrimaryVerticalDashed };

static const TAknsItemID KAknsIIDQgnGrafLineSecondaryHorizontal =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafLineSecondaryHorizontal };

static const TAknsItemID KAknsIIDQgnGrafLineSecondaryVertical =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafLineSecondaryVertical };

static const TAknsItemID KAknsIIDQgnGrafStatusSmallProgress =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafStatusSmallProgress };

static const TAknsItemID KAknsIIDQgnGrafStatusSmallWaitBg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafStatusSmallWaitBg };

static const TAknsItemID KAknsIIDQgnGrafTabActiveL =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafTabActiveL };

static const TAknsItemID KAknsIIDQgnGrafTabActiveM =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafTabActiveM };

static const TAknsItemID KAknsIIDQgnGrafTabActiveR =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafTabActiveR };

static const TAknsItemID KAknsIIDQgnGrafTabPassiveL =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafTabPassiveL };

static const TAknsItemID KAknsIIDQgnGrafTabPassiveM =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafTabPassiveM };

static const TAknsItemID KAknsIIDQgnGrafTabPassiveR =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafTabPassiveR };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet10Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet10Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet10On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet10On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet1Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet1Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet1On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet1On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet2Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet2Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet2On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet2On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet3Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet3Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet3On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet3On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet4Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet4Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet4On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet4On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet5Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet5Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet5On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet5On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet6Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet6Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet6On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet6On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet7Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet7Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet7On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet7On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet8Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet8Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet8On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet8On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet9Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet9Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSet9On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSet9On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall10Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall10Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall10On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall10On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall1Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall1Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall1On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall1On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall2Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall2Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall2On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall2On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall3Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall3Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall3On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall3On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall4Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall4Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall4On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall4On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall5Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall5Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall5On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall5On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall6Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall6Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall6On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall6On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall7Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall7Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall7On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall7On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall8Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall8Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall8On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall8On };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall9Off =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall9Off };

static const TAknsItemID KAknsIIDQgnGrafVolumeSmall9On =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafVolumeSmall9On };

static const TAknsItemID KAknsIIDQgnGrafWaitIncrem =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafWaitIncrem };

static const TAknsItemID KAknsIIDQgnImStatEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnImStatEmpty };

static const TAknsItemID KAknsIIDQgnIndiAmInstNoAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAmInstNoAdd };

static const TAknsItemID KAknsIIDQgnIndiAttachAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachAdd };

static const TAknsItemID KAknsIIDQgnIndiAttachUnfetchedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachUnfetchedAdd };

static const TAknsItemID KAknsIIDQgnIndiAttachVideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAttachVideo };

static const TAknsItemID KAknsIIDQgnIndiBatteryStrengthLsc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBatteryStrengthLsc };

static const TAknsItemID KAknsIIDQgnIndiBrowserMmcAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBrowserMmcAdd };

static const TAknsItemID KAknsIIDQgnIndiBrowserPauseAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBrowserPauseAdd };

static const TAknsItemID KAknsIIDQgnIndiBtConnectedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiBtConnectedAdd };

static const TAknsItemID KAknsIIDQgnIndiCallVideoBlindInMaskSoft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVideoBlindInMaskSoft };

static const TAknsItemID KAknsIIDQgnIndiCallVideoBlindOutMaskSoft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVideoBlindOutMaskSoft };

static const TAknsItemID KAknsIIDQgnIndiCamsBright =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsBright };

static const TAknsItemID KAknsIIDQgnIndiCamsBurst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsBurst };

static const TAknsItemID KAknsIIDQgnIndiCamsContrast =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsContrast };

static const TAknsItemID KAknsIIDQgnIndiCamsZoomBgMax =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsZoomBgMax };

static const TAknsItemID KAknsIIDQgnIndiCamsZoomBgMin =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsZoomBgMin };

static const TAknsItemID KAknsIIDQgnIndiChiFindCangjie =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiChiFindCangjie };

static const TAknsItemID KAknsIIDQgnIndiConnectionOnRoamAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiConnectionOnRoamAdd };

static const TAknsItemID KAknsIIDQgnIndiDrmManyMoAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDrmManyMoAdd };

static const TAknsItemID KAknsIIDQgnIndiDycDiacreetAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiDycDiacreetAdd };

static const TAknsItemID KAknsIIDQgnIndiEnter =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiEnter };

static const TAknsItemID KAknsIIDQgnIndiFindGlassAdvanced =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFindGlassAdvanced };

static const TAknsItemID KAknsIIDQgnIndiFindNone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFindNone };

static const TAknsItemID KAknsIIDQgnIndiImportantAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiImportantAdd };

static const TAknsItemID KAknsIIDQgnIndiImMessage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiImMessage };

static const TAknsItemID KAknsIIDQgnIndiLocPolicyAcceptAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiLocPolicyAcceptAdd };

static const TAknsItemID KAknsIIDQgnIndiLocPolicyAskAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiLocPolicyAskAdd };

static const TAknsItemID KAknsIIDQgnIndiMmsEarpiece =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsEarpiece };

static const TAknsItemID KAknsIIDQgnIndiMmsNoncorm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsNoncorm };

static const TAknsItemID KAknsIIDQgnIndiMmsStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsStop };

static const TAknsItemID KAknsIIDQgnIndiSettProtectedInvAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSettProtectedInvAdd };

static const TAknsItemID KAknsIIDQgnIndiSignalStrengthLsc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalStrengthLsc };

static const TAknsItemID KAknsIIDQgnIndiSignalWcdmaSuspended =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalWcdmaSuspended };

static const TAknsItemID KAknsIIDQgnIndiTextLeft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiTextLeft };

static const TAknsItemID KAknsIIDQgnIndiTextRight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiTextRight };

static const TAknsItemID KAknsIIDQgnIndiWmlImageNoteShown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlImageNoteShown };

static const TAknsItemID KAknsIIDQgnIndiWmlImageNotShown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlImageNotShown };

static const TAknsItemID KAknsIIDQgnPropBildNavigationSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBildNavigationSub };

static const TAknsItemID KAknsIIDQgnPropBtDevicesTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBtDevicesTab2 };

static const TAknsItemID KAknsIIDQgnPropGroupVip =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropGroupVip };

static const TAknsItemID KAknsIIDQgnPropLogCallsTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallsTab3 };

static const TAknsItemID KAknsIIDQgnPropLogTimersTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogTimersTab3 };

static const TAknsItemID KAknsIIDQgnPropMceDrafts =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceDrafts };

static const TAknsItemID KAknsIIDQgnPropMceDraftsNew =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceDraftsNew };

static const TAknsItemID KAknsIIDQgnPropMceMailFetReadDel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMailFetReadDel };

static const TAknsItemID KAknsIIDQgnPropMceSmsTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceSmsTab4 };

static const TAknsItemID KAknsIIDQgnPropModeRing =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropModeRing };

static const TAknsItemID KAknsIIDQgnPropPbContactsTab1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPbContactsTab1 };

static const TAknsItemID KAknsIIDQgnPropPbContactsTab2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPbContactsTab2 };

static const TAknsItemID KAknsIIDQgnPropPinbExclamationId =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbExclamationId };

static const TAknsItemID KAknsIIDQgnPropPlsnActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPlsnActive };

static const TAknsItemID KAknsIIDQgnPropSetButton =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSetButton };

static const TAknsItemID KAknsIIDQgnPropVoiceMidi =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVoiceMidi };

static const TAknsItemID KAknsIIDQgnPropVoiceWav =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVoiceWav };

static const TAknsItemID KAknsIIDQgnPropVpnAccessPoint =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropVpnAccessPoint };

static const TAknsItemID KAknsIIDQgnPropWmlUssd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWmlUssd };

static const TAknsItemID KAknsIIDQgnStatChiCangjie =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatChiCangjie };

static const TAknsItemID KAknsIIDQgnStatConnectionOnUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatConnectionOnUni };

static const TAknsItemID KAknsIIDQgnStatCsd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCsd };

static const TAknsItemID KAknsIIDQgnStatCsdUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCsdUni };

static const TAknsItemID KAknsIIDQgnStatDsign =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatDsign };

static const TAknsItemID KAknsIIDQgnStatHscsd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatHscsd };

static const TAknsItemID KAknsIIDQgnStatHscsdUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatHscsdUni };

static const TAknsItemID KAknsIIDQgnStatMissedCalls =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMissedCalls };

static const TAknsItemID KAknsIIDQgnStatNoCalls =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatNoCalls };

static const TAknsItemID KAknsIIDQgnStatNoCallsUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatNoCallsUni };

static const TAknsItemID KAknsIIDQgnIndiWlanSecureNetworkAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWlanSecureNetworkAdd };

static const TAknsItemID KAknsIIDQgnIndiWlanSignalGoodAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWlanSignalGoodAdd };

static const TAknsItemID KAknsIIDQgnIndiWlanSignalLowAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWlanSignalLowAdd };

static const TAknsItemID KAknsIIDQgnIndiWlanSignalMedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWlanSignalMedAdd };

static const TAknsItemID KAknsIIDQgnPropCmonConnActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCmonConnActive };

static const TAknsItemID KAknsIIDQgnPropCmonWlanAvail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCmonWlanAvail };

static const TAknsItemID KAknsIIDQgnPropCmonWlanConn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropCmonWlanConn };

static const TAknsItemID KAknsIIDQgnPropWlanBearer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWlanBearer };

static const TAknsItemID KAknsIIDQgnPropWlanEasy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropWlanEasy };

static const TAknsItemID KAknsIIDQgnStatWlanActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatWlanActive };

static const TAknsItemID KAknsIIDQgnStatWlanActiveSecure =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatWlanActiveSecure };

static const TAknsItemID KAknsIIDQgnStatWlanActiveSecureUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatWlanActiveSecureUni };

static const TAknsItemID KAknsIIDQgnStatWlanActiveUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatWlanActiveUni };

static const TAknsItemID KAknsIIDQgnStatWlanAvail =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatWlanAvail };

static const TAknsItemID KAknsIIDQgnStatWlanAvailUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatWlanAvailUni };

static const TAknsItemID KAknsIIDQgnGrafMmsAudioCorrupted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsAudioCorrupted };

static const TAknsItemID KAknsIIDQgnGrafMmsAudioDrm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsAudioDrm };

static const TAknsItemID KAknsIIDQgnGrafMmsImageCorrupted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsImageCorrupted };

static const TAknsItemID KAknsIIDQgnGrafMmsImageDrm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsImageDrm };

static const TAknsItemID KAknsIIDQgnGrafMmsVideoCorrupted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsVideoCorrupted };

static const TAknsItemID KAknsIIDQgnGrafMmsVideoDrm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsVideoDrm };

static const TAknsItemID KAknsIIDQgnMenuEmpty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuEmpty };

static const TAknsItemID KAknsIIDQgnPropImFriendTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImFriendTab3 };

static const TAknsItemID KAknsIIDQgnPropImIboxTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImIboxTab3 };

static const TAknsItemID KAknsIIDQgnPropImListTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImListTab3 };

static const TAknsItemID KAknsIIDQgnPropImSavedChatTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropImSavedChatTab3 };

static const TAknsItemID KAknsIIDQgnIndiSignalEgprsAttach =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalEgprsAttach };

static const TAknsItemID KAknsIIDQgnIndiSignalEgprsContext =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalEgprsContext };

static const TAknsItemID KAknsIIDQgnIndiSignalEgprsMultipdp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalEgprsMultipdp };

static const TAknsItemID KAknsIIDQgnIndiSignalEgprsSuspended =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSignalEgprsSuspended };

static const TAknsItemID KAknsIIDQgnStatPocOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatPocOn };

static const TAknsItemID KAknsIIDQgnMenuGroupConnectLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupConnectLst };

static const TAknsItemID KAknsIIDQgnMenuGroupConnect =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupConnect };

static const TAknsItemID KAknsIIDQgnMenuGroupExtrasLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupExtrasLst };

static const TAknsItemID KAknsIIDQgnMenuGroupExtras =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupExtras };

static const TAknsItemID KAknsIIDQgnMenuGroupInstallLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupInstallLst };

static const TAknsItemID KAknsIIDQgnMenuGroupInstall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupInstall };

static const TAknsItemID KAknsIIDQgnMenuGroupOrganiserLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupOrganiserLst };

static const TAknsItemID KAknsIIDQgnMenuGroupOrganiser =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupOrganiser };

static const TAknsItemID KAknsIIDQgnMenuGroupToolsLst =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupToolsLst };

static const TAknsItemID KAknsIIDQgnMenuGroupTools =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupTools };

static const TAknsItemID KAknsIIDQgnIndiCamsZoomMax =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsZoomMax };

static const TAknsItemID KAknsIIDQgnIndiCamsZoomMin =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCamsZoomMin };

static const TAknsItemID KAknsIIDQgnIndiAiMusicPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiMusicPause };

static const TAknsItemID KAknsIIDQgnIndiAiMusicPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiMusicPlay };

static const TAknsItemID KAknsIIDQgnIndiAiNtDef =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtDef };

static const TAknsItemID KAknsIIDQgnIndiAlarmInactiveAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAlarmInactiveAdd };

static const TAknsItemID KAknsIIDQgnIndiCdrTodo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCdrTodo };

static const TAknsItemID KAknsIIDQgnIndiViewerPanningDown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiViewerPanningDown };

static const TAknsItemID KAknsIIDQgnIndiViewerPanningLeft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiViewerPanningLeft };

static const TAknsItemID KAknsIIDQgnIndiViewerPanningRight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiViewerPanningRight };

static const TAknsItemID KAknsIIDQgnIndiViewerPanningUp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiViewerPanningUp };

static const TAknsItemID KAknsIIDQgnIndiViewerPointer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiViewerPointer };

static const TAknsItemID KAknsIIDQgnIndiViewerPointerHand =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiViewerPointerHand };

static const TAknsItemID KAknsIIDQgnPropLogCallsMostdialTab4 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogCallsMostdialTab4 };

static const TAknsItemID KAknsIIDQgnPropLogMostdSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLogMostdSub };

static const TAknsItemID KAknsIIDQgnAreaMainMup =
    { EAknsMajorGeneric, EAknsMinorGenericQgnAreaMainMup };

static const TAknsItemID KAknsIIDQgnGrafBlid =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBlid };

static const TAknsItemID KAknsIIDQgnGrafBlidDestNear =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBlidDestNear };

static const TAknsItemID KAknsIIDQgnGrafBlidDir =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBlidDir };

static const TAknsItemID KAknsIIDQgnGrafMupBarProgress =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMupBarProgress };

static const TAknsItemID KAknsIIDQgnGrafMupBarProgress2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMupBarProgress2 };

static const TAknsItemID KAknsIIDQgnGrafMupVisualizerImage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMupVisualizerImage };

static const TAknsItemID KAknsIIDQgnGrafMupVisualizerMaskSoft =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMupVisualizerMaskSoft };

static const TAknsItemID KAknsIIDQgnIndiAppOpen =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAppOpen };

static const TAknsItemID KAknsIIDQgnIndiCallVoipActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipActive };

static const TAknsItemID KAknsIIDQgnIndiCallVoipActive2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipActive2 };

static const TAknsItemID KAknsIIDQgnIndiCallVoipActiveConf =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipActiveConf };

static const TAknsItemID KAknsIIDQgnIndiCallVoipCallstaDisconn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipCallstaDisconn };

static const TAknsItemID KAknsIIDQgnIndiCallVoipDisconn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipDisconn };

static const TAknsItemID KAknsIIDQgnIndiCallVoipDisconnConf =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipDisconnConf };

static const TAknsItemID KAknsIIDQgnIndiCallVoipHeld =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipHeld };

static const TAknsItemID KAknsIIDQgnIndiCallVoipHeldConf =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipHeldConf };

static const TAknsItemID KAknsIIDQgnIndiCallVoipWaiting1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipWaiting1 };

static const TAknsItemID KAknsIIDQgnIndiCallVoipWaiting2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiCallVoipWaiting2 };

static const TAknsItemID KAknsIIDQgnIndiMupButtonLink =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonLink };

static const TAknsItemID KAknsIIDQgnIndiMupButtonLinkDimmed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonLinkDimmed };

static const TAknsItemID KAknsIIDQgnIndiMupButtonLinkHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonLinkHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonLinkInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonLinkInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonMc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonMc };

static const TAknsItemID KAknsIIDQgnIndiMupButtonMcHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonMcHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonMcInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonMcInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonNext =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonNext };

static const TAknsItemID KAknsIIDQgnIndiMupButtonNextHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonNextHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonNextInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonNextInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPause };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPauseHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPauseHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPauseInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPauseInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlay };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlaylist =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlaylist };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlaylistDimmed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlaylistDimmed };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlaylistHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlaylistHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlaylistInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlaylistInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlayHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlayHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPlayInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPlayInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPrev =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPrev };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPrevHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPrevHl };

static const TAknsItemID KAknsIIDQgnIndiMupButtonPrevInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonPrevInact };

static const TAknsItemID KAknsIIDQgnIndiMupButtonStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonStop };

static const TAknsItemID KAknsIIDQgnIndiMupButtonStopHl =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonStopHl };

static const TAknsItemID KAknsIIDQgnIndiMupEq =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupEq };

static const TAknsItemID KAknsIIDQgnIndiMupEqBg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupEqBg };

static const TAknsItemID KAknsIIDQgnIndiMupEqSlider =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupEqSlider };

static const TAknsItemID KAknsIIDQgnIndiMupPause =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupPause };

static const TAknsItemID KAknsIIDQgnIndiMupPauseAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupPauseAdd };

static const TAknsItemID KAknsIIDQgnIndiMupPlay =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupPlay };

static const TAknsItemID KAknsIIDQgnIndiMupPlayAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupPlayAdd };

static const TAknsItemID KAknsIIDQgnIndiMupSpeaker =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupSpeaker };

static const TAknsItemID KAknsIIDQgnIndiMupSpeakerMuted =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupSpeakerMuted };

static const TAknsItemID KAknsIIDQgnIndiMupStop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupStop };

static const TAknsItemID KAknsIIDQgnIndiMupStopAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupStopAdd };

static const TAknsItemID KAknsIIDQgnIndiMupVolumeSlider =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupVolumeSlider };

static const TAknsItemID KAknsIIDQgnIndiMupVolumeSliderBg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupVolumeSliderBg };

static const TAknsItemID KAknsIIDQgnMenuGroupMedia =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuGroupMedia };

static const TAknsItemID KAknsIIDQgnMenuVoip =
    { EAknsMajorGeneric, EAknsMinorGenericQgnMenuVoip };

static const TAknsItemID KAknsIIDQgnNoteAlarmTodo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnNoteAlarmTodo };

static const TAknsItemID KAknsIIDQgnPropBlidTripSub =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidTripSub };

static const TAknsItemID KAknsIIDQgnPropBlidTripTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidTripTab3 };

static const TAknsItemID KAknsIIDQgnPropBlidWaypoint =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropBlidWaypoint };

static const TAknsItemID KAknsIIDQgnPropLinkEmbd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropLinkEmbd };

static const TAknsItemID KAknsIIDQgnPropMupAlbum =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupAlbum };

static const TAknsItemID KAknsIIDQgnPropMupArtist =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupArtist };

static const TAknsItemID KAknsIIDQgnPropMupAudio =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupAudio };

static const TAknsItemID KAknsIIDQgnPropMupComposer =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupComposer };

static const TAknsItemID KAknsIIDQgnPropMupGenre =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupGenre };

static const TAknsItemID KAknsIIDQgnPropMupPlaylist =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupPlaylist };

static const TAknsItemID KAknsIIDQgnPropMupSongs =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupSongs };

static const TAknsItemID KAknsIIDQgnPropNrtypVoip =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypVoip };

static const TAknsItemID KAknsIIDQgnPropNrtypVoipDiv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropNrtypVoipDiv };

static const TAknsItemID KAknsIIDQgnPropSubCurrent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSubCurrent };

static const TAknsItemID KAknsIIDQgnPropSubMarked =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropSubMarked };

static const TAknsItemID KAknsIIDQgnStatPocOnUni =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatPocOnUni };

static const TAknsItemID KAknsIIDQgnStatVietCaseCapital =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVietCaseCapital };

static const TAknsItemID KAknsIIDQgnStatVietCaseSmall =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVietCaseSmall };

static const TAknsItemID KAknsIIDQgnStatVietCaseText =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatVietCaseText };

static const TAknsItemID KAknsIIDQgnIndiSyncSetAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiSyncSetAdd };

static const TAknsItemID KAknsIIDQgnPropMceMms =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMceMms };

static const TAknsItemID KAknsIIDQgnPropUnknown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropUnknown };

static const TAknsItemID KAknsIIDQgnStatMsgNumber =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMsgNumber };

static const TAknsItemID KAknsIIDQgnStatMsgRoom =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatMsgRoom };

static const TAknsItemID KAknsIIDQgnStatSilent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatSilent };

static const TAknsItemID KAknsIIDQgnGrafBgGray =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafBgGray };

static const TAknsItemID KAknsIIDQgnIndiAiNt3g =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNt3g };

static const TAknsItemID KAknsIIDQgnIndiAiNtAudvideo =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtAudvideo };

static const TAknsItemID KAknsIIDQgnIndiAiNtChat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtChat };

static const TAknsItemID KAknsIIDQgnIndiAiNtDirectio =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtDirectio };

static const TAknsItemID KAknsIIDQgnIndiAiNtDownload =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtDownload };

static const TAknsItemID KAknsIIDQgnIndiAiNtEconomy =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtEconomy };

static const TAknsItemID KAknsIIDQgnIndiAiNtErotic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtErotic };

static const TAknsItemID KAknsIIDQgnIndiAiNtEvent =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtEvent };

static const TAknsItemID KAknsIIDQgnIndiAiNtFilm =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFilm };

static const TAknsItemID KAknsIIDQgnIndiAiNtFinanceu =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFinanceu };

static const TAknsItemID KAknsIIDQgnIndiAiNtFinancuk =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFinancuk };

static const TAknsItemID KAknsIIDQgnIndiAiNtFind =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFind };

static const TAknsItemID KAknsIIDQgnIndiAiNtFlirt =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFlirt };

static const TAknsItemID KAknsIIDQgnIndiAiNtFormula1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFormula1 };

static const TAknsItemID KAknsIIDQgnIndiAiNtFun =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtFun };

static const TAknsItemID KAknsIIDQgnIndiAiNtGames =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtGames };

static const TAknsItemID KAknsIIDQgnIndiAiNtHoroscop =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtHoroscop };

static const TAknsItemID KAknsIIDQgnIndiAiNtLottery =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtLottery };

static const TAknsItemID KAknsIIDQgnIndiAiNtMessage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtMessage };

static const TAknsItemID KAknsIIDQgnIndiAiNtMusic =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtMusic };

static const TAknsItemID KAknsIIDQgnIndiAiNtNewidea =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtNewidea };

static const TAknsItemID KAknsIIDQgnIndiAiNtNews =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtNews };

static const TAknsItemID KAknsIIDQgnIndiAiNtNewsweat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtNewsweat };

static const TAknsItemID KAknsIIDQgnIndiAiNtParty =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtParty };

static const TAknsItemID KAknsIIDQgnIndiAiNtShopping =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtShopping };

static const TAknsItemID KAknsIIDQgnIndiAiNtSoccer1 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtSoccer1 };

static const TAknsItemID KAknsIIDQgnIndiAiNtSoccer2 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtSoccer2 };

static const TAknsItemID KAknsIIDQgnIndiAiNtSoccerwc =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtSoccerwc };

static const TAknsItemID KAknsIIDQgnIndiAiNtStar =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtStar };

static const TAknsItemID KAknsIIDQgnIndiAiNtTopten =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtTopten };

static const TAknsItemID KAknsIIDQgnIndiAiNtTravel =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtTravel };

static const TAknsItemID KAknsIIDQgnIndiAiNtTv =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtTv };

static const TAknsItemID KAknsIIDQgnIndiAiNtVodafone =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtVodafone };

static const TAknsItemID KAknsIIDQgnIndiAiNtWeather =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtWeather };

static const TAknsItemID KAknsIIDQgnIndiAiNtWinterol =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtWinterol };

static const TAknsItemID KAknsIIDQgnIndiAiNtXmas =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiAiNtXmas };

static const TAknsItemID KAknsIIDQgnPropPinbEight =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropPinbEight };

static const TAknsItemID KAknsIIDQgnGrafMmsPostcardBack =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsPostcardBack };

static const TAknsItemID KAknsIIDQgnGrafMmsPostcardFront =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsPostcardFront };

static const TAknsItemID KAknsIIDQgnGrafMmsPostcardInsertImageBg =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsPostcardInsertImageBg };

static const TAknsItemID KAknsIIDQgnIndiFileCorruptedAdd =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiFileCorruptedAdd };

static const TAknsItemID KAknsIIDQgnIndiMmsPostcardDown =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsPostcardDown };

static const TAknsItemID KAknsIIDQgnIndiMmsPostcardImage =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsPostcardImage };

static const TAknsItemID KAknsIIDQgnIndiMmsPostcardStamp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsPostcardStamp };

static const TAknsItemID KAknsIIDQgnIndiMmsPostcardText =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsPostcardText };

static const TAknsItemID KAknsIIDQgnIndiMmsPostcardUp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMmsPostcardUp };

static const TAknsItemID KAknsIIDQgnIndiMupButtonMcDimmed =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonMcDimmed };

static const TAknsItemID KAknsIIDQgnIndiMupButtonStopInact =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupButtonStopInact };

static const TAknsItemID KAknsIIDQgnIndiMupRandom =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupRandom };

static const TAknsItemID KAknsIIDQgnIndiMupRepeat =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiMupRepeat };

static const TAknsItemID KAknsIIDQgnIndiWmlWindows =
    { EAknsMajorGeneric, EAknsMinorGenericQgnIndiWmlWindows };

static const TAknsItemID KAknsIIDQgnPropFileVideoMp =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropFileVideoMp };

static const TAknsItemID KAknsIIDQgnPropMcePostcard =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMcePostcard };

static const TAknsItemID KAknsIIDQgnPropMmsPostcardAddressActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsPostcardAddressActive };

static const TAknsItemID KAknsIIDQgnPropMmsPostcardAddressInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsPostcardAddressInactive };

static const TAknsItemID KAknsIIDQgnPropMmsPostcardGreetingActive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsPostcardGreetingActive };

static const TAknsItemID KAknsIIDQgnPropMmsPostcardGreetingInactive =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMmsPostcardGreetingInactive };

static const TAknsItemID KAknsIIDQgnPropDrmExpForbidSuper =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmExpForbidSuper };

static const TAknsItemID KAknsIIDQgnPropDrmRemovedLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRemovedLarge };

static const TAknsItemID KAknsIIDQgnPropDrmRemovedTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRemovedTab3 };

static const TAknsItemID KAknsIIDQgnPropDrmRightsExpSuper =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsExpSuper };

static const TAknsItemID KAknsIIDQgnPropDrmRightsGroup =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsGroup };

static const TAknsItemID KAknsIIDQgnPropDrmRightsInvalidTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsInvalidTab3 };

static const TAknsItemID KAknsIIDQgnPropDrmRightsValidSuper =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsValidSuper };

static const TAknsItemID KAknsIIDQgnPropDrmRightsValidTab3 =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmRightsValidTab3 };

static const TAknsItemID KAknsIIDQgnPropDrmSendForbidSuper =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmSendForbidSuper };

static const TAknsItemID KAknsIIDQgnPropDrmValidLarge =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropDrmValidLarge };

static const TAknsItemID KAknsIIDQgnPropMupPlaylistAuto =
    { EAknsMajorGeneric, EAknsMinorGenericQgnPropMupPlaylistAuto };

static const TAknsItemID KAknsIIDQgnStatCarkit =
    { EAknsMajorGeneric, EAknsMinorGenericQgnStatCarkit };

static const TAknsItemID KAknsIIDQgnGrafMmsVolumeOff =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsVolumeOff };

static const TAknsItemID KAknsIIDQgnGrafMmsVolumeOn =
    { EAknsMajorGeneric, EAknsMinorGenericQgnGrafMmsVolumeOn };

// SCMMARKER_INSERTIONPOINT

// SCCMARKER_END

// ============================================================================
// Other constants
// ============================================================================

/**
* UID that identifies active skin instance when fetched using
* <code>CCoeEnv::Static</code>.
*
* @since 2.0
*/
const TUid KAknsSkinInstanceTls         = {0x10005a27};

/**
* UID that identifies AppUi skin parameters when fetched using 
* <code>CCoeEnv::Static</code>.
*
* @since 2.0
*/
const TUid KAknsAppUiParametersTls      = {0x101F84CD};

/**
* Skin change event UID value.
*
* @since 2.0
*/                                            
const TInt KUidValueAknsSkinChangeEvent = 0x10005A30;

/**
* Skin change message value.
*
* @since 2.0
*/
const TInt KAknsMessageSkinChange       = 0x10005A31;

/**
* Image table indices for frame elements.
*
* @since 2.0
*/
enum TAknsFrameElementIndex
    {
    EAknsFrameIndexTl                   = 0,
    EAknsFrameIndexTr                   = 1,
    EAknsFrameIndexBl                   = 2,
    EAknsFrameIndexBr                   = 3,
    EAknsFrameIndexT                    = 4,
    EAknsFrameIndexB                    = 5,
    EAknsFrameIndexL                    = 6,
    EAknsFrameIndexR                    = 7,
    EAknsFrameIndexCenter               = 8,
    EAknsFrameElementsN                 = 9
    };

// ============================================================================
// Obsolete constants
// ============================================================================

// If defined, does not define obsolete constants.
// @todo Remove when Avkon changes are in place!
#ifndef AKNS_EXCLUDE_OBSOLETE_CONSTANTS

/**
* Obsolete, do not use!
*/
enum TAknsCommonIIDMajorValue
    {
    EAknsIIDMajorNone           = -1,
    EAknsIIDMajorDefault        = 0,
    EAknsIIDMajorAppIcon        = EAknsMajorAppIcon,
    EAknsIIDMajorAppIconBmpLst  = EAknsMajorAppIconBmpLst,
    EAknsIIDMajorAppIconBmpCtx  = EAknsMajorAppIconBmpCxt,
    EAknsIIDMajorSkinBmp        = EAknsMajorSkin,
    EAknsIIDMajorEikCtlBmp      = 0x1000489c,   // EikCtl UID
    EAknsIIDMajorAvkonBmp       = EAknsMajorAvkon
    };

/**
* Obsolete, do not use!
*/
enum TAknsCommonIIDMinorValue
    {
    EAknsIIDMinorNone           = EAknsMinorNone,
    EAknsIIDMinorDefault        = EAknsMinorDefault
    };

/**
* Obsolete, do not use!
*/
enum TAknsSkinBmpControlPaneColorTableIndex
    {
    EAknsCTISkinBmpControlPane_CbaText      = 0,
    EAknsCTISkinBmpControlPane_ScindFirst   = 0,
    EAknsCTISkinBmpControlPane_ScindLast    = 15
    };

/**
* Obsolete, do not use!
*/
enum TAknsSkinBmpIIDMinorValue
    {
    EAknsIIDMinorSkinBmpControlPane                 = EAknsMinorQsnBgAreaControl,
    EAknsIIDMinorSkinBmpControlPaneColorTable       = EAknsMinorNone,
    EAknsIIDMinorSkinBmpIdleWallpaperDefault        = EAknsMinorQsnBgAreaMainIdle,
    EAknsIIDMinorSkinBmpPinboardWallpaperDefault    = EAknsMinorNone,
    EAknsIIDMinorSkinBmpMainPaneUsual               = EAknsMinorQsnBgAreaMain,
    EAknsIIDMinorSkinBmpListPaneNarrowA             = EAknsMinorQsnBgColumnA,
    EAknsIIDMinorSkinBmpListPaneWideA               = EAknsMinorQsnBgColumnAB,
    EAknsIIDMinorSkinBmpNoteBgDefault               = EAknsMinorNone,

    // R_AVKON_STATUS_PANE_LAYOUT_USUAL
    EAknsIIDMinorSkinBmpStatusPaneUsual             = EAknsMinorQsnBgAreaStatus,    

    // R_AVKON_STATUS_PANE_LAYOUT_IDLE
    EAknsIIDMinorSkinBmpStatusPaneIdle              = EAknsMinorQsnBgAreaStatus
    };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpControlPane =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpControlPane };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpControlPaneColorTable =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpControlPaneColorTable };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpIdleWallpaperDefault =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpIdleWallpaperDefault };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpPinboardWallpaperDefault =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpPinboardWallpaperDefault };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpMainPaneUsual =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpMainPaneUsual };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpListPaneNarrowA =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpListPaneNarrowA };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpListPaneWideA =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpListPaneWideA };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpNoteBgDefault =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpNoteBgDefault };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpStatusPaneUsual =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpStatusPaneUsual };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDSkinBmpStatusPaneIdle =
    { EAknsIIDMajorSkinBmp, EAknsIIDMinorSkinBmpStatusPaneIdle };

/**
* Obsolete, do not use!
*/
enum TAknsAvkonBmpIIDMinorValue
    {
    EAknsIIDMinorAvkonBmpTab21            = 0,    
    EAknsIIDMinorAvkonBmpTab22            = 2,
    EAknsIIDMinorAvkonBmpTab31            = 4,
    EAknsIIDMinorAvkonBmpTab32            = 6,
    EAknsIIDMinorAvkonBmpTab33            = 8,
    EAknsIIDMinorAvkonBmpTab41            = 10,
    EAknsIIDMinorAvkonBmpTab42            = 12,
    EAknsIIDMinorAvkonBmpTab43            = 14,
    EAknsIIDMinorAvkonBmpTab44            = 16,
    EAknsIIDMinorAvkonBmpTabLong21        = 18,
    EAknsIIDMinorAvkonBmpTabLong22        = 20,
    EAknsIIDMinorAvkonBmpTabLong31        = 22,
    EAknsIIDMinorAvkonBmpTabLong32        = 24,
    EAknsIIDMinorAvkonBmpTabLong33        = 26
    };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab21 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab21 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab22 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab22 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab31 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab31 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab32 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab32 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab33 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab33 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab41 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab41 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab42 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab42 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab43 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab43 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTab44 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTab44 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTabLong21 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTabLong21 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTabLong22 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTabLong22 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTabLong31 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTabLong31 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTabLong32 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTabLong32 };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDAvkonBmpTabLong33 =
    { EAknsIIDMajorAvkonBmp, EAknsIIDMinorAvkonBmpTabLong33 };

/**
* Obsolete, do not use!
*/
enum TAknsMinorSkinValueOBSOLETE
    {
    // Digital clock
    EAknsMinorQsnCpClockDigital0        = 0x4010,
    EAknsMinorQsnCpClockDigital1        = 0x4011,
    EAknsMinorQsnCpClockDigital2        = 0x4012,
    EAknsMinorQsnCpClockDigital3        = 0x4013,
    EAknsMinorQsnCpClockDigital4        = 0x4014,
    EAknsMinorQsnCpClockDigital5        = 0x4015,
    EAknsMinorQsnCpClockDigital6        = 0x4016,
    EAknsMinorQsnCpClockDigital7        = 0x4017,
    EAknsMinorQsnCpClockDigital8        = 0x4018,
    EAknsMinorQsnCpClockDigital9        = 0x4019,
    EAknsMinorQsnCpClockDigitalPeriod   = 0x401a,
    EAknsMinorQsnCpClockDigital0MaskSoft= 0x4020,
    EAknsMinorQsnCpClockDigital1MaskSoft= 0x4021,
    EAknsMinorQsnCpClockDigital2MaskSoft= 0x4022,
    EAknsMinorQsnCpClockDigital3MaskSoft= 0x4023,
    EAknsMinorQsnCpClockDigital4MaskSoft= 0x4024,
    EAknsMinorQsnCpClockDigital5MaskSoft= 0x4025,
    EAknsMinorQsnCpClockDigital6MaskSoft= 0x4026,
    EAknsMinorQsnCpClockDigital7MaskSoft= 0x4027,
    EAknsMinorQsnCpClockDigital8MaskSoft= 0x4028,
    EAknsMinorQsnCpClockDigital9MaskSoft= 0x4029,
    EAknsMinorQsnCpClockDigitalPeriodMaskSoft = 0x402a
    };

/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital0 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital0 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital1 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital1 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital2 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital2 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital3 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital3 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital4 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital4 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital5 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital5 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital6 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital6 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital7 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital7 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital8 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital8 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital9 =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital9 };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigitalPeriod =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalPeriod };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital0MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital0MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital1MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital1MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital2MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital2MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital3MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital3MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital4MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital4MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital5MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital5MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital6MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital6MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital7MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital7MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital8MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital8MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigital9MaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigital9MaskSoft };
/**
* Obsolete, do not use!
*/
static const TAknsItemID KAknsIIDQsnCpClockDigitalPeriodMaskSoft =
    { EAknsMajorSkin, EAknsMinorQsnCpClockDigitalPeriodMaskSoft };

// If defined, does not define obsolete constants.
// @todo Remove when Avkon changes are in place!
#endif // AKNS_EXCLUDE_OBSOLETE_CONSTANTS

#endif // AKNSCONSTANTS_H

// End of File
