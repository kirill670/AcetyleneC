// EIKEDWIN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__EIKEDWIN_H__)
#define __EIKEDWIN_H__

#include <s32std.h>
#include <gdi.h>
#include <txtetext.h>
#include <medobsrv.h>
#include <gulutil.h>
#include <fepbase.h>
#include <frmvis.h>
#include <frmtview.h>
#include <uikon.hrh>
#include <eikon.hrh>
#include <eikbctrl.h>
#include <eikedwob.h>
#include <eiksbfrm.h>
#include <eikccpu.h>
#include <eiklay.h>
#include <lafmain.h>
#include <AknPictographDrawerInterface.h>
#include <babitflags.h>

class CGlobalText;
class CParaFormatLayer;
class CCharFormatLayer;
class MLayDoc;
class CEikEdwinFepSupport;
class CLafEdwinCustomDrawBase;
class CClipboard;
class CAknEdwinFormAccessor;
class CAknEdwinState;
class CAknInputPolicyManager;
class CFormCursorModifier;
class CTextView;
class MAknsControlContext;
class CAknEdwinDrawingModifier;
class CAknEdwinFormExtendedInterfaceProvider;
class CAknPhoneNumberInlineTextSource;
class CAknNoMatchesIndicatorInlineTextSource;
class CAknInlineTextSource;
class CAknPictographInterface;

// Forward declaration of now removed (Series 60 vsn 2.0) custom drawer class for CEikEdwin
class CEikAvkonCustomDraw;

// Forward declaration of now removed (Series 60 vsn 2.0) custom drawer class for CEikEdwin
class CEikAvkonCustomDraw;

// For construction of Rich Text - based custom formatters
class CRichText;

enum TReplaceOption
	{
	ENoReplace,
	EReplaceOnce,
	EReplaceAll,
	EReplaceSkip
	};

struct SEdwinFindModel
	{
	TInt iFlags; // TEdwinFindFlags
	TBuf<EEikEdwinFindStringMaxLen> iText;
	TBuf<EEikEdwinFindStringMaxLen> iReplaceText;
	TReplaceOption iReplaceOption;
	};

enum TAknsHighlightStyle
    {
    EEikEdwinHighlightNormal = 0,
    EEikEdwinHighlightLink
    };

// inline utility to handle RGB values (set / unset)      

class SAknRgb
    {
// data (private)    
    TRgb iValue;
    TBool iIsSet;
public: // utilities   
    SAknRgb():iIsSet(EFalse){}
    TRgb Value(){return iValue;}
    SAknRgb& operator=(TRgb aRgb)
        {
        iValue = aRgb;
        iIsSet = ETrue;
        return *this;
        }
    TBool IsSet(){return iIsSet;}
    };    


