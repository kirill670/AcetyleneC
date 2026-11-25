/*
* ==============================================================================
*  Name        : cknlogicalfont.h
*  Part of     : CUIKLAF
*  Interface   : Logical Font API
*  Description : The TCknLogicalFont font class and enum of font types.
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


#ifndef CKNLOGICALFONT_H
#define CKNLOGICALFONT_H

// INCLUDES
#include <CknLogicalFont.hrh>
#include <gulfont.h>


/**
 * The <code>TCknLogicalFont</code> class derives from <code>TLogicalFont</code>
 * (defined in gulfont.h) and is the Ckon Logical Font interface. Font 
 * categories have been added here that represent all of the Logical Fonts in 
 * the system. A Logical Font category defines a font by the situation in 
 * which it is used, for example, dialog title, menu item, and application view.
 * A Logical Font can be passed in to <code>CEikonEnv::Font()</code> to obtain 
 * a pointer to a <code>CFont</code> object (defined in gdi.h), which is used 
 * to actually draw text. A new Logical Font is constructed by passing one of 
 * the font categories as a parameter to the constructor. The 
 * <code>iCategory</code> member of <code>TLogicalFont</code> is used to store 
 * the new font category. The <code>iStyle</code> and <code>iZoomFactor</code> 
 * members are not used for <code>TCknLogicalFont</code> objects.
 * 
 * @lib egul.lib
 * @lib gdi.lib
 * @since Series90 1.0
 */
