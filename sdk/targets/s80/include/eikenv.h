/*
* ==============================================================================
*  Name        : eikenv.h
*  Part of     : UIKON
*  Interface   : Environment API
*  Description : Application environment classes.
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


#ifndef EIKENV_H
#define EIKENV_H

//** INCLUDES *
#include <uikon.hrh>
#include <coemain.h>
#include <coedef.h>
#include <eikdef.h>
#include <gulalign.h>
#include <apaflrec.h>
#include <apacmdln.h>
#include <badesca.h>
#include <baerrhan.h>
#include <gulcolor.h>
#include <eikaufty.h>
#include <eiklibry.h>
#include <eikamnt.h>
#include <lafmain.h>
#include <skin.h>
#include "eikvcurs.h"

//** FORWARD DECLARATIONS *
class CEikProcess;
class CEikInfoMsgWin;
class CEikBusyMsgWin;
class CEikAppUi;
class CEikHotKeyTable;
class CCoeControl;
class CParaFormatLayer;
class CCharFormatLayer;
class CCoeBrushAndPenContext;
class CEikCommandButton;
class CPrintSetup;
class CDictionaryStore;
class CApaWindowGroupName;
class CEikErrorIdler;
class CEikApplication;
class MEikInfoDialog;
class MEikAlertWin;
class CEikDialog;
class MEikDebugKeys;
class CEikLibrary;
class MEikAppUiFactory;
class MEikIrFactory;
class CGulIcon;
class CApaMaskedBitmap;
class CEikLogicalBorder;
class CEikLafEnv;
class TLogicalFont;
class CEikPictureFactory;
class CEikEnvExtra;
class MCknFepControlObserver;
class MEikCDlgDialogFactory;
class MEikPrintDialogFactory;
class MEikFileDialogFactory;
class CEikScreenClearerWin;

//** CONSTANTS *

/**
 * the default cursor width
 * @publishedPartner
 * @released
 */
const TInt KEikDefaultCursorWidth=2;

/**
 * the default time between clicks, in microseconds
 * @publishedPartner
 * @released
 */
const TInt KTimeBetweenClicks=1000000; 

/**
 * the default distance between clicks
 * @publishedPartner
 * @released
 */
const TInt KDoubleClickDistance=10;

/**
 * the default keyboard repeat rate
 * @publishedPartner
 * @released
 */
const TInt KKeyboardRepeatRate=50000;

/**
 * the default keyboard initial delay
 * @publishedPartner
 * @released
 */
const TInt KKeyboardRepeatInitialDelay=800000;

/**
 * @internal Component
 */
const TUid KSystemIniFileUid = {0x1000010C};

/**
 * @internal Component
 */
const TUid KUikonLibraryUid = {KUidUikonLibraryValue};

/**
 * the maximum length of text used by the error resolver
 * @publishedPartner
 * @released
 */
const TInt KEikErrorResolverMaxTextLength = 256;

/**
 * Message UID
 * CEikApplicationKey sends this message to the cycling FEP of the foreground application
 * when the key sequence <func>+application is pressed to avoid launch of character map
 * dialog.
 */
const TInt KUidFepCancelDialogLaunchMesgValue = 0x101FAC5D;
const TUid KUidFepCancelDialogLaunchMesg = {KUidFepCancelDialogLaunchMesgValue};

//** DATA TYPES *

/**
 * Sets the method to call to set the query and info dialogs.
 * Initially, it is used to set the dialogs to <code>CCknInfoDialog</code>
 * and <code>CCknConfirmationDialog</code>.
 * @see SetQueryDialog
 * @see SetInfoDialog
 * @see CCknInfoDialog
 * @see CCknConfirmationDialog
 * @publishedAll
 * @released
 */
typedef void (*TRequestDialogFunc)();

/**
 * Creates the <code>CEikLibrary</code> interface object by calling the first
 * ordinal method that is mapped to the <code>NewL()</code> method. The method
 * leaves with <code>KErrBadLibraryEntryPoint</code> if the ordinal 1 method
 * cannot be found.
 *
 * @publishedPartner
 * @released
 * @internal
 */
typedef CEikLibrary* (*EikLibraryEntryPoint)();

/**
 * The <code>MEikPictureFactory</code> class is a mixin interface class that
 * provides support for embedding pictures. This class does not support 
 * <code>CApaDoor</code> picture objects or objects that have a picture type of
 * <code>KUidPictureTypeDoor</code>.
 * See apgdoor.h for more information on <code>CApaDoor</code>.
 * 
 * @lib eikcore.lib
 * @since 6.1
 */
class MEikPictureFactory
    {
public:

    /**
     * Gets the UID of the picture factory.
     *
     * @return the UID of the picture factory
     * @remarks The UID is not predefined for this class, but must not be
     *          of type <code>KUidPictureTypeDoor</code>
     * @see
     */
    IMPORT_C virtual TUid Id() const;

    /**
     * Determines whether the factory supports the specified picture type.
     *
     * @param aPictureType The UID of the picture type
     * @return <code>ETrue</code> if the factory supports the
     *         specified picture type; <code>EFalse</code> otherwise
     * @remarks Picture type <code>KUidPictureTypeDoor</code> is not supported
     * @see
     */
    virtual TBool SupportsPictureType(TUid aPictureType) const=0;

    /**
     * Gets a pointer to the real picture factory, 
     * <code>MPictureFactory</code>. Use of this method does not transfer 
     * ownership of the picture factory to the caller.
     *
     * @param aPictureType The picture type
     * @return the pointer to the picture factory
     * @remarks
     * @see MPictureFactory in gdi.h
     */
    virtual const MPictureFactory* PictureFactory(TUid aPictureType) const=0;

    /**
     * Inserts a new picture object. The ownership of <code>aData</code>
     * transfers as soon as the method is called.
     *
     * @param aPictureType The picture type
     * @param aData The base address of the data
     * @return the picture header
     * @remarks
     * @see TPictureHeader in gdi.h
     */
    virtual TPictureHeader InsertL(TUid aPictureType,CBase* aData)=0;

    /**
     * Enables a picture object to be edited, with the option of making it 
     * read-only, that is, any changes made to its content do not persist.
     *
     * @param aPictureHeader The picture header
     * @param aReadOnly If <code>ETrue</code> the object is read-only,
     *                  and changes made to its content do not persist;
     *                  if <code>EFalse</code> otherwise changes can be made
     * @remarks
     * @see TPictureHeader in gdi.h
     */
    virtual void EditL(const TPictureHeader& aPictureHeader,TBool aReadOnly)=0;

private:
    IMPORT_C virtual void MEikPictureFactory_Reserved_1();
    IMPORT_C virtual void MEikPictureFactory_Reserved_2();
    };

/**
 * The <code>CEikonEnv</code> class provides an environment for creating Uikon
 * controls. It provides utility functions for manipulating those controls.
 * Every Uikon application is provided with an instance of
 * <code>CEikonEnv</code> by the framework. This can be accessed through
 * either <code>CEikonEnv::Static()</code> or the <code>iEikonEnv</code>
 * macro of <code>CEikApplication</code>. This class is not intended for 
 * derivation.
 *
 * @lib eikcore.lib
 * @since 6.0
 */