class CEikEdwin : public CEikBorderedControl, public MEikScrollBarObserver, public CTextView::MObserver, public MEditObserver, public MEikCcpuEditor
	{
private:
	class CUndoBuffer;
	NONSHARABLE_CLASS(CEikEdwinExtension) : public CBase
		{
	public:
		static CEikEdwinExtension* NewL(CEikEdwin* aEdwin);
		~CEikEdwinExtension();
		IMPORT_C CAknEdwinFormAccessor* FormAccessor() const;
		IMPORT_C void SetFormAccessor(CAknEdwinFormAccessor* aFormAccessor);
		IMPORT_C void SetScrollBarSetter(CIdle* aScrollBarSetter);
		IMPORT_C CIdle* ScrollBarSetter();
		IMPORT_C const TAvkonEditorCustomWrap& TextWrapper();

		// the following two methods are deprecated
        IMPORT_C CFormCursorModifier* FormCursorModifier() const;
        
        /**
        * Store a locally stored (but externally set) Skins background control context
        *
        * @param aBackgroundControlContext   Control context to store. Not owned. Can be NULL
        */
        void SetSkinBackgroundControlContext( MAknsControlContext* aBackgroundControlContext );
        
        /**
        * Access to locally stored Skins background control context
        * 
        * @return Pointer to locally stored control context
        */
        
        MAknsControlContext* SkinBackgroundControlContext() const;
        
        /**
        * This returns a flag that records whether the background context has ever been 
        * set by API 
        *
        * @return   EFalse iff control context has never been set
        */
        TBool SkinBackgroundControlContextHasBeenSet() const;

        /**
        * Stores the alignment value
        *
        * @param aAlignment   editor alignment to be stored
        */
        void SetAlignment(TInt aAlignment);

        /**
        * Returns the stored alignment value
        *
        * @return value of current editor alignment
        */
        TInt CurrentAlignment() const;

        /**
        * Sets pictograph animation callback
        */
        void SetPictoCallBack( TCallBack& aCallBack );

        /**
        * Sets pictograph animation callback
        */
        const TCallBack& PictoCallBack() const;

        /**
        * Creates the CAknFormExtendedInterfaceProvider object if it does not exist
        */
        void CreateFormExtendedInterfaceProviderIfNeededL();

        /**
        * Access to Form's extended interface provider
        */
        CAknEdwinFormExtendedInterfaceProvider* FormExtendedInferfaceProvider() const;

        /**
        * Create a custom formatter for pure phone number content
        *
        * Calls CreateFormExtendedInterfaceProviderIfNeededL to ensure that there is an
        * ExtendedInterfaceProvider object built.
        *
        * @param    aTextLayout     Reference to the CTextLayout object used for this editor
        *           aText           CPlainText object reference for the text used in the editor
        */
        void CreatePurePhoneNumberFormatterL( CTextLayout& aTextLayout, const CPlainText& aText);

        /**
        * Create a custom formatter for pure phone number content
        *
        * Calls CreateFormExtendedInterfaceProviderIfNeededL to ensure that there is an
        * ExtendedInterfaceProvider object built.
        *
        * @param    aTextLayout     Reference to the CTextLayout object used for this editor
        */
        void CreateNoMatchesIndicatorFormatterL( CTextLayout& aTextLayout );

        /**
        * Create a custom formatter for rich text editor with general content. Phone numbers are
        * recognized using an internal parser and formatted with the number grouping engine
        *
        * Calls CreateFormExtendedInterfaceProviderIfNeededL to ensure that there is an
        * ExtendedInterfaceProvider object built.
        *
        * @param    aTextLayout     Reference to the CTextLayout object used for this editor
        */
        void CreateRichTextPhoneNumberFormatterL( CTextLayout& aTextLayout, const CRichText& aText );

        /**
        * This allows the caller to access the single inline text interface that will be seen
        * by Tagma.  All installed inline text source classes are held behind this single interface
        * 
        * @return   pointer to the inline text source object that will be provided to Tagma
        *           Null is returned if none is installed.
        */
        CAknInlineTextSource* InlineTextSource() const;

        /**
        * Returns pointer to pictograph interface.
        *
        * @return Pointer to pictograph interface. The value can be NULL if pictographs are not supported.
        */
        CAknPictographInterface* PictographInterface() const;
        
	private:
		CEikEdwinExtension();
		void ConstructL(CEikEdwin* aEdwin);
    private:
        enum TFlagIndices
            {
            ESkinBackgroundControlContextHasBeenSetIndex = 0
            };
        class TAknEdwinPictographDrawer : public MAknPictographAnimatorCallBack
            {
            private: // From MAknPictographAnimatorCallBack
                void DrawPictographArea();
            };        
	private:
		CIdle* iSetScrollBar;
		TAvkonEditorCustomWrap iTextWrapper;
		CAknEdwinFormAccessor* iFormAccessor;
        CFormCursorModifier* iFormCursorModifier;
        MAknsControlContext* iSkinBackgroundControlContext;
        TBitFlags iFlags;
        TInt iAlignment;
        TCallBack iPictoCallBack;       
        CAknEdwinFormExtendedInterfaceProvider* iFormExtendedInterfaceProvider; // Owned
        CAknInlineTextSource* iPhoneNumberFormatter;                 // Not owned
        CAknNoMatchesIndicatorInlineTextSource* iNoMatchesIndicatorFormatter;   // Not owned
        TAknEdwinPictographDrawer iPictographDrawer;
        CAknPictographInterface* iPictographInterface;
     public:   
        TInt iSkinIdForText;
        TAknsHighlightStyle iSkinHighlightStyle;
        SAknRgb iEditorBackgroundColor;
        TInt iUpperFullFormattingLength;
		};

public:
	enum TFlags
		{ // user flags
		EZeroEnumValue			=0x00000000, 
		EKeepDocument			=0x00000001,
		ESegmentedStorage		=0x00000002,
		EWidthInPixels			=0x00000004,
		ENoAutoSelection		=0x00000008,
		EJustAutoCurEnd			=0x00000010,
		ENoWrap					=0x00000020,
		ELineCursor				=0x00000040, 
		ENoHorizScrolling		=0x00000080, 
		EInclusiveSizeFixed		=0x00000100, 
		EUserSuppliedText		=0x00000200,
		EOwnsWindow				=0x00000400,
		EDisplayOnly			=0x00000800,
		EAlwaysShowSelection	=0x00001000,
		EReadOnly				=0x00002000,
		EAllowPictures			=0x00004000,
		EAllowUndo				=0x00008000,
		ENoLineOrParaBreaks		=0x00010000,
		EOnlyASCIIChars			=0x00020000,
		EResizable				=0x00040000,
		EIgnoreVirtualCursor	=0x00080000,
		ENoCustomDraw			=0x01000000,
		EAvkonEditor			=0x02000000,
		EAvkonDisableCursor		=0x04000000,
		EAvkonNotEditable		=0x08000000, 
		EEdwinAlternativeWrapping = 0x10000000
		};
	enum TClipboardFunc
		{
		ENoClipboard,
		ECut,
		ECopy,
		EPaste
		};
	enum TFindFlags
		{
		EFindDirectionUp	=0x01,
		EFindWholeWord		=0x02,
		EFindCaseSensitive	=0x04,
		EFindAgain			=0x08,
		ENoBusyMessage		=0x10,
		EReadOnlyFile		=0x20 // New for CKon
		};
	enum TSetContent
		{
		EUseText,
		ECopyText
		};
	enum TOwnershipType
		{
		EOwnsText,
		EDoesNotOwnText
		};
	enum TEdwinHotKeys // order of hotkeys defined in resource file.  Not all applicable to plain text editors
		{
		EHotKeyCut,
		EHotKeyCopy,
		EHotKeyPaste,
		EHotKeyUndo,
		EHotKeyFind,
		EHotKeyInsertChar,
		EHotKeyBold,
		EHotKeyItalic,
		EHotKeyUnderline,
		EHotKeyFont,
		EHotKeyInsertObject,
		EHotKeyEditObject,
		EHotKeyFormatObject
		};
public: // construction and destruction
	IMPORT_C ~CEikEdwin();
	IMPORT_C CEikEdwin();
	IMPORT_C CEikEdwin(const TGulBorder& aBorder);
	IMPORT_C void ConstructL(TInt aEdwinFlags=0,TInt aWidthInChars=0,TInt aTextLimit=0,TInt aNumberOfLines=0);
	IMPORT_C void SetEdwinObserver(MEikEdwinObserver* aEdwinObserver);
	IMPORT_C void AddEdwinObserverL(MEikEdwinObserver* aEdwinObserver);
	IMPORT_C void RemoveEdwinObserver(MEikEdwinObserver* aEdwinObserver);
	IMPORT_C void SetContainerWindowL();
	IMPORT_C void SetDocumentContentL(CGlobalText& aText,TSetContent aContent=CEikEdwin::ECopyText);
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void ActivateL();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	/**
	* Access to the input capabilities of the edwin
	*
	* @return copy of input capabilities structure
	*/
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	/**
	* This method sets the input capabilities of the edwin. Ownership of the T-class is not
	* transferred; a copy is maintained somewhere within the edwin.
	*
	* @param aInputCapabilities		Reference to an input capabilities object on the heap 
	*/
	IMPORT_C void SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities); 
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
public: // from MEikScrollBarObserver
	IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType); // from MEilScrollBarObserver
