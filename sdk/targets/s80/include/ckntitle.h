
/*
* ==============================================================================
*  Name        : ckntitle.h
*  Part of     : CKON
*  Interface   : Title API
*  Description : Classes to implement an application title bar.
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

#ifndef __CKNTITLE_H__
#define __CKNTITLE_H__

// INCLUDES
#include <eikbctrl.h>
#include <eiklabel.h>

// FORWARD DECLARATIONS
class CGulIcon;


/**
  * @internal
 */
struct SIconInfo
    {
		CGulIcon* iIcon;
		TRect iRect;
    };

/**
 * The CCknGradientBrush class implements a gradient brush for use in titles.
 *
 * @since Series90 1.0
 * @lib cknctl.lib
 */
class CCknGradientBrush : public CBase
	{
	public:

		/**
		* Destructor.
		*/
		IMPORT_C ~CCknGradientBrush();
        enum TGradientBrush
            {
            ESolid,
            EGradientVertical,
            EGradientHorizontal
            };

		/**
		* Create a brush bitmap of the specified size, and delete the old one if it exists.
		* Uses bitmap utility class for creating a brush bitmap of class CFbsBitmap. This bitmap
		* is drawn on the title bar.
		* @param aSize The size of the brush bitmap.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void CreateBrushBitmapL(const TSize aSize);

		/**
		* @return The brush bitmap.
		* <BR><B>Type of return value:</B> const CFbsBitmap*
		*/
		IMPORT_C const CFbsBitmap* BrushBitmap() const;
	private:
		CFbsBitmap* iBrushBitmap;
	};
/**
 * The CColouredLabel class implements a label for use in main titles which will draw with the colour
 * that has been set.
 *
 * @since Series90 1.0
 * @lib cknctl.lib
 * @internal
 */
class CColouredLabel : public CEikLabel
    {
	public:
		void SetColour(const TRgb aColour);

   // protected: // from CCoeControl
		void Draw(const TRect& aRect) const;

	private:
		TRgb iColour;
    };

/**
 * The CMainTitle class implements the maintitle control used by CCknAppTitle. The main title text is white and is drawn with
 * black shadow.
 *
 * @since Series90 1.0
 * @lib cknctl.lib
 * @internal
 */
class CMainTitle : public CCoeControl, public MCoeControlContext
	{
	public:

		/**
		* Destructor.
		*/
		~CMainTitle();

		void ConstructL(const TDesC& aText, const CFont* aFont);
		void SetTextL(const TDesC& aText);
		const TDesC* Text() const;
		const TDesC* ShadowText() const;
		void SetFont(const CFont* aFont);
		const CFont* Font() const;
	public:
        enum TMainTitleTextType
            {
            EPlain,
            EShadow
            };
	public: // From CCoeControl
		TSize MinimumSize();
		void HandleResourceChange(TInt aType);
		void SetContainerWindowL(const CCoeControl& aContainer);

	protected: // From CCoeControl
		void FocusChanged(TDrawNow aDrawNow);
		void SizeChanged();
		TInt CountComponentControls() const;
		CCoeControl* ComponentControl(TInt aIndex) const;

	private:
		void SetTitleTextColors();	//Only used in Series 80.

	private:
		CColouredLabel* iText;
		CColouredLabel* iShadow;
		const CFont* iFont;
	};