class CEikonEnv : public CCoeEnv, public MApaAppStarter
    {
public:
    friend class CEikonEnvSkinObs;

    /**
     * The enumeration <code>TErrorValidity</code> specifies whether an error
     * code is valid or not.
     */
    enum TErrorValidity
        {
        /** the error is valid */
        EErrorNumValid,
        /** the error is not valid */
        EErrorNumInvalid
        };

public:
    /**
     * The object destructor. This method frees any resources acquired
     * by this <code>CEikonEnv</code> during its construction.
     *
     * @remarks
     * @see
     */
    IMPORT_C ~CEikonEnv();

    /**
     * The default object constructor. To be correctly initialized, the second-phase
     * constructor should be called after the constructor for the environment.
     *
     * @remarks
     * @see
     */
    IMPORT_C CEikonEnv();

    /**
     * Completes construction. This method initializes a new
     * <code>CEikonEnv</code> field. It allocates memory for
     * the new <code>CEikonEnv</code> object.
     *
     * @remarks
     * @see
     */
    IMPORT_C void ConstructL();

    /**
     * Completes construction. This method is called by the
     * previous constructor <code>ConstructL()</code>, with
     * <code>aInitialFocusState</code> of <code>ETrue</code>.
     *
     * @param aInitialFocusState The window group initial focus state. If
     *                           <code>ETrue</code>, keyboard focus is enabled;
     *                           if <code>EFalse</code>, keyboard focus is
     *                           disabled
     * @remarks
     * @see
     */
    IMPORT_C void ConstructL(TBool aInitialFocusState);

    /**
     * Initializes an application. This method constructs a new application
     * consisting of a <code>CEikAppUi</code>, a <code>CEikApplication</code>,
     * and a <code>CEikDocument</code>. The new Uikon application starts with
     * a new controlling process and runs in this Uikon environment. The new
     * application is passed any command line file using the method
     * <code>CEikAppUi::ProcessCommandParametersL()</code>.
     *
     * @param aCommandLine The command line used to initialize the new
     *                     application
     * @remarks This method is called by <code>EikDll::RunAppInsideThread()</code>
     * @see
     */
    IMPORT_C void ConstructAppFromCommandLineL(const CApaCommandLine& aCommandLine);

    /**
     * This method initializes the control stack.
     * It initializes debug preferences, constructs the debug keys, initializes 
     * the alert window, and creates a <code>CEikErrorIdler</code>.
     *
     * @remarks This method is called by <code>CEikAppUi::BaseConstructL()</code>
     * @see
     */
    IMPORT_C void ControlStackReadyL();

    /**
     * Gets the Uikon version that is currently running.
     *
     * @return the Uikon version class comprising:
     *         <code>aMajor</code> - the <code>TInt</code> major version
     *         number (0 to 127); <code>aMinor</code> - the <code>TInt</code>
     *         minor version number (0 to 99); <code>aBuild</code> - the
     *         <code>TInt</code> build number (0 to 32,767)
     * @remarks
     * @see
     */
    IMPORT_C static TVersion Version();

    /**
     * Gets the <code>CEikonEnv</code> maintained by the framework for the
     * application.
     * This method should never be run in a thread where such a static Uikon
     * environment does not exist, because it will not be  set up properly.
     * (Code that runs on the server side of an application server is 
     * such a case.)
     *
     * @return a static <code>CEikonEnv</code>
     * @remarks
     * @see CCoeEnv::Static()
     */
    inline static CEikonEnv* Static();

    /**
     * Gets the standard annotation font for this environment.
     *
     * @return the pointer to the annotation font
     * @remarks
     * @see
     */
    IMPORT_C const CFont* AnnotationFont() const;

    /**
     * Gets the standard title font for this environment.
     *
     * @return the pointer to the title font
     * @remarks
     * @see
     */
    IMPORT_C const CFont* TitleFont() const;

    /**
     * Gets the standard legend font for this environment.
     *
     * @return the pointer to the legend font
     * @remarks
     * @see
     */
    IMPORT_C const CFont* LegendFont() const;

    /**
     * Gets the standard symbol font for this environment.
     *
     * @return the pointer to the symbol font
     * @remarks
     * @see
     */
    IMPORT_C const CFont* SymbolFont() const;

    /**
     * Gets the standard dense font for this environment.
     *
     * @return the pointer to the dense font
     * @remarks
     * @see
     */
    IMPORT_C const CFont* DenseFont() const;

    /**
     * Gets the font that is the nearest match to the specified font.
     *
     * @param aLogicalFont The font for which a match is sought
     * @return the pointer to the font that most closely matches
     *         <code>aLogicalFont</code>
     * @remarks The return value is never <code>NULL</code>
     * @see
     */
    IMPORT_C const CFont* Font(const TLogicalFont& aLogicalFont) const;

    /**
     * Sets the cursor observer that allows a FEP to observe events from
     * controls, such as when a dialog is opened and when the cursor moves in 
     * editor controls. The FEP should call this to make itself the observer 
     * of the cursor position.
     *
     * @param aFepControlObserver The cursor observer
     * @remarks
     * @see MCknFepControlObserver in cknfepcontrolobserver.h
     */
    IMPORT_C void SetFepControlObserver(MCknFepControlObserver* aFepControlObserver);

    /**
     * Gets the current cursor observer.
     *
     * @return the current cursor observer
     * @remarks
     * @see
     */
    IMPORT_C MCknFepControlObserver* FepControlObserver();

    /**
     * This method is called by an editor to notify an observer that the
     * cursor position has changed. It informs the FEP of a change in the cursor
     * position.
     *
     * @remarks
     * @see
     */
    IMPORT_C void InformFepOfChangeInCursorPosition();

    /**
     * This method is called by an editor to notify the FEP observer
     * of a pen-down event.
     *
     * @remarks
     * @see
     */
    IMPORT_C void InformFepOfPenDownEvent();

    /**
     * This method is called by an editor to notify the FEP observer
     * of a pen-up event.
     *
     * @remarks
     * @see
     */
    IMPORT_C void InformFepOfPenUpEvent();

    /**
     * This method is called when a dialog is about to be displayed.
     * It adds the dialog to the dialog array maintained by <code>CEikonEnv</code>.
     * It also informs the FEP observer, so that it can access the dialog
     * in order to set its position. The FEP is also notified
     * that a dialog has been opened.
     *
     * @param aDialog The newly activated dialog
     * @remarks
     * @see
     */
    IMPORT_C void AddActiveDialogL(CCoeControl& aDialog);

    /**
     * This method is called when a dialog is dismissed so that the dialog
     * is removed from the list of active dialogs.
     *
     * @param aDialog The dialog that is being dismissed
     * @remarks
     * @see
     */
    IMPORT_C void RemoveActiveDialog(CCoeControl& aDialog);

    /**
     * The AppUI calls this method when a FEP requests that the position
     * of a dialog is changed.
     *
     * @return a pointer to the topmost active dialog
     * @remarks
     * @see
     */
    CCoeControl* TopActiveDialog() const;

public: //** internal to Symbian *
    /**
     * @internal
     */
    IMPORT_C const CFbsBitmap* TexturedBitmap() const;

public: //** Do not use *
    /**
     * @internal
     */
    IMPORT_C const CFbsBitmap* GrayBitmap() const;

    /**
     * Gets the bitmap that is used by the horizontal option buttons for this
     * environment.
     *
     * @return Pointer to the option bitmap.
     * @internal
     */
    IMPORT_C const CFbsBitmap* OptionBitmap() const;

    /**
     * @internal
     */
    IMPORT_C const CFbsBitmap* HighlightedOptionBitmap() const;

    /**
     * @internal
     */
    IMPORT_C const CFbsBitmap* OptionMaskBitmap() const;

public:
    /**
     * Gets the specified bitmap from the list of system bitmaps
     * maintained by <code>CEikonEnv</code> by using the UID as an index.
     * The UIDs for these bitmaps are defined in lafenv.h.
     *
     * @param aUidBmp The UID of the bitmap to retrieve
     * @return a pointer to the bitmap
     * @remarks
     * @see CFbsBitmap in fbs.h
     * @see lafenv.h
     */
    IMPORT_C const CFbsBitmap* Bitmap(TUid aUidBmp) const;

    /**
     * @internal
     */
    void InitSystemBitmapsL();

public: //** Internal to Symbian **
    /**
     * @internal
     */
    IMPORT_C MLafEnv& LafEnv() const;

    /**
     * Gets the standard height for an editable control, based on the normal font height.
     *
     * @internal
     * @since Series90 1.0
     * @return the height.
     * @remarks
     * @see
     */
    inline TInt EditableControlStandardHeight() const;

public:
    /**
     * Gets the Uikon process that manages the files of applications started
     * in this environment.
     *
     * @return the Uikon process object
     * @remarks
     * @see CEikProcess in eikproc.h
     */
    inline CEikProcess* Process() const;

    /**
     * Get the alert window for this environment.
     *
     * @since Series90 1.0
     * @return a pointer to the alert window
     * @remarks
     * @see MEikAlertWin is used by eikalert.h
     */
    inline const MEikAlertWin* Alert() const;

    /**
     * Gets the picture factory for this environment.
     *
     * @return the pointer to the picture factory
     * @remarks
     * @see MPictureFactory is in gdi.h
     */
    IMPORT_C MPictureFactory* PictureFactory()const;

    /**
     * Gets a picture factory object in the environment that supports the
     * specified picture type. If none exists, the method returns
     * <code>NULL</code>.
     *
     * @since 6.1
     * @param aPictureType The picture type
     * @return a picture factory that supports the picture type
     *         <code>aPictureType</code>; if no such factory
     *         exists in this environment, <code>NULL</code> is returned
     * @remarks
     * @see MEikPictureFactory
     */
    IMPORT_C MEikPictureFactory* ExtendedPictureFactory(TUid aPictureType) const;

    /**
     * Adds the picture factory to the set of factories maintained by the
     * Uikon environment. For a picture factory to be available system-wide,
     * <code>AddPictureFactoryL()</code> should normally be called during the
     * <code>InitializeL()</code> method of a <code>CEikLibrary</code>
     * derived class.
     *
     * @since 6.1
     * @param aFactory The picture factory to add
     * @remarks If there is insufficient memory available, the method
     *          leaves with <code>KErrNoMemory</code>
     * @see CEikLibrary in eiklibry.h
     */
    IMPORT_C void AddPictureFactoryL(MEikPictureFactory& aFactory);

    /**
     * Removes the specified picture factory, if it exists, from the set of
     * picture factories owned by the Uikon environment.
     *
     * @since 6.1
     * @param aFactoryId The ID of the picture factory to be removed
     * @remarks
     * @see
     */
    IMPORT_C void RemovePictureFactory(TUid aFactoryId);

    /**
     * Sets the alert window for this environment.
     *
     * @since Series90 1.0
     * @param aAlertWin A pointer to the alert window
     * @remarks
     * @see MEikAlertWin is used by eikalert.h
     */
    IMPORT_C void SetAlertWin(MEikAlertWin* aAlertWin);

    /**
     * Displays an alert window with a message on a single line.
     *
     * @param aMsg The line of text in the message
     * @remarks
     * @see
     */
    IMPORT_C void AlertWin(const TDesC& aMsg);

    /**
     * Displays an alert window with a brief message.
     *
     * @param aMsg1 First line of the message
     * @param aMsg2 Second line of the message
     * @remarks
     * @see
     */
    IMPORT_C void AlertWin(const TDesC& aMsg1,const TDesC& aMsg2);

    /**
     * Displays a formatted info message and then leaves.
     * This method calls <code>User::Leave(KLeaveWithoutAlert)</code>. This
     * is defined in basched.h.
     * <b>Note</b>: The number of parameters depends on the format of the 
     * string.
     *
     * @param aResourceId ID of a <code>TBUF</code> resource used to format the
     *                    string (see <code>TBuf::Format()</code>)
     * @param ... The list of items to be formatted
     * @remarks
     * @see
     */
    IMPORT_C void LeaveWithInfoMsg(TInt aResourceId,...);

public: //** Internal to Symbian *
    /**
     * @internal
     */
    IMPORT_C void LeaveWithErrorContext(TInt aError,const TDesC& aContextText);

    /**
     * Gets the error text for <code>aError</code> error code.
     * <code>TUid aAppUid</code> is set to <code>KNullUid</code>, which implies
     * that it is not looking for the application-specific errors.
     *
     * @param aDes On return, contains the error text
     * @param aError Error number
     * @remarks
     * @see Error codes in e32std.h
     * @since 7.0
     */
    IMPORT_C void GetErrorText(TDes& aDes,TInt aError) const;

    /**
     * Gets the error text for <code>aError</code> error code, in the application
     * identified by <code>aAppUid</code>. Returns whether the
     * error code is valid or not.
     *
     * @param aDes On return, contains the error text
     * @param aError The error number
     * @param aAppUid The application UID
     * @return <code>EErrorNumValid</code> if the error code is valid;
     *         <code>EErrorNumInvalid</code> if the error code is invalid
     * @remarks
     * @see Error codes in e32std.h
     * @since 7.0
     */
    IMPORT_C TErrorValidity GetErrorText(TDes& aDes,TInt aError,TUid aAppUid) const;

public:
    /**
     * Displays the error that has occurred via a dialog.
     *
     * @param aError The error number
     * @param aAppUid The application UID
     * @since 7.0
     * @remarks
     * @see Error codes in e32std.h
     */
    IMPORT_C void ResolveError(TInt aError,TUid aAppUid=KNullUid) const;

    /**
     * Sets the <code>InfoMsg</code> bitmap to the ID supplied.
     *
     * @param aBitmapCategory The bitmap category UID 
     * @param aBitmapId The bitmap ID
     * @remarks The default <code>InfoMsg</code> bitmap category is 
     *          <code>KUidSkinGeneralBitmaps</code> in skinuid.h, using the ID
     *          <code>EMbmSkingeneralQgn_note_infoprint</code>,
     *          which is found in skingeneral.mbg
     * @see
     */
    IMPORT_C void SetInfoMsgBitmapId(const TUid aBitmapCategory, TInt aBitmapId);

    /**
     * Resets the <code>InfoMsg</code> bitmap to the default image.
     * Called after using <code>SetInfoMsgBitmapId()</code>.
     *
     * @remarks
     * @see
     */
    IMPORT_C void SetInfoMsgDefaultBitmap();

    /**
     * Displays an info message in the system default corner of the screen.
     * The info message window disappears after a few seconds.
     * <b>Note</b>: Info messages are also known as 'infoprints'.
     *
     * @param aDes The message to display
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsg(const TDesC& aDes);

    /**
     * Displays an info message in the specified corner of the screen.
     * Information messages can be built at run-time from a formatting string
     * defined as a <code>TBUF</code> resource and a list of arbitrary data.
     *
     * @param aCorner The corner of the screen to display the message in
     * @param aDes The message to display
     * @remarks
     * @see TGulAlignment in gulalign.h
     */
    IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,const TDesC& aDes);

    /**
     * Displays an info message in the system default corner of the screen.
     * The info message disappears after a few seconds. A
     * <code>TBUF</code>-resource-specified formatting string may be used to
     * build the message at run-time from arbitrary data in a similar way to
     * C's <code>printf()</code>.
     *
     * @param aResourceId The ID of a <code>TBUF</code> resource used to format
     *                    the string (see <code>TBuf::Format()</code>)
     * @param ... The list of items to be formatted
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsg(TInt aResourceId,...);

    /**
     * Displays an info message in the system default corner of the screen.
     * The info message disappears after a few seconds. 
     * <b>Note</b>: This method is called by 
     * <code>InfoMsg(TInt aResourceId, ...)</code> to set up the 
     * <code>VA_LIST</code>, required for multiple argument lists.
     *
     * @param aResourceId The ID of a <code>TBUF</code> resource used to format
     *                    the string
     * @param aList The list of items to be formatted
     * @remarks
     * @see TBuf::Format()
     */
    IMPORT_C void InfoMsg(TInt aResourceId,VA_LIST aList);

    /**
     * Displays an info message in the specified corner of the screen.
     * Info messages can be built at run-time from a formatting string
     * defined as a <code>TBUF</code> resource and a list of arbitrary data.
     *
     * @param aCorner The screen corner the message is displayed in
     * @param aResourceId The ID of a <code>TBUF</code> resource used to format
     *                    the string
     * @param ... The list of items to be formatted
     * @remarks
     * @see TBuf::Format()
     */
    IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,...);

    /**
     * Displays an info message in the specified corner of the screen.
     * Info messages can be built at run-time from a formatting string
     * defined as a <code>TBUF</code> resource and a list of arbitrary data.
     * <b>Note</b>: This method is called by 
     * <code>InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,...)</code>
     * to set up the <code>VA_LIST</code>, required for multiple argument lists.
     *
     * @param aCorner The corner of the screen to display the message in
     * @param aResourceId The ID of a <code>TBUF</code> resource used to format
     *                    the string
     * @param aList The list of items to be formatted
     * @remarks
     * @see TBuf::Format()
     */
    IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,VA_LIST aList);

    /**
     * Displays an info message for a period <code>aDuration</code>.
     * The text displayed is supplied in a descriptor argument.
     *
     * @param aDes The message to display
     * @param aDuration The length of time to display the message
     * @since 6.1
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsgWithDuration(const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration);

    /**
     * Displays an info message for a period <code>aDuration</code>. The text
     * displayed is supplied in a resource file, as a string with some
     * formatting information for extra arguments. These extra arguments are
     * supplied through the variable argument list that is also passed into
     * this method.
     *
     * @param aDuration The length of time to display the message
     * @param aResourceId The ID of a <code>TBUF</code> resource used to
     *                    format the string (see <code>TBuf::Format()</code>)
     * @param ... The list of items to be formatted
     * @since 6.1
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...);

    /**
     * Displays an info message for a specified period.
     * The text displayed is supplied in a resource file, as a string with
     * some formatting information. Values for the formatting information are
     * supplied as extra arguments. These extra arguments are packaged in a
     * <code>VA_LIST</code> object, which is also passed into this method.
     * <b>Note</b>: This method is called by 
     * <code>InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...)</code>
     * to set up the <code>VA_LIST</code>, required for multiple argument lists.
     *
     * @since 6.1
     * @param aResourceId The message to display
     * @param aDuration The duration of the message
     * @param aList The list of items to be formatted
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, VA_LIST aList);

    /**
     * Displays an info message with a specified alignment for a specified
     * period. The text displayed is supplied in a descriptor argument and
     * aligned using the <code>aCorner</code> parameter.
     *
     * @since 6.1
     * @param aCorner The corner of the screen to display the message in
     * @param aDes The message to display
     * @param aDuration The duration of the message
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration);

    /**
     * Displays an info message for a period <code>aDuration</code>. The text
     * displayed is supplied in a resource file, as a string with some
     * formatting information for extra arguments. These extra arguments are
     * supplied through the variable argument list that is also passed into
     * this method. The text is aligned using the <code>aCorner</code>
     * parameter.
     *
     * @param aCorner The corner of the screen to display the message in
     * @param aResourceId The message to display
     * @param aDuration The duration of the message
     * @param ... The list of items to be formatted
     * @remarks
     * @see
     * @since 6.1
     */
    IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...);

    /**
     * Displays an info message for a period <code>aDuration</code>. The text
     * displayed is supplied in a resource file, as a string with some
     * formatting information for extra arguments. These extra arguments are
     * packaged in a <code>VA_LIST</code> object that is also passed into this
     * method. The text is aligned using the <code>aCorner</code> parameter.
     * <b>Note</b>: This method is called by 
     * <code>InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...)</code>
     * to set up the <code>VA_LIST</code>, required for multiple argument lists.
     *
     * @param aCorner The corner of the screen to display the message in
     * @param aResourceId The message to display
     * @param aDuration The duration of the message
     * @param aList The list of items to be formatted
     * @since 6.1
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,VA_LIST aList);

    /**
     * Cancels the currently displaying information message.
     *
     * @remarks
     * @see
     */
    IMPORT_C void InfoMsgCancel();

    /**
     * Displays an information message, if verbose information reporting has
     * been set. If verbose information reporting has not been set, the message
     * is not displayed.
     *
     * @param aDes The message to display
     * @remarks Verbose can be turned on and off in debug mode via the
     *          keys <code>ctrl+alt+shift+v</code>
     * @see CEikDebugKeys in eikhfdlg.h
     */
    IMPORT_C void VerboseInfoMsg(const TDesC& aDes);