public: // from CTextView::MObserver
	IMPORT_C void OnReformatL(const CTextView* aTextView);
public:
	IMPORT_C TInt TextLength() const;
	IMPORT_C TInt CursorPos() const;
	IMPORT_C TInt SelectionLength() const;
	IMPORT_C TCursorSelection Selection() const;
	IMPORT_C void ClearSelectionL();
	IMPORT_C void SetSelectionL(TInt aCursorPos,TInt aAnchorPos);
	IMPORT_C void SetCursorPosL(TInt aCursorPos,TBool aSelect);
	IMPORT_C void SelectAllL();
	IMPORT_C void CalculateWidth(TInt aWidthInChars);
	IMPORT_C void GetText(TDes& aDes) const;
	IMPORT_C HBufC* GetTextInHBufL() const;
	IMPORT_C void SetTextL(const TDesC* aDes);
	IMPORT_C void ClipboardL(TClipboardFunc aClipboardFunc);
	IMPORT_C void InsertFieldL(CTextField* aField,TUid aFieldType);
	IMPORT_C void UpdateAllFieldsL();
	IMPORT_C void UpdateCurrentFieldL();
	IMPORT_C TInt CountWords();
	IMPORT_C void InsertFromTextFileL(const TFileName &aFileName,const CPlainText::TTextOrganisation aTextOrganisation=CPlainText::EOrganiseByLine);
	IMPORT_C static TInt IdleL(TAny *aPtr);
	IMPORT_C CPlainText* Text() const;
	IMPORT_C void CancelFepTransaction(); // this is particularly important for when the front-end processor is inline-editing a CEikEdwin
	IMPORT_C void HandleTextChangedL();
	IMPORT_C TInt LayoutWidth() const;
	IMPORT_C void NotifyNewDocumentL();
	IMPORT_C void NotifyNewFormatL();
	IMPORT_C TBool FindL(const TDesC* aFindText,TInt aFindFlags=0);
	IMPORT_C TInt FindTextL(const TDesC* aFindText,TInt aPos,TInt aFindFlags);
	IMPORT_C void ReplaceL(SEdwinFindModel* aFindModel);
	IMPORT_C void ReplaceAllL(SEdwinFindModel* aFindModel);
	IMPORT_C void GetFindText(TDes* aFindText);
	IMPORT_C void UpdateScrollBarsL();
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL();
	inline CEikScrollBarFrame* CreatePreAllocatedScrollBarFrameL();
	inline CEikScrollBarFrame* ScrollBarFrame();
	IMPORT_C void SetWordWrapL(TBool aWrapIsOn);
	IMPORT_C virtual TInt LineCursorWidth() const;
	IMPORT_C void SetZoomFactorL(TZoomFactor* aZoomFactor);
	IMPORT_C void SetBackgroundColorL(TRgb aBackground);
	IMPORT_C void SetWysiwygModeOn(TInt aLayoutWidth,MGraphicsDeviceMap* aDevice);
	IMPORT_C void SetWysiwygModeOff();
	IMPORT_C void UpdateLayoutWidth(TInt aLayoutWidth); // for use in wysiwyg mode only
	IMPORT_C void SendDataOverIrL();
	IMPORT_C void ReceiveDataOverIrL();
	IMPORT_C void SetAmountToFormatL(TBool aIsNewDoc=EFalse);
	IMPORT_C void SetPasteFromIrStore(TBool aPasteFromIrStore);
	IMPORT_C void PasteFromStoreL(CStreamStore& aStore, CStreamDictionary& aDict);
	IMPORT_C void CopyToStoreL(CStreamStore& aStore, CStreamDictionary& aDict);
	IMPORT_C void SetBorderViewMargins(TMargins8 aMargins);
	IMPORT_C void ForceScrollBarUpdateL();
	IMPORT_C void SetDocumentOwnership(TOwnershipType aOwner);
	IMPORT_C void SetTextLimit(TInt aLimit);
	IMPORT_C void RunCharMapDialogL();
	IMPORT_C TMargins8 Margins() const;
	IMPORT_C TInt UpperFullFormattingLength() const;
	IMPORT_C TInt LowerPartialFormattingLength() const;
	IMPORT_C void SetReadOnly(TBool aReadOnly);
	IMPORT_C TBool IsReadOnly() const;
	IMPORT_C void CheckNotReadOnlyL();
	IMPORT_C void SetAllowPictures(TBool aAllow);
	IMPORT_C void CheckRemovePictures(TInt aStartPos,TInt aLength);
	IMPORT_C void SetRightWrapGutter(TInt aGap);
	IMPORT_C void UndoL();
	IMPORT_C void ClearUndo();
	IMPORT_C void SetAllowUndo(TBool aAllow);
	IMPORT_C TBool SupportsUndo() const;
	IMPORT_C TBool CanUndo() const;
	IMPORT_C void SetWordDelimiters(TBool aPicture,TBool aPunctuation);
	IMPORT_C void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength) const;
	IMPORT_C void MoveCursorL(TCursorPosition::TMovementType aMovement,TBool aSelect);
	IMPORT_C void MoveDisplayL(TCursorPosition::TMovementType aMovement);
	IMPORT_C void CheckValidityOfChars(TInt aStartPos,TInt aLength);
	IMPORT_C void SetOnlyASCIIChars(TBool aASCIIOnly);
	IMPORT_C TBool OnlyASCIIChars() const;
	inline TInt AvgLinesInViewRect() const;
	inline TInt AvgCharsPerLine() const;
	inline void SetAvgLinesInViewRect(TInt aAvgLines);
	inline void SetAvgCharsPerLine(TInt aAvgChars);
	IMPORT_C void SetEdwinSizeObserver(MEikEdwinSizeObserver* aEdwinSizeObserver);
	IMPORT_C TInt MinimumHeight() const;