/**
 * The CCkcnAppTitle class implements an application title control. It is made up of a main title text and optionally an extension text,
 * a sub title and a extension drawn on a colored background.
 *
 * @since Series90 1.0
 * @lib cknctl.lib
*/
class CCknAppTitle : public CEikBorderedControl
	{
	public:
        enum TAppTitleType
            {
            EEditor,
            EWindow,
	        EList
            };
        enum TAppTitleElement
            {
            EMainTitle,
            ETitleExtension,
	        ESubTitle,
	        EAdditionalInfo
            };
	public:

		/**
		* Destructor.
		*/
		IMPORT_C ~CCknAppTitle();

		/**
		* Static constructor.
		*/
		IMPORT_C static CCknAppTitle* NewL();

		/**
		* Static constructor.
		* @param aTitleType The type of app title, either EEditor, EWindow or EList.
		* @return Pointer to created object.
		* <BR><B>Type of return value:</B> CCknAppTitle*
		*/
		IMPORT_C static CCknAppTitle* NewL(TAppTitleType aTitleType);

		/**
		* Static constructor.
		* @param aMainTitleText The main text of the application title.
		* @param aTitleExtensionText The extension text of the application title.
		* @param aSubTitleText The subtitle text.
		* @param aAdditionalInfoText Any additional text about the application.
		* @param aTitleType The type of app title, either EEditor, EWindow or EList.
		* @param aMaximumIconSize The maximum size of icon that can be displayed by the title. Default value is (0,0).
		* @return Pointer to created object.
		* <BR><B>Type of return value:</B> CCknAppTitle*
		*/
		IMPORT_C static CCknAppTitle* NewL(	 const TDesC& aMainTitleText,
								 const TDesC& aTitleExtensionText,
								 const TDesC& aSubTitleText,
								 const TDesC& aAdditionalInfoText,
                                 TAppTitleType aTitleType,
                                 const TSize& aMaximumIconSize=TSize(0,0) );


		/**
		* Constructs the CCknAppTitle from resources. This requires a resource struct of type APPTITLE
		* and id ECknCtAppTitle.
		* See CCoeControl.
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Changes the text of an exsisting application title element. Gets two parameters:
		* A reference to the descriptor containing the new text, and a TAppTitleElement
		* identifying the element to be changed.
		* If a non-exsisting element is tried to be changed nothing will happen.
		* Note: Because adding and removing text elements from the title has an effect on
		* the minimum size of the title area, this method can not be used for this purpose.
		* Adding a new element into the application title has to be done by constructing
		* a new application title with the desired elements.
		* @param aTitleText The new text.
		* @param aElement The element to have its text modified. This should be one of: EMainTitle, ETitleExtension, ESubTitle or EAdditionalInfo.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetTextL(const TDesC& aTitleText,  TAppTitleElement aElement);

		/**
		* Set the width allowed for an element in the title
		* If there is a maintitle and extension the default is to allow 2/3 for the maintitle
		* and 1/3 for the extension.
		* If this is not suitable then use this method to set the width of the element to be given a set size.
		* The element not set will be givem the remaining space in the title.
		* @param aWidth The new width.
		* @param aElement The element to have its width modified. This should be one of: EMainTitle, ETitleExtension, ESubTitle or EAdditionalInfo.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAreaWidth(TInt aWidth,TAppTitleElement aElement);

		/**
		* Get the width of any element of the title.
		* @param aElement The element to get the width of. This should be one of: EMainTitle, ETitleExtension, ESubTitle or EAdditionalInfo.
		* @return The element's width.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt AreaWidth(TAppTitleElement aElement);

		/**
		* Get the text of any element of the title.
		* @param aElement The element to get the text of. This should be one of: EMainTitle, ETitleExtension, ESubTitle or EAdditionalInfo.
		* @return A pointer to the text in this element.
		* <BR><B>Type of return value:</B> const TDesC*
		*/
		IMPORT_C const TDesC* Text( TAppTitleElement aElement);

		/**
		* Draw the TitleExtension part of the Apptitle. 
		* Drawing of the other types is not supported.
 		* Draws any element of the title instantly.
		* @param aElement The element to be drawn. This should be one of: EMainTitle, ETitleExtension, ESubTitle or EAdditionalInfo.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void DrawElementNow(TAppTitleElement aElement)const;
		//status icons

		/**
		* Sets a CGulIcon object to a specified icon position in the application
		* title. If the position is out of the range that is specified in the
		* LAF part, the icon will be inserted into the last free icon position.
		* If there are no free icon positions, the last icon will be removed,all
		* remaining icons will be shifted by one position, and the new icon will
		* be inserted into the first position.
		*
		* @param aIcon The icon to be inserted. The CCknAppTitle now owns the icon.
		* @param aIconPosition The position within the icon array to insert the icon at.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetStatusIconL(CGulIcon* aIcon, TInt aIconPosition);

		/**
		* Inserts a CGulIcon object into application title. The icon will
		* be inserted into the last free icon position. If the number of icons
		* in the title reaches the maximum that is defined in LAF part, the
		* last icon will be removed, all remaining icons will be
		* shifted by one position, and the new icon will be inserted into the first
		* position.
		*
		* @param aIcon The icon to be inserted. The CCknAppTitle now owns the icon.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void InsertStatusIconL(CGulIcon* aIcon);

		/**
		* Removes an icon from the application title. The icon is defined by
		* icon position index. If the index is out of the range that is defined
		* in LAF part, or there is no icon in the position, no icon will be
		* removed.
		*
		* @param aIconPosition The position to remove the icon from
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void DeleteStatusIcon(TInt aIconPosition);

		/**
		* Returns the icon at the array position.
		* @param aIconPosition The position to get the icon from.
		* @return The icon at the specified position.
		* <BR><B>Type of return value:</B> CGulIcon*
		*/
		IMPORT_C CGulIcon* StatusIconL(TInt aIconPosition);
	public: // From CCoeControl

		/**
		* See CCoeControl.
		*/
		IMPORT_C TSize MinimumSize();

		/**
		* See CCoeControl.
		*/
		IMPORT_C void HandleResourceChange(TInt aType);

		/**
		* See CCoeControl.
		*/
		void SetContainerWindowL(const CCoeControl& aContainer);
	protected: // From CCoeControl

		/**
		* See CCoeControl.
		*/
		IMPORT_C void FocusChanged(TDrawNow aDrawNow);

		/**
		* See CCoeControl.
		*/
		IMPORT_C void SizeChanged();

		/**
		* See CCoeControl.
		*/
		IMPORT_C void Draw(const TRect& aRect) const;

		/**
		* See CCoeControl.
		*/
		IMPORT_C TInt CountComponentControls() const;

		/**
		* See CCoeControl.
		*/
		IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	private:
		void FormatMainTitle();
		void FormatLabel(CEikLabel& aLabel,TAppTitleElement aElement);
	
		CCknAppTitle();
		void ConstructL(	     const TDesC& aMainTitleText,
								 const TDesC& aTitleExtensionText,
								 const TDesC& aSubTitleText,
								 const TDesC& aAdditionalInfoText,
                                 TAppTitleType aTitleType,
                                 const TSize& aMaximumIconSize);
		void ConstructL(TAppTitleType aTitleType);
		void TextChanged();
		const CFont* Font(TAppTitleElement aElement);
		void CreateTitleType(TAppTitleType aTitleType);
		void CreateBorders(TAppTitleType aTitleType);
		void CreateIconsL();
		void CreateBrushL();
	private:
		TAppTitleType iTitleType;
		CCknGradientBrush* iGradientBrush;
		CMainTitle* iMainTitle;
		CColouredLabel* iTitleExtension;
		CColouredLabel* iSubTitle;
		CColouredLabel* iAdditionalInfo;
		HBufC* iMainTitleCopy;
		HBufC* iTitleExtensionCopy;
		HBufC* iSubTitleCopy;
		HBufC* iAdditionalInfoCopy;
		CArrayFix<SIconInfo*>* iIconInfo;
		TSize iMaximumIconSize;
		TMargins8 iElementMargins;
		TMargins8 iBackgroundMargins;
		TRgb iBackground;
		TInt iAreaWidth[4];
	};