public: //** Internal to Symbian *

    /**
     * @internal
     */
    IMPORT_C void SetVerboseInfoReporting(TBool aVerbose);

public:
    /**
     * Displays a flashing busy message in the system default corner of the
     * screen. This method takes a descriptor for the message.
     *
     * @param aDes The busy message to display
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgL(const TDesC& aDes);

    /**
     * Displays a flashing busy message in the specified corner of the
     * screen. This method takes a descriptor for the busy message.
     *
     * @param aDes The message to display
     * @param aCorner The corner of the screen to display the message in
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgL(const TDesC& aDes,TGulAlignment aCorner);

    /**
     * Displays a flashing busy message in the system default corner of the
     * screen. This method takes a resource ID for the busy message.
     *
     * @param aResourceId The ID of the resource describing the message
     *                    to display
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgL(TInt aResourceId);

    /**
     * Displays a flashing busy message in the system default corner of the
     * screen for a specified duration. This method takes a descriptor for
     * the busy message.
     *
     * @param aDes The message to display.
     * @param aInitialDelay The number of microseconds for which the message is
     *        displayed
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgL(const TDesC& aDes,TTimeIntervalMicroSeconds32 aInitialDelay);

    /**
     * Displays a flashing busy message in the specified corner of the
     * screen for a specified duration. This method takes a descriptor for
     * the busy message.
     *
     * @param aDes The message to display
     * @param aCorner The corner of the screen to display the message in
     * @param aInitialDelay The number of microseconds for which the message is
     *        displayed
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgL(const TDesC& aDes,TGulAlignment aCorner,TTimeIntervalMicroSeconds32 aInitialDelay);

    /**
     * Displays a flashing busy message in the system default corner of the
     * screen for a specified duration. This method takes a resource ID for
     * the busy message.
     *
     * @param aInitialDelay The number of microseconds for which the message is
     *        displayed
     * @param aResourceId The ID of the resource describing the busy
     *             message to display
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgL(TInt aResourceId,TTimeIntervalMicroSeconds32 aInitialDelay);

    /**
     * Cancels any busy message posted by a <code>BusyMsgL()</code>.
     *
     * @remarks
     * @see
     */
    IMPORT_C void BusyMsgCancel();

    /**
     * Displays a dialog asking the user to confirm that all changes are lost
     * to the current document, and returns their response.
     *
     * @return <code>ETrue</code> to lose all changes; <code>EFalse</code>
     *         otherwise
     * @remarks
     * @see
     */
    IMPORT_C TBool ConfirmLossOfAllChangesL() const;

    /**
     * Displays a modal query dialog to ask the user a question that requires
     * a yes or no response.
     *
     * @param aFirstLine The first line of the query text
     * @param aSecondLine The second line of the query text
     * @return <code>ETrue</code> if the user selects Yes; <code>EFalse</code>
     *         otherwise
     * @remarks It is possible to insert carriage returns into the message
     *          with <code>'\n'</code>. The length of the string for either
     *          line should not exceed 60 characters
     * @see
     */
    IMPORT_C static TBool QueryWinL(const TDesC& aFirstLine,const TDesC& aSecondLine);

    /**
     * Displays a modal query dialog to ask the user a question that requires
     * a yes or no response. The text is read from resources.
     *
     * @since Series90 1.0
     * @param aFirstLineId The resource ID for first line of query text
     * @param aSecondLineId The resource ID for second line of query text
     * @return <code>ETrue</code> if the user selects Yes; <code>EFalse</code>
     *         otherwise
     * @remarks It is possible to insert carriage returns into the message
     *          with <code>'\n'</code>. The length of the string for either
     *          line should not exceed 60 characters
     * @see
     */
    IMPORT_C TBool QueryWinL(TInt aFirstLineId,TInt aSecondLineId=0) const;

    /**
     * Displays a modal information dialog (<code>CEikInfoDialog</code>) with
     * the specified lines of text. The user input cannot continue outside a
     * modal dialog until the dialog is dismissed, although applications can be
     * switched.
     *
     * @param aFirstLine The first line of dialog text
     * @param aSecondLine The second line of dialog text
     * @remarks It is possible to insert carriage returns into the message
     *          with <code>'\n'</code>. The length of the string for either
     *          line should not exceed 60 characters
     * @see
     */
    IMPORT_C static void InfoWinL(const TDesC& aFirstLine,const TDesC& aSecondLine);

    /**
     * Displays a modal information dialog (<code>CEikInfoDialog</code>) with
     * the specified lines of text. The user input cannot continue outside a
     * modal dialog until the dialog is dismissed, although applications can be
     * switched. The text is read from resources.
     *
     * @since Series90 1.0
     * @param aFirstLineId The resource ID for the first line of dialog text
     * @param aSecondLineId The resource ID for the second line of dialog text
     * @remarks It is possible to insert carriage returns into the message
     *          with <code>'\n'</code>. The length of the string for either
     *          line should not exceed 60 characters
     * @see
     */
    IMPORT_C void InfoWinL(TInt aFirstLineId,TInt aSecondLineId=0) const;

    /**
     * Sets the query dialog to use. Initially, this method is set to use
     * <code>CCknConfirmationDialog</code> as the query dialog.
     *
     * @param aQueryDialog The query dialog
     * @remarks
     * @see <code>MEikInfoDialog</code> is used by
     *      <code>CCknConfirmationDialog</code> in cknconf.h
     */
    IMPORT_C void SetQueryDialog(MEikInfoDialog* aQueryDialog);

    /**
     * Sets the information dialog to use. Initially, this method is set to use
     * <code>CCknConfirmationDialog</code> as the information dialog.
     *
     * @param aInfoDialog The information dialog
     * @remarks
     * @see <code>MEikInfoDialog</code> is used by
     *      <code>CCknInfoDialog</code> in ckninfo.h
     */
    IMPORT_C void SetInfoDialog(MEikInfoDialog* aInfoDialog);

    /**
     * Sets the method to call to set the query dialog.
     * Initially, this method is used to set the dialog to
     * <code>CCknConfirmationDialog</code>.
     *
     * @param aQueryDialogFunc The request query dialog
     * @remarks
     * @see <code>CCknConfirmationDialog</code> in cknconf.h
     */
    IMPORT_C void SetRequestQueryDialogFunc(TRequestDialogFunc aQueryDialogFunc);

    /**
     * Sets the method to call to set the info dialog.
     * Initially, this method is used to set the dialog to
     * <code>CCknInfoDialog</code>.
     *
     * @param aInfoDialogFunc The request information dialog
     * @remarks
     * @see <code>CCknInfoDialog</code> in ckninfo.h
     */
    IMPORT_C void SetRequestInfoDialogFunc(TRequestDialogFunc aInfoDialogFunc);

    /**
     * Displays an info message showing the total number of
     * cells allocated on the current thread's heap and the total
     * space allocated to them (in bytes).
     *
     * @remarks The size of an individual cell can vary,
     *          depending on how it was allocated
     * @see <code>RHeap</code> in e32std.h
     */
    IMPORT_C void AllocInfoMsg();

    /**
     * Displays an info message showing the number of resources
     * currently open for the window server session.
     *
     * @remarks
     * @see <code>RWsSession</code> in w32std.h
     */
    IMPORT_C void WservAllocInfoMsg();

    /**
     * Displays an info message showing the number of resources
     * currently open for the file server session.
     *
     * @remarks
     * @see <code>RFs</code> in f32file.h
     */
    IMPORT_C void FservAllocInfoMsg();

    /**
     * Emits a beep.
     * This method is deprecated.
     *
     * @deprecated
     * @remarks
     * @see
     */
    IMPORT_C static void Beep();

    /**
     * Creates a bitmap, loading the image bitmap from <code>aFileName</code>
     * and identified by <code>aId</code>.
     * This method creates a new <code>CWsBitmap</code> and returns a pointer to it.
     * Ownership is transferred to the caller, who must delete the bitmap appropriately.
     *
     * @param aFileName The file name specifying the bitmap file to load
     * @param aId The index number for the bitmap in the file
     * @return a pointer to the loaded bitmap
     * @remarks If a zero length descriptor is passed as <code>aFileName</code>,
     *          the Eikon resource file is used. If the wildcard '*' is passed
     *          as <code>aFileName</code>, the default application resource
     *          file is used
     * @see
     */
    IMPORT_C CWsBitmap* CreateBitmapL(const TDesC& aFileName,TInt aId);

    /**
     * Creates an icon, loading the image bitmap identified by
     * <code>aBitmapId</code> and the mask identified by <code>aMaskId</code>
     * from the resource file <code>aFileName</code>.
     * Returns a pointer to the icon and ownership is transferred to the caller,
     * who must delete the icon appropriately.
     *
     * @param aFileName The file name specifying the bitmap files to load
     * @param aBitmapId The index number for the bitmap in the file
     * @param aMaskId The index number for the bitmap mask in the file
     * @return a pointer to the created icon
     * @remarks If a zero length descriptor is passed as <code>aFileName</code>,
     *          the Eikon resource file is used. If the wildcard '*' is passed
     *          as <code>aFileName</code>, the default application resource
     *          file is used
     * @see
     */
    IMPORT_C CGulIcon* CreateIconL(const TDesC& aFileName,TInt aBitmapId,TInt aMaskId=-1);

    /**
     * Creates an icon from a masked bitmap.
     * The icon is created by copying the image bitmap and mask from the
     * masked bitmap <code>aApaMaskedBitmap</code>. It returns a pointer to
     * the icon and transfers ownership to the
     * caller, who must delete the icon appropriately.
     *
     * @param aApaMaskedBitmap The masked bitmap from which the icon is created
     * @return a pointer to the created icon
     * @remarks
     * @see
     */
    IMPORT_C static CGulIcon* CreateIconFromMaskedBitmapL(const CApaMaskedBitmap& aApaMaskedBitmap);

