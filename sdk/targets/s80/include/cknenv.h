/*
* =============================================================================
*  Name        : cknenv.h
*  Part of     : CKON / CKNCORE
*  Interface   : 
*  Description : CKON core environment
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
* =============================================================================
*/


#ifndef CKNENV_H
#define CKNENV_H

//** INCLUDES *
#include <e32def.h>
#include <gulbordr.h>
#include <skin.h>
#include <CknObjectType.h>
#include <bamdesca.h>
#include <APMSTD.H>
#include <SkinRegionType.h>

//** CONSTANTS *
/** 
 * uniform resource locator; to be used with <code>FindActionableText()</code>
 * and <code>ActionText()</code> 
 */
const TInt KUidActionTextUrlValue =0x101F57bf;
/** the UID for URL actionable text */
const TUid KUidActionTextUrl={KUidActionTextUrlValue};
/** 
 * telephone number. To be used with <code>FindActionableText()</code> and 
 * <code>ActionText()</code> 
 */
const TInt KUidActionTextTelephoneNumberValue =0x101F57c0;
/** the UID for telephone number actionable text  */
const TUid KUidActionTextTelephoneNumber={KUidActionTextTelephoneNumberValue};
/** 
 * email address. To be used with <code>FindActionableText()</code> and 
 * <code>ActionText()</code> 
 */
const TInt KUidActionTextEmailAddressValue =0x101F57c1;
/** the UID for email address actionable address */
const TUid KUidActionTextEmailAddress={KUidActionTextEmailAddressValue};
/** ellipsis character. Used by <code>ClipToFit()</code> */
const TUint KCknEnvClipEndChar=0x2026;

//** FORWARD DECLARATIONS *
class CApaMaskedBitmap;
class CEikDialog;
class MCknButtonDimmedObserver;

