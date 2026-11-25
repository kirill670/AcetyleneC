/** @file skin.h */
/*
* ==============================================================================
*  Name        : skin.h
*  Part of     : CUIKLAF
*  Interface   : Skin API
*  Description : Base class for skin framework.
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


#ifndef SKIN_H
#define SKIN_H

// INCLUDES
#include <e32base.h>
#include <skinuid.h>
#include <gdi.h>
#include <w32std.h>
#include <CknLogicalFont.h>
#include <apgicnfl.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class CGulIcon;
class CCoeControl;
class CEikToolBar;
class RApaLsSession;

/**

When the skin is changed, the skin loader (or skin server) informs all controls
of the skin change event via <code>HandleResourceChange()</code>.

*/

// CONSTANTS
/** resource change event */
const TInt KUidSkinResourceChangeEvent=0x101F57EB;
/** resource change event layout */
const TInt KUidSkinResourceChangeEventLayout=0x101F87AA;

/// ellipsis character; used by ClipToFit()
/**
 * clip end character. This is an ellipsis character used by
 * <code>ClipToFit()</code>
 */
const TUint KCknSkinClipEndChar=0x2026;

/**
 * The enumeration <code>TCknSkinPanic</code> provides the skin manager panic
 * codes.
 */
enum TCknSkinPanic
    {
    /** the array is null */
    ECknSkinPanicArrayNull,
    /** multiple allocation  */
    ECknSkinPanicMultipleAlloc,
    /** the list size is mismatched */
    ECknSkinPanicListSizeMismatch,
    /** invalid UID */
    ECknSkinPanicInvalidUid,
    /** the icon ID could not be found */
    ECknSkinPanicInvalidTSkinIconId,
    /** invalid .mbm file parameters  */
    ECknSkinPanicInvalidMbmFileParams,
    /** invalid array index */
    ECknSkinPanicInvalidArrayIndex,
    /** invalid resource file */
    ECknSkinPanicInvalidResourceFile,
    /** invalid color range */
    ECknSkinPanicInvalidColorRange,
    /** invalid sound info */
    ECknSkinPanicInvalidSoundInfo,
    /** the logical color is not found */
    ECknSkinPanicLogicalColorNotFound,
    /** the bitmap section is not found in the configuration file */
    ECknSkinPanicBitmapSectionNotFound,
    /** the constant section is not found in the configuration file */
    ECknSkinPanicConstantSectionNotFound,
    /** the resource section is not found in the configuration file */
    ECknSkinPanicResourceSectionNotFound,
    /** the color section is not found in the configuration file */
    ECknSkinPanicColorSectionNotFound,
    /** the sound section is not found in the configuration file */
    ECknSkinPanicSoundSectionNotFound,
    /** the AppView type is not recognized */
    ECknSkinPanicAppViewUnrecognised,
    /** invalid number region values */
    ECknSkinPanicInvalidNumRegionValues,
    /** the system font parameters are invalid */
    ECknSkinPanicSystemFontParamsInvalid,
    /** the system font section is not found in the configuration file */
    ECknSkinPanicSystemFontsSectionNotFound,
    /** invalid skin configuration parser */
    ECknSkinPanicInvalidSkinConfigParser,
    /** no mask is available */
    ECknSkinPanicNoMaskAvailable,
	/** fct arg invalid */
	ECknSkinPanicInvalidArgument
    };

/**
 * The enumeration <code>TSkinAppView</code> provides the application view
 * bitmap types.
 */

enum TSkinAppView
    {
    /** the AppView has a CBA and no toolband */
    ESkinAppViewWithCbaNoToolband,
    /** the AppView has no CBA and no toolband */
    ESkinAppViewNoCbaNoToolband,
    /** the AppView has CBA and toolband */
    ESkinAppViewWithCbaWithToolband,
    /** the AppView has no CBA and has toolband */
    ESkinAppViewNoCbaWithToolband,
    /** the AppView has no CBA and no narrow toolband. Not supported on Series 90 */
    ESkinAppViewNoCbaNoToolbandNarrow,
    /** the AppView has no CBA and no wide toolband. Not supported on Series 90 */
    ESkinAppViewNoCbaNoToolbandWide,
    /** the AppView type is undefined */
    ESkinAppViewUndefined
    };