/*	
Please do not use the following method for deciding heights if you are using edwins with Maximum Heights 
in forms.  Use MaximumHeightInLines instead. JIn
*/
	IMPORT_C TInt MaximumHeight() const;

	IMPORT_C void SetMinimumHeight(TInt aHeight);
/*	
Please do not use the following method for setting maximum heights if you are using edwins with 
Maximum Heights in forms.  Use MaximumHeightInLines instead. JIn
*/
	IMPORT_C void SetMaximumHeight(TInt aHeight);
public: // new utility methods
	IMPORT_C void InsertDeleteCharsL(TInt aInsertPos,const TDesC& aText,const TCursorSelection& aDelete);
	IMPORT_C void SetNonPrintingCharsVisibility(TNonPrintingCharVisibility aVisibility);
	IMPORT_C TNonPrintingCharVisibility NonPrintingCharsVisibility() const;
public: // new Avkon wrap interface
	IMPORT_C void SetAvkonWrap(TBool aAvkonWrapIsOn);
public:	// Avkon editor extensions

    /**
    * Set default case for the editor. The case is used when the editor
    * is focused first time. Available case flags from uikon.hrh
    * are EAknEditorUpperCase, EAknEditorLowerCase and EAknEditorTextCase.
    * EAknEditorTextCase is used if the initial case is not set from EDWIN
    * resource default_case or with this API.
    *
    * @param aCase Initial case to be used in the editor.
    */
    IMPORT_C void SetAknEditorCase(TInt aCase);

    /**
    * Set permitted cases for the editor.
    * Possible flags from uikon.hrh are EAknEditorAllCaseModes, 
    * EAknEditorUpperCase, EAknEditorLowerCase and EAknEditorTextCase.
    * EAknEditorAllCaseModes is used if the value is not set from EDWIN
    * resource allowed_case_modes or with this API.
    *
    * @param aPermittedCaseModes Case modes that are available in the editor.
    */
    IMPORT_C void SetAknEditorPermittedCaseModes(TInt aPermittedCaseModes);

    /**
    * Set number mode key mapping for '*' and '#' keys. The key mapping is used
    * in editors when numeric input mode is used. Key mapping characters
    * for '*' key are shown on special character table if also text input modes
    * are allowed in the editor but the current input mode is numeric mode.
    * EAknEditorStandardNumberModeKeymap is used in editors that allow only 
    * numeric input if the mapping is not set from EDWIN resource numeric_keymap
    * or with this API. EAknEditorAlphanumericNumberModeKeymap is used as default
    * if the editor allows also text input mode.
    *
    * @param aNumericKeymap Key mapping used in an editor with number input mode.
    */
    IMPORT_C void SetAknEditorNumericKeymap(TAknEditorNumericKeymap aNumericKeymap);

    /**
    * Set default input mode for the editor. The input mode is used when 
    * the editor is focused first time. 
    * EAknEditorTextInputMode is used if the initial input mode is not set 
    * from EDWIN resource default_input_mode or with this API.
    *
    * @param aInputMode Initial input mode to be used in the editor.
    */
    IMPORT_C void SetAknEditorInputMode(TInt aInputMode);

    /**
    * Set allowed input modes for the editor. 
    * All input modes are allowed (EAknEditorAllInputModes) if the value 
    * is not set from EDWIN resource allowed_input_modes or with this API.
    *
    * @param aInputModes Input modes that are allowed in the editor.
    */
    IMPORT_C void SetAknEditorAllowedInputModes(TInt aInputModes);

    /**
    * Set editor specific special character table. 
    *
    * @param aSCTResId Special character table dialog resource.
    */
    IMPORT_C void SetAknEditorSpecialCharacterTable(TInt aSCTResId);

    /**
    * Set initial editor flags for the editor.
    * This method can be used also to update editor flags after the editor is focused.
    * FEP is automatically notified of the updated editor flags.
    *
    * @param aFlags Avkon editor flags for the editor.
    */
    IMPORT_C void SetAknEditorFlags(TInt aFlags);

    IMPORT_C void EnableCcpuSupportL(TBool aSupport);

    /**
    * Updates editor input mode. FEP is automatically notified of the
    * new input mode in editor state and FEP takes new input mode to use 
    * immediatelly. Current inline editing is reset.
    * This method should not be used for setting initial input mode for the editor.
    * Use SetAknEditorInputMode() method instead for setting initial input mode.
    *
    * @param aInputMode New input mode for the editor.
    */
    IMPORT_C void SetAknEditorCurrentInputMode(TInt aInputMode);

    /**
    * Returns the input mode that has been saved to editor state.
    *
    * @since 2.6
    * @return Input mode that is saved to editor state.
    */
    IMPORT_C TInt AknEditorCurrentInputMode();

    /**
    * Updates editor case. FEP is automatically notified of the
    * case change in editor state and FEP takes new case to use immediatelly.
    * Available case flags from uikon.hrh are EAknEditorUpperCase, 
    * EAknEditorLowerCase and EAknEditorTextCase.
    * This method should not be used to set initial case for the editor.
    * Use SetAknEditorCase() method instead for setting initial case.
    *
    * @param aCase New case for the editor.
    */
    IMPORT_C void SetAknEditorCurrentCase(TInt aCase);

    /**
    * Set new local input language for the editor. Global input language
    * changes have not effect for the input language but the user can still
    * change the input language from the edit menu.
    *
    * @param aLanguage Editor local input language.
    */
    IMPORT_C void SetAknEditorLocalLanguage(TLanguage aLanguage);

    /** 
    * This call causes FEP to reset current editing state and
    * new editing state is fetched from CAknEdwinState object.
    */
    IMPORT_C void NotifyEditorStateObserverOfStateChangeL();
