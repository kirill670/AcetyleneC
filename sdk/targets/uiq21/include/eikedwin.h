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
#include <eikbctrl.h>
#include <eikedwob.h>
#include <eiksbfrm.h>

class CGlobalText;
class CParaFormatLayer;
class CCharFormatLayer;
class MLayDoc;
class CEikEdwinExtra;
class CLafEdwinCustomDrawBase;
class CLafEdwinCustomWrapBase;
class CEikonEnv;


const TUid KUidEdwinClipboardObserverTls={0x1000AD19};

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

 /**
 * The CEikEdwinDefaultClipboard class provides the default implementation of the Clipboard 
 * functions defined in MEikEdwinClipboardObserver.
 * 
 * @internal
 * @since App-Framework_6.2
 */
//class CEikEdwinDefaultClipboard

class CEikEdwinDefaultClipboard : public CBase, public MEikEdwinClipboardObserver
	{
public:
	IMPORT_C static CEikEdwinDefaultClipboard* NewL(CEikonEnv& aEikEnv);
public:
	void HandleNothingSelected(TClipboardFunc aClipboardFunc);
	void HandleCopiedToClipboard();
	void Release();
private:
	CEikEdwinDefaultClipboard(CEikonEnv& aEikEnv);
private: // from MEikEdwinClipboardObserver
	void MEikEdwinClipboardObserver_Reserved_1();
private:
	CEikonEnv& iEikEnv;
	};

/**
 * The CEikEdwinClipboardObserverTls class implements global static storage and access to the object 
 * providing the default implementation of clipboard feedback.
 *
 * @since App-Framework_6.2
 */
//class CEikEdwinClipboardObserverTls
 
class CEikEdwinClipboardObserverTls : public CCoeStatic
	{
public:
	IMPORT_C static void SetL(MEikEdwinClipboardObserver* aClipboardObserver);
public:
	static MEikEdwinClipboardObserver* Current();
public:
	~CEikEdwinClipboardObserverTls();
private:
	inline CEikEdwinClipboardObserverTls();
	inline static CEikEdwinClipboardObserverTls* Self();
private:
	MEikEdwinClipboardObserver* iClipboardObserver;
	};

inline CEikEdwinClipboardObserverTls::CEikEdwinClipboardObserverTls()
	: CCoeStatic(KUidEdwinClipboardObserverTls)
	{}

inline CEikEdwinClipboardObserverTls* CEikEdwinClipboardObserverTls::Self()
	{
	return (static_cast<CEikEdwinClipboardObserverTls*>(CCoeEnv::Static(KUidEdwinClipboardObserverTls)));
	}


/**
 *
 * Base class for controls that display and allow manipulation of text.
 *
 * The properties of a particular Edwin object can be set using bitwise
 * flags, which are defined in member enums (see <code>TFlags</code> for
 * example).Edwins support Front End Processors if present on the target
 * machine, and so are a highly effective way of getting textual data
 * from the user. The text currently being composed by the user is called
 * the composition text.
 *
 * @since 6.0
 * @lib " eikcoctl.lib "
 */