/**
 * The enumeration <code>TSkinAppViewDrawMode</code> provides the application
 * view bitmap draw modes.
 */
enum TSkinAppViewDrawMode
    {
    /** the AppView draw mode without mask */
    ESkinAppViewDrawModeWithoutMask,
    /** the AppView draw mode with mask */
    ESkinAppViewDrawModeWithMask
    };

/**
 * The enumeration <code>TSkinReloadStatus</code> provides the skin reload
 * status.
 */
enum TSkinReloadStatus
    {
    /** the reload status is successful */
    ESkinReloadStatusSuccess=0,
    /** the reload status is failure */
    ESkinReloadStatusFailure,
    /** the reload request is cancelled. The status is cancelled */
    ESkinReloadStatusCancelled,
    /** the reload status is unknown */
    ESkinReloadStatusUnknown
    };

/**
* The <code>MCknSkinServObserver</code> class is a mixin class that allows all
* the applications and their skin managers to be notified of a change to the
* skin. An application registers an observer with the skin manager and when a
* reload occurs, the skin manager can inform its observers. The observer can
* also be notified of a change to the application view.
*
* @lib ckncore.lib
* @since Series90 1.0
*/
class MCknSkinServObserver
    {
    public:
        /**
        * This method is called after an attempt to reload a skin.
        *
        * @param aReloadStatus Whether the skin reload was successful or not. Either:
        *        <code>ESkinReloadStatusSuccess</code>, if it was successful
        *        <code>ESkinReloadStatusFailure</code>, if it failed
        *        <code>ESkinReloadStatusCancelled</code>, if it was cancelled
        * @remarks Implementation of this method, may use methods that leave
        * @see
        */
        virtual void HandleSkinReloadEventL(TSkinReloadStatus aReloadStatus)=0;

        /**
        * This method is called when the application view bitmap has changed.
        *
        * @remarks
        * @see
        */
        virtual void HandleAppViewChange()=0;
    };

