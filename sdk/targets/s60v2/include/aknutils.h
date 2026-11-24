/*
* ============================================================================
*  Name     : AknUtils.h
*  Part of  : Avkon
*
*  Description:
*     General Avkon Utilities. Includes:
*		- listbox utilities
*		- layout utilities
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
* ============================================================================
*/

#ifndef __AKNUTILS_H__
#define __AKNUTILS_H__

#include <eiktxlbm.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <coedef.h>
#include <coecobs.h>
#include <w32std.h>
#include <gulalign.h>
#include <gulutil.h>
#include <eikenv.h>
#include <biditext.h>
#include <eiksbfrm.h>
#include <AknsConstants.h>

#include <aknlayout.lag>

// These are for listbox column lengths (These are used to allocate memory from stack while drawing listboxes, they should be as small as possible, but not smaller!)
const TInt KMaxColumnDataLength = 80; // This is maximum length of data for one listbox column -- after that the data is truncated before drawing.
const TInt KMaxTotalDataLength = 8*KMaxColumnDataLength;  // max of 5 columns can have full 80 characters...

/** AVKON utility module
 *
 * From this file, you can find several tools for making application development easier for Series 60
 *
 * 1) Conversion modules to convert coordinate data from european LAF to usable formats
 *     AknLayoutUtils, TAknLayoutRect, TAknLayoutText
 * 2) Utilities to clip text
 * 3) Part of selection service implementation
 * 4) Different classes that help using listboxes
 * 5) Handling colors in AKN_LAF_COLOR macro.
 * 6) Resource readers for different purposes
 * 7) Utility to find files without specifying the drive letter or path
 */


class CCoeControl;
class CEikTextListBox;
class CEikColumnListBox;
class CEikFormattedCellListBox;
class CGulIcon;
class CEikSettingsListBox;
class CAknLAF;
class CEikImage;
class CEikMfne;
class CEikListBox;
class CEikLabel;
class CEikEdwin;
class CEikMenuPane;
class CAknPopupField;
class CListBoxView;
class CAknColumnListBox;
class CEikSecretEditor;
class CFindExtension;
class CAknLayoutFont;

/**
 * Egul library had methods to clip text from right side, this class includes methods to clip from both sides.
 * It does add 3 dots to the end of the text.
 */
const TInt  KDefaultClipWidth = -1;
const TUint KDefaultClipChar  = TUint(0x2026);

