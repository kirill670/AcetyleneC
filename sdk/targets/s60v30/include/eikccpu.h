#ifndef EIKCCPU_H
#define EIKCCPU_H

#include <coecntrl.h>
#include <eikdef.h>
#include <eikmobs.h>
#include <babitflags.h>
#include <AknControl.h>

class CEikButtonGroupContainer;
class CEikMenuBar;


//
// MEikCcpuEditor
//
class MEikCcpuEditor
	{
public:
	virtual TBool CcpuIsFocused() const = 0;
	virtual TBool CcpuCanCut() const = 0;
	virtual void CcpuCutL() = 0;
	virtual TBool CcpuCanCopy() const = 0;
	virtual void CcpuCopyL() = 0;
	virtual TBool CcpuCanPaste() const = 0;
	virtual void CcpuPasteL() = 0;
	virtual TBool CcpuCanUndo() const = 0;
	virtual void CcpuUndoL() = 0;
	};


//
// CAknCcpuSupport
//
class CAknCcpuSupport : public CAknControl, public MEikMenuObserver
	{
public:
	IMPORT_C CAknCcpuSupport(MEikCcpuEditor* aEditor);
	IMPORT_C ~CAknCcpuSupport();
	IMPORT_C void ConstructL();

	IMPORT_C void HandleSelectionChangeL();
	IMPORT_C void HandleFocusChangeL();

	// from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	// from MEikMenuObserver
	IMPORT_C void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
	IMPORT_C void ProcessCommandL(TInt aCommandId);

private:
	void UpdateCBALabelsL();
	TBool UpdateCBALabelL(TInt aPosition, TInt aCommandId, TInt aTextResId);
	void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	TBitFlags iFlags;

	// Owned
	CEikButtonGroupContainer* iCba;

	// Not owned
	CEikMenuBar* iMenu;
	MEikCcpuEditor* iEditor;
	};




#endif