/*
Here is a brief description of the skin framework.

The skin is composed of:

-# bitmap files (*.mbm)
-# sound files (*.wav)
-# resource files (*.rss)
-# font files
-# a configuration file (*.skn)
-# any number of extension, configuration files (*.ske)

The configuration files have two purposes:

-# they tell the system which .mbm, Wav and RSS files to load
-# they tell the system where and how to draw various UI components

MBM paths and Wav paths in the configuration file can be absolute or relative.

Applications may access the skin via the Skin Manager. The skin manager API is
defined by CCknSkinBase, and a reference to the Skin Manager can be gained via:

#include <cknenv.h>

CCknSkinBase& skin=CknEnv().Skin();

(link against ckncore.lib)

Alternatively, if a control is derived from CCknBorderedControl, it can access
the skin manager via the iSkin member variable.

The Skin Manager allows an application to do the following (refer to the
definition of CCknSkinBase for more detail):

-# get a skin bitmap (the Skin Manager owns the bitmap)
-# create a skin bitmap (the application owns the bitmap)
-# get a skin constant defined by the skin configuration file
-# set the application view type (toolbar on/off, command-bar on/off)
-# get the application view bitmap
-# set the shape of a floating popup window
-# set the position of the toolband
-# re-load the skin (used only by the Personalisation app)

The default skin config file is located at the path specified by the skin
redirection file - "z:\system\data\skinconfig\skinpath.txt". skinpath.txt is a
Unicode text file containing the absolute path of the *.skn file and all
other *.ske files.

The skin is changed by:

-# writing a new skin redirection file to
   "c:\system\data\skinconfig\skinpath.txt"
-# calling CCknSkinBase::Reload()

The system may revert back to the default skin, by deleting the
re-direction file on c: and calling CCknSkinBase::Reload() again.

There are a number of MBM files in the "core" skin:

-# SkinScrollbar.mbm
-# SkinProgress.mbm
-# SkinGeneral.mbm
-# SkinFileSystem.mbm
-# SkinWidgets.mbm
-# SkinStatusPane.mbm
-# SkinBorders.mbm
-# SkinMenu.mbm
-# SkinDialogButton.mbm
-# SkinAppView.mbm
-# SkinCommandBar.mbm
-# SkinDialogFrame.mbm
-# SkinViewButton.mbm

Note that applications may add further MBM files via the skin extension
framework (*.ske files).

At boot time, the skin server reads the skin configuration files and loads the
appropriate skin bitmaps (both "core" bitmaps and Extension bitmaps defined by
*.ske files).

When an application requests a skin bitmap, its Skin Manager duplicates the
skin bitmap from a bitmap handle supplied by the skin server. This bitmap
duplication is faster than loading the bitmap which requires the system to
determine whether the bitmap has already been loaded.

There may be a slight delay in duplicating a bitmap because the Skin Manager
duplicates all the bitmaps in the MBM file holding the requested bitmap.

The *.ske files will be loaded at system boot time. The system expects the
*.ske files to be in the same directory as the skin configuration file. The
default skin configuration directory contains the full set of default *.ske
files used by the system.  When loading an alternative skin, if any *.ske files
have not been loaded from the alternative skin config directory then the
missing ones will be loaded from the default skin config directory.

LoadSkinExtensionL allows a default *.ske file
(located in z:\system\data\skinconfig) to be replaced with an alternative
*.ske file without having to reload the entire skin. This alternative *.ske
file should be located in the directory specified by the skin redirection file.

If an alternative *.ske file is to be loaded only when the skin is changed
then LoadSkinExtensionL doesn't need to be called.

LoadSkinExtensionL will search through the skin server's array of MBM
files trying to find UIDs that match the UIDs of the MBM files that
are to be loaded in the alternative *.ske file. If it finds these UIDs then
it will delete these from the skin server's array and load the new ones.
*
*  @lib skin.lib
*  @since Series90 1.0
*/

/**
 * Applications may access the skin via the skin manager. The skin manager API
 * is defined by the class <code>CCknSkinBase</code>, and a reference to the
 * skin manager can be gained using <code>CCknSkinBase& skin=CknEnv().Skin()</code>
 * by including cknenv.h and linking against ckncore.lib.
 * Alternatively, if a control is derived from <code>CCknBorderedControl</code>,
 * it can access the skin manager via the <code>iSkin</code> member variable.
 *
 * @lib skin.lib
 * @since Series90 1.0
 */