/**
* Text utilities.
* Text truncating and wrapping methods in this class do not support 
* text that requires conversion from logical to visual form,
* e.g. Arabic/Hebrew, Thai and Hindi text. Code that needs to support that
* kind of text should use corresponding methods in AknBidiTextUtils instead.
*/
class AknTextUtils 
    {
public:
    enum TClipDirection
	{
	EDoNotClip,
	EClipFromEnd,
	EClipFromBeginning
	};
    /** ClipToFit() Generic clipping
	
	@param aBuffer         String that needs to be clipped. will be modified by this call
	@param aFont           Font used in the code
	@param aMaxWidthInPixels Maximum length of text that will not be clipped.
	@param aDir            Where is the text clipped from. EDoNotClip, EClipFromEnd, EClipFromBeginning.
	@param aClipWidth      The length of the text after clipping. KDefaultClipWidth will make it use aMaxWidthInPixels.
	@param aClipString     The representation of three dots. (not really used anywhere - use the default value always or "")
       
	returns true if the text was clipped and 3 dots were added. 
    */
    
    IMPORT_C static TBool ClipToFit(TDes& aBuffer, const CFont& aFont, TInt aMaxWidthInPixels, TClipDirection aDir=EClipFromEnd, TInt aClipWidth = KDefaultClipWidth, const TDesC &aClipString=_L("..."));

    /** ClipToFit() for clipping text inside lists
     *
     * NOTICE: This method cannot handle situation where the text may dynamically change its size! Especially when you have bitmaps on the right side!
     *
     * This needs to be done AFTER the listbox has done its SizeChanged()!
     */
    IMPORT_C static TBool ClipToFit(TDes& aBuffer, TClipDirection aDir, CEikFormattedCellListBox *aListBox, TInt aItemIndex, TInt aSubCellNumber);

    /** ClipToFit() for clipping text inside lists
     *
     * NOTICE: This method cannot handle situation where the text may dynamically change its size! Especially when you have bitmaps on the right side!
     *
     * This needs to be done AFTER the listbox has done its SizeChanged()!
     */
    IMPORT_C static TBool ClipToFit(TDes& aBuffer, TClipDirection aDir, CEikColumnListBox *aListBox, TInt aItemIndex, TInt aColumnNumber);

    // implementation

    static TBool DoClipToFit(
        TDes& aBuffer,
        const CFont& aFont,
        TInt aMaxWidthInPixels,
        TClipDirection aDir,
        TInt aClipWidth,
        const TDesC& aClipString );

    /**
    * Wraps a string to an array of pointers.
	* The number of lines and line widths are specified by aLineWidthArray.
	* The pointers in aWrappedArray point to positions inside aWrappedString.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Line widths in pixels
    * @param aFont              Used font
    * @param aWrappedArray      Pointers to wrapped lines
    */
    IMPORT_C static void WrapToArrayL( 
        const TDesC& aStringToWrap,
	    const CArrayFix<TInt>& aLineWidthArray,
	    const CFont& aFont,
	    CArrayFix<TPtrC>& aWrappedArray);

    /**
    * Wraps a string to an array of pointers.
	* Constant line width is given.
	* The pointers in aWrappedArray point to positions inside aWrappedString.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidth         Constant line width in pixels
    * @param aFont              Used font
    * @param aWrappedArray      Pointers to wrapped lines
    */
    IMPORT_C static void WrapToArrayL( 
        const TDesC& aStringToWrap,
	    TInt aLineWidth,
	    const CFont& aFont,
	    CArrayFix<TPtrC>& aWrappedArray );

    /**
    * Wraps a string to an array of pointers and clips at the end
	* of the last line if there aren't enough lines to accomodate
	* the entire text. When clipping three dots are inserted at the
	* end of the last line.
	* The number of lines and line widths are specified by aLineWidthArray.
	* The pointers in aWrappedArray point to positions inside aWrappedString.
    *
	* Expect the string to be modified if clipping is needed.
	* (Clipping character KEllipsis is inserted at the ending point)
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Line widths in pixels
    * @param aFont              Used font
    * @param aWrappedArray      Pointers to wrapped lines
    */
    IMPORT_C static void WrapToArrayAndClipL( 
        TDes& aStringToWrap,             
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont,                     
	    CArrayFix<TPtrC>& aWrappedArray );       
	
	/**
    * Chops a string when a line break character is encountered.
	* Clips at the end of each line if there isn't enough space
	* on that line.
	* When clipping, KEllipsis (shown as 3 dots) is inserted at
    * the end of the line.
	* The number of lines and line widths are specified by aLineWidthArray.
	* The pointers in aChoppedArray point to positions inside aStringToChop.
    *
	* Expect the string to be modified if clipping is needed
	* (Clipping character KEllipsis is inserted in the end of the lines)
    *
    * @param aStringToChop      String that needs to be chopped
    * @param aLineWidthArray    Line widths in pixels
    * @param aFont              Used font
    * @param aChoppedArray      Pointers to chopped lines
    */
	IMPORT_C static void ChopToArrayAndClipL(
		TDes& aStringToChop,             
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont,                    
	    CArrayFix<TPtrC>& aChoppedArray);

	/**
    * Chops a string when a line break character is encountered.
	* Clips at the end of each line if there isn't enough space
	* on that line.
	* When clipping, KEllipsis (shown as 3 dots) is inserted at
    * the end of the line.
	* Constant line width is given.
	* The pointers in aChoppedArray point to positions inside aStringToChop.
    *
	* Expect the string to be modified if clipping is needed
	* (Clipping character KEllipsis is inserted in the end of the lines)
    *
    * @param aStringToChop      String that needs to be chopped
    * @param aLineWidth         Constant line width in pixels
    * @param aFont              Used font
    * @param aChoppedArray      Pointers to chopped lines
    */
	IMPORT_C static void ChopToArrayAndClipL(
		TDes& aStringToChop,             
	    TInt aLineWidth, 
	    const CFont& aFont,                    
	    CArrayFix<TPtrC>& aChoppedArray );

    /**
    * Wraps a string (aStringToWrap) into lines according to the
	* number of lines and line widths specified in aLineWidthArray. 
	* Inserts '\n' at the end of lines. 
	* Copies the result into aWrappedString.
    * Leaves if aWrappedString isn't big enough.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Lines widths in pixels
    * @param aFont              Used font
    * @param aWrappedString     Wrapped string 
    */
    IMPORT_C static void WrapToStringL( 
        const TDesC& aStringToWrap,
	    const CArrayFix<TInt>& aLineWidthArray,
	    const CFont& aFont,
	    TDes& aWrappedString );

   /**
	* Wraps a string (aStringToWrap) into lines according to the
	* number of lines and line widths specified in aLineWidthArray. 
	* Inserts '\n' at the end of lines. 
	* Clips the last line if there aren't enough lines to
	* fit the entire string. 
	* Copies the result into aWrappedString.
    * Leaves if aWrappedString isn't big enough.
    *
    * @param aStringToWrap      String that needs to be wrapped
    * @param aLineWidthArray    Width of lines in pixels
    * @param aFont              Used font
    * @param aWrappedString     Wrapped string 
    */
	IMPORT_C static void WrapToStringAndClipL(
	    const TDesC& aStringToWrap, 
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont, 
	    TDes& aWrappedString ); 

    /**
     * This routine is used to strip away a set of characters from
     * a descriptor.
     *
     * Useful for example for listboxes to make sure strings from
     * network or typed by the end user does not have tab or linefeed
     * characters. (as those will make listbox broken.)
     * 
     * @param   aDes         Parameter to change
     * @param   aCharacters  A set of characters to remove
     *
     * There exists predefined character sets to remove:
     *    KAknStripTabs
     *    KAknStripListControlChars  (\t's and \n's and \r's)
     */
    IMPORT_C static void StripCharacters(TDes &aDes, const TDesC &aCharacters);

    /**
     * This routine is used to replace all control chars with a single 
     * character, usually a whitespace.
     *
     * @param   aDes         Parameter to change
     * @param   aCharacters  A set of characters to remove
     * @param   aReplacement a character used as replacement
     *
     *    KAknReplaceTabs
     *    KAknReplaceListControlChars  (\t's and \n's)
     */
    IMPORT_C static void ReplaceCharacters(TDes &aDes, const TDesC &aChars, TChar aReplacement);

    /**
     * This routine is used to remove extra whitespaces from text before 
     * showing on screen
     *
     * @param   aDes                   Parameter to change
     * @param   aWhiteSpaceCharacters  A set of whitespace characters to remove
     */
    IMPORT_C static void PackWhiteSpaces(TDes &aDes, const TDesC &aWhiteSpaceChars);
    
    // non-exported implementation

    static void WrapToStringL(
        const TDesC& aStringToWrap, 
	    const CArrayFix<TInt>& aLineWidthArray, 
	    const CFont& aFont, 
	    TDes& aWrappedString,
        TInt aFlags,
        TInt aDirectionality );

    static void WrapToArrayL( 
        TDes& aStringToWrap,
        const CArrayFix<TInt>* aLineWidthArray, 
        const CFont& aFont,
        CArrayFix<TPtrC>& aWrappedArray,
        TInt aLineWidth,
        TInt aFlags,
        TInt aDirectionality );

    static void ChopToArrayAndClipL(
		TDes& aStringToChop,             
	    const CArrayFix<TInt>* aLineWidthArray,
	    const CFont& aFont,                 
	    CArrayFix<TPtrC>& aChoppedArray,
        TInt aLineWidth );    

	/**
	* This utility is used to see if a text is empty according to the conventions of 
	* Avkon.
	*
	* @param	aTextToTest
	* @return	ETrue if the text is empty according to Avkon
	*/
	static TBool IsEmptyText( const TDesC& aTextToTest );

	/**
	 * This routine is used to convert between arabic-indic digits and european digits.
	 * based on existing language setting. So it'll convert any digit from the string
	 * to use either european digits or arabic-indic digits based on current settings.
     *
	 * NOTE: THis method can be also called in european release. The method is required
	 * to do the correct thing with all the languages.
     *
	 * This method should only be used just before displaying the number as unicode string.
	 * Also, never store the converted string as unicode.
	 *
	 * @since 2.0
	 * @param   aDes                    Parameter to change
	 */
	IMPORT_C static void LanguageSpecificNumberConversion(TDes &aDes);

    /**
     * This routine is used to convert digits from any digit format to another format eg. from 
     * european digits to arabic-indic digits.
     *
	 * @since 2.0
     * @param aDes                      Parameter to change. It can contain digits from several digit types.
     * @param aDigitType                Destination digit type.
     */
    IMPORT_C static void ConvertDigitsTo( TDes& aDes, TDigitType aDigitType );

    /**
    * Convenience routine to obtain the directionality of the current input language
    * This routine will attempt to access this information in a system-efficient way.
    *
    * This is not to be confused with either the directionality of the display text 
    * language or (a closely associated concept) the layout direction of the UI 
    * (accessed via AknLayoutUtils::LayoutMirrored() )
    * 
    * @since 2.0
    * @return TBidiText::ELeftToRight if the current input language is left to right
    *         TBidiText::ERightToLeft if the current input langauge is right to left     
    */
    IMPORT_C static TBidiText::TDirectionality CurrentScriptDirectionality();

    /**
    * Method used to constrain the digit type to use to that consisted with the current input language
    * 
    * @since 2.0
    * @returns TDigitType consistent with the current input language
    */
    static TDigitType InputLanguageFilteredDigitType();

    /**
    * Method used to constrain the digit type to use to that consisted with the current display text language
    * 
    * @since 2.0
    * @returns TDigitType consistent with the current input language
    */
    static TDigitType DisplayTextLanguageFilteredDigitType();

    /**
    * Returns the digit type to be used for editors that are purely numeric in quality.
    *
    * @since 2.0
    * @returns TDigitType to use for purely numeric editors
    */ 
	IMPORT_C static TDigitType NumericEditorDigitType();

    /**
	 * This routine is used to convert between arabic-indic digits and european digits.
	 * based on existing language setting. So it'll convert any digit from the string
	 * to use either european digits or arabic-indic digits based on current settings.
     *
     * This routine builds in the constraints imposed by current display text languages. 
     *
     * The number of characters in the buffer is not changed by this routine. It can therefore be 
     * safely used easily with existing (modifiable) descriptors.
     *
	 * This method should only be used just before displaying the number as unicode descriptor.
	 * Never store the converted string.
	 *
	 * @since 2.0
	 * @param   aDes                    Parameter to change
	 */
    IMPORT_C static void DisplayTextLanguageSpecificNumberConversion(TDes &aDes);
  
    /**
    * Returns the digit type to be used for editors that are alphanumeric.
    * (Note that these editors may be configurable to be purely numeric - that is have a numeric
    * mode, but they remain alphanumeric editors for the sake of this API.)
    *
    * This may be useful for instance for input processors that convert numeric key events to the 
    * currently set input digit type.
    *
    * @since 2.0
    * @returns TDigitType to editors with alphanumeric capability
    */ 
    IMPORT_C static TDigitType TextEditorDigitType();

	enum TDigitModeQueryType {
		EDigitModeEditorDefault, // in editors by default whether western or foreign digits are used
		EDigitModeUserModifiableEditor, // in editors whether user can modify digitmode with keypad
	    EDigitModeShownToUser // in all components when displaying digits
	};
	/**
	 * This routine can be used to check what modes digits can be on.
	 *
	 * It uses input language, display language and the setting from general settings
	 * to calculate whether foreign digits need to be used.
	 *
	 * This is useful for editor implementation and anyone that needs to convert
	 * digits for display.
	 * 
	 * @since 2.0
	 * @param aQueryType   what is the situation where the digits are to be used.
	 * @returns ETrue to indicate whether digit conversions need to be used.
	 * @returns EFalse to indicate that no conversion is needed.
	 */
	IMPORT_C static TBool DigitModeQuery(TDigitModeQueryType aQueryType = EDigitModeShownToUser);

    /** Converts a filename AAAAA.EXT to format which is suitable for display. 
     *
     * This method handles arabic&hebrew text correctly inside filename.
     *
     * @since 2.6
     */
    IMPORT_C static HBufC *ConvertFileNameL(const TDesC &aDes);


    /**
    * @deprecated
    * Do not use. This method will be removed.
    */
    IMPORT_C static HBufC* LoadScalableTextL(CCoeEnv& aCoe, TInt aResourceId);

    /**
    * @deprecated
    * Do not use. This method will be removed.
    */
    IMPORT_C static HBufC* LoadScalableTextLC(CCoeEnv& aCoe, TInt aResourceId);

    /**
    * @deprecated
    * Do not use. This method will be removed.
    */
    IMPORT_C static TInt LoadScalableText(CCoeEnv& aCoe, TInt aResourceId, TDes& aBuffer ); 

    /**
    * @deprecated
    * Do not use. This method will be removed.
    */
    IMPORT_C static HBufC* ClipAccordingScreenOrientationLC(CCoeEnv& aCoe, HBufC* aBuf); 

    /**
    * Utility method used in scalable UI for choosing the longest fitting text variant.
    * Truncating and wrapping methods in classes AknTextUtils and AknBidiTextUtils do
    * the choice by themselves, so whenever they are used to process the text, it is not
    * necessary to call this method.
    *
    * Applications do not need to call this method if they pass their localized texts
    * to Avkon's UI components.
    *
    * @since 2.8
    * 
    * @param aText Text containing one or many variants with varying text widths,
    * separated with the character 0x0001. The text is supposed to be 
    * in logical order.
    * @param aFont Font used to render the text.
    * @param aMaxWidthInPixels Max width in pixels.
    *
    * @ret Longest fitting text. If none of the variants fits,
    * the shortest one in pixels is returned.
    */
    IMPORT_C static TPtrC ChooseScalableText(
        const TDesC& aText,
        const CFont& aFont,
        TInt aMaxWidthInPixels );
    };