public: //** Internal to Symbian *
    /**
     * @internal
     */
    IMPORT_C void SetDebugKeys(MEikDebugKeys* aDebugKeys);

    /**
     * @internal
     */
    IMPORT_C void LaunchPopupMenuL(TInt aResourceId,const TPoint& aTargetPos,TPopupTargetPosType aTargetType=EPopupTargetTopLeft,const CEikHotKeyTable* aHotKeyTable=NULL);

public:
    /**
     * Adds a window shadow of the standard height to a control.
     *
     * @param aWinArea The control to add a shadow to
     * @remarks
     * @see
     */
    IMPORT_C static void AddWindowShadow(CCoeControl* aWinArea);

    /**
     * Gets the animated DLL that is used to animate the toolbar clock of the
     * Uikon application using this <code>CEikonEnv</code>.
     *
     * @return a reference to the animated DLL
     * @remarks <code>RAnimDll</code> provides methods to create, load, close,
     *          and destroy a server-side <code>CAnimDll</code> object
     * @see <code>RAnimDll</code> in w32std.h
     */
    IMPORT_C RAnimDll& ClockDllL();

    /**
     * Gets the single line paragraph format layer, if it exists. If it does
     * not exist, this method calls
     * <code>CEikonEnv::NewDefaultSingleLineParaFormatLayerL()</code> to
     * create a new paragraph format layer for single line texts.
     * <code>CParaFormatLayer</code> stores the object's global paragraph
     * formatting, implements persistence, and allows attributes to be set
     * and sensed, such as, paragraph alignment.
     *
     * @return a single line paragraph format layer
     * @remarks
     * @see <code>CParaFormatLayer</code> in txtfmlyr.h
     */
    IMPORT_C CParaFormatLayer* SystemSingleLineParaFormatLayerL();

    /**
     * Gets the paragraph format layer if it exists. If it does not exist,
     * calls <code>CEikonEnv::NewDefaultParaFormatLayerL()</code> to create a
     * new paragraph format layer.
     * <code>CParaFormatLayer</code> stores the object's global paragraph
     * formatting, implements persistence, and allows attributes to be set
     * and sensed, such as, paragraph alignment.
     *
     * @return the paragraph format layer
     * @remarks
     * @see <code>CParaFormatLayer</code> in txtfmlyr.h
     */
    IMPORT_C CParaFormatLayer* SystemParaFormatLayerL();

    /**
     * Gets the character format layer if it exists. If it does not exist,
     * this method calls <code>CEikonEnv::NewDefaultCharFormatLayerL()</code>
     * to create a new character format layer.
     * <code>CCharFormatLayer</code> stores the object's global character
     * formatting, implements persistence, and allows attributes to be set
     * and sensed, such as, font typeface and height.
     *
     * @return the character format layer
     * @remarks
     * @see <code>CParaFormatLayer</code> in txtfmlyr.h
     */
    IMPORT_C CCharFormatLayer* SystemCharFormatLayerL();

    /**
     * Creates a paragraph format layer for single line texts.
     *
     * @return a new paragraph format layer suitable for
     *         single line texts
     * @remarks
     * @see
     */
    IMPORT_C static CParaFormatLayer* NewDefaultSingleLineParaFormatLayerL();

    /**
     * Creates a default paragraph format layer for text that has more than
     * one line.
     *
     * @return a new paragraph format layer suitable for text
     *         that has more than one line
     * @remarks
     * @see
     */
    IMPORT_C static CParaFormatLayer* NewDefaultParaFormatLayerL();

    /**
     * Creates a default character format layer.
     *
     * @return a new character format layer in the default
     *         style
     * @remarks
     * @see
     */
    IMPORT_C static CCharFormatLayer* NewDefaultCharFormatLayerL();

    /**
     * Gets printer names from a <code>CPrinterModelList</code>. The printer
     * names are returned through <code>aPrinterNameList</code>.
     *
     * @param aModelNameList The input list of printer model information
     * @param aPrinterNameList On return, contains all the printer names from
     *            <code>aModelNameList</code>
     * @remarks
     * @see
     */
    IMPORT_C static void GetPrinterNamesL(CPrinterModelList* aModelNameList,CDesCArray& aPrinterNameList);

    /**
     * Gets the application UI of the application using this
     * <code>CEikonEnv</code>.
     *
     * @return a pointer to the <code>CEikAppUi</code>
     * @remarks
     * @see
     */
    inline CEikAppUi* EikAppUi() const;

    /**
     * Adds a dialog-like control to the stack, such as the pop-out
     * listbox from a choicelist control. If a control already exists in
     * the control stack with a priority greater than
     * <code>ECoeStackPriorityDialog</code> and less than
     * <code>ECoeStackPriorityFep</code>, this method leaves with no alert.
     *
     * @param aControl The control to add
     * @remarks
     * @see
     */
    IMPORT_C void AddDialogLikeControlToStackL(CCoeControl* aControl);

    /**
     * Adds a alert dialog-like control to the stack. If a control already
     * exists in the control stack with a priority greater than
     * <code>ECoeStackPriorityAlert</code> and less than
     * <code>ECoeStackPriorityFep</code>, this method leaves with no alert.
     *
     * @param aControl The control to add
     * @remarks
     * @see
     */
    IMPORT_C void AddAlertDialogLikeControlToStackL(CCoeControl* aControl);

    /**
     * Removes a control from the control stack.
     *
     * @param aControl The control to remove
     * @remarks
     * @see
     */
    IMPORT_C void RemoveFromStack(CCoeControl* aControl);

    /**
     * Adds a sleeping dialog to the CONE control stack.
     * A sleeping dialog is one that can be displayed at any time, because
     * its memory resources are pre-allocated. A sleeping dialog is not visible
     * initially.
     *
     * @param aControl The control to add
     * @remarks
     * @see
     */
    IMPORT_C void AddSleepingDialogToStackL(CCoeControl* aControl);

    /**
     * Adds a sleeping dialog to the CONE control stack that when roused is
     * displayed with a priority similar to an alert.
     * A sleeping dialog is one that can be displayed at any time, because
     * its memory resources are pre-allocated. A sleeping dialog is not visible
     * initially.
     *
     * @param aControl The control to add
     * @remarks
     * @see
     */
    IMPORT_C void AddSleepingAlertDialogToStackL(CCoeControl* aControl);

    /**
     * Sets the dialog sleep state, that is, whether the dialog is active and
     * visible or not.
     *
     * @param aControl The control to rouse or put to sleep
     * @param aRoused <code>ETrue</code> to rouse <code>aControl</code>;
     *        <code>EFalse</code> to put it to sleep
     * @remarks
     * @see
     */
    IMPORT_C void RouseSleepingDialog(CCoeControl* aControl,TBool aRoused);

    /**
     * Draws the text cursor into a control with the specified position and
     * width. The cursor's height and ascent is by default suitable for this
     * <code>CEikonEnv</code> object's normal font.
     * If <code>aControl</code> is not focused when this method is called,
     * a panic is raised - <code>EEikPanicCursorControlNotFocused</code>.
     *
     * @param aControl The control to draw into
     * @param aPosition The position of the cursor's baseline in the control's
     *        co-ordinate space
     * @param aWidth The cursor width
     * @remarks
     * @see
     */
    IMPORT_C void DrawCursor(const CCoeControl* aControl,const TPoint& aPosition,TInt aWidth);

    /**
     * Draws the text cursor into a control with the specified position and
     * width.
     * If <code>aControl</code> is not focused when this method is called,
     * a panic is raised - <code>EEikPanicCursorControlNotFocused</code>.
     *
     * @param aControl The control to draw into
     * @param aPosition The position of the cursor's baseline in the control's
     *            co-ordinate space
     * @param aWidth The cursor width
     * @param aAscent The cursor ascent
     * @param aHeight The cursor height
     * @remarks
     * @see
     */
    IMPORT_C void DrawCursor(const CCoeControl* aControl,const TPoint& aPosition,TInt aWidth,TInt aAscent,TInt aHeight);

    /**
     * Removes the text cursor from a control.
     * In debug builds, a panic is raised when this method is called on a
     * control that is not the cursor owner - <code>EEikPanicControlNotCursorOwner</code>.
     *
     * @param aControl The control that owns the cursor
     * @remarks
     * @see
     */
    IMPORT_C void HideCursor(const CCoeControl* aControl);

     /**
      * Updates the process name from the caption of the task's window group.
      *
      * @remarks
      * @see <code>CApaWindowGroupName</code> in apgwgnam.h
      */
    IMPORT_C void UpdateTaskNameL();

    /**
     * Repositions the root window group in the stacking hierarchy or pushes
     * it to the back.
     * Calls to this method are ignored if the auto-forward flag is set to
     * <code>ETrue</code>.
     *
     * @param aForwards <code>ETrue</code> to reposition the root window group
     *            at <code>aPriority</code>. <code>EFalse</code> to push
     *            the root window group to the back
     * @param aPriority If <code>aForwards</code> is <code>ETrue</code>,
     *            this argument determines where the root window group
     *            is placed in the stacking hierarchy
     * @remarks
     * @see
     */
    IMPORT_C void BringForwards(TBool aForwards,TInt aPriority=ECoeWinPriorityAlwaysAtFront);

    /**
     * Sets auto-forward state for the window group.
     * Used by the method <code>BringForwards()</code>
     *
     * @param aForwarding <code>ETrue</code> to set auto-forwarding on;
     *        <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C void SetAutoForwarding(TBool aForwarding);

public: //** Internal to Symbian *
    /**
     * @internal
     */
    IMPORT_C TPtrC KeyPressLabel(TInt aIndex) const;

