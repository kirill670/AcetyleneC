/*
 *           vCard Bio Control 
 *           -------------------------
 * 
 *           SW Include Document - C++
 * 
/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Defines API for vCard Bio Control.

-----------------------------------------------------------------------------
*/

#if !defined(__VCARDBIOCONTROL_H__)
#define __VCARDBIOCONTROL_H__


#if !defined(__MSGBIOCONTROL_H__)
#include <msgbiocontrol.h>                      // for CMsgBioControl
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>                            // for MCoeControlObserver
#endif

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>                           // for CEikBorderedControl
#endif

#include "vcardcontrol.h"

// FORWARD DECLARATIONS

class CEikButtonGroupContainer;
class MMsgBioControlObserver;
class CEikLabel;
class CEikRichTextEditor;

class CVCardBioControl: public CMsgBioControl, public MCoeControlObserver
    {
    public:
        enum TMsgCommand
            {
            ECBASend   = 0,
            ECBADelete,		//Only used in Series 80
			ECBAAddressBook,
			ECBACreate,
			ECBADoNothing,
			ECBAClose
            };

    public:
        IMPORT_C static CMsgBioControl* NewL(MMsgBioControlObserver& aObserver, TZoomFactor& aZoomFactor, 
            CMsvSession& aSession, TMsvId aId);
        ~CVCardBioControl();

        public: // from CMsgBioControl
        void SetAndGetSizeL(TSize& aSize);
        void SetToolBarCommandSetL(CEikButtonGroupContainer& aToolBar);
        void HandleCommandL(TInt aCommand);
        TRect CurrentLineRect() const;
        void SetDataContentL(CRichText& aText);
        CRichText& DataContentL() const;
        void SetReadOnly(TBool aReadOnly);
        void ClipboardL(TMsgClipboardFunc aFunc);
        void EditL(TMsgEditFunc aFunc);
        TBool IsFocusChangePossible(TMsgFocusDirection aDirection) const;
        TBool IsClipboardFuncPossible(TMsgClipboardFunc aFunc) const;
        TBool IsEditFuncPossible(TMsgEditFunc aFunc) const;
        TBool IsCursorLocation(TMsgCursorLocation aLocation) const;
		TBool CursorInFirstLine() const;
        TBool CursorInLastLine() const;
        HBufC* GetHeaderIconAndTextL(CGulIcon& aIcon)  const;
        TInt PrepareForEventL(TMsgEvent /*aEvent*/) { return KErrNone; }
		void AddToContactsL();	//Only used in Series 80.

    public: // from CCoeControl
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        void GetHelpContext(TCoeHelpContext& aContext) const;


    public: // from MCoeControlObserver
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
		void HandleZoomL();
    
    protected: // from CCoeControl
	    TInt CountComponentControls() const;
	    CCoeControl* ComponentControl(TInt aIndex) const;
        void SizeChanged(); 
	    void FocusChanged(TDrawNow aDrawNow);
        void SetContainerWindowL(const CCoeControl& aContainer);

    private:
        CVCardBioControl(MMsgBioControlObserver& aObserver, TZoomFactor& aZoomFactor, CMsvSession& aSession, TMsvId aId);
        void ConstructL();
		void SetMsgReadL();
		TBool DeleteMsgL();		//Only used in Series 80.

    private: // not available
        CVCardBioControl();
        CVCardBioControl(const CVCardBioControl& aSource);
        const CVCardBioControl& operator=(const CVCardBioControl& aSource);

    private:
		CMsvEntry*			iMsvEntry;
		TFileName			iFileName;		//Only used in Series 80.
		TInt				iResourceFileOffset;
		CVCardControl*		iControl;
		TBool				iSending;
    };



#endif // __VCARDBIOCONTROL_H__