_LIT(KAknStripTabs, "\t");
_LIT(KAknStripListControlChars, "\t\n");
_LIT(KAknReplaceTabs, "\t");
_LIT(KAknReplaceListControlChars, "\t\n");
_LIT(KAknCommonWhiteSpaceCharacters, " \n\t\r");

/**
 * These are part of Selection service and they should be called by application's HandleCommandL() to get
 * menus and cba's handled automatically for selection service.
 *
 * The right way to implement these would be to have dialogs with names "Selection List", "MultiSelection List"
 * and "Markable list" and make them keep a listbox inside it. (look at CAknPopupList, it does similar things)
 *
 * See CAknSelectionListDialog and CAknMarkableListDialog from aknselectionlist.h, they provide better
 * interface for applications.
 */
class AknSelectionService
    {
public:
    /** Helper function to implement ProcessCommandL() for selection list dialogs
     */
    IMPORT_C static void HandleSelectionListProcessCommandL(TInt aCommand, CEikListBox* aListBox);
    /** Helper function to implement ProcessCommandL() for selection list dialogs
     */
    IMPORT_C static void HandleMultiselectionListProcessCommandL(TInt aCommand, CEikListBox* aListBox);
    /** Helper function to implement ProcessCommandL() for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListProcessCommandL(TInt aCommand, CEikListBox* aListBox);

    /** Helper function to implement ProcessCommandL() for menu lists
     */
    IMPORT_C static TKeyResponse HandleMenuListOfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType, CEikListBox* aListBox);
    /** Helper function to implement DynInitMenuPaneL() for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListDynInitMenuPane(TInt aResourceId, CEikMenuPane *aMenu, CEikListBox *aListBox);
    /** Helper function to implement DynInitMenuPaneL() for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListDynInitMenuItem(CEikMenuPane *aMenu, CEikListBox *aListBox, TInt aCommandId, TBool aCanBeAppliedToMultipleItems);
    /** Helper function to implement command handling for markable list dialogs
     */
    IMPORT_C static void HandleMarkableListUpdateAfterCommandExecution(CEikListBox *aListBox);

    /** Helper function to position list highlight correctly after item removal
     */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, TBool aCurrentItemWasRemoved);
    // This one updates selectionindexes too.
    /** Helper function to position list highlight correctly after item removal
     *
     * It also updates selection index array based on information about which
     * items were removed.
     */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, CArrayFix<TInt> &aIndexesOfRemovedItemsBeforeRemoval);
    };



class CAknSearchField;

/** This class implments Find requirements from component specifications
 * This class works also as documentation of how to use different find components. (The implementation has been
 * copied from the example application which implements find and replaced the code with calls to these static
 * functions)
 *
 * There is no reason for an application to use this class directly.
 * Application should use CAknSelectionListDialog instead. This class
 * is public only because sometimes it is necessary to access the
 * low level behaviour of find to implement similar functionality in
 * places independent of find; or if CAknSelectionListDialog is not
 * used for some reason.
 */
class AknFind
    {
public:
    IMPORT_C static void HandleFindPopupProcessCommandL(TInt aCommand, CEikListBox *aListBox, CAknSearchField *aSearchField, CCoeControl *aParentControl);
    IMPORT_C static TKeyResponse HandleFindOfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType, CCoeControl *aListBoxParent, CEikListBox *aListBox, CAknSearchField *aSearchField, TBool isFindPopup, TBool &aNeedRefresh);

    /*
    * Do not use this method.
    *
    * @deprecated
    */
    IMPORT_C static void HandleFindSizeChanged(CCoeControl *aParentControl, 
					       CEikListBox *aListBox, 
					       CAknSearchField *aSearchField, 
					       TBool ispopup = ETrue, 
					       TInt aFindWindowResourceId = R_AVKON_POPUP_FIND_WINDOW, 
					       TInt aListAreaId = R_AVKON_LIST_GEN_PANE, 
					       TInt aListResourceIdWithFindPopup = R_AVKON_LIST_GEN_PANE_WITH_FIND_POPUP, 
					       TInt aFindWindowParentResourceId = R_AVKON_MAIN_PANE_WITH_STATUS_PANE);

    /** This is the new typesafe(and easier to use) version of HandleFindSizeChanged. Use this instead of (deprecated) HandleFindSizeChanged().
     */
    IMPORT_C static void HandleFixedFindSizeChanged(CCoeControl *aParentControl,
						    CAknColumnListBox *aListBox, // only available with column lists
						    CAknSearchField *aSearchField);
    
    /** This is the new typesafe(and easier to use) version of HandleFindSizeChanged. Use this instead of (deprecated) HandleFindSizeChanged().
     */
    IMPORT_C static void HandlePopupFindSizeChanged(CCoeControl *aParentControl,
						    CEikListBox *aListBox,  // available with all lists.
						    CAknSearchField *aSearchField);
    /*
    * Use this variant in cases, where the methods above are not sufficient.
    * @since 2.6
    */
    IMPORT_C static void HandleFindSizeChangedLayouts(CCoeControl *aParentControl, 
        CEikListBox* aListBox, 
        CAknSearchField* aSearchField, 
        const TAknWindowLineLayout& aFindWindow,
        const TAknWindowLineLayout& aListArea,
        TBool aIsPopup,
        const TAknWindowLineLayout& aFindWindowParent );

public:
    /**
     * Returns ETrue if list box item text aItemText matches aSearchText in the 
     * sense described in Series 60
     */
    IMPORT_C static TBool IsFindMatch(const TDesC& aItemText, const TDesC& aSearchText);

    /**
     * Returns ETrue if aCh is a word separator character as described in Series 60
     */
    IMPORT_C static TBool IsFindWordSeparator(TChar aCh);


    /**
     * Helper function to handle find pane's visibility
     */
    static void HandleFindPaneVisibility(CAknSearchField *aSearchField, TBool ispopup, TBool textchanged, TBool &aNeedRefresh);

    };


/** 
 * Utility class to initialize editor control. 
 * Use this in conjunction with AknLayoutUtils::LayoutEdwin()
 * The class is not fully implemented yet.
 */
class AknEditUtils
    {
    public:
    struct SAknEditorParameters 
	{
	TInt iEditingSpace;
	TInt iEditingWindow;
	TInt iCharacterCase;
	TInt iJustification;
	TBool iAllowedToMoveInsertionPoint;
	TBool iCursorYesNo;
	TBool iOverflowYesNo;
	};

    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, TInt aResourceId);
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, TResourceReader& aReader);
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, const SAknEditorParameters &aParams);

/**
 *  Configures edwin editor. Use AknLayoutUtils::LayoutEdwin() with this method.
 *
 *  @param aEdwin Edwins created with new.
 *  @param aEditingSpace maximum number of characters for the editor
 *  @param aEditingWindow maximum number of lines in the editor
 *  @param aCharacterCase initial character case:
 *          EAknEditorCharactersUpperCase = EAknEditorUpperCase,
 *	        EAknEditorCharactersLowerCase = EAknEditorLowerCase,
 *	        EAknEditorCharactersTextCase = EAknEditorTextCase,
 *          EAknEditorCharactersTitleCase = EAknEditorTitleCase
 *
 *  @param aJustification alignment for the editor text ( EAknEditorAlignCenter, 
 *         EAknEditorAlignLeft, EAknEditorAlignRight)
 *  @param aAllowedToMoveInsertionPoint user can move cursor
 *  @param aCursorYesNo is cursor visible or not.
 *  @param aOverflowYesNo
 */
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, 
					   TInt aEditingSpace, 
                       TInt aEditingWindow, 
                       TInt aCharacterCase, 
                       TInt aJustification, 
                       TBool aAllowedToMoveInsertionPoint, 
                       TBool aCursorYesNo, 
                       TBool aOverflowYesNo);
                       