public:
    /**
     * Creates and returns a pointer to a new default printer setup object.
     * The <code>CPrintSetup</code> class stores the information needed to
     * set up, start, and stop a print job.
     *
     * @return a default printer setup object
     * @remarks
     * @see <code>CPrintSetup</code> is in prnsetup.h
     */
    IMPORT_C CPrintSetup* NewDefaultPrintSetupL();

public: //** Internal to Symbian *
    /**
     * @internal
     */
    IMPORT_C void DisplayTaskList();

    /**
     * @internal
     */
    IMPORT_C void SendEventToEikonServer(TInt aEvent,const TAny* aPtr,TInt aLength);

public:
    /**
     * Sets the window group's busy state.
     * Stops the task from being shut down externally. If busy tasks are set
     * as hidden, hides this process from the task list,
     *
     * @param aBusy <code>ETrue</code> to set as busy; <code>EFalse</code>
     *        otherwise
     * @remarks
     * @see
     */
    IMPORT_C void SetBusy(TBool aBusy);

    /**
     * Determines whether the window group is busy.
     *
     * @return <code>ETrue</code> if the window group is busy;
     *         <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C TBool IsBusy() const;

    /**
     * Sets the environment's system attribute. This method stops the task
     * from being shut down externally. If system tasks are set as hidden,
     * the method hides this process from the task list.
     *
     * @param aSystem <code>ETrue</code> to set the system attribute;
     *        <code>EFalse</code> to unset it
     * @remarks
     * @see
     */
    IMPORT_C void SetSystem(TBool aSystem);

    /**
     * Tests the value of the system attribute.
     *
     * @return <code>ETrue</code> if the system attribute is set;
     *          <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C TBool IsSystem() const;

    /**
     * Sets whether a document name is a file.
     *
     * @param aDocNameIsAFile <code>ETrue</code> to set the document name as a
     *                        file; <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C void SetDocNameIsAFile(TBool aDocNameIsAFile);

    /**
     * Tests whether the document name is a file.
     *
     * @return <code>ETrue</code> if the document name is a file;
     *         <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C TBool DocNameIsAFile() const;

    /**
     * Sets whether an application responds to shutdown events.
     *
     * @param aRespondsToShutdownEvent <code>ETrue</code> if the application
     *                                 responds to shutdown events;
     *                                 <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C void SetRespondsToShutdownEvent(TBool aRespondsToShutdownEvent);

    /**
     * Tests whether an application responds to shutdown events.
     *
     * @return <code>ETrue</code> if the application responds to
     *         shutdown events; <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C TBool RespondsToShutdownEvent() const;

    /**
     * Sets whether an application responds to switch files events - that is,
     * when a process is asked to close its existing document, and to
     * create or open a new document.
     *
     * @param aRespondsToSwitchFilesEvent <code>ETrue</code> if the application
     *                                    responds to switch files events;
     *                                    <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C void SetRespondsToSwitchFilesEvent(TBool aRespondsToSwitchFilesEvent);

    /**
     * Tests whether an application responds to switch files events.
     *
     * @return <code>ETrue</code> if the application responds to
     *         switch files events; <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C TBool RespondsToSwitchFilesEvent() const;

    /**
     * Gets the virtual cursor. The virtual cursor is used on Series 90 devices
     * that do not have a touch screen.
     *
     * @return the virtual cursor
     * @remarks
     * @see
     */
    IMPORT_C TEikVirtualCursor& VirtualCursor();

    /**
     * Notifies this environment that an idle error occurred while redrawing
     * was in progress. This method is usually called by the user when a
     * drawing error occurs. It displays an error via a dialog and will
     * not re-display the alert if the problem occurs again within the next
     * 60 seconds.
     *
     * @param aError The ID of the idle error
     * @remarks
     * @see
     */
    IMPORT_C void NotifyIdleErrorWhileRedrawing(TInt aError);

    /**
     * Notifies this environment of an idle error.
     * This method reads the error context text from the resource
     * identified by <code>aContextRid</code>.
     *
     * @param aError The ID of the idle error
     * @param aContextRid The ID of the resource from which the context text
     *                    is read
     * @remarks
     * @see
     */
    IMPORT_C void NotifyIdleError(TInt aError,TInt aContextRid);

    /**
     * Handles the specified error.
     * This method reads the error context text from the resource
     * identified by <code>aContextRid</code>.
     *
     * @param aError The ID of the error to handle
     * @param aContextRid The ID of the resource from which the context is
     *                    read
     * @remarks
     * @see
     */
    IMPORT_C void HandleErrorWithContext(TInt aError,TInt aContextRid);

    /**
     * Gets the Application UI factory object.
     * This object implements the <code>MEikAppUiFactory</code> interface.
     *
     * @return the application UI factory interface
     * @remarks
     * @see
     */
    IMPORT_C MEikAppUiFactory* AppUiFactory() const;

    /**
     * Gets the Application UI factory object for the specified AppUI.
     * If the specified AppUI does not exist in this environment, the method
     * returns <code>NULL</code>. Otherwise the method returns an object that
     * implements the <code>MEikAppUiFactory</code> interface.
     *
     * @since 6.1
     * @param aAppUi The AppUI for this application
     * @return the application UI factory object, or <code>NULL</code> if
     *         <code>aAppUi</code> does not exist in this environment
     * @remarks
     * @see
     */
    IMPORT_C MEikAppUiFactory* AppUiFactory(const CEikAppUi& aAppUi) const;