class TCknLogicalFont : public TLogicalFont
    {
    public:
    /**
     * The enumeration <code>TFontCategory</code> provides the Logical Font 
     * categories that define a font by the screen element for which it is 
     * used, for example, dialog title, menu item, or application view.
     * This enumeration is repeated in cknlogicalfont.hrh for use in .rss files.
     */
    enum TFontCategory
        {
        /** application title font */
        EAppTitle=ECknLogicalFontAppTitle,
        /** application sub-name (optional text to right of title) font */
        EViewSelectorFont,
        /** normal CBA button font */
        ECommandButtonFontNormal, 
        /** 
         * small CBA button font; used when label text is too long for normal
         * font 
         */
        ECommandButtonFontSmall, 
        /** clock under CBA font */
        ECBBClock,
        /** plain text editor (edwin) font */
        EPlainTextEditorFont,
        /** rich text editor font */
        ERichTextEditorFont,
        /** application view level 1 font in default zoom */
        EViewLevel1ZoomDefaultFont, 
        /** application view level 2 font in default zoom */
        EViewLevel2ZoomDefaultFont, 
        /** application view level 3 font in default zoom */
        EViewLevel3ZoomDefaultFont,
        /** application view level 4 font in default zoom */
        EViewLevel4ZoomDefaultFont,
        /** application view level 1 font in small zoom (zoomed out) */
        EViewLevel1ZoomSmallFont,
        /** application view level 2 font in small zoom (zoomed out) */
        EViewLevel2ZoomSmallFont,
        /** application view level 3 font in small zoom (zoomed out) */
        EViewLevel3ZoomSmallFont,
        /** application view level 4 font in small zoom (zoomed out) */
        EViewLevel4ZoomSmallFont,
        /** application view level 1 font in big zoom (zoomed in) */
        EViewLevel1ZoomBigFont,
        /** application view level 2 font in big zoom (zoomed in) */
        EViewLevel2ZoomBigFont,
        /** application view level 3 font in big zoom (zoomed in) */
        EViewLevel3ZoomBigFont,
        /** application view level 4 font in big zoom (zoomed in) */
        EViewLevel4ZoomBigFont, 
        /** dialog title font */
        EDialogTitleFont,
        /** dialog tab font */
        EDialogTabFont, 
        /** dialog caption font */
        EDialogCaptionFont,
        /** dialog trailer font */
        EDialogTrailerFont,
        /** dialog label font */
        EDialogLabelFont, 
        /** dialog button font */
        EDialogButtonFont,
        /** dialog subtitle font */
        EDialogSubTitleFont,
        /** first level menu item font */
        EMenuItemFont,
        /** second level menu item font */
        EMenuItemFontSecondLevel,
        /** third level menu item font */
        EMenuItemFontThirdLevel,
        /** menu shortcut font */
        EMenuShortcut,
        /** banner (info message) font */
        EBannerFont,
        /** progress bar font */
        EProgressBarFont,
        /** calendar month name font */
        ECalendarMonthNameFont,
        /** calendar day initial (for example, MoTuWeThFrSaSu) font */
        ECalendarDayInitialFont,
        /** calendar week number font */
        ECalendarWeekNumberFont,
        /** calendar day number font */
        ECalendarDayNumberFont,
        /** grid field font */
        EGridFieldFont,
        /** grid label font */
        EGridLabelFont,
        /** character map font */
        ECharmapFont,
        /** time-picker font */
        ETimePicker,
        /** symbol font */
        ESymbolFont,
        /** note font, used in panic dialog, installation dialog, alarm notifier, etc. */
        ENoteFont,
        /** view button font */
        EViewButtonFont,
        /** a fixed width font */
        EMonospaceFont,
        /** big digital clock am/pm font */
        EBigDigitalAmPmFont,
        /** big digital clock number font */
        EBigDigitalNumberFont,
        /** small digital clock am/pm font */
        ESmallDigitalAmPmFont,
        /** small digital clock number font */
        ESmallDigitalNumberFont,
        /** big analog clock am/pm font */
        EBigAnalogFont,
        /** small analog clock am/pm font */
        ESmallAnalogFont,
        /** calendar appointment day initial (for example, MoTuWeThFrSaSu) font */
        ECalendarAppointmentDayInitialFont,
        /** not used */
        EListItemRemovedDefault,
        /** not used */
        EListItemRemovedSmall,
        /** not used */
        EListItemRemovedBig,
        /** not used */
        EListItemWaitingDefault,
        /** not used */
        EListItemWaitingSmall,
        /** not used */
        EListItemWaitingBig,
        /** total result in calculation line in the Calculator basic view */
        ECalculatorBasicCalculationLine,
        /** call header button label font */
        ECallHeaderButton,
        /** am/pm font in time-picker control */
        ETimePickerFormatFont,
        /** virtual keyboard in default zoom */
        EVirtualKeyboardZoomDefault,
        /** virtual keyboard in small zoom (zoomed out) */
        EVirtualKeyboardZoomSmall,
        /** virtual keyboard in big zoom (zoomed in) */
        EVirtualKeyboardZoomBig,
        /** time/date text in partial mode */
        EPartialModeDateTime,
        /** profile text in partial mode */
        EPartialModeProfileText,
        /** unread messages in default zoom */
        EMarkedItemZoomDefault,
        /** unread messages in small zoom (zoomed out) */
        EMarkedItemZoomSmallFont,
        /** unread messages in big zoom (zoomed in) */
        EMarkedItemZoomBigFont,
        /** left and right indicators in calculation line in Calculator */
        ECalculatorFunctionalIndicator,
        /** calculation line font in Calculator TillRoll view */
        ECalculatorTillRollCalculationLine,
        /** call status text font */
        ECallStatusText,
        /** dialer button number font */
        EDialerButtonNumber,
        /** dialer button letter font */
        EDialerButtonLetter,
        /** dialer input in big zoom (zoomed in) */
        EDialerInputZoomBig,
        /** dialer input in default zoom */
        EDialerInputZoomMiddleSize,
        /** dialer input in small zoom (zoomed out) */
        EDialerInputZoomSmall,
        /** dialer indicator font */
        EDialerIndicator,
        /** dialer operator name font */
        EDialerOperatorName,
        /** web view font */
        EWebView,
        /** toolbar font */
        EToolbar,
        /** plain text editor (edwin) bold font */
        EPlainTextEditorBold,
        /** application view level 1 bold font in default zoom */
        EViewLevel1ZoomDefaultBold,
        /** application view level 1 bold font in small zoom (zoomed out) */
        EViewLevel1ZoomSmallBold,
        /** application view level 1 bold font in big zoom (zoomed in) */
        EViewLevel1ZoomBigBold,
        /** calendar day entry font */
        ECalendarDayEntry,
        /** weekday picker font */
        EWeekdayPicker,
        /** font for seek bar */
        ESeekBarFont,
        /** name info of the station */
        ERadioStationNameFont,
        /** font for frequency */
        ERadioFrequencyFont,
        /** layout selectors normal zoom level */
        EPeninputButtonDefault,
        /** layout selectors small zoom level */
        EPeninputButtonSmall,
        /** layout selectors big zoom level */
        EPeninputButton,
        /** language indicator normal zoom level*/
        EPeninputLangDefault,
        /** language indicator small zoom level */
        EPeninputLangSmall,
        /** language indicator big zoom level */
        EPeninputLangBig,
        /** dialog font for highlighting text */
        EDialogMarked,
        /** MMS text editor title font in default zoom */
        EMMSTextEditorTitleZoomDefault,
        /** MMS text editor title in small zoom (zoomed out) */
        EMMSTextEditorTitleZoomSmall,
        /** MMS text editor title in big zoom (zoomed in) */
        EMMSTextEditorTitleZoomBig,
        /** used in a dialog to indicate the header for body text/captions */ 
        // (was supposed to be <code>ETitleFont</code>) 
        EDialogHeader,
        /** the font for progress banner text in browser application */
        EBrowserProgressBannerFont,
        /** series 80 only */
        EMainTitleFont,
        /** title font for information and confirmation notes */
        ENoteTitleFont,
        /** font used to annotate things */
        EAnnotationFont,
        /** font used for listbox descriptive column */
        EListItemDescriptive,
        /** font used below icon as caption font where zooming is not possible */
        EIconCaptionFont
        };
    public:

        /**
        * The default object constructor.
        *
        * @remarks Sets the font category to the normal system font, 
        *          <code>TLogicalFont::EView</code>
        * @see
        */
        inline TCknLogicalFont();

        /**
        * The object constructor.
        *
        * @param aCategory The font category to set
        * @remarks
        * @see
        */
        inline TCknLogicalFont(TFontCategory aCategory);

        /**
        * Sets the Logical Font category.
        *
        * @param aCategory The font category to set
        * @remarks
        * @see
        */
        inline void SetCategory(TFontCategory aCategory);
        
        /**
        * Returns the Logical Font category.
        *
        * @return the font type from the 
        *         <code>TCknLogicalFont::TFontCategory</code> enumeration
        * @remarks
        * @see
        */
        inline TFontCategory Category() const;
    };

inline TCknLogicalFont::TCknLogicalFont() :
    TLogicalFont()
    {
    }

inline TCknLogicalFont::TCknLogicalFont(TFontCategory aCategory) :
    TLogicalFont(KNullUid, 
                 static_cast<TLogicalFont::TFontCategory>(static_cast<TInt>(aCategory)), 
                 TLogicalFont::ENormal, 
                 TZoomFactor())
    {
    }

inline void TCknLogicalFont::SetCategory(TFontCategory aCategory)
    {
    iCategory=static_cast<TLogicalFont::TFontCategory>(static_cast<TInt>(aCategory));
    }

inline TCknLogicalFont::TFontCategory TCknLogicalFont::Category() const
    {
    return static_cast<TCknLogicalFont::TFontCategory>(static_cast<TInt>(iCategory));
    }
    
#endif  // CKNLOGICALFONT_H

// End of File