/**
 *  Configures edwin editor. Use AknLayoutUtils::LayoutEdwin() with this method.
 *  
 *  @param aEdwin Edwins created with new.
 *  @param aEditingSpace maximum number of characters for the editor
 *  @param aEditingWindow maximum number of lines in the editor
 *  @param aCharacterCase initial character case:
 *          EAknEditorCharactersUpperCase = EAknEditorUpperCase,
 *	        EAknEditorCharactersLowerCase = EAknEditorLowerCase,
 *	        EAknEditorCharactersTextCase = EAknEditorTextCase,
 *          EAknEditorCharactersTitleCase = EAknEditorTitleCase
 *
 *  @param aJustification alignment for the editor text ( EAknEditorAlignCenter, 
 *         EAknEditorAlignLeft, EAknEditorAlignRight)
 *  @param aAllowedToMoveInsertionPoint user can move cursor
 *  @param aCursorYesNo is cursor visible or not.
 *  @param aOverflowYesNo
 *  @param aIsResizeable is edwin resizeable (one line editor should use EFalse, in order to have proper scrolling)
 */
    IMPORT_C static void ConstructEditingL(CEikEdwin* aEdwin, 
                                              TInt aEditingSpace, 
                                              TInt aEditingWindow, 
                                              TInt aCharacterCase, 
                                              TInt aJustification, 
                                              TBool aAllowedToMoveInsertionPoint, 
                                              TBool aCursorYesNo, 
                                              TBool aOverflowYesNo,
                                              TBool aIsResizable);

    };

/** Automatic numbering for list items. (DEPRECATED)
 * Just create this kind of object and attach it to a listbox, and you'll
 * have automatic numbering. 
 *
 *
 * You'll need to call UpdateL() each time you modify the listbox's model!
 */
class CListBoxNumbers : public CBase
	{
public:
	IMPORT_C CListBoxNumbers(CEikTextListBox* aListBox);
	IMPORT_C void ConstructL();
	IMPORT_C void UpdateL();
private:
	CEikTextListBox* iListBox;
	};

class CAknListBoxFilterItems;

/** This class shows how application should build its model for filtered items. 
 *
 * Notice, application should not use this directly, if he has his own model or if there's
 * any special things needed for MatchableTextArray(). Application can derive from this though.
 *
 * All listboxes use CAknFilteredTextListBoxModel by default. CreateFilter call enables it.
 */
class CAknFilteredTextListBoxModel : public CTextListBoxModel, public MDesCArray
    {
public: // public interface for apps
    /**
     * Creates a CAknListBoxFilterItems and thus enables filtering of list items.
     */
    IMPORT_C void CreateFilterL(CEikListBox* aListBox, CAknSearchField* aSearchField);
    /**
     * Access function for the filter
     */
    IMPORT_C CAknListBoxFilterItems* Filter() const;
    /**
     * Destructor
     */
    IMPORT_C ~CAknFilteredTextListBoxModel();
public: // from CTextListBoxMode
    /**
     * Implementation of CTextListBoxModel::NumberOfItems()
     */
    IMPORT_C virtual TInt NumberOfItems() const;
    /**
     * Implementation of CTextListBoxModel::ItemText()
     */
    IMPORT_C virtual TPtrC ItemText(TInt aItemIndex) const;
public: // from MEikTextListBoxModel (default filtering string conversions)
    /**
     * Implementation of CTextListBoxModel::MatchableTextArray()
     */
    IMPORT_C const MDesCArray* MatchableTextArray() const;

private:
    CAknListBoxFilterItems* iFilter; // owned
private: // From MdesCArray (these implement default matchabletextarray for filtering.)
    IMPORT_C TInt MdcaCount() const;
    IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
private: // from MListBoxModel
	IMPORT_C virtual TAny* MListBoxModel_Reserved();
    };

/** Listbox item filtering
 *
 * This module has methods you need to call from your own model
 *
 * This class is designed to be stored inside a listbox model and the model should call this
 * in its NumberOfItems() and ItemText() implementation. The model must be given to this class
 * and it must have MatchableTextArray() implemented correctly.
 *
 * HandleOfferKeyEvent() should be called from the same offerkeyevent implementation which forwards the
 * keys to listbox and searchfield
 *
 * If you have both markable list and Find at the same time, you should call ResetFiltering() before
 * executing the command for marked items. This ensures that the ListBox's SelectionIndexes() returns
 * all items instead of only those items that are visible.
 *
 * This will modify list's SelectionIndexes() to move selected items when
 * list is filtered. All selected items can be found under 
 * CAknListBoxFilterItems::SelectionIndexes().
 * 
 */
class CAknListBoxFilterItems : public CBase, public MCoeControlObserver
    {
public:
    IMPORT_C CAknListBoxFilterItems(CEikListBox *aListBox, CAknSearchField *aSearchField, MListBoxModel *aModel, CListBoxView *aView);
    IMPORT_C void ConstructL(); // for setting empty list text.
    /** ResetFiltering
     *
     * To be called when filter is cleared
     */
    IMPORT_C void ResetFilteringL();
    /** 
     * The next one will update FilterItems state from the
     * searchfield and listbox.
     */
    IMPORT_C void UpdateCachedDataL(); // updates iOldSearchCriteria and selection indexes.
    IMPORT_C ~CAknListBoxFilterItems();    

public: 
    /** this one gives all indexes, not just the ones that are visible.
     */
    IMPORT_C CArrayFix<TInt> *SelectionIndexes();
    /** This will syncronize the selection indexes from the listbox.
	If you use SelectionIndexes(), call this before...

	This is heavy operation - goes through all list items. Need to be 
        called if listbox's SelectionIndexes might have changed...
     */
    IMPORT_C void UpdateSelectionIndexesL();
    IMPORT_C void UpdateSelectionIndexL(TInt aVisibleIndex);

public: // Applications should call this in their listbox model implementation
    /** FilteredNumberOfItems() is like MdcaCount(), it is used to ask how many list items
     *  are available after filter has been used. Counts visible list items.
     */
    IMPORT_C TInt FilteredNumberOfItems() const;
    /** FilteredItemIndex is like MdcaPoint(TInt). It is used to fetch the content of a list
     *  item after filter has been used. The content is indexes to the real list item array.
     *  Thus we return TInt from this.
     * @param aVisibleItemIndex the list item index. This counts the visible items only.
     * @return index to the original item array.
     */
    IMPORT_C TInt FilteredItemIndex(TInt aVisibleItemIndex) const;

public: // Needed to change the correct item.

    /** NonFilteredNumberOfItems() returns number of original list items.
     */
    IMPORT_C TInt NonFilteredNumberOfItems() const; // this always returns >= FilteredNumberOfItems()
    /** 
     * Finds the list item on the screen when the item array index is given.
     *
     * @param aOriginalIndex finds index of list item when item from the original array is given.
     *
     * VisibleItemIndex returns -1 if the aOriginalIndex is not visible.
     */
    IMPORT_C TInt VisibleItemIndex(TInt aOriginalIndex) const;
public: 
    /** For building MdcaPoint() of the model's MatchableTextArray.
     *
     *  This method builds the default value for MatchableTextArray.
     */
    IMPORT_C TPtrC DefaultMatchableItemFromItem(TPtrC aText);

public: 
    /** Applications should call this in offerkeyevent which gives keys to listbox and searchfield.
     */
    IMPORT_C void HandleOfferkeyEventL();
    /** 
     *	When you change the whole list item array, call this method to let find also know about the change.
     */
    IMPORT_C void HandleItemArrayChangeL();

public: // MCoeControlObserver
    /**
     * Gives ability to follow what events searchfield gives to find. Standard observer API.
     */
    IMPORT_C void SetObserver(MCoeControlObserver *aObserver);
    /**
     * Searchfield calls this method to inform about changes in find state.
     */
    IMPORT_C void HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType);

public: // For FEP
    /**
     * Sends key events to fep. This is used to resend key event to fep if AknFind's HandleOfferKeyEventL()
     * gets the key while searchfield has no focus. If searchfield has a focus, the key events go directly
     * to the editor and this is not called.
     *
     * NOTE, this method does only handle single key event at the time and it sends KEYDOWN, KEYEVENT and KEYUP 
     * events.
     */
    IMPORT_C void DeferredSendKeyEventToFepL(TUint aValue);
    /**
     * This does the actual sending of a key event. Does not support more than one event at the time.
     */
    static TInt IdleCallBack(TAny *aFilterItems);

public: // For size changed
    /**
     * AknFind uses this to inform us who is the parent control owning the listbox and searchfield.
     * This control should be window-owning control and it will be used to resize the listbox when
     * changes to the filtering happens.
     */
    IMPORT_C void SetParentControl(CCoeControl *aControl);
   /**
    * AknFind uses this to inform us that we have popup find. Applications shouldnt call this. 
    * Instead, you should use CAknSelectionListDialog or AknFind.
    */
    IMPORT_C void SetPopup();