public:

    // These methods have been added for use with Avkon to set maximum editor heights.
	IMPORT_C void SetMaximumHeightInLines(TInt aLines);

	IMPORT_C TInt MaximumHeightInLines() const;

public: // From MEikCcpuEditor
	IMPORT_C TBool CcpuIsFocused() const;
	IMPORT_C TBool CcpuCanCut() const;
	IMPORT_C void CcpuCutL();
	IMPORT_C TBool CcpuCanCopy() const;
	IMPORT_C void CcpuCopyL();
	IMPORT_C TBool CcpuCanPaste() const;
	IMPORT_C void CcpuPasteL();
	IMPORT_C TBool CcpuCanUndo() const;
	IMPORT_C void CcpuUndoL();
	IMPORT_C TInt  AknEdwinFlags() const;
 

public: // Internal to Symbian
	// the following methods are deprecated and will be removed in a future release
	IMPORT_C void CreateTextViewL();
	IMPORT_C CTextView* TextView() const;
	IMPORT_C CTextLayout* TextLayout() const;
	IMPORT_C TBool SetUndoBufferL(const TCursorSelection& aSelection);
	IMPORT_C void SetUndoableText(const TCursorSelection& aSelection);

	CAknEdwinState* EditorState() const;
	inline void SetMaxLength(TInt aLength );
	inline TInt MaxLength() const;
public:
	// added to get access to user flags without a get/set for every different flag.
	IMPORT_C void AddFlagToUserFlags(TUint32 aFlag);
	IMPORT_C void RemoveFlagFromUserFlags(TUint32 aFlag);
	IMPORT_C TUint32 UserFlags() const ;

public:
	IMPORT_C void SetCharFormatLayer(CCharFormatLayer* aCharFormatLayer);
	IMPORT_C void SetParaFormatLayer(CParaFormatLayer* aParaFormatLayer);

// Skins support
public:
    /**
    * Sets within in the editor an externally owned Skins background control context.
    * This background control context will then be used by the editor to draw background.
    *
    * If this API is not called, then the editor IS skin enabled, (that is CEikEdwins are skin
    * enabled by default) but it will try to find a control context with which to perform background 
    * drawing from the Control Environment, via the Object Provider.
    *
    * Setting this control context to NULL will have the effect of turning off background 
    * skinning. 
    *
    * @param aBackgroundControlContext   Control context to store. Not owned. Can be NULL
    */
    IMPORT_C void SetSkinBackgroundControlContextL( MAknsControlContext* aContext );

    /**
    * Access to Skins background control context that is potentially being used by the Editor.
    *
    * This API will first check to see if an control context has been set by API, and if so, 
    * return that.  If the background control context has been set to NULL by API, then it will
    * return NULL. If the background control context has never been set by API, then this returns
    * the control context (if one exists) that the object obtains from Object Provider.
    * 
    * 
    * @return Pointer to control context potentially in use, or NULL.
    */
    MAknsControlContext* SkinBackgroundControlContext() const;

    /**
    * Access to disposition of the editor to perform Skinning. This does not take into account
    * whether the application is skin enabled or whether the environment is providing a background
    * control context. It is only a function of whether editor's (default) disposition to skin has
    * been countered by calls on the editor API.
    * 
    * @return   EFalse iff SetSkinBackgroundControlContextL has been called with NULL in its most recent call
    */
    TBool SkinEnabled() const;

	/**
	* Stores the alignment value for an editor
	*
	* @param aAlignment   editor alignment to be stored - must be supplied as
	*					  one of the values in Avkon editor alignment enum i.e.:
	*						EAknEditorAlignCenter
	*						EAknEditorAlignLeft
	*						EAknEditorAlignRight 
	*						EAknEditorAlignBidi
	*/
	IMPORT_C void SetAlignment(TInt aAlignment);