//
// The classes that are declared below implement a LAF for the CKON application
// title. However, since there are some dependencies to the UIKON, they can not
// be moved into a separate DLL as is.
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
/**
 * The LafMainTitle class implements a look and feel for the CCknMain Title
 * @internal
 * @since Series90 1.0
 * @lib cknctl.lib
 */
class LafMainTitle
	{
	public:

		static void MainTitleTextType(CMainTitle::TMainTitleTextType& aType);
		static void MainTitleShadowShifting(TPoint& shifting);
		static void MainTitleTextColour(TRgb& aTextColour);
		static void MainTitleShadowColour(TRgb& aShadowColour);
		static void MainTitleTextTypeFocused(CMainTitle::TMainTitleTextType& aType);
		static void MainTitleTextTypeNonFocused(CMainTitle::TMainTitleTextType& aType);
	};

/**
 * The LafAppTitle class implements a look and feel for the CCknAppTitle
 * @internal
 * @since Series90 1.0
 * @lib cknctl.lib
 */
class LafAppTitle
	{
	public:

		static void AppTitleType(CCknGradientBrush::TGradientBrush& aAppTitleType);
		static void MainColour(TRgb& aMainColour);
		static void GradientEndColour(TRgb& aGradientEndColour);
		static void TopMarginInsideTitle(TInt& aMargin);
		static void BottomMarginInsideTitle(TInt& aMargin);
		static void LeftMarginInsideTitle(TInt& aMargin);
		static void RightMarginInsideTitle(TInt& aMargin);
		static const CFont* MainTitleFont(const CCoeControl* aMainTitle,
                                          const CCoeControl* aTitleExtension,
                                          const CCoeControl* aSubTitle,
                                          const CCoeControl* aAdditionalInfo,
                                          const TBool aIsFocused);
		static const CFont* TitleExtensionFont(const CCoeControl* aMainTitle,
                                               const CCoeControl* aTitleExtension,
                                               const CCoeControl* aSubTitle,
                                               const CCoeControl* aAdditionalInfo,
                                               const TBool aIsFocused);
		static const CFont* SubTitleFont(const CCoeControl* aMainTitle,
                                         const CCoeControl* aTitleExtension,
                                         const CCoeControl* aSubTitle,
                                         const CCoeControl* aAdditionalInfo,
                                         const TBool aIsFocused);
		static const CFont* AdditionalInfoFont(const CCoeControl* aMainTitle,
                                               const CCoeControl* aTitleExtension,
                                               const CCoeControl* aSubTitle,
                                               const CCoeControl* aAdditionalInfo,
                                               const TBool aIsFocused);

		static void BorderType(TInt& aType,TInt& aAdjacent,CCknAppTitle::TAppTitleType aTitleType);
		static void SizeChanged(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void SetEditableMainTitleRect(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void SetNonEditableMainTitleRect(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void SetTitleExtensionRect(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void SetSubTitleRect(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void SetAdditionalInfoRect(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void SetIconRects(TRect& aNonEditableMainTitleRect, TRect& aTitleExtensionRect, TRect& aSubTitleRect, TRect& aAdditionalInfoRect, CArrayFix<SIconInfo*>* aIconInfo, const TRect& aRect);
		static void FormatText(TPtr& aText, const CCknAppTitle::TAppTitleElement aElement, const CFont& aFont,const TInt aElementWidth);
		static void CalculateAppTitleSize(TSize& aAppTitleSize,const TSize& aNonEditableMainTitleSize,const TSize& aTitleExtensionSize,const TSize& aSubTitleSize,const TSize& aAdditionalInfoSize,const CArrayFix<SIconInfo*>* aIconInfo,const CCknAppTitle::TAppTitleType aTitleType);
		static void MinimumAppTitleSize(TSize& aMinimumAppTitleSize, const TSize& aMaximumIconSize, const CCknAppTitle::TAppTitleType aTitleType, CCoeEnv* aCoeEnv);
		static void MaxNumberOfIcons(TInt& aMaxNumberOfIcons);
		static void BackgroundMarginsEditor(TMargins8& aMargins);
		static void BackgroundMarginsWindow(TMargins8& aMargins);
		static void BackgroundMarginsList(TMargins8& aMargins);
		static void ElementMarginsEditor(TMargins8& aMargins);
		static void ElementMarginsWindow(TMargins8& aMargins);
		static void ElementMarginsList(TMargins8& aMargins);
		static void IconSpacingVertical(TInt& aSpacing);
		static void IconSpacingHorizontal(TInt& aSpacing);
	};

#endif	// __CKNTITLE_H__

// End of File