public: // For detaching and attaching list, findbox, model and view...
	/**
	 * SetListBox attaches or detaches list used by the filtering
	 * @since 2.0
     * @param aListBox a pointer to listbox or NULL.
	 */
	IMPORT_C void SetListBox(CEikListBox *aListBox);
	/**
	 * SetSearchField attaches or detaches find pane used by the filtering
	 * @since 2.0
     * @param aSearchField a pointer to findbox or NULL.
	 */
	IMPORT_C void SetSearchField(CAknSearchField *aSearchField);
	/**
	 * SetModel attaches or detaches list model used by the filtering
	 * @since 2.0
     * @param aModel a pointer to list model or NULL.
	 */
	IMPORT_C void SetModel(MListBoxModel *aModel);
	/**
	 * SetView attaches or detaches list view used by the filtering
	 * @since 2.0
     * @param aModel a pointer to list view or NULL.
	 */
	IMPORT_C void SetView(CListBoxView *aView);

public:
    IMPORT_C CCoeControl *FindBox() const;

private:
    void NoCriteriaL(); // remove criteria completely.
    void TightenCriteriaL(const TDesC& aCriteria); // slow operation (do when adding new characters to search criteria)
    void ReleaseCriteriaL(const TDesC& aCriteria); // very slow operation (do when removing characters from search criteria)
    // EmptyListText handling
    void InstallEmptyTextL();
    void UninstallEmptyTextL();
    // Selections -- these methods form a pair, 
    // you must call Fetch first and then push.
    void FetchSelectionIndexesFromListBoxL();
    void PushSelectionIndexesToListBoxL();

    // HandleItemAddition without ResetFilteringL() call
    void HandleItemAdditionL();
    void HandleItemRemovalL();
private:
    TBool IsItemVisible(const TDesC& aMatchableItemString, const TDesC& aSearchText);
    static TBool IsSeparatorCharacter(TChar c);
    TBool IsItemSelected(TInt aRealIndex) const;
private:
    CArrayFix<TInt> *iShownIndexes; // own // uses non-filtered indexes
    CArrayFix<TInt> *iSelectionIndexes; // own   // this uses non-filtered indexes
    HBufC *iOldSearchCriteria; // own
    MListBoxModel *iModel;
    CListBoxView *iView;
    TInt iOldItemCount;
    HBufC* iEmptyListText; // own
    CEikListBox* iListBox;
    CAknSearchField* iSearchField;
    TBuf<256> iMatchableText;
    MCoeControlObserver *iObserver;
    CFindExtension *iExtension;
    TUint iKeyValue;
    CCoeControl *iParentControl;
    TBool iIsPopup;
    TBool iDisableChangesToShownIndexes;
    };


/** Removing optimization that breaks listbox views 
 * A view which removes optimization from CListBoxView which breaks with lists where all items are not
 * the same layout.
 * Use it like this: 
 *   CListBoxView* MakeViewClassInstanceL() { return new(ELeave) NoOptimizationView<CListBoxView>; }
 */
template<class T>
class NoOptimizationView : public T
    {
public:
    virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect)
	{
	// AVKON LAF
	if (this->RedrawDisabled())
		return;
	if (this->iTopItemIndex == aNewTopItemIndex)
		return;
	aMinRedrawRect.SetRect(this->iViewRect.iTl,this->iViewRect.Size());
	this->SetTopItemIndex(aNewTopItemIndex);
	this->Draw(&aMinRedrawRect);
	// end of AVKON LAF
	}
    };


/** This is private class, do not use it except for drawing controls!
 * 
 * Do not use it in applications.
 */


class AknLAFUtils 
	{
public:
	static void DrawLines(CGraphicsContext* aGc, 
			      const TRect& mainpane,
			      TInt x);
	IMPORT_C static void ReplaceColumn(TPtr aTarget, TDesC* aSource, TDesC* aReplacement, TChar aColumnSeparator, TInt aColumn);
	};


/**
 * Resource reader class
 *
 * This is utility class for reading listbox resouces.
 *
 * This should be derived from and it reads resource file for you.
 *
 * This seems to be only used by listbox resource readers. (Do not use it in applications)
 */
struct SAknLayoutGfx;
struct SAknLayoutText;
struct SAknLayoutCmd;
struct SAknLayoutGfx;
// Not for apps
struct SAknLayoutPos 
    {
    TInt l, t, r, b, W, H;

    typedef SAknLayoutPos ItemType;
    static void ReadResource(TResourceReader& aReader, ItemType& aTarget);    
    };
template<class T> class CArrayReader;
class CAknGenericReader : public CBase
    {
public:
    IMPORT_C void ConstructL(TInt aResourceId);
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
    IMPORT_C ~CAknGenericReader();

    IMPORT_C const SAknLayoutGfx* GfxItem(TInt aIndex) const;
    IMPORT_C const SAknLayoutText* TextItem(TInt aIndex) const;
    IMPORT_C const SAknLayoutCmd* CmdItem(TInt aIndex) const;
    IMPORT_C const SAknLayoutGfx* AreaItem(TInt aIndex) const;

    CArrayReader<SAknLayoutGfx>* iGfx;
    CArrayReader<SAknLayoutText>* iText;
    CArrayReader<SAknLayoutCmd>* iCmd;
    CArrayReader<SAknLayoutGfx>* iArea;
    };



// Use this to mark that the position in LAF specification is empty.
const TInt AknLayoutUtilsNoValue = ELayoutEmpty;

/** Utility classes to build layout based on European LAF from resource files. (can be used by applications)
 *
 * Methods in this class are designed to be called from your control's SizeChanged() method!
 *
 * This class knows the specification's coordinate data format and ensures that different types of
 * controls are positioned and setup correctly according to European LAF. 
 * 
 * This class helps you with positioning labels, controls, rects and other things to according to LAF specification.
 * (It is NOT trivial to get it correct and this adjusts easily to changes in the LAF specification - if you're not
 * using this, remember to read the whole LAF specification - especially the beginning and the end with color and
 * especially how text margins and widths interact!!)
 *
 * (idea of this class is that when specification of one component changes, only resource file needs to be changed and when you 
 * get new product with new specification format, only this module needs to be changed and resources rewritten from the specification. 
 * And when component's specification changes, only the component need to be changed (usually only change is what components are
 * inside it and how it calls this module.).. => all controls have common format that decides its layout!
 *
 * Parent rectangles are always coordinates of LAF specification's parent rectangle in the screen.
 * 
 * To use this, call one of the methods in your SizeChanged() and then you'll need to make sure you
 * draw the area between controls using ClearBetweenRects() call from egul library. (CCoeControl::Rect() helps with that...)
 *
 * A Tip: You do not want to use any dynamic calculation of layouts! It is almost always an error to do so!
 *        => Do not allow layouts that have not been specified!
 *
 * (If LAF spec has many numbers and you need to dynamically choose between them, then keep the numbers in
 * code as function-local using SAknLayoutText/SAknLayoutRect/... -structs..)
 *
 * You'll want to use TAknLayoutRect and TAknLayoutText too to build layout
 * for your custom controls.
 */