/**
* The <code>CknEnv</code> class provides the Ckon core library.
*
* @lib ckncore.lib
* @since Series90 1.0
*/
class CknEnv
    {
public:
    /**
    * Returns the skin manager.
    * Use of this method assumes the skin manager exists. If it does not
    * exist, <code>NULL</code> is returned.
    *
    * @return a reference to the skin manager
    * @remarks
    * @see <code>CCknSkinBase</code> in skin.h
    */
    IMPORT_C static CCknSkinBase& Skin();

    /**
    * Returns the skin manager or <code>NULL</code> if the skin manager has 
    * been destroyed
    *
    * @return a pointer to the skin manager
    * @remarks
    * @see <code>CCknSkinBase</code> in skin.h
    */
    IMPORT_C static CCknSkinBase* SkinOrNull();

    /**
    * Returns the default application icon.
    * This method creates a new masked bitmap based on the one in the .aif file
    * whose size is closest to the size specified.
    * If all bitmaps in the file are larger than the size specified, the new bitmap 
    * is based on the smallest and is shrunk to the specified size.
    *
    * @param aSize The size of the bitmap to create, in pixels
    * @return a pointer to the new bitmap
    * @remarks
    * @see <code>CApaMaskedBitmap</code> in apgicnfl.h
    */
    IMPORT_C static CApaMaskedBitmap* DefaultAppBitmapL(TInt aSize);

    /**
    * Sets the toolbar size and position according to whether the command
    * bar is shown or not. If <code>aView</code> is <code>NULL</code>, the 
    * ordinal position of the toolbar is set to zero. Otherwise, the ordinal 
    * position of the toolbar is set to the ordinal position of 
    * <code>aView</code>. The caller must first set the AppView type before
    * calling this method - that is, 
    * <code>SetAppViewType(ESkinAppViewWithCbaNoToolband)</code>
    * from the skin manager.
    *
    * @param aToolband The pointer to the toolbar
    * @param aView If passed in, the view that the ordinal position of the
    *              toolbar will be set to
    * @remarks
    * @see <code>TSkinAppView</code> in skin.h
    */
    IMPORT_C static void SetToolbandSizeAndPosition(CEikToolBar* aToolband, const CCoeControl* aView=NULL);

    /**
    * Searches within a descriptor for actionable text, such as, telephone 
    * numbers, URLs, and email addresses, and returns the position and length 
    * of the first occurrence. If no actionable text is
    * found or if there is an error, it returns a length of zero.
    *
    * @param aPieceOfText The descriptor to be searched
    * @param aPos Specifies the search start index within the descriptor. 
    *             If actionable text is found, it returns the start index
    *             of the actionable text
    * @param aLen Specifies the number of characters to search. If 
    *             actionable text is found, it returns the length of the 
    *             actionable text. If no actionable text is found it is set
    *             to 0
    * @param aType Specifies the type of actionable text to find, for example,
    *              <code>KUidActionTextUrl</code>. If the UID is not 
    *              recognized, that is, if a UID is <code>0</code>, all types 
    *              are searched for, with the first type to occur taking 
    *              priority. If actionable text is found, it returns the type 
    *              found
    * @remarks
    * @see See this class's constants
    */
    IMPORT_C static void FindActionableText(const TDesC& aPieceOfText, TInt& aPos, TInt& aLen, TUid& aType);

    /**
    * Actions the selected text.
    *
    * @param aPieceOfActionableText The text to be actioned
    * @param aType The type of text, for example, <code>KUidActionTextUrl</code>
    * @remarks
    * @see See this class's constants
    */
    IMPORT_C static void ActionText(const TDesC& aPieceOfActionableText, TUid aType);

    /**
    * Formats a string containing a single <code>%s</code> ensuring that the 
    * resulting formatted string does not exceed the required maximum width, in 
    * pixels (taking into account whether the format string is multi-line). 
    * This method also ensures the resulting length is not greater than the 
    * maximum length.
    *
    * @param aFrmStr The format string (containing a single <code>%s</code>)
    * @param aText The text to be placed in the format string
    * @param aFont The font to be used
    * @param aMaxWidthInPixels The maximum allowable width of the 
    *                          string, in pixels 
    * @param aMaxLengthInChars Maximum allowable length of the 
    *                          string, in pixels 
    * @param aPreTruncate If <code>EFalse</code>, an ellipsis is appended after 
    *                     the string is formatted; if <code>ETrue</code>, 
    *                     the text to be placed in the string is truncated with 
    *                     an ellipsis, before the string is formatted
    * @return the formatted string
    * @remarks
    * @see
    */
    IMPORT_C static HBufC* FormatStringLC(const TDesC& aFrmStr, const TDesC& aText, const CFont* aFont, TInt aMaxWidthInPixels, TInt aMaxLengthInChars, TBool aPreTruncate=EFalse);

    /**
    * If it is necessary to fit a string within a certain width, this method 
    * truncates the string and adds a given end character. Any white space 
    * before the end character is removed.
    *
    * @param aBuffer The string to be truncated
    * @param aFont The font to use
    * @param aMaxWidthInPixels The maximum width of the finished string, in 
    *                          pixels 
    * @param aEnd The character to place on the end - by default 
    *             <code>KCknEnvClipEndChar</code>, the ellipsis character
    * @remarks
    * @see
    */
    IMPORT_C static void ClipToFit(TDes& aBuffer,const CFont& aFont,TInt aMaxWidthInPixels,TChar aEnd=KCknEnvClipEndChar);

    /**
    * Sets a dialog label and attempts to keep the dialog width within the
    * screen width.
    *
    * @param aFrmStr The format string containing formatting parameters
    * @param aText The text to be formatted
    * @param aDialog The dialog that contains the label
    * @param aControlId The control ID for the label control to format
    * @param aPreTruncate If <code>EFalse</code>, an ellipsis is appended after 
    *                     the string is formatted; if <code>ETrue</code>, 
    *                     the text to be placed in the string is truncated with 
    *                     an ellipsis, before the string is formatted
    * @remarks
    * @see <code>FormatStringLC()</code>
    */
    IMPORT_C static void FormatLabelL(TInt aFrmStr, const TDesC& aText, CEikDialog& aDialog, TInt aControlId, TBool aPreTruncate=EFalse);

    /**
    * Gets the height of the tallest character, taking open fonts into
    * account. If a font is initialized from a <code>CFont</code>, the maximum 
    * height is the same as the ascent and the maximum depth is the same as
    * the descent. Otherwise, the maximum height may be greater than the 
    * ascent and the maximum depth may be greater than the descent. 
    *
    * @param aFont The font being used
    * @param aMaxHeight On return, contains the maximum height
    * @param aMaxDepth On return, contains the maximum depth
    * @remarks
    * @see
    */
    IMPORT_C static void GetFontMaxHeight(const CFont* aFont, TInt& aMaxHeight, TInt& aMaxDepth);

    /**
    * Formats North American telephone numbers.
    * This method formats a supplied telephone number, removing all spaces
    * and replacing them where appropriate. The first digit(s) are taken
    * into account when performing the format, for example, 
    * "1234567890" becomes "1 234 567 890".
    *
    * @param aCursorPos The cursor position in the text
    * @param aPhoneNumber The text containing phone number
    * @remarks
    * @see
    */
    IMPORT_C static void FormatNATelephoneNumberString(TInt& aCursorPos, TPtrC& aPhoneNumber);

    /**
    * Sets the <code>MCknButtonDimmedObserver</code>. This is notified when
    * the user taps a dimmed toolbar or CBA button.
    *
    * @param aObserver The <code>MCknButtonDimmedObserver</code> observer
    * @remarks
    * @see
    */
    IMPORT_C static void SetButtonDimmedObserver(MCknButtonDimmedObserver* aObserver);

    /**
    * Returns a text representation of the object type for a given file. The method can 
    * identify document, workbook, image, sound clip, presentation, HTML document, 
    * XML document, certificate, application, and message (not messaging) types. 
    * If the type is not recognized, it returns "unknown type".
    * For example, for the object type <code>EObjectTypeDocument</code>, the
    * text "document" is returned.
    *
    * @param aFileName The name of the file
    * @param aTypeString On return, contains the default path
    * @remarks
    * @see <code>TCknObjectType</code> in cknobjecttype.h for the object
    *      types that are known
    */
    IMPORT_C static void GetObjectTypeStringForFileL(const TDesC& aFileName, TDes& aTypeString);

    /**
    * Returns the object type for a given file. It is used to determine 
    * info messages in file dialogs. The method can identify: document, workbook, 
    * image, presentation, HTML document, XML document, certificate, 
    * application, message (not messaging) types.  If the type is not 
    * recognized, it returns "unknown type".
    *
    * @param aFileName The name of the file
    * @return the type of object
    * @remarks
    * @see <code>TCknObjectType</code> in cknobjecttype.h
    */
    IMPORT_C static TCknObjectType GetObjectTypeForFile(const TDesC& aFileName);

    /**
    * Returns the object type for a given datatype as above, but cannot 
    * distinguish application files. To do this, use 
    * <code>GetObjectTypeForFile(const TDesC& aFileName)</code>
    *
    * @param aDataType The type of data
    * @return the type of object
    * @remarks
    * @see
    */
    IMPORT_C static TCknObjectType GetObjectTypeFromDataTypeL(TDataType aDataType);

    /**
    * Draws a focus rectangle from bitmaps. If the method fails to get the
    * bitmaps from the skin server, the focus rectangle is drawn using 
    * <code>aGc.DrawRoundRect</code>.
    *
    * @param aControl The control with the focus
    * @param aGc The graphics context
    * @param aRect The focus rectangle
    * @param aActiveFocus <code>ETrue</code> if the focus is to be active;
    *                     <code>EFalse</code> if the focus is to be passive
    * @remarks
    * @see
    */
    IMPORT_C static void DrawFocusRect(const CCoeControl& aControl, CBitmapContext& aGc, const TRect& aRect, TBool aActiveFocus);

    /**
    * Returns the default path "c:\MyDocs\" or the equivalent on the device 
    * (<code>R_CKN_USERS_ROOT_FOLDER_PATH</code>). This is a default path that
    * most applications use, for example, the initial directory that the
    * File Manager application goes to.
    *
    * @param aFilePath On return, contains the default path
    * @remarks
    * @see
    */
    IMPORT_C static void GetDefaultPath(TDes& aFilePath);

    /**
    * Finds the index of the nearest matching number in 
    * <code>aTextNumArray</code>. If no exact match is found, it returns the 
    * nearest lower match or the nearest higher match.
    * This method is used by <code>CEikListBox</code> and 
    * <code>CEikChoiceListBase</code> in the methods that go to the nearest 
    * item in <code>aTextNumArray</code> that contains
    * the text <code>aMatchText</code>.
    *
    * @param aMatchText The text to be searched
    * @param aTextNumArray The array of numbers 
    * @return the index into <code>aTextNumArray</code> for the closest 
    *         matching number
    * @remarks
    * @see
    */
    IMPORT_C static TInt IndexOfNearestNumberMatch(const TDesC& aMatchText, const MDesCArray& aTextNumArray);

    /**
    * Controls that use the skin framework to retrieve skin bitmaps,
    * should call <code>CCknSkinBase::DuplicateBitmapsL()</code> in their 
    * <code>ConstructL()</code> and they should call 
    * <code>ReleaseSkinBitmaps()</code> in their destructor.
    *
    * @param aUid The unique identifier of the skin multi-bitmap file
    * @remarks
    * @see
    */
    IMPORT_C static void ReleaseSkinBitmaps(TUid aUid);

public:
    /**
    * @deprecated
    */
    IMPORT_C static void SetDropShadowToLogicalBorder(TBool aDropShadow,TGulBorder::TLogicalType aBorder,TRgb aBackGroundColor);

    /**
    * Internal use only
    * @internal
    */
    IMPORT_C static TFileName GetFileNameForResourceIdL(const TInt aResourceId);
    };

#endif //** CKNENV_H *

//** End of File *