public: //** Internal to Symbian *
    /**
     * @internal
     */
    IMPORT_C void SetAppUiFactoryL(MEikAppUiFactory* aAppUiFactory); // DLL decoupling between core and core controls

    /**
     * @internal
     */
    IMPORT_C void AddAppUiFactoryL(MEikAppUiFactory* aAppUiFactory);

    /**
     * @internal
     */
    IMPORT_C void RemoveAppUiFactory();

public:
    /**
     * @internal
     * Do not use
     *
     * @since ER5U
     */
    IMPORT_C TInt AddLibraryL(TCreateByTypeFunction aControlFactory, TFileName* aResourceFile);

    /**
     * @internal
     * Do not use
     *
     * @since ER5U
     */
    inline TInt AddLibraryL(TCreateByTypeFunction aControlFactory);

    /**
     * @internal
     * Do not use
     *
     * @since ER5U
     */
    inline TInt AddLibraryL(TFileName* aResourceFile);

    /**
     * @internal
     * Do not use
     *
     * @since ER5U
     */
    IMPORT_C void RemoveLibrary(TCreateByTypeFunction aControlFactory, TInt aResourceFileOffset);

    /**
     * @internal
     * Do not use
     *
     * @since ER5U
     */
    inline void RemoveLibrary(TCreateByTypeFunction aControlFactory);

    /**
     * @internal
     * Do not use
     *
     * @since ER5U
     */
    inline void RemoveLibrary(TInt aResourceFileOffset);

    /**
     * Gets the minus nudge character. For example, this could be the left
     * arrow.
     *
     * @return the minus nudge character
     * @remarks Used by the multi-field numeric editor
     * @see <code>CEikMfne</code> in eikmfne.h
     */
    inline TChar NudgeCharMinus() const;

    /**
     * Gets the plus nudge character, For example, this could be the right
     * arrow.
     *
     * @return the plus nudge character
     * @remarks Used by the multi-field numeric editor
     * @see <code>CEikMfne</code>  in eikmfne.h
     */
    inline TChar NudgeCharPlus() const;

    /**
     * Gets the application's color list.
     * The color list provides member functions to retrieve and modify
     * colors in the list, and to append new arrays of colors to the color
     * list.
     *
     * @return the application's color list
     * @remarks
     * @see
     */
    inline CColorList& ColorList() const;

    /**
     * Gets the physical (<code>TRgb</code>) color that corresponds to the
     * logical color. Logical colors are used to specify the color scheme
     * for the controls in an application.
     *
     * @param aLogicalColor A logical color value
     * @return the physical color that corresponds to <code>aLogicalColor</code>
     * @remarks
     * @see <code>TLogicalColor</code> in gulcolor.h
     */
    inline TRgb Color(TLogicalColor aLogicalColor) const;

    /**
     * Sets the mapping in the application's color list between the logical
     * and physical colors specified.
     *
     * @param aLogicalColor A logical color value
     * @param aColor A physical color value
     * @remarks
     * @see
     */
    inline void SetColor(TLogicalColor aLogicalColor, TRgb aColor);

    /**
     * Gets the physical (<code>TRgb</code>) color that corresponds to the
     * logical color specified from the application's color list.
     * If the color of the control specified in <code>aControl</code> has
     * been overridden using <code>CCoeControl::OverrideColorL()</code>, this
     * method returns the overridden color.
     *
     * @param aLogicalColor A logical color value
     * @param aControl A pointer to the control itself
     * @return the physical color that corresponds to
     *         <code>aLogicalColor</code>
     * @remarks
     * @see
     */
    IMPORT_C TRgb ControlColor(TLogicalColor aLogicalColor,const CCoeControl& aControl) const;

    /**
     * Gets the custom color array.
     * This is the list of standard control colors.
     *
     * @return the custom color array
     * @remarks
     * @see <code>CColorArray</code> is in gulcolor.h
     */
    inline CColorArray& CustomColorArray() const;

public: //** Internal to Symbian *
    /**
     * Sets the current dialog factory.
     * This function is needed because of the DLL decoupling between Controls and Common Dialogs.
     * Pass hot keys to the factory which launches the appropriate dialog.
     *
     * @internal
     * @since Series90 1.0
     * @param aDialogFactory The common dialog factory.
     * @remarks
     * @see
     */
    inline void SetCDlgDialogFactory(MEikCDlgDialogFactory* aDialogFactory);

    /**
     * Sets the current print dialog factory.
     * This function is needed because of the DLL decoupling between Controls and Print Dialogs.
     *
     * @internal
     * @since Series90 1.0
     * @param aDialogFactory The print dialog factory.
     * @remarks
     * @see
     */
    inline void SetPrintDialogFactory(MEikPrintDialogFactory* aDialogFactory);

    /**
     * Sets the current file dialog factory.
     * This function is needed because of the DLL decoupling between Controls and File Dialogs.
     *
     * @internal
     * @since Series90 1.0
     * @param aDialogFactory The file dialog factory.
     * @remarks
     * @see
     */
    inline void SetFileDialogFactory(MEikFileDialogFactory* aDialogFactory);

    /**
     * Sets the current Ir send/receive factory.
     * This function is needed because of the DLL decoupling between Controls and Ir send/receive.
     *
     * @internal
     * @since Series90 1.0
     * @param aIrFactory The Ir send/receive factory.
     * @remarks
     * @see
     */
    inline void SetIrFactory(MEikIrFactory* aIrFactory);

    /**
     * Get the current common dialog factory.
     *
     * @internal
     * @since Series90 1.0
     * @return the current common dialog factory.
     * @remarks
     * @see
     */
    inline MEikCDlgDialogFactory* CDlgDialogFactory() const;

    /**
     * Get the current print dialog factory.
     *
     * @internal
     * @since Series90 1.0
     * @return the current print dialog factory.
     * @remarks
     * @see
     */
    inline MEikPrintDialogFactory* PrintDialogFactory() const;

    /**
     * Get the current file dialog factory.
     *
     * @internal
     * @since Series90 1.0
     * @return the current file dialog factory.
     * @remarks
     * @see
     */
    inline MEikFileDialogFactory* FileDialogFactory() const;

    /**
     * Get the current ir send/receive factory.
     *
     * @internal
     * @since Series90 1.0
     * @return the current ir send/receive factory.
     * @remarks
     * @see
     */
    inline MEikIrFactory* IrFactory() const;

    /**
     * Get the array of control factories.
     *
     * @internal
     * @since Series90 1.0
     * @return the array of control factories.
     * @remarks
     * @see
     */
    CArrayFix<TCreateByTypeFunction>* ControlFactoryFuncArray() const;

    /**
     * Sets the zoom factor for the environment.
     *
     * @internal
     * @since Series90 1.0
     * @param aZoomFactor The zoom factor
     * @remarks
     * @see
     */
    inline void SetZoomFactor(TZoomFactor& aZoomFactor);

    /**
     * Gets the zoom factor for the environment.
     *
     * @internal
     * @since Series90 1.0
     * @return the zoom factor.
     * @remarks
     * @see
     */
    inline TZoomFactor ZoomFactor() const;

    /**
     * @internal
     */
    inline TInt StatusPaneCoreResId() const;

    /**
     * @internal
     */
    inline void SetStatusPaneCoreResId(TInt aStatusPaneCoreResId);

    /**
     * Add aTitle to the array of menu titles automatically added to the standard app menu bar.
     * Takes ownership of aTitle at the end of the function
     *
     * @param aTitle the title
     * @internal
     */
    IMPORT_C void AddAutoMenuTitleL(CEikAutoMenuTitle* aTitle);

    /**
     * Get the array of menu titles automatically added to the standard app menu bar.
     *
     * @internal
     * @since Series90 1.0
     * @return The menu array.
     * @remarks
     * @see
     */
    inline CEikAutoMenuTitleArray* AutoMenuTitleArray() const;

public:
    /**
     * Gets the default display mode for the window server session with the
     * maximum possible number of colors.
     *
     * @return the default display mode
     * @remarks
     * @see <code>TDisplayMode</code> in gdi.h
     * @since 6.0
     */
    IMPORT_C TDisplayMode DefaultDisplayMode() const;

