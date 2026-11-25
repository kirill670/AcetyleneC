//vcalbiocontrol.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__VCalBIOCONTROL_H__)
#define __VCalBIOCONTROL_H__


#include <msgbiocontrol.h>                      // for CMsgBioControl
#include <coecobs.h>                            // for MCoeControlObserver
#include <eikbctrl.h>                           // for CEikBorderedControl, Only used in Series 80

// FORWARD DECLARATIONS

class CEikButtonGroupContainer;
class MMsgBioControlObserver;
class CEikLabel;
class CVCalEditor;
class CParserVCal;
class CCknFloatingProgressBall;
class CVCalBioControl: public CMsgBioControl, public MCoeControlObserver
    {
    public:

	enum TMsgCommand 
	    {
		ECBASend,
		ECBARecipient,
		ECBAOptions,
		ECBAClose,
		ECBAReply,	//Only used in Series 80
		ECBAAddToCal,
		ECBARemoveFromCal,
		ECBADelete
        };
    public:
        IMPORT_C static CMsgBioControl* NewL(MMsgBioControlObserver& aObserver, TZoomFactor& aZoomFactor, 
            CMsvSession& aSession, TMsvId aId);
        ~CVCalBioControl();

        public: // from CMsgBioControl
        void SetAndGetSizeL(TSize& aSize);
        void SetToolBarCommandSetL(CEikButtonGroupContainer& aToolBar);
        void HandleCommandL(TInt aCommand);
        TRect CurrentLineRect() const;
        //void SetDataContentL(CRichText& aText);
        //CRichText& DataContentL() const;
        void SetReadOnly(TBool aReadOnly);
        void ClipboardL(TMsgClipboardFunc aFunc);
        void EditL(TMsgEditFunc aFunc);
        TBool IsFocusChangePossible(TMsgFocusDirection aDirection) const;
        TBool IsClipboardFuncPossible(TMsgClipboardFunc aFunc) const;
        TBool IsEditFuncPossible(TMsgEditFunc aFunc) const;
        TBool IsCursorLocation(TMsgCursorLocation aLocation) const;
        HBufC* GetHeaderIconAndTextL(CGulIcon& aIcon)  const;
        TInt PrepareForEventL(TMsgEvent /*aEvent*/) { return KErrNone; }

        //HKO
        virtual void GetHelpContext(TCoeHelpContext& aContext) const;
    public: // from CCoeControl
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    public: // from MCoeControlObserver
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    
    protected: // from CCoeControl
	    TInt CountComponentControls() const;
	    CCoeControl* ComponentControl(TInt aIndex) const;
        void SizeChanged(); 
	    void FocusChanged(TDrawNow aDrawNow);
        void SetContainerWindowL(const CCoeControl& aContainer);

    private:
        CVCalBioControl(MMsgBioControlObserver& aObserver, TZoomFactor& aZoomFactor, CMsvSession& aSession, TMsvId aId);
        void ConstructL();
        CEikLabel* CreateCaptionL(const TDesC& aText);
        TBool CursorInFirstLine() const;
        TBool CursorInLastLine() const;

		void OptionsL();
		TBool DeleteMsgL();	//Only used in Series 80
		void SetMsgReadL();
		void AddToCalendarL();	//Only used in Series 80
		void RemoveFromCalendarL();

    private: // from CCoeControl
	    void Draw(const TRect& aRect) const;

    private: // not available
        CVCalBioControl();
        CVCalBioControl(const CVCalBioControl& aSource);
        const CVCalBioControl& operator=(const CVCalBioControl& aSource);

    private:
        CVCalEditor*		iEditor;
		CParserVCal*		iVCal;
		CMsvEntry*			iMsvEntry;
		TFileName			iFileName;	//Only used in Series 80
		TInt				iResourceFileOffset;
		TInt				iSending;
		CCknFloatingProgressBall*   iprogressball;	//Only used in Series 80
    };



#endif // __VCalBIOCONTROL_H__