class CEikEdwin : public CEikBorderedControl, public MEikScrollBarObserver, public CTextView::MObserver, public MEditObserver
	{
private:
	class CUndoBuffer;
public:
	/**
	 *
	 * The following flags may be combined with a bitwise OR to form the
	 * <code>aEdwinFlags</code> argument to <code>ConstructL(TInt, .
	 * ..)</code> or the flags field of an <code>EDWIN</code> resource
	 * structure run through <code>ConstructFromResourceL()</code>.These
	 * flags are duplicated in uikon.hrh (see
	 * <code>EEikEdwinKeepDocument</code> etc.)
	 */
	enum TFlags
		{ // user flags
		EKeepDocument			=0x00000001,			/** If set, the edwin does not destroy its content on destruction. */
		ESegmentedStorage		=0x00000002,			/** If set, the content buffer uses segmented storage (see <code>CEditableText::ESegmentedStorage</code>). */

		/** The size specified in the resource used to construct the object is
		given in pixels, not character widths.
		 */
		EWidthInPixels			=0x00000004,

		/** No automatic selection takes place. Normally the entire text is
		selected whenever the Edwin is created, resized or has its text set as
		one operation.
		 */
		ENoAutoSelection		=0x00000008,

		/** If set, then whenever the control is activated the cursor is moved to
		the end of the text.
		 */
		EJustAutoCurEnd			=0x00000010,
		ENoWrap					=0x00000020,			/** Do not wrap the text being edited. */
		ELineCursor				=0x00000040,			/** Use a line cursor instead of a block cursor. */
		ENoHorizScrolling		=0x00000080,			/** Do not perform horizontal scrolling. */

		/** If set, scroll bars required to edit long documents appear inside the
		Edwin. This reduces the area used to display the Edwin.If not set,
		scroll bars appear outside the Edwin.
		 */
		EInclusiveSizeFixed		=0x00000100, 
		EUserSuppliedText		=0x00000200,			/** Set the Edwins height according to the number of lines of text supplied by the user. */
		EOwnsWindow				=0x00000400,			/** The Edwin is a window-owning control. */
		EDisplayOnly			=0x00000800,			/** The Edwin does not respond to input at all. */
		EAlwaysShowSelection	=0x00001000,			/** Do not hide the selection if the Edwin loses focus. */

		/** The Edwin is read-only so users cannot add text to any document it
		displays. A user attempt to add text results in a message to notify
		them that the Edwin is read-only.
		 */
		EReadOnly				=0x00002000,

		/** If set, no special attempt to delete embedded pictures cleanly will be
		made.This flag does not apply to Edwins which do not edit rich text.
		 */
		EAllowPictures			=0x00004000,
		EAllowUndo				=0x00008000,			/** The Edwin supports undo operations. */
		ENoLineOrParaBreaks		=0x00010000,			/** Do not allow line or paragraph breaks in the text being edited. */
		EOnlyASCIIChars			=0x00020000,			/** Allow only ASCII characters. */
		EResizable				=0x00040000,			/** The Edwin is resizable. */
		EIgnoreVirtualCursor	=0x00080000,			/** The Edwin ignores the virtual cursor. */
		ENoCustomDraw			=0x01000000,
		ECustomWrap				=0x02000000,
		ENoTextParsers			=0x04000000,
		};
	/**
	 * The following symbols specify actions for ClipboardL().
	 */
	enum TClipboardFunc
		{
		ENoClipboard,									/** Do nothing. */
		ECut,											/** Cut. */
		ECopy,											/** Copy. */
		EPaste											/** Paste. */
		};
	/**
	 * The following flags may be ORed together for text searches (see
	 * <code>FindL()</code> for example).
	 */
	enum TFindFlags
		{
		EFindDirectionUp	=0x01,						/** Search progresses up the screen. */
		EFindWholeWord		=0x02,						/** Only whole-word matches count. */
		EFindCaseSensitive	=0x04,						/** Search is case-sensitive. */
		EFindAgain			=0x08,						/** Find again. */
		ENoBusyMessage		=0x10,						/** Dont display a busy message. */
		EReadOnlyFile		=0x20 // New for CKon
		};
	/**
	 * When content is supplied to an Edwin using SetDocumentContentL(), the
	 * Edwin can either copy the supplied content into its existing content,
	 * or it can replace its existing content with the supplied content.
	 */
	enum TSetContent
		{
		EUseText,										/** Replace the Edwins existing content. */
		ECopyText										/** Copy the supplied content into the existing content. */
		};
	/**
	 * Specifies whether the Edwin owns the document it is being used to
	 * edit.
	 * If the Edwin owns the document, the document object is destroyed on
	 * destruction.
	 */
	enum TOwnershipType
		{
		EOwnsText,										/** Document is owned by the Edwin. */
		EDoesNotOwnText									/** Document is owned by some other object. */
		};
	/**
	 * Order of hotkeys defined an Edwin resource structure.
	 * Not all are applicable to plain text editors.
	 */
	enum TEdwinHotKeys
		{
		EHotKeyCut,										/** Cut. */
		EHotKeyCopy,									/** Copy. */
		EHotKeyPaste,									/** Paste. */
		EHotKeyUndo,									/** Undo. */
		EHotKeyFind,									/** Find. */
		EHotKeyInsertChar,								/** Insert a character. */
		EHotKeyBold,									/** Bold. */
		EHotKeyItalic,									/** Italic. */
		EHotKeyUnderline,								/** Underline. */
		EHotKeyFont,									/** Font. */
		EHotKeyInsertObject,							/** Insert an object. */
		EHotKeyEditObject,								/** Edit an object. */
		EHotKeyFormatObject								/** Format an object. */
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
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
	IMPORT_C void SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities); // not available before Release 006
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
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
	IMPORT_C void SetEdwinClipboardObserverL(MEikEdwinClipboardObserver* aEdwinClipboardObserver, TBool aOwnedExternally);
	IMPORT_C TInt MinimumHeight() const;
	IMPORT_C TInt MaximumHeight() const;
	IMPORT_C void SetMinimumHeight(TInt aHeight);
	IMPORT_C void SetMaximumHeight(TInt aHeight);
	IMPORT_C TInt CalculateHeight();
public: // new utility methods
	IMPORT_C void InsertDeleteCharsL(TInt aInsertPos,const TDesC& aText,const TCursorSelection& aDelete);
	IMPORT_C void SetNonPrintingCharsVisibility(TNonPrintingCharVisibility aVisibility);
	IMPORT_C TNonPrintingCharVisibility NonPrintingCharsVisibility() const;
public: // Internal to Symbian
	// the following methods are deprecated and will be removed in a future release
	IMPORT_C void CreateTextViewL();
	IMPORT_C CTextView* TextView() const;
	IMPORT_C CTextLayout* TextLayout() const;
	IMPORT_C TBool SetUndoBufferL(const TCursorSelection& aSelection);
	IMPORT_C void SetUndoableText(const TCursorSelection& aSelection);
protected:
	/**
	 * Specifies the end points of the editable area.
	 */
	enum TEnd
		{
		EStart,			/** The start of the editable area. */
		EEnd			/** The end of the editable area. */
		};
	/**
	 * Specifies the chunk size as either a word, or a paragraph.
	 */
	enum TChunkSize
		{
		EChunkWord,		/** A word. */
		EChunkPara		/** A paragraph. */
		};
	enum TEikEdwinFlags
		{ // internal flags
		ERichText           =0x00000001,
		EDragDouble			=0x00000002,
		ELeftDownInViewRect =0x00000004,
		ENumericCharacters	=0x00000008 // only used to calculate initial width
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
protected: // Internal to Symbian
	IMPORT_C void CreateLayoutL(MLayDoc* aLayDoc);
	IMPORT_C void CreateTextAndLayoutL(CParaFormatLayer* aParaFormatLayer,CCharFormatLayer* aCharFormatLayer);
protected:
	void CheckCreateExtensionL();
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
	void CheckEdwinHeight(TInt& aHeight);
	TBool IsNewHeightWithinMinimumAndMaximum(TInt aNewHeight) const;
	void SetEdwinHeight(TInt aHeight);
	void DoCreateCustomDrawL();
	void DoCreateCustomWrapL();
	void HandleCapsLockMessage();
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TInt HeightForNumOfLines();
	void SetLayoutFormat(TBool aIsUpperThresholdFull=EFalse);
	void SetUpTextCursor();
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
	CIdle* iSetScrollBar;
	CEikScrollBarFrame* iSBFrame;
	MEikEdwinObserver* iEdwinObserver;
	CArrayPtr<MEikEdwinObserver>* iObserverArray;
	CEikEdwinExtra* iEdwinExtra; // replaces CEikEdwinFepSupport* iEdwinFepSupport
	CUndoBuffer* iUndoStore;
	TInt iAvgLinesInViewRect;
	TInt iAvgCharsPerLine;
	TInt iRightWrapGutter;
	TInt iLayoutWidth;
	MEikEdwinSizeObserver* iEdwinSizeObserver;
	TInt iMinimumHeight;
	TInt iMaximumHeight;
	CLafEdwinCustomDrawBase* iCustomDrawer;
	TInt iLastPointerAnchorPos;
	};


/**
 *
 * Creates a pre-allocated scroll bar frame.
 *
 * @returns   " CEikScrollBarFrame* "
 *            Pre-allocated scroll bar frame.
 */
inline CEikScrollBarFrame* CEikEdwin::CreatePreAllocatedScrollBarFrameL()
	{ return CreateScrollBarFrameL(ETrue);}

/**
 *
 * Gets the scroll bar frame surrounding this Edwin.
 *
 * @returns   " CEikScrollBarFrame* "
 *            Pointer to this Edwins scroll bar frame.
 */
inline CEikScrollBarFrame* CEikEdwin::ScrollBarFrame()
	{ return ((CEikScrollBarFrame* const)iSBFrame); }

/**
 *
 * Gets the average number of lines shown in Edwins view.
 *
 * @returns   " TInt "
 *            The average number of lines.
 */
inline TInt CEikEdwin::AvgLinesInViewRect() const
	{ return iAvgLinesInViewRect; }

/**
 *
 * Gets the average number of characters on a line.
 *
 * @returns   " TInt "
 *            The average number of characters on a line.
 */
inline TInt CEikEdwin::AvgCharsPerLine() const
	{ return iAvgCharsPerLine;}

/**
 *
 * Sets the average number of lines displayed in Edwins view.
 *
 * @param     " TInt aAvgLines "
 *            The average number of lines to display.
 */
inline void CEikEdwin::SetAvgLinesInViewRect(TInt aAvgLines)
	{ iAvgLinesInViewRect=aAvgLines; }

/**
 *
 * Sets the average number of characters per line.
 *
 * @param     " TInt aAvgChars "
 *            The average number of characters per line.
 */
inline void CEikEdwin::SetAvgCharsPerLine(TInt aAvgChars)
	{ iAvgCharsPerLine=aAvgChars; }


#endif