public: //** Do not use *
    /**
     * @internal
     * @deprecated
     * Use CCoeStatic instead
     */
    IMPORT_C void SetExtension(CBase* aExtension);

    /**
     * @internal
     * @deprecated
     */
    inline CBase* Extension() const;

public: //** Internal to Symbian *
    //** framework functions *

    /**
     * @internal
     */
    IMPORT_C void HandleError(TInt aError);
	IMPORT_C void HandleErrorNoNotify(TInt aError);

public: //** internal *
    /**
     * Writes the internal state of all CCoeControls on the control stack into a file
     * c:\debuglog_#APPNAME#(#NUMBER#) in the Epoc filing system. Works in debug mode only.
     *
     * @internal
     * @since App-Framework_6.1
     */
    IMPORT_C void WriteInternalStateOfStackedControlsL();

protected: //** internal *
	IMPORT_C void SetIsNotifierEnv(TBool aIsNotifierEnv);

public:	//** internal *
	IMPORT_C TBool IsNotifierEnv();

public: //** internal *
    /**
     * @internal
     */
    IMPORT_C void UpdateColorListL();

    /**
     * @internal
     */
    void PostAppUiInitializeL();

    /**
     * Exported for testing only - not intended to be used outside App Framework subsystem
     *
     * @internal
     */
    IMPORT_C void DoGetErrorText(TDes& aDes,TInt aError) const;

public: //** Internal to Symbian *
    //** framework functions *

    /**
     * @internal
     */
    IMPORT_C void DestroyEnvironment();

public:
	//** To be used by FEP to determine whether to launch the character map dialog *
	IMPORT_C void SetFepDialogLaunchFlag(TBool aSetDialog);
	IMPORT_C TBool FepDialogLaunchFlag() const;

private: //** framework functions *
    IMPORT_C void DestroyScreen();
    IMPORT_C void InitSystemFontsL();
    IMPORT_C TInt ResourceFileVersionNumber() const;
    IMPORT_C void Reserved_1();
    IMPORT_C void Reserved_2();

private: // from MApaAppStarter
    IMPORT_C TThreadId StartAppL(const CApaCommandLine& aCommandLine);

public: //** Internal to Symbian *
    /**
     * Gets the query dialog for this environment.
     *
     * @internal
     * @return The query dialog.
     * @remarks
     * @see
     */
    IMPORT_C MEikInfoDialog* QueryDialog() const;

    /**
     * Gets the info dialog for this environment.
     *
     * @internal
     * @return The info dialog.
     * @remarks
     * @see
     */
    IMPORT_C MEikInfoDialog* InfoDialog() const;


public: //** Internal to Symbian *
    /**
     * This function is for use by the dialog exit function. When the dialog is exited
     * by pressing a key this function disables the key event until the next key up.
     * If this wasn't done then the key up event corresponding to the key event that
     * dismissed the dialog would be sent to whatever component becomes focused after the
     * dialog is dismissed.
     * @param aDisable ETrue if the events must be disabled, EFalse to reenable the key events.
     *
     * @internal
     * @remarks
     * @see AreKeyEventsDisabled
     */
    IMPORT_C void DisableKeyEventsL(TBool aDisable);
    /**
     * Checks if the key events have been disabled by a call to DisableKeyEventsL.
     *
     * @internal
     * @remarks
     * @see DisableKeyEventsL
     */
    IMPORT_C TBool AreKeyEventsDisabled();
	IMPORT_C TBool ScreenIsBeingCleared() const;

public: /* new functions */
    /**
     * This function returns true if personal tones are on otherwise false
     * Use it to see whether you should play a sound or not
     */
    IMPORT_C static TBool PersonalTonesL();

protected:
    void doConstructAppFromCommandLineL(const CApaCommandLine& aCommandLine);

protected:
    friend class CEikServAppUi;

private: //** new functions *
    void InitSystemResourceFileL();
    void InitPrivateResourceFileL();
    void InitInfoMsgL();
    void PrepareBusyMsgL();
    void InitAlertWinL();
    void SetUpFepL();
    TErrorHandlerResponse PrepareToHandleError(TInt aError);
    void DoHandleError(TErrorHandlerResponse aType);
    static TInt IdleErrorCallBack(TAny* aThis);
    void InitColorsL();
    void LoadParserListL();
    void LoadLibrariesL();
    void CloseLibraries();
    TRequestDialogFunc RequestQueryDialogFunc();
    TRequestDialogFunc RequestInfoDialogFunc();
    TBool IsEiksrvThread() const;
    void CloseClearer();
    CEikScreenClearerWin *doConstructL(const CApaCommandLine& aCommandLine);
private:
    /**
     * Data structure used in an array for storing MEikAppUiFactory.
     *
     * @internal
     */
    class TEikAppUiFactory
        {
        public:
            MEikAppUiFactory*   iFactory;
            CEikAppUi*          iAppUi;
        };

private:
    TInt iEikonEnvFlags;
    TInt iForwardsCount;
    TInt iBusyCount;
    CEikProcess* iProcess;
    RAnimDll* iClockDll;
    CArrayPtr<CFont>* iFontArray;
    CEikInfoMsgWin* iInfoMsgWin;
    CEikBusyMsgWin* iBusyMsgWin;
    MEikAlertWin* iAlertWin;
    TInt iSystemResourceFileOffset;
    HBufC8* iKeyPressLabels;
    CParaFormatLayer* iSingleLineParaFormatLayer;
    CParaFormatLayer* iParaFormatLayer;
    CCharFormatLayer* iCharFormatLayer;
    const CCoeControl* iCursorWindow;
    TInt iEditableControlStandardHeight;
    CApaWindowGroupName* iWgName;
    CEikErrorIdler* iErrorIdler;
    TInt iPrivateResourceFileOffset;
    CColorList* iColorList;
    CEikPictureFactory* iPictureFactory;
    TBuf<2> iNudgeChars;
    MEikInfoDialog* iQueryDialog;
    MEikInfoDialog* iInfoDialog;
    TRequestDialogFunc  iQueryDialogFunc;
    TRequestDialogFunc  iInfoDialogFunc;
    CArrayFix<RLibrary>* iLibArray;
    CArrayFix<TCreateByTypeFunction>* iControlFactoryFuncArray;
    CArrayFix<TInt>* iResourceFileOffsetArray;
    TBool iAlertWinInitialized;
    MEikDebugKeys* iDebugKeys;
    MEikCDlgDialogFactory* iCDlgDialogFactory;
    MEikPrintDialogFactory* iPrintDialogFactory;
    MEikFileDialogFactory* iFileDialogFactory;
    CArrayFix<TEikAppUiFactory>* iAppUiFactoryArray;
    MEikIrFactory* iIrFactory;
    CArrayPtr<CEikLibrary>* iLibraries;
    TInt iEmbeddedAppLevel;
    TInt iAutoLoadedResourceFiles;
    TInt iAutoLoadedControlFactories;
    TZoomFactor iZoomFactor;
    CBase* iExtension;
    TInt iStatusPaneCoreResId;
    CEikAutoMenuTitleArray* iAutoMenuTitleArray;
    TEikVirtualCursor iVirtualCursor;
    CEikLogicalBorder* iLogicalBorder;
    CEikLafEnv* iLafEnv;
    CArrayPtrFlat<CFbsBitmap>* iBitmapArray;
    CEikEnvExtra* iEikEnvExtra;      // used to be TInt iSpare1;
    HBufC* iOOMErrorText;            // used to be TInt iSpare2;
    CArrayPtr<CFont>* iOldFontArray; // used to be TInt iSpare3;
    };

class CEikonEnvSkinObsExtension;

/**
 * The <code>CEikonEnvSkinObs</code> class is the skin observer class for this
 * environment. This class updates environment variables when the skin is
 * changed.
 * <code>CEikonEnvSkinObs</code> is used in eiksrv.h.
 *
 * @since Series90 1.0
 * @lib eikcore.lib
 */
class CEikonEnvSkinObs : public CEikonEnv, public MCknSkinServObserver
    {
public:
    /**
     * Updates the fonts array stored in the Eikon Environment. The method
     * delays deletion of the old array in case applications redraw before
     * they have taken the new fonts.
     *
     * @param aReloadStatus This method does nothing unless
     *                      <code>aReloadStatus=ESkinReloadStatusSuccess</code>
     * @remarks
     * @see <code>TSkinReloadStatus</code> in skin.h
     */
    IMPORT_C void HandleSkinReloadEventL(TSkinReloadStatus aReloadStatus);

    /**
     * <B>Note:</B> this method is not supported in Series 90.
     *
     * @remarks
     * @see
     */
    IMPORT_C void HandleAppViewChange();

    /**
     * Destroys the skin before the environment.
     *
     * @remarks
     * @see
     */
    IMPORT_C void DestroyEnvironment();

    /**
     * Completes construction of the <code>CEikonEnvSkinObs</code> object.
     *
     * @remarks
     * @see
     */
    IMPORT_C void ConstructL();

    /**
     * The object destructor.
     *
     * @remarks
     * @see
     */
    IMPORT_C ~CEikonEnvSkinObs();

    void ConstructAppFromCommandLineL(const CApaCommandLine& aCommandLine);

private:
    void SetSkinObserverL();

private:
    CEikonEnvSkinObsExtension* iExt;
    };


/**
 * The <code>MEikInfoDialog</code> class is the base class used for deriving
 * <code>CEikInfoDialog</code>. The class provides the interface for launching
 * a dialog with a title and a message, for instance a query dialog. Dialogs
 * implementing this interface can be passed to
 * <code>CEikonEnv::SetQueryDialog()</code> or
 * <code>CEikonEnv::SetInfoDialog()</code>.
 *
 * @since 6.0
 * @lib eikcore.lib
 * @publishedAll
 * @released
 */
class MEikInfoDialog
    {
public:
    /**
     * Displays an information dialog and returns when the user selects a button.
     *
     * @param aResource The resource ID of the dialog
     * @param aTitle The title text for the dialog
     * @param aMsg The message text of the dialog
     * @return <code>ETrue</code> on dialog closing; <code>EFalse</code> if an
     *         error prevents the usual dialog display
     * @remarks
     * @see
     */
    virtual TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg) = 0;
    };