// Pictograph support
public:

    /**
    * Redraws text view. Used for pictograph animations.
    */
    void DrawTextView() const;

    /**
    * Sets the callback, which the editor calls after having redrawn itself for
    * animated pictographs. CEikCaptionedControl uses it to draw the highlight
    * frame on top of the editor.
    *
    * @since 2.6
    */
    IMPORT_C void SetPictographAnimationCallBack( TCallBack& aCallBack );

    /**
    * Returns pictograph animation callback. If it is not set, the function
    * pointer is NULL.
    */
    const TCallBack& PictographAnimationCallBack() const;

    /**
    * This method sets the upper limit of full document formatting.  
    *
    * At construction, the mode is full document formatting, where the text formatter processes
    * the whole document to determine its layout.
    * 
    * When the text content is set, or when user input causes the length of text to exceed this value, 
    * the formatting mode switches to "Band" formatting, where the text formatter attempts to format 
    * as little as possible - optimally just the visible screen.
    * 
    * A lower limit is calculated from the passed-in value, by the subtraction of a constant. 
    * When the text becomes smaller than this lower limit, the formatting switches to 
    * full document formatting.
    * 
    * Internally-imposed limits prevent the client setting too small a value for proper operation of the 
    * text formatting.
    *
    * If this method is not called, the upper and lower limts are set to a large default values.
    *
    * Access to the actual limits is available via the methods UpperFullFormattingLength() and 
    * LowerPartialFormattingLength().
    *
    * @since 3.0
    *
    * @param    aUpperFullFormattingLimit  The value above which formatting switches to Band formatting
    */
    IMPORT_C void SetUpperFullFormattingLength( TInt aUpperFullFormattingLimit );
    
protected:
	enum TEnd
		{
		EStart,
		EEnd   
		};
	enum TChunkSize
		{
		EChunkWord,
		EChunkPara
		};
	enum TEikEdwinFlags
		{ // internal flags
		ERichText           =0x00000001,
		EDragDouble			=0x00000002,
		ELeftDownInViewRect =0x00000004,
		ENumericCharacters	=0x00000008, // only used to calculate initial width
		EHasOneLineOnly     =0x00000010,  // when edwin has one line and is not resizable
        EPhoneNumberGrouping = 0x00000020 // Custom formatter is installed to find and format phone numbers (CEikRichTextEditor only)
		};
protected: // from MEditObserver
	IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);
protected:
	IMPORT_C void TrappedDraw(const TRect& aRect) const;
	IMPORT_C void DrawContents();
	IMPORT_C void BaseConstructL();
	IMPORT_C void FormatTextL();
	IMPORT_C TInt DeleteHighlightL(TBool& aChanged,TBool aIsBackSpace=EFalse,TBool aPromptConfirmation=ETrue);
	IMPORT_C TBool OkToDeleteSelectionL();
	IMPORT_C void DeleteL(TBool& aChanged,const TCursorSelection& aSelection,TBool aIsBackSpace=EFalse,TBool aAllowUndo=ETrue);
	IMPORT_C void TrappedSizeChanged();
	IMPORT_C void HandleSizeChangedL();
	IMPORT_C void CancelSelectionL(TEnd aEndOfSelectionToLeaveCursor);
	IMPORT_C void MoveCursorToChunkStartL(TBool aSelect,TChunkSize aChunkSize,TEnd aEndScanningTowards);
	IMPORT_C void CancelInsertCharFormat();
	IMPORT_C void PlaceDataOnClipboardL();
	IMPORT_C void ReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);
	IMPORT_C void SetLineCursorDetailsL();
	IMPORT_C virtual void CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText);
	IMPORT_C void DisplayFindTextNotFound(TDes& aFindText);
	IMPORT_C virtual void HandleTextPastedL(TInt aStartPos,TInt& aLength);
	IMPORT_C virtual CLafEdwinCustomDrawBase* CreateCustomDrawL();
	// Avkon editor extensions
	IMPORT_C void ReadAknResourceL(TResourceReader& aReader);
protected: // Internal to Symbian
	IMPORT_C void CreateLayoutL(MLayDoc* aLayDoc);
	IMPORT_C void CreateTextAndLayoutL(CParaFormatLayer* aParaFormatLayer,CCharFormatLayer* aCharFormatLayer);
	IMPORT_C void CheckEdwinExtensionL();
	IMPORT_C CEikEdwinExtension* EdwinExtension();

private:
	enum
		{ // internal flags
		EWysiwygOn						=0x00000010,
		EUnderOneScreenFormattedText	=0x00000020,
		EPictureDelimits				=0x00000040,
		EPunctuationDelimits			=0x00000080,
		EPasteFromIrStore				=0x00000100,
		ELockScrollBarState				=0x00000200,
		EOnReformatting					=0x00000400
		};