class AknLayoutUtils
    {
public:

    struct SAknLayoutText
	{
	TInt iFont, iC, iL, iR, iB, iW, iJ;
	};
    struct SAknLayoutTextMultiline
	{
	TInt iFont, iC, iL, iR, iB, iW, iJ, iNumberOfLinesShown, iNextLineB;
	};
    typedef SAknLayoutTextMultiline SAknLayoutLabel;
    typedef SAknLayoutTextMultiline SAknLayoutEdwin;
    typedef SAknLayoutText SAknLayoutMfne;
    typedef SAknLayoutText SAknLayoutSecEd;
    struct SAknLayoutRect
	{
	TInt iC, iL, iT, iR, iB, iW, iH;
	};
    typedef SAknLayoutRect SAknLayoutControl;
    typedef SAknLayoutRect SAknLayoutImage;

    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, TInt aResourceId, const CFont* aCustomFont=0);
    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, TResourceReader& aReader, const CFont* aCustomFont=0);
    /** Layouts a label via a structure of layout parameters
	@param aLayout   the structure
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, const SAknLayoutLabel& aLayout, const CFont *aCustomFont=0);
    /** Layouts a label via a layout compiler output
	@param aLayout   a define from aknlayout.lag file
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, const TAknMultiLineTextLayout& aLayout, const CFont *aCustomFont=0);
    /** Layouts a label via a layout compiler output
	@param aLayout   a define from aknlayout.lag file
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, const TAknTextLineLayout& aLayout, const CFont *aCustomFont=0);
    /** Layouts a label via parameters from the specification
	@param aLayout   a define from aknlayout.lag file
	@param font      font id, ELatinPlain12, ELatinBold12, ELatinBold13, ELatinBold17, ELatinBold19 etc..
	@param C         colour index, 0..255
	@param l         left margin
	@param r         right margin
	@param B         Baseline from top of the parent rectangle
	@param W         text width in pixels
	@param J         justification. ELayoutAlignNone; ELayoutAlignCenter; ELayoutAlignLeft; ELayoutAlignRight; ELayoutAlignBidi
	@param NextLineB baseline of 2nd line for multi-line labels/editors
	@param aCustomFont   a font used, if resource file uses EFontCustom
     */
    IMPORT_C static void LayoutLabel(CEikLabel* aLabel, const TRect& aLabelParent, TInt font, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J, TInt NextLineB=0, const CFont* aCustomFont=0);

    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, TInt aResourceId, TInt aNumberOfLines = 0, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, TResourceReader& aReader, TInt aNumberOfLines = 0, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);

    /** Layouts an editor via a structure of layout parameters
	@param aLayout   the structure
     */
    IMPORT_C static void LayoutEdwin(CEikEdwin* aEdwin, const TRect& aEdwinParent, const SAknLayoutEdwin& aLayout, const CFont* aCustomFont=0, TBool aMinimizeEdwinView=EFalse);
    /** Layouts an editor via a structure of layout parameters
	@param aLayout   the structure
     */

    IMPORT_C static void LayoutEdwin( CEikEdwin* aEdwin,
                                      const TRect& aEdwinParent,
                                      const TAknMultiLineTextLayout& aLayout,
                                      const CFont* aCustomFont=0,
                                      TBool aMinimizeEdwinView=EFalse);

    IMPORT_C static void LayoutEdwin( CEikEdwin* aEdwin,
                                      const TRect& aEdwinParent,
                                      const TAknMultiLineTextLayout& aLayout,
                                      TAknsQsnTextColorsIndex aOverrideColor,
                                      const CFont* aCustomFont=0,
                                      TBool aMinimizeEdwinView=EFalse ); 
        


    IMPORT_C static void LayoutEdwin( CEikEdwin* aEdwin,
                                      const TRect& aEdwinParent,
                                      const TAknTextLineLayout& aLayout,
                                      const CFont* aCustomFont=0,
                                      TBool aMinimizeEdwinView=EFalse );

    IMPORT_C static void LayoutEdwin( CEikEdwin* aEdwin,
                                      const TRect& aEdwinParent,
                                      const TAknTextLineLayout& aLayout,
                                      TAknsQsnTextColorsIndex aOverrideColor,
                                      const CFont* aCustomFont=0,
                                      TBool aMinimizeEdwinView=EFalse );
        
    /** Layouts an editor via parameters from the specification
	@param aLayout   a define from aknlayout.lag file
	@param font      font id, ELatinPlain12, ELatinBold12, ELatinBold13, ELatinBold17, ELatinBold19 etc..
	@param C         colour index, 0..255
	@param l         left margin
	@param r         right margin
	@param B         Baseline from top of the parent rectangle
	@param W         text width in pixels
	@param J         justification. ELayoutAlignNone; ELayoutAlignCenter; ELayoutAlignLeft; ELayoutAlignRight; ELayoutAlignBidi
	@param aNumberOfLinesShown number of lines visible for the editor
	@param NextLineB baseline of 2nd line for multi-line labels/editors
	@param aMinimizeEdwinView whether to use minimum size. You need to use MinimizedEdwinRect() if you use ETrue here.
     */
    IMPORT_C static void LayoutEdwin( CEikEdwin* aEdwin,
                                      const TRect& aEdwinParent,
                                      TInt font,
                                      TInt C,
                                      TInt l,
                                      TInt r,
                                      TInt B,
                                      TInt W,
                                      TInt J,
                                      TInt aNumberOfLinesShown,
                                      TInt aNextLineBaseline,
                                      const CFont* aCustomFont=0 ,
                                      TBool aMinimizeEdwinView=EFalse );

    IMPORT_C static void LayoutEdwin( CEikEdwin* aEdwin,
                                      const TRect& aEdwinParent,
                                      TInt font,
                                      TInt C,
                                      TInt l,
                                      TInt r,
                                      TInt B,
                                      TInt W,
                                      TInt J,
                                      TInt aNumberOfLinesShown,
                                      TInt aNextLineBaseline,
                                      TAknsQsnTextColorsIndex aOverrideColor,
                                      const CFont* aCustomFont=0 ,
                                      TBool aMinimizeEdwinView=EFalse );
    /** Use this, if you give aMinimizeEdwinView to LayoutEdwin as true.
     * The edwin will not draw the whole rectangle allocated for the control.
     */
    IMPORT_C static TRect MinimizedEdwinRect(const CEikEdwin *aEdwin);


    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, TInt aResourceId);
    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, TResourceReader& aReader);

    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, const SAknLayoutMfne& aLayout);
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, const TAknTextLineLayout& aLayout);
    IMPORT_C static void LayoutMfne(CEikMfne* aMfne, const TRect& aMfneParent, TInt font, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J);

    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, TInt aResourceId);
    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, TResourceReader& aReader);

    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, const SAknLayoutControl& aLayout);
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);
    IMPORT_C static void LayoutControl(CCoeControl* aControl, const TRect& aControlParent, TInt /*C*/, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);

    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, TInt aResourceId);
    /**
    * Deprecated! Do not use!
    */    
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, TResourceReader& aReader);

    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, const SAknLayoutControl& aLayout);
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, const TAknWindowLineLayout& aLayout);
    IMPORT_C static void LayoutImage(CEikImage* aImage, const TRect& aParent, TInt C, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);

    /** Sets CEikSecretEditor's position, colors and fonts based on LAF specification
     *
     */
    IMPORT_C static void LayoutSecretEditor(CEikSecretEditor* aSecEd, const TRect& aParent, const SAknLayoutText& aLayout);
    IMPORT_C static void LayoutSecretEditor(CEikSecretEditor* aSecEd, const TRect& aParent, const TAknTextLineLayout& aLayout);

