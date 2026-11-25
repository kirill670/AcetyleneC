/*
* ==============================================================================
*  Name        : eikfard.h
*  Part of     : CKON
*  Interface   : Find and Replace API
*  Description : Find and replace dialog.
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



#ifndef EIKFARD_H
#define EIKFARD_H


// INCLUDES
#include <e32std.h>
#include <coecntrl.h>
#include <e32def.h>
#include <eikgted.h>
#include <CknObjectType.h>


// DATA TYPES

/** The maximum length for the Find and Replace string */
const TInt KMaxFindAndReplaceStringLength = 256;


// FORWARD DECLARATIONS


// CLASS DECLARATIONS

/**
 * The <code>CEikFindAndReplaceDialog</code> class provides a Find and Replace 
 * dialog, which allows the user to pass Find and Replace instructions to text 
 * editors.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikFindAndReplaceDialog : public CEikDialog
    {
    public:  // Declarations
    // New methods
        /**
        * <code>RunDlgLD</code> runs the Find and Replace dialog. Find and 
        * Replace instructions are communicated to <code>aObserver</code>.The
        * dialog will always be positioned at the bottom right of the screen. 
		* <code>aEdwinRect</code> is not currently used.
        * If <code>aFindOnly</code> is <code>ETrue</code>, the dialog will 
		* display only the Find line and not the Replace line.
        * If <code>aModel.iReplaceOption</code> is set to <code>ENoReplace</code>. 
        * the replace button will not be present.
        * The maximum Find and Replace string lengths are 
        * <code>EEikEdwinFindStringMaxLen</code>.
        *
        * @param aObserver Observes Find and Replace instructions
        * @param aModel Contains the find text and criteria
        * @param aFindOnly Whether it is a find only. If <code>ETrue</code>,
        *                  the dialog will open the Find line only
        * @param aEdwinRect The boundary rectangle of the control containing the 
		*					text being searched (not currently used)
        * @param aOptionsObserver Observes Find and Replace options 
		*                         instructions
        * @remarks
        * @see
        */
        IMPORT_C static void RunDlgLD(MEikFindAndReplaceDlgObserver& aObserver, 
                                  SEdwinFindModel& aModel, 
                                  TBool aFindOnly, 
                                  TRect aEdwinRect,
                                  MEikFindAndReplaceDlgOptionsDialogObserver* aOptionsObserver=NULL);

        /**
        * <code>RunDlgLD</code> runs the Find and Replace dialog. Find and 
        * Replace instructions are communicated to <code>aObserver</code>. The
        * dialog will always be positioned at the bottom right of the screen. 
        * If <code>aFindOnly</code> is <code>ETrue</code>, the dialog will 
		* display only the Find line and not the Replace line, 
        * If <code>aModel.iReplaceOption</code> is set to <code>ENoReplace</code>. 
        * the replace button will not be present.
        * If <code>aMaxLenFindText</code> or <code>aMaxLenReplaceText</code> 
        * are set to <code>0</code>, no custom limitation is to be applied and 
        * the default edwin find text length limit, 
        * <code>EEikEdwinFindStringMaxLen</code>, will be applied for that text 
        * string.
        *
        * @param aObserver Observes Find and Replace instructions
        * @param aModel Contains the find text and criteria
        * @param aFindOnly Whether it is a find only. If <code>ETrue</code>,
        *                  the dialog will open only the find line
        * @param aObjectType The object type, for example 'document'
				 (<code>EObjectTypeDocument</code>). This is used to determine
				 the text in an info print if the object being edited is read only.
        * @param aMaxLenFindText The maximum find text length 
        * @param aMaxLenReplaceText The maximum replace text length
        * @param aOptionsObserver Observes Find and Replace options 
		*                         instructions
        * @remarks
        * @see <code>TCknObjectType</code> in cknobjectype.h
        */
        IMPORT_C static void RunDlgLD(MEikFindAndReplaceDlgObserver& aObserver, 
                                  SEdwinFindModel& aModel, 
                                  TBool aFindOnly,
                                  TCknObjectType aObjectType,
                                  TInt aMaxLenFindText=KMaxFindAndReplaceStringLength, 
                                  TInt aMaxLenReplaceText=KMaxFindAndReplaceStringLength, 
                                  MEikFindAndReplaceDlgOptionsDialogObserver* aOptionsObserver=NULL);

        /**
        * @deprecated
        */
        IMPORT_C static void RunDlgLD(MEikFindAndReplaceDlgObserver& aObserver, 
                                  SEdwinFindModel& aModel, 
                                  TBool aFindOnly, 
                                  TRect aEdwinRect, 
                                  TInt aMaxLenFindText, 
                                  TInt aMaxLenReplaceText, 
                                  MEikFindAndReplaceDlgOptionsDialogObserver* aOptionsObserver=NULL);

    // Constructors and destructor


        /**
        * The object destructor.
        */
        ~CEikFindAndReplaceDialog();

    // Methods from base classes

        /**
        * Returns help information about the dialog.
        *
        * @param aContext Filled in with help details
        * @remarks
        * @see CCoeControl
        */
        void GetHelpContext(TCoeHelpContext& aContext) const;

        /**
        * Handles a change to the control's resources that are shared across 
		* the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @return
        * @remarks
        * @see CCoeControl
        */
    void HandleResourceChange(TInt aType);