private: // from CCoeControl
	IMPORT_C void SizeChanged();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void NotifyInvalidOperationOnReadOnlyL();
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc);
	void SetVirtualCursorStateL(TBool aIsFocused) const;
	void SetHeightForNumOfLinesL();
	void ApplyAutoSelectionL();
	void SetScrollBarsL();
	void SetVertScrollBarModelByCharactersL(TEikScrollBarModel& aVertModel) const;
	void RetrieveDataFromClipboardL();
	void SetCursorVisibilityL(TBool aEmphasis);
	TBool OwnsScrollBars() const;
	void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
	void UpdateHorizScrollBarThumb();
	void UpdateVertScrollBarThumbL();
	void DoSetUndoBufferL(const TCursorSelection& aSelection);
	void DoPasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
	void DoReplaceAllL(SEdwinFindModel* aModel,TBool& aTextFound,TBool& aReplaced);
	void DeleteExtraParasL(TInt aStartPos,TInt aLength);
	TInt LocateChar(TChar aChar,TInt aStartPos,TInt aLength);
	TBool IsValidChar(TInt aChar) const;
	TInt CalcMinimumHeightFromNumOfLinesL() const;
	void CheckEdwinHeight();
	TBool IsNewHeightWithinMinimumAndMaximum(TInt aNewHeight) const;
	void SetEdwinHeight(TInt aHeight);
	void DoCreateCustomDrawL();
	void SetCursorSizeAndType();
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void DoCcpuCanPasteL() const;
	void DoReportEventL(MCoeControlObserver::TCoeEvent aEvent);
	void CheckIfEdwinIsResizable();
	void SetKeyboardRepeatRate(TTimeIntervalMicroSeconds32 aKeyRepeatRate) const;
	HBufC* GetAllowedCharsLC() const;
	TInt CheckAllowedCharsL(const TDesC& aChars, CClipboard& aClipboard, TBool aRichText) const;

	TInt CursorWidth() const;
	TFontSpec CursorFontSpec() const;

	void BuildEdwinFepSupport();
	void MakeCharFormatLayerMatchL(CCharFormatLayer* aCharFormatLayer);
	void MakeParaFormatLayerMatchL(CParaFormatLayer* aParaFormatLayer);
    void UpdateCache(TInt aId);
	void DrawBackgroundAroundTextView( 
		CWindowGc& gc, 
		const TRect& aOuterRect, 
		const TRect& aInnerRect, 
		const TRgb& aBackgroundColor  ) const;
	TInt CurrentAlignment() const;
	void DoAlignment();
	void NewParagraphL();
private:
	void DrawFirstLineTextL() const;
    CAknEdwinDrawingModifier* AknEdwinDrawingModifier();
    TBool EditorSupportsNeutralProtection() const;

    /**
    * Main routine for neutral protection.  This routine returns a boolean stating if there is a
    * requirement for protection, but also returns the text that should replace the to-be-deleted text.
    * 
    * @param aPosOfLosEndOfDelete   index of the first character deleted
    * @param aLengthToDelete        length the text to be deleted
    * @param aNewText               neutral protection characters to replace the delete 
    * @param aForwardProtectionNeeded EFalse if only reverse protection needed; data valid only if 
    *                               method does not return EFalse.
    * @return                       EFalse iff no deletion is to be performed
    */
    TBool NeedsNeutralProtection( TInt aPosOfLowEndOfDelete, TInt aLengthToDelete, TDes& aNewText, TBool& aForwardProtectionNeeded );

    /**
    * Returns whether the character is strongly directional
    *
    * @param    aChar   character to be examined
    * @param    aRightToLeft    This is valid upon return only if EFalse is not returned. 
    *                           Value is EFalse if the strong directionality is Left-to-right
    * @return   EFalse if the character is not strongly directional.  
    */
    TBool GetStrongDirectionality(TChar aChar, TBool& aRightToLeft ) const;

    /**
    * Returns ETrue if the character at aPos is neutral
    *
    * @param    aPos    index in editor; must be a valid index
    * @return           EFalse iff the character is not neutral
    */
    TBool CharIsNeutral( TInt aPos ) const;

    /**
    * Looks through the passed descriptor, looking for a strongly directional character.  
    * Direction of search can be set. Search starts at the begining if searching forward; 
    * starts at the end if searching backwards.
    * 
    * Search is carried out until a strong character is found or the end (or beginning) 
    * of the descriptor has been reached.
    * 
    * @param aText      Descriptor to search.
    * @param aForward   If EFalse, then search is backward (decreasing index) in logical buffer
    * @param aIsRightToLeft     Set to ETrue on return if first strong character found is RTL
    *
    * @return           EFalse if no strong character was found.
    */
    TBool GetExposedDirectionOfTextInDescriptor( const TDesC& aText, TBool aForward, TBool& aIsRightToLeft ) const;

    /**
    * Looks through the editor's text starting at character aPos, looking for a
    * strongly directional character.  Direction of search can be set.
    * Search is carried out until a strong character is found or the end (or beginning) 
    * of the editor text has been reached.
    * 
    * @param aPos       First character to look at
    * @param aForward   If EFalse, then search is backward (decreasing index) in logical buffer
    * @param aIsRightToLeft     Set to ETrue on return if first strong character found is RTL
    *
    * @return           EFalse if no strong character was found.
    */
    TBool GetExposedDirectionOfText( TInt aPos, TBool aForward, TBool& aIsRightToLeft ) const;

    /**
    * Routine to perform the operation of replacing a selection with new text. 
    * This is intended for internal use.
    * 
    * The current selection, if non-zero length is deleted, and replace with aNewText if non-zero length
    * iTextView must be set.
    * 
    * @param aNewText               Replacement text. May be zero length.
    * @param aCursorPosInNewText    This is the position, relative to the beginning of the newtext,
    *                               that you want the cursor to be at when the operation is complete
    * @param aFormatHasChanged  Set this to ETrue if you want the reformatting to start at
    *                           the beginning of the paragraph. EFalse if just to reformat the line.
    *                           This variable may also be set by the call to DeleteHighlight that this
    *                           code executes, so it may be set to ETrue upon return, even if EFalse was
    *                           passed.
    */
    void ReplaceSelectionWithTextL( const TDesC& aNewText, 
                                    TInt aCursorPosInNewText,
                                    TBool& aFormatHasChanged );

    /**
    * Returns EFalse iff ( phone number had only numeric input modes AND the keymap is a phone number
    * type keymap ). 
    * Phone number type keymaps are:
    *   EAknEditorStandardNumberModeKeymap
    *   EAknEditorFixedDiallingNumberModeKeymap
    *
    * @return       EFalse if the phone number will only contain a pure phone number
    */
    TBool IsPurePhoneNumberEditor() const;

    /**
    * Standard check on upper and lower formatting thresholds versus current textview formatting mode.
    *
    * @return       EFalse iff the formatting mode does not need changing
    */ 
    TBool NeedToChangeFormattingModeL() const;         	