class CCknSkinBase : public CBase
    {
    public:

        /**
        * The object destructor.
        */
        virtual ~CCknSkinBase();
    ///

        /**
        * Creates a bitmap and transfers ownership of the bitmap to the caller.
        * The bitmap is created by duplicating a skin manager-owned bitmap.
        *
        * @param aMbmUid The UID of the file containing the bitmap
        * @param aId The index of the bitmap within the file
        * @return the created bitmap
        * @remarks
        * @see
        */
        virtual CFbsBitmap* CreateBitmapL(TUid aMbmUid, TInt aId)=0;

        /**
        * Creates a mask and transfers ownership of the mask to the caller.
        * The mask is created by duplicating a skin manager-owned mask.
        *
        * @param aMbmUid The UID of the file containing the bitmap mask
        * @param aId The index of the bitmap mask within the file
        * @return the created bitmap mask
        * @remarks
        * @see
        */
        virtual CFbsBitmap* CreateMaskL(TUid aMbmUid, TInt aId)=0;

        /**
        * Creates an icon and transfers ownership of the icon to the caller.
        * The icon is created from bitmaps owned by the skin manager.
        *
        * @param aId The ID of the icon
        * @return the created icon
        * @remarks
        * @see TSkinIconId in skinuid.h
        */
        virtual CGulIcon* CreateIconL(TSkinIconId aId)=0;

        /**
        * Returns the currently selected application view bitmap. Ownership of
        * the bitmap is not transferred to the caller.
        *
        * @return a pointer to the application view bitmap
        * @remarks
        * @see
        */
        virtual const CFbsBitmap* GetAppViewBitmapL()=0;

        /**
        * Returns the currently selected application view bitmap mask.
        * Ownership of the bitmap mask is not transferred to the caller.
        *
        * @return a pointer to the application view bitmap mask
        * @remarks
        * @see
        */
        virtual const CFbsBitmap* GetAppViewMaskL()=0;

        /**
        * This method is for heap testing. It duplicates all the skin
        * bitmaps from the skin server in RAM, so that all subsequent calls to
        * <code>GetBitmapL()</code> do not allocate heap memory.
        *
        * @remarks This method allows the client of the skin manager to 
        *          duplicate all the skin bitmaps, to stop subsequent calls to 
        *          <code>BitmapL()</code> from allocating memory. This method 
        *          is used on the emulator only
        * @see
        */
        virtual void DuplicateAllBitmapsL()=0;

        /**
        * Gets a color from the extended colors in the skin.
        *
        * @param aColorUid The UID of the color to find
        * @param aColor On return, this color is set
        * @return <code>KErrNone</code> if the color was found successfully;
        *         <code>KErrNotFound</code> otherwise
        * @remarks Enumeration values for the colors available in the skin
        *          are defined in skincoloruid.h and should be 
        *          used for <code>aColorUid</code>
        * @see TRgb is defined in gdi.h
        */
        virtual TInt GetColor(TUid aColorUid, TRgb& aColor)=0;

        /**
        * Sets a <code>TRegion</code> to a shape according to the region type.
        * 
        *
        * @param aRegionType The type of region
        * @param aControl The control whose shape is to be used
        * @param aTRegion The region to be changed
        * @remarks This method uses the size of the control to set the corner 
        *          region. 
        * @see TRegionType in skinregiontype.h for region type definitions
        */
        virtual void SetCornerRegion(TInt aRegionType,
                                     const CCoeControl& aControl,
                                     TRegion& aTRegion) const=0;

        /**
        * Sets a <code>TRegion</code> to a shape according to the region type.
        * This region can then be used with <code>RWindow.SetShape()</code> to
        * produce windows with rounded corners.
        *
        * @param aRegionType The type of region
        * @param aWindow The window whose shape is to be used
        * @param aTRegion The region to be changed
        * @remarks This method uses the size of the window to set the corner 
        *          region
        * @see TRegionType in skinregiontype.h for region type definitions
        */
        virtual void SetWinCornerRegion(TInt aRegionType,
                                        const RWindowBase& aWindow,
                                        TRegion& aTRegion) const=0;
    /// This function sets the shape of a floating window.

        /**
        * Sets a window to a shape according to the region type.
        *
        * @param aRegionType The type of region
        * @param aWindow The window to be reshaped
        * @remarks
        * @see TRegionType in skinregiontype.h for region type definitions
        */
        virtual void SetWinShape(TInt aRegionType, RWindowBase& aWindow) const=0;

        /**
        * Returns a skin constant.
        *
        * @param aId The ID for the skin constant
        * @return the value of the skin constant
        * @remarks
        * @see TSkinConstId
        */
        virtual TInt Constant(TSkinConstId aId) const=0;

        /**
        * This method is used by the CUIKLAF (Uikon look and feel) 
        * logical border drawing code to
        * draw the application view frame.
        *
        * @param aGc The graphics context to draw with
        * @param aRect The application view frame
        * @remarks  
        * @see
        */
        virtual void DrawAppView(CGraphicsContext& aGc, const TRect& aRect)=0;

        /**
        * Draws the currently selected application view bitmap. <code>aRect</code>
        * must be in the co-ordinate space of <code>aControl</code>.
        *
        * @param aGc The graphics context to draw with
        * @param aRect The frame for the application view bitmap
        * @param aControl The origin of the bitmap is copied from this control
        * @remarks The application view bitmaps are defined in 
        *          <code>TSkinAppView</code>. The application view bitmap
        *          is set using <code>SetAppViewType(TSkinAppView aAppView)</code>
        * @see
        */
        virtual void DrawAppView(CGraphicsContext& aGc,
                                 const TRect& aRect,
                                 const CCoeControl& aControl)=0;

        /**
        * Allows an application to select an application view.
        *
        * @param aAppView The type of application view to be displayed
        * @remarks The application view bitmaps are defined in enumeration
        *          <code>TSkinAppView</code>
        * @see TSkinAppView
        */
        virtual void SetAppViewType(TSkinAppView aAppView)=0;

        /**
        * Allows an application to determine the currently selected
        * application view.
        *
        * @return the type of application view currently displayed
        * @remarks
        * @see
        */
        virtual TSkinAppView AppViewType() const=0;

        /**
        * Returns the application view margins depending on the application
        * view bitmap being used
        *
        * @return the margins
        * @remarks
        * @see TMargins in gdi.h
        */
        virtual TMargins AppViewMargin() const=0;

        /**
        * Sets a patterned brush for drawing view controls with
        * application view bitmap background.
        *
        * @param aGc The graphics context to use for drawing
        * @param aControl The view control
        * @remarks
        * @see
        */
        virtual void SetAppViewBrush(CGraphicsContext& aGc, const CCoeControl& aControl)=0;

        /**
        * Sets the draw mode of the application view bitmap.
        * It allows an application to draw into the non-rectangular areas
        * outside the application client area and inside the AppView frame.
        *
        * @param aValue Either <code>ESkinAppViewDrawModeWithMask</code> or
        *        <code>ESkinAppViewDrawModeWithoutMask</code> to draw the
        *        bitmap with or without its mask
        * @remarks The color magenta (<code>0xff00ff</code>) is used as the 
        *          bitmap mask. Therefore when the 
        *          <code>ESkinAppViewDrawModeWithMask</code> is specified, the 
        *          area around the bitmap is transparent. When 
        *          <code>ESkinAppViewDrawModeWithoutMask</code> is used, the 
        *          area around the bitmap is not transparent and therefore 
        *          covers anything underneath the bitmap
        * @see
        */
        virtual void SetAppViewDrawMode(TSkinAppViewDrawMode aValue)=0;

        /**
        * Initiates a skin reload.
        *
        * @remarks This is a synchronous call and therefore blocks for a period.
        *          It is recommended that the asynchronous 
        *          <code>Reload(TRequestStatus& aStatus)</code> is used in an 
        *          active object instead of this method
        * @see
        */
        virtual void ReloadL()=0;

        /**
        * Initiates a skin reload asynchronously.
        *
        * @param aStatus The request status object. This is set when the search
        *        operation is complete
        * @remarks Typically, used in an active object
        * @see
        */
        virtual void Reload(TRequestStatus& aStatus)=0;

        /**
        * Cancels an asynchronous skin reload.
        *
        * @remarks Typically, used in an active object. This method halts the 
        *          process started by the 
        *          <code>Reload(TRequestStatus& aStatus)</code>
        *          request. The process is only stopped if the skin reload 
        *          request has not been completed
        * @see
        */
        virtual void CancelReload()=0;

        /**
        * Allows an application to register an observer with the skin
        * manager, so that the application can be notified when a skin reload
        * occurs or when the AppView type changes.
        *
        * @param aObserver The skin observer
        * @remarks
        * @see
        */
        virtual void SetObserverL(MCknSkinServObserver* aObserver)=0;

        /**
        * If an embedded application is closed, this method removes one of the
        * observers from the array.
        *
        * @param aObserver The observer to be removed
        * @remarks
        * @see
        */
        virtual void RemoveObserver(MCknSkinServObserver* aObserver)=0;

       /**
        * Gets a system font UID from a logical font category.
        *
        * @param aLogicalFont The font category
        * @param aSystemFont On return, contains the UID of the system font
        * @return <code>KErrNone</code>, if the UID was found successfully;
        *         <code>KErrNotFound</code> otherwise
        * @remarks The logical font category is a list of fonts that are  
        *          mapped on to system fonts. 
        * @see TCknLogicalFont::TFontCategory in cknlogicalfont.h
        */
        virtual TInt GetSystemFontUid(
                              TCknLogicalFont::TFontCategory aLogicalFont,
                              TUid& aSystemFont)=0;


        /**
        * Reduces a given rectangle by the amount required for the skin's
        * margins.
        *
        * @param aOuterRect The rectangle to be reduced
        * @return the modified rectangle
        * @remarks This method is used to get the rectangular coordinates of 
        *          the inside of a given rectangle. For example, to draw text 
        *          inside a control, the height and width of the control is 
        *          passed as a parameter and the area available inside the 
        *          control for drawing the text is returned
        * @see
        */
        virtual TRect FocusInnerRect(const TRect& aOuterRect) const=0;

        /**
        * Maps a logical font to a baseline position.
        *
        * @param aFont The logical font
        * @return the baseline position to draw the font from
        * @remarks The baseline position can be one of three zoom settings -
        *          small, default, and big.
        *          The logical font is mapped to ensure the correct display
        *          of a font when the zoom feature is used
        * @see TCknLogicalFont in cknlogicalfont.h
        */
        virtual TInt GetBaseline(const TCknLogicalFont& aFont)=0;

        /**
        * Maps a logical font to a line height.
        *
        * @param aFont The logical font
        * @return the line height
        * @remarks
        * @see TCknLogicalFont in cknlogicalfont.h
        */
        virtual TInt GetLineHeight(const TCknLogicalFont& aFont)=0;

        /**
        * Creates an icon and transfers ownership of the
        * icon to the caller. The icon is created from bitmaps owned
        * by the skin manager.
        *
        * @param aId The ID of the icon
        * @return the created icon
        * @remarks
        * @see TSkinIconId in skinuid.h
        */
        virtual CGulIcon* CreateIconLC(TSkinIconId aId)=0;

        /**
        * When a skin reload has completed, this method should be called by
        * the client side application. It informs all window groups of the
        * change in skin color and updates the <code>Wserv</code> fading
        * parameters from the new skin data.
        *
        * @remarks Fading is used to change the color of windows so that 
        *          they are either closer to white or closer to black. This is
        *          to give another window prominence. For example, when 
        *          displaying a dialog, all other windows in the system can
        *          be faded
        * @see
        */
        virtual void ProcessReloadComplete()=0;


        /**
        * Duplicates the bitmaps in an .mbm file. If the file has not been 
        * loaded, the skin server loads the bitmaps contained in the file into 
        * RAM. This method must be
        * called to ensure that an .mbm is loaded into RAM so that the bitmaps
        * can be obtained using methods <code>GetBitmap()</code> and 
        * <code>Bitmap()</code>.
        *
        * @param aMbmUid The UID of the .mbm file to duplicate
        * @remarks
        * @see
        */
        virtual void DuplicateBitmapsL(TUid aMbmUid)=0;

        /**
        * Returns a skin bitmap.
        *
        * @param aMbmUid The UID of the file containing the bitmap
        * @param aId The index of the bitmap within the file
        * @return a pointer to the skin bitmap
        * @remarks A <code>NULL</code> value is returned if the file containing 
        *          the bitmap is not found. If the file exists and the bitmap
        *          requested does not, the first bitmap in the file is
        *          returned. Method <code>DuplicateAllBitmapsL()</code>
        *          should be called before this method is used
        * @see
        */
        virtual const CFbsBitmap* GetBitmap(TUid aMbmUid, TInt aId)=0;

        /**
        * Returns a bitmap and associated mask. Ownership is not transferred
        * to the caller. If the bitmap cannot be loaded, <code>aBitmap</code>
        * and <code>aMask</code> are set to <code>NULL</code>.
        *
        * @param aMbmUid The UID of the file containing the bitmap
        * @param aId The index of the bitmap within the file
        * @param aBitmap On return, contains a pointer to a pointer to the skin
        *        bitmap
        * @param aMask On return, contains a pointer to a pointer to the skin
        *        bitmap mask
        * @remarks Method <code>DuplicateAllBitmapsL()</code>
        *          should have been called before this method is used
        * @see
        */
        virtual void Bitmap(TUid aMbmUid,
                            TInt aId,
                            const CFbsBitmap** aBitmap,
                            const CFbsBitmap** aMask)=0;

        /**
        * Returns the currently selected application view
        * bitmap. Ownership of the bitmap is not transferred to the caller.
        *
        * @return a pointer to the application view bitmap
        * @remarks 
        * @see TSkinAppView for the application view bitmaps
        */
        virtual const CFbsBitmap* GetAppViewBitmap()=0;

        /**
        * Returns the currently selected application view
        * bitmap mask. Ownership of the bitmap mask is not transferred to the
        * caller.
        *
        * @return a pointer to the application view bitmap mask
        * @remarks
        * @see <code>TSkinAppView</code> for the application view bitmaps
        */
        virtual const CFbsBitmap* GetAppViewMask()=0;

        /**
        * Draw a focus rectangle for a control.
        *
        * @param aGc The bitmap context for drawing
        * @param aRect The outline of the focused control
        * @param aActiveFocus <code>ETrue</code> if the control is focused;
        *                     <code>EFalse</code> otherwise
        * @param aFrameOnly <code>ETrue</code> if only the focus rectangle is
        *                   to be drawn; <code>EFalse</code> otherwise
        * @remarks
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawFocusRect(CBitmapContext& aGc,
                                   const TRect& aRect,
                                   TBool aActiveFocus,
                                   TBool aFrameOnly=EFalse)=0;
    ///

        /**
        * Draws a focus rectangle for a masked control.
        *
        * @param aGc The bitmap context for drawing
        * @param aRect The outline of the focused control
        * @param aActiveFocus <code>ETrue</code> if the control is focused;
        *                     <code>EFalse</code> otherwise
        * @remarks
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawFocusRectMask(CBitmapContext& aGc,
                                       const TRect& aRect,
                                       TBool aActiveFocus)=0;

        /**
        * Draws the border to a control.
        *
        * @param aGc The bitmap context for drawing
        * @param aRect The outline of the control
        * @param aDimmed <code>ETrue</code> if the control is dimmed;
        *                <code>EFalse</code> otherwise
        * @remarks
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawControlBorder(CBitmapContext& aGc,
                                       const TRect& aRect,
                                       TBool aDimmed)=0;
    ///

        /**
        * Draws the border to a window.
        *
        * @param aGc The bitmap context for drawing
        * @param aRect The outline of the window
        * @remarks
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawWindowBorder(CGraphicsContext& aGc,
                                      const TRect& aRect)=0;
    ///

        /**
        * Draws the border to a window.
        *
        * @param aMasked <code>ETrue</code> if the window is masked;
        *                <code>EFalse</code> otherwise
        * @param aGc The bitmap context for drawing
        * @param aRect The outline of the window
        * @remarks <code>aMasked</code> is used to determine whether the mask 
        *          aspect of a bitmap should be drawn.
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawWindowBorder(TBool aMasked,
                                      CGraphicsContext& aGc,
                                      const TRect& aRect)=0;
    ///
    /// maps a logical font to a baseline position

        /**
        * Draws a cell text button.
        *
        * @param aGc The bitmap context for drawing.
        * @param aString The text to draw
        * @param aRect The height and width of the control - that is, the 
        *              outline of the cell
        * @param aPressed <code>ETrue</code> if the button is pressed;
        *                 <code>EFalse</code> otherwise
        * @param aFocused <code>ETrue</code> if the button is focused;
        *                 <code>EFalse</code> otherwise
        * @param aDimmed <code>ETrue</code> if the button is dimmed;
        *                <code>EFalse</code> otherwise
        * @remarks A cell text button contains a single text label. For 
        *          example, a cell text button can display a day in the week 
        *          as the string
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawCell(CBitmapContext& aGc,
                              const TDesC &aString,
                              const TRect &aRect,
                              TBool aPressed,
                              TBool aFocused,
                              TBool aDimmed)=0;

        /**
        * Attempts to release the memory used by the .mbm file. The .mbm file
        * of type <code>CSkinMbmFile</code> keeps an access count, which is 
        * incremented every time <code>DuplicateBitmapsL()</code> is called. 
        * The count value is decremented when this method is called. When the
        * value of count is zero, the bitmaps contained in the .mbm file are 
        * deleted and then the .mbm file is deleted.
        *
        * @param aUid The UID of the .mbm file
        * @remarks
        * @see

        */
        virtual void ReleaseBitmaps(TUid aUid)=0;

        /**
        * Draws the border to a control with the bottom border not drawn.
        *
        * @param aGc The bitmap context for drawing
        * @param aRect The height and width of the control
        * @param aDimmed <code>ETrue</code> if the control is dimmed
        * @remarks
        * @see CBitmapContext in gdi.h
        */
        virtual void DrawControlBorderNoBottom(CBitmapContext& aGc,
                                               const TRect& aRect,
                                               TBool aDimmed)=0;

        /**
        * Truncates a string and adds a given end character, if necessary, to
        * fit within a certain width. The method removes any white space
        * before the end character.
        *
        * @param aBuffer The string to be truncated
        * @param aFont The font to use
        * @param aMaxWidthInPixels The maximum width of the finished string,
        *                          in pixels
        * @param aEnd The character to place on the end
        * @remarks If the current text width is less than or equal to 
        *          <code>aMaxWidthInPixels</code>, no action is taken
        * @see KCknSkinClipEndChar in skin.h
        */
        virtual void ClipToFit(TDes& aBuffer,
                               const CFont& aFont,
                               TInt aMaxWidthInPixels,
                               TChar aEnd=KCknSkinClipEndChar)=0;

        /**
        * Returns a pointer to a requested bitmap.
        *
        * @param aMbmUid The UID of the file containing the requested bitmap
        * @param aId The UID of the requested bitmap stored in the bitmap file
        * @return a pointer to the requested bitmap
        * @remark The method leaves if the UID for the file is invalid. If the 
        *         file UID is valid and the requested bitmap ID is invalid, a
        *         pointer to the first bitmap in the file is returned. Otherwise, 
        *         a pointer to the requested bitmap is returned
        * @see
        */
        virtual const CFbsBitmap* GetBitmapL(TUid aMbmUid, TInt aId)=0;

        /**
        * Gets a requested bitmap and its associated bitmap mask.
        *
        * @param aMbmUid The UID of the file containing the requested bitmap
        * @param aId The UID of the requested bitmap stored in the bitmap file
        * @param aBitmap Contains the requested bitmap
        * @param aMask Contains the requested bitmap mask
        * @remark The method leaves if the UID for the file is invalid. If the 
        *         file UID is valid and the requested bitmap ID is invalid, the 
        *         first bitmap and bitmap mask in the file are assigned to the third and 
        *         fourth parameters. Otherwise the requested bitmap and mask are 
        *         assigned
        * @see
        */
        virtual void BitmapL(TUid aMbmUid, 
                             TInt aId, 
                             const CFbsBitmap** aBitmap, 
                             const CFbsBitmap** aMask)=0;

        /**
        * Gets a the handles of bitmaps for the specified application UID. Some parameters only used in S80
        *
        * @param aAppUid The UID of the application
        * @param aArray returned array of bitmap handles, alternating between bitmaps and masks
        * @return ETrue if skin icon exists, else EFalse. Any errors cause a leave
        */
        virtual TBool GetAppIconL(RApaLsSession& aApaSession, TUid aAppUid, const TSize &aIconSize, CApaMaskedBitmap &aMaskedBitMap,TBool aDontReloadApparcIcon=EFalse)=0;

        /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_1()=0;

       /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_2()=0;

               /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_3()=0;

       /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_4()=0;

       /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_5()=0;

        /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_6()=0;

        /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_7()=0;

       /**
        * @internal
        */
        virtual void CCknSkinBase_Reserved_8()=0;

    };

#endif  // SKIN_H

// End of File