/**
 * The <code>MEikAlertWin</code> class is the base class used for
 * deriving alert windows.
 *
 * @since Series90 1.0
 * @publishedPartner
 * @released
 */
class MEikAlertWin
    {
public:
    /**
     * Completes construction of the <code>MEikAlertWin</code> object.
     *
     * @remarks
     * @see
     */
    virtual void ConstructL() = 0;

    /**
     * Displays the alert dialog.
     *
     * @param aTitle The dialog title
     * @param aMsg The dialog text
     * @remarks
     * @see
     */
    virtual void RunAlert(const TDesC& aTitle, const TDesC& aMsg) = 0;

    /**
     * Destroy all resources for this dialog.
     *
     * @remarks
     * @see
     */
    virtual void Release() = 0;

    /**
     * Returns a pointer to this alert dialog as a <code>CEikDialog</code>.
     *
     * @return a pointer to this alert dialog
     * @remarks
     * @see
     */
    virtual CEikDialog* AsEikDialog() = 0;

    /**
     * Returns a const pointer to this alert dialog as a <code>CEikDialog</code>.
     *
     * @return a pointer to this alert dialog
     * @remarks
     * @see
     */
    inline const CEikDialog* AsEikDialog() const;
    };


/**
 * The <code>MEikDebugKeys</code> class is the base class used for deriving
 * a debug class. This is a class that handles various keyboard events to
 * aid in debugging an application.
 * <code>MEikDebugKeys</code> is used by <code>CEikDebugKeys</code> in
 * eikhfdlg.h.
 *
 * @since Series90 1.0
 * @publishedPartner
 * @released
 */
class MEikDebugKeys
    {
public:
    /**
     * Completes construction of the <code>MEikDebugKeys</code> object.
     *
     * @remarks
     * @see
     */
    virtual void ConstructL() = 0;

    /**
     * Cleans up resources.
     *
     * @remarks
     * @see
     */
    virtual void Release() = 0;
    };


/**
 * Gets the CEikonEnv maintained by the framework for the application.
 *
 * This function should never be run in a thread where such a static Uikon environment
 * does not exist. Code that may run on the server side of an application server
 * is one such case.
 *
 * @return A static CEikonEnv.
 * @see CCoeEnv::Static()
 */
inline CEikonEnv* CEikonEnv::Static()
    { return((CEikonEnv*)(CCoeEnv::Static())); }

/**
 * @publishedPartner
 * @released
 */
inline TInt CEikonEnv::EditableControlStandardHeight() const
    { return(iEditableControlStandardHeight); }

/**
 * Gets the Uikon process that manages the files of applications started in this
 * environment.
 *
 * @return The CEikProcess object.
 * @remarks
 * @see
 */
inline CEikProcess* CEikonEnv::Process() const
    { return(iProcess); }

/**
 * Gets the application UI of the application using this CEikonEnv.
 *
 * @return Pointer to the CEikAppUi.
 * @remarks
 * @see
 */
inline CEikAppUi* CEikonEnv::EikAppUi() const
    { return((CEikAppUi*)iAppUi); }

inline const MEikAlertWin* CEikonEnv::Alert() const
    { return(iAlertWin); }

/**
 * Gets the minus nudge character, this could be the left arrow for example.
 *
 * @return Minus nudge character.
 * @remarks
 * @see
 */
inline TChar CEikonEnv::NudgeCharMinus() const
    {return(iNudgeChars[0]);}

/**
 * Gets the plus nudge character, this could be the right arrow for example.
 *
 * @return Plus nudge character.
 * @remarks
 * @see
 */
inline TChar CEikonEnv::NudgeCharPlus() const
    {return(iNudgeChars[1]);}

/**
 * Gets the physical (TRgb) color which corresponds to a logical color.
 *
 * @param aLogicalColor A logical color value.
 * @return The physical color which corresponds to aLogicalColor.
 * @remarks
 * @see
 */
inline TRgb CEikonEnv::Color(TLogicalColor aLogicalColor) const
    {return ColorList().Color(aLogicalColor); }

/**
 * Gets the custom color array.
 *
 * @return The custom color array.
 * @remarks
 * @see
 */
inline CColorArray& CEikonEnv::CustomColorArray() const
    {return *(ColorList().ColorArray(TUid::Uid(KEikCustomColorsArrayValue)));}

/**
 * Gets the application's color list.
 *
 * The color list provides member functions to retrieve and modify colors
 * in the list, and to append new arrays of colors to the color list.
 *
 * @return The application's color list
 * @remarks
 * @see
 */
inline CColorList& CEikonEnv::ColorList() const
    {__ASSERT_DEBUG(iColorList,User::Invariant()); return *iColorList; }

/**
 * Sets a mapping in the application's color list between the logical and physical
 * colors specified.
 *
 * @param aLogicalColor A logical color value.
 * @param aColor A physical color value.
 * @return
 * @remarks
 * @see
 */
inline void CEikonEnv::SetColor(TLogicalColor aLogicalColor, TRgb aColor)
    { ColorList().SetColor(aLogicalColor, aColor); }

/**
 * @publishedPartner
 * @released
 */
inline void CEikonEnv::SetCDlgDialogFactory(MEikCDlgDialogFactory* aDialogFactory)
    {iCDlgDialogFactory=aDialogFactory;}

/**
 * @publishedPartner
 * @released
 */
inline void CEikonEnv::SetPrintDialogFactory(MEikPrintDialogFactory* aDialogFactory)
    {iPrintDialogFactory=aDialogFactory;}

/**
 * @publishedPartner
 * @released
 */
inline void CEikonEnv::SetFileDialogFactory(MEikFileDialogFactory* aDialogFactory)
    {iFileDialogFactory=aDialogFactory;}

/**
 * @publishedPartner
 * @released
 */
inline void CEikonEnv::SetIrFactory(MEikIrFactory* aIrFactory)
    {iIrFactory=aIrFactory;}

/**
 * @publishedPartner
 * @released
 */
inline MEikCDlgDialogFactory* CEikonEnv::CDlgDialogFactory() const
    {return iCDlgDialogFactory;}

/**
 * @publishedPartner
 * @released
 */
inline MEikPrintDialogFactory* CEikonEnv::PrintDialogFactory() const
    {return iPrintDialogFactory;}

/**
 * @publishedPartner
 * @released
 */
inline MEikFileDialogFactory* CEikonEnv::FileDialogFactory() const
    {return iFileDialogFactory;}

/**
 * @publishedPartner
 * @released
 */
inline MEikIrFactory* CEikonEnv::IrFactory() const
    {return iIrFactory;}


inline TInt CEikonEnv::AddLibraryL(TCreateByTypeFunction aControlFactory)
    {return(AddLibraryL(aControlFactory, NULL));}
inline TInt CEikonEnv::AddLibraryL(TFileName* aResourceFile)
    {return(AddLibraryL(NULL, aResourceFile));}
inline void CEikonEnv::RemoveLibrary(TCreateByTypeFunction aControlFactory)
    {RemoveLibrary(aControlFactory, NULL);}
inline void CEikonEnv::RemoveLibrary(TInt aResourceFileOffset)
    {RemoveLibrary(NULL, aResourceFileOffset);}

/**
 * @publishedPartner
 * @released
 */
inline void CEikonEnv::SetZoomFactor(TZoomFactor& aZoomFactor)
    {iZoomFactor=aZoomFactor;}

/**
 * @publishedPartner
 * @released
 */
inline TZoomFactor CEikonEnv::ZoomFactor() const
    {return iZoomFactor;}

inline CBase* CEikonEnv::Extension() const
    {return iExtension;}

inline TInt CEikonEnv::StatusPaneCoreResId() const
    {return iStatusPaneCoreResId;}

inline void CEikonEnv::SetStatusPaneCoreResId(TInt aStatusPaneCoreResId)
    {iStatusPaneCoreResId=aStatusPaneCoreResId;}

/**
 * @publishedPartner
 * @released
 */
inline CEikAutoMenuTitleArray* CEikonEnv::AutoMenuTitleArray() const
    {return iAutoMenuTitleArray;}

inline const CEikDialog* MEikAlertWin::AsEikDialog() const
    {return (const CEikDialog*)const_cast<MEikAlertWin*>(this)->AsEikDialog();}


/**
 * The enumeration <code>TEikPortFlag</code> defines the printer port settings.
 * This is used by GUI print dialogs.
 */
enum TEikPortFlag
    {
    /** printing is via a serial port */
    ESerialPort =0x01,
    /** printing is via a parallel port */
    EParallelPort =0x02,
    /** printing is via infrared */
    EIrdaPort= 0x04,
    /** printing is to a file */
    EFilePort=0x08,
    /** printing is via a PC */
    EViaPCPort=0x10,
    /** printing is via Bluetooth */
    EBluetoothPort=0x20,
    /** printing via Socket */
    ESocketPort=0x40,
    /** printing via LPR */
    ELprPort=0x80
    };


/**
 * Static method to internalize, i.e. read, a printer port flag from a
 * stream.
 *
 * @since Series90 1.0
 * @param aThing The port to save
 * @param aStream The read stream to save to
 * @remarks
 * @see
 */
IMPORT_C void InternalizeL(TEikPortFlag& aThing,RReadStream& aStream);

/**
 * Externalizes, i.e. writes, a port flag to a stream.
 *
 * @param aStream The stream to be externalized
 * @param aThing The port flag
 * @return the reference to the write stream
 * @remarks
 * @see
 */
inline RWriteStream& operator<<(RWriteStream& aStream,const TEikPortFlag& aThing)
    {aStream.WriteUint8L(aThing);return aStream;}

/**
 * Internalizes, i.e. reads, a port flag to a stream.
 *
 * @param aStream The stream to be internalized
 * @param aThing The port flag
 * @return the reference to the read stream
 * @remarks
 * @see
 */
inline RReadStream& operator>>(RReadStream& aStream,TEikPortFlag& aThing)
    {InternalizeL(aThing,aStream);return aStream;}


#endif //** EIKENV_H *

//** End of File *