private: //C'tor
    CEikFindAndReplaceDialog(MEikFindAndReplaceDlgObserver& aObserver,
        SEdwinFindModel& aModel, TBool aFindOnly, TRect aEdwinRect, MEikFindAndReplaceDlgOptionsDialogObserver* aOptionsObserver,
        TInt aMaxLenFindText, TInt aMaxLenReplaceText);
public: 
        /**
        * Handles an event from an observed control.
        *
        * @param aControl The control
        * @param aEventType The event type
        * @remarks
        * @see <code>MCoeControlObserver</code> in coecobs.h
		* @see <code>TCoeEvent</code> in coecobs.h
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

private:
    enum TDialogPosition
        {
        EPositionDefault=0x01,
        EPositionTopRight
        };
private: // Framework
    void PostLayoutDynInitL();
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
    void SetSizeAndPosition(const TSize& aSize);
private:
    void DoAddButtonL(TInt aTextResourceId, TInt aOldBid, TInt aNewBid);
    void RemoveFindNextButton();
    void AddFindNextButtonL();
    void HandleReplacePressedL();
    void SelectAllTextL();
    void RunOptionsDialogL();
    void AddReplaceLineL(TBool aLayout=ETrue);
    void DoFirstFindL();
    void DimReplace(TBool aDimmed);
    TInt GetReadOnlyResource();
    void LoadSpecialCharacterSetL();
    void InitialiseFindMode();
    void PositionDialog(TDialogPosition aPosition=EPositionDefault);
    void DimFindAndReplace();
    void TryChangeReplaceButtonTextL();
private:
    class COptionsDlg : public CEikDialog
        {
    public:
        static TBool RunDlgLD(SEdwinFindModel& aModel, TBool aFindOnly);
        //from CCoeControl
        void GetHelpContext(TCoeHelpContext& aContext) const;
    private:
        COptionsDlg(SEdwinFindModel& aModel, TBool aFindOnly);
    private: 
        // from CEikDialog
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aButtonId);
    private:
        SEdwinFindModel& iModel;
        TBool iFindOnly;
        };
private:
    MEikFindAndReplaceDlgObserver&  iObserver;
    SEdwinFindModel&                iModel;
    TBool                           iFindOnly;
    TBool                           iFirstFind;
    TRect                           iEdwinRect;
    MEikFindAndReplaceDlgOptionsDialogObserver* iOptionsObserver;
    TInt                            iMaxLenFindText;
    TInt                            iMaxLenReplaceText;
    TCknObjectType                  iObjectType;
    HBufC*                          iSpecialCharSet;
    TDialogPosition                 iDialogPosition;
    };

#endif