protected:	// from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	
public: // new since 3.0
    IMPORT_C void SetTextSkinColorIdL(TInt aAknSkinIdForTextColor);
    IMPORT_C void SetHighlightStyleL(TAknsHighlightStyle aStyle);
    
    // for custom drawer, not exported
    TInt SkinColorId() const;
    TAknsHighlightStyle HighlightStyle() const;
    TRgb EditorBackgroundColor(TRgb& aConditionalColor) const;
         	
	
protected:
	TUint32 iEdwinUserFlags;
	TUint32 iEdwinInternalFlags;
	CPlainText* iText;
protected: // Internal to Symbian
	CTextView* iTextView;
	CTextLayout* iLayout;
protected:
	TInt iTextLimit;
	TInt iNumberOfLines;
	MGraphicsDeviceMap* iZoomFactor;
	TInt iLastPointerDocPos;
	TMargins8 iMargins;
private:
	friend class CEikEdwinFepSupport;
	friend class CEikEdwinExtension;
	// added this class to allow additional data members without breaking BC
	CEikEdwinExtension* iEdwinExtension; // replaced iSetScrollBar
	CEikScrollBarFrame* iSBFrame;
	MEikEdwinObserver* iEdwinObserver;
	CArrayPtr<MEikEdwinObserver>* iObserverArray;
	CEikEdwinFepSupport* iEdwinFepSupport;
	CUndoBuffer* iUndoStore;
	TInt iAvgLinesInViewRect;
	TInt iAvgCharsPerLine;
	TInt iRightWrapGutter;
	TInt iLayoutWidth;
	MEikEdwinSizeObserver* iEdwinSizeObserver;
	TInt iMinimumHeight;
	TInt iMaximumHeight;
/* 
iMaximumHeightInLines
---------------------
This is simply a holder for the number, used to simplify some Avkon LAF requirements.
The viewable region of an edwin is actually measured in pixels, However, if certain LAF
requirements are enforced (that the view region has to be smaller than the number of 
lines viewable * the baseline separation (in pixels)) some undesired scrolling effects
occur.


That is to say, by simply setting iMaximumHeightInLines, this will not affect
the actual maximum height of the edwin.  To do this, you must set the iMaximumHeight

One of the use cases of this member variable is for AknLayoutUtils::LayoutEdwin. 
That method uses iMaximumHeightInLines along with the baseline separation, to set 
the iMaximumHeight.

The general formula is very simple, to remove unneeded scrolling.
iMaximumHeight=baselineSeparation*iMaximumNumberOfLines

If you cannot allocate sufficient space to the edwin, to permit so much viewable region
then the method AlterViewRect can be called on the TextView() component.  This will introduce
a clipping rectangle, which allows blank space required by the edwin layout component
to not be shown.
*/
	TInt iMaximumHeightInLines; 
	CLafEdwinCustomDrawBase* iCustomDrawer;
	TInt iLastPointerAnchorPos;
	CAknCcpuSupport* iCcpuSupport;
	CCharFormatLayer* iCharFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
	TInt iSpare_1;
	TInt iSpare_2;
	};


inline CEikScrollBarFrame* CEikEdwin::CreatePreAllocatedScrollBarFrameL()
	{ return CreateScrollBarFrameL(ETrue);}
inline CEikScrollBarFrame* CEikEdwin::ScrollBarFrame()
	{ return ((CEikScrollBarFrame* const)iSBFrame); }
inline TInt CEikEdwin::AvgLinesInViewRect() const
	{ return iAvgLinesInViewRect; }
inline TInt CEikEdwin::AvgCharsPerLine() const
	{ return iAvgCharsPerLine;}
inline void CEikEdwin::SetAvgLinesInViewRect(TInt aAvgLines)
	{ iAvgLinesInViewRect=aAvgLines; }
inline void CEikEdwin::SetAvgCharsPerLine(TInt aAvgChars)
	{ iAvgCharsPerLine=aAvgChars; }

inline void CEikEdwin::SetMaxLength(TInt aLength ) 
	{ SetTextLimit(aLength); }
inline TInt CEikEdwin::MaxLength() const 
	{ return iTextLimit; }

#endif