public:
    /** Different conversions
     * Fonts: ELatinPlain12, ELatinBold12, ELatinBold13, ELatinBold17, ELatinBold19, ENumberPlain5, EClockBold30, ELatinClock14, EFontCustom
     *        EAknLogicalFontPrimaryFont, EAknLogicalFontSecondaryFont, EAknLogicalFontTitleFont,
     * Alignments: ELayoutAlignNone, ELayoutAlignCenter, ELayoutAlignLeft, ELayoutAlignRight, ELayoutAlignBidi with these..
     */
    IMPORT_C static TRect TextRectFromCoords(const TRect& aParent, const CFont* aFont, TInt l, TInt r, TInt B, TInt W, TInt LB = 0);
    IMPORT_C static TRect RectFromCoords(const TRect& aParent, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);

    /**
    * Method to return a useable system font reference from a Series 60 font enumeration from among
    * the supported list.
    * 
    * This method should only be used if application code needs to render its own graphics. That is, it
    * is not using Series 60 controls and furthermore not using the recommended methods 
    * AknLayoutUtils::LayoutEdwin(), AknLayoutUtils::LayoutLabel() or AknLayoutUtils::LayoutSecretEditor(). 
    * 
    * Fonts returned by this are not recommended to be stored in clients' member data, but should be
    * accessed when they are required for use.
    *
    * Applications that are written to run with their layout dynamically adapting to different screen sizes 
    * should use only the values found in the Series 60 logical font enumeration, TAknLogicalFontId.
    * 
    * @param aFontId        Input Series 60 font id.
    * @param aCustomFont    Font to return if aFontId is given as EFontCustom
    * @return               const pointer to a system font, or aCustomFont
    */
    IMPORT_C static const CFont* FontFromId(TInt aFontId, const CFont* aCustomFont=0);

    /**
    * Method to return a system font reference from a Series 60 font id. This will always conform to type CAknLayoutFont
    * 
    * This method should only be used if application code needs to render its own graphics. That is, it
    * is not using Series 60 controls and furthermore not using the recommended methods 
    * AknLayoutUtils::LayoutEdwin(), AknLayoutUtils::LayoutLabel() or AknLayoutUtils::LayoutSecretEditor(). 
    * 
    * Fonts returned by this are not recommended to be stored in clients' member data, but should be
    * accessed when they are required for use.
    *
    * Applications that are written to run with their layout dynamically adapting to different screen sizes 
    * should use only the values found in the Series 60 logical font enumeration, TAknLogicalFontId.
    * 
    * @param aFontId        Input Series 60 font id.
    * @param aCustomFont    Font to return if aFontId is given as EFontCustom
    * @return               const pointer to a system font, or aCustomFont
    */
    IMPORT_C static const CAknLayoutFont* LayoutFontFromId(TInt aId, const CAknLayoutFont *aCustomFont = 0);

    /**
    * Deprecated! Do not use!
    */
    IMPORT_C static const CFont* FontFromName(const TDesC& aName); 

	IMPORT_C static CGraphicsContext::TTextAlign TextAlignFromId(TInt aId);
    IMPORT_C static TGulAlignment GulAlignFromId(TInt aId);

	IMPORT_C static TInt CursorHeightFromFont(const TFontSpec& aFont);
	IMPORT_C static TInt CursorWidthFromFont (const TFontSpec& aFont);
	IMPORT_C static TInt CursorAscentFromFont(const TFontSpec& aFont);
	IMPORT_C static void CursorExtensionsFromFont(const TFontSpec& /*aFont*/, TInt& aFirstExtension, TInt& aSecondExtension);

	IMPORT_C static TInt HighlightLeftPixelsFromFont (const TFontSpec& aFont);
	IMPORT_C static TInt HighlightRightPixelsFromFont(const TFontSpec& aFont);
    static void HighlightExtensionsFromFont(const TInt fontid, TInt& aLeft, TInt& aRight, TInt&  aTop, TInt& aBottom);

    /**
    * Access the system font array to see if there is a font that matches the  
    * font specification presented in Twips. Device map is also passed in case the 
    * system font array has fonts from different devices.
    * 
    * A null return value means that the system font array is not constructed yet, or does
    * not contain a font that has the same TFontSpec or device map.
    *
    **/
    static const CAknLayoutFont* MatchFontFromSystemFontArray( 
        const TFontSpec& aSpec, MGraphicsDeviceMap* aMap );

	IMPORT_C static TBool LayoutMirrored();

    /*
    * This method returns build variant based on which flag is active,
    * __AVKON_ELAF__ or __AVKON_APAC__.
    *
    * If you need to decide which layout to use, do not do it based on this method.
    * Instead, use CAknEnv::GetCurrentLayoutId().
    *
    * @return current variant
    */
	IMPORT_C static EVariantFlag Variant();

    /*
    * Don't use this method, instead use the above one.
    *
    * @deprecated
    *
    * @return current variant
    */
	IMPORT_C static EVariantFlag Variant( CEikonEnv& aEnv );

    IMPORT_C static ESubVariantFlag SubVariant();

	IMPORT_C static void OverrideControlColorL(CCoeControl& aControl, TLogicalColor aLogicalColor, TRgb aColor);
    
    /*
    * This method returns the default scrollbar type for the given application. 
    * For non-layout aware applications (e.g. legacy apps designed for 176x208 screen) 
    * this method returns always EArrowHead. But for layout aware apps the returned type 
    * may vary depending on the type of scrollbar which has been set as preferred 
    * scrollbar type in the device.
    *
    * Note that applications may use freely whatever scrollbartype, this method only 
    * returns the default scrollbartype for the application.
    * 
    * @since  2.6
    * @param  aApplication Application of which default scrollbar type is requested.
    * @return Default scrollbar type for the given application
    */
    IMPORT_C static CEikScrollBarFrame::TScrollBarType DefaultScrollBarType(CEikAppUi* aApplication);

    /*
    * This method sets the layout for vertical scrollbar of the given scrollbar frame. Layout
    * can freely only be set for EDoubleSpan type scrollbars.
    * 
    * @since  2.6
    * @param  aScrollBarFrame   Scrollbarframe of which vertical scrollbar layout will be set.
    * @param  aControlParent    Rect of the parent control of the scrollbarframe.
    * @param  aLayout           Layout for the vertical scrollbar.
    *
    *
    * This method can also be useful when layout of the scrollbar needs to be changed for scrollbars
    * which are owned by some other components such as e.g. ListBoxes, Editors or Grids.
    *
    * Example of use:
    *
    *  // Get a pointer to scrollbarframe of the listbox
    *  CEikScrollBarFrame* frame = iListBox->ScrollBar();
    *  
    *  // Get the layout data
    *  TAknWindowLineLayout layout = GetMyListBoxLayout();
    *  Trect parentRect = GetMyListBoxParentRect();
    *
    *  // Set the layout
    *  AknLayoutUtils::LayoutVerticalScrollBar(frame, parentRect, layout);
    *
    *  // The layout for scrollbar is now set.
    *
    */
    IMPORT_C static void LayoutVerticalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);

    /*
    * This method sets the layout for horizontal scrollbar of the given scrollbar frame. Layout
    * can freely only be set for EDoubleSpan type scrollbars.
    * 
    * @since  2.6
    * @param  aScrollBarFrame   Scrollbarframe of which horizontal scrollbar layout will be set.
    * @param  aControlParent    Rect of the parent control of the scrollbarframe.
    * @param  aLayout           Layout for the horizontal scrollbar.
    *
    *
    * Usage of this method is similar as for LayoutVerticalScrollBar().
    *
    */
    IMPORT_C static void LayoutHorizontalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);

public:   // Metrics API
	enum TAknLayoutMetrics
		{
		EScreen,
		EApplicationWindow,
		EStatusPane,
		EMainPane,
		EControlPane,
		ESignalPane,
		EContextPane,
		ETitlePane,
		EBatteryPane,
		EUniversalIndicatorPane,
		ENaviPane,
		EFindPane,
		EWallpaperPane,
		EIndicatorPane,
		EAColunm,
		EBColunm,
		ECColunm,
		EDColunm,
		EStaconTop,
		EStaconBottom,
		EStatusPaneBottom,
		EControlPaneBottom,
		EControlPaneTop = EControlPane,
		EStatusPaneTop = EStatusPane
		};


	/**
	* Fills given TRect with rectangle for given layout component. 
	* Returns EFalse for status pane descendants if requested
	* layout component is not available in current layout. For
	* other components returns always ETrue (returned rectangle is
	* from layout definition).
	*
	* @since  2.8
	* @param  aParam   Layout component to be queried. 
	* @param  aRect    Resulting rectangle.
	* @param  ETrue    If requested value was available.
	*         EFalse   Otherwise.
	*/
    IMPORT_C static TBool LayoutMetricsRect(TAknLayoutMetrics aParam, TRect& aRect);

	/**
	* This method returns size of rectangle for given layout component.
	* Returns EFalse for status pane descendants if requested
	* layout component is not available in current layout. For
	* other components returns always ETrue (returned size is
	* from layout definition).
	*
	* @since  2.8
	* @param  aParam   Layout component to be queried. 
	* @param  aSize    Resulting size.
	* @param  ETrue    If requested value was available.
	*         EFalse   Otherwise.
	*/
    IMPORT_C static TBool LayoutMetricsSize(TAknLayoutMetrics aParam, TSize& aSize);

	/**
	* This method returns position of top left corner for given layout component.
	* Returns EFalse for status pane descendants if requested
	* layout component is not available in current layout. For
	* other components returns always ETrue (returned position is
	* from layout definition).
	*
	* @since  2.8
	* @param  aParam   Layout component to be queried. 
	* @param  aPos     Resulting position.
	* @param  ETrue    If requested value was available.
	*         EFalse   Otherwise.
	*/
	IMPORT_C static TBool LayoutMetricsPosition(TAknLayoutMetrics aParan, TPoint& aPos);
public:
	/**
	* This method returns a new value for a baseline, based upon a value for bottom and 
    * a value for height. For legacy layout data, the baseline will be correct, and this
    * method will detect that it is a legacy font id and just return aBottom. 
    * However, for scalable layout data, the bottom value will be hidden inside 
    * the old baseline variable, so call this method passing in 'iB', NOT passing in 'ib'
    * ... e.g.: (the following line is an example, so is ok to have commented out code)
    * TInt newbaseline = CorrectBaseline(myLayoutLine.iB, myLayoutLine.iFont);
	*
	* @since  2.8
	* @param  aBottom  Baseline or Bottom value of text pane (found in TAknTextLineLayout.iB)
	* @param  aFontId     FontId of text pane (for scalable layouts, this will encode the height)
    * @return   new Baseline value
	*/
	static TInt CorrectBaseline(TInt aParentHeight, TInt aBaseline, TInt aFontId);

    /**
	* This method tells if the scalable layout interface is available.
    * 
	* @internal
    * @return ETrue if scalable layout interface can be used, otherwise EFalse.
	*/
	IMPORT_C static TBool ScalableLayoutInterfaceAvailable();

};

/** Low level drawing based on European LAF document (can be used by application's custom controls)
 *
 * This class reads AVKON_LAYOUT_TEXT resources
 */
class TAknLayoutText
    {
public:
    IMPORT_C TAknLayoutText();
    /** Read resources and calculate information needed to draw text.
     *
     * LayoutText() call should be placed to control's SizeChanged() method.
     */
    IMPORT_C void LayoutText(const TRect& aParent, TInt aResourceId, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, TResourceReader& aReader, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, const AknLayoutUtils::SAknLayoutText& aLayout, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, const TAknTextLineLayout& aLayout, const CFont* aCustomFont=0);
    IMPORT_C void LayoutText(const TRect& aParent, TInt fontid, TInt C, TInt l, TInt r, TInt B, TInt W, TInt J, const CFont* aCustomFont=0);

    /** Do the actual drawing, should be placed to control's Draw() method.
     */
    IMPORT_C void DrawText(CGraphicsContext& aGc, const TDesC& aText) const;
    
    /**
    * In case of bidirectional text, which is already converted from logical to
    * visual order, use this method with parameter 
    * aUseLogicalToVisualConversion EFalse.
    */
    IMPORT_C void DrawText(
        CGraphicsContext& aGc,
        const TDesC& aText,
        TBool aUseLogicalToVisualConversion ) const;

    IMPORT_C void DrawText(
        CGraphicsContext& aGc,
        const TDesC& aText,
        TBool aUseLogicalToVisualConversion,
        const TRgb &aColor) const;
                           

public:
    /** This returns rectangle that is used to draw the text.
     *
     * This allows you to divide screen space for egul's TextUtils::ClearBetweenRect()
     * without knowing exact coordinates => when coordinates change, your code does not need to change.
     */
    IMPORT_C TRect TextRect() const;
    const CFont *Font() const { return iFont; }
    TRgb Color() const { return AKN_LAF_COLOR_STATIC(iColor); }
    CGraphicsContext::TTextAlign Align() const { return iAlign; }
private:
    TRect iTextRect;
    const CFont *iFont; // not owned..
    TInt iColor;
    TInt iOffset;
    CGraphicsContext::TTextAlign iAlign;
    friend class CBubbleOutlookNumberEntry;
    };

/** Low level rectangle management based on European LAF document (can be used by application's custom controls)
 * 
 * This allows you to draw images, rectangles, lines or just calculate rectangles based on LAF spec.
 *
 * This class reads AVKON_LAYOUT_RECT resources.
 *
 * Instances of this class should be placed inside controls for reading low level layout from resources.
 */
class TAknLayoutRect
    {    
public:
    IMPORT_C TAknLayoutRect();
    /** LayoutRect should be called from control's SizeChanged() method.
     */
    IMPORT_C void LayoutRect(const TRect &aParent, TInt aResourceId);
    IMPORT_C void LayoutRect(const TRect &aParent, TResourceReader &aReader);
    IMPORT_C void LayoutRect(const TRect &aParent, const AknLayoutUtils::SAknLayoutRect &aLayout);
    IMPORT_C void LayoutRect(const TRect &aParent, const TAknWindowLineLayout &aLayout);
    IMPORT_C void LayoutRect(const TRect &aParent, TInt C, TInt l, TInt t, TInt r, TInt b, TInt W, TInt H);
    
    /** Color() can be called from control's Draw() method. 
	
	DO NOT CALL it in SizeChanged(), ConstructL() or ActivateL() method, because 
	it messes up color scheme changes. Especially if you're using colors 226-248.
	If you store color values, be prepared to update TRgb's you store when color
	palette is changed! Best thing to do is to make your Draw() methods call
	AKN_LAF_COLOR().
     */    
    IMPORT_C TRgb Color() const;
    /** Rect() can be called from control's Draw() or in SizeChanged() as input for some other table's layout code.
     */
    IMPORT_C TRect Rect() const;
	TBool Valid() const;

    /** DrawRect() and DrawImage() should be called from control's Draw() method.
     */
    IMPORT_C void DrawRect(CWindowGc& aGc) const;
    IMPORT_C void DrawOutLineRect(CWindowGc& aGc) const;
    IMPORT_C void DrawImage(CBitmapContext& aGc, CFbsBitmap* aBitmap, CFbsBitmap* aMask) const;
private:
    TInt iColor;
    TRect iRect;
    };

/**
 * Helper functions for drawing empty lists and window shadows
 */
class AknDraw 
    {
public:
    /** 
	Draws standard empty list
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyList(const TRect& aRect, CWindowGc& aGc, TPtrC aText);
    /** 
	Draws empty list for setting item editing
	@param aRect the rectangle of setting page's content
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListForSettingPage(const TRect &aRect, CWindowGc &aGc, TPtrC text); // only for setting page with empty layout.
    /** 
	Draws empty list for lists with find
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListWithFind(const TRect& aClientRect, CWindowGc& aGc, TPtrC aText); // only for fixed find pane used with single graphics listbox..
    /** 
	Draws empty list for lists with heading
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListHeading(const TRect &aClientRect, CWindowGc& aGc, TPtrC aText); // only heading style lists.
    // The following is optimization for drawing window shadows.
    /** 
	Draws a window shadow
	@param aCoverRect the area covered by the shadow
	@param aSecondShadowRect the area used for second shadow
	@param aFirstShadowRect  the area of first shadow
	@param aOutliineFrameRect the area of black outline frame
	@param aInsideAreaRect   the area of content inside the window
     */
    IMPORT_C static void DrawWindowShadow(CWindowGc& aGc, const TAknLayoutRect& aCoverRect, const TAknLayoutRect& aSecondShadowRect, const TAknLayoutRect& aFirstShadowRect, const TAknLayoutRect& aOutlineFrameRect, const TAknLayoutRect& aInsideAreaRect);
public:

    /** 
	The main implementation routine for empty list drawing.
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
	@param aLayoutLine1 Resource id of AVKON_LAYOUT_TEXT for first line layout 
	@param aLayoutLine2 Resource id of AVKON_LAYOUT_TEXT for second line layout 
     */
    IMPORT_C static void DrawEmptyListImpl(const TRect& aRect, CWindowGc& aGc, TPtrC aText, TInt aLayoutLine1, TInt aLayoutLine2);
    
    };

/**
 * Helper functions for drawing empty lists and window shadows
 */
class AknDrawWithSkins
    {
public:
    /** 
	Draws standard empty list
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyList(const TRect& aRect, CWindowGc& aGc, TPtrC aText, CCoeControl *aControl);
    /** 
	Draws empty list for setting item editing
	@param aRect the rectangle of setting page's content
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListForSettingPage(const TRect &aRect, CWindowGc &aGc, TPtrC text, CCoeControl *aControl); // only for setting page with empty layout.
    /** 
	Draws empty list for lists with find
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListWithFind(const TRect& aClientRect, CWindowGc& aGc, TPtrC aText, CCoeControl *aControl); // only for fixed find pane used with single graphics listbox..
    /** 
	Draws empty list for lists with heading
	@param aRect the client rectangle
	@param aGc   the graphics context
	@param aText text for empty list in format "Line1\nLine2"
     */
    IMPORT_C static void DrawEmptyListHeading(const TRect &aClientRect, CWindowGc& aGc, TPtrC aText, CCoeControl *aControl); // only heading style lists.
    // The following is optimization for drawing window shadows.
    /** 
	Draws a window shadow
	@param aCoverRect the area covered by the shadow
	@param aSecondShadowRect the area used for second shadow
	@param aFirstShadowRect  the area of first shadow
	@param aOutliineFrameRect the area of black outline frame
	@param aInsideAreaRect   the area of content inside the window
     */
    IMPORT_C static void DrawWindowShadow(CWindowGc& aGc, const TAknLayoutRect& aCoverRect, const TAknLayoutRect& aSecondShadowRect, const TAknLayoutRect& aFirstShadowRect, const TAknLayoutRect& aOutlineFrameRect, const TAknLayoutRect& aInsideAreaRect, CCoeControl *aControl);
    
    };




// Browser and calculator fonts will not be placed here. Application
// can use them themselves with CEikonEnv::Static()->Font() call.
IMPORT_C const CFont *LatinPlain12();
IMPORT_C const CFont *LatinBold12();
IMPORT_C const CFont *LatinBold13();
IMPORT_C const CFont *LatinBold16(); // since 2.0
IMPORT_C const CFont *LatinBold17();
IMPORT_C const CFont *LatinBold19(); 
IMPORT_C const CFont *NumberPlain5();
IMPORT_C const CFont *ClockBold30();
IMPORT_C const CFont *LatinClock14();
const CFont *CalcBold21();
const CFont *CalcOperBold21();
const CFont *CalcOperBold13();



IMPORT_C const CFont *ApacPlain12();
IMPORT_C const CFont *ApacPlain16();


/**
* CompletePathWithAppPath
*   All the components that are specified in the given descriptor (drive letter,
*   path and file name, including extension) are put into the result;
*   any missing components (path and drive letter) are taken from the app's path.
*
*   Can be used e.g. to load a bitmap file when an application don't know where
*   it has been installed.
*
*   Example1:
*        TFilename fname = _L("\testdir\pics.mbm"); // Use _LIT instead
*        CompletePathWithAppPath( fname );
*        Result:
*            fname == "c:\testdir\pics.mbm" if application was installed to c:
*
*   Example2:
*        TFilename fname = _L("pics.mbm"); // Use _LIT instead
*        CompletePathWithAppPath( fname );
*        Result:
*            fname == "c:\system\apps\myapp\pics.mbm" if application was 
*                installed to c:\system\apps\myapp
*
* @param    aFileName   FileName which will be completed with application's path
* @return   Error code if an error occured. In case of an error aFileName will
*               not be changed
*/
IMPORT_C TInt CompleteWithAppPath( TDes& aFileName );

/**
 * Test whether the value falls within the parent relative range
 * as defined in AknLayout2Def.h
 *
 * @since 2.8
 * @param aVal value
 * @return ETrue if value is within the parent relative range, EFalse otherwise
 */
TBool IsParentRelative(TInt aVal);

#endif //  __AKNUTILS_H__

// End of file









